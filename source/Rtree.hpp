#include<bits/stdc++.h>
using namespace std;

class Node;

class Rtree{
	private:
		// x1 for key
		Node* root;
	public:
		Rtree();
		Rtree(vector<Node>, bool);
		insert(vector<Node>, bool);

		search_node(Node);
		delete_node(Node*);

};

class Node{
	private:
	public:
		bool m_isLeaf;
		int m_x1, m_x2, m_y1, m_y2;
		int m_type;
		string m_name;
		multimap<int, vector<Node*> > m_tree;

		Node(int x1, int y1, int x2, int y2, string name = "", bool isLeaf = true)
			: m_x1(x1), m_y1(y1), m_x2(y2), m_y2(y2), m_name(name), m_isLeaf(isLeaf);
		bool operator==(const Node&);
};


bool Node::operator==(const Node&){
	return 	x1 == Node.x1 && 
			x2 == Node.x2 &&
			y1 == Node.y1 &&
			y2 == Node.y2;
}


Rtree::Rtree(vector<Node> data, bool overlap = false){
	root = Node(INT_MIN, INT_MIN, INT_MAX, INT_MAX, "", false);
	query(init);
}

Rtree::insert(vector<Node> data){
	for(auto& node : data){
		




	}
}






