//for user define libraries you need to add them with ""
#include"ELECTION.H"

int main() {
    while (1)
    {
        printf("\n\t\t\t   1.Student panel \n\t\t\t   2.Admin panel \n\t\t\t   3.Exit \n\t\t\t   Option:");
        char input;
        scanf(" %c",&input);
        switch (input)
        {
        case '1':
            studentpanel();
            break;
        case '2':
           adminpanel();
            break;
        case '3':
           return 0;
        
        default:
            printf("\ninvalid option");
            getchar();
        }


    }
    
    return 0;
}