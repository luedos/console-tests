#pragma once

#include <stdint.h>

namespace encryption
{

struct PRNG
{
	//! State size
	enum { SizeState = 624 };
	//! Internal state   
	uint32_t state[SizeState];
	//! Offset of next state's word   
	int next;
};

static void TwistPRNG(PRNG& gen)
{
	const int M = 397;
	const int FirstHalf = PRNG::SizeState - M;
	// first 624-397=227 words  
	int i;
	for (i = 0; i < FirstHalf; i++)
	{
		uint32_t bits = (gen.state[i] & 0x80000000) | (gen.state[i + 1] & 0x7fffffff);
		gen.state[i] = gen.state[i + M] ^ (bits >> 1) ^ ((bits & 1) * 0x9908b0df);
	}
	// remaining words (except the very last one)   
	for (; i < PRNG::SizeState - 1; i++)
	{
		uint32_t bits = (gen.state[i] & 0x80000000) | (gen.state[i + 1] & 0x7fffffff);
		gen.state[i] = gen.state[i - FirstHalf] ^ (bits >> 1) ^ ((bits & 1) * 0x9908b0df);
	}
	// last word is computed pretty much the same way, but i + 1 must wrap around to 0  
	uint32_t bits = (gen.state[i] & 0x80000000) | (gen.state[0] & 0x7fffffff);
	gen.state[i] = gen.state[M - 1] ^ (bits >> 1) ^ ((bits & 1) * 0x9908b0df);
	// word used for next random number   
	gen.next = 0;
}

static void InitPRNG(PRNG& gen, uint32_t seed)
{
	gen.state[0] = seed;
	for (int i = 1; i < PRNG::SizeState; i++) {
		gen.state[i] = 1812433253UL * (gen.state[i - 1] ^ (gen.state[i - 1] >> 30)) + i;
	}
	// let's twist'n'shout ...   
	TwistPRNG(gen);
}

static uint32_t PRNGGenerate(PRNG& gen)
{
	// compute new state ?   
	if (gen.next >= PRNG::SizeState) {
		TwistPRNG(gen);
	}

	// shuffle bits around   
	uint32_t x = gen.state[gen.next++];
	x ^= x >> 11;
	x ^= (x << 7) & 0x9d2c5680;
	x ^= (x << 15) & 0xefc60000;
	x ^= x >> 18;
	return x;
}

}