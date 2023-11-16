#include <cvirte.h>		
#include <userint.h>
#include "radar.h"

static int panelHandle;

#include <userint.h>
#include <ansi_c.h>
#include <stdio.h>
#include <cvidef.h>
#include <analysis.h>
#include <math.h>
#include <utility.h>

#define DATA_LENGTH 65536

#define PANEL 1


#define PANEL_COMPRESS 2


#define CompressCallBack 1000

#define CHIRP_START_FREQUENCY 1000.0
#define CHIRP_END_FREQUENCY 2000.0
#define SAMPLING_RATE 10000.0

#define PI 3.14159265358979323846

static int *inputArray = NULL; 

static double *timeArray = NULL;
static int PanelHandle = 0;



static double compressed[DATA_LENGTH];

//static double *inputArray = NULL;						
static double radarData[DATA_LENGTH];
static double chirpModel[DATA_LENGTH];
static double largeCompressed[DATA_LENGTH * 2];


//int CVICALLBACK goButtonCall(int P, int ctr, int E, void *callBackData, int eventData1, int eventData2 ); 

void correlateLargeArray(double arrayOne[], size_t sizeOfOne, double arrayTwo[], size_t sizeOfTwo,  double OutArray[], size_t sizeOutArray){
	
	
			double* tempArray = malloc((sizeOfOne + sizeOfTwo - 1) * sizeof(double));
			
			Correlate(arrayOne, sizeOfOne, arrayTwo, sizeOfTwo, tempArray);
			
			for(int i = 0; i < sizeOfOne; i++ ){
			
			
				  OutArray[i] = tempArray[i + sizeOfTwo - 1];
			
			}

			
					free(tempArray); 
		 // perform correlation with larger output array
		 //uses existing correlate function OR implementation of existing correlation logic in this correlate function
		 
		 
		 
		 //example of an existing correlate function with example parameters
			//Correlate(arrayOne, sizeOfOne, arrayTwo, sizeOfTwo, OutArray);


}

//int main(int argc, char *argv[] )
int CVICALLBACK goButtonCall(int P, int ctr, int E, void *callBackData, int eventData1, int eventData2)
{		///int i; 
	
		//static double inputArray[DATA_LENGTH]; 
		//double VAL_ENTIRE_ARRAY = 0;
		
		 
		
		
		//inputArray = VAL_ENTIRE_ARRAY;
		
		
		switch (E)
		{
				
			case EVENT_COMMIT:
				
				{
		
					char filePath[MAX_PATHNAME_LEN];
					
					FileSelectPopup("", "*.*", "", "SELECT A FILE TO TRANSMIT", VAL_LOAD_BUTTON, 0, 1, 1, 0, filePath);
					
					FILE *file = fopen(filePath, "r");
					
					if (file == NULL){
					
					
						MessagePopup("ERROR", "FAILED TO OPEN FILE");
						
					
						
						return 0;
					
					
					
					
					}
					
					
				
					
					free(inputArray); 
					
					inputArray = malloc(DATA_LENGTH * sizeof(int)); 
					timeArray = malloc(DATA_LENGTH * sizeof(double));
					
					int j = 0;  
					
					if (inputArray != NULL){
						
							
							
							 
							
							for ( j = 0; j <DATA_LENGTH; j++) {
					
						
						
									fscanf(file, "%i", &inputArray[j]);
									
									timeArray[j] = ((double)j)/1500000000.0;
							
									printf("%i\n", inputArray[j]);
									
									printf("%i\n", inputArray[j]);
					
							}
					
					}
					
					
					
					
					
					
					
					if (j == 0 ){
					
						MessagePopup("ERROR", "NO DATA FOUND IN FILE");
						
					}	else if (j == DATA_LENGTH && !feof(file)){
						
							MessagePopup("WARNING", "DATA_LENGTH EXCEEDED. ONLY FIRST 4096 VALUES WERE READ>");
					
					
					
					
					}
					
				
					
					
					
					fclose(file);
		
		//double radarData[DATA_LENGTH];	   //radar data placeholder
		
		//simulates radar data generation
		
		//replaces this with actual data retrieval from AD9081
		
		
					for (int i=0; i <DATA_LENGTH; i++){
			
						double T = i/SAMPLING_RATE; //time
						double chirpFrequency = CHIRP_START_FREQUENCY + (CHIRP_END_FREQUENCY - CHIRP_START_FREQUENCY)* T / (DATA_LENGTH / SAMPLING_RATE);
			
			
						radarData[i] = sin(2* PI * chirpFrequency * T);		 //chirpSignal
			
			
		
			
			
		}
		
						double chirpModel[DATA_LENGTH]; //transmitted chirp signal replica
						double compressed[DATA_LENGTH];  //placeholder for data that has been compressed
		
		
		
		//int window = V_H_W // val hamming window
		
		
					for (int i = 0; i <DATA_LENGTH; i++){
		
					 	double T = i /SAMPLING_RATE; //time
					 
						double chirpFrequency = CHIRP_START_FREQUENCY + (CHIRP_END_FREQUENCY - CHIRP_START_FREQUENCY *T/( DATA_LENGTH / SAMPLING_RATE));
					 
					 	chirpModel[i] = sin(2 * PI * chirpFrequency * T);  //chirp signal model
					 
					 
				
			
			
			
			
			}
			
			//performs correlation (chirp compression) using a larger output array					    
					size_t sizeOutArray= DATA_LENGTH * 2; //increases output array
			
					double largeCompressed[sizeOutArray];
			  //perfroms chirp compression
					correlateLargeArray(radarData, DATA_LENGTH, chirpModel, DATA_LENGTH, largeCompressed, sizeOutArray);
					
					//DATA_LENGTH = i;
			
					PlotXY(PANEL, PANEL_COMPRESSED, timeArray, inputArray, 32768, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
			
			//displays compresssed data
			
			
					free(timeArray);
					
					free(inputArray);
			
					for (int i = 0; i <sizeOutArray; i++){
				
				
						printf("%f\n", largeCompressed[i]);
				
				
				
				//for (int j = 0; j<10; j++)
			
	
					  		if(i == 10){
					  
					  
					  				break;
					  
					  
					  
					    	}else{
						  
						  			printf("%f\n", largeCompressed[i]);
						  
						  
						  
						  
						  
						   			getchar();
						  //while (KeyHit ())                   // Purge keyboard buffer
        					//GetKey ();
    						//printf ("\nPress a key to finish:");
    						//GetKey ();                          // Wait for user action
   							
				
				
			
					 break;
			
					}
				
				}
			
			}
		
		}
			

			
		 return 0;  
		
		}







int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "radar.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}
