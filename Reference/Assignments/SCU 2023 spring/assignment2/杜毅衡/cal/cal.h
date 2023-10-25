#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
const double eps=1e-6;
void init();
void sol(string op);
pair<int,double> get_value(string op);
bool check(pair<int,double> res);
int priority(char c);