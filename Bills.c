#include <stdio.h>
#include <stdlib.h>

#define SAME_NET_CHARGE 1
#define OTHER_NET_CHARGE 2
#define LOG_LENGTH 2        //Number of call records
#define RENTAL 200
#define TAX 0.05

int bill_number;
char my_number[10];
int month;
char f_name[10];
char l_name[10];
char numbers[LOG_LENGTH][10];
int minutes[LOG_LENGTH];
int fee;
int fee_with_tax;

struct bill{
    int bill_number;
    char *my_number;
    int month;
    char *f_name;
    char *l_name;
    int fee;
}my_bill;

void get_details();
void calculate_charges();
int getExcessUsage();
void setData();
void saveToFile();
int compareNetwork(char myNum[], char num[]);

int main()
{	
    printf("Hello, Welcome to the billing system!\n");
    getchar();
    get_details();
    printf("\nCalculating Charges...\n");
    calculate_charges();    
    printf("Calculating Excess Usage Charges...\n");
    getExcessUsage();
    printf("Fee without Tax: %d\n", fee);
    printf("Fee with Tax: %d\n", fee_with_tax);
    printf("\nSetting Data to struct...\n");
    setData();
    printf("Saving to File...\n");
    saveToFile();
    printf("Saved to File...\n");
    printf("Job Done.\n");
    printf("Press Enter to Exit");
    getchar();
    getchar();
    return 0;
}

void get_details(){
    printf("Fetching Details...\n");
    printf("Enter Bill Number: ");
    scanf("%d", &bill_number);
    printf("Enter Your Number: ");
    scanf("%s", my_number);
    printf("Enter Month Number: ");
    scanf("%d", &month);
    printf("Enter First Name: ");
    scanf("%s", f_name);
    printf("Enter Last Name: ");
    scanf("%s", l_name);
    printf("Enter Call Log...\n");
    int i;
    for(i = 0; i < LOG_LENGTH; i++){
        printf("Enter Number %d: ", i+1);
        scanf("%s", numbers[i]);
        printf("Enter Call Time(mins): ");
        scanf("%d", &minutes[i]);
    }
    printf("Call Log Entered...\n");
    printf("Fetching Done.\n");
}

void calculate_charges(){
    int basic = RENTAL;
    int excess = getExcessUsage();
    fee = basic + excess;
    fee_with_tax = fee + fee*TAX;    
}

int getExcessUsage(){
    int excess_charge = 0;
    int sum_mins = 0;
    int limit = 1000;
    int i;
    for(i = 0; i < LOG_LENGTH; i++){
		sum_mins += minutes[i];
		if(limit < sum_mins){
			int excess = sum_mins - limit;
			if(compareNetwork(my_number, numbers[i]) == 1){
				excess_charge += excess*SAME_NET_CHARGE;
			}else{
				excess_charge += excess*OTHER_NET_CHARGE;
			}
			limit += excess;
		}
	}
    return excess_charge;
}

int compareNetwork(char myNum[], char num[]){
	if((myNum[0]==num[0]) & (myNum[1]==num[1]) & (myNum[2]==num[2])){
		return 1;
	}
	return 0;
}

void setData(){
    my_bill.bill_number = bill_number;
    my_bill.my_number = my_number;      
    my_bill.month = month;
    my_bill.f_name = f_name;            
    my_bill.l_name = l_name;          
    my_bill.fee = fee_with_tax;
}

void saveToFile(){
    FILE *fp;
    fp = fopen("bill.txt", "a");		//Use "w" to overwrite output. "a" is for append
    fprintf(fp, "Bill Number %d\n", my_bill.bill_number);
    fprintf(fp, "Phone Number: %s\n", my_bill.my_number);
    fprintf(fp, "Month: %d\n", my_bill.month);
    fprintf(fp, "First Name: %s\n", my_bill.f_name);
    fprintf(fp, "Last Name: %s\n", my_bill.l_name);
    fprintf(fp, "Charge: %d\n", my_bill.fee);
    fprintf(fp, "\n");
    fclose(fp);
}
