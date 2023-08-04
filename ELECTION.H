// its election admin panel 
//include necessary files 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Define a structure to store current valid user ID parameters
struct valid_user_id {
    int year;
    char branch[6]; //a string to store branch 
    int totalvoter;
};
// Define a typedef for the candidate structure
typedef struct candidate {
    int cid;
    char cname[20];
    int votes;

}candidate;

// Declare global variables
struct valid_user_id valid_user_id;
candidate candidatearray[20];
int number_of_candidates;
char student_votes[200];
// Function to extract year from user ID that is a string For example, userID:2019btecs00094 year:2019
int extract_year(char userID[15]) {
    //length is 15 becuse of null character at the end 
    int year = 0;
    int temp;
    for(int i=0;i<4;i++) {
        temp=userID[i];
        year = (year*0)+(temp-48); // treating temp as asci value 

    }
    return year;


}
// Function to extract roll number from user ID
// Takes a user ID as input and returns the extracted roll number
int extract_rollno(char userID[15]) {
    int rollno=0;
    int temp;
    for(int i=9; i<14; i++) {
        temp = userID[i];
        rollno =(rollno*10)+(temp-48);

    }
    return rollno;

}
// Function to check whether the branch code in the user ID matches the global branch code
// Takes a user ID as input and returns 1 if the branch codes match, 0 otherwise
int check_branch_code(char userID[15]) {
    char branch_code[6];
    for(int i=4;i<9;i++) {
        branch_code[i-4]=userID[i];
    }
    branch_code[5]='\0';
    if(strcmp(branch_code,valid_user_id.branch)==0) {
        return 1;
        
    }
    else
    {
        return 0;
    }
}
// Function to authenticate the administrator
// Returns 1 if the authentication is successful, 0 otherwise
int admin_auth() {
    char username[15];
    char password[6];
    printf("\n Enter username: ");
    scanf("%c",username);
    if((strcmp(username,"Admin"))!=0)
    return 0;
    else {
        printf("\n Enter password: ");
        int i = 0;
        for(i=0;i<5;i++) {
            password[i]= getchar();
            printf("%s","*");
        }
        password[i]='\0';
        if((strcmp(password,"admin"))!=0)
        return 0;

        
    }
    return 1;
}
// Function to ban user IDs
// Creates a "Banned.txt" file and bans user IDs by marking their votes as '$'
void ban_userid() {
           printf("\n creating baned.txt....\n");
           FILE *file = fopen("baned.txt","w");
           if(file == NULL) {
            printf("banned.txt is not created\n");
            fclose(file);
            return;
           }
           
            printf("just print last rollno to ban \n press 0 to exit\n");
            int input;
            while (1)
            {
               printf("enter number: ");
               scanf("%d",&input);
               if(input == 0)
               break;
               student_votes[input-1]= '$';
               fprintf(file,"%d\n", input);


            }
            fclose(file);
            printf("created successfully\n");

}
// Function to create candidate files
// Creates separate files for each candidate with initial vote count and candidate name
void createcandidatefiles() {
           printf("creating candidate files\n");
           FILE *fb;
           char filename[20];
           for(int i =1;i<number_of_candidates;i++) {
            sprintf(filename,"candidate%d.txt",i);
             fb = fopen(filename,"w");
             fprintf (fb , "0\n%s",candidatearray[i-1].cname);
             fclose(fb);
           }
           printf("file created successfully\n");

}
// Function to delete an illegal vote
// Decrements the vote count for the candidate associated with the vote
// Removes the vote from the candidate's file and updates the candidate's vote count
void deleteilligalvote(char userID[15]) {
    FILE *fp,*fcp;
    char filename[20];
    char line[20];
    int location = extract_rollno(userID);
    sprintf(filename,"candiate%d.txt",candidatearray[student_votes[location-1]-49].cid);
    candidatearray[student_votes[location-1]-49].votes--;
    student_votes[location-1] = '0';
    if((fp = fopen(filename,"r"))==NULL) {
        printf("\nfile cann't be opened ..operation failed");
        return;
    }
    printf("\ndeleting in progress\n");
    if((fcp = fopen("temp.txt","w"))== NULL) {
        printf("\nfile cannot be opened operation failed\n");
        return;
    }
    while(feof(fp)) {
        fscanf(fp,"%s",line);
        fprintf(fcp,"%s\n",line);
    }
    fclose(fp);
    fclose(fcp);
    if((fp = fopen(filename,"w"))==NULL) {
        printf("\n file cannot be opened,operation failed\n");
        return;
    }
    int numFromfile;
    char cnameformfile[20];
    fcp = fopen("tmp.txt","r");
    fscanf(fcp,"%d",&numFromfile);
    fprintf(fp,"%d",numFromfile);
    fscanf(fcp,"%s",cnameformfile);
    fprintf(fp,"\n%s",cnameformfile);
    while (!feof)
    {
        fscanf(fcp,"%d",&numFromfile);
        if(numFromfile!=location) {
            fprintf(fp,"\n%d",numFromfile);
        }
    }
    fclose(fp);
    fclose(fcp);
    remove("temp.txt");
    printf("\nVote deleted successfully\nPress any key to continue...");
    getchar();
}
// Function to get the winner of the election
// Returns the candidate ID of the winner, or -1 in case of a tie
int getwinner() {
    int maxV= -1;
    int winnercid;
    for(int i = 0;i<number_of_candidates;i++) {
       if(candidatearray[i].votes >maxV) {
        winnercid=candidatearray[i].cid;
        maxV = candidatearray[i].votes;
       } 
       else if(candidatearray[i].votes==maxV) {
        return -1;
       }
    }
    return winnercid;
}
// Function to initiate a new election
// Prompts the user to enter election details, candidate names, and number of candidates
void initiatnewelection() {
    printf("new election initiation\n");
    printf("\nelection for which year: ");
    scanf("%d",&valid_user_id.year);
    printf("Enter branch code:");
    scanf("%s",valid_user_id.branch);
    printf("enter max rollno");
    scanf("%d",&valid_user_id.totalvoter);
    printf("Enter number of canduates: ");
    scanf("%d",&number_of_candidates);
    for(int i=0;i<valid_user_id.totalvoter;i++) {
        student_votes[i] = '0';
    }
    for(int i=0; i<number_of_candidates;i++) {
        candidatearray[i].cid = i+1;
        printf("Enter name of candidate %d: ",i+1);
        scanf("%s",candidatearray[i].cname);
        candidatearray[i].votes= 0;


    }
    return;

}
// Function to save election information in a file
// Writes the current valid ID parameters and number of candidates to "ElectionInfo.txt" file
void saveelectioninfoinfile() {
    printf("Saving Election Info in File...\n");
    FILE *fp = fopen("Electioninfo.txt","w");
    if(fp==NULL)
    {
        printf("\nError in file creation\n");
        fclose(fp);
        return;
    }
    fprintf( fp,"%d\n%s\n%d\n%d",valid_user_id.year,valid_user_id.branch,valid_user_id.totalvoter,number_of_candidates

    );
    fclose(fp);
    printf("\nfile close succussfully");

}

// Function to load election information from a file
// Reads the current valid ID parameters and number of candidates from "ElectionInfo.txt" file
// Loads candidate information and student votes from separate files
void loadelectioninfofromfile() {
    FILE *f1,*f2,*f3;
    f1 = fopen("Electioninfo.txt","r");
    if(f1==NULL) 
      printf("File not exist");
    fscanf(f1,"%d",&valid_user_id.year);
    fseek(f1,2,SEEK_CUR); //it is used to move file pointer 
    fscanf(f1,"%s",valid_user_id.branch);
    fseek(f1,2,SEEK_CUR);
    fscanf(f1,"%d",&valid_user_id.totalvoter);
    fseek(f1,2,SEEK_CUR);
    fscanf(f1,"%d",&number_of_candidates);
    fclose(f1);
    //load candiate info and student votes
    for(int i =0;i<valid_user_id.totalvoter; i++) {
        student_votes[i] = '0';

    }
    for(int i = 0; i<number_of_candidates; i++) {
        int location;
        char filename[20];
        sprintf(filename,"candiate%d.txt",i);
        f2 = fopen(filename,"r+");
        candidatearray[i-1].cid =i;
        fscanf(f2,"%d",&candidatearray[i-1].votes);
        fscanf(f2,"%s",candidatearray[i-1].cname);
        while (!feof(f2))
        {
            fscanf(f2,"%d",&location);
            student_votes[location-1] = i+48;

        }
        fclose(f2);
        
    }
    //load banned votes
    int location;
    f3 = fopen("banned,txt","r+");
    while (!feof(f3))
    {
        fscanf(f3,"%d",&location);
        student_votes[location-1] = '$';
    }
    fclose(f3);


}

// Function for the administrator panel
// Allows the administrator to authenticate, perform various actions, and view the election results
void adminpanel() {
    while(1) {
        if(admin_auth()!=1) {
            printf("\n wrong username or password\n");
            break;
        }
        printf("\n\nLOGGED IN SUCCESSFULLY (Press Enter)");
        getchar();
        while (1)
        {
           char inputID[15];
           char input ;
           char baninp;
           int winercid;
           int totalvotednow=0;
           printf("\n1.New Election\n2.Continue Previous Election\n3.Delete Illegal Vote\n4.Ban User IDs\n5.Result\n6.Logout\nOption:");
           scanf(" %c",&input);
           switch (input)
           {
           
           case '1':
           initiatnewelection();
           saveelectioninfoinfile();
           createcandidatefiles();
            break;
            case '2':
            loadelectioninfofromfile();

            break;
            case '3':
            printf("\n Enter user id to its vote: \n");
            scanf("%s",inputID);
            deleteilligalvote(inputID);
            break;
            case '4':
            printf("Do you want to ban particular ID's?\nPress 1 if yes or any other key to continue...");
            scanf("%c",&baninp);
            if(baninp=='1') {
                ban_userid();
            }

            break;
            case '5':
            winercid = getwinner();
            if(winercid != -1) {
                printf("\nWinner is %s with %d votes\n",candidatearray[winercid-1].cname,candidatearray[winercid-1].votes);
            }
            else {
                printf("\nits a tie");
            }
            printf("\n Full result\n");
            for(int i=0; i<number_of_candidates; i++) {
                totalvotednow+=candidatearray[i].votes;
                printf("%d. %s -> %d votes\n",candidatearray[i].cid,candidatearray[i].cname,candidatearray[i].votes);
            }
            printf("\n Voting percentage: %d %%\n\n",(totalvotednow*100)/valid_user_id.totalvoter);
            break;
            case '6':
            return;
            break;
           
           default:
           printf("invalid option");
           getchar();
          
           }


        }
        
    }
}

// Function to check if a user ID is valid
// Takes a user ID as input and returns 1 if it is valid, 0 otherwise
 int isvalidId(char userID[15]) {
     if(strlen(userID)!=15) {
        return 0;
     }
     int inputedyear = extract_year(userID);
     int inputedrollno = extract_rollno(userID);
     if(inputedyear!=valid_user_id.year|| check_branch_code(userID)!=1 ||inputedrollno>valid_user_id.totalvoter)
        return 0;
    
    return 1;

 }

// Function to check if a user ID has already voted
// Takes a user ID as input and returns 1 if the ID has voted, 0 otherwise
int isvoted(char userID[15]) {
    int location = extract_rollno(userID);
    if(student_votes[location-1]=='0') {
        return 0;
        }
    else {
        return 1;
    }
}

// Function to check if a user ID is banned
// Takes a user ID as input and returns 1 if the ID is banned, 0 otherwise
int isbanned(char userID[15]) {
   int location = extract_rollno(userID);
   if(student_votes[location-1]=='$')
      return 1;
   else 
      return 0;

}

// Function to save a vote
// Takes a user ID and the candidate's vote as input
// Updates the studentVotes array and the candidate's vote count in their respective files
void savevote(char userID[15], char voteinput) {
    char filename[20];
    sprintf(filename,"candiate%d.txt",voteinput-48);
    FILE *fp = fopen(filename,"r+");
    int location = extract_rollno(userID);
    student_votes[location-1] = voteinput;
    candidatearray[voteinput-49].votes++;
    fseek(fp,0,SEEK_SET);
    fprintf(fp,"%d\n",candidatearray[voteinput-49].votes);
    fseek(fp,0,SEEK_END);
    fprintf(fp,"\n%d",location);
    fclose(fp);

}

// Function for the student panel
// Allows students to enter their user ID, view candidate names, and cast their votes

void studentpanel() {
    char userId[15];
    char voteinput;
    while (1)
    {
        printf("\n\n to exit press 0");
        printf("\nenter userID: ");
        scanf("%s",userId);
        if(strcmp(userId,"0")==0)
            return;
        if(isvalidId(userId)!=1) {
            printf("\n invalid userid(press enter)");
            getchar();
            continue;
        }
        if(isvoted(userId)!=0) {
            printf("\n  Your PRN entered is already voted\n  Contact Admin for furthur query");
            getchar();
            continue;
        }
        printf("\n\n  Candidates for election:");
        for(int i=0;i<number_of_candidates; i++){
            printf("\n %d.%s",i+1,candidatearray[i].cname);
        }
        printf("\n\n  Your Vote(Enter Number):");
        voteinput=getchar();
        printf("*");
        if(voteinput-48 < 1|| voteinput-48>number_of_candidates) {
             printf("\nInvalid Vote\nTry Again...");
            getchar();
            continue;
        }
        savevote(userId,voteinput);
        printf("\n\nThanks for your precious vote(Press Enter)");
        getchar();

    }
    
}




























