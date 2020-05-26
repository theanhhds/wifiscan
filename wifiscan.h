typedef struct
	{
		unsigned char MAC[20];	// MAC address 6 bytes
		int channel;		// Channel number 1-13
		double frequency;	// Frequency of this channel
		char essid[100];	// ESSID of the network
		int slevel;		// Signal level in dBm
	}WIFI_INFO;

#define CMD "sudo iwlist wlan0 scan | egrep \"Address|Frequency|ESSID|Quality\" > scan.txt"
//#define DEBUG

//Function prototypes

int read_data(void);
void remove_spaces(char []);
void get_MAC(char [], char []);
double get_frequency(char []);
int get_slevel(char []);
void get_essid(char [], char[]);
int get_channel(char *);
void show_wifi_data(WIFI_INFO [], int);
