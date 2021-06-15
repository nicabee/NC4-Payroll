/* Final Requirement for NC4 by Barrientos, Monica B.*/

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
void readFromDTR(char employeeCode[], float salaryRate);
char* convertToUpperCase(char arr[]);
int stringtoInt(char arr[]);
float getTotalHours(char timeIn[], char timeOut[]);
float getLate(char timeIn[]);
float getOverTime(char timeIn[], char timeOut[]);
float getSalaryRate(char employeeCode[]);
float getRegularIncome(float totalWorkHours, float salaryRate);
float getOvertimeIncome(float totalOThrs, float salaryRate);
float getHolidayIncome(float totalHolidayhrs, float salaryRate);
float getSSS(float grossIncome, float salaryRate);
float getTax(float grossIncome);


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
	char scode[20], employeecode[20];
	float salaryRate, sRate;
   	int i;
//   	float hatdog;
//  	hatdog = getHolidayIncome(8, 380);
//   	printf("hehe:%.2f\n", hatdog);

	
	do 
		{
		 printf("\nEmployee Info\n");
		 printf("\nMenu\n");
		 printf("1. Add a new employee record. \n");
		 printf("2. Search for a certain employee and add their time-ins and time-outs. \n");
		 printf("3. Read current time in and time outs per employee. \n");
		 printf("4. Exit \n");
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
							
							writeToDTR(emp.employeeCode);
							
                            getch();
                            break;
                        }
                    }
                    fclose(fp);
                    getch();
                    system("cls");
                    break;
		     case 3:
				 printf("Enter employee code to be Checked:\n");
				 scanf("%s",employeecode);
	             fflush(stdin);
	             searchCode=convertToUpperCase(employeecode);
	             sRate =  getSalaryRate(searchCode);
			     readFromDTR(searchCode, sRate);
			     getch();
				 system("cls");
			     break;
		    case 4:
		    	printf("Goodbye!\n"); 
		        break;
		     default: 
			 	printf("Wrong Choice. Enter again\n");
			 	getch();
		      	system("cls");
		        break;
		 } 
		} while (choice != 4);

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

float getSalaryRate(char employeeCode[]){
	struct employeeRec emp;  
    FILE *fp;
    float salaryRate;
    fp=fopen("employee.txt","rb");
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
    
    return salaryRate;
}
void readFromDTR(char employeeCode[], float salaryRate){
	struct employee emp;
	FILE* fp;
	fp=fopen("dtr.txt","rb");
	int x, flag=0;
	char day[5];
	float TotalHours = 0, retHrs = 0, totalOvertime=0, totalHoliday=0, retOThrs=0, regularInc, OTInc, holidayInc, sss, tax, grossIncome;
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
					printf("HOLIDAY HRS: %.2f\n", retHrs);
					totalHoliday+=retHrs;
				}
    			
    			if(strcmp(emp.information[x].timeInOT, "00:00") != 0 && strcmp(emp.information[x].timeOutOT, "00:00") != 0){
    				printf("Overtime-in for %s: %s\n", emp.information[x].weekDay, emp.information[x].timeInOT);
    				printf("Overtime-out for %s: %s\n", emp.information[x].weekDay, emp.information[x].timeOutOT);
    				retOThrs = getOverTime(emp.information[x].timeInOT,emp.information[x].timeOutOT);
    				printf("OT HRS: %.2f\n", retOThrs);
    				totalOvertime+=retOThrs;
				}
    			
    			printf("\t====================\t\n");
			}
    		printf("Coverage Date: %s\t\t\n", emp.dateCovered);
		}
    }
    if(flag == 1){
    	printf("Total Number of Work Hours:%.0f\n",TotalHours);
    	printf("Total Number of Holiday Work Hours:%.0f\n",totalHoliday);
    	printf("Overtime Hours:%.0f\n",totalOvertime);
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
    	printf("Net Income: %.2f\n", grossIncome - (tax + sss) + 500);
	}else{
		printf("User not found!");
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
    if( *e != '\0' ){
    	fprintf(stderr, "invalid input\n");
        //return 1;
    }
    //printf("string val = %s, int value = %d\n", arr, d);
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
			printf("Regular Work Hours\n");
			returnHrs = 8;
		}else if (timeOutInt < 1700){
			printf("Started on time but ended early\n");

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

		if(timeOutInt >= 1700){ //late and finishes at 17:00 or more but not OT
		printf("Late but ended on time\n");
			lateval = getLate(timeIn);
			printf("%.2f\n", lateval);
			returnHrs = (float)9 - lateval;
		}else if (timeOutInt < 1700){ //late and undertime
		printf("Late and ended early\n");
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
	}else if (timeInInt < 800){ //early
		if(timeOutInt >= 1700){ //early and finishes at 17:00 or more but not OT
			printf("Early but ended on time\n");
			in1 = timeInInt/100;
			in2 = 800/100;
			hrs = in2 - in1;
			in1Mod = timeInInt % 100;
			hrs-=in1Mod/60.0;
			returnHrs = 8 + hrs; 
		}else if (timeOutInt < 1700){ //early and undertime
			printf("Early and ended early\n");
			
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
	}else if (timeInInt == 0 || timeOutInt == 0){
		printf("Absent\n");
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
float getLate(char timeIn[]){
	float returnLate;
	int timeInInt, diff, diffmod, timeMod;
	float deci;
	
	timeInInt = stringtoInt(timeIn);
	if(timeInInt > 800){
		//printf("Late!\n");
		diff = timeInInt - 800;
		if(diff < 100){
			deci = diff/60.0;
			//printf("%f\n",deci);
			returnLate = deci;
		}else{
			timeMod = diff/100; //5
			diffmod = diff % 100; //30
			deci = diffmod/60.00; //0.5
			returnLate = timeMod + deci;
		}
	}else{
		returnLate = 0.0;
	}
	
	return returnLate;
	
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


