#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    int sno;
    char name[8];
} Student;

#define MAX_STUDENTS 32
Student students[MAX_STUDENTS];
int studentNumber = 0;

void addStudent(int sno, char *name)
{
    // Student *student = &students[studentNumber];
    Student *student = students + studentNumber;name = E
name = F
name = G
>Exit code: 0
>./ex0
name = (null)
name = B
name = C
name = D
name = E
name = F
name = G
>Exit code: 0
>./ex0
name = (null)
name = B
name = C
name = D
name = E
name = F
name = G
>Exit code: 0
>./ex0
name = (null)
name = B
name = C
name = D
name = E
name = F
name = G
>Exit code: 0
>./ex0
name = (null)
name = B
name = C
name = D
name = E
name = F
name = G
>Exit code: 0
>./ex0
name = (null)
name = B
name = C
name = D
name = E
name = F
name = G
>Exit code: 0
>./ex0
name = (null)
name = B
name = C
name = D
name = E
name = F
name = G
>Exit code: 0
>./ex0
name = (null)
name = B
name = C
name = D
name = E
name = F
name = G
>Exit code: 0
    student->sno = sno;
    strcpy(student->name, name);
    studentNumber++;
}

void dumpStudent(Student *student)
{
    printf("sno = %d, name = %s\n", student->sno, student->name);
}

void dumpStudents()
{
    int i;

    for (i = 0; i < studentNumber; i++) {
        Student *student = students + i;
        dumpStudent(student);
    }
}

void createStudents()
{
    addStudent(1, "A");
    addStudent(2, "B");
    addStudent(3, "C");
    addStudent(4, "D");
    addStudent(5, "E");
    addStudent(6, "F");
    addStudent(7, "G");
}

char *linearSearch(int sno)
{
    int i;

    for (i = 0; i < studentNumber; i++) {
        Student *student = students + i;
        if (student->sno == sno)
            return student->name;
    } 

    return NULL;
}

void testLinearSearch()
{
    createStudents();

    char *name;
    name = linearSearch(3);
    printf("name = %s\n", name);
    name = linearSearch(5);
    printf("name = %s\n", name);
}

// [low, high)
char *binarySearch(int sno)
{
 //	int Search_Bin ( SSTable ST, Key key )
//	{
 //  low = 1;  high = ST.length;     // 置区间初值
 //  while (low <= high) {
 //     mid = (low + high) / 2;
 //     if  (key == ST.elem[mid].key) 
 //       return  mid;        // 找到待查元素
//     else  if (key < ST.elem[mid].key) 
//        high = mid - 1;       // 继续在前半区间进行查找
//      else  low = mid + 1; // 继续在后半区间进行查找
//   }
	int low = 1 , high = studentNumber;
	
	while (low <= high)
	{
		int mid=( low + high ) / 2;
		
		if (sno == students[mid + 1].sno )
			return students[mid].name;
		else 
			if(sno < students[mid].sno)
				high = mid -1;
			else
				low = mid + 1 ;
		
	}
	
	return 0;                 // 顺序表中不存在待查元素
} // Search_Bin   
	
void testBinarySearch()
{
    createStudents();

    for (int sno = 1; sno <= 7; sno++) {
        char *name;
        name = binarySearch(sno);
        printf("name = %s\n", name);
    }
}

int main()
{
    testBinarySearch();
    return 0;
}
