#pragma once

#include <iostream>
#include <string>

#include <Windows.h>
#include <TlHelp32.h>


// Better than using namespace std;

using std::cout;
using std::endl;
using std::string;

// datatype for a module in memory (dll, regular exe) 
struct module
{
	size_t dwBase, dwSize;
};

class SignatureScanner
{
public:
	// for comparing a region in memory, needed in finding a signature
	static bool MemoryCompare(const BYTE* bData, const BYTE* bMask, const char* szMask) {
		for (; *szMask; ++szMask, ++bData, ++bMask) {
			if (*szMask == 'x' && *bData != *bMask) {
				return false;
			}
		}
		return (*szMask == NULL);
	}

	// for finding a signature/pattern in memory of another process
	static size_t FindSignature(size_t start, size_t size, const char* sig, const char* mask)
	{
		BYTE* data = (BYTE*)start;

		for (size_t i = 0; i < size; i++)
		{
			if (MemoryCompare((const BYTE*)(data + i), (const BYTE*)sig, mask)) {
				return start + i;
			}
		}
		return NULL;
	}
};