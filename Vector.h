#pragma once

template <typename T>
class Vector 
{
public:
	template <typename T>
	class VectorIterator
	{
	public:
		VectorIterator(Vector& vec, std::size_t index) {}
		T& operator*() {}
		VectorIterator operator++() {}
	};

public:
	Vector() {}
	virtual ~Vector() {}
	void reserve(std::size_t size) {}
	std::size_t capacity() {}
	void push_back(const T& element) {}
	VectorIterator begin() {}
	VectorIterator end() {}
	T& operator[](std::size_t index) {}
	const T& at(std::size_t index) const {}
	std::size_t size() const {}
	bool empty() const {}

protected:
	
};