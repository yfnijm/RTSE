#include<std/c++.h>
using namespace std;
#define DIMENSION 2


class Node_non_overlapping{
	private:
		vector<int> m_coor1, m_coor2;
	pubic:
		Node_non_overlapping(vector<int> data, int dim);
		bool operator== (Node_non_overlapping& cmp);
		vector<int> get_coor1(){ return m_coor1; }
		vector<int> get_coor2(){ return m_coor2; }
};

Node_non_overlapping::Node_non_overlapping(vector<int> coors, int dim){
	if(coors.size() != dim * 2){
		cerr << "Nonvalid input!" << endl;
		exit(1);
	}
	m_coor1 = vector<int>{coors.begin(), coors.begin() + dim};
	m_coor2 = vector<int>{coors.end() - dim, coors.end()};
}


Node_non_overlapping::operator== (Node_non_overlapping& cmp){
	return m_coor1 == cmp.get_coor1() && m_coor2 == cmp.get_coor2();
}


struct cmp_node_non_overlapping{
	bool operator()( Node_non_overlapping& n1, Node_non_overlapping& n2){
		return n1.get_coor1() != n2.get_coor1() ? n1.get_coor1() < n2.get_coor1() : n1.get_coor2() < n2.get_coor2();
	}
};



class Rtree_non_overlapping{
	private:
		int m_dim = DIMENSION;
		
		
		// the index for key
		int m_refer_index = 0;

		//know the max length need to search
		int m_max_refer_length = 0;

		map<int, vector<Node_non_overlapping>> m_tree;

		map<Node_non_overlapping, vector<Node_non_overlapping>::iterator, > m_fast_find;

	public:
		Rtree_non_overlapping(int dim) : m_dim(dim){};
		Rtree_non_overlapping(vector<vector<int>>, int dim);
		
		void insert_nodes(vector<Node>, int dim);
		vector<bool> search_nodes(Node);
		vector<int> delete_nodes(Node*);

};

Rtree_non_overlapping::Rtree_non_overlapping(vector<vector<int>> init_data, int dim){
	for(auto& coors : init_data){
		Node_non_overlapping cur_node(coors, m_dim);
		m_tree(coors[refer_index]).push_back(cur_node);
	}
	Rtree_non_overlapping(dim);
	insert(init_data, dim);
}

void Rtree_non_overlapping::insert_nodes(vector<vector<int>> data, int dim){
	for(auto& coors : data){
		Node_non_overlapping cur_node(coors, m_dim);
		m_tree(coors[m_refer_index]).push_back(cur_node);
	}
}

//not finish
void Rtree_non_overlapping::delete_nodes(vector<vector<int>> data, int dim){	
	for(int i=0; i<data.size(); i++){
		//Node_non_overlapping cur_node(coors, m_dim);
		//m_tree(coors[m_refer_index]).push_back(cur_node);
	}
}


vector<vector<Node_non_overlapping*>> spatial_queries(vector<pair<vector<int>, int>> query_list, int dim){
	vector<vector<Node_non_overlapping>> res;
	
	for(auto& query : query_list){
		//hyper box
		auto [spatial, oper] = query;
		vector<Node_non_overlapping> find;

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


vector<Node_non_overlapping> Rtree_non_overlapping::insert_nodes(vector<int> hyperbox){
	int ref_num = hyperbox[m_refer_index];
	int bound = hyperbox[(m_refer_index + hyperbox.size() / 2) % hyperbox];
	
	auto it = m_tree.l
	for(auto it = ){




	}


}











