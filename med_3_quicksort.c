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

const int  MAX_N =  500000;
int global_n; // Didn't want to mess up functions when debugging, 
              // so I added this to use as the list size
bool PRINTING = false; // Print debugging statements if true.

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
    //x += random() % 100;
    //a[i] = x;
      a[i] = i;
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
    if( PRINTING )
      print_list(a, global_n);
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
    if( PRINTING )
      print_list(a, global_n);
    quick_sort_left(a, left, j - 1);
    quick_sort_left(a, j + 1, right);
    }  // end if

  } // quick sort

////////////////////////////////////////////////////////////////////

///////////////////////// CAITLIN AND DAN CODE /////////////////////////
//scrambles a list into the worst case for a median of three where the pivot 
//is swapped to the left. 
//n is size of list
//sorted is a sorted list of length n
//scrambled will store the worst case for a median of three
////integer power function
int pow (int base, int power)
{
  if (power == 0)
  {
    return 1; 
  }
  if (power % 2 == 1)
  {
    return pow(base, power-1) * base; 
  }
  int z = pow(base, power/2); 
  return z*z; 
}

void scrambleList (int n, long sorted [], long scrambled [])
{
  //l is the power we are working on 
  //start in the starting index odd numbers 
  //step is the current step we are on
  int l = 0, start, step; 
  //place the odd numbers in
  cout << "Scrambling odds" << endl;
  for (int p = 1; p < n; )
  {
    //cout << "Outer P: " << p << endl;
    start = pow (2, l) - 1; 
    step = pow(2, l+1); 

    if( start > (n-1)/2)
      break;


    cout << "START: " << start << "  STEP: " << step << "  P: " << p <<  endl;
    while (start < (n-1)/2)
    {
      //cout << "start: " << start << " p: " << p << endl;
      scrambled[start] = sorted[p]; 
      p = p + 2; 
      start = start + step; 
    }
    l++; 
  }
  
  cout << "Scrambling evens" << endl;
  //placing the even numbers in
  int num = 0; 
  for (int i = (n-1)/2; i < n - 1; i++)
  {
    scrambled[i] = sorted[num];
    num = num + 2; 
  }

  //placing the last number in 
  scrambled[n-1] = sorted[n-1];
}


////////////////////// END CAITLIN AND DAN CODE /////////////////////////

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
  if( argc == 2 )
    n = atoi(argv[1]);
  else
    n = 10000;
  global_n = n;
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

  // Scramble a sorted list for worst case in quicksort
  scrambleList (n, b, a);
  // Copy scrambled list to run on normal quicksort
  for( i=0; i<n; i++ )
  {
    if( PRINTING )
      cout << a[i] << " ";
    b[i] = a[i];
  }
  cout << endl;

  cout << "Before WORST CASE quicksort_median_3" << endl;
  t1 = clock_seconds();
  quick_sort_median_3(a, 0, n - 1);
  t2 = clock_seconds();
  cout << "After WORST CASE quicksort_median_3" << endl;
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


  }

////////////////////////////////////////////////////////////////////
//                End median of 3 quicksort                       //
////////////////////////////////////////////////////////////////////
