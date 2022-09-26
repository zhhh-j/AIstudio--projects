#include"demo.h"
#include<iostream>
#include<string>
using namespace std;

int main() {
	ListNode a(1);
	ListNode b(2);
	ListNode c(3);
	ListNode d(4);
	a.next = &b;
	b.next = &c;
	c.next = &d;
	d.next = &c;
	ListNode *head = &a;
	//cout << "before reverse" << endl;
	//while (head) {
	//	cout << head->val << endl;
	//	head = head->next;
	//}

	Solution s;
	vector<string> result;
	vector<int> nums = { 1, 2, 3, 5 };
	result = s.gen_kuohao2(2);

	for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < result[i].size(); j++)
		{
			cout << result[i][j];
		}
		cout << "\n";
	}

	getchar();
}