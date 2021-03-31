#include "LZOCompression.h"
#include "3rdparty/minilzo.h"
#include <iostream>

void LZOCompression::Compress(const std::vector<uint8_t>& data, std::vector<uint8_t>& output, bool* error) {
	if(lzo_init() != LZO_E_OK) {
		std::cout << "[ERROR]: Initialisation of LZO library failed - This usually indicates a compiler bug" << std::endl;
		if(error) {
			*error = true;
		}
		return;
	}

	uint64_t outputSize = data.size() + data.size() / 16 + 64 + 3;// Make the output block slightly bigger than the input block, in case the data is incompressible
	output.resize(outputSize);

	uint64_t workingMemorySize = ((LZO1X_1_MEM_COMPRESS) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t);
	lzo_align_t* workingMemory = new lzo_align_t[workingMemorySize];

	int result = lzo1x_1_compress(&data.front(), data.size(), &output.front(), &outputSize, workingMemory);
	if(result != LZO_E_OK) {
		std::cout << "[ERROR]: Internal error - compression failed. Error code: " << result << std::endl;
		if(error) {
			*error = true;
		}
		return;
	}

	output.resize(outputSize);

	if(error) {
		*error = false;
	}
}

void LZOCompression::Decompress(const std::vector<uint8_t> data, std::vector<uint8_t>& output, uint32_t decompressedSize, bool* error) {
	if(lzo_init() != LZO_E_OK) {
		std::cout << "[ERROR]: Initialisation of LZO library failed - This usually indicates a compiler bug" << std::endl;
		if(error) {
			*error = true;
		}
		return;
	}

	uint64_t outputSize = decompressedSize;
	output.resize(outputSize);

	int result = lzo1x_decompress(&data.front(), data.size(), &output.front(), &outputSize, nullptr);
	if(result != LZO_E_OK) {
		std::cout << "[ERROR]: Internal error - compression failed. Error code: " << result << std::endl;
		if(error) {
			*error = true;
		}
		return;
	}

	uint32_t outputSizeShort = (outputSize);
	if(outputSizeShort != outputSize) { // This shouldn't happen, because I think it'd segfault before this
		std::cout << "[ERROR]: Size of decompressed data is greater than that which a 4 bytes can hold" << std::endl;
		if(error) {
			*error = true;
		}
		return;
	}

	output.resize(outputSizeShort);
}