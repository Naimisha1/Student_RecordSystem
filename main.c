#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int roll;
    char name[50];
    float marks;
};

void addStudent()
{
    struct Student s;
    FILE *f = fopen("students.dat","ab");
    printf("Enter Roll No: ");
    scanf("%d",&s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]",s.name);
    printf("Enter Marks: ");
    scanf("%f",&s.marks);
    fwrite(&s,sizeof(s),1,f);
    fclose(f);
    printf("Student added successfully.\n");
}

void displayStudents()
{
    struct Student s;
    FILE *f=fopen("students.dat", "rb");
    printf("\nAll Student Records:\n");
    while(fread(&s,sizeof(s),1,f))
    {
        printf("Roll: %d | Name: %s | Marks: %.2f\n",s.roll,s.name,s.marks);
    }
    fclose(f);
}

void searchStudent()
{
    struct Student s;
    int roll,found=0;
    FILE *f=fopen("students.dat","rb");
    printf("Enter Roll No to search: ");
    scanf("%d",&roll);
    while(fread(&s,sizeof(s),1,f))
        {
        if(s.roll==roll)
        {
            printf("Found: %s with %.2f marks\n",s.name,s.marks);
            found=1;
            break;
        }
    }
    if(!found) printf("Student not found.\n");
    fclose(f);
}

void deleteStudent()
{
    struct Student s;
    int roll;
    FILE *f=fopen("students.dat", "rb");
    FILE *temp=fopen("temp.dat", "wb");
    printf("Enter Roll No to delete: ");
    scanf("%d",&roll);
    while(fread(&s,sizeof(s),1,f))
    {
        if(s.roll!=roll)
            fwrite(&s,sizeof(s),1,temp);
    }
    fclose(f);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat","students.dat");
    printf("Student deleted (if existed).\n");
}
void updateStudent()
{
    struct Student s;
    int roll,found=0;
    FILE *f =fopen("students.dat","rb+");
    printf("Enter Roll No to update: ");
    scanf("%d",&roll);
    while(fread(&s,sizeof(s),1,f))
        {
        if(s.roll==roll)
        {
            printf("Enter new name: ");
            scanf(" %[^\n]",s.name);
            printf("Enter new marks: ");
            scanf("%f", &s.marks);
            fseek(f,-(long)sizeof(s),SEEK_CUR);
            fwrite(&s,sizeof(s),1,f);
            found=1;
            printf("Record updated.\n");
            break;
        }
    }
    if(!found) printf("Student not found.\n");
    fclose(f);
}

int main()
{
    int choice;
    do
    {
        printf("\n--- Student Record System ---\n");
        printf("1. Add\n2. Display\n3. Search\n4. Update\n5. Delete\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1: addStudent();
            break;
            case 2: displayStudents();
            break;
            case 3: searchStudent();
            break;
            case 4: updateStudent();
            break;
            case 5: deleteStudent();
            break;
            case 6: printf("Exiting...\n");
            break;
            default: printf("Invalid choice.\n");
        }
    }
    while(choice!=6);
    return 0;
}
