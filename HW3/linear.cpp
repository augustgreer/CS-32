//
//  linear.cpp
//  HW3
//
//  Created by August Greer on 2/9/18.
//  Copyright © 2018 CS32. All rights reserved.
//
//#include <cassert>
//#include <iostream>

//bool somePredicate(double x)
//{
//    return x > 0;
//}

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
    if (0 >= n)
        return true;
    if (somePredicate(a[n - 1]))
    {
        if (allTrue(a, n - 1))
            return true;
    }
    return false;
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
    int countLast = 0;
    int countFirst = 0;
    if (0 >= n)
        return 0;
    if (!somePredicate(a[n - 1]))
        countLast++;
    countFirst = countFalse(a, n - 1);
    return countFirst + countLast;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n)
{
    if (0 >= n)
        return -1;
    if (!somePredicate(a[0]))
        return 0;
    int first = firstFalse(a + 1, n - 1);
    if (-1 == first)
        return -1;
    else
        return ++first;
}

// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
   if (0 >= n)
       return -1;
    if (1 == n)
        return 0;
    if (a[indexOfMin(a, n - 1)] > a[n - 1])
        return --n;
    else
        return indexOfMin(a, n - 1);
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if (0 >= n2)
        return true;
    if (0 >= n1) //and n2 is not empty
        return false;
    if (a1[0] == a2[0])
        return (includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1));
    else
        return (includes(a1 + 1, n1 - 1, a2, n2));
}

//int main()
//{
//    double negArr[5] = {1,2,3,-3,7};
//    double arr[5] = {1,2,3,3,7};
//    assert(!allTrue(negArr, 5));
//    assert(allTrue(arr, 5));
//    assert(countFalse(negArr, 5) == 1);
//    assert(countFalse(arr, 5) == 0);
//    assert(firstFalse(negArr, 5) == 3);
//    assert(firstFalse(arr, 5) == -1);
//    assert(indexOfMin(arr, 5) == 0);
//    assert(indexOfMin(negArr, 5) == 3);
//    assert(!includes(arr, 5, negArr, 5));
//}

