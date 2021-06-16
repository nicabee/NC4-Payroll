/* Final Requirement for NC4 by Barrientos, Monica B.*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include<stdlib.h>
#include<time.h>
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
    char recordGenerated[50];
}; 

struct employeeRec{
    char employeeCode[20];
    char employeename[50];
    int salaryLevel;
};
/* Basic Input functions */
void getEmployeeInfo(struct employeeRec emp);
/* File handling functions */
void writeToDTR(char employeeCode[]);
void readFromDTR(char employeeCode[], float salaryRate);
/* Conversion functions */
char* convertToUpperCase(char arr[]);
int stringtoInt(char arr[]);
/* Working hours calculation functions */
float getTotalHours(char timeIn[], char timeOut[]);
float getOverTime(char timeIn[], char timeOut[]);
float getSalaryRate(char employeeCode[]);
/* Income calculation functions */
float getRegularIncome(float totalWorkHours, float salaryRate);
float getOvertimeIncome(float totalOThrs, float salaryRate);
float getHolidayIncome(float totalHolidayhrs, float salaryRate);
/* Deduction calculation functions */
float getSSS(float grossIncome, float salaryRate);
float getTax(float grossIncome);
/* Error Trapping Functions */
int checkTimeInput(char arr[]);

int main()
{
 	struct employeeRec emp;
	printf("\nWelcome to NC4 Payroll System by Monica B. Barrientos\n");
	getEmployeeInfo(emp);

}

void getEmployeeInfo(struct employeeRec emp){
	int choice,ch,c,flag=0, i;
	FILE *fp;
	char* searchCode;
	char* retecode;
	char scode[20], employeecode[20], ecode[20];
	float salaryRate, sRate;
	do 
		{
		 printf("\nEmployee Info\n");
		 printf("\nMenu\n");
		 printf("1. Add a new employee information. \n");
		 printf("2. Display employee information. \n");
		 printf("3. Add employee's time-in and time-out. \n");
		 printf("4. Display Breakdown of Income (Test Case # 3) \n");
		 printf("5. Exit \n");
		 scanf("%d",&choice);
		  
		 switch (choice)
		 {
		     case 1: 
		      	 fp=fopen("employee.txt","ab");
		      	 if(fp!=NULL){
		      	 	system("cls");
                    printf("Enter the Employee Code:\n");
                    scanf("%s", ecode);
                    fflush(stdin);
                    retecode=convertToUpperCase(ecode);
                    strcpy(emp.employeeCode,retecode);
                    printf("Enter the Employee Name\n");
                    scanf ("%[^\n]%*c", emp.employeename);
                    fflush(stdin);
                    printf("Enter the Salary Level:\n");
                    scanf("%d", &emp.salaryLevel);
                    fwrite(&emp,sizeof(emp),1,fp);
                    fflush(stdin);		      	 	
				}else{
					printf("Unable to open file.\n");
				}
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
                    if(fp!=NULL){
                    	while(fread(&emp,sizeof(emp),1,fp))
	                    {
	                        if(strcmp(searchCode,emp.employeeCode)==0)
	                        {
	                        	flag = 1;
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
	                            break;
	                        }
	                    }
					}else{
						printf("File not found!\n");
					}
	                    
                    if(flag==0){
                    	printf("User not found!\n");
					}
					flag=0;
                    fclose(fp);
                    getch();
                    system("cls");
                    break;
		    	case 3:
		     		fp=fopen("employee.txt","rb");
					system("cls");
                    printf("Enter the Employee Code\n");
                    scanf("%s",scode);
                    searchCode=convertToUpperCase(scode);
                    if(fp!=NULL){
                    	while(fread(&emp,sizeof(emp),1,fp))
	                    {
	                        if(strcmp(searchCode,emp.employeeCode)==0)
	                        {
	                        	flag = 1;
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
								writeToDTR(emp.employeeCode);
	                            break;
	                        }
	                    }
					}else{
						printf("File not found!\n");
					}
                    if(flag==0){
                    	printf("User not found!\n");
					}
					flag=0;
                    fclose(fp);
                    getch();
                    system("cls");
                    break;
		     	case 4:
					 printf("Enter employee code to be Checked:\n");
					 scanf("%s",employeecode);
		             fflush(stdin);
		             searchCode=convertToUpperCase(employeecode);
		             sRate =  getSalaryRate(searchCode);
				     readFromDTR(searchCode, sRate);
				     getch();
					 system("cls");
				     break;
		     	case 5:
			    	printf("Goodbye!\n"); 
			        break;
		     	default: 
			 		printf("Wrong Choice. Enter again\n");
			 		getch();
		      		system("cls");
		        	break;
		 } 
		} while (choice != 5);

}

void writeToDTR(char employeeCode[]){
	struct employee emp;  
    FILE *fp;
    int j,ans;
    char res;
    char scode[10];
    int a;
    time_t t;   
    time(&t);
    
    strcpy(emp.employeeCode,employeeCode);
    fp=fopen("dtr.txt","ab");
    for(j=0;j<SIZE;j++){
		strcpy(emp.information[j].weekDay, DayNames[j]);
    	do{
	    	printf("Enter Time in for %s\n",DayNames[j]);
	    	scanf("%s",emp.information[j].timeIn);
	    	fflush(stdin);
			a = checkTimeInput(emp.information[j].timeIn);
		}while(a==0);
		do{
			printf("Enter Time Out for %s\n",DayNames[j]);
    		scanf ("%[^\n]%*c", emp.information[j].timeOut);
    		fflush(stdin);
    		a = checkTimeInput(emp.information[j].timeOut);
		}while(a==0);
    	printf("Is %s a holiday? Y/N \n", DayNames[j]);
    	scanf("%c", &res);
    	ans = (res=='Y' || res == 'y')? 1 : 0;
    	emp.information[j].isHoliday = ans;
    	
    	do{
    	    printf("Enter the overtime-in for %s\n", DayNames[j]);
	    	scanf ("%s", emp.information[j].timeInOT);
	    	fflush(stdin);	
	    	a = checkTimeInput(emp.information[j].timeInOT);
		}while(a==0);
		do{
			printf("Enter the overtime-out for %s\n", DayNames[j]);
	    	scanf ("%[^\n]%*c", emp.information[j].timeOutOT);
	    	fflush(stdin);
	    	a = checkTimeInput(emp.information[j].timeOutOT);
		}while(a==0);
	}
	printf("Enter the coverage date of this payroll: (Ex. June 1-5, 2021)\n");
	scanf ("%[^\n]%*c", emp.dateCovered);
    fflush(stdin);
    strcpy(emp.recordGenerated,ctime(&t));
    fwrite(&emp,sizeof(emp),1,fp);
    fclose(fp);
}

float getSalaryRate(char employeeCode[]){
	struct employeeRec emp;  
    FILE *fp;
    float salaryRate;
    fp=fopen("employee.txt","rb");
    if(fp!=NULL){
     	while(fread(&emp,sizeof(emp),1,fp))
	    {
	    	if(strcmp(employeeCode,emp.employeeCode)==0){
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
	        }
	    }   	
	}else{
		printf("Unable to open file for salary rate!\n");
	}

    return salaryRate;
}
void readFromDTR(char employeeCode[], float salaryRate){
	struct employee emp;
	FILE* fp;
	fp=fopen("dtr.txt","rb");
	int x, flag=0;
	char day[5];
	float TotalHours = 0, retHrs = 0, totalOvertime=0, totalHoliday=0, retOThrs=0, regularInc, OTInc, holidayInc, sss, tax, grossIncome;
	if(fp!=NULL){
		
	
	    while(fread(&emp,sizeof(emp),1,fp))
	    {
	    	if(strcmp(employeeCode,emp.employeeCode)==0){
	    		flag = 1;
	    		for(x=0;x<SIZE;x++){
	    			printf("\t====================\t\t\n");
	    			printf("\t\t%s\t\t\n", emp.information[x].weekDay);
	    			(emp.information[x].isHoliday == 1)?strcpy(day,"Holiday") : strcpy(day,"Regular");
	    			printf("\t\t%s\t\t\n",day);
	    			printf("Time In for %s: %s\n", emp.information[x].weekDay, emp.information[x].timeIn);
	    			printf("Time Out for %s: %s\n", emp.information[x].weekDay, emp.information[x].timeOut);
	    			retHrs = getTotalHours(emp.information[x].timeIn, emp.information[x].timeOut);
	    			if(emp.information[x].isHoliday == 0){
	    				
	    				TotalHours+=retHrs;
					}else{
						totalHoliday+=retHrs;
					}
	    			
	    			if(strcmp(emp.information[x].timeInOT, "00:00") != 0 && strcmp(emp.information[x].timeOutOT, "00:00") != 0){
	    				printf("Overtime-in for %s: %s\n", emp.information[x].weekDay, emp.information[x].timeInOT);
	    				printf("Overtime-out for %s: %s\n", emp.information[x].weekDay, emp.information[x].timeOutOT);
	    				retOThrs = getOverTime(emp.information[x].timeInOT,emp.information[x].timeOutOT);
	    				totalOvertime+=retOThrs;
					}
	    			
	    			printf("\t====================\t\n");
				}
	    		printf("Coverage Date: %s\t\t\n", emp.dateCovered);
	    		printf("This record was made on: %s\t\t\n", emp.recordGenerated);
			}
	    }
	}else{
		printf("Unable to open dtr.txt file!\n");
	}
    if(flag == 1){
    	//Work hours
    	printf("Total Number of Work Hours: %.0f\n",TotalHours);
    	printf("Total Number of Holiday Work Hours: %.0f\n",totalHoliday);
    	printf("Overtime Hours: %.0f\n",totalOvertime);
    	
    	//Income
    	regularInc = getRegularIncome(TotalHours, salaryRate);
    	printf("Regular Income: Php %.2f\n",regularInc);
    	holidayInc = getHolidayIncome(totalHoliday, salaryRate);
    	printf("Holiday Income: Php %.2f\n",holidayInc);
    	OTInc = getOvertimeIncome(totalOvertime, salaryRate);
    	printf("Overtime Income: Php %.2f\n",OTInc);
		grossIncome = OTInc + regularInc + holidayInc;
    	printf("Gross Income: Php %.2f\n", grossIncome);
    	
    	//Deductions
    	tax = getTax(grossIncome);
    	printf("*Tax: Php %.2f\n", tax);
    	sss = getSSS(grossIncome, salaryRate);
    	printf("*SSS: Php %.2f\n", sss);
    	
    	//Net Income
    	printf("Net Income: Php %.2f\n", (grossIncome - (tax + sss)) + 500); /* Weekly Net Salary Income = (WGSI - (tax + GSIS)) + allowance*/
	}else{
		printf("Time In and Time Out Details not found!\n");
	}

    fclose(fp);
}
int stringtoInt(char arr[]){
	int d,g;
    char *e;
    char *f;
	int retVal;
    d = strtol(arr, &e, 10);
    if( *e == ':' ){
        d *= 100;
        d += strtol(e + 1, &e, 10);
    }
    retVal = d;
    return retVal;
}


float getRegularIncome(float totalWorkHours, float salaryRate){
	float regIncome = 0;
	
	if (totalWorkHours > 0){
		salaryRate/=8;
		regIncome=salaryRate*totalWorkHours;
	}
	return regIncome;
}

float getHolidayIncome(float totalHolidayhrs, float salaryRate){
	float HolidayIncome = 0;

	if(totalHolidayhrs > 0){
		salaryRate/=8;
		salaryRate*=1.1;
		HolidayIncome = totalHolidayhrs * salaryRate;
	}
	return HolidayIncome;
}

float getOvertimeIncome(float totalOThrs, float salaryRate){
	float OtIncome = 0;
	
	if (totalOThrs > 0){
		salaryRate/=8;
		salaryRate*=1.1;
		OtIncome=totalOThrs * salaryRate;
	}
	return OtIncome;
}

float getTax(float grossIncome){
	float tax = 0, rate;
	
	if(grossIncome > 0){
		tax = grossIncome * 0.1;
	}
	return tax;
}

float getSSS(float grossIncome, float salaryRate){
	float sss = 0, rate;
	
	if(grossIncome > 0){
		if(salaryRate == 380.00){
			rate = 0.01;
		}else if (salaryRate == 450){
			rate = 0.015;
		}else{
			rate = 0.02;
		}
		
		sss = grossIncome * rate;
	}
	return sss;
}
float getTotalHours(char timeIn[], char timeOut[]){
	float returnHrs; 
	int timeInInt, timeOutInt, diff;
	float lateval, vals, hrs;
	timeInInt = stringtoInt(timeIn);
	timeOutInt = stringtoInt(timeOut);
	
	int out, in, in1, in2;
	int outMod, inMod, in1Mod, in2Mod;
	
	if(timeInInt == 800){
		if(timeOutInt >= 1700){
			//printf("Regular Work Hours\n");
			returnHrs = 8;
		}else if (timeOutInt < 1700){
			//printf("Started on time but ended early\n");
			out = timeOutInt/100; //hr for out
			in = timeInInt/100; //hr for in
			vals = out - in;
			outMod = timeOutInt%100; //mins for out
			inMod = timeInInt%100; //mins for in
			if(outMod < inMod){
				diff = outMod - inMod;
				diff += 60;
				vals--;
				returnHrs = vals + diff/100.0 - 1;
			}else if (outMod > inMod){
				diff = outMod - inMod;
				returnHrs = vals + diff/100.0 - 1;
			}else{
				returnHrs = vals;
			}	
		}
		
	}else if (timeInInt > 800){ //late
	
		if(timeInInt < 1200 && timeOutInt >= 1700){ // late before lunch and ends on time
			//printf("Late but ended on time 2\n");
			out = 1700/100;
			in = timeInInt/100;
			vals = out - in;
			outMod = 1700%100;
			inMod = timeInInt%100;
			vals--; // minus 1 hour for lunch break
			if(outMod < inMod){
				diff = outMod - inMod;
				diff += 60;
				vals--;
				returnHrs = vals + diff/100.0;
			}else if (outMod > inMod){
				diff = outMod - inMod;
				returnHrs = vals + diff/100.0;
			}else{
				returnHrs = vals;
			}
		}
		else if(timeOutInt >= 1700){ //late and finishes at 17:00 or more but not OT
			//printf("Late but ended on time\n");
			out = 1700/100;
			in = timeInInt/100;
			vals = out - in;
			outMod = 1700%100;
			inMod = timeInInt%100;
			if(outMod < inMod){
				diff = outMod - inMod;
				diff += 60;
				vals--;
				returnHrs = vals + diff/100.0;
			}else if (outMod > inMod){
				diff = outMod - inMod;
				returnHrs = vals + diff/100.0;
			}else{
				returnHrs = vals;
			}					
		}else if (timeInInt < 1200 && timeOutInt < 1700){ //late before lunch time and ended early
			//printf("Late b4 lunch and ended early\n");
			out = timeOutInt/100; //hr for out
			in = timeInInt/100; //hr for in
			vals = out - in;
			outMod = timeOutInt%100; //mins for out
			inMod = timeInInt%100; //mins for in
			vals--;
			if(outMod < inMod){
				diff = outMod - inMod;
				diff += 60;
				vals--;
				returnHrs = vals + diff/100.0;
			}else if (outMod > inMod){
				diff = outMod - inMod;
				returnHrs = vals + diff/100.0;
			}else{
				returnHrs = vals;
			}
		}
		else if (timeOutInt < 1700){ //late and undertime
			//printf("Late and ended early\n");
			out = timeOutInt/100; //hr for out
			in = timeInInt/100; //hr for in
			vals = out - in;
			outMod = timeOutInt%100; //mins for out
			inMod = timeInInt%100; //mins for in
			if(outMod < inMod){
				diff = outMod - inMod;
				diff += 60;
				vals--;
				returnHrs = vals + diff/100.0;
			}else if (outMod > inMod){
				diff = outMod - inMod;
				returnHrs = vals + diff/100.0;
			}else{
				returnHrs = vals;
			}
		}
	}else if (timeInInt < 800 && timeInInt > 0){ //early
		if(timeOutInt >= 1700){ //early and finishes at 17:00 or more but not OT
			printf("Early but ended on time\n");
			returnHrs = 8; 
		}else if (timeOutInt < 1700){ //early and undertime
			//printf("Early and ended early\n");
			out = timeOutInt/100; //hr for out
			in = timeInInt/100; //hr for in
			vals = out - in;
			outMod = timeOutInt%100; //mins for out
			inMod = timeInInt%100; //mins for in
			if(outMod < inMod){
				diff = outMod - inMod;
				diff += 60;
				vals--;
				returnHrs = vals + diff/100.0;
			}else if (outMod > inMod){
				diff = outMod - inMod;
				returnHrs = vals + diff/100.0;
			}else{
				returnHrs = vals;
			}			
		}
	}else if (timeInInt == 0 && timeOutInt == 0){
		returnHrs = 0;
	}
	return returnHrs;
}

float getOverTime(char timeIn[], char timeOut[]){
	float retHrs=0,hrs;
	int timeInInt, timeOutInt, out, in, excessTime, outMod, inMod,diff;
	timeInInt = stringtoInt(timeIn);
	timeOutInt = stringtoInt(timeOut);

	if(timeInInt < 1730){
		
		out = timeOutInt/100;
		in = timeInInt/100;
		hrs = out - in;
		outMod = timeOutInt % 100;
		inMod = timeInInt % 100;
		if(outMod < inMod){
			diff = outMod - inMod;
			diff+=60;
			hrs--;
			retHrs = hrs + diff/100.0;
		}else{
			retHrs = hrs;
		}
	}else if (timeInInt >= 1730){
		
		if (timeInInt == 1730){
			out = timeOutInt/100;
			in = timeInInt/100;
			hrs = out - in;
			outMod = timeOutInt % 100;
			inMod = timeInInt % 100;
			if(outMod < inMod){
				diff = outMod - inMod;
				diff+=60;
				hrs--;
				retHrs = hrs + diff/100.0;
			}else if (outMod > inMod){
				diff = outMod - inMod;
				retHrs = hrs + diff/100.0;
			}
			else{
				retHrs = hrs;
			}
		}
	}
	
	return retHrs;
}


int checkTimeInput(char arr[]){
	int retVal=0,x,cnt=0;
	int len = strlen(arr);
	int timeinInt;
	timeinInt = stringtoInt(arr);
	if(timeinInt/100 < 24 && timeinInt%100 < 60){
		if(len == 4 && arr[1] == ':'){ //1:00 1::0
			for(x=0;x<strlen(arr);x++){
				if(':' == arr[x]){
					cnt++;
				}
			}
			if(cnt == 1){
				retVal = 1;
			}
			else{
				printf("Invalid Input. Please Try Again.\n");
				retVal = 0;
			}
		}else if(len == 5 && arr[2] == ':'){
			for(x=0;x<strlen(arr);x++){
				if(':' == arr[x]){
					cnt++;
				}
			}
			if(cnt == 1){
				retVal = 2;
			}
			else{
				printf("Invalid Input. Please Try Again.\n");
				retVal = 0;
			}
		}
		else{
			printf("Invalid Input. Please Try Again.\n");
			retVal = 0;
		}
	}else{
		printf("Invalid Input. Please Try Again.\n");
	}
	return retVal;
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


