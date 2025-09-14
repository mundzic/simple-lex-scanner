/*
 * kernel_builder.h
 *
 *  Created on: Feb 18, 2015
 *      Author: Zahida
 */

#ifndef KERNEL_BUILDER_H_
#define KERNEL_BUILDER_H_

#include <fstream>
#include <string>
#include <vector>
#include <map>

#include <iostream>

#include "Rule.h"
#include "Cfg.h"

using std::map;
using std::vector;
using std::string;
using std::ifstream;

using std::cout;
using std::endl;

class KernelBuilder
{
public:

	static void build_kernel_tables()
	{
		Cfg::cfg = new Cfg();

		cout << "kernel_builder start :-)" << endl;

		KernelBuilder builder(Cfg::cfg_file_name, Cfg::cfg->kernel_rules,
				Cfg::cfg->symbol_id2string_map, Cfg::cfg->kernel_strings);
		builder.get_non_terminal_productions();
		builder.build_kernel_rules();

		Cfg::cfg->init_lexer_tables();

		builder.debug_table_printer();

		cout << "kernel_builder finish :-)" << endl;
	}

    static void build_kernel_tables(const string file_name,
    			vector<GrammarRule<int> >& kernel_table_map,
				map<int, string>&          token_id_debug_map,
				vector<vector<string> >&   kernel_table_debug_map)
    {
        cout << "kernel_builder start :-)" << endl;

        KernelBuilder builder(file_name, kernel_table_map,
        		token_id_debug_map, kernel_table_debug_map);
        builder.get_non_terminal_productions();
        builder.build_kernel_rules();

        builder.debug_table_printer();

        cout << "kernel_builder finish :-)" << endl;
    }

private:
    typedef enum
    {
        semicolon,
        colon,
        bar,
        identifier,
        eof
    } BNF_Token;

    KernelBuilder(const string& file_name,
                  vector<GrammarRule<int> >& kernel_table_map,
                  map<int, string>&          token_id_debug_map,
                  vector<vector<string> >&   kernel_table_debug_map)
    : curr_token(eof)
    , curr_svalue("")
    , infile(file_name.c_str())
    , curr_header("")
    , curr_rule(0)
    , kernel_rules_debug_map(kernel_table_debug_map)
    , token_id2string_map(token_id_debug_map)
    , kernel_rules(kernel_table_map)
    , token_id_count(0)
    {
        if(!infile) cout << "no input file!" << endl;
    }

    void build_kernel_rules()
    {
        for (unsigned ii=0; ii < kernel_rules_debug_map.size(); ii++)
        {
            GrammerRulePlain<int> rule;
            for (unsigned jj=0; jj < kernel_rules_debug_map[ii].size(); jj++)
            {
                rule.push_back(token_id_map[kernel_rules_debug_map[ii][jj]]);
            }
            kernel_rules.push_back(GrammarRule<int>(rule, token_id2string_map));
        }
    }

    void update_token_maps(const string& token)
    {
        curr_rule->push_back(token);
        if (token_id_map.find(token) == token_id_map.end())
        {
            token_id_map[token] = token_id_count;
            token_id2string_map[token_id_count] = token;
            token_id_count++;
        }
    }

    void error(const char msg[]) { cout << msg << endl; }

    void debug_printer()
    {
        cout << "curr_token: " << curr_token << endl;
        cout << "curr_svalue: " << curr_svalue << endl;
    }
    void debug_table_printer()
    {
        for (unsigned ii=0; ii < kernel_rules_debug_map.size(); ii++)
        {
            for (unsigned jj=0; jj < kernel_rules_debug_map[ii].size(); jj++)
            {
                if (jj==1) cout << "->";
                cout << kernel_rules_debug_map[ii][jj] << "/" << token_id_map[kernel_rules_debug_map[ii][jj]] << "/" " ";
            }
            cout << " (r" << ii << ")"<< endl;
        }
    }

    int accept(BNF_Token t)
    {
        if (curr_token == t)
        {
            get_token();
            return 1;
        }
        return 0;
    }

    int expect(BNF_Token t)
    {
        if (accept(t))
            return 1;
        error("expect: unexpected token");
        return 0;
    }


    void get_variable()
    {
        debug_printer();
        if (accept(identifier))
        {
            ;
        }
        else
        {
            error("get_variable: syntax error");
            get_token();
        }
    }

    void get_body()
    {
        do
        {
            if (curr_token == identifier)
                update_token_maps(curr_svalue);
            debug_printer();
        } while ( accept(identifier) );
    }


    void get_production_body_list()
    {
        kernel_rules_debug_map.push_back(vector<string>());
        curr_rule = &kernel_rules_debug_map.back();
        update_token_maps(curr_header);
        //curr_rule->push_back(curr_header);
        nonterminal_id_map[curr_header] = token_id_map[curr_header];
        get_body();
        if (accept(bar))
        {
            get_production_body_list();
        }
    }

    void get_productions()
    {
        curr_header = curr_svalue;
        get_variable();
        expect(colon);
        get_production_body_list();
    }

    void get_non_terminal_productions()
    {
        get_token();
        while (curr_token != eof)
        {
            get_productions();
            expect(semicolon);
        }
    }

    void get_token(void)
    {
        char ch;
        curr_svalue.clear();

        while( infile.get(ch) )
        {
            switch (ch)
            {
                case ';': curr_token = semicolon; return;
                case ':': curr_token = colon; return;
                case '|': curr_token = bar; return;
                case'\'': do curr_svalue.push_back(ch);
                              while (infile.get(ch) && ch != '\'') ;
                             //while (infile.get(ch) && ch != '\'' && curr_svalue.back() != '\\')
                          curr_svalue.push_back(ch);
                          curr_token = identifier;
                          return;
                default:
                    if ( isalpha(ch) )
                    {
                        do
                        {
                            curr_svalue.push_back(ch);
                        } while (infile.get(ch) && (isalpha(ch) || (ch == '-')));
                        if (infile) infile.putback(ch);
                        curr_token = identifier;
                        return;
                    }
                    break;
            }
        }
        curr_token = eof;
        return;
    }


    BNF_Token                     curr_token;
    string                        curr_svalue;

    ifstream                      infile;

    string                        curr_header;
    vector<string>*               curr_rule;

    vector<vector<string> >&      kernel_rules_debug_map;
    map<int, string>&             token_id2string_map;
    vector<GrammarRule<int> >&    kernel_rules;

    int                           token_id_count;
    map<string, int>              token_id_map;

    map<string, int>              terminal_id_map;
    map<string, int>              nonterminal_id_map;
};



#endif /* KERNEL_BUILDER_H_ */
