#include <string>
#include <iostream>
#include <cmath> //gives us pow and sqrt!

using std::string; using std::cout;
using std::cin; using std::pow;
using std::sqrt; using std::endl;

std::pair<bool, std::pair<double, double>> quadratic(double a, double b, double c){
	//get radical, test if negative, return false if so
	double radical = pow(b, 2) - (4*a*c);
	if(radical < 0){
		return std::make_pair(false, std::make_pair(-1, -1));
	} else {
		double root1 = (-1*b + sqrt(radical)) / (2*a);
		double root2 = (-1*b - sqrt(radical)) / (2*a);
		return std::make_pair(true, std::make_pair(root1, root2));
	}

	//otherwise get roots and return

	return {false, {-1, -1}};
}

int main(){
	//get 3 doubles (ax^2 + bx + c)
	double a, b, c;
	cout << "Give me 3 coefficients: " << endl;
	cin >> a >> b >> c;
	//get roots if they exist- use structured binding!
	

	return 0;
}