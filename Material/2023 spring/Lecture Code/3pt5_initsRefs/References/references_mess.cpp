#include <iostream>
#include <vector>

using std::cout;    using std::endl;
using std::string; using std::cin; 
using std::vector;

void poll(string question);
void print_vector(vector<int> nums);

//lecture example: play around with the references and copies and test yourself!
void ref_var_example(){
	//create vectors
	vector<int> original{1, 2};
	vector<int> copy = original;
	vector<int>& ref = original;
	cout << "executing: \n vector<int> original{1, 2}; \n vector<int> copy = original; \n vector<int>& ref = original;" << endl;

	//change vectors
	original.push_back(3);
	copy.push_back(4);
	ref.push_back(5);

	cout << "executing:\n original.push_back(3); \n copy.push_back(4); \nref.push_back(5);" << endl;

	poll("What is the state of each object?");

	cout << "original: ";
	print_vector(original);
	cout << "copy: ";
	print_vector(copy);
	cout << "ref: ";
	print_vector(ref);
}

void print_vector(vector<int> vec){
	cout << "{ ";
	for(int i = 0; i < vec.size() - 1; i++){
		cout << vec[i] << ", ";
	}

	cout << vec[vec.size() - 1] << " }" << endl;
}

void print_vector(vector<std::pair<int, int>> vec){
	cout << "{ ";
	for(int i = 0; i < vec.size() - 1; i++){
		cout << "{" << vec[i].first << ", " << vec[i].second << "}, ";
	}

	cout << "{" << vec[vec.size() - 1].first << "," << vec[vec.size() - 1].second << "} }" << endl;
}

//utility function just pauses program to poll the class
void poll(string question){
	string fluff;
	cout << question << endl;
	getline(cin, fluff);
}


void shift(vector<int>& nums) {
	for (size_t i = 0; i < nums.size(); ++i) {
		int num = nums[i];
		num++;
	}

}

void shift(vector<std::pair<int, int>>& nums) {
	for (size_t i = 0; i < nums.size(); ++i) {
		auto [num1, num2] = nums[i];
		num1++;
		num2++;
	}

}

int main(){
	// vector<std::pair<int, int>> nums{{1, 2}};
	// cout << "nums starts as: ";
	// print_vector(nums);
	// shift(nums);

	// poll("what does nums look like now?");

	// print_vector(nums);
	ref_var_example();

	
}