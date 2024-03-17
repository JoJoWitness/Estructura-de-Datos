#include <iostream>
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
        };
        string getWorkerRol(string aName, string aPassword){
          if(aName == name && aPassword == password)
          return rol;
          else return "Password or name incorrect";
        };
        void loadToWorkerDB(){
        
          arc.open("worker.dat",ios::binary | ios::app);
          arc.write((char *)this,sizeof(*this));
          arc.close();
        };
        void getWorkerName(){
          cout << name << endl;
        };
};

class Provider
{
    private:
        int id;
        string name, phone;
    public:
        Provider(int aId, string aName, string aPhone) {
            id = aId;
            name = aName;
            phone = aPhone;
        };
        int getProviderId(){
          return id;
        };
        string getProviderData(){
          return name, phone;
        };
        
};

class Product
{
    private:
        int id, price, stock, stock_min;
        string description;
        int* id_provider;
    public:
        Product(int aId, int* aId_provider, int aPrice, int aStock, int aStock_min, string aDescription) {
            id = aId;
            id_provider = aId_provider;
            price = aPrice;
            stock = aStock;
            stock_min = aStock_min;
            description = aDescription;
        };
        void setStock(int aStock){
          stock -= aStock;
        };
        bool checkStock(){
          if(stock > stock_min) return false;
          else return true;
        };
        void reStock(int* aId_provider){
           
        };
};

int main(){
  arc.open("worker.dat",ios::binary | ios::out);
  arc.close();

  Worker w1(1, "Juan", "Admin", "1234");
  w1.loadToWorkerDB();
  Worker w2(2, "Pedro", "User", "1234");
  w2.loadToWorkerDB();


  arc.open("worker.dat",ios::binary | ios::in);
  Worker buf;
  int flag = 1;
  while (flag ==1){
  arc.read((char *)&buf,sizeof(buf));
  if(arc.eof()) {flag =0;};
  buf.getWorkerName();
};
  arc.close();
  
  



  return 0;
}