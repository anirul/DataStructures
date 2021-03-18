#pragma once

template <typename T>
class List 
{
protected:
	struct ListNode 
	{
		T element;
		ListNode* next = nullptr;
	};

public:
	class ListIterator
	{
	public:
		ListIterator(ListNode* pointer) : pointer_(pointer) {}
		T& operator*() { return pointer_->element; }
		bool operator!=(const ListIterator& r) const 
		{ 
			return pointer_ == r.pointer_; 
		}
		ListIterator operator++() 
		{
			if (pointer_)
				return ListIterator(pointer_->next);
			else
				return ListIterator(nullptr);
		}
		ListNode* pointer() { return pointer_; }

	protected:
		ListNode* pointer_ = nullptr;
	};

public:
	List() {}
	virtual ~List() { while (front().pointer()) pop_front(); }
	ListIterator front() { return ListIterator(root_); }
	ListIterator back() { return ListIterator(end_); }
	ListIterator begin() { return ListIterator(root_); }
	ListIterator end() { return ListIterator(nullptr); }
	void clear() {}
	ListIterator insert(ListIterator it, const T& element) {}
	ListIterator erase(ListIterator it) 
	{
		ListNode* previous = previous_element(it.pointer());
		ListNode* next = it.pointer()->next;
		delete it.pointer();
		previous->next = next;
		size_--;
	}
	void push_back(const T& element) 
	{
		ListNode* n = new ListNode{};
		n->element = element;
		n->next = nullptr;
		if (end_)
		{
			end_->next = n;
			end_ = n;
		}
		else
		{
			end_ = n;
		}
		size_++;
		if (size_ == 1)
		{
			root_ = end_;
		}
	}
	void pop_back() 
	{
		if (end_)
		{
			ListNode* previous = previous_element(end_);
			delete end_;
			if (previous)
			{
				previous->next = nullptr;
				end_ = previous;
			}
			size_--;
		}
		if (size_ == 0)
		{
			root_ = nullptr;
			end_ = nullptr;
		}
	}
	void push_front(const T& element) 
	{
		ListNode* n = new ListNode{};
		n->element = element;
		n->next = root_;
		root_ = n;
		if (!end_) end_ = n;
		size_++;
	}
	void pop_front() 
	{
		if (!root_) return;
		ListNode* p = root_->next;
		delete root_;
		root_ = p;
		size_--;
		if (size_ == 1)
		{
			end_ = root_;
		}
	}
	bool empty() const { return (bool)root_; }
	std::size_t size() const { return size_; }

protected:
	ListNode* previous_element(ListNode* it)
	{
		ListNode* previous = root_;
		if (previous != it)
		{
			assert(previous);
			previous = previous->next;
		}
		return previous;
	}
	ListNode* root_ = nullptr;
	ListNode* end_ = nullptr;
	std::size_t size_ = 0;
};