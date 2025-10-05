#include <stdio.h>
#include <unistd.h>

main() 
{
char program[80],*a[2];  // Declare a character array for program name and argument array
int i;                   // Declare an integer variable to store return value from execvp()
printf ("\n");           // Print a blank line
strcpy(program, "replace1");  // Copy string "replace1" into program array
printf(" This line is from source1 \n");  // Display message
strcpy(program, "replace1");  // Copy string "replace1" into program array again
a[0] = "replace1";       // Set first argument to program name "replace1"
a[1] = NULL;             // Set second argument to NULL
i = execvp(program, a);  // Execute the program specified by 'program' with arguments 'a'
printf("i=%d ... End of Source1", i);  // This line should never execute if execvp() succeeds
}