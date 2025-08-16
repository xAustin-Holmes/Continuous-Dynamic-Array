#include <random>
#include <iostream>
#include <string>

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
        int initial;
        bool initFlag;

        /*
         * Doubles the capacity of the array
         */
        void doubleCap() {
            int newCapacity = capacity * 2;
            elmtype *newArray =  new elmtype[newCapacity];

            for (int i=0;i < size;i++) {
                newArray[i] = arrayA[(i + front) % size];
            }

            delete[] arrayA;
            arrayA = newArray;
            capacity = newCapacity;
            front = 0;
            return;
        };

        /*
         * Shrinks the capacity of the array
         */
        void shrinkCap() {
            int newCapacity = capacity / 2;
            elmtype *newArray =  new elmtype[newCapacity];

            for (int i=0;i < size;i++) {
                newArray[i] = arrayA[(i + front) % size];
            }

            delete[] arrayA;
            arrayA = newArray;
            capacity = newCapacity;
            front = 0;
            return;
        };

        /*
         * MergeSort Algorithm
         */
        void mergeSort(int min, int max) {
            if (min >= max) {
                return;
            }
            int mid = (min + max + 1) / 2;

            mergeSort(min, mid - 1);
            mergeSort(mid, max);

            merge(min,mid,max);
            return;
        };

        /*
         * Merges the left and right subarrays
         */
        void merge(int min, int mid, int max) {
            elmtype *newArray =  new elmtype[max - min + 1];
            int initMin = min;

            int midR = mid;
            int midL = mid - 1;

            int i = 0;

            for (;min<=midL && max >= midR;i++) {
                if (arrayA[(midR + front) % size] < arrayA[(min + front) % size]) {
                    newArray[i] = arrayA[(midR + front) % size];
                    midR++;
                } else {
                    newArray[i] = arrayA[(min + front) % size];
                    min++;
                }
            }

            for (;min<=midL;i++, min++) {
                newArray[i] = arrayA[(min + front) % size];
            }

            for (;max<=midR;i++, midR++) {
                newArray[i] = arrayA[(midR + front) % size];
            }

            for (int j=0;j<i;j++) {
                arrayA[(j + initMin + front) % size] = newArray[j];
            }

            delete[] newArray;
            return;
        };

    public:

        /*
         * Constructs empty array
         */
        CDA() {
            size = 0;
            capacity = 2;
            front = 0;
            back = 0;
            arrayA = new elmtype;
            arrayB = new int;
            arrayC = new int;
            initFlag = 0;

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
                return -1;
            } else {
                if (arrayB[i] < cSize) {
                    if (arrayC[arrayB[i]] == i) {
                        return arrayA[(front + i) % size];
                    } else {
                        return initial;
                    }
                } else {
                    return -1;
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
            } else {
                if (back == size - 1 && front != 0) {
                    back = 0;
                } else {
                    back = back + 1;
                }
            }
            size = size + 1;
            arrayA[back] = v;
            arrayB[back] = cSize;
            arrayC[cSize] = back;
            cSize++;

            return;
        };

        /*
         * Stores element v at front of array
         * Doubles array capacity if v does not fit
         */
        void AddFront(elmtype v) {
            if (size == capacity) {
                doubleCap();
            }
            if (front == 0) {
                front = capacity - 1;
            } else {
                front = front - 1;
            }
            arrayA[front] = v;
            size = size + 1;

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
                shrinkCap();
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
                shrinkCap();
            }
            return;
        };

        /*
         * Returns the size of the array
         */
        int length() {
            return size;
        };

        /*
         * Returns the capacity of the array
         */
        int capacity() {
            return capacity;
        };

        /*
         * Uses QuickSelect to return the kth 
         * smallest element
         * Array is not sorted
         */
        elmtype Select(int k) {
            return;
        };

        /*
         * Uses MergeSort to sort array elements
         * from smallest to largest
         */
        void Sort() {
            mergeSort(arrayA[front], arrayA[back]);
        };

        /*
         * Performs a linear search of the array
         * to find element e
         * Array is not sorted
         */
        int Search(elmtype e) {
            for (int i = 0; i < size - 1; i++) {
                if (arrayA[i] == e) {
                    return (front + 1) % size;
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

            while (min < max) {
                int mid = (min + front) % size + (max - min) / 2;
                if (arrayA[mid] == e) {
                    return mid;
                } 
                else if (arrayA[mid] < e) {
                    min = mid + 1;
                } else {
                    max = mid - 1;
                }
            }
            return -1;
        };
};