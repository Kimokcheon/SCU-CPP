//
// Created by GAO on 2023/3/27.
//
#include "functions.h"

int Functions::LmoreThanR(string a, string b){
    if(a.size() > b.size()) {
        return 1;
    } else if(a.size() < b.size()) {
        return -1;
    } else {
        for(int i = 0; i < a.size(); i++) {
            if(a[i] > b[i]) {
                return 1;
            } else if(a[i] < b[i]) {
                return -1;
            }
        }
        return 0;
    }
}

string Functions::add(string a, string b) {
    string res;
    int carry = 0;
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int x = i >= 0 ? a[i--] - '0' : 0;
        int y = j >= 0 ? b[j--] - '0' : 0;
        int sum = x + y + carry;
        res += to_string(sum % 10);
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

string Functions::add_decimal(string a, string b) {
    int judge1 = 0, judge2 = 0;
    for(int i = 0; i < a.size(); i++) {
        if(a[i] == '.') {
            judge1 = i;
            break;
        }
    }
    for(int i = 0; i < b.size(); i++) {
        if(b[i] == '.') {
            judge2 = i;
            break;
        }
    }
    if(judge1 == 0) {
        a += ".0";
        judge1 = a.size() - 2;
    }
    if(judge2 == 0) {
        b += ".0";
        judge2 = b.size() - 2;
    }
    string a_int = a.substr(0, judge1);
    string a_decimal = a.substr(judge1 + 1);
    string b_int = b.substr(0, judge2);
    string b_decimal = b.substr(judge2 + 1);
    if(a_decimal.size() > b_decimal.size()) {
        b_decimal += string(a_decimal.size() - b_decimal.size(), '0');
    } else {
        a_decimal += string(b_decimal.size() - a_decimal.size(), '0');
    }
    string int_part = add(a_int, b_int);
    string decimal_part = add(a_decimal, b_decimal);
    if(decimal_part.size() > a_decimal.size()) {
        int_part = add(int_part, "1");
        decimal_part = decimal_part.substr(1);
    }
    if(decimal_part == "0"){
        return int_part;
    }
    return int_part + '.' + decimal_part;
}

string Functions::multiply(char a, string b) {
    string res;
    int carry = 0;
    for(int i = b.size()-1; i >= 0; i--) {
        int x = a - '0';
        int y = b[i] - '0';
        int sum = x * y + carry;
        res += to_string(sum % 10);
        carry = sum / 10;
    }
    if(carry) {
        res = to_string(carry);
    }
    reverse(res.begin(), res.end());
    if(res[0] == '0') {
        res.erase(res.begin());
    }
    return res;
}

string Functions::multiply_decimal(string a, string b) {
    int judge1 = 0, judge2 = 0;
    int len_a = a.size(), len_b = b.size();
    for(int i = 0; i < len_a; i++) {
        if(a[i] == '.') {
            judge1 = i+1;
            while(i < len_a - 1){
                a[i] = a[i + 1];
                i++;
            }
            a.erase(a.end() - 1);
        }
    }
    for(int i = 0; i < len_b; i++) {
        if(b[i] == '.') {
            judge2 = i+1;
            while(i < len_b - 1) {
                b[i] = b[i + 1];
                i++;
            }
            b.erase(b.end() - 1);
        }
    }
    if(judge1 == 0) {
        judge1 = len_a;
    }
    if(judge2 == 0) {
        judge2 = len_b;
    }
    string res = "0";
    for(int i = len_a - 1 - !(judge1 == len_a); i >= 0; i--) {
        string temp1 = multiply(a[i], b);
        string temp2 = temp1 + string(len_a - 1 - i - !(judge1 == len_a), '0');
        res = add_decimal(res, temp2);
    }
    string t = res.substr(res.size() - (len_a - judge1) - (len_b - judge2));
    if(a.length() == 0) {
        res = res.substr(0, res.size() - (len_a - judge1) - (len_b - judge2));
    }
    else{
        res = res.substr(0, res.size() - (len_a - judge1) - (len_b - judge2)) + '.' + res.substr(res.size() - (len_a - judge1) - (len_b - judge2));
    }
    return res;
}

string Functions::minus(string a, string b) {
    string res;
    int carry = 0;
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int x = i >= 0 ? a[i--] - '0' : 0;
        int y = j >= 0 ? b[j--] - '0' : 0;
        int sum = x - y - carry;
        if(sum < 0) {
            sum += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        res += to_string(sum);
    }
    reverse(res.begin(), res.end());
    if(res[0] == '0') {
        res.erase(res.begin());
    }
    return res;
}

string Functions::minus_decimal(string a, string b) {
    int judge1 = 0, judge2 = 0;
    int len_a = a.size(), len_b = b.size();
    for(int i = 0; i < len_a; i++) {
        if(a[i] == '.') {
            judge1 = i+1;
            while(i < len_a - 1){
                a[i] = a[i + 1];
                i++;
            }
            a.erase(a.end() - 1);
        }
    }
    for(int i = 0; i < len_b; i++) {
        if(b[i] == '.') {
            judge2 = i+1;
            while(i < len_b - 1) {
                b[i] = b[i + 1];
                i++;
            }
            b.erase(b.end() - 1);
        }
    }
    if(judge1 == 0) {
        a += ".0";
        judge1 = a.size() - 2;
    }
    if(judge2 == 0) {
        b += ".0";
        judge2 = b.size() - 2;
    }

    // 补齐小数点后的位数
    int len = max(a.size() - judge1 + 1, b.size() - judge2 + 1);
    a.insert(a.length(), len + judge1 - a.size() - 1 , '0');
    b.insert(b.length(), len + judge2 - b.size() - 1, '0');

    // 计算差值
    string res;
    if(LmoreThanR(a, b) == 1) {
        res = minus(a, b);
        if (res.length() < len-1) {
            res.insert(0, len-1 - res.length(), '0');
        }
        res.insert(res.length() - len, ".");
    }
    else if(LmoreThanR(a, b) == -1) {
        res = minus(b, a);
        if(res.length() < len-1) {
            res.insert(0, len-1 - res.length(), '0');
        }
        res.insert(res.length() - len, ".");
        res = "-" + res;
    }
    else if(LmoreThanR(a, b) == 0) {
        return "0";
    }
    return res;
}
