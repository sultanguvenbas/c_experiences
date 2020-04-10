#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{

    int employee_id;
    char employee_name[20];
    char employee_department[20];
    int birth_year;
    int salary;

} employeeData;

void menu(void);
void convertTextFile(FILE *fPtr);
void addRecord(FILE *fPtr);
void deleteRecord(FILE *fPtr);
void updateRecord(FILE *fPtr);
void showRecords(FILE *fPtr);

void showRecords(FILE *fPtr)
{
    employeeData emp[100];
    printf("%-5s %-20s %-20s %-15s %-10s\n","ID No","Employee Name","Department","Birth Year","Salary");
    for (int i = 0; i < 100; i++)
    {
        fread(&emp[i], sizeof(emp[i]), 1, fPtr);
        if(emp[i].employee_id !=0 ) 
        printf("%-5d %-20s %-20s %-15d %-10d\n", emp[i].employee_id, emp[i].employee_name, emp[i].employee_department, emp[i].birth_year, emp[i].salary);
    }
}

void convertTextFile(FILE *fPtr){
  employeeData emp[100];
  
  FILE *file;
  file=fopen("employee.txt","w");

  fprintf(file,"%-5s %-20s %-20s %-15s %-10s\n","ID No","Employee Name","Department","Birth Year","Salary");
  for (int i = 0; i < 100; i++)
    {
        fread(&emp[i], sizeof(emp[i]), 1, fPtr);
        if(emp[i].employee_id !=0 ) 
        fprintf(file,"%-5d %-20s %-20s %-15d %-10d\n", emp[i].employee_id, emp[i].employee_name, emp[i].employee_department, emp[i].birth_year, emp[i].salary);
    } 
  fclose(file);
  printf("employee.txt file is ready!\n");
}

void updateRecord(FILE *fPtr){
  employeeData emp;
  int id, percentage, new_salary;

  printf("Enter id to update amount of employee : ");
  scanf("%d",&id);
  
  
  if(id>0 && id<101){
   
    printf("%-5s %-20s %-20s %-15s %-10s\n","ID No","Employee Name","Department","Birth Year","Salary");
    fseek(fPtr,sizeof(emp)*(id-1),SEEK_SET);
    fread(&emp, sizeof(emp), 1, fPtr);

    if(emp.employee_id==0){
      printf("There is no record!!!!\n");
      updateRecord(fPtr);
    }
    
    printf("%-5d %-20s %-20s %-15d %-10d\n", emp.employee_id, emp.employee_name, emp.employee_department, emp.birth_year, emp.salary);

    printf("Enter the percentage of increase for salary :");
    scanf("%d",&percentage);

    fseek(fPtr, -sizeof(int), SEEK_CUR);

    int newSalary=emp.salary+(emp.salary*percentage)/100.0;
    emp.salary=newSalary;
    fwrite(&newSalary, sizeof(newSalary), 1, fPtr);

    printf("%-5s %-20s %-20s %-15s %-10s\n","ID No","Employee Name","Department","Birth Year","Salary");
    printf("%-5d %-20s %-20s %-15d %-10d\n", emp.employee_id, emp.employee_name, emp.employee_department, emp.birth_year, emp.salary);


  }
  else{
    printf("Please enter availabile id!!!\n");
  }
 
}
void addRecord(FILE *fPtr){
  employeeData emp;
  int id;

  printf("Enter id to create new employee record: ");
  scanf("%d",&id);

  fseek(fPtr,sizeof(emp)*(id-1),SEEK_SET);
  fread(&emp, sizeof(emp), 1, fPtr);
  if(emp.employee_id!=0){
    printf("This id is already exist!Try again\n\n");
    addRecord(fPtr);
  }
  else{
    emp.employee_id=id;
    printf("Employee Name :");
    scanf("%s",emp.employee_name);
    printf("Department :");
    scanf("%s",emp.employee_department);
    printf("Birth Year :");
    scanf("%d",&emp.birth_year);
    printf("Salary :\n");
    scanf("%d",&emp.salary);

    fseek(fPtr,sizeof(emp)*(id-1),SEEK_SET);
    fwrite(&emp,sizeof(emp),1,fPtr);

    printf("Employee with id #%d is recorded ",id);
  }

}
void deleteRecord(FILE *fPtr){
  employeeData emp;
  int id;

  printf("Enter id to remove employee record :");
  scanf("%d",&id);

  emp.employee_id=id;
  if(emp.employee_id==0){
    printf("There is no record with #%d ",emp.employee_id);
  }
  else{
    fseek(fPtr,sizeof(emp)*(id-1),SEEK_SET);
    memset(&emp,0,sizeof(emp));
    fwrite(&emp,sizeof(emp),1,fPtr);

    printf("Employee record with id #%d is removed\n",id);
    
  }

}



void menu(void)
{

    FILE *fPtr;
    int number;
    fPtr = fopen("employee.bin", "rb+");

    puts("EMPLOYEE RECORD SYSTEM\n1-Add new record\n2-Uptades record\n3-Delete record\n4-Print all records\n5-Save as txt file\n6-End program\n\nENTER A CHOICE => ");
    scanf("%d", &number);

    switch (number){
        
        case 1:
          addRecord(fPtr);
            break;
        case 2:
          updateRecord(fPtr);
            break;
        case 3:
          deleteRecord(fPtr);
            break;
        case 4:
            showRecords(fPtr);
            break;
        case 5:
            convertTextFile(fPtr);
            break;
        case 6:
          exit(0);

        default:
            break;
    }
    fclose(fPtr);
    printf("\n*************************************************\n");
}

int main(void)
{

   
    while (1)
    {
        menu();
    }
    return 0;
}
