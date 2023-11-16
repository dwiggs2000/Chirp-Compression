/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_TOGGLEBUTTON               2       /* control type: toggle, callback function: goButtonCall */
#define  PANEL_XY_GRAPH                   3       /* control type: graph, callback function: (none) */
#define  PANEL_GRAPH                      4       /* control type: graph, callback function: moveMarker */
#define  PANEL_TOGGLEBUTTON_2             5       /* control type: textButton, callback function: correlateLargeArray */
#define  PANEL_COMMANDBUTTON              6       /* control type: command, callback function: closeProgram */
#define  PANEL_COLOR_DIST                 7       /* control type: color, callback function: (none) */
#define  PANEL_COLOR_LEV                  8       /* control type: color, callback function: (none) */
#define  PANEL_PANEL_GRAPH                9       /* control type: strip, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK closeProgram(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK correlateLargeArray(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK goButtonCall(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK moveMarker(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
