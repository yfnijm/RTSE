#include<bits/stdc++.h>
using namespace std;
#define RTREE_MAX_SIZE 6
#define RTREE_MIN_SIZE 1
#define RTREE_REF 0
#define RTREE_DIM 3

int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}

// Leaf node
class Leaf_node{
	private:
		int m_dim = RTREE_DIM;

	public:
		Leaf_node() {}
		Leaf_node(vector<int>);

		vector<int> m_box;

		bool intersects(vector<int> spatial);
		bool covered_by(vector<int> spatial);
		bool disjoint(vector<int> spatial);
		bool overlaps(vector<int> spatial);
		bool within(vector<int> spatial);
};

Leaf_node::Leaf_node(vector<int> data){
	m_box = data;
}


bool Leaf_node::intersects(vector<int> hyperbox){
	int count = 0;
	for(int i = 0; i < m_dim; i++){
		if(m_box[i + m_dim] >= hyperbox[i] ||
				m_box[i] <= hyperbox[i + m_dim]){
			count++;
		}else break;
	}
	return (count == m_dim);
}

bool Leaf_node::covered_by(vector<int> hyperbox){
	bool flag = true;
	for(int i = 0; i < m_dim; i++){
		if(m_box[i] < hyperbox[i]){
			flag = false;
			break;
		}
	}

	for(int i = m_dim; i < m_dim + m_dim; i++){
		if(m_box[i] > hyperbox[i]){
			flag = false;
			break;
		}
	}

	for(int i = 0; i < m_dim; i++){
		if(m_box[i] != hyperbox[i] && 
				m_box[i + m_dim] != hyperbox[i + m_dim]){
			flag = false;
			break;
		}
	}
	return flag;
}


bool Leaf_node::disjoint(vector<int> hyperbox){
	bool flag = false;
	for(int i = 0; i < m_dim; i++){
		if(m_box[i + m_dim] < hyperbox[i] ||
				m_box[i] > hyperbox[i + m_dim]){
			flag = true;
			break;
		}
	}
	return flag;
}

bool Leaf_node::overlaps(vector<int> hyperbox){
	int count = 0;
	for(int i = 0; i < m_dim; i++){
		if(m_box[i + m_dim] >= hyperbox[i] ||
				m_box[i] <= hyperbox[i + m_dim]){
			count++;
			break;
		}
	}
	return (count == m_dim);
}

bool Leaf_node::within(vector<int> hyperbox){
	bool flag = true;
	for(int i = 0; i < m_dim; i++){
		if(m_box[i] <= hyperbox[i]){
			flag = false;
			break;
		}
	}

	for(int i = m_dim; i < m_dim + m_dim; i++){
		if(m_box[i] >= hyperbox[i]){
			flag = false;
			break;
		}
	}

	return (flag);
}


//Non Tree Node
class Node{
	private:
		int m_dim = RTREE_DIM;
	public:
		Node();

		int m_count = 0;
		vector<int> m_box = vector<int>(RTREE_DIM * 2);

		//using one of them
		vector<Node*> m_non_leaf_children;
		vector<Leaf_node*> m_leaf_data;

		void update_box();
		void add_leaf(vector<int> leaf);
		void add_non_leaf(Node* child);


		bool intersects(vector<int> spatial);
		bool covered_by(vector<int> spatial);
		bool disjoint(vector<int> spatial);
		bool overlaps(vector<int> spatial);
		bool within(vector<int> spatial);
};

Node::Node(){
	for(int i=0; i < m_dim; i++)
		m_box[i] = INT_MAX;

	for(int i=0; i < m_dim; i++)
		m_box[i + m_dim] = INT_MIN;
}


void Node::update_box(){
	if(m_leaf_data.size()){
		for(auto& leaf: m_leaf_data){
			for(int i = 0; i < m_dim; i++)
				m_box[i] = min(m_box[i], leaf->m_box[i]);

			for(int i = 0; i < m_dim; i++)
				m_box[i + m_dim] = max(m_box[i], leaf->m_box[i]);
		}
	}else{
		for(auto& child : m_non_leaf_children){
			for(int i = 0; i < m_dim; i++)
				m_box[i] = min(m_box[i], child->m_box[i]);

			for(int i = 0; i < m_dim; i++)
				m_box[i + m_dim] = max(m_box[i], child->m_box[i]);
		}
	}
}

void Node::add_leaf(vector<int> leaf_data){
	Leaf_node* leaf = new Leaf_node(leaf_data);

	m_leaf_data.push_back(leaf);
	m_count++;
		
	for(int i = 0; i < m_dim; i++)
		m_box[i] = min(m_box[i], leaf->m_box[i]);

	for(int i = 0; i < m_dim; i++)
		m_box[i + m_dim] = max(m_box[i], leaf->m_box[i]);
}


void Node::add_non_leaf(Node* child){
	m_non_leaf_children.push_back(child);
	m_count++;

	for(auto& child : m_non_leaf_children){
		for(int i=0; i<m_dim; i++)
			m_box[i] = min(m_box[i], child->m_box[i]);

		for(int i=0; i<m_dim; i++)
			m_box[i + m_dim] = max(m_box[i], child->m_box[i]);
	}
}

bool Node::intersects(vector<int> hyperbox){
	int count = 0;
	for(int i = 0; i < m_dim; i++){
		if(m_box[i + m_dim] >= hyperbox[i] ||
				m_box[i] <= hyperbox[i + m_dim]){
			count++;
		}else break;
	}
	return (count == m_dim);
}

bool Node::covered_by(vector<int> hyperbox){
	bool flag = true;
	for(int i = 0; i < m_dim; i++){
		if(m_box[i] < hyperbox[i]){
			flag = false;
			break;
		}
	}

	for(int i = m_dim; i < m_dim + m_dim; i++){
		if(m_box[i] > hyperbox[i]){
			flag = false;
			break;
		}
	}

	for(int i = 0; i < m_dim; i++){
		if(m_box[i] != hyperbox[i] && 
				m_box[i + m_dim] != hyperbox[i + m_dim]){
			flag = false;
			break;
		}
	}
	return flag;
}


bool Node::disjoint(vector<int> hyperbox){
	bool flag = false;
	for(int i = 0; i < m_dim; i++){
		if(m_box[i + m_dim] < hyperbox[i] ||
				m_box[i] > hyperbox[i + m_dim]){
			flag = true;
			break;
		}
	}
	return flag;
}

bool Node::overlaps(vector<int> hyperbox){
	int count = 0;
	for(int i = 0; i < m_dim; i++){
		if(m_box[i + m_dim] >= hyperbox[i] ||
				m_box[i] <= hyperbox[i + m_dim]){
			count++;
			break;
		}
	}
	return (count == m_dim);
}

bool Node::within(vector<int> hyperbox){
	bool flag = true;
	for(int i = 0; i < m_dim; i++){
		if(m_box[i] <= hyperbox[i]){
			flag = false;
			break;
		}
	}

	for(int i = m_dim; i < m_dim + m_dim; i++){
		if(m_box[i] >= hyperbox[i]){
			flag = false;
			break;
		}
	}

	return (flag);
}

//RTREE
class Rtree{
	private:
		Node* m_root;
		int m_dim = RTREE_DIM;

	public:
		//Rtree(){};
		Rtree(vector<vector<int>>);

		void insert();
		Node* access();
		bool topdown();
		void push();

		void sperate();
		void update();
		void delete_();
		void move();
		void replace();
		void restore();
		void getleft();
		void getright();
		void combine();
		
		void query();
	
		vector<vector<Leaf_node>> spatial_queries(vector<pair<vector<int>, int>> query_list);

		vector<Leaf_node> intersects(vector<int> spatial);
		vector<Leaf_node> covered_by(vector<int> spatial);
		vector<Leaf_node> disjoint(vector<int> spatial);
		vector<Leaf_node> overlaps(vector<int> spatial);
		vector<Leaf_node> within(vector<int> spatial);
};


Rtree::Rtree(vector<vector<int>> data){
	int size = data.size();
	int init_size = (RTREE_MAX_SIZE + RTREE_MIN_SIZE) / 2;

	//log2 (x) = logy (x) / logy (2)
	int height = ceil(log(size) / log(init_size));

	sort(data.begin(), data.end(), [](auto& n1, auto& n2){
		return n1[RTREE_REF] < n2[RTREE_REF];
	});

	vector<Node*> next, cur;
	for(int i=0; i<size; i += init_size){
		Node* new_node = new Node;
		for(int j = i; j < min(size, i + init_size); j++){
			new_node->add_leaf(data[i]);
		}
		cur.push_back(new_node);
	}

	while(cur.size() == 1){
		for(int i=0; i<cur.size(); i += init_size){
			Node* new_node = new Node;
			for(int j = i; j < min((int)cur.size(), i + init_size); j++){
				new_node->add_non_leaf(cur[i]);
			}
			next.push_back(new_node);
		}
		cur.clear();
		swap(next, cur);
	}

	m_root = cur[0];
}


vector<vector<Leaf_node>> Rtree::spatial_queries(vector<pair<vector<int>, int>> query_list){
	vector<vector<Leaf_node>> res;

	for(auto& query : query_list){
		//hyper box
		auto [spatial, oper] = query;
		vector<Leaf_node> find;
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


vector<Leaf_node> Rtree::intersects(vector<int> hyperbox){
	vector<Leaf_node> find;
	queue<Node*> candi_node;
	candi_node.push(m_root);
	
	while(candi_node.size()){
		int size = candi_node.size();
		while(size --){
			Node* cur_node = candi_node.front();
			candi_node.pop();

			if(cur_node->m_leaf_data.size()){
				for(auto leaf : cur_node->m_leaf_data){
					if(leaf->intersects(hyperbox))
						find.push_back(*leaf);
				}
			}else{
				for(auto node : cur_node->m_non_leaf_children){
					if(node->intersects(hyperbox))
						candi_node.push(node);
				}
			}
		}
	}

	return find;
}


vector<Leaf_node> Rtree::covered_by(vector<int> hyperbox){
	vector<Leaf_node> find;
	queue<Node*> candi_node;
	candi_node.push(m_root);
	
	while(candi_node.size()){
		int size = candi_node.size();
		while(size --){
			Node* cur_node = candi_node.front();
			candi_node.pop();

			if(cur_node->m_leaf_data.size()){
				for(auto leaf : cur_node->m_leaf_data){
					if(leaf->covered_by(hyperbox))
						find.push_back(*leaf);
				}
			}else{
				for(auto node : cur_node->m_non_leaf_children){
					if(node->intersects(hyperbox))
						candi_node.push(node);
				}
			}
		}
	}

	return find;
}

vector<Leaf_node> Rtree::disjoint(vector<int> hyperbox){
	vector<Leaf_node> find;
	queue<Node*> candi_node;
	candi_node.push(m_root);
	
	while(candi_node.size()){
		int size = candi_node.size();
		while(size --){
			Node* cur_node = candi_node.front();
			candi_node.pop();

			if(cur_node->m_leaf_data.size()){
				for(auto leaf : cur_node->m_leaf_data){
					if(leaf->disjoint(hyperbox))
						find.push_back(*leaf);
				}
			}else{
				for(auto node : cur_node->m_non_leaf_children){
					candi_node.push(node);
				}
			}
		}
	}

	return find;
}

vector<Leaf_node> Rtree::overlaps(vector<int> hyperbox){
	vector<Leaf_node> find;
	queue<Node*> candi_node;
	candi_node.push(m_root);
	
	while(candi_node.size()){
		int size = candi_node.size();
		while(size --){
			Node* cur_node = candi_node.front();
			candi_node.pop();

			if(cur_node->m_leaf_data.size()){
				for(auto leaf : cur_node->m_leaf_data){
					if(leaf->overlaps(hyperbox))
						find.push_back(*leaf);
				}
			}else{
				for(auto node : cur_node->m_non_leaf_children){
					if(node->intersects(hyperbox))
						candi_node.push(node);
				}
			}
		}
	}

	return find;
}


vector<Leaf_node> Rtree::within(vector<int> hyperbox){
	vector<Leaf_node> find;
	queue<Node*> candi_node;
	candi_node.push(m_root);
	
	while(candi_node.size()){
		int size = candi_node.size();
		while(size --){
			Node* cur_node = candi_node.front();
			candi_node.pop();

			if(cur_node->m_leaf_data.size()){
				for(auto leaf : cur_node->m_leaf_data){
					if(leaf->within(hyperbox))
						find.push_back(*leaf);
				}
			}else{
				for(auto node : cur_node->m_non_leaf_children){
					if(node->intersects(hyperbox))
						candi_node.push(node);
				}
			}
		}
	}

	return find;
}
