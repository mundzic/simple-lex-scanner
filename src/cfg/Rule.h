/*
 * rule.h
 *
 *  Created on: Feb 13, 2015
 *      Author: Zahida
 */

#ifndef RULE_H_
#define RULE_H_

#include <string>
#include <vector>
#include <map>

#include <iostream>

using std::map;
using std::vector;
using std::string;

using std::cout;
using std::endl;

template<class SymbolType>
class GrammerRulePlain : public vector<SymbolType> {};


template<class SymbolType>
class GrammarRule
{
public:

    GrammarRule(GrammerRulePlain<SymbolType> pr, map<SymbolType, string>& debug_map)
    : rule_id(id_count++)
    , dot_pos(1)
    , rule(pr)
    , has_lookahead_token(false)
    , symbol_debug_map(debug_map)
    {

    }

    void printRule() const
    {
        for(unsigned jj=0; jj< rule.size(); jj++)
        {
            if (jj==1) cout << "->";
            if (dot_pos == jj) cout << ".";
            cout << symbol_debug_map[rule[jj]];
            //cout << rule[jj];
        }
        cout << " lh_token: ";
        if (has_lookahead_token) cout << symbol_debug_map[lookahead_tokens.back()]; else cout << "no_lookahead_token";
        if (has_lookahead_token)
            for(unsigned ii=0; ii< lookahead_tokens.size(); ii++)
                cout << "[ " << symbol_debug_map[lookahead_tokens[ii]] << " ]";
        cout << " (r" << rule_id << ")"<< endl;
    }

    unsigned size() const { return rule.size(); }
    SymbolType head() const { return rule[0]; }
    SymbolType end() const { return rule[rule.size()-1]; }
    SymbolType dot() const { return dot_pos < rule.size() ? rule[dot_pos] : rule[dot_pos-1]; }
    //SymbolType lookahead() { return rule[dot_pos+1]; }

    bool shift() { return dot_pos < rule.size() ? dot_pos++ : false; }
    void add_lookahead(GrammarRule<SymbolType> forRule)
    {
        if (forRule.has_lookahead_token)
        {
            lookahead_tokens.push_back(forRule.lookahead_tokens.back());
            has_lookahead_token = true;
        }

        if (forRule.dot_pos+1 < forRule.rule.size())
        {
            lookahead_tokens.push_back(forRule.rule[forRule.dot_pos+1]);
            has_lookahead_token = true;
        }
    }

    bool ended() const { return dot_pos >= rule.size(); }
    bool ends() const { return dot_pos == rule.size(); }
    unsigned id() const { return rule_id; }
    const GrammarRule& operator=(const GrammarRule<SymbolType>& other)
    {
        if (this != &other)
        {
            rule_id = other.rule_id;
            dot_pos = other.dot_pos;
            rule    = other.rule;

            has_lookahead_token = other.has_lookahead_token;
            lookahead_tokens = other.lookahead_tokens;

            symbol_debug_map = other.symbol_debug_map;
        }
        return *this;
    }

    friend bool operator==(const GrammarRule& l, const GrammarRule& r)
    {
        bool lookahead_same = false;
        if (l.has_lookahead_token && r.has_lookahead_token)
        {
            lookahead_same = l.lookahead_tokens.back() == r.lookahead_tokens.back();
        }
        else if ( !l.has_lookahead_token && !r.has_lookahead_token)
        {
            lookahead_same = true;
        }

        return l.rule_id == r.rule_id && l.dot_pos == r.dot_pos && lookahead_same;
    }
    friend bool operator<(const GrammarRule& l, const GrammarRule& r)
    {
        return l.rule_id < r.rule_id ? true :
               r.rule_id < l.rule_id ? false :
               l.dot_pos < r.dot_pos;
    }

private:
    static unsigned id_count;
    unsigned rule_id;
    unsigned dot_pos;
    GrammerRulePlain<SymbolType> rule;

    bool                has_lookahead_token;
    vector<SymbolType>  lookahead_tokens;

    map<SymbolType, string>& symbol_debug_map;
};

template<class SymbolType>
unsigned GrammarRule<SymbolType>::id_count = 0;






#endif /* RULE_H_ */
