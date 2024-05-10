#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

class Node {
public:
    int key;
    Node *left;
    Node *right;
    int height;
};

int height(Node *node){
    if(node == NULL) return 0;
    return node->height;
}

int getBalanceFactor(Node *node){
    if(node == NULL) return 0;
    return height(node->left) - height(node->right);
}

Node *newNode(int key){
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node *rotateRight(Node *x){
    Node *y = x->left;
    Node *t = y->right;
    y->right = x;
    x->left = t;
    x->height = max(height(x->right), height(x->left)) + 1;
    y->height = max(height(y->right), height(y->left)) + 1;
    return y;
}

Node *rotateLeft(Node *y){
    Node *x = y->right;
    Node *t = x->left;
    x->left = y;
    y->right = t;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node *insertNode(Node *node, int key){
    if(node == NULL){
        return newNode(key);
    }
    if(key < node->key){
        node->left = insertNode(node->left, key);
    } else if(key > node->key){
        node->right = insertNode(node->right, key);
    } else {
        return node;
    }
    node->height = 1 + max(height(node->left), height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if(balanceFactor > 1){
        if(key < node->left->key){
            return rotateRight(node);
        } else if(key > node->left->key){
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if(balanceFactor < -1){
        if(key < node->right->key){
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        } else if(key > node->right->key){
            return rotateLeft(node);
        }
    }
    return node;
}

void BFS(Node* root, vector<double>& averages) {
    if(root == nullptr)
        return;

    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        int size = q.size();
        double sum = 0.0;
        for(int i = 0; i < size; i++) {
            Node* current = q.front();
            q.pop();
            sum += current->key;

            if(current->left)
                q.push(current->left);
            if(current->right)
                q.push(current->right);
        }
        averages.push_back(sum / size);
    }
}

int main() {
    int n;
    cin >> n;

    Node* root = nullptr;

    for(int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        root = insertNode(root, value);
    }

    vector<double> averages;
    BFS(root, averages);

    cout << "Average values on each level: ";
    for(int i = 0; i < averages.size(); ++i) {
        cout << averages[i];
        if(i != averages.size()-1)
            cout << " ";
    }
    cout << " " << endl;

    return 0;
}
