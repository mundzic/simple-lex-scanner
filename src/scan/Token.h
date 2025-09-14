/*
 * Token.h
 *
 *  Created on: 14.04.2015
 *      Author: Sulejman
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
#include <cstdio>

using std::string;

typedef int SymbolCode;
typedef int RuleCode;

typedef enum //TokenTag
{
    undefined,
    identifier,
    integer,
    real,
    keyword,
    literal,
    delimiter,
    err,
    eof
}TokenTag;

class MyTokenType
{
public:
    MyTokenType() : tag(undefined), code(-1) {}
    MyTokenType(TokenTag t, SymbolCode c) : tag(t), code(c) {}
    TokenTag   tag;
    SymbolCode code;
};

class Token
{
public:
    Token() : type(), value(""), line(0), startColumn(0), endColumn(0) {}
    ~Token() {}
    void reinit(unsigned ln, unsigned cl)
    {
        type.tag = undefined;
        type.code = -1;
        value.clear();
        line = ln;
        startColumn = cl;
        endColumn = cl;
    }

    MyTokenType  type;
    string       value;

    unsigned   line;
    unsigned   startColumn;
    unsigned   endColumn;
};


#endif /* TOKEN_H_ */
