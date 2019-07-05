void DegreeCen(vector<vector<int>> adjlist, vector<float>& degree)
{
	for (int i = 0; i < nodes; i++)
	{
		degree.push_back(adjlist[i].size());

	}
}
