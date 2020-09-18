#include <stdio.h>
#include <stdlib.h>
#include <time.h>//checking the execution time of code.

/* Declare global variables, including a buffer as a dynamic array of integers */
int *buffer = NULL;
int max_fill_size = 0;
int max_empty_size = 0;
int number_iterations = 0;
int bufferSize = 0;
int e;
int f;
int next_in;
int next_out;
/***************************************************************/
void optionOne() {
	
	/* Declare local variables */
	/* Prompt for size of the buffer and allocate memory */
   printf("\nEnter size of the buffer: ");
   scanf("%d", &bufferSize);
   printf("%d", bufferSize);
   buffer  = (int *)calloc(bufferSize,sizeof(int));
	/* Prompt for max_fill_size, max_empty_size, number of iterations */
   printf("\nEnter maximum fill size: ");
   scanf("%d", &max_fill_size);
   printf("%d", max_fill_size);
   
   printf("\nEnter maximum empty size: ");
   scanf("%d", &max_empty_size);
   printf("%d", max_empty_size);
   
   printf("\nEnter maximum number of iterations: ");
   scanf("%d", &number_iterations);
   printf("%d", number_iterations);
   
	return;
}


/******NOTE: replace "variable" with an actual variable*********/
int p(int var) {
	/* Decrement "variable" if non-negative */
   if(var > 0)
   {
      var=var - 1;
   }
	return var;
}


/******NOTE: replace "variable" with an actual variable*********/
int v(int var) {
/* Increment "variable" if it is less than the size of the buffer */
   if(var < bufferSize)
   {
      var=var + 1;
   }
	return var;
}


/***************************************************************/
void printBufferProcedure() {
   //PROCEDURE TO PRINT THE CONTENTS OF THE BUFFER
	/* Declare local variables */
	int i;
	/* Print each element in a for-loop */
   printf("Buffer=");
   for(i = 0; i < bufferSize; i++)
   {
      printf("%d",buffer[i]);
   }
	return;
}
	

/***************************************************************/
void producerProcedure() {
	
	/* Declare/initilize k1 of type clock_t to hold random value between 1 and max_fill_size, using function: clock() */
   clock_t k1 = clock() % max_fill_size + 1;
	/* Declare other local variables */	
   int i;	
	/* For each cell of the buffer to fill from 1 to k1 */
   for(i = 1; i < k1; i++)
   {
		/* if not full, decrement e semaphore */
      if(e>0)
      {
         e=p(e);
   		/* increment buffer cell referenced by next_in */
         buffer[next_in] = 1;
   		/* increment value of next_in modulo n */
         next_in= (next_in + 1) % bufferSize;
   		/* increment f semaphore */
         f=v(f);
      }
   }		
	/* call procedure to print contents of buffer */
   printf("\nP[%ld]: ",k1);
   printBufferProcedure();
	return;
}			


/***************************************************************/
void consumerProcedure() {
	/* Declare/initilize k2 of type clock_t to hold random value between 1 and max_empty_size, using function: clock() */
   clock_t k2 = clock() % max_empty_size + 1;
	/* Declare other local variables */
   int i;		
	/* For each cell of the buffer to empty from 1 to k2 */
   for(i = 1; i < k2; i++)
   {
		/* if not empty, decrement f semaphore */
      if(f>0)
      {
         f=p(f);
   		/* reset buffer cell referenced by next_out */
         buffer[next_out] = 0;
   		/* increment value of next_out modulo n */
         next_out = (next_out +1) % bufferSize; 
   		/* increment e semaphore */
         e=v(e);
      }
   }
	/* call procedure to print contents of buffer */
   printf("\nC[%ld]: ",k2);
   printBufferProcedure();
	return;
}


/**********************************************/
void optionTwo() {
   //SIMULATEFUNCTION
	/* Declare variable pc of type clock_t to be used for randomly selecting between the producer and consumer */
   clock_t var;
   e = bufferSize;
   f = 0;
   next_in = 0;
   next_out = 0;
	/* Declare other local variables */
   int i = 0;
	/* For each iteration */
		/* Set pc to a random value between 0 and 1 */
		/* if pc is 0, call the producer procedure */
		/* else, call the consumer procedure */
   for(i = 0; i < number_iterations; i++)
   {
      var = clock() % 2;
      if(var == 0)
      {
         producerProcedure();
      }
      else
      {
         consumerProcedure();
      }
   }
	return;
}


/***************************************************************/
void optionThree() {
   //GARBAGE COLLECTION (optional)
	/* If the buffer is not NULL, free the buffer */
   printf("\nQuitting Program");
   if(buffer != NULL)
   {
      free(buffer);
   }
	return;
}


/***************************************************************/
int main() {
	/* Declare local var's */
    int userInput = -1;
/* Until user quits */
	/* print menu of options, prompt for user input, and select appropriate option */
	 while(userInput != 3)
    {
        printf("\nProducer-Consumer problem");
        printf("\n--------------------------");
        printf("\n1) Enter parameters\n2) Simulate on a shared circular buffer\n3) Quit program and free memory");
        printf("\n\nEnter selection: ");
        scanf("%d", &userInput);
        printf("%d", userInput);
        if(userInput == 1)
        {
            optionOne();
        }
        if(userInput ==2)
        {
            optionTwo();
        }
        if(userInput ==3)
        {
            optionThree();
        }
    }
}
