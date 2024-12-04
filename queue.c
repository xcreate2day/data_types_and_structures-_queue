#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 4

//fifo queue

struct item {
    int value;
    struct item *next;
};

struct queue {
    struct item *first; 
    struct item *last;  
    int max_size;
    int cur_size;
} *q;

void init(void);
bool is_empty(void);
bool is_filled(void);
bool first_exists(void);
bool dequeue(void); //pop, first el
bool enqueue(void); //push, last el
void set_item_value(struct item *n_item);
void print_q(void);
void choose_action(void);
void app_run(void);


int main(void) {

    app_run();
    return 0;

}


void init(void) { 

    if((q = (struct queue *)malloc(sizeof(struct queue))) == NULL) {
  printf("init memory error\n");
  exit(1); 
 }
    q->max_size = MAX_SIZE;
    q->cur_size = 0;
    q->first = q->last = NULL;   

}

bool is_filled(void) {

    if(q->cur_size == MAX_SIZE) return true;
    return false;

}

bool is_empty(void) {

    if(!(q->cur_size)) return true;
    return false;

}

bool first_exists(void) {

    if(q->first) return true;
    return false;

}

void set_item_value(struct item *n_item) {

 printf("input value (integer):\t");
 scanf("%d", &n_item->value);
 getchar();

}

bool enqueue(void) { 

 if(is_filled()) {
  printf("queue is filled\n");
  return false;
 } 
 
 struct item *new_item = (struct item *)malloc(sizeof(struct item));
 
 if(is_empty()) {
  q->first = new_item;
  q->last = new_item;
 }
 else {
  new_item->next = q->last;
  q->last = new_item;
  q->first->next = new_item;    
 }
 
 set_item_value(new_item);

 q->cur_size++;

 return true;

}

bool dequeue(void) { 

 if(is_empty()) {
  printf("queue is empty\n");
  return false;
 } 

 q->cur_size--; 
 
 if(!(q->cur_size)) { 
  //free(q->first); 
  q->first = q->last = NULL; 
 }
 else { 
  struct item *tmp_item = (struct item *)malloc(sizeof(struct item));
  tmp_item = q->last;
  while (tmp_item->next != q->first) tmp_item = tmp_item->next;
  free(q->first);
  q->first = tmp_item;
  q->first->next = q->last;  
 }
 
 return true; 

}

void print_q(void) {

 int count;
 struct item *tmp_item = (struct item *)malloc(sizeof(struct item));;
 tmp_item = q->last; 

 if(is_empty()) {
  printf("queue is empty\n");
  return;
 }

 for(count = q->cur_size; count; count--, tmp_item = tmp_item->next) {
  printf("queue item %d = %d\n", count, tmp_item->value);
 }

 free(tmp_item);

}

void choose_action(void) {

 int choice;
 
 printf("Choose action:\n"\
   "1 - check is_filled\n"\
   "2 - check is_empty\n"\
   "3 - check first\n"\
   "4 - push item\n"\
   "5 - pop item\n"\
   "6 - print q\n"\
   "7 - end\n");
 scanf("%d", &choice);

 switch (choice) {

  case 1:
   if(is_filled()) printf("filled\n");
   else printf("not filled\n");
   choose_action();
   break; 

  case 2:
   if(is_empty()) printf("empty\n");
   else printf("not empty\n");
   choose_action();
   break;

  case 3:
   if(first_exists()) printf("first exists\n");
   else printf("first doesn't exist\n");
   choose_action();
   break;

  case 4:   
   if(enqueue()) printf("pushed\n");
   else printf("can't push\n");
   choose_action();
   break;

  case 5:   
   if(dequeue()) printf("deleted\n");
   else printf("can't delete\n");
   choose_action();
   break;  

  case 6:   
   print_q();
   choose_action();
   break;

  case 7:   
   exit(0);

  default: 
   printf("please, input correct number\n");
   choose_action();

 }

}

void app_run(void) {

    init(); 
    choose_action();

}