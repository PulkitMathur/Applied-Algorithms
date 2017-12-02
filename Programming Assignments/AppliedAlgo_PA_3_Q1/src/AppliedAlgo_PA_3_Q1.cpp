#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define RESULT_FILE "C:\\Users\\mathu\\Desktop\\AppliedAlgoPA3\\output_q1.txt"
#define DATA_FILE "C:\\Users\\mathu\\Desktop\\AppliedAlgoPA3\\data.txt"

using namespace std;

// Used to modify result up to last 5 digits.
long mod = pow(10, 5);


// User defined functions
long countWays(int arr[], int size, int N);
void WriteToFile();
vector<long> ReadFromFile();


// Main Function
int main()
{
	int arr[3];
	arr[0] = 1;
	arr[1] = 3;
	arr[2] = 4;

	cout << "Writing Input Data to File....." << endl;
	WriteToFile();

	cout << "Reading Input Data from File...." << endl;
	std::vector<long>Data = ReadFromFile();

	cout << "Writing Output to File..." << endl;
	ofstream myfile(RESULT_FILE);
	if (myfile.is_open())
	{

		for (int i = 0; i < Data.size(); i++)
		{
			long a = Data[i];
			long b = countWays(arr, 3, Data[i]);
			myfile << "Input: ";
			myfile << a;
			myfile << "  Output: ";
			myfile << b;
			myfile << "\n";
			cout << "a ->" << a << "  " << b << endl;
		}
	}
	cout << "Finished" << endl;
	return 0;
}

/*
 *	Function Name: WriteToFile
 *	Parameters In: None
 *	Parameters Out: None
 *	Description: Write numbers form 1 to 520000 to a .txt file
 */
void WriteToFile() {
	ofstream myfile(DATA_FILE);
	if (myfile.is_open()) {
		for (int i = 1; i < 510000; i++) {
			myfile << i;
			myfile << "\n";
		}
		myfile.close();
	} else {
		cout << "Unable to open file";
	}
}


/*
 *	Function Name: ReadFromFile
 *	Parameters In: None
 *	Parameters Out: Array of numbers
 *	Description: Read all numbers from the text file and pushes inside an array and then returns the same array.
 */
vector<long> ReadFromFile()
{
	std::vector<long> data;
	string line;
	std::fstream myfile(DATA_FILE);
	if (myfile.is_open()) {
		long x;
		for (int i = 0; i < 510000; i++) {
			myfile >> x;
			data.push_back(x);
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file";
	}
	return data;
}




/*
 *	Function Name: countWays
 *	Parameters In: Array of numbers used to find permutations, size of array and number for which we need to find number of permutations.
 *	Parameters Out: Numbers of permutations for given input number.
 *	Description: Finds the number of permutations possible to sum upto given input based on array of numbers provided.
 */
long countWays(int arr[], int size, int N)
{
	/*
	 * Bottom Up Approach
	 * Subproblem: Counting permutations for all numbers from 1 to N
	 * The count[] array stores the number of permutations for all numbers 1 to N
	 */
	long count[N + 1];
	for (int i = 1; i <= N; i++)
		count[i] = 0;

	// base case
	count[0] = 1;

	// count ways for all values up to 'N'
	// and store the result
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < size; j++)

			// if i >= arr[j] then
			// accumulate count for value 'i' as
			// ways to form value 'i-arr[j]'

			if (i >= arr[j])
			{
				count[i] += count[i - arr[j]];
				count[i] %= mod;
			}

	// required number of ways
	return count[N];

}
