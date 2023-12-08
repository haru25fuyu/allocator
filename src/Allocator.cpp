#include "Allocator.h"
#include <iostream>

void* Allocator::Alloc(size_t size)
{
	MemoryInfo* info_memory = (MemoryInfo*)memory_;
	char* mem = info_memory->GetMemory();
	while (true) {
		//�ݏo���擪�A�h���X�Ō�������
		if (info_memory == nullptr)
			break;

		if (!info_memory->returned || info_memory->size_ != size) {
			info_memory = info_memory->next_mem;
			if (info_memory->next_mem == nullptr)
				break;
			mem = info_memory->GetMemory();
			continue;
		}
		info_memory->returned = false;
		return info_memory->GetMemory();
	}

	MemoryInfo* front = (MemoryInfo*)front_available_;
	//�O��݂��o�������Ɏ��݂��o��������������		
	MemoryInfo* previous_info = (MemoryInfo*)last_memory_;
	previous_info->next_mem = front;

	//�ݏo���������̕����m�ۂ���
	MemoryInfo* info = (MemoryInfo*)front;
	info->size_ = size;
	info->next_mem = nullptr;
	info->returned = false;
	//�ݏo�����Ă��郁�����̐擪�A�h���X����A�ݏo�T�C�Y�������l���t���[�A�h���X�̐擪�ɂȂ�
	front_available_ = info->GetMemory() + info->size_;
	last_memory_ = (char*)front;
	if (front_available_ > memory_ + size_)
		return nullptr;
	return  info->GetMemory();
}

void Allocator::Free(void* pMemory)
{
	//�@�ԋp���郁�������̌���
	MemoryInfo* info_memory = (MemoryInfo*)memory_;
	char* mem = info_memory->GetMemory();
	while (true) {
		
		//�ݏo���擪�A�h���X�Ō�������
		if (mem != pMemory) {			
			mem = info_memory->GetMemory();
			if (info_memory->next_mem == nullptr)
				return;
			info_memory = info_memory->next_mem;
			continue;
		}
		// �ԋp���X�g�ɕۑ�
		info_memory->returned = true;
		//�f�[�^��NULL�Ŗ��߂�
		for (int i = sizeof(MemoryInfo); i < info_memory->size_; ++i) {
			char* mem = (char*)info_memory + i;
			mem = NULL;
		}
		return;
	}

}
