#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
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

int main(){

   DataBase datatest("db_1");
   datatest.pushTableInfo("testone");
   datatest.replace("testone", 0, 300, "12345678911234567892                                                                                                                                                                                                                                                                                        ");
   return 0;
}