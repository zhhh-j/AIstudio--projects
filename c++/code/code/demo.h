#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
#include<string>
using namespace std ;

struct  ListNode{
	// 数据域，指针域，构造函数
	int val;
	ListNode *next;
	ListNode(int x): val(x), next(NULL){}
};

struct RandomListNode {
	int val;
	RandomListNode *next, *random;
	RandomListNode(int x) : val(x), next(NULL), random(NULL){}
};


class Solution
{
public:
	// head, newhead
	// 三步走，1备份head->next, 2修改head指向, 3更新head和newhead
	ListNode* reverseList(ListNode* head);

	// 逆转 从m开始的n个元素
	ListNode* reverseListmn(ListNode* head, int m, int n);

	// 求链表的交点, 运用set
	ListNode* CrossList(ListNode* headA, ListNode* headB);

	// 求链表交点，思路2，求出两链表的长度，将头指针对齐，同时向后遍历，当指向同一头结点时，停止。
	//  ListNode* CrossList(ListNode* a, ListNode *b);

	// 查找环，且找到环的起始节点，1. 运用set  2. 快慢指针赛跑
	ListNode* detectCycle(ListNode* head);

	// 拆分列表，妙用头节点
	ListNode* partition(ListNode* head, int val);


	// 深拷贝有随机指针的链表 RandomListNode
	RandomListNode* deepcopy(RandomListNode* head);

	RandomListNode* deepcopy_again(RandomListNode* head);

	ListNode* mergeTwoLists(ListNode *L1, ListNode *L2);

	// 合并k个链表，分制后相连
	ListNode* mergeKList(std::vector<ListNode*> lists);

	bool check_is_valid_order(queue<int> &order);


	//-----------------------------------------------贪心

	// 1.分糖果
	int findContentChildren(vector<int>& g, vector<int> &s);

	//------------------------------------------------递归
	// 1. 产生子集
	vector<vector<int>> subsets(vector<int >nums) {
		vector<int> item;
		vector<vector<int>> result;
		result.push_back(item);
		generate(0, nums, item, result);
		return result;
	}

	// 2. 位运算产生子集，all_sets用二进制表示，对每个sets进行相应位运算构造集合
	vector<vector<int>> subsets2(vector<int >nums) {
		vector<vector<int>> result;
		int all_sets =  1 << nums.size();
		for (int i = 0; i < all_sets; i++) {
			vector<int> item;
			for (int j = 0; j < nums.size(); j++) {
				if (i & (1<<j)) {
					item.push_back(nums[j]);
				}
			}
			result.push_back(item);
		}
		return result;
	}

	// 3.产生 sum == target的子集
	vector<vector<int>> subsets_e_target(vector<int >nums, int target) {
		set<vector<int>> res_set;
		vector<vector<int>> result;
		vector<int> item;
		int sum = 0;
		//res_set.insert(item);
		//result.push_back(item);
		sort(nums.begin(), nums.end());
		generate2(0, nums, item, res_set, result, sum, target);
		return result;
	}

	// 4. 产生 组数为 n 的（）的所有可能组合
	vector<string> gen_kuohao(int n) {
		vector<string> result;
		string item;
		gen(item, n, result);
		return result;
	}

	// 5. 产生 组数为 n 的 （） 的所有合法组合
	// 左括号个数等于右括号个数==n
	// 先放过左括号，才能放右括号
	vector<string> gen_kuohao2(int n) {
		vector<string> result;
		string item;
		gen2(item, n, n, result);
		return result;
	}



private:

	void generate (int i, vector<int> nums,
		vector<int> &item, vector<vector<int>> &result) {
		if (i >= nums.size()) {
			return;
		}
		item.push_back(nums[i]);
		result.push_back(item);
		generate(i + 1, nums, item, result);
		item.pop_back();
		generate(i + 1, nums, item, result);
	}

	void generate2(int i, vector<int> nums,
		vector<int> &item,  set<vector<int>>& res_set, vector<vector<int>> &result,
		int &sum, int target) {
		if (i >= nums.size() || sum > target) {
			return;
		}
		sum += nums[i];
		item.push_back(nums[i]);
		
		if (sum == target && res_set.find(item) == res_set.end()) {
			res_set.insert(item);
			result.push_back(item);
		}
		generate2(i + 1, nums, item, res_set, result, sum, target);
		item.pop_back();
		sum = sum - nums[i];
		generate2(i + 1, nums, item, res_set, result, sum, target);
	}

	void gen(string item, int n, vector<string> &result) {
		if (item.size() == 2 * n) {
			result.push_back(item);
			return;
		}
		if (1) {
			gen(item + '(', n, result);
			gen(item + ')', n, result);
		}

	}

	void gen2(string item, int left, int right, vector<string> &result) {
		if (left == 0 && right == 0) {
			result.push_back(item);
			return;
		}
		if (left > 0) {
			gen2(item + '(', left - 1, right, result);
		}
		if (left < right) {
			gen2(item + ')', left, right - 1, result);
		}
	}
};


