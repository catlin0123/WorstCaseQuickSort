////////////////////////////////////////////////////////////////////
//                                                                //
//               Quicksort With Median of 3 Pivot                 //
//                                                                //
//    Uses setrlimit to set stack size                             //
//                                                                //
////////////////////////////////////////////////////////////////////

#include <iostream>
#include <values.h>  // for MAXLONG
#include <sys/resource.h>  // for setrlimit (stack size)
#include <stdlib.h>
using namespace std;

const int  MAX_N =  100000;

////////////////////////////////////////////////////////////////////

float clock_seconds()
  {
  return clock() / (float) CLOCKS_PER_SEC;
  }

////////////////////////////////////////////////////////////////////

void gen_rand_list(long a[], int n)
  {
  int  i;
  long x;

  x = 0;
  for (i = 0; i < n; i++)
    {
    x += random() % 100;
    a[i] = x;
    }

  }

////////////////////////////////////////////////////////////////////

void check_order(long a[], int n)
  {
  int i;
  bool ordered;

  ordered = true;
  for(i = 0; i < n - 1; i++)
    {
    if (a[i] > a[i + 1])
      ordered = false;
    }
  if (ordered)
    cout << "List is in order" << endl;
  else
    cout << "List is NOT in order" << endl;
  }



////////////////////////////////////////////////////////////////////

void swap(long &x, long &y)
  {
  long oldx;
  long oldy;

  oldx = x;
  oldy = y;
  x = oldy;
  y = oldx;
  }

////////////////////////////////////////////////////////////////////

void print_list(long a[], int n)
  {
  int i;

  for(i = 0; i < n; i++)
    {
    cout << " " << a[i];
    if ((i + 1) % 10 == 0)
      cout << endl;
    }
  cout << endl;
  }

////////////////////////////////////////////////////////////////////
//   swap median of first, middle, last to first so               //
//   quicksort function does not need to be changed               //
////////////////////////////////////////////////////////////////////

void median_of_3_to_left(long a[], int left, int right)
  {
  long a_left;
  long a_right;
  long a_mid;
  int  mid;

  mid = (left + right) / 2;
  a_left = a[left];
  a_right = a[right];
  a_mid = a[mid];

  // check for left value already median
  if ((a_left >= a_mid) && (a_left <= a_right))
    return;
  if ((a_left <= a_mid) && (a_left >= a_right))
    return;

  // check for middle value is median
  if ((a_mid >= a_left) && (a_mid <= a_right))
    {
    swap(a[mid], a[left]);
    return;
    }
  if ((a_mid <= a_left) && (a_mid >= a_right))
    {
    swap(a[mid], a[left]);
    return;
    }

  // others aren't, so right value must be median
  swap(a[right], a[left]);
  }

////////////////////////////////////////////////////////////////////
//                          quicksort                             //
//    uses original partition algorithm                           //
//    uses median of three as pivot                               //
////////////////////////////////////////////////////////////////////

void quick_sort_median_3(long a[], int left, int right)
  {
  int  i;
  int  j;
  long pivot;

  if (left < right)
    {
    i = left;
    j = right + 1;
    median_of_3_to_left(a, left, right);
    pivot = a[left];

    do
      {
      do
        i++;
      while(a[i] < pivot);

      do
        j--;
      while(a[j] > pivot);

      if (i < j)
        swap(a[i], a[j]);

      } // end do
    while (i <= j);

    swap(a[left], a[j]);
    quick_sort_median_3(a, left, j - 1);
    quick_sort_median_3(a, j + 1, right);
    }  // end if

  } // quick sort

////////////////////////////////////////////////////////////////////

void quick_sort_left(long a[], int left, int right)
  {
  int  i;
  int  j;
  long pivot;

  if (left < right)
    {
    i = left;
    j = right + 1;
    pivot = a[left];

    do
      {
      do
        i++;
      while(a[i] < pivot);

      do
        j--;
      while(a[j] > pivot);

      if (i < j)
        swap(a[i], a[j]);

      } // end do
    while (i <= j);

    swap(a[left], a[j]);
    quick_sort_left(a, left, j - 1);
    quick_sort_left(a, j + 1, right);
    }  // end if

  } // quick sort

////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
  {
  long      a[MAX_N + 1]; // quicksort needs an extra spot at end
  long      b[MAX_N + 1]; // copy for sorting again
  // long      a[100]; // quicksort needs an extra spot at end
  // long      b[100]; // copy for sorting again
  int       i;
  int       n;
  float     t1;
  float     t2;
  float     t3;
  float     t4;
  rlimit    rlim;

/*********** Set stack size as large as possible  ***/
  rlim . rlim_cur = RLIM_INFINITY;
  rlim . rlim_max = RLIM_INFINITY;
/****************/
/********* Set small stack for testing stack overflow ***
  rlim . rlim_cur = 10000;
  rlim . rlim_max = 10000;
*/
  setrlimit(RLIMIT_STACK,&rlim);
  n = 10000;
  cout << "Running quicksorts with " << n << " numbers" << endl;
  if (rlim . rlim_max == RLIM_INFINITY)
    cout << "Using maximum stack size." << endl;
  else
    cout << "Using stack size " << rlim . rlim_max << "." << endl;
  gen_rand_list(a, n);
  for (i = 0; i < n; i++)
    b[i] = a[i];

  a[n] = MAXLONG;
  b[n] = MAXLONG;

  cout << "Before quicksort_median_3" << endl;
  t1 = clock_seconds();
  quick_sort_median_3(a, 0, n - 1);
  t2 = clock_seconds();
  cout << "After quicksort_median_3" << endl;
  check_order(a, n);
  cerr << "median 3 took " << t2 - t1 << " seconds." << endl;

  cout << "Before quicksort_left" << endl;
  a[n] = MAXINT;
  t3 = clock_seconds();
  quick_sort_left(b, 0, n - 1);
  t4 = clock_seconds();
  cout << "After quicksort_left" << endl;
  check_order(b, n);
  cerr << "left took " << t4 - t3 << " seconds." << endl;

  cout << "Done with quicksort" << endl;

  }

////////////////////////////////////////////////////////////////////
//                End median of 3 quicksort                       //
////////////////////////////////////////////////////////////////////
