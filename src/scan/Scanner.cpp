/*
 * Scaner.cpp
 *
 *  Created on: 13.04.2015
 *      Author: Sulejman
 */

#include <Scanner.h>
#include <iostream>


Scanner::Scanner(const string& xfile)
    : cfg(&Cfg::instance())
    , xfilename(xfile)
    , infile(xfile)
    , tokenCount(0)
    , lineCount(1)
    , columnCount(2)
{
    if(!infile)
    {
        error("no input file!");
    }

    prev_TokenPtr = curr_TokenPtr = lookahead_TokenPtr = &tokens[tokenCount];

    get_ansii_symbol();  //get lookahead symbol
    get_ansii_symbol();  //get current symbol
    step();              //get lookahead token
    step();              //get current token
}


Scanner::~Scanner(void)
{
    stop();
}

void Scanner::read_file(const string& xfile)
{
    if (infile.is_open())
        infile.close();

    tokenCount  = 0;
    lineCount   = 1;
    columnCount = 1;

    xfilename   = xfile;

    infile.open(xfile);

    start();
}

void Scanner::start(void)
{
    if(!infile)
    {
        error("no input file!");
    }
    else
    {
        get_ansii_symbol();  //get lookahead symbol
        get_ansii_symbol();  //get current symbol
        step();              //get lookahead token
        step();              //get current token
    }
}

void Scanner::stop(void)
{
    if (infile.is_open())
        infile.close();
}

void Scanner::error(const string& msg, TokenLocus tl)
{
    fault_reporter(msg.c_str(), "ERROR", tl);
}
void Scanner::warning(const string& msg, TokenLocus tl)
{
    fault_reporter(msg.c_str(), "WARNING", 0);
}
void Scanner::info(const string& msg, TokenLocus tl)
{
    fault_reporter(msg.c_str(), "INFO", tl);
}

void Scanner::fault_reporter(const char* msg, const char* severity, TokenLocus token_locus)
{
    const char*  srcFilename = xfilename.c_str();

    Token*       atToken    = token_locus == 1 ? lookahead_TokenPtr :
                              token_locus == 0 ? curr_TokenPtr : prev_TokenPtr;

    //const char*  atModifier = token_locus == 1 ? "before" :
    //                          token_locus == 0 ? "@" : "after";


    unsigned     lineNo      = atToken->line;
    unsigned     columnNo    = atToken->startColumn;

    const char*  cursorText  = atToken->value.c_str();
    const char*  atModifier  = "before";

    const char*  inMsg       = msg;


    FILE* out = stdout;

    fprintf(out, "[%s:[%d]:[%d]] %s @ %s \'%s\' cause: %s\n", srcFilename,
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
 * PRIVATE METHODS IMPLEMENTING C-SUBSET LEXER
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
        errMsg = "parser abrupt input stream processing";
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
        if (cfg->symbol_code(msg.c_str()) != -1)
            errMsg = "syntax error: expected syntax construct (token) \'" + msg + "\' missing";
        else
            errMsg = "parse error: \'" + msg + "\' grammar non conform token";
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
            lookahead_TokenPtr->type.tag = real;
        }
        get_ansii_symbol();
    }
}

void Scanner::get_symbols_token()
{
    int is_Keyword;
    do
    {
        is_Keyword = cfg->symbol_code((lookahead_TokenPtr->value + curr_SymbolValue).c_str()) != -1;

        if (curr_SymbolType == operatorsymb && is_Keyword)
            lookahead_TokenPtr->value += curr_SymbolValue;
    }
    while ( is_Keyword && accept(operatorsymb) );
}


void Scanner::get_string_token()
{

    while (curr_SymbolType == alphasymb || (curr_SymbolType == digitsymb))
    {
        lookahead_TokenPtr->value += curr_SymbolValue;
        get_ansii_symbol();
    }
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
        lookahead_TokenPtr->type.code = cfg->symbol_code(lookahead_TokenPtr->value.c_str());
        if (lookahead_TokenPtr->type.code != -1)
        {
            lookahead_TokenPtr->type.tag  = keyword;
        }
        else
        {
            lookahead_TokenPtr->type.tag = identifier;
        }
        lookahead_TokenPtr->endColumn = lookahead_TokenPtr->startColumn + lookahead_TokenPtr->value.size();
    }
    else if (accept(digitsymb))
    {
        get_constant_number();
        lookahead_TokenPtr->type.code = -1;
        lookahead_TokenPtr->endColumn = lookahead_TokenPtr->startColumn + lookahead_TokenPtr->value.size();
    }
    else if (accept(operatorsymb))
    {
        get_symbols_token();
        SymbolCode code = cfg->symbol_code(lookahead_TokenPtr->value.c_str());

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
        lookahead_TokenPtr->endColumn = lookahead_TokenPtr->startColumn + lookahead_TokenPtr->value.size();
    }
    else if (accept(separatorsymb))
    {
        SymbolCode code = cfg->symbol_code(lookahead_TokenPtr->value.c_str());
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
        lookahead_TokenPtr->endColumn = lookahead_TokenPtr->startColumn + lookahead_TokenPtr->value.size();
    }
    else if (accept(eofsymb))
    {
        lookahead_TokenPtr->type.tag = eof;
        lookahead_TokenPtr->type.code = -1;
    }
    else
    {
        lookahead_TokenPtr->type.tag  = err;
        lookahead_TokenPtr->type.code = -1;
        string errMsg = "\'" + lookahead_TokenPtr->value +  "\' stray input";
        fault_reporter(errMsg.c_str(), "WARNING", true);
        do
        {
            get_ansii_symbol();
        }
        while( (lookahead_SymbolType == errsymb) && !(lookahead_SymbolType == eofsymb));
        get_ansii_symbol(); //move read-head ahead
        get_program_token();

    }
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
            case '~': case ':': case '^': case '!': case '?':
            case '.':
                lookahead_SymbolType = operatorsymb;
                break;

            //separator symbols appear only in single symbol token
            //they can not be put together to build multiply symbol token
            case '(': case ')': case '{': case '}': case '[': case ']':
            case ';': case ',':
                lookahead_SymbolType = separatorsymb;
                break;

            default:
                if ( (lookahead_SymbolValue >= 'A' && lookahead_SymbolValue <= 'Z') ||
                     (lookahead_SymbolValue >= 'a' && lookahead_SymbolValue <= 'z') ||
                     (lookahead_SymbolValue == '_')                                  )
                    lookahead_SymbolType = alphasymb;
                else
                    lookahead_SymbolType = errsymb;
                break;
        }
        columnCount++;
        return;
    }
    lookahead_SymbolType = eofsymb;
    stop();
    return;
}


