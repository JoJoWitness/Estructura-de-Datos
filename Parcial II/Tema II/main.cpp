#include <iostream>
#include <string>
#include <cctype>
#include <limits>
using namespace std;


// Parcial II Practica 2 Integrantes:
// 29907856 Jordano Pernia
// 29929240 Oriana Moreno
// 31180603 Ariani Valera
//

struct recipeStep {
    int stepNumber;
    string content;
};

struct Node {
    recipeStep step;
    Node *next;
    Node *prev;
};

struct Node* head_ref = NULL;

int getCurrentStepNumber() {
    struct Node* ptr;
    ptr = head_ref;
    while (ptr != NULL) {
        if (ptr->next == NULL)
            return ptr->step.stepNumber;
        ptr = ptr->next;
    }
    return 0;
}

void pushNodeEnd(Node** head_ref, string content) {
    Node* newNode = new Node();
    Node* last = *head_ref;

    struct Node* ptr;

    newNode->step.stepNumber = getCurrentStepNumber() + 1;
    newNode->step.content = content;
    newNode->next = NULL;

    if ((*head_ref) == NULL) {
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
    while (ptr != NULL) {
        cout << ptr->step.stepNumber << " " << ptr->step.content << endl;
        ptr = ptr->next;
    }
}

void searchNode(int step) {
    struct Node* ptr;
    ptr = head_ref;
    while (ptr != NULL) {
        if (ptr->step.stepNumber == step) {
            cout << ptr->step.stepNumber << " " << ptr->step.content << endl;
            return;
        }
        ptr = ptr->next;
    }
    cout << "No se encontro el paso." << endl;
}

void updateNode(int step, string content) {
    struct Node* ptr;
    ptr = head_ref;
    while (ptr != NULL) {
        if (ptr->step.stepNumber == step) {
            ptr->step.content = content;
            cout << "Paso Actualizado:" << endl;
            cout << ptr->step.stepNumber << " " << ptr->step.content << endl;
            return;
        }
        ptr = ptr->next;
    }
    cout << "No se encontro el paso." << endl;
}

void emptyList() {
    struct Node *ptr, *nextTemp, *ptrTemp;
    ptr = head_ref;

    while (ptr != NULL) {
        nextTemp = ptr->next;
        ptr->step.content = "";
        ptr->step.stepNumber = 0;
        ptr->next = NULL;
        ptr->prev = NULL;
        ptrTemp = ptr;
        ptr = nextTemp;

        free(ptrTemp);
    }
    head_ref = NULL;
}

void deleteNode(int step) {
    struct Node *ptr, *prevNode, *nextNode, *prtTemp;
    ptr = head_ref;
    bool foundFlag = false;
    while (ptr != NULL) {
        if (foundFlag) {
            ptr->step.stepNumber -= 1;
        }

        nextNode = ptr->next;

        if (ptr->step.stepNumber == step && !foundFlag) {
            prevNode = ptr->prev;
            nextNode = ptr->next;
            if (prevNode != NULL) {
                prevNode->next = nextNode;
            }
            if (nextNode != NULL) {
                nextNode->prev = prevNode;
            }
            if (ptr == head_ref) {
                head_ref = nextNode;
            }
            prtTemp = ptr;

            ptr->next = NULL;
            ptr->prev = NULL;
            ptr->step.content = "";
            ptr->step.stepNumber = 0;
            foundFlag = true;

            free(prtTemp);
        }
        ptr = nextNode;
    }

    if (!foundFlag) {
        cout << "No se encontró el paso." << endl;
    }
}

void viewStepsOneByOne() {
    struct Node* ptr = head_ref;
    char choice;
    if (ptr == NULL) {
        cout << "\nNo hay pasos en la receta." << endl;
        return;
    }
    while (ptr != NULL) {
        cout << "\nPaso " << ptr->step.stepNumber << ": " << ptr->step.content << endl;
        cout << "1. Ver paso anterior \n2. Continuar  \n3. Volver al menu" << endl;
        cout << "Seleccione una opcion: ";
        cin >> choice;
        if (choice == '1') {
            if (ptr->prev != NULL) {
                ptr = ptr->prev;
            } else {
                cout << "\nEste es el primer paso." << endl;
            }
        } else if (choice == '2') {
            if (ptr->next != NULL) {
                ptr = ptr->next;
            } else {
                cout << "\nEste es el ultimo paso." << endl;
                break;
            }
        } else if (choice == '3') {
            break;
        } else {
            cout << "Opcion no valida, intente de nuevo." << endl;
        }
    }
}


int getStepCount(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}


int main() {
    string recipeName;
    char option;

    cout<<"\n************************************************"<<endl;
    cout<<"-------\t\t COOK THE CODE\t\t-------"<<endl;
    cout<<"************************************************\n"<<endl;

    
    cout<<"------------Bienvenido a Cook The Code------------"<<endl;
    cout<<"\nUn lugar donde puede almacenar tu receta favorita."<<endl;
    cout<<"Puedes agregar tantos pasos como desees, pero solo"<<endl;
    cout<<"una receta. Por lo que asegurate que sea especial"<<endl;
    cout<<"para que asi puedas recordarla siempre!"<<endl;

    do {
        cout<<"\n\n--------------------------------------------------"<<endl;
        cout << "\t\t  Menu de opciones\t\t" << endl;
        cout<<"--------------------------------------------------"<<endl;
        cout << "1. Agregar la receta" << endl;
        cout << "2. Ver la receta" << endl;
        cout << "3. Ver pasos en secuencia" << endl;
        cout << "4. Buscar paso" << endl;
        cout << "5. Editar paso" << endl;
        cout << "6. Eliminar paso" << endl;
        cout << "7. Eliminar la receta" << endl;
        cout << "8. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> option;

        switch (option) {
            case '1': {
                int step = 1; 
                string content;
                char addMore;
                system("cls");
                cout << "--------------------------------------------------" << endl;
                cout << "          Ingrese los pasos de la receta" << endl;
                cout << "--------------------------------------------------" << endl;
                
                if(!recipeName.empty()) {
                    cout << "La receta " << recipeName << " ya ha sido ingresada!" << endl;
                    cout << "Desea agregar mas pasos? \n1. Si \n2. No" << endl;
                    cout << "Opcion: ";
                    cin >> addMore;
                    cout << endl;
                    if (addMore == '2') {
                        system("cls");
                        break;                        
                    } else {
                        step = getStepCount(head_ref) + 1;
                    }
                } else {
                    cout << "Ingrese el nombre de la receta: ";
                    cin.ignore();
                    getline(cin, recipeName);
                }
                
                

                do {
                    cout << "Ingrese el paso " << step << " de la receta: ";
                    getline(cin, content);
                    pushNodeEnd(&head_ref, content);
                    cout << "-- Desea agregar otro paso? \n1. Si \n2. No" << endl;
                    cout << "Opcion: ";
                    cin >> addMore;
                    cout << endl;
                    step++;
                    cin.ignore(); 
                } while (addMore == '1');

                system("cls");
                cout << ".... La receta ha sido guardada ...." << endl;
                break;
            }
            case '2': {
                if (recipeName == ""){
                        system("cls");
                        cout<<"\nNo ha agregado una receta."<<endl;
                        cout<<endl;
                        system("pause");
                        system("cls");
                        break;
                }
                system("cls");
                cout<<"\n--------------------------------------------------"<<endl;
                cout << "\t\t    "<< recipeName << endl;
                cout<<"--------------------------------------------------"<<endl;
                displayList();
                cout<<endl;
                system("pause");
                system("cls");
                break;

            }
            case '3': { //ver uno por uno
                system("cls");
                cout<<"\n--------------------------------------------------"<<endl;
                cout << "\t\t Pasos en la secuencia" << endl;
                cout<<"--------------------------------------------------"<<endl;
                viewStepsOneByOne();
                system("pause");
                system("cls");
                break;
            }
            case '4': { // busqueda
                char searchMore;
                do{
                    system("cls");
                    if(searchMore != '1'){
                    cout<<"\n--------------------------------------------------"<<endl;
                    cout << "\t\t   Busqueda" << endl;
                    cout<<"--------------------------------------------------"<<endl;
                    }
                
                    int stepNumber;
                    cout << "Ingrese el numero del paso a buscar: ";
                    cin >> stepNumber;
                    searchNode(stepNumber);

                    cout<<"\nDesea buscar otro paso? \n1. Si \n2. No"<<endl;
                    cout<<"Opcion: ";
                    cin>> searchMore;
                }while(searchMore == '1');
                
                system("cls");
                break;
            }
            case '5': {//edicion paso
                system("cls");
                cout<<"\n--------------------------------------------------"<<endl;
                cout << "\t\t   Editar un paso" << endl;
                cout<<"--------------------------------------------------"<<endl;
                int stepNumber;
                string content;
                
                cout << "Receta actual: "<<recipeName<< endl;
                displayList();

                cout << "\nIngrese el numero del paso a editar: ";
                cin >> stepNumber;
                cout << "Ingrese nuevo contenido del paso: ";
                cin.ignore();
                getline(cin, content);
                updateNode(stepNumber, content);

                cout<<"\n--------------------------------------------------"<<endl;
                cout <<"Los nuevos pasos de la receta "<<recipeName<<endl;
                displayList();
                cout<<endl;
                system("pause");
                system("cls");
                break;
            }
            case '6': {//eliminar paso
                system("cls");
                cout<<"\n--------------------------------------------------"<<endl;
                cout << "\t\t   Eliminar un paso" << endl;
                cout<<"--------------------------------------------------"<<endl;
                int stepNumber;

                cout << "Receta actual:" << endl;
                displayList();

                cout << "\nIngrese el numero del paso a eliminar: ";
                cin >> stepNumber;
                deleteNode(stepNumber);

                cout<<"\n--------------------------------------------------"<<endl;
                cout <<"Los nuevos pasos de la receta "<<recipeName<<endl;
                displayList();
                cout<<endl;
                system("pause");
                system("cls");
                break;
            }
            case '7': {//eliminar receta
                system("cls");
                emptyList();
                cout<<"\n--------------------------------------------------"<<endl;
                cout << "La receta "<<recipeName<<" ha sido eliminada." << endl;
                cout<<"--------------------------------------------------\n"<<endl;
                system("pause");
                system("cls");
                break;
            }
            case '8': {
                system("cls");
                cout<<"\n------------------------------------------------------"<<endl;
                cout << " Muchas gracias por compartir su receta con nosotros." << endl;
                cout<<"------------------------------------------------------\n"<<endl;
                break;
            }
            default: {
                cout << "\n  !!Opcion no valida, intente de nuevo!!" << endl;
                break;
            }
        }
    } while (option != '8');

    return 0;
}
