    /*
     *  testBackToFront.h
     *  UNSW comp1917
     *
     *  Created by David Collien & Richard Buckland
     *  Share freely CC-BY-3.0
     *
     *  this program runs a simple test for moving the
     *  last element of a list to the front of the list
     *  by changing pointers.
     */
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "backToFront.h"
     
    #define FIRST  1
    #define SECOND 2
    #define THIRD  3
    #define FOURTH 4
    #define FIFTH  5
    #define SIXTH  6
     
    void testBackToFront (void);
     
    int main (int argc, char *argv[]) {
       printf ("Running unit tests on backToFront()...\n");
       testBackToFront();
       printf ("All PRAC EXAM tests passed! You are AWESOME!\n");
       
       return EXIT_SUCCESS;
    }
     
    void testBackToFront (void) {
       
       nodePtr inputList;
       nodePtr outputList;
       
       node first;
       node second;
       node third;
       node fourth;
       node fifth;
       node sixth;
       
       first.value = FIRST;
       second.value = SECOND;
       third.value = THIRD;
       fourth.value = FOURTH;
       fifth.value = FIFTH;
       sixth.value = SIXTH;
       
       
       printf ("TEST 1: testing backToFront on an empty list...\n");
       inputList = NULL;
       outputList = backToFront (inputList);
       assert (outputList == NULL);
       printf ("... TEST 1 passed!\n");
       
       
       
       printf ("TEST 2: testing backToFront on a single item list...\n");
       
       inputList = &first;
       first.next = NULL;
       
       outputList = backToFront (inputList);
       assert (outputList == &first);
       assert (outputList->value == FIRST);
       assert (outputList->next == NULL);
       
       printf ("... TEST 2 passed!\n");
       
       
       
       printf ("TEST 3: testing backToFront on double item list...\n");
       
       inputList = &first;
       first.next = &second;
       second.next = NULL;
       
       outputList = backToFront (inputList);
       assert (outputList == &second);
       
       assert (outputList->value == SECOND);
       assert (outputList->next == &first); // 9
       
       assert (outputList->next->value == FIRST);
       assert (outputList->next->next == NULL);
       
       printf ("... TEST 3 passed!\n");
       
       
       
       printf ("TEST 4: testing backToFront on 6 item list...\n");
       
       // input list is first->...->sixth->NULL
       inputList = &first;
       first.next = &second;
       second.next = &third;
       third.next = &fourth;
       fourth.next = &fifth;
       fifth.next = &sixth;
       sixth.next = NULL;
       
       outputList = backToFront (inputList);
       // after moving back to front the output list should be
       // sixth->first->second->third->fourth->fifth;
       
       
       printf ("   test that the links are correct\n" );
       
       assert (outputList  == &sixth);
       assert (sixth.next  == &first);
       assert (first.next  == &second);
       assert (second.next == &third);
       assert (third.next  == &fourth);
       assert (fourth.next == &fifth);
       assert (fifth.next  == NULL);
       
       printf ("   YES, links are correct\n" );
       
       printf ("   test that node values have not been changed\n" );
       
       assert(first.value  == FIRST);
       assert(second.value == SECOND);
       assert(third.value  == THIRD);
       assert(fourth.value == FOURTH);
       assert(fifth.value  == FIFTH);
       assert(sixth.value  == SIXTH);
       
       printf ("   YES, node values have not been changed\n" );
       
       printf ("... TEST 4 passed!\n");
       
       
       
       
    }
