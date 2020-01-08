#include <stdio.h>              /// Standard input output header...
#include<string.h>              /// String handling & various memory handling functions ...
#include<conio.h>               /// Console input and output ...
#include<windows.h>             /// For all of the functions in the Windows API ...(Application programming interface)

void d_mainmenu ();             /// Main menu...

void calculate_bill ();         /// Calculate the customer goods bill...
void add_goods ();              /// Add goods...
void edit_goods ();             /// Edit any goods...
void display ();                /// Display all the goods...
void search_information ();     /// Search the specific good...
void delete_goods ();           /// Delete the specific good...
void Exit();                    /// Close the program...


void design();                  /// Program design...

struct item object;             /// Create own datatype...

FILE *file1,*file2;             /// file1=object.txt, file2=temp.txt...

int main()                      /// Check password in this function...
{
    char password[100];
    int flag=0;
    for(int i=1; i<=3; i++)
    {
        printf("Enter the password : ");
        gets(password);
        if(strcmp(password,"p")==0)
        {
            printf("Login successful");
            flag++;
            printf("\nPress any key");
            getch();
            system("cls");
            d_mainmenu();
            break;
        }
        else
        {
            printf("\nInvalid password.Try again.\n\n");
            system("pause");
            system("cls");

        }
    }
    if(flag==0)
    {
        printf("You enter invalid password 3 times.\n");

        return 0;
    }

}

struct item
{
    char name[100];
    int code,SN;
    float rate,quantity;
};


void calculate_bill ()
{
    system("cls");
    char sell[10];
    float q,total=0,gtotal=0;
    int found=0;
    printf("\n");

    design();

    printf("\n                        +++Calculating your bill+++\n");
    printf("\n                  Enter which item you need with quantity...\n");

a:

    file1=fopen("object.txt","r");      /// Date file open to read...
    file2=fopen("temp.txt","w");        /// Data file open to write...
    rewind(file1);
    printf("                  !----------------------------------------!\n");
    printf("\n                         Enter the item name    : ");
    scanf("%s",&sell);
    printf("                         Enter the item quantity : ");
    scanf("%f",&q);
    printf("                               --------------\n");
    while(fscanf(file1,"%s %d %f %f\n",&object.name,&object.code,&object.rate,&object.quantity)!=EOF)
    {
        if(strcmp(sell,object.name)==0)     /// Scan and erase from file1 and save in file1..
        {
            if(object.quantity!=0)
            {
                total=object.rate*q;
                gtotal=gtotal+total;
                object.quantity=object.quantity-q;
                fprintf(file2,"%s\t\t%d\t%.2f\t\t%.2f\n",object.name,object.code,object.rate,object.quantity);
            }
            else
            {
                fprintf(file2,"%s\t\t%d\t%.2f\t\t%.2f\n",object.name,object.code,object.rate,object.quantity);
                printf("\n                         The quantity of %s : 0",object.name);
                printf("\n\n                         Press any key");
                getch();                            /// Get any character...
                system("cls");
                design();
            }
        }

        else
        {
            fprintf(file2,"%s\t\t%d\t%.2f\t\t%.2f\n",object.name,object.code,object.rate,object.quantity);
        }

    }

    char ans ;
    fflush(stdin);
    printf("\n                       Press \"y\" to ADD & \"n\" to FINISH\n");
    printf("                         Choice your option y/n : ");
    scanf("%c",&ans);
    if(ans=='n')
    {
        printf("\n                  ---> The total amount is : %.2f <---\n",gtotal);
        printf("\n                  !----------------------------------------!\n");
        printf("                        Press any key to Main menu....");
        getch();
        fclose(file1);
        fclose(file2);
        remove("object.txt");               /// Remove file1=object.txt...
        rename("temp.txt","object.txt");    /// Rename the temp.txt to object.txt...

        system("cls");                      /// Clear screen...
        d_mainmenu();
    }

    else if (ans == 'y')
    {
        fclose(file1);
        fclose(file2);
        remove("object.txt");               /// Remove file1=object.txt...
        rename("temp.txt","object.txt");    /// Rename the temp.txt to object.txt...

        goto a;
    }


}

void add_goods ()
{
    system("cls");
    printf("\n");

    design();

    printf("\n                                Add Goods\n");
    struct item object[100];
    int number;
    file1=fopen("object.txt","a");      /// File open to append...
    printf ("                       How many item do you want to add ?\n\n");
    printf("                                  -> ");
    scanf ("%d",&number);
    printf("\n                !----------------------------------------!\n");
    for (int i=1; i<=number; i++)
    {
        printf ("\n                        Enter item Name    : ");
        scanf("%s",&object[i].name);
        fflush (stdin);
        fprintf(file1,"%s\t\t",object[i].name);     /// Save name in file1....
        printf("                        Enter code         : ");
        scanf("%d",&object[i].code);
        fprintf(file1,"%d\t",object[i].code);       /// Save code in file1....
        printf ("                        Enter item rate    : ");
        scanf ("%f",&object[i].rate);
        fprintf(file1,"%.2f\t",object[i].rate);     /// Save rate in file1....
        printf ("                        Enter item quantity: ");
        scanf ("%f",&object[i].quantity);
        fprintf(file1,"%.2f",object[i].quantity);   /// Save quantity in file1....
    }
    fclose(file1);
    printf("\n                !----------------------------------------!\n");
    printf("\n\n                       Press any key to Main menu....");
    getch();
    system("cls");
    d_mainmenu();
}

void edit_goods ()
{
    system("cls");

    char x[100];
    int n,found=0,i=1;
    printf("\n");

    design();

    printf("\n                 Enter item name which do you want to edit.....\n");
    printf("\n                          Enter the item name : ");
    scanf("%s",&x);
    file1=fopen("object.txt","r");      /// File open to read...
    file2=fopen("temp.txt","a");        /// File open to append...
    rewind(file1);
    while(fscanf(file1,"%s %d %f %f\n",&object.name,&object.code,&object.rate,&object.quantity)!=EOF)
    {
        if(strcmp(object.name,x)==0)
        {
            found=1;
            break;
        }
    }
    if(found==1)
    {
        printf("\n     SN\t  ITEM NAME\tCODE\tRATE\t\tQUANTITY\tTOTAL\n\n");
        printf("      %d\t  %s\t\t%d\t%.2f\t\t%.2f\t\t%.2f",i,object.name,object.code,object.rate,object.quantity,object.rate*object.quantity);
    }

    printf("\n\n\n                      Which part do you want to change\n");
    printf("                                1 - RATE\n");
    printf("                                2 - QUANTITY\n");
    printf("                           Choice your option 1/2 : ");
    scanf("%d",&n);
    switch(n)
    {
    case 1 :

        system("cls");
        design();
        printf("\n\n");
        printf("\n                               CHANGE RATE\n\n");
        float newrate;


        printf("\n                            Enter new rate : ");
        scanf("%f",&newrate);
        printf("\n\n                               RATE CHANGED\n");
        rewind(file1);
        while(fscanf(file1,"%s %d %f %f\n",&object.name,&object.code,&object.rate,&object.quantity)!=EOF)
        {
            if(strcmp(x,object.name)==0)
            {
                object.rate=newrate;    /// Scan and save new rate in file2
                fprintf(file2,"%s\t\t%d\t%.2f\t\t%.2f\n",object.name,object.code,object.rate,object.quantity);
            }
            else                        /// Data save in file2...
                fprintf(file2,"%s\t\t%d\t%.2f\t\t%.2f\n",object.name,object.code,object.rate,object.quantity);

        }
        fclose(file1);                      /// File close...
        fclose(file2);
        remove("object.txt");               /// Remove file1=object.txt...
        rename("temp.txt","object.txt");    /// Rename temp.txt to object.txt...
        printf("\n\nPress any key to Main menu....");
        getch();
        system("cls");
        d_mainmenu();

        break;

    case 2 :

        system("cls");
        design();
        printf("\n                               CHANGE QUANTITY\n\n");
        float newquantity,oldquantity=0;
        printf("\n                               Add quantity : ");
        scanf("%f",&newquantity);
        printf("\n\n                               QUANTITY CHANGED\n");

        rewind(file1);
        while(fscanf(file1,"%s %d %f %f\n",&object.name,&object.code,&object.rate,&object.quantity)!=EOF)
        {
            if(strcmp(x,object.name)==0)
            {                       /// Scan and add new quantity...
                object.quantity=object.quantity+newquantity;
                fprintf(file2,"%s\t\t%d\t%.2f\t\t%.2f\n",object.name,object.code,object.rate,object.quantity);
            }
            else
                fprintf(file2,"%s\t\t%d\t%.2f\t\t%.2f\n",object.name,object.code,object.rate,object.quantity);

        }
        fclose(file1);                      /// File close...
        fclose(file2);
        remove("object.txt");               /// Remove file1=object.txt...
        rename("temp.txt","object.txt");    /// Rename temp.txt to object.txt...
        printf("\n\nPress any key to mainmenu");
        getch();                            /// Get any character...
        system("cls");
        d_mainmenu();

        break;
    }
}
void display ()
{
    system("cls");
    int i=1;
    file1=fopen("object.txt","r");
    printf("\n");

    design();

    printf("\n                               TOTAL ITEM LIST\n");
    printf("    !-----------------------------------------------------------------------!");
    printf("\n     SN\t  ITEM NAME\tCODE\tRATE\t\tQUANTITY\tTOTAL\n\n");
    rewind(file1);
    while(fscanf(file1,"%s %d %f %f",&object.name,&object.code,&object.rate,&object.quantity)!=EOF)
    {
        printf("      %d\t  %s\t\t%d\t%.2f\t\t%.2f\t\t%.2f",i,object.name,object.code,object.rate,object.quantity,object.rate*object.quantity);
        printf("\n");                   /// Scan and display all item...
        i++;
    }
    fclose(file1);                      /// Close file1...
    printf("    !-----------------------------------------------------------------------!");
    printf("\n\n                    Press any key to Main menu.....");
    getch();                            /// Get any character...
    system("cls");
    d_mainmenu();
}

void search_information ()
{

a:

    system("cls");
    file1=fopen("object.txt","r");          /// File open to read...
    char x[10];
    int i=1;
    int found=0;
    printf("\n");

    design();

    printf("\n                 Enter item name which you want to search....\n");
    printf("\n                             Item name : ");
    scanf("%s",&x);                         /// Get char for compare...
    printf("    !-----------------------------------------------------------------------!");
    printf("\n                            Your searching item....\n\n\n");
    rewind(file1);                          /// Set the cursore position to the begining...

    while(fscanf(file1,"%s %d %f %f",&object.name,&object.code,&object.rate,&object.quantity)!=EOF)
    {
        if(strcmp(x,object.name)==0)
        {                           /// Scan file1 and compare...
            found=1;
            break;
        }
    }
    if(found==1)                    /// Display the compared item...
        printf("\n     SN\t  ITEM NAME\tCODE\tRATE\t\tQUANTITY\tTOTAL\n\n");
    if(found==1)
        printf("      %d\t  %s\t\t%d\t%.2f\t\t%.2f\t\t%.2f",i,object.name,object.code,object.rate,object.quantity,object.rate*object.quantity);
    else
    {
        printf("                              ITEM NOT FOUND\n\n");
        printf("\n    !-----------------------------------------------------------------------!");
        printf("                         Press any key to search again....");
        getch();
        goto a;
    }
    fclose(file1);                            /// File close...
    printf("\n    !-----------------------------------------------------------------------!");
    printf("\n\n                       Press any key to Main menu.....");
    getch();                                  /// Get any character...
    system("cls");
    d_mainmenu();
}
void delete_goods ()
{
    system("cls");
    char x[100];
    printf("\n");

    design();

    printf("\n                             Delete option....\n");
    printf("\n                          Enter the item name : ");
    scanf("%s",&x);
    fflush(stdin);
    file1=fopen("object.txt","r");      /// File1 open to read...
    file2=fopen("temp.txt","a");        /// File2 open to append...
    rewind(file1);
    while(fscanf(file1,"%s %d %f %f\n",&object.name,&object.code,&object.rate,&object.quantity)!=EOF)
    {
        if(strcmp(x,object.name)==0)
        {               /// Scan and not save in file1
            printf("\n\n                                Item deleted");
        }
        else            /// Save in file2
            fprintf(file2,"%s\t\t%d\t%.2f\t%.2f",object.name,object.code,object.rate,object.quantity);
    }
    fclose(file1);
    fclose(file2);
    remove("object.txt");
    rename("temp.txt","object.txt");
    printf("\n\n                      Press any key to Main menu.....");
    getch();
    system("cls");
    d_mainmenu();
}


void design()
{
    printf("                  !----------------------------------------!\n");
    printf ("                  ! --::..INFINITY DEPARTMENTAL STORE..::--!\n");
    printf("                  !----------------------------------------!\n");

}
void Exit()
{
    system("cls");                  /// Program stop...
    design();
    printf ("\n\n                       ..........PROGRAM EXIT..........\n\n");
    exit(0);
}

void d_mainmenu ()
{
    int number;
    printf("\n");               /// Display the mainmenu in this function...

    design();

    printf ("\n                        !--:::_____:::--:::_____:::--!\n");
    printf ("                         !                          !      \n");
    printf ("                         !    1.CALCULATE BILL      !\n");
    printf ("                         !    2.ADD GOODS           !\n");
    printf ("                         !    3.EDIT GOODS          !\n");
    printf ("                         !    4.DISPLAY             !\n");
    printf ("                         !    5.SEARCH INFORMATION  !\n");
    printf ("                         !    6.DELETE GOODS        !\n");
    printf ("                         !    7.EXIT                !\n");
    printf ("                         !                          !      \n");
    printf ("                        !--:::_____:::--:::_____:::--!\n");
    printf ("\n                            Enter your choice : ");
    scanf ("%d",&number);
    switch (number)
    {
    case 1:
        calculate_bill ();
        break;
    case 2:
        add_goods ();
        break;
    case 3:
        edit_goods ();
        break;
    case 4:
        display ();
        break;
    case 5:
        search_information ();
        break;
    case 6:
        delete_goods ();
        break;
    case 7:
        Exit();
        break;
    default :
        printf ("try again!!!!\n");
    }
}

