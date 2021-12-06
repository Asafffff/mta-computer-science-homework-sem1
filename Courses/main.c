#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SEMESTER_A 'A'
#define SEMESTER_B 'B'
#define NUMBER_OF_STUDENTS_IN_A_GROUP 6
#define MAXIMUM_OF_NUMBER_GRADES_IN_TABLE 7
#define MAXIMUM_STUDENT_NAME_LENGTH 21
#define MAXIMUM_GROUP_NAME_LENGTH 6
#define MAXIMUM_NUMBER_OF_COURSES 10
#define PASSING_GRADE 60

struct CourseInfo {
  int courseNumber;
  int grade;
};
typedef struct CourseInfo COURSE_INFO;

struct Student {
  char fullName[MAXIMUM_STUDENT_NAME_LENGTH];
  int identityNumber;
  int numberOfCoursesInSemesterA;
  COURSE_INFO courseInfo[MAXIMUM_NUMBER_OF_COURSES];
};
typedef struct Student STUDENT;

void printWelcomeMessage();
void getCourseInfo(COURSE_INFO semesterCoursesInfo[], int numberOfCourses);
void addStudentsToGroups(STUDENT groupOfGroupsOfStudents[][NUMBER_OF_STUDENTS_IN_A_GROUP], int numberOfSubGroups,
                         int numberOfStudents);
STUDENT getStudentInfoFromInput();
int getNumberOfStudentNamesByCourseNumberAndPrintThem(
    STUDENT groupOfGroupsOfStudents[][NUMBER_OF_STUDENTS_IN_A_GROUP], int numberOfSubGroups, int numberOfStudents,
    int courseNumber, char studentNames[][MAXIMUM_GROUP_NAME_LENGTH + MAXIMUM_STUDENT_NAME_LENGTH]);
char getGroupNameByIndex(int index);
int getCourseNumberFromInput();
void switchNamesWithLoisToLaneAndPrintThem(char studentNames[][MAXIMUM_GROUP_NAME_LENGTH + MAXIMUM_STUDENT_NAME_LENGTH],
                                           int numberOfStudents);
void deleteNamesWithLexAndPrintThem(char studentNames[][MAXIMUM_GROUP_NAME_LENGTH + MAXIMUM_STUDENT_NAME_LENGTH],
                                    int numberOfStudents);
void getStudentGradesByCourseNumberAndPrintThem(STUDENT groupOfGroupsOfStudents[][NUMBER_OF_STUDENTS_IN_A_GROUP],
                                                int numberOfSubGroups, int numberOfStudents, int courseNumber,
                                                int studentGrades[][MAXIMUM_OF_NUMBER_GRADES_IN_TABLE]);
void searchMaximumGradePerGroup(int studentGrades[][MAXIMUM_OF_NUMBER_GRADES_IN_TABLE], int numberOfSubGroups);
bool isStringHasLex(char string[]);
void shiftStringArrayLeft(char array[][MAXIMUM_GROUP_NAME_LENGTH + MAXIMUM_STUDENT_NAME_LENGTH], int arraySize,
                          int offset);
void resetStringToEmptyChars(char string[], int stringSize);

int main() {
  const int numberOfSubGroups = 3, numberOfStudentsInAGroup = NUMBER_OF_STUDENTS_IN_A_GROUP;
  int courseNumber, numberOfStudentsInCourse;
  STUDENT groupOfGroupsOfStudents[numberOfSubGroups][numberOfStudentsInAGroup];
  char studentNames[numberOfSubGroups * numberOfStudentsInAGroup]
                   [MAXIMUM_GROUP_NAME_LENGTH + MAXIMUM_STUDENT_NAME_LENGTH];
  int studentGrades[numberOfSubGroups][MAXIMUM_OF_NUMBER_GRADES_IN_TABLE];

  printWelcomeMessage();
  addStudentsToGroups(groupOfGroupsOfStudents, numberOfSubGroups, numberOfStudentsInAGroup);

  courseNumber = getCourseNumberFromInput();
  printf("Names of students in course#%d:\n", courseNumber);

  numberOfStudentsInCourse = getNumberOfStudentNamesByCourseNumberAndPrintThem(
      groupOfGroupsOfStudents, numberOfSubGroups, numberOfStudentsInAGroup, courseNumber, studentNames);

  switchNamesWithLoisToLaneAndPrintThem(studentNames, numberOfStudentsInCourse);
  deleteNamesWithLexAndPrintThem(studentNames, numberOfStudentsInCourse);

  printf("\nGrades in course#%d:\n", courseNumber);
  getStudentGradesByCourseNumberAndPrintThem(groupOfGroupsOfStudents, numberOfSubGroups, numberOfStudentsInAGroup,
                                             courseNumber, studentGrades);

  printf("\nMaximum grades in course#%d:\n", courseNumber);
  searchMaximumGradePerGroup(studentGrades, numberOfSubGroups);

  return 0;
}

void printWelcomeMessage() {
  printf("********************\n"
         "* Welcome Students *\n"
         "********************\n\n");
}

void getCourseInfo(COURSE_INFO semesterCoursesInfo[], int numberOfCourses) {
  for (int i = 0; i < numberOfCourses; i++) {
    printf("Enter Course number and grade: ");
    scanf("%d %d", &semesterCoursesInfo[i].courseNumber, &semesterCoursesInfo[i].grade);
  }
}

/**
 * @brief
 * groupOfGroupsOfStudents = groupOfGroupsOfStudents
 * groupOfStudents = groupOfGroupsOfStudents[i]
 * student = groupOfGroupsOfStudents[i][j]
 *
 * @param groupOfGroupsOfStudents
 * @param numberOfStudents
 */
void addStudentsToGroups(STUDENT groupOfGroupsOfStudents[][NUMBER_OF_STUDENTS_IN_A_GROUP], int numberOfSubGroups,
                         int numberOfStudents) {
  int i, j;
  char groupName;

  // Loop through sub groups
  for (i = 0; i < numberOfSubGroups; i++) {
    groupName = getGroupNameByIndex(i);

    printf("Enter students data for GROUP %c:\n", groupName);
    printf("________________________________\n");

    // Loop through students of sub groups
    for (j = 0; j < numberOfStudents; j++) {
      groupOfGroupsOfStudents[i][j] = getStudentInfoFromInput();
    }
  }
}

STUDENT getStudentInfoFromInput() {
  // FIXME - Remove
  // int r = rand() % 5;
  // STUDENT student = {
  //     .fullName = "Lois Noir",
  //     .identityNumber = 0,
  //     .numberOfCoursesInSemesterA = 1,
  //     .courseInfo[0].courseNumber = 10,
  //     .courseInfo[0].grade = 10,
  // };

  // STUDENT student2 = {
  //     .fullName = "Gur Lex",
  //     .identityNumber = 1,
  //     .numberOfCoursesInSemesterA = 1,
  //     .courseInfo[0].courseNumber = 10,
  //     .courseInfo[0].grade = 20,
  // };

  // STUDENT student3 = {
  //     .fullName = "Natali Mor",
  //     .identityNumber = 2,
  //     .numberOfCoursesInSemesterA = 1,
  //     .courseInfo[0].courseNumber = 10,
  //     .courseInfo[0].grade = 30,
  // };

  // STUDENT student4 = {
  //     .fullName = "Amit Gurevich",
  //     .identityNumber = 3,
  //     .numberOfCoursesInSemesterA = 1,
  //     .courseInfo[0].courseNumber = 10,
  //     .courseInfo[0].grade = 50,
  // };

  // STUDENT student5 = {
  //     .fullName = "Lois Lois",
  //     .identityNumber = 4,
  //     .numberOfCoursesInSemesterA = 1,
  //     .courseInfo[0].courseNumber = 10,
  //     .courseInfo[0].grade = 40,
  // };

  // switch (r) {
  //   case 0:
  //     return student;
  //   case 1:
  //     return student2;
  //   case 2:
  //     return student3;
  //   case 3:
  //     return student4;
  //   case 4:
  //     return student5;
  //   default:
  //     return student;
  // }
  STUDENT student;
  char firstName[(int)MAXIMUM_STUDENT_NAME_LENGTH / 2], lastName[(int)MAXIMUM_STUDENT_NAME_LENGTH / 2];

  printf("\nEnter student first name and last name (seperated by spaces): ");
  scanf("%s %s", firstName, lastName);

  strcat(firstName, " ");
  strcat(firstName, lastName);
  strcpy(student.fullName, firstName);

  printf("Enter student ID: ");
  scanf("%d", &student.identityNumber);

  printf("\nEnter number of courses taken in semester A: ");
  scanf("%d", &student.numberOfCoursesInSemesterA);

  getCourseInfo(student.courseInfo, student.numberOfCoursesInSemesterA);

  return student;
}

int getNumberOfStudentNamesByCourseNumberAndPrintThem(
    STUDENT groupOfGroupsOfStudents[][NUMBER_OF_STUDENTS_IN_A_GROUP], int numberOfSubGroups, int numberOfStudents,
    int courseNumber, char studentNames[][MAXIMUM_GROUP_NAME_LENGTH + MAXIMUM_STUDENT_NAME_LENGTH]) {
  int i, j, k, l;
  int numberOfStudentsInCourse, studentNamesIndex = 0;
  char currentGroupName;
  char fullGroupNameAsString[] = "GroupX";
  char fullNameWithGroupPrefix[MAXIMUM_GROUP_NAME_LENGTH + MAXIMUM_STUDENT_NAME_LENGTH];

  for (i = 0; i < numberOfSubGroups; i++) {
    currentGroupName = getGroupNameByIndex(i);
    fullGroupNameAsString[MAXIMUM_GROUP_NAME_LENGTH - 1] = currentGroupName;
    for (j = 0; j < numberOfStudents; j++) {
      resetStringToEmptyChars(fullNameWithGroupPrefix, MAXIMUM_GROUP_NAME_LENGTH + MAXIMUM_STUDENT_NAME_LENGTH);

      STUDENT currentStudent = groupOfGroupsOfStudents[i][j];
      for (k = 0; k < currentStudent.numberOfCoursesInSemesterA; k++) {
        if (currentStudent.courseInfo[k].courseNumber == courseNumber) {
          // Copy student name in the format of 'GroupX studentName'
          strcat(fullNameWithGroupPrefix, fullGroupNameAsString);
          strcat(fullNameWithGroupPrefix, " ");
          strcat(fullNameWithGroupPrefix, currentStudent.fullName);
          strcpy(studentNames[studentNamesIndex], fullNameWithGroupPrefix);

          printf("%s\n", studentNames[studentNamesIndex]);
          studentNamesIndex++;
          resetStringToEmptyChars(fullNameWithGroupPrefix, MAXIMUM_GROUP_NAME_LENGTH + MAXIMUM_STUDENT_NAME_LENGTH);
        }
      }
    }
  }

  numberOfStudentsInCourse = studentNamesIndex;

  return numberOfStudentsInCourse;
}

void resetStringToEmptyChars(char string[], int stringSize) {
  int i;

  for (i = 0; i < stringSize; i++) {
    string[i] = '\0';
  }
}

char getGroupNameByIndex(int index) {
  char groupName;

  switch (index) {
    case 0:
      groupName = 'A';
      break;
    case 1:
      groupName = 'B';
      break;
    case 2:
      groupName = 'C';
      break;
    default:
      break;
  }

  return groupName;
}

int getCourseNumberFromInput() {
  int courseNumber;

  // FIXME
  // courseNumber = 10;
  printf("\nEnter a course number: ");
  scanf("%d", &courseNumber);

  return courseNumber;
}

void switchNamesWithLoisToLaneAndPrintThem(char studentNames[][MAXIMUM_GROUP_NAME_LENGTH + MAXIMUM_STUDENT_NAME_LENGTH],
                                           int numberOfStudents) {
  int i, j;

  printf("\nNames after changing \"Lois\" to \"Lane\":\n");
  for (i = 0; i < numberOfStudents; i++) {
    for (j = 0; j < (int)(strlen(studentNames[i]) - 3); j++) {
      if (studentNames[i][j] == 'L' && studentNames[i][j + 1] == 'o' && studentNames[i][j + 2] == 'i' &&
          studentNames[i][j + 3] == 's') {
        studentNames[i][j] = 'L';
        studentNames[i][j + 1] = 'a';
        studentNames[i][j + 2] = 'n';
        studentNames[i][j + 3] = 'e';
        j += 3;
      }
    }
    printf("%s\n", studentNames[i]);
  }
}

void deleteNamesWithLexAndPrintThem(char studentNames[][MAXIMUM_GROUP_NAME_LENGTH + MAXIMUM_STUDENT_NAME_LENGTH],
                                    int numberOfStudents) {
  int i, l, k, m;
  int numberOfDeletedNames = 0;

  printf("\nNames after deleting names with \"Lex\":\n");

  for (i = 0; i < numberOfStudents - numberOfDeletedNames; i++) {
    if (isStringHasLex(studentNames[i])) {
      shiftStringArrayLeft(studentNames, numberOfStudents, i);
      numberOfDeletedNames++;
      i -= 1;
    }
  }

  for (i = 0; i < numberOfStudents - numberOfDeletedNames; i++) {
    printf("%s\n", studentNames[i]);
  }
}

bool isStringHasLex(char string[]) {
  int i = 0;

  for (i = 0; i < strlen(string); i++) {
    if (string[i] == 'L' && string[i + 1] == 'e' && string[i + 2] == 'x') {
      return true;
    }
  }

  return false;
}

void shiftStringArrayLeft(char array[][MAXIMUM_GROUP_NAME_LENGTH + MAXIMUM_STUDENT_NAME_LENGTH], int arraySize,
                          int offset) {
  int i = 0;

  for (i = offset; i < arraySize - 1; i++) {
    strcpy(array[i], array[i + 1]);
  }
}

void getStudentGradesByCourseNumberAndPrintThem(STUDENT groupOfGroupsOfStudents[][NUMBER_OF_STUDENTS_IN_A_GROUP],
                                                int numberOfSubGroups, int numberOfStudents, int courseNumber,
                                                int studentGrades[][MAXIMUM_OF_NUMBER_GRADES_IN_TABLE]) {
  int i, j, k, l;
  int numberOfStudentsInCourseByGroup;
  char currentGroupName;

  for (i = 0; i < numberOfSubGroups; i++) {
    numberOfStudentsInCourseByGroup = 0;
    currentGroupName = getGroupNameByIndex(i);
    for (j = 0; j < numberOfStudents; j++) {
      STUDENT currentStudent = groupOfGroupsOfStudents[i][j];
      for (k = 0; k < currentStudent.numberOfCoursesInSemesterA; k++) {
        if (currentStudent.courseInfo[k].courseNumber == courseNumber) {
          studentGrades[i][numberOfStudentsInCourseByGroup + 1] = currentStudent.courseInfo[k].grade;
          numberOfStudentsInCourseByGroup++;
        }
      }
    }
    studentGrades[i][0] = numberOfStudentsInCourseByGroup;
    printf("Group%c: ", currentGroupName);
    for (l = 0; l < numberOfStudentsInCourseByGroup; l++) {
      printf("%d ", studentGrades[i][l + 1]);
    }
    printf("\n");
  }
}

void searchMaximumGradePerGroup(int studentGrades[][MAXIMUM_OF_NUMBER_GRADES_IN_TABLE], int numberOfSubGroups) {
  int i, j;
  int firstMaximumGrade = -1, secondMaximumGrade = -1;
  int maximumNumberOfGradesInGroup;
  char currentGroupName;

  for (i = 0; i < numberOfSubGroups; i++) {
    currentGroupName = getGroupNameByIndex(i);
    firstMaximumGrade = -1;
    maximumNumberOfGradesInGroup = studentGrades[i][0];

    for (j = 1; j <= maximumNumberOfGradesInGroup; j++) {
      if (studentGrades[i][j] > firstMaximumGrade) {
        secondMaximumGrade = firstMaximumGrade;
        firstMaximumGrade = studentGrades[i][j];
      } else if (studentGrades[i][j] <= firstMaximumGrade && studentGrades[i][j] > secondMaximumGrade) {
        secondMaximumGrade = studentGrades[i][j];
      }
    }

    if (firstMaximumGrade != -1 && secondMaximumGrade != -1) {
      printf("Group%c: max grade is: %d and second max is: %d\n", currentGroupName, firstMaximumGrade,
             secondMaximumGrade);
    } else if (firstMaximumGrade != -1 && secondMaximumGrade == -1) {
      printf("Group%c: max grade is: %d (no second max found)\n", currentGroupName, firstMaximumGrade);
    } else {
      printf("Group%c: no grades found in group\n", currentGroupName);
    }
  }
}