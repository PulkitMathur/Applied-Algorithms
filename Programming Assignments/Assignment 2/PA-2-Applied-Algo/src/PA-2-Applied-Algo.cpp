//============================================================================
// Name        : PA-2-Applied-Algo.cpp
// Author      : Pulkit Mathur
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iomanip>
#include <time.h>
#include <vector>
#include <iostream>
#include <fstream>
#include<algorithm>
#define N 28000
#define STEP 1000
using namespace std;


void part1();
void part2();
void part3();
void InsertionSort(int arr[],int size);
void MergeSort(int arr[], int l, int r);
void Merge(int arr[], int l, int m, int r);
void swap(int* a, int* b);
void QuickSort(int arr[], int low, int high);
int Partition (int arr[], int low, int high);
void WriteToFile();
vector<int> ReadFromFile(int size);
int findTimeInsertionSort(int arr[],int input_size);
int findTimeMergeSort(int arr[],int input_size);
int findTimeQuickSort(int arr[],int input_size);

int main()
{
	WriteToFile();

	/*std::vector<int> temp = ReadFromFile(10);
	cout << "temp: " << endl;
	for(int i=0;i<temp.size();i++)
	{
		cout << temp[i] << " ";
	}
	cout << endl << "Sort: ";


	int A[temp.size()];
	int B[temp.size()];
	int C[temp.size()];
	for(int j=0;j<temp.size();j++)
	{
		A[j] = temp[j];
		B[j] = temp[j];
		C[j] = temp[j];
	}
	InsertionSort(A,temp.size());
	MergeSort(B,0,temp.size()-1);
	QuickSort(C,0,temp.size()-1);


	cout << endl << "A: ";
	for(int j=0;j<temp.size();j++)
	{
		cout<<A[j] << " ";
	}
	cout << endl << "B: ";
	for(int j=0;j<temp.size();j++)
	{
		cout<<B[j] << " ";
	}
	cout << endl << "C: ";
	for(int j=0;j<temp.size();j++)
	{
		cout<<C[j] << " ";
	}*/

	part1();
	part2();
	part3();

	return 0;
}

void WriteToFile()
{
	ofstream myfile ("C:\\Users\\mathu\\Desktop\\Algo_PA2\\data.txt");
	if (myfile.is_open())
	{
		cout << "Able to open file" << endl;
		for(int i=0;i<N;i++)
		{
			myfile << rand()%N;
			myfile << "\n";
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}
vector<int> ReadFromFile(int size)
																				{
	std::vector<int>data;
	string line;
	std::fstream myfile ("C:\\Users\\mathu\\Desktop\\Algo_PA2\\data.txt");
	if (myfile.is_open())
	{
		int x;
		for(int i=0;i<size;i++)
		{
			//getline (myfile,line);
			myfile >> x;
			data.push_back(x);
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	return data;
																				}
void part1()
{
	cout << "Part 1 executing..." << endl;
	/*std::vector<int> temp = ReadFromFile(10);
	cout << "temp: " << endl;
	for(int i=0;i<temp.size();i++)
	{
		cout << temp[i] << " ";
	}
	cout << endl;*/


	std::vector<double>insertionSortTimings;
	std::vector<double>mergeSortTimings;
	std::vector<double>quickSortTimings;


	for(int i = STEP;i<=N;i=i+STEP)
	{
		int t1 = 0;
		int t2 = 0;
		int t3 = 0;
		for(int a=0;a<10;a++)
		{
			std::vector<int> temp = ReadFromFile(i);
			int A[temp.size()];
			int B[temp.size()];
			int C[temp.size()];
			for(int j=0;j<temp.size();j++)
			{
				A[j] = temp[j];
				B[j] = temp[j];
				C[j] = temp[j];
			}
			t1 = t1 + findTimeInsertionSort(A,i);
			t2 = t2 + findTimeMergeSort(B,i);
			t3 = t3 + findTimeQuickSort(C,i);
		}
		insertionSortTimings.push_back(t1/10);
		mergeSortTimings.push_back(t2/10);
		quickSortTimings.push_back(t3/10);
	}

	cout << "Insertion Sort Timings: ";
	for(int i=0;i<insertionSortTimings.size();i++)
	{
		cout << insertionSortTimings[i] << " ";
	}
	cout << endl;
	cout << "Merge Sort Timings: ";
	for(int i=0;i<mergeSortTimings.size();i++)
	{
		cout << mergeSortTimings[i] << " ";
	}
	cout << endl;
	cout << "Quick Sort Timings: ";
	for(int i=0;i<quickSortTimings.size();i++)
	{
		cout << quickSortTimings[i] << " ";
	}
	cout << endl;
}

void part2()
{
	cout << "Part 2 executing..." << endl;
	std::vector<double>insertionSortTimings;
	std::vector<double>mergeSortTimings;
	std::vector<double>quickSortTimings;


	for(int i = STEP;i<=N;i=i+STEP)
	{
		int t1 = 0;
		int t2 = 0;
		int t3 = 0;
		for(int a=0;a<10;a++)
		{
			std::vector<int> temp = ReadFromFile(i);
			std::sort(temp.begin(),temp.end());
			int A[temp.size()];
			int B[temp.size()];
			int C[temp.size()];
			for(int j=0;j<temp.size();j++)
			{
				A[j] = temp[j];
				B[j] = temp[j];
				C[j] = temp[j];
			}
			t1 = t1 + findTimeInsertionSort(A,i);
			t2 = t2 + findTimeMergeSort(B,i);
			t3 = t3 + findTimeQuickSort(C,i);
		}

		insertionSortTimings.push_back(t1/10);
		mergeSortTimings.push_back(t2/10);
		quickSortTimings.push_back(t3/10);
	}

	cout << "Insertion Sort Timings: ";
	for(int i=0;i<insertionSortTimings.size();i++)
	{
		cout << insertionSortTimings[i] << " ";
	}
	cout << endl;
	cout << "Merge Sort Timings: ";
	for(int i=0;i<mergeSortTimings.size();i++)
	{
		cout << mergeSortTimings[i] << " ";
	}
	cout << endl;
	cout << "Quick Sort Timings: ";
	for(int i=0;i<quickSortTimings.size();i++)
	{
		cout << quickSortTimings[i] << " ";
	}
	cout << endl;
}

void part3()
{
	cout << "Part 3 executing..." << endl;
	std::vector<double>insertionSortTimings;
	std::vector<double>mergeSortTimings;
	std::vector<double>quickSortTimings;


	for(int i = STEP;i<=N;i=i+STEP)
	{
		int t1 = 0;
		int t2 = 0;
		int t3 = 0;
		for(int a=0;a<10;a++)
		{
			std::vector<int> temp = ReadFromFile(i);
			std::sort(temp.begin(),temp.end(),greater<int>());
			int A[temp.size()];
			int B[temp.size()];
			int C[temp.size()];
			for(int j=0;j<temp.size();j++)
			{
				A[j] = temp[j];
				B[j] = temp[j];
				C[j] = temp[j];
			}
			t1 = t1 + findTimeInsertionSort(A,i);
			t2 = t2 + findTimeMergeSort(B,i);
			t3 = t3 + findTimeQuickSort(C,i);

		}

		insertionSortTimings.push_back(t1/10);
		mergeSortTimings.push_back(t2/10);
		quickSortTimings.push_back(t3/10);
	}

	cout << "Insertion Sort Timings: ";
	for(int i=0;i<insertionSortTimings.size();i++)
	{
		cout << insertionSortTimings[i] << " ";
	}
	cout << endl;
	cout << "Merge Sort Timings: ";
	for(int i=0;i<mergeSortTimings.size();i++)
	{
		cout << mergeSortTimings[i] << " ";
	}
	cout << endl;
	cout << "Quick Sort Timings: ";
	for(int i=0;i<quickSortTimings.size();i++)
	{
		cout << quickSortTimings[i] << " ";
	}
	cout << endl;
}


/*
 *	Function Name: InsertionSort
 *	Parameters: Array and it's size
 *	Description: Sorting the input array using insertion sort algorithm
 *
 */
void InsertionSort(int arr[],int size)
{
	//cout << "In insertion sort" << endl;
	int i, key, j;
	for (i = 1; i < size; i++)
	{
		key = arr[i];
		j = i-1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j+1] = arr[j];
			j = j-1;
		}
		arr[j+1] = key;
	}
}


void MergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = l+(r-l)/2;
		MergeSort(arr, l, m);
		MergeSort(arr, m+1, r);
		Merge(arr, l, m, r);
	}
}

void Merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 =  r - m;

	/* create temporary arrays */
	int L[n1], R[n2];

	/* Copy data to temporary arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}


/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void QuickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
           at right place */
		int pi = Partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		QuickSort(arr, low, pi - 1);
		QuickSort(arr, pi + 1, high);
	}
}


int Partition (int arr[], int low, int high)
{
	int pivot = arr[high];    // pivot
	int i = (low - 1);  // Index of smaller element

	for (int j = low; j <= high- 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (arr[j] <= pivot)
		{
			i++;    // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}


/*
 *	Function Name: findTimeInsertionSort_1
 *	Parameters: Array and it's size
 *	Description: Find the running time of insertion sort over different input sizes.
 *
 */
int findTimeInsertionSort(int arr[],int input_size)
{
	auto t_start = std::chrono::high_resolution_clock::now();
	InsertionSort(arr,input_size);
	auto t_end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
}


int findTimeMergeSort(int arr[],int input_size)
{
	auto t_start = std::chrono::high_resolution_clock::now();
	MergeSort(arr,0,input_size-1);
	auto t_end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
}

int findTimeQuickSort(int arr[],int input_size)
{
	auto t_start = std::chrono::high_resolution_clock::now();
	QuickSort(arr,0,input_size-1);
	auto t_end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
}
