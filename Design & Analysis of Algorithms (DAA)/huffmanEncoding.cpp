#include <bits/stdc++.h>
using namespace std;

struct HuffmanNode {
	char data;
	int freq;
	HuffmanNode* left;
	HuffmanNode* right;
	
	HuffmanNode(char data, int freq) {
		left = right = nullptr;
		this->data = data;
		this->freq = freq;
	}
};
// ===============================
void printCodes(HuffmanNode *root, string str, unordered_map<char, string>& huffmanCode) {
	if (!root) return;
	
	if (!root->left && !root->right) {
		huffmanCode[root->data] = str;
	}
	
	printCodes(root->left, str + "0", huffmanCode);
	printCodes(root->right, str + "1", huffmanCode);
}
// ===============================
// Custom Comparator function to create min-heap
struct compare {
	bool operator()(HuffmanNode* l, HuffmanNode* r) {
		return l->freq > r->freq;	// If TRUE, the objects in the heap are swapped, to prioritize lower frequency chars
	}
};
// ===============================
unordered_map<char, string> encode(vector<char>& chars, vector<int>& freqs) {
	// Create a priority-queue as a min-heap
	priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> minHeap;
	
	// Populate it with the chars and frequencies
	for (int i = 0; i < chars.size(); i++) {
		minHeap.push(new HuffmanNode(chars[i], freqs[i]));
	}
	
	// Generate a Huffman Tree
	while (minHeap.size() != 1) {
		HuffmanNode* left = minHeap.top();
		minHeap.pop();
		
		HuffmanNode* right = minHeap.top();
		minHeap.pop();
		
		HuffmanNode *top = new HuffmanNode('$', (left->freq + right->freq));
		top->left = left;
		top->right = right;
		
		minHeap.push(top);
	}
	
	HuffmanNode *root = minHeap.top();
	unordered_map<char, string> huffmanCode;
	
	printCodes(root, "", huffmanCode);
	
	return huffmanCode;
}
// ===============================
int main() {
	cout << "-- Huffman Encoding --\n\n";
	string s;
	cout << "Enter string to encode: ";
	getline(cin, s);
	// cin >> s;
	
	unordered_map<char, int>mp;
	
	// Traverses the string char by char and stores chars along with frequencies in the map
	for (auto ch : s) {
		mp[ch]++;
	}
	
	// Map data is moved into vectors for ease of use
	vector<char> chars;
	vector<int> freqs;
	
	for (auto it: mp) {
		chars.push_back(it.first);
		freqs.push_back(it.second);
	}
	
	// Processes the input and returns map with chars and their corresponding codes
	unordered_map<char, string>huffman = encode(chars, freqs);
	
	int codeLengths = 0;
	
	cout << "\nCodes for each character:\n";
	for (auto pair : huffman) {
		cout << pair.first << " : " << pair.second << "\n";
		codeLengths += pair.second.length();
	}
	
	int bitSizes = 0;
	
	cout << "Encoded String: ";
	for (int i = 0; i < s.length(); i++) {
		bitSizes += huffman[s[i]].length();
		cout << huffman[s[i]] << " ";
	}
	cout << endl;
	cout << "\nOriginal Size of string: " << s.length() * 8 << " bits\n";
	cout << "\nSize of encoded string: " << bitSizes << " bits\n";
	
	/*
 	// the following commented code just gives extra information which would be required
  	// if hypothetically the encoded data were to be sent to a receiver
 
	int tableSize = huffman.size() + codeLengths;
	cout << "Size of table to send: " << tableSize << " bits";
	
	cout << "\n\nTotal bits to send: " << tableSize + bitSizes << " bits\n\n";
	*/
	
	return 0;
}
