//-----------------------------------------------------------------------------
//
//	This sample program shows how to log data to a DIAdem file.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
#include "nilibddc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//-----------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------
#define ddcChk(f) if (ddcError = (f), ddcError < 0) goto Error; else

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
#define				NUM_DATA_PTS	128
static const char * FILE_PATH		= ".\\sampleFile.tdm";
static const char *	FILE_NAME		= "DIAdem Log Data Example";
static const char *	FILE_DESC		= "Data file created by example";
static const char *	GROUP_NAME		= "Simulated Data";
static const char *	GROUP_DESC		= "Simulated data generated by the example";
static const char *	CHANNEL1_NAME	= "Channel One";
static const char *	CHANNEL2_NAME	= "Channel Two";
static const char *	CHANNEL1_DESC	= "Data for Channel One";
static const char *	CHANNEL2_DESC	= "Data for Channel Two";
static const char *	CHANNEL1_UNITS	= "Volts";
static const char *	CHANNEL2_UNITS	= "Volts";

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
static void GetSineData (int numDataPoints, double *dataBuffer);
static void GetRandomData (int numDataPoints, double *dataBuffer);

//-----------------------------------------------------------------------------
// Program entry-point function
//-----------------------------------------------------------------------------
int main (int argc, char *argv[])
{
	int						ddcError = 0;
	DDCFileHandle			file = 0;
	DDCChannelGroupHandle	group;
	DDCChannelHandle		channels[2];
	double					channel1Data[NUM_DATA_PTS], channel2Data[NUM_DATA_PTS];

	// If file exists, delete it.
	remove (FILE_PATH);

	printf ("Generating data file...\n");

	// Create file and add channel group and channels.
	ddcChk (DDC_CreateFile (FILE_PATH, "TDM", FILE_NAME, FILE_DESC, "", "", &file));
	ddcChk (DDC_AddChannelGroup (file, GROUP_NAME, GROUP_DESC, &group));
	ddcChk (DDC_AddChannel (group, DDC_Double, CHANNEL1_NAME,
		CHANNEL1_DESC, CHANNEL1_UNITS, &channels[0]));
	ddcChk (DDC_AddChannel (group, DDC_Double, CHANNEL2_NAME,
		CHANNEL2_DESC, CHANNEL2_UNITS, &channels[1]));

	GetSineData (NUM_DATA_PTS, channel1Data);
	GetRandomData (NUM_DATA_PTS, channel2Data);

	// Write the data in the channels
	ddcChk (DDC_SetDataValues (channels[0], channel1Data, NUM_DATA_PTS));
	ddcChk (DDC_SetDataValues (channels[1], channel2Data, NUM_DATA_PTS));

	// Save the file
	ddcChk (DDC_SaveFile (file));

Error:
	// Close the file and report any errors
	if (file)
		DDC_CloseFile (file);
	if (ddcError < 0)
		printf ("\nError: %s\n", DDC_GetLibraryErrorDescription(ddcError));
	else
		printf ("\nNo errors.\n");
	printf("End of program, press Enter key to quit\n");
	getchar();
	return 0;
}

//-----------------------------------------------------------------------------
// Helper functions
//-----------------------------------------------------------------------------
static void GetSineData (int numDataPoints, double *dataBuffer)
{
	int 	i;
	double 	radianIncrement = 2 * 3.14159 / numDataPoints;

	for (i = 0; i < numDataPoints; i++)
		dataBuffer[i] = sin (i * radianIncrement);
}

static void GetRandomData (int numDataPoints, double *dataBuffer)
{
	int i;

	for (i = 0; i < numDataPoints; i++)
		dataBuffer[i] = rand () / (double)RAND_MAX;
}
//-----------------------------------------------------------------------------
