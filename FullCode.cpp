#include <iostream>
#include<vector>
#include<queue>
#include <iomanip>

using namespace std;
class Priority_Queue
{
private:
	void min_heapify(int Arr[], int i, int N)
	{
		int left = 2 * i;
		int right = 2 * i + 1;
		int smallest;
		if (left <= N and Arr[left] < Arr[i])
			smallest = left;
		else
			smallest = i;
		if (right <= N and Arr[right] < Arr[smallest])
			smallest = right;
		if (smallest != i)
		{
			swap(Arr[i], Arr[smallest]);
			min_heapify(Arr, smallest, N);
		}
	}
	void build_minheap(int Arr[], int N)
	{

		for (int i = N / 2; i >= 1; i--)
			min_heapify(Arr, i, N);
	}

public:
	Priority_Queue() { vector<pair<int, pair<int, int>>> queue; }
};

int nodes, edges, a, b, w;
vector<float> degree(nodes, 0.0);
vector<float> closs(nodes, 0.0);
vector<float> betw(nodes, 0.0);

void quickSort(vector<pair<int, int>> arr, int l, int r);

void DegreeCen(vector<vector<int>> adjlist, vector<float>& degree)
{
	for (int i = 0; i < nodes; i++)
	{
		degree.push_back(adjlist[i].size());

	}
}
int shortest(vector<vector<pair<int, int>>> adjlist, int src)
{
	priority_queue<pair<int, pair<int, int>>,
		vector<pair<int, pair<int, int>>>,
		greater<pair<int, pair<int, int>>>> nodes_q;
	int n = adjlist.size();
	vector<int> d(n, -1);
	vector<int> pi(n, -1);
	int summation = 0;
	nodes_q.push({ 0,{src,src} });
	while (!nodes_q.empty()) {
		pair<int, pair<int, int> > p = nodes_q.top();
		nodes_q.pop();
		int cur_node = p.second.first;
		int cur_prev_node = p.second.second;
		int cur_dis = p.first;
		if (d[cur_node] != -1)
			continue;
		d[cur_node] = cur_dis;
		summation += cur_dis;
		pi[cur_node] = cur_prev_node;


		for (int i = 0; i < adjlist[cur_node].size(); i++)
		{
			int next_node = adjlist[cur_node][i].first;
			int weight = adjlist[cur_node][i].second;
			if (d[next_node] != -1)
				continue;
			nodes_q.push({ cur_dis + weight,
				{ next_node, cur_node } });
		}
	}
	return summation;
	/*4 5
	0 1 1
	1 3 1
	0 3 5
	0 2 10
	2 3 4*/
}
void closeness(vector<vector<pair<int, int>>> adjlist, vector<float>& closs)
{

	int n = adjlist.size();
	for (int i = 0; i < n; i++)
	{
		//quickSort(adjlist[i], 0, adjlist[i].size() - 1);
		//sort(adjlist[i].begin(), adjlist[i].end());
		int sum = 0;
		sum = shortest(adjlist, i);

		if (sum != 0)
			closs.push_back((float)(n - 1) / (float)sum);
	}
}

float shortest_bet(vector<vector<pair<int, int>>> adjlist, int src, int v, int des)
{
	int n = adjlist.size();
	vector<int> short_count(n, 1); // 3dd el shortest paths
	vector<int> short_val(n, 0); // weight of shortest path
	vector<int> visited(n, 0);
	vector<int> parent(n, -1);
	vector<int> mwgoda_flag(n, 0);

	queue<int> nodes_q;
	nodes_q.push(src);
	visited[src] = 1;

	while (!nodes_q.empty())
	{
		int cur_node = nodes_q.front();
		nodes_q.pop();
		/*
		///////////////////////////////////////////////
		if (cur_node == des)
		{
			//short_count[des] -> num of shortest paths from src to count
			//mwgoda_flag[des] -> num of times v exist in shortest path from src to des
			break;
		}
		///////////////////////////////////////////////
		*/


		for (int i = 0; i < adjlist[cur_node].size(); i++)
		{
			int next_node = adjlist[cur_node][i].first;
			int weight = adjlist[cur_node][i].second;
			parent[next_node] = cur_node;


			if (visited[next_node] == 0)
			{
				if (next_node == v)
				{
					mwgoda_flag[next_node]++; // el node de mwgoda f kam shortest path mn src l des	
				}
				else
				{
					mwgoda_flag[next_node] = mwgoda_flag[cur_node];
				}

				short_val[next_node] = short_val[cur_node] + weight;
				// lw awl mra a3dy 3leha yb2a shortest mn next l cur hwa shortest el cur+ weight el next
				short_count[next_node] = short_count[cur_node];
				visited[next_node] = 1;
				nodes_q.push(next_node);
			}
			else if (visited[next_node] == 1)
			{
				if (short_val[next_node] == short_val[cur_node] + weight)
				{
					//yb2a el shortest distance sabta bs 3dd el shortest paths hyzed 3leh bto3 el cur
					short_count[next_node] += short_count[cur_node];
					if (next_node == v)
					{
						mwgoda_flag[next_node]++;
					}
					else
					{
						if (mwgoda_flag[cur_node] >= 0)
							mwgoda_flag[next_node] += mwgoda_flag[cur_node];
					}

				}
				else if (short_val[next_node] > short_val[cur_node] + weight)
				{
					short_val[next_node] = short_val[cur_node] + weight;
					short_count[next_node] = short_count[cur_node];
					if (next_node == v)
					{
						// y3ni el node kant mwgoda abl kda fe path atwal 	
						if (mwgoda_flag[next_node] > 0)
						{
							mwgoda_flag[next_node]--;
						}

					}
					else
					{
						mwgoda_flag[next_node] = mwgoda_flag[cur_node];
					}

				}

			}

		}


	}

	return (float)mwgoda_flag[des] / (float)short_count[des];

}
void bet(vector<vector<pair<int, int>>> adjlist, vector<float>& betw)
{

	int n = adjlist.size();
	for (int v = 0; v < n; v++)
	{
		float sum = 0.0;


		for (int src = 0; src < n; src++)
		{
			if (src == v)
				continue;
			for (int des = src + 1; des < n; des++)
			{
				if (src == des || des == v)
					continue;
				sum += shortest_bet(adjlist, src, v, des);

			}

		}

		betw.push_back((float)sum);
	}
}

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

void quickSort(vector<pair<int, int>> arr, int l, int r) {
	if (l >= r) return;
	int pivot = arr[l].first;
	int i = l + 1;
	int j = r;
	while (i <= j) {
		while (arr[i].first <= pivot) i++;
		while (arr[j].first > pivot) j--;
		if (i < j)
			swap(arr[i], arr[j]);
	}
	swap(arr[l], arr[j]);
	quickSort(arr, l, j - 1);
	quickSort(arr, i, r);
}
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
