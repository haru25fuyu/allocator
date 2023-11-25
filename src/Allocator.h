#pragma once

//-------------------------------------------------------
/// <summary>
///		アロケータ
/// </summary>
//-------------------------------------------------------
class Allocator
{
public:
	/// <summary>
	///		コンストラクタ
	/// </summary>
	///
	///		<param name="pMemory">	アロケータで管理するメモリの先頭アドレス</param>
	///		<param name="size">		アロケータで管理するメモリのサイズ</param>
	///
	Allocator( char* pMemory, unsigned int size );

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
	void*	Alloc( unsigned int size );

	/// <summary>
	///		指定メモリを解放
	/// </summary>
	///
	///		<param name="pMemory">解放したいメモリの先頭アドレス</param>
	///
	void	Free( void* pMemory );
};
