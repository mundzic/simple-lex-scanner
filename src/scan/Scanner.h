/*
 * Scenner.h
 *
 *  Created on: 13.04.2015
 *      Author: Sulejman
 */

#ifndef SCENNER_H_
#define SCENNER_H_


#include <Token.h>
#include "Cfg.h"

#include <string>
#include <fstream>

using std::string;
using std::ifstream;

class Scanner
{

public:
  Scanner(const string& xfile);
  virtual ~Scanner(void);

  void   read_file(const string& xfile);

  void   step(void);

  bool   accept(TokenTag tag);
  bool   accept(const char* key);

  bool   expect(TokenTag tag);
  bool   expect(const char* key);

  typedef int TokenLocus;

  const Token&  token(TokenLocus tl = 0)  const     { return *curr_TokenPtr; }
  TokenTag      token_tag(TokenLocus tl = 0) const  { return curr_TokenPtr->type.tag; }
  const string& token_text(TokenLocus tl = 0) const { return curr_TokenPtr->value; }

  const Token&  lookahead_token() const { return *lookahead_TokenPtr; }
  TokenTag      lookahead_tag() const   { return lookahead_TokenPtr->type.tag; }
  const string& lookahead_text(void) const  { return lookahead_TokenPtr->value; }

  const Token&  lookbehind_token() const { return *prev_TokenPtr; }
  TokenTag      lookbehind_tag() const   { return prev_TokenPtr->type.tag; }
  const string& lookbehind_text() const  { return prev_TokenPtr->value; }


  const string& filename(void) const { return xfilename; }

  virtual void error(const string& msg, TokenLocus tl = 0);
  virtual void warning(const string& msg, TokenLocus tl = 0);
  virtual void info(const string& msg, TokenLocus tl = 0);

  Scanner* operator->() const { return (Scanner*)this; }


private:
  typedef enum
  {
    blanksymb,
    alphasymb,
    digitsymb,
    escapesym,
    operatorsymb,
    separatorsymb,
    errsymb,
    eofsymb
  } ANSII_SymbolType;

  typedef const unsigned buffsize_t;

  void start();
  void stop();
  void fault_reporter(const char* msg, const char* severity = "ERROR", TokenLocus token_locus = 0);
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

  const Cfg*       cfg;

  string           xfilename;
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

  //TODO: encapsulate it InputCursor
  unsigned         curr_tokenLine;
  unsigned         curr_tokenColumn;
  unsigned         prev_tokenColumn;

  unsigned         lineCount;
  unsigned         columnCount;
};



#endif /* SCENNER_H_ */
