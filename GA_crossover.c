#include "GA_crossover.h"

void GA_Crossover(GA_Population_t* pGA_population)
{
	uint8_t cross_pos_a, cross_pos_b, cross_pos_temp;
	uint64_t cross_mask = 0, cross_segment[2];

	for (int i = 0; i < pGA_population->population_size; i += 2)
	{
		if (GA_Misc_GetRandomFactor() < pGA_population->crossover_rate)
		{
			cross_pos_a = (uint8_t)(GA_Misc_GetRandomFactor() * pGA_population->chromosome_size);
			cross_pos_b = (uint8_t)(GA_Misc_GetRandomFactor() * pGA_population->chromosome_size);

			if (cross_pos_a == pGA_population->chromosome_size || cross_pos_b == pGA_population->chromosome_size)
				continue;

			if (cross_pos_a > cross_pos_b)
			{
				cross_pos_temp = cross_pos_a;
				cross_pos_a = cross_pos_b;
				cross_pos_b = cross_pos_temp;
			}

			cross_pos_b = 0;

			for (int j = cross_pos_a; j <= cross_pos_b; j++)
				cross_mask |= (uint64_t)(0x01 << j);
			
			cross_segment[0] = cross_mask & pGA_population->individual[i].chromosome;
			cross_segment[1] = cross_mask & pGA_population->individual[i + 1].chromosome;

			pGA_population->individual[i].chromosome &= ~cross_mask;
			pGA_population->individual[i].chromosome |= cross_segment[1];

			pGA_population->individual[i + 1].chromosome &= ~cross_mask;
			pGA_population->individual[i + 1].chromosome |= cross_segment[0];

			cross_mask = 0;
		}
	}
}