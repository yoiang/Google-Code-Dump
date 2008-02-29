#include "FTPClient.h"

int GetCode(char *szMessage)
{
	char cTemp = szMessage[3] ;
	szMessage[3] = '\0' ;
	int iCode = atoi(szMessage) ;
	szMessage[3] = cTemp ;
	return iCode ;
}

void HandleCommand(Client &FTPClient, char *szCommand)
{
	char szBuffer[256] ;
	int iLen = 0 ;
	while (szCommand[iLen] != '\0')
	{
		if (szCommand[iLen] == ' ')
		{
			szCommand[iLen] = '\0' ;
			break ;
		}
		iLen ++ ;
	}

	if (stricmp(szCommand, "OPEN") == 0)
	{
		if (FTPClient.Connect(szCommand+5))
			printf("Connected successfully to %s\n", szCommand+5) ;
		else 
		{
			printf("Connection to %s failed\n", szCommand+5) ;
			return ;
		}

		szBuffer[0] = '\0' ;
		while (1)
		{
			FTPClient.RecieveMain(szBuffer, 256) ;
			char *temp = (szBuffer + strlen(szBuffer) - 6) ;
			if (strlen(szBuffer) > 6 && stricmp(szBuffer + strlen(szBuffer) - 6, "ready.") == 0)
				break ;
			if (GetCode(szBuffer) / 100 == 5)
			{
				FTPClient.Disconnect() ;
				return ;
			}
		}
		return ;
	}	else if (stricmp(szCommand, "CLOSE") == 0)
	{
		FTPClient.Disconnect() ;
		return ;
	}	else if (stricmp(szCommand, "EXIT") == 0)
	{
		return ;
	}	else if (stricmp(szCommand, "CD") == 0)
	{
		if (stricmp(szCommand+3, "..") == 0)
			FTPClient.SendMain("CDUP", 4) ;
		else 
		{
			sprintf(szBuffer, "CWD %s", szCommand+3) ;
			FTPClient.SendMain(szBuffer) ;
		}
		FTPClient.RecieveMain(szBuffer, 256) ;
		return ;
	}	else if (stricmp(szCommand, "DELETE") == 0)
	{
		sprintf(szBuffer, "DELE %s", szCommand+7) ;
		FTPClient.SendMain(szBuffer) ;
		FTPClient.RecieveMain(szBuffer, 256) ;
	}	else if (stricmp(szCommand, "USER") == 0)
	{
		szCommand[4] = ' ' ;
		FTPClient.SendMain(szCommand) ;
		FTPClient.RecieveMain(szBuffer, 256) ;
	}	else if (stricmp(szCommand, "PASS") == 0)
	{
		szCommand[4] = ' ' ;
		FTPClient.SendMain(szCommand) ;
		FTPClient.RecieveMain(szBuffer, 256) ;
	}	else if (stricmp(szCommand, "HELP") == 0)
	{
		FTPClient.SendMain("HELP", 4) ;
		FTPClient.RecieveMain(szBuffer, 256) ;
		return ;
	}	else if (stricmp(szCommand, "MKDIR") == 0)
	{
		sprintf(szBuffer, "MKD %s", szCommand+6) ;
		FTPClient.SendMain(szBuffer) ;
		FTPClient.RecieveMain(szBuffer, 256) ;
	}	else if (stricmp(szCommand, "RMDIR") == 0)
	{
		sprintf(szBuffer, "RMD %s", szCommand+6) ;
		FTPClient.SendMain(szBuffer) ;
		FTPClient.RecieveMain(szBuffer, 256) ;
	}	else if (stricmp(szCommand, "LS") == 0)
	{
		FTPClient.PORTRequest() ;
		FTPClient.RecieveMain(szBuffer, 256) ;
		if (GetCode(szBuffer) / 100 != 5)
		{
			FTPClient.SendMain("LIST", 4) ;
			FTPClient.RecieveMain(szBuffer, 256) ;
			if (GetCode(szBuffer) / 100 != 5)
			{
				FTPClient.PORTAccept() ;
				int iRecieved = 256 ;
				while (iRecieved > 2)
				{
					iRecieved = FTPClient.RecievePORT(szBuffer, 256) ;
//					printf("%s\n", szBuffer) ;
				}
				FTPClient.PORTClose() ;
				FTPClient.RecieveMain(szBuffer, 256) ;

			} else
			{
				printf("Error with LIST command\n") ;
			}
		}	else
		{
			printf("PORT request failed, cannot LIST\n") ;
		}
		return ;
	}	else if (stricmp(szCommand, "PWD") == 0)
	{
		FTPClient.SendMain("PWD", 3) ;
		FTPClient.RecieveMain(szBuffer, 256) ;
		return ;
	}	else if (stricmp(szCommand, "RETR") == 0)
	{
		FTPClient.PORTRequest() ;
		FTPClient.RecieveMain(szBuffer, 256) ;
		if (GetCode(szBuffer) / 100 != 5)
		{
			szCommand[4] = ' ' ;
			FTPClient.SendMain(szCommand) ;
			FTPClient.RecieveMain(szBuffer, 256) ;
			if (GetCode(szBuffer) / 100 != 5)
			{
				FILE *pFile ;
				if (FTPClient.GetType() == I_TYPE) pFile = fopen(szCommand + 5, "wb") ;
				else pFile = fopen(szCommand + 5, "w") ;
				FTPClient.PORTAccept() ;
/*				char cTemp = ' ' ;
				char szBuffer[2] ;
				while (szBuffer[0] != 255 && szBuffer[0] != 0)
				{
					FTPClient.RecievePORT(szBuffer, 2) ;
					fputc(szBuffer[0], pFile) ;
					fputc(szBuffer[1], pFile) ;
				}
*/
				char cTemp = ' ' ;
				int iRecieve = 1;
				while (iRecieve > 0)
				{
					iRecieve = FTPClient.RecievePORT(&cTemp, 1) ;
					fputc(cTemp, pFile) ;
				}
				fclose(pFile) ;
				FTPClient.PORTClose() ;
				FTPClient.RecieveMain(szBuffer, 256) ;

			} else
			{
				printf("Error with RETR command\n") ;
			}
		}	
	}	else if (stricmp(szCommand, "STOR") == 0)
	{
		FTPClient.PORTRequest() ;
		FTPClient.RecieveMain(szBuffer, 256) ;
		if (GetCode(szBuffer) / 100 != 5)
		{
			szCommand[4] = ' ' ;
			FTPClient.SendMain(szCommand) ;
			FTPClient.RecieveMain(szBuffer, 256) ;
			if (GetCode(szBuffer) / 100 != 5)
			{
				FILE *pFile ;
				if (FTPClient.GetType() == I_TYPE) pFile = fopen(szCommand + 5, "rb") ;
				else pFile = fopen(szCommand + 5, "r") ;

				if (pFile == NULL) printf("Error opening %s\n", szCommand+5) ;

				FTPClient.PORTAccept() ;
				SOCKET hSocket = FTPClient.GetPORT() ;
				char szBuffer[256] ;
				int iRead ;
				if (pFile != NULL) while (!feof(pFile))
				{
					iRead = fread(szBuffer, sizeof(char), 256, pFile) ;
					send(hSocket, szBuffer, iRead, 0) ;
				}
				fclose(pFile) ;
				FTPClient.PORTClose() ;
				FTPClient.RecieveMain(szBuffer, 256) ;

			} else
			{
				printf("Error with STOR command\n") ;
			}
			return ;
		}	else
		{
			printf("PORT request failed, cannot RETR\n") ;
			return ;
		}
		return ;
	}	else if (stricmp(szCommand, "BINARY") == 0)
	{
		FTPClient.SetType(I_TYPE) ;
		return ;
	}	else if (stricmp(szCommand, "ASCII") == 0)
	{
		FTPClient.SetType(A_TYPE) ;
		return ;
	}	else if (stricmp(szCommand, "REN") == 0)
	{
		int iTrav = 4 ;
		while (szCommand[iTrav] != '\0')
		{
			if (szCommand[iTrav] == ' ')
				szCommand[iTrav] = '\0' ;
			iTrav ++ ;
		}
		sprintf(szBuffer, "RNFR %s", szCommand+4) ;
		FTPClient.SendMain(szBuffer) ;
		FTPClient.RecieveMain(szBuffer, 256) ;
		sprintf(szBuffer, "RNTO %s", szCommand+strlen(szCommand+4)+5) ;
		FTPClient.SendMain(szBuffer) ;
		FTPClient.RecieveMain(szBuffer, 256) ;
	}	else if (stricmp(szCommand, "?") == 0)
	{
		printf("OPEN CLOSE USER PASS EXIT LS PWD CD MKDIR RMDIR RETR STOR REN DELETE HELP\n") ;
		return ;
	}	else
	{
		printf("Invalid command\n") ;
	}
}

int main()
{
	Client FTPClient ;
	char szCommand[256] ;
	szCommand[0] = '\0' ;
	while (stricmp(szCommand, "EXIT") != 0)
	{
		scanf("%256[^\n\0\t]", szCommand) ;
		fflush(stdin) ;
		HandleCommand(FTPClient, szCommand) ;
	}
	FTPClient.Disconnect() ;
	return 0 ;
}