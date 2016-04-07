//  Created by Bernice Chen on 10/05/2014.
//
//header file for a Linked List structure
//contains functions that can be implemented on a Linked List
 
typedef struct _node* Node;
typedef struct _list* List;
 
 
//returns a new list of length 0
List newList();
//frees everything malloced for the list
void destroy(List l);
//appends a node of value to the end of the list
void append(List l, int value);
//returns the int value of the node at index
//assumes input index is within range of the list's length
int getValue(List l, int index);
 
//TODO
//inserts a node of value AFTER specified index
//given a list 0->1->2-X
//then insertAt(l, 1, 9)
//now the list will be 0->1->9->2-X
void insertAt(List l, int index, int value);
 
//TODO
//reverses all nodes in a list
//given a list 0->1->2->X
//then reverse(l)
//now the list will be 2->1->0->X
void reverse(List l);