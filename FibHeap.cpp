#include <random>
#include <iostream>
#include <cstring>
using namespace std;

template <typename keytype>
class FibHeap {
    private:

        struct FNode {
			FNode *left, *right,*child, *parent, *rightSib;
			keytype key;
            int degree;
		};

        FNode* newNode(keytype key) {
            FNode *newnode = new FNode;
            newnode->left = NULL;
            newnode->right = NULL;
            newnode->child = NULL;
            newnode->parent = NULL;
            newnode->rightSib = NULL;
            newnode->key = key;
            newnode->degree = 0;
            
            return newnode;
        };

        FNode* min;
        FNode* head;
        FNode* tail;

        void preorder(FNode *curr) {
            if (curr) {
                cout << curr->key << " ";
                preorder(curr->child);
                preorder(curr->rightSib);
            }
        }

        FNode* link(FNode* node1, FNode* node2) {
            FNode* greater;
            FNode* lesser;
            

            if (node1->key > node2->key) {
                lesser = node2;
                greater = node1;

            }

            else {
                lesser = node1;
                greater = node2;

            }

            greater->rightSib = lesser->child;
            lesser->child = greater;
            greater->parent = lesser;
            lesser->degree++;

            return lesser;

        }

        void consolidate() {
            FNode* curr = head;
            FNode* tempRight;
            FNode* BinTree[50] = {NULL};
            int currDegree;

            while (curr) {
                currDegree = curr->degree;
                tempRight = curr->right;

                while (currDegree < 50 && BinTree[currDegree] != NULL) {
                    curr = link(BinTree[currDegree], curr);
                    BinTree[currDegree] = NULL;
                    currDegree++;
                }
                BinTree[currDegree] = curr;
                curr = tempRight;

            }
            curr = NULL;
            min = NULL;
            head = NULL;
            tail = NULL;

            for (int i = 0; i < 50; i++) {
                if (BinTree[i] != NULL) {

                    if (head == NULL) {

                        min = BinTree[i];

                        head = BinTree[i];
                        head->left = NULL;
                        head->right = NULL;

                        curr = head;
                    }

                    else {

                        curr->right = BinTree[i];
                        BinTree[i]->left = curr;
                        BinTree[i]->right = NULL;

                        if (BinTree[i]->key < min->key) {
                            min = BinTree[i];

                        }

                        curr = curr->right;
                    }
                }
            }
            tail = curr;

        }
        
    public:

        /*
         * Default Constructor.
         * Heap should be empty
         */
        FibHeap() {
            head = NULL;
            tail = NULL;
            min = NULL;
            
        };

        /*
         * Heap should be built using the array K containing
         * s items of keytype.  Once all the data is in the
         * heap, a single call of consolidate should be used
         * to form the binomial trees.
         */
        FibHeap(keytype k[], int s) {
            min = NULL;
            head = NULL;
            tail = NULL;

			for (int i = 0; i < s; i++) {
				insert(k[i]);
			}

            consolidate();
        };

        /*
         * Copy constructor
         */
        // FibHeap(const FibHeap &oldTree) {
        //     //root = CopyHelper(oldTree.root);

        // };

        /*
         * Copy assignment operator
         */
        // FibHeap& operator=(FibHeap& other) {
			
		// }

        /*
         * Destructor
         */
        // ~FibHeap() {
        //     //Destructor(root);
        // };

        /*
         * Returns the minimum key in the heap without 
         * modifying the heap.
         */
        keytype peekKey() {
            return min->key;
        };

        /*
         * Removes the minimum key in the heap
         * and returns the key
         */
        keytype extractMin() {
            return peekKey();
        };

        /*
         * Inserts the key k into the heap
         */
        void insert(keytype k) {
            FNode* newnode = new FNode();
            newnode = newNode(k);

            if (head == NULL) {
                head = newnode;
                min = newnode;
                tail = newnode;
            }

            else if (k < min->key) {
                tail->right = newnode;
                tail = tail->right;
                tail->right = NULL;
                min = newnode;
            }

            else {
                tail->right = newnode;
                tail = tail->right;
                tail->right = NULL;
            }

        };

        /*
         * Merges the heap H2 into the current heap.
         * Consumes H2
         */
        void merge(FibHeap<keytype> &H2) {
            // link head to tail both ways
            tail->right = H2.head;
            H2.head->left = tail;
            tail = H2.tail;

            // find new min if needed
            FNode* curr = head;
            while(curr != NULL){
                if(min == NULL || curr->key < min->key){
                    min = curr;
                }
                curr = curr->right;
            }
        };

        /*
         * Writes the keys stored in the heap, starting
         * at the head of the list.  When printing a
         * binomial tree, print the size of the tree first
         * and then use a modified preorder traversal
         * of the tree.
         */
        void printKey() {
            FNode* curr = head;

            while (curr) {
                cout << "B" << curr->degree << endl << curr->key << " ";
                preorder(curr->child);
                curr = curr->right;
                cout << endl << endl;
            }
		}

};