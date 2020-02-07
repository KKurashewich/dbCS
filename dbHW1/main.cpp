#include <iostream>
#include <fstream>

#include <filesystem>
#include <string>
#include <vector>



bool createTable(std::string dBName, std::string tableName, std::string attributes);
bool removeTable(std::string dBName, std::string tableName);
bool createDB(std::string dBName);
bool removeDB(std::string dBName);
bool modifyTable(std::string dBName, std::string tableName, std::string attributes);
bool addQuery(std::string attributes);
std::vector<std::string> getTableInfo(std::string dBName, std::string tableName);
std::vector<std::string> parseTableInfo(std::string tableInfo);
int getTableRowLength(std::string dBName, std::string tableName);
bool checkValidQuery(std::string dBName, std::string tableName, std::string attributes);



int main(){
createDB("testDB");
createTable("testDB", "table_1", "name,char(20),address,varchar(23),age,int");
std::vector<std::string> info= parseTableInfo(getTableInfo("testDB", "table_1"));
for(int x = 0; x< info.size(); x++)
	std::cout << info[x]<<std::endl;

return 0;
}

bool createTable(std::string dBName, std::string tableName, std::string attributes){	//"(name:CHAR(30),age:)
	bool isAvailable = !std::filesystem::exists(dBName+'/'+tableName+".tb");
	if(isAvailable){
		std::fstream dataFile;
		dataFile.open(dBName+'/'+tableName+".tb", std::ios::out);
		dataFile << "0," << attributes << std::endl;
		dataFile.close();
	}
	return isAvailable;
}

bool removeTable(std::string dBName, std::string tableName){
	bool isExisting = std::filesystem::exists(dBName+'/'+tableName+".tb");
	if(isExisting){
		std::filesystem::remove("rm "+dBName+'/'+ tableName + ".tb");
	}
	return isExisting;
}

bool createDB(std::string dBName){
	bool isAvailable = !std::filesystem::exists(dBName);
	if(isAvailable){

		std::filesystem::create_directory(dBName);
	}
	return isAvailable;
}

//TODO: we need to get list of names inside a directory.
bool removeDB(std::string dBName){
	bool isExisting = std::filesystem::exists(dBName);
	if(isExisting){
		for(auto& p: std::filesystem::directory_iterator(dBName))
        	std::filesystem::remove_all(dBName);
		//system(("rmdir "+ dBName).c_str());
	}
	return isExisting;
}

bool modifyTable(std::string dBName, std::string tableName, std::string attributes){
	std::vector<std::string> data = getTableInfo(dBName, tableName);

	return true;
}

int getTableRowLength(std::string dBName, std::string tableName){
	
}
//max size--
//int: 11 digits 2147483647
//float: say 41 digits 3.40282e+38
//double: say 410 digits 1.79769e+308
//char: 1
//varchar: 255
//text: 255


std::vector<std::string> getTableInfo(std::string dBName, std::string tableName){
	bool isExisting = std::filesystem::exists(dBName+'/'+tableName+".tb");
	std::string tableType;
	if(isExisting){
		std::fstream dataFile;
		dataFile.open(dBName+'/'+tableName+".tb", std::ios::in);
		//dataFile.seekg(20L, std::ios::beg);
		std::getline(dataFile, tableType);
		dataFile.close();
	}
	std::vector<std::string> data = parseTableInfo(tableType);
	return data;
}

//TODO: we need to get list of names inside a directory.
//example: "0,name,char(20),address,varchar(23),age:int"
//max size--
//int: 11 digits 2147483647
//float: say 41 digits 3.40282e+38
//double: say 410 digits 1.79769e+308
//char: 1
//varchar: 255
//text: 255
std::vector<std::string> parseTableInfo(std::string tableInfo){
	int index = 0;
	std::vector<std::string> info;
	std::string storage = "";
	while(tableInfo[index]){
		if(tableInfo[index]==','){
			info.push_back(storage);
			storage = "";

		}else{
			storage += tableInfo[index];
		}
		index ++;
	}
	return info;
}


