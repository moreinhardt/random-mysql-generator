#ifndef _STATEMENT_
#define _STATEMENT_

#include<vector>

class Statement {
	private:
		char * table_name;
		std::vector<char*> attributes;
		std::vector<char*> types;
		std::vector<int> lengths;

		char * getAsString();
		int getRandomInt(int);
		char * getRandomString(int);
	public:
		Statement(char *, std::vector<char*>, std::vector<char*>, std::vector<int> lengths);
		bool createFile(char *, int);
};

#endif
