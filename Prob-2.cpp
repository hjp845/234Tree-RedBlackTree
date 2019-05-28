#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#define red "RED"
#define black "BLACK"
using namespace std;

class node {
public:
	node* left;
	node* right;
	node* up;
	int key;
	string color;
	node();
	node(int key, node* parent);
	bool isLeaf();
	bool hasRed();
	node* uncle();
};

node::node() {
	left = nullptr;
	right = nullptr;
	up = nullptr;
	key = NULL;
	color = black;
}


node leaf;  // 자 다 일로 모이겠습니다.~~~~
node* nil = &leaf;

node* node::uncle() {
	if (up->up->right == up) {
		return up->up->left;
	}
	else {
		return up->up->right;
	}
}

bool node::hasRed() {
	if (left->color == red || right->color == red) {
		return true;
	}
	return false;
}

bool node::isLeaf() {
	return (left == nil && right == nil);
}





node::node(int a, node* parent) {
	left = nil;
	right = nil;
	up = parent;
	key = a;
	color = red;
}

class tree {
public:
	vector<string> ans;
	node* root;
	tree();

	void insert(int key);
	void remove(int key);
	void show(node* now, string gap="");

	void check(node* now);
	void ddbb(node* now);
	node* get_sibling(node* now);
	void restruct(node* now);
	void display();
};

void tree::display() {
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << endl;
	}
}

void tree::restruct(node* now) {
	if (now->up->up == root) {
		if (now->key < now->up->key && now->key < now->up->up->key) { // now->up 이 대빵이 된다.
			now->up->up->left = now->up->right;
			now->up->right->up = now->up->up;
			now->up->right = now->up->up;
			now->up->up->up = now->up;
			root = now->up;
			root->up = nullptr;

			now->up->color = black;
			now->up->left->color = red;
			now->up->right->color = red;
		}
		else if (now->key > now->up->key && now->key < now->up->up->key) { // now가 대빵이 된다.
			now->up->right = now->left;
			now->left->up = now->up;
			now->up->up->left = now->right;
			now->right->up = now->up->up;
			now->left = now->up;
			now->right = now->up->up;
			now->left->up = now;
			now->right->up = now;
			root = now;
			root->up = nullptr;

			now->color = black;
			now->left->color = red;
			now->right->color = red;
		}
		else if (now->key > now->up->key && now->key > now->up->up->key) { // now->up 이 대빵이 된다.
			now->up->up->right = now->up->left;
			now->up->left->up = now->up->up;
			now->up->left = now->up->up;
			now->up->up->up = now->up;
			root = now->up;
			root->up = nullptr;

			now->up->color = black;
			now->up->left->color = red;
			now->up->right->color = red;
		}
		else if (now->key < now->up->key && now->key > now->up->up->key) { // now가 대빵이 된다.
			now->up->left = now->right;
			now->right->up = now->up;
			now->up->up->right = now->left;
			now->left->up = now->up->up;
			now->left = now->up->up;
			now->right = now->up;
			now->left->up = now;
			now->right->up = now;
			root = now;
			root->up = nullptr;

			now->color = black;
			now->left->color = red;
			now->right->color = red;
		}
	}
	else {  // 루트로부터 한창 밑에 있을 때
		if (now->up->up->up->right == now->up->up) { // 젤 윗노드가 오른쪽 자식일 때
			if (now->key < now->up->key && now->key < now->up->up->key) { // now->up 이 대빵이 된다.
				now->up->up->left = now->up->right;
				now->up->right->up = now->up->up;
				now->up->right = now->up->up;

				now->up->up = now->up->up->up;
				now->up->up->up = now->up;

				now->up->up->right = now->up;

				now->up->color = black;
				now->up->left->color = red;
				now->up->right->color = red;
			}
			else if (now->key > now->up->key && now->key < now->up->up->key) { // now 가 대빵이 된다.
				now->up->right = now->left;
				now->left->up = now->up;
				now->up->up->left = now->right;
				now->right->up = now->up->up;
				now->left = now->up;
				now->right = now->up->up;

				now->up = now->right->up;
				now->right->up = now;
				now->left->up = now;

				now->up->right = now;

				now->color = black;
				now->left->color = red;
				now->right->color = red;
			}
			else if (now->key > now->up->key && now->key > now->up->up->key) { // now->up 이 대빵이 된다.
				now->up->up->right = now->up->left;
				now->up->left->up = now->up->up;
				now->up->left = now->up->up;

				now->up->up = now->up->up->up;
				now->up->up->up = now->up;

				now->up->up->right = now->up;

				now->up->color = black;
				now->up->left->color = red;
				now->up->right->color = red;
			}
			else if (now->key < now->up->key && now->key > now->up->up->key) { // now가 대빵이 된다.
				now->up->left = now->right;
				now->right->up = now->up;
				now->up->up->right = now->left;
				now->left->up = now->up->up;

				now->left = now->up->up;
				now->right = now->up;

				now->up = now->left->up;
				now->left->up = now;
				now->right->up = now;

				now->up->right = now;

				now->color = black;
				now->left->color = red;
				now->right->color = red;
			}
		}
		else if (now->up->up->up->left == now->up->up) { // 젤 윗놈이 왼쪽 자식일 때					
			if (now->key < now->up->key && now->key < now->up->up->key) { // now->up 이 대빵이 된다.
				now->up->up->left = now->up->right;
				now->up->right->up = now->up->up;
				now->up->right = now->up->up;

				now->up->up = now->up->up->up;
				now->up->up->up = now->up;

				now->up->up->left = now->up;

				now->up->color = black;
				now->up->left->color = red;
				now->up->right->color = red;
			}
			else if (now->key > now->up->key && now->key < now->up->up->key) { // now 가 대빵이 된다.
				now->up->right = now->left;
				now->left->up = now->up;
				now->up->up->left = now->right;
				now->right->up = now->up->up;
				now->left = now->up;
				now->right = now->up->up;

				now->up = now->right->up;
				now->right->up = now;
				now->left->up = now;

				now->up->left = now;

				now->color = black;
				now->left->color = red;
				now->right->color = red;
			}
			else if (now->key > now->up->key && now->key > now->up->up->key) { // now->up 이 대빵이 된다.
				now->up->up->right = now->up->left;
				now->up->left->up = now->up->up;
				now->up->left = now->up->up;

				now->up->up = now->up->up->up;
				now->up->up->up = now->up;

				now->up->up->left = now->up;

				now->up->color = black;
				now->up->left->color = red;
				now->up->right->color = red;
			}
			else if (now->key < now->up->key && now->key > now->up->up->key) { // now가 대빵이 된다.
				now->up->left = now->right;
				now->right->up = now->up;
				now->up->up->right = now->left;
				now->left->up = now->up->up;

				now->left = now->up->up;
				now->right = now->up;

				now->up = now->left->up;
				now->left->up = now;
				now->right->up = now;

				now->up->left = now;

				now->color = black;
				now->left->color = red;
				now->right->color = red;
			}

		}
	}
	
}

tree::tree() {
	root = nullptr;
}

node* tree::get_sibling(node* now) {
	if (now->up->left == now) {
		return now->up->right;
	}
	else {
		return now->up->left;
	}
}

void tree::insert(int key) {
	if (!root) {
		root = new node(key, nullptr);
		root->color = black;
		return;
	}
	node* now = root;
	while (true) {
		if (key < now->key) {
			if (now->left == nil) {
				now->left = new node(key, now);
				check(now->left);
				return;
			}
			else {
				now = now->left;
			}
		}
		else if (key == now->key) {
			ans.push_back(to_string(key) + " ALREADY EXISTS");
			return;
		}
		else { // now->key < key
			if (now->right == nil) {
				now->right = new node(key, now);
				check(now->right);
				return;
			}
			else {
				now = now->right;
			}
		}
	}	
}

void tree::check(node* now) {
	if (now == root || now->up == root) {
		return;
	}
	if (now->up->color == red) {
		if (get_sibling(now->up)->color == red) { // Recoloring
			now->up->color = black;
			get_sibling(now->up)->color = black;
			now->up->up->color = red;
			root->color = black;
			check(now->up->up);
		}
		else {  // Restructing
			restruct(now);
			
		}
	}
	else {
	return;
	}
}

void tree::ddbb(node* now) {
	if (get_sibling(now)->hasRed() && get_sibling(now)->color == black) {
		if (get_sibling(now)->left->color == red) { // restructing 동료의 왼쪽 자식부터 레드인지 확인
			restruct(get_sibling(now)->left);
		}
		else { // resturucting
			restruct(get_sibling(now)->right);
		}
		now->up->up->color = now->up->color;
		now->up->color = black;
		get_sibling(now->up)->color = black;
	}
	else if (get_sibling(now)->color == black && get_sibling(now)->left->color == black && get_sibling(now)->right->color == black) {
		if (now->up->color == red) {
			now->up->color = black;
			get_sibling(now)->color = red;
		}
		else {
			get_sibling(now)->color = red;
			now->up->color = black;
			ddbb(now->up); // 재귀 !! --------------------------------------------------------------
		}
	}
	else if (get_sibling(now)->color == red) {
		if (now->up->right == now) {
			restruct(now->up->left->left);
			now->up->color = red;
			get_sibling(now->up)->color = black;
			now->up->up->color = black;
			ddbb(now);
		}
		else {
			restruct(now->up->right->right);
			now->up->color = red;
			get_sibling(now->up)->color = black;
			now->up->up->color = black;
			ddbb(now);
		}
	}
}

void tree::remove(int key) {
	node* now = root;
	while (true) {
		if (key < now->key) {
			if (now->left == nil) {
				ans.push_back(to_string(key) + " NOT FOUND");
				return;
			}
			else {
				now = now->left;
			}
		}
		else if (key == now->key) {
			if (now->isLeaf()) { // 외부노드라면
				if (now->color == red) { // red라면 간단하게 지우고 끝난다.
					if (now->up->left == now) {
						now->up->left = nil;
						return;
					}
					else {
						now->up->right = nil;
						return;
					}
				}
				else { // 근데 외부노드+ black 이라면 더블블랙 발생!
					if (now->up->left == now) {
						now->up->left = nil;
						nil->up = now->up;
						ddbb(nil);
						return;
					}
					else {
						now->up->right = nil;
						nil->up = now->up;
						ddbb(nil);
						return;
					}
				}
			}
			else { // 내부노드라면				
				if (now->right == nil) {
					if (now->up->right == now) {
						now->up->right = now->left;
						if (now->color == black) {
							ddbb(now->left);
							return;
						}
						else {
							return;
						}
					}
					else {
						now->up->left = now->left;
						if (now->color == black) {
							ddbb(now->left);
							return;
						}
						else {
							return;
						}
					}
				}
				else {
					node* end = now->right;
					while (end->left != nil) {
						end = end->left;
					}
					now->key = end->key;
					if (end->color == black) {
						end->up->left = end->right;
						end->right->up = end->up;
						ddbb(end->right);
						return;
					}
					else {
						end->up->left = nil;
						return;
					}
				}							
			}
		}
		else { // key > now->key;
			if (now->right == nil) {
				ans.push_back(to_string(key) + " NOT FOUND");
				return;
			}
			else {
				now = now->right;
			}
		}
	}
}

void tree::show(node* now, string gap) {
	if (root == nullptr) {
		ans.push_back("NO KEYS");
		return;
	}
	if (now->key == NULL) {
		ans.push_back(gap + "LEAF" + " (" + now->color + ")");
		return;
	}
	ans.push_back(gap + to_string(now->key) + " (" + now->color + ")");
	show(now->left, gap + "    ");
	show(now->right, gap + "    ");
}

int main() {
	tree hjp;
	while (true) {
		string input_getline;
		getline(cin, input_getline);
		stringstream input_ss(input_getline);
		string input;
		input_ss >> input;
		if (input == "SHOWTREE") {
			hjp.show(hjp.root);
		}
		else if (input == "INSERT") {
			string key_string;
			input_ss >> key_string;
			int key;
			key = stoi(key_string);
			hjp.insert(key);
		}
		else if (input == "DELETE") {
			string key_string;
			input_ss >> key_string;
			int key;
			key = stoi(key_string);
			hjp.remove(key);
		}
		else if (input == "QUIT") {
			hjp.display();
			return 0;
		}
	}

}