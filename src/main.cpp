#include "Allocator.h"

// アロケータが管理するメモリ
char memory[ 1000 ];

// アロケータ
Allocator	allocator( memory, sizeof( memory ) );

//-------------------------------------------------------
/// <summary>
///		メイン関数
/// </summary>
//-------------------------------------------------------
int	main()
{
	void* pAllocMemory;

	// メモリを確保
	pAllocMemory = allocator.Alloc( 10 );

	/*
		テストコード
		- 意図したとおりの結果か？
		- アロケータ内部の状態が意図したとおりになっているのか？
		などのテストを行う
	*/

	// メモリを解放
	allocator.Free( pAllocMemory );
}
