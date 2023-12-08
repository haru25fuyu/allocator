#include "Allocator.h"
#include <iostream>

void* Allocator::Alloc(size_t size)
{
	MemoryInfo* info_memory = (MemoryInfo*)memory_;
	char* mem = info_memory->GetMemory();
	while (true) {
		//貸出た先頭アドレスで検索する
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
	//前回貸し出した情報に次貸し出すメモリを入れる		
	MemoryInfo* previous_info = (MemoryInfo*)last_memory_;
	previous_info->next_mem = front;

	//貸出メモリ情報の分を確保する
	MemoryInfo* info = (MemoryInfo*)front;
	info->size_ = size;
	info->next_mem = nullptr;
	info->returned = false;
	//貸出ししているメモリの先頭アドレスから、貸出サイズ足した値がフリーアドレスの先頭になる
	front_available_ = info->GetMemory() + info->size_;
	last_memory_ = (char*)front;
	if (front_available_ > memory_ + size_)
		return nullptr;
	return  info->GetMemory();
}

void Allocator::Free(void* pMemory)
{
	//　返却するメモリ情報の検索
	MemoryInfo* info_memory = (MemoryInfo*)memory_;
	char* mem = info_memory->GetMemory();
	while (true) {
		
		//貸出た先頭アドレスで検索する
		if (mem != pMemory) {			
			mem = info_memory->GetMemory();
			if (info_memory->next_mem == nullptr)
				return;
			info_memory = info_memory->next_mem;
			continue;
		}
		// 返却リストに保存
		info_memory->returned = true;
		//データをNULLで埋める
		for (int i = sizeof(MemoryInfo); i < info_memory->size_; ++i) {
			char* mem = (char*)info_memory + i;
			mem = NULL;
		}
		return;
	}

}
