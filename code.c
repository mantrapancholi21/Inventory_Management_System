#include<stdio.h>

void displayInventory(void)
{

FILE *data=fopen("data.txt","r");

    char name[50];
    int itemid;
    float price;
    int id;
    float stock1;
    int found = 0;
    char h1[50], h2[50], h3[50] ,h4[50];

    printf("\n_________________________________________________\n");
    fscanf(data, "%s %s %s %s", h1, h2, h3 ,h4);
    printf("| %-7s|  %-17s|    %-6s| %s |", h1 ,h2 ,h3 ,h4);
    printf("\n|-----------------------------------------------|");
    for(int i=0 ; i<20 ; i++)
    {
      int t=fscanf(data, "%d %s %f %f", &itemid, name, &price, &stock1);
      if(t==4)
      {
        printf("\n| %-7d|  %-17s|   %-7.1f|  %4.0f |", itemid, name, price, stock1);
      }
    }
    printf("\n|-----------------------------------------------|\n");

    fclose(data);
}

void menu(void)
{
    FILE *data=fopen("data.txt","r");

    char name[50];
    int itemid;
    float price;
    int id;
    float stock1;
    int found = 0;
    char h1[50], h2[50], h3[50] ,h4[50];
    fscanf(data, "%s %s %s %s", h1, h2, h3 ,h4);
    printf("%s %-15s %s\n", h1 ,h2 ,h3);
    
    for(int i=0 ; i<20 ; i++)
    {
      int t=fscanf(data, "%d %s %f %f", &itemid, name, &price, &stock1);
      if(t==4)
      {
        printf("%-6d %-15s %5.1f\n", itemid, name, price);
      }
    }
    fclose(data);
}

void load(char name[20][16],int itemid[], int itemPrice[],int stockCount[],char h1[],char h2[],char h3[],char h4[])
{
    FILE *data=fopen("data.txt","r");
    int i;
    fscanf(data, "%s %s %s %s", h1, h2, h3 ,h4);
    for(int i=0 ; i<20 ; i++)
        fscanf(data,"%d %s %d %d", &itemid[i], name[i], &itemPrice[i] ,&stockCount[i]);
}

void updateStock(char name[20][16],int itemid[], int itemPrice[],int stockCount[],char h1[],char h2[],char h3[],char h4[])
{
    FILE *data1=fopen("data.txt","w");
    fprintf(data1,"%s %-15s %s %s\n", h1 ,h2 ,h3, h4);
    for(int i=0 ; i<20 ; i++)
            fprintf(data1,"%-6d %-15s %-4d  %-4d\n", itemid[i], name[i], itemPrice[i], stockCount[i]);
    fclose(data1);
}
int check(int qty,int d)
{
	if( d < qty)
	{
		printf("\nWe Apologise!!!\nCurrenty We don't have Stock as per your requirment\n");
		printf("Current Stock = %d\n",d);
		return 0;
	}
	return 1;
}
void main()
{
    int id,qty,c,d,t=0,fprice=0,flow;
    int itemid[20];
    int stockCount[20];
    int itemPrice[20];
    char name[20][16];
    char work,choice;
    char h1[50],h2[50],h3[50],h4[50];
    start:
    printf("Select what you want to do\n1. Enter s for selling item\n2. Enter c to check stock\n3. Enter r to restock item");
    printf("\n\nEnter here :-> ");
    scanf(" %c",&work);
//-------------------------------------------------------------------------------------------------
  if(work=='s')
  {  
      nextitem:
      menu();
      printf("\n\nEnter ItemId here :-> ");
      scanf("%d",&id);
      id=id-101;
      load(name,itemid,itemPrice,stockCount,h1,h2,h3,h4);
      for(int i=0 ; i<20 ; i++)
      {
        if(id == i)
            {
              printf("%-6s %-15s %-5s %s\n",h1,h2,h3,h4);
              printf("%-6d %-15s %-4d %3d\n", itemid[i], name[i], itemPrice[i],stockCount[i]);
              break;
            }
      }
      d=stockCount[id];
      reenter:
      printf("\nYour selected Action Figure is \"%s\" \nEnter number of quantity you want to buy :-> ",name[id]);
      scanf("%d",&qty);
      //==========================
      c=check(qty,d);
      if(c==0)
      	goto reenter;
      //==========================
      t=qty*itemPrice[id];
      fprice+=t;
      printf("\nYour bill for %d x %s is: $%d\n",qty,name[id],t);
      load(name,itemid,itemPrice,stockCount,h1,h2,h3,h4);
      stockCount[id]=stockCount[id]-qty;
      updateStock(name,itemid,itemPrice,stockCount,h1,h2,h3,h4);
      printf("Do you want to buy anything else, \nif yes enter 1 and if no enter 0 : ");
      scanf(" %c",&choice);
      if(choice=='1')
        goto nextitem;
      else if(choice=='0')
      {
        printf("\n\nYour total bill is : $%d",fprice);
        printf("\n\nPlease Enter Your Pin To Pay : ");
        scanf("%*s");
        printf("PAYMENT SUCCESFUL");
      }
      printf("\n\nTo End Session ENTER : 0\nOR To Go to MainMenu ENTER : 1\n\nENTER 0|1 : ");
      scanf("%d",&flow);
        if (flow)
            goto start;
        else 
            return;
  }
//-----------------------------------------------------------------------------------------------
    else if(work=='c')
    {
        displayInventory();
        printf("\n\nTo End Session ENTER : 0\nOR To Go to MainMenu ENTER : 1\n\nENTER 0|1 : ");
        scanf("%d",&flow);
          if (flow)
              goto start;
          else
              return;
    }
//-----------------------------------------------------------------------------------------------
  else if(work=='r')
  {
      restock:
      printf("Enter the ID of item that you want to restock : ");
      displayInventory();
      printf("\nEnter ID : ");
      scanf("%d",&id);
      id-=101;
      load(name,itemid,itemPrice,stockCount,h1,h2,h3,h4);
      printf("Your selected product is \" %s \"\nCurrent stock in storage is : %d ",name[id],stockCount[id]);
      printf("\nAmount you restock is : ");
      scanf("%d",&qty);
      stockCount[id]=stockCount[id]+qty;
      
      printf("Updated stock is :->\n");
      updateStock(name,itemid,itemPrice,stockCount,h1,h2,h3,h4);
      displayInventory();
      printf("\n\nDo you want to continue restock then enter 1 or else enter 0 : ");
      scanf("%d",&flow);
        if (flow)
            goto restock;
      printf("\n\nTo End Session ENTER : 0\nOR To Go to MainMenu ENTER : 1\n\nENTER 0|1 : ");
      scanf("%d",&flow);
        if (flow)
        {
            goto start;
        }
        else 
            return;
    
    
  }
  
}
