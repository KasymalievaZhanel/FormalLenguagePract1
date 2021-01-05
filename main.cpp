#include "headers.h"


int main() {
    datainput input = GetInput();
    if (Result(input)) {
        std::cout<< "Yes";
        return 0;
    }
    std::cout << "NO";
    return 0;
}


datainput::datainput(string &regularexpr, char symbol, int amount): symbol(symbol), amount(amount) {
    regular = std::move(regularexpr);
}

datainput GetInput() {
    string regularexpr;
    char symbol;
    int amount;
    std::cin >> regularexpr >> symbol >> amount;
    datainput data(regularexpr, symbol, amount);
    if (!IsValid(data)) {
        throw std::invalid_argument("ERROR: Invalid input");
    }
    return data;
}


bool IsValid(datainput input) {
    for (char expr_symb : input.regular) {
        if (!IsOperation(expr_symb) && !IsLetterOr1(expr_symb)) {
            return false;
        }
    }
    return IsLetterOr1(input.symbol);
}

bool IsLetterOr1(char expr_symb) {
    return expr_symb == 'a' || expr_symb == 'b' || expr_symb == 'c' || expr_symb == '1';
}

bool IsOperation(char expr_symb) {
    return expr_symb == '+' || expr_symb == '.' || expr_symb == '*';
}


bool Result(datainput &data) {
    std::stack<vector<bool>> result_reg_stack;
    for (char c : data.regular) {
        if (IsLetterOr1(c)) {
            PushLetterOr1(result_reg_stack, c, data);
        } else if (c == '+') {
            OR(result_reg_stack);
        } else if (c == '.') {
            MULL(result_reg_stack);
        } else if (c == '*') {
            ITER(result_reg_stack);
        }
    }

    if (result_reg_stack.size() != 1) {
        throw std::invalid_argument("ERROR: Invalid regular expression");
    }
    auto result = result_reg_stack.top();
    return result[data.amount];//k
}


void PushLetterOr1(std::stack<vector<bool>> &reg_st, char symb, datainput &input) {
    vector<bool> for_each_reg_symbol(input.amount + 1, false);//k+1
    if (symb == input.symbol) {
        for_each_reg_symbol[1] = true;
    } else {
        for_each_reg_symbol[0] = true;
    }
    reg_st.push(for_each_reg_symbol);
}


void OR(std::stack<std::vector<bool>> &result_reg_stack) {
    auto [expr1, expr2] = GetTopTwice(result_reg_stack);
    result_reg_stack.push(_or(expr1, expr2));
}

void MULL(std::stack<std::vector<bool>> &result_reg_stack) {
    auto [expr1, expr2] = GetTopTwice(result_reg_stack);
    result_reg_stack.push(_mul(expr1, expr2));
}

void ITER(std::stack<std::vector<bool>> &result_reg_stack) {
    if (result_reg_stack.empty()) {
        throw std::invalid_argument("Invalid regular expression");
    }
    auto expr = result_reg_stack.top();
    result_reg_stack.pop();
    result_reg_stack.push(_iter(expr));
}


std::vector<bool> _or(std::vector<bool> &expr1, std::vector<bool> &expr2) {
    std::vector<bool> expr_res(expr1.size(), false);
    for (int i = 0; i < expr1.size(); ++i) {
        expr_res[i] = expr1[i] | expr2[i];
    }
    return expr_res;
}

std::vector<bool> _mul(std::vector<bool> &expr1, std::vector<bool> &expr2) {
    std::vector<bool> expr_res(expr1.size(), false);
    for (int i = 0; i < expr1.size(); ++i) {
        for (int j = 0; j < expr2.size(); ++j) {
            if (expr1[i] && expr2[j] && i + j < expr1.size()) {
                expr_res[i + j] = true;
            }
        }
    }
    return expr_res;
}

std::vector<bool> _iter(std::vector<bool> &expr) {
    std::vector<bool> expr_res(expr.size(), false);
    expr_res[0] = true;
    for (int k = 0; k <= expr.size(); ++k) {
        auto step = _mul(expr_res, expr);
        expr_res = _or(expr_res, step);
    }
    return expr_res;
}


std::pair<vector<bool>, vector<bool>> GetTopTwice(std::stack<vector<bool>> &result_reg_stack) {
    if (result_reg_stack.size() < 2) {
        throw std::invalid_argument("ERROR: Invalid regular expression");
    }
    auto vec1 = result_reg_stack.top();
    result_reg_stack.pop();
    auto vec2 = result_reg_stack.top();
    result_reg_stack.pop();
    return {vec1, vec2};
}

