#include "Table.h"

Table::Table(string tableName, vector<string> dataTypes, vector<string> dataNames, int variableCushion){
    this->tableName = tableName;
    this->dataTypes = dataTypes;
    this->dataNames = dataNames;
    this->variableCushion = variableCushion;
    this->count = 0;
}
Table::Table(string tableName, string tableInfo){
    this->tableName = tableName;
    setTableInfo(tableInfo);
}

Table::~Table(){
    //cout << "Table: deconstructor" << endl;
}
string Table::getTableName(){
    return this->tableName;
}

vector<string> Table::getDataTypes(){
    return this->dataTypes;
}
vector<string> Table::getDataNames(){
    return this->dataNames;
}
int Table::getCount(){
    return this->count;
}
int Table::getVariableCount(){
    return this->dataNames.size();
}

void Table::incrementCount(){
    this->count++;
}
void Table::decreaseCount(){
    this->count--;
}

void Table::changeDataTypes(vector<string> dataTypes){
    this->dataTypes = dataTypes;
}

void Table::changeDataNames(vector<string> dataNames){
    this->dataNames = dataNames;
}
string Table::generateCushionInfo(string data){     // data ends with %
    int length = this->dataNames.size()*this->variableCushion+1;
    string cushWord = data + '%';
    for(int x = data.length(); x < length; x++)
        cushWord += ' ';
    return cushWord;
}
string Table::generateCushion(string data){
    vector<string> dataParsed = parseInfo(data);
    string cushData = "";
    for(int x = 0; x < dataParsed.size(); x++){
        cushData += dataParsed[x] + '%';
        for(int y = cushData.length(); y < x*this->variableCushion; y++){
            cushData += ' ';
        }
    }
    return cushData;
}

void Table::setTableInfo(string info){
    vector<string> parsedInfo = parseInfo(info);
    this->count = stoi(parsedInfo[0]);
    this->variableCushion = stoi(parsedInfo[1]);
    for(int x = 2; x < parsedInfo.size(); x++){
        this->dataNames.push_back(parsedInfo[x]);
        x++;
        this->dataTypes.push_back(parsedInfo[x]);
    }
}

string Table::getTableInfo(){// returns the string that wholds data names and types
    string tableInfo = "";
    tableInfo += to_string(this->count) +','+ to_string(this->variableCushion);
    for(int x = 0; x < this->dataNames.size(); x++){
        tableInfo += ',' + this->dataNames[x] + ',' + this->dataTypes[x];
    }
    return generateCushionInfo(tableInfo);
}

string Table::convertInfo(vector<string> dataNames, vector<string> data){ //convert to row formate in single string
    string tableInfo = "";
    for(int x = 0; x < dataNames.size(); x++){
        tableInfo += ',' + dataNames[x] + ',' + data[x];
    }
    return generateCushion(tableInfo);
}

vector<string> Table::parseInfo(string info){
    vector<string> parsedInfo;
    string holder;

    for(int x = 0; x < info.length(); x++){
        if(info[x] == ','){
            parsedInfo.push_back(holder);
            holder = "";
        }else{
            holder+= info[x];
        }
    }
    parsedInfo.push_back(holder);
    return parsedInfo;
}

int Table::getStartLocation(int rowIndex, int columnIndex){  //returns the bit location to start deleting and when to end
    return (rowIndex*this->dataNames.size()*this->variableCushion)+(this->variableCushion*columnIndex);
}   //exp:(0,2)Cush=100,varCount=3 -> 0*3*100 + 100*2 = 500


int Table::getEndLocation(int rowIndex, int columnIndex){
    return (rowIndex*this->dataNames.size()*this->variableCushion)+(this->variableCushion*columnIndex)+this->variableCushion;
}

void Table::displayRow(string row){
    vector<string> parsedRow = parseInfo(row);
    cout << "< ";
    for(int x = 0; x < parsedRow.size(); x++){
        cout << parsedRow[x] << "=";
        x++;
        cout << parsedRow[x] << " ";
    }
    cout << endl;
}

void Table::displayInfo(){
    cout <<"tableName: "<<this->tableName<< ", rowCount: "<< this->count <<", variableCushion: "<< this->variableCushion << " <TYPE COLUMNNAME, ...><";
    for(int x = 0; x < this->dataNames.size(); x++){
         cout << this->dataTypes[x] << " "<< this->dataNames[x];
         if(x +1 < this->dataNames.size()){
             cout << ", ";
         }
    }
    cout << ">" << endl;
}