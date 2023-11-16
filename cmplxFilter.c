#include <userint.h>
#include "filterTest.h"
#include <analysis.h>

void convolve (double *p_coeffs, int p_coeffs_n,
               double *p_in, double *p_out, int n)
{
  int i, j, k;
  double tmp;

  for (k = 0; k < n; k++)  //  position in output
  {
    tmp = 0;

    for (i = 0; i < p_coeffs_n; i++)  //  position in coefficients array
    {
      j = k - i;  //  position in input

      if (j >= 0)  //  bounds check for input buffer
      {
        tmp += p_coeffs [i] * p_in [j];
      }
    }

    p_out [k] = tmp;
  }
}


void cmpxFilter (double coeffs[16384][2], int numCoeff, double signalToFilter[65536][2], double filtSig[65536][2], int samples)
{
	double	coeffI[numCoeff];
	double	coeffQ[numCoeff];
	double	sampI[samples];
	double	sampQ[samples];
	double	filtI[samples];
	double	filtQ[samples];
	double	iXi[samples];
	double	iXq[samples];
	double	qXi[samples];
	double	qXq[samples];
	
	int	counter;
	
	for(counter = 0;counter < numCoeff; counter++){
		coeffI[counter]=coeffs[counter][0];
		coeffQ[counter]=coeffs[counter][1];
	}
	for(counter = 0;counter < samples; counter++){
		sampI[counter]=signalToFilter[counter][0];
		sampQ[counter]=signalToFilter[counter][0];
	}
	
	convolve(coeffI,numCoeff,sampI,iXi,samples);
	convolve(coeffQ,numCoeff,sampI,iXq,samples);
	convolve(coeffI,numCoeff,sampQ,qXi,samples); 
	convolve(coeffI,numCoeff,sampQ,qXq,samples);
	for(counter = 0;counter < samples; counter++){
		filtSig[counter][0]= iXi[counter]-qXq[counter];
		filtSig[counter][1]= iXq[counter]-qXi[counter];
	}
}


