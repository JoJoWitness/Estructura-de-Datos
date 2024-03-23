#include <iostream>
#include <time.h>
#include <string>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

// First, we build an object for each of the table of the DB, as an extract table for the workers
fstream work, prov, prod, client, receipt, purc, arc;
class Worker
{
private:
    int id;
    char name[60];
    char rol[10];
    char password[8];

    char g[2] = "0";

public:
    Worker() = default;
    Worker(int aId, string aName, string aRol, string aPassword)
    {
        id = aId;
        strcpy(name, aName.c_str());
        strcpy(rol, aRol.c_str());
        strcpy(password, aPassword.c_str());

        work.open("worker.dat", ios::binary | ios::app);
        work.write(reinterpret_cast<char *>(this), sizeof(*this));
        work.close();
    };

    bool checkWorkerRol(string aName, string aPassword)
    {
        if (strcmp(aName.c_str(), name) == 0 && strcmp(aPassword.c_str(), password) == 0)
        {
            return true;
        }
        else
        {
            return false;
        };
    };

    char *getWorkerRol()
    {
        return rol;
    }

    char *getWorkerName()
    {
        return name;
    };

    char *getWorkerPassword()
    {
        return password;
    };

    int getWorkerId()
    {
        return id;
    };

    void setName(string aName)
    {
        strcpy(name, aName.c_str());
    };

    void setRol(string aRol)
    {
        strcpy(rol, aRol.c_str());
    };

    void setPassword(string aPassword)
    {
        strcpy(password, aPassword.c_str());
    };
};
void editWorker()
{
    int idTemp;
    int flag2 = 1;
    string aName, aRol, aPassword;
    bool found = false;

    Worker buf;
    while (flag2 == 1)
    {
        cout << "Enter the id of the worker you want to edit: " << endl;
        cin >> idTemp;

        work.open("worker.dat", ios::in | ios::out | ios::binary);
        while (1)
        {
            work.read((char *)&buf, sizeof(buf));
            if (work.eof())
                break;
            if (buf.getWorkerId() == idTemp)
            {
                cout << "Enter the new name: " << endl;
                cin >> aName;
                buf.setName(aName);
                cout << "Enter the new password: " << endl;
                cin >> aPassword;
                buf.setPassword(aPassword);
                cout << "Enter the new rol: " << endl;
                cin >> aRol;
                buf.setRol(aRol);

                work.seekp(work.tellg() - static_cast<std::streamoff>(sizeof(buf)), std::ios_base::beg);
                work.write((char *)&buf, sizeof(buf));

                cout << "A new worker was created" << endl;
                found = true;
                break;
            }
        }
        work.close();
        if (!found)
        {
            cout << "Worker Not Found" << endl;
        }

        cout << "if you want to continue this process, press 1, if not, press any other number" << endl;
        cin >> flag2;
    };
}
void deleteWorker()
{
    int idTemp;
    int flag2 = 1;
    bool found = false;
    Worker buf;
    ifstream f("worker.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    while (flag2 == 1)
    {
        cout << "Enter the id of the worker you want to delete: " << endl;
        cin >> idTemp;

        while (f.read((char *)&buf, sizeof(buf)))
        {

            if (buf.getWorkerId() != idTemp)
            {
                temp.write((char *)&buf, sizeof(buf));
                found = true;
            };
        };

        f.close();
        temp.close();

        remove("worker.dat");
        rename("temp.dat", "worker.dat");

        if (found)
        {
            flag2 = 0;
        }
        else
        {
            cout << "Worker Not Found" << endl;
            cout << "if you want to continue this process, press 1, if not, press any other number" << endl;
            cin >> flag2;
        }
    };
}

class Provider
{
private:
    int id;
    char name[50];
    char phone[14];

public:
    Provider()=default;
    Provider(int aId, string aName, string aPhone)
    {
        id = aId;
        strcpy(name, aName.c_str());
        strcpy(phone, aPhone.c_str());

        prov.open("provider.dat", ios::binary | ios::app);
        prov.write(reinterpret_cast<char *>(this), sizeof(*this));
        prov.close();
    };

    int getProviderId()
    {
        return id;
    };

    void setProviderName(string aName)
    {
        strcpy(name, aName.c_str());
    };
    void setProviderPhone(string aPhone)
    {
        strcpy(phone, aPhone.c_str());
    };
    char *getProviderName()
    {
        return name;
    };
    char *getProviderPhone()
    {
        return phone;
    };
};
void editProvider()
{
    int idTemp;
    int flag2 = 1;
    string aName, aPhone;
    bool found = false;

    Provider buf;
    while (flag2 == 1)
    {
        cout << "Enter the id of the Provider you want to edit: " << endl;
        cin >> idTemp;

        prov.open("provider.dat", ios::in | ios::out | ios::binary);
        while (1)
        {
            prov.read((char *)&buf, sizeof(buf));
            if (prov.eof())
                break;
            if (buf.getProviderId() == idTemp)
            {
                cout << "Enter the new name: " << endl;
                cin >> aName;
                buf.setProviderName(aName);
                cout << "Enter the new password: " << endl;
                cin >> aPhone;
                buf.setProviderPhone(aPhone);

                prov.seekp(work.tellg() - static_cast<std::streamoff>(sizeof(buf)), std::ios_base::beg);
                prov.write((char *)&buf, sizeof(buf));
                found = true;
                break;
            }
        }
        prov.close();

        if (!found)
        {
            cout << "Provider not Found" << endl;
        };

        cout << "if you want to continue this process, press 1, if not, press any other number" << endl;
        cin >> flag2;
    };
}
void deleteProvider()
{
    int idTemp;
    int flag2 = 1;
    bool found = false;
    Worker buf;
    ifstream f("provider.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    while (flag2 == 1)
    {
        cout << "Enter the id of the worker you want to delete: " << endl;
        cin >> idTemp;

        while (f.read((char *)&buf, sizeof(buf)))
        {

            if (buf.getWorkerId() != idTemp)
            {
                temp.write((char *)&buf, sizeof(buf));
                found = true;
            };
        };

        f.close();
        temp.close();

        remove("provider.dat");
        rename("temp.dat", "provider.dat");

        if (found)
        {
            flag2 = 0;
        }
        else
        {
            cout << "Provider not Found" << endl;
            cout << "if you want to continue this process, press 1, if not, press any other number" << endl;
            cin >> flag2;
        }
    };
}

class Product : public Provider
{
    Provider buf;

private:
    int id, price, stock, stock_min, id_provider;
    char description[30];

public:
    Product(){};
    Product(int aId, int aId_provider, int aPrice, int aStock, int aStock_min, string aDescription)
    {
        id = aId;
        id_provider = aId_provider;
        price = aPrice;
        stock = aStock;
        stock_min = aStock_min;
        strcpy(description, aDescription.c_str());

        prov.open("product.dat", ios::binary | ios::app);
        prov.write(reinterpret_cast<char *>(this), sizeof(*this));
        prov.close();
    };

    int getProductId()
    {
        return id;
    };

    int getProductPrice()
    {
        return price;
    };

    int getProviderId()
    {
        return id_provider;
    };

    int getProductStock()
    {
        return stock;
    };

    int getProductMinStock()
    {
        return stock_min;
    };

    char *getProductDescription()
    {
        return description;
    }

    void setProductPrice(int aPrice)
    {
        price = aPrice;
    };

    void setProductStockMin(int aStock_min)
    {
        stock_min = aStock_min;
    };

    void setProductDescription(string aDescription)
    {
        strcpy(description, aDescription.c_str());
    };

    void setProviderId(int aId_provider)
    {
        id_provider = aId_provider;
    }

    void setProductStock(int aStock)
    {
        stock = aStock;
    };

    void decreaseProductStock(int aStock)
    {
        stock = stock - aStock;
    }

    bool checkStock(int quantity)
    {
        if (stock > quantity)
            return true;
        else
            return false;
    };

    void checkReStock()
    {
        if (stock < stock_min)
        {
            reStock();
        }
    };

    void reStock()
    {
        prov.open("provider.dat", ios::binary | ios::in);
        while (1)
        {
            prov.read((char *)&buf, sizeof(buf));
            if (prov.eof())
                break;
            if (buf.getProviderId() == id_provider)
            {
                string providerName = buf.getProviderName();
                string providerPhone = buf.getProviderPhone();

                string requestDocTitle = "restockOrder_" + to_string(id) + ".dat";
                string requestDocContent = "We need to restock the product with id: " + to_string(id) + "\nWe need 100 units of it.\n";
                string requestDocProviderData = "Send to provider: " + providerName + "\nVia: " + providerPhone + ".";
                
                ofstream file(requestDocTitle);
                file << requestDocContent;
                file << requestDocProviderData;
                file.close();
            }
        }
        prov.close()
    };
};
void editProduct()
{
    int idTemp, aProviderId, aPrice, aStock, aMinStock;
    string aDescription;
    bool productCheck = false;
    int flag2 = 1;

    Product buf;
    while (flag2 == 1)
    {
        cout << "Enter the id of the product you want to edit: " << endl;
        cin >> idTemp;

        prod.open("product.dat", ios::in | ios::out | ios::binary);
        while (1)
        {
            prod.read((char *)&buf, sizeof(buf));
            if (prod.eof())
                break;

            if (buf.getProductId() == idTemp)
            {
                productCheck = true;
                int flag3 = 1;
                while (flag3 == 1)
                {
                    cout << "Enter the id of new the provider: " << endl;
                    cin >> aProviderId;
                    // we need to check that the provider exits
                    Provider buff;
                    fstream f;
                    f.open("provider.dat", ios::binary | ios::in);
                    f.seekg(0, ios::beg);
                    while (1)
                    {
                        f.read((char *)&buff, sizeof(buff));
                        if (f.eof())
                        {
                            cout << "Provider not found" << endl;
                            cout << "Enter an existing id" << endl;

                            break;
                        }
                        if (buff.getProviderId() == aProviderId)
                        {
                            buf.setProviderId(aProviderId);
                            flag3 = 0;
                            break;
                        }
                    }
                    f.close();
                }

                cout << "Enter the new price: " << endl;
                cin >> aPrice;
                buf.setProductPrice(aPrice);
                cout << "Enter the new stock: " << endl;
                cin >> aStock;
                buf.setProductStock(aStock);
                cout << "Enter the new min stock: " << endl;
                buf.setProductStockMin(aMinStock);
                cin >> aMinStock;
                cout << "Enter the new description: " << endl;
                cin >> aDescription;
                buf.setProductDescription(aDescription.c_str());

                prov.seekp(prov.tellg() - static_cast<std::streamoff>(sizeof(buf)), std::ios_base::beg);
                prov.write((char *)&buf, sizeof(buf));

                cout << "New product data" << endl;
                cout << "Description of the product: " << buf.getProductDescription() << endl;
                cout << "Price of the product: " << buf.getProductPrice() << endl;
                cout << "Id of the provider: " << buf.getProviderId() << endl;
                cout << "Stock of the Product: " << buf.getProductStock() << endl;
                cout << "Min stock of the product: " << buf.getProductMinStock() << endl;
                break;
            }
            prov.close();
        }
        prod.close();
        if (!productCheck)
        {
            cout << "" << endl;
            cout << "Product Not Found" << endl;
        }

        cout << "if you want to continue this process, press 1, if not, press any other number" << endl;
        cin >> flag2;
    };
}
void deleteProduct()
{
    int idTemp;
    int flag2 = 1;
    bool found = false;
    Worker buf;
    ifstream f("product.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (flag2 == 1)
    {
        cout << "Enter the id of the worker you want to delete: " << endl;
        cin >> idTemp;

        while (f.read((char *)&buf, sizeof(buf)))
        {

            if (buf.getWorkerId() != idTemp)
            {
                temp.write((char *)&buf, sizeof(buf));
                found = true;
            };
        };

        f.close();
        temp.close();

        remove("product.dat");
        rename("temp.dat", "product.dat");

        if (found)
        {
            flag2 = 0;
            cout << "The operation was succesfull." << endl;
        }
        else
        {
            cout << "Product Not Found" << endl;
            cout << "if you want to continue this process, press 1, if not, press any other number" << endl;
            cin >> flag2;
        }
    };
};

class Client
{
private:
    int id;
    char name[50], address[50], phone[14];

public:
    Client()=default;
    Client(int aId, string aName, string aPhone, string anAddress)
    {
        id = aId;
        strcpy(name, aName.c_str());
        strcpy(phone, aPhone.c_str());
        strcpy(address, anAddress.c_str());
        client.open("client.dat", ios::binary | ios::app);
        client.write(reinterpret_cast<char *>(this), sizeof(*this));
        client.close();
    };

    int getClientId()
    {
        return id;
    };

    void setClientName(string aName)
    {
        strcpy(name, aName.c_str());
    }
    void setClientPhone(string aPhone)
    {
        strcpy(phone, aPhone.c_str());
    }
};
void editClient()
{
    int idTemp;
    int flag2 = 1;
    string aName, aPhone;
    bool found = false;

    Client buf;
    while (flag2 == 1)
    {
        cout << "Enter the id of the Client you want to edit: " << endl;
        cin >> idTemp;

        client.open("client.dat", ios::in | ios::out | ios::binary);
        while (1)
        {
            client.read((char *)&buf, sizeof(buf));
            if (client.eof())
                break;
            if (buf.getClientId() == idTemp)
            {
                cout << "Enter the new name: " << endl;
                cin >> aName;
                buf.setClientName(aName);
                cout << "Enter the new phone: " << endl;
                cin >> aPhone;
                buf.setClientPhone(aPhone);

                client.seekp(client.tellg() - static_cast<std::streamoff>(sizeof(buf)), std::ios_base::beg);
                client.write((char *)&buf, sizeof(buf));
                found = true;
                break;
            }
        }
        client.close();
        if (!found)
        {
            cout << "Client not Found" << endl;
        }

        cout << "if you want to continue this process, press 1, if not, press any other number" << endl;
        cin >> flag2;
    };
}
void deleteClient()
{
    int idTemp;
    int flag2 = 1;
    bool found = false;
    Worker buf;
    ifstream f("client.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    while (flag2 == 1)
    {
        cout << "Enter the id of the worker you want to delete: " << endl;
        cin >> idTemp;

        while (f.read((char *)&buf, sizeof(buf)))
        {

            if (buf.getWorkerId() != idTemp)
            {
                temp.write((char *)&buf, sizeof(buf));
                found = true;
            };
        };

        f.close();
        temp.close();

        remove("client.dat");
        rename("temp.dat", "client.dat");

        if (found)
        {
            flag2 = 0;
        }
        else
        {
            cout << "Client not Found" << endl;
            cout << "if you want to continue this process, press 1, if not, press any other number" << endl;
            cin >> flag2;
        }
    };
}
void createClient(int anId)
{
    string aName, aPhone, anAddress;
    cout << "Enter the name of the new client: " << endl;
    cin >> aName;
    cout << "Enter the phone number of the new client: " << endl;
    cin >> aPhone;
    cout << "Enter the addres of the new client: " << endl;
    cin >> anAddress;
    Client(anId, aName, aPhone, anAddress);
    cout << "Operation succesfull, a new client was created." << endl;
}

class Receipt : public Product
{
    time_t unparsedDate = time(0);

private:
    char id[5];
    int id_client;
    char *date;

public:
    Receipt()=default;
    Receipt(string anId, int aId_client)
    {
        strcpy(id, anId.c_str());
        id_client = aId_client;
        date = asctime(localtime(&unparsedDate));

        receipt.open("receipt.dat", ios::binary | ios::app);
        receipt.write(reinterpret_cast<char *>(this), sizeof(*this));
        receipt.close();
    };

    char *getReceiptId()
    {
        return id;
    }
};
class Purchase
{
private:
    char id[5];
    int id_product;
    char id_receipt[5];
    int quantity;

public:
    Purchase(string anId, int aId_product, string aId_receipt, int aQuantity)
    {
        strcpy(id, anId.c_str());
        id_product = aId_product;
        strcpy(id_receipt, aId_receipt.c_str());
        quantity = aQuantity;

        purc.open("purchase.dat", ios::binary | ios::app);
        purc.write(reinterpret_cast<char *>(this), sizeof(*this));
        purc.close();
    };
};

string createRandomId()
{
    string r = to_string(rand() % 11);
    char a = 97 + rand() % 26;
    char nd = 65 + rand() % 26;
    string anId = (r + a + nd);

    return anId;
}

void loadWorkers()
{
    Worker(29907856, "Jordano", "admi", "ryuk");
    Worker(29929240, "Oriana", "warehouse", "oriexe");
    Worker(31180603, "Ariani", "cashier", "aliendot");
};
void loadProviders()
{
    Provider(29907856, "Jordano Pernia", "0414-3711282");
    Provider(29929240, "Oriana Moreno", "0414-7347068");
    Provider(31180603, "Ariani Valera", "0426-2705797");
};
void loadProducts()
{

    int providersid[3];
    Provider buf;

    arc.open("provider.dat", ios::binary | ios::in);

    int n = 0;
    while (1)
    {
        arc.read((char *)&buf, sizeof(buf));
        if (arc.eof())
            break;
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
};
void loadClients()
{
    Client(29907856, "Jordano Pernia", "0414-3711282", "San Cristobal");
    Client(29929240, "Oriana Moreno", "0414-7347068", "Patiecitos");
    Client(31180603, "Ariani Valera", "0426-2705797", "Tariba");
};

// the programn starts here

int main()
{

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

    cout << "Welcome to the store's system" << endl;
    cout << "Please, before continuing, enter your name and password" << endl;
    cout << "----------------------------------------------------------------" << endl;
    int flag1 = 1;

    while (flag1 == 1)
    {

        char name[50], password[12];
        cout << "Name: ";
        cin >> name;
        cout << "Password: ";
        cin >> password;

        Worker buf;

        work.open("worker.dat", ios::binary | ios::in);
        while (1)
        {
            work.read((char *)&buf, sizeof(buf));
            if (work.eof())
            {
                cout << "Password or name incorrect." << endl;
                break;
            }
            if (buf.checkWorkerRol(name, password))
            {
                rol = buf.getWorkerRol();
                user = true;
                userName = buf.getWorkerName();
                break;
            };
        }
        work.close();

        if (user)
        {
            break;
        }

        cout << "----------------------------------------------------------------" << endl;
        cout << "Enter 1 to try again, or any other key to end the program" << endl;
        cin >> flag1;
    }

    int option;

    if (rol == "admi")
    {
        cout << "----------------------------------------------------------------" << endl;
        cout << "Welcome " << userName << endl;
        cout << "What do you want to do?" << endl;
        while (1)
        {
            cout << "" << endl;
            cout << "  1. Change the products database" << endl;
            cout << "  2. Change the providers database" << endl;
            cout << "  3. Change the clients database" << endl;
            cout << "  4. Change the workers database" << endl;
            cout << "  5. Exit" << endl;
            cout << "" << endl;
            cout << "Select one of the options above by entering it's number" << endl;
            cin >> option;

            switch (option)
            {
            case 1:
            {
                int productFlag = 1;
                while (productFlag == 1)
                {
                    cout << "----------------------------------------------------------------" << endl;
                    cout << "" << endl;
                    cout << "What do you want to do?" << endl;
                    cout << "  1. Add a new product" << endl;
                    cout << "  2. Edit a product" << endl;
                    cout << "  3. Delete a product" << endl;
                    cout << "  4. Exit" << endl;
                    cout << "" << endl;
                    cout << "Select one of the options above by entering it's number" << endl;

                    int productOption;
                    cin >> productOption;
                    switch (productOption)
                    {
                    case 1:
                    {
                        int anId, aProviderId, aPrice, aStock, aMinStock;
                        string aDescription;
                        cout << "Enter the id of the new product: " << endl;
                        cin >> anId;
                        int flag3 = 1;
                        while (flag3 == 1)
                        {
                            cout << "Enter the id of the provider: " << endl;
                            cin >> aProviderId;
                            // we need to check that the provider exits
                            Provider buf;
                            arc.open("provider.dat", ios::binary | ios::in);
                            while (1)
                            {
                                arc.read((char *)&buf, sizeof(buf));
                                if (arc.eof())
                                {
                                    cout << "Provider not found" << endl;
                                    cout << "Enter an existing id" << endl;
                                    arc.close();
                                    break;
                                }
                                if (buf.getProviderId() == aProviderId)
                                {
                                    flag3 = 0;
                                    break;
                                }
                            }
                        }
                        arc.close();
                        cout << "Enter the price of the new product: " << endl;
                        cin >> aPrice;
                        cout << "Enter the stock of the new product: " << endl;
                        cin >> aStock;
                        cout << "Enter the minimum stock of the new product: " << endl;
                        cin >> aMinStock;
                        cout << "Enter the description of the new product: " << endl;
                        cin >> aDescription;
                        Product(anId, aProviderId, aPrice, aStock, aMinStock, aDescription);
                        cout << "Operation succesfull, a new product was created." << endl;
                        break;
                    }
                    case 2:
                    {
                        cout << "" << endl;
                        cout << "You chose to edit a product" << endl;
                        cout << "" << endl;
                        editProduct();
                        break;
                    }
                    case 3:
                    {

                        cout << "" << endl;
                        cout << "You chose to delete product." << endl;
                        cout << "" << endl;
                        deleteProduct();
                        break;
                    }
                    default:
                    {
                        productFlag = 0;
                        break;
                    }
                    }

                    cout << "" << endl;
                    cout << "Do you want to do further modifications?" << endl;
                    cout << "press 1 to continue, press any other number to end the program." << endl;
                    int productMenuEnd;
                    cin >> productMenuEnd;
                    if (productMenuEnd != 1)
                    {
                        productFlag = 0;
                    }
                };
            };
            case 2:
            {
                int providerFlag = 1;
                while (providerFlag == 1)
                {
                    cout << "----------------------------------------------------------------" << endl;
                    cout << "" << endl;
                    cout << "What do you want to do?" << endl;
                    cout << "  1. Add a new provider" << endl;
                    cout << "  2. Edit a provider" << endl;
                    cout << "  3. Delete a provider" << endl;
                    cout << "  4. Exit" << endl;
                    cout << "" << endl;
                    cout << "Select one of the options above by entering it's number" << endl;

                    int providerOption;
                    cin >> providerOption;
                    switch (providerOption)
                    {
                    case 1:
                    {
                        int anId;
                        string aName, aPhone;
                        cout << "Enter the id of the new provider: " << endl;
                        cin >> anId;
                        cout << "Enter the name of the new provider: " << endl;
                        cin >> aName;
                        cout << "Enter the phone number of the new provider: " << endl;
                        cin >> aPhone;
                        Provider(anId, aName, aPhone);
                        cout << "Operation succesfull, a new provider was created." << endl;
                        break;
                    }
                    case 2:
                    {
                        cout << "" << endl;
                        cout << "You chose to edit a provider" << endl;
                        cout << "" << endl;
                        editProvider();
                        break;
                    }
                    case 3:
                    {

                        cout << "" << endl;
                        cout << "You chose to delete product." << endl;
                        cout << "" << endl;
                        deleteProduct();
                        break;
                    }
                    default:
                    {
                        providerFlag = 0;
                        break;
                    }
                    }

                    cout << "" << endl;
                    cout << "Do you want to do further modifications?" << endl;
                    cout << "press 1 to continue, press any other number to end the program." << endl;
                    int providerMenuEnd;
                    cin >> providerMenuEnd;
                    if (providerMenuEnd != 1)
                    {
                        providerFlag = 0;
                    }
                };
            }
            case 3:
            {
                int clientFlag = 1;
                while (clientFlag == 1)
                {
                    cout << "----------------------------------------------------------------" << endl;
                    cout << "" << endl;
                    cout << "What do you want to do?" << endl;
                    cout << "  1. Add a new client" << endl;
                    cout << "  2. Edit a client" << endl;
                    cout << "  3. Delete a client" << endl;
                    cout << "  4. Exit" << endl;
                    cout << "" << endl;
                    cout << "Select one of the options above by entering it's number" << endl;

                    int clientOption;
                    cin >> clientOption;
                    switch (clientOption)
                    {
                    case 1:
                    {
                        int anId;
                        cout << "Enter the id of the new client: " << endl;
                        createClient(anId);
                        break;
                    }
                    case 2:
                    {
                        cout << "" << endl;
                        cout << "You chose to edit a client" << endl;
                        cout << "" << endl;
                        editClient();
                        break;
                    }
                    case 3:
                    {

                        cout << "" << endl;
                        cout << "You chose to delete client." << endl;
                        cout << "" << endl;
                        deleteClient();
                        break;
                    }
                    default:
                    {
                        clientFlag = 0;
                        break;
                    }
                    }
                    cout << "" << endl;
                    cout << "Do you want to do further modifications?" << endl;
                    cout << "press 1 to continue, press any other number to end the program." << endl;
                    int clientMenuEnd;
                    cin >> clientMenuEnd;
                    if (clientMenuEnd != 1)
                    {
                        clientFlag = 0;
                    }
                };
            }
            case 4:
            {
                int workerFlag = 1;
                while (workerFlag == 1)
                {
                    cout << "----------------------------------------------------------------" << endl;
                    cout << "" << endl;
                    cout << "What do you want to do?" << endl;
                    cout << "  1. Add a new worker" << endl;
                    cout << "  2. Edit a worker" << endl;
                    cout << "  3. Delete a worker" << endl;
                    cout << "  Any key. Exit" << endl;
                    cout << "" << endl;
                    cout << "Select one of the options above by entering it's number" << endl;
                    int workerOption;
                    cin >> workerOption;
                    switch (workerOption)
                    {
                    case 1:
                    {
                        int anId;
                        string aName, aRol, aPassword;
                        cout << "" << endl;
                        cout << "You chose to add a new worker" << endl;
                        cout << "" << endl;
                        cout << "Enter the worker's id: " << endl;
                        cin >> anId;
                        cout << "Enter the worker's name: " << endl;
                        cin >> aName;
                        cout << "Enter the worker's rol: " << endl;
                        cin >> aRol;
                        cout << "Enter the worker's password: " << endl;
                        cin >> aPassword;
                        Worker(anId, aName, aRol, aPassword);

                        cout << "Operation succesfull." << endl;
                        break;
                    };
                    case 2:
                    {
                        cout << "" << endl;
                        cout << "You chose to edit worker." << endl;
                        cout << "" << endl;
                        editWorker();

                        break;
                    }
                    case 3:
                    {

                        cout << "" << endl;
                        cout << "You chose to delete worker." << endl;
                        cout << "" << endl;

                        deleteWorker();
                        cout << "operation succesfull." << endl;
                        break;
                    };
                    default:
                    {
                        workerFlag = 0;
                        break;
                    }
                    }

                    cout << "" << endl;
                    cout << "Do you want to do further modifications?" << endl;
                    cout << "press 1 to continue, press any other number to end the program." << endl;
                    int workerMenuEnd;

                    cin >> workerMenuEnd;
                    if (workerMenuEnd != 1)
                    {
                        workerFlag = 0;
                    }
                }
            }
            case 5:
            {
                cout << "Thank you for using the program" << endl;
                return 0;
            }
            default:
            {
                cout << "Enter a correct option" << endl;
                break;
            }
            }
        }
    }
    else if (rol == "warehouse")
    {
        cout << "----------------------------------------------------------------" << endl;
        cout << "Welcome " << userName << endl;
        cout << "What do you want to do?" << endl;
        cout << "" << endl;

        int warehouseFlag = 1;
        while (warehouseFlag == 1)
        {
            cout << "  1. Add a new product" << endl;
            cout << "  2. Edit a product" << endl;
            cout << "  3. Exit" << endl;
            cout << "" << endl;
            cout << "Select one of the options above by entering it's number" << endl;

            int productOption;
            cin >> productOption;
            switch (productOption)
            {
            case 1:
            {
                int anId, aProviderId, aPrice, aStock, aMinStock;
                string aDescription;
                cout << "Enter the id of the new product: " << endl;
                cin >> anId;
                int flag3 = 1;
                while (flag3 == 1)
                {
                    cout << "Enter the id of the provider: " << endl;
                    cin >> aProviderId;
                    // we need to check that the provider exits
                    Provider buf;
                    arc.open("provider.dat", ios::binary | ios::in);
                    while (1)
                    {
                        arc.read((char *)&buf, sizeof(buf));
                        if (arc.eof())
                        {
                            cout << "Provider not found" << endl;
                            cout << "Enter an existing id" << endl;
                            arc.close();
                            break;
                        }
                        if (buf.getProviderId() == aProviderId)
                        {
                            flag3 = 0;
                            break;
                        }
                    }
                }
                arc.close();
                cout << "Enter the price of the new product: " << endl;
                cin >> aPrice;
                cout << "Enter the stock of the new product: " << endl;
                cin >> aStock;
                cout << "Enter the minimum stock of the new product: " << endl;
                cin >> aMinStock;
                cout << "Enter the description of the new product: " << endl;
                cin >> aDescription;
                Product(anId, aProviderId, aPrice, aStock, aMinStock, aDescription);
                cout << "Operation succesfull, a new product was created." << endl;
                break;
            }
            case 2:
            {
                cout << "" << endl;
                cout << "You chose to edit a product" << endl;
                cout << "" << endl;
                editProduct();
                break;
            }
            default:
            {
                break;
            }
            }

            cout << "" << endl;
            cout << "Do you want to do further modifications?" << endl;
            cout << "press 1 to continue, press any other number to end the program." << endl;
            int productMenuEnd;
            cin >> productMenuEnd;
            if (productMenuEnd != 1)
            {
                warehouseFlag = 0;
            };
        };
    }
    else if (rol == "cashier")
    {
        cout << "----------------------------------------------------------------" << endl;
        cout << "Welcome " << userName << endl;
        cout << "The cash register is open" << endl;
        cout << "" << endl;
        int cashierFlag = 1;

        while (cashierFlag == 1)
        {
            int cashierOption;
            cout << "1. to procces a sale" << endl;
            cout << "Any key. to close the cash register" << endl;
            cin >> cashierOption;

            Client buf;
            switch (cashierOption)
            {
            case 1:
            {
                int clientId;
                bool clientCheck;

                string r = to_string(rand() % 11);
                char a = 97 + rand() % 26;
                char nd = 65 + rand() % 26;
                string anId = (r + a + nd);

                cout << "Enter the client's id: " << endl;
                cin >> clientId;
                client.open("client.dat", ios::binary | ios::in);
                client.seekg(0, ios::beg);
                while (1)
                {
                    client.read((char *)&buf, sizeof(buf));
                    if (client.eof())
                    {
                        cout << "Client not found on the database. Procces with their registration." << endl;
                        
                        clientCheck = false;
                        break;
                    }
                    if (buf.getClientId() == clientId)
                    {
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

                cout << "How many items does the client bought?" << endl;
                cin >> quantity;

                for (int i = 0; i < quantity; i++)
                {
                    bool productFound = false;
                    while (!productFound)
                    {
                        Product buffe;
                        cout << "Enter the id of the product: " << endl;
                        cin >> productId;
                        prod.open("product.dat", ios::in | ios::out | ios::binary);
                        while (1)
                        {
                            prod.read((char *)&buffe, sizeof(buffe));
                            if (prod.eof())
                            {
                                cout << "Product not found" << endl;
                                cout << "Enter an existing id" << endl;
                                break;
                            }
                            if (buffe.getProductId() == productId)
                            {
                                while (1)
                                {
                                    cout << "Enter the quantity of the product: " << endl;
                                    cin >> productQuantity;
                                    if (buffe.checkStock(productQuantity))
                                    {
                                        buffe.decreaseProductStock(productQuantity);
                                        prod.seekp(prod.tellg() - static_cast<std::streamoff>(sizeof(buffe)), std::ios_base::beg);
                                        prod.write((char *)&buffe, sizeof(buffe));
                                        string purchaseId = createRandomId();
                                        Purchase(purchaseId, productId, anId, productQuantity);
                                        break;
                                    }
                                    else
                                    {
                                        cout << "We don't have enough stock for this product" << endl;
                                        cout << "Please enter a valid quantity" << endl;
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
            default:
            {
                cashierFlag = 0;
                break;
            };
            };
        };
    }

    return 0;
}