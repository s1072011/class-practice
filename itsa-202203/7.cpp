#include <iostream>
#include <string>

using namespace std;

class LinkedList;
class ListNode {
private:
	string data;
	ListNode* next;
	ListNode(string data) {
		this->data = data;
		next = NULL;
	}
	~ListNode() {
		delete next;
	}
	friend class LinkedList;
};
class LinkedList {
private:
	ListNode* first;
	size_t size;
public:
	LinkedList() {
		first = NULL;
		size = 0;
	}
	~LinkedList() {
		delete first;
	}
	void push(string s) {
		ListNode* newNode = new ListNode(s);
		newNode->next = first;
		first = newNode;
		size++;
	}
	void pop() {
		if (first == NULL) {
			return;
		}
		ListNode* top = first;
		first = first->next;
		delete top;
		size--;
	}
	string top() {
		if (first == NULL) return "";
		return first->data;
	}
	size_t length() {
		return size;
	}
};
int main()
{
	LinkedList myStack;
	int n;
	cin >> n;
	cin.ignore();
	while (n--)
	{
		string s;
		bool isPreFix = false;
		bool isPostFix = false;
		getline(cin, s);
		if ((s[0] >= 48 && s[0] <= 57 && s[s.length() - 1] >= 48 && s[s.length() - 1] <= 57)
			|| (s[0] == '(' || s[s.length() - 1] == ')')) {
			cout << "same" << endl;
			continue;
		}
		else if (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/') {
			reverse(s.begin(), s.end());
			isPreFix = true;
		}
		else if (s[s.length() - 1] == '+' || s[s.length() - 1] == '-' ||
			s[s.length() - 1] == '*' || s[s.length() - 1] == '/') {
			isPostFix = true;
		}
		for (size_t i = 0; i < s.length(); i++) {
			if (s[i] >= 48 && s[i] <= 57) {
				string str(1, s[i]);
				myStack.push(str);
			}
			else {
				string num1 = myStack.top();
				myStack.pop();
				string num2 = myStack.top();
				myStack.pop();
				string back;
				if (isPreFix)
					back = num1 + s[i] + num2;
				else if (isPostFix)
					back = num2 + s[i] + num1;
				if (i != s.length() - 1) {
					back.insert(0, 1, '(').push_back(')');
				}
				myStack.push(back);
			}
		}
		cout << myStack.top() << endl;
		myStack.pop();
	}
}