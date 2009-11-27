#ifndef _STATEMENT_
#define _STATEMENT_


class Statement {
	private:
		char * table_name;
		char ** attributes;
		char ** types;

		char * getAsString();
		int getRandomInt(int);
		char * getRandomString(int);
	public:
		Statement(char *, vector<char*>, vector<char*>, vector<int> lengths);
		bool createFile(char *, int);
};

#endif
