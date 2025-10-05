#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 

main()
{
char *args[3];       // Declare array of character pointers for command arguments

printf("Listing contents of current directory in long format:\n");  // Display header message
printf("==========================================\n");   // Display separator line

args[0] = "ls";      // Set first argument to "ls" command
args[1] = "-l";      // Set second argument to "-l" flag for long format
args[2] = NULL;      // Set third argument to NULL to terminate argument list

execvp("ls", args);  // Replace current process with ls command
}
