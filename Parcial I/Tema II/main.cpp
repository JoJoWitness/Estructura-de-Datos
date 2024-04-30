#include <iostream>
#include <time.h>
#include <string>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <vector>

using namespace std;

// First, we build an object for each of the table ofs the DB, as an extract table for the workers
//No incluimos la edicion de facturas ni compras, porque es un negocio de verdad eso seria catalogado como fraude fiscal
//Por lo que decidimos centrarnos en las maneras en que funcionaria un sistema en la vida real.


// Integrantes
// 29907856 Jordano Pernia
// 29929240 Oriana Moreno
// 31180603 Ariani Valera
//

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

        cout << "\nSi desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro n�mero para salir" << endl;
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
            cout << "\nSi desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro n�mero para salir" << endl;
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

        cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro n�mero para salir" << endl;
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
            cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro n�mero para salir" << endl;
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

        void getAllInfo(){
            if(id < 10){
                cout << "id: " << id << "    " <<"Producto: " << description << endl;   
            }
            else{
                cout << "id: " << id << "   " <<"Producto: " << description << endl;  
            }
            
        }

        void getCompleteInfo(){
            cout << "id: " << id << "   " << "Descripcion: " << description << "   " << "Precio: " << price << "   " << "Proveedor: " << id_provider << "   " << "Existencia: " << stock << "   " << "Minima existencia: " << stock_min << endl;
        
        }
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

        cout << "\nSi desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro n�mero para salir" << endl;
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
            cout << "\nSi desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro n�mero para salir" << endl;
            cin >> flag2;
        }
    };
};

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
	
        char* getClientName(){
            return name;
        }

        char *getClientPhone(){
            return phone;
        }
        char *getClientAddress(){
            return address;
        }

        void setClientId(int anId){
            id = anId;
        }

	    void setClientName(string aName){
	        strcpy(name, aName.c_str());
	    }
	    void setClientPhone(string aPhone){
	        strcpy(phone, aPhone.c_str());
	    }
        void setClientAddress(string anAddress){
            strcpy(address, anAddress.c_str());
        }

        
        void getClientInfo(){ 
            if(id < 10){
            cout << "id: " << id << "         " << "Nombre: " << name << endl;
            }
            else if(id <10000000 && id >= 10){
            cout << "id: " << id << "        " << "Nombre: " << name << endl;
            }
            else{
            cout << "id: " << id << "  " << "Nombre: " << name << endl;   
            };
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

        cout << "\nSi desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro n�mero para salir" << endl;
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
            cout << "\nSi desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro n�mero para salir" << endl;
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

void loadWorkers(){
    Worker(29907856, "Jordano", "admi", "ryuk");
    Worker(29929240, "Oriana", "warehouse", "butterfly");
    Worker(31180603, "Ariani", "cashier", "aliendot");
    Worker(31180603, "Ryuk", "organizer", "bestdog");
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
                    {6, providersid[1], 6800, 50, 10, "Caraotas"},
                    {7, providersid[2], 2000, 30, 10 , "Galletas"},
                    {8, providersid[0], 3000, 70, 10, "Frijoles"},
                    {9, providersid[1], 1000, 50, 10, "Gelatina"},
                    {10, providersid[2], 2000, 30, 10 , "Arvejas Verdes"},
                    {11, providersid[0], 3000, 70, 10, "Arvejas Amarillas"},
                    {12, providersid[1], 6500, 60, 15, "Cafe"},
                    {13, providersid[2], 4500, 90, 10, "Te"},
                    {14, providersid[1], 5500, 70, 5, "Desodorante"},
                    {15, providersid[0], 4200, 60, 155, "Crema de dental"},
                    {16, providersid[1], 6800, 50, 10, "Papel Higienico"},
                    {17, providersid[2], 2000, 30, 10 , "Colitas"},
                    {18, providersid[0], 3000, 70, 10, "Chupetas"},
                    {19, providersid[1], 1000, 50, 10, "Caramelos de cafe"},
                    {20, providersid[2], 2000, 30, 10 , "Caramelos de mantequilla"},
                    {21, providersid[0], 3000, 70, 10, "Carne de Res"},
                    {22, providersid[1], 6500, 60, 15, "Pollo"},
                    {23, providersid[2], 4500, 90, 10, "Carne de Cochino"},
                    {24, providersid[1], 5500, 70, 5, "Levadura"},
                    {25, providersid[0], 4200, 60, 155, "Polvo de Hornear"},
                    {26, providersid[1], 6800, 50, 10, "Chocolate"},
                    {27, providersid[2], 2000, 30, 10 , "Chocolate de reposteria"},
                    {28, providersid[0], 3000, 70, 10, "Baterias AAA"},
                    {29, providersid[1], 1000, 50, 10, "Baterias AA"},
                    {30, providersid[2], 2000, 30, 10 , "Baterias 9V"},
                    {31, providersid[0], 3000, 70, 10, "Gomitas"},
                    {32, providersid[1], 6500, 60, 15, "Masmelos"},
                    {33, providersid[2], 4500, 90, 10, "Jamon"},
                    {34, providersid[1], 5500, 70, 5, "Queso"},
                    {35, providersid[0], 4200, 60, 155, "Tocineta"},
                    {36, providersid[1], 6800, 50, 10, "Alcaparras"},
                    {37, providersid[2], 2000, 30, 10 , "Papel Aluminio"},
                    {38, providersid[0], 3000, 70, 10, "Aceitunas"},
                    {39, providersid[1], 1000, 50, 10, "Onoto"},
                    {40, providersid[2], 2000, 30, 10 , "Pasas"},
                    {41, providersid[0], 3000, 70, 10, "Garbanzos"},
                    {42, providersid[1], 6500, 60, 15, "Oregano"},
                    {43, providersid[2], 4500, 90, 10, "Albahaca"},
                    {44, providersid[1], 5500, 70, 5, "Comino"},
                    {45, providersid[0], 4200, 60, 155, "Curry"},
                    {46, providersid[1], 6800, 50, 10, "Laurel"},
                    {47, providersid[2], 2000, 30, 10 , "Paprika"},
                    {48, providersid[0], 3000, 70, 10, "Pimienta"},
                    {49, providersid[1], 1000, 50, 10, "Romero"},
                    {50, providersid[2], 2000, 30, 10 , "Menta"},
                    {51, providersid[0], 3000, 70, 10, "Hierbabuena"},
                    {52, providersid[1], 6500, 60, 15, "Limonaria"},
                    {53, providersid[2], 4500, 90, 10, "Manzanilla"},
                    {54, providersid[1], 5500, 70, 5, "Lavanda"},
                    {55, providersid[0], 4200, 60, 155, "Pico de loro"},
                    {56, providersid[1], 6800, 50, 10, "Frijol Chino"},
                    {57, providersid[2], 2000, 30, 10 , "Lapices"},
                    {58, providersid[0], 3000, 70, 10, "Cuadernos"},
                    {59, providersid[1], 1000, 50, 10, "Marcadores"},
                    {60, providersid[2], 2000, 30, 10 , "Malta"},
                    };
};


void loadClients(){
    // Client(29907856, "Jordano Pernia", "0414-3711282", "San Cristobal");
    // Client(29929240, "Oriana Moreno", "0414-7347068", "Patiecitos");
    // Client(31180603, "Ariani Valera", "0426-2705797", "Tariba");
    Client(1, "Jordano Pernia", "0414-3711282", "San Cristobal");
    Client(2, "Oriana Moreno", "0414-7347068", "Patiecitos");
    Client(3, "Ariani Valera", "0426-2705797", "Tariba");
    Client(4, "Luz D'Santiago", "0414-1234567", "La Popita");
    Client(5, "Javier Pernia", "0414-1234567", "La Normal");
    Client(6, "Carmen de Pernia", "0414-1234567", "La Normal");
    Client(7, "Octaviano Pernia", "0414-1234567", "La Normal");
    Client(8, "Ryuk", "0414-1234567", "La normal");
    Client(9, "Orianna Villamizar", "0414-1234567", "La Concordia");
    Client(10, "Raymond Bravo", "0414-1234567", "Pueblo Nuevo");
    Client(11, "Francisco Vargas", "0414-1234567", "Pueblo Nuevo");
    Client(12, "Jhaisam Ferreira", "0414-1234567", "Los Agustinos");
    Client(13, "Hillary Alvarado", "0414-1234567", "La Concordia");
    Client(14, "Aisskel Duarte", "0414-1234567", "Rubio");
    Client(15, "Osmar Porras", "0414-1234567", "Santa Teresa");
    Client(16, "Gabriel Galan", "0414-1234567", "Los Naranjos");
    Client(17, "Tyler Joseph", "0414-1234567", "La Fria");
    Client(18, "Campana Pelusa", "0414-1234567", "La Popita");
    Client(19, "Pablo Vivas", "0414-1234567", "España");
    Client(20, "Alicia Apolinar", "0414-1234567", "La Normal");
    Client(21, "Andrea Barrios", "0414-1234567", "Pueblo Nuevo");
    Client(22, "Arturo Tascon", "0414-1234567", "Cordero");
    Client(23, "Rafael Bastidas", "0414-1234567", "Avenida Libertador");
    Client(24, "Gerardo Squillaro", "0414-1234567", "Pirineos");
    Client(25, "Augusto Montoya", "0414-1234567", "La Popita");
    Client(26, "Dickson", "0414-1234567", "Rubio");
    Client(27, "Juan Pulido", "0414-1234567", "Guasdulito");
    Client(28, "Antonio Gomez", "0414-1234567", "Paris");
    Client(29, "Javier Parra", "0414-1234567", "Paris");
    Client(30, "Xander Azuaje", "0414-1234567", "Madrid");
    Client(31, "Camila Uribe", "0414-1234567", "Utah");
    Client(32, "Liz Ramirez", "0414-1234567", "Idaho");
    Client(33, "Valentina Cornago", "0414-1234567", "Merida");
    Client(34, "Marisabel Urbina", "0414-1234567", "La Rotaria");
    Client(35, "Sebastian Mora", "0414-1234567", "Las Acacias");
    Client(36, "Mariangel Guerraro", "0414-1234567", "Tariba");
    Client(37, "Victor Maldonado", "0414-1234567", "Barrio Sucre");
    Client(38, "Joseph Colmenares", "0414-1234567", "La Concordia");
    Client(39, "Ana Sandoval", "0414-1234567", "La Normal");
    Client(40, "Sofia Bonilla", "0414-1234567", "New York");
    Client(41, "Mariana Duque", "0414-1234567", "Avenida Libertador");
    Client(42, "Miguel Ramirez", "0414-1234567", "Tariba");
    Client(43, "Francisco Adrianza", "0414-1234567", "La Normal");
    Client(44, "Franklin Ortiz", "0414-1234567", "Las Acacias");
    Client(45, "Arturo Diaz", "0414-1234567", "California");
    Client(46, "Maria Perez", "0414-1234567", "Los Naranjos");
    Client(47, "Luisa Cardenas", "0414-1234567", "Cueva del Oso");
    Client(48, "Maria Baptista", "0414-1234567", "La Popita");
    Client(49, "Cesar Mora", "0414-1234567", "El Junquito");
    Client(50, "Camila Escalante", "0414-1234567", "Barrio Obrero");
    Client(51, "Kenie Escalante", "0414-1234567", "La Normal");
    Client(52, "Gabriel Aguilar", "0414-1234567", "Cordero");
    Client(53, "Elizabeth Manzilla", "0414-1234567", "Aeropuesto");
    Client(54, "Launnie Des Dianteaux", "0414-1234567", "Avaloir");
    Client(55, "Elaine Fritz", "0414-1234567", "Londres");
    Client(56, "Jacob Rose", "0414-1234567", "Londres");
    Client(57, "Marcel Leroy", "0414-1234567", "Paris");
    Client(58, "Cirico Matamorros", "0414-1234567", "Madrid");
    Client(59, "Altagracia de la Torre", "0414-1234567", "Leon");
    Client(60, "Zellie Dubois", "0414-1234567", "Provenza");
    
};

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
///                              Nuevas funciones                                  /// 
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

Product productArray[60];
void loadProductToArray(){
    int i = 0;
    
    Product buf;
    ifstream prod("product.dat", ios::binary);

    while (1){
        prod.read((char *)&buf, sizeof(buf));
        if (prod.eof()){
            break;
        }
        productArray[i] = buf;
        ++i;
    }

    prod.clear();
    prod.close();
};

Client clientArray[60];
void loadClientToArray(){
    int i = 0;
    
    Client buf;
    ifstream client("client.dat", ios::binary);

    while (1){
        client.read((char *)&buf, sizeof(buf));
        if (client.eof()){
            break;
        }
        clientArray[i] = buf;
        ++i;
    }

    client.close();

}

void quicksort(Product arr[], int low, int high){ //Recibe un objeto de Products, ojo
        int middle, i, j;
        middle = (low+high)/2;

        //pivote en valor central
        string pivot = arr[middle].getProductDescription();
        //separar segmentos
        i = low;
        j = high;

        while(i<=j){
            //separando en dos partes el array
            while(arr[i].getProductDescription()<pivot) i++; //separo valores menores del pivote
            while(arr[j].getProductDescription()>pivot) j--; //separo valores mayores del pivote
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

int getFileSize() {
        ifstream file("client.dat", ios::binary);
        file.seekg(0, ios::end);
        int size = file.tellg();
        file.seekg(0, ios::beg);
        file.close();
        return size / sizeof(Client);
    }

void splitFile(int groupSize){
    Client client;
    int group1, group2;
    int size = getFileSize() - 1;

    ifstream fi("client.dat", ios::binary);
    ofstream aux1("aux1.dat", ios::binary);
    ofstream aux2("aux2.dat", ios::binary);

    if(fi.fail() || aux1.fail() || aux2.fail()){
        cout<<"Error al abrir el archivo"<<endl;
        return;
    }

    int i = 0;
    while (i < size){
        group1 = 0;
        group2 = 0;

        while(group1 < groupSize && fi.read((char*)&client,sizeof(client))){
            aux1.write((char*)&client, sizeof(client));
            group1++;
            i++;
        }

        while(group2 < groupSize && fi.read((char*)&client,sizeof(client))){
            aux2.write((char*)&client, sizeof(client));
            group2++;
            i++;
        }
    }

    
    /*int i = 0, division = 1;
    while(fi.read((char*)&client, sizeof(client))){
        if(division == 1){
            aux1.write((char*)&client, sizeof(client));
        }else{
            aux2.write((char*)&client, sizeof(client));
        }

        i++;

        if(i == groupSize){
            division *= -1;
            i = 0;
        }

    }*/

    fi.close();
    aux1.close();
    aux2.close();   
}

void fusionFileDirect(int groupSize){
    Client client1, client2;
    int numGroups;
    int position1 = 0, position2 = 0, size1 = 0, size2 = 0;

    ofstream fi("client.dat", ios::binary);
    ifstream aux1("aux1.dat", ios::binary);
    ifstream aux2("aux2.dat", ios::binary);

    while(aux1.read((char*)&client1, sizeof(client1))){
        size1++;
    }

    while(aux2.read((char*)&client1, sizeof(client1))){
        size2++;
    }

    aux1.close();
    aux2.close();

    if(size1 % groupSize == 0){
        numGroups = size1 / groupSize;
    } else {
        numGroups = size2 /  groupSize;
    }

    aux1.open("aux1.dat", ios::binary);
	aux2.open("aux2.dat", ios::binary);
	
	aux1.read((char *)&client1,sizeof(client1));
	aux2.read((char *)&client2,sizeof(client2));

    for(int i=0; i<numGroups; i++){
        while(position1 < (groupSize + groupSize*i) || position2 < (groupSize + groupSize*i)){
            while(position1 == (groupSize + groupSize*i) && position2 < (groupSize + groupSize*i)){
                fi.write((char*)&client2, sizeof(client2));
                if(!aux2.read((char*)&client2, sizeof(client2))){
                    position2 = (groupSize + groupSize*i) - 1;
                }
                position2++;
            }

            while(position2 == (groupSize + groupSize*i) && position1 < (groupSize + groupSize*i)){
                    fi.write((char *)&client1,sizeof(client1));
                    if(!aux1.read((char*)&client1, sizeof(client1))){
                    position1 = (groupSize + groupSize*i) - 1;
                }
                position1++;
            }

            if((position1 < (groupSize + groupSize*i) && position2 < (groupSize + groupSize*i)) && (strcmp(client1.getClientName(), client2.getClientName()) <= 0 )){
                fi.write((char*)&client1, sizeof(client1));
                if(!aux1.read((char*)&client1, sizeof(client1))){
                    if(size1 < size2){
                        position1 = (groupSize +  groupSize*i) -1;
                    }
                }
                position1++;
            } else if((position1<(groupSize +  groupSize*i) && position2<(groupSize + groupSize*i)) && (strcmp(client1.getClientName(), client2.getClientName())>0)){
                fi.write((char*)&client2, sizeof(client2));
                if(!aux2.read((char*)&client2, sizeof(client2))){
                    if(size2 < size1){
                        position2 = (groupSize +  groupSize*i) -1;
                    }
                }
                position2++;
        
            }    
        }   
    }

    if(size1 % groupSize!=0 && size1 > size2){
        do{
            fi.write((char*)&client1, sizeof(client1));
        }while(aux1.read((char*)&client1,sizeof(client1)));
    }

    if(size2 % groupSize!=0 && size2 > size1){
        do{
            fi.write((char*)&client2, sizeof(client2));
        }while(aux2.read((char*)&client2,sizeof(client2)));
    }

    fi.close();
    aux1.close();
    aux2.close();
	
}

void directMergeSort(){
    Client client;
    int groupSize = 1;
    while(groupSize < getFileSize() - 1){
        splitFile(groupSize);
        fusionFileDirect(groupSize);
        groupSize = groupSize * 2;
    }
}

void fusionFileNatural(vector<int>& size1, vector<int>& size2){
    Client client1, client2;
    int numGroups = 0, position1 = 0, position2 = 0;

    ofstream fi("client.dat", ios::binary);
    ifstream aux1("aux1.dat", ios::binary);
    ifstream aux2("aux2.dat", ios::binary);

    if(size1.size() > size2.size()){
        numGroups = size2.size();
    } else {
        numGroups = size1.size();
    }

    aux1.read((char*)&client1, sizeof(client1));
    aux2.read((char*)&client1, sizeof(client2));

    for(int i = 0; i < numGroups; i++){
        position1 = 0;
        position2 = 0;

        while(position1 < size1[i] || position2 < size2[i]){
            while(position1 == size1[i] && position2 < size2[i]){
                fi.write((char*)&client2, sizeof(client2));
                if(!aux2.read((char*)&client2, sizeof(client2))){
                    position2 = size2[i]-1;
                }
                position2++;
            }
            while(position2 == size2[i] && position1 < size1[i]){
                fi.write((char*)&client1, sizeof(client1));
                if(!aux2.read((char*)&client1, sizeof(client1))){
                    position1 = size1[i]-1;
                }
                position1++;
            }

            if((position1 < size1[i] && position2 < size2[i]) && (strcmp(client1.getClientName(), client2.getClientName()) <= 0)){
                fi.write((char*)&client1, sizeof(client1));
                if(!aux1.read((char*)&client1, sizeof(client1))){
                    position1 = size1[i]-1;
                }

                position1++;

            } else if ((position1 < size1[i] && position2 < size2[i]) && (strcmp(client1.getClientName(), client2.getClientName()) > 0)){
                fi.write((char*)&client2, sizeof(client2));
                if(!aux2.read((char*)&client2, sizeof(client2))){
                    position2 = size2[i]-1;
                }
                position2++;
            }
        }
    }

    if(size1.size() > size2.size()){
        do{
            fi.write((char*)&client1, sizeof(client1));
        }while(aux1.read((char*)&client1, sizeof(client1)));
    }

    if(size2.size() > size1.size()){
        do{
            fi.write((char*)&client2, sizeof(client2));
        }while(aux2.read((char*)&client2, sizeof(client2)));
    }

    fi.close();
    aux1.close();
    aux2.close();
}

void naturalMergeSort(){
    Client client1, client2;
    int group1 = 0, group2 = 0, x = 0, n1 = 0, n2 = 0;
    int size = getFileSize() - 1;
    bool isWritten = false;
    vector<int> size1;
    vector<int> size2;
    
    do{
        ifstream fi("client.dat", ios::binary);
        ofstream aux1("aux1.dat", ios::binary);
        ofstream aux2("aux2.dat", ios::binary);

        if(fi.fail() || aux1.fail() || aux2.fail()){
            cout<<"Error al abrir el archivo"<<endl;
            return;
        }
        
        int i = 0;
        while(i < size){
            if(i == 0){
                fi.read((char*)&client1, sizeof(client1));
                aux1.write((char*)&client1,sizeof(client1));
                i++;
                n1++;
            } else {
                aux1.write((char*)&client1,sizeof(client1));
                i++;
                n1++;
            }

            isWritten = false;
            
            while(fi.read((char*)&client2, sizeof(client2)) && strcmp(client1.getClientName(), client2.getClientName()) <= 0){
                aux1.write((char*)&client2, sizeof(client2));
                i++;
                n1++;
                client1 = client2;
                isWritten = true;
            }

            group1++;
            size1.push_back(n1);
            n1 = 0;

            if(i < size){
                if(isWritten){
                    aux2.write((char*)&client2, sizeof(client2));
                    client1 = client2;
                    i++;
                    n2++;
                } else {
                    client1 = client2;
                    aux2.write((char*)&client1, sizeof(client1));
                }

                while(fi.read((char*)&client2, sizeof(client2)) && strcmp(client1.getClientName(), client2.getClientName()) <= 0){
                    aux2.write((char*)&client2, sizeof(client2));
                    i++;
                    n2++;
                    client1 = client2;
                }

                client1 = client2;
                size2.push_back(n2);
                group2++;
                n2 = 0;
            }
        }

        fi.close();
        aux1.close();
        aux2.close();

        fusionFileNatural(size1, size2);
        x = size1[0];
        size1.resize(0);
        size2.resize(0);

    }while(x < getFileSize()-1);
}

int binarySearch(Product arr[],string product) { 
    int n = 60;
    int l = 0; 
    int r = n - 1; 
    char charProduct[50];
    strcpy(charProduct, product.c_str());
  
    while (l <= r) { 
  
        int mid = l + (r - l) / 2; 
  
        int res = -10; 
  
        if (strcmp(charProduct, arr[mid].getProductDescription()) == 0){
            return mid;
        } 
        else if (strcmp(charProduct, arr[mid].getProductDescription()) > 0){
            l = mid + 1;
        }
        else{
            r = mid - 1;
        } 
    }
  
    return -1; 
} 

void printClients(){
    Client client;
    ifstream fi;
    fi.open("client.dat", ios::binary | ios::in);
    while(fi.read((char*)&client, sizeof(client))){
        cout<<"ID: "<<client.getClientId()<<" Nombre: "<<client.getClientName()<<endl;
    }
    
    fi.close();
}


///////////////////////////////////////////////////////////////////////////////////////
///                              the program starts here                            /// 
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
    
	cout << "---------------------------------------------------------------" << endl;
    cout <<"\n--------------BIENVENID@ AL SISTEMA DE LA TIENDA--------------" << endl;
    cout << "Por favor, antes de continuar, ingrese su nombre y su clave" << endl;
    cout << "\n---------------------------------------------------------------" << endl;
    cout << endl << "Puede ingresar como: \n\t1. Jordano (administrador) \n\t2. Oriana (proveedor) \n\t3. Ariani (vendedor) \n\t4. Ryuk (Organizador)" << endl;
    cout << "Las claves son:\n\t1. ryuk \n\t2. butterfly \n\t3. aliendot \n\t4. bestdog" << endl;
    cout << "---------------------------------------------------------------" << endl;
    int flag1 = 1;

    //cout << strcmp("Ariani", "Jordano"); 

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
        cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro n�mero para salir" << endl;
        cin >> flag1;
    }

    int option;

    if (rol == "admi"){
        system("cls");
        system("clear");//////////////////////////////////////////////////////////////////
        cout << "----------------------------------------------------------------" << endl;
        cout << "--------------------- Bienvenido " << userName <<" -----------------------"<<endl;
        while (1){
            cout << "----------------------------------------------------------------" << endl;
            cout << "\nQue desea realizar?" << endl;
            cout << "\n  1. Cambiar la base de datos de los productos" << endl;
            cout << "  2. Cambiar la base de datos de los proveedores" << endl;
            cout << "  3. Cambiar la base de datos de los clientes" << endl;
            cout << "  4. Cambiar la base de datos de los trabajadores" << endl;
            cout << "  5. Salir" << endl;
            cout << "\nSeleccione una de las opciones ingresando su numero" << endl;
            cin >> option;

            switch (option){
            case 1:{
                int productFlag = 1;
                while (productFlag == 1){
                    system("cls");
                    system("clear");//////////////////////////////////////////////////////////////////
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
                        system("clear");//////////////////////////////////////////////////////////////////
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
                        system("clear");//////////////////////////////////////////////////////////////////
                        cout << "\nEscogio editar un producto\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        editProduct();
                        break;
                    }
                    
                    case 3:{
                        system("cls");
                        system("clear");//////////////////////////////////////////////////////////////////
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
                    cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir" << endl;
                    int productMenuEnd;
                    cin >> productMenuEnd;
                    if (productMenuEnd != 1){
                        system("cls");
                        system("clear");//////////////////////////////////////////////////////////////////
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
                    system("clear");//////////////////////////////////////////////////////////////////
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
                        system("clear");//////////////////////////////////////////////////////////////////
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
                        system("clear");//////////////////////////////////////////////////////////////////
                        cout << "\nEscogio editar el proveedor.\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        editProvider();
                        break;
                    }
                    
                    case 3:{
                        system("cls");
                        system("clear");//////////////////////////////////////////////////////////////////
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
                        system("clear");//////////////////////////////////////////////////////////////////
                    }
                };
                break;
            }
            
            case 3:{
                int clientFlag = 1;
                while (clientFlag == 1){
                    system("cls");
                    system("clear");//////////////////////////////////////////////////////////////////
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
                        system("clear");//////////////////////////////////////////////////////////////////
                        cout<<"\nEscogio agregar nuevo cliente.\n"<<endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        cout << "Ingrese el id del nuevo cliente: " << endl;
                        cin >> anId;
                        createClient(anId);
                        break;
                    }
                    
                    case 2:{
                        system("cls");
                        system("clear");//////////////////////////////////////////////////////////////////
                        cout << "\nEscogio editar un cliente.\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        editClient();
                        break;
                    }
                    
                    case 3:{
                        system("cls");
                        system("clear");//////////////////////////////////////////////////////////////////
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
                    cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro n�mero para salir." << endl;
                    int clientMenuEnd;
                    cin >> clientMenuEnd;
                    if (clientMenuEnd != 1){
                        clientFlag = 0;
                        system("cls");
                        system("clear");//////////////////////////////////////////////////////////////////
                    }
                };
                break;
            }
            
			case 4:{
                int workerFlag = 1;
                while (workerFlag == 1){
                    system("cls");
                    system("clear");//////////////////////////////////////////////////////////////////
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
                        system("clear");//////////////////////////////////////////////////////////////////
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
                        system("clear");//////////////////////////////////////////////////////////////////
                        cout << "\nEscogio editar un trabajador.\n" << endl;
                        cout << "----------------------------------------------------------------\n" << endl;
                        editWorker();
                        break;
                    }
                    
                    case 3:{
                        system("cls");
                        system("clear");//////////////////////////////////////////////////////////////////
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
                    cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro n�mero para salir." << endl;
                    int workerMenuEnd;
                    cin >> workerMenuEnd;
                    if (workerMenuEnd != 1){
                        workerFlag = 0;
                        system("cls");
                        system("clear");//////
                    }
                };
                break;
            }
            
            case 5:{
                system("cls");
                system("clear");//////////////////////////////////////////////////////////////////
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
            system("clear");
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
                system("clear");////
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
                system("clear");
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
            cout << "Si desea continuar con el proceso, presione 1 \nDe lo contrario, presione cualquier otro numero para salir del programa" << endl;
            int productMenuEnd;
            cin >> productMenuEnd;
            if (productMenuEnd != 1){
                system("cls");
                system("clear");
                warehouseFlag = 0;
                break;
            };
        };
    }
    else if (rol == "cashier"){
        system("cls");
        system("clear");///////
        cout << "----------------------------------------------------------------" << endl;
        cout << "--------------------- Bienvenido " << userName <<" ------------------------"<<endl;
        cout << "----------------------------------------------------------------" << endl;
        cout << "\nLa caja registradora esta abierta" << endl;

        int cashierFlag = 1;
        while (cashierFlag == 1){
            
            int cashierOption;
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
                system("clear");///////
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
                        cout << "\nIngrese el id del producto: " << endl;
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

                                        cout << "----------------------------------------" << endl;
                                        cout << productQuantity << " " << buffe.getProductDescription() << endl;
                                        cout << "----------------------------------------" << endl;
                                       

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
    else if (rol == "organizer"){

            int organizerFlag=1;
            system("cls");
            system("clear");
            cout << "----------------------------------------------------------------" << endl;
            cout << "--------------------- Bienvenido " << userName <<" -------------------------"<<endl;
            cout << "----------------------------------------------------------------" << endl;
            while(organizerFlag == 1){

            
            cout << "\nQue desea realizar?" << endl;
            cout << "\n  1. Ordenar el array de productos" << endl;
            cout << "  2. Ordenar el array de clientes - mezcla directa" << endl;
            cout << "  3. Ordenar el array de clientes - mezcla natural" << endl;
            cout << "  4. Buscar un producto" << endl;
            cout << "  5. Salir" << endl;
            cout << "\nSeleccione una de las opciones ingresando su numero" << endl;
            cin >> option;

            loadProductToArray();
            loadClientToArray();
          
            switch (option){
            case 1:{
                
                system("cls");
                system("clear");////
                int n = sizeof(productArray) / sizeof(productArray[0]);
                cout<<"\nEscogio ordenar los productos"<<endl;
                cout << "----------------------------------------------------------------\n" << endl;
                cout<< "" << endl;
                cout << "Arreglo desordenado: " << endl;
                 for (int i = 0; i < n; i++){
                    productArray[i].getAllInfo();
                }

                cout<< "" << endl;

                clock_t startClock;
                clock_t stopClock;

                startClock = clock();
                quicksort(productArray, 0, 59);
                stopClock = clock();
                cout << "----------------------------------------------------------------\n" << endl;
                cout << "Arreglo ordenado: " << endl;

                for (int i = 0; i < n; i++){
                    productArray[i].getAllInfo();
                }

                double duration = double(stopClock - startClock) / CLOCKS_PER_SEC * 1000;
                cout << "----------------------------------------------------------------"<< endl;
                cout<<"\tTiempo fue de: "<<duration<<" milisegundos"<<endl;
                cout << "----------------------------------------------------------------\n"<< endl;
               
                break;
            }
            
            case 2:{

                system("cls");
                system("clear");

                cout << "\nEscogio ordenar los clientes por mezcla directa" << endl;
                cout << "----------------------------------------------------------------\n"<< endl;
                cout<<"" <<endl;
                cout<<"Archivo de clientes desordenado: "<<endl;
                printClients();//////////////
                cout<<"\n\n"<<endl;
                
                clock_t startClock;
                clock_t stopClock;
                int n = getFileSize();
                startClock = clock();
                   
                directMergeSort();
                cout << "----------------------------------------------------------------\n"<< endl;
                cout << "Arreglo ordenado: "<<endl;
                ifstream clientSorted("client.dat", ios::binary);
                clientSorted.seekg(0, ios_base::beg);
                Client buf;
                int i =0;
                while(clientSorted.read((char *)&buf, sizeof(buf))){
                    buf.getClientInfo();
                };

                clientSorted.close();//
                
                stopClock = clock();double duration = double(stopClock - startClock) / CLOCKS_PER_SEC * 1000;
                cout << "----------------------------------------------------------------"<< endl;
                cout<<"\tTiempo fue de: "<<duration<<" milisegundos"<<endl;
                cout << "----------------------------------------------------------------\n"<< endl;

                
                cout<<"\nSi desea ver el funcionamiento del otro tipo de mezcla, por favor, cierre el sistema y vuelva a ejecutarlo." <<endl;
                break;
                
            }

            case 3:{
                
                system("cls");
                system("clear");
                cout<<"\nEscogio ordenar los clientes por mezcla natural\n" << endl;
                cout << "----------------------------------------------------------------\n"<< endl;

                cout<<"Archivo de clientes desordenado: "<<endl;
                printClients();//////////////
                cout<<"\n\n"<<endl;

                clock_t startClock;
                clock_t stopClock;
                int n = getFileSize();
                startClock = clock();
                
                
                cout << "----------------------------------------------------------------\n"<< endl;
                cout << "Arreglo ordenado: "<<endl;
                naturalMergeSort();
                ifstream clientSorted("client.dat", ios::binary);
                clientSorted.seekg(0, ios_base::beg);
                Client buf;
                int i =0;
                while(clientSorted.read((char *)&buf, sizeof(buf))){
                    buf.getClientInfo();
                };

                clientSorted.close();
                stopClock = clock();double duration = double(stopClock - startClock) / CLOCKS_PER_SEC * 1000;
                cout << "----------------------------------------------------------------"<< endl;
                cout<<"\tTiempo fue de: "<<duration<<" milisegundos"<<endl;
                cout << "----------------------------------------------------------------\n"<< endl;

                cout<<"\nSi desea ver el funcionamiento del otro tipo de mezcla, por favor, cierre el sistema y vuelva a ejecutarlo." << endl;
                break;

            }

            case 4:{
               
                system("cls");
                system("clear");
                cout << "\nEscogio buscar un producto\n" << endl;
                cout << "----------------------------------------------------------------\n" << endl;
                int n = sizeof(productArray) / sizeof(productArray[0]);
                quicksort(productArray, 0, n - 1);
                cout << "Ingrese el nombre del producto que desea buscar: " << endl;
                string searchFor;
                cin.ignore();
                getline(cin, searchFor);

                int result = binarySearch(productArray, searchFor);
                if (result == -1){
                    cout << "Producto no encontrado" << endl;
                }
                else{
                    cout << "El producto se encontraba en el indice: " << result << endl;
                    productArray[result].getCompleteInfo();
                }
                break;
            }
            case 5:{
                system("cls");
                system("clear");//////////////////////////////////////////////////////////////////
                cout << "\n----------------------------------------------------------------" << endl;
                cout << "\t\tGracias por usar el programa!" << endl;
                cout << "----------------------------------------------------------------" << endl;
                return 0;
            }
            
            default:{
                cout << "\nIngrese una opcion valida" << endl;
                break;
            }
            };
            
            cout << "\n----------------------------------------------------------------" << endl;
            cout << "\nDesea seguir con el proceso?" << endl;
            cout << "Si desea continuar con el proceso, presione 1. Si desea terminar el proceso, presione cualquier numero." << endl;
            int closeWhile;
            cin >> closeWhile;
            if(closeWhile != 1){
                organizerFlag = 0;
            };

            system("cls");
            system("clear");

        };
    }
    
    return 0;
}
