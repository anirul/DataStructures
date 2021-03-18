#pragma once

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
		TreeIterator operator++() 
		{
			switch (direction_)
			{
				case TreeLocation::left:
				{
					if (pointer_->left)
					{
						direction_ = TreeLocation::right;
						return TreeIterator(pointer_->left);
					}
					[[fallthrough]];
				}
				case TreeLocation::right:
				{
					if (pointer_->right)
					{
						direction_ = TreeLocation::top;
						return TreeIterator(pointer_->right);
					}
					[[fallthrough]];
				}
				case TreeLocation::top:
				{
					if (pointer_->parent)
						return TreeIterator(pointer_->parent).operator++();
					else
						return TreeIterator(nullptr);
				}
				default:
					throw std::runtime_error("should not be here.");
			}
		}
		TreeNode* pointer() 
		{
			return pointer_;
		}

	protected:
		TreeLocation direction_ = TreeLocation::left;
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
		if (p)
		{
			while (p->left)
			{
				p = p->left;
			}
		}
		return TreeIterator(p);
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
