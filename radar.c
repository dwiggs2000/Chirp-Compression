#include <cvintwrk.h>
#include <userint.h>
#include <ansi_c.h>
#include <stdio.h>
#include <cvidef.h>
#include <analysis.h>
#include <math.h>
#include <utility.h>
#include <formatio.h>
#include <cvirte.h>
#include "filterCoefficients64k.h"
#include "cmplxFilter.h"
#include "radar.h"
#define DATA_LENGTH 65536
#define CompressCallBack 1000
#define CHIRP_START_FREQUENCY 1000.0
#define CHIRP_END_FREQUENCY 2000.0
#define SAMPLING_RATE 10000.0
#define PI 3.14159265358979323846
int *inputArrayI = 	NULL;
int *inputArrayQ = NULL;
int plotXYHandle = 0;
double *timeArray = NULL;
double compressed[DATA_LENGTH];					
double radarData[DATA_LENGTH];
double chirpModel[DATA_LENGTH];
double largeCompressed[DATA_LENGTH * 2];
double inputI[DATA_LENGTH];
double inputQ[DATA_LENGTH];
double filtI[DATA_LENGTH];
double filtQ[DATA_LENGTH];
double outputI[DATA_LENGTH];
double outputQ[DATA_LENGTH];
double pulse[DATA_LENGTH];
double distance[DATA_LENGTH];
static int PanelHandle = 0;

int main(int argc, char *argv[]){



		if(InitCVIRTE(0, argv, 0) == 0)
			printf(-1);
		PanelHandle = LoadPanel(0, "radar.uir", PANEL);
		SetCtrlAttribute(PanelHandle, PANEL_PANEL_GRAPH, ATTR_CALLBACK_FUNCTION_POINTER, goButtonCall);
		SetCtrlAttribute(PanelHandle, PANEL_PANEL_GRAPH, ATTR_CALLBACK_FUNCTION_POINTER, correlateLargeArray); 
		DisplayPanel(PanelHandle);
		RunUserInterface();
		DiscardPanel(PanelHandle);
		CloseCVIRTE();
		
		
		return 0;
		
		

}
   
int CVICALLBACK correlateLargeArray(int panel, int control, int event, void *callbackData, int eventData1, int eventData2 ){

		int samples = 65536;
		int counter = 0;
		double value;
		int maxIndex=0;
    	double max =-1000;
		switch (event)
	{
			case EVENT_COMMIT:
				//here is where the file from the ADS9 would be imported
				{	 
					 
					 int telnetHandle = 0;
					 int ftpHandle = 0;
					 int written = 0;
					 int error = 0;
					 double pulseShifted[65536];
					 //const char* sourceDirectory = "\ ";
					 
					 const char* file1 = "C:\\ChirpWorking\\testI.txt";
					 
					 const char* file2 = "C:\\ChirpWorking\\testQ.txt";
					 
					 char readBuffer[1024];
					 
					 telnetHandle = InetTelnetOpen ("192.168.0.10", 23, 0);
					 error = InetTelnetReadUntil (telnetHandle, readBuffer, 1024, "login:", 25000);
					 error = InetTelnetWrite (telnetHandle, "root", "\r\n", -1, &written, 25000);				 
					 error = InetTelnetReadUntil (telnetHandle, readBuffer, 1024, "word:", 25000);				 
					 error = InetTelnetWrite (telnetHandle, "analog", "\r\n", -1, &written, 25000);				 				 
					 error = InetTelnetReadUntil (telnetHandle, readBuffer, 1024, "#", 25000);				 
									
					 error = InetTelnetWrite (telnetHandle, "cd /root/api/AD9082/src/ad9082_xtra/app_ads9", "\r\n", -1, &written, 25000);
					 error = InetTelnetReadUntil (telnetHandle, readBuffer, 1024, "ads9#", 25000);
					 error = InetTelnetWrite (telnetHandle, "rm test_L0C0.txt", "\r\n", -1, &written, 25000);
					 error = InetTelnetReadUntil (telnetHandle, readBuffer, 1024, "ads9#", 25000);
					 error = InetTelnetWrite (telnetHandle, "rm test_L0C1.txt", "\r\n", -1, &written, 25000); 
					 error = InetTelnetReadUntil (telnetHandle, readBuffer, 1024, "ads9#", 25000);
					 error = InetTelnetWrite (telnetHandle, "./debug/ad9082_xtra rx --cap test 65536", "\r\n", -1, &written, 25000);
					 error = InetTelnetReadUntil (telnetHandle, readBuffer, 1024, "ads9#", 25000);
					 Delay(3);
					 ftpHandle = InetFTPLoginEx ("192.168.0.10", "root", "analog", 60000);
					 if(ftpHandle < 0){ 
								 printf("couldn't connect");
					 }
					 else{
					 			error = InetFTPRetrieveFile (ftpHandle, "C:\\ChirpWorking\\testI.txt", "/root/api/AD9082/src/ad9082_xtra/app_ads9/test_L0C0.txt", INET_FTP_FILE_TYPE_ASCII);
					 			error = InetFTPRetrieveFile (ftpHandle, "C:\\ChirpWorking\\testQ.txt", "/root/api/AD9082/src/ad9082_xtra/app_ads9/test_L0C1.txt", INET_FTP_FILE_TYPE_ASCII);
					 }
			         error = InetFTPClose (ftpHandle);
					 error = InetTelnetClose (telnetHandle); 
					
					FILE *file = fopen(file1, "r");
					
					if (file == NULL){
						MessagePopup("ERROR", "FAILED TO OPEN FILE");
						return 0;
					}
					
					else{
						for(counter=0;counter<samples;counter++){
						
								fscanf (file, "%lf", &value);
								inputI[counter]=value; }
					}
					file = fopen(file2, "r");
					
					if (file == NULL){
						MessagePopup("ERROR", "FAILED TO OPEN FILE");
						return 0;
					}
					
					else{
						for(counter=0;counter<samples;counter++){
						
								fscanf (file, "%lf", &value);
								inputQ[counter]=value; }
					}
						
					//calculate the distance
					for(counter=0;counter<DATA_LENGTH;counter++){
						distance[counter]=0.1625*(double)counter;
					}
					//get the correlation filter coefficients
					for(counter=0;counter<DATA_LENGTH;counter++){
						filtI[counter]=chirpCorrelationCoef64k[counter][0];
						filtQ[counter]=chirpCorrelationCoef64k[counter][1]*-1;
					}
					//fft the input signal
					FFT (inputI, inputQ, DATA_LENGTH);
					//fft the coefficients
					FFT (filtI, filtQ,DATA_LENGTH);
					//multiply the fft results in the frequency domain
					for(counter=0;counter<DATA_LENGTH;counter++){
						outputI[counter]=inputI[counter]*filtI[counter]-inputQ[counter]*filtQ[counter];
						outputQ[counter]=inputI[counter]*filtQ[counter]+inputQ[counter]*filtI[counter];
					}
					//turn it back into the time domain
					InvFFT (outputI, outputQ, DATA_LENGTH);
					for(counter=0;counter<DATA_LENGTH;counter++)
					{
					//find the magnitude of the signals
						pulse[counter]=sqrt(pow(outputI[counter],2)+pow(outputQ[counter],2));
						if(pulse[counter]<1)
							pulse[counter]=1;
						pulse[counter]=20*log10(pulse[counter]);
						if(pulse[counter] > max)
						{
                        	max =  pulse[counter];
                        	maxIndex = counter;
						}
					}
					if(maxIndex > 31){
						for(counter=0;counter<DATA_LENGTH;counter++)
						{
                    		pulseShifted[counter]= pulse[(counter+maxIndex-31)%DATA_LENGTH]-max;
						}
					}
					else{
						 for(counter=0;counter<DATA_LENGTH;counter++)
						{
                    		pulseShifted[counter]= pulse[counter]-max;
						}
					}
					//plot it
					if(plotXYHandle > 0){
					error = DeleteGraphPlot (PanelHandle, PANEL_GRAPH, plotXYHandle, VAL_IMMEDIATE_DRAW);
					}
					plotXYHandle = PlotXY (PanelHandle, PANEL_GRAPH, distance, pulseShifted, 3076, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);	
					SetAxisScalingMode (PanelHandle, PANEL_GRAPH, VAL_LEFT_YAXIS, VAL_MANUAL, -100, 0.0);
			}
			break;
		}
		
		 return 0;
	  }
		
int CVICALLBACK goButtonCall(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	

			return 0;
		  
		
		}
		

int CVICALLBACK closeProgram (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
				QuitUserInterface(0);

			break;
	}
	return 0;
}

int CVICALLBACK cursorsMoved (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		double xPoint = 0;
		double yPoint = 0;
		case EVENT_COMMIT:
			GetGraphCursor (PanelHandle, PANEL_GRAPH, 1, &xPoint, &yPoint);
            SetCtrlVal(PanelHandle,PANEL_CURSOR,xPoint);
			break;
	}
	return 0;
}