#include "GA_misc.h"

/**
* @brief
* @param
* @retval None
*/
double GA_Misc_GetRandomFactor(void)
{
	static int srand_flag;

	if (!srand_flag)
	{
		srand((unsigned int)time(NULL));
		srand_flag = 1;
	}

	return rand() / 32767.0f;
}

/**
* @brief
* @param
* @retval None
*/
uint8_t GA_Misc_GetRandomBit(void)
{
	if (GA_Misc_GetRandomFactor() > 0.5f)
		return 1;
	else
		return 0;
}

/**
* @brief
* @param
* @retval None
*/
void GA_Misc_GetBestIndividual(GA_Population_t* pGA_population)
{
	uint16_t best_idx = 0;

	for (int i = 0; i < pGA_population->population_size; i++)
	{
		if (pGA_population->individual[i].fitness > pGA_population->individual[best_idx].fitness)
			best_idx = i;
	}

	if(pGA_population->best_individual.fitness < pGA_population->individual[best_idx].fitness)
		pGA_population->best_individual = pGA_population->individual[best_idx];
}

/**
* @brief
* @param
* @retval None
*/
void GA_Misc_GetBestMeanFitness(GA_Population_t* pGA_population)
{
	double sum_fitness = 0;

	for (int i = 0; i < pGA_population->population_size; i++)
		sum_fitness += pGA_population->individual[i].fitness;

	sum_fitness /= pGA_population->population_size;

	if (pGA_population->best_mean_fitness < sum_fitness)
		pGA_population->best_mean_fitness = sum_fitness;
}

/**
* @brief
* @param
* @retval None
*/
void GA_Misc_DispChromosome_Binary(GA_Population_t* pGA_population, GA_Individual_t pGA_individual)
{
	for (int i = pGA_population->chromosome_size - 1; i >= 0; i--)
	{
		if (pGA_individual.chromosome & (uint64_t)(0x01 << i))
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}

/**
* @brief
* @param
* @retval None
*/
void GA_Misc_DispPopulationInfo(GA_Population_t* pGA_population)
{
	printf("Generation:%d\n", pGA_population->generation);
	printf("Best Mean Fitness:%f\n", pGA_population->best_mean_fitness);
	printf("Best Individual Fitness:%f\n", pGA_population->best_individual.fitness);
	printf("Best Result:%f\n", pGA_population->var_lower_bound + (pGA_population->var_upper_bound - pGA_population->var_lower_bound) * (double)pGA_population->best_individual.chromosome / (pow(2, pGA_population->chromosome_size) - 1));
	//GA_Misc_DispChromosome_Binary(pGA_population, pGA_population->best_individual);
}

FILE *fd_log;
uint8_t fd_init_flag;
char LogFileName[128];

void GA_Misc_Log(GA_Population_t* pGA_population)
{
	if (!fd_init_flag)
	{
		char str_data[64];
		struct tm t_temp;
		time_t timer = time(NULL);

		localtime_s(&t_temp, &timer);
		strftime(str_data, 64, "%Y%m%d%H%M%S", &t_temp);
		strcat_s(LogFileName, 128, str_data);
		strcat_s(LogFileName, 128, ".txt");
		fopen_s(&fd_log, LogFileName, "w");

		if (fd_log == NULL)
			printf("Failed to create log file.\n");
		else
			fprintf(fd_log, "G:\tMn_Fit:\tBst_Fit:\tBst_Res:\n");

		fd_init_flag = 1;
	}

	if (fd_log != NULL)
	{
		fprintf(fd_log, "%d\t%f\t%f\t%f", pGA_population->generation, pGA_population->best_mean_fitness, pGA_population->best_individual.fitness, pGA_population->var_lower_bound + (pGA_population->var_upper_bound - pGA_population->var_lower_bound) * (double)pGA_population->best_individual.chromosome / (pow(2, pGA_population->chromosome_size) - 1));
		for (int i = 0; i < pGA_population->population_size; i++)
		{
			fprintf(fd_log, "%8.4f\t", pGA_population->individual[i].fitness);
		}
		fprintf(fd_log, "\n");
	}
		
}

void GA_Misc_SaveLog(void)
{
	if (fd_log != NULL)
	{
		fd_init_flag = 0;
		LogFileName[0] = '\0';
		fclose(fd_log);
	}
		
}