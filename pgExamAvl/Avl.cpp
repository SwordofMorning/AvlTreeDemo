#include "Avl.h"

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
}
