#ifndef __MANAGER_H
#define __MANAGER_H



#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include "DataBase.h"
#include "Table.h"

using namespace std;
namespace fs = std::filesystem;

class Manager{
    private:

        string dataBaseCollection;
        vector<DataBase> dataBases;
        int selectedIndex;
    public:
        Manager(string dataBaseCollection);

        //void loadDataBase(string dBName);
        void createDataBase(string dBName);
        void deleteDataBase(string dBName);

        void mountDataBase(string dBName);
        void displayInfoFromTable(string tableName);
        void addColumnToTable(string tableName, string dataName, string dataType, string defaultValue = "NULL");
        
        void createTable(string tableName, vector<string> dataNames, vector<string> dataTypes);
        void createTable2(string tableName, string info);
        void deleteTable(string tableName);

        void exit();

        bool processCommand(string command);
        vector<string> parseCommand(string command);

        int getDBIndex(string dBName);

};
#endif