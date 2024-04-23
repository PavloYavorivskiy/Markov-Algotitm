#include <iostream>
#include <fstream>
using namespace std;
class String {
private:
    size_t size;
    char* str;
    static const size_t npos = -1;

public:
    String() : size(0), str(nullptr) {}

    String(const char* a) {
        size = 0;
        while (a[size] != '\0') {
            size++;
        }
        str = new char[size + 1];
        for (size_t i = 0; i < size; ++i) {
            str[i] = a[i];
        }
        str[size] = '\0';
    }

    String(const String& other) {
        size = other.size;
        str = new char[size + 1];
        for (size_t i = 0; i < size; ++i) {
            str[i] = other.str[i];
        }
        str[size] = '\0';
    }

    ~String() {
        delete[] str;
    }
        const char* c_str() const {
        return str;
    }
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            size = other.size;
            str = new char[size + 1];
            for (size_t i = 0; i < size; ++i) {
                str[i] = other.str[i];
            }
            str[size] = '\0';
        }
        return *this;
    }

    size_t length() const {
        return size;
    }
    bool operator==(const String& other) const {
    if (size != other.size) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (str[i] != other.str[i]) {
            return false;
        }
    }
    return true;
}

    String operator+(const String& other) const {
        size_t new_size = size + other.size;
        char* new_str = new char[new_size + 1];
        for (size_t i = 0; i < size; ++i) {
            new_str[i] = str[i];
        }
        for (size_t i = 0; i < other.size; ++i) {
            new_str[size + i] = other.str[i];
        }
        new_str[new_size] = '\0';
        String result(new_str);
        delete[] new_str;
        return result;
    }

    String& operator+=(const String& other) {
        size_t new_size = size + other.size;
        char* new_str = new char[new_size + 1];
        for (size_t i = 0; i < size; ++i) {
            new_str[i] = str[i];
        }
        for (size_t i = 0; i < other.size; ++i) {
            new_str[size + i] = other.str[i];
        }
        new_str[new_size] = '\0';
        delete[] str;
        size = new_size;
        str = new_str;
        return *this;
    }

    bool operator!=(const String& str2) {
        if (size != str2.length()) {
            return true;
        }
        for (size_t i = 0; i < size; ++i) {
            if (str[i] != str2[i]) {
                return true;
            }
        }
        return false;
    }

    String operator+(const char* other) const {
        String temp(other);
        return *this + temp;
    }

    String& operator+=(const char* other) {
        String temp(other);
        return *this += temp;
    }

    String& operator+=(char ch) {
        char* new_str = new char[size + 2];
        for (size_t i = 0; i < size; ++i) {
            new_str[i] = str[i];
        }
        new_str[size] = ch;
        new_str[size + 1] = '\0';
        delete[] str;
        str = new_str;
        ++size;
        return *this;
    }

    char& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return str[index];
    }
    String substr(size_t pos, size_t len = npos) const {
    if (pos > size) {
        throw out_of_range("Position out of range");
    }
    if (len == npos) {
        len = size - pos;
    }
    if (pos + len > size) {
        throw out_of_range("Length out of range");
    }

    char* new_str = new char[len + 1];
    for (size_t i = 0; i < len; ++i) {
        new_str[i] = str[pos + i];
    }
    new_str[len] = '\0';

    String result(new_str);
    delete[] new_str;
    return result;
}
    const char& operator[](size_t index) const {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return str[index];
    }

    char at(size_t index) const {
        if (index >= size || index < 0) {
            throw out_of_range("Index out of range");
        }
        return str[index];
    }

    friend ostream& operator<<(ostream& os, const String& a) {
        os << a.str;
        return os;
    }
    void replace_first(String& str, const String& from, const String& to) {
    size_t start_pos = str.find(from);
    if (start_pos == String::npos) {
        return; 
    }

    String new_str = str.substr(0, start_pos) + to + str.substr(start_pos + from.length());
    str = new_str;
}
bool bool_find(String& str, String& substr) {
    return str.find(substr) != String::npos;
}
size_t find(const String& substr, size_t pos = 0) const {
    for (size_t i = pos; i <= size - substr.size; ++i) {
        bool found = true;
        for (size_t j = 0; j < substr.size; ++j) {
            if (str[i + j] != substr.str[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return String::npos;
}
};
struct Rule {
    String from; 
    String to;  
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
