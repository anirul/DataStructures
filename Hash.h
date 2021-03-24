#pragma once

#include <functional>
#include "Vector.h"

template <typename T, int TABLE_SIZE_BIT = 8>
class HashMap 
{
public:
	class HashMapIterator 
	{
	public:
		HashMapIterator(
			HashMap& hash_map, 
			std::int64_t hash = 0, 
			std::int64_t pos = -1) :
			hash_map_(hash_map), hash_(hash), pos_(pos) {}
		T& operator*() 
		{
			return hash_map_.table_[hash_ % table_size]->operator[](pos_);
		}
		HashMapIterator& operator++()
		{
			auto old_hash = hash_;
			// Check if at the end.
			if (pos_ != -1) 
			{
				pos_++;
				if (pos_ >= hash_map_.table_[hash_ % table_size]->size())
					pos_ = -1;
			}
			// If not the end then iterate and check.
			if (pos_ == -1)
			{
				// Go to the next hash (in case current one doesn't exist).
				while (!hash_map_.table_[hash_ % table_size]) hash_++;
				// This is the end!
				if (hash_ < old_hash)
				{
					pos_ = -1;
					return *this;
				}
				pos_ = 0;
			}
			return *this;
		}
		bool operator!=(const HashMapIterator& r)
		{
			if (hash_ != r.hash_)
				return false;
			if (pos_ != r.pos_)
				return false;
			return true;
		}

	protected:
		const std::int64_t table_size = 1 << TABLE_SIZE_BIT;
		HashMap& hash_map_;
		std::int64_t hash_ = 0;
		std::size_t pos_;
	};

public:
	HashMap(std::function<int(const T&)> func) : func_(func)
	{ 
		for(int i = 0; i < TABLE_SIZE; ++i) 
			table_[i] = nullptr; 
	}
	virtual ~HashMap() 
	{ 
		for(int i = 0; i < TABLE_SIZE; ++i)
		{ 
			if (table_[i]) 
				delete table_[i]; 
		}
	}
	HashMapIterator insert(const T& element)
	{
		int hash = func_(element);
		auto vec = table_[hash % TABLE_SIZE];
		if (!table_[hash % TABLE_SIZE])
		{
			table_[hash % TABLE_SIZE] = new Vector<T>();
		}
		table_[hash % TABLE_SIZE]->push_back(element);
		size_++;
		return HashMapIterator(
			*this, 
			hash, 
			table_[hash % TABLE_SIZE]->size() - 1);
	}
	std::size_t size() const
	{
		return size_;
	}
	HashMapIterator begin()
	{
		auto hmi = HashMapIterator(*this);
		return ++hmi;
	}
	HashMapIterator end()
	{
		auto hmi = HashMapIterator(
			*this, 
			std::numeric_limits<std::int64_t>::max());
		return ++hmi;
	}

protected:
	std::function<int(const T&)> func_;
	std::size_t size_ = 0;
	const int TABLE_SIZE = 1 << TABLE_SIZE_BIT;
	Vector<T>* table_[1 << TABLE_SIZE_BIT];
};
