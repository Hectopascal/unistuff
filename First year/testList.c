//  Created by Bernice Chen on 10/05/2014.
//
//run this testList.c file with a compilable list.c
//that should have the functions declared in list.h implemented 
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
 
 
void test_test();
 
void test_insertAt();
void test_reverse();
 
int main( int argc, char * argv[] ) {
   printf("......STARTING TESTS......\n");
 
   test_test();
   test_insertAt();
   test_reverse();
 
   printf("ALL TESTS PASSED. YOU ARE AWESOME!\n");
 
   return EXIT_SUCCESS;
}
 
void test_test() {
   List l = newList();
   append(l, 0);
   append(l, 1);
   append(l, 2);
   assert ( getValue(l, 0) == 0);
   assert ( getValue(l, 1) == 1);
   assert ( getValue(l, 2) == 2);
 
   printf("EXISTING FUNCTIONS WORK FINE.\n");
}
 
 
//function to test the insertAt() function
void test_insertAt() {
   printf("TESTING insertAt()...\n");
   
 
   //inserting in the beginning
   // 0->1->2->3->X
   // insertAt(l, 0, 9);
   // 0->9->1->2->3->X
   List l = newList();
   append(l, 0);
   append(l, 1);
   append(l, 2);
   append(l, 3);
   insertAt(l, 0, 9);
   assert ( getValue(l, 0) == 0 );
   assert ( getValue(l, 1) == 9 );
   assert ( getValue(l, 2) == 1 );
   assert ( getValue(l, 3) == 2 );
   assert ( getValue(l, 4) == 3 );
   destroy(l);
   printf("insertAt Test1 passed.\n");
 
   //inserting in the middle
   // 0->1->2->3->X
   // insertAt(l, 1, 9);
   // 0->1->9->2->3->X
   l = newList();
   append(l, 0);
   append(l, 1);
   append(l, 2);
   append(l, 3);
   insertAt(l, 1, 9);
   assert ( getValue(l, 0) == 0 );
   assert ( getValue(l, 1) == 1 );
   assert ( getValue(l, 2) == 9 );
   assert ( getValue(l, 3) == 2 );
   assert ( getValue(l, 4) == 3 );
   destroy(l);
   printf("insertAt Test2 passed.\n");
 
 
   //inserting at the end
   // 0->1->2->3->X
   // insertAt(l, 3, 9);
   // 0->1->2->3->9->X
   l = newList();
   append(l, 0);
   append(l, 1);
   append(l, 2);
   append(l, 3);
   insertAt(l, 3, 9);
   assert ( getValue(l, 0) == 0 );
   assert ( getValue(l, 1) == 1 );
   assert ( getValue(l, 2) == 2 );
   assert ( getValue(l, 3) == 3 );
   assert ( getValue(l, 4) == 9 );
   destroy(l);
   printf("insertAt Test3 passed.\n");
 
   //inserting into an empty list
   // (empty list)
   // insertAt(l, 0, 9);
   // 9->X
   l = newList();
   insertAt(l, 0, 9);
   assert ( getValue(l, 0) == 9 );
   destroy(l);
   printf("insertAt Test4 passed.\n");
 
   printf("ALL insertAt() TESTS PASSED!\n");
 
}
 
 
void test_reverse() {
   printf("TESTING reverse()...\n");
   
   //reversing linked list of length>3
   // 0->1->2->3->X
   // reverse(l);
   // 3->2->1->0->X
   List l = newList();
   append(l, 0);
   append(l, 1);
   append(l, 2);
   append(l, 3);
   reverse(l);
   assert ( getValue(l, 0) == 3 );
   assert ( getValue(l, 1) == 2 );
   assert ( getValue(l, 2) == 1 );
   assert ( getValue(l, 3) == 0 );
   destroy(l);
   printf("reverse Test1 passed.\n");
 
   //reversing linked list of length==2
   // 0->1->X
   // reverse(l);
   // 1->0->X
   l = newList();
   append(l, 0);
   append(l, 1);
   reverse(l);
   assert ( getValue(l, 0) == 1 );
   assert ( getValue(l, 1) == 0 );
   destroy(l);
   printf("reverse Test2 passed.\n");
 
   //reversing linked list of length==1
   // 0->X
   // reverse(l);
   // 0->X
   l = newList();
   append(l, 0);
   reverse(l);
   assert ( getValue(l, 0) == 0 );
   destroy(l);
   printf("reverse Test3 passed.\n");
 
   //reversing linked list of length==0
   // (empty list)
   // reverse(l);
   // (still empty list)
   l = newList();
   reverse(l);
   destroy(l);
   printf("reverse Test4 passed.\n");
 
   printf("ALL reverse() TESTS PASSED!\n");
 
}
 
 
 
 
 
 
 
