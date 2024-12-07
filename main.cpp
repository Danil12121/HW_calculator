#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <stack>
#include <vector>
#include <deque>
#include <valarray>

using namespace std;

const double e = 2.71828;
struct item{
    char type; // 2 - знак +-*/(), 1 - число, 3 - операция qwrfy
               // q - sin, w - cos, r - tg, f - ctg, y - exp
    double dval;
    char cval;
    string sval;
};

int findErrors(const string& s){
    string numsF = "0123456789(qwrfy", numsL = "0123456789)", availible = "1234567890-+*/()qwrfyx";

    stack<char> stack1;
    for (char i: s)
        if (count(availible.begin(), availible.end(), i) == 0)
            return 5;
    if (count(numsF.begin(), numsF.end(), s[0]) == 0)// символ вначале
        return 1;
    if (count(numsL.begin(), numsL.end(), s[s.length()-1]) == 0)// символ вконце
        return 2;
    if (s.find("()") != string::npos)// проверка на пустые скобки
        return 3;
    for (char i: s){    //проверка правильности скобочной последовательности
        if (i == '(')
            stack1.push(i);
        if (i == ')') {
            if (stack1.empty())
                return 4;
            else
                stack1.pop();
        }
    }
    return 0;
}

void replaceFuncNames(string & s, const string& last, const string& modif){
    string::size_type index;
    while((index = s.find(last)) != std::string::npos)
        s.replace(index, last.size(), modif);
}

int makeVectorOfItems(const string& form, vector<item> &v){
    item prom{};
    string nums = "0123456789.";
    string znaks = "+-*/()";
    string operations = "qwrfy";
    for (char i : form){
        if (count(nums.begin(), nums.end(), i) != 0) {
            prom.sval += i;
            prom.type = 1;
        }
        if (count(operations.begin(), operations.end(), i) != 0){
            v.push_back(prom);
            prom = {};
            prom.type = 3;
            prom.cval = i;
            v.push_back(prom);
            prom = {};
        }
        if (count(znaks.begin(), znaks.end(), i) != 0) {
            if (!prom.sval.empty()) {
                if ((count(prom.sval.begin(), prom.sval.end(), '.') <= 1)) { //проверка, что в числе точек <= 1
                    prom.dval = stod(prom.sval);
                    prom.type = 1;
                } else {
                    cout << "Your formula is incorrect.";
                    return 1;
                }
            }

        v.push_back(prom);
        prom = {};
        prom.type = 2;
        prom.cval = i;
        v.push_back(prom);
        prom = {};
        }
    }
    return 0;
}

deque<item> makePostfix(const vector<item>& v){
    stack<item> stack1;
    deque<item> deque1;
    for (const item& i: v){
        if (i.type == 2){ // знак
            if (i.cval == '(')
                stack1.push(i);
            if (i.cval == '+' || i.cval == '-'){
                if (stack1.top().cval == '(' || stack1.empty())
                    stack1.push(i);
                else {
                    while (stack1.top().cval != '(') {
                        deque1.push_back(stack1.top());
                        stack1.pop();
                    }
                    stack1.push(i);
                }
            }
            if (i.cval == '*' || i.cval == '/'){
               if (stack1.top().cval == '+' || stack1.top().cval == '-')
                   stack1.push(i);
               else {
                   while (stack1.top().cval != '(') {
                       deque1.push_back(stack1.top());
                       stack1.pop();
                   }
                   stack1.push(i);
               }
            }
            if (i.cval == ')'){
                while (stack1.top().cval != '('){
                    deque1.push_back(stack1.top());
                    stack1.pop();
                }
                stack1.pop();
            }
        }
        if (i.type == 1) // число
            deque1.push_back(i);
        if (i.type == 3){ // функция
            stack1.push(i);
        }
    }
    while (!stack1.empty()) {
        deque1.push_back(stack1.top());
        stack1.pop();
    }
    return deque1;
}

double calculateFromPostfix(const deque<item>& deque1){
    stack<item> stack1;
    for (item i: deque1){
        if (i.type == 1)
            stack1.push(i);
        if (i.type == 2){
            double m, n, res;
            m = stack1.top().dval; stack1.pop();
            n = stack1.top().dval; stack1.pop();
            //cout << m << " " << n << " " << i.cval <<  endl;
            switch (i.cval) {
                case '+': {res = n + m; break;}
                case '-': {res = n - m; break;}
                case '*': {res = n * m; break;}
                case '/': {res = n / m; break;}
                default: {cout << "unknown operation"; res = 8989;}
            }
            stack1.push(item {1, res});
        }
       if (i.type == 3){
           double n, res;
           n = stack1.top().dval; stack1.pop();
           switch (i.cval) {
               case 'q': {res = sin(n); break;}
               case 'w': {res = cos(n); break;}
               case 'r': {res = tan(n); break;}
               case 'f': {res = 1/tan(n); break;}
               case 'y':{res = pow(e ,n); break;}
               default: {cout << "unknown operation"; res = 8989;}
           }
           stack1.push(item {1, res});
        }
    }
    return stack1.top().dval;
}

int main(){
    string form;
    cout << "Input formula:";
    getline(cin, form);
    string ban = "qwrfy";
    for (char i: form) //проверка символов, на которые будем заменять.
        if (count(ban.begin(), ban.end(), i) != 0){
            cout << "Your formula is incorrect";
            return 1;
        }

    form = '(' + form + ')';
    replaceFuncNames(form, "sin", "q");
    replaceFuncNames(form, "cos", "w");
    replaceFuncNames(form, "tg",  "r");
    replaceFuncNames(form, "ctg", "f");
    replaceFuncNames(form, "exp", "y");
    replaceFuncNames(form, "(-", "(0-");
    form.erase(remove_if(form.begin(), form.end(), ::isspace), form.end()); //удаление лишних пробелов

    if (findErrors(form)){ //проверка на ошибки
        cout << "Your formula is incorrect" << (findErrors(form));
        return 1;
    }
    if (count(form.begin(), form.end(), 'x') != 0){ // вставка переменной x
        cout << "enter x:";
        string x; cin >> x;
        replaceFuncNames(form, "x", x);
    }

    vector<item> v;
    if (makeVectorOfItems(form, v)) //разделение строки на числа и знаки
        return 1;
    for (int i = 0; i < v.size(); i++) //удаляем пустые элементы
        if (!v[i].type)
            v.erase(v.cbegin() + i);
    deque<item> d = makePostfix(v); //переводим инфиксную в постфиксную
    cout << calculateFromPostfix(d); //считаем и выводим результат
    return 0;
}
