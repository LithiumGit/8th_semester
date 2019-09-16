#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <functional>
#include <queue>

using namespace std;

struct node
{
	int index;
	string name;
	int isLeaf;
	string value;
	vector<string> condition;
	vector<node> child;
};

map<string, int> indexMaping;

double calculateEntropy(int row, vector<string> decisionValues)
{
	map<string, bool> previoulyTaken;
	vector<string> values;
	map<string, int> count;

	for (int i = 0; i < row; i++)
	{
		if (!previoulyTaken[decisionValues[i]])
		{
			values.push_back(decisionValues[i]);
			previoulyTaken[decisionValues[i]] = true;
		}
		count[decisionValues[i]]++;
	}

	double entropy = 0.0;
	if (values.size() == 1)
		return 0;
	for (int i = 0; i < values.size(); i++)
	{
		double probability = (double)count[values[i]] / row;
		entropy += probability * log2(probability);
	}
	entropy *= -1;
	return entropy;
}

void builtTree(int row, int col, string **a, node &currentNode, string *header)
{
	vector<string> decisionValues;

	for (int i = 0; i < row; i++)
		decisionValues.push_back(a[i][col - 1]);
	double previousEntropy = calculateEntropy(row, decisionValues);
	vector<string> valuesOfThisNode;
	map<string, int> rowCount;
	int index = -1;

	for (int i = 0; i < col - 1; i++)
	{
		double newEntroy = 0.0;
		map<string, int> rowCountTemp;
		map<string, bool> taken;
		vector<string> values;
		for (int j = 0; j < row; j++)
			if (!taken[a[j][i]])
			{
				taken[a[j][i]] = true;
				values.push_back(a[j][i]);
			}

		for (int j = 0; j < values.size(); j++)
		{
			vector<string> tempDecisionValues;
			for (int k = 0; k < row; k++)
				if (a[k][i] == values[j])
					tempDecisionValues.push_back(a[k][col - 1]);
			newEntroy += (double)tempDecisionValues.size() / row * calculateEntropy(tempDecisionValues.size(), tempDecisionValues);
			rowCountTemp[values[j]] = tempDecisionValues.size();
		}
		if (newEntroy < previousEntropy)
		{
			index = i;
			previousEntropy = newEntroy;
			valuesOfThisNode = values;
			rowCount = rowCountTemp;
		}
	}

	if (index != -1)
	{
		currentNode.name = header[index];
		currentNode.index = indexMaping[currentNode.name];
		currentNode.condition = valuesOfThisNode;
		node tempNode;
		//    	cout << "attribute name " << currentNode.name << endl;

		for (int i = 0; i < currentNode.condition.size(); i++)
		{
			node tempNode;
			string *tempHeader;
			tempHeader = new string[col - 1];
			int count = 0;
			for (int j = 0; j < col; j++)
			{
				if (j == index)
					continue;
				tempHeader[count] = header[j];
				count++;
			}

			string **arrTemp;
			arrTemp = new string *[rowCount[currentNode.condition[i]]];
			for (int j = 0; j < rowCount[currentNode.condition[i]]; j++)
				arrTemp[j] = new string[col - 1];

			int jj = 0;
			for (int j = 0; j < row; j++)
			{
				int kk = 0;
				bool test;
				for (int k = 0; k < col; k++)
				{
					if (k != index && a[j][index] == currentNode.condition[i])
					{
						arrTemp[jj][kk] = a[j][k];
						kk++;
					}
				}
				if (a[j][index] == currentNode.condition[i]) //if(test) continue;
					jj++;
			}
			//	cout << " >>>> >> condition name " << currentNode.condition[i] << endl;
			builtTree(rowCount[currentNode.condition[i]], col - 1, arrTemp, tempNode, tempHeader);
			currentNode.child.push_back(tempNode);
		}
	}

	else
	{
		currentNode.isLeaf = 1;
		//	cout << "- - - - - - - - - - " << endl;
		vector<string> v;
		map<string, int> map;
		for (int i = 0; i < row; i++)
		{
			if (map[a[i][col - 1]] == 0)
				v.push_back(a[i][col - 1]);
			map[a[i][col - 1]]++;
		}
		string finalValue = v[0];
		for (int i = 0; i < v.size(); i++)
			if (map[v[i]] > map[finalValue])
				finalValue = v[i];
		currentNode.value = finalValue;
		//cout <<"result  == == " <<  currentNode.value << endl;
		//cout << "----------------------------------" << endl;
	}
}

string testResult(node currentNode, string *a)
{
	if (currentNode.condition.size() == 0)
		return currentNode.value;

	int index = -1;
	for (int i = 0; i < currentNode.condition.size(); i++)
		if (a[currentNode.index] == currentNode.condition[i])
		{
			index = i;
			break;
		}

	if (index != -1)
		return testResult(currentNode.child[index], a);

	return "undefined condition";
}

void printTree(queue<node> nd, string prevStr)
{
	if (nd.empty())
		return;
	node currentNode = nd.front();
	nd.pop();
	//cout<<"Node name:"+currentNode.name+"\n";
	string identifier;
	if (currentNode.isLeaf == 1)
	{
		cout << prevStr +"-->" + currentNode.value + "\n";
		return;
	}

	string tempStr = "";

	for (unsigned i = 0; i < currentNode.child.size(); i++)
	{

		identifier = currentNode.child.at(i).name;

		tempStr = prevStr + currentNode.name + "=" + currentNode.condition.at(i) + "-->";
		nd.push(currentNode.child.at(i));
		printTree(nd, tempStr);
	}
}

int main(void)
{
	freopen("data.txt", "r", stdin);
	int row, col;
	cin >> row >> col;

	string **data, *header;
	data = new string *[row];
	header = new string[col];
	for (int i = 0; i < col; i++)
	{
		cin >> header[i];
		indexMaping[header[i]] = i;
	}

	for (int i = 0; i < row; i++)
		data[i] = new string[col];

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			cin >> data[i][j];

	node root;
	builtTree(row, col, data, root, header);
	queue<node> nodes;
	nodes.push(root);
	printTree(nodes, "");
	cout << "testing data:\n";
	string testData[4] = {"rainy", "hot", "high", "FALSE"};
	cout << testData[0] + "  " + testData[1] + "  " + testData[2] + "  " + testData[3] + "\n";
	cout << "play?\n";
	cout << "result:";
	cout << testResult(root, testData) << endl;

	for (int i = 0; i < row; i++)
		delete[] data[i];
	delete[] data;
	delete[] header;

	return 0;
}
