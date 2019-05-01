#include "GA_fitness.h"

double GA_Fitness_Func(double var_value)
{
	return -var_value - 10 * sin(5 * var_value) - 7 * cos(4 * var_value);
}

void GA_Fitness(GA_Population_t* pGA_population)
{
	double var_value;

	for (int i = 0; i < pGA_population->population_size; i++)
	{
		var_value = pGA_population->var_lower_bound + (pGA_population->var_upper_bound - pGA_population->var_lower_bound) * (double)pGA_population->individual[i].chromosome / (pow(2, pGA_population->chromosome_size) - 1);
		pGA_population->individual[i].fitness = GA_Fitness_Func(var_value);
	}

	GA_Misc_GetBestMeanFitness(pGA_population);
	GA_Misc_GetBestIndividual(pGA_population);
	//GA_Misc_Log(pGA_population);
}

