#include <iostream>
#include <climits>

using namespace std;

class BST {
    struct Node {
        int key;
        int h;
        Node *l = nullptr; Node *r = nullptr;
        Node(int key): key(key), h(1) {}
    } *root = nullptr;

    void add(Node *&n, int x) {
        if (!n) {
            n = new Node(x);
            return;
        }
        if (x < n->key) {
            add(n->l, x);
        }
        else if (n->key < x) {
            add(n->r, x);
        }
        else {
            return;
        }
        
        update_height(n);
        balance(n);
    }

    void del(Node *&n, int key) {
        if (!n) {
            return;
        }
        if (key < n->key) {
            del(n->l, key);
        }
        else if (n->key < key) {
            del(n->r, key);
        }
        else {
            if (!n->l && !n->r) {
                delete n;
                n = nullptr;
            }
            else if (!n->l) {
                Node *temp = n;
                n = n->r;
                delete temp;
            }
            else if (!n->r) {
                Node *temp = n;
                n = n->l;
                delete temp;
            }
            else {
                Node *temp = n->r;
                while (temp->l) {
                    temp = temp->l;
                }
                n->key = temp->key;
                del(n->r, temp->key);
            }
        }

        update_height(n);
        balance(n);
    }

    bool exists(Node *n, int key) {
        if (!n) {
            return false;
        }
        if (n->key == key) {
            return true;
        }
        if (key < n->key) {
            return exists(n->l, key);
        }
        else {
            return exists(n->r, key);
        }
    }

    void update_height(Node *n) {
        if (!n) {
            return;
        }
        int left_height = n->l ? n->l->h : 0;
        int right_height = n->r ? n->r->h : 0;

        n->h = 1 + max(left_height, right_height);
    }

    void print(Node *n) {
        if (!n) {
            return;
        }
        cout << n->key << " ";
        print(n->l);
        print(n->r);
    }

    void left(Node *&n) {
        if (!n || !n->r) return;
        Node *b = n->r;
        n->r = b->l;
        b->l = n;
        n = b;
        update_height(n->l);
        update_height(n);
    }

    void right(Node *&n) {
        if (!n || !n->l) return;
        Node *b = n->l;
        n->l = b->r;
        b->r = n;
        n = b;
        update_height(n->r);
        update_height(n);
    }

    void left(Node *&n, int x) {
        if (!n) return;

        if (x < n->key) {
            left(n->l, x);
            update_height(n);
        }
        else if (n->key < x) {
            left(n->r, x);
            update_height(n);
        }
        else {
            left(n);
        }
    }

    void right(Node *&n, int x) {
        if (!n) return;

        if (x < n->key) {
            right(n->l, x);
            update_height(n);
        }
        else if (n->key < x) {
            right(n->r, x);
            update_height(n);
        }
        else {
            right(n);
        }
    }

    int height(Node* n) {
        return n ? n->h : 0;
    }

    int get_balance(Node *n) {
        if (!n) return 0;
        int left_height = height(n->l);
        int right_height = height(n->r);

        return right_height - left_height;
    }

    void balance(Node *&n) {
        if (!n) return;
        int bal = get_balance(n);

        if (bal == 2) {
            int bal_r = get_balance(n->r);
            if (bal_r >= 0) {
                left(n);
            } else {
                right(n->r);
                left(n);
            }
        }
        else if (bal == -2) {
            int bal_l = get_balance(n->l);
            if (bal_l <= 0) {
                right(n);
            } else {
                left(n->l);
                right(n);
            }
        }
    }

    int next(Node* n, int x) {
        if (!n) return INT_MAX;
        if (n->key < x) {
            return next(n->r, x);
        } else {
            return min(n->key, next(n->l, x));
        }
    }

    int prev(Node* n, int x) {
        if (!n) return INT_MIN;
        if (n->key > x) {
            return prev(n->l, x);
        } else {
            return max(n->key, prev(n->r, x));
        }
    }

public:
    void add(int x) {
        add(root, x);
    }

    void del(int key) {
        del(root, key);
    }

    bool exists(int key) {
        return exists(root, key);
    }

    int next(int x) {
        return next(root, x);
    }

    int prev(int x) {
        return prev(root, x);
    }

    void print_root() {
        if (root) {
            cout << root->key;
        }
        else {
            cout << "Empty";
        }
        cout << '\n';
    }

    int height() {
        return height(root);
    }

    void print() {
        if (!root) {
            cout << "Empty";
        }
        else {
            print(root);
        }
        cout << '\n';
    }
};

int main() {
    int q; cin >> q;
    BST bst;

    while (q--) {
        string query; cin >> query;
        if (query == "add") {
            int x; cin >> x;
            bst.add(x);
        }
        else if (query == "del") {
            int x; cin >> x;
            bst.del(x);
        }
        else if (query == "exists") {
            int x; cin >> x;
            cout << (bst.exists(x) ? "YES" : "NO") << '\n';
        }
        else if (query == "next") {
            int x; cin >> x;
            int res = bst.next(x);
            if (res == INT_MAX) {
                cout << "None\n";
            } else {
                cout << res << '\n';
            }
        }
        else if (query == "prev") {
            int x; cin >> x;
            int res = bst.prev(x);

            if (res == INT_MIN) {
                cout << "None\n";
            } else {
                cout << res << '\n';
            }
        }
        else if (query == "root") {
            bst.print_root();
        }
        else if (query == "height") {
            cout << bst.height() << '\n';
        }
        else if (query == "print") {
            bst.print();
        }
    }
}