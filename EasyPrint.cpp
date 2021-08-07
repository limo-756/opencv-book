#include "bits/stdc++.h"
using namespace std;

#define IN(x,y) ((y).find((x))!=(y).end())

static inline std::string &trim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

set<char> openingBrackets = {'[', '{', '<', '('};
set<char> closingBrackets = {']', '}', '>', ')'};
vector<string> variableSplitter(const string &s) {
    stack<char> bracketHolder;
    vector<string> variables;
    string currentVariable;
    for (char var : s) {
        if (IN(var, openingBrackets)) {
            bracketHolder.push(var);
            currentVariable += var;
        } else if (IN(var, closingBrackets)) {
            bracketHolder.pop();
            currentVariable += var;
        } else if (var == ',' && bracketHolder.empty()) {
           variables.push_back(trim(currentVariable));
           currentVariable = "";
        } else {
            currentVariable += var;
        }
    }
    variables.push_back(trim(currentVariable));
    return variables;
}

void debug_out(
        vector<string> __attribute__ ((unused)) args,
        __attribute__ ((unused)) int idx,
        __attribute__ ((unused)) int LINE_NUM) { cerr << endl; }

template<typename Head, typename... Tail>

void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
    if (idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
    stringstream ss;
    ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, LINE_NUM, T...);
}

#define trace(...) debug_out(variableSplitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__);
