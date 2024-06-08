#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <bits/stdc++.h>

/*
    Parcial III Practica 1 ABB Integrantes:
    9907856 Jordano Pernia
    29929240 Oriana Moreno
    31180603 Ariani Valera
*/

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
int calculateTreeHeight(Node * tree){
    if(tree==NULL){
        return 0;
    }else{
        int left_h = calculateTreeHeight(tree->hi);
        int right_h = calculateTreeHeight(tree->hd);
        return (left_h>right_h ? left_h +1:right_h+1);
    }

}

// Cantidad de hojas 
unsigned int countLeaves(Node * tree){
    if(tree == NULL){
        return 0;
    }
    if(tree->hi ==NULL && tree->hd ==NULL){
        return 1;
    }
    
    return countLeaves(tree->hi) + countLeaves(tree->hd);
    
}

// Imprimir contenido hojas
void printLeaves(Node * tree){
    if(tree == NULL){
        return;
    }
    if(tree->hi ==NULL && tree->hd ==NULL){
        cout<<tree->inf<<" ";
    }
    printLeaves(tree->hi);
    printLeaves(tree->hd);
}

// Imprimir arbol
void printTree(Node * tree,int cont){
      if(tree==NULL){
        return;
    }else{
        printTree(tree->hd,cont+1);
        for(int i=0;i<cont;i++){
            cout<<"     ";
        }
        cout<<tree->inf<<endl;
        printTree(tree->hi,cont+1);
    }
}

// Verificar arbol equilibrado
bool isBalanced(Node * tree){
    int left_h, right_h;
    if(tree == NULL){
        return true;
    }
    left_h = calculateTreeHeight(tree->hi);
    right_h = calculateTreeHeight(tree->hd);

    if(abs(left_h-right_h)<= 1 && isBalanced(tree->hi) && isBalanced(tree->hd)){
        return true;
    }
    return false; 
}



// Iniciar ABB
Node *tree = NULL;

int main(){
    int treeNum=1,h,leavesNum;
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
        getline(treetxt, sentence);
        istringstream iss(sentence);
        
        
        while(iss >> word){
            insertNode(tree,word);
        }

        cout << "\n---------------------------------------------------------------" << endl;
        cout<<"--------------------------- ARBOL -"<<treeNum<<" -------------------------- "<<endl;
        cout<<endl;
        printTree(tree,0);
        cout<<endl;
        cout << "Busqueda Postorder: ";
        postOrder(tree);
        cout<<endl;
        cout<<endl;
        h = calculateTreeHeight(tree);
        cout<<"Altura: "<<h<<endl;
        leavesNum = countLeaves(tree) ;
        cout<<"Cantidad de nodos hoja: "<< leavesNum <<endl;
        cout<<"Nodos hoja: ";
        printLeaves(tree);
        cout<<endl;
        balance = isBalanced(tree);
        cout<<"Balance: "<<(balance?" Es equilibrado":" No esta equilibrado")<<endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << endl;
    

        treeNum++;
        tree = NULL;
    }

    treetxt.close();
    return 0;
}
