#include <stdexcept>

#include "DistormWrapper.h"
#include "mnemonics.h"

std::vector<_DInst> GetInstructions(const std::string& code, const std::vector<unsigned int>& relocs, size_t prologSize, size_t epilogSize)
{
	if (code.size() <= epilogSize + prologSize) {
		return {};
	}

	const size_t max_instructions = 1000;

	std::vector<_DInst> out;

	// Holds the result of the decoding.
	_DecodeResult res;
	// Decoded instruction information.
	_DInst dInstructions[max_instructions];

	_CodeInfo codeInfo;
	codeInfo.codeOffset = prologSize;
	codeInfo.nextOffset = 0;

	codeInfo.relocs = relocs.data();
	codeInfo.relocSize = relocs.size();

	codeInfo.code = reinterpret_cast<const unsigned char*>(code.data() + prologSize);
	codeInfo.codeLen = code.size() - (epilogSize + prologSize);
	codeInfo.dt = Decode32Bits;

	codeInfo.features = 0;

	// next is used for instruction's offset synchronization.
	// decodedInstructionsCount holds the count of filled instructions' array by the decoder.
	unsigned int decodedInstructionsCount = 0;

	while (true)
	{
		res = distorm_decompose(&codeInfo, dInstructions, max_instructions, &decodedInstructionsCount);

		if (res == DECRES_INPUTERR) {
			throw std::runtime_error{ "Input error while disassembling code" };
		}

		for (size_t i = 0; i < decodedInstructionsCount; i++) {
			//std::string test = reinterpret_cast<const char*>(GET_MNEMONIC_NAME(dInstructions[i].opcode));
			out.push_back(dInstructions[i]);
		}

		if (res == DECRES_SUCCESS) {
			break;
		} // All instructions were decoded.

		else if (decodedInstructionsCount == 0) {
			break;
		}

		unsigned long next = (unsigned long)(dInstructions[decodedInstructionsCount - 1].addr - codeInfo.codeOffset);
		next += dInstructions[decodedInstructionsCount - 1].size;
		// Advance ptr and recalc offset.
		codeInfo.code += next;
		codeInfo.codeLen -= next;
		codeInfo.codeOffset += next;
	}

	return out;
}
