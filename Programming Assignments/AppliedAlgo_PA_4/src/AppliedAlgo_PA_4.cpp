//============================================================================
// Name        : AppliedAlgo-PA4.cpp
// Author      : Pulkit Mathur
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#define BOOK1_PATH "C:\\Users\\mathu\\Desktop\\AppliedAlgoPA4\\book.txt"
#define BOOK2_PATH "C:\\Users\\mathu\\Desktop\\AppliedAlgoPA4\\book2.txt"
#define MAX_TREE_HT 100
#define OUT_FILE_1 "C:\\Users\\mathu\\Desktop\\AppliedAlgoPA4\\output.txt"
#define CONCLUSION_FILE "C:\\Users\\mathu\\Desktop\\AppliedAlgoPA4\\conclusion.txt"

#include <vector>
#include <map>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <utility>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

using namespace std;


std::map<char,std::vector<int>>codes;

struct MinHeapNode
{
	char data;  // One of the input characters
	unsigned frequency;  // Frequency of the character
	struct MinHeapNode *left, *right; // Left and right children
};

struct MinHeap
{
	unsigned size;    // Current size of min heap
	unsigned capacity;   // capacity of min heap
	struct MinHeapNode **array;  // Array of minheap node pointers
};


struct MinHeapNode* getNewNode(char data, unsigned freq);
struct MinHeap* createMinHeap(unsigned capacity);
void swapNodes(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap, int idx);
int isSizeOne(struct MinHeap* minHeap);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode);
void buildMinHeap(struct MinHeap* minHeap);
int isLeaf(struct MinHeapNode* root);
struct MinHeap* createAndBuildMinHeap(std::map<char,int>wordMap);
struct MinHeapNode* buildHuffmanTree(std::map<char,int>wordMap);
void storeHuffmanCodes(struct MinHeapNode* root, int arr[], int top);
void generateHuffmanCodes(std::map<char,int>wordMap);
void readBook(std::string path, std::vector<std::string>& lines);
void createCharacterMap(std::map<char,int>& wordMap,std::vector<std::string> lines);
void writeToFile(std::string path,std::map<char,int>wordMap);

int main() {

	cout << "Applied Algo -> PA 4" << endl;
	std::map<char,int>wordMap;
	std::vector<std::string>lines;

	cout << "Reading Book.." << endl;
	readBook(BOOK1_PATH,lines);

	int initialBits = 0;
	for(int i = 0;i<lines.size();i++)
	{
		initialBits = initialBits + lines[i].size();
	}

	initialBits = initialBits*7;

	cout << "Creating Character Map...." << endl;
	createCharacterMap(wordMap,lines);

	cout << "Creating Huffman Tree......" << endl;
	cout << "Getting Huffman Codes........" << endl;
	generateHuffmanCodes(wordMap);

	cout << "Writing Huffman Codes to File...." << endl;
	writeToFile(OUT_FILE_1,wordMap);
	cout << "Finished" << endl;

	int finalBits = 0;
	for(map<char, int >::const_iterator it = wordMap.begin();it != wordMap.end(); ++it)
	{
		map<char, std::vector<int> >::const_iterator it2 = codes.find(it->first);
		finalBits =  finalBits + it->second * it2->second.size();
	}


	ofstream outFile(CONCLUSION_FILE);
	if (outFile.is_open())
	{
		outFile << "Initial bits required to represent the file: " << initialBits<< endl;

		outFile << "Final bits required to represent the file: " << finalBits << endl;

		outFile << "Bits Saved: " << initialBits - finalBits << endl;

		double difference = (initialBits - finalBits);
		double ratio = difference/initialBits;
		double compression = ratio*100;
		outFile << "% Compression: " << compression << "%" << endl;

	}
	return 0;
}



/*
 *	Function Name: writeToFile
 *	Parameters In: path of file, character map
 *	Parameters Out: void
 *	Description: Write data to file
 */
void writeToFile(std::string path,std::map<char,int>wordMap)
{
	ofstream outFile(path);
	if (outFile.is_open())
	{
		outFile << "Number of Unique ASCII characters used: " << wordMap.size() << endl;
		outFile << "Character Map: (character -> frequency)" << endl;
		for(map<char, int >::const_iterator it = wordMap.begin();it != wordMap.end(); ++it)
		{
			outFile << it->first << " -> " << it->second << endl;
		}

		outFile << endl << endl << "Codes: (character -> Code)" << endl;
		for(map<char, std::vector<int> >::const_iterator it = codes.begin();it != codes.end(); ++it)
		{
			outFile << it->first << " -> ";
			for(int i = 0;i<it->second.size();i++)
			{
				outFile << it->second[i];
			}
			outFile << endl;

		}
		outFile.close();
	}
	else
	{
		cout << "Unable to open file" << endl;
	}

}



/*
 *	Function Name: createCharacterMap
 *	Parameters In: character map, vector of words
 *	Parameters Out: void
 *	Description: Create character map from input array of strings
 */
void createCharacterMap(std::map<char,int>& wordMap,std::vector<std::string> lines)
{
	for(int i = 0;i<lines.size();i++)
	{
		if(lines[i].length()>0)
		{
			for(int j = 0;j<lines[i].length();j++)
			{
				char key = lines[i][j];
				if(isascii(key))
				{
					std::map<char, int>::iterator it = wordMap.find(key);
					if (it != wordMap.end())
					{
						it->second++;
					}
					else
					{
						wordMap.insert ( std::pair<char,int>(key,1));
					}
				}
			}
		}
	}

}


/*
 *	Function Name: readBook
 *	Parameters In: Path of file/book, vector to store words of file
 *	Parameters Out: void
 *	Description: Create vector of words read from file.
 */
void readBook(std::string path,std::vector<std::string>& lines)
{
	string line;
	fstream myfile (path);
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			lines.push_back(line);
		}
		myfile.close();
	}
}


/*
 *	Function Name: getNewNode
 *	Parameters In: A character and corresponding frequency.
 *	Parameters Out: MinHeapNode
 *	Description: A utility function allocate a new min heap node with given character and frequency of the character
 */

struct MinHeapNode* getNewNode(char data, unsigned freq)
{
	struct MinHeapNode* temp =
			(struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
	temp->left = temp->right = NULL;
	temp->data = data;
	temp->frequency = freq;
	return temp;
}


/*
 *	Function Name: createMinHeap
 *	Parameters In: Capacity of min heap to be constructed.
 *	Parameters Out: MinHeapNode
 *	Description: A utility function to create a min heap of given capacity
 */

struct MinHeap* createMinHeap(unsigned capacity)
{
	struct MinHeap* minHeap =
			(struct MinHeap*) malloc(sizeof(struct MinHeap));
	minHeap->size = 0;  // current size is 0
	minHeap->capacity = capacity;
	minHeap->array =
			(struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}


/*
 *	Function Name: swapNodes
 *	Parameters In: Two nodes to swap.
 *	Parameters Out: void
 *	Description: A utility function to swap two min heap nodes
 */

void swapNodes(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

/*
 *	Function Name: minHeapify
 *	Parameters In: A minHeap and id from where to heapify
 *	Parameters Out: void
 *	Description: A standard heapify function.
 */

void minHeapify(struct MinHeap* minHeap, int idx)
{
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size &&
			minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
		smallest = left;

	if (right < minHeap->size &&
			minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
		smallest = right;

	if (smallest != idx)
	{
		swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}


/*
 *	Function Name: isSizeOne
 *	Parameters In: A minHeap node.
 *	Parameters Out: integer
 *	Description: A utility function to check if size of heap is 1 or not
 */

int isSizeOne(struct MinHeap* minHeap)
{
	return (minHeap->size == 1);
}


/*
 *	Function Name: extractMin
 *	Parameters In: A minHeap node.
 *	Parameters Out: MinHeapNode
 *	Description: A standard function to extract minimum value node from heap.
 */
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 0);
	return temp;
}


/*
 *	Function Name: insertMinHeap
 *	Parameters In: A MinHeap node and a MinHeapNode.
 *	Parameters Out: void
 *	Description: A utility function to insert a new node to Min Heap
 */
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
	++minHeap->size;
	int i = minHeap->size - 1;
	while (i && minHeapNode->frequency < minHeap->array[(i - 1)/2]->frequency)
	{
		minHeap->array[i] = minHeap->array[(i - 1)/2];
		i = (i - 1)/2;
	}
	minHeap->array[i] = minHeapNode;
}


/*
 *	Function Name: buildMinHeap
 *	Parameters In: A MinHeap node.
 *	Parameters Out: void
 *	Description: A standard function to build min heap
 */
void buildMinHeap(struct MinHeap* minHeap)
{
	int n = minHeap->size - 1;
	int i;
	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

/*
 *	Function Name: isLeaf
 *	Parameters In: A MinHeap root node.
 *	Parameters Out: integer
 *	Description: Utility function to check if this node is leaf.
 */
int isLeaf(struct MinHeapNode* root)
{
	return !(root->left) && !(root->right) ;
}


/*
 *	Function Name: createAndBuildMinHeap
 *	Parameters In: Character Map.
 *	Parameters Out: integer
 *	Description: Creates a min heap of capacity equal to size and inserts all character of data[] in min heap. Initially size of min heap is equal to capacity.
 */

struct MinHeap* createAndBuildMinHeap(std::map<char,int>wordMap)
{
	struct MinHeap* minHeap = createMinHeap(wordMap.size());
	int i = 0;
	for(map<char, int >::const_iterator it = wordMap.begin();it != wordMap.end(); ++it)
	{
		minHeap->array[i] = getNewNode(it->first,it->second);
		i++;
	}

	minHeap->size = wordMap.size();
	buildMinHeap(minHeap);
	return minHeap;
}

/*
 *	Function Name: buildHuffmanTree
 *	Parameters In: Character Map.
 *	Parameters Out: MinHeapNode
 *	Description: The main function that builds Huffman tree.
 */
struct MinHeapNode* buildHuffmanTree(std::map<char,int>wordMap)
{
	struct MinHeapNode *left, *right, *top;

	struct MinHeap* minHeap = createAndBuildMinHeap(wordMap);

	while (!isSizeOne(minHeap))
	{
		left = extractMin(minHeap);
		right = extractMin(minHeap);
		top = getNewNode('$', left->frequency + right->frequency);
		top->left = left;
		top->right = right;
		insertMinHeap(minHeap, top);
	}

	return extractMin(minHeap);
}


/*
 *	Function Name: storeHuffmanCodes
 *	Parameters In: MinHeapNode, arr and its size.
 *	Parameters Out: void
 *	Description: Huffman codes from the root of Huffman Tree.  It uses arr[] to store codes.
 */
void storeHuffmanCodes(struct MinHeapNode* root, int arr[], int top)
{
	if (root->left)
	{
		arr[top] = 0;
		storeHuffmanCodes(root->left, arr, top + 1);
	}

	if (root->right)
	{
		arr[top] = 1;
		storeHuffmanCodes(root->right, arr, top + 1);
	}

	if (isLeaf(root))
	{
		std::vector<int>temp;
		for(int i = 0;i<top;i++)
		{
			temp.push_back(arr[i]);
		}
		codes.insert ( std::pair<char,std::vector<int>>(root->data,temp));
		temp.clear();
	}
}


/*
 *	Function Name: generateHuffmanCodes
 *	Parameters In: A character Map.
 *	Parameters Out: void
 *	Description: The main function that builds a Huffman Tree and print codes by traversing the built Huffman Tree
 */
void generateHuffmanCodes(std::map<char,int>wordMap)
{
	struct MinHeapNode* root = buildHuffmanTree(wordMap);
	int arr[MAX_TREE_HT], top = 0;
	storeHuffmanCodes(root, arr, top);
}
