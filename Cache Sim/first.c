#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<math.h>

#include<ctype.h>

struct node

{

unsigned long long int data;

int valid;

  struct node *next;

};



int hit=0;

int miss=0;

int read=0;

int write=0;

int hit_2=0;

int miss_2=0;

int read_2=0;

int write_2=0;

struct node** searchcac(struct node **cache,int set, char typeofaction,unsigned long long int val,int);

unsigned long long int gettagbit(unsigned long long int addr,int bsize,int setbit);

struct node** makecache(int set, int a);

int checkpower(int value);

int setbit(unsigned long long int addr,int bsize,int set);

struct node** searchcacb(struct node **cache,unsigned long long int address,int block,int set,int setb, char typeofaction,unsigned long long int tagbit,int a,int prefsize);

struct node** makecacheb(int set, int a);

struct node** fifowith_prefetch(struct node** cache,unsigned long long int addr,int prefsize,int blocksize,int set);









void printcach(struct node ** cache ,int set)

{



  struct node *temp;

  for(int i=0 ;i<set;i++)

  {

    temp=cache[i]->next;

    while(temp!=NULL)

    {

      printf("%llx\t",temp->data);

      temp=temp->next;

    }

    printf("\n");

  }

}

int main(int argc, char** argv){





  if(argc != 7){

                           printf("Incorrect number of parameters\n");

                           exit(0);

              }

unsigned long long  int val,tgb;

unsigned long long  int tgb2;

struct node **arr;

struct node **arr2;

char c;

int set,a,setb,setb_2;

char *cl;

int blocksize,cachesize,prefsize;

//char cachepolicy1[4]='fifo';
//char cachepolicy1;

if( argv[3][0]=='l')
{exit(0);}

blocksize=atoi(argv[2]);

checkpower(blocksize);

prefsize =atoi(argv[5]);

cachesize=atoi(argv[1]);

checkpower(cachesize);



FILE* fp =fopen(argv[6],"r");

if(argv[4][0]=='d')

{

a=1;

set=(cachesize/(blocksize*a));

}

else if(argv[4][0]=='a' && argv[4][5]=='\0')

{

set=1;

a=(cachesize/blocksize);

}

else if(argv[4][0]=='a' && argv[4][5]==':')

{

  int lengt, i;

  cl=argv[4];

  lengt= strlen(cl);

  char ch;

  for(i=0;i<lengt;i++)

  {

    ch=cl[i];

    if(isdigit(ch))

    {

      a=cl[i]-'0';

    }

  }

  checkpower(a);

set=(cachesize/(blocksize*a));

}

else{

  printf("error\n");

  exit(0);

}



//arr=

arr=makecache(set,a);

arr2=makecacheb(set, a);

//printcach(arr,set);



while(fscanf(fp,"%c %llx\n",&c, &val)!=EOF)

{

  if(c=='#'){

    break;

  }

else if(c=='R')

{

  setb= setbit(val,blocksize,set);

  tgb= gettagbit(val,blocksize,set);

  arr= searchcac(arr,setb,'r',tgb,a);

  /*if(check == 0)

  {

   // arr=fiforeplacement(arr,tgb,setb,a);

  }*/

}

  else{

    setb= setbit(val,blocksize,set);

    tgb= gettagbit(val,blocksize,set);

    arr= searchcac(arr,setb,'w',tgb,a);

  /*  if(check == 0)

    {

   // arr=  fiforeplacement(arr,tgb,setb,a);

    }

    */



}

//printf("value%llx\t ",tgb);

//printf("set-%d\n ",setb);

//printcach(arr, set);

if(c=='R'){

  setb_2= setbit(val,blocksize,set);

  tgb2= gettagbit(val,blocksize,set);

  arr2= searchcacb(arr2,val,blocksize,set,setb_2, 'r',tgb2,a,prefsize);



}

else{

    setb_2= setbit(val,blocksize,set);

  tgb2= gettagbit(val,blocksize,set);

  arr2= searchcacb(arr2,val,blocksize,set,setb_2, 'w',tgb2,a,prefsize);

}



}

//printf("%d\t %d\t%d\t%d",miss,hit,read,write);

printf("no-prefetch\n");

printf("Memory reads: %d\n", read);

printf("Memory writes: %d\n",write);

printf("Cache hits: %d\n",hit);

printf("Cache misses: %d\n",miss);

printf("with-prefetch\n");

printf("Memory reads: %d\n", read_2);

printf("Memory writes: %d\n",write_2);

printf("Cache hits: %d\n",hit_2);

printf("Cache misses: %d\n",miss_2);

/*tgb=0xbf8ef49c;

setb=0;

printf("%llx %d",tgb,setb);



printf("\n");

printf("\n");*/

/*for(int i=0;i<set;i++)

{

struct node *tp;

tp=arr[i]->next;

while(tp!=NULL)

{

  printf("%llx\t",tp->data);

  tp=tp->next;

}

printf("\n");

}*/







return 0;

}





int  checkpower(int value)

{

  int count=0;

  double temp=value;

  while(temp!=1)

  {

    temp=temp/2;

    count++;

    if(temp<1)

    {

      printf("error");

      exit(0);

    }

  }

  return count;

}





struct node** makecache(int set, int a)

{

  //printf("%d %d\n",set ,a );

  int count =0;

  int dup=0;

  struct node *temp;

struct node **arr= malloc(set*(sizeof(struct node*)));

for(int i=0;i<set;i++)

{struct node* rear=NULL;

  dup=0;

//  struct  node *ptr;

  arr[i]= malloc((sizeof(struct node)));



  while(dup<a){

  struct  node *ll =  malloc(sizeof(struct node));

  ll->next=NULL;



  ll->valid=0;

  struct node *head;

  if(arr[i]->next==NULL)

  {

head=ll;

arr[i]->next=head;

rear=head;

dup++;

continue;

  }

//  ptr=head;

  else if(head!=NULL)

  {

    temp=ll;

    rear->next=temp;

    rear=temp;

    //temp=temp->next;

    dup++;

    count++;

    continue;

  }



  //dup++;

}

}

return  arr;

}

struct node** searchcac(struct node **cache,int set, char typeofaction,unsigned long long int tagbit,int a)

{



  struct node *head;

  struct node *temp;

  head=cache[set]->next;

// printf("tagbit: %llx  index: %d\n",tagbit,set);

  temp=head;



  if(a==1){



      if(tagbit==temp->data)

    {

      if(typeofaction=='w')

      {

          write++;

          hit++;

          return cache;

      }

      else{

        hit++;

        return cache;

      }

    }



      else if(typeofaction=='w')

      {

          write++;

          read++;

          miss++;

      }

      else{

        miss++;

        read++;

      }

   if(temp->valid==0){

       temp->valid=1;

       temp->data = tagbit;

       return cache;

   }

  temp->data = tagbit;

  return cache;

  }



  while(temp!=NULL)

  {

    if(temp->valid==0)

    {



      temp->data=tagbit;

      temp->valid=1;

      if(typeofaction=='w')

      {

          write++;

          read++;

          miss++;

      }

      else{

        miss++;

        read++;

      }

      return cache;



    }

    else if(tagbit==temp->data)

    {

      if(typeofaction=='w')

      {

          write++;

          hit++;

      }

      else{

        hit++;

      }

      return cache;

    }

    temp=temp->next;

  }

  if(typeofaction=='w')

  {

      write++;

      read++;

      miss++;

  }

  else{

    miss++;

    read++;

  }

  temp=head;

// cache = fiforeplacement(cache,tagbit,set,a);

while(temp->next!=NULL)

{

  temp->data=temp->next->data;

  temp=temp->next;

}

temp->data=tagbit;



return cache;

}

int setbit(unsigned long long int addr,int bsize,int set)

{

  int val2;

  int blockoffsetbit= log2(bsize);

  val2=(addr>>blockoffsetbit)%set;

  return val2;

}

unsigned long long int gettagbit(unsigned long long int addr,int bsize,int set)

{

  unsigned long long int val2;

  int set_bits = log2(set);

  int blockoffsetbit= log2(bsize);

  val2=addr>>(blockoffsetbit+set_bits);



  return val2;

}

/*struct node** fiforeplacement(struct node **cache,unsigned long long int tagb,int setb,int a)

{

struct node *temp;

temp=cache[setb]->next;



if(a==1){



if(temp->valid==0){

temp->valid = 1;

}

temp->data=tagb;

return cache;

}

//struct node *temp;

struct node *head;

struct node *rear;

struct node *ptr;

//temp=cache[setb]->next;

head=cache[setb]->next;

ptr=head;

while(ptr!=NULL){

  rear=ptr;

ptr=ptr->next;

}

ptr= head;

head=head->next;

rear->next=ptr;

ptr->data=tagb;

ptr->next = NULL;

rear=ptr;

return cache;*/



struct node** makecacheb(int set, int a)

{

  int count =0;

  int dup=0;

  struct node *temp;

struct node **arr= malloc(set*(sizeof(struct node*)));

for(int i=0;i<set;i++)

{struct node* rear=NULL;

  dup=0;

  arr[i]= malloc((sizeof(struct node)));



  while(dup<a){

  struct  node *ll =  malloc(sizeof(struct node));

  ll->next=NULL;



  ll->valid=0;

  struct node *head;

  if(arr[i]->next==NULL)

  {

head=ll;

arr[i]->next=head;

rear=head;

dup++;

continue;

  }

//  ptr=head;

  else if(head!=NULL)

  {

    temp=ll;

    rear->next=temp;

    rear=temp;

    //temp=temp->next;

    dup++;

    count++;

    continue;

  }



  //dup++;

}

}

return  arr;

}

struct node** searchcacb(struct node **cache,unsigned long long int address,int block,int set,int setb, char typeofaction,unsigned long long int tagbit,int a,int prefsize)

{



  struct node *head;

  struct node *temp;

  head=cache[setb]->next;

// printf("tagbit: %llx  index: %d\n",tagbit,set);

  temp=head;



  if(a==1){



      if(tagbit==temp->data)

    {

      if(typeofaction=='w')

      {

          write_2++;

          hit_2++;

          return cache;

      }

      else{

        hit_2++;

        return cache;

      }

    }



      else if(typeofaction=='w')

      {

          write_2++;

          read_2++;

          miss_2++;

      }

      else{

        miss_2++;

        read_2++;

      }

   if(temp->valid==0){

       temp->valid=1;

       temp->data = tagbit;

       cache=  fifowith_prefetch(cache,address,prefsize,block,set);

       return cache;

   }

  temp->data = tagbit;

  cache=  fifowith_prefetch(cache,address,prefsize,block,set);



  return cache;

  }



  while(temp!=NULL)

  {

    if(temp->valid==0)

    {



      temp->data=tagbit;

      temp->valid=1;

      cache=  fifowith_prefetch(cache,address,prefsize,block,set);

      if(typeofaction=='w')

      {

          write_2++;

          read_2++;

          miss_2++;

      }

      else{

        miss_2++;

        read_2++;

      }

      return cache;



    }

    else if(tagbit==temp->data)

    {

      if(typeofaction=='w')

      {

          write_2++;

          hit_2++;

      }

      else{

        hit_2++;

      }

      return cache;

    }

    temp=temp->next;

  }

  if(typeofaction=='w')

  {

      write_2++;

      read_2++;

      miss_2++;

  }

  else{

    miss_2++;

    read_2++;

  }

  temp=head;



  while(temp->next!=NULL)

{

  temp->data=temp->next->data;

  temp=temp->next;

}

temp->data=tagbit;

cache=  fifowith_prefetch(cache,address,prefsize,block,set);



return cache;

}

/*while(temp->next!=NULL)

{

  temp->data=temp->next->data;

  temp=temp->next;

}

temp->data=tagb;*/

//return cache;



struct node** fifowith_prefetch(struct node** cache,unsigned long long int addr,int prefsize,int blocksize,int set)

{

    int counter=0;

    int counter2=0;

unsigned long long int addr2;

addr2=addr;

unsigned long long int tgb;

struct node *temp;

struct node *head;

int setb;

for(int i=0;i<prefsize;i++)

{

addr2=addr+blocksize;

setb=setbit( addr2, blocksize,set);

tgb=gettagbit(addr2,blocksize,set);



head=cache[setb]->next;

temp=head;

while(temp!=NULL)

{

if(temp->data==tgb)

{

     counter=1;

     counter2=1;

     break;

}

else if(temp->valid==0)

{

     counter=1;

    /* if(setb!=0)

     {

         if(cache[setb-1]->next->data==tgb)

         {

          break;

         }

     }*/

     temp->data=tgb;



     temp->valid=1;

     break;

}

temp=temp->next;

}

temp=head;

if(counter==0){

     while(temp->next!=NULL)

{

  temp->data=temp->next->data;

  temp=temp->next;

}

temp->data=tgb;



}

addr=addr2;



if(counter2==0)

{

  read_2++;

}

counter=0;

counter2=0;

}

return cache;

}
