/*
 * RunTime.h
 *
 *  Created on: Apr 3, 2019
 *      Author: Sulejman
 */

#ifndef SRC_RUNTIME_H_
#define SRC_RUNTIME_H_


#include <Scanner.h>
#include <vector>

class RunTime
{
public:
    RunTime(const string& xfilename);
    ~RunTime();

    int       run();
    int       exec();
private:
    Scanner*       scanner;
    vector<string> SourceFiles;
};

#endif /* SRC_RUNTIME_H_ */
