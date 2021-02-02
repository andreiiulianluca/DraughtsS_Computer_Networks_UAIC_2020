#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
int dame[8][8],vectorid[100],continuare=0;
int AfisareDame(int dame[8][8]){
   printf("A-B-C-D-E-F-G-H");
   printf("\n");
   printf("***************");
   printf("\n");
   for(int i=0;i<8;i++)
   {
      for(int j=0;j<8;j++)
      {
         if(dame[i][j]==0)
         {
            if((i+j)%2!=0)
            printf("+ ");
            if((i+j)%2==0)
            printf("- ");
         }
         if(dame[i][j]==1)
      printf("B ");
         if(dame[i][j]==2)
      printf("W ");
         if(dame[i][j]==3)
      printf("DB ");
         if(dame[i][j]==4)
      printf("DW ");
       
      }
      
      printf("\n");
   }
   printf("***************\n");  }
int ConversieColoana(char* input){
 if(strcpy(input,"a")==0||strcpy(input,"A")==0)
     return 0;
 if(strcpy(input,"b")==0||strcpy(input,"B")==0)
     return 1;
  if(strcpy(input,"c")==0||strcpy(input,"C")==0)
     return 2;
  if(strcpy(input,"d")==0||strcpy(input,"D")==0)
     return 3;
  if(strcpy(input,"e")==0||strcpy(input,"E")==0)
     return 4;
  if(strcpy(input,"f")==0||strcpy(input,"F")==0)
     return 5;
  if(strcpy(input,"g")==0||strcpy(input,"G")==0)
     return 6;
  if(strcpy(input,"h")==0||strcpy(input,"H")==0)
     return 7;       } 
int Clasament(int vectorid[100]){
	printf("ID-ul unic   Punctajul");
	for(int i=0;i<100;i++)
	   printf("%d   %d",i,vectorid[i]-1);
}
extern int errno;
/* portul de conectare la server*/
int port;
int linia1,linia2;
int coloana1,coloana2;
char* coloanaprimita;
int pozitieok;
int castigator1;//aici primim semnal daca am castigat sau nu
int main (int argc, char *argv[])
{
  int sd;			// descriptorul de socket
  struct sockaddr_in server;	// structura folosita pentru conectare 
  char nickname[10];		// nickname transmis catre server
  int castigator=0;
  int id=-1;
  int tura,runda;
  int pozitie=1;//cu aceasta variabila vom relua procesul de trimitere a coordonatelor piesei
  int mutare=1; 
  int continuare=0;
  int tip,tipul=0;
  int detinereid;//mesajul de la client in cazul in care are deja asignat un id
  if (argc != 3)
    {
      printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

  /* stabilim portul */
  port = atoi (argv[2]);

  /* cream socketul */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr(argv[1]);
  /* portul de conectare */
  server.sin_port = htons (port);
  
  /* ne conectam la server */
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }

  
  printf("Bine ati venit la jocul de Dame!\n"); 
  fflush (stdout);

  /*aici facem schimbul initial de nickname-uri*/
  printf ("Introduceti va rog un nickname: ");
  fflush (stdout);
  bzero (nickname, 10);
  scanf("%s",nickname);
  fflush (stdin);
  write(sd, nickname, 10);
  
  printf("Imediat veti primi si numele adversarului!\n");
  fflush (stdout);
  bzero (nickname, 10);
  read(sd, nickname, 10);
  
  printf("Nickname-ul adversarului dumneavoastra este: %s\n",nickname);
  fflush (stdout);
  
  /*aici vom stabilit tipul de joc pe care jucatorii vor decide sa il joace*/
  do{
  printf("Va rugam alegeti tipul de joc:\n");
  printf("1.Classical Draughts\n");
  printf("2.Suicidal Checkers\n");
  scanf("%d",&tip);
  write(sd,&tip,sizeof(int));
  read(sd,&tipul,sizeof(int));
  if(tipul==0)
  printf("Ambii jucatori trebuie sa aleaga acelasi mod de joc!\n");
  }while(tipul==0);
   
   printf("Aveti deja asignat un ID?(DA-1 NU-0)\n");
   scanf("%d",&detinereid);
   write(sd,&detinereid,sizeof(int));
   if(detinereid==0){
   /*acum primim id-ul unic*/
   read(sd, &id,sizeof(int));
   printf("ID-ul dumneavoastra unic este: %d\n",id);
   fflush(stdout);
   }
   if(detinereid==1){
   printf("Va rugam sa ne furnizati ID-ul:\n");
   scanf("%d",&id);
   write(sd,&id,sizeof(int));
   }
  

   /*acum vom primi matricea initiala*/
   for(int i=0;i<8;i++)
     for(int j=0;j<8;j++)
     {
        read(sd, &dame[i][j], sizeof(int));
     }
   printf("Tabla de dame este pregatita, putem incepe!\n");
   fflush(stdout);
   AfisareDame(dame);
   fflush(stdout);
   /* acum dorim sa trimitem catre server coordonatele piesei pe care dorim sa o mutam si coordonatele locului unde va ajunge piesa aleasa*/
   
   do{
   read(sd,&runda,sizeof(int));
   //printf("Runda: %d\n",runda);
   
   if(runda==1){
   printf("Este randul dumneavoastra!");
   pozitie=1;
   do{
   do{
   /*citim prima data matricea in momentul actual*/
   printf("In momentul actual, tabla de dame arata astfel:\n");
   fflush(stdout);
   for(int i=0;i<8;i++)
     for(int j=0;j<8;j++)
     {
        read(sd, &dame[i][j], sizeof(int));
     }
   AfisareDame(dame);  
   fflush(stdout);   
   printf("Va rog sa ne oferiti linia piesei pe care doriti sa o mutati:\n");
   fflush(stdout);
   scanf("%d",&linia1);
   fflush (stdin);
   write(sd,&linia1,sizeof(int));
   
   printf("Va rog sa ne oferiti coloana piesei pe care doriti sa o mutati:\n");
   printf("A-0 B-1 C-2 D-3 E-4 F-5 G-6 H-7\n");
   fflush(stdout);
   scanf("%d",&coloana1);
   fflush(stdin);
   write(sd,&coloana1,sizeof(int));
   
   read(sd,&pozitie,sizeof(int));//semnalul dat de catre server daca pozitia este in regula
   //printf("Stare pozitie: %d\n",pozitie);
   if(pozitie==0)
   printf("Pozitia nu este corecta, va rugam reintroduceti coordonatele!\n");
   fflush(stdout);
   }while(pozitie==0);
   
   do{
   printf("Va rog sa ne oferiti linia mutarii pe care doriti sa o efectuati:\n");
   fflush(stdout);
   scanf("%d",&linia2);
   fflush (stdin);
   write(sd,&linia2,sizeof(int));

   printf("Va rog sa ne oferiti coloana mutarii pe care doriti sa o efectuati:\n");
   printf("A-0 B-1 C-2 D-3 E-4 F-5 G-6 H-7\n");
   fflush(stdout);
   scanf("%d",&coloana2);
   fflush(stdin);
   write(sd,&coloana2,sizeof(int));

   read(sd,&mutare,sizeof(int));//semnalul dat de catre server daca mutarea este in regula
   //printf("Stare mutare: %d\n",mutare);
   if(mutare==0)
   printf("Mutarea nu este corecta, va rugam reintroduceti coordonatele!\n");
   fflush(stdout);
   }while(mutare==0);
   printf("Dupa mutare tabla arata astfel:\n");
   fflush(stdout);
   for(int i=0;i<8;i++)
     for(int j=0;j<8;j++)
     {
        read(sd, &dame[i][j], sizeof(int));
     }
   AfisareDame(dame);
   fflush(stdout);
   read(sd,&continuare,sizeof(int));
   if(continuare==0)
   printf("Nu se mai poate efectua nicio mutare.Continuam!\n");
   if(continuare==1)
   printf("Conform regulilor mai puteti efectua o mutare!\n");
   }while(continuare==1);
   
   }
   
   if(runda==0)
   printf("Este randul celuilalt jucator, va rugam asteptati!\n");
   
   read(sd,&castigator,sizeof(int));
   //printf("Castigator: %d\n",castigator);
   fflush(stdout);

   }while(castigator==0);
   
   read(sd,&castigator1,sizeof(int));
   if(castigator1==1)
   printf("Felicitari, ati castigat!Ati primit un punct in tabelul final!\n");
   if(castigator1==0)
   printf("Din pacate ati pierdut..Mult noroc data viitoare!");
     
   for(int i=0;i<100;i++)
   read(sd,&vectorid[i],sizeof(int));
  /* inchidem conexiunea, am terminat */
  close (sd);
}