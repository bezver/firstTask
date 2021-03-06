/*
the program finds the maximum, minimum numbers in the file, 
median (statistics), arithmetic mean 
and numerical sequences
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

void printVector(size_t left, size_t right, vector<long> &a) {
	for (size_t i = left; i < right; i++)
		cout << a[i] << ' ';
	cout << endl;
}

int main()
{
	long n, i, variable, startTime;
	long long sum;
	double median, arifmeticMean;
	vector<long> test, resUp, resDown;
	struct Sequence {
		long left = 0;
		long right, size = 0;
	} up, down, upMax, downMax;
		
	cout << "start input..." << endl;
	ifstream input("input.txt");
	input >> variable;
	test.push_back(variable);
	sum = variable;
	i = 1;
	while (!input.eof()) {			
		input >> variable;
		test.push_back(variable);
		sum += variable;			
		
		if (variable > test[i - 1]) {			// search an increase
			up.right = i;
			up.size++;
		}
		else {
			if (up.size > upMax.size) {
				upMax = up;
			}
			up.left = up.right = i;
			up.size = 0;
		}
		
		if (variable < test[i - 1]) {			// search an decrease
			down.right = i;
			down.size++;
		}
		else {
			if (down.size > downMax.size) {
				downMax = down;
			}
			down.left = down.right = i;
			down.size = 0;
		}
		i++;
	}
	n = i;

	arifmeticMean = (double)sum / n;
	if (up.size > upMax.size) {			// if used all elements (upMax == 0, up != 0)
		upMax = up;
	}
	if (down.size > downMax.size) {		// if (down != 0 and downMax == 0)
		downMax = down;
	}
	// save result of search
	for (i = upMax.left; i <= upMax.right; i++) {		
		resUp.push_back(test[i]);
	}
	for (i = downMax.left; i <= downMax.right; i++) {
		resDown.push_back(test[i]);
	}

	startTime = clock();
	cout << "input time = " << startTime / 1000.0 << endl;
	
	// sort
	cout << "start sort..." << endl;
	sort(test.begin(), test.end());		
	cout << "sort time = " << (clock() - startTime) / 1000.0 << endl;
	
	// search a median
	if (n % 2 == 0) {
		median = 0.5 * (test[n / 2] + test[n / 2 - 1]);		
	}
	else {
		median = (double)test[n / 2];
	}
	
	// output result
	cout << "1. the maximum number in the file = " << test[n - 1] << endl;
	cout << "2. the minimum number in the file = " << test[0] << endl;
	cout << "3. median = " << median << endl;
	cout << "4. arifmetic mean = " << arifmeticMean << endl;
	cout << "5. upMax: " << endl;
	if (resUp.size() != 0)
		printVector(0, resUp.size(), resUp);
	else {
		cout << '-' << endl;
	}
	cout << "6. downMax: " << endl;
	if (resDown.size() != 0) {
		printVector(0, resDown.size(), resDown);
	}
	else {
		cout << '-' << endl;
	}
	cout << "time run = " << clock() / 1000.0 << endl;
	
	input.close();
	return 0;
}

