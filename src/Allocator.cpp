#include "Allocator.h"
#include <iostream>

void* Allocator::Alloc(size_t size)
{
	MemoryInfo* info_memory = (MemoryInfo*)returned_first;
	MemoryInfo* front = (MemoryInfo*)front_available_;
	
	while (true) {
		//貸出た先頭アドレスで検索する
		if (info_memory == nullptr)
			break;
		if (returned_first == nullptr)
			break;
		std::cout << "返却されたメモリ" << (char*)info_memory << std::endl;
		//サイズが同じじゃなかったら
		if (info_memory->size_ != size) {
			if (info_memory->free_next == nullptr)
				break;
			info_memory = (MemoryInfo*)info_memory->free_next;
			continue;
		}

		info_memory->free_next = nullptr;
		//リターンされた最初のアドレスとおなじであれば書き換え
		if (info_memory == (MemoryInfo*)returned_first)
			returned_first = info_memory->free_next;

		//前に貸し出したメモリ情報に自身のアドレスを入れる
		MemoryInfo* previous_info = (MemoryInfo*)last_memory_;
		previous_info->next_mem = (char*)info_memory;
		last_memory_ = (char*)info_memory;
		std::cout << "貸し出すメモリ" << (char*)info_memory << std::endl;
		return info_memory->GetMemory();
	}

	//前回貸し出した情報に次貸し出すメモリを入れる		
	MemoryInfo* previous_info = (MemoryInfo*)last_memory_;
	previous_info->next_mem = (char*)front;

	//貸出メモリ情報の分を確保する
	MemoryInfo* info = (MemoryInfo*)front;
	info->size_ = size;
	info->next_mem = nullptr;
	info->free_next = nullptr;
	//貸出ししているメモリの先頭アドレスから、貸出サイズ足した値がフリーアドレスの先頭になる
	front_available_ = (char*)info->GetMemory() + info->size_;
	last_memory_ = (char*)front;
	if (front_available_ > memory_ + size_)
		return nullptr;
	return  info->GetMemory();
}

void Allocator::Free(void* pMemory)
{
	//　返却するメモリ情報の検索
	MemoryInfo* info_memory = (MemoryInfo*)memory_;
	void* mem = info_memory->GetMemory();
	while (true) {
		std::cout << "貸出しメモリ" << mem << std::endl;
		//貸出た先頭アドレスで検索する
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
		//前回返却したデータに接続情報を保存
		if (returned_last != nullptr) {
			MemoryInfo* last_mem = (MemoryInfo*)returned_last;
			last_mem->free_next = (char*)info_memory;
		}

		returned_last = (char*)info_memory;
		info_memory->next_mem = nullptr;
		//データをNULLで埋める
		for (size_t i = sizeof(MemoryInfo); i < info_memory->size_; ++i) {
			char* mem = (char*)info_memory + i;
			mem = NULL;
		}
		return;
	}

}
