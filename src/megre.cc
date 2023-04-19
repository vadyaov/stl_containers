#include <iostream>
#include <vector>

using namespace std;

template<typename T>
  void MergeSort(typename vector<T>::iterator first, typename vector<T>::iterator last) {
    if (last - first < 2)
      return;
    if (last - first == 2) {
      if (*first > *(first + 1)) {
        swap(*first, *(last - 1));
        cout << *first << " " << *(last - 1) << endl;
      }
      return;
    }
    MergeSort<T>(first, first + (last - first) / 2);
    MergeSort<T>(first + (last - first) / 2, last);

    vector<T> tmp;
    typename vector<T>::iterator start_left = first,
                                 end_left = first + (last - first) / 2,
                                 start_right = end_left;
      /* cout << "start_left = " << *start_left << endl; */
      /* cout << "start_right = " << *start_right << endl; */
    while (start_right < last && start_left < end_left) {
      if (*start_left < *start_right)
        tmp.push_back(*start_left++);
      else
        tmp.push_back(*start_right++);
    }
    while (start_right < last)
      tmp.push_back(*start_right++);
    while (start_left < end_left)
      tmp.push_back(*start_left++);

    /* for (auto k : tmp) */
    /*   cout << k << " "; */
    /* cout << endl; */

    
  }

int main() {
  vector<int> vec {38, 27, 43, 3, 9, 82, 10};

  for (auto i : vec)
    cout << i << " ";
  cout << endl;

  MergeSort<int>(vec.begin(), vec.end());

  /* for (auto i : vec) */
  /*   cout << i << " "; */
  /* cout << endl; */
  return 0;
}
