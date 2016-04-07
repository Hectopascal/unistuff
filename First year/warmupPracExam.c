/*Put your program in a file called warmupPracExam.c

Write a program which reads in any odd number, n > 0, and which prints out 
an nxn square containing a cross exactly matching the format below.

Print a newline character ('\n') at the end of each line (including the last line).  
You may assume that n is odd.

*/

#include <stdlib.h>
#include <stdio.h>

void cross(int n);

 int main(int argc, char *argv[])
{
    int n;

    scanf("%d",&n);

    cross(n);

    return 0;
}

void cross(int n){
    int size = n;
    int columns = 0;
    int rows = 0;
    while(rows < n){
        
        while(columns < n){
            if(columns == rows || columns + rows == size - 1){
                printf("#");
                columns++;
            }else{
            printf("-");
            columns++;
            }
        }
        printf("\n");
        columns = 0;
        rows++;
    }

}