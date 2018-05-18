#pragma once

#include <iostream>
using namespace std;
// A class that contains a memory resource.
class MemoryBlock
{
	// TODO: Add resources for the class here.
};

void g(const MemoryBlock &)
{
	cout << "In g(const MemoryBlock&)." << endl;
}

void g(MemoryBlock &&)
{
	cout << "In g(MemoryBlock&&)." << endl;
}

void RightValueRef()
{
	MemoryBlock block;
	g(block);
	g(static_cast<MemoryBlock &&>(block));
}

