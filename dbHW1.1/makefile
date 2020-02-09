

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g -std=c++17
PATH = lib/
OBJP = obj/

# ****************************************************
# Targets needed to bring the executable up to date
#$(OBJP)main.o $(OBJP)Manager.o $(OBJP)DataBase.o $(OBJP)Table.o


main: $(OBJP)main.o $(OBJP)Manager.o $(OBJP)DataBase.o $(OBJP)Table.o
	$(CXX) $(CXXFLAGS) -o main $^
	
$(OBJP)main.o: main.cpp $(PATH)Manager.h $(PATH)DataBase.h $(PATH)Table.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
    
$(OBJP)Table.o:  $(PATH)Table.cpp $(PATH)Table.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJP)DataBase.o: $(PATH)DataBase.cpp $(PATH)DataBase.h $(PATH)Table.h 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJP)Manager.o: $(PATH)Manager.cpp $(PATH)Manager.h $(PATH)DataBase.h $(PATH)Table.h 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

	