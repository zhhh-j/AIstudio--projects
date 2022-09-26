#include"demo.h"
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<queue>
#include<stack>

using namespace std;

ListNode* Solution::reverseList(ListNode* head) {
	ListNode *new_head = NULL; // 指向新链表头节点的指针
	ListNode *temp = NULL;
	while (head) {
		temp = head->next;
		head->next = new_head;
		new_head = head;
		head = temp;
	}
	return new_head;
}

ListNode* Solution::reverseListmn(ListNode* head, int m, int n) {
	int change_len = n - m + 1; //计算需要逆置的个数
	ListNode *pre_head = NULL;
	ListNode *result = head; // 常规情况下返回的结果节点
	while (head && --m) { // 循环了m-1次
		pre_head = head;
		head = head->next;
	}
	ListNode *tail = head; // 逆转完成后使用
	ListNode *new_head = NULL;
	while (head && change_len) {
		change_len--;
		ListNode *temp = head->next;
		head->next = new_head;
		new_head = head;
		head = temp;
	}
	
	tail->next = head;

	// 考虑特殊情况
	if (pre_head) {
		pre_head->next = new_head;
		}
	else {
		result = new_head;
	}
	return result;
}

ListNode* Solution::CrossList(ListNode* headA, ListNode* headB) {
	set<ListNode*> node_set;
	while (headA)
	{
		node_set.insert(headA);
		headA = headA->next;
	}
	while (headB)
	{
		// 判断是否在集合中
		if (node_set.find(headB) != node_set.end()) {
			return headB;
		}
		headB = headB->next;
	}
	return NULL;
}

// 快慢指针赛跑
ListNode* Solution::detectCycle(ListNode* head) {
	ListNode *slow = head;
	ListNode *fast = head;
	ListNode *meet = NULL;
	while (fast)
	{
		fast = fast->next;
		slow = slow->next;
		if (fast == NULL) {
			return NULL;
		}
		fast = fast->next;

		if (fast == slow) {
			meet = fast;
			break;
		}
	}
	if(!meet)
	{
		return NULL;
	}
	while (meet != head) {
		meet = meet->next;
		head = head->next;
	}
	return meet;
}

ListNode* Solution::partition(ListNode* head, int val) {
	// 指针会向后移动，但头节点不会，妙用头节点
	ListNode less_head(0);
	ListNode more_head(0);
	ListNode *less_ptr = &less_head;
	ListNode *more_ptr = &more_head;
	while (head) {
		if (head->val < val) {
			less_ptr->next = head;
			less_ptr = head;
		}
		else {
			more_ptr->next = head;
			more_ptr = head;
		}
		head = head->next;
	}
	less_ptr->next = &more_head;
	more_ptr->next = NULL;

	return less_head.next;
}


RandomListNode* Solution::deepcopy(RandomListNode* head) {
	map<RandomListNode *, int> node_map; // 地址到int的map；
	vector<RandomListNode *> node_vec;
	RandomListNode *ptr = head;
	int i = 0;
	while (ptr) {
		node_vec.push_back(new RandomListNode(ptr->val)); //第i个结点
		node_map[ptr] = i;
		i++;
		ptr = ptr->next;
	}
	ptr = head;
	i = 0;

	// 多插入一个变量，使得不用处理node_vce[i+1]位空的情况
	node_vec.push_back(0);
	while (ptr) {
		node_vec[i]->next = node_vec[i+1];
		if (ptr->random) {
			int id = node_map[ptr->random];
			node_vec[i]->random = node_vec[id];
		}
		ptr = ptr->next;
		i++;
	}
	return node_vec[0];
}

RandomListNode* Solution::deepcopy_again(RandomListNode* head) {
	vector<RandomListNode*> vec;
	map<RandomListNode *, int> node_map;
	RandomListNode *ptr = head;
	int i = 0;
	while (ptr)
	{
		vec.push_back(new RandomListNode(ptr->val));
		// map：地址到i
		node_map[ptr] = i;
		i++;
		ptr = ptr->next;
	}

	vec.push_back(0);
	ptr = head;
	i = 0;
	
	while (ptr)
	{
		vec[i]->next = vec[i + 1];
		if (ptr->random) {
			int id = node_map[ptr->random];
			vec[i]->random = vec[id];
		}
		i++;
		ptr = ptr->next;
	}
	return vec[0];
}

ListNode* Solution::mergeTwoLists(ListNode *L1, ListNode *L2) {
	ListNode temp_head(0);
	ListNode *pre = &temp_head;

	while (L1 && L2)
	{
		if (L1->val < L2->val) {
			pre->next = L1;
			L1 = L1->next;
			pre = pre->next;
		}
		else
		{
			pre->next = L2;
			L2 = L2->next;
			pre = pre->next;
		}
	}

	if (L1) {
		pre->next = L1;
	}

	if (L2) {
		pre->next = L2;
	}

	return temp_head.next;
}


ListNode* Solution::mergeKList(std::vector<ListNode*> lists) {
	// 分治法两两归并，共合并logk次
	if (lists.size() == 0) {
		return NULL;
	}
	if (lists.size() == 1) {
		return lists[0];
	}
	if (lists.size() == 2) {
	// 数组索引代表了指针
		return mergeTwoLists(lists[0], lists[1]);
	}

	int mid = lists.size() / 2;
	vector<ListNode *> sub1;
	vector<ListNode *> sub2;
	for (int i = 0; i < mid; i++) {
		sub1.push_back(lists[i]);
	}
	for (int i = mid; i < lists.size(); i++) {
		sub2.push_back(lists[i]);
	}
	ListNode *L1 = mergeKList(sub1);
	ListNode *L2 = mergeKList(sub2);
	
	return mergeTwoLists(L1, L2);
}

bool Solution::check_is_valid_order(queue<int> &order) {
	// 模拟n个元素入栈出栈过程
	int n = order.size(); 
	stack<int> S;

	for (int i = 0; i < n; i++)
	{
		S.push(i);
		while (S.top() == order.front() && !S.empty()) {
			S.pop();
			order.pop();
		}
	}

	if (!S.empty()) {
		return 0;
	}
	return 1;
}

int Solution::findContentChildren(vector<int>&g, vector<int> &s) {
	sort(g.begin(), g.end());
	sort(s.begin(), s.end());
	int child = 0;
	int cookie = 0;
	while (child<g.size(), cookie<s.size())
	{
		if (g[child] < s[child]) {
			child++;
		}
		cookie++;
	}
	return child;
}

