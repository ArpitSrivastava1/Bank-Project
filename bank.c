#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
struct autonumber
{
    int ano;
    int tid;
};
struct account
{
    int ano;
    char name[50];
    int pno;
    int adhaar;
    char add[50];
    char type[20];
    int bal;
    int pass;
};
struct transact
{
    int ano;
    int tid;
    int w;
    int d;
    int bal;
    char status[30];

};
int transid()
{
   FILE *fp;
   FILE *temp;
   int x;
   struct autonumber a;
   fp=fopen("auto.dat","rb");
   temp=fopen("temp.dat","wb");
   fread(&a,1,sizeof(struct autonumber),fp);
   x=a.tid++;
   fwrite(&a,1,sizeof(struct autonumber),temp);
   fclose(fp);
   fclose(temp);
   rename("temp.dat","auto.dat");
   return x;
}
int accno()
{
   FILE *fp;
   FILE *temp;
   int x;
   struct autonumber a;
   fp=fopen("auto.dat","rb");
   temp=fopen("temp.dat","wb");
   fread(&a,1,sizeof(struct autonumber),fp);
   x=a.ano++;
   fwrite(&a,1,sizeof(struct autonumber),temp);
   fclose(fp);
   fclose(temp);
   rename("temp.dat","auto.dat");
   return x;
}
int createaccount()
{
    struct account acc;
    FILE *fp;
    fp=fopen("account.dat","ab");
    if (fp==NULL)
    {
        printf("cannot open file!");
    }
    else{
    printf("enter details:\n");
    acc.ano=accno();
    printf("your account no. is: %d\n",acc.ano);
    printf("enter name: ");
    fflush(stdin);
    gets(acc.name);
    printf("enter pno: ");
    scanf("%d",&acc.pno);
    printf("enter address: ");
    fflush(stdin);
    gets(acc.add);
    printf("enter adhaar no.: ");
    scanf("%d",&acc.adhaar);
    printf("enter balance: ");
    scanf("%d",&acc.bal);
    printf("enter type of account(saving/current): ");
    fflush(stdin);
    gets(acc.type);
    fflush(stdin);
    printf("Set password:");
    scanf("%d",&acc.pass);
    fwrite(&acc,1,sizeof(struct account),fp);
    fclose(fp);}
    return (0);
}
void displayaccount()
{
    FILE *fp;
    struct account acc;
    int accno,pass,count=0;
    printf("enter accno.:");
    scanf("%d\n",&accno);
    fp=fopen("account.dat","rb");

    while (fread(&acc,1,sizeof(struct account),fp))
    {
        if (acc.ano==accno)
        {
            printf("Enter password:");
            scanf("%d",&pass);
            count=1;
            if (acc.pass==pass)
            {
              printf(" ano     name     phoneno.   adhaar    address    balance      type");
              printf("\n");
              printf("%d   %s   %d   %d   %s   %d   %d   %s",acc.ano,acc.name,acc.pno,acc.adhaar,acc.add,acc.bal,acc.type);
              printf("\n");
            }
            else{
                printf("wrong password.Diverting you to the home page");
                }
        }
    }
    if (count==0)
    {
        printf("account doesn't exist!");
    }
    fclose(fp);

};
void displayall()
{
    FILE *fp;
    struct account acc;
    fp=fopen("account.dat","rb");
    printf(" ano     name    phoneno.   adhaar    address    balance   debitno     type/n");
    while (fread(&acc,1,sizeof(struct account),fp))
    {
        printf("%d   %s   %d   %d   %s   %d   %d   %s /n",acc.ano,acc.name,acc.pno,acc.adhaar,acc.add,acc.bal,acc.type);
    }
    fclose(fp);

};
void delaccount()
{
    FILE *fp;
    FILE *temp;
    struct account acc;
    int accno,pass,count=0;
    printf("enter accno.:");
    scanf("%d\n",&accno);
    fp=fopen("account.dat","rb");
    temp=fopen("temp.dat","wb");
    while (fread(&acc,1,sizeof(struct account),fp))
    {
        if (acc.ano==accno)
        {
            printf("Enter password:");
            scanf("%d",&pass);
            count=1;
            if (acc.pass==pass)
            {
              printf("Account sucessfully deactivated!");
            }
            else{
                printf("wrong password.Diverting you to the home page");
                fwrite(&acc,1,sizeof(struct account),temp);
            }
        }
        else{
            fwrite(&acc,1,sizeof(struct account),temp);
        }

    }
    if (count==0)
    {
        printf("account doesn't exist!");
    }
    fclose(fp);
    fclose(temp);
    rename("temp.dat","account.dat");

};
void editaccount()
{
    FILE *fp;
    FILE *temp;
    struct account acc;
    int accno,pass,i,x,count=0;
    char y[50];
    printf("enter accno.:");
    scanf("%d\n",&accno);
    fp=fopen("account.dat","rb");
    temp=fopen("temp.dat","wb");
    while (fread(&acc,1,sizeof(struct account),fp))
    {
        if (acc.ano==accno)
        {
            printf("Enter password:");
            scanf("%d",&pass);
            count=1;
            if (acc.pass==pass)
            {
              printf("select to edit details:\n");
              printf("1) Name of Account Holder\n");
              printf("2) Contact No.\n");
              printf("3) Adhaar linked with account\n");
              printf("4) Address\n");
              printf("5) Change password\n");
              printf("Enter your choice: ");
              scanf("%d",&i);
              switch(i)
              {
               case 1:
                  printf("Enter New Name: ");
                  fflush(stdin);
                  gets(y);
                  strcpy(acc.name,y);
                  break;
              case 2:
                  printf("Enter new contact No.: ");
                  scanf("%d",&x);
                  acc.pno=x;
                  break;
              case 3:
                  printf("Enter adhaar no.: ");
                  scanf("%d",&x);
                  acc.adhaar=x;
                  break;
              case 4:
                  printf("Enter New Address: ");
                  fflush(stdin);
                  gets(y);
                  strcpy(acc.add,y);
                  break;
              case 5:
                  printf("Enter new password: ");
                  scanf("%d",&x);
                  acc.pass=x;
                  break;
             }
             fwrite(&acc,1,sizeof(struct account),temp);
            }
            else{
                printf("wrong password.Diverting you to the home page");
                fwrite(&acc,1,sizeof(struct account),temp);
            }
        }
        else{
            fwrite(&acc,1,sizeof(struct account),temp);
        }

    }
    if (count==0)
    {
        printf("account doesn't exist!");
    }
    fclose(fp);
    fclose(temp);
    rename("temp.dat","account.dat");

};
void withdraw()
{
    FILE *fp;
    FILE *fpt;
    FILE *temp;
    struct account acc;
    struct transact trans;
    int accno,pass,w,count=0;
    printf("enter accno.:");
    scanf("%d\n",&accno);
    fp=fopen("account.dat","rb");
    fpt=fopen("transact.dat","ab");
    temp=fopen("temp.dat","wb");

    while (fread(&acc,1,sizeof(struct account),fp))
    {
        if (acc.ano==accno)
        {
            printf("Enter password:");
            scanf("%d",&pass);
            count=1;
            if (acc.pass==pass)
            {
              printf("Enter withdrawl amount: ");
              scanf("%d",&w);
              trans.ano=acc.ano;
              trans.tid=transid();
              trans.w=w;
              trans.d=0;
              if (w<acc.bal)
              {
                  acc.bal=acc.bal-w;
                  trans.bal=acc.bal;
                  strcpy(trans.status,"Confirmed");
                  printf("transaction successful");
                  printf("your transaction recipt:-\n");
              }
              else
              {
                  trans.bal=acc.bal;
                  strcpy(trans.status,"Declined");
                  printf("transaction declined! \nYou don't have enough balance\nSorry for the inconvienience\nYour transaction Recipt:-\n");
              }
              printf("ano   tid   withdraw   deposit   Balance   Status");
              printf("%d   %d   %d   %d   %d   %s",trans.ano,trans.tid,trans.w,trans.d,trans.bal,trans.status);
              fwrite(&trans,1,sizeof(struct transact),fpt);

            }
            else{
                printf("wrong password.Diverting you to the home page");
                }
        }
        fwrite(&acc,1,sizeof(struct account),temp);
    }
    if (count==0)
    {
        printf("account doesn't exist!");
    }
    fclose(fp);
    fclose(fpt);
    fclose(temp);
    rename("temp.dat","account.dat");
};
void deposit()
{
    FILE *fp;
    FILE *fpt;
    FILE *temp;
    struct account acc;
    struct transact trans;
    int accno,pass,d,count=0;
    printf("enter accno.:");
    scanf("%d\n",&accno);
    fp=fopen("account.dat","rb");
    fpt=fopen("transact.dat","ab");
    temp=fopen("temp.dat","wb");

    while (fread(&acc,1,sizeof(struct account),fp))
    {
        if (acc.ano==accno)
        {
            printf("Enter password:");
            scanf("%d",&pass);
            count=1;
            if (acc.pass==pass)
            {
              printf("Enter Deposit amount: ");
              scanf("%d",&d);
              trans.ano=acc.ano;
              trans.tid=transid();
              trans.w=0;
              trans.d=d;
              acc.bal=acc.bal+d;
              trans.bal=acc.bal;
              strcpy(trans.status,"Confirmed");
              printf("transaction successful");
              printf("your transaction recipt:-\n");
              printf("ano   tid   withdraw   deposit   Balance   Status");
              printf("%d   %d   %d   %d   %d   %s",trans.ano,trans.tid,trans.w,trans.d,trans.bal,trans.status);
              fwrite(&trans,1,sizeof(struct transact),fpt);

            }
            else{
                printf("wrong password.Diverting you to the home page");
                }
        }
        fwrite(&acc,1,sizeof(struct account),temp);
    }
    if (count==0)
    {
        printf("account doesn't exist!");
    }
    fclose(fp);
    fclose(fpt);
    fclose(temp);
    rename("temp.dat","account.dat");
}
void passbook()
{
    FILE *fp;
    FILE *fpt;
    struct account acc;
    struct transact trans;
    int accno,pass,d,count=0;
    printf("enter accno.:");
    scanf("%d\n",&accno);
    fp=fopen("account.dat","rb");
    fpt=fopen("transact.dat","rb");


    while (fread(&acc,1,sizeof(struct account),fp))
    {
        if (acc.ano==accno)
        {
            printf("Enter password:");
            scanf("%d",&pass);
            count=1;
            if (acc.pass==pass)
            {
                printf("Your passbook:-\n");
                printf("ano   tid   withdraw   deposit   Balance   Status");
                while (fread(&trans,1,sizeof(struct account),fpt))
                {
                    if(trans.ano==accno)
                    {
                        printf("%d   %d   %d   %d   %d   %s",trans.ano,trans.tid,trans.w,trans.d,trans.bal,trans.status);
                    }
                }
            }
            else{
                printf("wrong password.Diverting you to the home page");
                }
        }
    }
    if (count==0)
    {
        printf("account doesn't exist!");
    }
    fclose(fp);
    fclose(fpt);
}
/*void revtrans()
{
    FILE *fp;
    FILE *fpt;
    FILE *temp;
    struct account acc;
    struct transact trans;
    struct transact trans1;
    int accno,pass,id,x,count=0;
    printf("enter accno.:");
    scanf("%d\n",&accno);
    fp=fopen("account.dat","rb");
    fpt=fopen("transact.dat","rb+");
    temp=fopen("temp.dat","wb");

    while (fread(&acc,1,sizeof(struct account),fp))
    {
        if (acc.ano==accno)
        {
            printf("Enter password:");
            scanf("%d",&pass);
            count=1;
            if (acc.pass==pass)
            {
              Cprintf("Enter  Transaction Id: ");
              scanf("%d",&id);
              while (fread(&trans,1,sizeof(struct account),fp))
              {
                  if (trans.tid==id)
                  {
                      trans1.ano=acc.ano;
                      trans1.tid=transid();
                      trans1.w=trans.d;
                      trans1.d=trans.w;
                      x=acc.bal+trans1.d-trans1.w;
                      if(x>0)
                      {
                          acc.bal=x;
                          trans1.bal=acc.bal;
                          strcpy(trans1.status,"Reversed");
                          printf("transaction successfully reversed");
                          printf("your transaction recipt:-\n");
                          printf("ano   tid   withdraw   deposit   Balance   Status");
                          printf("%d   %d   %d   %d   %d   %s",trans1.ano,trans1.tid,trans1.w,trans1.d,trans1.bal,trans1.status);
                      }
                      else
                      {
                          trans1.bal=acc.bal;
                          strcpy(trans1.status,"Declined");
                          printf("transaction reversal request declined!\nInsufficient Balance\n");
                          printf("your transaction recipt:-\n");
                          printf("ano   tid   withdraw   deposit   Balance   Status");
                          printf("%d   %d   %d   %d   %d   %s",trans1.ano,trans1.tid,trans1.w,trans1.d,trans1.bal,trans1.status);
                      }
                      fwrite(&trans1,1,sizeof(struct transact),fpt);


                  }
                  else
                  {
                      printf("Transaction doesn't exist!");
                  }

            }
            else
            {
                printf("wrong password.Diverting you to the home page");
            }
        }
        fwrite(&acc,1,sizeof(struct account),temp);
    }
    if (count==0)
    {
        printf("account doesn't exist!");
    }
    fclose(fp);
    fclose(fpt);
    fclose(temp);
    rename("temp.dat","account.dat");
}
*/
void branchreport()
{
    FILE *fp;
    struct transact trans;
    fp=fopen("transact.dat","rb");
    printf("ano   tid   withdraw   deposit   Balance   Status");
    while (fread(&trans,1,sizeof(struct transact),fp))
    {
        printf("%d   %d   %d   %d   %d   %s",trans.ano,trans.tid,trans.w,trans.d,trans.bal,trans.status);
    }
    fclose(fp);
}

void main()
{
  int i,count=0;
  struct autonumber a={12345,700};
  FILE *fp;
  fp=fopen("auto.dat","wb");
  fwrite(&a,1,sizeof(struct autonumber),fp);
  fclose(fp);
  while(count==0)
  {
    printf("        Dear customer,Jaypee Indian Bank welcomes you \n");
    printf("        How can we serve you?\n\n ");
    printf("        1) create new bank account\n");
    printf("        2) View Selected Account\n");
    printf("        3) Delete your account\n");
    printf("        4) Display all accounts\n");
    printf("        5) Money Withdrawl\n");
    printf("        6) Money Deposit\n");
    printf("        7) Edit account details\n");
    printf("        8) Print passbook \n");
    printf("        9) Reverse transaction: Temporary not available\n");
    printf("        10) Generate Branch Report");
    printf("        11)exit\n\n");
    printf("        Enter your choice:");
    scanf("%d",&i);

    switch(i)
     {
        case 1:
          createaccount();
          break;

        case 2:
          displayaccount();
          break;
        case 3:
            delaccount();
            break;
        case 4:
            displayall();
            break;
        case 5:
            withdraw();
            break;
        case 6:
            deposit();
        case 7:
            editaccount();
            break;
        case 8:
            passbook();
        /*case 9:
            revtrans();*/
        case 10:
            branchreport();
        case 11:
            count=1;
            break;
        default:
            printf("wrong input.please enter again");
            break;

     }
  }

  //remove("account.dat");
  //remove("transact.dat");
  //remove("auto.dat")

}




