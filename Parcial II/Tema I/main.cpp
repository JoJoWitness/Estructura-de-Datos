#include <iostream>
#include <time.h>
#include <string>
#include <string.h>

using namespace std;

class Queue{
  private:
    int front;
    int end;
    string queue[25], clientCode;

  public:
    Queue(){
      for(int i = 0; i < sizeof(queue)/sizeof(queue[0]); i++){
        queue[i] = "";
      }
      front = -1;
      end = -1;
    }

    void enqueue(string clientCode){
      
      if(front == -1){
        front = 0;
      }
    
      if(!isFull()){
        
        if(end == sizeof(queue)/sizeof(queue[0]) - 1 && front != 0){
        
        end = 0;
        queue[end] = clientCode; 
        return;
        }

        end++;      
        queue[end] = clientCode;       
      }
      else{
        cout << "La cola esta llena" << endl;
      }
    };

    string dequeue(){
      if(!isEmpty()){

        clientCode = queue[front];
        queue[front] = "";
        if(front == end){
          front = -1;
          end = -1;
        }
        else if(front == sizeof(queue)/sizeof(queue[0]) - 1){
          front = 0;
        }
        else{
          front++;
        }
       
        return clientCode;
      }
      else{
        return "###";
      }
    };

    bool isEmpty(){
      if(front == -1){
        return true;
      }
      else{
        return false;
      }
    };

    bool isFull(){
      if (front == 0 && end == sizeof(queue)/sizeof(queue[0])-1){
        return true;
      }
      else if(front - abs(end) == 1){
        return true;
      }
      else{
        return false;
      }
    };

    bool compareCode(string clientCode){  
      bool flag = true;
      int i = (front > -1) ? front : 0;
      int tempClientCode = stoi(clientCode);
      int tempQueueCode;

      while(flag){
        if(queue[i] == ""){
          flag = false;
          break;
        }
        tempQueueCode = stoi(queue[i]);
        if(i == end){
          flag = false;
        }
        if(tempClientCode == tempQueueCode){
          return true;
        }
        if(i == sizeof(queue)/sizeof(queue[0]) - 1){
          i = 0;
          continue;
        }
          i++;
      }

      return false;
    }

    void displayQueue(){
      bool flag = true;
      int i = front;
      if(!isEmpty()){
        cout << "Codigos en cola: " << endl;
        cout << "                           ___   "<< endl;
        while(flag){
          if(i == end)  {
            flag = false;
          }
          if(i > sizeof(queue)/sizeof(queue[0]) -1){
            i = 0;
            continue;
          }
          cout << "                          |" << queue[i] << "|   "<< endl;
          i++;
        }
        cout << "                          |___|   "<< endl;
        }
      else{
        cout << "La cola esta vacia." << endl;
      }

    }

    void generateCode(string clientId){
      int size = clientId.length();
      string strCutId;
      if(size >= 3){
        strCutId = clientId.substr(size-3, 3);
        if(compareCode(strCutId)){
          clientId.erase(clientId.begin() + size -1);
          generateCode(clientId);
        }
        else{
          enqueue(strCutId);
          return;
        }
      }
      else{
        return;
      };
    }
    
    int getEnd(){
      return end;
    }

};
class Stack{
  private:
    int top;
    char stack[25];

  public:
    Stack(){
       for(int i = 0; i < sizeof(stack)/sizeof(stack[0]); i++){
        stack[i] = ' ';
      }
      top = -1;
  };

  void push(int clientCode){
    if(!isFull()){
      top++;
      stack[top] = clientCode;
    }
    else{
      cout << "La pila esta llena" << endl;
    }
  };

  char pop(){
    char clientCode;
    if(!isEmpty()){
      clientCode = stack[top];
    
      top--;
      return clientCode;
    }
    else{
      return 'f';
    }
  };

  bool isFull(){
    if(top == sizeof(stack)/sizeof(stack[0]) - 1){
      return true;
    }
    else{
      return false;
    }
  };
  
  bool isEmpty(){
    if(top == -1){
      return true;
    }
    else{
      return false;
    }
  };

  void invertCode(string clientId){
    for(int i = 0; i < clientId.length() ; i++){
      push(clientId[i]);
    }
  };

  string getinvertCode(){
    string strInvertedCode =""; 
    int n = top;
      for(int i = 0; i < n+1 ; i++){
        if(!isEmpty()){    
          strInvertedCode += pop();
        }
      }
    return strInvertedCode;
};
};

int main(){

  Queue clientQueue;

  string taquilla1= "###", taquilla2 = "###", taquilla3= "###";
  char menuOption;
  bool flag1 = true, flag2 = true;
  string currentClientId;
  int tempEnd; 

  cout << "-------------------------------------------------------------------" << endl;
  cout << "--------------BIENVENID@ AL SISTEMA DEL BANCO TESORO---------------" << endl;
  cout << "-------------------------------------------------------------------" << endl;
  cout << endl;
  cout << endl;
  cout << "A continuacion se dara una breve aclaratoria del funcionamiento de este sistema"<< endl;
  cout << "Antes de realizar cualquier accion dentro del sistema, se mostrara el estado de las taquillas y de la cola de usuario"<< endl;
  cout << "El valor ### es un placeholder para no romper la estetica de la impresion" << endl;
  cout << endl;
  cout << endl;
  
  while(flag1){
    cout << "______________________________________________________" << endl;
    cout << "|  Taquilla 1  |   |  Taquilla 2  |   |  Taquilla 3  |" << endl;
    cout << "|              |   |              |   |              |" << endl;
    cout << "|      " << taquilla1 << "     |   " << "|      " << taquilla2 << "     |   " << "|      " << taquilla3 << "     |   "<< endl;
    cout << "|______________|___|______________|___|______________|" << endl;
    cout << endl;
    clientQueue.displayQueue();
    cout << endl;
    flag2 = true;

    while(flag2){
      cout << "Que desea realizar? presione la tecla que desee" << endl;
      cout << "A. Ingresar un nuevo cliente a la cola" << endl;
      cout << "1. Llamar al siguiente de la cola virtual en taquilla 1." << endl;
      cout << "2. Llamar al siguiente de la cola virtual en taquilla 2." << endl;
      cout << "3. Llamar al siguiente de la cola virtual en taquilla 3." << endl;
      cout << "F. Finalizar el programa" << endl;
      cout << endl;

      cin >> menuOption;

      if(isdigit(menuOption)){
        menuOption = menuOption;
      } else {menuOption = toupper(menuOption);}

      switch (menuOption)
      {
      case 'A':
        cout << "Ingrese el ID del cliente, minimo 3 digitos" << endl;
        cin >> currentClientId;
        tempEnd = clientQueue.getEnd();
        clientQueue.generateCode(currentClientId);
        if(tempEnd == clientQueue.getEnd()){
          Stack invertedCodeStack;
          invertedCodeStack.invertCode(currentClientId);
          clientQueue.generateCode(invertedCodeStack.getinvertCode());
        }
          
        flag2 = false;
        break;
      
      case '1':
        taquilla1 = clientQueue.dequeue();
        flag2 = false;
        break;
      case '2':
        taquilla2 = clientQueue.dequeue();
        
        flag2 = false;
        break;
      case '3':
        taquilla3 = clientQueue.dequeue();
        flag2 = false;
        break;
      case 'F':
        cout << "------------------------------------------------------------------"<<endl;
        cout << "-------------------Gracias por usar el programa-------------------" << endl;
        cout << "------------------------------------------------------------------"<<endl;
        flag1 = false;
        flag2 = false;
        break;
      
      default:
        cout << "Opcion no valida, intente de nuevo\n" << endl;
        break;
      }
    }
  }

  return 0;
}
