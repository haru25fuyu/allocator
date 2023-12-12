#pragma once
#include<vector>
#include<iostream>

//貸出メモリのヘッダー
struct MemoryInfo {
	unsigned int size_;
	void* GetMemory() {
		return  (char*)this + sizeof(MemoryInfo);
	}
	char* next_mem = nullptr;		//<! 次に貸し出された先頭メモリ
	char* free_next = nullptr;	//<!　次に返却されたメモリ
};

//-------------------------------------------------------
/// <summary>
///		アロケータ
/// </summary>
//-------------------------------------------------------
class Allocator
{
	char* front_available_;	//<! 利用可能な先頭アドレス
	char* memory_;			//<! アクセス可能なアドレス
	unsigned int	size_;	//<! アクセス可能なサイズ
	char* last_memory_;		//<! 最後に取得されたメモリ
	char* returned_first_;		//<! 返却された先頭メモリ
	char* returned_last_;		//<! 最後に返却されたメモリ
	char* rental_first_;		//<! レンタルした基準メモリ

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
		front_available_(pMemory),
		last_memory_(pMemory),
		returned_first_(nullptr),
		returned_last_(nullptr),
		rental_first_(pMemory)
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
