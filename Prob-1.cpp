#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

class node {
public:
	int key1;
	int key2;
	int key3;
	int key4;
	node* up;
	node* node1;
	node* node2;
	node* node3;
	node* node4;
	node* node5;
	node();
	node(int key, node* parent);
	node(int key, node* left, node* right, node* parent);
	node(int key1, int key2, node* left, node* middle, node* right, node* parent);
	bool is1node();
	bool is2node();
	bool is3node();
	bool is4node();
	bool is5node();
	bool isLeaf();
	void removeFirst();
};

node::node() {
	key1 = NULL;
	key2 = NULL;
	key3 = NULL;
	key4 = NULL;
	up = nullptr;
	node1 = nullptr;
	node2 = nullptr;
	node3 = nullptr;
	node4 = nullptr;
	node5 = nullptr;
}

node::node(int key, node* parent) {
	key1 = key;
	key2 = NULL;
	key3 = NULL;
	key4 = NULL;
	up = parent;
	node1 = nullptr;
	node2 = nullptr;
	node3 = nullptr;
	node4 = nullptr;
	node5 = nullptr;
}

node::node(int key, node* left, node* right, node* parent) {
	key1 = key;
	key2 = NULL;
	key3 = NULL;
	key4 = NULL;
	up = parent;
	node1 = left;
	node2 = right;
	node3 = nullptr;
	node4 = nullptr;
	node5 = nullptr;
	if (left != nullptr) {
		left->up = this;
	}
	if (right != nullptr) {
		right->up = this;
	}
}

node::node(int key_first, int key_second, node* left, node* middle, node* right, node* parent) {
	key1 = key_first;
	key2 = key_second;
	key3 = NULL;
	key4 = NULL;
	up = parent;
	node1 = left;
	node2 = middle;
	node3 = right;
	node4 = nullptr;
	node5 = nullptr;
	if (left != nullptr) {
		left->up = this;
	}
	if (middle != nullptr) {
		middle->up = this;
	}
	if (right != nullptr) {
		right->up = this;
	}
}

bool node::is1node() {
	return (key1 == NULL && key2 == NULL && key3 == NULL && key4 == NULL);
}

bool node::is2node() {
	return (key1 != NULL && key2 == NULL && key3 == NULL && key4 == NULL);
}

bool node::is3node() {
	return (key1 != NULL && key2 != NULL && key3 == NULL && key4 == NULL);
}

bool node::is4node() {
	return (key1 != NULL && key2 != NULL && key3 != NULL && key4 == NULL);
}

bool node::is5node() {
	return (key1 != NULL && key2 != NULL && key3 != NULL && key4 != NULL);
}

bool node::isLeaf() {
	return (node1 == nullptr && node2 == nullptr && node3 == nullptr && node4 == nullptr);
}

void node::removeFirst() {

	key1 = key2;
	key2 = key3;
	key3 = NULL;

	node1 = node2;
	node2 = node3;
	node3 = node4;
	node4 = nullptr;
}

class tree {
public:
	vector<string> ans;
	node* root;
	tree();
	void insert(int key);

	void remove(int key);

	void show(node* node, string gap = "");

	void is(int key, node* now);
	void split(node* now, node* parent);
	node* check_next(int key, node* now);
	bool check_is(int key, node* now);
	void underflow(node* now, node* parent);
	void display();
};

void tree::display() {
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << endl;
	}
}

bool tree::check_is(int key, node* now) {
	if (key == now->key1) {
		return true;
	}
	else if (key == now->key2) {
		return true;
	}
	else if (key == now->key3) {
		return true;
	}
	else {
		return false;
	}
}

node* tree::check_next(int key, node* now) {
	if (now->is2node()) {
		if (key < now->key1) {
			return now->node1;
		}
		else {
			return now->node2;
		}
	}
	else if (now->is3node()) {
		if (key < now->key1) {
			return now->node1;
		}
		else if (key < now->key2) {
			return now->node2;
		}
		else {
			return now->node3;
		}
	}
	else if (now->is4node()) {
		if (key < now->key1) {
			return now->node1;
		}
		else if (key < now->key2) {
			return now->node2;
		}
		else if (key < now->key3) {
			return now->node3;
		}
		else {
			return now->node4;
		}
	}
	else {
		return now->node1;
	}
}

tree::tree() {
	root = nullptr;
}

void tree::insert(int key) {
	if (root == nullptr) {
		root = new node(key, nullptr);
		return;
	}
	node* parent = root;
	node* now = root;
	while (true) {
		if (now->isLeaf() == false) {
			parent = now;
			if (now->is2node()) {
				if (key < now->key1) {
					now = now->node1;
				}
				else if (key == now->key1) {
					ans.push_back(to_string(key) + " ALEADY EXISTS");
					break;
				}
				else {
					now = now->node2;
				}
			}
			else if (now->is3node()) {
				if (key < now->key1) {
					now = now->node1;
				}
				else if (key == now->key1) {
					ans.push_back(to_string(key) + " ALEADY EXISTS");
					break;
				}
				else if (key < now->key2) {
					now = now->node2;
				}
				else if (key == now->key2) {
					ans.push_back(to_string(key) + " ALEADY EXISTS");
					break;
				}
				else {
					now = now->node3;
				}
			}
			else if (now->is4node()) {
				if (key < now->key1) {
					now = now->node1;
				}
				else if (key == now->key1) {
					ans.push_back(to_string(key) + " ALEADY EXISTS");
					break;
				}
				else if (key < now->key2) {
					now = now->node2;
				}
				else if (key == now->key2) {
					ans.push_back(to_string(key) + " ALEADY EXISTS");
					break;
				}
				else if (key < now->key3) {
					now = now->node3;
				}
				else if (key == now->key3) {
					ans.push_back(to_string(key) + " ALEADY EXISTS");
					break;
				}
				else {
					now = now->node4;
				}
			}
		}
		else {	// �� ����� ��,
			if (now->is2node()) {
				if (key < now->key1) {
					now->key2 = now->key1;
					now->key1 = key;
					break;
				}
				else if (key == now->key1) {
					ans.push_back(to_string(key) + " ALEADY EXISTS");
					break;
				}
				else {
					now->key2 = key;
					break;
				}
			}
			else if (now->is3node()) {
				if (key < now->key1) {
					now->key3 = now->key2;
					now->key2 = now->key1;
					now->key1 = key;
					break;
				}
				else if (key == now->key1) {
					ans.push_back(to_string(key) + " ALEADY EXISTS");
					break;
				}
				else if (key < now->key2) {
					now->key3 = now->key2;
					now->key2 = key;
					break;
				}
				else if (key == now->key2) {
					ans.push_back(to_string(key) + " ALEADY EXISTS");
					break;
				}
				else {
					now->key3 = key;
					break;
				}
			}
			else if (now->is4node()) {
				if (key < now->key1) {
					now->key4 = now->key3;
					now->key3 = now->key2;
					now->key2 = now->key1;
					now->key1 = key;

				}
				else if (key == now->key1) {
					ans.push_back(to_string(key) + " ALEADY EXISTS");
					break;
				}
				else if (key < now->key2) {
					now->key4 = now->key3;
					now->key3 = now->key2;
					now->key2 = key;

				}
				else if (key == now->key2) {
					ans.push_back(to_string(key) + " ALEADY EXISTS");
					break;
				}
				else if (key < now->key3) {
					now->key4 = now->key3;
					now->key3 = key;

				}
				else if (key == now->key3) {
					ans.push_back(to_string(key) + " ALEADY EXISTS");
					break;
				}
				else {
					now->key4 = key;

				}
				if (now->is5node()) {
					split(now, parent);
				}
				break;
			}
		}
	}
}

void tree::split(node* now, node* p) {
	if (now == root) {
		root = new node(now->key3, nullptr);
		root->node1 = new node(now->key1, now->key2, now->node1, now->node2, now->node3, root);
		root->node2 = new node(now->key4, now->node4, now->node5, root);
	}
	else {
		if (p->is2node()) {
			if (p->node1 == now) {
				p->key2 = p->key1;
				p->key1 = now->key3;
				p->node3 = p->node2;
				p->node2 = new node(now->key4, now->node4, now->node5, p);
				p->node1 = new node(now->key1, now->key2, now->node1, now->node2, now->node3, p);
			}
			else {
				p->key2 = now->key3;
				p->node3 = new node(now->key4, now->node4, now->node5, p);
				p->node2 = new node(now->key1, now->key2, now->node1, now->node2, now->node3, p);
			}
		}
		else if (p->is3node()) {
			if (p->node1 == now) {
				p->key3 = p->key2;
				p->key2 = p->key1;
				p->key1 = now->key3;
				p->node4 = p->node3;
				p->node3 = p->node2;
				p->node2 = new node(now->key4, now->node4, now->node5, p);
				p->node1 = new node(now->key1, now->key2, now->node1, now->node2, now->node3, p);
			}
			else if (p->node2 == now) {
				p->key3 = p->key2;
				p->key2 = now->key3;
				p->node4 = p->node3;
				p->node3 = new node(now->key4, now->node4, now->node5, p);
				p->node2 = new node(now->key1, now->key2, now->node1, now->node2, now->node3, p);
			}
			else {
				p->key3 = now->key3;
				p->node4 = new node(now->key4, now->node4, now->node5, p);
				p->node3 = new node(now->key1, now->key2, now->node1, now->node2, now->node3, p);
			}
		}
		else if (p->is4node()) {
			if (p->node1 == now) {
				p->key4 = p->key3;
				p->key3 = p->key2;
				p->key2 = p->key1;
				p->key1 = now->key3;
				p->node5 = p->node4;
				p->node4 = p->node3;
				p->node3 = p->node2;
				p->node2 = new node(now->key4, now->node4, now->node5, p);
				p->node1 = new node(now->key1, now->key2, now->node1, now->node2, now->node3, p);
			}
			else if (p->node2 == now) {
				p->key4 = p->key3;
				p->key3 = p->key2;
				p->key2 = now->key3;
				p->node5 = p->node4;
				p->node4 = p->node3;
				p->node3 = new node(now->key4, now->node4, now->node5, p);
				p->node2 = new node(now->key1, now->key2, now->node1, now->node2, now->node3, p);
			}
			else if (p->node3 == now) {
				p->key4 = p->key3;
				p->key3 = now->key3;
				p->node5 = p->node4;
				p->node4 = new node(now->key4, now->node4, now->node5, p);
				p->node3 = new node(now->key1, now->key2, now->node1, now->node2, now->node3, p);
			}
			else {
				p->key4 = now->key3;
				p->node5 = new node(now->key4, now->node4, now->node5, p);
				p->node4 = new node(now->key1, now->key2, now->node1, now->node2, now->node3, p);
			}
		}
		if (p->is5node()) {
			split(p, p->up);
		}
	}

}

void tree::remove(int key) {
	node* now = root;
	node* parent = root;
	while (now != nullptr) {
		if (!now->isLeaf()) {
			parent = now;
			//-------------------------------------
			node* startNode = now;
			int kl; // KEY LOACATION Ű ��ġ ����صδ� ����.
			if (now->key1 == key) {
				now = now->node2;
				kl = 1;
			}
			else if (now->key2 == key) {
				now = now->node3;
				kl = 2;
			}
			else if (now->key3 == key) {
				now = now->node4;
				kl = 3;
			}
			else {	// �ش��ϴ� ���� ���� ���.
				now = check_next(key, now); // ���� ��忡 ���ٸ�, ���� ���� �� ���ΰ�

				continue;
			}

			while (now->node1 != nullptr) {
				now = now->node1;

			}



			if (kl == 1) {
				startNode->key1 = now->key1;

			}
			else if (kl == 2) {
				startNode->key2 = now->key1;
			}
			else if (kl == 3) {
				startNode->key3 = now->key1;
			}


			now->removeFirst();


			if (now->key1 == NULL) {

				underflow(now, now->up);
			}
			return; // ���� ���� �Ե��°� ���γ�� ���� ���������� ������ ���̴ϱ�.
			//-------------------------------------------------------------
		}
		else {	// �ܺγ���� ��� 1. ���� ��� ���, 2. �ִٸ� �����ε� 
			if (check_is(key, now)) { // �ִ�.

				if (now->is2node()) { // �ϳ��ۿ� ��� ����� underflow �߻�

					if (now == root) { // �Ѱ� �����ϰ� �Ѱ� ����� ��Ȳ ���.
						root = nullptr;
						break;
					}



					underflow(now, parent);
					return;

				}

				else { // �� ���� ����� ���� ( ���� ����� Ű�� 2��, 3���϶�)
					if (key == now->key1) {
						now->key1 = now->key2;
						now->key2 = now->key3;
						now->key3 = NULL;
						break;
					}
					else if (key == now->key2) {
						now->key2 = now->key3;
						now->key3 = NULL;
						break;
					}
					else if (key == now->key3) {
						now->key3 = NULL;
						break;
					}
				}
			}
			else { // ����.
				ans.push_back(to_string(key) + " NOT FOUND");
				break;
			}
		}
	}
}

void tree::underflow(node* now, node* parent) {

	while (true) {  // �� �ϴ� �ѹ� �����, ����÷ο��� �� ��� �����ߵǴµ�!! ���������, �� ���� ��Ʈ�϶���?

		if (parent->node1 == now) { // ���� ���ᰡ ���ٸ�
			if (parent->node2->is2node()) { // �� ������ �ڽ��� ȥ�ڶ��
				if (parent->is2node()) {  // �θ� 1����� -------------------------------------------------------
					parent->node2->key2 = parent->node2->key1;
					parent->node2->key1 = parent->key1;
					parent->node2->node3 = parent->node2->node2;
					parent->node2->node2 = parent->node2->node1;
					parent->node2->node1 = now->node1;
					if (now->node1 != nullptr) {
						now->node1->up = parent->node2; // �ٽ� �θ� ����Ī������Ѵ�!!
					}

					parent->key1 = NULL;
					parent->node1 = parent->node2;
					parent->node2 = nullptr;
				}
				else if (parent->is3node() || parent->is4node()) { // �θ� 2�����
					parent->node2->key2 = parent->node2->key1;
					parent->node2->key1 = parent->key1;
					parent->node2->node3 = parent->node2->node2;
					parent->node2->node2 = parent->node2->node1;
					parent->node2->node1 = now->node1;
					if (now->node1 != nullptr) {
						now->node1->up = parent->node2;
					}
					now->node1->up = parent->node2;
					parent->removeFirst();
					return;
				}
			}
			else if (parent->node2->is3node()) { // �� ������ �ڽ��� �ΰ����
				now->key1 = parent->key1;
				parent->key1 = parent->node2->key1;
				now->node2 = parent->node2->node1;
				if (parent->node2->node1 != nullptr) {
					parent->node2->node1->up = now;
				}
				parent->node2->removeFirst();
				return;
			}
			else if (parent->node2->is4node()) { // �� ������ �ڽ��� �������
				now->key1 = parent->key1;
				parent->key1 = parent->node2->key1;
				now->node2 = parent->node2->node1;
				if (parent->node2->node1 != nullptr) {
					parent->node2->node1->up = now;
				}

				parent->node2->removeFirst();
				return;
			}
		}
		else { // ���� ���ᰡ �ִٸ�


			if (parent->node2 == now) { // ���� ��尡 �ι� ° �ڽ��� ��


				if (parent->node1->is2node()) { // �� �� �ڽ��� ȥ�ڶ��
					if (parent->is2node()) { // �� �θ� ȥ�ڶ��!! �̶� �߻��Ѵ�!! *****-------------------------

						parent->node1->key2 = parent->key1;
						parent->key1 = NULL;
						parent->node1->node3 = now->node1;
						if (now->node1 != nullptr) {
							now->node1->up = parent->node1;
						}

						parent->node2 = nullptr;
						// parent->node1 �� �״�� ����.

					}
					else if (parent->is3node()) { // �θ� 2�����
						parent->node1->key2 = parent->key1;
						parent->node2 = parent->node3;
						parent->key1 = parent->key2;
						parent->node1->node3 = now->node1;
						if (now->node1 != nullptr) {
							now->node1->up = parent->node1;
						}

						return;
					}
					else if (parent->is4node()) { // �θ� 3�����
						parent->node1->key2 = parent->key1;
						parent->node2 = parent->node3;
						parent->node3 = parent->node4;
						parent->key1 = parent->key2;
						parent->key2 = parent->key3;
						parent->node1->node3 = now->node1;
						if (now->node1 != nullptr) {
							now->node1->up = parent->node1;
						}

						return;
					}
				}
				else if (parent->node1->is3node()) { // �� �� �ڽ��� �ΰ����
					now->key1 = parent->key1;
					parent->key1 = parent->node1->key2;
					parent->node1->key2 = NULL;
					now->node2 = now->node1;
					now->node1 = parent->node1->node3;
					if (parent->node1->node3 != nullptr) {
						parent->node1->node3->up = now;
					}

					parent->node1->node3 = nullptr;
					return;
				}
				else if (parent->node1->is4node()) { // �� �� �ڽ��� �������

					now->key1 = parent->key1;
					parent->key1 = parent->node1->key3;
					parent->node1->key3 = NULL;
					now->node2 = now->node1;
					now->node1 = parent->node1->node4;
					if (parent->node1->node4 != nullptr) {
						parent->node1->node4->up = now;
					}

					parent->node1->node4 = nullptr;
					return;
				}
			}
			else if (parent->node3 == now) { // ���� ��尡 ���� ° �ڽ��� ��
				if (parent->node2->is2node()) { // �� �� �ڽ��� ȥ�ڶ�� -- merge�� �Ͼ�µ� �θ��Ѱ��� �پ��Ƿ� �Ű�������
					parent->node2->key2 = parent->key2;
					parent->node2->node3 = now->node1;
					if (now->node1 != nullptr) {
						now->node1->up = parent->node2;
					}

					parent->node3 = parent->node4;
					parent->key2 = parent->key3;
				}
				else if (parent->node2->is3node()) { // �� �� �ڽ��� �ΰ����
					now->key1 = parent->key2;
					parent->key2 = parent->node1->key2;
					parent->node1->key2 = NULL;
					now->node2 = now->node1;
					now->node1 = parent->node2->node3;
					if (parent->node2->node3 != nullptr) {
						parent->node2->node3->up = now;
					}

					parent->node2->node3 = nullptr;
					return;
				}
				else if (parent->node2->is4node()) { // �� �� �ڽ��� �������
					now->key1 = parent->key2;
					parent->key2 = parent->node1->key3;
					parent->node1->key3 = NULL;
					now->node2 = now->node1;
					now->node1 = parent->node2->node4;
					if (parent->node2->node4 != nullptr) {
						parent->node2->node4->up = now;
					}

					parent->node2->node4 = nullptr;
					return;
				}
			}
			else { // ���� ��尡 �׹� ° �ڽ��� ��
				if (parent->node3->is2node()) { // �� �� �ڽ��� ȥ�ڶ��
					parent->node3->key2 = parent->key3;
					parent->node3->node3 = now->node1;
					if (now->node1 != nullptr) {
						now->node1->up = parent->node3;
					}

					parent->node4 = nullptr;
					parent->key3 = NULL;
					return;
				}
				else if (parent->node3->is3node()) { // �� �� �ڽ��� �ΰ����
					now->key1 = parent->key3;
					parent->key3 = parent->node1->key2;
					parent->node1->key2 = NULL;
					now->node2 = now->node1;
					now->node1 = parent->node3->node3;
					if (parent->node3->node3 != nullptr) {
						parent->node3->node3->up = now;
					}

					parent->node3->node3 = nullptr;
					return;
				}
				else if (parent->node3->is4node()) { // �� �� �ڽ��� �������
					now->key1 = parent->key3;
					parent->key3 = parent->node1->key3;
					parent->node1->key3 = NULL;
					now->node2 = now->node1;
					now->node1 = parent->node3->node4;
					if (parent->node3->node4 != nullptr) {
						parent->node3->node4->up = now;
					}

					parent->node3->node4 = nullptr;
					return;
				}
			}
		}

		if (parent == root) {
			root = parent->node1;
			return;
		}
		now = parent;
		parent = parent->up;

	}
}



void tree::is(int key, node* now) {
	node* startNode = now;
	int kl;
	if (now->key1 == key) {
		now = now->node2;
		kl = 1;
	}
	else if (now->key2 == key) {
		now = now->node3;
		kl = 2;
	}
	else if (now->key3 == key) {
		now = now->node4;
		kl = 3;
	}
	else {	// �ش��ϴ� ���� ���� ���.
		return;
	}

	while (now->node1 != nullptr) {
		now = now->node1;
	}

	if (kl == 1) {
		startNode->key1 = now->key1;
	}
	else if (kl == 2) {
		startNode->key2 = now->key1;
	}
	else if (kl == 3) {
		startNode->key3 = now->key1;
	}

	now->removeFirst();

	if (now->key1 == NULL) {
		now->up->node1 = nullptr;
	}
}



void tree::show(node* node, string gap) {
	if (root == nullptr) {
		ans.push_back("NO KEYS");
		return;
	}
	if (node == nullptr) {
		return;
	}
	if (node->is2node()) {
		ans.push_back(gap + to_string(node->key1));

		show(node->node1, gap + "    ");

		show(node->node2, gap + "    ");

	}
	else if (node->is3node()) {
		ans.push_back(gap + to_string(node->key1) + "," + to_string(node->key2));
		show(node->node1, gap + "    ");
		show(node->node2, gap + "    ");
		show(node->node3, gap + "    ");
	}
	else if (node->is4node()) {
		ans.push_back(gap + to_string(node->key1) + "," + to_string(node->key2) + "," + to_string(node->key3));
		show(node->node1, gap + "    ");
		show(node->node2, gap + "    ");
		show(node->node3, gap + "    ");
		show(node->node4, gap + "    ");
	}
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