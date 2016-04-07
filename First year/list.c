//  Created by Bernice Chen on 10/05/2014.
//
//list.c file that implements all functions declared in list.h
//implement the insertAt() and reverse() functions here
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
 
typedef struct _node {
    int value;
    Node next;
} node;
 
typedef struct _list {
    Node head;
} list;
 
//when both insertAt() and reverse() functions are complete,
//compile with testList.c, type
//"gcc -Wall -Werror -O -o test testList.c list.c"
//to run program, type
//"./test"
 
//TODO
//inserts a node of value AFTER specified index
//given a list 0->1->2-X
//then insertAt(l, 1, 9);
//now the list will be 0->1->9->2-X
void insertAt(List l, int index, int value) {
   Node new = malloc(sizeof(node));
   new->value = value;
   if(l->head == NULL){
    
     l->head = new;
     new->next = NULL;
    
    } else {
       
       Node current = l->head;
       int i = 0;
       
       while(i < index){
           current = current -> next;
           i++;
       }
       
       new->next = current->next;
       current->next = new;
       
   }
}
 
//TODO
//reverses all nodes in a list
//given a list 0->1->2->X
//then reverse(l)
//now the list will be 2->1->0->X
void reverse(List l) {
    if(l->head == NULL){
    
    
    } else {
       Node p = l->head;
       Node c = p->next;
       Node n = c->next;

       while(c!=NULL){

            if(p == l->head){
              p->next = NULL;
            }
            c->next = p;
            p = c;
            c = n;
            if(n!= NULL){
              n = n->next;
            }

       }
       l->head = p;

   }
   
}
 
 
//returns a new list of length 0
List newList() {
   List l = malloc(sizeof(list));
   assert ( l!=NULL );
   l->head = NULL;
   return l;
}
 
//frees everything malloced for the list
void destroy(List l) {
   Node curNode = l->head;
   Node prevNode = NULL;
 
   while (curNode != NULL) {
     prevNode = curNode;
     curNode = prevNode->next;
     free(prevNode);
   }
 
   free(l);
}
 
//appends a node of value to the end of the list
void append(List l, int value) {
   Node newNode = malloc(sizeof(node));
   newNode->value = value;
   newNode->next = NULL;
   Node curNode = l->head;
   if ( curNode==NULL ) {
      l->head = newNode;
   } else {
      while ( curNode->next!=NULL ) {
         curNode = curNode->next;
      }
      curNode->next = newNode;
   }
}
 
//returns the int value of the node at index
//assumes input index is within range of the list's length
int getValue(List l, int index) {
 
   Node curNode = l->head;
   assert (curNode!=NULL);
   int counter = 0;
   while (counter<index) {
      curNode = curNode->next;
      counter++;
   }
   return curNode->value;
}
 
