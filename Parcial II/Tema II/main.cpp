#include <iostream>
#include <string>

using namespace std;


struct recipeStep{
  int stepNumber;
  string content;
};

struct Node
{
    recipeStep step;
    Node *next;
    Node *prev;
    
};

struct Node* head_ref = NULL;

int getCurrentStepNumber(){
  struct Node* ptr;
  ptr = head_ref;
  while(ptr != NULL) {
    if(ptr->next == NULL)
      return ptr->step.stepNumber;
     ptr = ptr->next;
  }
  return 0;
}



void pushNodeEnd(Node** head_ref, string content){
    
  Node* newNode = new Node();
  Node* last = *head_ref;

  struct Node* ptr;
  
  newNode->step.stepNumber = getCurrentStepNumber() + 1;
  
  newNode->step.content = content;

  newNode->next = NULL;

  if ((*head_ref) == NULL){
    newNode->prev = newNode;
    (*head_ref) = newNode;
    return;
  }

    while (last->next != NULL)
      last = last->next;
  
      last->next = newNode;

  newNode->prev = last;
  
}

  void displayList() {
   struct Node* ptr;
   ptr = head_ref;
   while(ptr != NULL) {
      cout<< ptr->step.stepNumber << " " <<ptr->step.content << endl;
      ptr = ptr->next;
   }
}



  void searchNode(int step){
   struct Node* ptr;
   ptr = head_ref;
   while(ptr != NULL) {
      if(ptr->step.stepNumber == step){
        cout<< ptr->step.stepNumber << " " <<ptr->step.content << endl;
        return;
      }
      ptr = ptr->next;
   }

    cout<< "No se encontro el paso." << endl;
  }

void updateNode(int step, string content){
 struct Node* ptr;
   ptr = head_ref;
   while(ptr != NULL) {
      if(ptr->step.stepNumber == step){
        ptr->step.content = content;

        cout<< "Paso Actualizado:" << endl;
        cout<< ptr->step.stepNumber << " " <<ptr->step.content << endl; 
        return; 
      }
      ptr = ptr->next;
   }

    cout<< "No se encontro el paso." << endl;

}

void emptyList() {
   struct Node *ptr, *nextTemp, *ptrTemp;
   ptr = head_ref;

   while(ptr != NULL) {
      nextTemp = ptr->next;
      ptr->step.content = "";
      ptr->step.stepNumber= 0;
      ptr->next = NULL;
      ptr->prev = NULL;
      ptrTemp = ptr;
      ptr = nextTemp;

      free(ptrTemp);
   } 
}

void deleteNode(int step){
  struct Node *ptr, *prevNode, *nextNode, *prtTemp;
   ptr = head_ref;
   bool foundFlag = false;
   while(ptr != NULL) {
      
      if(foundFlag){
        ptr->step.stepNumber -= 1; 
      }

      nextNode= ptr->next;

      if(ptr->step.stepNumber == step && !foundFlag){

        prevNode= ptr->prev;
        nextNode= ptr->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        prtTemp = ptr;

        ptr->next = NULL;
        ptr->prev = NULL;
        ptr->step.content= "";
        ptr->step.stepNumber= 0;
        foundFlag = true;
        
        free(prtTemp);
      
    }
     ptr = nextNode;

     
   }

  if(!foundFlag){
    cout<< "No se encontro el paso." << endl;
  }

}



int main(){
  pushNodeEnd(&head_ref, "Preparar los ingredientes");
  pushNodeEnd(&head_ref, "Mezclar los ingredientes");
  pushNodeEnd(&head_ref, "Hornear");
  pushNodeEnd(&head_ref, "Decorar");

  displayList();



  cout << endl;
 deleteNode(3);
  displayList();
  cout << endl;

  emptyList();
  displayList();

  return 0;
}

