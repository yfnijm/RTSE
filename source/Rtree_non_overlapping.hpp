#include<bits/stdc++.h>
using namespace std;
#define DIMENSION 2

// The node's part
class Node_non_overlapping{
	private:
		vector<int> m_coor1, m_coor2;
	public:
		Node_non_overlapping(vector<int> data, int dim);
		
		bool operator== (Node_non_overlapping& cmp);
		int operator[](size_t id) { 
			return id < m_coor1.size() ? m_coor1[id] : m_coor2[id - m_coor1.size()];
		}

		vector<int> get_coor1(){ return m_coor1; }
		vector<int> get_coor2(){ return m_coor2; }
		void print_node();
};

Node_non_overlapping::Node_non_overlapping(vector<int> coors, int dim){
	if(coors.size() != dim * 2){
		cerr << "Nonvalid input!" << endl;
		exit(1);
	}
	m_coor1 = vector<int>{coors.begin(), coors.begin() + dim};
	m_coor2 = vector<int>{coors.end() - dim, coors.end()};
}


bool Node_non_overlapping::operator== (Node_non_overlapping& cmp){
	return m_coor1 == cmp.get_coor1() && m_coor2 == cmp.get_coor2();
}

void Node_non_overlapping::print_node(){
	cout << "coor: ";
	for(auto n : m_coor1)
		cout << n << " ";
	for(auto n : m_coor2)
		cout << n << " ";
	cout << endl;
}


struct cmp_node_non_overlapping{
	bool operator()( Node_non_overlapping& n1, Node_non_overlapping& n2){
		return n1.get_coor1() != n2.get_coor1() ? n1.get_coor1() < n2.get_coor1() : n1.get_coor2() < n2.get_coor2();
	}
};


//The Rtree main Structure
class Rtree_non_overlapping{
	private:
		int m_dim = DIMENSION;
		
		// the index for key
		int m_refer_index = 1;

		//know the max length need to search
		int m_max_refer_length = 0;
		int m_node_counter = 0;
		map<int, vector<Node_non_overlapping>> m_tree;
		map<Node_non_overlapping, vector<Node_non_overlapping>::iterator> m_fast_find;

	public:
		Rtree_non_overlapping(int dim) : m_dim(dim){};
		Rtree_non_overlapping(vector<vector<int>> init_data, int dim) : Rtree_non_overlapping(dim) 
			{ insert_nodes(init_data); };
	
		void insert_nodes(vector<vector<int>> data);
		//vector<bool> search_nodes(Node);
		void delete_nodes(vector<vector<int>> data);
		void print_nodes();
		size_t size() { return m_node_counter; };
		vector<vector<Node_non_overlapping>> spatial_queries(vector<pair<vector<int>, int>> query_list);

		vector<Node_non_overlapping> intersects(vector<int> spatial);
		vector<Node_non_overlapping> covered_by(vector<int> spatial);
		vector<Node_non_overlapping> disjoint(vector<int> spatial);
		vector<Node_non_overlapping> overlaps(vector<int> spatial);
		vector<Node_non_overlapping> within(vector<int> spatial);
};

void Rtree_non_overlapping::insert_nodes(vector<vector<int>> data){
	for(auto& coors : data){
		Node_non_overlapping cur_node(coors, m_dim);
		m_tree[coors[m_refer_index]].push_back(cur_node);

		m_node_counter ++;
	}
}

void Rtree_non_overlapping::delete_nodes(vector<vector<int>> data){	
	for(auto& coors : data){
		Node_non_overlapping tar_node(coors, m_dim);
		auto& vec = m_tree[coors[m_refer_index]];
		for(int i = 0; i < vec.size(); i++){
			if(vec[i] == tar_node){
				swap(vec[i], vec.back());
				vec.pop_back();


				m_node_counter--;
				break;
			}
		}
	}
}

void Rtree_non_overlapping::print_nodes(){
	for(auto& p : m_tree){
		for(auto& node : p.second){
			node.print_node();
		}
	}
}



vector<vector<Node_non_overlapping>> Rtree_non_overlapping::spatial_queries(vector<pair<vector<int>, int>> query_list){
	vector<vector<Node_non_overlapping>> res;
	
	for(auto& query : query_list){
		//hyper box
		auto [spatial, oper] = query;
		vector<Node_non_overlapping> find;
		if(spatial.size() != m_dim * 2){
			cerr << "query dim error" << endl;
			exit(1);
		}
			

		switch(oper){
			case 0:
				find = intersects(spatial);
				break;
			
			case 1:
				find = covered_by(spatial);
				break;

			case 2:
				find = disjoint(spatial);
				break;
			
			case 3:
				find = overlaps(spatial);
				break;

			case 4:
				find = within(spatial);
				break;
		}
		res.push_back(find);
	}
	return res;
}


vector<Node_non_overlapping> Rtree_non_overlapping::intersects(vector<int> hyperbox){
	vector<Node_non_overlapping> find;
	auto it = m_tree.lower_bound(hyperbox[m_refer_index] - m_max_refer_length);
	for(; it != m_tree.end() && it->first <= hyperbox[m_refer_index + m_dim]; it++){
		for(auto& node : it->second){
			int count = 0;
			for(int i = 0; i < m_dim; i++){
				if(node[i + m_dim] >= hyperbox[i] ||
					node[i] <= hyperbox[i + m_dim]){
					count++;
				}else break;
			}
			if(count == m_dim) find.push_back(node);
		}
	}
	return find;
}

vector<Node_non_overlapping> Rtree_non_overlapping::covered_by(vector<int> hyperbox){
	vector<Node_non_overlapping> find;
	auto it = m_tree.lower_bound(hyperbox[m_refer_index]);
	for(; it != m_tree.end() /*&& it->first <= hyperbox[m_refer_index + m_dim]*/; it++){
		for(auto& node : it->second){
			bool flag = true;
			for(int i = 0; i < m_dim; i++){
				if(node[i] < hyperbox[i]){
					flag = false;
					break;
				}
			}
			
			for(int i = m_dim; i < m_dim + m_dim; i++){
				if(node[i] > hyperbox[i]){
					flag = false;
					break;
				}
			}
				
			for(int i = 0; i < m_dim; i++){
				if(node[i] != hyperbox[i] && 
					node[i + m_dim] != hyperbox[i + m_dim]){
					flag = false;
					break;
				}
			}

			if(flag) find.push_back(node);
		}
	}
	return find;
}


vector<Node_non_overlapping> Rtree_non_overlapping::disjoint(vector<int> hyperbox){
	vector<Node_non_overlapping> find;
	auto it = m_tree.begin();
	for(; it != m_tree.end(); it++){
		for(auto& node : it->second){
			bool flag = false;
			for(int i = 0; i < m_dim; i++){
				if(node[i + m_dim] < hyperbox[i] ||
					node[i] > hyperbox[i + m_dim]){
					flag = true;
					break;
				}
			}
			if(flag) find.push_back(node);
		}
	}
	return find;
}

vector<Node_non_overlapping> Rtree_non_overlapping::overlaps(vector<int> hyperbox){
	vector<Node_non_overlapping> find;
	auto it = m_tree.lower_bound(hyperbox[m_refer_index] - m_max_refer_length);
	for(; it != m_tree.end() && it->first <= hyperbox[m_refer_index + m_dim]; it++){
		for(auto& node : it->second){
			int count = 0;
			for(int i = 0; i < m_dim; i++){
				if(node[i + m_dim] >= hyperbox[i] ||
					node[i] <= hyperbox[i + m_dim]){
					count++;
					break;
				}
			}
			if(count == m_dim) find.push_back(node);
		}
	}
	return find;
}

vector<Node_non_overlapping> Rtree_non_overlapping::within(vector<int> hyperbox){
	vector<Node_non_overlapping> find;
	auto it = m_tree.lower_bound(hyperbox[m_refer_index]);
	for(; it != m_tree.end() && it->first <= hyperbox[m_refer_index + m_dim]; it++){
		for(auto& node : it->second){
			bool flag = true;
			for(int i = 0; i < m_dim; i++){
				if(node[i] <= hyperbox[i]){
					flag = false;
					break;
				}
			}
			
			for(int i = m_dim; i < m_dim + m_dim; i++){
				if(node[i] >= hyperbox[i]){
					flag = false;
					break;
				}
			}
			
			if(flag) find.push_back(node);
		}
	}
	return find;
}


