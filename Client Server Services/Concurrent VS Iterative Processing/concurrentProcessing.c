#include <stdlib.h>
#include <stdio.h>

int sum;                             /* sum is global variable */

main() {
	int i;                       /* i is local variable   */
	int returnValue;             /* variable to store the return value  */
	sum = 0;
	returnValue = fork();        /* Create a new process */
	
         
        char nameOfProcess[8]; 
        for (i=1 ; i<=5 ; i++) {            /* iterate i from 1 to 5  */

		printf (" The value of i is %d ", i);

		if(returnValue ==0){  /* Child process */
                strcpy(nameOfProcess, "Child");		
        	printf (" Child \n");

		} else if( returnValue >0 ){   /* parent process */
	                strcpy(nameOfProcess, "parent");	
                	printf ("Parent \n");
                }    

		fflush(stdout);    /* flush the buffer   */
		sum += i;
	}
               printf ("The sum of %s is %d\n ",nameOfProcess, sum);
	exit(0);             /* terminate the program */
}
