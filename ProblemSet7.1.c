#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<math.h>
//#define max 100
//#define thefile "sine.dat"
//#define x 2


/*compiled code here
gcc ProblemSet7.1.c -o 7.1 && ./7.1
*/



char* commandsForGnuplot[] = {"plot \"sine.dat\" every ::0::100 w linespoint"};


int main()
{
    FILE * gnuplotPipe = popen("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "%s", commandsForGnuplot[0]); //Send commands to gnuplot one by one.

    fflush(gnuplotPipe);
    //system("gnuplot --persist -e \"plot '< head -100 sine.dat' using 1:2 w lines\"");


    pclose(gnuplotPipe);
  
    return 0;
  }