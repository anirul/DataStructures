#pragma once

template <typename T>
class Tree
{
protected:
	struct TreeNode
	{
		T element;
		TreeNode* left;
		TreeNode* right;
	};

public:
	class TreeIterator
	{
	public:
		TreeIterator(TreeNode* node) {}
		T& operator*() {}
		bool operator!=(const TreeIterator& r) const {}
		TreeIterator operator++() {}
		TreeNode* pointer() {}
	};

public:
	Tree() {}
	virtual ~Tree() {}
	void insert(const T& element) {}
	TreeIterator erase(TreeIterator it) {}
	TreeIterator begin() {}
	TreeIterator end() {}
};