#include <stdio.h>
#include <unistd.h>
#include <time.h>

main()
{
int i;               // Declare an integer variable
time_t time1;        // Declare time_t variable to store current time
char* time_string;   // Declare character pointer to store formatted time string
char *args[2];       // Declare an array of character pointers for execvp() arguments

time1 = time(NULL);  // Get current time in seconds

time_string = ctime(&time1);  // Convert time to human-readable string format
printf("This line is from replace1 and the current time is %s", time_string);  // Display message with current time

printf("i=%d ... Now starting list100 program\n", i);  // Display message before starting list100

args[0] = "list100";  // Set first argument to program name "list100"
args[1] = NULL;       // Set second argument to NULL to terminate argument list

execvp("./list100", args);  // Execute the list100 program with arguments
}