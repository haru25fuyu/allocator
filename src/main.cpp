#include <iostream>
#include<assert.h>
#include "Allocator.h"
#include <vector>

// アロケータが管理するメモリ
char memory[1000];

// アロケータ
Allocator	allocator(memory, sizeof(memory));

void* operator new(size_t size) {
	return allocator.Alloc(size);
}

void operator delete(void* data) {
	allocator.Free(data);
}

//-------------------------------------------------------
/// <summary>
///		メイン関数
/// </summary>
//-------------------------------------------------------
int	main()
{
	void* pAllocMemory;
	void* aa;
	void* bb;
	void* cc;
	int* a;

	// メモリを確保
	pAllocMemory = allocator.Alloc(10);
	aa = allocator.Alloc(10);
	bb = allocator.Alloc(10);
	a = new int;
	*a = 'a';
	/*
		テストコード
		- 意図したとおりの結果か？
		- アロケータ内部の状態が意図したとおりになっているのか？
		などのテストを行う
	*/
	std::cout <<"pAllocMemory :" << pAllocMemory << std::endl;
	std::cout << "aa :" << aa << std::endl;
	std::cout << "bb :" << bb << std::endl;
	std::cout << "a :" << *a << std::endl;
	allocator.Free(aa);
	cc = allocator.Alloc(10);
	delete a;

	std::cout << "cc :" << cc << std::endl;
	
	
	for (int i = 0; i < 1000; ++i) {
		a = new int;
		
		std::cout << "a：" << *a << std::endl;
		std::cout << "Ra：" << a << std::endl;
		delete a;
	}


	// メモリを解放
	allocator.Free(pAllocMemory);
}
