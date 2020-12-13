#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <locale.h>

#define SIGNLEN 1000

int SignatureComparison(long int SignIndent, char *FileAdrr, char *SignName)
{
  if(FileAdrr == NULL)
  {
    printf("\a\nArgument error!");
    return 2;
  }
  if(SignName == NULL)
  {
    printf("\a\nArgument error!");
    return 3;
  }
  int Error;
  FILE* NoDer;
  char Mz[2];
  char *Sign;
  Sign = (char*)malloc((strlen(SignName) + 1) * sizeof(char));
  if(Sign == NULL)
  {
    printf("\a\nMemory allocation error!");
    return 4;
  }
  NoDer = fopen(FileAdrr, "rb");
  if(NoDer == NULL)
  {
    printf("\a\nError opening file!");
    return 5;
  }
  if(fread(Mz, sizeof(char), 2, NoDer) != 2)
  {
    if(!feof(NoDer))
    {
      printf("\a\nError reading from file 1!");
      return 6;
    }
  }

  if(Mz[0] != 'M' || Mz[1] != 'Z')
  {
    Error = printf("\t\tClear\n");
    if(Error == 0)
    {
      printf("\a\nError printf1!");
      return 7;
    }
    if(fclose(NoDer) == EOF)
    {
      printf("\a\nError closing file!");
      return 8;
    }
    return 0;
  }
  else
  {
    Error = fseek(NoDer, SignIndent, SEEK_SET);
    if(Error != 0)
    {
      printf("\a\nFile shift error!");
      return 9;
    }
    if(fread(Sign, sizeof(char), strlen(SignName) + 1, NoDer) != strlen(SignName) + 1)
    {
      if(!feof(NoDer))
      {
        printf("\a\nError reading from file 2!");
        return 10;
      }
    }
    if(strcmp(Sign, SignName) == 0)
    {
      Error = printf("\a\t\tDanger\t\t%s\n",  SignName);
      if(Error < 0)
      {
        printf("\a\nError printf 1!");
        return 11;
      }
      Error = system("pause");
      if(Error != 0)
      {
        printf("\a\nError in the \"systems\" function!");
        return 12;
      }
      if(fclose(NoDer) == EOF)
      {
        printf("\a\nError closing file!");
        return 13;
      }
      return 0;
    }
  	else
    {
      Error = printf("\t\tClear\n");
      if(Error < 0)
      {
        printf("\a\nError printf 2!");
        return 14;
      }
      if(fclose(NoDer) == EOF)
      {
        printf("\a\nError closing file!");
        return 15;
      }
      return 0;
    }
  }
}

int ScanfDerr(char *DerName)
{
  if(DerName == NULL)
  {
    printf("\a\nArgument error!");
    return 1;
  }
  int Error, i = 0;
  Error = printf("DerName: ");
  if(Error == 0)
  {
    printf("\a\nError printf 1!");
    return 2;
  }
  while((DerName[i] = getchar()) != '\n')
  {
  	if(DerName[i] == EOF)
  	{
  		printf("\a\nError in %d getchr", i);
  		return 3;
	  }
  	i++;
  }
  DerName[i] = '\0';
  if(fflush(stdin) != 0)
  {
    printf("\a\nError clearing the stream stdin!");
    return 4;
  }
  return 0;
}


int ScanSign(char *SignName, long int *SignIndent)
{
  if(SignName == NULL)
  {
    printf("\a\nArgument error!");
    return 1;
  }
  int Error, j, i = 0, Len = 0;
  char Num[100];
  FILE* File;

  File = fopen("sign.txt", "r");
  if(File == NULL)
  {
    printf("\a\aCannot open file!");
    return 3;
  }
  while((SignName[i] = fgetc(File)) != '\n')
  {
  	if(SignName[i] == EOF)
  	{
  		printf("\a\aError %d fgetc1!", i);
  		return 4;
	}
	i++;
  }

  SignName[i] = '\0';

  i = 0;

  while((Num[i] = fgetc(File)) != EOF)
  {
    if(Num[i] == EOF)
    {
		printf("\a\aError %d fgetc 2!", i);
    	return 5;
  	}
  	i++;
  }

  Num[i] = '\0';

  for(j = 0; i > 0; i--, j++)
  {
  		if(Num[j] >= '0' && Num[j] <= '9') *SignIndent += (Num[j] - '0') * pow(10, i - 1);
  }

  Error = fclose(File);
  if(Error == EOF)
  {
    printf("\a\aError fclose");
    return 6;
  }
  return 0;
}


int FindFileInDer(char *DerName, char *SignName, long int SignIndent)
{
  if(DerName == NULL)
  {
    printf("\a\nArgument error!");
    return 1;
  }
  if(SignName == NULL)
  {
    printf("\a\nArgument error!");
    return 2;
  }
  int Error;
  HANDLE hFile = NULL;
  FILE* NoDer;
  WIN32_FIND_DATAA DataInfo = {0};
 	char Next1[MAX_PATH] = {0}, Next2[MAX_PATH] = {0}, FileAdrr[MAX_PATH] = {0};
 	Error = printf("%s\n", DerName);
  if(Error < 0)
  {
    printf("\a\nError printf 1!");
    return 4;
  }
 	hFile = FindFirstFileA(DerName, &DataInfo);
 	do
 	{
   		if((0 == lstrcmp(DataInfo.cFileName, ".")) || (0 == lstrcmp(DataInfo.cFileName, "..")) || (0 == lstrcmp(DataInfo.cFileName, "$Recycle.Bin")) || (0 == lstrcmp(DataInfo.cFileName, "Documents and Settings")))
   		{
   	    	continue;
   		}
   		if(DataInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
   		{
   			if(strcat(Next1, DerName) == NULL)
        {
          printf("\a\nError in str cat!");
          return 5;
        }
		Next1[strlen(Next1) - 1] = '\0';
        if(strcat(Next1, DataInfo.cFileName) == NULL)
        {
          printf("\a\nError in str cat!");
          return 6;
        }

   		Error = printf("\tThis podder %s\n", DataInfo.cFileName);
        if(Error < 0)
        {
          printf("\a\nError printf 2!");
          return 7;
        }
        if(strcat(Next1, "\\*") == NULL)
        {
          printf("\a\nError in str cat!");
          return 8;
        }

       	Error = FindFileInDer(Next1, SignName, SignIndent);
        if(Error != 0)
        {
          printf("\a\nError in FindFileInDer!");
          return 9;
        }
       	Next1[0] = '\0';
        if(strcat(Next1, Next2) == NULL)
        {
          printf("\a\nError in str cat!");
          return 10;
        }
		}
		else
		{
			Error = printf("\t\t%s", DataInfo.cFileName);
      		if(Error < 0)
      		{
        		printf("\a\nError printf 3!");
        		return 11;
      		}
      		if(strcat(FileAdrr, DerName) == NULL)
      		{
        		printf("\a\nError in str cat!");
        		return 12;
      		}
			FileAdrr[strlen(FileAdrr) - 1] = '\0';
      		if(strcat(FileAdrr, DataInfo.cFileName) == NULL)
      		{
        		printf("\a\nError in str cat!");
        		return 13;
      		}
			Error = SignatureComparison(SignIndent, FileAdrr, SignName);
      		if(Error != 0)
      		{
        		printf("\a\nError in SignatureComparison!");
            	return 14;
      		}
			FileAdrr[0] = '\0';
		}
	}while(FindNextFileA(hFile, &DataInfo));
  return 0;
}

int main()
{
  int Error;
  long int SignIndent = 0;
  char DerName[MAX_PATH], SignName[SIGNLEN];
  setlocale(LC_ALL, "Rus");
  Error = ScanfDerr(DerName);
  if(Error != 0)
  {
  	printf("Error ScanfDerr");
  	return 0;
  }
  Error = ScanSign(SignName, &SignIndent);
  if(Error != 0)
  {
    printf("Error ScanSign");
    return 2;
  }
  Error = system("cls");
  if(Error != 0)
  {
    printf("\a\nError in the \"systems\" function!");
    return 3;
  }
  Error = FindFileInDer(DerName, SignName, SignIndent);
  if(Error != 0)
  {
    printf("\a\aError FindFileInDer!");
    return 4;
  }
  system("pause");
  return 0;
}
