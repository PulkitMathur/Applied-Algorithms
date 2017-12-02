//============================================================================
// Name        : AppliedAlgo-PA3-Q2.cpp
// Author      : Pulkit Mathur
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

#define NUM_PATHS 4
#define PATH_1 "C:\\Users\\mathu\\Desktop\\AppliedAlgoPA3\\input1.txt"
#define PATH_2 "C:\\Users\\mathu\\Desktop\\AppliedAlgoPA3\\input2.txt"
#define PATH_3 "C:\\Users\\mathu\\Desktop\\AppliedAlgoPA3\\input3.txt"
#define PATH_4 "C:\\Users\\mathu\\Desktop\\AppliedAlgoPA3\\input4.txt"
#define RESULT_FILE "C:\\Users\\mathu\\Desktop\\AppliedAlgoPA3\\output_q2.txt"

using namespace std;

std::vector<int> startTime;
std::vector<int> finishTime;
std::vector<int> weights;

class Job {
public:
	int start, finish, weight;
};

// User defined functions
int latestNonConflict(std::vector<Job> arr, int i);
bool jobComparataor(Job s1, Job s2);
void ReadFromFile(std::string path);
int findMaxWeight(std::vector<Job> arr);
int findMaximumWeight();

int main() {
	std::vector<int> maxWeights;
	std::map<int, std::string> pathMap;
	pathMap[0] = PATH_1;
	pathMap[1] = PATH_2;
	pathMap[2] = PATH_3;
	pathMap[3] = PATH_4;

	for (int i = 0; i < pathMap.size(); i++) {
		cout << "Evaluating for File" << (i+1) << endl;
		ReadFromFile(pathMap[i]);
		maxWeights.push_back(findMaximumWeight());
	}


	// Writing output to file
	ofstream outFile(RESULT_FILE);
	if (outFile.is_open()) {
		for (int i = 0; i < maxWeights.size(); i++) {
			outFile << "File ";
			outFile << (i + 1);
			outFile << " -> ";
			outFile << "Maximum Weight: ";
			outFile << maxWeights[i];
			outFile << "\n";
		}
	}

	return 0;
}



/*
 *	Function Name: latestNonConflict
 *	Parameters In: Array of jobs and job index
 *	Parameters Out: Index of conflicting job or -1
 *	Description: Find the index of conflicting job
 */
int latestNonConflict(std::vector<Job> arr, int i) {
	for (int j = i - 1; j >= 0; j--) {
		if (arr[j].finish <= arr[i].start)
			return j;
	}
	return -1;
}



/*
 *	Function Name: jobComparataor
 *	Parameters In: Two Jobs
 *	Parameters Out: True or False
 *	Description: Checks if finish time of first job is less than finish time of other.
 */
bool jobComparataor(Job s1, Job s2) {
	return (s1.finish < s2.finish);
}



/*
 *	Function Name: findMaxWeight
 *	Parameters In: Array of Jobs
 *	Parameters Out: Maximum Weight
 *	Description: Find the maximum possible weight depending on to the jobs we have.
 */
int findMaxWeight(std::vector<Job> arr) {
	// Sort jobs according to finish time
	int n = arr.size();
	sort(arr.begin(), arr.end(), jobComparataor);

	/* Create an array to store solutions of subproblems.  table[i]
	 stores the profit for jobs till arr[i] (including arr[i])*/
	int *table = new int[n];
	table[0] = arr[0].weight;

	// Fill entries in M[] using recursive property
	for (int i = 1; i < n; i++) {
		// Find profit including the current job
		int inclProf = arr[i].weight;
		int l = latestNonConflict(arr, i);
		if (l != -1)
			inclProf += table[l];

		// Store maximum of including and excluding
		table[i] = max(inclProf, table[i - 1]);
	}

	// Store result and free dynamic memory allocated for table[]
	int result = table[n - 1];
	delete[] table;

	return result;
}




/*
 *	Function Name: ReadFromFile
 *	Parameters In: path of file
 *	Parameters Out: None
 *	Description: Read the file from specified path and return an array of numbers read.
 */
void ReadFromFile(std::string path) {
	startTime.clear();
	finishTime.clear();
	weights.clear();

	std::fstream myfile(path);
	int a;
	if (myfile.is_open()) {
		int i = 0;
		while (myfile >> a) {
			//cout << a << endl;
			if (i == 0) {
				startTime.push_back(a);
				i = 1;
			} else if (i == 1) {
				finishTime.push_back(a);
				i = 2;
			} else if (i == 2) {
				weights.push_back(a);
				i = 0;
			}
		}
	} else {
		cout << "unable to open file" << endl;
	}

	myfile.close();
}



/*
 *	Function Name: findMaximumWeight
 *	Parameters In: None
 *	Parameters Out: Maximum Weight of Jobs
 *	Description: This is an auxiliary function to create an array of jobs and pass that array to the main function to find the maximum weight
 */
int findMaximumWeight() {
	std::vector<Job> jobs;
	Job objJob[startTime.size()];

	for (int i = 0; i < startTime.size(); i++) {
		objJob[i].start = startTime[i];
		objJob[i].finish = finishTime[i];
		objJob[i].weight = weights[i];
		jobs.push_back(objJob[i]);
	}

	return findMaxWeight(jobs);

}
