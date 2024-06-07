#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct Node{
    string inf;
    Node *hi,*hd;

    // constructor 
    Node(string val): inf(val), hi(NULL), hd(NULL){}
};

// funcion para insertar nodos al ABB
void insertNode(Node *&tree, string inf){
    if(tree == NULL){
        Node *new_node = new Node(inf); 
        tree = new_node;
    }else{
        
        if(strcmp(inf.c_str(), tree -> inf.c_str()) < 0){
            insertNode(tree->hi,inf);
        }
        else{
            insertNode(tree->hd,inf);
        }
    }
};

// Funcion recorrido postorden
void postOrder(Node * tree){
    if(tree==NULL){
        return;
    }else{
        postOrder(tree->hi);
        postOrder(tree->hd);
        cout<<tree->inf<<" - ";
    }
}

// Calcular altura
int treeHeight(Node * tree){
    if(tree==NULL){
        return 0;
    }else{
        int left_h = treeHeight(tree->hi);
        int right_h = treeHeight(tree->hd);
        return (left_h>right_h ? left_h +1:right_h+1);
    }

}

// Cantidad de hojas 
unsigned int leaves(Node * tree){
    if(tree == NULL){
        return 0;
    }
    if(tree->hi ==NULL && tree->hd ==NULL){
        return 1;
    }
    
    return leaves(tree->hi) + leaves(tree->hd);
    
}

// Verificar arbol equilibrado
bool isBalanced(Node * tree){
    int left_h, right_h;
    if(tree == NULL){
        return true;
    }
    left_h = treeHeight(tree->hi);
    right_h = treeHeight(tree->hd);

    if(abs(left_h-right_h)<= 1 && isBalanced(tree->hi) && isBalanced(tree->hd)){
        return true;
    }
    return false; 
}



// Iniciar ABB
Node *tree = NULL;

int main(){
    int ntree=1,h,leavesNum;
    bool balance;
    string word;
    string sentence;
    ifstream treetxt;
    treetxt.open("arbol.txt");

    if (treetxt.fail()) {
        cerr << "Error al leer el archivo." << endl;
        return 1;
    }

    while(!treetxt.eof()){
        //treetxt.getline(sentence,LENGHT,'\n');
        getline(treetxt, sentence);
        istringstream iss(sentence);
        
        
        while(iss >> word){
            insertNode(tree,word);
        }

        cout<<"Arbol-"<<ntree<<" (Postorder): "<<endl;
        postOrder(tree);

        h = treeHeight(tree);
        cout<<"Altura: "<<h<<endl;
        leavesNum = leaves(tree) ;
        cout<<"Nodos Hoja: "<< leavesNum <<endl;
        balance = isBalanced(tree);
        cout<<"Balance: "<<(balance?" Es balanceado":" No esta balanceado")<<endl;
        cout << endl;
    

        ntree++;
        tree = NULL;
    }

    treetxt.close();
    return 0;
}
