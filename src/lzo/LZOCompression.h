#ifndef LZOCOMPRESSION_H
#define LZOCOMPRESSION_H

#include <cstdint>
#include <vector>

class LZOCompression {
public:
	/// Returns a pointer to the compressed data (first) and the size of the compressed data (second)
	/// Supports compressing up to 0xffffffff bytes, although the output of compression may be bigger
	/// If an error occurs, error message will be sent to stdout and this function will return an empty vector, and <code>error</error> will be set to true
	static std::vector<uint8_t> Compress(const std::vector<uint8_t>& data, uint32_t dataSize, bool* error = nullptr);
	/// Returns a pointer to the decompressed data (first) and the size of the decompressed data (second)
	/// Supports decompressing up to 0xffffffffffffffff bytes, although the decompressed data must occupy less than 0xffffffff bytes
	/// If an error occurs, error message will be sent to stdout and this function will return an empty vector, and <code>error</error> will be set to true
	static std::vector<uint8_t> Decompress(const std::vector<uint8_t> data, uint64_t dataSize, uint32_t decompressedSize, bool* error = nullptr);
};

#endif // LZOCOMPRESSION_H
