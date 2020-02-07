#ifndef __MANAGER_H
#define __MANAGER_H



#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Manager{
    private:
        vector<DataBase> dataBases;
    public:
        Manager();   //search for dataBases
        ~Manager();
        vector<string> getDataBaseNames();
        DataBase getDataBase(string dataBaseName);
        void loadDataBases();
        bool dataBaseExists(string dataBaseName);
        void createDataBase(string dataBaseName);
        void deleteDataBase(string dataBaseName);
};

#endif