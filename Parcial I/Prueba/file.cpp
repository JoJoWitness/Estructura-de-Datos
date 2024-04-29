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
                

                client.seekp(client.tellg() - static_cast<streamoff>(sizeof(buf)), std::ios_base::beg);
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