    /*
     *  testQ2.c
     *  comp1917 final prac exam
     *  some unit tests for Q2.c
     *  Richard Buckland: 21 june 2014
     *  
     *
     */
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "list.h"
     
    static void testQ2unique (void);
    static void testQ2duplicates (void);
     
    static node *newNode (int item);
     
    int main (int argc, const char * argv[]) {
       
       printf ("About to test the Q2 redact function\n");
       printf ("(testing on lists which have no duplicates)\n");   
       testQ2unique();   
       printf ("All no dups tests passed - well done.\n");
       printf ("About to test the Q2 redact function\n");
       printf ("(testing on lists which have duplicates)\n");   
       testQ2duplicates();   
       printf ("All Q2 redact tests passed - well done.\n");
       printf ("You are Awesome!\n\n");
       
       return EXIT_SUCCESS;
    }
     
     
    void testQ2duplicates (void) {
       
       // create test nodes, names indicate their value, next=NULL
       node *nodeO  = newNode ('o');
       node *nodeC  = newNode ('c');
       node *nodeU  = newNode ('u');
       node *nodeP  = newNode ('p');
       node *nodeI  = newNode ('i');
       node *nodeE  = newNode ('e');
       node *nodeD  = newNode ('d');
     
       node *nodeC1 = newNode ('c');
       node *nodeE1 = newNode ('e');
       node *nodeE2 = newNode ('e');
       node *nodeE3 = newNode ('e');
       node *nodeE4 = newNode ('e');
       node *nodeE5 = newNode ('e');
       node *nodeE6 = newNode ('e');
       
       node *nodeO1 = newNode ('o');
       node *nodeO2 = newNode ('o');
       node *nodeO3 = newNode ('o');
       node *nodeO4 = newNode ('o');
       node *nodeO5 = newNode ('o');
     
       list testList  = malloc (sizeof (list*));
       assert (testList != NULL);
     
       printf ("testing a two letter list - redact both\n");
       testList->head = nodeC;
       nodeC->next = nodeC1;
       nodeC1->next = NULL;
       
       redact (testList,'c');  // remove all nodes
       assert (testList->head == NULL);
       printf ("test passed!\n");
     
     
       printf ("testing a three letter list - leave first\n");
       testList->head = nodeO;
       nodeO->next = nodeC;
       nodeC->next = nodeC1;
       nodeC1->next = NULL;
       
       redact (testList,'c');  // remove both cs
       assert (testList->head == nodeO);
       assert (nodeO->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a three letter list - leave middle\n");
       testList->head = nodeC;
       nodeC->next = nodeO;
       nodeO->next = nodeC1;
       nodeC1->next = NULL;
       
       redact (testList,'c');  // remove both cs
       assert (testList->head == nodeO);
       assert (nodeO->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing a three letter list - leave last\n");
       testList->head = nodeC;
       nodeC->next = nodeC1;
       nodeC1->next = nodeO;
       nodeO->next = NULL;
       
       redact (testList,'c');  // remove both cs
       assert (testList->head == nodeO);
       assert (nodeO->next == NULL);
       printf ("test passed!\n");
     
     
       printf ("testing an alternating list - redact odd places\n");
       testList->head = nodeE1;
       nodeE1->next = nodeO1;
       nodeO1->next = nodeE2;
       nodeE2->next = nodeO2;
       nodeO2->next = nodeE3;
       nodeE3->next = nodeO3;
       nodeO3->next = nodeE4;
       nodeE4->next = nodeO4;
       nodeO4->next = nodeE5;
       nodeE5->next = nodeO5;
       nodeO5->next = nodeE6;
       nodeE6->next = NULL;
       
       redact (testList,'o');  // remove odd places
       assert (testList->head == nodeE1);
       assert (nodeE1->next == nodeE2);
       assert (nodeE2->next == nodeE3);
       assert (nodeE3->next == nodeE4);
       assert (nodeE4->next == nodeE5);
       assert (nodeE5->next == nodeE6);
       assert (nodeE6->next == NULL);
       printf ("test passed!\n");
     
       printf ("testing an alternating list - redact even places\n");
       testList->head = nodeE1;
       nodeE1->next = nodeO1;
       nodeO1->next = nodeE2;
       nodeE2->next = nodeO2;
       nodeO2->next = nodeE3;
       nodeE3->next = nodeO3;
       nodeO3->next = nodeE4;
       nodeE4->next = nodeO4;
       nodeO4->next = nodeE5;
       nodeE5->next = nodeO5;
       nodeO5->next = nodeE6;
       nodeE6->next = NULL;
       
       redact (testList,'e');  // remove odd places
       assert (testList->head == nodeO1);
       assert (nodeO1->next == nodeO2);
       assert (nodeO2->next == nodeO3);
       assert (nodeO3->next == nodeO4);
       assert (nodeO4->next == nodeO5);
       assert (nodeO5->next == NULL);
       printf ("test passed!\n");
     
     
     
       printf ("redacting a long list with duplicates 1\n");
       testList->head = nodeO;
       nodeO->next = nodeC;
       nodeC->next = nodeC1;
       nodeC1->next = nodeU;
       nodeU->next = nodeP;
       nodeP->next = nodeI;
       nodeI->next = nodeE;
       nodeE->next = nodeD;
       nodeD->next = nodeE1;
       nodeE1->next = nodeE2;
       nodeE2->next = nodeE3;
       nodeE3->next = NULL;
     
       redact (testList,'e');  // no effect
       assert (testList->head == nodeO);
       assert (nodeO->next == nodeC);
       assert (nodeC->next == nodeC1);
       assert (nodeC1->next == nodeU);
       assert (nodeU->next == nodeP);
       assert (nodeP->next == nodeI);
       assert (nodeI->next == nodeD);
       assert (nodeD->next == NULL);
       printf ("test passed!\n");
     
       printf ("redacting a long list with duplicates 2\n");
     
       redact (testList,'c');  // no effect
       assert (testList->head == nodeO);
       assert (nodeO->next == nodeU);
       assert (nodeU->next == nodeP);
       assert (nodeP->next == nodeI);
       assert (nodeI->next == nodeD);
       assert (nodeD->next == NULL);
       printf ("test passed!\n");
     
       printf ("redacting a long list with duplicates 3\n");
     
       redact (testList,'p');  // no effect
       redact (testList,'u');  // no effect
       redact (testList,'o');  // no effect
       assert (testList->head == nodeI);
       assert (nodeI->next == nodeD);
       assert (nodeD->next == NULL);
       printf ("test passed!\n");
     
     
       printf ("testing node values have not changed\n");
       
       assert (nodeO->value == 'o');
       assert (nodeC->value == 'c');
       assert (nodeU->value == 'u');
       assert (nodeP->value == 'p');
       assert (nodeI->value == 'i');
       assert (nodeE->value == 'e');
       assert (nodeD->value == 'd');
     
       assert (nodeC1->value == 'c');
       assert (nodeE1->value == 'e');
       assert (nodeE2->value == 'e');
       assert (nodeE3->value == 'e');
       assert (nodeE4->value == 'e');
       assert (nodeE5->value == 'e');
       assert (nodeE6->value == 'e');
       
       assert (nodeO1->value == 'o');
       assert (nodeO2->value == 'o');
       assert (nodeO3->value == 'o');
       assert (nodeO4->value == 'o');
       assert (nodeO5->value == 'o');
     
       printf ("test passed!\n");
     
     
     
       printf ("testing that no nodes have been freed\n...");
       // free the nodes - not needed in subsequent tests
       // might fail if students have inadventantly freed nodes
       // already
       free (nodeO);
       free (nodeC);
       free (nodeU);
       free (nodeP);
       free (nodeI);
       free (nodeE);
       free (nodeD);
       
       free (nodeC1);
     
       free (nodeO1);
       free (nodeO2);
       free (nodeO3);
       free (nodeO4);
       free (nodeO5);
     
       free (nodeE1);
       free (nodeE2);
       free (nodeE3);
       free (nodeE4);
       free (nodeE5);
       free (nodeE6);
       
       printf ("test passed!\n");
    }     
     
    /////////////////////////////////
     
     
    void testQ2unique (void) {
       
       // create test nodes, names indicate their value, next=NULL
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
