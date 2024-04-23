#include <iostream>
#include <fstream>
#include "String.h"
using namespace std;

struct Rule {
    String from; 
    String to;
    bool is_terminal;  
};
class Markov
{
private:
    String Ryadok;
    Rule* rules;
    int ruleCount;
    int capacity;
public:
    Markov() : rules(nullptr), ruleCount(0), capacity(0) {}
    const String& getRyadok() const {
    return Ryadok;
}
void add_ryadok(const String& newRyadok) {
    Ryadok = newRyadok;
}
    void add_rule(Rule rule) {
        if (ruleCount == capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            Rule* newRules = new Rule[capacity];
            for (int i = 0; i < ruleCount; ++i) {
                newRules[i] = rules[i];
            }
            delete[] rules;
            rules = newRules;
        }
        rules[ruleCount++] = rule;
    }
    void pidstanovka(Rule* rule){
        if(Ryadok.bool_find(Ryadok,rule->from)){
        Ryadok.replace_first(Ryadok,rule->from,rule->to);
        }
    }
    void program(){
    while (true) {
        bool replacementMade = false;

        for (int i = 0; i < ruleCount; ++i) {
            if (Ryadok.bool_find(Ryadok, rules[i].from)) {
                Ryadok.replace_first(Ryadok, rules[i].from, rules[i].to);
                if(rules[i].is_terminal)break;
                replacementMade = true;
            }
        }

        if (!replacementMade) {
            break;
        }
    }
    }
    ~Markov() {
        delete[] rules;
    }
};
int main() {
    String word("100000");
    Markov markov;


    markov.add_rule({ "1", "t" ,1});
    markov.add_rule({ "0", "nt" ,0});
    markov.add_rule({ "0", "nt" ,0});

    markov.add_ryadok(word);
    markov.program();

    cout << "Result: " << markov.getRyadok() << endl;

    system("pause");
    return 0;
}
