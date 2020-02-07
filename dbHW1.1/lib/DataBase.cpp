#include "DataBase.h"

/*

class DataBase{
    private:
        string dataBaseName;
        vector<Table> tables;
    public:
        DataBase(string dataBaseName);
        ~DataBase();
        string getDataBaseName();
        vector<string> getTableNames();
        Table getTable(string tableName);   
        int tableIndex(string tableName);  //returns -1 if it does not exist or index
        void createTable(string tableName);
        void deleteTable(string tableName);
        int checkTableForRow(string tableName, string attributeName, string value); //returns index or -1
        void addRowToTable(string tableName, vector<string> attributeNames, vector<string> attributeValues);
        void deleteRowFromTable(string tableName, string attributeName, string value);
        void displayTable(string tableName);

        //void appendString(string rowInfo);
        //void removeString(index)

};
*/
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
//we need to take in string replace part then output data
void DataBase::replace(string tableName, int startIndex, int endIndex, string info){
    
    int length;
    char * buffer;


    ifstream iFile(this->dataBaseName + '/'+tableName);

    iFile.seekg(0, std::ios::end);
    length = iFile.tellg();
    iFile.seekg(0, std::ios::beg);    
    buffer = new char[startIndex];

    iFile.read(buffer, sizeof(*buffer));    
    
    //cout << buffer << endl;   
    iFile.close();                    

    ofstream oFile(this->dataBaseName + '/'+tableName+".cpy");

    oFile << buffer << info;
    delete [] buffer;
    oFile.close();
      cout << "test" << endl; 
    iFile.open(this->dataBaseName + '/'+tableName);
    cout << length<< endl;
    cout << endIndex<< endl;
    buffer = new char[length-endIndex];
    iFile.seekg(endIndex);
    iFile.read(buffer, sizeof(buffer));
    iFile.close();

    oFile.open(this->dataBaseName + '/'+tableName+".cpy");
    oFile << buffer;
    delete [] buffer;
    oFile.close();
}

void DataBase::pushTableInfo(string tableName){
    //fstream outputToFile;
    //outputToFile.open(this->dataBaseName +'/'+tableName);
    //cout << tableName << endl;
    Table *ptr = getTable(tableName);
    string info = ptr->getTableInfo();
    ptr->getStartLocation(0, 0);
    replace(tableName,0,ptr->getEndLocation(0, ptr->getVariableCount()-1), info);// startIndex, endIndex);
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
    //cout << index << "tableIndex"<<endl;
    return index;
}
void DataBase::createTable(string tableName){

}
void DataBase::deleteTable(string tableName){

}
int DataBase::checkTableForRow(string tableName, string attributeName, string value){ //returns index or -1

}
void DataBase::addRowToTable(string tableName, vector<string> attributeNames, vector<string> attributeValues){

}
void DataBase::deleteRowFromTable(string tableName, string attributeName, string value){

}
void DataBase::displayTable(string tableName){

}
void DataBase::displayTablesInfo(){

}

