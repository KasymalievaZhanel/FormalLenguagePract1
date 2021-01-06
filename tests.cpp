#include <gtest/gtest.h>
#include <headers.h>
#include <vector>

TEST(ClassinputTest, IsValidTest) {
    datainput data1("abcda*..*", 'c', 22);
    datainput data2("bbc+a*..*", 'c', 22);
    datainput data3("cabc.+.*", 'k', 22);

    EXPECT_EQ(data1.isValid(), false);
    EXPECT_EQ(data2.isValid(), true);
    EXPECT_EQ(data3.isValid(), false);
}

TEST(UsefulFunctionsTest, IsLetterOr1Test) {
    EXPECT_EQ(IsLetter('a'), true);
    EXPECT_EQ(IsLetter('b'), true);
    EXPECT_EQ(IsLetter('c'), true);
    for (int i = 1; 'c' + i <= 'z'; ++i) {
        EXPECT_EQ(IsLetterOr1('c' + i), false);
    }
    for (int i = 0; 'A' + i <= 'Z'; ++i) {
        EXPECT_EQ(IsLetterOr1('A' + i), false);
    }
}


TEST(UsefulFunctionsTest, getTopTwiceTest) {
    std::stack<std::vector<bool>> st;
    std::vector<bool> v1 = {false, true};
    std::vector<bool> v2 = {false, false};
    std::vector<bool> v3 = {true, true};
    st.push(v1);
    EXPECT_ANY_THROW(GetTopTwice(st));
    st.push(v2);
    st.push(v3);
    auto res = GetTopTwice(st);
    std::pair<std::vector<bool>, std::vector<bool>> predicted_res = {v3, v2};
    EXPECT_EQ(res, predicted_res);
}

#include <random>
std::mt19937 rnd;

TEST(ExprTest, ORTest) {
    for (int i = 1; i < 100; ++i) {
        int expr_len = 50;
        std::vector<bool> expr1(expr_len, false), expr2(expr_len, false);
        for (int j = 0; j < expr_len; ++j) {
            expr1[j] = rnd() % 2;
            expr2[j] = rnd() % 2;
        }
        auto res = _or(expr1, expr2);
        for (int j = 0; j < expr_len; ++j) {
            EXPECT_EQ(res[j], (expr1[j] | expr2[j]));
        }
    }
}

TEST(ExprTest, MULLTest) {
    for (int i = 1; i < 100; ++i) {
        int expr_len = 35;
        std::vector<bool> expr1(expr_len, false), expr2(expr_len, false);
        for (int j = 0; j < expr_len; ++j) {
            expr1[j] = rnd() % 2;
            expr2[j] = rnd() % 2;
        }
        auto res = _mul(expr1, expr2);
        for (int n = 0; n < expr_len; ++n) {
            bool flag = true;
            for (int j = 0; j <= n; ++j) {
                if (expr1[j] && expr2[n - j]) {
                    EXPECT_EQ(res[n], true);
                    flag = false;
                }
            }
            if (flag) {
                EXPECT_EQ(res[n], false);
            }
        }
    }
}

TEST(ExprTest, IterTest) {
    int expr_len = 50;
    for (int i = 1; i < expr_len; ++i) {
        std::vector<bool> expr(expr_len, false);
        expr[i] = true;
        auto res = _iter(expr);
        for (int j = 0; j < expr_len; ++j) {
            if (j % i == 0) {
                EXPECT_EQ(res[j], true);
            } else {
                EXPECT_EQ(res[j], false);
            }
        }
    }
    std::vector<bool> expr(expr_len, false);
    expr[0] = true;
    auto res = _iter(expr);
    for (int j = 1; j < expr_len; ++j) {
        EXPECT_EQ(res[j], false);
    }
}

TEST(RegTest, PushLetterOr1Test) {
    std::stack<std::vector<bool>> result_reg_stack;
    datainput data("ababa", 'a', 3);
    push_letter(result_reg_stack, 'a', data);
    EXPECT_EQ(result_reg_stack.size(), 1);
    EXPECT_EQ(result_reg_stack.top().size(), 4);
    EXPECT_EQ(result_reg_stack.top()[0], false);
    EXPECT_EQ(result_reg_stack.top()[1], true);

    push_letter(result_reg_stack, 'b', data);
    EXPECT_EQ(result_reg_stack.size(), 2);
    EXPECT_EQ(result_reg_stack.top().size(), 4);
    EXPECT_EQ(result_reg_stack.top()[0], true);
    EXPECT_EQ(result_reg_stack.top()[1], false);
}

TEST(RegTest, ORTest) {
    for (int i = 1; i < 100; ++i) {
        int expr_len = 45;
        std::vector<bool> expr1(expr_len, false), expr2(expr_len, false);
        for (int j = 0; j < expr_len; ++j) {
            expr1[j] = rnd() % 2;
            expr2[j] = rnd() % 2;
        }
        std::stack<std::vector<bool>> reg_st;
        reg_st.push(expr1);
        reg_st.push(expr2);
        OR(reg_st);
        EXPECT_EQ(reg_st.size(), 1);
        for (int j = 0; j < expr_len; ++j) {
            EXPECT_EQ(reg_st.top()[j], (expr1[j] | expr2[j]));
        }
    }
}

TEST(RegTest, MULLTest) {
    for (int i = 1; i < 100; ++i) {
        int expr_len = 20;
        std::vector<bool> expr1(expr_len, false), expr2(expr_len, false);
        for (int j = 0; j < expr_len; ++j) {
            expr1[j] = rnd() % 2;
            expr2[j] = rnd() % 2;
        }
        std::stack<std::vector<bool>> reg_st;
        reg_st.push(expr1);
        reg_st.push(expr2);
        MULL(reg_st);
        EXPECT_EQ(reg_st.size(), 1);
        for (int n = 0; n < expr_len; ++n) {
            for (int j = 0; j <= n; ++j) {
                if (expr1[j] && expr2[n - j]) {
                    EXPECT_EQ(reg_st.top()[n], true);
                }
            }
        }
    }
}

TEST(RegTest, IterTest) {
    int expr_len = 50;
    for (int i = 1; i < expr_len; ++i) {
        std::stack<std::vector<bool>> reg_st;
        EXPECT_ANY_THROW(regIter(reg_st));
        std::vector<bool> expr(expr_len, false);
        expr[i] = true;
        reg_st.push(expr);
        ITER(reg_st);
        for (int j = 0; j < expr_len; ++j) {
            if (j % i == 0) {
                EXPECT_EQ(reg_st.top()[j], true);
            } else {
                EXPECT_EQ(reg_st.top()[j], false);
            }
        }
    }
}


TEST(AlgoTest, TaskTest) {
    datainput data("ab+c.aba.∗.bac.+.+∗", 'a', 2);
    EXPECT_EQ(getAnswer(data), true);
    datainput data1("ab.a+c.a.", 'a', 2);
    EXPECT_EQ(getAnswer(data1), true);
    data1.symbCount = 1;
    EXPECT_EQ(getAnswer(data1), false);
    data1.symbCount = 3;
    EXPECT_EQ(getAnswer(data1), false);
    datainput data2("ab.a+c.a.*a.b.a+", 'a', 1);
    EXPECT_EQ(getAnswer(data2), true);
    data2.symbCount = 2;
    EXPECT_EQ(getAnswer(data2), false);
    data2.symbCount = 115;
    EXPECT_EQ(getAnswer(data2), true);
    datainput data3("aab.*c+a.*ab.+.c.", 'a', 2);
    EXPECT_EQ(getAnswer(data3), true);
    data3.symbCount = 161;
    EXPECT_EQ(getAnswer(data3), true);
    data3.symbCount = 0;
    EXPECT_EQ(getAnswer(data3), false);
}
