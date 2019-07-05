#include <iostream>
#include<vector>
#include<queue>
#include <iomanip>
#include "header.h"
#include "degree.cpp"
#include "clossness.cpp"
#include "betweennes.cpp"

int nodes, edges, a, b, w;
vector<float> degree(nodes, 0.0);
vector<float> closs(nodes, 0.0);
vector<float> betw(nodes, 0.0);

int main()
{
	char c;
	cout << "Enter type of centrality: 'D' for Degree, 'C' for Closeness, & 'B' for Betweennes\n";
	cin >> c;
	if (c == 'D')
	{
		cin >> nodes >> edges;
		vector<vector<int>> mylist(nodes, vector<int>(0));
		for (int i = 0; i < edges; i++)
		{
			cin >> a >> b >> w;
			mylist[a].push_back(b);
			mylist[b].push_back(a);
		}
		DegreeCen(mylist, degree);
		for (int i = 0; i < mylist.size(); i++)
			cout << degree[i] << "\n";
	}
	else if (c == 'C')
	{
		cin >> nodes >> edges;
		vector<vector<pair<int, int>>> mylistos(nodes, vector<pair<int, int>>(0));
		for (int i = 0; i < edges; i++)
		{
			cin >> a >> b >> w;
			mylistos[a].push_back({ b,w });
			mylistos[b].push_back({ a,w });
		}
		closeness(mylistos, closs);
		for (int i = 0; i < mylistos.size(); i++)
			cout << closs[i] << "\n";
	}
	else if (c == 'B')
	{
		cin >> nodes >> edges;
		vector<vector<pair<int, int>>> mylistos(nodes, vector<pair<int, int>>(0));

		for (int i = 0; i < edges; i++)
		{
			cin >> a >> b >> w;
			mylistos[a].push_back({ b,w });
			mylistos[b].push_back({ a,w });
		}

		bet(mylistos, betw);
		for (int i = 0; i < mylistos.size(); i++)
		{
			std::cout << std::fixed;
			std::cout << std::setprecision(8);
			std::cout << betw[i] << "\n";
		}
	}


}
