#include <ansi_c.h>
#include <userint.h>
#include <cvirte.h> 
#include <utility.h>


//#define PANEL_MAIN 1
#define BUTTON_GO  1
#define GRAPH_DATA 2
#define BUTTON_TRANSMIT 3
#define BUTTON_FILTER	4



//static int panelH = 0;

//static double arrayX[DATA_LENGTH];

//static double arrayY[DATA_LENGTH];
//void CVIChirp();

int LoadPanel(int P, const char *uifilename, PANEL_MAIN);  

int CVICALLBACK goButtonCallTwo(int P, int ctr, int E, void *callBackData);

int CVICALLBACK transmitButtonCall(int P, int ctr, int E, void *callBackData);

int CVICALLBACK filterButtonCall(int P, int ctr, int E, void *callBackData);



int radar() {
		 
	int P;
	
	if (InitCVIRTE(0, 0, 0) == 0) 
		printf(-1);

	
	//P = LoadPanel(0, "CVIChirp.uir", 0);
	
	
	SetCtrlAttribute(P, BUTTON_GO, ATTR_CALLBACK_FUNCTION_POINTER, goButtonCallTwo);
	
	SetCtrlAttribute(P, BUTTON_TRANSMIT, ATTR_CALLBACK_FUNCTION_POINTER, transmitButtonCall);
	
	SetCtrlAttribute(P, BUTTON_FILTER, ATTR_CALLBACK_FUNCTION_POINTER, filterButtonCall);
	
	
	DisplayPanel(P);
	
	RunUserInterface();

	DiscardPanel(P);
	
	CloseCVIRTE();
	
	
	return 0;


}



int CVICALLBACK goButtonCallTwo(int P, int ctr, int E, void *callBackData){


	switch(E){
	
		case EVENT_COMMIT:
			
			break;
	
	
	
	
	
	
	}



		 return 0;





}

int CVICALLBACK transmitButtonCall(int P, int ctr, int E, void *callBackData){


		switch (E){
		
			case EVENT_COMMIT:
				
				break;
		
		
		
		
		
		}



		return 0;





}


int CVICALLBACK filterButtonCall(int P, int ctr, int E, void *callBackData){


		switch (E){
		
			case EVENT_COMMIT:
				
				break;
		
		
		
		
		
		}



		return 0;





}






