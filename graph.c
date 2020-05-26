#include <string.h>
#include <stdio.h>
#include "wifiscan.h"
#include "graph.h"

void setFGcolor(int fg)
{
        printf("\033[%d;1m",fg);
        fflush(stdout);
}

void resetColor(void)
{
        printf("\033[0m");
        fflush(stdout);
}

void gotoXY(int row, int col)
{
        printf("\033[%d;%dH",row,col);
        fflush(stdout);
}

void clearScreen(void)
{
        printf("\033[2J");
        fflush(stdout);
}

void graph(WIFI_INFO wf[], int count)
{
	int i=0;
	int row = 0;
	gotoXY(1,30);
	setFGcolor(32);
	printf("  .;'                     `;,\n"); gotoXY(2,30);	//I coppied this from another project (wifite)
	printf(" .;'  ,;'             `;,  `;,\n");  gotoXY(3,30);
	printf(".;'  ,;'  ,;'     `;,  `;,  `;,\n");  gotoXY(4,30);
	printf("::   ::   :   ( )   :   ::   ::\n");	 gotoXY(5,30);
	printf(" :.  ':.  ':. /_\\ ,:'  ,:'  ,::\n");  gotoXY(6,30);
	printf("  :.  ':.    /___\\    ,:'  ,:\n");  gotoXY(7,30);
	printf("   :.       /_____\\      ,:\n");  gotoXY(8,30);
	printf("           /       \\ \n");	 gotoXY(9,30);
	resetColor();
	gotoXY(10,30);
	printf("Wifi scanner - %d APs were found",count);
	gotoXY(60,1);
	for (i=1;i<=13;i++) printf("%7.d",i);			//Write out the numbers of channels
	for (i=0;i<=count;i++)
	{
		setFGcolor(31+i%10);
		if (-35+wf[i].slevel > 55) row = 55;		//Scale the wifi columns
			else row = -35+wf[i].slevel;		//Scale the wifi columns
		if (row<15) row = 15;
		draw_rec(row,wf[i].channel);			//Draw a rectangular
		gotoXY(row,wf[i].channel*7-strlen(wf[i].essid)/2);	//Goto x;y to write wifi essid
		printf("%s",wf[i].essid);
		resetColor();
	}
}

void draw_rec(int top, int channel)
{
	int i=0;
	for (i=top+1;i<=59;i++)
	{
		gotoXY(i,channel*7-15);
		if (channel*7-15>0)		//If it's still on the screen
			printf("|");
		gotoXY(i,channel*7+15);		//Print the oposite edge
		printf("|");
	}
	for (i=channel*7-15;i<=channel*7+15;i++)//Print the horizontal edge
	{
		gotoXY(top,i);
		if (i>0)
		printf("-");
	}
}
