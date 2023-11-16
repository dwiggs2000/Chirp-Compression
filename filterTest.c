#include <analysis.h>
#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>
#include "filterTest.h"
#include "filterCoefficients.h"
#include "cmplxFilter.h"
#include <stdio.h>
#include <math.h>

static int panelHandle;
double inputI[16384];
double inputQ[16384];
double filtI[16384];
double filtQ[16384];
double outputI[16384];
double outputQ[16384];
double pulse[16384];
double distance[16384];

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "filterTest.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK runFilter (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	FILE *fp;
	int samples = 32768;
	int counter = 0;
	double value;
	switch (event)
	{
		case EVENT_COMMIT:
			//here is where the file from the ADS9 would be imported
			fp = fopen ("20ftCable into 20dBPad.csv", "r");
			if(fp!=-1){
				for(counter=0;counter<samples;counter++){
					if(counter%2==0){
						fscanf (fp, "%lf", &value);
						inputI[counter/2]=value; }
					else{	
						fscanf (fp, "%lf", &value);
						inputQ[counter/2]=value; }
						
				}
				//calculate the distance
				for(counter=0;counter<16384;counter++){
					distance[counter]=0.325*(double)counter;
				}
				//get the correlation filter coefficients
				for(counter=0;counter<16384;counter++){
					filtI[counter]=chirpCorrelationCoef[counter][0];
					filtQ[counter]=chirpCorrelationCoef[counter][1]*-1;
				}
				//fft the input signal
				FFT (inputI, inputQ, 16384);
				//fft the coefficients
				FFT (filtI, filtQ,16384);
				//multiply the fft results in the frequency domain
				for(counter=0;counter<16384;counter++){
					outputI[counter]=inputI[counter]*filtI[counter]-inputQ[counter]*filtQ[counter];
					outputQ[counter]=inputI[counter]*filtQ[counter]+inputQ[counter]*filtI[counter];
				}
				//turn it back into the time domain
				InvFFT (outputI, outputQ, 16384);
				for(counter=0;counter<16384;counter++){
					//find the magnitude of the signals
					pulse[counter]=sqrt(pow(outputI[counter],2)+pow(outputQ[counter],2));
					if(pulse[counter]<1)
						pulse[counter]=1;
					pulse[counter]=20*log10(pulse[counter]);
				}
				//plot it
				PlotXY (panelHandle, PANEL_GRAPH, distance, pulse, 16384, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);	
				
			}
			break;
	}
	return 0;
}

int CVICALLBACK close (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}
