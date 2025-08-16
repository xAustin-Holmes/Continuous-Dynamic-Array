#include <random>
#include <iostream>
#include <cstring>
using namespace std;
#include "CDA.cpp"

template <typename keytype>
class Heap {
    private:

        CDA<keytype> HArray;

        void swap(keytype &key1, keytype &key2) {
            keytype tempKey = key1;
            key1 = key2;
            key2 = tempKey;
        }

        void heapify(int i) {
            int min = i;
            int l = 2 * i + 1; // left child
            int r = 2 * i + 2; // right child
            int length = HArray.Length() - 1;
        
            if (l <= length && HArray[l] < HArray[i]) {
                min = l;
            }

            else {
                min = i;
            }
            
            if (r <= length && HArray[r] < HArray[min]) {
                min = r;
            }
        
            if (min != i) {
                swap(HArray[i], HArray[min]);
        
                heapify(min);
            }
        }

    public:

        /*
         * Default Constructor.
         * Heap should be empty
         */
        Heap() {

        };

        /*
         * Heap should be built using the array K containing
         * s items of keytype.  The heap should be constructed
         * using the O(n) bottom up heap building method.
         */
        Heap(keytype k[], int s) {
            for (int i = 0; i < s; i++) {
                HArray.AddEnd(k[i]);
            }
            int j = (HArray.Length() - 2) / 2;
            for (int i = j; i >= 0; i--) {
                heapify(i);
            }
        };

        /*
         * Copy constructor
         */
        Heap(const Heap &oldHeap) {
            HArray = oldHeap.HArray;

        };

        /*
         * Copy assignment operator
         */
        Heap& operator=(const Heap &oldHeap) {
            HArray = oldHeap.HArray;

        };

        /*
         * Destructor
         */
        ~Heap() {
            while (HArray.Length() > 0) {
                HArray.DelEnd();
            }
        };

        /*
         * Returns the minimum key in the heap without 
         * modifying the heap.
         */
        keytype peekKey() {
            return HArray[0];
        };

        /*
         * Removes the minimum key in the heap
         * and returns the key
         */
        keytype extractMin() {
            keytype minKey = HArray[0];
            int length = HArray.Length() - 1;
            HArray[0] = HArray[length];
            heapify(0);
            HArray.DelEnd();
            return minKey;
        };

        /*
         * Inserts the key k into the heap
         */
        void insert(keytype k) {
            HArray.AddEnd(k);
            int length = HArray.Length() - 1;
            while(length != 0 && HArray[(length - 1) / 2] > HArray[length]) {
                swap(HArray[length], HArray[(length - 1) / 2]);
                length = (length - 1) / 2;
            }
        };

        /*
         * Writes the keys stored in the array,
         * starting at the root
         */
        void printKey() {
            for (int i = 0; i < HArray.Length(); i++) {
                cout << HArray[i] << " ";
            }
            cout << endl;
        };

};