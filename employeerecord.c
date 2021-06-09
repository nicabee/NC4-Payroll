#include <stdio.h>
#include <conio.h>
#include <string.h>
#include<stdlib.h>


struct employeeRec{
        char employeeCode[20];
        char employeename[50];
        int salaryLevel;
};
void getEmployeeInfo(struct employeeRec emp);

int main()
{
 	struct employeeRec emp;
	printf("\nWelcome to NC4 Payroll System\n");
	getEmployeeInfo(emp);
		

}

void getEmployeeInfo(struct employeeRec emp){
	int choice,ch,c,flag=0;
	FILE *fp;
	char scode[20];
	float salaryRate;
	do 
		{
		 printf("\nEmployee Info\n");
		 printf("\nMenu\n");
		 printf("1. Add a new employee record. \n");
		 printf("2. Search for a certain employee. \n");
		 printf("3. Exit \n");
		 scanf("%d",&choice);
		  
		 switch (choice)
		 {
		     case 1: 
		      	 fp=fopen("employee.txt","a");
		      	 	system("cls");
                    printf("Enter the Employee Code:\n");
                    scanf("%s",emp.employeeCode);
                    fflush(stdin);
                    printf("Enter the Employee Name\n");
                    scanf ("%[^\n]%*c", emp.employeename);
                    fflush(stdin);
                    printf("Enter the Salary Level:\n");
                    scanf("%d", &emp.salaryLevel);
                    fwrite(&emp,sizeof(emp),1,fp);
                    fflush(stdin);
//                    printf("Enter the Salary Rate:\n");
//                    scanf("%d", &emp.salaryRate);
//                    printf("%d", emp.salaryRate);
                    fwrite(&emp,sizeof(emp),1,fp);
                    fflush(stdin);
                    fclose(fp);
                    getch();
                    system("cls");
                    break;
		     case 2:
		     		fp=fopen("employee.txt","r");
					system("cls");
                    printf("Enter the Employee Code\n");
                    scanf("%s",scode);
                    while(fread(&emp,sizeof(emp),1,fp))
                    {
                        if(strcmp(scode,emp.employeeCode)==0)
                        {
                            printf("Employee Name: %s\n",emp.employeeCode);
                            printf("Employee Code: %s\n",emp.employeename);
                            printf("Salary Level: %d\n",emp.salaryLevel);
                            if(emp.salaryLevel == 1){
                            	salaryRate = 380.00;
                            	printf("Salary Rate: Php %.2f /day", salaryRate);
							}else if (emp.salaryLevel == 2){
								salaryRate = 450.00;
								printf("Salary Rate: Php %.2f /day", salaryRate);
							}else if (emp.salaryLevel == 3){
								salaryRate = 550.00;
								printf("Salary Rate: Php %.2f /day", salaryRate);
							}
                            getch();
                            flag = 1;
                            break;
                        }
                    }
                    (flag==1)?printf("") : printf("Employee not found!\n");
                    fclose(fp);
                    getch();
                    system("cls");
                    break;
		     case 3: 
				printf("Goodbye!\n"); 
		        break;
		     default: 
			 	printf("Wrong Choice. Enter again\n");
			 	getch();
		      	system("cls");
		        break;
		 } 
		} while (choice != 3);

}


