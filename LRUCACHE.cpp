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

class LRUCache {
public:
    class Node{
        public: 
            int key;
            int val;
            Node* prev;
            Node* next;

            Node(int key, int val){
                this->key = key;
                this->val = val;
            }
    };

    Node* head = new Node(-1, -1);
    Node* tail = new Node(-1, -1);

    int cap;
    unordered_map<int, Node*> m;

    LRUCache(int capacity) {
        cap = capacity;
        head -> next = tail;
        tail -> prev = head;
    }

    void addNode(Node* newnode){
        Node* temp = head -> next;

        newnode -> next = temp;
        newnode -> prev = head;

        head -> next = newnode;
        temp -> prev = newnode;
    }

    void deleteNode(Node* delnode){
        Node* prevv = delnode -> prev;
        Node* nextt = delnode -> next;

        prevv -> next = nextt;
        nextt -> prev = prevv;
    }
    
    int get(int key) {
        if(m.find(key) != m.end()){
            Node* resNode = m[key];
            int ans = resNode -> val;

            m.erase(key);
            deleteNode(resNode);
            addNode(resNode);

            m[key] = head -> next;
            return ans;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(m.find(key) != m.end()){
            Node* curr = m[key];
            m.erase(key);
            deleteNode(curr);
        }

        if(m.size() == cap){
            m.erase(tail -> prev -> key);
            deleteNode(tail -> prev);
        }

        addNode(new Node(key, value));
        m[key] = head -> next;
    }
};

int main() {
    LRUCache cache(2); // capacity = 2

    cache.put(1, 10);     // cache: {1=10}
    cache.put(2, 20);     // cache: {2=20, 1=10}
    std::cout << cache.get(1) << "\n"; // returns 10, cache: {1=10, 2=20}
    cache.put(3, 30);     // evicts key 2, cache: {3=30, 1=10}
    std::cout << cache.get(2) << "\n"; // returns -1 (not found)
    std::cout << cache.get(3) << "\n"; // returns 30
    std::cout << cache.get(1) << "\n"; // returns 10

    return 0;
}



/*
Intuition:
The intuition is to maintain a fixed-size cache of key-value pairs using a doubly linked list and an unordered map. When accessing or adding a key-value pair, it moves the corresponding node to the front of the linked list, making it the most recently used item. This way, the least recently used item is always at the end of the list. When the cache is full and a new item is added, it removes the item at the end of the list (least recently used) to make space for the new item, ensuring the LRU property is maintained.

Explanation:
Node Class:
This is a nested class representing a doubly linked list node.
Each node contains an integer key, an integer value, and pointers to the previous and next nodes in the linked list.
LRUCache Class:
This is the main LRU Cache class.
It has a fixed capacity (cap) that is specified during its instantiation.
It uses an unordered_map<int, Node*> named m to store key-value pairs, where the key is the integer key, and the value is a pointer to the corresponding Node.
head and tail Nodes:
The LRUCache class has two dummy nodes: head and tail.
These nodes act as sentinels in the doubly linked list, helping to simplify the edge cases and avoid dealing with null pointers.
head is the first node in the linked list, and tail is the last node.
addNode Function:
This function is used to add a new node to the front of the doubly linked list (right after head).
It takes a Node* newnode as input, representing the node to be added.
The function updates the pointers of the new node, the previous first node, and head to include the new node as the new first node.
deleteNode Function:
This function is used to delete a node from the doubly linked list.
It takes a Node* delnode as input, representing the node to be deleted.
The function updates the pointers of the previous and next nodes to exclude the node to be deleted, effectively removing it from the linked list.
get Function:
This function is used to retrieve a value from the cache based on the given key.
If the key exists in the cache (m.find(key) != m.end()), it retrieves the corresponding node (resNode), extracts its value (ans), and performs the following steps:
Erase the key-value pair from the m unordered map.
Delete the node from its current position in the linked list using deleteNode.
Add the node to the front of the linked list using addNode, making it the most recently used node.
Update the m map to store the key with the most recently used node.
If the key doesn't exist in the cache, it returns -1.
put Function:
This function is used to insert or update a key-value pair in the cache.
If the key already exists in the cache, it updates the value by performing the following steps:
Erase the existing key-value pair from the m unordered map.
Delete the corresponding node from its current position in the linked list using deleteNode.
If the cache is full (i.e., m.size() == cap), it removes the least recently used node from the cache by erasing the key-value pair from the m map and deleting the node from the end of the linked list using deleteNode.
After handling the eviction (if needed), it creates a new node using new Node(key, value) and adds it to the front of the linked list using addNode.
Finally, it updates the m map to store the key with the newly added node.
*/