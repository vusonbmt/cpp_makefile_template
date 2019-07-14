
//main.h 


class Student
{
    public:
    int studentID;
    int grades[10];

    void setStudentID(int inID)
    {
        studentID = inID;
    }

    int getStudentID()
    {
        return studentID;
    }

    void setGrade(int gradeNumber, int gradeIn)
    {
        grades[gradeNumber] = gradeIn;
    }

    int * getGrades()
    {
        return grades;
    }

    int getGrade(int gradeNumber)
    {
        return grades[gradeNumber];
    }

    void printGrades()
    {
        std::cout<<"StudentID = "<<studentID<<"\n";
        for(int i = 0; i < 10; i++)
        {
            std::cout<<"\t"<<grades[i]<<"\n";
        }
    }


    int sortGrades()
    {
    //sort ascending
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 9 - i; j++)
            {
                if(grades[j] > grades[j + 1])
                {
                    int temp;
                    temp=grades[j];
                    grades[j]=grades[j + 1];
                    grades[j + 1]=temp;
                }
            }
    }
    }
    int getMin()
    {
        sortGrades();
        //std::cout<<"in class min"<<grades[0];
        return grades[9];
    }

    int getMax()
    {
        sortGrades();
        //std::cout<<"in class max"<<grades[9];
        return grades[0];
    }

    float getAverageGrade()
    {
        float sum = 0;
        for(int i = 0; i<10; i++)
        {
            sum = sum + grades[i];
        }
        return sum/10;
    }
};

//********************
class CourseEnrollment
{
    public:
    Student students[6];
    int courseMinGrade;
    int courseMaxGrade;
    float courseAvgGrade;
    int grades[60];

    void addStudents(Student* studentIn)
    {
        for(int i = 0;i<6;i++)
        {
            students[i] = studentIn[i];
        }
    }

    int * getAllGrades()
    {
        //int grades[60];
        int k = 0;
        for(int i = 0; i<6;i++)
        {
            for(int j = 0; j<10;j++)
            {
                grades[k] = students[i].getGrade(j);
                k = k + 1;
            }
        }
        return grades;
    }

    int * sortAllGrades()
    {
        for(int i = 0; i < 60; i++)
        {
            for(int j = 0; j < 59 - i; j++)
            {
                if(grades[j] > grades[j + 1])
                {
                    int temp;
                    temp=grades[j];
                    grades[j]=grades[j + 1];
                    grades[j + 1]=temp;
                }
            }
        }
        return grades;
    }


    int getMinGrade()
    {
        sortAllGrades();
        return grades[0];
    }
    int getMaxGrade()
    {
        sortAllGrades();
        return grades[59]; 
    }

    float getAvgGrade()
    {
        int sum = 0;
        for(int i=0;i<60;i++)
        {
            sum = sum + grades[i];
        }
        return sum/60;
    }

    void printAllGrades()
    {
        for(int i=0;i<60;i++)
        {
            std::cout<<"grade="<<grades[i]<<"\n";
        }
    }


};