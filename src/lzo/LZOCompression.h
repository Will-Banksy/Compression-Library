#ifndef LZOCOMPRESSION_H
#define LZOCOMPRESSION_H

#include <cstdint>

template<typename T1, typename T2>
struct Pair {
	T1 first;
	T2 second;

	Pair(T1 first, T2 second) : first(first), second(second) {}
};

class LZOCompression {
public:
	/// Returns a pointer to the compressed data (first) and the size of the compressed data (second)
	/// Supports compressing up to 0xffffffff bytes, although the output of compression may be bigger
	/// Note that the returned size of the compressed data won't be equal to the amount of memory allocated for it
	/// If an error occurs, error message will be sent to stdout and this function will return { nullptr, 0 }
	static Pair<uint8_t*, uint64_t> Compress(uint8_t* data, uint32_t dataSize);
	/// Returns a pointer to the decompressed data (first) and the size of the decompressed data (second)
	/// Supports decompressing up to 0xffffffffffffffff bytes, although the decompressed data must occupy less than 0xffffffff bytes
	/// If an error occurs, error message will be sent to stdout and this function will return { nullptr, 0 }
	static Pair<uint8_t*, uint32_t> Decompress(uint8_t* data, uint64_t dataSize, uint32_t decompressedSize);
};

#endif // LZOCOMPRESSION_H
