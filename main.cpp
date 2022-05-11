#include <iostream>
#include <cstring>

using namespace std;
const int LEN = 80;
const int MAX = 40;

class Stack {
private:
    char st[MAX];
    int top;
public:
    Stack() {
        top = 0;
    }

    void push(char var) {
        st[++top] = var;
    }

    char pop() {
        return st[top--];
    }

    int getTop() {
        return top;
    }
};

class Expression {
private:
    Stack s;
    char *pStr;
    int len;
public:
    Expression(char *ptr) {
        pStr = ptr;
        len = strlen(pStr);
    }

    void parse();

    int solve();
};

void Expression::parse() {
    char ch;
    char lastVal;
    char lastTop;
    for (int i = 0; i < len; ++i) {
        ch = pStr[i];
        if (ch >= '0' && ch <= '9')
            s.push(ch - '0');
        else if (ch == '*' || ch == '/' || ch == '+' || ch == '-') {
            if (s.getTop() == 1)
                s.push(ch);
            else {
                lastVal = s.pop();
                lastTop = s.pop();
                if ((ch == '*' || ch == '/') && (lastTop == '+' || lastTop == '-')) {
                    s.push(lastTop);
                    s.push(lastVal);
                } else {
                    switch (lastTop) {
                        case '+':
                            s.push(s.pop() + lastVal);
                            break;
                        case '-':
                            s.push(s.pop() - lastVal);
                            break;
                        case '*':
                            s.push(s.pop() * lastVal);
                            break;
                        case '/':
                            s.push(s.pop() / lastVal);
                            break;
                        default:
                            cout << "Unknown Operator";
                            exit(1);
                    }
                }
                s.push(ch);
            }
        } else {
            cout << "Unknown Value";
            exit(1);
        }
    }
}

int Expression::solve() {
    char lastVal;
    while (s.getTop() > 1)
    {
        lastVal = s.pop();
        switch (s.pop()) {
            case '+':
                s.push(s.pop() + lastVal);
                break;
            case '-':
                s.push(s.pop() - lastVal);
                break;
            case '*':
                s.push(s.pop() * lastVal);
                break;
            case '/':
                s.push(s.pop() / lastVal);
                break;
            default:
                cout << "Unknown Operator";
                exit(1);
        }
    }
    return int (s.pop());
}

int main() {

    char ans;
    char string[LEN];
    cout << "\n Input expression as \'2 + 4*3 - 8/4\'";

    do {
        cout << "\n Expression: ";
        cin >> string;
        Expression* exp = new Expression(string);
        exp->parse();
        cout << "\n Result: " << exp->solve();
        delete exp;
        cout << "\nRepeat? (y/n)";
        cin >> ans;
    } while (ans == 'y');
    return 0;
}
