#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 32
#define C_OK  1
#define C_NOK 0


typedef struct{
    char  title[MAX];
    char author[MAX];
    int         year; 
}BookType;



typedef struct Node{
    BookType *data;
    struct Node *next;
}NodeType;


typedef struct{
   NodeType *head;

}ListType;



//forward declarations below 

int  initBook(BookType **book);
void initList(ListType *l);
void addByTitle(ListType *list, BookType *newBook);
void addByYear(ListType *list, BookType *newBook);
void printList(ListType *list);
void copyList(ListType *list, ListType *dest);
void copyByYear(ListType *list, ListType *dest);
void delAuthor(ListType *list, char *name);
void cleanupData(ListType *list);
void cleanupList(ListType *list);
void printBook(BookType *b);


int main(){

 // declaring three listType structures

  ListType l1;
  ListType l2;
  ListType l3;

// declaring three listType structure pointers
  ListType *booksByTitle;
  ListType *booksByYear;
  ListType *tmpList;

// pointing listptrs to lists
  booksByTitle = &l1;
  booksByYear  = &l2;
  tmpList      = &l3;
  
// author to remove is a string that will be used to delete authors from lists 
  char authorToRemove[MAX];

// initializing lists, ie seting the head to null 
  initList(booksByTitle);
  initList(booksByYear);
  initList(tmpList);

// continuously ask for book inout until user types in "end" for a title
  BookType *b;
  while(1){
  int d =  initBook(&b);
  if(d==C_OK)
      addByTitle(booksByTitle,b);
  else
      break;
   
  
  
  
  }
  printf("\n");
  printf("[Adding books to booksByTitle sorted in ascending order by title]\n \n");
  printf("===============BOOKS BY TITLE==============\n");
  printList(booksByTitle);

  printf("===========================================\n\n\n\n"); 
  

  printf("[Copying books from booksByTitle into tmpList]\n");
  copyList(booksByTitle,tmpList);
  printf("\n");
  printf("Select an author to remove from the tmpList: \n\n");
  scanf("%s",authorToRemove);
  delAuthor(tmpList,authorToRemove);

  printf("===============BOOKS BY TITLE==============\n\n");
  
  printf("[Books by '%s' have not been removed from booksByTitle.]\n\n"
          ,authorToRemove); 
  printList(booksByTitle);
 
  printf("===========================================\n\n");


  printf("==================TMP LIST=================\n\n"); 
  printf("[Books by '%s' have been removed from tmpList.]\n\n",authorToRemove);
  printList(tmpList);

  printf("==========================================\n\n\n\n");

  copyByYear(booksByTitle,booksByYear);

  printf("[Copying books into booksByYear sorted by year in descending order]\n");
  printf("\n");

  printf("===============BOOKS BY TITLE==============\n"); 
  printf("[Books are not sorted by year.] \n\n");
  printList(booksByTitle);

  printf("==========================================\n\n");


  printf("===============BOOKS BY YEAR===============\n"); 
  printf("[Books are sorted by year]\n\n");
  printList(booksByYear);

  printf("===========================================\n");


  // clean up the books that are shared by the lists first, then delete the lists. 
  cleanupData(booksByTitle);
  cleanupList(booksByTitle);
  cleanupList(booksByYear);
  cleanupList(tmpList);

  
  
  

        
   


return 0;

}




// init book asks for user input and dynamically alocates books using this input, 
// the int return parameter is used to show if a book was made or not, if a book was made C_OK is 
// returned, else C_NOK is returned.

int initBook(BookType **book){
  char title[MAX];
  char  author[MAX];
  int    year; 


  printf("Enter the title: ");
  printf("\n");
  scanf("%s",title);
  if(strcmp(title,"end")==0){
    return C_NOK;
  }
  printf("Enter the authors name: ");
  scanf("%s",author);
  
  printf("Enter the year: ");
  scanf("%d", &year);

  printf("\n");

  // dynamically alocate book 
  *book = (BookType*)malloc(sizeof(BookType));
  strcpy((*book)->title, title);
  strcpy((*book)->author, author);
  (*book)->year = year;

  return C_OK;
   
  


}

// initializes a listType data strucutre by setting the head to null 

void initList(ListType *l){
   
   l->head = NULL;
}



// adds book to list in correct order  
void addByTitle(ListType *list, BookType *newBook){
  
  NodeType *tmpNode;
  NodeType *currNode;
  NodeType *prevNode;
  
  tmpNode = malloc(sizeof(NodeType));
  tmpNode->data = newBook;
  tmpNode->next = NULL;

  currNode = list->head;
  prevNode = NULL;

    
  while(currNode != NULL){
      // strcmp == 1 means currNode data is larger than newBook data 
      if(strcmp(currNode->data->title,newBook->title)==1){
          break;
      }
      prevNode = currNode;
      currNode = currNode->next;
  }
  if(prevNode == NULL){

    list->head = tmpNode;
  }
  else{
      prevNode->next = tmpNode;
  }
  tmpNode->next = currNode;
}


// same as addByTitle, except books years are compared instead
void addByYear(ListType *list, BookType *newBook){    
  if (newBook!=NULL){    
    NodeType *tmpNode;                                                              
    NodeType *currNode;                                                             
    NodeType *prevNode;              
                                                                                                    
    tmpNode = malloc(sizeof(NodeType));                                             
    tmpNode->data = newBook;                                                        
    tmpNode->next = NULL;                                                                             
    
    currNode = list->head;                                                          
    prevNode = NULL;                                                                                  
                                    
  while(currNode != NULL){
      if(currNode->data->year < newBook->year){

          break;  
      }                                  
      prevNode = currNode;   
      currNode = currNode->next;                                                                    
  }
  // if prevNode null then there was no head in list 
  if(prevNode == NULL){                     
      list->head = tmpNode;                     
  }


  else{      
      prevNode->next = tmpNode;                                                
  }   
  tmpNode->next = currNode;
  }                                             
}                                                                                                   

// prints the list by itterating over the nodes starting at the head
void printList(ListType *list){

  int index =0;
  NodeType *currNode = list->head;
  // tail is used when printing out the tail, thats its only use 
  NodeType *tail = NULL;  
  
    
  while(currNode!=NULL){
  
  printBook(currNode->data);    
  tail = currNode;
  currNode = currNode->next;
  }
  printf("\n");

  if(list->head!=NULL){
      printf("[The book '%s' is the head of the list.]\n",
              list->head->data->title);
  
  }
  
  if(tail!=NULL){
      printf("[The book '%s' is the tail of the list.]\n", tail->data->title);
      
  }

}

// itterates of list nodes starting at the head, adding each book to dest 
void copyList(ListType *list, ListType *dest){

    NodeType *currNode;
    NodeType *prevNode;                                                                             
                                                                                                                                                                                                        
    currNode = list->head;    
    prevNode = NULL;                                                                                
                                                                                                    
  while(currNode != NULL){                                                                          
      addByTitle(dest, currNode->data);                                                     
      prevNode = currNode;                                                                          
      currNode = currNode->next;                                                                    
  }                                                                                                 
                                                                                                 
                                                                                                        

}


// same as copyList, however books are added using addByYear so they are in the corect order
void copyByYear(ListType *list, ListType *dest){

    NodeType *currNode;
    NodeType *prevNode;

    currNode = list->head;
    prevNode = NULL;

  while(currNode != NULL){
      addByYear(dest, currNode->data);
      prevNode = currNode;
      currNode = currNode->next;
  }

}

// itterated over list removing every book with the author 'name', 

void delAuthor(ListType *list, char *name){

  NodeType *currNode, *prevNode;

  currNode = list->head;
  prevNode = NULL;

  // checks if head data title is equal to name
  while(currNode != NULL && strcmp(currNode->data->author,name)==0){
   list->head = currNode->next;
   free(currNode);
   currNode = list->head;
  
  }
  // checks other nodes 
  while(currNode != NULL){
    while(currNode !=NULL && strcmp(currNode->data->author,name)!=0){
       prevNode = currNode;
       currNode = currNode->next;
    }
    if(currNode == NULL)
        return;
    prevNode->next = currNode->next;
    free(currNode);
    currNode = prevNode->next;
  }

}



// iterates over list, deleting each node 
void cleanupList(ListType *list){
    NodeType *currNode, *nextNode;

    currNode = list->head;
    while(currNode != NULL){
     nextNode = currNode->next;
     free(currNode);
     currNode = nextNode;

    }

}

// itterates over list deleting the data from each node 
void cleanupData(ListType *list){
     NodeType *currNode, *nextNode;                                                                  
                                                                                                    
    currNode = list->head;                                                                          
    while(currNode != NULL){                                                                        
     nextNode = currNode->next;                                                                     
     free(currNode->data);                                                                                
     currNode = nextNode;
    }

}



// this fn is used only to print book data, its used in the printList fn 
void printBook(BookType *b){
    printf("Title: %5s,  Author: %5s, Year: %d\n",b->title,b->author,b->year);
 
 
}



