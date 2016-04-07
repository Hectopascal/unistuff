    /*
     *  testQ1.c
     *  comp1917 final prac exam
     *  some unit tests for Q1.c
     *  Richard Buckland: 21 june 2014
     *  
     *
     */
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "list.h"
     
    static void testQ1 (void);
     
    static node *newNode (int item);
     
    int main (int argc, const char * argv[]) {
       
       printf ("About to test Q1.c the FIRST redact function\n");
       testQ1();   
       printf ("\nAll Q1.c redact tests passed!  You are Awesome!\n\n");
       printf ("1. Submit your Q1.c solution\n");
       printf (" and then \n");
       printf ("2. Implement the modified redact #2 function in Q2.c\n");
       
       return EXIT_SUCCESS;
    }
     
    void testQ1 (void) {
       
       // create 10 nodes, names indicate their value, next=NULL
       node *nodeO = newNode ('o');
       node *nodeN = newNode ('n');
       node *nodeE = newNode ('e');
       node *nodeT = newNode ('t');
       node *nodeC = newNode ('c');
       node *nodeA = newNode ('a');
       node *nodeM = newNode ('m');
       node *nodeW = newNode ('w');
       node *nodeR = newNode ('r');
       node *nodeK = newNode ('k');
       node *nodeI = newNode ('i');
       
       printf ("testing redact on empty list \n");
       list testList  = malloc (sizeof (list*));
       assert (testList != NULL);
       testList->head = NULL;
       
       redact (testList, 'e');  // == NULL
       assert (testList->head == NULL);
       printf ("test passed!\n");
         
       printf ("testing a one letter list - redact nothing\n");
       testList->head = nodeK;
       nodeK->next = NULL;
       
       redact (testList,'e');  // no effect
       assert (testList->head == nodeK);
       assert (nodeK->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a one letter list - redact one\n");
       redact (testList,'k');  // no effect
       assert (testList->head == NULL);
       printf ("test passed!\n");
     
       printf ("testing a two letter list - redact nothing\n");
       testList->head = nodeK;
       nodeK->next = nodeI;
       nodeI->next = NULL;
       
       redact (testList,'e');  // no effect
       assert (testList->head == nodeK);
       assert (nodeK->next == nodeI);
       assert (nodeI->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a two letter list - redact first\n");
       redact (testList,'k');  // no effect
       assert (testList->head == nodeI);
       assert (nodeI->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a two letter list - redact last\n");
       testList->head = nodeO;
       nodeO->next = nodeK;
       nodeK->next = NULL;
     
       redact (testList,'k');  // no effect
       assert (testList->head == nodeO);
       assert (nodeO->next == NULL);
       printf ("test passed!\n");
     
     
       printf ("testing a three letter list - redact nothing\n");
       testList->head = nodeO;
       nodeO->next = nodeN;
       nodeN->next = nodeE;
       nodeE->next = NULL;
       
       redact (testList,'i');  // no effect
       assert (testList->head == nodeO);
       assert (nodeO->next == nodeN);
       assert (nodeN->next == nodeE);
       assert (nodeE->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a three letter list - redact first\n");
       redact (testList,'o');  // no effect
       assert (testList->head == nodeN);
       assert (nodeN->next == nodeE);
       assert (nodeE->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a three letter list - redact middle\n");
       testList->head = nodeO;
       nodeO->next = nodeN;
       nodeN->next = nodeE;
       nodeE->next = NULL;
       
       redact (testList,'n');  // no effect
       assert (testList->head == nodeO);
       assert (nodeO->next == nodeE);
       assert (nodeE->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a three letter list - redact last\n");
       testList->head = nodeO;
       nodeO->next = nodeN;
       nodeN->next = nodeE;
       nodeE->next = NULL;
       
       redact (testList,'e');  // no effect
       assert (testList->head == nodeO);
       assert (nodeO->next == nodeN);
       assert (nodeN->next == NULL);
       printf ("test passed!\n");
     
     
       printf ("testing a four letter list - redact nothing\n");
       testList->head = nodeO;
       nodeO->next = nodeN;
       nodeN->next = nodeC;
       nodeC->next = nodeE;
       nodeE->next = NULL;
       
       redact (testList,'i');  // no effect
       assert (testList->head == nodeO);
       assert (nodeO->next == nodeN);
       assert (nodeN->next == nodeC);
       assert (nodeC->next == nodeE);
       assert (nodeE->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a four letter list - redact first\n");
       redact (testList,'o');  // no effect
       assert (testList->head == nodeN);
       assert (nodeN->next == nodeC);
       assert (nodeC->next == nodeE);
       assert (nodeE->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a four letter list - redact second\n");
       testList->head = nodeO;
       nodeO->next = nodeN;
       nodeN->next = nodeC;
       nodeC->next = nodeE;
       nodeE->next = NULL;
       
       redact (testList,'n');  // no effect
       assert (testList->head == nodeO);
       assert (nodeO->next == nodeC);
       assert (nodeC->next == nodeE);
       assert (nodeE->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a four letter list - redact third\n");
       testList->head = nodeO;
       nodeO->next = nodeN;
       nodeN->next = nodeC;
       nodeC->next = nodeE;
       nodeE->next = NULL;
       
       redact (testList,'c');  // no effect
       assert (testList->head == nodeO);
       assert (nodeO->next == nodeN);
       assert (nodeN->next == nodeE);
       assert (nodeE->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a four letter list - redact last\n");
       testList->head = nodeO;
       nodeO->next = nodeN;
       nodeN->next = nodeC;
       nodeC->next = nodeE;
       nodeE->next = NULL;
       
       redact (testList,'e');  // no effect
       assert (testList->head == nodeO);
       assert (nodeO->next == nodeN);
       assert (nodeN->next == nodeC);
       assert (nodeC->next == NULL);
       printf ("test passed!\n");
     
     
     
     
     
       printf ("testing a long list - redact none\n");
       testList->head = nodeT;
       nodeT->next = nodeE;
       nodeE->next = nodeA;
       nodeA->next = nodeM;
       nodeM->next = nodeW;
       nodeW->next = nodeO;
       nodeO->next = nodeR;
       nodeR->next = nodeK;
       nodeK->next = NULL;
       
       redact (testList,'i');  // no effect
       assert (testList->head == nodeT);
       assert (nodeT->next == nodeE);
       assert (nodeE->next == nodeA);
       assert (nodeA->next == nodeM);
       assert (nodeM->next == nodeW);
       assert (nodeW->next == nodeO);
       assert (nodeO->next == nodeR);
       assert (nodeR->next == nodeK);
       assert (nodeK->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a long list - redact first\n");
       testList->head = nodeT;
       nodeT->next = nodeE;
       nodeE->next = nodeA;
       nodeA->next = nodeM;
       nodeM->next = nodeW;
       nodeW->next = nodeO;
       nodeO->next = nodeR;
       nodeR->next = nodeK;
       nodeK->next = NULL;
       
       redact (testList,'t');  // no effect
       assert (testList->head == nodeE);
       assert (nodeE->next == nodeA);
       assert (nodeA->next == nodeM);
       assert (nodeM->next == nodeW);
       assert (nodeW->next == nodeO);
       assert (nodeO->next == nodeR);
       assert (nodeR->next == nodeK);
       assert (nodeK->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a long list - redact m\n");
       testList->head = nodeT;
       nodeT->next = nodeE;
       nodeE->next = nodeA;
       nodeA->next = nodeM;
       nodeM->next = nodeW;
       nodeW->next = nodeO;
       nodeO->next = nodeR;
       nodeR->next = nodeK;
       nodeK->next = NULL;
       
       redact (testList,'m');  // no effect
       assert (testList->head == nodeT);
       assert (nodeT->next == nodeE);
       assert (nodeE->next == nodeA);
       assert (nodeA->next == nodeW);
       assert (nodeW->next == nodeO);
       assert (nodeO->next == nodeR);
       assert (nodeR->next == nodeK);
       assert (nodeK->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a long list - redact w\n");
       testList->head = nodeT;
       nodeT->next = nodeE;
       nodeE->next = nodeA;
       nodeA->next = nodeM;
       nodeM->next = nodeW;
       nodeW->next = nodeO;
       nodeO->next = nodeR;
       nodeR->next = nodeK;
       nodeK->next = NULL;
       
       redact (testList,'w');  // no effect
       assert (testList->head == nodeT);
       assert (nodeT->next == nodeE);
       assert (nodeE->next == nodeA);
       assert (nodeA->next == nodeM);
       assert (nodeM->next == nodeO);
       assert (nodeO->next == nodeR);
       assert (nodeR->next == nodeK);
       assert (nodeK->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a long list - redact o\n");
       testList->head = nodeT;
       nodeT->next = nodeE;
       nodeE->next = nodeA;
       nodeA->next = nodeM;
       nodeM->next = nodeW;
       nodeW->next = nodeO;
       nodeO->next = nodeR;
       nodeR->next = nodeK;
       nodeK->next = NULL;
       
       redact (testList,'o');  // no effect
       assert (testList->head == nodeT);
       assert (nodeT->next == nodeE);
       assert (nodeE->next == nodeA);
       assert (nodeA->next == nodeM);
       assert (nodeM->next == nodeW);
       assert (nodeW->next == nodeR);
       assert (nodeR->next == nodeK);
       assert (nodeK->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a long list - redact r\n");
       testList->head = nodeT;
       nodeT->next = nodeE;
       nodeE->next = nodeA;
       nodeA->next = nodeM;
       nodeM->next = nodeW;
       nodeW->next = nodeO;
       nodeO->next = nodeR;
       nodeR->next = nodeK;
       nodeK->next = NULL;
       
       redact (testList,'r');  // no effect
       assert (testList->head == nodeT);
       assert (nodeT->next == nodeE);
       assert (nodeE->next == nodeA);
       assert (nodeA->next == nodeM);
       assert (nodeM->next == nodeW);
       assert (nodeW->next == nodeO);
       assert (nodeO->next == nodeK);
       assert (nodeK->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a long list - redact last\n");
       testList->head = nodeT;
       nodeT->next = nodeE;
       nodeE->next = nodeA;
       nodeA->next = nodeM;
       nodeM->next = nodeW;
       nodeW->next = nodeO;
       nodeO->next = nodeR;
       nodeR->next = nodeK;
       nodeK->next = NULL;
       
       redact (testList,'k');  // no effect
       assert (testList->head == nodeT);
       assert (nodeT->next == nodeE);
       assert (nodeE->next == nodeA);
       assert (nodeA->next == nodeM);
       assert (nodeM->next == nodeW);
       assert (nodeW->next == nodeO);
       assert (nodeO->next == nodeR);
       assert (nodeR->next == NULL);
       printf ("test passed!\n");
     
     
     
     
     
     
     
       printf ("testing node values have not changed\n");
       
       assert (nodeO->value == 'o');
       assert (nodeN->value == 'n');
       assert (nodeE->value == 'e');
       assert (nodeT->value == 't');
       assert (nodeC->value == 'c');
       assert (nodeA->value == 'a');
       assert (nodeM->value == 'm');
       assert (nodeW->value == 'w');
       assert (nodeR->value == 'r');
       assert (nodeK->value == 'k');
       assert (nodeI->value == 'i');
       printf ("test passed!\n");
     
     
     
       printf ("testing that no nodes have been freed\n...");
       // free the nodes - not needed in subsequent tests
       // might fail if students have inadventantly freed nodes
       // already
       free (nodeO);
       free (nodeN);
       free (nodeE);
       free (nodeT);
       free (nodeC);
       free (nodeA);
       free (nodeM);
       free (nodeW);
       free (nodeR);
       free (nodeK);
       free (nodeI);
       
       printf ("test passed!\n");
    }   
     
    static node *newNode (int item) {
       node *new = malloc (sizeof (node));
       assert (new != NULL);
       new->value = item;
       new->next  = NULL;
       
       return new;
    }
