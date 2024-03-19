#include <iostream>
#include <time.h>
#include <string.h>
#include <string>
#include <fstream>


using namespace std;

// First, we build an object for each of the table of the DB, as an extract table for the workers

fstream arc;

class Worker
{
 
    private:
        int id;
        char name[60];
        char rol[10];
        char password[8];

    public:
      Worker()  { }
      Worker(int aId, char *aName, char *aRol, char *aPassword) {
            id = aId;
            strcpy(name,aName);
            strcpy(rol,aRol);
            strcpy(password,aPassword);

          arc.open("worker.dat",ios::binary | ios::app);
          arc.write(reinterpret_cast<char *>(this),sizeof(*this));
          arc.close();
        };

      char *getWorkerRol(char* aName, char* aPassword){
        if(strcmp(aName, name) == 0 && strcmp(aPassword, password) == 0){
          return rol;
        }
        else{
          return "0";
        };
      };
};
class Provider
{
    private:
        int id;
        char name[50];
        char phone[14];
    public:
        Provider(){ };
        Provider(int aId, char* aName, char* aPhone) {
            id = aId;
            strcpy(name, aName);
            strcpy(phone, aPhone);

            arc.open("provider.dat",ios::binary | ios::app);
            arc.write(reinterpret_cast<char *>(this),sizeof(*this));
            arc.close();
        };

        int getProviderId(){
          return id;
        };
        void setProviderName(char* aName){
           strcpy(name, aName);
        };
        void setProviderPhone(char* aPhone){
          strcpy(phone, aPhone);
        };
        char* getProviderName(){
          return name;
        };
        char* getProviderPhone(){
          return phone;
};
};
class Product : public Provider
{
  Provider buf;
    private:
        int id, price, stock, stock_min, id_provider;
        char description[30];

    public:
        Product() {};
        Product(int aId, int aId_provider, int aPrice, int aStock, int aStock_min, char* aDescription) {
            id = aId;
            id_provider = aId_provider;
            price = aPrice;
            stock = aStock;
            stock_min = aStock_min;
            strcpy(description, aDescription);

            arc.open("product.dat",ios::binary | ios::app);
            arc.write(reinterpret_cast<char *>(this),sizeof(*this));
            arc.close();
        };

        int getProductId(){
          return id;
        };

        int getProductPrice(){
          return price;
        };

        void setProductPrice(int aPrice){
          price = aPrice;
        };
        
        int setProductStockMin(int aStock_min){
          stock_min = aStock_min;
        };

        void setProductDescription(char* aDescription){
          strcpy(description, aDescription);
        };

        void setProductStock(int aStock){
          stock -= aStock;
        };

        bool checkStock(int quantity){
          if(stock > quantity) return true;
          else return false;   
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
            if (buf.getProviderId() == id_provider){
              char* providerName = buf.getProviderName();
              char* providerPhone = buf.getProviderPhone();

              string requestDocTitle ="restockOrder_" + to_string(id) + ".dat";
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
        char name[50], address[50], phone[14];
    public:
        Client(){ };
        Client(int aId, char* aName, char* aPhone) {
            id = aId;
            strcmp(name, aName);
            strcmp(phone, aPhone);

            arc.open("client.dat",ios::binary | ios::app);
            arc.write(reinterpret_cast<char *>(this),sizeof(*this));
            arc.close();
        };

        int getClientId(){
          return id;
        };
        void setClientName(char* aName){
          strcmp(name, aName);
        };
        void setClientPhone(char* aPhone){
          strcmp(phone, aPhone);
        };
        char* getClientName(){
          return name;
        };
        char* getClientPhone(){
          return phone;
        };
};
class Receipt: public Product
{

  time_t unparsedDate = time(0);
    private:
        int id;
        int id_client;
        char* date;
    public:
        Receipt(int aId, int aId_client) {
            id = aId;
            id_client = aId_client;
            date = asctime(localtime(&unparsedDate));
            

            arc.open("receipt.dat",ios::binary | ios::app);
            arc.write(reinterpret_cast<char *>(this),sizeof(*this));
            arc.close();
        };

       
};
class Purchase : public Product
{

Product buf;

    private:
        int id;
        int id_product;
        int id_client;
        int quantity;
    public:
        Purchase(int aId, int aId_product, int aId_Client, int aQuantity) {

            arc.open("product.dat",ios::binary | ios::in);
            
            while(1)
            {
              arc.read((char *)&buf,sizeof(buf));
              if (arc.eof()) break;
              if (buf.getProductId() == aId_product){
                if(buf.checkStock(quantity)){

                      id = aId;
                      id_product = buf.getProductId(); 
                      id_client = aId_Client;
                      quantity = aQuantity;

                    arc.open("purchase.dat",ios::binary | ios::app);
                      arc.write(reinterpret_cast<char *>(this),sizeof(*this));
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
  Worker w[] = {{29907856,"Jordano" , "admi", "ryuk"},
                {1,"Oriana", "warehouse", ""},
                {2,"Ariani", "cashier", ""}};
  arc.open("worker.dat",ios::binary | ios::app);
  arc.write((char *)w,sizeof(w));
  arc.close();
};

void loadProviders(){
  Provider p[] = {{29907856,"Jordano Pernia", "0414-3711282"},
                  {1,"Oriana Moreno", "0414-7347068"},
                  {2,"Ariani Valera", "0426-2705797"}};
  arc.open("provider.dat",ios::binary | ios::app);
  arc.write((char *)p,sizeof(p));
  arc.close();
};

void loadProducts(){

  int providersid[3];
  Provider buf;
  

    arc.open("provider.dat", ios::binary | ios::in );

    int n = 0;
    while (1)
    {
      arc.read((char *)&buf,sizeof(buf));
      if (arc.eof()) break;
      providersid[n] = buf.getProviderId();
      n++;
    }
    arc.close();
    
    Product pr[] = {{1, providersid[0], 3900, 80, 20, "Corn Flour"}, 
                    {2, providersid[1], 6500, 60, 15, "White Flour"}, 
                    {3, providersid[2], 4500, 90, 10, "Sugar"}, 
                    {4, providersid[1], 5500, 70, 5, "Pasta"}, 
                    {5, providersid[0], 4200, 60, 155, "Rice"}, 
                    {6, providersid[1], 6800, 50, 10, "Beans"}};

    arc.open("product.dat",ios::binary | ios::app);
    arc.write((char *)pr,sizeof(pr));
    arc.close();
   

  };

void loadClients(){
  Client c[] = {{29907856,"Jordano Pernia", "0414-3711282"},
                {1,"Oriana Moreno", "0414-7347068"},
                {2,"Ariani Valera", "0426-2705797"}};
  arc.open("client.dat",ios::binary | ios::app);
  arc.write((char *)c,sizeof(c));
  arc.close();

};

int main(){

  arc.open("worker.dat",ios::binary | ios::out);
  arc.close();

  arc.open("provider.dat",ios::binary | ios::out);
  arc.close();

  arc.open("product.dat",ios::binary | ios::out);
  arc.close();

  arc.open("client.dat",ios::binary | ios::out);
  arc.close();

  loadWorkers();
  loadProviders();
  loadProducts();
  loadClients();

  string rol = "0";

  cout << "Welcome to the store's system" << endl;
  cout << "Please, before continuing, enter your name and password" << endl;
  cout << "----------------------------------------------------------------" << endl;
  int flag1 = 1;

  while(flag1 == 1){

    char name[50], password[12];
    cout << "Name: ";
    cin >> name;
    cout << "Password: ";
    cin >> password;

    Worker buf;
    
    arc.open("worker.dat", ios::binary | ios::in );
    while (1)
    {
      arc.read((char *)&buf,sizeof(buf));
      if (arc.eof()) { 
        cout << "Password or name incorrect." << endl;
        break;
        }
      rol = buf.getWorkerRol(name, password);
      if(rol != "0"){
      cout << "Welcome " << rol << endl;
      break;
    }
    }
    arc.close();

    if(rol != "0")break;

    cout << "----------------------------------------------------------------" << endl;
    cout << "Enter 1 to try again, or any other key to end the program" << endl;
    cin >> flag1;

  }

  if(rol == "admi"){
    
  }


  return 0;
}