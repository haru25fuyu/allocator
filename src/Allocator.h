#pragma once

//-------------------------------------------------------
/// <summary>
///		�A���P�[�^
/// </summary>
//-------------------------------------------------------
class Allocator
{
public:
	/// <summary>
	///		�R���X�g���N�^
	/// </summary>
	///
	///		<param name="pMemory">	�A���P�[�^�ŊǗ����郁�����̐擪�A�h���X</param>
	///		<param name="size">		�A���P�[�^�ŊǗ����郁�����̃T�C�Y</param>
	///
	Allocator( char* pMemory, unsigned int size );

	/// <summary>
	///		�w��T�C�Y�̃��������m��
	/// </summary>
	///
	///		<param name="size">�m�ۂ������T�C�Y</param>
	///
	///		<returns>
	///			�m�ۂ����������̐擪�A�h���X
	///		</returns>
	///
	void*	Alloc( unsigned int size );

	/// <summary>
	///		�w�胁���������
	/// </summary>
	///
	///		<param name="pMemory">����������������̐擪�A�h���X</param>
	///
	void	Free( void* pMemory );
};
