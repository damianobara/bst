#include <iostream>
#include <memory>
#include <stack>

class Tree {
    struct Node {
        size_t key;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(size_t x) : key(x), left(), right() {}
    };

    std::shared_ptr<Node> root;

    bool remove(size_t x, std::shared_ptr<Node> &p) {
        if (p && x < p->key) {
            return remove(x, p->left);
        } else if (p && x > p->key) {
            return remove(x, p->right);
        } else if (p && p->key == x) {
            if (!p->left) {
                p = p->right;
            } else if (!p->right) {
                p = p->left;
            } else {
                std::shared_ptr<Node> q = p->left;
                while (q->right) {
                    q = q->right;
                }
                p->key = q->key;
                remove(q->key, p->left);
            }
            return true;
        }
        return false;
    }

    void insert(size_t x, std::shared_ptr<Node> &p) {
        std::shared_ptr<Node> act = p;
        while (act && x != act->key) {
            if (act && x < act->key && act->left) {
                act = act->left;
            } else if (act && x < act->key && !act->left) {
                act->left = std::shared_ptr<Node>(new Node(x));
                return;
            } else if (act && x > act->key && act->right) {
                act = act->right;
            } else if (act && x > act->key && !act->right) {
                act->right = std::shared_ptr<Node>(new Node(x));
                return;
            }
        }
    }

public:
    Tree() {
        root = nullptr;
    }

    ~Tree() {
        while (root) remove(root->key);
    }

    bool remove(size_t x) {
        return remove(x, root);
    }

    void insert(size_t x) {
        if (!root) {
            root = std::shared_ptr<Node>(new Node(x));
        } else return insert(x, root);
    }

    static size_t size(std::shared_ptr<Node> &p) {
        if (!p) return 0;
        return size(p->left) + size(p->right) + 1;
    }

    friend void count(std::shared_ptr<Node> &a, std::shared_ptr<Node> &b, size_t *result);

    friend size_t count(Tree &a, Tree &b);
};

void build(Tree &t) {
    size_t size, val;
    std::cin >> size;
    for (size_t i = 0; i < size; i++) {
        std::cin >> val;
        t.insert(val);
    }
}

void count(std::shared_ptr<Tree::Node> &a, std::shared_ptr<Tree::Node> &b, size_t *result) {
    std::stack<std::shared_ptr<Tree::Node>> stack1;
    std::stack<std::shared_ptr<Tree::Node>> stack2;
    stack1.push(a);
    stack2.push(b);
    while (!stack1.empty() && !stack2.empty()) {
        a = stack1.top();
        stack1.pop();
        b = stack2.top();
        stack2.pop();

        if (!a) {
            *result += Tree::size(b);
        } else if (!b) {
            (*result)++;
        } else if (a && b && a->key == b->key) {
            stack1.push(a->left);
            stack2.push(b->left);
            stack1.push(a->right);
            stack2.push(b->right);
        } else if (a && b && a->key != b->key) {
            *result += Tree::size(b) + 1;
        }
    }
}

size_t count(Tree &a, Tree &b) {
    if (!a.root && !b.root) return 0;
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
    std::cout << count(A, B) << std::endl;
}