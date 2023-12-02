#pragma once
#include<vector>

//�ݏo�������̃w�b�_�[
struct MemoryInof {
	unsigned int size_;
	char* GetMemory() {
		return  (char*)this + sizeof(MemoryInof);
	}
};



//-------------------------------------------------------
/// <summary>
///		�A���P�[�^
/// </summary>
//-------------------------------------------------------
class Allocator
{
	char*			front_available_;	//<! ���p�\�Ȑ擪�A�h���X
	char*			memory_;			//<! �A�N�Z�X�\�ȃA�h���X
	unsigned int	size_;				//<! �A�N�Z�X�\�ȃT�C�Y

	std::vector<MemoryInof*>	available_mem;	//<! ���p�A�h���X�̏��
	std::vector<size_t>			delete_idx;		//<! �ԋp�A�h���X�̏��


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
		front_available_(pMemory + sizeof(Allocator))
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
