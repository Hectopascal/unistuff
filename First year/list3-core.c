

// create an empty list

list newList (void){
    list new = malloc(sizeof(node));
    assert(new!=NULL);
    new->head = NULL;
    return new;

}

// delete the first node
void deleteHead (list l){
    link current = l->head;
    l->head = l->head->next;
    free(current);
}

// delete the end node
void deleteLast (list l){
    if(l!= NULL && l->head != NULL){
        link current = l->head;
        while(current->next->next!= NULL){
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }
}

// join two lists

// move all the elements from the second list to the end of
// the first list (in order).  this leaves the second list
// empty and all the elements in the first list. 
void concatenate (list to, list from);

// count the number of nodes containing 42
int count42s (list l);

void showList (list listToPrint){
    assert( 1!=NULL);
    link current = listToPrint->head;
    while(current != NULL){
        printf("[%d] -> ",current->value);
        current = current->next;
    }
    printf("X \n");
    
}

void frontInsert (list l, int item){
    link new = malloc(sizeof(node));
    assert (new != NULL);
    new->value = item;
    
    new->next = l->head;
    l->head = new;
}

int numItems (list l){
    assert(1!=NULL);
    int i = 0;
    link current = l->head;
    while(current != NULL){
        i++;
        current= current->next;
    }
    return i;
}


void append (list l, int value){
    assert (l!=NULL);
    link current = l->head;
    link new = malloc(sizeof(node));
    new->value = value;
    assert(new!=NULL);
    if(l->head==NULL){
        l->head = new;
    } else{
        while(current->next !=NULL){
            current=current->next;
        }
    }
    new->next = NULL;
    current->next = new;

}

int lookup (list l, int position){
    int value = 0;
    int i = 0;
    link current = l->head;
    assert(1!=NULL);
    while(current!=NULL){
        current = current-> next;
        i++;
    }
    assert (position >=0);
    assert (position <=i);
    i=0;
    while(i!=position){
        current = current->next;
    
    }
    value = current->value;
    
    return value;

}
