#include<iostream>
#include "statement.H"
#include<vector>

void usage(char * erromsg) {
	std::cout << erromsg << std::endl;
	std::cout << "USAGE: ./random-mysql-generator <tablename> <attr1> <type1> [<size1>] [<attr2> <type2> [<size2>]...] <number_of_entries>" << std::endl;
	std::cout << "Where type = {integer, string}" << std::endl;
	std::cout << "size only needed it type=string" << std::endl;
	std::cout << "outputfile will be \"insert_<tablename>_<nrOfEntries>" << std::endl;
	exit(1);
}

Statement * prepareArguments(int argc, char ** argv) {
	char * tablename = argv[0];
	vector<char*> attributes;
	vector<char*> types;
	vector<int> lengths;
	for(int i=1; i<argc-1; ++i) {  //-1 because there are pairs // i=1 because it starts with the secand parameter
		attributes.push_back(argv[i++]); //i++ -> set i to type
		switch(argv[i]) {
			case "integer":
				types.push_back("integer");
				break;
			case "string":
				types.push_back("string");
				lengths.push_back(argv[++i]); //if string get length
				break;
			default:
				usage("Invalid parameters!");
		}
	}
	Statement s = new Statement(tablename, attributes, types, lengths); //kopierkonstrutkor used...
	return s;
}

char * createFilename(char * tablename, char * nrOfEntries) {
	int len = strlen(tablename);
	len += strlen(nrOfEntries);
	len += 7; //=strlen("insert_") + strlen("_")
	char * filename = new char[len];
	filename = "insert_" << tablename << "_" << nrOfEntries;
	return filename;
}

int main(int argc, char ** argv) {
	if(argc < 4) usage("To few parameters!");
	
	Statement *s = prepareArguments(argc, argv);
	char * filename = createFilename(argv[0], argv[argc-1]);
	s->createFile(filename, int(argv[argc-1])); //not sure if cast works with more than one digit

	return 0;
}

