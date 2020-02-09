#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <string>
#include "lib/Table.h"
#include "lib/DataBase.h"
#include "lib/Manager.h"

using namespace std;

template <class type>
void displayVector(vector<type> data){
    for(int x = 0; x < data.size(); x++){
        cout << data[x] << endl;
    }
}

int main(int argc, char *argv[]){
    string test = "";
    Manager dBManager("dataBaseCollection");
    while(test != ".EXIT"){
        getline(cin,test, '\n');
        dBManager.processCommand(test);
    };
   

    //displayVector(test.parseCommand("CREATE TABLE tbl_2 (a3 float, a4 char(20));"));
    //test.createDataBase("db_2");
    //test.deleteDataBase("db_2");


/*
CREATE DATABASE db_1;
CREATE DATABASE db_1;
CREATE DATABASE db_2;
DROP DATABASE db_2;
DROP DATABASE db_2;
CREATE DATABASE db_2;


USE db_1;
CREATE TABLE tbl_1 (a1 int, a2 varchar(20));
CREATE TABLE tbl_1 (a3 float, a4 char(20));
DROP TABLE tbl_1;
DROP TABLE tbl_1;
CREATE TABLE tbl_1 (a1 int, a2 varchar(20));
SELECT * FROM tbl_1;
ALTER TABLE tbl_1 ADD a3 float;
SELECT * FROM tbl_1;
CREATE TABLE tbl_2 (a3 float, a4 char(20));
SELECT * FROM tbl_2;
USE db_2;
SELECT * FROM tbl_1;
CREATE TABLE tbl_1 (a3 float, a4 char(20));
SELECT * FROM tbl_1;

.EXIT


    */
    //test.addColumnToTable("testone", "2ar", "char", "NULL");
    //test.createTable2("tb_4", "a3 float a4 char(20)");
    //test.deleteTable("db_3");
    //test.displayInfoFromTable("testone");
    //DataBase datatest("db_1");
    //datatest.addDataColumnToTable("testthree", "dataName", "dataType", "12345%         ");
    //datatest.replace("testthree", {"12345%         "}, -1, 3, 2);
    //datatest.replace("testthree", {"one%           ","two%           ","two%           "}, -1, 3, 2);//adding column at index 2
    //datatest.createTable("testone", {"name", "city", "state"}, {"char", "char", "char(20)"}, 30);    
    //datatest.deleteTable("testTwo");
    //datatest.addRowToTable("testthree", {"kevin", "reno", "nevada"}); 
    //datatest.addDataColumnToTable("testone", "random", "char(20)"); 
    //string test = "0,30,name,char,city,char,state,char(20)%                                                  ";
    //datatest.addDataColumnToTable("testone", "random", "char(20)"); 
    //datatest.replace("testthree", {"one%           ","two%           ","two%           "}, -1, 2, 1);//adding column at index 2
    //datatest.replace("testthree", {"one%           ","two%           ","two%           "}, -1, 0, 0);//replace column index 0
    //datatest.replace("testthree", {"one%           two%           two%           "}, 1, 0, 2);//replaceing row at index 1
    //datatest.replace("testthree",{"one%           "}, 1, 0, 0);//replaceing single variable at index row=1, col=0

    //datatest.replace("testthree", {"ren1%          "}, 2, 2, 2);
    //cout << test.length()<<endl;
    return 0;
}