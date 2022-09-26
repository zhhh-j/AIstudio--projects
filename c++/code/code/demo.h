#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
#include<string>
using namespace std ;

struct  ListNode{
	// ������ָ���򣬹��캯��
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
	// �����ߣ�1����head->next, 2�޸�headָ��, 3����head��newhead
	ListNode* reverseList(ListNode* head);

	// ��ת ��m��ʼ��n��Ԫ��
	ListNode* reverseListmn(ListNode* head, int m, int n);

	// ������Ľ���, ����set
	ListNode* CrossList(ListNode* headA, ListNode* headB);

	// �������㣬˼·2�����������ĳ��ȣ���ͷָ����룬ͬʱ����������ָ��ͬһͷ���ʱ��ֹͣ��
	//  ListNode* CrossList(ListNode* a, ListNode *b);

	// ���һ������ҵ�������ʼ�ڵ㣬1. ����set  2. ����ָ������
	ListNode* detectCycle(ListNode* head);

	// ����б�����ͷ�ڵ�
	ListNode* partition(ListNode* head, int val);


	// ��������ָ������� RandomListNode
	RandomListNode* deepcopy(RandomListNode* head);

	RandomListNode* deepcopy_again(RandomListNode* head);

	ListNode* mergeTwoLists(ListNode *L1, ListNode *L2);

	// �ϲ�k���������ƺ�����
	ListNode* mergeKList(std::vector<ListNode*> lists);

	bool check_is_valid_order(queue<int> &order);


	//-----------------------------------------------̰��

	// 1.���ǹ�
	int findContentChildren(vector<int>& g, vector<int> &s);

	//------------------------------------------------�ݹ�
	// 1. �����Ӽ�
	vector<vector<int>> subsets(vector<int >nums) {
		vector<int> item;
		vector<vector<int>> result;
		result.push_back(item);
		generate(0, nums, item, result);
		return result;
	}

	// 2. λ��������Ӽ���all_sets�ö����Ʊ�ʾ����ÿ��sets������Ӧλ���㹹�켯��
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

	// 3.���� sum == target���Ӽ�
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

	// 4. ���� ����Ϊ n �ģ��������п������
	vector<string> gen_kuohao(int n) {
		vector<string> result;
		string item;
		gen(item, n, result);
		return result;
	}

	// 5. ���� ����Ϊ n �� ���� �����кϷ����
	// �����Ÿ������������Ÿ���==n
	// �ȷŹ������ţ����ܷ�������
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


