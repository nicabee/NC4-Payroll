#include <stdio.h>
#include <conio.h>
#include <string.h>
#include<stdlib.h>
#define SIZE 5
const char *DayNames[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

struct time   
{  
    char weekDay[10]; 
    char timeIn[10];
    char timeOut[10];
    int isHoliday;
    char timeInOT[10];
    char timeOutOT[10];
};
struct employee  
{  
    char employeeCode[20];  
    struct time information[SIZE];  
    char dateCovered[20];
}; 

struct employeeRec{
        char employeeCode[20];
        char employeename[50];
        int salaryLevel;
};
void getEmployeeInfo(struct employeeRec emp);
void writeToDTR(char employeeCode[]);
void readFromDTR(char employeeCode[]);
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
                            	printf("Salary Rate: Php %.2f /day\n", salaryRate);
							}else if (emp.salaryLevel == 2){
								salaryRate = 450.00;
								printf("Salary Rate: Php %.2f /day\n", salaryRate);
							}else if (emp.salaryLevel == 3){
								salaryRate = 550.00;
								printf("Salary Rate: Php %.2f /day\n", salaryRate);
							}
							
							//writeToDTR(emp.employeeCode);
							readFromDTR(emp.employeeCode);
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

void writeToDTR(char employeeCode[]){
	struct employee emp;  
    FILE *fp;
    int j,ans;
    char res;
    char scode[10];
    
    strcpy(emp.employeeCode,employeeCode);
    fp=fopen("dtr.txt","ab");
    for(j=0;j<SIZE;j++){
    	strcpy(emp.information[j].weekDay, DayNames[j]);
    	printf("Enter Time in for %s\n",DayNames[j]);
    	scanf("%s",emp.information[j].timeIn);
    	fflush(stdin);
    	printf("Enter Time Out for %s\n",DayNames[j]);
    	scanf ("%[^\n]%*c", emp.information[j].timeOut);
    	fflush(stdin);
    	printf("Is %s a holiday? Y/N \n", DayNames[j]);
    	scanf("%c", &res);
    	ans = (res=='Y' || res == 'y')? 1 : 0;
    	emp.information[j].isHoliday = ans;
    	printf("Enter the overtime-in for %s\n", DayNames[j]);
    	scanf ("%s", emp.information[j].timeInOT);
    	fflush(stdin);
    	printf("Enter the overtime-out for %s\n", DayNames[j]);
    	scanf ("%[^\n]%*c", emp.information[j].timeOutOT);
    	fflush(stdin);
	}
	printf("Enter the coverage date of this payroll: (Ex. June 1-5, 2021)\n");
	scanf ("%[^\n]%*c", emp.dateCovered);
    fflush(stdin);
    fwrite(&emp,sizeof(emp),1,fp);
    fclose(fp);
}

void readFromDTR(char employeeCode[]){
	struct employee emp;
	FILE* fp;
	fp=fopen("dtr.txt","rb");
	int x;
	char day[5];
    while(fread(&emp,sizeof(emp),1,fp))
    {
    	if(strcmp(employeeCode,emp.employeeCode)==0){
    		for(x=0;x<SIZE;x++){
    			printf("\t====================\t\t\n");
    			printf("\t\t%s\t\t\n", emp.information[x].weekDay);
    			(emp.information[x].isHoliday == 1)?strcpy(day,"Holiday") : strcpy(day,"Regular");
    			printf("\t\t%s\t\t\n",day);
    			printf("Time In for %s: %s\n", emp.information[x].weekDay, emp.information[x].timeIn);
    			printf("Time Out for %s: %s\n", emp.information[x].weekDay, emp.information[x].timeOut);
    			if(strcmp(emp.information[x].timeInOT, "00:00") != 0 && strcmp(emp.information[x].timeOutOT, "00:00") != 0){
    				printf("Overtime-in for %s: %s\n", emp.information[x].weekDay, emp.information[x].timeInOT);
    				printf("Overtime-out for %s: %s\n", emp.information[x].weekDay, emp.information[x].timeOutOT);
				}
    			
    			printf("\t====================\t\n");
			}
    		printf("Coverage Date: %s\t\t\n", emp.dateCovered);
		}
    }
    fclose(fp);
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


