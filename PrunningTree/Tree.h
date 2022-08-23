#pragma once

//決定木クラス
#include "TreeNode.h"

class Tree
{
public:
	static TrainingData* trdata;

	Tree(); //訓練データをもとに木を生成→計算回数を返す
	~Tree();

	void prunningtree();
	double get_evaluation(); //評価値計算
	int countnode(); //ノード数カウント

	TestData* Tedata; //テストデータオブジェクトのポインタ
	TreeNode* root;
	double evaluatevalue; //評価値
	double comparisonvalue; //比較回数　|n – m / n| n:枝刈り比較回数目標値　m:実際の枝刈り回数
	double cutvalue; //切らないのみ→1 両方ある場合→0
	double attusevalue; //全属性の使用　|全属性値 - 使用している属性値 / 全属性値|
	double Prunningvalue; //枝刈りの一意性　|比較回数 - 判断可能なパターン / 比較回数|
};

/*
・ノード数カウントはどっちに入れればいいのか
・*/