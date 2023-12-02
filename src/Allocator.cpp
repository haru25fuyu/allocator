#include "Allocator.h"
#include <assert.h>

void* Allocator::Alloc(size_t size)
{
	for (size_t i = 0; i < delete_idx.size(); ++i) {
		if (available_mem[delete_idx[i]]->size_ == size) {
			return available_mem[delete_idx[i]]->GetMemory();
		}
	}

	void* front = front_available_;
	available_mem.resize(available_mem.size() + 1);
	int idx = available_mem.size() - 1;
	available_mem[idx] = (MemoryInof*)front;
	available_mem[idx]->size_ = size;
	//�ݏo�����Ă��郁�����̐擪�A�h���X����A�ݏo�T�C�Y�������l���t���[�A�h���X�̐擪�ɂȂ�
	front_available_ = available_mem[idx]->GetMemory() + available_mem[idx]->size_;
	if (front_available_ > memory_+size_)
		return nullptr;
	return  available_mem[idx]->GetMemory();
}

void Allocator::Free(void* pMemory)
{
	//�@�ԋp���郁�������̌���
	unsigned int idx = 0;
	char* info_memory = nullptr;
	for (size_t i = 0; i < available_mem.size(); ++i) {
		info_memory = available_mem[i]->GetMemory();
		//�ݏo���擪�A�h���X�Ō�������
		if (info_memory != pMemory)
			continue;
		// �ԋp���X�g�ɕۑ�
		delete_idx.emplace_back(i);
		idx = i;
		break;
	}

	//������Ȃ�������
	if (info_memory == nullptr)
		return;

	//�f�[�^��NULL�Ŗ��߂�
	for (int i = 0; i < available_mem[idx]->size_; ++i) {
		info_memory[i] = NULL;
	}
}
