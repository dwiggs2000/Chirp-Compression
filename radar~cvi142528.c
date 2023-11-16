#include <ansi_c.h>
#include <stdio.h>
#include <cvidef.h>
#include <analysis.h>
#include <math.h>
#include <utility.h>

#define DATA_LENGTH 4096

//#define DATA_LENGTH_ARR2 4096

#define CHIRP_START_FREQUENCY 1000.0
#define CHIRP_END_FREQUENCY 2000.0
#define SAMPLING_RATE 10000.0

#define PI 3.14159265358979323846



void correlateLargeArray(double arrayOne[], ssize_t sizeOfOne, double arrayTwo[], size_t sizeOfTwo,  double OutArray[], size_t sizeOutArray){

		 // perform correlation with larger output array
		 //uses existing correlate function OR implementation of existing correlation logic in this correlate function
		 
		 
		 
		 //example of an existing correlate function with example parameters
		Correlate(arrayOne, sizeOfOne, arrayTwo, sizeOfTwo, OutArray);


}

int main(void)
{		///int i; 
		//double T = i; 
		double VAL_ENTIRE_ARRAY = 0;
		//double V_N_S = 0;
		//double V_S_T_Z = 0;
		
		
		double radarData[DATA_LENGTH];	   //radar data placeholder
		
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
			
			
			//displays compresssed data
			
			for (int i = 0; i <sizeOutArray; i++){
				
				
				printf("%f\n", largeCompressed[i]);
				
				
				
				for (int j = 0; j<10; j++)
			
	
					  if(i == 10){
					  
					  
					  		break;
					  
					  
					  
					    }else{
						  
						  printf("%f\n", largeCompressed[i]);
						  
						  
						  
						  
						  
						   getchar();
						  //while (KeyHit ())                   // Purge keyboard buffer
        					//GetKey ();
    						//printf ("\nPress a key to finish:");
    						//GetKey ();                          // Wait for user action
   							
				
				
			
			
			
				}
				
			}
			

			
		 return 0;  
		
		}
		
		
		
		
		
		







