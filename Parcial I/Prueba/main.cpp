// /*#include <iostream>
// #include <cstring>
// #include <ctime>

// using namespace std;
// // codigo de mezcla directa 
void merge(char* arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    char* L[n1];
    char* R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(char* arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

int main() {
    clock_t startClock;
    clock_t stopClock;

    cout<<"esto funciona?????"<<endl;
    char* arr[] = {"John", "Alice", "Ariana", "Bob", "David", "Eve", "Charlie"};

    int n = sizeof(arr) / sizeof(arr[0]);
    // aqui esta lo del reloj. Si quiere le explico, esto debe ir declarado siempre sobre el cosito de mergeSort
    startClock = clock();
    mergeSort(arr, 0, n - 1);
    stopClock = clock();
    double duration = double(stopClock - startClock) / CLOCKS_PER_SEC * 1000;
    cout<<"Tiempo fue de: "<<duration<<" milisegundos"<<endl;
    cout << "Arreglo ordenado: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}


#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Ordenamiento {

public:
    void mezclaNatural(string archivoClientes) {
        ifstream archivoEntrada(archivoClientes, ios::in);
        ofstream archivoTemporal("temp.dat", ios::out);

        if (!archivoEntrada) {
            cerr << "Error al abrir el archivo de clientes." << endl;
            return;
        }
        archivoTemporal << archivoEntrada.rdbuf();
        archivoTemporal.close();

        ifstream archivoTemporalLectura("temp.dat", ios::binary | ios::ate);
        int tamano = archivoTemporalLectura.tellg();
        archivoTemporalLectura.close();
        clock_t inicio = clock();

        mezclaNaturalAux("temp.dat", 0, tamano - 1);
        clock_t fin = clock();
        double duracion = double(fin - inicio) / CLOCKS_PER_SEC;
        cout << "Tiempo de duración del proceso: " << duracion << " segundos." << endl;
        mostrarArchivo("temp.dat");
        remove("temp.dat");
    }

private:
    void mezclaNaturalAux(string archivo, int izquierda, int derecha) {
        if (izquierda < derecha) {
            // Encontrar el punto medio
            int medio = izquierda + (derecha - izquierda) / 2;

            // Dividir y ordenar las partes
            mezclaNaturalAux(archivo, izquierda, medio);
            mezclaNaturalAux(archivo, medio + 1, derecha);

            // Mezclar las partes ordenadas
            mezclarArchivos(archivo, izquierda, medio, derecha);
        }
    }

    void mezclarArchivos(string archivo, int izquierda, int medio, int derecha) {
        ifstream archivoIzquierdo("temp.dat", ios::in | ios::binary);
        ifstream archivoDerecho("temp.dat", ios::in | ios::binary);

        // Posicionar punteros de lectura al inicio de las partes correspondientes
        archivoIzquierdo.seekg(izquierda * sizeof(Cliente));
        archivoDerecho.seekg((medio + 1) * sizeof(Cliente));

        // Archivo temporal para almacenar la mezcla
        ofstream archivoTemporal("temp_merge.dat", ios::out | ios::binary);

        // Variables auxiliares para comparación
        Cliente clienteIzquierdo, clienteDerecho;

        // Mezclar los archivos
        while (archivoIzquierdo.read((char*)&clienteIzquierdo, sizeof(Cliente)) &&
               archivoDerecho.read((char*)&clienteDerecho, sizeof(Cliente))) {
            if (strcmp(clienteIzquierdo.nombre, clienteDerecho.nombre) <= 0) {
                archivoTemporal.write((char*)&clienteIzquierdo, sizeof(Cliente));
                // Retroceder el puntero del archivo derecho para volver a leerlo
                archivoDerecho.seekg(-sizeof(Cliente), ios::cur);
            } else {
                archivoTemporal.write((char*)&clienteDerecho, sizeof(Cliente));
                // Retroceder el puntero del archivo izquierdo para volver a leerlo
                archivoIzquierdo.seekg(-sizeof(Cliente), ios::cur);
            }
        }

        // Copiar los elementos restantes del archivo izquierdo, si los hay
        while (archivoIzquierdo.read((char*)&clienteIzquierdo, sizeof(Cliente))) {
            archivoTemporal.write((char*)&clienteIzquierdo, sizeof(Cliente));
        }

        // Copiar los elementos restantes del archivo derecho, si los hay
        while (archivoDerecho.read((char*)&clienteDerecho, sizeof(Cliente))) {
            archivoTemporal.write((char*)&clienteDerecho, sizeof(Cliente));
        }

        // Cerrar archivos
        archivoIzquierdo.close();
        archivoDerecho.close();
        archivoTemporal.close();

        // Copiar el archivo mezclado temporal al archivo original
        ifstream archivoTemporalLectura("temp_merge.dat", ios::in | ios::binary);
        ofstream archivoOriginal("temp.dat", ios::out | ios::binary);

        archivoOriginal << archivoTemporalLectura.rdbuf();

        // Cerrar archivos
        archivoTemporalLectura.close();
        archivoOriginal.close();

        // Eliminar el archivo temporal de mezcla
        remove("temp_merge.dat");
    }

    void mostrarArchivo(string archivo) {
        ifstream archivoLectura(archivo, ios::in | ios::binary);

        if (!archivoLectura) {
            cerr << "Error al abrir el archivo." << endl;
            return;
        }

        cout << "Contenido del archivo ordenado:" << endl;

        Cliente cliente;
        while (archivoLectura.read((char*)&cliente, sizeof(Cliente))) {
            cout << "Nombre: " << cliente.nombre << ", Edad: " << cliente.edad << endl;
        }

        archivoLectura.close();
    }

    struct Cliente {
        char nombre[50];
        int edad;
    };
};

int main() {
    Ordenamiento ordenador;
    ordenador.mezclaNatural("clientes.dat");

    return 0;
}


// NOTAAAAAAAAAAAAAAAAAA los comentarios fueron puestos por ariani y por mi para guia de lo que hicimos, cualquier cosa POR FAVOR nos avisas besitos
// en la cola
// :p


// Nota 2: arriba hay un boseto de lo que estaba haciendo, por si algo no funciona abajo :( los dos de arriba son 100% funcionales 

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

class Sorting {
public:
    // ------------------------------ Metodo de Quicksort ------------------------------
    void quicksort(Products arr[], int low, int high){ //Recibe un objeto de Products, ojo
        int middle, i, j;
        middle = (low+high)/2;

        //pivote en valor central
        string pivot = arr[middle].getName();
        //separar segmentos
        i = low;
        j = high;

        while(i<=j){
            //separando en dos partes el array
            while(arr[i].getName()<pivot) i++; //separo valores menores del pivote
            while(arr[j].getName()>pivot) j--; //separo valores mayores del pivote
            if(i<=j){ //intercambio de valores 
                Product temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }
        if(low<j)
            quicksort(arr,low,j);
        if(i<high)
            quicksort(arr,i,high);   
    }
    
    
    /// ------------------------------ Mezcla directa ------------------------------
    // aqui esta mas que todo lo de los archivos
    void directMerge(string clientsFile) {
        //Nota tem_direct es un archivo auxiliar temporal de la mezcla directa:)
        ifstream inputFile(clientsFile, ios::in | ios::binary);
        ofstream tempFile("temp_direct.dat", ios::out | ios::binary);

        if (!inputFile) {
            cerr << "Hubo un error al abrir el archivo." << endl;
            return;
        }

        tempFile << inputFile.rdbuf();
        tempFile.close();

        ifstream tempInput("temp_direct.dat", ios::in | ios::binary);
        int size = getFileSize(tempInput);
        tempInput.close();
        clock_t start = clock();

        directMergeAux("temp_direct.dat", 0, size - 1);
        clock_t end = clock();
        double duration = double(end - start) / CLOCKS_PER_SEC * 1000;
        cout << "Tiempo de duracion del proceso: " << duration << " milisegundos." << endl;
        showFile("temp_direct.dat");
        remove("temp_direct.dat");
    }


    // ------------------------------ Mezcla natural ------------------------------
    void naturalMerge(string clientsFile) {
        ifstream inputFile(clientsFile, ios::in | ios::binary);
        ofstream tempFile("temp_natural.dat", ios::out | ios::binary);

        if (!inputFile) {
            cerr << "Hubo un error al abrir el archivo de clientes." << endl;
            return;
        }

        tempFile << inputFile.rdbuf();
        tempFile.close();

        ifstream tempInput("temp_natural.dat", ios::in | ios::binary);
        int size = getFileSize(tempInput);
        tempInput.close();
        clock_t start = clock();

        naturalMergeAux("temp_natural.dat", 0, size - 1);
        clock_t end = clock();
        double duration = double(end - start) / CLOCKS_PER_SEC * 1000;
        cout << "Tiempo de duracion del proceso: " << duration << " seconds." << endl;
        showFile("temp_natural.dat");
        remove("temp_natural.dat");
    }

private:
    // ------------------------------ Aqui esta la logica de la mezcla directa y natural ------------------------------
    void directMergeAux(string file, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            directMergeAux(file, left, mid);
            directMergeAux(file, mid + 1, right);
            mergeFilesDirect(file, left, mid, right);
        }
    }

    void naturalMergeAux(string file, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            naturalMergeAux(file, left, mid);
            naturalMergeAux(file, mid + 1, right);
            mergeFilesNatural(file, left, mid, right);
        }
    }


    // escritura sobre archivo
    void mergeFilesDirect(string file, int left, int mid, int right) {
        ifstream leftFile("temp_direct.dat", ios::in | ios::binary);
        ifstream rightFile("temp_direct.dat", ios::in | ios::binary);

        //En client se pasa lo del archivo del cliente tho :)  

        Client client;

        leftFile.seekg(left * sizeof(Client));
        rightFile.seekg((mid + 1) * sizeof(Client));

        ofstream tempFile("temp_merge_direct.dat", ios::out | ios::binary);

        Client leftClient;
        Client rightClient;

        while (leftFile.read((char*)&leftClient, sizeof(Client)) &&
               rightFile.read((char*)&rightClient, sizeof(Client))) {
            if (strcmp(leftClient.name, rightClient.name) <= 0) {
                tempFile.write((char*)&leftClient, sizeof(Client));
                rightFile.seekg(-sizeof(Client), ios::cur);
            } else {
                tempFile.write((char*)&rightClient, sizeof(Client));
                leftFile.seekg(-sizeof(Client), ios::cur);
            }
        }

        while (leftFile.read((char*)&leftClient, sizeof(Client))) {
            tempFile.write((char*)&leftClient, sizeof(Client));
        }

        while (rightFile.read((char*)&rightClient, sizeof(Client))) {
            tempFile.write((char*)&rightClient, sizeof(Client));
        }

        leftFile.close();
        rightFile.close();
        tempFile.close();

        ifstream tempRead("temp_merge_direct.dat", ios::in | ios::binary);
        ofstream tempOriginal("temp_direct.dat", ios::out | ios::binary);

        tempOriginal << tempRead.rdbuf();

        tempRead.close();
        tempOriginal.close();
        remove("temp_merge_direct.dat");
    }

    void mergeFilesNatural(string file, int left, int mid, int right) {
        ifstream leftFile("temp_natural.dat", ios::in | ios::binary);
        ifstream rightFile("temp_natural.dat", ios::in | ios::binary);

        leftFile.seekg(left * sizeof(Client));
        rightFile.seekg((mid + 1) * sizeof(Client));

        ofstream tempFile("temp_merge_natural.dat", ios::out | ios::binary);

        Client leftClient;
        Client rightClient;

        while (leftFile.read((char*)&leftClient, sizeof(Client)) &&
               rightFile.read((char*)&rightClient, sizeof(Client))) {
            if (strcmp(leftClient.name, rightClient.name) <= 0) {
                tempFile.write((char*)&leftClient, sizeof(Client));
                rightFile.seekg(-sizeof(Client), ios::cur);
            } else {
                tempFile.write((char*)&rightClient, sizeof(Client));
                leftFile.seekg(-sizeof(Client), ios::cur);
            }
        }

        while (leftFile.read((char*)&leftClient, sizeof(Client))) {
            tempFile.write((char*)&leftClient, sizeof(Client));
        }

        while (rightFile.read((char*)&rightClient, sizeof(Client))) {
            tempFile.write((char*)&rightClient, sizeof(Client));
        }

        leftFile.close();
        rightFile.close();
        tempFile.close();

        ifstream tempRead("temp_merge_natural.dat", ios::in | ios::binary);
        ofstream tempOriginal("temp_natural.dat", ios::out | ios::binary);

        tempOriginal << tempRead.rdbuf();

        tempRead.close();
        tempOriginal.close();
        remove("temp_merge_natural.dat");
    }

    int getFileSize(ifstream& file) {
        file.seekg(0, ios::end);
        int size = file.tellg();
        file.seekg(0, ios::beg);
        return size / sizeof(Client);
    }

    void showFile(string file) {
        ifstream inputFile(file, ios::in | ios::binary);

        if (!inputFile) {
            cerr << "Error abriendo el archivo." << endl;
            return;
        }

        cout << "Contenido del archivo ordenado: " << endl;

        Client client;
        while (inputFile.read((char*)&client, sizeof(Client))) {
            cout << "Name: " << client.name << ", Phone: " << client.phone << ", Address: " << client.address << endl;
        }

        inputFile.close();
    }
};

int main() {
    Sorting sorter;
    sorter.directMerge("clients.dat");
    sorter.naturalMerge("clients.dat");

    return 0;
}
