#include "LZOCompression.h"
#include "3rdparty/minilzo.h"
#include <iostream>

Pair<uint8_t*, uint64_t> LZOCompression::Compress(uint8_t* data, uint32_t dataSize) {
	if(lzo_init() != LZO_E_OK) {
		std::cout << "[ERROR]: Initialisation of LZO library failed - This usually indicates a compiler bug" << std::endl;
		return { nullptr, 0 };
	}

	uint64_t outputSize = dataSize + dataSize / 16 + 64 + 3;
	uint8_t* output = new uint8_t[outputSize]; // Make the output block slightly bigger than the input block, in case the data is incompressible

	uint64_t workingMemorySize = ((LZO1X_1_MEM_COMPRESS) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t);
	lzo_align_t* workingMemory = new lzo_align_t[workingMemorySize];

	int result = lzo1x_1_compress(data, dataSize, output, &outputSize, workingMemory);
	if(result != LZO_E_OK) {
		std::cout << "[ERROR]: Internal error - compression failed. Error code: " << result << std::endl;
		delete[] output;
		return { nullptr, 0 };
	}

	return { output, outputSize };
}

Pair<uint8_t*, uint32_t> LZOCompression::Decompress(uint8_t* data, uint64_t dataSize, uint32_t decompressedSize) {
	if(lzo_init() != LZO_E_OK) {
		std::cout << "[ERROR]: Initialisation of LZO library failed - This usually indicates a compiler bug" << std::endl;
		return { nullptr, 0 };
	}

	uint64_t outputSize = decompressedSize;
	uint8_t* output = new uint8_t[outputSize];

	int result = lzo1x_decompress(data, dataSize, output, &outputSize, nullptr);
	if(result != LZO_E_OK) {
		std::cout << "[ERROR]: Internal error - compression failed. Error code: " << result << std::endl;
		delete[] output;
		return { nullptr, 0 };
	}

	uint32_t outputSizeShort = (outputSize);
	if(outputSizeShort != outputSize) { // This shouldn't happen, because I think it'd segfault before this
		std::cout << "[ERROR]: Size of decompressed data is greater than that which a 4 bytes can hold" << std::endl;
		delete[] output;
		return { nullptr, 0 };
	}

	return { output, outputSizeShort };
}