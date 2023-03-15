#include <cstdio>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////

int GetPositiveInteger(char* s)
{
    if(*s==0) return -1;
    int v=0;
    while(*s)
    {
        if(*s<'0'||*s>'9') return -1;
        v=v*10+*s-'0';
        s++;
    }
    return v;
}

void GetAscii(unsigned char ch, char* ascii)
{
    if(ch<32 || ch>126) {ascii[0]=ascii[1]='0'; return;}
    ascii[1]=ch%16; ch=ch/16; ascii[0]=ch%16;
    if(ascii[0]<10) ascii[0]+='0'; else ascii[0]=ascii[0]-10+'A';
    if(ascii[1]<10) ascii[1]+='0'; else ascii[1]=ascii[1]-10+'A';
}

//////////////////////////////////////////////////////////////////////////////////////////

void Encode(int n, char* s[])
{
    if(n<5)
    {
        printf("Too few arguments. The command must include: filename, assignment ID, number of students, and student IDS.\n"
                   "Example: assign_encode ./myassign.txt 1 3 20120001 20120071 20120301\n");
        fflush(stdout); return;
    }

    char* input_file_name=s[1];

    if(*input_file_name==0) {printf("Incorrect file name (%s)\n", s[1]); fflush(stdout); return;}

    int assign_id=GetPositiveInteger(s[2]);
    int num_students=GetPositiveInteger(s[3]);

    if(assign_id<=0 || assign_id>9) {printf("Incorrect assignment ID (%s)\n", s[2]); fflush(stdout); return;}

    if(num_students<=0 || num_students>=10) {printf("Incorrect number of students (%s)\n", s[3]); fflush(stdout); return;}
    if(num_students+4!=n) {printf("The number of entered IDs does not equal to the entered number of students.\n"); fflush(stdout); return;}

    char output_file_name[1000];
    int i, cur=0;
    sprintf(output_file_name+cur, "./assign_%d", assign_id); cur+=10;
    for(i=0;i<num_students;i++)
    {
        int student_id=GetPositiveInteger(s[4+i]);
        if(student_id<20000000||student_id>21000000) {printf("Incorrect student ID (%s).\n", s[4+i]); fflush(stdout); return;}
        sprintf(output_file_name+cur, "_%d", student_id); cur+=9;
    }

    sprintf(output_file_name+cur, ".bin");

    char input_file_data[50*1024];
    char output_file_data[2*50*1024];

    FILE* input_file=fopen(input_file_name, "rb");
    if(input_file==0) {printf("Cannot open the input file (%s).\n", input_file_name); fflush(stdout); return;}

    int ind=0, cnt=fread(input_file_data, 1, 50*1024, input_file);
    if(cnt<=0) {printf("Cannot read the input file (%s).\n", input_file_name); fflush(stdout); return;}
    if(cnt>=15*1010) {printf("The input file size must be less than 15,000 characters.\n"); fflush(stdout); return;}

    int last_char=-1;

    for(i=0;i<cnt;i++)
    {
        int cur_char=input_file_data[i];
        if(cur_char+last_char==23) {last_char=-1; continue;}

        if(cur_char!=10 && cur_char!=13 && !(cur_char>=32 && cur_char<=126))
        {
            if(cur_char==9) {printf("TAB characters are not allowed. Convert each TAB to 4 spaces then try again.\n"); fflush(stdout); return;}
            else {printf("The character with ascii code (%d) is not allowed.\n", cur_char); fflush(stdout); return;}
        }

        GetAscii(cur_char, output_file_data+ind);
        ind+=2;
        last_char=cur_char;
    }
    output_file_data[ind]=0;

    fclose(input_file);

    FILE* output_file=fopen(output_file_name, "wt");
    if(output_file==0) {printf("Cannot open the output file (%s).\n", output_file_name); fflush(stdout); return;}

    fwrite(output_file_data, 1, ind, output_file);

    fclose(output_file);
}

//////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    Encode(argc, argv);

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
