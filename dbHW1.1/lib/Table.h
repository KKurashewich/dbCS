#ifndef __TABLE_H
#define __TABLE_H

#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class Table{
    private:
        string tableName;
        vector<string> dataTypes;
        vector<string> dataNames;   //first column name like 'ID' must have a unique value from all rows;
        int variableCushion;
        int count;
    public:
        Table(string tableName, vector<string> dataTypes, vector<string> dataNames, int variableCushion);
        Table(string tableName, string tableInfo);
        ~Table();
        string getTableName();
        vector<string> getDataTypes();
        vector<string> getDataNames();
        int getCount();
        int getVariableCount();
        void incrementCount();
        void decreaseCount();
        void changeDataTypes(vector<string> dataTypes);
        void changeDataNames(vector<string> dataNames);
        
        string generateCushionInfo(string data);
        string generateCushion(string data);
        void setTableInfo(string info);
        string getTableInfo();// returns the string that wholds data names and types
        string convertInfo(vector<string> dataNames, vector<string> data); //convert info to row format in single string
        vector<string> parseInfo(string info);//converts single string into parsed info
        int getStartLocation(int rowIndex, int columnIndex);
        int getEndLocation(int rowIndex, int columnIndex);
        void displayRow(string info);
        void displayInfo();
};

#endif