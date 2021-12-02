#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SEMESTER_A 'A'
#define SEMESTER_B 'B'
#define MAXIMUM_NUMBER_OF_EXERCISES 13
#define MINIMUM_NUMBER_OF_EXERCISES 2
#define AVERAGE_SIZE_OF_EXERCISE_GRADES 3
#define PASSING_GRADE_THRESHOLD '6'
#define FIXED_FIRST_GRADE 30
#define FIXED_LAST_GRADE 100
#define PASSING_GRADE 60

struct CourseInfo {
  int courseNumber;
  int grade;
};
typedef struct CourseInfo COURSE_INFO;

void printWelcomeMessage();
int getNumberOfCoursesFromInput(char semester);
void getCourseInfo(COURSE_INFO semesterCoursesInfo[], int numberOfCourses);
void integerSwapAtIndex(int array[], int index1, int index2);
void sortCoursesByCourseNumber(COURSE_INFO semesterCoursesInfo[], int numberOfCourses);
void printCoursesBySemester(char semester, COURSE_INFO semesterCoursesInfo[], int numberOfCourses);
int unifyCoursesInfoAndReturnSize(COURSE_INFO coursesInfoA[], int numberOfCoursesA, COURSE_INFO coursesInfoB[],
                                  int numberOfCoursesB, int unifiedCoursesInfo[]);
int intersectCoursesInfoAndReturnSize(COURSE_INFO coursesInfoA[], int numberOfCoursesA, COURSE_INFO coursesInfoB[],
                                      int numberOfCoursesB, int intersectedCoursesInfo[]);
void sortAscending(int array[], int size);
void printUnifiedCoursesNumber(int unifiedCoursesInfo[], int unifiedCoursesInfoSize);
void printIntersectedCoursesNumber(int intersectedCoursesInfo[], int intersectedCoursesInfoSize);
COURSE_INFO findMinimumGrade(COURSE_INFO semesterCoursesInfo[], int numberOfCourses);
void getExcercisesGradesFromCourse(int courseNumber, int grade);
void buildExcercisesGradesByNumberOfExercises(int exericesGrades[], int numberOfExercises);
void printExcercisesGrades(int exericesGrades[], int numberOfExercises);
void changeGradeAtIndexTo(int excercisesGrades[], int index, int grade);
int findIndexOfSequentFailPass(int excercisesGrades[], int numberOfExcercises);
int reorderGradesByLimit(int exercisesGrades[], int numberOfExercises, int limit);
void printArrayValuesUpToLimit(int array[], int limit);

int main() {
  int numberOfFirstSemesterCourses, numberOfSecondSemesterCourses;
  COURSE_INFO firstSemesterCoursesInfo[10], secondSemesterCoursesInfo[10];

  int numberOfUnifiedCourses, numberOfIntersectedCourses;
  int unifiedCoursesInfo[20], intersectedCoursesInfo[20];

  COURSE_INFO minimumGradeCourse;

  printWelcomeMessage();

  numberOfFirstSemesterCourses = getNumberOfCoursesFromInput(SEMESTER_A);
  getCourseInfo(firstSemesterCoursesInfo, numberOfFirstSemesterCourses);

  numberOfSecondSemesterCourses = getNumberOfCoursesFromInput(SEMESTER_B);
  getCourseInfo(secondSemesterCoursesInfo, numberOfSecondSemesterCourses);

  sortCoursesByCourseNumber(firstSemesterCoursesInfo, numberOfFirstSemesterCourses);
  sortCoursesByCourseNumber(secondSemesterCoursesInfo, numberOfSecondSemesterCourses);

  printCoursesBySemester(SEMESTER_A, firstSemesterCoursesInfo, numberOfFirstSemesterCourses);
  printCoursesBySemester(SEMESTER_B, secondSemesterCoursesInfo, numberOfSecondSemesterCourses);

  numberOfUnifiedCourses =
      unifyCoursesInfoAndReturnSize(firstSemesterCoursesInfo, numberOfFirstSemesterCourses, secondSemesterCoursesInfo,
                                    numberOfSecondSemesterCourses, unifiedCoursesInfo);
  numberOfIntersectedCourses = intersectCoursesInfoAndReturnSize(firstSemesterCoursesInfo, numberOfFirstSemesterCourses,
                                                                 secondSemesterCoursesInfo,
                                                                 numberOfSecondSemesterCourses, intersectedCoursesInfo);

  printUnifiedCoursesNumber(unifiedCoursesInfo, numberOfUnifiedCourses);
  printIntersectedCoursesNumber(intersectedCoursesInfo, numberOfIntersectedCourses);

  minimumGradeCourse = findMinimumGrade(firstSemesterCoursesInfo, numberOfFirstSemesterCourses);
  printf("\n\nMinimum grade in semester %c is: %d in course #%d\n", SEMESTER_A, minimumGradeCourse.grade,
         minimumGradeCourse.courseNumber);

  getExcercisesGradesFromCourse(minimumGradeCourse.courseNumber, minimumGradeCourse.grade);

  return 0;
}

void printWelcomeMessage() {
  printf(" Welcome students!!\n"
         "and bye bye Pizzeria\n\n");
}

// Get number of courses from user input
int getNumberOfCoursesFromInput(char semester) {
  int numberOfCourses;
  printf("Please enter number of courses in semester %c: \n", semester);
  scanf("%d", &numberOfCourses);
  return numberOfCourses;
}

void getCourseInfo(COURSE_INFO semesterCoursesInfo[], int numberOfCourses) {
  for (int i = 0; i < numberOfCourses; i++) {
    printf("Enter course number and grade:\n");
    scanf("%d %d", &semesterCoursesInfo[i].courseNumber, &semesterCoursesInfo[i].grade);
  }
}

void integerSwapAtIndex(int array[], int index1, int index2) {
  int temp = array[index1];
  array[index1] = array[index2];
  array[index2] = temp;
}

// Sort courses by course number using bubble sort. Complexity: O(n^2)
void sortCoursesByCourseNumber(COURSE_INFO semesterCoursesInfo[], int numberOfCourses) {
  int i, j;
  COURSE_INFO tempCourseInfo;

  for (i = 0; i < numberOfCourses - 1; i++) {
    for (j = 0; j < numberOfCourses - i - 1; j++) {
      if (semesterCoursesInfo[j].courseNumber > semesterCoursesInfo[j + 1].courseNumber) {
        tempCourseInfo = semesterCoursesInfo[j];
        semesterCoursesInfo[j] = semesterCoursesInfo[j + 1];
        semesterCoursesInfo[j + 1] = tempCourseInfo;
      }
    }
  }
}

void printCoursesBySemester(char semester, COURSE_INFO semesterCoursesInfo[], int numberOfCourses) {
  printf("Sorted courses of semester %c:\n", semester);
  printf("Course# Grade\n");
  printf("======= =====\n");
  for (int i = 0; i < numberOfCourses; i++) {
    printf("%d\t%d\n", semesterCoursesInfo[i].courseNumber, semesterCoursesInfo[i].grade);
  }
  printf("\n");
}

// Unify coursesInfoA and coursesInfoB and return unifiedCoursesInfoSize. Complexity: O(n + m)
int unifyCoursesInfoAndReturnSize(COURSE_INFO coursesInfoA[], int numberOfCoursesA, COURSE_INFO coursesInfoB[],
                                  int numberOfCoursesB, int unifiedCoursesInfo[]) {
  int i = 0, j = 0;
  int unifiedCoursesInfoIndex = 0;
  int courseNumberA, courseNumberB;

  while (i < numberOfCoursesA && j < numberOfCoursesB) {
    courseNumberA = coursesInfoA[i].courseNumber;
    courseNumberB = coursesInfoB[j].courseNumber;

    if (courseNumberA == courseNumberB) {
      unifiedCoursesInfo[unifiedCoursesInfoIndex] = courseNumberA;
      i++;
      j++;
    } else if (courseNumberA < courseNumberB) {
      unifiedCoursesInfo[unifiedCoursesInfoIndex] = courseNumberA;
      i++;
    } else {
      unifiedCoursesInfo[unifiedCoursesInfoIndex] = courseNumberB;
      j++;
    }
    unifiedCoursesInfoIndex++;
  }

  if (i < numberOfCoursesA) {
    for (i; i < numberOfCoursesA; i++) {
      unifiedCoursesInfo[unifiedCoursesInfoIndex] = coursesInfoA[i].courseNumber;
      unifiedCoursesInfoIndex++;
    }
  } else if (j < numberOfCoursesB) {
    for (j; j < numberOfCoursesB; j++) {
      unifiedCoursesInfo[unifiedCoursesInfoIndex] = coursesInfoB[j].courseNumber;
      unifiedCoursesInfoIndex++;
    }
  }

  return unifiedCoursesInfoIndex;
}

// Intersect coursesInfoA and coursesInfoB and fill intersectedCoursesInfo. Complexity: O(n + m)
int intersectCoursesInfoAndReturnSize(COURSE_INFO coursesInfoA[], int numberOfCoursesA, COURSE_INFO coursesInfoB[],
                                      int numberOfCoursesB, int intersectedCoursesInfo[]) {
  int i = 0, j = 0;
  int intersectedCoursesInfoIndex = 0;
  int courseNumberA, courseNumberB;

  while (i < numberOfCoursesA && j < numberOfCoursesB) {
    courseNumberA = coursesInfoA[i].courseNumber;
    courseNumberB = coursesInfoB[j].courseNumber;

    if (courseNumberA == courseNumberB) {
      intersectedCoursesInfo[intersectedCoursesInfoIndex] = courseNumberA;
      intersectedCoursesInfoIndex++;
      i++;
      j++;
    } else if (courseNumberA < courseNumberB) {
      i++;
    } else {
      j++;
    }
  }

  return intersectedCoursesInfoIndex;
}

// Sort algorithem: Bubble Sort. Complexity: O(n^2)
void sortAscending(int array[], int size) {
  int i, j;

  for (i = 0; i < size - 1; i++) {
    for (j = 0; j < size - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        integerSwapAtIndex(array, j, j + 1);
      }
    }
  }
}

void printUnifiedCoursesNumber(int unifiedCoursesInfo[], int unifiedCoursesInfoSize) {
  printf("\ncourses taken in semester A or semester B: ");
  for (int i = 0; i < unifiedCoursesInfoSize; i++) {
    printf("%d ", unifiedCoursesInfo[i]);
  }
}

void printIntersectedCoursesNumber(int intersectedCoursesInfo[], int intersectedCoursesInfoSize) {
  printf("\ncourses taken in semester A and semester B: ");
  for (int i = 0; i < intersectedCoursesInfoSize; i++) {
    printf("%d ", intersectedCoursesInfo[i]);
  }
}

COURSE_INFO findMinimumGrade(COURSE_INFO semesterCoursesInfo[], int numberOfCourses) {
  COURSE_INFO minimumGradeCourseInfo;
  minimumGradeCourseInfo.courseNumber = -1;
  minimumGradeCourseInfo.grade = -1;

  for (int i = 0; i < numberOfCourses; i++) {
    if ((semesterCoursesInfo[i].grade < minimumGradeCourseInfo.grade ||
         (semesterCoursesInfo[i].grade == minimumGradeCourseInfo.grade &&
          semesterCoursesInfo[i].courseNumber < minimumGradeCourseInfo.courseNumber)) ||
        minimumGradeCourseInfo.courseNumber == -1) {
      minimumGradeCourseInfo.courseNumber = semesterCoursesInfo[i].courseNumber;
      minimumGradeCourseInfo.grade = semesterCoursesInfo[i].grade;
    }
  }

  return minimumGradeCourseInfo;
}

void getExcercisesGradesFromCourse(int courseNumber, int grade) {
  int numberOfExcercises, indexOfFailPass;
  int limitGrade, numberOfGradesLowerThanLimit;

  printf("How many exercises were given in course #%d? \n", courseNumber);
  scanf("%d", &numberOfExcercises);

  if (numberOfExcercises > MAXIMUM_NUMBER_OF_EXERCISES) {
    numberOfExcercises = MAXIMUM_NUMBER_OF_EXERCISES;
  } else if (numberOfExcercises < MINIMUM_NUMBER_OF_EXERCISES) {
    numberOfExcercises = MINIMUM_NUMBER_OF_EXERCISES;
  }

  int excercisesGrades[numberOfExcercises];

  printf("Enter exercises grades: \n");
  buildExcercisesGradesByNumberOfExercises(excercisesGrades, numberOfExcercises);

  changeGradeAtIndexTo(excercisesGrades, 0, FIXED_FIRST_GRADE);
  changeGradeAtIndexTo(excercisesGrades, numberOfExcercises - 1, FIXED_LAST_GRADE);

  printExcercisesGrades(excercisesGrades, numberOfExcercises);

  indexOfFailPass = findIndexOfSequentFailPass(excercisesGrades, numberOfExcercises);
  printf("Index of Fail-Pass is: %d\n", indexOfFailPass);

  printf("Please enter a limit grade: \n");
  scanf("%d", &limitGrade);
  numberOfGradesLowerThanLimit = reorderGradesByLimit(excercisesGrades, numberOfExcercises, limitGrade);
  printf("After reordering grades, the grades smaller than %d are: ", limitGrade);
  printArrayValuesUpToLimit(excercisesGrades, numberOfGradesLowerThanLimit);

  return;
}

void buildExcercisesGradesByNumberOfExercises(int exericesGrades[], int numberOfExercises) {
  int i = 0;

  while (i < numberOfExercises) {
    scanf("%d", &exericesGrades[i]);
    i++;
  }

  return;
}

void printExcercisesGrades(int exericesGrades[], int numberOfExercises) {
  int i;

  printf("Exercise grades: ");
  for (int i = 0; i < numberOfExercises; i++) {
    printf("%d ", exericesGrades[i]);
  }
  printf("\n");
}

void changeGradeAtIndexTo(int excercisesGrades[], int index, int grade) {
  excercisesGrades[index] = grade;
}

// Find index of sequest fail or pass by grade. Complexity: O(log(n))
int findIndexOfSequentFailPass(int excercisesGrades[], int numberOfExcercises) {
  int leftIndex = 0, rightIndex = numberOfExcercises - 1;
  int middleIndex;

  while (leftIndex <= rightIndex) {
    middleIndex = (int)((leftIndex + rightIndex) / 2);

    if (excercisesGrades[middleIndex] < PASSING_GRADE && excercisesGrades[middleIndex + 1] >= PASSING_GRADE) {
      return middleIndex;
    } else if (excercisesGrades[middleIndex] >= PASSING_GRADE) {
      rightIndex = middleIndex - 1;
    } else {
      leftIndex = middleIndex + 1;
    }
  }

  return -1;
}

// Reorder grades by limit. Complexity: O(n^2)
int reorderGradesByLimit(int exercisesGrades[], int numberOfExercises, int limit) {
  int i, j;
  int numberOfGradesLowerThanLimit = 0;

  for (i = 0; i < numberOfExercises; i++) {
    if (exercisesGrades[i] >= limit) {
      for (j = i + 1; j < numberOfExercises; j++) {
        if (exercisesGrades[j] < limit) {
          integerSwapAtIndex(exercisesGrades, i, j);
          numberOfGradesLowerThanLimit++;
          break;
        }
      }
    } else {
      numberOfGradesLowerThanLimit++;
    }
  }

  return numberOfGradesLowerThanLimit;
}

void printArrayValuesUpToLimit(int array[], int limit) {
  int i;

  for (i = 0; i < limit; i++) {
    printf("%d ", array[i]);
  }

  return;
}
