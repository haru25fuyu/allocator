#include "Allocator.h"
#include <iostream>

void* Allocator::Alloc(size_t size)
{
	MemoryInfo* info_memory = (MemoryInfo*)returned_first;
	MemoryInfo* front = (MemoryInfo*)front_available_;
	
	while (true) {
		//�ݏo���擪�A�h���X�Ō�������
		if (info_memory == nullptr)
			break;
		if (returned_first == nullptr)
			break;
		std::cout << "�ԋp���ꂽ������" << (char*)info_memory << std::endl;
		//�T�C�Y����������Ȃ�������
		if (info_memory->size_ != size) {
			if (info_memory->free_next == nullptr)
				break;
			info_memory = (MemoryInfo*)info_memory->free_next;
			continue;
		}

		info_memory->free_next = nullptr;
		//���^�[�����ꂽ�ŏ��̃A�h���X�Ƃ��Ȃ��ł���Ώ�������
		if (info_memory == (MemoryInfo*)returned_first)
			returned_first = info_memory->free_next;

		//�O�ɑ݂��o�������������Ɏ��g�̃A�h���X������
		MemoryInfo* previous_info = (MemoryInfo*)last_memory_;
		previous_info->next_mem = (char*)info_memory;
		last_memory_ = (char*)info_memory;
		std::cout << "�݂��o��������" << (char*)info_memory << std::endl;
		return info_memory->GetMemory();
	}

	//�O��݂��o�������Ɏ��݂��o��������������		
	MemoryInfo* previous_info = (MemoryInfo*)last_memory_;
	previous_info->next_mem = (char*)front;

	//�ݏo���������̕����m�ۂ���
	MemoryInfo* info = (MemoryInfo*)front;
	info->size_ = size;
	info->next_mem = nullptr;
	info->free_next = nullptr;
	//�ݏo�����Ă��郁�����̐擪�A�h���X����A�ݏo�T�C�Y�������l���t���[�A�h���X�̐擪�ɂȂ�
	front_available_ = (char*)info->GetMemory() + info->size_;
	last_memory_ = (char*)front;
	if (front_available_ > memory_ + size_)
		return nullptr;
	return  info->GetMemory();
}

void Allocator::Free(void* pMemory)
{
	//�@�ԋp���郁�������̌���
	MemoryInfo* info_memory = (MemoryInfo*)memory_;
	void* mem = info_memory->GetMemory();
	while (true) {
		std::cout << "�ݏo��������" << mem << std::endl;
		//�ݏo���擪�A�h���X�Ō�������
		if (mem != pMemory) {
			if (info_memory->next_mem == nullptr)
				return;
			info_memory = (MemoryInfo*)info_memory->next_mem;
			mem = info_memory->GetMemory();
			continue;
		}
		if (returned_first == nullptr) {
			returned_first = (char*)info_memory;	
		}
		//�O��ԋp�����f�[�^�ɐڑ�����ۑ�
		if (returned_last != nullptr) {
			MemoryInfo* last_mem = (MemoryInfo*)returned_last;
			last_mem->free_next = (char*)info_memory;
		}

		returned_last = (char*)info_memory;
		info_memory->next_mem = nullptr;
		//�f�[�^��NULL�Ŗ��߂�
		for (size_t i = sizeof(MemoryInfo); i < info_memory->size_; ++i) {
			char* mem = (char*)info_memory + i;
			mem = NULL;
		}
		return;
	}

}
