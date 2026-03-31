// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> st;
    std::string out;
    std::map<char, int> prec;
    prec['+'] = 1;
    prec['-'] = 1;
    prec['*'] = 2;
    prec['/'] = 2;
    prec['('] = 0;

    size_t i = 0;
    size_t len = inf.length();
    while (i < len) {
        char c = inf[i];
        if (std::isdigit(c)) {
            std::string num;
            while (i < len && std::isdigit(inf[i])) {
                num += inf[i];
                ++i;
            }
            if (!out.empty()) out += ' ';
            out += num;
            continue; // i уже увеличено
        } else if (c == '(') {
            st.Push(c);
        } else if (c == ')') {
            while (!st.IsEmpty() && st.Top() != '(') {
                if (!out.empty()) out += ' ';
                out += st.Pop();
            }
            if (!st.IsEmpty() && st.Top() == '(') st.Pop();
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!st.IsEmpty() && st.Top() != '(' && prec[st.Top()] >= prec[c]) {
                if (!out.empty()) out += ' ';
                out += st.Pop();
            }
            st.Push(c);
        }
        ++i;
    }

    while (!st.IsEmpty()) {
        if (!out.empty()) out += ' ';
        out += st.Pop();
    }
    return out;
}

int eval(const std::string& post) {
    TStack<int, 100> st;
    std::stringstream ss(post);
    std::string token;
    while (ss >> token) {
        if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
            int b = st.Pop();
            int a = st.Pop();
            int res;
            switch (token[0]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
                default: res = 0;
            }
            st.Push(res);
        } else {
            st.Push(std::stoi(token));
        }
    }
    return st.Pop();
}
