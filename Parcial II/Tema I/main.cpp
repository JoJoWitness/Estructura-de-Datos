#include <iostream>
#include <time.h>
#include <string>
#include <string.h>

using namespace std;



class Queue{
  private:
    int front;
    int end;
    int queue[25];
    int clientCode;

  public:
    Queue(){
      front = -1;
      end = -1;
    }

    void enqueue(int clientCode){
      if(front == -1){
        front = 0;
      }
      if(!isFull()){
        if(end == sizeof(queue)/sizeof(queue[0]) - 1 && front != 0){
        
        end = 0;
        queue[end] = clientCode;
        return;
        }

        ++end;
        queue[end] = clientCode;
      }
      else{
        cout << "La cola esta llena" << endl;
      }
    };

    int dequeue(){
      if(!isEmpty()){

        clientCode = queue[front];
        queue[front] = 0;
        if(front == end){
          front = -1;
          end = -1;
        };
        front++;
        return clientCode;
      }
      else{
        return -1;
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
      if (front == 0 && end == sizeof(queue)/sizeof(queue[0])){
        return true;
      }
      else if(front - end == 1){
        return true;
      }
      else{
        return false;
      }
    };

    bool compareCode(int clientCode){  
      bool flag = true;
      int i = front;

      while(flag){
        if(queue[i] == 0){
          flag = false;
        }
        if(clientCode == queue[i]){
          return true;
        }
        if(i == sizeof(queue)/sizeof(queue[0])){
          i = 0;
        }

      }
      return false;
    }

    void displayQueue(){
      bool flag = true;
      int i = front;
      
      if(!isEmpty){
        cout << "Codigos en cola: " << endl;
        while(flag){
          if(queue[i] == 0){
            flag = false;
          }
          if(i == sizeof(queue)/sizeof(queue[0])){
            i = 0;
          }
          cout << queue[i] << endl;
        }
      }
      else{
        cout << "La cola esta vacia." << endl;
      }

    }

    bool generateCode(int clientId){
      string strId = to_string(clientId);
      int size = strId.length();
      string strCutId;
      int cutId, decreasedId;

      if(size >= 3){
        strCutId = strId[size-3] + strId[size-2] + strId[size-1];
        cutId = stoi(strCutId);
        
        if(compareCode(cutId)){
          strId.erase(strId.begin() + size -1);
          decreasedId = stoi(strId);
          generateCode(decreasedId);
        }
        else{
          return true;
        }
      }
      else{
        return false;
      }
    }

};

