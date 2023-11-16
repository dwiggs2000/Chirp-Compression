 #include <userint.h>
#include <ansi_c.h>
#include <stdio.h>
#include <cvidef.h>
#include <analysis.h>
#include <math.h>
#include <utility.h>

#include "radarTwo.h"

#define DATA_LENGTH 32768

#define PANEL 1


#define PANEL_COMPRESSED 2


#define CompressCallBack 1000

#define CHIRP_START_FREQUENCY 1000.0
#define CHIRP_END_FREQUENCY 2000.0
#define SAMPLING_RATE 10000.0

#define PI 3.14159265358979323846



int main(int argc, char *argv[]){



		if(InitCVIRTE(0, argv, 0) == 0)
			printf(-1);
		
		
		
		PanelHandle = LoadPanel(0, "radar.uir", PANEL);
		
		
		
		SetCtrlAttribute(PanelHandle, PANEL_COMPRESSED, ATTR_CALLBACK_FUNCTION_POINTER, goButtonCall);
		
		
		
		
		
		DisplayPanel(PanelHandle);
		
		RunUserInterface();
		
		DiscardPanel(PanelHandle);
		
		if(inputArray != NULL){
				free(inputArray);
		
		}
		
		
		CloseCVIRTE();
		
		
		return 0;
		
		

}
