#include "GA_selection.h"

/**
* @brief
* @param
* @retval None
*/
GA_Individual_t GA_Selection_Roulette(GA_Population_t* pGA_population)
{
	double sum_fitness = 0.0f;
	double min_fitness = 0.0f;
	double random_factor = (double)GA_Misc_GetRandomFactor();
	double *selective_probability = (double*)calloc(pGA_population->population_size, sizeof(double));
	double *accumulated_probability = (double*)calloc(pGA_population->population_size, sizeof(double));

	GA_Individual_t null_individual = { 0,0 };

	for (int i = 0; i < pGA_population->population_size; i++)
		if (pGA_population->individual[i].fitness < min_fitness)
			min_fitness = pGA_population->individual[i].fitness;

	for (int i = 0; i < pGA_population->population_size; i++)
		sum_fitness += pGA_population->individual[i].fitness + fabs(min_fitness);

	for (int i = 0; i < pGA_population->population_size; i++)
		selective_probability[i] = (pGA_population->individual[i].fitness + fabs(min_fitness)) / sum_fitness;

	for (int i = 0; i < pGA_population->population_size; i++)
		for (int j = 0; j <= i; j++)
			accumulated_probability[i] += selective_probability[j];

	for (int i = 0; i < pGA_population->population_size; i++)
	{
		if (accumulated_probability[i] > random_factor)
		{
			//printf("Ind:%d Val:%f\n", i, pGA_population->individual[i].fitness);
			return pGA_population->individual[i];
			break;
		}
	}

	return null_individual;

	free(selective_probability);
	free(accumulated_probability);
}

void GA_Selection(GA_Population_t* pGA_population, bool_t elitism)
{
	GA_Individual_t *new_individuals = (GA_Individual_t*)calloc(pGA_population->population_size, sizeof(GA_Individual_t));
	int i;

	if (elitism == TRUE && pGA_population->generation != 0)
		new_individuals[0] = pGA_population->best_individual;

	for (i = (elitism == TRUE) ? 1 : 0; i < pGA_population->population_size; i++)
	{
		while (new_individuals[i].chromosome == 0)
			new_individuals[i] = GA_Selection_Roulette(pGA_population);
	}

	pGA_population->generation++;

	for (int i = 0; i < pGA_population->population_size; i++)
		pGA_population->individual[i] = new_individuals[i];
	
	free(new_individuals);
}
