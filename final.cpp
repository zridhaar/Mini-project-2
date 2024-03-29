#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
int i,j;
int main_exit;
int test=0;
void menu();
char u1[10]="em";
int password=12;
void menufore();
void menuforu(void);
int main();
void print();
struct date{
    int month,day,year;
};
struct ad{
    char name[60];
    int acc_no,age;
    char address[60];
    char username;
    char passord[60];
    double phone;
    float amt;
    struct date dob;
    }add,upd,check,rem,transaction;
struct node{
	char name[60];
    int acc_no,age;
    char address[60];
    double username;
    char passord[60];
    double phone;
    float amt;
    struct date dob;
    struct node *next=NULL;
};
struct node *chain[10];
int count=0;
void init(){
	int i;
	for(i=0;i<10;i++){
		chain[i]=NULL;
	}
} 
int getSum(int n)
{
    int sum = 0;
    while (n != 0) {
        sum = sum + n % 10;
        n = n / 10;
    }
    return sum;
}
void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}
void new_acc()
{
    int choice;
    FILE *ptr;
    int con;
    account_no:
    system("cls");
    init();
	do{
	ptr=fopen("record.dat","a+");
	printf("\tADD RECORD");
    printf("\nEnter the account number:");
    scanf("%d",&check.acc_no);
    while(fscanf(ptr,"%d %s %d/%d/%d %d %s %lf %f \n",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,&add.phone,&add.amt)!=EOF)
    {
        if (check.acc_no==add.acc_no)
            {
			printf("Account no. already in use!");
			delay(10);
            goto account_no;
}
    }
    add.acc_no=check.acc_no;
    printf("\nEnter the name:");
    scanf("%s",add.name);
    printf("\nEnter the date of birth(mm/dd/yyyy):");
    scanf("%d/%d/%d",&add.dob.month,&add.dob.day,&add.dob.year);
    printf("\nEnter the age:");
    scanf("%d",&add.age);
    printf("\nEnter the address:");
    scanf("%s",add.address);
    printf("\nEnter the phone number: ");
    scanf("%lf",&add.phone);
    printf("\nEnter the amount to deposit:$");
    scanf("%f",&add.amt); 
    fprintf(ptr,"%d %s %d/%d/%d %d %s %lf %f \n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.phone,add.amt);
    fclose(ptr);
    struct node *btemp;
    btemp=(struct node*)malloc(sizeof(struct node));
	btemp->acc_no=add.acc_no;
	strcpy(btemp->address,add.address);
	btemp->age=add.age;
	strcpy(btemp->name,add.name);
	btemp->amt=add.amt;
	printf("enter the username to use as login");
	scanf("%s",&add.username);
	btemp->username=add.username;
	printf("Enter the password for your account");
	scanf("%s",&add.passord);
	strcpy(btemp->passord,add.passord);
	int key =getSum(add.acc_no);
	if(chain[key]==NULL){
        chain[key]=btemp;
        chain[key]->next=NULL;
    }
    else
    {
	struct node *tem= chain[key];
        while(tem->next)
        {
            tem=tem->next;
        }
        tem->next=btemp;
        btemp->next=NULL;
    }
    printf("if you want to continue");
    scanf("%d",&con);
}while(con==1);
    print();
	add_invalid:
    printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d",&main_exit);
    if (main_exit==1){
        main();
    }
    else if(main_exit==0)
     {
           exit(0);
        }
    else
        {
            printf("\nInvalid!");
            goto add_invalid;
        }
}

void print()
{
    int i;
	for(i =0; i <10; i++)
    {
        struct node *temp = chain[i];
        printf("chain[%d]-->",i);
        while(temp)
        {
            printf("%s-->",temp->name);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}
void edit()
{
    int choice,test=0;
    FILE *old,*newrec;
    old=fopen("record.dat","r");
    newrec=fopen("new.dat","w");
    printf("\nEnter the account no. of the customer whose info you want to change:");
    scanf("%d",&upd.acc_no);
    int key=getSum(upd.acc_no);
    struct node *etemp;
    etemp=chain[key];
    while(etemp){
    	if(etemp->acc_no==upd.acc_no){
          break;
	}
	else{
		etemp=etemp->next;
	}
	}
    int i;
    while(fscanf(old,"%d %s %d/%d/%d %d %s %lf %f \n",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,&add.phone,&add.amt)!=EOF){
    	if (add.acc_no==upd.acc_no){
    		test=1;
    		printf("\nWhich information do you want to change?\n1.Address\n2.Phone\n\nEnter your choice(1 for address and 2 for phone):");
    		scanf("%d",&choice);
    		if(choice==1)
                {printf("Enter the new address:");
                scanf("%s",upd.address);
                fprintf(newrec,"%d %s %d/%d/%d %d %s %lf %f \n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,upd.address,add.phone,add.amt);
                strcpy(etemp->address,upd.address);
				printf("Changes saved!");
                }
    		else if(choice==2)
                {
                printf("Enter the new phone number:");
                scanf("%lf",&upd.phone);
                fprintf(newrec,"%d %s %d/%d/%d %d %s %lf %f \n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,upd.phone,add.amt);
                etemp->phone=upd.phone;
                printf("Changes saved!");
                }
           }
                else{
                	fprintf(newrec,"%d %s %d/%d/%d %d %s %lf %f \n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.phone,add.amt);
				}
			}
	fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat","record.dat");
    if(test!=1)
        {   
            printf("\nRecord not found!!\a");
            edit_invalid:
              printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
              scanf("%d",&main_exit);
                 if (main_exit==1)
                    menufore();
                else if (main_exit==2)
                    exit(0);
                else if(main_exit==0)
                    edit();
                else
                    {
					printf("\nInvalid!\a");
                    goto edit_invalid;}
        }
    else
        {printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        if (main_exit==1)
            menufore();
        else
            exit(0);
        }
}
void transact(void)
{   int choice,test=0;
    char tempusername;
    char temppassord[60]; 
    FILE *old,*newrec;
    old=fopen("record.dat","r");
    newrec=fopen("new.dat","w");

    printf("Enter the account no. of the customer:");
    scanf("%d",&transaction.acc_no);
    int key;
    key=getSum(transaction.acc_no);
    struct node *ttemp;
    ttemp=chain[key];
    while(ttemp){
		if(ttemp->acc_no==transaction.acc_no){
			break;
		}
		else{
		ttemp=ttemp->next;
	}
	}
	printf("%s\n",ttemp->name);
   while (fscanf(old,"%d %s %d/%d/%d %d %s %lf %f \n",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,&add.phone,&add.amt)!=EOF)
   {
        if(add.acc_no==transaction.acc_no)
            {   test=1;
                printf("\n\nDo you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1 for deposit and 2 for withdraw):");
                scanf("%d",&choice);
                if (choice==1)
                {
                    printf("Enter the amount you want to deposit:$ ");
                    scanf("%f",&transaction.amt);
                    printf("Enter the password");
                    scanf("%s",temppassord);
                    if(strcmp(temppassord,ttemp->passord)==0){
					add.amt+=transaction.amt;
                    fprintf(newrec,"%d %s %d/%d/%d %d %s %lf %f \n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.phone,add.amt);
                    printf("\n\nDeposited successfully!");
                    ttemp->amt+=transaction.amt;
                }
                else{
                	printf("password is wrong");
				}
                }
                else
                {
                    printf("Enter the amount you want to withdraw:$ ");
                    scanf("%f",&transaction.amt);
                    printf("Enter the password");
                    scanf("%s",temppassord);
                    if(strcmp(temppassord,ttemp->passord)==0){
                    add.amt-=transaction.amt;
                    fprintf(newrec,"%d %s %d/%d/%d %d %s %lf %f \n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.phone,add.amt);
                    printf("\n\nWithdrawn successfully!");
                    ttemp->amt-=transaction.amt;
                }
            }
	}
            else
            {
               fprintf(newrec,"%d %s %d/%d/%d %d %s %lf %f \n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.phone,add.amt);
            }
   }
   fclose(old);
   fclose(newrec);
   remove("record.dat");
   rename("new.dat","record.dat");
   if(test!=1)
   {
    printf("\n\nRecord not found!!");
    transact_invalid:
    printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
    scanf("%d",&main_exit);
    if (main_exit==0)
        transact();
    else if (main_exit==1)
        menuforu();
    else if (main_exit==2)
        exit(0);
    else
    {
        printf("\nInvalid!");
        goto transact_invalid;
    }

   }
   else
   {
       printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        if (main_exit==1)
            menuforu();
        else
            exit(0);
   }

}
void menuforu(void)
{   int choice;
    printf("\nCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\nWELCOME TO THE MAIN MENU");
    printf("\n1.For transactions\n2-exit\n3-back\nEnter your choice:");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:transact();
        break;
        case 2:exit(0);
        break;
        case 3:
        	main();
        	break;
        

    }
}
void menufore(){
		int choice1;
		printf("1-create an account \n2-edit\n3-exit\n4-back");
		printf("\nEnter the choice");
		scanf("%d",&choice1);
			switch(choice1)
			{
				case 1:
					new_acc();
					break;
				case 2:
					edit();
					break;
				case 3:
					exit(0);
					break;
				case 4:
					main();
					break;
				}
			}
int main(){
	char username[60];
	int pass;
	int choice;
	int choice2;
	printf("******BANK MANAGEMENT SYSTEM********\n");
	printf("ARE YOU A 1-EMPOLYEE OR 2-USER");
	scanf("%d",&choice);
	if(choice==1){
	printf("Enter the username to login");
	scanf("%s",&username);
	printf("Enter the password");
	scanf("%d",&pass);
	if(strcmp(username,u1)==0){
		if(pass==password){
           menufore();
	}
}
}
else{
	menuforu();
}
return 0;
}

    
    



































































































































































































































































