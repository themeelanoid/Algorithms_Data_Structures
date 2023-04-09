/*
PROBLEM DESCRIPTION
Given two sorted arrays nums1 and nums2 of size m and n respectively,
return the median of the two sorted arrays.
The overall run time complexity should be O(log (m+n)).
*/

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const int kPlusInf = numeric_limits<int>::max();
const int kMinusInf = numeric_limits<int>::min();

class Solution {
 public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    if (n1 > n2) {
      return findMedianSortedArrays(nums2, nums1);
    }
    if (n1 == 0) {
      return n2 % 2 ? nums2[n2 / 2] : (nums2[n2 / 2] + nums2[n2 / 2 - 1]) / 2.0;
    }

    int l = 0;
    int r = n1;
    int middle = (n1 + n2 + 1) / 2;
    do {
      int posN1 = (l + r) / 2;
      int posN2 = middle - posN1;
      int leftN1 = posN1 == 0 ? kMinusInf : nums1[posN1 - 1];
      int leftN2 = posN2 == 0 ? kMinusInf : nums2[posN2 - 1];
      int rightN1 = posN1 >= n1 ? kPlusInf : nums1[posN1];
      int rightN2 = posN2 >= n2 ? kPlusInf : nums2[posN2];

      if (leftN1 <= rightN2 && leftN2 <= rightN1) {
        return (n1 + n2) % 2
                   ? max(leftN1, leftN2)
                   : (max(leftN1, leftN2) + min(rightN1, rightN2)) / 2.0;
      } else if (leftN1 > rightN2) {
        r = posN1 - 1;
      } else {
        l = posN1 + 1;
      }
    } while (l <= r);
    return 0;
  }
};

int main() {
  vector<int> a = {1, 2, 5, 7, 10, 11};
  vector<int> b = {2, 3, 4, 6, 7, 8, 9, 10, 11};
  Solution sol;
  cout << sol.findMedianSortedArrays(a, b) << endl;
}