#ifndef GA_MISC_H
#define GA_MISC_H

#include<time.h>
#include<string.h>
#include"GA.h"

uint8_t GA_Misc_GetRandomBit(void);
double GA_Misc_GetRandomFactor(void);
void GA_Misc_GetBestIndividual(GA_Population_t* pGA_population);
void GA_Misc_GetBestMeanFitness(GA_Population_t* pGA_population);
void GA_Misc_DispChromosome_Binary(GA_Population_t* pGA_population, GA_Individual_t pGA_individual);
void GA_Misc_DispPopulationInfo(GA_Population_t* pGA_population);
void GA_Misc_Log(GA_Population_t* pGA_population);
void GA_Misc_SaveLog(void);

#endif

