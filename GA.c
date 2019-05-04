#include "GA.h"

GA_Population_t Kangaroo;

void GA_Init(GA_Population_t* pGA_population, 
	uint16_t population_size, 
	uint16_t chromosome_size,
	uint16_t generation_size,
	double var_upper_bound,
	double var_lower_bound,
	double crossover_rate,
	double mutation_rate)
{
	GA_Individual_t *pGA_individual = calloc(population_size, sizeof(GA_Individual_t));

	pGA_population->var_upper_bound = var_upper_bound;
	pGA_population->var_lower_bound = var_lower_bound;
	pGA_population->population_size = population_size;
	pGA_population->chromosome_size = chromosome_size;
	pGA_population->generation_size = generation_size;
	pGA_population->individual = pGA_individual;
	pGA_population->mutation_rate = mutation_rate;
	pGA_population->crossover_rate = crossover_rate;

	pGA_population->generation = 0;

	pGA_population->best_mean_fitness = 0.0f;
	pGA_population->best_generation = 0;
	pGA_population->best_individual.chromosome = 0;
	pGA_population->best_individual.fitness = 0.0f;

	for (int i = 0; i < population_size; i++)
	{
		for (int j = 0; j < chromosome_size; j++)
		{
			if (GA_Misc_GetRandomBit())
				pGA_population->individual[i].chromosome |= (uint64_t)(0x01 << j);
		}
		//GA_Misc_DispChromosome_Binary(pGA_population, pGA_population->individual[i]);
	}

	GA_Codec_Binary2Gray(pGA_population);

}
 
void GA_Kill(GA_Population_t* pGA_population)
{
	free(pGA_population->individual);
	GA_Misc_SaveLog();
}

void GA_Calc(GA_Population_t* pGA_population)
{
	for (uint32_t i = 0; i < pGA_population->generation_size; i++)
	{
		GA_Fitness(pGA_population);
		GA_Selection(pGA_population, TRUE);
		GA_Crossover(pGA_population);
		GA_Mutation(pGA_population);
	}
	GA_Codec_Gray2Binary(pGA_population);
	GA_Misc_DispPopulationInfo(pGA_population);
}

void main(void)
{

	GA_Init(&Kangaroo, 30, 30, 200, 10.0f, 0.0f, 0.6f, 0.1f);
	GA_Calc(&Kangaroo);
	GA_Kill(&Kangaroo);

	getchar();
	getchar();
}