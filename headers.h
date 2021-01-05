#ifndef TRY_NKA_H
#define TRY_NKA_H


#include <iostream>
#include <string>
#include <stack>
#include <vector>
using std::string, std::vector;

struct datainput {
    datainput(string &regularexpr, char symbol, int count);
    string regular;
    char symbol;
    int amount;
};

bool IsLetterOr1(char c);
bool IsOperation(char c);
bool IsValid(datainput);

datainput GetInput();
std::pair<vector<bool>, vector<bool>> GetTopTwice(std::stack<vector<bool>> &st);


void PushLetterOr1(std::stack<vector<bool>> &reg_st, char symb, datainput &input);
void OR(std::stack<vector<bool>> &result_reg_stack);
void MULL(std::stack<vector<bool>> &result_reg_stack);
void ITER(std::stack<vector<bool>> &result_reg_stack);

vector<bool> _or(vector<bool> &expr1, vector<bool> &expr2);
vector<bool> _mul(vector<bool> &expr1, vector<bool> &expr2);
vector<bool> _iter(vector<bool> &expr);

bool Result(datainput &data);

#endif
