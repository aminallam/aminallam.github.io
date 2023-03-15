#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////
// Input and Output ////////////////////////////////////////////////////////////////

struct InFile
{
    FILE* file;

    InFile(const char* str) {file=fopen(str, "r");}
    ~InFile(){if(file) fclose(file);}

    char GetNextTokenChar()
    {
        int ch=fgetc(file);
        if(ch==EOF) return 0;
        return ch;
    }
};

struct OutFile
{
    FILE* file;

    OutFile(const char* str) {file=0; if(str) file=fopen(str, "w");}
    ~OutFile(){if(file) fclose(file);}

    void Out(const char* s)
    {
        fprintf(file, "%s\n", s); fflush(file);
    }
};

////////////////////////////////////////////////////////////////////////////////////
// Compiler Parameters /////////////////////////////////////////////////////////////

struct CompilerInfo
{
    InFile in_file;
    OutFile out_file;
    OutFile debug_file;

    CompilerInfo(const char* in_str, const char* out_str, const char* debug_str)
                : in_file(in_str), out_file(out_str), debug_file(debug_str)
    {
    }
};

////////////////////////////////////////////////////////////////////////////////////
// Scanner /////////////////////////////////////////////////////////////////////////

#define MAX_TOKEN_LEN 40

enum TokenType{
                ID, ASSIGN,
                PLUS, MINUS, TIMES, DIVIDE, POWER,
                LEFT_PAREN, RIGHT_PAREN,
                ERROR, ENDFILE
              };

// Used for debugging only /////////////////////////////////////////////////////////
const char* TokenTypeStr[]=
            {
                "ID", "Assign",
                "Plus", "Minus", "Times", "Divide", "Power",
                "LeftParen", "RightParen",
                "Error", "EndFile"
            };

struct Token
{
    TokenType type;
    char ch;

    Token(){ch=0; type=ERROR;}
    Token(TokenType _type, const char _ch) {type=_type; ch=_ch;}
};

const Token symbolic_tokens[]=
{
    Token(ID, 0), // This line is not used
    Token(ASSIGN, '='),
    Token(PLUS, '+'),
    Token(MINUS, '-'),
    Token(TIMES, '*'),
    Token(DIVIDE, '/'),
    Token(POWER, '^'),
    Token(LEFT_PAREN, '('),
    Token(RIGHT_PAREN, ')')
};
const int num_symbolic_tokens=sizeof(symbolic_tokens)/sizeof(symbolic_tokens[0]);

void GetNextToken(CompilerInfo* pci, Token* ptoken)
{
    ptoken->type=ERROR;
    ptoken->ch=0;

    int i;
    char s=pci->in_file.GetNextTokenChar();

    if(!s)
    {
        ptoken->type=ENDFILE;
        ptoken->ch=0;
        return;
    }

    for(i=0;i<num_symbolic_tokens;i++)
    {
        if(s==symbolic_tokens[i].ch)
        {
            ptoken->type=symbolic_tokens[i].type;
            ptoken->ch=s;
            break;
        }
    }

    if(s>='A'&&s<='Z')
    {
        ptoken->type=ID;
        ptoken->ch=s;
    }
}

////////////////////////////////////////////////////////////////////////////////////
// Parser //////////////////////////////////////////////////////////////////////////

// Extended BNF (EBNF) Grammar:
// ----------------------------
// assignstmt -> id = expr
// expr -> term { (+|-) term }    left associative
// term -> factor { (*|/) factor }    left associative
// factor -> newexpr { ^ newexpr }    right associative
// newexpr -> ( expr ) | id

enum NodeKind{
                ASSIGN_NODE,
                OPER_NODE, ID_NODE
             };

// Used for debugging only /////////////////////////////////////////////////////////
const char* NodeKindStr[]=
            {
                "Assign",
                "Oper", "ID"
            };

#define MAX_CHILDREN 2

struct TreeNode
{
    TreeNode* child[MAX_CHILDREN];

    NodeKind node_kind;

    char id;
    TokenType oper;

    TreeNode() {int i; for(i=0;i<MAX_CHILDREN;i++) child[i]=0;}
};

struct ParseInfo
{
    Token next_token;
};

void Match(CompilerInfo* pci, ParseInfo* ppi, TokenType expected_token_type)
{
    pci->debug_file.Out("Start Match");

    if(ppi->next_token.type!=expected_token_type) throw 0;
    GetNextToken(pci, &ppi->next_token);

    fprintf(pci->debug_file.file, "%c (%s)\n", ppi->next_token.ch, TokenTypeStr[ppi->next_token.type]); fflush(pci->debug_file.file);
}

TreeNode* Expr(CompilerInfo*, ParseInfo*);

// newexpr -> ( expr ) | id
TreeNode* NewExpr(CompilerInfo* pci, ParseInfo* ppi)
{
    pci->debug_file.Out("Start NewExpr");

    // Compare the next token with the First() of possible statements

    if(ppi->next_token.type==ID)
    {
        TreeNode* tree=new TreeNode;
        tree->node_kind=ID_NODE;
        tree->id=ppi->next_token.ch;
        Match(pci, ppi, ppi->next_token.type);

        pci->debug_file.Out("End NewExpr");
        return tree;
    }

    if(ppi->next_token.type==LEFT_PAREN)
    {
        Match(pci, ppi, LEFT_PAREN);
        TreeNode* tree=Expr(pci, ppi);
        Match(pci, ppi, RIGHT_PAREN);

        pci->debug_file.Out("End NewExpr");
        return tree;
    }

    throw 0;
    return 0;
}

// factor -> newexpr { ^ newexpr }    right associative
TreeNode* Factor(CompilerInfo* pci, ParseInfo* ppi)
{
    pci->debug_file.Out("Start Factor");

    TreeNode* tree=NewExpr(pci, ppi);

    if(ppi->next_token.type==POWER)
    {
        TreeNode* new_tree=new TreeNode;
        new_tree->node_kind=OPER_NODE;
        new_tree->oper=ppi->next_token.type;

        new_tree->child[0]=tree;
        Match(pci, ppi, ppi->next_token.type);
        new_tree->child[1]=Factor(pci, ppi);

        pci->debug_file.Out("End Factor");
        return new_tree;
    }
    pci->debug_file.Out("End Factor");
    return tree;
}

// term -> factor { (*|/) factor }    left associative
TreeNode* Term(CompilerInfo* pci, ParseInfo* ppi)
{
    pci->debug_file.Out("Start Term");

    TreeNode* tree=Factor(pci, ppi);

    while(ppi->next_token.type==TIMES || ppi->next_token.type==DIVIDE)
    {
        TreeNode* new_tree=new TreeNode;
        new_tree->node_kind=OPER_NODE;
        new_tree->oper=ppi->next_token.type;

        new_tree->child[0]=tree;
        Match(pci, ppi, ppi->next_token.type);
        new_tree->child[1]=Factor(pci, ppi);

        tree=new_tree;
    }
    pci->debug_file.Out("End Term");
    return tree;
}

// expr -> term { (+|-) term }    left associative
TreeNode* Expr(CompilerInfo* pci, ParseInfo* ppi)
{
    pci->debug_file.Out("Start Expr");

    TreeNode* tree=Term(pci, ppi);

    while(ppi->next_token.type==PLUS || ppi->next_token.type==MINUS)
    {
        TreeNode* new_tree=new TreeNode;
        new_tree->node_kind=OPER_NODE;
        new_tree->oper=ppi->next_token.type;

        new_tree->child[0]=tree;
        Match(pci, ppi, ppi->next_token.type);
        new_tree->child[1]=Term(pci, ppi);

        tree=new_tree;
    }
    pci->debug_file.Out("End Expr");
    return tree;
}

// assignstmt -> id := expr
TreeNode* AssignStmt(CompilerInfo* pci, ParseInfo* ppi)
{
    pci->debug_file.Out("Start AssignStmt");

    TreeNode* tree=new TreeNode;
    tree->node_kind=ASSIGN_NODE;

    if(ppi->next_token.type==ID) tree->id=ppi->next_token.ch;
    Match(pci, ppi, ID);
    Match(pci, ppi, ASSIGN); tree->child[0]=Expr(pci, ppi);

    pci->debug_file.Out("End AssignStmt");
    return tree;
}

TreeNode* Parse(CompilerInfo* pci)
{
    ParseInfo parse_info;
    GetNextToken(pci, &parse_info.next_token);

    TreeNode* syntax_tree=AssignStmt(pci, &parse_info);

    if(parse_info.next_token.type!=ENDFILE)
        pci->debug_file.Out("Error code ends before file ends");

    return syntax_tree;
}

void PrintTree(TreeNode* node, int sh=0)
{
    int i, NSH=3;
    for(i=0;i<sh;i++) printf(" ");

    printf("[%s]", NodeKindStr[node->node_kind]);

    if(node->node_kind==OPER_NODE) printf("[%s]", TokenTypeStr[node->oper]);
    else if(node->node_kind==ID_NODE || node->node_kind==ASSIGN_NODE) printf("[%c]", node->id);

    printf("\n");

    for(i=0;i<MAX_CHILDREN;i++) if(node->child[i]) PrintTree(node->child[i], sh+NSH);
}

void DestroyTree(TreeNode* node)
{
    int i;

    for(i=0;i<MAX_CHILDREN;i++) if(node->child[i]) DestroyTree(node->child[i]);

    delete node;
}

////////////////////////////////////////////////////////////////////////////////////
// Code Generator //////////////////////////////////////////////////////////////////

int Evaluate(TreeNode* node)
{
    if(!node) return 0;
    if(node->node_kind==OPER_NODE)
    {
        printf("(");
        Evaluate(node->child[0]);
        if(node->node_kind==OPER_NODE) printf("%c", symbolic_tokens[node->oper].ch);
        Evaluate(node->child[1]);
        printf(")");
    }
    else if(node->node_kind==ID_NODE)
    {
        printf("%c", node->id);
    }
    return 0;
}

void RunProgram(TreeNode* node)
{
    if(node->node_kind==ASSIGN_NODE)
    {
        Evaluate(node->child[0]);
        printf("\n");
    }
}

////////////////////////////////////////////////////////////////////////////////////
// Scanner and Compiler ////////////////////////////////////////////////////////////

void StartCompiler(CompilerInfo* pci)
{
    TreeNode* syntax_tree=Parse(pci);

    printf("Syntax Tree:\n");
    PrintTree(syntax_tree);
    printf("---------------------------------\n"); fflush(NULL);

    printf("Run Program:\n");
    RunProgram(syntax_tree);
    printf("---------------------------------\n"); fflush(NULL);

    DestroyTree(syntax_tree);
}

////////////////////////////////////////////////////////////////////////////////////
// Scanner only ////////////////////////////////////////////////////////////////////

void StartScanner(CompilerInfo* pci)
{
    Token token;

    while(true)
    {
        GetNextToken(pci, &token);
        printf("%c (%s)\n", token.ch, TokenTypeStr[token.type]); fflush(NULL);
        if(token.type==ENDFILE || token.type==ERROR) break;
    }
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("Start main()\n"); fflush(NULL);
    
    // Create input.txt file which contains something like: A=A+C+B*C^A-(A+B)*C+A^B^C

    CompilerInfo compiler_info("input.txt", "output.txt", "debug.txt");

    //StartScanner(&compiler_info);
    StartCompiler(&compiler_info);

    printf("End main()\n"); fflush(NULL);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////
