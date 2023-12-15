#include "Allocator.h"
#include <iostream>
#include <stdexcept>

void* Allocator::Alloc(size_t size)
{
	MemoryInfo* info_memory = (MemoryInfo*)returned_first_;
	MemoryInfo* previous_memory = nullptr;
	MemoryInfo* front = (MemoryInfo*)front_available_;

	while (true) {
		//貸出た先頭アドレスで検索する
		if (info_memory == nullptr)
			break;

		if (returned_first_ == nullptr)
			break;
		//サイズが同じじゃなかったら
		if (info_memory->size_ != size) {
			if (info_memory->free_next == nullptr)
				break;
			previous_memory = info_memory;
			info_memory = (MemoryInfo*)info_memory->free_next;
			continue;
		}

		//接続データの更新
		if (previous_memory != nullptr) {
			previous_memory->free_next = info_memory->free_next;
		}
		//リターンされた最初のアドレスとおなじであれば書き換え
		if (returned_first_ == (char*)info_memory) {
			returned_first_ = info_memory->free_next;
		}
		if (returned_last_ == (char*)info_memory) 
			returned_last_ = (char*)previous_memory;
		

		info_memory->free_next = nullptr;

		//前に貸し出したメモリ情報に自身のアドレスを入れる
		MemoryInfo* previous_info = (MemoryInfo*)last_memory_;
		previous_info->next_mem = (char*)info_memory;
		last_memory_ = (char*)info_memory;

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

	if (rental_first_ == nullptr)
		rental_first_ = (char*)info;
	return  info->GetMemory();
}

void Allocator::Free(void* pMemory)
{
	//　返却するメモリ情報の検索
	MemoryInfo* previous_info = nullptr;
	MemoryInfo* info_memory = (MemoryInfo*)rental_first_;	//<! 返却された先頭メモリ
	void* mem = info_memory->GetMemory();

	while (true) {
		if (info_memory == nullptr)
			break;
		//貸出た先頭アドレスで検索する
		if (mem != pMemory) {
			if (info_memory->next_mem == nullptr)
				throw std::invalid_argument("Negative value encountered");
			previous_info = info_memory;
			info_memory = (MemoryInfo*)info_memory->next_mem;
			mem = info_memory->GetMemory();
			continue;
		}

		//返却されたのが最初だったら自身のメモリをリストの先頭にする
		if (returned_first_ == nullptr) {
			returned_first_ = (char*)info_memory;
		}

		//前回返却したデータに接続情報を保存
		if (returned_last_ != nullptr) {
			MemoryInfo* last_mem = (MemoryInfo*)returned_last_;
			last_mem->free_next = (char*)info_memory;
		}

		returned_last_ = (char*)info_memory;

		//接続データの変更
		if (previous_info != nullptr) {
			previous_info->next_mem = info_memory->next_mem;
			if (last_memory_ == (char*)info_memory)
				last_memory_ = (char*)previous_info;
		}

		if(rental_first_  == (char*)info_memory)
			rental_first_ = info_memory->next_mem;

		info_memory->next_mem = nullptr;
		info_memory->free_next = nullptr;

		//データをNULLで埋める
		for (size_t i = sizeof(MemoryInfo); i < info_memory->size_; ++i) {
			char* mem = (char*)info_memory + i;
			mem = NULL;
		}
		return;
	}

}
