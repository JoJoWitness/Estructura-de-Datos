#include <iostream>
#include <time.h>
#include <fstream>


using namespace std;

// First, we build an object for each of the table of the DB, as an extract table for the workers

fstream arc;

class Worker
{
 
    private:
        int id;
        string name;
        string rol;
        string password;

    public:
      Worker()  { }
      Worker(int aId, string aName, string aRol, string aPassword) {
            id = aId;
            name = aName;
            rol = aRol;
            password = aPassword;

          arc.open("worker.dat",ios::binary | ios::app);
          arc.write((char *)this,sizeof(*this));
          arc.close();
        };

      string getWorkerRol(string aName, string aPassword){
        if(aName == name && aPassword == password)
        return rol;
        else return "Password or name incorrect";
      };
      
     
};
class Provider
{
    private:
        int id;
        string name, phone;
    public:
        Provider(){ };
        Provider(int aId, string aName, string aPhone) {
            id = aId;
            name = aName;
            phone = aPhone;

            arc.open("provider.dat",ios::binary | ios::app);
            arc.write((char *)this,sizeof(*this));
            arc.close();
        };

        int getProviderId(){
          return id;
        };
        void setProviderName(string aName){
          name = aName;
        };
        void setProviderPhone(string aPhone){
          phone = aPhone;
        };
        string getProviderName(){
          return name;
        };
        string getProviderPhone(){
          return phone;
};
};
class Product : public Provider
{
  Provider buf;
    private:
        int id, price, stock, stock_min;
        string description;
        int* id_provider;

    public:
        Product() {};
        Product(int aId, int* aId_provider, int aPrice, int aStock, int aStock_min, string aDescription) {
            id = aId;
            id_provider = aId_provider;
            price = aPrice;
            stock = aStock;
            stock_min = aStock_min;
            description = aDescription;

            arc.open("product.dat",ios::binary | ios::app);
            arc.write((char *)this,sizeof(*this));
            arc.close();
        };

        int getProductId(){
          return id;
        };

        void setStock(int aStock){
          stock -= aStock;
        };

        bool checkStock(int quantity){
          if(stock > quantity) true;
          else false;   
        };

        void checkReStock(){
          if(stock < stock_min){
            reStock();
          }
        };

        void reStock(){
          arc.open("provider.dat",ios::binary | ios::in);
          while (1)
          {
            arc.read((char *)&buf,sizeof(buf));
            if (arc.eof()) break;
            if (buf.getProviderId() == *id_provider){
              string providerName = buf.getProviderName();
              string providerPhone = buf.getProviderPhone();

              string requestDocTitle = "restockOrder_" + to_string(id) + ".dat";
              string requestDocContent = "We need to restock the product with id: " + to_string(id);


              arc.open(requestDocTitle,ios::binary | ios::out);
              arc.write((char *)&providerName,sizeof(providerName));
              arc.write((char *)&providerPhone,sizeof(providerPhone));

              arc.close();
              
            }
          }
        };
};
class Client
{
    private:
        int id;
        string name, address, phone;
    public:
        Client(){ };
        Client(int aId, string aName, string aPhone) {
            id = aId;
            name = aName;
            phone = aPhone;

            arc.open("client.dat",ios::binary | ios::app);
            arc.write((char *)this,sizeof(*this));
            arc.close();
        };

        int getClientId(){
          return id;
        };
        void setClientName(string aName){
          name = aName;
        };
        void setClientPhone(string aPhone){
          phone = aPhone;
        };
        string getClientName(){
          return name;
        };
        string getClientPhone(){
          return phone;
        };
};
class Receipt: public Product
{

  time_t unparsedDate = time(0);
    private:
        int id;
        int* id_client;
        char* date;
    public:
        Receipt(int aId, int* aId_client) {
            id = aId;
            id_client = aId_client;
            date = asctime(localtime(&unparsedDate));
            

            arc.open("receipt.dat",ios::binary | ios::app);
            arc.write((char *)this,sizeof(*this));
            arc.close();
        };

       
};
class Purchase : public Product
{

Product buf;

    private:
        int id;
        int* id_product;
        int* id_client;
        int quantity;
    public:
        Purchase(int aId, int aId_product, int* aId_Client, int aQuantity) {

            arc.open("product.dat",ios::binary | ios::in);
            
            while(1)
            {
              arc.read((char *)&buf,sizeof(buf));
              if (arc.eof()) break;
              if (buf.getProductId() == aId_product){
                if(buf.checkStock(quantity)){

                      id = aId;
                      *id_product = buf.getProductId(); 
                      id_client = aId_Client;
                      quantity = aQuantity;

                    arc.open("purchase.dat",ios::binary | ios::app);
                      arc.write((char *)this,sizeof(*this));
                      arc.close();
                };
             
              }
              else{
                cout << "We don't have enough stock for this product" << endl;
              };
            };

            arc.close();
        };

        
};

void loadWorkers(){
  Worker jordano(29907856,"Jordano Pernia" , "admi", "ryuk");
  Worker oriana(1,"Oriana Moreno", "warehouse", "");
  Worker ariani(2,"Ariani Valera", "cashier", "");
};

void loadProviders(){
  Provider provider1(29907856,"Jordano Pernia", "0414-3711282");
  Provider provider2(2,"Oriana Moreno", "0414-7347068");
  Provider provider3(3,"Ariani Valera", "0426-2705797");
};

void loadProducts(){

// Este proceso es necesario para obtener la direccion de memoria del id de cada uno 
// de los proveedores sin tener que usar dobles punteros o intermediarios

  Product products[5]; 
  int prices[] = {4000, 6500, 5000, 4500, 3500};
  int stock[] = {80, 50, 60, 55, 40};
  int minStock[] = {20, 10, 15, 10, 5};
  string descriptions[] = {"Corn Flour", "White Flour", "Pasta", "Lentils", "Milk"};
  int n = 0;
  Product buf;
    arc.open("provider.dat", ios::binary | ios::in );

    while (1)
    {
      arc.read((char *)&buf,sizeof(buf));
      if (arc.eof()) break;
      products[n] = Product(n, &buf.getProviderId(), prices[n],stock[n], minStock[n], descriptions[n]);
      n++;
    }
    


  };

int main(){
  loadWorkers();
  loadProviders();
  loadProducts();

  return 0;
}