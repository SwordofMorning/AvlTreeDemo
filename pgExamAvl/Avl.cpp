#include "Avl.h"

/* ===== Function 00 : Constructor ===== */
template<typename elemType>
Avl<elemType>::Avl()
{
}

/* ===== Function 01 : 查找最小值 ===== */
template<typename elemType>
Avl<elemType>::Node<elemType>* Avl<elemType>::FindMin(Node<elemType>* node)
{
	if (!node) return nullptr;

	if (!node->left) return node;

	return FindMin(node->left);
}

/* ===== Function 02 : 查找最大值 ===== */
template<typename elemType>
Avl<elemType>::Node<elemType>* Avl<elemType>::FindMax(Node<elemType>* node)
{
	if (!node) return nullptr;

	if (!node->right) return node;

	return FindMax(node->right);
}

/* ===== Function 03 : 按值查找 ===== */
template<typename elemType>
Avl<elemType>::Node<elemType>* Avl<elemType>::FindVal(const elemType& ele)
{
	return this->FindVal(ele, root);
}

template<typename elemType>
Avl<elemType>::Node<elemType>* Avl<elemType>::FindVal(const elemType& ele, Node<elemType>* node)
{
	// 空节点
	if (!node) return nullptr;

	// 是当前节点
	if (node->element == ele) return node;

	// 查左子树
	Node<elemType>* lt = nullptr;
	lt = this->FindVal(ele, node->left);

	if (lt) return lt;

	// 查右子树
	Node<elemType>* rt = nullptr;
	rt = this->FindVal(ele, node->right);

	if (rt) return rt;

	// 无结果
	return nullptr;
}

/* ===== Function 04 : 插入（线索二叉树，按准则排序，此处用<） ===== */
template<typename elemType>
void Avl<elemType>::Insert(const elemType& ele)
{
	this->Insert(ele, root);
}

template<typename elemType>
void Avl<elemType>::Insert(const elemType& ele, Node<elemType>*& node)
{
	// 有空位插
	if (!node)
	{
		node = new Node<elemType>(ele, nullptr, nullptr);
	}
	// 这个空位有人了，和他比较下，按一定排序准则选择左右，这里以 < 为排序准则。
	else if (ele < node->element)
	{
		this->Insert(ele, node->left);
	}
	else if (node->element < ele)
	{
		this->Insert(ele, node->right);
	}

	this->Balance(node);
}

/* ===== Function 05 : 按元素删除 ===== */
template<typename elemType>
void Avl<elemType>::Remove_val(const elemType& ele)
{
	this->Remove_val(ele, root);
}

template<typename elemType>
void Avl<elemType>::Remove_val(const elemType& ele, Node<elemType>*& node)
{
	if (!node) return;

	// 不是目标，比较
	if (ele < node->element)
		this->Remove_val(ele, node->left);
	else if (ele > node->element)
		this->Remove_val(ele, node->left);
	// 找到目标
	else if (node->left && node->right)		// 被删除目标有两个节点
	{
		// 可替换左子树的最大值、右子树的最小值（中序向量的两个点，选一）
		node->element = this->FindMin(node->right)->element;
		// 更新删除目标
		Remove_val(node->element, node->right);
	}
	else									// 被删除目标只有一个节点或无节点
	{
		Node<elemType>* oldOne = node;
		node = (node->left) ?
			node->left :
			node->right;
		delete oldOne;
	}

	Balance(node);
}

/* ===== Function 06 : 高度计算 ===== */
template<typename elemType>
int Avl<elemType>::Height(Node<elemType>* node)
{
	// 这里从0计数，即空树为0；常见的也有使用-1
	return node ?
		node->height :
		0;
}

/* ===== Function 07 : LL ===== */
template<typename elemType>
void Avl<elemType>::LL(Node<elemType>*& violate)
{
	Node<elemType>* violateLeft = violate->left;

	// 交换节点
	violate->left = violateLeft->right;
	violateLeft->right = violate;

	// 高度更新
	violate->height = std::max(Height(violate->left), Height(violate->right)) + 1;
	violateLeft->height = std::max(Height(violateLeft->left), violate->height) + 1;

	violate = violateLeft;
}

/* ===== Function 08 : RR ===== */
template<typename elemType>
void Avl<elemType>::RR(Node<elemType>*& violate)
{
	Node<elemType>* violateRight = violate->right;

	// 交换节点
	violate->right = violateRight->left;
	violateRight->left = violate;

	// 高度更新
	violate->height = std::max(Height(violate->left), Height(violate->right)) + 1;
	violateRight->height = std::max(violate->height, Height(violateRight->right)) + 1;

	violate = violateRight;
}

/* ===== Function 09 : LR ===== */
template<typename elemType>
void Avl<elemType>::LR(Node<elemType>*& violate)
{
	RR(violate->left);
	LL(violate);
}

/* ===== Function 09 : RL ===== */
template<typename elemType>
void Avl<elemType>::RL(Node<elemType>*& violate)
{
	LL(violate->right);
	RR(violate);
}

/* ===== Function 11 : 平衡 ===== */
template<typename elemType>
void Avl<elemType>::Balance(Node<elemType>*& node)
{
	if (!node)	return;

	// 左高
	if (Height(node->left) - Height(node->right) >= 2)
	{
		if (Height(node->left->left) >= Height(node->left->right))
		{
			LL(node);
		}
		else
		{
			LR(node);
		}
	}
	// 右高
	else if (Height(node->right) - Height(node->left) >= 2)
	{
		if (Height(node->right->right) >= Height(node->right->right))
		{
			RR(node);
		}
		else
		{
			RL(node);
		}
	}

	// 更新高度
	node->height = std::max(Height(node->left), Height(node->right)) + 1;
}
