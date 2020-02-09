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
        fs::remove_all(this->dataBaseCollection+'/'+dBName);
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
        cout << "!Failed to select table "<<tableName<<" because are not using a dataBase."<<endl;
    }else{
        tableIndex = this->dataBases[this->selectedIndex].tableIndex(tableName);
        if(tableIndex != -1){
            this->dataBases[this->selectedIndex].displayTablesInfo(tableIndex);
        }else{
            cout << "!Failed to select table "<<tableName << " does not exist."<<endl;
        }
    }
}
void Manager::addColumnToTable(string tableName, string dataName, string dataType, string defaultValue){
    int tableIndex;
    if(this->selectedIndex == -1){
        cout << "!Failed to select table "<<tableName<<" because are not using a dataBase."<<endl;
    }else{
        tableIndex = this->dataBases[this->selectedIndex].tableIndex(tableName);
        if(tableIndex != -1){
            this->dataBases[this->selectedIndex].addDataColumnToTable(tableName, dataName, dataType, "NULL");
        }else{
            cout << "!Failed to select table "<<tableName << " does not exist."<<endl;
        }
    }
}
void Manager::createTable(string tableName, vector<string> dataNames, vector<string> dataTypes){
    int tableIndex;
    if(this->selectedIndex == -1){
        cout << "!Failed to select table "<<tableName<<" because are not using a dataBase."<<endl;
    }else{
        tableIndex = this->dataBases[this->selectedIndex].tableIndex(tableName);
        if(tableIndex == -1){
            cout << "Table "<< tableName << " created." << endl;
            this->dataBases[this->selectedIndex].createTable(tableName, dataNames, dataTypes, 100);//100 is each variable cusshion
        }else{
            cout << "!Failed to create table "<<tableName << " because it exists."<<endl;
        }
    }
}
void Manager::createTable2(string tableName, string info){
    //a3 float, a4 char(20)
    int tableIndex;
    vector<string> dataNames;
    vector<string> dataTypes;
    vector<string> data;
    string temp;

    if(this->selectedIndex == -1){
        cout << "!Failed to select table "<<tableName<<" because are not using a dataBase."<<endl;
    }else{
        tableIndex = this->dataBases[this->selectedIndex].tableIndex(tableName);
        if(tableIndex == -1){
            cout << "Table "<< tableName << " created." << endl;
            for(int x = 0; x < info.length(); x++){
                if(info[x] == ' '){
                    data.push_back(temp);
                    temp = "";
                }else{
                    temp+= info[x];
                }
            }
            data.push_back(temp);
            for(int x = 0; x <  data.size(); x++){
                if(x % 2 == 0){
                    dataNames.push_back(data[x]);
                }else{
                    dataTypes.push_back(data[x]);
                }
            }
            this->dataBases[this->selectedIndex].createTable(tableName, dataNames, dataTypes, 100);//100 is each variable cusshion
        }else{
            cout << "!Failed to create table "<<tableName << " because it exists."<< endl;
        }
    }
}
void Manager::deleteTable(string tableName){
    int tableIndex;
    if(this->selectedIndex == -1){
        cout << "!Failed to select table "<<tableName<<" because are not using a dataBase."<<endl;
    }else{
        tableIndex = this->dataBases[this->selectedIndex].tableIndex(tableName);
        if(tableIndex != -1){
            cout << "Table "<< tableName << " deleted." << endl;
            this->dataBases[this->selectedIndex].deleteTable(tableName);
        }else{
            cout << "!Failed to delete table "<<tableName << " because it does not exist."<<endl;
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
    
    vector<string> parsed = this->parseCommand(command);
    if(parsed[0] == "CREATE"){
        if(parsed[1] == "DATABASE"){
            this->createDataBase(parsed[2]);
        }else if(parsed[1] == "TABLE"){
            this->createTable2(parsed[2], parsed[3]);
        }
    }else if(parsed[0] == "DROP"){
        if(parsed[1] == "DATABASE"){
            this->deleteDataBase(parsed[2]);
        }else if(parsed[1] == "TABLE"){
            this->deleteTable(parsed[2]);
        }
    }else if(parsed[0] == "USE"){
        this->mountDataBase(parsed[1]);
    }else if(parsed[0] == "SELECT"){
        this->displayInfoFromTable(parsed[3]);
    }else if(parsed[0] == "ALTER"){//ALTER TABLE tbl_1 ADD a3 float;
        if(parsed[3]=="ADD"){
            this->addColumnToTable(parsed[2], parsed[4], parsed[5], "NULL");
        }
    }else if(parsed[0] == ".EXIT"){
        this->exit();
    }else{
        //cout << parsed[0];
        //cout << " not a command"<<endl;
    }
}

vector<string> Manager::parseCommand(string command){
    vector<string> dataOrganized;
    string temp = "";
    int x = 0;
    int pCount = 0;
    while(command[x] != ';' && x < command.length()){
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
                }else if(command[x] == ','){
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