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
