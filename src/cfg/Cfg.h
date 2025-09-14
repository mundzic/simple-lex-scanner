/*
 * Cfg.h
 *
 *  Created on: 13.04.2015
 *      Author: Sulejman
 */

#ifndef CFG_H_
#define CFG_H_

#include <string>
#include <vector>
#include <map>

#include <Token.h> //RuleCode, SymbolCode
#include <Rule.h>

using std::map;
using std::vector;
using std::string;

class Cfg {
public:
  Cfg(void){}
  ~Cfg(void){ delete cfg; cfg = 0; }

  static Cfg& instance();

  int         kernel_size(void) const {return kernel_rules.size();}
  const char* symbol_name(SymbolCode sc) const;
  SymbolCode  symbol_code(const string& symbolName) const;
  int         nonterminal_code(const string& ntName) const;

private:
  friend class KernelBuilder;
  void init_lexer_tables();

  static Cfg*               cfg;
  static const char*        cfg_file_name;

  vector<vector<string> >   kernel_strings;
  map<int, string>          symbol_id2string_map;
  vector<GrammarRule<int> > kernel_rules;

  //lexical tables
  map<string, int>          symbol_name2id_map;
  map<string, int>          symbol_key_name2id_map;
};


#endif /* CFG_H_ */
