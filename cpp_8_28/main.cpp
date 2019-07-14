/*GOAL: Practice writing and calling functions

*/

#include <iostream>
#include <stdio.h>
#include "main.h"

const int CLASS_SIZE = 6;

int main()
{
    Student studentsInClass[CLASS_SIZE];
    CourseEnrollment course1;

    static int studentNumber = 1000;
    int grade;
    // int userInput;

    //asign student id to each student
    for(int i = 0; i < CLASS_SIZE; i++)
    {
        studentsInClass[i].setStudentID(studentNumber);
        studentNumber++;
    }

    //for(int i = 0; i < CLASS_SIZE; i++)
    //{
    //    std::cout<<"student #"<<i<<" has studentID #"<<studentsInClass[i].getStudentID()<<"\n\n";
    //}

    //assign grades to all students
    for(int i = 0; i <CLASS_SIZE; i++)
    {
      for(int j = 0; j <10 ; j++)
        {
            scanf("%d", &grade);
            studentsInClass[i].setGrade(j,grade);
        }  
    }

    //print out all students grades
    for(int i = 0; i < CLASS_SIZE; i++)
    {
        studentsInClass[i].printGrades();
        std::cout<<"\nMin grade = "<<studentsInClass[i].getMin()<<"\n";
        std::cout<<"Max grade = "<<studentsInClass[i].getMax()<<"\n";
        std::cout<<"Grade Average = "<<studentsInClass[i].getAverageGrade()<<"\n\n";
    }

    course1.addStudents(studentsInClass);

    int *allGrades;
    allGrades = course1.getAllGrades();
    allGrades = course1.sortAllGrades();
    std::cout<<"ALLGRADES\n";
    std::cout<<"Lowest grade for entire course = "<<course1.getMinGrade()<<"\n";
    std::cout<<"Highest grade for entire course = "<<course1.getMaxGrade()<<"\n";
    std::cout<<"Avg grade for entire course = "<<course1.getAvgGrade()<<"\n";
    return 0;
}