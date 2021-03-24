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
	virtual ~List() { while (begin().pointer()) pop_front(); }
	T& front() { return root_->element; }
	T& back() 
	{ 
		auto* p = root_;
		while (p->next) p = p->next;
		return p->element; 
	}
	ListIterator begin() { return ListIterator(root_); }
	ListIterator end() { return ListIterator(nullptr); }
	void clear() { while (root_) erase(root_); }
	ListIterator insert(ListIterator it, const T& element) 
	{
		ListNode* current = it.pointer();
		ListNode* new_element = new ListNode;
		new_element->element = element;
		new_element->next = current->next;
		current->next = new_element;
		size_++;
	}
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