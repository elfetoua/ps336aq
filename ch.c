#include <stdio.h>
#include <stdlib.h>

typedef struct node{
       int data;
       struct node *next;
       int n;
       }node;

typedef struct list list;
struct list{
    node *first;
};

void afficherliste(node* L);
node* createvect(int n)
{
    node *p;
    node *q, *head;
    int i = 1,a;
    printf("entrer coordonnee %d \n",i);
    p=(node*)malloc(sizeof(node));
    scanf("%d",&a);
    p->data = a;
    p->next = NULL;
    head=p;
 for(i=2;i<=n;i++)
 {
     printf("entrer coordonnee %d \n",i);
     q=(node*)malloc(sizeof(node));
     scanf("%d",&a);
     q->data=a;
     q->next= NULL;
     p->next=q;
     p=p->next;
 }
 p->next=NULL;
 afficherliste(head);
 return head;
}

void afficherliste(node* L)
{

    while(L!= NULL)
    {
        printf("%d ",L->data);
        L=L->next;
    }
printf("\n\n");
}

int main()
{
    int n,i,y,t=1;

    struct node *list;
    printf("donner le nombre de vecteurs : \n");
    scanf("%d",&y);

   while(t<=y)
   {
       for(i=1;i<=y;i++)
        {
       printf("entrer la dimension du vecteur %d : \n",t);
       scanf("%d",&n);

       list = createvect(n);
      t++;
      }

   }
   return 0;
}