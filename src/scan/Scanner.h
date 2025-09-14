/*
 * Scenner.h
 *
 *  Created on: 13.04.2015
 *      Author: Sulejman
 */

#ifndef SCENNER_H_
#define SCENNER_H_

#include <string>
#include <fstream>

#include "../cfg/Cfg.h"
#include "Token.h"

using std::string;
using std::ifstream;



class Scanner
{

public:
  Scanner(const char* xfile);
  virtual ~Scanner(void);

  void   step(void);

  bool   accept(TokenTag tag);
  bool   accept(const char* key);

  bool   expect(TokenTag tag);
  bool   expect(const char* key);


  const Token&  token(void)  const { return *curr_TokenPtr; }
  TokenTag      token_tag(void) const  { return curr_TokenPtr->type.tag; }
  const string& token_text(void) const { return curr_TokenPtr->value; }

  const Token&  lookahead_token(void) const { return *lookahead_TokenPtr; }
  TokenTag      lookahead_tag(void) const { return lookahead_TokenPtr->type.tag; }
  const string& lookahead_text(void) const { return lookahead_TokenPtr->value; }


  virtual void error(const string& msg);
  virtual void warning(const string& msg);
  virtual void info(const string& msg);

private:
  typedef enum
  {
    blanksymb,
    alphasymb,
    digitsymb,
    //punctuatorsym
    operatorsymb,
    separatorsymb,
    errsymb,
    eofsymb
  } ANSII_SymbolType;

  typedef const unsigned buffsize_t;

  void fault_reporter(const char* msg, const char* severity = "ERROR");
  void error(TokenTag tag, const string& msg);
  int  accept(ANSII_SymbolType t);
  void get_ansii_symbol(void);
  void get_program_token();

  void skip_comment();
  void skip_multiline_comment();
  void skip_singleline_comment();
  void get_delimiter();
  void get_constant_number();
  void get_symbols_token();
  void get_string_token();

  const Cfg&       cfg;
  const string     xfilename;

  ifstream         infile;

  ANSII_SymbolType curr_SymbolType;
  char             curr_SymbolValue;
  ANSII_SymbolType lookahead_SymbolType;
  char             lookahead_SymbolValue;

  Token*           lookahead_TokenPtr;
  Token*           curr_TokenPtr;
  Token*           prev_TokenPtr;

  static
  const
  unsigned         TOKBUFF_SIZE = 5;
  Token            tokens[TOKBUFF_SIZE];
  unsigned         tokenCount;


  unsigned         curr_tokenLine;
  unsigned         curr_tokenColumn;
  unsigned         prev_tokenColumn;

  unsigned         lineCount;
  unsigned         columnCount;
};



#endif /* SCENNER_H_ */
