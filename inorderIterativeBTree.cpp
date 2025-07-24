/*
*   author: aniketwazarkar
*/

#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fr(a,b) for(int i = a; i < b; i++)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define mod 1000000007
#define inf (1LL<<60)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define triplet pair<ll,pair<ll,ll>>
#define goog(tno) cout << "Case #" << tno <<": "
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define read(x) int x; cin >> x
using namespace std;

void init_code(){
    fast_io;
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* makeTree(const initializer_list<optional<int>>& nodes) {
    vector<optional<int>> vals(nodes);
    if (vals.empty() || !vals[0].has_value()) return nullptr;

    TreeNode* root = new TreeNode(vals[0].value());
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < vals.size()) {
        TreeNode* current = q.front();
        q.pop();

        if (i < vals.size() && vals[i].has_value()) {
            current->left = new TreeNode(vals[i].value());
            q.push(current->left);
        }
        i++;

        if (i < vals.size() && vals[i].has_value()) {
            current->right = new TreeNode(vals[i].value());
            q.push(current->right);
        }
        i++;
    }

    return root;
}

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode* node = root;
        stack<TreeNode*> st;

        while (node || !st.empty()) {
            while (node) {
                st.push(node);
                node = node->left;
            }
            node = st.top(); st.pop();
            res.push_back(node->val);
            node = node->right;
        }
        return res;
    }
};

int main() {
    Solution sol;

    TreeNode* root = makeTree({1,2,3,4,5,nullopt,8,nullopt,nullopt,6,7,9});
    vector<int> result = sol.inorderTraversal(root);

    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}