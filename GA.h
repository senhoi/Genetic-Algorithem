#ifndef  _GENETIC_ALGORITHEM_H
#define _GENETIC_ALGORITHEM_H

#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

typedef enum bool_t
{
	FALSE,
	TRUE
}bool_t;

typedef struct GA_Individual_t
{
	uint64_t chromosome;
	double fitness;
}GA_Individual_t;

typedef struct GA_Population_t
{
	double var_upper_bound;
	double var_lower_bound;
	uint16_t population_size;
	uint16_t chromosome_size;
	uint32_t generation_size;
	GA_Individual_t *individual;

	double crossover_rate;
	double mutation_rate;
	
	uint16_t generation;

	double best_mean_fitness;
	uint16_t best_generation;
	GA_Individual_t best_individual;
}GA_Population_t;

#include"GA_misc.h"
#include"GA_selection.h"
#include"GA_crossover.h"
#include"GA_fitness.h"
#include"GA_mutation.h"

#endif

