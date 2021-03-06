#pragma once

#include <limits>

template <typename T>
class Vector 
{
public:
	class VectorIterator
	{
	public:
		VectorIterator(Vector& vec, std::size_t index) : 
			vec_(vec), index_(index) {}
		T& operator*() { return vec_.operator[](index_); }
		bool operator!=(const VectorIterator& r) const
		{
			return index_ != r.index_;
		}
		VectorIterator& operator++() 
		{ 
			if (index_ < vec_.size())
				index_++;
			if (index_ >= vec_.size())
				index_ = end_;
			return *this;
		}
		std::size_t index() const { return index_; }

	protected:
		Vector& vec_;
		std::size_t index_;
		const std::size_t end_ = std::numeric_limits<std::size_t>::max();
	};

public:
	Vector() {}
	virtual ~Vector() { if (data_) delete [] data_; }
	void reserve(std::size_t size) 
	{ 
		T* temp = data_;
		data_ = new T[size];
		if (temp) 
		{
			for (int i = 0; i < size_; ++i)
				data_[i] = temp[i];
			delete [] temp;
		}
		capacity_ = size;
	}
	std::size_t capacity() { return capacity_; }
	void push_back(const T& element) 
	{
		if (size_ + 1 > capacity_)
			reserve((capacity_) ? capacity_ * 2 : 8);
		data_[size_] = element;
		size_++;
	}
	VectorIterator& erase(const VectorIterator& it) 
	{
		auto index = it.index();
		for (std::size_t i = index; i < size_; ++i)
			data_[i] = data_[i + 1];
		size_--;
		if (size_ < capacity_ / 2)
			reserve(capacity_ / 2);
	}
	VectorIterator begin() { return VectorIterator(*this, 0); }
	VectorIterator end() { return VectorIterator(*this, end_); }
	T& operator[](std::size_t index) { return data_[index]; }
	const T& at(std::size_t index) const { return data_[index]; }
	std::size_t size() const { return size_; }
	bool empty() const { return !(bool)size_; }

protected:
	std::size_t size_ = 0;
	std::size_t capacity_ = 0;
	const std::size_t end_ = std::numeric_limits<std::size_t>::max();
	T* data_ = nullptr;
};
