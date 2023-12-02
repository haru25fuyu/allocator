#pragma once
#include<vector>

//貸出メモリのヘッダー
struct MemoryInof {
	unsigned int size_;
	char* GetMemory() {
		return  (char*)this + sizeof(MemoryInof);
	}
};



//-------------------------------------------------------
/// <summary>
///		アロケータ
/// </summary>
//-------------------------------------------------------
class Allocator
{
	char*			front_available_;	//<! 利用可能な先頭アドレス
	char*			memory_;			//<! アクセス可能なアドレス
	unsigned int	size_;				//<! アクセス可能なサイズ

	std::vector<MemoryInof*>	available_mem;	//<! 利用アドレスの情報
	std::vector<size_t>			delete_idx;		//<! 返却アドレスの情報


public:
	/// <summary>
	///		コンストラクタ
	/// </summary>
	///
	///		<param name="pMemory">	アロケータで管理するメモリの先頭アドレス</param>
	///		<param name="size">		アロケータで管理するメモリのサイズ</param>
	///
	Allocator(char* pMemory, unsigned int size) :
		memory_(pMemory),
		size_(size),		
		front_available_(pMemory + sizeof(Allocator))
	{
	}

	/// <summary>
	///		指定サイズのメモリを確保
	/// </summary>
	///
	///		<param name="size">確保したいサイズ</param>
	///
	///		<returns>
	///			確保したメモリの先頭アドレス
	///		</returns>
	///
	
	void* Alloc(size_t size);

	/// <summary>
	///		指定メモリを解放
	/// </summary>
	///
	///		<param name="pMemory">解放したいメモリの先頭アドレス</param>
	///
	void	Free(void* pMemory);
};
