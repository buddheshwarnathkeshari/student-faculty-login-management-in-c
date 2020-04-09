#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

typedef struct 
{
char name[50],mob[25],id[25],email[100],pass[100];
int year, branch;		//cse =1, Me=2, CE=3, EE=4 ,EC=5
}student;
typedef struct
{
	char name[50],mob[25],id[25],email[100],pass[100];
}faculty;
void stud();
void loggedstudprofile();
int studlogin();
void getpass(char *);
int getmob(char *);		int getname(char*);			int getid(char *);		int getemail(char *);
void gotoxy(int,int);	void box(int,int,int,int);	int isword(char);		void capitalize(char *);	int exist(char *);
void adminlogged();		int adminlogin();			int facultylogin();		void fac();
int addstudent();		void liststud();			void delstud();			void searchstud();			void modstud();
int addfac();			void listfac();				void delfac();			void searchfac();			void modfac();
void loggedfacprofile();
void editfac(faculty ,faculty);
void editstud(student,student);

int i,inttemp;
char chartemp,choice,stringtemp[100];
faculty loggedf,Admin,f,f1,f2,f3,f4;
student loggeds ,S,s,s2,s3,temp;
char studrec[50]="studRec.txt",facrec[50]="facrec.txt",admin[50]="Admin.txt";
FILE *Temp,*fp;
int studsize=sizeof(S),facsize=sizeof(f);

#include"cquizgame.c"
main()
{
//	system("pause");
//	main2();
	system("color F0");
	begin:	
	SetConsoleTitle("STUDENT RECORD STORAGE & MANAGEMENT SYSTEM->LOGIN");
		system("CLS");
	box(15,1,3,62);		printf("\t\t\t***CHOOSE YOUR OPTION***");
	box(15,6,3,30);		printf("1.Administrator");
	box(47,6,3,30);		printf("2.Login as faculty");
	box(15,10,3,30);	printf("3.login as student");
	box(47,10,3,30);	printf("4.Exit");
	box(30,14,3,22);	printf("Enter your option->");
	wo2:	box(54,14,3,6);		choice=getch();
	switch(choice)
	{
		case '1':
			if(!exist(admin))
			{	strcpy(Admin.name,"Administrator");	strcpy(Admin.id,"Admin");	strcpy(Admin.pass,"Admin");	strcpy(Admin.mob,"1234567890");	strcpy(Admin.email,"faculty@default.com");
				fp=fopen(admin,"ab+");	fwrite(&Admin,sizeof(f),1,fp);	fclose(fp);
			}	
			if(!adminlogin())
			{
				goto begin;
			}
			goto begin;
		case '2':
				if(facultylogin())
				{
				
					fac();
				}
			goto begin;
		case '3':
			if(studlogin())
			{
				
				stud();
			}
			goto begin;
		case '4':
			exit(0);
		default:
			goto wo2;
	}
}


void gotoxy(int x,int y)
{
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void box(int x,int y,int height,int width)
{	int i;
	height++;
	width+=2;

	for(i=x;i<=x+width;i++)
	{
		gotoxy(i,y);
		printf("%c",177);
		gotoxy(i,y+height);
		printf("%c",177);
		
	}
	for(i=y;i<=y+height;i++)
	{
		gotoxy(x,i);
		printf("%c%c",177,177);
		gotoxy(x+width,i);
		printf("%c%c",177,177);
	}
	gotoxy(x+3,y+2);
}
int getmob(char *mob)
{
	fflush(stdin);
	gets(mob);
	if(strlen(mob)!=10)	return 1;
	for(i=0;i<strlen(mob);i++)		if(!isdigit(mob[i]))	return 1;
	if(mob[0]=='0') return 1;

	return 0;
	
	
}

int getid(char *id)
{
	fflush(stdin);
	gets(id);
	if(strlen(id)!=10)	return 1;
	
	for(i=0;i<strlen(id);i++)		if(!isdigit(id[i]))	return 1;
	if(id[0]=='0') return 1;

	return 0;
	
	
}


int getname(char *name)
{
	fflush(stdin);
	gets(name);
	for( i=0;i<strlen(name);i++){	if(!(isword(name[i])||name[i]==' '))	return 1;}
	capitalize(name);
	return 0;
}

int isword(char w)
{
	if(w>=65&&w<=90||w>=97&&w<=122) return 1;	
	return 0;
}
void capitalize(char *n)
{
	int i;
	strlwr(n);
	for(i=0;i<strlen(n);i++)
	{
		if(i==0)
				if(n[i]>='a'&&n[i]<='z')
					n[0]-=32;
		else if(n[i]==' ')
		{
			i++;
			if(n[i]>='a'&&n[i]<='z')
				n[i]-=32;
		}
		
	}
}
int getemail(char *e)
{
	fflush(stdin);
	char email[100];
	gets(email);
	int length=strlen(email);
	int i,at=0,atpos,dot=0,dotpos;
	for(i=0;i<length;i++)
		if(email[i]=='@')	{	at++;	atpos=i;	}
	if(at!=1)	return 1;
	if(atpos==0)	return 1;
	for(i=0;i<length;i++)
		if(email[i]=='.')	{	dot++;	dotpos=i;	}
	if(dot<1)	return 1;
	if(length-1-dotpos<2)	return 1;
	if(dotpos-atpos<2)	return 1;
	strcpy(e,email);
	return 0;
}
int exist(char *filename)
{
	FILE *fp=fopen(filename,"r");
	if(fp==NULL)
	return 0;
	else
	{
		fclose(fp);
		return 1;
	}
	
}
int addstudent()
{
	
			printf("Enter the name of student\n");
			fflush(stdin);
			while(getname(S.name))			printf("Invalid Name\nEnter the name again\n");
			
			printf("Enter the ID(Roll No.)\n");
			fflush(stdin);
			while(getid(S.id))				printf("Invalid ID\n Enter the correct id again\n");
			fp=fopen(studrec,"ab+");
			rewind(fp);
			while(fread(&temp,studsize,1,fp))
			{
				if(!strcmp(S.id,temp.id))
				{
				printf("\nThis Id is already in use\n");
				system("pause");
				system("cls");
				return 1;
				}
			}
			printf("Enter the email of %s\n",S.name);
			fflush(stdin);
			while(getemail(S.email))
				printf("Invalid email\nEnter the email in correct format\n");
				
			printf("Enter the mobile number of %s\n",S.name);
			fflush(stdin);
			while(getmob(S.mob))
				printf("Invalid mobile number\nEnter the mobile number again\n");
			
			year:
			printf("Enter your year(i.e. 1st , 2nd, 3rd or 4th)\n");
			fflush(stdin);
			chartemp=getch();
			printf("%c\n",chartemp);
			if(chartemp>'4'||chartemp<'1')
			{
				printf("\nInvalid year\n");
				goto year;
			}
			else
			S.year=chartemp=='1'?1:chartemp=='2'?2:chartemp=='3'?3:4;
			branch:
			printf("Choose your branch\n");
			printf("1.Computer science and engineering(CSE)\n");
			printf("2.Mechanical Engineering(ME) \n");
			printf("3.Civil Engineering(CE)\n");
			printf("4.Electrical Engineering(EE)\n");
			printf("5.Electronics and Communication Engineering(EC)\n");
			fflush(stdin);
			chartemp=getch();
			printf("%c\n",chartemp);
			if(chartemp>'5'||chartemp<'1')
			{
				printf("\nInvalid branch\n");
				goto branch;
			}
			else
			S.branch=chartemp=='1'?1:chartemp=='2'?2:chartemp=='3'?3:chartemp=='4'?4:5;
			
			strcpy(S.pass,S.id);
			fwrite(&S,studsize,1,fp);
			fclose(fp);
			printf("Record successfully added\n");
			
}
void liststud()
{
		fp=fopen(studrec,"ab+");
			rewind(fp);
			if(!fread(&S,studsize,1,fp))
			{
				printf("No record found\n");
			}
			else
			{
				rewind(fp);
				while(fread(&S,studsize,1,fp))
				{
					for(i=0;i<60;i++)	printf("%c",205);
					printf("\n");
					printf("\t%-15s:","Name");
					puts(S.name);
					printf("\t%-15s:","ID/Roll No.");
					puts(S.id);
					printf("\t%-15s:","Mobile No.");
					puts(S.mob);
					printf("\t%-15s:","Email id");
					puts(S.email);
					printf("\t%-15s:%d%s %s","Year",S.year,S.year==1?"st":S.year==2?"nd":S.year==3?"rd":"th","year");
					printf("\n\t%-15s:","Branch");
					S.branch==1?printf("CSE"):S.branch==2?printf("ME"):S.branch==3?printf("CE"):S.branch==4?printf("EE"):printf("EC");
					printf("\n");
					for(i=0;i<60;i++)	printf("%c",205);
					printf("\n");
				
				}
			}
		fclose(fp);
}
void delstud()
{
	int flag=0;
	system("CLS");
			Temp=fopen("Temp.DAT","ab+");
			fp=fopen(studrec,"ab+");
			printf("Enter the ID/Roll No., which you want to delete\n");
			while(getid(temp.id))	printf("\nINVALID ID\nEnter the ID again\n");
			
			rewind(fp);
			rewind(Temp);
			while(fread(&S,studsize,1,fp))
			{
				if(!strcmpi(temp.id,S.id))
				{
					flag=1;
				continue;
				}
				else
				fwrite(&S,studsize,1,Temp);
			}
			fclose(fp);
			fclose(Temp);
			remove(studrec);
			rename("Temp.DAT",studrec);
			if(flag)
			printf("File deleted successfully!...\n");
			else
			printf("File not found...\n");
}
void modstud()
{
		system("CLS");
			printf("Enter the ID/Roll no. of the student\n");
			gets(temp.id);
		
			fp=fopen(studrec,"rb+");
			rewind(fp);
			while(fread(&S,studsize,1,fp))
			{
				if(!strcmpi(S.id,temp.id))
				{
					
				printf("\nEnter new details\n");
				printf("Enter the name of student\n");
				fflush(stdin);
				while(getname(S.name))
					printf("Invalid Name\nEnter the name again\n");
				
				printf("Enter the ID(Roll No.)\n");
				id:
				fflush(stdin);
				while(getid(S.id))
					printf("Invalid ID\n Enter the correct id again\n");
					
				rewind(fp);
			if(strcmp(S.id,temp.id))
			while(fread(&s,studsize,1,fp))
			{
				if(!strcmp(S.id,s.id))
				{
				printf("\nThis Id is already in use\n");
				printf("Enter the correct id\n");
				goto id;
				}
			}
			printf("Enter the email of %s",S.name);
			
			fflush(stdin);
			while(getemail(S.email))
				printf("Invalid email\nEnter the email in correct format\n");
				
			printf("Enter the mobile number of %s\n",S.name);
			fflush(stdin);
			
			while(getmob(S.mob))
				printf("Invalid mobile number\nEnter the mobile number again\n");
			
			year2:
			printf("Enter your year(i.e. 1st , 2nd, 3rd or 4th)\n");
			fflush(stdin);
			chartemp=getch();
			printf("%c\n",chartemp);
			if(chartemp>'4'||chartemp<'1')
			{
				printf("\nInvalid year\n");
				goto year2;
			}
			else
				S.year=chartemp=='1'?1:chartemp=='2'?2:chartemp=='3'?3:4;
			
			branch2:
			printf("Choose your branch\n");
			printf("1.Computer science and engineering(CSE)\n");
			printf("2.Mechanical Engineering(ME) \n");
			printf("3.Civil Engineering(CE)\n");
			printf("4.Electrical Engineering(EE)\n");
			printf("5.Electronics and Communication Engineering(EC)\n");
			fflush(stdin);
			chartemp=getch();
			printf("%c\n",chartemp);
			inttemp=0;
			if(chartemp>'5'||chartemp<'1')
			{
				printf("\nInvalid branch\n");
				goto branch2;
			}
			else
			S.branch=chartemp=='1'?1:chartemp=='2'?2:chartemp=='3'?3:chartemp=='4'?4:5;
			rewind(fp);
			while(fread(&s2,studsize,1,fp))
				if(!strcmpi(s2.id,temp.id))
					break;
			inttemp=5;
			fseek(fp,-studsize,SEEK_CUR);				                      
			fwrite(&S,studsize,1,fp);				                     
			fclose(fp);										                 
			printf("\nRecord modify successfully\n");		                
			break;
				}
			}
			if(inttemp!=5)
			{
				printf("\nRecord not found\n");
			}

}
void searchstud()
{
	inttemp=0;
			printf("Enter the ID/Roll no. \n");
			fflush(stdin);
			gets(temp.id);
			fp=fopen(studrec,"ab+");
			rewind(fp);
			while(fread(&S,studsize,1,fp))
			{	if(!strcmp(temp.id,S.id))
				{
				for(i=0;i<60;i++)	printf("%c",205);
				printf("\n");
				printf("\t%-15s:","Name");
				puts(S.name);
				printf("\t%-15s:","ID/Roll No.");
				puts(S.id);
				printf("\t%-15s:","Mobile No.");
				puts(S.mob);
				printf("\t%-15s:","Email id");
				puts(S.email);
				printf("\t%-15s:%d%s %s","Year",S.year,S.year==1?"st":S.year==2?"nd":S.year==3?"rd":"th","year");
				printf("\n\t%-15s:","Branch");
				S.branch==1?printf("CSE"):S.branch==2?printf("ME"):S.branch==3?printf("CE"):S.branch==4?printf("EE"):printf("EC");
				printf("\n");
				for(i=0;i<60;i++)	printf("%c",205);
				printf("\n");
				inttemp=2;
				}
			}
			if(inttemp!=2)
			printf("Record not found\n");
			fclose(fp);
}
int facultylogin()
{
	system("cls");
		SetConsoleTitle("STUDENT RECORD STORAGE & MANAGEMENT SYSTEM->FACULTY");
	FILE *fp;
	int flag=0,flag1=0;
	char id[50],pass[50];
	begin:
		
	printf("Enter your id\n");
	gets(f1.id);
	printf("Enter your password\n");
	getpass(f1.pass);
	if(!exist(facrec))
	{
		fp=fopen(admin,"ab+");
		rewind(fp);
		fread(&f,facsize,1,fp);
		fclose(fp);
		if(!strcmp(id,f.id)&&!strcmp(pass,f.pass))
		{ 		
			loggedf=f;
			return 1; 
		}
		else 
		{
			
			printf("\n\nWrong details\nEnter again\n");
			goto begin;	
			
			
		}
			fclose(fp);
	}
	else
	{
		flag=0,flag1=0;
		fp=fopen(facrec,"ab+");
		rewind(fp);
		while(fread(&f,facsize,1,fp))
		{
			if(!strcmp(f1.id,f.id))
			{
				flag1=1;
				if(!strcmp(f1.pass,f.pass))
				{
					fclose(fp);
					loggedf=f;
					flag=1;
					return 1;
				}
			}
		}
		if(!flag)
		{
			if(!flag1)
			{
				printf("\n\nThe id \"%s\" is not registered!\nplease contact your administrator\n\n",f1.id);
				system("pause");
				fclose(fp);
			}
			else
			{
				printf("\nWrong details\n\n");
				char i;
				printf("1.Login Menu\n2.Enter the details again\n");
				op:
				i=getch();
				if(i=='2')
				goto begin;
				else if(i=='1')
				{
					fclose(fp);
					return 1;
				}
				else
					goto op;
			}
		}	
	}
	return 0;
}
void fac()
{
	FILE *fp=fopen(facrec,"ab+");
	begin:	
	system("cls");
	box(1,1,3,94);		printf("\t \t\t\t  \t***CHOOSE YOUR OPTION***");
	box(1,6,3,30);		printf("1.See your profile");
	box(33,6,3,30);		printf("2.Edit your profile");
	box(65,6,3,30);		printf("3.logout");
	box(1,10,3,30);		printf("4.Add a student");
	box(33,10,3,30);	printf("5.List of students");
	box(65,10,3,30);	printf("6.Search a student");
	box(1,14,3,30);		printf("7.Search a faculty");
	box(33,14,3,30);	printf("8.Modify a student's record");
	box(65,14,3,30);	printf("9.Remove a student's record");
	
//	box(1,18,3,30);	printf("A. Add a student");

	
	box(33,18,3,22);	printf("Enter your option->");
	wo:
	box(57,18,3,6);		choice=getch();
	if(choice<'1'||choice>'9')		goto wo;
	system("CLS");
	switch(choice)
	{
		case '1':
			system("cls");
			
			box(1,1,3,50);	printf("\t\t---------MY PROFILE---------");
			printf("\n\n\n\n");
			
				printf("\n");
				printf("\t%-15s:","Name");
				puts(loggedf.name);
				printf("\n\t%-15s:","ID/Roll No.");
				puts(loggedf.id);
				printf("\n\t%-15s:","Mobile No.");
				puts(loggedf.mob);
				printf("\n\t%-15s:","Email id");
				puts(loggedf.email);
				box(1,5,10,50);
				gotoxy(1,20);
				system("pause");
				
			
			goto begin;
		case '2':
			system("cls");
				printf("\t---------Your current detail---------");
				printf("\n\n");
				printf("\n");
				printf("\t%-15s:","Name");
				puts(loggedf.name);
				printf("\t%-15s:","ID/Roll No.");
				puts(loggedf.id);
				printf("\t%-15s:","Mobile No.");
				puts(loggedf.mob);
				printf("\t%-15s:","Email id");
				puts(loggedf.email);
				
				
				
				printf("\n\n\nEnter new details\n");
				printf("Enter your name\n");
				while(getname(f.name)) printf("Enter the correct name\n");
				printf("Enter your Id");
				gets(f.id);
				
				rewind(fp);
				if(strcmp(f.id,loggedf.id))
				while(fread(&f2,facsize,1,fp))
				{
					if(!strcmp(f.id,f2.id))
					{
					printf("\nThis Id is already in use\n");
					printf("Enter the correct id\n");
					system("pause");
					goto begin;
					}
				}
				
				printf("Enter your Mobile number\n");
				while(getmob(f.mob)) printf("Enter the correct mobile number\n");
				printf("Enter your email\n");
				while(getemail(f.email)) printf("Invalid email\nEnter the email in correct format\n");
				printf("Enter your new password\n");
				getpass(f.pass);
				printf("\n\nEnter your current password to make changes\n");
				getpass(f3.pass);
				if(strcmp(f3.pass,loggedf.pass))
				{
					printf("Wrong password\n");
					system("pause");
					goto begin;
				}
				else
				{
				
					fp=fopen(facrec,"rb+");
					rewind(fp);
					while(fread(&f3,facsize,1,fp))
						if(!strcmpi(loggedf.id,f3.id))
						break;
						
						fseek(fp,-facsize,SEEK_CUR);				                      
						fwrite(&f,facsize,1,fp);				                     
						fclose(fp);
						printf("\n\nChanges saved successfully\n");
						loggedf=f;
						printf("Your password is: ");
						puts(f.pass);
						printf("\nRemember it carefully\n");	
						system("pause");
				
				}
			goto begin;
			
		case '3':
			return;
		case '4':
				system("cls");
				if(addstudent())
				goto begin;
			system("pause");
			system("cls");			
			goto begin;
		
		case '5':
			system("cls");
			printf("Choose your option\n");
			printf("1.List of all students\n2.List of students year wise\n3.List of student year and branch wise\n");
			wo66:
			choice=getch();
			switch(choice)
			{
				case '1':
					liststud();
					system("pause");
					system("cls");
					goto begin;
				case '2':
					system("cls");
					inttemp=0;
					rewind(fp);
					printf("Enter the year(i.e. 1,2,3 or 4)\n");
					scanf("%d",&temp.year);
					fp=fopen(studrec,"ab+");
					while(fread(&S,studsize,1,fp))
					{	
						if(temp.year==S.year)
						{
							for(i=0;i<60;i++)	printf("%c",205);
							printf("\n");
							printf("\t%-15s:","Name");
							puts(S.name);
							printf("\t%-15s:","ID/Roll No.");
							puts(S.id);
							printf("\t%-15s:","Mobile No.");
							puts(S.mob);
							printf("\t%-15s:","Email id");
							puts(S.email);
							printf("\t%-15s:%d%s %s","Year",S.year,S.year==1?"st":S.year==2?"nd":S.year==3?"rd":"th","year");
							printf("\n\t%-15s:","Branch");
							S.branch==1?printf("CSE"):S.branch==2?printf("ME"):S.branch==3?printf("CE"):S.branch==4?printf("EE"):printf("EC");
							printf("\n");
							inttemp=3;
							for(i=0;i<60;i++)	printf("%c",205);
							printf("\n");
						}
					}
					if(inttemp!=3)
					printf("No record found\n");
					fclose(fp);
					system("pause");
					system("cls");
					goto begin;
				case '3':
					system("cls");
					inttemp=0;
				rewind(fp);
				printf("Enter the year(i.e. 1,2,3 or 4)\n");
				scanf("%d",&temp.year);
				printf("Choose your branch\n");
				printf("1.Computer science and engineering(CSE)\n");
				printf("2.Mechanical Engineering(ME) \n");
				printf("3.Civil Engineering(CE)\n");
				printf("4.Electrical Engineering(EE)\n");
				printf("5.Electronics and Communication Engineering(EC)");
				scanf("%d",&temp.branch);
				fp=fopen(studrec,"ab+");
				while(fread(&S,studsize,1,fp))
				{	if(temp.year==S.year&&temp.branch==S.branch)
					{
					for(i=0;i<60;i++)	printf("%c",205);
					printf("\n");
					printf("\t%-15s:","Name");
					puts(S.name);
					printf("\t%-15s:","ID/Roll No.");
					puts(S.id);
					printf("\t%-15s:","Mobile No.");
					puts(S.mob);
					printf("\t%-15s:","Email id");
					puts(S.email);
					printf("\t%-15s:%d%s %s","Year",S.year,S.year==1?"st":S.year==2?"nd":S.year==3?"rd":"th","year");
					printf("\n\t%-15s:","Branch");
					S.branch==1?printf("CSE"):S.branch==2?printf("ME"):S.branch==3?printf("CE"):S.branch==4?printf("EE"):printf("EC");
					printf("\n");
					inttemp=4;
					for(i=0;i<60;i++)	printf("%c",205);
					printf("\n");
					}
				}
				if(inttemp!=4)
				printf("No record found\n");
				fclose(fp);
				system("pause");
				system("cls");
				goto begin;	
						default:
							goto wo66;
				}
				goto begin;
		case '6':
			system("cls");
			searchstud();
			system("pause");
			system("cls");
			goto begin;
			 
		case '7':
			system("cls");
			searchfac();
			system("pause");
			system("cls");
			goto begin;
		case '8':
			modstud();
			system("pause");
			system("cls");	
			goto begin;	
		case '9':
				delstud();
			system("pause");
			system("cls");
			goto begin;	
			
	
	}
}

int adminlogin()
{
	system("cls");
	
	SetConsoleTitle("STUDENT RECORD STORAGE & MANAGEMENT SYSTEM->ADMINISTRATOR");
	begin:
	printf("Enter the id\n");	gets(f.id);
	printf("Enter the password\n");	getpass(f.pass);
	fp=fopen(admin,"ab+");
	fread(&Admin,sizeof(Admin),1,fp);
	fclose(fp);
	if(!strcmpi(f.id,Admin.id)&&!strcmp(f.pass,Admin.pass))		
	{
		loggedf=Admin;
		adminlogged();
	}
	else 
		{	printf("\nWrong details\n\n");
			char i;
			printf("1.Login Menu\n2.Enter the details again\n");
			op:
			i=getch();
			if(i=='2')
				goto begin;
			else if(i=='1')
				return 1;
			else
			{
				goto op;
			}
		}
}
void adminlogged()
{	begin:
	system("cls");
	box(1,1,3,94);			printf("Hello %s! You are logged in\n",loggedf.name);
	box(1,6,3,30);			printf("A.See your profile\n");
	box(33,6,3,30);			printf("B.Edit your profile\n");
	box(65,6,3,30);			printf("C.Search a faculty\n");
	box(1,10,3,30);			printf("D.Search a student\n");
	box(33,10,3,30);		printf("E.List of faculties\n");
	box(65,10,3,30);		printf("F.List of students\n");
	box(1,14,3,30);			printf("G.Add a student\n");
	box(33,14,3,30);		printf("H.Add a faculty\n");
	box(65,14,3,30);		printf("I.Remove a student\n");
	box(1,18,3,30);			printf("J.Remove a faculty\n");
	box(33,18,3,30);		printf("K.Modify record of student\n");
	box(65,18,3,30);		printf("L.Modify record of faculty\n");
	box(1,22,3,44);			printf("M.logout\n");
	box(47,22,3,43);		printf("Enter your choice");
	wo:	
	box(92,22,3,3);	
	choice=getch();

	switch(choice)
	{
		case 'A':
		case 'a':
			loggedfacprofile();
			goto begin;
		case 'B':
		case 'b':
			system("cls");
				printf("\t---------Your current detail---------");
			printf("\n\n");
				printf("\n");
				printf("\t%-15s:","Name");
				puts(loggedf.name);
				printf("\t%-15s:","ID/Roll No.");
				puts(loggedf.id);
				printf("\t%-15s:","Mobile No.");
				puts(loggedf.mob);
				printf("\t%-15s:","Email id");
				puts(loggedf.email);
				printf("\n\n\nEnter new details\n");
				printf("Enter your name\n");
				while(getname(f.name)) printf("Enter the correct name\n");
				printf("Enter your Id");
				gets(f.id);
				printf("Enter your Mobile number\n");
				while(getmob(f.mob)) printf("Enter the correct mobile number\n");
				printf("Enter your email\n");
				while(getemail(f.email)) printf("Invalid email\nEnter the email in correct format\n");
				printf("Enter your new password\n");
				getpass(f.pass);
				printf("\n\nEnter your current password to make changes\n");
				getpass(f2.pass);
				if(strcmp(f2.pass,loggedf.pass))
				{
					printf("Wrong password\n");
					system("pause");
					goto begin;
				}
				else
				{
					fp=fopen(admin,"wb");
					fwrite(&f,sizeof(f),1,fp);
					fclose(fp);
					loggedf=f;
					printf("\n\nChanges saved successfully\n");
					printf("Your password is: ");
					puts(f.pass);
					printf("\nRemember it carefully\n");
					system("pause");
				}
				
			goto begin;
		case 'C':
		case 'c':
			searchfac();
			system("pause");
			system("cls");
			goto begin;
		case 'D':
		case 'd':
			system("cls");
			searchstud();
			system("pause");
			system("cls");
			goto begin;
			 
		case 'E':
		case 'e':
			system("cls");
			listfac();
			system("pause");
			system("cls");
			goto begin;
			
			break;
		case 'F':
		case 'f':
			system("cls");
			printf("Choose your option\n");
			printf("1.List of all students\n2.List of students year wise\n3.List of student year and branch wise\n");
			wo66:
			choice=getch();
			switch(choice)
			{
				case '1':
					liststud();
					system("pause");
					system("cls");
					goto begin;
				case '2':
					system("cls");
					inttemp=0;
					rewind(fp);
					printf("Enter the year(i.e. 1,2,3 or 4)\n");
					scanf("%d",&temp.year);
					fp=fopen(studrec,"ab+");
					while(fread(&S,studsize,1,fp))
					{	
						if(temp.year==S.year)
						{
							for(i=0;i<60;i++)	printf("%c",205);
							printf("\n");
							printf("\t%-15s:","Name");
							puts(S.name);
							printf("\t%-15s:","ID/Roll No.");
							puts(S.id);
							printf("\t%-15s:","Mobile No.");
							puts(S.mob);
							printf("\t%-15s:","Email id");
							puts(S.email);
							printf("\t%-15s:%d%s %s","Year",S.year,S.year==1?"st":S.year==2?"nd":S.year==3?"rd":"th","year");
							printf("\n\t%-15s:","Branch");
							S.branch==1?printf("CSE"):S.branch==2?printf("ME"):S.branch==3?printf("CE"):S.branch==4?printf("EE"):printf("EC");
							printf("\n");
							inttemp=3;
							for(i=0;i<60;i++)	printf("%c",205);
							printf("\n");
						}
					}
					if(inttemp!=3)
					printf("No record found\n");
					fclose(fp);
					system("pause");
					system("cls");
					goto begin;
				case '3':
					system("cls");
					inttemp=0;
				rewind(fp);
				printf("Enter the year(i.e. 1,2,3 or 4)\n");
				scanf("%d",&temp.year);
				printf("Choose your branch\n");
				printf("1.Computer science and engineering(CSE)\n");
				printf("2.Mechanical Engineering(ME) \n");
				printf("3.Civil Engineering(CE)\n");
				printf("4.Electrical Engineering(EE)\n");
				printf("5.Electronics and Communication Engineering(EC)");
				scanf("%d",&temp.branch);
				fp=fopen(studrec,"ab+");
				while(fread(&S,studsize,1,fp))
				{	if(temp.year==S.year&&temp.branch==S.branch)
					{
				
					for(i=0;i<60;i++)	printf("%c",205);
					printf("\n");
					printf("\t%-15s:","Name");
					puts(S.name);
					printf("\t%-15s:","ID/Roll No.");
					puts(S.id);
					printf("\t%-15s:","Mobile No.");
					puts(S.mob);
					printf("\t%-15s:","Email id");
					puts(S.email);
					printf("\t%-15s:%d%s %s","Year",S.year,S.year==1?"st":S.year==2?"nd":S.year==3?"rd":"th","year");
					printf("\n\t%-15s:","Branch");
					S.branch==1?printf("CSE"):S.branch==2?printf("ME"):S.branch==3?printf("CE"):S.branch==4?printf("EE"):printf("EC");
					printf("\n");
					inttemp=4;
					for(i=0;i<60;i++)	printf("%c",205);
					printf("\n");
					}
				}
				if(inttemp!=4)
				printf("No record found\n");
				fclose(fp);
				system("pause");
				system("cls");
				goto begin;	
						default:
							goto wo66;
				}
				goto begin;
		case 'G':
		case 'g':
			system("cls");
				if(addstudent())
				goto begin;
			system("pause");
			system("cls");			
			goto begin;
		case 'H':
		case 'h':
			system("cls");
			if(addfac())
				goto begin;
			system("pause");
			system("cls");
			goto begin;
		case 'I':
		case 'i':
			delstud();
			system("pause");
			system("cls");
			goto begin;		
		case 'J':
		case 'j':
			delfac();
			system("pause");
			system("cls");
			goto begin;
		case 'K':
		case 'k':
			modstud();
			system("pause");
			system("cls");	
			goto begin;			
		case 'L':
		case 'l':
			modfac();
			system("pause");
			system("cls");	
			goto begin;	
		case 'M':
		case 'm':
			return;
			
		default:
		 goto wo;			
	}	
}
int addfac()
{
			printf("Enter the name of faculty\n");
			while(getname(f.name))			printf("Invalid Name\nEnter the name again\n");
			printf("Enter the ID\n");
			gets(f.id);	
			fp=fopen(facrec,"ab+");
			rewind(fp);
			while(fread(&f2,sizeof(f),1,fp))
			{
				if(!strcmp(f.id,f2.id))
				{
				printf("\nThis Id is already in use\n");
				system("pause");
				system("cls");
				return 1;
				}
			}
			printf("Enter the email of %s\n",f.name);
			fflush(stdin);
			while(getemail(f.email))
				printf("Invalid email\nEnter the email in correct format\n");
				
			printf("Enter the mobile number of %s\n",f.name);
			fflush(stdin);
			while(getmob(f.mob))
				printf("Invalid mobile number\nEnter the mobile number again\n");
			strcpy(f.pass,f.id);
			fwrite(&f,sizeof(f),1,fp);
			fclose(fp);
			printf("Record successfully added\n");
			
	return 0;
}
void loggedfacprofile()
{

	system("cls");
			
			box(1,1,3,50);	printf("\t---------MY PROFILE---------");
			printf("\n\n");
			
				printf("\n");
				printf("\t%-15s:","Name");	puts(loggedf.name);
				printf("\t%-15s:","ID/Roll No.");
				puts(loggedf.id);
				printf("\t%-15s:","Mobile No.");
				puts(loggedf.mob);
				printf("\t%-15s:","Email id");
				puts(loggedf.email);
				box(1,5,10,50);
				gotoxy(1,20);
				system("pause");
}
void loggedstudprofile()
{

	system("cls");
			
			box(1,1,3,50);	printf("\t---------MY PROFILE---------");
			printf("\n\n");
			
				printf("\n");
				printf("\t%-15s:","Name");	puts(loggeds.name);
				printf("\t%-15s:","ID/Roll No.");
				puts(loggeds.id);
				printf("\t%-15s:","Mobile No.");
				puts(loggeds.mob);
				printf("\t%-15s:","Email id");
				puts(loggeds.email);
		
			printf("\t%-15s:%d%s %s","Year",loggeds.year,loggeds.year==1?"st":loggeds.year==2?"nd":loggeds.year==3?"rd":"th","year");
			printf("\n\t%-15s:","Branch");
			loggeds.branch==1?printf("CSE"):S.branch==2?printf("ME"):S.branch==3?printf("CE"):S.branch==4?printf("EE"):printf("EC");
			printf("\n");
				printf("\n\n");
				box(1,5,10,50);
				gotoxy(1,20);
				system("pause");
}

void searchfac()
{
	system("cls");
		inttemp=0;
			printf("Enter the ID\n");
			fflush(stdin);
			gets(f2.id);
			fp=fopen(facrec,"ab+");
			rewind(fp);
			while(fread(&f,facsize,1,fp))
			{	if(!strcmp(f.id,f2.id))
				{
				for(i=0;i<60;i++)	printf("%c",205);
				printf("\n");
				printf("\t%-15s:","Name");
				puts(f.name);
				printf("\t%-15s:","ID");
				puts(f.id);
				printf("\t%-15s:","Mobile No.");
				puts(f.mob);
				printf("\t%-15s:","Email id");
				puts(f.email);
				for(i=0;i<60;i++)	printf("%c",205);
				printf("\n");
				inttemp=2;
				}
			}
			if(inttemp!=2)
			printf("Record not found\n");
			fclose(fp);
}
void listfac()
{
		fp=fopen(facrec,"ab+");
			rewind(fp);
			if(!fread(&f,facsize,1,fp))
			{
				printf("No record found\n");
			}
			else
			{
				rewind(fp);
				while(fread(&f,facsize,1,fp))
				{
					for(i=0;i<60;i++)	printf("%c",205);
					printf("\n");
					printf("\t%-15s:","Name");
					puts(f.name);
					printf("\t%-15s:","ID/Roll No.");
					puts(f.id);
					printf("\t%-15s:","Mobile No.");
					puts(f.mob);
					printf("\t%-15s:","Email id");
					puts(f.email);
					for(i=0;i<60;i++)	printf("%c",205);
					printf("\n");
				
				}
			}
		fclose(fp);
}

void delfac()
{
	int flag=0;
	system("CLS");
	Temp=fopen("Temp.txt","ab+");
	fp=fopen(facrec,"ab+");
	printf("Enter the ID/Roll No., which you want to delete\n");
	gets(f2.id);
	rewind(fp);
	rewind(Temp);
	while(fread(&f,facsize,1,fp))
	{
		if(!strcmpi(f.id,f2.id))
		{
			flag=1;
			continue;
		}
		else
		fwrite(&f,facsize,1,Temp);
	}
	fclose(fp);
	fclose(Temp);
	remove(facrec);
	rename("Temp.txt",facrec);
	if(flag)
	printf("File deleted successfully!...\n");
	else 
	printf("File not found\n");
}
void modfac()
{
	system("CLS");
	printf("Enter the ID\n");
	gets(f2.id);
	fp=fopen(facrec,"rb+");
	rewind(fp);
	while(fread(&f,facsize,1,fp))
	{
		if(!strcmpi(f.id,f2.id))
		{
			printf("\nEnter new details\n");
			printf("Enter the name of faculty\n");
			fflush(stdin);
			while(getname(f.name))
				printf("Invalid Name\nEnter the name again\n");
			printf("Enter the ID\n");
			id:
			fflush(stdin);
			gets(f.id);
			rewind(fp);
			if(strcmp(f.id,f2.id))	
			while(fread(&f3,facsize,1,fp))
			{
				if(!strcmp(f.id,f3.id))
				{
					printf("\nThis Id is already in use\n");
					printf("Enter the correct id\n");
					goto id;
				}
			}
			
			printf("Enter the email of %s",f.name);
			fflush(stdin);
			while(getemail(f.email))
			printf("Invalid email\nEnter the email in correct format\n");			
			printf("Enter the mobile number of %s\n",f.name);
			fflush(stdin);
			while(getmob(f.mob))
				printf("Invalid mobile number\nEnter the mobile number again\n");
					
			rewind(fp);
		while(fread(&f4,facsize,1,fp))
			if(!strcmpi(f4.id,f2.id))
				break;	
				inttemp=5;
				fseek(fp,-facsize,SEEK_CUR);				                      
				fwrite(&f,facsize,1,fp);				                     
				fclose(fp);										                
										                 
					printf("\nRecord modify successfully\n");
					break;
				}
			}
			if(inttemp!=5)
			{
				printf("\nRecord not found\n");
			}

}
int studlogin()
{
	system("cls");
	SetConsoleTitle("STUDENT RECORD STORAGE & MANAGEMENT SYSTEM->STUDENT");
	int flag=0;
	begin:
	printf("Enter your id\n");
	getid(S.id);
	printf("Enter your password\n");
	getpass(S.pass);
	fp=fopen(studrec,"ab+");
	rewind(fp);
	while(fread(&s,studsize,1,fp))
	{
		if(!strcmp(S.id,s.id)&&!strcmp(S.pass,s.pass))
		{
			loggeds=s;
			flag=1;
			fclose(fp);
			return 1;
		}		
	}
	if(flag==0)
	{
			printf("\n\nThe id %s is not registered!\nplease contact your administrator or any faculty.\n\n",S.id);
			fclose(fp);
			system("pause");
//			goto begin;
	}
	
	return 0;
}
void stud()
{
	char choice;
	begin:
	system("cls");
box(1,1,3,62);	printf("CHOOSE YOUR OPTION\n");
box(1,6,3,30);	printf("1.See your profile\n");
box(33,6,3,30);	printf("2.Edit your profile\n");
box(1,10,3,30);	printf("3.List of your classmates\n");
box(33,10,3,30);	printf("4.Logout\n");
box(1,14,3,30);	printf("5.Play a quiz\n");
		box(33,14,3,20); printf("Choose your option ");
	
	wo:
		box(55,14,3,8);
	choice= getch();
	switch(choice)
	{
	case '1':
		loggedstudprofile();
		goto begin;
	case '2':
			system("cls");
			box(1,1,3,50);	printf("\tYour current details");
			printf("\n\n");
			printf("\n");
			printf("\t%-15s:","Name");	puts(loggeds.name);
			printf("\t%-15s:","ID/Roll No.");
			puts(loggeds.id);
			printf("\t%-15s:","Mobile No.");
			puts(loggeds.mob);
			printf("\t%-15s:","Email id");
			puts(loggeds.email);
			printf("\t%-15s:%d%s %s","Year",loggeds.year,loggeds.year==1?"st":loggeds.year==2?"nd":loggeds.year==3?"rd":"th","year");
			printf("\n\t%-15s:","Branch");
			loggeds.branch==1?printf("CSE"):S.branch==2?printf("ME"):S.branch==3?printf("CE"):S.branch==4?printf("EE"):printf("EC");
			printf("\n");
			box(1,5,10,50);
			gotoxy(1,20);
			
			
			
			
			printf("Enter your new details\n");
			printf("Enter your name\n");
			while(getname(s.name)) printf("Invalid name\nEnter the name again\n");
			id:
			printf("Enter your id\n");
			while(getid(s.id)) printf("Invalid id\nEnter the id again\n");
			fp=fopen(studrec,"ab+");
			rewind(fp);
			if(strcmp(s.id,loggeds.id))
			while(fread(&temp,studsize,1,fp))
			{
				if(!strcmp(s.id,temp.id))
				{
				printf("\nThis Id is already in use\n");
				printf("Enter the correct id\n");
				goto id;
				}
			}
			printf("Enter mobile number\n");
			while(getmob(s.mob)) printf("Invalid Mobile number\nEnter the correct mobile number again\n");
			printf("Enter Email\n");
			while(getemail(s.email)) printf("Invalid email\nEnter the email in correct format\n");
			
				printf("Enter the year(i.e. 1,2,3 or 4)\n");
				scanf("%d",&s.year);
				printf("Choose your branch\n");
				printf("1.Computer science and engineering(CSE)\n");
				printf("2.Mechanical Engineering(ME) \n");
				printf("3.Civil Engineering(CE)\n");
				printf("4.Electrical Engineering(EE)\n");
				printf("5.Electronics and Communication Engineering(EC)");
				scanf("%d",&s.branch);
				
			printf("Enter your new password\n");
			getpass(s.pass);
			printf("\n\nEnter your current password to save changes\n");
			getpass(s2.pass);
			if(strcmp(loggeds.pass,s2.pass))
			{
					printf("Wrong password\n");
					system("pause");
					goto begin;
			}
			else
			{
				fp=fopen(studrec,"rb+");
					rewind(fp);
					while(fread(&s3,studsize,1,fp))
						if(!strcmpi(loggeds.id,s3.id))
						break;
						
						fseek(fp,-studsize,SEEK_CUR);				                      
						fwrite(&s,studsize,1,fp);				                     
						fclose(fp);
						printf("\n\nChanges saved successfully\n");
						loggeds=s;
						printf("Your password is: ");
						puts(s.pass);
						printf("\nRemember it carefully\n");	
						system("pause");
									
			}					
			
			goto begin;
	case '3':
		fp=fopen(studrec,"ab+");
		rewind(fp);
		system("cls");
		fread(&S,studsize,1,fp);
		if(!fread(&S,studsize,1,fp))
		{
			printf("No record found\n");
		}
		else
		{
			rewind(fp);
			while(fread(&S,studsize,1,fp))
				if((S.year==loggeds.year)&&(S.branch==loggeds.branch)&&strcmp(loggeds.id,S.id))
				{	for(i=0;i<60;i++)	printf("%c",205);
					printf("\n");
					printf("\t%-15s:","Name");
					puts(S.name);
					printf("\t%-15s:","ID/Roll No.");
					puts(S.id);
					printf("\t%-15s:","Mobile No.");
					puts(S.mob);
					printf("\t%-15s:","Email id");
					puts(S.email);
					printf("\t%-15s:%d%s %s","Year",S.year,S.year==1?"st":S.year==2?"nd":S.year==3?"rd":"th","year");
					printf("\n\t%-15s:","Branch");
					S.branch==1?printf("CSE"):S.branch==2?printf("ME"):S.branch==3?printf("CE"):S.branch==4?printf("EE"):printf("EC");
					printf("\n");
					for(i=0;i<60;i++)	printf("%c",205);
					printf("\n");
				
				}
			}
		
		fclose(fp);
		system("pause");
		goto begin;
	case '4':
		return;

	case '5':
		main2();
		break;
	default:
		goto wo;
	}
}

void getpass(char *password)
{
	char ch,pass[100];
	int i=0;
	ch=getch();
	while(ch !=13)
	{
		if(ch==8&&i!=0)
		{
			printf("\b \b");
			i--;
		}
		else if(ch==8&&i==0)
		{	}
		else
		{
		pass[i]=ch;
		printf("*");
		i++;
		}
		ch=getch();
	}
	pass[i]='\0';
	strncpy(password,pass,i+1);	
}
