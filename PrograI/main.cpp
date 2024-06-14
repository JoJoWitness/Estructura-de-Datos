#include <iostream>

using namespace std;

class Gandola{
  public:
  string matricula;
  string tipo_de_mercancia;
  string origen;
  int precio;
  int peso;


  virtual void get_datos() = 0;

 string get_matricula() {
        return matricula;
    }

    string get_tipo_de_mercancia() {
        return tipo_de_mercancia;
    }

    string get_origen() {
        return origen;
    }

    int get_precio() {
        return precio;
    }

    int get_peso() {
        return peso;
    }

    void set_matricula(string nuevo_matricula) {
        matricula = nuevo_matricula;
    }

    void set_tipo_de_mercancia(string nuevo_tipo_de_mercancia) {
        tipo_de_mercancia = nuevo_tipo_de_mercancia;
    }

    void set_origen(string nuevo_origen) {
        origen = nuevo_origen;
    }

    void set_precio(int nuevo_precio) {
        precio = nuevo_precio;
    }

    void set_peso(int nuevo_peso) {
        peso = nuevo_peso;
    }
};

class GandolaColombiana: public Gandola{
  public:
    string poliza;
    string direccion;

   GandolaColombiana(string nueva_matricula, string nueva_mercancia, 
                      string nuevo_origen, int nuevo_precio, 
                      int nuevo_peso, string nueva_poliza, string nueva_direccion){
      
      matricula = nueva_matricula;
      tipo_de_mercancia = nueva_mercancia;
      origen = nuevo_origen;
      precio = nuevo_precio;
      peso = nuevo_peso;
      poliza = nueva_poliza;
      direccion = nueva_direccion;
   }

     string get_poliza() {
        return poliza;
    }

    string get_direccion() {
        return direccion;
    }

    void set_poliza(string nueva_poliza) {
        poliza = nueva_poliza;
    }

    void set_direccion(string nueva_direccion) {
        direccion = nueva_direccion;
    }

    void get_datos();
};

void GandolaColombiana::get_datos(){
  cout << matricula << "     " << peso << "     " << tipo_de_mercancia << "     " << poliza << endl;
}

class GandolaVenezolana: public Gandola{
  public:
    string responsable;

    GandolaVenezolana(string nueva_matricula, string nueva_mercancia, string nuevo_origen, int nuevo_precio, int nuevo_peso, string nuevo_responsable){
      
      matricula = nueva_matricula;
      tipo_de_mercancia = nueva_mercancia;
      origen = nuevo_origen;
      precio = nuevo_precio;
      peso = nuevo_peso;
      responsable= nuevo_responsable;
   }

    string get_responsable() {
        return responsable;
    }

    void set_responsble(string nuevo_responsable) {
        responsable = nuevo_responsable;
    }


    void get_datos();
};

void GandolaVenezolana::get_datos(){
  cout << matricula << "     " << peso << "     " << tipo_de_mercancia << "     " << responsable << endl;
}

void cargarDatos(Gandola* vectorDeGandolas, int cantidad_de_gandolas){
	int i;
	string gandola_origen, gandola_matricula, gandola_mercancia, gandola_poliza, gandola_direccion, gandola_responsable;
  	int gandola_precio, gandola_peso;
  	
 for(i = 0; i < cantidad_de_gandolas ; i++){
    cout << "Gandola " << i << endl;
    while(true){
      cout << "Ingrese la nacionalidad de la gandola: "; 
      cin >> gandola_origen;
      if(gandola_origen == "Colombia" || gandola_origen == "colombia" || gandola_origen == "Venezuela" || gandola_origen == "venezuela"){
        break;
      }else{
        cout << "Ingrese un valor adecuado." << endl;
      }
    }
    while(true){
      cout << "Ingrese el tipo de mercancia: ";
      cin >> gandola_mercancia;
      if(gandola_mercancia == "Alimentos" || gandola_mercancia == "alimentos" || gandola_mercancia == "Metales" || gandola_mercancia == "metales" || gandola_mercancia == "Vehiculos" || gandola_mercancia == "vehiculos"  || gandola_mercancia == "Varios" || gandola_mercancia == "varios"){
        break;
      }
      else{
        cout << "Ingrese un valor adecuado." << endl;
      }
    }
    cout << endl;
    cout << "Ingrese el peso de la gandola: ";
    cin >> gandola_peso;
    cout << endl;
    cout << "Ingrese el precio de la mercancia: ";
    cin >> gandola_precio;

    if(gandola_origen == "Colombia" || gandola_origen == "colombia"){
      cout << "Ingrese numero de poliza: ";
      cin >> gandola_poliza;
      cout << endl;
      cout << "Ingrese la direccion: ";
      cin >> gandola_precio;
      vectorDeGandolas[i] = new GandolaColombiana(gandola_matricula, gandola_matricula, gandola_origen,gandola_precio, gandola_peso, gandola_poliza, gandola_direccion);  
    }
    else{
      cout << "Ingrese nombre del responsable: " ;
      cin >> gandola_responsable;
      vectorDeGandolas[i] = new GandolaVenezolana(gandola_matricula, gandola_matricula, gandola_origen,gandola_precio, gandola_peso, gandola_responsable);  
    }
    }
}

void mostrar_datos_segun_origen(string origen, Gandola* vectorDeGandolas, int cantidad_de_gandolas){
  int i, peso, precio;
  string mercancia;
  if(origen == "Colombia" || origen == "colombia"){
    cout << "Matricula" << "     " << "Peso (toneladas)" << "     " << "Tipo De Mercancia" << "     " << "#Poliza" << endl;
    
  }
  else{ 
    cout << "Matricula" << "     " << "Peso (toneladas)" << "     " << "Tipo De Mercancia" << "     " << "Responsable" << endl;
  }

  for(i =0; i<cantidad_de_gandolas; i++ ){
      if(vectorDeGandolas[i]->get_origen() == origen){
        vectorDeGandolas[i]->get_datos();
      }
    }
}

void cantidad_total_de_mercancia_por_tipos( Gandola* vectorDeGandolas, int cantidad_de_gandolas){
  int i, indice_de_mayor_mercancia, mayor_precio_temporal;
  int precio_de_la_mercancia[8];
  
  for(i = 0; i < cantidad_de_gandolas; i++){

    if(vectorDeGandolas[i]->get_origen() == "Colombia")
      if (vectorDeGandolas[i]->get_tipo_de_mercancia() == "Alimentos") {
          precio_de_la_mercancia[0] += vectorDeGandolas[i]->peso;
      } else if (vectorDeGandolas[i]->get_tipo_de_mercancia()== "Metales") {
          precio_de_la_mercancia[1] += vectorDeGandolas[i]->peso;
      } else if (vectorDeGandolas[i]->get_tipo_de_mercancia() == "Vehiculos") {
          precio_de_la_mercancia[2] += vectorDeGandolas[i]->peso;
      } else{
          precio_de_la_mercancia[3] += vectorDeGandolas[i]->peso;
      } 
    else{
      if (vectorDeGandolas[i]->get_tipo_de_mercancia() == "Alimentos") {
          precio_de_la_mercancia[4] += vectorDeGandolas[i]->precio;
      } else if (vectorDeGandolas[i]->get_tipo_de_mercancia()== "Metales") {
          precio_de_la_mercancia[5] += vectorDeGandolas[i]->precio;
      } else if (vectorDeGandolas[i]->get_tipo_de_mercancia() == "Vehiculos") {
          precio_de_la_mercancia[6] += vectorDeGandolas[i]->precio;
      } else{
          precio_de_la_mercancia[7] += vectorDeGandolas[i]->precio;
      } 
    }
  }

    for(i=0; i < cantidad_de_gandolas; i++){
      if(precio_de_la_mercancia[i] > mayor_precio_temporal){
        mayor_precio_temporal = precio_de_la_mercancia[i];
        indice_de_mayor_mercancia = i;
      }
    }

    cout << "La mayor mercancia fue: ";
    
    if(indice_de_mayor_mercancia == 0 || indice_de_mayor_mercancia == 4){
      cout << "Alimentos" << endl;
    }
    else if(indice_de_mayor_mercancia == 1 || indice_de_mayor_mercancia == 5){
      cout << "Metales" << endl;
    }
    else if(indice_de_mayor_mercancia == 2 || indice_de_mayor_mercancia == 6){
      cout << "Vehiculos" << endl;
    }
    else{
      cout << "Varios" << endl;
    }

  if(indice_de_mayor_mercancia < 4){
    cout << "Es de origen: " << cout << "Colombiano"<< endl;
    cout << "Se dirige a: " << cout << "Venezuela" << endl;
  }else{
    cout << "Es de origen: " << cout << "Venezolano"<< endl;
    cout << "Se dirige a: " << cout << "Colombia" << endl;
  }
    
    
}

int main(){

  int cantidad_de_gandolas, i, bandera = 1;
  string gandola_origen, gandola_matricula, gandola_mercancia, gandola_poliza, gandola_direccion, gandola_responsable;
  int gandola_precio, gandola_peso;
  bool gandola_encontrada;

  cout << "Bienvenido al sistema de aduanas de San Antonio" << endl;
  cout << "Antes de hacer uso del sistema, porfavor, lea las instrucciones:" <<endl;
  cout << endl;
  cout << endl;
  cout << endl;
  cout << "Instrucciones:" << endl;
  cout << "1- Para ingresar la nacionalidad de las gandolas, ingrese las palabras 'Colombia' o 'Venezuela'." << endl;
  cout << "2- Solo se aceptan 4 tipos de mercancia: Aliemento, Metales, Vehiculos y Varios. " << endl;
  cout << "3- No use ninguna otra variacion para el ingreso de estos datos, de ser asi, el programa no lo dejara avanzar hasta que ingrese bien los datos" << endl;
  cout << "4- El peso se pide en toneladas." << endl;
  cout << "5- El precio en bolivares debe se pide en millones, se asume los 6 ceros."<< endl;
  cout << endl;
  cout << endl;
  cout << endl;
  cout << "Por favor, ingreso la cantidad de gandolas que pasaron por la aduana: ";
  cin >> cantidad_de_gandolas;

  Gandola* vectorDeGandolas[cantidad_de_gandolas];

  cargarDatos(vectorDeGandolas, cantidad_de_gandolas);

  cout << endl;
  mostrar_datos_segun_origen("Colombia", vectorDeGandolas, cantidad_de_gandolas);
  mostrar_datos_segun_origen("Venezuela", vectorDeGandolas, cantidad_de_gandolas);
  cantidad_total_de_mercancia_por_tipos(vectorDeGandolas, cantidad_de_gandolas);
  cout << endl;

    cout << "A continuacion podra revisar los datos de una gandola que desee";
    while(bandera != 0){
        cout << "Ingrese la matricula a buscar: ";
        cin >> gandola_precio;

       for(i = 0; i < cantidad_de_gandolas ; i++){
          if(gandola_matricula == vectorDeGandolas[i]->get_matricula()){
            vectorDeGandolas[i]->get_datos()
            gandola_encontrada = true;
            break;
          }
       }
       if(!gandola_encontrada){
         cout << "No fue posible encontrar la gandola. " << endl;
       }

       cout << "Ingrese cualquier numero diferente de 0 si desea continuar buscando gandolas";
       cin >> bandera;


    }
return 0;
}

