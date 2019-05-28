<h1> 자료구조 과제 HW#3</h1>

<p> Prof.조성현</p>

<p> Asis. 지서연 </p>

<p> 201711205 황정평 </p>



<h4>-컴파일 환경</h4>

window10, Visualstudio2017, _MSC_VER: 1916, MSYC++14.16

<h2> Prob-1.cpp </h2>

<h4>-알고리즘</h4>

1) 2-4(tree)는 이진탐색트리에서 더 확장되어 한 노드에 최대 3개의 키와 4개의 서브노드를 가질 수 있는 자료구조이다. 또한 높이를 맞춰주기 위해 삽입, 삭제 과정에서 밸런싱이 이루어진다. 5node가 되면 split  되는 형식이며, root 노드에서 split이 일어났을 때야만 트리의 height가 증가한다.

2) 5node를 split 할 땐, 3node와 2node로 나눈다.

3) 삭제시 inorder successor를 이용한다.

4) 삭제에서 underflow 발생시 동료는 왼쪽 동료를 이용한다. 없다면 오른쪽 동료를 이용한다.

<h4>-코드 설명</h4>

```c++
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;
```

자료구조 string과 vector를, 또한 답을 출력하기 위해 sstream도 받아온다.

```c++
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
```

key값 4개와, node5개, 부모노드 1개, 기본생성자, key값과 부모를 갖는 생성자, 거기에 자식둘까지 갖는 생성자, 거기에 키값 하나 더와 자식을 하나더 갖는 생성자, 몇 노드인지 체크해주는 함수들, 말단 노드인지 체크해주는 함수, 첫키와 첫노드를 삭제해주는 함수를 선언한다.

```c++
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
```

기본생성자이다. NULL 값과 nullptr 값을 갖는다.

```c++
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
```

1) key값과 부모노드를 갖는 노드를 생성한다.

2) key값과 부모노드를 갖고, node1, node2를 갖는 노드를 생성한다.

3) key값과 부모노드를 갖고, node1, node2, node3을 갖는 노드를 생성한다.

```c++
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
```

각 노드들이 몇 노드 함수인지 구분할 수 있게 만든 함수들이다. 마지막 함수는 말단노드인지 확인할 수 있게 만든 함수이다.

```c++
void node::removeFirst() {

	key1 = key2;
	key2 = key3;
	key3 = NULL;

	node1 = node2;
	node2 = node3;
	node3 = node4;
	node4 = nullptr;
}
```

노드의 key1 값과, node1이 사라지고 왼쪽으로 한칸씩 당겨온다.

```c++
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
```

답을 담는 ans,  root노드를 가리키는 포인터, 삽입함수, 삭제함수, 트리를 보여주는 함수, inorder successor를 처리하는 함수, 3과 2node로 split해주는 함수, 키값과 비교하여 다음 노드를 가리키는 포인터를 반환하는 함수, 노드에 특정 key값이 존재하는지 확인하는 함수, underflow발생시 처리하는 함수, ans를 보여주는 함수를 선언한다.

```c++
tree::tree() {
	root = nullptr;
}
```

기본생성자이다. root는 아무것도 가리키지 못한다.

```c++
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
		else {	// 잎 노드일 때,
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
```

key값을 인자로 받고 삽입하는 함수이다. 내부 노드라면, 각 노드의 key값과 비교하여 작다면 왼쪽으로, 크다면 오른쪽으로 간다. 같다면 이미 존재한다고 출력한다. 외부 노드라면, 작다면 왼쪽에 추가하고, 크다면 오른쪽에 추가한다.

```c++
void tree::remove(int key) {
	node* now = root;
	node* parent = root;
	while (now != nullptr) {
		if (!now->isLeaf()) {
			parent = now;
			//-------------------------------------
			node* startNode = now;
			int kl; // KEY LOACATION 키 위치 기억해두는 변수.
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
			else {	// 해당하는 값이 없는 경우.
				now = check_next(key, now); // 내부 노드에 없다면, 이제 어디로 갈 것인가

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
			return; // 여기 까지 왔따는건 내부노드 값을 성공적으로 삭제한 것이니까.
			//-------------------------------------------------------------
		}
		else {	// 외부노드일 경우 1. 없는 경우 고려, 2. 있다면 삭제인데 
			if (check_is(key, now)) { // 있다.

				if (now->is2node()) { // 하나밖에 없어서 지우면 underflow 발생

					if (now == root) { // 한개 생성하고 한개 지우는 상황 대비.
						root = nullptr;
						break;
					}



					underflow(now, parent);
					return;

				}

				else { // 맘 편히 지우기 가능 ( 현재 노드의 키가 2개, 3개일때)
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
			else { // 없다.
				ans.push_back(to_string(key) + " NOT FOUND");
				break;
			}
		}
	}
}
```

key값을 인자로 받고 삭제하는 함수이다. 내부노드에 존재한다면, inorder successor를 불러오고, 그 노드는 삭제하는데 underflow가 발생하면 처리해준다. 외부노드에 존재한다면, 현재노드가 한개라면 underflow 처리를 해주고, 한개 이상이라면 그냥 삭제한다. 존재하지 않는다면 NOT FOUND를 출력한다.

```c++
void tree::underflow(node* now, node* parent) {

	while (true) {  // 자 일단 한번 지우고, 언더플로우일 때 계속 돌려야되는데!! 비어있을때, 자 이제 루트일때는?

		if (parent->node1 == now) { // 왼쪽 동료가 없다면
			if (parent->node2->is2node()) { // 그 오른쪽 자식이 혼자라면
				if (parent->is2node()) {  // 부모가 1개라면 -------------------------------------------------------
					parent->node2->key2 = parent->node2->key1;
					parent->node2->key1 = parent->key1;
					parent->node2->node3 = parent->node2->node2;
					parent->node2->node2 = parent->node2->node1;
					parent->node2->node1 = now->node1;
					if (now->node1 != nullptr) {
						now->node1->up = parent->node2; // 다시 부모를 리매칭해줘야한다!!
					}

					parent->key1 = NULL;
					parent->node1 = parent->node2;
					parent->node2 = nullptr;
				}
				else if (parent->is3node() || parent->is4node()) { // 부모가 2개라면
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
			else if (parent->node2->is3node()) { // 그 오른쪽 자식이 두개라면
				now->key1 = parent->key1;
				parent->key1 = parent->node2->key1;
				now->node2 = parent->node2->node1;
				if (parent->node2->node1 != nullptr) {
					parent->node2->node1->up = now;
				}
				parent->node2->removeFirst();
				return;
			}
			else if (parent->node2->is4node()) { // 그 오른쪽 자식이 세개라면
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
		else { // 왼쪽 동료가 있다면


			if (parent->node2 == now) { // 현재 노드가 두번 째 자식일 때


				if (parent->node1->is2node()) { // 그 옆 자식이 혼자라면
					if (parent->is2node()) { // 그 부모가 혼자라면!! 이때 발생한다!! *****-------------------------

						parent->node1->key2 = parent->key1;
						parent->key1 = NULL;
						parent->node1->node3 = now->node1;
						if (now->node1 != nullptr) {
							now->node1->up = parent->node1;
						}

						parent->node2 = nullptr;
						// parent->node1 은 그대로 간다.

					}
					else if (parent->is3node()) { // 부모가 2개라면
						parent->node1->key2 = parent->key1;
						parent->node2 = parent->node3;
						parent->key1 = parent->key2;
						parent->node1->node3 = now->node1;
						if (now->node1 != nullptr) {
							now->node1->up = parent->node1;
						}

						return;
					}
					else if (parent->is4node()) { // 부모가 3개라면
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
				else if (parent->node1->is3node()) { // 그 옆 자식이 두개라면
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
				else if (parent->node1->is4node()) { // 그 옆 자식이 세개라면

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
			else if (parent->node3 == now) { // 현재 노드가 세번 째 자식일 때
				if (parent->node2->is2node()) { // 그 옆 자식이 혼자라면 -- merge가 일어나는데 부모한개가 줄어드므로 신경써줘야함
					parent->node2->key2 = parent->key2;
					parent->node2->node3 = now->node1;
					if (now->node1 != nullptr) {
						now->node1->up = parent->node2;
					}

					parent->node3 = parent->node4;
					parent->key2 = parent->key3;
				}
				else if (parent->node2->is3node()) { // 그 옆 자식이 두개라면
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
				else if (parent->node2->is4node()) { // 그 옆 자식이 세개라면
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
			else { // 현재 노드가 네번 째 자식일 때
				if (parent->node3->is2node()) { // 그 옆 자식이 혼자라면
					parent->node3->key2 = parent->key3;
					parent->node3->node3 = now->node1;
					if (now->node1 != nullptr) {
						now->node1->up = parent->node3;
					}

					parent->node4 = nullptr;
					parent->key3 = NULL;
					return;
				}
				else if (parent->node3->is3node()) { // 그 옆 자식이 두개라면
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
				else if (parent->node3->is4node()) { // 그 옆 자식이 세개라면
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
```

underflow발생시 일단 왼쪽 동료가 있는지 오른쪽 동료가 있는지로 나뉜다. 그 후, 현재 노드가 몇번째 자식인지로 나뉜다. 그 후, 동료의 키값이 몇개인지로 나뉜다. 그 후 부모의 키값이 몇개인지로 나뉜다. underflow의 반복을 위하여 키값이 모두 사라졌다면, 자식을 있는 노드는 node1으로 가리켜야한다. 

underflow의 반복은 동료도 키값이 하나이고, 부모도 키값이 하나일 때 일어난다.

```c++
void tree::is(int key, node* now) {
	node* startNode = now;
	int kl;  // Key Location 키 위치를 기억해두는 변수이다.
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
	else {	// 해당하는 값이 없는 경우.
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
```

인수로 들어온 노드에서 특정 key값을 갖는 키를 찾고, 그 키 기준에서 inorder successor이용하는 함수이다.

```c++
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
```

우선 인수로들어온 노드가 root노드인지 확인한다. root노드라면 새로운 노드를 생성하고 root를 변경한다. (height 증가) 일단 이 함수가 호출되었다는 것 자체가 어떤 노드를 split한다는 것이다. root노드가 아니라면, 부모의 키값의 개수에 따라 처리해준다. 기본 방식은 key3이 올라가고 왼쪽 자식으로 key1, key2 를 갖는 노드, 오른쪽 자식으로 key4를 갖는 노드를 이루헤 해준다. 그 후, 부모노드가 overflow 되었다면 부모노드를 기준으로 한번 더 해준다.

```c++
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
```

인자로 들어온 노드에서 인자로 들어온 key값을 기준으로 다음 노드는 어디인지 가리켜주는 포인터를 반환하는 함수이다.

```c++
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
```

인자로 들어온 노드에 key값이 존재하면 true, 존재하지 않는다면 false 를 반환한다.

```c++
void tree::display() {
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << endl;
	}
}
```

ans에 담긴 답을 출력해주는 함수이다.

```c++
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
```

stringstream을 이용하여 입력값을 받았다. 각 입력값에 맞게 올바른 함수를 호출하도록 구현하였다.

<h4>-결과창</h4>

![문제1 콘솔창](D:\DG3-1\자료구조\과제3\문제1 콘솔창.png)

QUIT를 기준으로 위가 입력값들이고, 아래가 출력값들이다. 주어진 예제 입출력 그대로 잘 나온것을 확인할 수 있다.



<h2>Prob-2.cpp</h2>

<h4>-알고리즘</h4>

1) 문제 1과 마찬가지로 이진탐색트리 기반의 트리이다. MAP은 key와 그에 해당하는 value를 같이 저장하지만, 본 숙제에서는 key만을 저장한다. 레드블랙트리에는 몇가지 규칙이 있다. 첫번 째, 모든 말단노드에서 루트까지 검은색 노드의 수를 세아렸을 때 모두 같아야한다. 두번 째, 빨간 노드가 연속으로 나오면 안된다. 세번 째, 루트노드는 무조건 검은색 노드이다.

2) 삭제시 inorder successor를 이용한다.

3) 더블블랙을 처리할 때, 동료가 black이고 최소 하나의 red자식을 가지고 있을 때, 왼쪽 자식부터 확인하여 이용한다.

4) 더블블랙 처리할 때, adjustment과정에서 LL rotate 또는 RR rotate 가 일어나게끔 한다.

<h4>-코드 설명</h4>

```c++
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#define red "RED"
#define black "BLACK"
using namespace std;

```

자료구조 string, vector를 받아오고 string stream을 쓰기위해 sstream 도 받아온다.  red변수를, black변수를 각각 "RED", "BLACK" 로 선언한다.

```c++
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
```

왼쪽, 오른쪽 자식, 부모노드를 가리키는 포인터를 선언한다. key변수를 선언한다. color변수도 선언한다. 기본생성자, 인수두개 받는 생성자, 말단노드인지 확인해주는 함수, 빨간자식을 가지는지 확인해주는 함수, 삼촌노드를 가리키는 포인터를 선언한다.

```c++
node::node() {
	left = nullptr;
	right = nullptr;
	up = nullptr;
	key = NULL;
	color = black;
}
```

기본생성자이다. color만  black으로 건드려준다.

```c++
node leaf;  // 자 다 일로 모이겠습니다.~~~~
node* nil = &leaf;
```

leaf노드를 선언한다. 모든 내부 말단노드들은 이 하나의 node leaf를 가리킬 것이다.

```c++
bool node::isLeaf() {
	return (left == nil && right == nil);
}
```

내부 말단노드이면 true, 아니면 false를 반환한다.

```c++
bool node::hasRed() {
	if (left->color == red || right->color == red) {
		return true;
	}
	return false;
}
```

자식으로 빨간노드를 하나라도 가지면 true, 아니면 false를 반환한다.

```c++
node* node::uncle() {
	if (up->up->right == up) {
		return up->up->left;
	}
	else {
		return up->up->right;
	}
}
```

이 노드의 삼촌노드를 가리키는 포인터이다.

```c++
node::node(int a, node* parent) {
	left = nil;
	right = nil;
	up = parent;
	key = a;
	color = red;
}
```

부모와 함께, key값을 갖는 노드를 생성할 수 있는 생성자이다.

```c++
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
```

답을 담는 공간인 ans변수를 선언한다. root를 가리키는 포인터를 선언한다. 순서대로 기본생성자 및 삽입함수, 삭제함수, 트리를 보여주는 함수, 이중빨간노드일 때 처리하는 함수, 더블블랙일 때 처리하는 함수, 동료를 가리키는 포인터, 특정 노드를 기준으로 resturuct해주는 함수, ans를 출력하는 함수를 선언한다.

```c++
tree::tree() {
	root = nullptr;
}
```

기본생성자이다. root는 아무것도 가리키지 못한다.

```c++
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
```

insert 함수는 key 값을 인자로 받는다. root노드가 존재하지 않는다면 만들어주고, black으로 칠힌다. root노드가 존재한다면 이제 내려가는데, 각 노드의 key값과 비교하며 작으면 왼쪽으로, 크면 오른쪽으로 가는데, nil이라면 그 곳에 노드를 동적 생성한다. 만약 같다면 이미 존재한다고 출력한다.

```c++
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
```

remove 함수는 key값을 인자로 받고, 각 노드의 key값과 비교해가며 내려간다. 작다면 왼쪽으로, 크다면 오른쪽으로 가는데 nil이 보인다면 NOT FOUND를 출력한다. 발견했다면, 우선 외부노드일 때와 내부노드일 때로 구분한다. 외부노드라면, red노드인지 black노드인지 구분하여 black노드라면 더블블랙을 처리해준다. 내부노드이면 inorder successor으로 대체하고 그 successor 노드를 삭제하는데, black 노드라면 더블블랙을 처리해준다.

```c++
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
```

재귀함수로 구현하였으며, 깊이가 깊어질 때마다 gap에 네칸의 스페이스바를 추가해 구분을 주었다. 중위 순회를 이용한 출력이다.

```c++
void tree::check(node* now) {
	if (now == root || now->up == root) { // 에러방지
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
```

이중red노드가 감지되었을 때, 호출되는 함수이다. 한번 더 부모노드가 red임을 확인해주고, 삼촌노드의 색이 빨강이라면 Recoloring을 진행한다. 삼촌노드가 검은색이라면 Restructing을 진행한다.

```c++
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
			ddbb(now->up); // 재귀 !! ------------------------------------------
		}
	}
	else if (get_sibling(now)->color == red) {
		if (now->up->right == now) {
			restruct(now->up->left->left);
			now->up->color = red;
			get_sibling(now->up)->color = black;
			now->up->up->color = black;
			ddbb(now); // 재귀 !!-------------------------
		}
		else {
			restruct(now->up->right->right);
			now->up->color = red;
			get_sibling(now->up)->color = black;
			now->up->up->color = black;
			ddbb(now); // 재귀 !!------------------------------------
		}
	}
}
```

더블블랙을 처리해주는 함수이다. 우선 크게 세가지 case로 나뉜다. 1) 동료가 빨간 자식을 가지고 있고, 동료가 검은색 노드일 때, 2) 동료와 동료의 자식들 모두 다 검은색 노드일 때, 3) 동료가 빨간색 노드일 때이다. 

1)동료 왼쪽 자식부터 빨간노드인지 확인하여 restructing한다.

2) 부모 노드가 빨간색이라면 색을 교체하고 끝나지만, 검은색이라면 동료를 빨간노드로 바꾸고 부모에서 다시 더블블랙을 처리해준다.

3) 무조건 재귀가 일어나는 조건문이다. 동료의 자식을 골라 restruncting을 진행하는데, LL or RR rotate가 일어나도록 고른다. 그 후, 부모의 노드만 빨간색으로 칠하고, 삼촌, 증부모는 검은색으로 칠한다. 그리고 다시 현재 위치에서 더블블랙 처리를 한다.

```c++
node* tree::get_sibling(node* now) {
	if (now->up->left == now) {
		return now->up->right;
	}
	else {
		return now->up->left;
	}
}
```

동료를 가리키는 포인터를 반환하는 함수이다.

```c++
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
```

restruct 함수는 우선 rotate를 할때, root노드가 관여하는지 체크한다. 관여하지 않는다면, 윗 조상의 오른쪽 자식인지 왼쪽 자식인지 체크한다. 그 후, LL LR RL RR rotate를 구현한 함수이다. 각 서브트리들이 이진검색트리를 깨지 않도록 잘 주고 받아져야한다. (함수가 매우 길다, 단축이 필요하다.)

```c++
void tree::display() {
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << endl;
	}
}
```

ans에 담긴 답들을 출력하는 함수이다.

```c++
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
```

입력값을 파싱하기 위해 stringstream를 이용하였다. 각 입력값에 맞게 올바른 함수들이 호출될 수 있도록 구현하였다.

<h4>-결과창</h4>

![문제2 콘솔창](D:\DG3-1\자료구조\과제3\문제2 콘솔창.png)

QUIT를 기준으로 위가 입력값들이고, 아래가 출력값들이다. 주어진 예제 입출력 그대로 잘 나온것을 확인할 수 있다.













