#ifndef GA_SELECTION_H
#define GA_SELECTION_H

#include"GA.h"

GA_Individual_t GA_Selection_Roulette(GA_Population_t* pGA_population);
void GA_Selection(GA_Population_t* pGA_population, bool_t elitism);

#endif
