#pragma once
//========================================================
//include
#include "../Type.h"


namespace base {
namespace util {
//========================================================
//FNV-1ÉnÉbÉVÉÖä÷êî
inline uint32 FNV1Hash(const void* p_buff, size_t size)
{
	const uint32 OFFSET_BASIS = 2166136261;
	const uint32 FNV_32_PRIME = 16777619;

	const uint8* p	  = static_cast<const uint8*>(p_buff);
	uint32		 hash = OFFSET_BASIS;

	for (int i = 0; i < size; ++i)
		hash = (hash * FNV_32_PRIME) ^ (p[i]);

	return hash;
}
} //namespace util
} //namespace base