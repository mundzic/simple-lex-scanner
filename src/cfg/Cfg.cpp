/*
 * Cfg.cpp
 *
 *  Created on: 14.04.2015
 *      Author: Sulejman
 */



#include <Cfg.h>
#include <KernelBuilder.h>

using namespace std;

Cfg*        Cfg::cfg = 0;
//const char* Cfg::cfg_file_name = "src/cfg/c_grammar.cfg";
const char* Cfg::cfg_file_name = "cfg/c_grammar.cfg";
//const char* Cfg::cfg_file_name = "c_grammar.cfg";


Cfg& Cfg::instance()
{
	if(!cfg)
	{
		KernelBuilder::build_kernel_tables();
	}
	return *cfg;
}


void Cfg::init_lexer_tables()
{
    map<int, string>::const_iterator it = symbol_id2string_map.begin();
    while (it != symbol_id2string_map.end())
    {
        symbol_name2id_map[it->second] = it->first;
        if (it->second[0] == '\'')
        {
            symbol_key_name2id_map[it->second.substr(1, it->second.size()-2)] = it->first;
        }
        it++;
    }
}


SymbolCode  Cfg::symbol_code(const string& symbolName) const
{
    map<string, int>::const_iterator it = symbol_key_name2id_map.find(symbolName);
    return it != symbol_key_name2id_map.end() ? it->second : -1;
}

int  Cfg::nonterminal_code(const string& name) const
{
    map<string, int>::const_iterator it = symbol_name2id_map.find(name);
    return it != symbol_name2id_map.end() ? it->second : -1;
}

const char* Cfg::symbol_name(SymbolCode sc) const
{
    map<int, string>::const_iterator it = symbol_id2string_map.find(sc);
    return it != symbol_id2string_map.end() ? it->second.c_str() : 0;
}

