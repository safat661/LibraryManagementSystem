#include<stdio.h>
#include<string.h>

//list of all the functions that are being used
void addBooks();
void mainmenu();
void deletebooks();
void editbooks();
void searchbooks();
void issuebooks();
void viewbooks();
void issuerecord();
void Password();
int readFromFile();
int checkid();
int size;
int find;
FILE *fp,*ft,*fs;
char catagories[][15]={"Computer","Electronics","Electrical","Civil","Mechnnical","Architecture"};
// categories used in addbooks


struct books{                                   //The basic structure that we will be using for the library
	int id;
	char stuName[20];
	char bookName[20];
	int quantity;
	char *cat;
};

struct books a;

//jus a check to find whether the book exists in library
int checkid(int t){
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	if(a.id==t)
		return 0;  //book exists
		return 1; //book does not exist
}

int readFromFile(){
	int t;

	printf("Enter information\n");

	printf("\nID: ");
	fflush(stdin);             //C programming treats all the devices as files. So devices such as the display are addressed in the same way as files
	scanf("%d",&t);

	if(checkid(t) == 0){
		printf("\nBook already exists\n");
		mainmenu();
		return 0;
	}

	a.id=t;

	printf("\nBook Name: ");
	fflush(stdin);
	scanf("%s",a.bookName);

	printf("\nQuantity: ");
	fflush(stdin);
	scanf("%d",&a.quantity);

	return 1;
}

// the function to add books
void addBooks(){
	int x;
	char choice;

	printf("\nYou are now in Add Books menu\n");
	printf("SELECT CATEGOIES: \n");
	printf("1. Computer\n");
	printf("2. Electronics\n");
	printf("3. Electrical\n");
	printf("4. Civil\n");
	printf("5. Mechanical\n");
	printf("6. Architecture\n");
	printf("7. Back to main menu\n");

	printf("Enter your choice: ");
	fflush(stdin);
	scanf("%d",&x);
	printf("\nYou have entered: %d\n", x);     // just a test whether the comment is executed properly

	if(x==7)
		mainmenu();

	fp=fopen("group.txt","a+");    // file openned for the text to be stored in the file

	if(readFromFile()==1){
		a.cat=catagories[x-1];
		fseek(fp,0,SEEK_END);
		fwrite(&a,sizeof(a),1,fp);
		fclose(fp);

		printf("The record is sucessfully saved\n");

		printf("Save any more?(Y / N): ");              // choice for whether to exit it or not
		fflush(stdin);
		scanf("%c", &choice);
		printf("\nyou have entered: %c\n", choice);
		if(choice=='n' ){
			mainmenu();
		}else{
			addBooks();
		}
	}
}

//Function that delete items from file fp
void deletebooks(){

	int d;
	char repeat='y';
	char decide;

	while(repeat=='y'){
		printf("Enter ID to Delete Book: ");
		fflush(stdin);
		scanf("%d",&d);
		fp=fopen("group.txt","r+");
		rewind(fp);
		while(fread(&a,sizeof(a),1,fp)==1){
			if(a.id==d){
			printf("\nBook found\n");
			printf("Book name is: %s\n",a.bookName);
			find= 1;
			}
		}

		if(find!=1){
			printf("No Book found of that ID \n");
			mainmenu();
		}

		if(find==1 ){
			printf("Do you want to delete the book?(Y/N): ");
			fflush(stdin); // used to clear buffer
			scanf("%c", &decide);
			printf("\nYou have entered: %c\n", decide);
			if(decide=='y'){
				ft=fopen("temp.txt","w+");  //temporary file created to delete the entry
				rewind(fp);

				while(fread(&a,sizeof(a),1,fp)==1){// continue reading till the end of file
					if(a.id!=d){					//look for the matching id
					fseek(ft,0,SEEK_SET);			//if id doesnt match, put cursour behind the entry and start reading
					fwrite(&a,sizeof(a),1,ft); //copying everything from group.txt to temp file except the entry to be deleted
					}//if id matches, then it does not copy and skips that entry. then re enters the while loop till end of file
				}
				fclose(ft);//closing file temp
				fclose(fp);//closing file group.txt
				remove("group.txt");//delete old file
				rename("temp.txt","group.txt"); //renaming temp to group.txt
				fp=fopen("group.txt","r+");

				if(find==1){
					printf("Book is deleted\n");
					printf("Delete another Book(Y/N): ");
					fflush(stdin); // used to clear buffer
					scanf("%c", &repeat);
					printf("\nYou have entered: %c\n", repeat);
					if(repeat=='y'){
						deletebooks();
					}else{
						mainmenu();
					}
				}
			}else{
				mainmenu();
			}
		}
	}
}

//Function to Delete books
void searchbooks(){
	int d;
	int i;
	char decide;
	printf("1 ID Search\n");
	printf("2 Name Search\n");
	printf("Enter Your Choice: \n");
	fflush(stdin);
	scanf("%d", &i);
	printf("you have entered: %d\n", i);

	fp=fopen("group.txt","r+"); //open file for reading propose
	rewind(fp);   //move pointer at the begining of file
	switch(i){

		//Search by id
		case 1:{
			printf("Searching book using ID\n");
			printf("Enter book id: \n");
			fflush(stdin);
			scanf("%d",&d);
			while(fread(&a,sizeof(a),1,fp)==1){
				if(a.id==d){
					printf("Book Found \n");
					printf("ID: %d\n",a.id);
					printf("Name: %s\n",a.bookName);
					printf("Qantity: %d\n",a.quantity);
					find='1';
				}

			}
			//checks whether conditiion enters inside loop or not
			if(find!='1'){
				printf("No Record Found\n");
			}

			printf("Search Another(Y/N): \n");
			fflush(stdin); // used to clear buffer
			scanf("%c", &decide);
			printf("You have entered: %c \n", decide);
			if(decide=='y'){
				searchbooks();
			}else{
				mainmenu();
			}
		break;
		}

		//Search by name
		case 2:{
			char s[15];
			printf("Search Books By Name\n");
			printf("Enter Book Name: \n");
			fflush(stdin);
			scanf("%s",s);
			int d=0;
			while(fread(&a,sizeof(a),1,fp)==1){
				//satement below checks whether a.bookName is equal to s or not
				if(strcmp(a.bookName,(s))==0){

					printf("Book is Found\n");
					printf("ID:%d \n",a.id);
					printf("Name:%s \n",a.bookName);
					printf("Qantity:%d \n",a.quantity);

					d=1;
				}

			}

			if(d!=1){
				printf("No Record Found \n");
			}

			printf("Search Another(Y/N): \n");
			fflush(stdin); // used to clear buffer
			fflush(stdin);
			scanf("%c", &decide);
			printf("You have entered: %c\n", decide);
			if(decide=='y'){
				searchbooks();
			}else{
				mainmenu();
			}
			break;
		}
		default :
			printf("Search Another(Y/N): \n");
			fflush(stdin); // used to clear buffer
			scanf("%c", &decide);
			printf("You have entered: %c\n", decide);
			if(decide=='y'){
				searchbooks();
			}else{
				mainmenu();
			}
		}
		fclose(fp);
}


//edit information about book
void editbooks(){
	int c=0;
	int d;
	char repeat='y';

	printf("Edit Books Section\n");

	while(repeat=='y'){
		printf("Enter Book Id to be edited: \n");
		fflush(stdin);
		scanf("%d",&d);
		fp=fopen("group.txt","r+");
		while(fread(&a,sizeof(a),1,fp)==1){
			if(checkid(d)==0){
				printf("Book is found\n");
				printf("Enter new name: \n");
				fflush(stdin);
				scanf("%s",a.bookName);
				printf("Enter new quantity: \n");
				fflush(stdin);
				scanf("%d",&a.quantity);
				printf("Record Updated \n");
				fseek(fp,ftell(fp)-sizeof(a),0);
				fwrite(&a,sizeof(a),1,fp);
				fclose(fp);
				c=1;
			}
			if(c!=1){
				printf("No book found \n");
			}
		}
		printf("Search another(Y/N): \n");
		fflush(stdin); // used to clear buffer
		scanf("%c", &repeat);
		printf("You have entered: %c", repeat);
		if(repeat=='y'){
			searchbooks();
		}else{
			mainmenu();
		}
	}
	mainmenu();
}

//Function to view books
void viewbooks(){
    int i=0;

    fp=fopen("group.txt","r+");
    while(fread(&a,sizeof(a),1,fp)==1){
        printf("Book ID:");
        printf("%d\n",a.id);
        printf("Book Name:");
        printf("%s",a.bookName);
        printf("\nNumber of quantity:");
        printf("%d\n",a.quantity);
        i=i+a.quantity;
    }

    printf("Total numebr of books = %d\n",i);
    fclose(fp);
    mainmenu();
}

//Function to Issue books
void issuebooks(){
	int t;
	int x;
	char decide;


	printf("1. Issue Books\n");
	printf("2. Delete Issued Books\n");

	printf("Enter your Choice: ");
	fflush(stdin);
	scanf("%d", &x);
	printf("you have entered: %d", x);

	switch(x){
	case 1:{
		int d=0;
		char another='y';
		while(another=='y'){
			printf("\nIssue Book section\n");
			printf("Enter the Book Id: ");
			fflush(stdin);
			scanf("%d",&t);
			fp=fopen("group.txt","r");
			fs=fopen("bookIssue.txt","w+");

			//checks matching id
			if(checkid(t)==0){
				printf("The book record is available\n");
				printf("Unissued books in library are %d \n",a.quantity);
				printf("Book: %s",a.bookName);
				printf("\nEnter student name:");
				fflush(stdin);
				scanf("%s",a.stuName);
				printf("\nBook issued to ID= %d, student name- %s",a.id, a.stuName);
				fseek(fs,sizeof(a),SEEK_END); //End of file
				fwrite(&a,sizeof(a),1,fs);
				fclose(fs);
				d=1;
			}
			if(d==0){
			printf("\nBook not found");
			}
			printf("\nIssue another(Y/N):");
			fflush(stdin); // used to clear buffer
			scanf("%c", &decide);
			printf("You have entered: %c\n", decide);
			if(decide=='y'){
				issuebooks();
			}else{
				mainmenu();
			}
			fclose(fp);
		}
	break;
	}
	case 2:{

		int b;
		FILE *fg;  //pointer for temporary file to receive book from student
		char another='y';
		char decide;

		while(another=='y'){
			printf("Enter book ID to unissue: \n");
			scanf("%d",&b);
			fs=fopen("bookIssue.txt","r");
			while(fread(&a,sizeof(a),1,fs)==1){
				if(a.id==b){
					issuerecord();
					find=1;
				}
				if(find==1){
					printf("Do you want to unissue (Y/N)\n");
					fflush(stdin); // used to clear buffer
					scanf("%c", &decide);
					printf("You have entered: %c\n", decide);
					if(decide=='y'){
						fg=fopen("tempIssue.txt","wb+");
						rewind(fs);
						while(fread(&a,sizeof(a),1,fs)==1){
							if(a.id!=b){
								fseek(fs,0,SEEK_CUR);
								fwrite(&a,sizeof(a),1,fg);
							}
						}
						fclose(fs);
						fclose(fg);
						remove("bookIssue.txt");
						rename("tempIssue.txt","bookIssue.txt");
						printf("\nThe book is unissued\n");

					}

				}
				if(find!=1){
				printf("No Book was issued\n");
				}
			}
			printf("Unissue more books(Y/N): ");
			fflush(stdin); // used to clear buffer
			scanf("%c", &decide);
			printf("You have entered: %c\n", decide);
			if(decide=='y'){
				another='y';
			}else{
				another='n';
			}
		}
	}
	default:
	issuebooks();
	break;
	}
	mainmenu();
}

//Keeps track of student to whom the books are issued
void issuerecord(){
	char output[1000];

	fp=fopen("bookIssue.txt","r"); //new file created to read from it

	while(!feof(fp)){
		fgets(output, 100, fp);
		puts(output);
	}
	mainmenu();
}

//Function to check username and password
void Password(){

	char c;           //character type c used to store password
	char u;           //character type c used to store user
	int loop=1;

	printf("\nEnter password and username\n");


	printf("Username: ");
	scanf("%c", &u);


	printf("\nPassword: ");
	scanf("%c", &c);

	printf("\nyou have entered password: %c and username: %c\n", u, c);

	while(loop==1){
		if(u=='u' && c=='y' ){
			loop=0;//loop exiting criteria
			mainmenu();
		}else{
			printf("\nWrong Password and Username combination\m.Enter again.( HINT- user name is u and password is y)");
			Password();
		}
	}

}

//Function containing all the switch cases for the main display menu
void mainmenu(){
	int i;

	printf("\n");
    printf("Categories\n");
	printf("1) Add books\n");
	printf("2) Delete books\n");
	printf("3) Search books\n");
	printf("4) Issue books\n");
	printf("5) View books\n");
	printf("6) Edit books\n");
	printf("7) issue record\n");
	printf("8) Exit\n");
	printf("Enter your choice:\n");
	scanf("%d", &i);
	printf("You have entered: %d\n", i);


	switch(i){              // switch case functions
		case 1:
		addBooks();
		break;
		case 2:
		deletebooks();
		break;
		case 3:
		searchbooks();
		break;
		case 4:
		issuebooks();
		break;
		case 5:
		viewbooks();
		break;
		case 6:
		editbooks();
		break;
		case 7:
		issuerecord();
		break;
		case 8:{
		printf("Exiting\n");
		exit(0);
		}
		break;
		default:{
            printf("PLEASE ENTER THE CORRECT NUMBER!!!!\n");
            mainmenu();
        }
	}
}


int main(void){

	Password();

	return 0;
}
