#include <iostream>
#include <memory>

using namespace std;



class Tree {
    struct Node {
        size_t key;
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        Node():key(), left(), right(){}
        Node(size_t x):key(x),left(), right(){}
    };
    shared_ptr<Node> root;

    bool remove(size_t x, shared_ptr<Node>& p) {
        if(p && x < p->key) {
            return remove(x, p->left);
        }
        else if(p && x > p->key) {
            return remove(x, p->right);
        }
        else if(p && p->key == x) {
            if(!p->left) {
                p = p->right;
            }
            else if(!p->right) {
                p = p->left;
            }
            else {
                shared_ptr<Node> q = p->left;
                while(q->right) {
                    q = q->right;
                }
                p->key = q->key;
                remove(q->key, p->left);
            }
            return true;
        }
        return false;
    }
    void insert(size_t x, shared_ptr<Node>& p) {
        if (p && x < p->key && p->left) {
            return insert(x, p->left);
        }
        else if (p && x < p->key && !p->left){
            p->left = shared_ptr<Node>(new Node(x));
        }

        else if (p && x > p->key && p->right) {
            return insert(x, p->right);
        }
        else if (p && x > p->key && !p->right) {
            p->right = shared_ptr<Node>(new Node(x));
        }
    }
public:
    Tree(){
        root = nullptr;
    }
    ~Tree(){
        while (root) remove(root->key);
    }
    bool remove(size_t x) {
        return remove(x, root);
    }
    void insert(size_t x) {
        if (!root) {
            root = shared_ptr<Node>(new Node(x));
        }
        else return insert(x, root);
    }

    static size_t size(shared_ptr<Node>& p) {
        if (!p) return 0;
        return size(p->left) + size(p->right) + 1;
    }
    friend void count (shared_ptr<Node>& a, shared_ptr<Node>& b, size_t *result);
    friend size_t count(Tree &a, Tree &b);
    };

void build(Tree &t) {
    size_t size, val;
    cin >> size;
    for (size_t i = 0; i < size; i++) {
        cin >> val;
        t.insert(val);
    }
}

void count (shared_ptr<Tree::Node>& a, shared_ptr<Tree::Node>& b, size_t *result) {
    if (!a) {
        *result += Tree::size(b);
    }
    else if (!b) {
        (*result)++;
    }
    else if (a && b && a->key == b->key) {
        count(a->left, b->left, result);
        count(a->right, b->right, result);
    }
    else if (a && b && a->key != b->key)
        *result += Tree::size(b) + 1;
}

size_t count(Tree &a, Tree &b) {
    if(!a.root && !b.root) return 0;
    else if (!b.root) return 1;
    else if (!a.root) return Tree::size(b.root);
    else {
        size_t result = 0;
        count(a.root, b.root, &result);
        return result;
    }
}

int main() {
    Tree A, B;
    build(A);
    build(B);
    cout << count(A, B);
}