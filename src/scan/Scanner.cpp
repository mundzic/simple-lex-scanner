/*
 * Scaner.cpp
 *
 *  Created on: 13.04.2015
 *      Author: Sulejman
 */

#include <iostream>

#include <Scanner.h>
#include <Cfg.h>
#include <KernelBuilder.h>

#include <iostream>


Scanner::Scanner(const char* xfile)
	: cfg(Cfg::instance())
    , xfilename(xfile)
    , infile(xfile)
    , tokenCount(0)
    , lineCount(1)
    , columnCount(1)
{

    if(!infile)
    {
        cout << "no input file!" << endl;
    }
    get_ansii_symbol();  //get lookahead symbol
    get_ansii_symbol();  //get current symbol
    step();              //get lookahead token
    step();              //get current token
}

Scanner::~Scanner(void){}

void Scanner::error(const string& msg)
{
    fault_reporter(msg.c_str(), "ERROR");
}
void Scanner::warning(const string& msg)
{
    fault_reporter(msg.c_str(), "WARNING");
}
void Scanner::info(const string& msg)
{
    fault_reporter(msg.c_str(), "INFO");
}

void Scanner::fault_reporter(const char* msg, const char* severity)
{
    const char*  srcFilename = xfilename.c_str();

    unsigned     lineNo      = curr_TokenPtr->line;
    unsigned     columnNo    = curr_TokenPtr->startColumn;

    const char*  cursorText   = curr_TokenPtr->value.c_str();
    const char*  atModifier  = "before";

    const char*  inMsg       = msg;

    fprintf(stdout, "[%s:[%d]:[%d]] %s @ %s \'%s\' cause: %s\n", srcFilename,
            lineNo, columnNo, severity, atModifier, cursorText, inMsg);
    flush(cout);
}

void Scanner::step()
{
    prev_TokenPtr      =  curr_TokenPtr;
    curr_TokenPtr      =  lookahead_TokenPtr;
    lookahead_TokenPtr = &tokens[(tokenCount)%TOKBUFF_SIZE];

    do
    {
        while ( curr_SymbolValue == '/'           &&
                lookahead_SymbolType != eofsymb   &&
                ( lookahead_SymbolValue == '*' || lookahead_SymbolValue == '/'  )  )
            skip_comment();

        lookahead_TokenPtr->reinit(curr_tokenLine, curr_tokenColumn);

        get_program_token();
    } while (lookahead_TokenPtr->type.tag == delimiter);

    tokenCount++;
}

bool Scanner::accept(TokenTag tag)
{
    if (curr_TokenPtr->type.tag == tag)
    {
        step();
        return true;
    }
    return false;
}

bool Scanner::accept(const char* key)
{
    if (curr_TokenPtr->value == key)
    {
        step();
        return true;
    }
    return false;
}

bool Scanner::expect(TokenTag tag)
{
    if (accept(tag))
        return true;
    error(tag, "");
    return false;
}

bool Scanner::expect(const char* key)
{
    if (string(key) == "")
        return false;
    if (accept(key))
        return true;
    error(err, key);
    return false;
}

/*
 *
 *
 * PRIVATE METHODS IMPLEMENTING UNA LEXER
 *
 *
 */

//expect error message generating handler
void Scanner::error(TokenTag tag, const string& msg)
{
    const char*  srcFilename = xfilename.c_str();

    unsigned     lineNo      = prev_TokenPtr->line;
    unsigned     columnNo    = prev_TokenPtr->endColumn;

    const char*  inputText   = prev_TokenPtr->value.c_str();

    string       errMsg      = "place holder should never be printed out";

    if (tag == identifier)
    {
        errMsg = "identifier expected";
    }
    else if (tag == eof)
    {
        errMsg = "parse error: preterm end of input expected";
    }
    else if (tag == err && msg == "")  // else if (msg == "")
    {
        //delivered using expect() error message reporting canal
        //redirect to conventional error message handler
        error("unexpected token");
        return;
    }
    else if (tag == err && msg != "")
    {
        errMsg = "\'" + msg + "\'" + " expected";
    }
    else //handle expect() requests requested by character string
    {
        if (cfg.symbol_code(msg) != -1)
            errMsg = "syntax error: expected syntax construct (token) \'" + msg + "\' missing";
        else
            errMsg = "parse error: \'" + msg + "\' grammar unconfirming token";
    }

    fprintf(stdout, "[%s:[%d]:[%d]] ERROR @ following \'%s\' cause: %s\n",
            srcFilename, lineNo, columnNo, inputText, errMsg.c_str());
    flush(cout);
}

int Scanner::accept(ANSII_SymbolType t)
{
    if (curr_SymbolType == t)
    {
        get_ansii_symbol();
        return 1;
    }
    return 0;
}

void Scanner::skip_comment()
{
    if (lookahead_SymbolValue == '*')
    {
        skip_multiline_comment();
    }
    else if(lookahead_SymbolValue == '/')
    {
        skip_singleline_comment();
    } else /* not a comment */;
}

void Scanner::skip_multiline_comment()
{
    get_ansii_symbol();
    do
    {
        get_ansii_symbol();
    }
    while( !(curr_SymbolValue == '*' && lookahead_SymbolValue == '/') && curr_SymbolType != eofsymb);

    get_ansii_symbol(); // get lookahead to current
    get_ansii_symbol(); // move read-head ahead
}

void Scanner::skip_singleline_comment()
{

    get_ansii_symbol();
    do
    {
        get_ansii_symbol();
    }
    while( !(curr_SymbolValue == '\n') && !(curr_SymbolType == eofsymb));
    get_ansii_symbol(); //move read-head ahead
}

void Scanner::get_delimiter()
{
    do
    {
        if (curr_SymbolType == blanksymb)
            lookahead_TokenPtr->value += curr_SymbolValue;
    }
    while ( accept(blanksymb) );
}


void Scanner::get_constant_number()
{
    lookahead_TokenPtr->type.tag = integer;

    while ( curr_SymbolType == digitsymb || (curr_SymbolValue == '.' && lookahead_TokenPtr->type.tag == integer ) )
    {
        lookahead_TokenPtr->value += curr_SymbolValue;
        if (curr_SymbolValue == '.')
        {
            //cout << "Scanner::get_constant_number(): REAL" << endl;
            lookahead_TokenPtr->type.tag = real;
        }
        get_ansii_symbol();
    }
}

void Scanner::get_symbols_token()
{
    do
    {
        if (curr_SymbolType == operatorsymb)
            lookahead_TokenPtr->value += curr_SymbolValue;
    }
    while ( accept(operatorsymb) );
}

void Scanner::get_string_token()
{
    do
    {
        if (curr_SymbolType == alphasymb)
            lookahead_TokenPtr->value += curr_SymbolValue;
    }
    while ( accept(alphasymb) );
}


void Scanner::get_program_token()
{
    lookahead_TokenPtr->value += curr_SymbolValue;

    if (accept(blanksymb))
    {
        get_delimiter();
        lookahead_TokenPtr->type.tag = delimiter;
        lookahead_TokenPtr->type.code = -1;
    }
    else if (accept(alphasymb))
    {
        get_string_token();
        lookahead_TokenPtr->type.code = cfg.symbol_code(lookahead_TokenPtr->value);
        if (lookahead_TokenPtr->type.code != -1)
        {
            lookahead_TokenPtr->type.tag  = keyword;
        }
        else
        {
            lookahead_TokenPtr->type.tag = identifier;
        }
    }
    else if (accept(digitsymb))
    {
        get_constant_number();
        //curr_TokenPtr->type.tag = integer;
        lookahead_TokenPtr->type.code = -1;
    }
    else if (accept(operatorsymb))
    {
        get_symbols_token();
        SymbolCode code = cfg.symbol_code(lookahead_TokenPtr->value);

        if (code != -1)
        {
            lookahead_TokenPtr->type.tag  = keyword;
            lookahead_TokenPtr->type.code = code;
        }
        else
        {
            //consider using assert in this place
            lookahead_TokenPtr->type.tag = err;
            lookahead_TokenPtr->type.code = code;
        }
    }
    else if (accept(separatorsymb))
    {
        SymbolCode code = cfg.symbol_code(lookahead_TokenPtr->value);

        if (code != -1)
        {
            lookahead_TokenPtr->type.tag  = keyword;
            lookahead_TokenPtr->type.code = code;
        }
        else
        {
            lookahead_TokenPtr->type.tag = err;
            lookahead_TokenPtr->type.code = code;
        }

    }
    else if (accept(eofsymb))
    {
        lookahead_TokenPtr->type.tag = eof;
        lookahead_TokenPtr->type.code = -1;
    }
    else
    {
        lookahead_TokenPtr->type.tag = err;
        error("get_program_token: syntax error");
        cout << lookahead_TokenPtr->value << endl;
        get_ansii_symbol();
    }

    if (lookahead_TokenPtr->line == curr_tokenLine)
        lookahead_TokenPtr->endColumn = curr_tokenColumn;
    else
        lookahead_TokenPtr->endColumn = prev_tokenColumn;
}


void Scanner::get_ansii_symbol(void)
{

    curr_SymbolValue = lookahead_SymbolValue;
    curr_SymbolType  = lookahead_SymbolType;

    curr_tokenLine   = lineCount;
    prev_tokenColumn = curr_tokenColumn + 1;  //account for new line symbol '\n' count
    curr_tokenColumn = columnCount - 2; //account for column counter advanced 1 step by 'lineCount' post-increment and 1 for new line '\n' token

    while( infile.get(lookahead_SymbolValue) )
    {
        switch (lookahead_SymbolValue)
        {
            case '\n':
                lineCount++; columnCount=1;
                lookahead_SymbolType = blanksymb;
                break;
            case '\t': case '\r': case '\f': case ' ':
                lookahead_SymbolType = blanksymb;
                break;

            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                lookahead_SymbolType = digitsymb;
                break;

            case '=': case '+': case '-': case '*': case '/':
            case '%': case '<': case '>': case '|': case '&':
            case '~': case ':':
                lookahead_SymbolType = operatorsymb;
                break;

            case '(': case ')': case '{': case '}': case '[': case ']':
            case ';': case ',': case '?': case '!': case '.':
                lookahead_SymbolType = separatorsymb;
                break;

            default:
                if ( (lookahead_SymbolValue >= 'A' && lookahead_SymbolValue <= 'Z') ||
                     (lookahead_SymbolValue >= 'a' && lookahead_SymbolValue <= 'z')  )
                    lookahead_SymbolType = alphasymb;
                else
                    lookahead_SymbolType = errsymb;
                break;
        }
        columnCount++;
        return;
    }
    lookahead_SymbolType = eofsymb;
    return;
}


