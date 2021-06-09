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
char* convertToUpperCase(char arr[]);


int main()
{
 	struct employeeRec emp;
	printf("\nWelcome to NC4 Payroll System\n");
	getEmployeeInfo(emp);
		

}

void getEmployeeInfo(struct employeeRec emp){
	int choice,ch,c,flag=0;
	FILE *fp;
	char* searchCode;
	char scode[20];
	float salaryRate;
	
	char s[100] = "a01-0001";
   int i;
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
		      	 fp=fopen("employee.txt","ab");
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
                    fclose(fp);
                    getch();
                    system("cls");
                    break;
		     case 2:
		     		fp=fopen("employee.txt","rb");
					system("cls");
                    printf("Enter the Employee Code\n");
                    scanf("%s",scode);
                    searchCode=convertToUpperCase(scode);
                    while(fread(&emp,sizeof(emp),1,fp))
                    {
                        if(strcmp(searchCode,emp.employeeCode)==0)
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
                            break;
                        }
                    }
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

char* convertToUpperCase(char arr[]){
	char *retString = malloc (sizeof (char) * 256);
	int i;
	for (i = 0; arr[i]!='\0'; i++) {
		
      if(arr[i] >= 'a' && arr[i] <= 'z') {
         retString[i] = arr[i] -32;
      }else{
      	retString[i] = arr[i];
	  }
      
   }
   retString[i]='\0';
   return retString;
}


