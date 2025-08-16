#include <random>
#include <iostream>
#include <cstring>
using namespace std;

template <typename elmtype>
class CDA {
    private:
        int size;
        int capacity;
        int front;
        int back;
        elmtype *arrayA;
        int *arrayB;
        int *arrayC;
        int cSize;
        elmtype initial;
        bool initFlag;
        elmtype error;

        /*
         * Doubles the capacity of the array
         */
        void doubleCap() {
            int newCapacity = capacity * 2;
            elmtype *newArray =  new elmtype[newCapacity];

            for (int i=0;i < size;i++) {
                newArray[i] = arrayA[(i + front) % capacity];
            }

            arrayA = newArray;
            capacity = newCapacity;
            front = 0;
            back = size - 1;
            return;
        };

        /*
         * Shrinks the capacity of the array
         */
        void shrinkCap() {
            int newCapacity = capacity / 2;
            elmtype *newArray =  new elmtype[newCapacity];

            for (int i=0;i < size;i++) {
                newArray[i] = arrayA[(i + front) % capacity];
            }

            arrayA = newArray;
            capacity = newCapacity;
            front = 0;
            return;
        };

        /*
         * MergeSort Algorithm
         */
        void mergeSort(elmtype a[], int n){
			if(n <= 1) return;
			elmtype *a1 = new elmtype[n / 2];
			elmtype *a2 = new elmtype[n - (n / 2)];
			for(int i = 0; i < n / 2; i++){
				a1[i] = a[(front + i) % capacity];
			}
			for(int i = n / 2; i < n; i++){
				a2[i - n / 2] = a[(front + i) % capacity];
			}
			front = 0;
			mergeSort(a1, n / 2);
			mergeSort(a2, n - (n / 2));
			merge(a, a1, a2, n);
		};

        /*
         * Merges the left and right subarrays
         */
        void merge(elmtype a[], elmtype a1[], elmtype a2[], int n){
			int n1 = n / 2;
			int n2 = (n - (n / 2));
			int p1 = 0;
			int p2 = 0;
			int i = 0;
			while(p1 < n1 && p2 < n2){
                a[i++] = a1[p1] < a2[p2] ? a1[p1++] : a2[p2++];
			}
			while(p1 < n1){
				a[i++] = a1[p1++];
			}
			while(p2 < n2){
				a[i++] = a2[p2++];
			}
		};
        
        /*
         * QuickSelect Algorithm
         */
        int quickSelect(elmtype arrayA[], int front, int back, int k) {
            if (k > 0 && k <= back - front + 1) {
                // Select random pivot
                int pivot = rand() % size;
        
                if (pivot - front == k - 1) {
                    return arrayA[pivot];
                }
                if (pivot - front > k - 1) {
                    return quickSelect(arrayA, front, pivot - 1, k);
                }
                return quickSelect(arrayA, pivot + 1, back, k - pivot + front - 1);
            }
        
            return error;
        };

    public:

        /*
         * Constructs empty array
         */
        CDA() {
            size = 0;
            capacity = 1;
            front = 0;
            back = 0;
            arrayA = new elmtype;
            arrayB = new int;
            arrayC = new int;
            initFlag = 0;
            error = -1;

        };

        /*
         * Constructs array of capacity and size s
         */
        CDA(int s) {
            size = s;
            capacity = s;
            front = 0;
            back = s - 1;
            arrayA = new elmtype[s];
            arrayB = new int[s];
            arrayC = new int[s];
            initFlag = 0;
            error = -1;

        };

        /*
         * Constructs array of capacity and size s
         * Initialezed with value init
         */
        CDA(int s, elmtype init) {
            size = s;
            capacity = s;
            front = 0;
            back = s - 1;
            arrayA = new elmtype[s];
            arrayB = new int[s];
            arrayC = new int[s];
            cSize = 0;
            initial = init;
            initFlag = 1;
            error = -1;

        };

        /*
         * Destructor
         */
        ~CDA() {
            if (arrayA) {
                delete[] arrayA;
            }
            if (arrayB) {
                delete[] arrayB;
            }
            if (arrayC) {
                delete[] arrayC;
            }
        };

        /*
         * Copy constructor
         */
        CDA(CDA &oldArray) {
            memcpy(this, &oldArray, sizeof(CDA));

        };

        /*
         * Copy assignment operator
         */
        CDA& operator=(CDA &oldArray) {
            if (this == &oldArray) return *this;
            else {
                memcpy(this, &oldArray, sizeof(CDA));
                return *this;
            }
        };

        /*
         * Traditional bracket [] operator
         */
        elmtype& operator[](int i) {
            if (i > size - 1 || i < 0) {
                return error;
            } else {
                if (initFlag) {
                    if (arrayB[i] < cSize) {
                        if (arrayC[arrayB[i]] == i) {
                            return arrayA[(front + i) % capacity];
                        } else {
                            return initial;
                        }
                    } else {
                        return error;
                    }
                } else {
                    return arrayA[(front + i) % capacity];
                }
            }
            
        };

        /*
         * Stores element v at end of array
         * Doubles array capacity if v does not fit
         */
        void AddEnd(elmtype v) {
            if (size == capacity) {
                doubleCap();
                back = back + 1;
            } 
            else {
                if ((back == capacity - 1 && front != 0) || front == back ) {
                    back = 0;
                } else {
                    back = back + 1;
                }
            }
            
            size = size + 1;
            arrayA[back] = v;
            if (initFlag) {
                arrayB[back] = cSize;
                arrayC[cSize] = back;
                cSize++;
            }
            return;
        };

        /*
         * Stores element v at front of array
         * Doubles array capacity if v does not fit
         */
        void AddFront(elmtype v) {
            if (size == capacity) {
                doubleCap();
                //back = back + 1;
            }
            if (front == 0) {
                front = capacity - 1;
            } else {
                front = front - 1;
            }
            arrayA[front] = v;
            size = size + 1;
            if (initFlag) {
                arrayB[front] = cSize;
                arrayC[cSize] = back;
                cSize++;
            }
            return;
        };

        /*
         * Deletes element at end of array
         * Halves array capacity at 25% usage
         */
        void DelEnd() {
            if (front == back) {
                return;
            }
            else if (back == 0) {
                back = capacity - 1;
            } else {
                back = back - 1;
            }
            size = size - 1;
            if (size <= (capacity/4)) {
                // Shouldn't shrink below 4 cap
                if (capacity > 4) {
                    shrinkCap();
                }
            }
            return;
        };

        /*
         * Deletes element at front of array
         * Halves array capacity at 25% usage
         */
        void DelFront() {
            if (front == back) {
                return;
            }
            else if (front == size - 1) {
                front = 0;
            } else {
                front = front + 1;
            }
            size = size - 1;
            if (size <= (capacity/4)) {
                // Shouldn't shrink below 4 cap
                if (capacity > 4) {
                    shrinkCap();
                }
            }
            return;
        };

        /*
         * Returns the size of the array
         */
        int Length() {
            return size;
        };

        /*
         * Returns the capacity of the array
         */
        int Capacity() {
            return capacity;
        };

        /*
         * Uses QuickSelect to return the kth 
         * smallest element
         * Array is not sorted
         */
        elmtype Select(int k) {
            return quickSelect(arrayA, front, back, k);
            //return error;
        };

        /*
         * Uses MergeSort to sort array elements
         * from smallest to largest
         */
        void Sort() {
            /*
            cout << "front: " << front << endl;
            cout << "back: " << back << endl;
            cout << "arrayA[front]: " << arrayA[front] << endl;
            cout << "arrayA[back]: " << arrayA[back] << endl;
            */
            mergeSort(arrayA, size);
            // Reset front and back after sort
            front = 0;
			back = size - 1;
            return;
        };

        /*
         * Performs a linear search of the array
         * to find element e
         * Array is not sorted
         */
        int Search(elmtype e) {
            for (int i = 0; i < size; i++) {
                if ((front + i) % capacity == e) {
                    return i;
                }
            }
            return -1;
        };

        /*
         * Performs a binary search of the array
         * to find element e
         * Array is sorted
         */
        int BinSearch(elmtype e) {
            int min = 0;
            int max = size - 1;
            int mid = (max + min) / 2;

            while (min <= max) {
                int mid = (max + min) / 2;

                if (arrayA[mid] == e) {
                    return mid;
                } 
                else if (arrayA[mid] < e) {
                    min = mid + 1;
                } else {
                    max = mid - 1;
                }
            }

            if (arrayA[min] <= e) {
                return ~size;
            } else {
                return ~min;
            }

            return -1;
        };
};