#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *f;

struct LinkedList{
    int data;
    int index;
    struct LinkedList *next;
 };

typedef struct LinkedList *node;

node CreateNode(int value,int index){
    node temp;
    temp = (node)malloc(sizeof(struct LinkedList));
    temp->next = NULL;
    temp->data = value;
    temp->index = index;
    return temp;
}

node AddTail(node head, int value,int index){
    node temp,p;
    temp = CreateNode(value,index);
    if(head == NULL){
        head = temp;
    }
    else{
        p  = head;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = temp;
    }
    return head;
}

node DelHead(node head){
    if(head == NULL){
        printf("\nNothing to Delete");
    }else{
        head = head->next;
    }
    return head;
}

node DelAt(node head, int index){
    if(index == 0 || head == NULL || head->next == NULL){
        head = DelHead(head);
    }
    else{
        node p = head;
        while(p->next->next != NULL && p->next->index != index) {p = p->next;}
        if (p->next->index == index) {p->next = p->next->next;}
    }
    return head;
}

void Traverser(node head){
    printf("\n");
    for(node p = head; p != NULL; p = p->next){
        printf("%5d", p->data);
    }
}

int Length(node head){
    int length = 0;
    for(node p = head; p != NULL; p = p->next){
        ++length;
    }
    return length;
}

int CheckSortedList(node head){
    node p = head;
    while (p != NULL)
    {
        if (p->data > p->next->data) {return 0;}
        p=p->next;
    }
    return 1;
}

void SortList(node head){ //using bubble sort

   int i, j, k, tempKey, tempData ;
   node current;
   node next;

   int size = Length(head);
   k = size ;

   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      current = head ;
      next = head->next ;

      for ( j = 1 ; j < k ; j++ ) {

         if ( current->data > next->data ) {
            tempData = current->data ;
            current->data = next->data;
            next->data = tempData ;

            tempKey = current->index;
            current->index = next->index;
            next->index = tempKey;
         }

         current = current->next;
         next = next->next;
      }
   }
}

node Input(){
    node head=NULL;
    int index=0;
    char line[100]; int value;
    f=fopen("list.txt","r");
    if (f==NULL) {perror("Can't open this file");}
    else
    {
        while (!feof(f))
        {
            fgets(line,100,f);
            if (line[strlen(line)-1]=='\n') {line[strlen(line)-1]='\0';}
            value=atoi(line);
            head=AddTail(head,value,index);
            index++;
        }
    }
    fclose(f);
    return head;
}

int RemoveDupNode(node head){
    int check=0;
    node p=head;
    while (p->next!= NULL){
        while (p->data == p->next->data) {head = DelAt(head,p->next->index);check=p->index;}
        p=p->next;
    }
    return check;
}

int main(){
    printf("\n== Read the Linked List ==");
    node head = Input();

    printf("\n== Your Linked List ==");
    Traverser(head);

    if (CheckSortedList(head)==0){
            printf("\n== List Sorted ==");
            SortList(head);
            Traverser(head);
    }

    if (RemoveDupNode(head)!=0){
        printf("\n== Your List After Remove Duplicate Node ==");
    Traverser(head);
    }
    else{printf("\n== Your List Doesn't Have Any Duplicate Node ==");}
}
