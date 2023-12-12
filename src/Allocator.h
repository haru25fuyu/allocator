#pragma once
#include<vector>
#include<iostream>

//�ݏo�������̃w�b�_�[
struct MemoryInfo {
	unsigned int size_;
	void* GetMemory() {
		return  (char*)this + sizeof(MemoryInfo);
	}
	char* next_mem = nullptr;		//<! ���ɑ݂��o���ꂽ�擪������
	char* free_next = nullptr;	//<!�@���ɕԋp���ꂽ������
};

//-------------------------------------------------------
/// <summary>
///		�A���P�[�^
/// </summary>
//-------------------------------------------------------
class Allocator
{
	char* front_available_;	//<! ���p�\�Ȑ擪�A�h���X
	char* memory_;			//<! �A�N�Z�X�\�ȃA�h���X
	unsigned int	size_;	//<! �A�N�Z�X�\�ȃT�C�Y
	char* last_memory_;		//<! �Ō�Ɏ擾���ꂽ������
	char* returned_first_;		//<! �ԋp���ꂽ�擪������
	char* returned_last_;		//<! �Ō�ɕԋp���ꂽ������
	char* rental_first_;		//<! �����^�������������

public:
	/// <summary>
	///		�R���X�g���N�^
	/// </summary>
	///
	///		<param name="pMemory">	�A���P�[�^�ŊǗ����郁�����̐擪�A�h���X</param>
	///		<param name="size">		�A���P�[�^�ŊǗ����郁�����̃T�C�Y</param>
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
	///		�w��T�C�Y�̃��������m��
	/// </summary>
	///
	///		<param name="size">�m�ۂ������T�C�Y</param>
	///
	///		<returns>
	///			�m�ۂ����������̐擪�A�h���X
	///		</returns>
	///

	void* Alloc(size_t size);

	/// <summary>
	///		�w�胁���������
	/// </summary>
	///
	///		<param name="pMemory">����������������̐擪�A�h���X</param>
	///
	void	Free(void* pMemory);
};
