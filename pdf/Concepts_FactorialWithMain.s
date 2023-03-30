# To download gcc on windows:
# download mingw (and make sure gcc is chosen while installation) from: 
# mingw-get-setup.exe at the site https://osdn.net/projects/mingw/
# then append c:\mingw\bin; to the start of the PATH environment variable from control panel

# To compile this assembly program on windows:
# gcc -O3 -o factorialwithmain.exe factorialwithmain.s
# After running the program, enter a positive integer (n>=0) and then press enter

#-----------------------------------------------------------------------------------------------------

.intel_syntax noprefix  # use the intel syntax, not AT&T syntax. do not prefix registers with %

#-----------------------------------------------------------------------------------------------------

.section .data        # initialized memory variables, will be part of the exe

input: .asciz "%d"    # string terminated by 0 that will be used for scanf parameter
output: .asciz "The factorial is: %d\n"     # string terminated by 0 that will be used for printf parameter

n: .int 0             # the variable n which we will get from user using scanf

#-----------------------------------------------------------------------------------------------------

.section .text        # instructions

.globl _Factorial

_Factorial:         # it takes as parameters the integer n and returns the factorial in %eax. C expects that too.

   push ebp         # we will use %ebp to access parameters and local variables. before doing this, we will save the old one
   mov ebp, esp     # now we can use %ebp to access parameters and local variables
   sub esp, 4       # reserve space for the local variables
   
   push edi         # the registers %edi, %esi, %ebx must be preserved (for C if this function is called from C) if they will be used here
   push esi
   push ebx

   #--------------------------------------------------------------------------------------------------

   #         Function parameter 1   [ebp+8]  (n)
   #         Return Address         [ebp+4]
   # ebp ->  Old ebp Value          [ebp]
   # esp ->  Local Variable 1       [ebp-4]  (f)

   #--------------------------------------------------------------------------------------------------

   mov ebx, [ebp+8]     # ebx=n
   
   mov eax, 1           # eax=1 (the return value)
   cmp eax, ebx         # compare eax,ebx (1,n) and update status register
   jge end_fun          # if 1>=n: end this function by jumping to label end_fun (the return value eax=1)
   
   mov [ebp-4], ebx     # f=ebx (f=n)

   sub ebx, 1           # ebx=n-1
   push ebx             # push to stack the first parameter to _Factorial (n-1)
   call _Factorial
   add esp, 4           # pop the above parameter from the stack
                        # now, eax contains Factorial(n-1)

   imul DWORD PTR [ebp-4]  # multiplies eax * [ebp-4] (Factorial(n-1)*f where f=n) and saves the result in [edx,eax]
                        # now, eax contains Factorial(n) (we will ignore the high order bits in edx)

   #---------------------------------------------------------------------------------------------------

end_fun:

   pop ebx
   pop esi
   pop edi
   
   mov esp, ebp
   pop ebp
   
   ret

#------------------------------------------------------------------------------------------------------

.globl _main           # make _main accessible from external

_main:                 # the label indicating the start of the program

   # get the number of integers from the user ---------------------------------------------------------

   push OFFSET n       # push to stack the second parameter to scanf (the address of the integer variable n)
   push OFFSET input   # push to stack the first parameter to scanf
   call _scanf         # call scanf, it will use the two parameters on the top of the stack in the reverse order
   add esp, 8          # pop the above two parameters from the stack (the esp register keeps track of the stack top, 8=2*4 bytes popped as param was 4 bytes)

   # calculate the factorial of the n integers --------------------------------------------------------

   push n              # push to stack the first parameter to _Factorial
   call _Factorial
   add esp, 4          # pop the above parameter from the stack

   # print the factorial of integers ------------------------------------------------------------------

   push eax            # push to stack the second parameter to printf
   push OFFSET output  # push to stack the first parameter to printf
   call _printf        # call printf
   add esp, 8          # pop the two parameters

   ret                 # end the main function
   
#------------------------------------------------------------------------------------------------------

#.type _Factorial, @function  # this line is needed for linux
