/* sequential.c - A conventional C program that sums integers from 1 to 5 */


#include <stdlib.h> 
#include <stdio.h>
int sum;				/* sum is a global variable */

main() {
	int i;				/* i is a local variable    */

	sum = 0;
	for (i=1 ; i<=5 ; i++){         /* iterate i from 1 to 5    */
		printf("The value of i is %d\n", i);
		fflush(stdout);         /* flush the buffer         */
		sum += i;
	}
	printf("The sum is %d\n", sum);
	exit(0);			/* terminate the program    */
}


 

