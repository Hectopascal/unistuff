//
//  main.c
//  memory
//
//  Created by Richard Buckland on 20/11/12.
//
 
#include <stdio.h>
#include <stdlib.h>
 
long add (int x, int y);
 
int main(int argc, const char * argv[]) {

   
   int x;
   int y;
   long total;
 
   x = 40000;
   y = 2;
 printf("%d",x);
   total = add (x, y);
 
   printf("the sum of %d and %d is %ld\n", x, y, total);
   printf("the address of x is %p\n",&x);
   printf("the address of y is %p\n",&y);
   printf("the address of total is %p\n",&total);
   char c = 200;
 
   printf("\n address of c %d is %p\n",c,&c);
  
   unsigned long ul       = 0;
   unsigned int ui        = 589478;
   unsigned long long ull = 2;
   unsigned short us      = 3;
 
   printf("blah blah %i\n", ui);
	printf("the address of ul is %p\n",&ul);
   printf("the address of ui is %p\n",&ui);    
  	printf("the address of ull is %p\n",&ull);

   printf("address of us is %p\n\n",&us);
  
  
   signed long sl       = -23543;
   signed int si        = 5;
   signed long long sll = 6;
   signed short ss      = 7;

	printf("the address of sl is %p\n",&sl);
   printf("the address of si is %p\n",&si);    
  	printf("the address of sll is %p\n",&sll);
   printf("the address of ss is %p\n",&ss);
   printf("the address of sl is %p\n",&sl);
  
   long l       = 42978029542;
   int i        = 9;
   long long ll = 10;
   short s      = 11;
   printf("%lu\n",l);
   float f = 3.1;
   double d = 3.14;

      printf("size of int is %zu\n",sizeof(int));
   printf("size of long is %zu\n",sizeof(long));
   printf("size of signed long long is %zu\n",sizeof(sll));

   printf("size of short is %zu\n",sizeof(short));
   printf("size of char is %zu\n",sizeof(char));
   printf("size of double is %zu\n",sizeof(double));
   printf("size of float is %zu\n",sizeof(float));
 
   // add them all together just to make use of them so the compiler
   // doesn't grumble that they are unused in the program
 
   double grandTotal;
   grandTotal =  c +
                 ul + ui + ull + us +
                 sl + si + sll + ss +
                  l +  i +  ll +  s +
                  f + d;
 
   printf ("all these things added together make %f\n", grandTotal);
 
   return EXIT_SUCCESS;
}
 
long add (int x, int y) {
   long answer;
   answer = x + y;
 
   return answer;
}
