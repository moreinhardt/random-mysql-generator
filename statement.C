#include<iostream>
#include<vector>
#include "statement.H"

int Statement::getRandomInt(int max=0) {
	srand( (unsigned) time(NULL) ) ;
	if(!max)
		return rand();
	else
		return rand() % (max+1);
}

char * Statement::getRandomString(int lenght) {
	char *string = new char[lenth];  //memory leak
	for(int i=0; i<length; ++i) {
		string[i] = char(getRandomInt(127));	//127 max in asci?
	}
	return string;
}

Statement::Statement(char * tablename, vector<char*> attributes, vector<char*> types, vector<int> lengths) {
	this->tablename = tablename;
	this->attributes = attributes;
	this->types = types;
	this->lengths = lengths;
}

bool Statement::createFile(char *filename, int count) {
	
}
