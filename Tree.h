#pragma once

#include <list>

template <typename T>
class Tree
{
public:
	struct TreeNode
	{
		T element;
		TreeNode* left = nullptr;
		TreeNode* right = nullptr;
		TreeNode* parent = nullptr;

		void print()
		{
			std::cout << "(" << element << ")";
			if (left) std::cout << "L";
			if (right) std::cout << "R";
			std::cout << std::endl;
			if (left) 
			{ 
				std::cout << "L";
				left->print();
			}
			if (right) {
				std::cout << "R";
				right->print();
			}
		}
	};
	enum class TreeLocation
	{ 
		left, 
		right, 
		top 
	};

public:
	class TreeIterator
	{
	public:
		TreeIterator(TreeNode* node) : pointer_(node) {}
		T& operator*() { return pointer_->element; }
		bool operator!=(const TreeIterator& r) const 
		{ 
			return pointer_ != r.pointer_; 
		}
		TreeIterator& operator++() 
		{
			if (path_.size() == 0)
			{
				push_right();
			}
			switch (path_.back())
			{
				case TreeLocation::left:
				{
					if (pointer_->right)
					{
						this->push_right();
					}
					else
					{
						this->push_up();
					}
				}
				case TreeLocation::right:
				{
					if (pointer_->parent)
					{
						this->push_up();
					}
					else
					{
						assert(path_.size() == 1);
						pointer_ = nullptr;
						path_.pop_back();
					}
				}
				default:
					throw std::runtime_error("should not be here.");
			}
		}
		TreeNode* pointer() 
		{
			return pointer_;
		}
		void push_left()
		{
			while (pointer_->left)
			{
				path_.push_back(TreeLocation::left);
				pointer_ = pointer_->left;
			}
		}
		void push_right()
		{
			if (pointer_->right)
			{
				path_.push_back(TreeLocation::right);
				pointer_ = pointer_->right;
			}
			push_left();
		}
		void push_up()
		{
			path_.pop_back();
			TreeLocation back = TreeLocation::left;
			if (path_.size()) back = path_.back();
			switch (back)
			{
				case TreeLocation::left:
				{
					if (pointer_->right) 
					{
						path_.pop_back();
						path_.push_back(TreeLocation::right);
						push_right();
					}
					else
					{
						push_up();
					}
				}
				case TreeLocation::right:
				{
					push_up();
				}
				throw std::runtime_error("Should not be here.");
			}
		}

	protected:
		std::list<TreeLocation> path_;
		TreeNode* pointer_ = nullptr;
	};

public:
	Tree() {}
	virtual ~Tree() 
	{ 
		while (root_)
		{
			root_ = erase(root_).pointer();
		}
	}
	void insert(const T& element) 
	{
		auto* p = root_;
		if (p) 
		{
			insert_at(p, element);
		}
		else
		{
			p = new TreeNode;
			p->element = element;
			root_ = p;
		}
	}
	TreeIterator erase(TreeIterator it) 
	{
		// TODO(anirul): Memory leak implement me!
		return TreeIterator(nullptr);
	}
	TreeIterator begin() 
	{
		auto* p = root_;
		auto it = TreeIterator(p);
		it.push_left();
		return it;
	}
	TreeIterator end() 
	{
		return TreeIterator(nullptr);
	}
	void print()
	{
		root_->print();
	}

protected:
	void insert_at(TreeNode* p, const T& element)
	{
		if (element < p->element)
		{
			if (p->left)
			{
				insert_at(p->left, element);
			}
			else
			{
				p->left = new TreeNode;
				p->left->element = element;
				p->left->parent = p;
			}
		}
		else
		{
			if (p->right)
			{
				insert_at(p->right, element);
			}
			else
			{
				p->right = new TreeNode;
				p->right->element = element;
				p->right->parent = p;
			}
		}
	}

protected:
	TreeNode* root_ = nullptr;
};
