#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    char name[20];
    char month[20];
    int date;
    char reason[30];
    float amount;
} add;

add sev[100];
int count = 0;
 void open(){
    count = 0;
    FILE *fptr = fopen("expense.txt","r");
    if(fptr == NULL){
        return;
    }
       add s;
    char line[200];

    while(fgets(line,sizeof(line),fptr) != NULL){
        if(count >= 100){
            printf("Too many records in the file.\n");
            break;
        }
        line[strcspn(line,"\n")]= '\0';

        char *token;
        
        token = strtok(line,"|");
        if(token == NULL){
            continue;
        }
        strcpy(s.name,token);

        token = strtok(NULL,"|");
        if(token == NULL){
            continue;
        }
        strcpy(s.month,token);
        
        token =strtok(NULL,"|");
        if(token == NULL){
            continue;
        }
        s.date = atoi(token);

        token =strtok(NULL,"|");
        if(token == NULL){
            continue;
        }
        strcpy(s.reason,token);

        token =strtok(NULL,"|");
        if(token == NULL){
            continue;
        }
        s.amount = atof(token);
        
        sev[count] = s;
        count++;
 }
 fclose(fptr);
}

 void print(add s){
     printf("Name = %s\n", s.name);
    printf("Month = %s\n", s.month);
    printf("Date = %d\n", s.date);
    printf("Reason = %s\n", s.reason);
    printf("Amount = %.2f\n", s.amount);
    printf("\n-------------------------\n");
 }

 void addexpense(){

    open();
    if(count >= 100){
        printf("Can't enter anymore system full");
        return;
    }
    add s;
    getchar();
    printf("Name: ");
    fgets(s.name,sizeof(s.name),stdin);
    s.name[strcspn(s.name,"\n")] = '\0';

    printf("Month: ");
    scanf("%s",s.month);

    printf("Date: ");
    scanf("%d",&s.date);
    if(s.date < 1 || s.date > 31){
        printf("Invalid");
        return;
    }

    printf("Reason of expense: ");
    getchar();
    fgets(s.reason,sizeof(s.reason),stdin);
    s.reason[strcspn(s.reason,"\n")]='\0';

    printf("amount: ");
    scanf("%f",&s.amount);
        
    FILE *fptr;
    fptr = fopen("expense.txt","a");
    if(fptr == NULL){
        printf("Couldn't open file!");
        return;
    }

    sev[count] = s;
    count++; 

    fprintf(fptr,"%s|%s|%d|%s|%.2f\n",s.name,s.month, s.date,s.reason,s.amount);
    fclose(fptr);
 }

 void viewexpense(){
    open();
    printf("Your expense files are:\n");
    if(count == 0){
        printf("No expenses found.\n");
        return;
    }

    for(int i = 0; i < count;i++){
        printf("Record %d\n",i+1);
        print(sev[i]);
 }
 }

 void delete(){
    FILE *fptr = fopen("expense.txt","w"); 
    if(fptr == NULL){
        printf("File didn't open!");
        return;
    }
    count = 0;
    fclose(fptr);
 }

 void update(){
    viewexpense();
    int choice;
    printf("Which record do you want to change(index): ");
    scanf("%d", &choice);
    choice--;
    if(choice < 0 || choice >= count){
        printf("Invalid record.\n");
        return;
    }
        print(sev[choice]);
 
    int option;
    printf("\n1. Name\n");
    printf("2. Month\n");
    printf("3. Date\n");
    printf("4. Reason\n");
    printf("5. Amount\n");

    printf("Enter what you want to change: ");
    scanf("%d",&option);

    switch(option){
        case 1: 
        getchar();
        printf("Enter new name:");
        fgets(sev[choice].name,sizeof(sev[choice].name),stdin);
        sev[choice].name[strcspn(sev[choice].name,"\n")] = '\0';
        break;
        case 2:
        printf("Enter new month: ");
        scanf("%s",sev[choice].month);
        break;
        case 3:
        printf("Enter date: ");
        scanf("%d",&sev[choice].date);
        break;
        case 4:
        getchar();
        printf("Reason of expense: ");
        fgets(sev[choice].reason,sizeof(sev[choice].reason),stdin);
        sev[choice].reason[strcspn(sev[choice].reason,"\n")]='\0';
        break;
        case 5:
        printf("Enter new amount: ");
        scanf("%f",&sev[choice].amount);
        break;
        default:
        printf("Invalid entry!");
        return;
    }

    FILE * fptr = fopen("expense.txt","w");
    if(fptr == NULL){
        printf("Couldn't open file!");
        return;
    }
    for(int i = 0; i < count;i++){
        fprintf(fptr,"%s|%s|%d|%s|%.2f\n",sev[i].name,sev[i].month,sev[i].date,sev[i].reason,sev[i].amount);
 }
    fclose(fptr);
 }

 void view_name(char search[]){
    open();
    int i = 0;
    int found = 0;
    while(i < count){
        if(strcmp(search,sev[i].name) == 0){
            print(sev[i]);
            found =1;
        }
        i++;
    }
    if(!found){
        printf("Record not found!\n");
    } 
 }

 void view_reason(char search[]){
    open();
    int i = 0;
    int found = 0;
    while(i < count){
        if(strcmp(search,sev[i].reason) == 0){
            print(sev[i]);
            found =1;
        }
        i++;
    }
    if(!found){
        printf("Record not found!\n");
    }
 }

 void viewmonth(char search[]){
    open();
    int choice;
    int date;
    printf("Would you like print the entire month's data or select a date?");
    printf("To select the whole month press 1.\n");
    printf("To print from a selected date press 2.\n");
    scanf("%d",&choice);
    int i = 0;
    int found = 0;
    switch(choice){
        case 1:
        while(i < count){
            if(strcmp(sev[i].month,search) == 0){
                print(sev[i]);
                found =1;
            }
            i++;
        }
        if(!found){
            printf("Record not found!\n");
        }
        break;
        case 2:
            printf("Enter the date: ");
            scanf("%d",&date);
            while(date < 1 || date > 31){
                int option;
                printf("Invalid date.\n");
                printf("1. Re-enter date\n");
                printf("2. Exit\n");
                scanf("%d", &option);   
                switch(option){
                    case 1:
                    printf("Enter date again: ");
                    scanf("%d",&date);
                    break;
                    case 2:
                    return;
                    default: printf("Invalid choice.\n"); return;
                }
                }
                    while(i < count){
                        if(strcmp(sev[i].month, search) == 0){
                            if(sev[i].date == date){
                                found = 1;
                                print(sev[i]);  
                            }
                        }
                        i++;
                    }
                    if(!found){
                        printf("Record not found.\n");
                    }
                    break;   

                    default: printf("Invalid choice.\n"); return;
    }
    

}

void viewamount(){
    open();
    float price;
    printf("Enter amount: ");
    scanf("%f",&price);
    int i = 0;
    int found = 0;
    while(i < count){
        if(sev[i].amount == price){
            print(sev[i]);
            found = 1;
        }
        i++;
    }
    if(!found){
        printf("Record not present.\n");
    }
    
 } 

 void view_by_trait(int x){
    char search[50];
    switch(x){
        case 1: printf("Enter name: "); break;
        case 2: printf("Enter month: "); break;
        case 3: printf("Enter reason: "); break;
        case 4: viewamount(); return;  
        default: printf("Invalid entry: "); return;
    }
        getchar();
        fgets(search,sizeof(search),stdin);
        search[strcspn(search,"\n")] = '\0';
        switch(x)  
{
     case 1: 
        view_name(search);
        return;
    
    case 2:
        viewmonth(search);
        return;

    case 3: 
        view_reason(search);
        return; 

    default : printf("Invalid entry,\n");return;
}

 }      

 void delete_by_name(char search[]){
    open();
    int i = 0;
    int found = 0;
    while(i < count){
    if(strcmp(search,sev[i].name) == 0){
        found = 1;
        for(int j = i;j < count - 1; j++){
            sev[j] = sev[j+1];
        }
        count--;
    }else{
        i++;
    }

 }
 if(!found){
    printf("Record not found.\n");
    return;
 }

 FILE *fptr = fopen("expense.txt","w");
 if(fptr == NULL){
    printf("Couldn't find file.\n");
    return;
 }
 for(i = 0; i< count; i++){
    fprintf(fptr,"%s|%s|%d|%s|%.2f\n",sev[i].name,sev[i].month,sev[i].date,sev[i].reason,sev[i].amount);
 }
 fclose(fptr);
 printf("Record(s) deleted successfully.\n");
}

void delete_by_month(char search[]){
    open();
    int i = 0;
    int found = 0;
    while(i < count){
        if(strcmp(search,sev[i].month) == 0){
            print(sev[i]);
            found = 1;
        }
        i++;
    }
    if(!found){
    printf("Record not found.\n");
    return;
}
    int choice;
    printf("Would you like to delete all the months or a specific date?\n");
    printf("Press 1 to delete all the data in the month.\n");
    printf("Press 2 to delete from a specific date.\n");
    scanf("%d",&choice);

    i = 0;
    switch(choice){
        case 1: 
        while(i < count){
            if(strcmp(search,sev[i].month) == 0){
                found =1;
                for(int j = i;j < count - 1;j++){
                    sev[j] =sev[j+1];
                }
                count--;
            }else{
                i++;
            }
        }
        break;
        case 2:
        int date;
        int option;
        printf("Enter date: ");
        scanf("%d",&date);
        while(date < 1 || date > 31){
            printf("Invalid date!\n");
            printf("Press 1 to re-enter date.\n");
            printf("Press 2 to exit.\n");
            scanf("%d",&option);

            switch(option){
                case 1: 
                printf("Re-enter date: ");
                scanf("%d",&date);
                break;
                case 2:
                return;
                default:
                printf("Invalid choice.\n");
                return;
            }
        }
        i=0;
        found =0;
        while(i < count){
            if(strcmp(search,sev[i].month) == 0){
                if(sev[i].date == date){
                    found = 1;
                    for(int j = i; j < count-1;j++){
                        sev[j] =sev[j+1];
                    } 
                    count--;
                }else{
                    i++;
                }
            }else{
                i++;
            }
        }

        if(!found){
            printf("Record not found.\n");
            return;
        }
        break;

        default: printf("Invalid choice.\n"); return;
    }
    FILE *fptr = fopen("expense.txt","w");
    if(fptr == NULL){
    printf("Couldn't find file.\n");
    return;
 }
     for(i = 0; i< count; i++){
    fprintf(fptr,"%s|%s|%d|%s|%.2f\n",sev[i].name,sev[i].month,sev[i].date,sev[i].reason,sev[i].amount);
 }
 fclose(fptr);
 printf("Record(s) deleted successfully.\n");
}
void delete_by_reason(char search[]){
    open();
    int i=0;
    int found=0;
      while(i < count){
    if(strcmp(search,sev[i].reason) == 0){
        found = 1;
        for(int j = i;j < count - 1; j++){
            sev[j] = sev[j+1];
        }
        count--;
    }else{
        i++;
    }

 }
 if(!found){
    printf("Record not found.\n");
    return;
 }
  FILE *fptr = fopen("expense.txt","w");
 if(fptr == NULL){
    printf("Couldn't find file.\n");
    return;
 }
 for(i = 0; i< count; i++){
    fprintf(fptr,"%s|%s|%d|%s|%.2f\n",sev[i].name,sev[i].month,sev[i].date,sev[i].reason,sev[i].amount);
 }
 fclose(fptr);
 printf("Record(s) deleted successfully.\n");
}

void delete_by_amount(){
    open();
    float amount;
    printf("Enter amount: ");
    scanf("%f",&amount);
    int i = 0;
    int found = 0;
    while(i < count){
        if(sev[i].amount == amount){
            found = 1;
            for(int j = i;j< count - 1; j++){
                sev[j] =sev[j+1];
            }
            count--;
        }else{
            i++;
        }
    }
     if(!found){
    printf("Record not found.\n");
    return;
 }
  FILE *fptr = fopen("expense.txt","w");
 if(fptr == NULL){
    printf("Couldn't find file.\n");
    return;
 }
 for(i = 0; i< count; i++){
    fprintf(fptr,"%s|%s|%d|%s|%.2f\n",sev[i].name,sev[i].month,sev[i].date,sev[i].reason,sev[i].amount);
 }
 fclose(fptr);
 printf("Record(s) deleted successfully.\n");
}

 void delete_by_trait(int x){
    char search[50];
    switch(x){
        case 1: 
        printf("Enter name: "); 
        break;
        case 2:
        printf("Enter month: ");
        break;
        case 3:
        printf("Enter reason: ");
        break;
        case 4:
        delete_by_amount();
        return;
        default: printf("Invalid choice: "); return;
    }
    getchar();
    fgets(search,sizeof(search),stdin);
    search[strcspn(search,"\n")] = '\0';
    

    switch(x){
        case 1: delete_by_name(search);
        return;
        case 2: delete_by_month(search);
        return;
        case 3: delete_by_reason(search);
        return;
        default: printf("Invalid choice.\n"); return;
    }
 }


int main(){
    while(1){
    int enter;
    printf("This is a simple friendly expense tracker!!\n");
    printf("What are you here for?\n");
    printf("1, Insert expense.\n");
    printf("2. View all the expenses.\n");
    printf("3. View expenses of your choice.\n");
    printf("4. Update your expenses.\n");
    printf("5. Delete everything\n");
    printf("6. Delete records of your choice.\n");
    printf("7. Exit\n");
    scanf("%d",&enter);
    switch(enter){
        case 1: addexpense(); break;
        case 2: viewexpense(); break;
        case 3:{
        int whichview;
        printf("1. Name.\n");
        printf("2. Month.\n");
        printf("3. Reason.\n");
        printf("4. Amount.\n");
        scanf("%d",&whichview); 
        view_by_trait(whichview); 
        break;
        }
        case 4: update(); break;
        case 5: delete(); break;
        case 6:{
         int whichdelete;
        printf("1. Name.\n");
        printf("2. Month.\n");
        printf("3. Reason.\n");
        printf("4. Amount.\n");
        scanf("%d",&whichdelete); 
        delete_by_trait(whichdelete); 
        break;
        }
        case 7: printf("Exit"); printf("Thank you!!!!"); return 0;
        default: printf("Invalid choice."); break;
    }
    }
    return 0;
}