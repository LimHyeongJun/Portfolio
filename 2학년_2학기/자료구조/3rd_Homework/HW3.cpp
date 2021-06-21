#include <algorithm>
#include <assert.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

template <class Item> class tree {
public:
	tree(const Item &init_data = Item(), tree *init_left = NULL,
		tree *init_right = NULL) {
		data_field = init_data;
		left_field = init_left;
		right_field = init_right;
	}
	Item &data() { return data_field; }
	tree *&left() { return left_field; }
	tree *&right() { return right_field; }
	void set_data(const Item &new_data) { data_field = new_data; }
	void set_left(tree *new_left) { left_field = new_left; }
	void set_right(tree *new_right) { right_field = new_right; }
	bool is_leaf() const { return (left_field == NULL && right_field == NULL); }

private:
	Item data_field;
	tree *left_field;
	tree *right_field;
};

bool insert(tree<char> *root, char data, int index);
int get_depth(int i);
int num_of_node(int i);
int get_position(int i);
void rotate_print(tree<char> *root, int depth);
void non_rotate_print(vector<char> v);
int center(int n);
int depth(int n);
void H(int node, int i, int j, int d, int U, int D, int R, int L);

char H_tree[100][100];
int V[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
vector<char> v;

int main(void) {
	string input;
	getline(cin, input);

	string commands[200];
	int k = 0;
	int index = 0;
	int decide_num = 0;
	int command_num = 0;

	stringstream ss(input);
	string str;
	while (ss >> str) {
		if (str == "INS") {
			decide_num = 1;
			++command_num;
		}
		else if (decide_num == 1) {
			char temp = str[0];
			if (isdigit(temp) || isupper(temp) || islower(temp) || temp == '?') {
				v.push_back(temp);
				push_heap(v.begin(), v.end());
			}
			decide_num = 0;
		}
		else if (str == "DEL") {
			assert(v.size() > 0);
			pop_heap(v.begin(), v.end());
			vector<char>::iterator iter;
			iter = v.end();
			v.erase(--iter);
			++command_num;
		}
		else if (str == "EOI") {
			++command_num;
			break;
		}
		else if (command_num == 200) {
			break;
		}
	}

	assert(v.size() > 0);

	tree<char> *root = new tree<char>();
	root->set_data(v[0]);

	for (int i = 1; i < v.size(); ++i)
		insert(root, v[i], i);

	cout << "-------- 1. rotate form으로 출력 --------" << endl;
	rotate_print(root, 0);
	cout << endl;

	cout << "-------- 2. non_rotate form으로 출력 --------" << endl;
	non_rotate_print(v);
	cout << endl;

	cout << "-------- 3. H-tree form으로 출력 --------" << endl;

	int middle = center(v.size()) + 1;

	H(1, middle, middle, depth(v.size()), 0, 1, 2, 3);

	int H_tree_nodenum = 0;
	int row = 0;
	int column = 0;

	for (int i = 0; i < 2 * middle; ++i) {
		for (int j = 0; j < 3 * middle; ++j) {
			if (isdigit(H_tree[i][j]) || isupper(H_tree[i][j]) || islower(H_tree[i][j]) || H_tree[i][j] == '?') {
				row = i;
				column = j;
				break;
			}
		}
		if (row != 0)
			break;
	}

	for (int i = row; i < 2 * middle; i++) {
		for (int j = column; j < 3 * middle; j++) {
			cout << H_tree[i][j] << " ";
			if (isdigit(H_tree[i][j]) || isupper(H_tree[i][j]) || islower(H_tree[i][j]) || H_tree[i][j] == '?') {
				++H_tree_nodenum;
			}
		}
		cout << endl;
		if (H_tree_nodenum == v.size())
			break;
	}

	return 0;
}

bool insert(tree<char> *root, char data, int index) {
	int depth = get_depth(index); //여기서 depth를 구한다.
	int nodenum =
		num_of_node(depth); // depth가 가질 수 있는 최대 노드의 갯수를 구한다.
	int position = get_position(index); //해당 depth에서 왼쪽에서 몇번째인지

	if (depth == 1 && position == 1) {
		root->set_left(new tree<char>(data));
		return true;
	}
	else if (depth == 1 && position == 2) {
		root->set_right(new tree<char>(data));
		return true;
	}

	int k = nodenum / 2;

	if (depth != 1 && position <= k)
		return insert(root->left(), data, index - k);
	else if (depth != 1 && position > k)
		return insert(root->right(), data, index - nodenum);
	else
		return false;
}

int get_depth(int i) {
	if (i == 0)
		return 0;
	else if (i == 1 || i == 2)
		return 1;
	else if (i >= 3 && i <= 6)
		return 2;
	else if (i >= 7 && i <= 14)
		return 3;
	else if (i >= 15 && i <= 30)
		return 4;
	else if (i >= 31 && i <= 62)
		return 5;
	else if (i >= 63 && i <= 126)
		return 6;
	else if (i >= 127 && i <= 199)
		return 7;
	else
		return 100000;
}

int num_of_node(int i) {
	int result = 1;
	for (int k = 0; k < i; k++)
		result *= 2;

	return result;
}

int get_position(int i) {
	if (i == 1 || i == 2)
		return i;
	else if (i >= 3 && i <= 6)
		return (i - 2);
	else if (i >= 7 && i <= 14)
		return (i - 6);
	else if (i >= 15 && i <= 30)
		return (i - 14);
	else if (i >= 31 && i <= 62)
		return (i - 30);
	else if (i >= 63 && i <= 126)
		return (i - 62);
	else if (i >= 127 && i <= 199)
		return (i - 126);
	else
		return 100000;
}

void rotate_print(tree<char> *root, int depth) {
	if (root != NULL) {
		rotate_print(root->right(), depth + 1);
		cout << setw(2 * depth) << "" << root->data() << endl;
		rotate_print(root->left(), depth + 1);
	}
}

void non_rotate_print(vector<char> v) {
	int total_depth = get_depth(v.size() - 1); //전체 depth
	int width = 1;
	for (int i = 0; i < total_depth; ++i)
		width *= 2;

	cout << setw(width) << "" << v[0] << endl; // root 우선 출력해둔다.

	for (int i = 1; i < v.size(); ++i) {
		int temp_depth = get_depth(i);
		int nodenum = num_of_node(temp_depth);
		int position = get_position(i);

		if (position == 1)
			cout << setw(width / 2) << "" << v[i];
		else
			cout << setw(width - 1) << "" << v[i];

		if (nodenum == position) {
			cout << endl;
			width /= 2;
		}
	}
}

int center(int n) { return n <= 1 ? 0 : 2 * center(n / 4) + 1; }

int depth(int n) { return n <= 7 ? 1 : 2 * depth(n / 4); }

void H(int node, int i, int j, int d, int U, int D, int R, int L) {
	int n = v.size();
	if (node > n)
		return;
	H_tree[i][j] = v[node - 1];
	if (2 * node <= n) {
		H_tree[i + d * V[L][0]][j + d * V[L][1]] = v[2 * node - 1];
		H(4 * node, i + d * (V[L][0] + V[U][0]), j + d * (V[L][1] + V[U][1]), d / 2, D, U, L, R);
		H(4 * node + 1, i + d * (V[L][0] + V[D][0]), j + d * (V[L][1] + V[D][1]), d / 2, U, D, R, L);
	}
	if (2 * node + 1 <= n) {
		H_tree[i + d * V[R][0]][j + d * V[R][1]] = v[2 * node];
		H(4 * node + 2, i + d * (V[R][0] + V[D][0]), j + d * (V[R][1] + V[D][1]), d / 2, U, D, R, L);
		H(4 * node + 3, i + d * (V[R][0] + V[U][0]), j + d * (V[R][1] + V[U][1]), d / 2, D, U, L, R);
	}
}