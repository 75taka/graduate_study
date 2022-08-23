#pragma once

//一つのノードを指すクラス
#include "DataSubSet.h"

class TreeNode
{
	static int stdClassNo;

	TreeNode(DataSubSet* subset, TreeNode* aParent);
	~TreeNode();
	int countNode();	//ノード数カウント
	void setLevel();	//ノードのレベルを設定する
	int maxLevel();		//木の深さを調べる
	int traverse(int* adata);	//木を探索する
	void evalInitA();			//評価用変数の初期化
	void Prunning();			//枝刈り用

	int childNum;
	int attribute;
	int classNo;
	int level;
	TreeNode* parent;
	TreeNode** child;
	int processNum;
	int correctNum;

private:
	int selectAtt(DataSubSet* subset);	//情報利得比び基づいて属性を選択
	void evalInitA2();					//評価用変数の初期化
};