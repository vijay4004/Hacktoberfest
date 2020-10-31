// Let us consider the following problem to understand Segment Trees without recursion.

// We have an array arr[0 . . . n-1]. We should be able to,

//     Find the sum of elements from index l to r where 0 <= l <= r <= n-1
//     Change value of a specified element of the array to a new value x. We need to do arr[i] = x where 0 <= i <= n-1.


// Solution is to create another array and store sum from start to i at the ith index in this array. Sum of a given range can now be 
// calculated in O(1) time, but update operation takes O(n) time now. This works well if the number of query operations are large and 
// very few updates.

#include <bits/stdc++.h> 
using namespace std; 
  
// limit for array size 
const int N = 100000;  
  
int n; // array size 
  
// Max size of tree 
int tree[2 * N]; 
  
// function to build the tree 
void build( int arr[])  
{  
    // insert leaf nodes in tree 
    for (int i=0; i<n; i++)     
        tree[n+i] = arr[i]; 
      
    // build the tree by calculating parents 
    for (int i = n - 1; i > 0; --i)      
        tree[i] = tree[i<<1] + tree[i<<1 | 1];     
} 
  
// function to update a tree node 
void updateTreeNode(int p, int value)  
{  
    // set value at position p 
    tree[p+n] = value; 
    p = p+n; 
      
    // move upward and update parents 
    for (int i=p; i > 1; i >>= 1) 
        tree[i>>1] = tree[i] + tree[i^1]; 
} 
  
// function to get sum on interval [l, r) 
int query(int l, int r)  
{  
    int res = 0; 
      
    // loop to find the sum in the range 
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) 
    { 
        if (l&1)  
            res += tree[l++]; 
      
        if (r&1)  
            res += tree[--r]; 
    } 
      
    return res; 
} 
  
// driver program to test the above function  
int main()  
{ 
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; 
  
    // n is global 
    n = sizeof(a)/sizeof(a[0]); 
      
    // build tree  
    build(a); 
      
    // print the sum in range(1,2) index-based 
    cout << query(1, 3)<<endl; 
      
    // modify element at 2nd index 
    updateTreeNode(2, 1); 
      
    // print the sum in range(1,2) index-based 
    cout << query(1, 3)<<endl; 
  
    return 0; 
} 

// Output:

// 5
// 3
