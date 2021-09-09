#include "Avl.h"

/* ===== Function 00 : Constructor ===== */
template<typename elemType>
Avl<elemType>::Avl()
{
}

/* ===== Function 01 : ������Сֵ ===== */
template<typename elemType>
Avl<elemType>::Node<elemType>* Avl<elemType>::FindMin(Node<elemType>* node)
{
	if (!node) return nullptr;

	if (!node->left) return node;

	return FindMin(node->left);
}

/* ===== Function 02 : �������ֵ ===== */
template<typename elemType>
Avl<elemType>::Node<elemType>* Avl<elemType>::FindMax(Node<elemType>* node)
{
	if (!node) return nullptr;

	if (!node->right) return node;

	return FindMax(node->right);
}

/* ===== Function 03 : ��ֵ���� ===== */
template<typename elemType>
Avl<elemType>::Node<elemType>* Avl<elemType>::FindVal(const elemType& ele)
{
	return this->FindVal(ele, root);
}

template<typename elemType>
Avl<elemType>::Node<elemType>* Avl<elemType>::FindVal(const elemType& ele, Node<elemType>* node)
{
	// �սڵ�
	if (!node) return nullptr;

	// �ǵ�ǰ�ڵ�
	if (node->element == ele) return node;

	// ��������
	Node<elemType>* lt = nullptr;
	lt = this->FindVal(ele, node->left);

	if (lt) return lt;

	// ��������
	Node<elemType>* rt = nullptr;
	rt = this->FindVal(ele, node->right);

	if (rt) return rt;

	// �޽��
	return nullptr;
}

/* ===== Function 04 : ���루��������������׼�����򣬴˴���<�� ===== */
template<typename elemType>
void Avl<elemType>::Insert(const elemType& ele)
{
	this->Insert(ele, root);
}

template<typename elemType>
void Avl<elemType>::Insert(const elemType& ele, Node<elemType>*& node)
{
	// �п�λ��
	if (!node)
	{
		node = new Node<elemType>(ele, nullptr, nullptr);
	}
	// �����λ�����ˣ������Ƚ��£���һ������׼��ѡ�����ң������� < Ϊ����׼��
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

/* ===== Function 05 : ��Ԫ��ɾ�� ===== */
template<typename elemType>
void Avl<elemType>::Remove_val(const elemType& ele)
{
	this->Remove_val(ele, root);
}

template<typename elemType>
void Avl<elemType>::Remove_val(const elemType& ele, Node<elemType>*& node)
{
	if (!node) return;

	// ����Ŀ�꣬�Ƚ�
	if (ele < node->element)
		this->Remove_val(ele, node->left);
	else if (ele > node->element)
		this->Remove_val(ele, node->left);
	// �ҵ�Ŀ��
	else if (node->left && node->right)		// ��ɾ��Ŀ���������ڵ�
	{
		// ���滻�����������ֵ������������Сֵ�����������������㣬ѡһ��
		node->element = this->FindMin(node->right)->element;
		// ����ɾ��Ŀ��
		Remove_val(node->element, node->right);
	}
	else									// ��ɾ��Ŀ��ֻ��һ���ڵ���޽ڵ�
	{
		Node<elemType>* oldOne = node;
		node = (node->left) ?
			node->left :
			node->right;
		delete oldOne;
	}

	Balance(node);
}

/* ===== Function 06 : �߶ȼ��� ===== */
template<typename elemType>
int Avl<elemType>::Height(Node<elemType>* node)
{
	// �����0������������Ϊ0��������Ҳ��ʹ��-1
	return node ?
		node->height :
		0;
}

/* ===== Function 07 : LL ===== */
template<typename elemType>
void Avl<elemType>::LL(Node<elemType>*& k2)
{
	Node<elemType>* k1 = k2->left;

	// �����ڵ�
	k2->left = k1->right;
	k1->right = k2;

	// �߶ȸ���
	k2->height = std::max(Height(k2->left), Height(k2->right)) + 1;
	k1->height = std::max(Height(k1->left), k2->height) + 1;

	k2 = k1;
}

/* ===== Function 08 : RR ===== */
template<typename elemType>
void Avl<elemType>::RR(Node<elemType>*& k2)
{
	Node<elemType>* k1 = k2->right;

	// �����ڵ�
	k2->right = k1->left;
	k1->left = k2;

	// �߶ȸ���
	k2->height = std::max(Height(k2->left), Height(k2->right)) + 1;
	k1->height = std::max(k2->height, Height(k1->right)) + 1;

	k2 = k1;
}

/* ===== Function 09 : LR ===== */
template<typename elemType>
void Avl<elemType>::LR(Node<elemType>*& k3)
{
	RR(k3->left);
	LL(k3);
}

/* ===== Function 09 : RL ===== */
template<typename elemType>
void Avl<elemType>::RL(Node<elemType>*& k3)
{
	LL(k3->right);
	RR(k3);
}

/* ===== Function 11 : ƽ�� ===== */
template<typename elemType>
void Avl<elemType>::Balance(Node<elemType>*& node)
{
	if (!node)	return;

	// ���
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
	// �Ҹ�
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

	// ���¸߶�
	node->height = std::max(Height(node->left), Height(node->right)) + 1;
}
