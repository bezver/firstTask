#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

void output(long left, long right, vector<long> &a) {
	for (long i = left; i < right; i++)
		cout << a[i] << ' ';
	cout << endl;
}

int main()
{
	long n, i, variable;
	long long sum;
	double median, arifmeticMean;
	vector<long> test, resUp, resDown;
	long long startTime, endTime;
	struct sequence {
		long left = 0;
		long right, size = 0;
	} up, down, upMax, downMax;
	startTime = clock();

	ifstream input("input.txt");
	cout << "start input..." << endl;
	input >> variable;
	test.push_back(variable);
	sum = variable;
	for (i = 1; !input.eof(); i++) {			// input
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
		
	}
	n = i;
	arifmeticMean = (double)sum / n;
	if (up.size > upMax.size) {			// if used all elements (upMax == 0, up != 0)
		upMax = up;
	}
	if (down.size > downMax.size) {		// if (down != 0 and downMax == 0)
		downMax = down;
	}
	for (i = upMax.left; i <= upMax.right; i++) {		// save result of search
		resUp.push_back(test[i]);
	}
	for (i = downMax.left; i <= downMax.right; i++) {
		resDown.push_back(test[i]);
	}
	endTime = clock();
	cout << "input time = " << endTime / 1000.0 << endl;

	cout << "start sort..." << endl;
	sort(test.begin(), test.end());		// sort
	
	cout << "sort time = " << (clock() - endTime) / 1000.0 << endl;
	

	if (n % 2 == 0) {										// search a median
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
		output(0, resUp.size(), resUp);
	else {
		cout << '-' << endl;
	}
	cout << "6. downMax: " << endl;
	if (resDown.size() != 0) {
		output(0, resDown.size(), resDown);
	}
	else {
		cout << '-' << endl;
	}
	cout << "time run = " << clock() / 1000.0 << endl;
	input.close();
	return 0;
}

