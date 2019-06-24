//
// oled test program
// Written by Larry Bank
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "oled96.h"

int main(int argc, char *argv[])
{
int i, iChannel;
int iOLEDAddr = 0x3c; // typical address; it can also be 0x3d
int iOLEDType = OLED_128x32; // Change this for your specific display
int bFlip = 1, bInvert = 1;

	i = -1;
	iChannel = -1;
	while (i != 0 && iChannel < 2) // try I2C channel 0 through 2
	{
		iChannel++;
		i=oledInit(iChannel, iOLEDAddr, iOLEDType, bFlip, bInvert);
	}
	if (i == 0)
	{
		printf("Successfully opened I2C bus %d\n", iChannel);
		oledFill(0); // fill with black
		oledWriteString(0,0,"OLED 96 Library!",FONT_NORMAL);
		oledWriteString(3,1,"BIG!",FONT_BIG);
		oledWriteString(0,1,"Small", FONT_SMALL);
		for (i=0; i<64; i++)
		{
			oledSetPixel(i, 16+i, 1);
			oledSetPixel(127-i, 16+i, 1);
		}
		printf("Press ENTER to quit\n");
		getchar();
		oledShutdown();
	}
	else
	{
		printf("Unable to initialize I2C bus 0-2, please check your connections and verify the device address by typing 'i2cdetect -y <channel>\n");
	}
   return 0;
} /* main() */
