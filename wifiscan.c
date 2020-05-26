#include "wifiscan.h"
#include <stdio.h>
#include <string.h>

int read_data(void)
{
	system("clear");
	FILE *f;
	WIFI_INFO wf[100];
	char line[200];		//a line of data
	int c,index;

	index=-1;
	if ((f = fopen("scan.txt","r"))==NULL)
	{
		printf("Cannot open file %s\n","scan.txt");
		return 1;
	}
	while (fgets(line,200,f)!=NULL)	//read file line by line
	{
		remove_spaces(line);	// remove leading space of the line
		if (strncmp(line, "Cell", 4)==0)
		{
			index++;
			c = 0;		// set line counter to 0
			get_MAC(line,wf[index].MAC);	//the first line contains MAC of AP
		}
		else
		{
			c++;		// line counter increasement
			if (c==1)	// 2nd line, contains frequency/channel No.
				wf[index].channel = get_channel(line);
			if (c==2)	// 3rd line, contains signal level (RSSI)
				wf[index].slevel = get_slevel(line);
			if (c==3)	// 4th line, contains ESSID
			{
				get_essid(line, wf[index].essid);
				if (strlen(wf[index].essid)==0)
					index=index-1;
			}
		}
	}
	show_wifi_data(wf,index);	//Show data
	fclose(f);
}

void remove_spaces(char s[])
//Remove all the none-charater (spaces, \t or \n) from the line
{
	int i, len=strlen(s);
	for (i=0;i<=len;i++)	//Stop when see a character
		if (s[i]!=' ' && s[i]!= '\t' && s[i]!='\n') break;
	strcpy(s,&s[i]);
}

void get_MAC(char line[], char mac[])
//This function use to find the MAC address from the first line of a CELL
//This line is formatted as
//"Cell nn - Address: xx:yy:zz:aa:bb:cc"
//So simply locate the 19th element of line, and use sscanf to scan 6 hexadecimal values
// into macaddr
{
	mac[0]='\0';
	strncpy(mac,&line[19],17);
}

int get_channel(char s[])
//This function use to return a channel number
//Line formatted as |Frequency: 2.245 GHz (Channel x)|
{
	int i,j,len = strlen(s);
	char temp[10] = {'\0'};	//Temporal string, initialized by null char
	for (i=0;i<len;i++)
		if (s[i]==')') break;	//Find ')'
	for (j=i;j>=0;j--)	//find the white space in front of it
		if (s[j]==' ') break;
	strncpy(temp, &s[j+1],i-j-1);
	return atoi(temp);
}

void get_essid(char s[], char essid[])
//This function find ESSID of a cell
//Line formatted as: |ESSID:"<name>"|
{
	essid[0]='\0';
	int i, len = strlen(s);
	for (i=7;i<len;i++)
		if(s[i]=='"') break;		//find the first '"' sign
	strncpy(essid,&s[7],i-7);
	essid[i-7]='\0';
}

int get_slevel(char s[])
//This function find signal level of a Cell
//Line formatted as: "Quality=xx/yy Signal level=-aa dBm"
{
	int i, c ,len = strlen(s);
	char temp[10];

	for (i=0,c=0;i<len;i++)
		if (s[i]== '=')
			if (++c == 2) break;	//Found 2nd '=' sign
	strncpy(temp,&s[i+2],3);
	return atoi(temp);
}

//--------------------Show what we got----------------------------------//
void show_wifi_data(WIFI_INFO wf[], int c)
{
#ifdef DEBUG
	int i=0;
	for (i=0;i<=c;i++)
	{
        	printf("MAC Addres: %s\n",wf[i].MAC);
	        printf("ESSID: %s\n", wf[i].essid);
	        printf("Signal level: -%ddBm\n",wf[i].slevel);
		printf("Wifi channel: %d\n",wf[i].channel);
		printf("Frequency: %.3fGHz\n",0.005*(wf[i].channel-1)+2.412);
		printf("-------------------------------\n");
	}
#else
	//Show graph here
	graph(wf,c);
#endif
}
