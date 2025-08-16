#include <random>
#include <iostream>
#include <cstring>
using namespace std;

template <typename keytype>
class Treap {
    private:

        struct TNode {
			TNode *left, *right;
			keytype key;
			float priority;
			int leftNodes;
		};

        TNode* root;

        int treapSize = 0;
        int curRank = 0;

        TNode* newNode(keytype key, float priority) {
            TNode *newnode = new TNode;
            newnode->left = NULL;
            newnode->right = NULL;
            newnode->key = key;
            newnode->priority = priority;
            newnode->leftNodes = 0;
            
            return newnode;
        };

        TNode* newNode(keytype key) {
            TNode *newnode = new TNode;
            newnode->left = NULL;
            newnode->right = NULL;
            newnode->key = key;
            newnode->priority = rand()%100;
            newnode->leftNodes = 0;
            
            return newnode;
        };

        TNode* CopyHelper(TNode* oldTreap) {
            if (oldTreap) {
                TNode* newTreap = new TNode;
                newTreap = newNode(oldTreap->key, oldTreap->priority);
                newTreap->left = CopyHelper(oldTreap->left);
                newTreap->right = CopyHelper(oldTreap->right);
                return newTreap;
            } else {
                return NULL;
            }
        };

        void Destructor(TNode* root) {
            if (root) {
                Destructor(root->left);
                Destructor(root->right);
                delete(root);
            }
        };

        TNode* InsertNode(TNode* root, keytype k, float p) {
            if (!root) {
                treapSize++;
                return newNode(k, p);
            }

            if (k < root->key) {
                root->leftNodes++;
                root->left = InsertNode(root->left, k, p);

                if (root->left != NULL && root->left->priority < root->priority) {
                    RightRotate(root);
                }
            }

            else {
                root->right = InsertNode(root->right, k, p);
        
                if (root->right != NULL && root->right->priority < root->priority) {
                    LeftRotate(root);
                }
            }
            return root;
        };
        
        TNode* RemoveNode(TNode* root, keytype k) {
            if (root == NULL) {
                return root;
            }
        
            if (k < root->key) {
                root->leftNodes--;
                root->left = RemoveNode(root->left, k);
            }

            else if (k > root->key) {
                root->right = RemoveNode(root->right, k);
            }
        
            else if (root->left == NULL) {
                TNode *temp = root->right;
                delete(root);
                root = temp;
            }
        
            else if (root->right == NULL) {
                TNode *temp = root->left;
                delete(root);
                root = temp;
            }
        
            else if (root->left->priority < root->right->priority) {
                RightRotate(root);
                root->right = RemoveNode(root->right, k);
            }

            else {
                LeftRotate(root);
                root->leftNodes--;
                root->left = RemoveNode(root->left, k);
            }
        
            return root;
        };

        void LeftRotate(TNode* &oldRoot) {
            TNode *newRoot = oldRoot->right;
            TNode *newRootLeft = newRoot->left;
        
            newRoot->left = oldRoot;
            oldRoot->right = newRootLeft;

            oldRoot = newRoot;

            // Adjust for leftNodes count
            oldRoot->leftNodes += (oldRoot->left->leftNodes + 1);
        };

        void RightRotate(TNode* &oldRoot) {
            // Adjust for lefNodes count
            oldRoot->leftNodes -= (oldRoot->left->leftNodes + 1);
            TNode *newRoot = oldRoot->left;
            TNode *newRootRight = newRoot->right;
        
            newRoot->right = oldRoot;
            oldRoot->left = newRootRight;
        
            oldRoot = newRoot;
        };

        void PreOrder(TNode* root) {
            if (root) {
                cout << root->key << " ";
                PreOrder(root->left);
                PreOrder(root->right);
            }
            
        };

        void InOrder(TNode* root) {
            if (root) {
                InOrder(root->left);
                cout << root->key << " ";
                InOrder(root->right);
            }
            
        };

        void PostOrder(TNode* root) {
            if (root) {
                PostOrder(root->left);
                PostOrder(root->right);
                cout << root->key << " ";
            }
            
        };

        float Search(TNode* root, keytype k) {
            if (!root) {
                return -1;
            }
        
            else if (root->key == k) {
                return root->priority;
            }
        
            else if (k < root->key) {
                return Search(root->left, k);
            }
        
            else {
                return Search(root->right, k);
            }
        };

        keytype Predeccessor(TNode* root, keytype k) {
            TNode* pre = new TNode;
            pre = newNode(k, root->priority);
            
            while(1) {

                if (k < root->key) {
                    root = root->left;
                }
        
                else if (k > root->key) {
                    pre = root;
                    root = root->right;
                }
        
                else {
                    if (root->left) {
                        // Go left, then find furthest right child
                        root = root->left;
                        while(root->right) {
                            root = root->right;
                        }
                        pre = root;

                    }
                    break;
                }
        
            }
            return pre->key;
            
        };

        keytype Successor(TNode* root, keytype k) {
            TNode* suc = new TNode;
            suc = newNode(k, root->priority);
            
            while(1) {
                if (k > root->key) {
                    if (!(root->left) && !(root->right)) {
                        return k;
                    }
                    root = root->right;
                }
        
                else if (k < root->key) {

                    suc = root;
                    root = root->left;
                }
        
                else {
                    if (root->right) {
                        // Go right, then find furthest left child
                        root = root->right;
                        while(root->left) {
                            root = root->left;
                        }
                        suc = root;

                    }
                    break;
                }
        
            }
            return suc->key;

        };

        int Rank(TNode* root, keytype k) {

            if (root->key == k) {
                curRank += root->leftNodes + 1;
                return curRank;
            }

            else if(root->key > k) {
                return Rank(root->left, k);
            }

            else if(root->key < k) {
                curRank += root->leftNodes + 1;
                return Rank(root->right, k);
            }

            else {
                return 0;
            }
        }
        
        keytype Select(TNode* root, int pos) {
            if(pos < 1 || pos > treapSize) {
                return 0;
            }

            else if(root->leftNodes + 1 == pos) {
                return root->key;
            }

            else if(root->leftNodes < pos) {
                pos -= root->leftNodes + 1;
                return Select(root->right, pos);
            }

            else {
                return Select(root->left, pos);
            }
        }
        
    public:

        /*
         * Constructs empty tree
         */
        Treap() {
            root = NULL;
        };

        /*
         * Constructs tree using the 
         * arrays k and p containing s items of keytype
         * and s floats in the range [0 … 1].
         */
        Treap(keytype k[], float p[], int s) {
            root = NULL;
            for (int i=0; i < s; i++) {
                insert(k[i], p[i]);
            }
        };

        /*
         * Copy constructor
         */
        Treap(const Treap &oldTree) {
            root = CopyHelper(oldTree.root);

        };

        /*
         * Copy assignment operator
         */
        Treap& operator=(const Treap &oldTree) {
            root = CopyHelper(oldTree.root);

        };

        /*
         * Destructor
         */
        ~Treap() {
            Destructor(root);
        };

        /*
         * Traditional search. 
         * Should return the priority associated with the key.
         * Returns -1 of key k is not found
         */
        float search(keytype k) {
            return Search(root, k);
        };

        /*
         * Inserts the node with key k and priority p 
         * into the treap
         */
        void insert(keytype k, float p) {
            root = InsertNode(root, k, p);
        };

        /*
         * Inserts the node with key k and generates a
         * random priority in the range [0…1]
         */
        void insert(keytype k) {
            root = InsertNode(root, k, rand()%100);
        };

        /*
         * Removes the node with key k and returns 1. 
         * If the node containing key k has more than one 
         * child, replace the key k and priority by the 
         * key and priority of the predecessor.
         * Return 0 if key k is not found
         */
        int remove(keytype k) {
            int success;
            if (Search(root, k) == -1) {
                success = 0;
            } else {
                success = 1;
                treapSize--;
            }
            root = RemoveNode(root, k);
            return success;
        };

        /*
         * Returns the rank of the key k in the tree
         * Returns 0 if the key k is not found
         */
        int rank(keytype k) {
            curRank = 0;
            return Rank(root, k);
        };

        /*
         * Returns the key of the node at position pos
         * in the tree
         */
        keytype select(int pos) {
            return Select(root, pos);
        };

        /*
         * Returns the key after k in the tree
         */
        keytype successor(keytype k) {
            return Successor(root, k);
        };

        /*
         * Returns the key before k in the tree
         */
        keytype predecessor(keytype k) {
            return Predeccessor(root, k);
        };

        /*
         * Returns the number of nodes in
         * the tree
         */
        int size() {
            return treapSize;
        };

        /*
         * Prints the keys of the tree in
         * preorder traversal
         */
        void preorder() {
            PreOrder(root);
            cout << endl;
        };

        /*
         * Prints the keys of the tree in
         * inorder traversal
         */
        void inorder() {
            InOrder(root);
            cout << endl;
        };

        /*
         * Prints the keys of the tree in
         * postorder traversal
         */
        void postorder() {
            PostOrder(root);
            cout << endl;
        };

};