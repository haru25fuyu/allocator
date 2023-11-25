#include <iostream>
#include<assert.h>
#include "Allocator.h"

// アロケータが管理するメモリ
char memory[1000];

// アロケータ
Allocator	allocator(memory, sizeof(memory));

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
	// メモリを確保
	pAllocMemory = allocator.Alloc(10);
	aa = allocator.Alloc(10);
	bb = allocator.Alloc(10);
	

	/*
		テストコード
		- 意図したとおりの結果か？
		- アロケータ内部の状態が意図したとおりになっているのか？
		などのテストを行う
	*/
	std::cout <<"pAllocMemory :" << pAllocMemory << std::endl;
	std::cout << "aa :" << aa << std::endl;
	std::cout << "bb :" << bb << std::endl;
	allocator.Free(aa);
	cc = allocator.Alloc(10);

	std::cout << "cc :" << cc << std::endl;

	

	// メモリを解放
	allocator.Free(pAllocMemory);
}
