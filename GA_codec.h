#ifndef GA_CODEC_H
#define GA_CODEC_H

#include"GA.h"

#define GA_CODEC_FIND_BIT(chromosome,shift_bit) (chromosome & (uint64_t)(0x01 << shift_bit))
#define GA_CODEC_SET_BIT(chromosome,shift_bit) (chromosome |= (uint64_t)(0x01 << shift_bit))
#define GA_CODEC_RESET_BIT(chromosome,shift_bit) (chromosome &= ~(uint64_t)(0x01 << shift_bit))

void GA_Codec_Binary2Gray(GA_Population_t* pGA_population);
void GA_Codec_Gray2Binary(GA_Population_t* pGA_population);

#endif // !GA_CODEC_H
