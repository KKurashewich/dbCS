#include "Manager.h"
            
//      vector<DataBase> dataBases;
//      int selectedIndex;

Manager::Manager(string dataBaseCollection){
        this->dataBaseCollection = dataBaseCollection;
        this->selectedIndex = -1;
        for(auto& p: fs::directory_iterator(dataBaseCollection)){
            DataBase dB(p.path().string());
            this->dataBases.push_back(dB);
        }
}

//void Manager::loadDataBase(string dBName){

//}
void Manager::createDataBase(string dBName){
    if(this->getDBIndex(dBName) == -1){
        cout << "Database "<<dBName<<" created." << endl;
        DataBase dB(this->dataBaseCollection +'/'+ dBName);
        this->dataBases.push_back(dB);
    }else{
        cout << "!Failed to create database "<< dBName<<" because it already exists."<< endl;
    }
}
// Database db_2 deleted.
// !Failed to delete db_2 because it does not exist.
void Manager::deleteDataBase(string dBName){
    int index = this->getDBIndex(dBName);
    if(index != -1){
        cout << "Database "<<dBName<<" deleted." << endl;
        this->dataBases.erase(this->dataBases.begin()+index);
    }else{
        cout << "!Failed to delete "<< dBName<<" because it already exists."<<endl;
    }
}
//Using Database db_2
void Manager::mountDataBase(string dBName){
    int index = this->getDBIndex(dBName);
    if(index == -1){
        cout << "!Failed to use "<<dBName<<" because it does not exist."<< endl;
    }else{
        cout << "Using Database "<<dBName<<endl;
        this->selectedIndex = index;
    }
}

void Manager::displayInfoFromTable(string tableName){
    int tableIndex;
    if(this->selectedIndex == -1){
        cout << "!Failed to select table "<<tableName<<" because are not using a dataBase.";
    }else{
        tableIndex = this->dataBases[this->selectedIndex].tableIndex(tableName);
        if(tableIndex != -1){
            this->dataBases[this->selectedIndex].displayTablesInfo(tableIndex);
        }else{
            cout << "!Failed to select table "<<tableName << " does not exist.";
        }
    }
}
void Manager::addColumnToTable(string tableName, string dataName, string dataType, string defaultValue){
    int tableIndex;
    if(this->selectedIndex == -1){
        cout << "!Failed to select table "<<tableName<<" because are not using a dataBase.";
    }else{
        tableIndex = this->dataBases[this->selectedIndex].tableIndex(tableName);
        if(tableIndex != -1){
            this->dataBases[this->selectedIndex].addDataColumnToTable(tableName, dataName, dataType, "NULL");
        }else{
            cout << "!Failed to select table "<<tableName << " does not exist.";
        }
    }
}
void Manager::createTable(string tableName, vector<string> dataNames, vector<string> dataTypes){
    int tableIndex;
    if(this->selectedIndex == -1){
        cout << "!Failed to select table "<<tableName<<" because are not using a dataBase.";
    }else{
        tableIndex = this->dataBases[this->selectedIndex].tableIndex(tableName);
        if(tableIndex == -1){
            cout << "Table "<< tableName << " created." << endl;
            this->dataBases[this->selectedIndex].createTable(tableName, dataNames, dataTypes, 100);//100 is each variable cusshion
        }else{
            cout << "!Failed to create table "<<tableName << " because it exists.";
        }
    }
}
void Manager::deleteTable(string tableName){
    int tableIndex;
    if(this->selectedIndex == -1){
        cout << "!Failed to select table "<<tableName<<" because are not using a dataBase.";
    }else{
        tableIndex = this->dataBases[this->selectedIndex].tableIndex(tableName);
        if(tableIndex != -1){
            cout << "Table "<< tableName << " deleted." << endl;
            this->dataBases[this->selectedIndex].deleteTable(tableName);
        }else{
            cout << "!Failed to delete table "<<tableName << " because it does not exist.";
        }
    }
}

void Manager::exit(){
    cout << "All done."<<endl;
}

bool Manager::processCommand(string command){
    //CREATE DATABASE db_1;
    //DROP DATABASE db_2;
    //USE db_1;
    //CREATE TABLE tbl_1 (a1 int, a2 varchar(20));
    //DROP TABLE tbl_1;
    //SELECT * FROM tbl_1;
    //ALTER TABLE tbl_1 ADD a3 float;
    //.EXIT
    vector<string> parsed = this->parsedCommand(command);
    
    
}

vector<string> Manager::parseCommand(string command){
    vector<string> dataOrganized;
    string temp = "";
    int x = 0;
    int pCount = 0;
    while(command[x] != ';'){
        if(command[x] == '('){
            pCount++;
            x++;
            while(pCount!=0){
                if(command[x]== '('){
                    pCount++;
                    temp+= command[x];
                }else if(command[x] == ')'){
                    pCount--;
                    if(pCount != 0){
                        temp += command[x];
                    }
                }else{
                    temp += command[x];
                }
                x++;
            }
            dataOrganized.push_back(temp);
            temp = "";
        }else if (command[x] == ' '){
            dataOrganized.push_back(temp);
            temp = "";
            x++;
        }else{
            temp += command[x];
            x++;
        }
    }
    dataOrganized.push_back(temp);
    return dataOrganized;
}

 int Manager::getDBIndex(string dBName){
    int index = -1;
    for(int x = 0; x < this->dataBases.size(); x++){
        if(this->dataBaseCollection +'/'+ dBName == this->dataBases[x].getDataBaseName()){
            index = x;
            break;
        }
    }
    return index;
 }