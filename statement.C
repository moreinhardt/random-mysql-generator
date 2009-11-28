#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>
#include<cstring>
#include<cstdio> //sprintf()
#include "statement.H"

int Statement::getRandomInt(int max=0) {
	srand( (unsigned) time(NULL) ) ;
	if(!max) {
		std::cout << "rand() = " << rand() << std::endl;
		return rand();
	} else
		return rand() % (max+1);
}

char * Statement::getRandomString(int length) {
	std::cout << "start getrandomstring()" << std::endl;
	char *string = new char[length];  //memory leak
	for(int i=0; i<length; ++i) {
		string[i] = static_cast<char>(getRandomInt(126));	//127 max in asci?
	}
	return string;
}

Statement::Statement(char * tablename, std::vector<char*> attributes, std::vector<char*> types, std::vector<int> lengths) {
	this->table_name = tablename;
	this->attributes = attributes;
	this->types = types;
	this->lengths = lengths;
}

bool Statement::createFile(char *filename, int count) {
	std::string output("INSERT INTO ");
	output += this->table_name;
	output += " (";
	int count_lengths = 0;
	for(int i=0; i<this->attributes.size(); ++i) {
		output += attributes[i];
		output += ", ";
	}
	output.erase(output.end()-1); // cut ", " off last one
	output.erase(output.end()-1);
	
	output += ") VALUES (";

	//begin calculating random data and inserting it
	for(int i=0; i<this->types.size(); ++i) {
		int s=0; //0=int
                if(!(std::strcmp(this->types[i],"string"))) //strcmp = 0 if the same
                        s=1;

                switch(s) {
                        case 0: //int
				char buffer[33];
				sprintf(buffer,"%d",getRandomInt());
				output += buffer;
				output += ",";
                                break;
                        case 1: //string
				output += "\'";
				std::cout << "before string" << std::endl;
				std::cout << "length: " << this->lengths[count_lengths] << std::endl;
				output += getRandomString(this->lengths[count_lengths++]); //increas count afterwards
				std::cout << "after" << std::endl;
				output += "\',";
                                break;
                        default:
				break;
                }
	}
	output.erase(output.end()-1); //cut off ","
	output += ");";
	std::cout << output << std::endl;
	
	return true;	
}
