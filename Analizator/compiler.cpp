#include "Token.h"
#include "Scaner.h"
#include <iostream>
#include <string>

#include <fstream>


int main() 
{
	ifstream ifile("myprog.txt");
	Scanner scanner(ifile);
	for (;;) 
	{
		Token currentLexem = scanner.getNextToken();
		currentLexem.print(cout);
		if (currentLexem.type() == LexemType::error
			|| currentLexem.type() == LexemType::eof)
		{
			break;
		}
	}
}