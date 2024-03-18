#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
// PROGRAMA DEMO PARA APLICAR LOS PRINCIPALES METODOS DE fstream
// GUARDA DATOS EN UN ARCHIVO NUEVO Y LO ABRE PARA LEER SECUENCIALMENTE E IMPRIMIR
// Actividad: Reemplaza los signos de interrogacion con los metodos u operadores correspondientes, 
//            compilar y ejecutar el programa correctamente
enum tipo{gato, perro, conejo};
string Tipo[]={"gato","perro","conejo"};

class Mascota
{
    private:
        string nom;
        int  edad;
        tipo animal;
    public:
        Mascota() { }
        Mascota(string n, int e, tipo tip=perro) { nom = n; edad=e; animal=tip;}
        string getNom() { return nom;}
        int  getEdad() { return edad;}
        tipo getTipo() { return animal;}
        void imprimir(){ cout<<nom<<"\t"<<edad<<"\t"<<Tipo[animal]<<endl; }
};

int main()
{

    Mascota v[]= { {"Sultan", 6, perro}, {"Mota", 3, gato}, {"Copito", 2, conejo}};
    Mascota buf;
    fstream arc;
    arc.open("mascota.dat",ios::binary | ios::out);
    arc.write((char *)v,sizeof(v));
    arc.close();
    
    arc.open("mascota.dat",ios::binary | ios::in);
    while (1)
    {
        arc.read((char *)&buf,sizeof(buf));
        if (arc.eof()) break;
        buf.imprimir();
        
    }
    arc.close();
    cout << "Fue creado el archivo mascota.dat\n" << endl;
    return 0;
}