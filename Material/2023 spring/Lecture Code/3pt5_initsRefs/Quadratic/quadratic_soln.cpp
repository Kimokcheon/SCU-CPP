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
		// First way: return std::make_pair(false, std::make_pair(-1, -1));
		// Uniform initialization
		return {false, {-1, -1}};
	} else {
		double root1 = ( -1*b + sqrt(radical) ) / (2*a);
		double root2 = ( -1*b - sqrt(radical) ) / (2*a);
		// First way: return std::make_pair(true, std::make_pair(root1, root2));
		// Uniform initialization
		return {true, {root1, root2}};

	}
}

int main(){
	//get 3 doubles (ax^2 + bx + c)
	double a, b, c;
	cout << "Input coefficients" << endl;
	cin >> a >> b >> c;
	//get roots if they exist
	// First way: std::pair<bool, std::pair<double, double>> res = quadratic(a, b, c);
	//Using structured binding:
	auto [exists, results] = quadratic(a, b, c);
	//print accordingly
	// if(res.first) {
	if (exists) {
		auto [root1, root2] = results;
		// cout << "Solutions are: " << res.second.first << " " << res.second.second << endl;
		cout << "Solutions are: " << root1 << " " << root2 << endl;
	} else {
		cout << "No solutions exist!" << endl;
	}

	return 0;
}