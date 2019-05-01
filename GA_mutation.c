#include "GA_mutation.h"

void GA_Mutation(GA_Population_t* pGA_population)
{
	uint8_t mutation_pos;

	for (int i = 0; i < pGA_population->population_size; i++)
	{
		if (GA_Misc_GetRandomFactor() < pGA_population->mutation_rate)
		{
			mutation_pos = (uint8_t)(GA_Misc_GetRandomFactor() * pGA_population->chromosome_size);

			if (mutation_pos == pGA_population->chromosome_size)
				continue;

			if (GA_Misc_GetRandomBit() == 0)
				pGA_population->individual[i].chromosome &= ~(uint64_t)(1 << mutation_pos);
			else if (GA_Misc_GetRandomBit() == 1)
				pGA_population->individual[i].chromosome |= (uint64_t)(1 << mutation_pos);
				//The mutation base-pairs is random, which means the chromosome maybe same with the origin chromosome after mutation.

		}
	}
}
