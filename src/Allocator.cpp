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
	//貸出ししているメモリの先頭アドレスから、貸出サイズ足した値がフリーアドレスの先頭になる
	front_available_ = available_mem[idx]->GetMemory() + available_mem[idx]->size_;
	if (front_available_ > memory_+size_)
		return nullptr;
	return  available_mem[idx]->GetMemory();
}

void Allocator::Free(void* pMemory)
{
	//　返却するメモリ情報の検索
	unsigned int idx = 0;
	char* info_memory = nullptr;
	for (size_t i = 0; i < available_mem.size(); ++i) {
		info_memory = available_mem[i]->GetMemory();
		//貸出た先頭アドレスで検索する
		if (info_memory != pMemory)
			continue;
		// 返却リストに保存
		delete_idx.emplace_back(i);
		idx = i;
		break;
	}

	//見つからなかったら
	if (info_memory == nullptr)
		return;

	//データをNULLで埋める
	for (int i = 0; i < available_mem[idx]->size_; ++i) {
		info_memory[i] = NULL;
	}
}
