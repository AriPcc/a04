/******************************************************************************
# Author:            Ari P.
# Assignment:        Assignment 4
# Date:              10/19/25
# Description:       This program will get a list of course numbers and their
#                    student counts, sorted alphabetically, and then delete
#                    courses with less than 10 students enrolled
# Input:             courseNum (cstring), numStudents (int)
# Output:            courseNums[] (cstring), students[] (int)
# Sources:           Assignment 4 specifications, zyBooks reference
#*****************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

// Declare and initialize global constant variables
const int MAX_CHAR = 51;
const int MAX_COURSE = 20;
const int MAX_STUDENT = 25;

// Declare functions, which are defined after main()
void welcome();
void readInput(char courseNums[][MAX_CHAR], int students[], int &count);
void readNum(string prompt, char num[]);
int getPos(char courseNum[], char courseNums[][MAX_CHAR], int count);
bool isGreater(char course1[], char course2[]);
void insertCourse(char courseNum[], char courseNums[][MAX_CHAR], int count, \
int pos);
void readInt(string prompt, int &num);
void insertCourse(int numStudents, int students[], int count, int pos);
void printList(char courseNums[][MAX_CHAR], int students[], int count);
void cancelCourses(char courseNums[][MAX_CHAR], int students[], int &count);
void deleteCourse(char courseNums[][MAX_CHAR], int students[], int &count, \
int pos);
void goodbye();

int main() {
   char courseNums[MAX_COURSE][MAX_CHAR];
   int students[MAX_STUDENT];
   int count = 0;

   welcome();
   cout << endl;
   // Get list of course numbers and corresponding list of student counts
   readInput(courseNums, students, count);
   cout << endl;
   // Check if there's at least one course
   if (count > 0) {
      cout << "List of course numbers and student counts:" << endl;
      printList(courseNums, students, count);

      // Delete each course with less than 10 students
      cancelCourses(courseNums, students, count);
      cout << "List after cancellations:" << endl;
      printList(courseNums, students, count);
      cout << endl;
   }
   goodbye();
   return 0;
}

// Name:    welcome()
// Desc:    This function prints a welcome message
// input:   None
// output:  None
// return:  void
void welcome() {
   cout << "Welcome to the Course Roster program!" << endl;
}

// Name:    readInput()
// Desc:    This function reads the lists of course numbers and student counts
// input:   courseNum (cstring), numStudents (int)
// output:  prompt (string)
// return:  void
void readInput(char courseNums[][MAX_CHAR], int students[], int &count) {
   char courseNum[MAX_CHAR];
   int numStudents = 0;
   int pos = 0;

   cout << "Please enter up to 20 course numbers and their student counts \
(enter quit for course number to stop)." << endl;
   // Ensure no more than 20 courses can be entered
   while (count < MAX_COURSE && strcmp(courseNum, "Quit") != 0 && \
strcmp(courseNum, "quit") != 0) {
      readNum("Enter course number: ", courseNum);
      // Check if "Quit" or "quit" was entered
      if (strcmp(courseNum, "Quit") != 0 && strcmp(courseNum, "quit") != 0) {
         // Get alphabetical position within list
         pos = getPos(courseNum, courseNums, count);
         insertCourse(courseNum, courseNums, count, pos);

         readInt("Enter number of students: ", numStudents);
         insertCourse(numStudents, students, count, pos);
         count++;
      }
   }
}

// Name:    readNum()
// Desc:    This function reads a course number
// input:   num (cstring)
// output:  prompt (string)
// return:  void
void readNum(string prompt, char num[]) {
   cout << prompt;
   cin >> num;
   // Ensure course number is no more than 50 characters
   while (cin.fail() || strlen(num) > MAX_CHAR - 1) {
      cin.clear();
      cin.ignore(100, '\n');
      cout << "Invalid answer! Please try again." << endl;
      cout << prompt;
      cin >> num;
   }
}

// Name:    getPos()
// Desc:    This function determines the list position to insert a course
//          number into, in ascending alphabetical order
// input:   None
// output:  None
// return:  pos (int)
int getPos(char courseNum[], char courseNums[][MAX_CHAR], int count) {
   int pos = 0;
   // Check if there's at least one course number in the list
   if (count > 0) {
      // Increment pos until an alphabetically-later course number is found
      while ( pos < count && isGreater(courseNum, courseNums[pos]) ) {
         pos++;
      }
   }
  return pos;
}

// Name:    isGreater()
// Desc:    This function determines whether a course number is
//          alphabetically-later than another
// input:   None
// output:  None
// return:  greaterThan (bool)
bool isGreater(char course1[], char course2[]) {
   bool greaterThan = false;
   if (strcmp(course1, course2) > 0) {
      greaterThan = true;
   }
   return greaterThan;
}

// Name:    insertCourse()
// Desc:    This function adds a course number to the list in a given position
// input:   None
// output:  None
// return:  void
void insertCourse(char courseNum[], char courseNums[][MAX_CHAR], int count, \
int pos) {
   // Check if there's at least one course number in the list
   if (count == 0) {
      strcpy(courseNums[0], courseNum);
   }
   // Check if position to be inserted is after last item in list
   else if (pos == count) {
      strcpy(courseNums[count], courseNum);
   }
   else {
      for (int i = count; i > pos; i--) {
         strcpy(courseNums[i], courseNums[i - 1]);
      }
      strcpy(courseNums[pos], courseNum);
   }
}

// Name:    readInt()
// Desc:    This function reads the number of students for a course
// input:   num (int)
// output:  prompt (string)
// return:  void
void readInt(string prompt, int &num) {
   cout << prompt;
   cin >> num;
   // Ensure student count is between 0 and 25
   while (cin.fail() || num < 0 || num > MAX_STUDENT) {
      cin.clear();
      cin.ignore(100, '\n');
      cout << "Invalid answer! Please try again." << endl;
      cout << prompt;
      cin >> num;
   }
}

// Name:    insertCourse()
// Desc:    This overloaded function adds a student count to the list in a 
//          given position
// input:   None
// output:  None
// return:  void
void insertCourse(int numStudents, int students[], int count, int pos) {
   // Check if there's at least one student count in the list
   if (count == 0) {
      students[0] = numStudents;
   }
   // Check if position to be inserted is after last item in list
   else if (pos == count) {
      students[count] = numStudents;
   }
   else {
      for (int i = count; i > pos; i--) {
         students[i] = students[i - 1];
      }
      students[pos] = numStudents;
   }
}

// Name:    printList()
// Desc:    This function prints the lists of course numbers and student counts
// input:   None
// output:  courseNums[] (cstring), students[] (int)
// return:  void
void printList(char courseNums[][MAX_CHAR], int students[], int count) {
   // Declare variables for formatting output
   int max = 0;
   int width = 0;
   // Find length of largest course number
   for (int i = 0; i < count; i++) {
      if (strlen(courseNums[i]) > max) {
         max = strlen(courseNums[i]);
      }
   }
   width = max + 3;

   for (int i = 0; i < count; i++) {
      // Space output appropriately
      cout << setw(width) << left << courseNums[i] << " | ";
      cout << setw(2) << right << students[i] << endl;
   }
}

// Name:    cancelCourses()
// Desc:    This function deletes all courses with less than 10 students
// input:   None
// output:  None
// return:  void
void cancelCourses(char courseNums[][MAX_CHAR], int students[], int &count) {
   for (int i = 0; i < count; i++) {
      // Check if there's less than 10 students in course
      if (students[i] < 10) {
         deleteCourse(courseNums, students, count, i);
      }
   }
}

// Name:    deleteCourse()
// Desc:    This function deletes a course number from the list
// input:   None
// output:  None
// return:  void
void deleteCourse(char courseNums[][MAX_CHAR], int students[], int &count, \
int pos) {
   for (int i = pos; i < count - 1; i++) {
      strcpy(courseNums[i], courseNums[i + 1]);
      students[i] = students[i + 1];
   }
   count--;
   strcpy(courseNums[count], "");
   students[count] = 0;
}

// Name:    goodbye()
// Desc:    This function prints a goodbye message
// input:   None
// output:  None
// return:  void
void goodbye() {
   cout << "Thank you for using the Course Roster program." << endl;
}