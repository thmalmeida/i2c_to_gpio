#ifndef RMS_HPP__
#define RMS_HPP__

#include "i2c.h"
#include "tim.h"						// needs for module uptime. It TIM3 update every 1 second.
#include "gpio.hpp"
#include "stm32_log.h"

/* Root Mean Square - RMS class
*/
class rms {
public:
	rms(void) {}
	~rms(void) {}

    float calc_irms(void);
	float calc_vrms(void);
	float calc_rms(void);
}

#endif


// // RMS calculation example
// //Reference: https://rosettacode.org/wiki/Averages/Root_mean_square
// C example:
// #include <stdio.h>
// #include <math.h>
// double rms(double *v, int n)
// {
// 	int i;
// 	double sum = 0.0;
// 	for(i = 0; i < n; i++)
// 		sum += v[i] * v[i];
// 	return sqrt(sum / n);
// }
// int main(void)
// {
// 	double v[] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10.};
// 	printf("%f\n", rms(v, sizeof(v)/sizeof(double)));
// 	return 0;
// }
// // C++ example
// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <numeric>
// int main(void) {
// 	std::vector<int> numbers ;
// 	for ( int i = 1 ; i < 11 ; i++ ) {
// 		numbers.push_back( i );
// 	}
// 	double meansquare = sqrt( ( std::inner_product( numbers.begin(), numbers.end(), numbers.begin(), 0 ) ) / static_cast<double>( numbers.size() ) );
// 	std::cout << "The quadratic mean of the numbers 1 .. " << numbers.size() << " is " << meansquare << " !\n" ;
// 	return 0 ;
// }


// float calcIrms()//uint8_t channel)//, uint8_t numberOfCycles)
// {
// 	int i, j=0;
// 	uint8_t high, low;
// 	int divScale_count = 1;

// 	ADCSRB &= ~(1<<MUX5);
// 	ADMUX  &= ~(1<<MUX4);
// 	ADMUX  &= ~(1<<MUX3);
// 	ADMUX  &= ~(1<<MUX2);
// 	ADMUX  &= ~(1<<MUX1);
// 	ADMUX  |=  (1<<MUX0);									// Select ADC1

// 	// ADC converter
// 	const float f = 60.0;									// Hertz;
// 	const int numberOfCycles = 16;							// Number of cycles;
// 	const int divScale = 8;									// Prescale for real sample rate Fs;

// 	const float Fs = 16000000/128/13;									// Sample rate of signal processed;
// 	const int nPointsPerCycle = (int) Fs/f;								// Number of points per cycle;
// 	const int nPoints = (int) nPointsPerCycle*numberOfCycles; 			// Number of signal points.

// 	const float Fs_div = 16000000/128/13/divScale;						// Sample rate of signal processed;
// 	const int nPointsPerCycle_div = (int) Fs_div/f;						// Number of points per cycle;
// 	const int nPoints_div = (int) nPointsPerCycle_div*numberOfCycles;	// Number of signal points.


// //	sprintf(buffer,"---- Signal Captured ----");
// //	Serial1.println(buffer);
// //	Serial1.println("");
// //
// //	Serial1.print("Fs:");
// //	Serial1.println(Fs);
// //	Serial1.println("");
// //
// //	sprintf(buffer,", nPointsPerCycle:%d", nPointsPerCycle);
// //	Serial1.println(buffer);
// //	Serial1.println("");
// //
// //	sprintf(buffer,"nPoints:%d", nPoints);
// //	Serial1.println(buffer);
// //	Serial1.println("");
// //
// //
// //
// //	sprintf(buffer,"---- Signal Processed ----");
// //	Serial1.println(buffer);
// //	Serial1.println("");
// //
// //	Serial1.print("Fs:");
// //	Serial1.println(Fs_div);
// //	Serial1.println("");
// //
// //	sprintf(buffer,", nPointsPerCycle:%d", nPointsPerCycle_div);
// //	Serial1.println(buffer);
// //	Serial1.println("");
// //
// //	sprintf(buffer,"nPoints:%d", nPoints_div);
// //	Serial1.println(buffer);
// //	Serial1.println("");


// 	int *adcSamples = NULL;
// 	adcSamples = (int*)malloc(nPoints_div * sizeof(int));

// 	// 160.2564 = 16000000/128/13/60.0;
// 	for(i=0;i<nPoints;i++)
// 	{
// 		ADCSRA |= (1<<ADSC);				// Start conversion;
// 		while (bit_is_set(ADCSRA, ADSC));	// wait until conversion done;

// //		Serial.println((ADCH << 8) | ADCL);

// 		if(divScale_count == 1)
// 		{
// 			low  = ADCL;
// 			high = ADCH;

// 			j = (int) i/divScale;
// 			adcSamples[j] = (high << 8) | low;
// 			divScale_count = divScale;
// 		}
// 		else
// 		{
// 			divScale_count--;
// 		}
// 	}

// //	Serial.println("ENTROU!");
// //	for(i=0;i<nPoints_div;i++)
// //	{
// //		Serial.println(adcSamples[i]);
// //	}
// //	Serial.println("SAIU!");


// 	float *vs = NULL;
// 	vs = (float*)malloc(nPoints_div * sizeof(float));

// 	for(i=0;i<nPoints_div;i++)
// 	{
// 		vs[i] = (adcSamples[i]*5.0)/1024.0;
// 	}

// 	free(adcSamples);

// 	// Offset remove.
// 	float Vmean = 0.0;
// 	for(i=0;i<nPoints_div;i++)
// 		Vmean += vs[i];

// 	Vmean = Vmean/nPoints_div;

// 	for(i=0;i<nPoints_div;i++)
// 		vs[i] = vs[i] - Vmean;

// 	float *vs2 = NULL;
// 	vs2 = (float*)malloc(nPoints_div * sizeof(float));

// 	// Power signal
// 	for(i=0;i<nPoints_div;i++)
// 		vs2[i] = vs[i]*vs[i];

// 	free(vs);

// 	float sum=0;
// 	float V2mean;

// 	// mean finder
// 	for(i=0;i<nPoints_div;i++)
// 		sum += vs2[i];
// 	V2mean = sum/nPoints_div;

// 	free(vs2);

// 	float I = 0.0;
// 	float k = 2020.0;
// 	float R = 310.0;

// 	// RMS equation
// 	I = (k*sqrt(V2mean))/R;

// 	return I;
// }