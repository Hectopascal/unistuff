#include <stdio.h>

int main(int argc, char * argv[]){
	int x = 3;
	int y = 10;

	int * p; //address of some int
	char * p2; //address of some char

	p = &x; 

	printf("x is %d\n",x);
	printf("address of x is %p\n",&x); 
	// &x shows the address of x, i.e the memory where x is saved (while program is running)
	// '0x' at start of address indicates that it is a hexadecimal

	printf("p is %p\n",p); //this will print the address of x, which is stored as variable p

	printf("%d\n",*p); 
	//as the asterisk dereferences p, which will redirect it to the address in p. Since x = 3 is stored in that address, 3 is returned.
	//for more info search 'dereferencing pointer'

	p = &y; //overwrites the variable p = &x
	printf("%d\n",*p); //address stored in p is now that of y; y = 10, therefore will return 10.

	*p = *p +1 // this is the same as y = y + 1
	print("%d\n",y);
	return 0;
}

//%d prints normal number
//%p prints address (as hex)

/* in otherwords
if p is &y (the address),
*p is y (the value stored).

the asterisk dereferences p, reversing the address-value thingy or sth*/
