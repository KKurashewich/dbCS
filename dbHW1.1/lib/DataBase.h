#ifndef __DATABASE_H
#define __DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "Table.h"

using namespace std;
namespace fs = std::filesystem;
class DataBase{
    private:
        string dataBaseName;
        vector<Table> tables;
    public:
        DataBase(string dataBaseName);
        ~DataBase();

        string getDataBaseName();
        vector<string> getTableNames();
        Table* getTable(string tableName);   
        int tableIndex(string tableName);  //returns -1 if it does not exist or index
        void createTable(string tableName, vector<string> dataNames, vector<string> dataTypes, int variableCushion);
        void deleteTable(string tableName);
        void addDataColumnToTable(string tableName, string dataName, string dataType, string defaultValue = "NULL");
        void deleteDataColumnFromTable(string tableName, string dataName);
        string getTableInfo(string tableName);
        void pushTableInfo(string tableName, string defaultValue);
        int checkTableForRow(string tableName, string attributeName, string value); //returns index or -1
        void addRowToTable(string tableName, vector<string> attributeValues);
        void deleteRowFromTable(string tableName, string attributeName, string value);
        void displayTable(string tableName);
        void displayTablesInfo();
        //void replace(string tableName, int startIndex, int endIndex, string info);
        void replace(string tableName, vector<string> info, int rowIndex, int colStartIndex, int colEndIndex);
        //void appendString(string rowInfo);
        //void removeString(index)

};

#endif