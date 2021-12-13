#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SIZE 10
#define MAX_INT_SIZE 10
#define FUNC_COUNT 9
#define EXIT 0

// Custom defines
#define ASCII_NUM_ZERO 48
#define END_OF_STRING_CHAR '\0'

// Add your recursive functions declarations here
bool isEven(int num, int digit);
int howManyPaths(int x, int y);
int biggestLowPower(int x, int num);
int partSum(int num);
void intToStr(int num, char s[]);
void fillMaxPrefixesArray(int numbers[], int n, int maxPrefixesArray[]);
void getMinToStart(int numbers[], int n);
void combineArrays(int sortedArr1[], int size1, int sortedArr2[], int size2);
int countSmaller(int arr[], int start, int end, int num);

// Testing functions
int readArray(int data[], int maxSize);
void printArray(int data[], int size);
void bubbleSort(int arr[], int size);
void swap(int arr[], int i, int j);
void checkQ1();
void checkQ2();
void checkQ3();
void checkQ4();
void checkQ5();
void checkQ6();
void checkQ7();
void checkQ8();
void checkQ9();

/*********** main - don't make any changes here !!! ***************************/
void main() {
  int funcNum;
  bool exit = false;

  while (!exit) {
    printf("Enter the number of function you want to check (1-%d) or %d to exit the program: ", FUNC_COUNT, EXIT);
    scanf("%d", &funcNum);

    switch (funcNum) {
      case 1:
        checkQ1();
        break;
      case 2:
        checkQ2();
        break;
      case 3:
        checkQ3();
        break;
      case 4:
        checkQ4();
        break;
      case 5:
        checkQ5();
        break;
      case 6:
        checkQ6();
        break;
      case 7:
        checkQ7();
        break;
      case 8:
        checkQ8();
        break;
      case 9:
        checkQ9();
        break;
      case EXIT:
        exit = true;
        break;
      default:
        printf("Invalid choice.\n");
    }
    printf("\n");
  }
}

/***************** Testing functions - don't make any changes here!!! ***************/
void checkQ1() {
  int num, dig;

  printf("Enter a positive integer: ");
  scanf("%d", &num);
  printf("Enter a digit: ");
  scanf("%d", &dig);
  if (isEven(num, dig)) {
    printf("%d appears even number of times in %d\n", dig, num);
  } else {
    printf("%d appears odd number of times in %d\n", dig, num);
  }
}

void checkQ2() {
  int x, y;

  printf("Enter two non-negative integers: ");
  scanf("%d%d", &x, &y);
  printf("There are %d paths from (0,0) to (%d,%d)\n", howManyPaths(x, y), x, y);
}

void checkQ3() {
  int x, num;

  printf("Enter two positive integers: ");
  scanf("%d%d", &x, &num);
  printf("The biggest power of %d which is smaller than %d is %d\n", x, num, biggestLowPower(x, num));
}

void checkQ4() {
  int num;

  printf("Enter a positive integer: ");
  scanf("%d", &num);
  printf("The partial sum of %d digits is %d\n", num, partSum(num));
}

void checkQ5() {
  int num;
  char string[MAX_INT_SIZE + 1];

  printf("Enter a positive integer: ");
  scanf("%d", &num);
  intToStr(num, string);
  printf("The string representing the integer %d is %s\n", num, string);
}

void checkQ6() {
  int numbers[SIZE];
  int maxPrefixes[SIZE];
  int size;

  size = readArray(numbers, SIZE);
  fillMaxPrefixesArray(numbers, size, maxPrefixes);
  printf("Max prefixes array: ");
  printArray(maxPrefixes, size);
}

void checkQ7() {
  int numbers[SIZE];
  int size;

  size = readArray(numbers, SIZE);
  getMinToStart(numbers, size);
  printf("The minimal number is: %d\n", numbers[0]);

  // check if all other numbers are still inb array
  bubbleSort(numbers, size);
  printf("The sorted array: ");
  printArray(numbers, size);
}

void checkQ8() {
  int arr1[SIZE], arr2[2 * SIZE];
  int size1, size2;

  size1 = readArray(arr1, SIZE);
  size2 = readArray(arr2, 2 * SIZE - size1);

  // sort arrays
  bubbleSort(arr1, size1);
  bubbleSort(arr2, size2);

  combineArrays(arr1, size1, arr2, size2);
  printf("The combined sorted array: ");
  printArray(arr2, size1 + size2);
}

void checkQ9() {
  int numbers[SIZE];
  int size, num;

  // read numbers from user (assumption: numbers are different from each other)
  size = readArray(numbers, SIZE);
  bubbleSort(numbers, size);

  printf("Please enter an integer: ");
  scanf("%d", &num);

  printf("There are %d numbers in array that are smaller than %d\n", countSmaller(numbers, 0, size - 1, num), num);
}

// This function reads a series of integers from user into data array.
// The function will first ask the user to enter the number of integers he wishes
// to enter to array. If number is bigger than maxSize, then only the first masSize
// numbers will be read.
// The fucntion returns the arrays logical size (number of elements inserted into array).
int readArray(int data[], int maxSize) {
  int count;
  int i; // number of elements inserted into array

  printf("How many numbers would you like to enter to array ? (no more than %d) ", maxSize);
  scanf("%d", &count);
  if (count > maxSize) {
    count = maxSize;
  }
  printf("Please enter %d integers: ", count);

  for (i = 0; i < count; i++) {
    scanf("%d", &data[i]); // read current input number
  }

  return count;
}

// This function prints the first size elements of data array (integers).
void printArray(int data[], int size) {
  int i;

  for (i = 0; i < size; i++) {
    printf("%d ", data[i]);
  }
  printf("\n");
}

// This functions sorts arr in increasing order using bubble sort algorithm
void bubbleSort(int arr[], int size) {
  int i, j;

  for (i = 0; i < size - 1; i++)
    for (j = 0; j < size - i - 1; j++)
      if (arr[j] > arr[j + 1])
        swap(arr, j, j + 1);
}

void swap(int arr[], int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

/******************************* Recursive functions **************************/
// Add recursive functions implementation here

bool isEven(int num, int digit) {
  int lastDigit, numWithoutLastDigit;

  if (num == 0) {
    return true;
  }

  lastDigit = num % 10;
  numWithoutLastDigit = num / 10;

  if (digit == lastDigit) {
    return !isEven(numWithoutLastDigit, digit);
  } else {
    return isEven(numWithoutLastDigit, digit);
  }
}

int howManyPaths(int x, int y) {
  if (y == 0 || x == 0) {
    return 1;
  }

  return howManyPaths(x - 1, y) + howManyPaths(x, y - 1);
}

int biggestLowPower(int x, int num) {
  if (num / x == 0) {
    return 1;
  }

  return biggestLowPower(x, num / x) * x;
}

int partSum(int num) {
  int firstDigit, i = 0;
  int modifiedNum = num;
  int powersOfTenResult = 1;
  int firstDigitByPowersOfTen;

  // Stop condition
  if (num / 10 == 0) {
    return 0;
  }

  // Modify the original number until we are able to get its first digit
  while (modifiedNum > 9) {
    modifiedNum /= 10;
    i++;
  }
  firstDigit = modifiedNum;

  // Calculate the power of tens we need to remove from the original number. For example, If the number is 2453,
  // and we need to remove the first digit, we need to remove 2000 from the number, or in other words - (2 * 10^i)
  while (i > 0) {
    powersOfTenResult *= 10;
    i--;
  }

  firstDigitByPowersOfTen = firstDigit * powersOfTenResult;

  return partSum(num - firstDigitByPowersOfTen) + firstDigit;
}

void intToStr(int num, char s[]) {
  int lastDigit = num % 10;
  char lastDigitInAscii = lastDigit + ASCII_NUM_ZERO;

  int i = 0;

  // Initialize first char of the string to our last digit, and mark the end of the string.
  if (num / 10 == 0) {
    s[0] = lastDigitInAscii;
    s[1] = END_OF_STRING_CHAR;
    return;
  }

  intToStr(num / 10, s);

  // Add sequent lastDigit to the end of the string
  while (true) {
    if (s[i] == END_OF_STRING_CHAR) {
      s[i] = lastDigitInAscii;
      s[i + 1] = END_OF_STRING_CHAR;
      break;
    }
    i++;
  }
}

void fillMaxPrefixesArray(int numbers[], int n, int maxPrefixesArray[]) {
  int lastNumber;
  int lastNumberInResultArray;

  if (n == 1) {
    maxPrefixesArray[0] = numbers[0];
    return;
  }

  fillMaxPrefixesArray(numbers, n - 1, maxPrefixesArray);

  // If last number of 'maxPrefixesArray' is >= last number of 'numbers', assign it as the next number of
  // 'maxPrefixesArray', otherwise, assign the last number of 'numbers' as the next number of 'maxPrefixesArray'
  lastNumber = numbers[n - 1];
  lastNumberInResultArray = maxPrefixesArray[n - 2];
  if (lastNumberInResultArray >= lastNumber) {
    maxPrefixesArray[n - 1] = lastNumberInResultArray;
  } else {
    maxPrefixesArray[n - 1] = lastNumber;
  }
}

void getMinToStart(int numbers[], int n) {
  int tempNum;

  if (n == 1) {
    return;
  }

  if (numbers[n - 1] < numbers[n - 2]) {
    tempNum = numbers[n - 2];
    numbers[n - 2] = numbers[n - 1];
    numbers[n - 1] = tempNum;
  }

  getMinToStart(numbers, n - 1);
}

void combineArrays(int sortedArr1[], int size1, int sortedArr2[], int size2) {
  int i, lastNumberArr1, lastNumberArr2;
  int totalSize = size1 + size2;

  if (size1 == 0 || size2 == 0) {
    if (size2 == 0 && size1 != 0) {
      for (i = 0; i < size1; i++) {
        sortedArr2[i] = sortedArr1[i];
      }
    }
    return;
  }

  lastNumberArr1 = sortedArr1[size1 - 1];
  lastNumberArr2 = sortedArr2[size2 - 1];

  if (lastNumberArr1 >= lastNumberArr2) {
    sortedArr2[totalSize - 1] = lastNumberArr1;
    combineArrays(sortedArr1, size1 - 1, sortedArr2, size2);
  } else if (lastNumberArr1 < lastNumberArr2) {
    sortedArr2[totalSize - 1] = lastNumberArr2;
    combineArrays(sortedArr1, size1, sortedArr2, size2 - 1);
  }
}

int countSmaller(int arr[], int start, int end, int num) {
  int middle = (end + start) / 2;
  int middleNumber = arr[middle];
  int firstNumber = arr[start];
  int lastNumber = arr[end];

  if (num > lastNumber) {
    return end + 1;
  }

  if (middle == start) {
    if (middleNumber < num) {
      return middle + 1;
    } else {
      return middle;
    }
  }

  if (num == middleNumber) {
    return middle;
  } else if (num > middleNumber) {
    return countSmaller(arr, middle, end, num);
  } else if (num < middleNumber) {
    return countSmaller(arr, start, middle, num);
  }
}