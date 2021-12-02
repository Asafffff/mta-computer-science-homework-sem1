// int findFailPass(int grades[], int size) {
//   int left = 0, right = size - 1;
//   int mid;

//   while (left <= right) {
//     mid = (int)((left + right) / 2);

//     if (grades[mid] < GRADE_PASS && grades[mid + 1] >= GRADE_PASS)
//       return mid;
//     else if (grades[mid] >= GRADE_PASS)
//       right = mid - 1;
//     else
//       left = mid + 1;
//   }
//   return NOT_FOUND;
// }