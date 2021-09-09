#pragma once
#include <iostream>

template<typename elemType>
class Avl
{
private:
	/* ===== Member 00 : 二叉树节点 ===== */
	template<typename elemType>
	class Node
	{
	public:
		elemType element;
		Node* left;
		Node* right;

		int height;

		// 构造函数
		Node(const elemType& p_ele, Node* p_lt, Node* p_rt, int p_h = 0)
			: element(p_ele), left(p_lt), right(p_rt), height(p_h) { }

		Node(elemType&& p_ele, Node* p_lt, Node* p_rt, int p_h = 0)
			: element(p_ele), left(p_lt), right(p_rt), height(p_h) { }
	};

	/* ===== Member 01 : 根节点 ===== */
	Node<elemType>* root;

	/* ===== Function 01 : 查找最小值 ===== */
	Node<elemType>* FindMin(Node<elemType>* node);

	/* ===== Function 02 : 查找最大值 ===== */
	Node<elemType>* FindMax(Node<elemType>* node);

	/* ===== Function 03 : 按值查找 ===== */
	Node<elemType>* FindVal(const elemType& ele, Node<elemType>* node);

	/* ===== Function 04 : 插入（线索二叉树，按准则排序，此处用<） ===== */
	void Insert(const elemType& ele, Node<elemType>*& node);

	/* ===== Function 05 : 按元素删除 ===== */
	void Remove_val(const elemType& ele, Node<elemType>*& node);

	/* ===== Function 06 : 高度计算 ===== */
	int Height(Node<elemType>* node);

	/*
		单旋
		Single Left Rotate
		Single Right Rotate
	*/

	/* ===== Function 07 : LL ===== */
	void LL(Node<elemType>*& k2);
	
	/* ===== Function 08 : RR ===== */
	void RR(Node<elemType>*& k2);

	/*
		双旋
		Double Left Rotate
		Double Right Rotate
	*/

	/* ===== Function 09 : LR ===== */
	void LR(Node<elemType>*& k3);

	/* ===== Function 10 : RL ===== */
	void RL(Node<elemType>*& k3);

	/* ===== Function 11 : 平衡 ===== */
	void Balance(Node<elemType>*& node);
public:
	/* ===== Function 00 : Constructor ===== */
	Avl();

	/* ===== Function 03 : 按值查找 ===== */
	Node<elemType>* FindVal(const elemType& ele);

	/* ===== Function 04 : 插入（线索二叉树，按准则排序，此处用<） ===== */
	void Insert(const elemType& ele);

	/* ===== Function 05 : 按元素删除 ===== */
	void Remove_val(const elemType& ele);

};

