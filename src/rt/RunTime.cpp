/*
 * RunTime.cpp
 *
 *  Created on: Apr 3, 2019
 *      Author: Sulejman
 */

#include <RunTime.h>
#include <Scanner.h>



RunTime::RunTime(const string& xfilename)
    : scanner(new Scanner(xfilename.c_str()))
{
    SourceFiles.push_back("calc.x");
    //srcFileList.push_back("errtest.x");
    //srcFileList.push_back("func.x");
    //srcFileList.push_back("frame.x");
    //srcFileList.push_back("main.x");
    //srcFileList.push_back("asmain.x");
    //srcFileList.push_back("assparam.x");
    //srcFileList.push_back("static.x");
    //srcFileList.push_back("prepost.x");
    //srcFileList.push_back("type.x");
    //srcFileList.push_back("assignment.x");
    //srcFileList.push_back("var_dec_def_tent.x");

    //SourceFiles.push_back("statement.x");

    //srcFileList.push_back("externdeclA.x");
    //srcFileList.push_back("externdeclB.x");


    //SourceFiles.push_back("var_dec_def.x");
    //SourceFiles.push_back("pointer.x");
}

RunTime::~RunTime()
{
    delete scanner;
}


int RunTime::exec()
{
	int retValue = 0;

	cout << "RunTime::main(): ..........................:"<< retValue << endl;

	return retValue;
}

int RunTime::run()
{
    for (auto file : SourceFiles)
    {
    	//ProgramCtx = CeeLang(file, ProgramCtx).parse();
    }

    while (scanner->token_tag() != eof)
    {
    	scanner->token_text();
        scanner->step();
    }
    
    return exec();
}

