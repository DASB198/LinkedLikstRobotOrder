#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct _robotOrder
{
    orderList *data;
    char *deliverTo;
    char *restaurant;
    struct _robotOrder *next;
} robotOrder;


void insertNode(robotOrder *headlist, robotOrder *food);
void printOrder(robotOrder *neadlist);
void deleteList(robotOrder *headlist);

int main()
{
    char buffer[50];
    char input;
    int count;
    char buffer1[100];
    robotOrder *headlist = dmalloc(sizeof(robotOrder));
    headlist->next = NULL;
    headlist->data = NULL;
    headlist->deliverTo = NULL;
    headlist->restaurant = NULL;
    robotOrder *food;
    char RoboNum;
    char *adrs;
    char *vendor;
    char *name;

    while(input != 'n')
    {
        printf("\n");
        printf("Want to place food delivery order? (y/n) ");
        fgets(buffer,5,stdin);
        sscanf(buffer,"%c",&input);
        printf("\n");


        switch(input)
        {

            case 'y':
                printf("Robot Number: ");
                fgets(buffer1,100,stdin);
                printf("Delivery Address for new delivery Order: ");
                fgets(buffer1,100,stdin);

                char address[100];
                strcpy(address,buffer1);
                strtok(address,"\n");

                adrs = strndup(address,strlen(address));


                if(!adrs)
                {
                    printf("Memory allocation failed\n");
                    exit(1);
                }

                food = dmalloc(sizeof(robotOrder));
                food->next = NULL;
                food->deliverTo = adrs;

                buffer1[0] = '\0';

                printf("Restaurant from which to pick up food: ");
                fgets(buffer1,100,stdin);

                char rest[100];
                strcpy(rest,buffer1);
                strtok(rest, "\n");

                vendor = strndup(rest,strlen(rest));


                if(!vendor)
                {
                    printf("Memory allocation failed\n");
                    exit(1);
                }

                food->restaurant = vendor;

                orderList *order = createItem();

                int print = 0;

                while(print == 0){

                    buffer1[0]='\0';

                    printf("Food Item: ");
                    fgets(buffer1,100,stdin);


                    if(buffer1[0] == '\n')
                    {
                        print++;
                        break;
                    }

                    char food[100];
                    strcpy(food,buffer1);
                    strtok(food,"\n");

                    name = strndup(food,strlen(food));


                    if(!name)
                    {
                        printf("Memory allocation failed\n");
                        exit(1);
                    }

                    insertInList(name,order);

                }
                food->data = order;

                insertNode(headlist,food);

                count++;
                break;
            case 'n':
                if(count >= 1){
                    printOrder(headlist);
                    deleteList(headlist);
                }else{
                    free(headlist);
                }
                break;
            default:
                printf("Invalid Input. Try again");
        }
    }
}

void insertNode(robotOrder *headlist, robotOrder *food)
{
    robotOrder *temp = headlist;

    food->next = temp->next;
    temp->next = food;
}

void printOrder(robotOrder *headlist)
{
    headlist = headlist->next;
    printf("List of Deliveries:\n ");
    printf("\n");
    while(headlist !=NULL)
    {
        
        printf("Robot Number: Delivery Order from %s has %d food item(s)\n" ,headlist->restaurant , headlist->data->count);
        printItemList(headlist->data);
        printf("Deliver To: %s\n ",headlist->deliverTo);
        printf("\n");
        headlist = headlist->next;
    }
}

void deleteList(robotOrder *headlist)
{
    robotOrder *temp;
    while(headlist!= NULL)
    {
        temp = headlist;
        if(headlist->data!=NULL){
            freeNode(temp->data);
            free(temp->data);
        }
        headlist = headlist->next;
        free(temp->deliverTo);
        free(temp->restaurant);
        free(temp);
    }
    free(headlist);
}

