#include "Allocator.h"
#include <iostream>
#include <stdexcept>

void* Allocator::Alloc(size_t size)
{
	MemoryInfo* info_memory = (MemoryInfo*)returned_first_;
	MemoryInfo* previous_memory = nullptr;
	MemoryInfo* front = (MemoryInfo*)front_available_;

	while (true) {
		//�ݏo���擪�A�h���X�Ō�������
		if (info_memory == nullptr)
			break;
		std::cout << "�ԋp���X�g" << info_memory->GetMemory() << std::endl;
		if (returned_first_ == nullptr)
			break;

		//�T�C�Y����������Ȃ�������
		if (info_memory->size_ != size) {
			if (info_memory->free_next == nullptr)
				break;
			previous_memory = info_memory;
			info_memory = (MemoryInfo*)info_memory->free_next;
			continue;
		}

		//�ڑ��f�[�^�̍X�V
		if (previous_memory != nullptr) {
			previous_memory->free_next = info_memory->free_next;
		}

		info_memory->free_next = nullptr;
		//���^�[�����ꂽ�ŏ��̃A�h���X�Ƃ��Ȃ��ł���Ώ�������
		if (info_memory == (MemoryInfo*)returned_first_)
			returned_first_ = info_memory->free_next;

		info_memory->free_next = nullptr;
		//�O�ɑ݂��o�������������Ɏ��g�̃A�h���X������
		//std::cout << "�݂��o��������" << last_memory_ << std::endl;
		MemoryInfo* previous_info = (MemoryInfo*)last_memory_;
		previous_info->next_mem = (char*)info_memory;
		last_memory_ = (char*)info_memory;
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
	MemoryInfo* previous_info = nullptr;
	MemoryInfo* info_memory = (MemoryInfo*)rental_first_;		//<! �ԋp���ꂽ�擪������
	;
	void* mem = info_memory->GetMemory();
	while (true) {
	
		if (info_memory == nullptr)
			break;
		//�ݏo���擪�A�h���X�Ō�������
		if (mem != pMemory) {
			if (info_memory->next_mem == nullptr)
				throw std::invalid_argument("Negative value encountered"); 
			previous_info = info_memory;
			info_memory = (MemoryInfo*)info_memory->next_mem;
			mem = info_memory->GetMemory();
			continue;
		}

		if (returned_first_ == nullptr) {
			returned_first_ = (char*)info_memory;
			returned_last_ = nullptr;
		}

		//�O��ԋp�����f�[�^�ɐڑ�����ۑ�
		if (returned_last_ != nullptr) {
			MemoryInfo* last_mem = (MemoryInfo*)returned_last_;
			last_mem->free_next = (char*)info_memory;
		}
		else {
			returned_last_ = (char*)info_memory;
		}
		

		//�ڑ��f�[�^�̕ύX
		if (previous_info != nullptr) {
			previous_info->next_mem = info_memory->next_mem;
		}
		else {
			if(info_memory->next_mem != nullptr)
				rental_first_ = info_memory->next_mem;
		}

		info_memory->next_mem = nullptr;
		info_memory->free_next = nullptr;

		//�f�[�^��NULL�Ŗ��߂�
		for (size_t i = sizeof(MemoryInfo); i < info_memory->size_; ++i) {
			char* mem = (char*)info_memory + i;
			mem = NULL;
		}
		std::cout << "�ԋp����" << pMemory << std::endl;
		return;
	}

}
