//
//  COMP1927 Assignment 1 - Vlad: the memory allocator
//  allocator.c ... implementation
//
//  Created by Liam O'Connor on 18/07/12.
//  Modified by John Shepherd in August 2014, August 2015
//  Copyright (c) 2012-2015 UNSW. All rights reserved.
//

#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define HEADER_SIZE    sizeof(struct free_list_header)  
#define MAGIC_FREE     0xDEADBEEF
#define MAGIC_ALLOC    0xBEEFDEAD

typedef unsigned char byte;
typedef u_int32_t vlink_t;
typedef u_int32_t vsize_t;
typedef u_int32_t vaddr_t;

typedef struct free_list_header *headerPtr;
typedef struct free_list_header *FreeHeader;

typedef struct free_list_header {
   u_int32_t magic;  // ought to contain MAGIC_FREE
   vsize_t size;     // # bytes in this block (including header)
   vlink_t next;     // memory[] index of next free block
   vlink_t prev;     // memory[] index of previous free block
} free_header_t;

static headerPtr pointerfy(vaddr_t i);
static headerPtr split(int half, headerPtr toSplit);
static void mergeBlock();

// Global data
static byte *memory = NULL;   // pointer to start of allocator memory
static vaddr_t free_list_ptr; // index in memory[] of first block in free list
static vsize_t memory_size;  // number of bytes malloc'd in memory[]
static headerPtr last = NULL;
static headerPtr first= NULL;

// Input: size - number of bytes to make available to the allocator
// Output: none              
// Precondition: Size is a power of two.
// Postcondition: `size` bytes are now available to the allocator
// 
// (If the allocator is already initialised, this function does nothing,
//  even if it was initialised with different size)

void vlad_init(u_int32_t size)
{
    memory_size = size;

    memory = malloc(memory_size);
    if(memory == NULL){
        fprintf(stderr, "vlad_init: insufficient memory");
        abort();
    }
    free_header_t *main = (free_header_t*)memory;
    last = main;
    first = main;
    main->magic = MAGIC_FREE;
    main->size = memory_size;
    main->next = 0;
    main->prev = 0;

    free_list_ptr = 0;

}


// Input: n - number of bytes requested
// Output: p - a pointer, or NULL
// Precondition: n is < size of memory available to the allocator
// Postcondition: If a region of size n or greater cannot be found, p = NULL 
//                Else, p points to a location immediately after a header block
//                      for a newly-allocated region of some size >= 
//                      n + header size.

void *vlad_malloc(u_int32_t n)
{
    headerPtr curr =(free_header_t*)(memory+free_list_ptr);
    int req = n+HEADER_SIZE;
   // int position = (vlink_t)curr-(vlink_t)memory;

    assert (free_list_ptr >= 0);

    while (curr->size< req){ 
        //check if current free block is more than required size 
        if(curr->magic != MAGIC_FREE){ 
            //check that the block is free, else end function
            fprintf(stderr, "Memory corruption");
            abort();
        }   
        curr=(headerPtr)(memory+curr->next);
        if(curr==pointerfy(free_list_ptr)){return NULL;}
        //if tranversed entire list and no suitable block, return NULL
    }
    int half;
    headerPtr new;
    //int loop = 0;
    while((curr->size/2) > req){
        half = curr->size/2;
        new = split(half, curr);
       
    }

    if(curr->next == (vaddr_t)curr-(vaddr_t)(memory)){
        return NULL; //only free region in list
    } else {
        new = (void*)memory + curr->next;
        curr->magic = MAGIC_ALLOC;
        free_list_ptr = curr -> next;
    
        new->prev = curr->prev;
        if(new->next == (vaddr_t)curr-(vaddr_t)memory){ 
            //only two parts left, thus link to self
            new->next = (vlink_t)new-(vlink_t)memory;
        }
        last = (free_header_t*)(memory+curr->prev);
        last->next = (vaddr_t)new-(vaddr_t)memory;
                free_list_ptr = curr -> next;

/*
        printf("SIZE curr: %d, new: %d\n", curr->size,new->size);
        printf("INDEX curr: %d, new: %d\n", ((vlink_t)curr-(vlink_t)memory),((vlink_t)new-(vlink_t)memory));
        printf("NEXT curr: %d, new: %d\n", (vlink_t)(curr->next), (vlink_t)(new->next));
        printf("PREV curr: %d, new: %d\n", (vlink_t)(curr->prev), (vlink_t)(new->prev));
        printf("LAST index: %d, prev: %d, next:%d\n", (vlink_t)last-(vlink_t)memory, (vlink_t)(last->prev),(vlink_t)last->next);
*/     
    }

    return ((void*)curr + HEADER_SIZE);                     
}

static headerPtr split(int half, headerPtr toSplit){
     //check if half the block is enough
        headerPtr new,after;
        new = (void*)toSplit+half;
        after = (void*)memory+toSplit->next;

        new->size = half;
        toSplit->size = half;

        new->prev = (vlink_t)toSplit-(vlink_t)memory;
        new->next = toSplit->next;
        new->magic = MAGIC_FREE;

        after->prev = (vlink_t)new-(vlink_t)memory;

        if(toSplit->prev ==toSplit->next &&
            toSplit->next == (vlink_t)toSplit-(vlink_t)memory ){
            toSplit->prev = (vlink_t)toSplit+half-(vlink_t)memory;
        }

        toSplit->next = (vlink_t)new-(vlink_t)memory;

        /*printf("INDEX curr: %d, new: %d\n", ((vlink_t)toSplit-(vlink_t)memory),((vlink_t)new-(vlink_t)memory));
        printf("NEXT curr: %d, new: %d\n", (vlink_t)(toSplit->next), (vlink_t)(new->next));
        printf("PREV curr: %d, new: %d\n", (vlink_t)(toSplit->prev), (vlink_t)(new->prev));
        printf("LAST index: %d, prev: %d, next:%d\n", (vlink_t)after-(vlink_t)memory, (vlink_t)(after->prev),(vlink_t)after->next);
        */
        return new;
}

// Input: object, a pointer.
// Output: none
// Precondition: object points to a location immediately after a header block
//               within the allocator's memory.
// Postcondition: The region pointed to by object can be re-allocated by 
//                vlad_malloc

void vlad_free(void *object)
{
    vaddr_t fIndex = (vaddr_t)object - (vaddr_t)memory - HEADER_SIZE;
    headerPtr toFree = pointerfy(fIndex);
    vaddr_t index = free_list_ptr;
    headerPtr curr = pointerfy(index);
    int special = 0;
    int loop=0;

    while (loop<10) { 
            if(index<free_list_ptr){
                free_list_ptr=index; //make freelistptr start from smallest
            }
            index = pointerfy(index)->next;
            curr = pointerfy(index);
            if(index==free_list_ptr){
                loop++;
            }
    }
    index = free_list_ptr;
    curr = pointerfy(index);
    //reset

    if (toFree->magic != MAGIC_ALLOC) {
        fprintf(stderr, "Attempt to free non-allocated memory");
        abort();
    }

    toFree->magic = MAGIC_FREE;
 

    if (index == curr->next) { //single block
        curr->next = fIndex;
        curr->prev = fIndex;
        toFree->next = index;
        toFree->prev = index;
        return;
    } else {
        vaddr_t aIndex = pointerfy(index)->next; 
        headerPtr after = pointerfy(aIndex);
            //printf("index:%d,aIndex:%d,fIndex:%d\n", index,aIndex,fIndex); 
        
        while (aIndex < fIndex || index>fIndex) { 
            if(index<free_list_ptr){
                free_list_ptr=index; //make freelistptr start from smallest
            }
            //printf("index:%d,aIndex:%d,fIndex:%d\n", index,aIndex,fIndex); 
            index = pointerfy(index)->next;
            aIndex = pointerfy(aIndex)->next;
            curr = pointerfy(index);
            after = pointerfy(aIndex);

            /*
        printf("INDEX curr: %d, after: %d\n", ((vlink_t)curr-(vlink_t)memory),((vlink_t)after-(vlink_t)memory));
        printf("NEXT curr: %d, after: %d\n", (vlink_t)(curr->next), (vlink_t)(after->next));
        printf("PREV curr: %d, after: %d\n", (vlink_t)(curr->prev), (vlink_t)(after->prev));
*/ 
            if (index == free_list_ptr) {
                //ran through entire list once and cannot find values in between
                special = 1;
                break; 
            }
        }

/*
        printf("INDEX curr: %d, after: %d\n", ((vlink_t)curr-(vlink_t)memory),((vlink_t)after-(vlink_t)memory));
        printf("NEXT curr: %d, after: %d\n", (vlink_t)(curr->next), (vlink_t)(after->next));
        printf("PREV curr: %d, after: %d\n", (vlink_t)(curr->prev), (vlink_t)(after->prev));
*/ 
        if(special == 1){ 
            //insert before curr, curr is freelistptr
            headerPtr prevHeader = pointerfy(curr->prev);
            toFree->next = index;
            prevHeader->next = fIndex;
            toFree->prev = curr->prev;

            curr->prev = fIndex;  
                        //printf("SPECIAL\n");
                    
            //printf("CURR index=%d next=%d prev=%d\n",index,curr->next,curr->prev );

            //printf("free index=%d next=%d prev=%d\n",fIndex,toFree->next,toFree->prev );

             
        } else{
            
            toFree->next = aIndex;
            curr->next = fIndex;

            toFree->prev = index;
            after->prev = fIndex;
            //printf("CURR index=%d next=%d prev=%d\n",index,curr->next,curr->prev );

            //printf("free index=%d next=%d prev=%d\n",fIndex,toFree->next,toFree->prev );

        }
    }   
 
    mergeBlock();

    return;
}

static void mergeBlock(){//merge forward!!!
    vaddr_t cIndex = free_list_ptr;
    
    headerPtr curr= pointerfy(cIndex);
    //printf("CURR index=%d next=%d prev=%d\n",cIndex,curr->next,curr->prev );
    headerPtr after= pointerfy(curr->next);
    headerPtr afafter= pointerfy(after->next);

    vaddr_t aIndex = curr->next;
    vaddr_t aaIndex = after->next;

    int done = 0;
    int merged = 0;
    int loop = 0;
    //printf("HIIIII\n");

    while(done!=1){
        if(aIndex > cIndex && //merging forwards
            curr->size == after->size && //equal size
            cIndex+curr->size == aIndex && //adjacent
            ((vaddr_t)afafter-(vaddr_t)memory)%(curr->size+after->size)==0
            ){
            //printf("BOOMSHAKALAKA\n");  
            curr->next = aaIndex;
            afafter->prev = cIndex;
            curr->size = curr->size + after->size;
            if(free_list_ptr==aIndex){
                free_list_ptr = cIndex;
            }
                
            merged = 1;
            loop = 0;
        } 
        //printf("loop=%d,merged=%d,done=%d,\n",loop,merged,done);
        //printf("cIndex=%d,aIndex=%d,aaIndex=%d,\n",cIndex,aIndex,aaIndex);
        //printf("c next=%d,a next=%d,aanext=%d,\n",curr->next,after->next,afafter->next);

        if(merged == 0 && loop == 3){ 
            //checked through whole list without merging anything
            //end loop
            done = 1;
        } 
            cIndex=curr->next;
            aIndex=after->next;
            aaIndex=afafter->next;
            curr = pointerfy(cIndex);
            after = pointerfy(curr->next);
            afafter = pointerfy(after->next);
            //assert(curr!=after);

            if(cIndex==free_list_ptr){loop++; merged=0;} 

        
    }

}
// Stop the allocator, so that it can be init'ed again:
// Precondition: allocator memory was once allocated by vlad_init()
// Postcondition: allocator is unusable until vlad_int() executed again


static headerPtr pointerfy(vaddr_t i){
    return (headerPtr)(memory+ i);
}

void vlad_end(void)
{
    if (memory != NULL) {
        free(memory);
        free_list_ptr = 0;
        memory_size = 0;
        memory = NULL;
    }
}


// Precondition: allocator has been vlad_init()'d
// Postcondition: allocator stats displayed on stdout

void vlad_stats(void)
{
   headerPtr fHeader =  pointerfy(free_list_ptr);
   printf("Free next:%d, prev: %d\n",fHeader->next,fHeader->prev);
   printf("free_list_ptr index: %d\n", free_list_ptr);
   printf("memory addresss: %p\n",&memory);
   printf("memory_size = %d\n",memory_size);
   printf("Size of first block: %d\n", ((free_header_t*)memory)->size );
   if(fHeader->magic==MAGIC_FREE){
        printf("free list ptr free\n");
    } else {
        printf("ALLOCATED\n");
    }
   //printf("Index of last block: %d\n", (vlink_t)last);
   //printf("vlad_stats() won't work until vlad_malloc() works\n");
   return;
}


//
// All of the code below here was written by Alen Bou-Haidar, COMP1927 14s2
//

//
// Fancy allocator stats
// 2D diagram for your allocator.c ... implementation
// 
// Copyright (C) 2014 Alen Bou-Haidar <alencool@gmail.com>
// 
// FancyStat is free software: you can redistribute it and/or modify 
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or 
// (at your option) any later version.
// 
// FancyStat is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>


#include <string.h>

#define STAT_WIDTH  32
#define STAT_HEIGHT 16
#define BG_FREE      "\x1b[48;5;35m" 
#define BG_ALLOC     "\x1b[48;5;39m"
#define FG_FREE      "\x1b[38;5;35m" 
#define FG_ALLOC     "\x1b[38;5;39m"
#define CL_RESET     "\x1b[0m"


typedef struct point {int x, y;} point;

static point offset_to_point(int offset,  int size, int is_end);
static void fill_block(char graph[STAT_HEIGHT][STAT_WIDTH][20], 
                        int offset, char * label);



// Print fancy 2D view of memory
// Note, This is limited to memory_sizes of under 16MB
void vlad_reveal(void *alpha[26])
{
    int i, j;
    vlink_t offset;
    char graph[STAT_HEIGHT][STAT_WIDTH][20];
    char free_sizes[26][32];
    char alloc_sizes[26][32];
    char label[3]; // letters for used memory, numbers for free memory
    int free_count, alloc_count, max_count;
    free_header_t * block;


    // initilise size lists
    for (i=0; i<26; i++) {
        free_sizes[i][0]= '\0';
        alloc_sizes[i][0]= '\0';
    }

    // Fill graph with free memory
    offset = 0;
    i = 1;
    free_count = 0;
    while (offset < memory_size){
        block = (free_header_t *)(memory + offset);
        if (block->magic == MAGIC_FREE) {
            snprintf(free_sizes[free_count++], 32, 
                "%d) %d bytes", i, block->size);
            snprintf(label, 3, "%d", i++);
            fill_block(graph, offset,label);
        }
        offset += block->size;
    }

    // Fill graph with allocated memory
    alloc_count = 0;
    for (i=0; i<26; i++) {
        if (alpha[i] != NULL) {
            offset = ((byte *) alpha[i] - (byte *) memory) - HEADER_SIZE;
            block = (free_header_t *)(memory + offset);
            snprintf(alloc_sizes[alloc_count++], 32, 
                "%c) %d bytes", 'a' + i, block->size);
            snprintf(label, 3, "%c", 'a' + i);
            fill_block(graph, offset,label);
        }
    }

    // Print all the memory!
    for (i=0; i<STAT_HEIGHT; i++) {
        for (j=0; j<STAT_WIDTH; j++) {
            printf("%s", graph[i][j]);
        }
        printf("\n");
    }

    //Print table of sizes
    max_count = (free_count > alloc_count)? free_count: alloc_count;
    printf(FG_FREE"%-32s"CL_RESET, "Free");
    if (alloc_count > 0){
        printf(FG_ALLOC"%s\n"CL_RESET, "Allocated");
    } else {
        printf("\n");
    }
    for (i=0; i<max_count;i++) {
        printf("%-32s%s\n", free_sizes[i], alloc_sizes[i]);
    }

}

// Fill block area
static void fill_block(char graph[STAT_HEIGHT][STAT_WIDTH][20], 
                        int offset, char * label)
{
    point start, end;
    free_header_t * block;
    char * color;
    char text[3];
    block = (free_header_t *)(memory + offset);
    start = offset_to_point(offset, memory_size, 0);
    end = offset_to_point(offset + block->size, memory_size, 1);
    color = (block->magic == MAGIC_FREE) ? BG_FREE: BG_ALLOC;

    int x, y;
    for (y=start.y; y < end.y; y++) {
        for (x=start.x; x < end.x; x++) {
            if (x == start.x && y == start.y) {
                // draw top left corner
                snprintf(text, 3, "|%s", label);
            } else if (x == start.x && y == end.y - 1) {
                // draw bottom left corner
                snprintf(text, 3, "|_");
            } else if (y == end.y - 1) {
                // draw bottom border
                snprintf(text, 3, "__");
            } else if (x == start.x) {
                // draw left border
                snprintf(text, 3, "| ");
            } else {
                snprintf(text, 3, "  ");
            }
            sprintf(graph[y][x], "%s%s"CL_RESET, color, text);            
        }
    }
}

// Converts offset to coordinate
static point offset_to_point(int offset,  int size, int is_end)
{
    int pot[2] = {STAT_WIDTH, STAT_HEIGHT}; // potential XY
    int crd[2] = {0};                       // coordinates
    int sign = 1;                           // Adding/Subtracting
    int inY = 0;                            // which axis context
    int curr = size >> 1;                   // first bit to check
    point c;                                // final coordinate
    if (is_end) {
        offset = size - offset;
        crd[0] = STAT_WIDTH;
        crd[1] = STAT_HEIGHT;
        sign = -1;
    }
    while (curr) {
        pot[inY] >>= 1;
        if (curr & offset) {
            crd[inY] += pot[inY]*sign; 
        }
        inY = !inY; // flip which axis to look at
        curr >>= 1; // shift to the right to advance
    }
    c.x = crd[0];
    c.y = crd[1];
    return c;
}






