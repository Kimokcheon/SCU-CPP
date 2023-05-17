#include <iostream>
#include <vector>

using std::cout;    using std::endl;
using std::string; using std::cin; 
using std::vector;

//utility function just pauses program to poll the class
void poll(string question){
	string fluff;
	cout << question << endl;
	getline(cin, fluff);
}

//utility function to print a vector
void print_vector(vector<int> vec){
	cout << "{ ";
	for(int i = 0; i < vec.size() - 1; i++){
		cout << vec[i] << ", ";
	}

	cout << vec[vec.size() - 1] <<" }" << endl;
}

vector<int> reference_func(vector<int>& ref_param){
	ref_param.push_back(4);
	return ref_param;
}

// void const_reference_func(const vector<int>& const_ref_param){
// 	reference_func(const_ref_param);
// }

void example_2(){
	vector<int> regular_vec{1, 2};
	auto return_val = reference_func (regular_vec);

	poll("What is the state of regular_vec?");
	cout << "regular_vec: ";
	print_vector(regular_vec);

	poll("What is the state of return_val?");
	cout << "return_val: ";
	print_vector(return_val);

	cout << "\npushing 5 onto return val\n" << endl;

	return_val.push_back(5);
	poll("What is the state of regular_vec?");
	cout << "regular_vec: ";
	print_vector(regular_vec);

	poll("What is the state of return_val?");
	cout << "return_val: ";
	print_vector(return_val);


}

void example_1(){

	// cout << "Executing: \nvector<int> regular_vec{1, 2};\nconst vector<int> const_vec{1, 2};\nvector<int>& regular_vec_ref = regular_vec;\nconst vector<int>& regular_vec_const_ref = regular_vec;" << endl;
	vector<int> regular_vec{1, 2};
	const vector<int> const_vec{1, 2};
	vector<int>& regular_vec_ref = regular_vec;
	const vector<int>& regular_vec_const_ref = regular_vec;

	// cout << "Executing:\nauto auto_vec = regular_vec_ref;\nauto_vec.push_back(3);" << endl;

	auto auto_vec = const_vec;
	auto_vec.push_back(3);
	poll("What is the state of auto_vec?");
	cout << "auto_vec: ";
	print_vector(auto_vec);

	poll("What is the state of regular_vec?");
	cout << "regular_vec: ";
	print_vector(regular_vec);

	poll("What is the state of regular_vec_ref?");
	cout << "regular_vec_ref: ";
	print_vector(regular_vec_ref);

	poll("What is the state of regular_vec_const_ref?");
	cout << "regular_vec_const_ref: ";
	print_vector(regular_vec_const_ref);
}

int main(){
	example_1();
	example_2();
}