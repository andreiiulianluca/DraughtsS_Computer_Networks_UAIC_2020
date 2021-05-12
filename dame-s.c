#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define PORT 2024
int puncte1, puncte2, id, vectorid[100], dame[8][8], tura;
int ConversieColoana(char input)
{
	if (input == 'a' || input == 'A')
		return 0;
	if (input == 'b' || input == 'B')
		return 1;
	if (input == 'c' || input == 'C')
		return 2;
	if (input == 'd' || input == 'D')
		return 3;
	if (input == 'e' || input == 'E')
		return 4;
	if (input == 'f' || input == 'F')
		return 5;
	if (input == 'g' || input == 'G')
		return 6;
	if (input == 'h' || input == 'H')
		return 7;
}
int VerificareCastigator()
{
	if (puncte1 == 12 || puncte2 == 12)
	{
		if (puncte1 == 12)
		{
			printf("Utilizatorul cu piese negre a castigat!Felicitari!\n");
			return 1;
		}
		if (puncte2 == 12)
		{
			printf("Utilizatorul cu piese albe a castigat!Felicitari!\n");
			return 1;
		}
	}
	return 0;
}
int InitializareDame(int dame[8][8])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 8; j++)
			if ((i + j) % 2 == 1)
				dame[i][j] = 2;

	for (int i = 5; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if ((i + j) % 2 == 1)
				dame[i][j] = 1;
}
int AfisareDame(int dame[8][8])
{
	printf("A-B-C-D-E-F-G-H\n");
	printf("\n");
	printf("***************\n");
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (dame[i][j] == 0)
				printf("- ");
			if (dame[i][j] == 1 || dame[i][j] == 3)
				printf("B ");
			if (dame[i][j] == 2 || dame[i][j] == 4)
				printf("W ");
		}

		printf("\n");
	}
	printf("***************\n");
}
int AdaugareMutare(int i, int j, int k, int l, int tura)
{
	if (tura == 1)
	{
		if (k == 0)
			dame[k][l] = 3;
		else
			dame[k][l] = 1;
	}
	if (tura == 2)
	{
		if (k == 7)
			dame[k][l] = 4;
		else
			dame[k][l] = 2;
	}
	if (dame[i][j] == 3)
		dame[k][l] = 3;
	if (dame[i][j] == 4)
		dame[k][l] = 4;

	dame[i][j] = 0;
}
int StergerePiesa(int i, int j, int tura)
{
	if (tura == 2)
	{
		if (dame[i + 2][j - 2] == 2 || dame[i + 2][j - 2] == 4)
		{
			if (dame[i + 1][j - 1] == 1 || dame[i + 1][j - 1] == 3)
			{
				printf("Am sters piesa BLACK!\n");
				dame[i + 1][j - 1] = 0;
				puncte2++;
			}
		}
		if (dame[i + 2][j + 2] == 2 || dame[i + 2][j + 2] == 4)
		{
			if (dame[i + 1][j + 1] == 1 || dame[i + 1][j + 1] == 3)
			{
				printf("Am sters piesa WHITE!\n");
				dame[i + 1][j + 1] = 0;
				puncte2++;
			}
		}
	}
	if (tura == 1)
	{
		if (dame[i - 2][j - 2] == 1 || dame[i - 2][j - 2] == 3)
		{
			if (dame[i - 1][j - 1] == 2 || dame[i - 1][j - 1] == 4)
			{
				dame[i - 1][j - 1] = 0;
				puncte1++;
			}
		}
		if (dame[i - 2][j + 2] == 1 || dame[i - 2][j + 2] == 3)
		{
			if (dame[i - 1][j + 1] == 2 || dame[i - 1][j + 1] == 4)
			{
				dame[i - 1][j + 1] = 0;
				puncte1++;
			}
		}
	}
}
int VerificareMutare(int i, int j, int k, int l, int tura)
{
	if (dame[i][j] == 3)
	{
		if (((dame[i - 1][j - 1] == 0 && k == i - 1 && l == j - 1) || (dame[i - 1][j + 1] == 0 && k == i - 1 && l == j + 1)) || ((dame[i - 2][j - 2] == 0 && k == i - 2 && l == j - 2 && (dame[i - 1][j - 1] == 2 || dame[i - 1][j - 1] == 4)) || (dame[i - 2][j + 2] == 0 && k == i - 2 && l == j + 2 && (dame[i - 1][j + 1] == 2 || dame[i - 1][j + 1] == 4))))
		{
			return 1;
		}
		if (((dame[i + 1][j - 1] == 0 && k == i + 1 && l == j - 1) || (dame[i + 1][j + 1] == 0 && k == i + 1 && l == j + 1)) || ((dame[i + 2][j - 2] == 0 && k == i + 2 && l == j - 2) || (dame[i + 2][j + 2] == 0 && k == i + 2 && l == j + 2)))
		{
			return 1;
		}
		return 0;
		if (dame[i][j] == 4)
		{
			if (((dame[i + 1][j - 1] == 0 && k == i + 1 && l == j - 1) || (dame[i + 1][j + 1] == 0 && k == i + 1 && l == j + 1)) || ((dame[i + 2][j - 2] == 0 && k == i + 2 && l == j - 2 && (dame[i + 1][j - 1] == 1 || dame[i + 1][j - 1] == 3)) || (dame[i + 2][j + 2] == 0 && k == i + 2 && l == j + 2 && (dame[i + 1][j + 1] == 1 || dame[i + 1][j + 1] == 3))))
			{
				return 1;
			}
			if (((dame[i - 1][j - 1] == 0 && k == i - 1 && l == j - 1) || (dame[i - 1][j + 1] == 0 && k == i - 1 && l == j + 1)) || ((dame[i - 2][j - 2] == 0 && k == i - 2 && l == j - 2) || (dame[i - 2][j + 2] == 0 && k == i - 2 && l == j + 2)))
			{
				return 1;
			}
		}
	}
	if (tura == 2)
	{

		if (((dame[i + 1][j - 1] == 0 && k == i + 1 && l == j - 1) || (dame[i + 1][j + 1] == 0 && k == i + 1 && l == j + 1)) || ((dame[i + 2][j - 2] == 0 && k == i + 2 && l == j - 2 && (dame[i + 1][j - 1] == 1 || dame[i + 1][j - 1] == 3)) || (dame[i + 2][j + 2] == 0 && k == i + 2 && l == j + 2 && (dame[i + 1][j + 1] == 1 || dame[i + 1][j + 1] == 3))))
		{
			return 1;
		}
		return 0;
	}
	if (tura == 1)
	{
		if (((dame[i - 1][j - 1] == 0 && k == i - 1 && l == j - 1) || (dame[i - 1][j + 1] == 0 && k == i - 1 && l == j + 1)) || ((dame[i - 2][j - 2] == 0 && k == i - 2 && l == j - 2 && (dame[i - 1][j - 1] == 2 || dame[i - 1][j - 1] == 4)) || (dame[i - 2][j + 2] == 0 && k == i - 2 && l == j + 2 && (dame[i - 1][j + 1] == 2 || dame[i - 1][j + 1] == 4))))
		{
			return 1;
		}
		return 0;
	}
}
int VerificarePozitie(int i, int j, int tura)
{
	if (i >= 0 && i < 8 && j >= 0 && j < 8)
	{
		if (j == 0)
		{

			if (tura == 1)
			{
				if (dame[i][j] == 1 || dame[i][j] == 3)
				{
					if (dame[i - 1][j + 1] == 0 || (dame[i - 2][j + 2] == 0 && (dame[i - 1][j + 1] == 2 || dame[i - 1][j + 1] == 4)))
					{
						if (((i + j) % 2) != 0 && dame[i][j] != 0)
							return 1;
						else
							return 0;
					}
					return 0;
				}
				return 0;
			}
			if (tura == 2)
			{
				if (dame[i][j] == 2 || dame[i][j] == 4)
				{
					if (dame[i + 1][j + 1] == 0 || (dame[i + 2][j + 2] == 0 && (dame[i + 1][j + 1] == 1 || dame[i + 1][j + 1] == 3)))
					{
						if (((i + j) % 2) != 0 && dame[i][j] != 0)
							return 1;
						else
							return 0;
					}
					return 0;
				}
				return 0;
			}
		}
		if (j == 7)
		{
			if (tura == 1)
			{
				if (dame[i][j] == 1 || dame[i][j] == 3)
				{
					if (dame[i - 1][j - 1] == 0 || (dame[i - 2][j - 2] == 0 && (dame[i - 1][j - 1] == 2 || dame[i - 1][j - 1] == 4)))
					{
						if (((i + j) % 2) != 0 && dame[i][j] != 0)
							return 1;
						else
							return 0;
					}
					return 0;
				}
				return 0;
			}
			if (tura == 2)
			{
				if (dame[i][j] == 2 || dame[i][j] == 4)
				{
					if (dame[i + 1][j - 1] == 0 || (dame[i + 2][j - 2] == 0 && (dame[i + 1][j - 1] == 2 || dame[i + 1][j - 1] == 4)))
					{
						if (((i + j) % 2) != 0 && dame[i][j] != 0)
							return 1;
						else
							return 0;
					}
					return 0;
				}
				return 0;
			}
		}

		if (tura == 1)
		{
			if (dame[i][j] == 1 || dame[i][j] == 3)
			{
				if (dame[i - 1][j - 1] == 0 || dame[i - 1][j + 1] == 0 || (dame[i - 2][j - 2] == 0 && (dame[i - 1][j - 1] == 2 || dame[i - 1][j - 1] == 4)) || (dame[i - 2][j + 2] == 0 && (dame[i - 1][j + 1] == 2 || dame[i - 1][j + 1] == 4)))
				{
					if (((i + j) % 2) != 0 && dame[i][j] != 0)
						return 1;
					else
						return 0;
				}
				return 0;
			}
		}
		if (tura == 2)
		{
			if (dame[i][j] == 2 || dame[i][j] == 4)
			{
				if (dame[i + 1][j - 1] == 0 || dame[i + 1][j + 1] == 0 || (dame[i + 2][j - 2] == 0 && (dame[i + 1][j - 1] == 1 || dame[i + 1][j - 1] == 3)) || (dame[i + 2][j + 2] == 0 && (dame[i + 1][j + 1] == 1 || dame[i + 1][j + 1] == 3)))
				{
					if (((i + j) % 2) != 0 && dame[i][j] != 0)
						return 1;
					else
						return 0;
				}
				return 0;
			}
		}
	}
	return 0;
}
int VerificareDubla(int i, int j, int k, int l, int tura)
{
	if (dame[i][j] == 3 || dame[i][j] == 4)
	{
		if ((k == i - 2 && l == j - 2) || (k == i - 2 && l == j + 2))
			return 1;
		if ((k == i + 2 && l == j - 2) || (k == i + 2 && l == j + 2))
			return 1;
	}
	if (tura == 1)
	{
		if ((k == i - 2 && l == j - 2) || (k == i - 2 && l == j + 2))
			return 1;
	}
	if (tura == 2)
	{
		if ((k == i + 2 && l == j - 2) || (k == i + 2 && l == j + 2))
			return 1;
	}
	return 0;
}
int ContinuareMutare(int k, int l, int tura)
{
	if (dame[k][l] == 3)
	{
		if (dame[k - 2][l - 2] == 0)
		{
			if (dame[k - 1][l - 1] == 2 || dame[k - 1][l - 1] == 4)
				return 1;
		}
		if (dame[k - 2][l + 2] == 0)
		{
			if (dame[k - 1][l + 1] == 2 || dame[k - 1][l + 1] == 4)
				return 1;
		}
		if (dame[k + 2][l - 2] == 0)
		{
			if (dame[k + 1][l - 1] == 2 || dame[k + 1][l - 1] == 4)
				return 1;
		}
		if (dame[k + 2][l + 2] == 0)
		{
			if (dame[k + 1][l + 1] == 2 || dame[k + 1][l + 1] == 4)
				return 1;
		}
	}
	if (dame[k][l] == 4)
	{
		if (dame[k + 2][l - 2] == 0)
		{
			if (dame[k + 1][l - 1] == 1 || dame[k + 1][l - 1] == 3)
				return 1;
		}
		if (dame[k + 2][l + 2] == 0)
		{
			if (dame[k + 1][l + 1] == 1 || dame[k + 1][l + 1] == 3)
				return 1;
		}
		if (dame[k - 2][l - 2] == 0)
		{
			if (dame[k - 1][l - 1] == 1 || dame[k - 1][l - 1] == 3)
				return 1;
		}
		if (dame[k - 2][l + 2] == 0)
		{
			if (dame[k - 1][l + 1] == 1 || dame[k - 1][l + 1] == 3)
				return 1;
		}
	}
	if (tura == 1)
	{
		if (dame[k - 2][l - 2] == 0)
		{
			if (dame[k - 1][l - 1] == 2 || dame[k - 1][l - 1] == 4)
				return 1;
		}
		if (dame[k - 2][l + 2] == 0)
		{
			if (dame[k - 1][l + 1] == 2 || dame[k - 1][l + 1] == 4)
				return 1;
		}
	}
	if (tura == 2)
	{
		if (dame[k + 2][l - 2] == 0)
		{
			if (dame[k + 1][l - 1] == 1 || dame[k + 1][l - 1] == 3)
				return 1;
		}
		if (dame[k + 2][l + 2] == 0)
		{
			if (dame[k + 1][l + 1] == 1 || dame[k + 1][l + 1] == 3)
				return 1;
		}
	}
	return 0;
}
int Clasament(int vectorid[100])
{
	printf("ID-ul unic   Punctajul");
	for (int i = 0; i < 100; i++)
		printf("%d   %d", i, vectorid[i]);
}
int RandomID(int id)
{
	//int id=-1;
	srand(time(NULL));
	id = rand() % 100;

	return id;
}
int RandomID2(int id2)
{
	//int id=-1;
	srand(time(NULL));
	id2 = rand() % 100;
	id2 = rand() % 100;

	return id2;
}
int id1, id2, length1 = -1, length2 = -1;
int linia1, linia2, coloana1, coloana2;
char coloanaprimita;
int mutareok = 1, pozitieok = 1;
extern int errno;
int main()
{
	struct sockaddr_in server;
	struct sockaddr_in from;
	int sd;
	int optval = 1;
	int OK = 1, NOTOK = 0;
	int pozitie = 1, mutare = 1; //cu aceaste variabila vom relua procesul de trimitere a coordonatelor piesei
	int continuare = 0;
	int tipul = 0, tip1, tip2;
	int detinereid1, detinereid2; //mesajul de la client in cazul in care are deja asignat un id
	FILE *fptr;

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Nu am putut crea un socket\n");
		return errno;
	}
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	bzero(&server, sizeof(server));
	bzero(&from, sizeof(from));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);

	if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
	{
		perror("Nu am putut apela functia bind().\n");
		return errno;
	}

	if (listen(sd, 1) == -1)
	{
		perror("[server]Eroare la listen().\n");
		return errno;
	}

	while (1)
	{
		int tura, client1, client2;
		int length = sizeof(from);
		char nickname1[10], nickname2[10];

		printf("Asteptam la portul %d...\n", PORT);
		fflush(stdout);

		/*acceptam cei 2 clienti necesari pentru inceperea jocului*/
		client1 = accept(sd, (struct sockaddr *)&from, &length);
		client2 = accept(sd, (struct sockaddr *)&from, &length);

		if (client1 < 0)
		{
			perror("[server]Eroare la accept().\n");
			continue;
		}

		if (client2 < 0)
		{
			perror("[server]Eroare la accept().\n");
			continue;
		}

		printf("Am primit 2 jucatori.Putem incepe jocul!\n");
		fflush(stdout);
		int pid;
		if ((pid = fork()) == -1)
		{
			close(client1);
			close(client2);
			continue;
		}
		else if (pid > 0)
		{
			// parinte
			close(client1);
			close(client2);
			while (waitpid(-1, NULL, WNOHANG))
				;
			continue;
		}
		else if (pid == 0)
		{
			// copil
			close(sd);
			bzero(nickname1, 10);
			bzero(nickname2, 10);

			read(client1, nickname1, 10);
			read(client2, nickname2, 10);

			write(client1, nickname2, 10);
			write(client2, nickname1, 10);

			do
			{
				read(client1, &tip1, sizeof(int));
				read(client2, &tip2, sizeof(int));
				if (tip1 == tip2 == 1)
				{
					write(client1, &OK, sizeof(int));
					write(client2, &OK, sizeof(int));
					tipul = 1;
				}
				if (tip1 == tip2 == 2)
				{
					write(client1, &OK, sizeof(int));
					write(client2, &OK, sizeof(int));
					tipul = 2;
				}
				if (tip1 != tip2)
				{
					write(client1, &NOTOK, sizeof(int));
					write(client2, &NOTOK, sizeof(int));
					tipul = 0;
				}
			} while (tipul == 0);
			printf("TIPUL ESTE: %d\n", tip1);
			/*acum trebuie sa asignam ID-ul unic pentru clasament*/
			read(client1, &detinereid1, sizeof(int));
			read(client2, &detinereid2, sizeof(int));
			if (detinereid1 == 0)
			{
				id1 = RandomID(id1);
				printf("%d\n", id1);
				fflush(stdout);
				write(client1, &id1, sizeof(int));
				printf("Am trimis id1\n");
				fflush(stdout);
			}
			if (detinereid1 == 1)
			{
				read(client1, &id1, sizeof(int));
				printf("%d", id1);
			}

			if (detinereid2 == 0)
			{
				id2 = RandomID2(id2);
				printf("Am asignat id2\n");
				fflush(stdout);
				printf("%d\n", id2);
				fflush(stdout);
				write(client2, &id2, sizeof(int));
			}
			if (detinereid2 == 1)
			{
				read(client1, &id2, sizeof(int));
				printf("%d\n", id2);
			}

			if (tip1 == 1)
			{
				fptr = fopen("/mnt/c/Users/inqui/Desktop/RC-Dame/dame.txt", "a");
				fprintf(fptr, "%d\n", id1);
				fclose(fptr);
				fptr = fopen("/mnt/c/Users/inqui/Desktop/RC-Dame/dame.txt", "a");
				fprintf(fptr, "%d\n", id2);
				fclose(fptr);
			}

			if (tip1 == 2)
			{
				fptr = fopen("/mnt/c/Users/inqui/Desktop/RC-Dame/suicide.txt", "a");
				fprintf(fptr, "%d\n", id1);
				fclose(fptr);
				fptr = fopen("/mnt/c/Users/inqui/Desktop/RC-Dame/suicide.txt", "a");
				fprintf(fptr, "%d\n", id2);
				fclose(fptr);
			}

			InitializareDame(dame);
			AfisareDame(dame);
			fflush(stdout);
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
				{
					write(client1, &dame[i][j], sizeof(int));
					write(client2, &dame[i][j], sizeof(int));
				}

			do
			{
				AfisareDame(dame);
				fflush(stdout);

				tura = 1;
				if (tura == 1)
				{
					write(client1, &OK, sizeof(int));
					write(client2, &NOTOK, sizeof(int));
					do
					{
						do
						{
							for (int i = 0; i < 8; i++) //trimitem matricea din acest moment la client1
								for (int j = 0; j < 8; j++)
								{
									write(client1, &dame[i][j], sizeof(int));
								}
							/*aici vom primi coordonatele din partea clientului*/
							read(client1, &linia1, sizeof(int));
							printf("%d\n", linia1);
							fflush(stdout);
							read(client1, &coloana1, sizeof(int));
							printf("%d\n", coloana1);
							fflush(stdout);
							if (VerificarePozitie(linia1, coloana1, tura) == 1)
							{
								write(client1, &OK, sizeof(int));
								pozitie = 1;
								printf("Pozitia este OK!\n");
								fflush(stdout);
							}
							if (VerificarePozitie(linia1, coloana1, tura) == 0)
							{
								write(client1, &NOTOK, sizeof(int));
								pozitie = 0;
								printf("Pozitia NU este OK!\n");
								fflush(stdout);
							}
						} while (pozitie == 0);

						do
						{
							read(client1, &linia2, sizeof(int));
							printf("%d\n", linia2);
							fflush(stdout);
							read(client1, &coloana2, sizeof(int));
							printf("Coloana 2 este: %d\n", coloana2);
							fflush(stdout);
							if (VerificareMutare(linia1, coloana1, linia2, coloana2, tura) == 1)
							{
								write(client1, &OK, sizeof(int));
								mutare = 1;
								printf("Mutarea este OK!\n");
							}
							if (VerificareMutare(linia1, coloana1, linia2, coloana2, tura) == 0)
							{
								write(client1, &NOTOK, sizeof(int));
								mutare = 0;
								printf("Mutarea NU este OK!\n");
							}
						} while (mutare == 0);
						AdaugareMutare(linia1, coloana1, linia2, coloana2, tura);
						StergerePiesa(linia1, coloana1, tura);
						printf("Punctaj 1: %d Punctaj 2: %d\n", puncte1, puncte2);
						printf("LINIA 2: %d COLOANA 2: %d\n", linia2, coloana2);
						fflush(stdout);

						for (int i = 0; i < 8; i++) //trimitem matricea dupa mutare
							for (int j = 0; j < 8; j++)
							{
								write(client1, &dame[i][j], sizeof(int));
							}
						if (VerificareDubla(linia1, coloana1, linia2, coloana2, tura) == 1)
						{
							if (ContinuareMutare(linia2, coloana2, tura) == 1)
							{
								continuare = 1;
								write(client1, &OK, sizeof(int));
								printf("Se mai poate efectua o mutare!\n");
							}
							if (ContinuareMutare(linia2, coloana2, tura) == 0)
							{
								continuare = 0;
								write(client1, &NOTOK, sizeof(int));
								printf("NU se mai poate efectua o mutare!\n");
							}
						}
						if (VerificareDubla(linia1, coloana1, linia2, coloana2, tura) == 0)
						{
							write(client1, &NOTOK, sizeof(int));
							continuare = 0;
							printf("NU se mai poate efectua o mutare!\n");
						}
					} while (continuare == 1);
					if (VerificareCastigator() == 0)
					{
						write(client1, &NOTOK, sizeof(int));
						write(client2, &NOTOK, sizeof(int));
					}
					if (VerificareCastigator() == 1)
					{
						write(client1, &OK, sizeof(int));
						write(client2, &OK, sizeof(int));
					}
					AfisareDame(dame);
					fflush(stdout);
				}

				tura = 2;
				/*CLIENTUL 2*/
				if (tura == 2)
				{
					write(client1, &NOTOK, sizeof(int));
					write(client2, &OK, sizeof(int));
					do
					{
						do
						{
							for (int i = 0; i < 8; i++) //trimitem matricea din acest moment la client1
								for (int j = 0; j < 8; j++)
								{
									write(client2, &dame[i][j], sizeof(int));
								}
							read(client2, &linia1, sizeof(int));
							printf("%d\n", linia1);
							fflush(stdout);
							read(client2, &coloana1, sizeof(int));
							printf("%d\n", coloana1);
							fflush(stdout);
							if (VerificarePozitie(linia1, coloana1, tura) == 1)
							{
								write(client2, &OK, sizeof(int));
								pozitie = 1;
								printf("Pozitia este OK!\n");
								fflush(stdout);
							}
							if (VerificarePozitie(linia1, coloana1, tura) == 0)
							{
								write(client2, &NOTOK, sizeof(int));
								pozitie = 0;
								printf("Pozitia NU este OK!\n");
							}
						} while (pozitie == 0);

						do
						{
							read(client2, &linia2, sizeof(int));
							printf("%d\n", linia2);
							fflush(stdout);
							read(client2, &coloana2, sizeof(int));
							printf("Coloana 2 este: %d\n", coloana2);
							fflush(stdout);
							if (VerificareMutare(linia1, coloana1, linia2, coloana2, tura) == 1)
							{
								write(client2, &OK, sizeof(int));
								mutare = 1;
								printf("Mutarea este OK!\n");
							}
							if (VerificareMutare(linia1, coloana1, linia2, coloana2, tura) == 0)
							{
								write(client2, &NOTOK, sizeof(int));
								mutare = 0;
								printf("Mutarea NU este OK!\n");
							}
						} while (mutare == 0);
						AdaugareMutare(linia1, coloana1, linia2, coloana2, tura);
						StergerePiesa(linia1, coloana1, tura);
						printf("LINIA 2: %d COLOANA 2: %d", linia2, coloana2);
						fflush(stdout);

						for (int i = 0; i < 8; i++) //trimitem matricea dupa mutare
							for (int j = 0; j < 8; j++)
							{
								write(client2, &dame[i][j], sizeof(int));
							}
						if (VerificareDubla(linia1, coloana1, linia2, coloana2, tura) == 1)
						{
							if (ContinuareMutare(linia2, coloana2, tura) == 1)
							{
								continuare = 1;
								write(client2, &OK, sizeof(int));
								printf("Se mai poate efectua o mutare!\n");
							}
							if (ContinuareMutare(linia2, coloana2, tura) == 0)
							{
								continuare = 0;
								write(client2, &NOTOK, sizeof(int));
								printf("NU se mai poate efectua o mutare!\n");
							}
						}
						if (VerificareDubla(linia1, coloana1, linia2, coloana2, tura) == 0)
						{
							write(client2, &NOTOK, sizeof(int));
							continuare = 0;
							printf("NU se mai poate efectua o mutare!\n");
						}

					} while (continuare == 1);
					if (VerificareCastigator() == 0)
					{
						write(client2, &NOTOK, sizeof(int));
						write(client1, &NOTOK, sizeof(int));
						printf("Nu avem un castigator!\n");
						fflush(stdout);
					}
					if (VerificareCastigator() == 1)
					{
						write(client1, &OK, sizeof(int));
						write(client2, &OK, sizeof(int));
						printf("Avem un castigator!\n");
						fflush(stdout);
					}
				}
				tura = 1;
			} while (VerificareCastigator() == 0);

			if (puncte1 == 12)
			{
				if (tip1 == 1)
				{
					write(client1, &OK, sizeof(int));
					write(client2, &NOTOK, sizeof(int));
					fptr = fopen("/mnt/c/Users/inqui/Desktop/RC-Dame/dame.txt", "a");
					fprintf(fptr, "%d\n", id1);
					fclose(fptr);
				}
				if (tip1 == 2)
				{
					write(client1, &NOTOK, sizeof(int));
					write(client2, &OK, sizeof(int));
					fptr = fopen("/mnt/c/Users/inqui/Desktop/RC-Dame/suicide.txt", "a");
					fprintf(fptr, "%d\n", id2);
					fclose(fptr);
				}
			}
			if (puncte2 == 12)
			{
				if (tip1 == 1)
				{
					write(client1, &NOTOK, sizeof(int));
					write(client2, &OK, sizeof(int));
					fptr = fopen("/mnt/c/Users/inqui/Desktop/RC-Dame/dame.txt", "a");
					fprintf(fptr, "%d\n", id2);
					fclose(fptr);
				}
				if (tip1 == 2)
				{
					write(client1, &OK, sizeof(int));
					write(client2, &NOTOK, sizeof(int));
					fptr = fopen("/mnt/c/Users/inqui/Desktop/RC-Dame/suicide.txt", "a");
					fprintf(fptr, "%d\n", id1);
					fclose(fptr);
				}
			}

			if (tip1 == 1)
			{
				fptr = fopen("/mnt/c/Users/inqui/Desktop/RC-Dame/dame.txt", "r");
				while (fptr)
				{
					fscanf(fptr, "%d", &id);
					vectorid[id]++;
				}
				fclose(fptr);
			}

			if (tip1 == 2)
			{
				fptr = fopen("/mnt/c/Users/inqui/Desktop/RC-Dame/suicide.txt", "r");
				while (fptr)
				{
					fscanf(fptr, "%d", &id);
					vectorid[id]++;
				}
				fclose(fptr);
			}
			for (int i = 0; i < 100; i++) //trimitem clasamentul final
			{
				write(client1, &vectorid[i], sizeof(int));
				write(client2, &vectorid[i], sizeof(int));
			}

			close(client1);
			close(client2);
			exit(0);
		}
	}
}
