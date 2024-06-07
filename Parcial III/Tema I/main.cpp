#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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
        string root = tree -> inf;
        if(inf<root){
            insertNode(tree->hi,inf);
        }
        else{
            insertNode(tree->hd,inf);
        }
    }
}

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
        return 1;
    }else{
        int left_h = treeHeight(tree->hi);
        int right_h = treeHeight(tree->hd);
        return (left_h>right_h ? left_h:right_h)+1;
    }
}

// Cantidad de hojas 
int leaves(Node * tree){
    if(tree == NULL){
        return 0;
    }
    if(tree->hi ==NULL && tree->hd ==NULL){
        return 1;
    }
    return leaves(tree->hi)+ leaves(tree->hd);
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

    }

    treetxt.close();
    return 0;
};
