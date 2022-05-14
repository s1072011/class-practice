#include <iostream>
#include <string>

using namespace std;

class ListNode {
private:
	char data;
	ListNode* next;
	ListNode(char data) {
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
	void push(char c) {
		ListNode* newNode = new ListNode(c);
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
	char top() {
		if (first == NULL) return '\0';
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
	while (n--) {
		string s;
		getline(cin, s);
		for (size_t i = 0; i < s.length(); i++) {
			if (s[i] == ' ') {
				continue;
			}
			if (s[i] >= 48 && s[i] <= 57) {
				cout << s[i] << " ";
			}
			else if (s[i] == '(') {
				myStack.push(s[i]);
			}
			else if (s[i] == ')') {
				while (myStack.top() != '(') {
					cout << myStack.top();
					if (myStack.length()) {
						cout << " ";
					}
					myStack.pop();
				}
				myStack.pop();
			}
			else if (s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-') {
				while (myStack.top() == '*' || myStack.top() == '/') {
					cout << myStack.top();
					if (myStack.length()) {
						cout << " ";
					}
					myStack.pop();
				}
				myStack.push(s[i]);
			}
		}
		while (myStack.top() != NULL) {
			cout << myStack.top();
			myStack.pop();
			if (myStack.length()) {
				cout << " ";
			}
		}
		cout << endl;
	}
}