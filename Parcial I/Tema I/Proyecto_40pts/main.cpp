#include <iostream>
#include <time.h>
#include <string>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

// First, we build an object for each of the table ofs the DB, as an extract table for the workers
//No incluimos la edicion de facturas ni compras, porque es un negocio de verdad eso seria catalogado como fraude fiscal
//Por lo que decidimos centrarnos en las maneras en que funcionaria un sistema en la vida real.


// Integrantes
// 29907856 Jordano Pernia
// 29929240 Oriana Moreno
// 31180603 Ariani Valera

//Recomendaciones:
//* Para facilitar la busqueda de datos al momento de entrar al sistema y hacer un resgitro o midificacion
// revisar la seccion del codigo desde las lineas 687 a la 720

fstream work, prov, prod, client, receipt, purc, arc;
class Worker{
	private:
	    int id;
	    char name[60];
	    char rol[10];
	    char password[8];

	public:
	    Worker(){};
	    Worker(int aId, string aName, string aRol, string aPassword){
	        id = aId;
	        strcpy(name, aName.c_str());
	        strcpy(rol, aRol.c_str());
	        strcpy(password, aPassword.c_str());
	
	        work.open("worker.dat", ios::binary | ios::app);
	        work.write(reinterpret_cast<char *>(this), sizeof(*this));
	        work.close();
	    };

    bool checkWorkerRol(string aName, string aPassword){
        if (strcmp(aName.c_str(), name) == 0 && strcmp(aPassword.c_str(), password) == 0){
            return true;
        }
        else{
            return false;
        };
    };

    char *getWorkerRol(){
        return rol;
    }

    char *getWorkerName(){
        return name;
    };

    char *getWorkerPassword(){
        return password;
    };

    int getWorkerId(){
        return id;
    };

    void setName(string aName){
        strcpy(name, aName.c_str());
    };

    void setRol(string aRol){
        strcpy(rol, aRol.c_str());
    };

    void setPassword(string aPassword){
        strcpy(password, aPassword.c_str());
    };
};

void editWorker(){
    int idTemp;
    int flag2 = 1;
    string aName, aRol, aPassword;
    bool found = false;

    Worker buf;
    while (flag2 == 1){
        cout << "Ingrese el id del trabajador que desea editar: " << endl;
        cin >> idTemp;

        work.open("worker.dat", ios::in | ios::out | ios::binary);
        while (1){
            work.read((char *)&buf, sizeof(buf));
            if (work.eof())
                break;
            if (buf.getWorkerId() == idTemp){
                cout << "Ingrese el nuevo nombre: " << endl;
                cin >> aName;
                buf.setName(aName);
                cout << "Ingrese la nueva clave: " << endl;
                cin >> aPassword;
                buf.setPassword(aPassword);
                cout << "Ingrese el nuevo rol (admi, warehouse, cashier): " << endl;
                cin >> aRol;
                buf.setRol(aRol);

                work.seekp(work.tellg() - static_cast<std::streamoff>(sizeof(buf)), std::ios_base::beg);
                work.write((char *)&buf, sizeof(buf));

                cout << "\nUn nuevo trabajador ha sido creado." << endl;
                cout << "----------------------------------------------------------------\n" << endl;
                found = true;
                break;
            }
        }
        work.close();
        if (!found){
            cout << "\nTrabajador no encontrado" << endl;
        }

        cout << "\nSi desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir" << endl;
        cin >> flag2;
    };
}

void deleteWorker(){
    int idTemp;
    int flag2 = 1;
    bool found = false;
    Worker buf;
    ifstream f("worker.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    while (flag2 == 1){
        cout << "Ingrese el id del trabajador que desea eliminar: " << endl;
        cin >> idTemp;

        while (f.read((char *)&buf, sizeof(buf))){

            if (buf.getWorkerId() != idTemp){
                temp.write((char *)&buf, sizeof(buf));
                found = true;
            };
        };

        f.close();
        temp.close();

        remove("worker.dat");
        rename("temp.dat", "worker.dat");

        if (found){
            flag2 = 0;
        }
		else{
            cout << "\nTrabajador no encontrado" << endl;
            cout << "\nSi desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir" << endl;
            cin >> flag2;
        }
    };
}

class Provider{
	private:
	    int id;
	    char name[50];
	    char phone[14];

	public:
	    Provider(){};
	    Provider(int aId, string aName, string aPhone)
	    {
	        id = aId;
	        strcpy(name, aName.c_str());
	        strcpy(phone, aPhone.c_str());
	
	        prov.open("provider.dat", ios::binary | ios::app);
	        prov.write(reinterpret_cast<char *>(this), sizeof(*this));
	        prov.close();
	    };
	
	    int getProviderId(){
	        return id;
	    };
	
	    void setProviderName(string aName){
	        strcpy(name, aName.c_str());
	    };
	    void setProviderPhone(string aPhone){
	        strcpy(phone, aPhone.c_str());
	    };
	    char *getProviderName(){
	        return name;
	    };
	    char *getProviderPhone(){
	        return phone;
	    };
	};
	
void editProvider(){
    int idTemp;
    int flag2 = 1;
    string aName, aPhone;
    bool found = false;

    Provider buf;
    while (flag2 == 1){
        cout << "Ingrese el id del proveedor que desea editar: " << endl;
        cin >> idTemp;

        prov.open("provider.dat", ios::in | ios::out | ios::binary);
        while (1){
            prov.read((char *)&buf, sizeof(buf));
            if (prov.eof())
                break;
            if (buf.getProviderId() == idTemp){
                cout << "Ingrese el nuevo nombre: " << endl;
                cin >> aName;
                buf.setProviderName(aName);
                cout << "Ingrese la nueva clave: " << endl;
                cin >> aPhone;
                buf.setProviderPhone(aPhone);

                prov.seekp(work.tellg() - static_cast<std::streamoff>(sizeof(buf)), std::ios_base::beg);
                prov.write((char *)&buf, sizeof(buf));
                found = true;
                break;
            }
        }
        prov.close();

        if (!found){
            cout << "Proveedor no encontrado" << endl;
        };

        cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir" << endl;
        int providerFlag;//////////////////////
        cin >> providerFlag;
        if(providerFlag!=1){
            flag2=0;
            break;
        }
    };
}

void deleteProvider(){
    int idTemp;
    int flag2 = 1;
    bool found = false;
    Provider buf;
    ifstream f("provider.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    
    while (flag2 == 1){
        cout << "Ingrese el id del proveedor que desea eliminar: " << endl;
        cin >> idTemp;

        while (f.read((char *)&buf, sizeof(buf))){
            if (buf.getProviderId() != idTemp){
                temp.write((char *)&buf, sizeof(buf));
                found = true;
            };
        };

        f.close();
        temp.close();

        remove("provider.dat");
        rename("temp.dat", "provider.dat");

        if (found){
            flag2 = 0;
        }
        else{
            cout << "Proveedor no encontrado" << endl;
            cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir" << endl;
            cin >> flag2;
        }
    };
}

class Product : public Provider{
    Provider buf;

	private:
	    int id, price, stock, stock_min, id_provider;
	    char description[30];
	
	public:
	    Product(){};
	    Product(int aId, int aId_provider, int aPrice, int aStock, int aStock_min, string aDescription){
	        id = aId;
	        id_provider = aId_provider;
	        price = aPrice;
	        stock = aStock;
	        stock_min = aStock_min;
	        strcpy(description, aDescription.c_str());
	
	        prod.open("product.dat", ios::binary | ios::app);
	        prod.write(reinterpret_cast<char *>(this), sizeof(*this));
	        prod.close();
	    };

	    int getProductId(){
	        return id;
	    };
	
	    int getProductPrice(){
	        return price;
	    };
	
	    int getProviderId(){
	        return id_provider;
	    };
	
	    int getProductStock(){
	        return stock;
	    };
	
	    int getProductMinStock(){
	        return stock_min;
	    };
	
	    char *getProductDescription(){
	        return description;
	    }
	
	    void setProductPrice(int aPrice){
	        price = aPrice;
	    };
	
	    void setProductStockMin(int aStock_min){
	        stock_min = aStock_min;
	    };
	
	    void setProductDescription(string aDescription){
	        strcpy(description, aDescription.c_str());
	    };
	
	    void setProviderId(int aId_provider){
	        id_provider = aId_provider;
	    }
	
	    void setProductStock(int aStock){
	        stock = aStock;
	    };
	
	    void decreaseProductStock(int aStock){
	        stock = stock - aStock;
	    }
	
	    bool checkStock(int quantity){
	        if (stock > quantity)
	            return true;
	        else
	            return false;
	    };
	
	    bool checkReStock(){
	        if (stock < stock_min)
	            return true;
	        else
	            return false;
	    };
	
	    void reStock(){
	        prov.open("provider.dat", ios::binary | ios::in);
	        while (1){
	            prov.read((char *)&buf, sizeof(buf));
	            if (prov.eof())
	                break;
	            if (buf.getProviderId() == id_provider){
	                string providerName = buf.getProviderName();
	                string providerPhone = buf.getProviderPhone();
	                string desc = description;
	                string requestDocTitle = "restockOrder_" + desc + ".txt";
	                string requestDocContent = "We need to restock the product: " + desc + "\nWe need 100 units of it.\n";
	                string requestDocProviderData = "Send to provider: " + providerName + "\nVia: " + providerPhone + ".";
	                
	                ofstream file(requestDocTitle.c_str());
	                file << requestDocContent;
	                file << requestDocProviderData;
	                file.close();
	            }
	        };
	        prov.close();
	    };
	};



void editProduct(){
    int idTemp, aProviderId, aPrice, aStock, aMinStock;
    string aDescription;
    bool productCheck = false;
    int flag2 = 1;

    Product buf;
    while (flag2 == 1){
        cout << "Ingrese el id del producto que desea editar: " << endl;
        cin >> idTemp;
        prod.open("product.dat", ios::in | ios::out | ios::binary);

        while (1){
            prod.read((char *)&buf, sizeof(buf));
            if (prod.eof())
                break;

            if (buf.getProductId() == idTemp){
                productCheck = true;
                int flag3 = 1;
                while (flag3 == 1){
                    cout << "Ingrese el id del proveedor: " << endl;
                    cin >> aProviderId;
                    // we need to check that the provider exits
                    Provider buff;
                    fstream f;
                    f.open("provider.dat", ios::binary | ios::in);
                    f.seekg(0, ios::beg);
                    while (1){
                        f.read((char *)&buff, sizeof(buff));
                        if (f.eof()){
                            cout << "Proveedor no encontrado: "<< endl;
                            cout << "Ingrese un id valido" << endl;
                            break;
                        }
                        if (buff.getProviderId() == aProviderId){
                            buf.setProviderId(aProviderId);
                            flag3 = 0;
                            break;
                        }
                    }
                    f.close();
                }

                cout << "Ingrese el nuevo precio del producto: " << endl;
                cin >> aPrice;
                buf.setProductPrice(aPrice);
                cout << "Ingrese la cantidad existente del producto:" << endl;
                cin >> aStock;
                buf.setProductStock(aStock);
                cout << "Ingrese la cantidad minima de la existencia del producto:" << endl;
                cin >> aMinStock;
                buf.setProductStockMin(aMinStock);
                cout << "Ingrese la nueva descripcion del producto: " << endl;
                cin >> aDescription;
                buf.setProductDescription(aDescription.c_str());

                prov.seekp(prov.tellg() - static_cast<std::streamoff>(sizeof(buf)), std::ios_base::beg);
                prov.write((char *)&buf, sizeof(buf));

                cout << "\n----------------------------------------------------------------" << endl;
                cout << "\t\t-Nueva informacion del producto-" << endl;
                cout << "----------------------------------------------------------------\n" << endl;
                cout << "Descripcion del producto: " << buf.getProductDescription() << endl;
                cout << "Precio del producto: " << buf.getProductPrice() << endl;
                cout << "Id del proveedor: " << buf.getProviderId() << endl;
                cout << "Existencia del producto: " << buf.getProductStock() << endl;
                cout << "Minima existencia del producto: " << buf.getProductMinStock() << endl;
                break;
            }
            prov.close();
        }
        prod.close();
        if (!productCheck){
            cout << "\nProducto no encontrado" << endl;
        }

        cout << "\nSi desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir" << endl;
        cin >> flag2;
    };
}
void deleteProduct(){
    int idTemp;
    int flag2 = 1;
    bool found = false;
    Product buf;
    ifstream f("product.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (flag2 == 1){
        cout << "\nIngrese el producto que desea eliminar: " << endl;
        cin >> idTemp;

        while (f.read((char *)&buf, sizeof(buf))){
            if (buf.getProductId() != idTemp){
                temp.write((char *)&buf, sizeof(buf));
                found = true;
            };
        };

        f.close();
        temp.close();

        remove("product.dat");
        rename("temp.dat", "product.dat");

        if (found){
            flag2 = 0;
            cout << "\nLa operaci�n fue exitosa." << endl;
        }
        else{
            cout << "\nProducto no encontrado" << endl;
            cout << "\nSi desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir" << endl;
            cin >> flag2;
        }
    };
};

Product productArray[60];
void loadProduct(){
    int i = 0;
    
    Product buf;
    ifstream f("product.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (1){
        prod.read((char *)&buf, sizeof(buf));
        if (prod.eof()){
            break;
        }
        productArray[i] = buf;
        ++i;
    }

    prod.close();
}


class Client{
	private:
	    int id;
	    char name[50], address[50], phone[14];
	
	public:
	    Client(){};
	    Client(int aId, string aName, string aPhone, string anAddress){
	        id = aId;
	        strcpy(name, aName.c_str());
	        strcpy(phone, aPhone.c_str());
	        strcpy(address, anAddress.c_str());
	        client.open("client.dat", ios::binary | ios::app);
	        client.write(reinterpret_cast<char *>(this), sizeof(*this));
	        client.close();
	    };
	
	    int getClientId(){
	        return id;
	    };
	
	    void setClientName(string aName){
	        strcpy(name, aName.c_str());
	    }
	    void setClientPhone(string aPhone){
	        strcpy(phone, aPhone.c_str());
	    }
        void setClientAddress(string anAddress){
            strcpy(address, anAddress.c_str());
        }
	};
	
void editClient(){
    int idTemp;
    int flag2 = 1;
    string aName, aPhone, anAddress;
    bool found = false;

    Client buf;
    while (flag2 == 1){
        cout << "\nIngrese el id del cliente que desea editar: " << endl;
        cin >> idTemp;

        client.open("client.dat", ios::in | ios::out | ios::binary);
        while (1){
            client.read((char *)&buf, sizeof(buf));
            if (client.eof())
                break;
            if (buf.getClientId() == idTemp)
            {
                cout << "Ingrese el nuevo nombre: " << endl;
                cin >> aName;
                buf.setClientName(aName);
                cout << "Ingrese el nuevo numero telefonico: " << endl;
                cin >> aPhone;
                buf.setClientPhone(aPhone);
                cout << "Ingrese la nueva direccion: " << endl;
                cin >> anAddress;
                buf.setClientAddress(anAddress);
                

                client.seekp(client.tellg() - static_cast<std::streamoff>(sizeof(buf)), std::ios_base::beg);
                client.write((char *)&buf, sizeof(buf));
                found = true;
                break;
            }
        }
        client.close();
        if (!found)
        {
            cout << "\nCliente no encontrado" << endl;
        }

        cout << "\nSi desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir" << endl;
        cin >> flag2;
    };
}
void deleteClient(){
    int idTemp;
    int flag2 = 1;
    bool found = false;
    Client buf;
    ifstream f("client.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    
    while (flag2 == 1){
        cout << "\nIngrese el id del cliente que desea eliminar: " << endl;
        cin >> idTemp;

        while (f.read((char *)&buf, sizeof(buf))){
            if (buf.getClientId() != idTemp){
                temp.write((char *)&buf, sizeof(buf));
                found = true;
            };
        };

        f.close();
        temp.close();
        remove("client.dat");
        rename("temp.dat", "client.dat");

        if (found){
            flag2 = 0;
        }
        else{
            cout << "\nCliente no encontrado" << endl;
            cout << "\nSi desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir" << endl;
            cin >> flag2;
        }
        cout<<"\nCliente eliminado exitosamente"<<endl;///////
    };
}

void createClient(int anId){
    string aName, aPhone, anAddress;
    cout << "----------------------------------------------------------------" << endl;
    cout << "\nIngrese el nombre del nuevo cliente: " << endl;
    cin >> aName;
    cout << "Ingrese el numero telefonico del nuevo cliente: " << endl;
    cin >> aPhone;
    cout << "Ingrese la direccion del nuevo cliente: " << endl;
    cin >> anAddress;
    Client(anId, aName, aPhone, anAddress);
    cout << "\nOperacion exitosa, se ha creado un nuevo cliente" << endl;
    cout << "----------------------------------------------------------------" << endl;
}

class Receipt : public Product{
    time_t unparsedDate = time(0);

	private:
	    int id;
	    int id_client;
	    char *date;
	
	public:
	Receipt(){};
	    Receipt(int anId, int aId_client){
	        id = anId;
	        id_client = aId_client;
	        date = asctime(localtime(&unparsedDate));
	
	        receipt.open("receipt.dat", ios::binary | ios::app);
	        receipt.write(reinterpret_cast<char *>(this), sizeof(*this));
	        receipt.close();
	    };
	
	    int getReceiptId(){
	        return id;
	    }
};

class Purchase{
	private:
	    int id;
	    int id_product;
	    int id_receipt;
	    int quantity;
	
	public:
	    Purchase(int anId, int aId_product, int aId_receipt, int aQuantity){
	        id = anId;
	        id_product = aId_product;
	        id_receipt = aId_receipt;
	        quantity = aQuantity;
	
	        purc.open("purchase.dat", ios::binary | ios::app);
	        purc.write(reinterpret_cast<char *>(this), sizeof(*this));
	        purc.close();
	    };
	};

//Originalmente se penso hacer un Id random para asignarle a las compras y la factura, pero dev c++ nos mostro problemas 
//Por usar ek metodo to_string()

// string createRandomId()
// {
//     string r = to_string(rand() % 11);
//     char a = 97 + rand() % 26;
//     char nd = 65 + rand() % 26;
//     string anId = (r + a + nd);
//     return anId;
// }

void loadWorkers(){
    Worker(29907856, "Jordano", "admi", "ryuk");
    Worker(29929240, "Oriana", "warehouse", "butterfly");
    Worker(31180603, "Ariani", "cashier", "aliendot");
};

void loadProviders(){
    Provider(29907856, "Jordano Pernia", "0414-3711282");
    Provider(29929240, "Oriana Moreno", "0414-7347068");
    Provider(31180603, "Ariani Valera", "0426-2705797");
};

void loadProducts(){
    int providersid[3];
    Provider buf;

    arc.open("provider.dat", ios::binary | ios::in);

    int n = 0;
    while (1){
        arc.read((char *)&buf, sizeof(buf));
        if (arc.eof())
            break;
        providersid[n] = buf.getProviderId();
        n++;
    }
    arc.close();

    Product pr[] = {{1, providersid[0], 3900, 80, 20, "Harina de maiz"},
                    {2, providersid[1], 6500, 60, 15, "Harina de trigo"},
                    {3, providersid[2], 4500, 90, 10, "Azucar"},
                    {4, providersid[1], 5500, 70, 5, "Pasta"},
                    {5, providersid[0], 4200, 60, 155, "Arroz"},
                    };
};

void loadClients(){
    Client(29907856, "Jordano Pernia", "0414-3711282", "San Cristobal");
    Client(29929240, "Oriana Moreno", "0414-7347068", "Patiecitos");
    Client(31180603, "Ariani Valera", "0426-2705797", "Tariba");
};

/////////////////////////////////////////////////////////////////////////////////
///                              the prsogram starts here                            /// 
//////////////////////////////////////////////////////////////////////////////////////


int main(){

    work.open("worker.dat", ios::binary | ios::out);
    work.close();
    loadWorkers();

    prov.open("provider.dat", ios::binary | ios::out);
    prov.close();
    loadProviders();

    prod.open("product.dat", ios::binary | ios::out);
    prod.close();
    loadProducts();

    client.open("client.dat", ios::binary | ios::out);
    client.close();
    loadClients();

    receipt.open("receipt.dat", ios::binary | ios::out);
    receipt.close();

    purc.open("purchase.dat", ios::binary | ios::out);
    purc.close();

    string rol, userName;
    bool user = false;

    loadProduct();

	cout << "---------------------------------------------------------------" << endl;
    cout <<"\n--------------BIENVENID@ AL SISTEMA DE LA TIENDA--------------" << endl;
    cout << "Por favor, antes de continuar, ingrese su nombre y su clave" << endl;
    cout << "\n---------------------------------------------------------------" << endl;
    cout << endl << "Puede ingresar como: \n\t1. Jordano (administrador) \n\t2. Oriana (proveedor) \n\t3. Ariani (vendedor)" << endl;
    cout << "Las claves son:\n\t1. ryuk \n\t2. butterfly \n\t3. aliendot" << endl;
    cout << "---------------------------------------------------------------" << endl;
    int flag1 = 1;
    cout << "ru ";

    for (int i = 0; i < 60; ++i) {
        cout <<  productArray[i].getProductDescription() << " ";
    }
 
   

    while (flag1 == 1){
        char name[50], password[12];
        cout << "\nNombre: ";
        cin >> name;
        cout << "Clave: ";
        cin >> password;

        Worker buf;

        work.open("worker.dat", ios::binary | ios::in);
        while (1){
            work.read((char *)&buf, sizeof(buf));
            if (work.eof()){
                cout << "Clave o nombre incorrectos." << endl;
                break;
            }
            if (buf.checkWorkerRol(name, password)){
                rol = buf.getWorkerRol();
                user = true;
                userName = buf.getWorkerName();
                break;
            };
        }
        work.close();

        if (user){
            break;
        }

        cout << "----------------------------------------------------------------" << endl;
        cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir del programa" << endl;
        cin >> flag1;
    }

    int option;

    if (rol == "admi"){
        system("cls");
        cout << "----------------------------------------------------------------" << endl;
        cout << "--------------------- Bienvenido " << userName <<" -----------------------"<<endl;
        while (1){
            cout << "----------------------------------------------------------------" << endl;
            cout << "\nQue desea realizar?" << endl;
            cout << "\n  1. Cambiar la base de datos de los productos" << endl;
            cout << "  2. Cambiar la base de datos de los proveedores" << endl;
            cout << "  3. Cambiar la base de datos de los clientes" << endl;
            cout << "  4. Cambiar la base de datos de los trabajadores" << endl;
            cout << "  5. salir" << endl;
            cout << "\nSeleccione una de las opciones ingresando su numero" << endl;
            cin >> option;

            switch (option){
            case 1:{
                int productFlag = 1;
                while (productFlag == 1){
                    system("cls");
                    cout << "----------------------------------------------------------------" << endl;
                    cout << "\nQue desea realizar?" << endl;
                    cout << "  1. Agregar un nuevo producto" << endl;
                    cout << "  2. Editar un producto" << endl;
                    cout << "  3. Eliminar un producto" << endl;
                    cout << "  4. Salir" << endl;
                    cout << "\nSeleccione una de las opciones ingresando su numero"<< endl;
                    int productOption;
                    cin >> productOption;
                    
                    switch (productOption){
                    case 1:{
                        system("cls");
                        int anId, aProviderId, aPrice, aStock, aMinStock;
                        string aDescription;
                        cout<<"\nEscogio agregar un nuevo producto\n"<<endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        cout << "Ingrese el id del nuevo producto: " << endl;
                        cin >> anId;
                        int flag3 = 1;
                        while (flag3 == 1){
                            cout << "Ingrese el id del proveedor: " << endl;
                            cin >> aProviderId;
                            // we need to check that the provider exits
                            Provider buf;
                            arc.open("provider.dat", ios::binary | ios::in);
                            while (1){
                                arc.read((char *)&buf, sizeof(buf));
                                if (arc.eof()){
                                    cout << "\nProveedor no encontrado" << endl;
                                    cout << "Ingrese un id valido" << endl;
                                    arc.close();
                                    break;
                                }
                                if (buf.getProviderId() == aProviderId){
                                    flag3 = 0;
                                    break;
                                }
                            }
                        }
                        arc.close();
                        cout << "Ingrese el precio del nuevo producto: " << endl;
                        cin >> aPrice;
                        cout << "Ingrese la existencia del nuevo producto: " << endl;
                        cin >> aStock;
                        cout << "Ingrese la existencia minima del nuevo producto: " << endl;
                        cin >> aMinStock;
                        cout << "Ingrese la descripcion del nuevo producto: " << endl;
                        cin >> aDescription;
                        Product(anId, aProviderId, aPrice, aStock, aMinStock, aDescription);
                        cout << "\nOperacion exitosa, se ha creado un nuevo producto." << endl;
                        break;
                    }
                    
                    case 2:{
                        system("cls");
                        cout << "\nEscogio editar un producto\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        editProduct();
                        break;
                    }
                    
                    case 3:{
                        system("cls");
                        cout << "\nEscogio eliminar un producto\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        deleteProduct();
                        break;
                    }
                    
                    default:{
                        productFlag = 0;
                        break;
                    }
                    
                }
                    cout << "\n----------------------------------------------------------------" << endl;
                    cout << "\nDesea realizar otras modificaciones?" << endl;
                    cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir del programa" << endl;
                    int productMenuEnd;
                    cin >> productMenuEnd;
                    if (productMenuEnd != 1){
                        system("cls");
                        productFlag = 0;
                        break;
                    }
                };
                break;
            };
            
            case 2:{
                int providerFlag = 1;
                while (providerFlag == 1){
                    system("cls");
                    cout << "----------------------------------------------------------------" << endl;
                    cout << "\nQue desea realizar?" << endl;
                    cout << "  1. Agregar un nuevo proveedor" << endl;
                    cout << "  2. Editar un proveedor" << endl;
                    cout << "  3. Eliminar un proveedor" << endl;
                    cout << "  4. Salir" << endl;
                    cout << "\nSeleccione una de las opciones ingresando su numero" << endl;

                    int providerOption;
                    cin >> providerOption;
                    switch (providerOption){
                    case 1:{
                        int anId;
                        string aName, aPhone;
                        system("cls");
                        cout<<"\nEscogio agregar nuevo proveedor.\n"<<endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        cout << "Ingrese el id del nuevo proveedor: " << endl;
                        cin >> anId;
                        cout << "Ingrese el nombre del nuevo proveedor: " << endl;
                        cin >> aName;
                        cout << "Ingrese el numero telefonico del nuevo proveedor: " << endl;
                        cin >> aPhone;
                        Provider(anId, aName, aPhone);
                        cout << "\nOperacion exitosa, se ha creado un nuevo proveedor." << endl;
                        break;
                    }
                    
                    case 2:{
                        system("cls");
                        cout << "\nEscogio editar el proveedor.\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        editProvider();
                        break;
                    }
                    
                    case 3:{
                        system("cls");
                        cout << "\nEscogio eliminar producto.\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        deleteProduct();
                        break;
                    }
                    
                    default:{
                        providerFlag = 0;
                        break;
                    }
                }
                    cout << "\nDesea realizar otras modificaciones?" << endl;
                    cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir" << endl;
                    int providerMenuEnd;
                    cin >> providerMenuEnd;
                    if (providerMenuEnd != 1){
                        providerFlag = 0;
                        system("cls");
                    }
                };
                break;
            }
            
            case 3:{
                int clientFlag = 1;
                while (clientFlag == 1){
                    system("cls");
                    cout << "----------------------------------------------------------------" << endl;
                    cout << "\nQue desea realizar?" << endl;
                    cout << "  1. Agregar un cliente nuevo" << endl;
                    cout << "  2. Editar un cliente" << endl;
                    cout << "  3. Borrar un cliente" << endl;
                    cout << "  4. Salir" << endl;
                    cout << "\nSeleccione una de las opciones ingresando su numero" << endl;

                    int clientOption;
                    cin >> clientOption;
                    switch (clientOption){
                    case 1:{
                        int anId;
                        system("cls");
                        cout<<"\nEscogio agregar nuevo cliente.\n"<<endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        cout << "Ingrese el id del nuevo cliente: " << endl;
                        cin >> anId;
                        createClient(anId);
                        break;
                    }
                    
                    case 2:{
                        system("cls");
                        cout << "\nEscogio editar un cliente.\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        editClient();
                        break;
                    }
                    
                    case 3:{
                        system("cls");
                        cout << "\nEscogio eliminar un cliente.\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        deleteClient();
                        break;
                    }
                    
                    default:{
                        clientFlag = 0;
                        break;
                    }              
                }
                    cout << "----------------------------------------------------------------\n" << endl;
                    cout << "\nDesea realizar otras modificaciones?" << endl;
                    cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir del programa." << endl;
                    int clientMenuEnd;
                    cin >> clientMenuEnd;
                    if (clientMenuEnd != 1){
                        clientFlag = 0;
                        system("cls");
                    }
                };
                break;
            }
            
			case 4:{
                int workerFlag = 1;
                while (workerFlag == 1){
                    system("cls");
                    cout << "----------------------------------------------------------------" << endl;
                    cout << "\nQue desea realizar?" << endl;
                    cout << "  1. Agregar un nuevo trabajador" << endl;
                    cout << "  2. Editar un trabajador" << endl;
                    cout << "  3. Eliminar un trabajador" << endl;
                    cout << "  4. Salir" << endl;
                    cout << "\nSeleccione una de las opciones ingresando su numero" << endl;
                    int workerOption;
                    cin >> workerOption;
                    switch (workerOption){
                    case 1:{
                        int anId;
                        string aName, aRol, aPassword;
                        system("cls");
                        cout << "\nEscogio agregar un nuevo trabajador.\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        cout << "\nIngrese el id del trabajador: " << endl;
                        cin >> anId;
                        cout << "Ingrese el nombre del trabajador: " << endl;
                        cin >> aName;
                        cout << "Ingrese el rol del trabajador (admi, warehouse, cashier): " << endl;
                        cin >> aRol;
                        cout << "Ingrese la clave del trabajador: " << endl;
                        cin >> aPassword;
                        Worker(anId, aName, aRol, aPassword);

                        cout << "\nOperacion exitosa, se ha creado un nuevo trabajador." << endl;
                        break;
                    };
                    
                    case 2:{
                        system("cls");
                        cout << "\nEscogio editar un trabajador.\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        editWorker();
                        break;
                    }
                    
                    case 3:{
                        system("cls");
                        cout << "\nEscogio eliminar un trabajador.\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        deleteWorker();
                        cout << "\nOperacion exitosa, ha eliminado a un trabajador." << endl;
                        cout<<"----------------------------------------------------------------\n" << endl;
                        break;
                    };
                    
                    default:{
                        workerFlag = 0;
                        break;
                    }
                }
                    cout << "\nDesea realizar otras modificaciones?" << endl;
                    cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir." << endl;
                    int workerMenuEnd;
                    cin >> workerMenuEnd;
                    if (workerMenuEnd != 1){
                        workerFlag = 0;
                        system("cls");
                    }
                };
                break;
            }
            
            case 5:{
                system("cls");
                cout << "\n----------------------------------------------------------------" << endl;
                cout << "\t\tGracias por usar el programa!" << endl;
                cout << "----------------------------------------------------------------" << endl;
                return 0;
            }
            
            default:{
                cout << "\nIngrese una opcion valida" << endl;
                break;
            }
        	}
    	}
    }
    else if (rol == "warehouse"){
        int warehouseFlag = 1;
        while (warehouseFlag == 1){
            system("cls");
            cout << "----------------------------------------------------------------" << endl;
            cout << "--------------------- Bienvenido " << userName <<" ------------------------"<<endl;
            cout << "----------------------------------------------------------------" << endl;
            cout << "\nQue desea realizar?" << endl;
            cout << "\n  1. Agregar un nuevo producto" << endl;
            cout << "  2. Editar un producto" << endl;
            cout << "  3. Salir" << endl;
            cout << "\nSeleccione una de las opciones ingresando su numero" << endl;

            int productOption;
            cin >> productOption;
            switch (productOption){
            case 1:{
                int anId, aProviderId, aPrice, aStock, aMinStock;
                string aDescription;
                system("cls");
                cout<<"\nEscogio agregar un nuevo producto"<<endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                cout << "Ingrese el id del producto: " << endl;
                cin >> anId;
                int flag3 = 1;
                while (flag3 == 1){
                    cout << "Ingrese el id del proveedor: " << endl;
                    cin >> aProviderId;
                    // we need to check that the provider exits
                    Provider buf;
                    arc.open("provider.dat", ios::binary | ios::in);
                    while (1){
                        arc.read((char *)&buf, sizeof(buf));
                        if (arc.eof()){
                            cout << "\nProveedor no encontrado" << endl;
                            cout << "Ingrese un id valido" << endl;
                            arc.close();
                            break;
                        }
                        if (buf.getProviderId() == aProviderId){
                            flag3 = 0;
                            break;
                        }
                    }
                }
                
                arc.close();
                cout <<"Ingrese el precio del nuevo producto: " << endl;
                cin >> aPrice;
                cout << "Ingrese la existencia del producto: " << endl;
                cin >> aStock;
                cout << "Ingrese la existencia minima del producto: " << endl;
                cin >> aMinStock;
                cout << "Ingrese la descripcion del nuevo producto: " << endl;
                cin >> aDescription;
                Product(anId, aProviderId, aPrice, aStock, aMinStock, aDescription);
                cout << "\nOperacion exitosa, se ha creado un nuevo producto." << endl;
                break;
            }
            
            case 2:{
                system("cls");
                cout << "\nEscogio editar un producto\n" << endl;
                cout << "----------------------------------------------------------------\n" << endl;
                editProduct();
                break;
            }
            
            default:{
                break;
            }
            }
            cout << "\n----------------------------------------------------------------" << endl;
            cout << "\nDesea realizar otras modificaciones?" << endl;
            cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir del programa." << endl;
            int productMenuEnd;
            cin >> productMenuEnd;
            if (productMenuEnd != 1){
                system("cls");
                warehouseFlag = 0;
                break;
            };
        };
    }
    else if (rol == "cashier"){
        system("cls");
        cout << "----------------------------------------------------------------" << endl;
        cout << "--------------------- Bienvenido " << userName <<" ------------------------"<<endl;

        int cashierFlag = 1;
        while (cashierFlag == 1){
            
            int cashierOption;
	    cout << "----------------------------------------------------------------" << endl;
            cout << "\nLa caja registradora esta abierta" << endl;
            cout << "\n1. Realizar una venta" << endl;
            cout << "2. Salir" << endl;
            cout << "\nSeleccione una de las opciones ingresando su numero" << endl;
            cin >> cashierOption;

            Client buf;
            switch (cashierOption){
            case 1:{
                int clientId;
                bool clientCheck;
                int anId = rand();

                system("cls");
                cout << "----------------------------------------------------------------" << endl;
                cout << "Ingrese el id del cliente: " << endl;
                cin >> clientId;
                client.open("client.dat", ios::binary | ios::in);
                client.seekg(0, ios::beg);
                while (1){
                    client.read((char *)&buf, sizeof(buf));
                    if (client.eof()){
                        cout << "\nEl cliente no fue encontrado en la base de datos. Proceda con el registro." << endl;
                        clientCheck = false;
                        break;
                    }
                    if (buf.getClientId() == clientId){
                        clientCheck = true;
                        break;
                    }
                }
                client.close();
                if(!clientCheck){
                    createClient(clientId);
                }
                Receipt(anId, clientId);

                int quantity, productId, productQuantity;
                cout << "\nCuantos productos compro el cliente?" << endl;
                cin >> quantity;

                for (int i = 0; i < quantity; i++){
                    bool productFound = false;
                    while (!productFound){
                        Product buffe;
                        cout << "\nIngrese el id del producto "<<i+1<<": " << endl;
                        cin >> productId;
                        prod.open("product.dat", ios::in | ios::out | ios::binary);
                        prod.seekg(0, ios::beg);
                        while (1){
                            prod.read((char *)&buffe, sizeof(buffe));
                            if (prod.eof()){
                                cout << "\nProducto no encontrado" << endl;
                                cout << "Ingrese un id valido" << endl;
                                break;
                            }
                            if (buffe.getProductId() == productId){
                                while (1){
                                    cout << "\nIngrese la cantidad de productos: " << endl;
                                    cin >> productQuantity;
                                    if (buffe.checkStock(productQuantity)){
                                        buffe.decreaseProductStock(productQuantity);
                                        prod.seekp(prod.tellg() - static_cast<std::streamoff>(sizeof(buffe)), std::ios_base::beg);
                                        prod.write((char *)&buffe, sizeof(buffe));
                                        int purchaseId = rand()*10;
                                        Purchase(purchaseId, productId, anId, productQuantity);

                                        system("cls");
                                        cout << "\n----------------------------------------------------------------" << endl;
                                        cout << "---------------------- PRODUCTOS VENDIDOS ----------------------" << endl;
                                        cout << "\n Cantidad"<<"\t\tDescripcion" <<"\t\t  Monto total\n"<< endl;
                                        cout << " "<<productQuantity << " \t\t\t" << buffe.getProductDescription()<< "\t\t  "<<buffe.getProductPrice()*productQuantity <<" .Cop."<< endl;
                                        cout << "\n----------------------------------------------------------------" << endl;
                                        break;
                                    }
                                    else{
                                        cout << "\nNo tenemos suficiente existencia de este producto" << endl;
                                        cout << "Por favor, ingrese una cantidad valida" << endl;
                                        cout << "" << endl;
                                    }
                                }
                                productFound = true;
                                break;
                            }
                        }
                        prod.close();
                    };
                }
               
                break;
            };
            
            default:{
                cashierFlag = 0;
                break;
            };
            };
        
           
        };
        Product buffer;
            prod.open("product.dat", ios::binary | ios::in);
            while(1){
                prod.read((char *)&buffer, sizeof(buffer));
                if(prod.eof()){
                    cout << "\n----------------------------------------------------------------" << endl;
                    cout << "\t\t  Gracias por su trabajo!" << endl;
                    cout << "----------------------------------------------------------------" << endl;
                    break;
                }
                if(buffer.checkReStock()){
                    buffer.reStock();
                }
            }
    }

    return 0;
}
