#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "list-selectEven.h"

//simple unit tests on the list
static void testList(void);
void showList (list l);

int main (int argc, char * argv[]){

	testList();
	printf("All tests passed ! You are awesome\n");
	return EXIT_SUCCESS;
}

void testList (void){

	// test a list with no nodes in it
    printf ("test an empty list\n");
    list sourceList = malloc (sizeof (*sourceList));
    assert (sourceList !=NULL);
    sourceList->head = NULL;  

    printf ("before function call..\n");
    printf("sourceList is: ");
    showList (sourceList);
    list evenList = selectEven (sourceList);
    printf ("after function call..\n");
    printf ("evenList is ");
	showList (evenList);
    printf ("sourceList is: ");
    showList (sourceList);

    assert (evenList->head == NULL); 
    assert (sourceList->head == NULL);
	
	// create 10 nodes on the stack 
    node nodes[10];
 
    // test a list with one even integer in it
    printf ("\ntest a list containing one even integer\n");
    sourceList->head = &nodes[0];
    sourceList->head->value = 42;
    sourceList->head->next = NULL;  
    
    printf ("before function call..\n");
    printf ("sourceList is: ");
    showList (sourceList);
    evenList = selectEven (sourceList);
    printf ("after function call..\n");
    printf ("evenList is ");
    showList (evenList);
    printf ("sourceList is: ");
    showList (sourceList);

    assert (evenList->head->value == 42);
    assert (evenList->head->next == NULL); 
	
    assert (sourceList->head == &nodes[0]);  
    assert (sourceList->head->value == 42);
    assert (sourceList->head->next == NULL); 	

    // test a list with one odd integer in it
    printf ("\ntest a list containing one odd integer\n");
    sourceList->head = &nodes[0];
    sourceList->head->value = 41;
    sourceList->head->next = NULL;  
    
    printf ("before function call..\n");
    printf ("sourceList is: ");
    showList (sourceList);
    evenList = selectEven (sourceList);
    printf ("after function call..\n");
    printf ("evenList is ");
    showList (evenList);
    printf("sourceList is: ");
    showList (sourceList);

    assert (evenList->head == NULL);  
    
    assert (sourceList->head == &nodes[0]);  
    assert (sourceList->head->value == 41);
    assert (sourceList->head->next == NULL);    

    // test a list with two integers - one odd and the other even 
    printf ("\ntest a list containing one odd and one even integer\n");
    sourceList->head = &nodes[0];
    nodes[0].value = 73;
    nodes[1].value = 22;
    nodes[0].next  = &nodes[1];
    nodes[1].next  = NULL;
    
    printf ("before function call..\n");
    printf ("sourceList is: ");
    showList (sourceList);
    evenList = selectEven (sourceList);
    printf ("after function call..\n");
    printf ("evenList is ");
    showList (evenList);
    printf ("sourceList is: ");
    showList (sourceList);

    assert (evenList->head->value == 22);
    assert (evenList->head->next == NULL); 
    
    assert (sourceList->head == &nodes[0]);  
    assert (sourceList->head->value == 73);
    assert (sourceList->head->next == &nodes[1]);
    assert (sourceList->head->next->value == 22);
    assert (sourceList->head->next->next == NULL);


    // test a list with two integers - both even
    printf ("\ntest a list containing two even integers\n");
    sourceList->head = &nodes[0];
    nodes[0].value = 100;
    nodes[1].value = 44;
    nodes[0].next  = &nodes[1];
    nodes[1].next  = NULL;
    
    printf ("before function call..\n");
    printf ("sourceList is: ");
    showList (sourceList);
    evenList = selectEven (sourceList);
    printf ("after function call..\n");
    printf ("evenList is ");
    showList (evenList);
    printf ("sourceList is: ");
    showList (sourceList);

    assert (evenList->head->value == 100);
    assert (evenList->head->next->value == 44);
    assert (evenList->head->next->next == NULL);
    
    assert (sourceList->head == &nodes[0]);  
    assert (sourceList->head->value == 100);
    assert (sourceList->head->next == &nodes[1]);
    assert (sourceList->head->next->value == 44);
    assert (sourceList->head->next->next == NULL);

    // test a list with two integers - both odd
    printf ("\ntest a list containing two odd integers\n");
    sourceList->head = &nodes[0];
    nodes[0].value = 101;
    nodes[1].value = 55;
    nodes[0].next  = &nodes[1];
    nodes[1].next  = NULL;
    
    printf ("before function call..\n");
    printf ("sourceList is: ");
    showList (sourceList);
    evenList = selectEven (sourceList);
    printf ("after function call..\n");
    printf ("evenList is ");
    showList (evenList);
    printf ("sourceList is: ");
    showList (sourceList);

    assert (evenList->head == NULL);  
    
    assert (sourceList->head == &nodes[0]);  
    assert (sourceList->head->value == 101);
    assert (sourceList->head->next == &nodes[1]);
    assert (sourceList->head->next->value == 55);
    assert (sourceList->head->next->next == NULL);


    //test a list with four integers - one odd and three even
    printf ("\ntest a list containing one odd and three even integers\n");
    sourceList->head = &nodes[0];
    nodes[0].value = 4;
    nodes[1].value = 166;
    nodes[2].value = 3;
    nodes[3].value = 72;
    nodes[0].next  = &nodes[1];
    nodes[1].next  = &nodes[2];
    nodes[2].next  = &nodes[3];
    nodes[3].next  = NULL;
    
    printf ("before function call..\n");
    printf ("sourceList is: ");
    showList (sourceList);
    evenList = selectEven (sourceList);
    printf ("after function call..\n");
    printf ("evenList is ");
    showList (evenList);
    printf ("sourceList is: ");
    showList (sourceList);
 
    assert (evenList->head->value == 4);
    assert (evenList->head->next->value == 166);
    assert (evenList->head->next->next->value == 72);
    assert (evenList->head->next->next->next == NULL);
    
    assert (sourceList->head == &nodes[0]);  
    assert (sourceList->head->value == 4);
    assert (sourceList->head->next == &nodes[1]);
    assert (sourceList->head->next->value == 166);
    assert (sourceList->head->next->next == &nodes[2]);
    assert (sourceList->head->next->next->value == 3);
    assert (sourceList->head->next->next->next == &nodes[3]);
    assert (sourceList->head->next->next->next->value == 72);
    assert (sourceList->head->next->next->next->next == NULL);


    // test a list with seven integers - four odd and three even
    printf ("\ntest a list containing four odd and three even integers\n");
    sourceList->head = &nodes[0];
    nodes[0].value = 3;
    nodes[1].value = 66;
    nodes[2].value = 71;
    nodes[3].value = 36;
    nodes[4].value = 45;
    nodes[5].value = 232;
    nodes[6].value = 21;
    nodes[0].next  = &nodes[1];
    nodes[1].next  = &nodes[2];
    nodes[2].next  = &nodes[3];
    nodes[3].next  = &nodes[4]; 
    nodes[4].next  = &nodes[5];
    nodes[5].next  = &nodes[6]; 
    nodes[6].next  = NULL;
    
    printf ("before function call..\n");
    printf ("sourceList is: ");
    showList (sourceList);
    evenList = selectEven (sourceList);
    printf ("after function call..\n");
    printf ("evenList is ");
    showList (evenList);
    printf ("sourceList is: ");
    showList (sourceList);
 
    assert (evenList->head->value == 66);
    assert (evenList->head->next->value == 36);
    assert (evenList->head->next->next->value == 232);
    assert (evenList->head->next->next->next == NULL);
    
    assert (sourceList->head == &nodes[0]);  
    assert (sourceList->head->value == 3);
    assert (sourceList->head->next == &nodes[1]);
    assert (sourceList->head->next->value == 66);
    assert (sourceList->head->next->next == &nodes[2]);
    assert (sourceList->head->next->next->value == 71);
    assert (sourceList->head->next->next->next == &nodes[3]);
    assert (sourceList->head->next->next->next->value == 36);
    assert (sourceList->head->next->next->next->next == &nodes[4]);
    assert (sourceList->head->next->next->next->next->value == 45);
    assert (sourceList->head->next->next->next->next->next == &nodes[5]);
    assert (sourceList->head->next->next->next->next->next->value == 232);
    assert (sourceList->head->next->next->next->next->next->next == &nodes[6]);
    assert (sourceList->head->next->next->next->next->next->next->value == 21);
    assert (sourceList->head->next->next->next->next->next->next->next == NULL);

}

void showList (list l) {
 
    assert (l !=NULL);
 
    // start at the first node
    link current = l->head;
    while (current != NULL) {
        printf ("[%d] -> ", current->value);
        current = current->next;
    }
    printf ("X\n");
}
