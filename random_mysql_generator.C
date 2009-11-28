#include<iostream>
#include "statement.H"
#include<vector>
#include<cstdlib>
#include<cstring>

void usage(char * erromsg) {
	std::cout << erromsg << std::endl;
	std::cout << "USAGE: ./random-mysql-generator <tablename> <attr1> <type1> [<size1>] [<attr2> <type2> [<size2>]...] <number_of_entries>" << std::endl;
	std::cout << "Where type = {integer, string}" << std::endl;
	std::cout << "size only needed if type=string" << std::endl;
	std::cout << "outputfile will be \"insert_<tablename>_<nrOfEntries>\"" << std::endl;
	std::exit(1);
}

Statement * prepareArguments(int argc, char ** argv) {
	char * tablename = argv[1];
	std::vector<char*> attributes;
	std::vector<char*> types;
	std::vector<int> lengths;
	for(int i=2; i<argc-1; ++i) {  //-1 because there are pairs // i=1 because it starts with the secand parameter
		attributes.push_back(argv[i++]); //i++ -> set i to type
		int s=0; //0=int
		if(!(std::strcmp(argv[i],"string"))) //strcmp = 0 if the same
			s=1;
		
		switch(s) {
			case 0: //int
				types.push_back("integer");
				break;
			case 1: //string
				types.push_back("string");
				lengths.push_back(atoi(argv[++i])); //if string get length
				break;
			default:
				usage("Invalid parameters!");
		}
	}
	Statement * s = new Statement(tablename, attributes, types, lengths); //kopierkonstrutkor used...
	return s;
}

//TODO rethink!
char * createFilename(char * tablename, char * nrOfEntries) {
	int len = strlen(tablename);
	len += strlen(nrOfEntries);
	len += 8; //=strlen("insert_") + strlen("_")
	char * filename = new char[len+1]; //+\0
	strcpy(filename, "insert_");
	strcat(filename, tablename);
	strcat(filename, "_");
	strcat(filename, nrOfEntries);
	//filename = "insert_" << tablename << "_" << nrOfEntries;
	return filename;
}

int main(int argc, char ** argv) {
	if(argc < 4) usage("To few parameters!");
	std::cout << static_cast<char>(50) << std::endl;
	
	Statement *s = prepareArguments(argc, argv);
	char * filename = createFilename(argv[1], argv[argc-1]);
	s->createFile(filename, int(argv[argc-1])); //not sure if cast works with more than one digit
	return 0;
}

