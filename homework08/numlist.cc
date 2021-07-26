#include "numlist.h"

// Partitioning functions
// Serial partition
unsigned int NumList::partition(vector<int>& keys, unsigned int low, 
                                unsigned int high)
{
    /*
    cout << "===Now print original list:=== " << endl;
    for(int i = 0; i < keys.size(); i ++){
        cout << keys.at(i) << " ";
    }
    cout << endl;*/
    // Use the last element as the pivot
    int pivot = keys[high];

    // TODO: Implement the serial partitioning method
    /*
    int num = keys.size();
    int *lt_1 = new int [num];
    int *gt_1 = new int [num];
    int *newKey = new int [num];
    
    for(int i = 0; i < num; i ++){
        if(i == high){
            lt_1[i] = 0;
            gt_1[i] = 0;
        }
        else if(keys[i] <= pivot){
            lt_1[i] = 1;
            gt_1[i] = 0;
        }
        else{
            lt_1[i] = 0;
            gt_1[i] = 1;
        }
    }
    
    int count = 0;
    for(int i = 0; i < num; i ++){
        if(lt_1[i] > 0){
            newKey[count ++] = keys[i];
        }
    }
    newKey[count ++] = pivot;
    for(int i = 0; i < num; i ++){
        if(gt_1[i] > 0){
            newKey[count ++] = keys[i];
        }
    }
    
    int returnVal = high;
    if(newKey[high] != keys[high]){
        returnVal ++;
    }
    
    //cout << "Now print my sorted list: " << endl;
    list.erase(list.begin(), list.end());
    for(int i = 0; i < num; i ++){
        //cout << newKey[i] << " ";
        list.push_back(newKey[i]);
    }
    //cout << endl;
    
    delete [] lt_1;
    delete [] gt_1;
    delete [] newKey;
    
    return returnVal;*/
    int position = low;
    for(int i = low; i < high; i ++){
        if(keys[i] < pivot){
            swap(keys[i], keys[position ++]);
        }
    }
    swap(keys[position], keys[high]);
    return position;
}

// Parallel partition
unsigned int NumList:: partition_par(vector<int>& keys, unsigned int low,
                                     unsigned int high)
{
    // Use the last element as the pivot
    int pivot = keys[high];
    // TODO: Implement the parallel partitioning method
    // There should be two #pragmas to parallelize the loop
    // First loop is calculating the lt and gt arrays
    // Second is when the integers are copied to the correct position (i.e.,
    // left or right side of the pivot
    int num = keys.size();
    int *lt = new int [num];
    int *gt = new int [num];
    int *newKey = new int [num];
    
#pragma omp parallel for
        for(int i = 0; i < num; i ++){
            if(i == high){
                lt[i] = 0;
                gt[i] = 0;
            }
            else if(keys[i] <= pivot){
                lt[i] = 1;
                gt[i] = 0;
            }
            else{
                lt[i] = 0;
                gt[i] = 1;
            }
        }
    int count = 0;
    for(int i = 0; i < num; i ++){
        if (lt[i] > 0){
            newKey[count ++] = keys[i];
        }
    }
        
    newKey[count ++] = pivot;
        
    for(int i = 0; i < num; i ++){
        if(gt[i] > 0){
            newKey[count ++] = keys[i];
        }
    }
    
    int returnVal = high;
    if(newKey[high] != keys[high]){
        returnVal ++;
    }
    
    list.erase(list.begin(), list.end());

    for(int i = 0; i < num; i ++){
        list.push_back(newKey[i]);
    }
    
    delete [] gt;
    delete [] lt;
    delete [] newKey;
    
    return returnVal;
}

// Actual qsort that recursively calls itself with particular partitioning
// strategy to sort the list
void NumList::qsort(vector<int>& keys, int low, int high, ImplType opt)
{
    if(low < high) {
        unsigned int pi;
        if(opt == serial) {
            pi = partition(keys, low, high);
        } else {
            pi = partition_par(keys, low, high);
        }
        qsort(keys, low, pi - 1, opt);
        qsort(keys, pi + 1, high, opt);
    }
}

// wrapper for calling qsort
void NumList::my_qsort(ImplType opt)
{
    /* Initiate the quick sort from this function */
    qsort(list, 0, list.size() - 1, opt);
}
// Default constructor
// This should "create" an empty list
NumList::NumList() {
    /* do nothing */
    /* you will have an empty vector */
}
// Contructor
// Pass in a vector and the partitioning strategy to use
NumList::NumList(vector<int> in, ImplType opt) {
    list = in;
    my_qsort(opt);
}
// Destructor
NumList::~NumList() {
    /* do nothing */
    /* vector will be cleaned up automatically by its destructor */
}
// Get the element at index
int NumList::get_elem(unsigned int index)
{
    return list[index];
}
// Print the list
void NumList::print(ostream& os)
{
    for(unsigned int i = 0; i < list.size(); i++) {
        os << i << ":\t" << list[i] << endl;
    }
}
