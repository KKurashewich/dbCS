#include "DataBase.h"

DataBase::DataBase(string dataBaseName){
    this->dataBaseName = dataBaseName;
    string name = "";
    
    if(fs::exists(fs::path(this->dataBaseName))){
            for(auto& p: fs::directory_iterator(this->dataBaseName)){
                name = &(p.path().string()[dataBaseName.length()+1]);
                Table newTable(name, getTableInfo(name));
                this->tables.push_back(newTable);
            }
    }else{
        fs::create_directories(this->dataBaseName);
    }
}

DataBase::~DataBase(){
    //cout << "DataBase Deconstructor" << endl;
}
string DataBase::getTableInfo(string tableName){
    string info = "";
    ifstream inFromFile;
    inFromFile.open(this->dataBaseName +'/'+tableName);
    getline(inFromFile, info, '%');
    inFromFile.close();
    return info;
}

//if rowNumber -1 we doing whole columns, if colStartIndex = colEndIndex we are inserting chunk, else we write over data
    //datatest.replace("testthree", {"one%           ","two%           ","two%           "}, -1, 2, 1);//adding column at index 2
    //datatest.replace("testthree", {"one%           ","two%           ","two%           "}, -1, 0, 0);//replace column index 0
    //datatest.replace("testthree", {"one%           two%           two%           "}, 1, 0, 2);//replaceing row at index 1
    //datatest.replace("testthree",{"one%           "}, 1, 0, 0);//replaceing single variable at index row=1, col=0
    //datatest.replace("testthree", {"","",""}, -1, 0, 0);//delete column at index 0
void DataBase::replace(string tableName, vector<string> info, int rowIndex, int colStartIndex, int colEndIndex){
    int currentReadIndex = 0;
    int rowCount;
    int startRead;
    int endRead;
    char *infoChunk;
    string newData ="";
    int tX = this->tableIndex(tableName);
    ifstream iFile(this->dataBaseName + '/'+tableName); 
    iFile.seekg(0, iFile.end);
    int length = iFile.tellg();
    //length --; //to be the index
    iFile.seekg(0, iFile.beg); 
    if(rowIndex == -1){
        rowCount = this->tables[tX].getCount();
        for(int y = 1; y <= rowCount; y++){
            startRead = this->tables[tX].getStartLocation(y, colStartIndex);
            endRead = this->tables[tX].getEndLocation(y, colEndIndex);
            infoChunk = new char [startRead - currentReadIndex+1];
            iFile.read(infoChunk, startRead - currentReadIndex);
            infoChunk[startRead - currentReadIndex] = '\0';
            if(info.size() == 1){
                newData += infoChunk + info[0];
            }else{
                newData += infoChunk + info[y-1];
            }
            delete [] infoChunk;
            iFile.seekg(endRead);
            currentReadIndex = endRead;
        }
    }else{
            startRead = this->tables[tX].getStartLocation(rowIndex, colStartIndex);
            endRead = this->tables[tX].getEndLocation(rowIndex, colEndIndex);
            infoChunk = new char [startRead - currentReadIndex+1];
            iFile.read(infoChunk, startRead - currentReadIndex );
            infoChunk[startRead - currentReadIndex] = '\0';
            newData += infoChunk + info[0];
            delete [] infoChunk;
            iFile.seekg(endRead);
            currentReadIndex = endRead;
    }

    infoChunk = new char [length - currentReadIndex + 1];
    iFile.read(infoChunk, length - currentReadIndex);
    infoChunk[length-currentReadIndex] = '\0';
    newData += infoChunk;
    
    delete [] infoChunk;
    iFile.close();
    cout << newData;
    ofstream oFile(this->dataBaseName + '/'+tableName);
    oFile << newData;
    oFile.close();
}

string DataBase::getDataBaseName(){
    return this->dataBaseName;
}
vector<string> DataBase::getTableNames(){
    vector<string> tableNames;
    for(int x = 0; x < this->tables.size(); x++){
        tableNames.push_back(this->tables[x].getTableName());
    }
    return tableNames;
}

Table* DataBase::getTable(string tableName){
    return &this->tables[tableIndex(tableName)];
}   
int DataBase::tableIndex(string tableName){  //returns -1 if it does not exist or index
    int index = -1;
    for(int x = 0; x < this->tables.size(); x++){
        if(tableName == tables[x].getTableName()){
            index = x;
        }
    }
    return index;
}
void DataBase::createTable(string tableName, vector<string> dataTypes, vector<string> dataNames, int variableCushion){
    Table newTable(tableName, dataNames, dataTypes, variableCushion);
    string convertedInfo = newTable.getTableInfo();
    ofstream oFile(this->dataBaseName + '/' + tableName);//put new data back
    oFile << convertedInfo<<endl;
    oFile.close();
    this->tables.push_back(newTable);
}
void DataBase::deleteTable(string tableName){
    fs::remove(this->dataBaseName+'/'+tableName);
}
void DataBase::addDataColumnToTable(string tableName, string dataName, string dataType, string defaultValue){
    int tX = tableIndex(tableName);
    //Table tableCopy = this->tableCopy;
    int variableCount = this->tables[tX].getVariableCount();
  
    this->replace(tableName, {defaultValue}, -1, variableCount, variableCount-1);//adding column

    string info = this->tables[tX].getTableInfo();
    string formated = "";
    int x = 0;
    while(info[x] != '%'){
        formated+=info[x];
        x++;
    }
    formated+=','+dataName+','+dataType+'%';
    Table cpy("cpy", formated);
    formated = cpy.getTableInfo();

    this->tables[tX].addDataName(dataName, dataType);
    //this->replace(tableName, {formated}, 0, 0, variableCount-1);//replaceing row at index 1

    
    //pushTableInfo(tableName, defaultValue);
}

void DataBase::deleteDataColumnFromTable(string tableName, string dataName){
    int tX = tableIndex(tableName);




    this->tables[tX].removeDataName(dataName);
    //pushTableInfo(tableName, "");
}

int DataBase::checkTableForRow(string tableName, string attributeName, string value){ //returns index or -1

}
void DataBase::addRowToTable(string tableName, vector<string> attributeValues){
    //add 1 to count, increase info count
    int index = tableIndex(tableName);
    this->tables[index].incrementCount();
    string rowData = this->tables[index].convertRowData(attributeValues);
    ofstream oFile(this->dataBaseName + '/' + tableName, ios::app);//put new data back
    oFile << rowData<<endl;
    oFile.close();
}
void DataBase::deleteRowFromTable(string tableName, string attributeName, string value){
    //delete 1 from count
    //we will decrease info coun, delete '\n' from rows 
}
void DataBase::displayTable(string tableName){

}
void DataBase::displayTablesInfo(){
    
}

