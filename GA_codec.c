#include"GA_codec.h"

void GA_Codec_Binary2Gray(GA_Population_t* pGA_population)
{
	uint64_t temp_chromosome_binary[2] = { 0,0 }, temp_chromosome_gray = 0;

	for (int i = 0; i < pGA_population->population_size; i++)
	{
		temp_chromosome_binary[0] = pGA_population->individual[i].chromosome;
		temp_chromosome_binary[1] = pGA_population->individual[i].chromosome >> 1;
		temp_chromosome_gray = temp_chromosome_binary[0] ^ temp_chromosome_binary[1];

		if (pGA_population->individual[i].chromosome & (uint64_t)(0x01 << pGA_population->chromosome_size))
			temp_chromosome_gray |= (uint64_t)(0x01 << pGA_population->chromosome_size);
		else
			temp_chromosome_gray &= ~(uint64_t)(0x01 << pGA_population->chromosome_size);

		pGA_population->individual[i].chromosome = temp_chromosome_gray;
	}
}

void GA_Codec_Gray2Binary(GA_Population_t* pGA_population)
{
	uint64_t temp_chromosome_binary = 0;

	for (int i = 0; i < pGA_population->population_size; i++)
	{
		for (int j = pGA_population->chromosome_size - 1; j >= 0; j--)
		{
			if (j == pGA_population->chromosome_size - 1)
			{
				if (GA_CODEC_FIND_BIT(pGA_population->individual[i].chromosome, pGA_population->chromosome_size))
					GA_CODEC_SET_BIT(temp_chromosome_binary, pGA_population->chromosome_size);
				else
					GA_CODEC_RESET_BIT(temp_chromosome_binary, pGA_population->chromosome_size);
			}
			else
			{
				if((GA_CODEC_FIND_BIT(temp_chromosome_binary, j + 1) != 0) != (GA_CODEC_FIND_BIT(pGA_population->individual[i].chromosome, j) != 0))
					GA_CODEC_SET_BIT(temp_chromosome_binary, j);
				else
					GA_CODEC_RESET_BIT(temp_chromosome_binary, j);
			}
		}
		pGA_population->individual[i].chromosome = temp_chromosome_binary;
		temp_chromosome_binary = 0;
	}
	
}