#pragma once

//決定木クラス
#include "TreeNode.h"

class Tree
{
public:
	static TrainingData* trdata;

	Tree(); //訓練データをもとに木を生成→計算回数を返す
	~Tree();

	void countnode(); //ノード数カウント
	void setDepth(); //深さカウント
	void calcScore(); //計算スコアカウント

	//未
	double get_evaluation(); //評価値計算
	void pruningtree();

	//TrainingData* Trdata;	//トレーニングデータのポインタ
	TestData* Tedata; //テストデータオブジェクトのポインタ
	TreeNode* root;

	int nodeNum;		// ノード数
	int depth;			// 木の深さ
	double TreeScore;	//枝刈り時の計算スコア

	//未
	double comparisonvalue; //比較回数の評価値　|n – m / n| n:枝刈り比較回数目標値　m:実際の枝刈り回数
	int cutvalue; //切らないのみ→1 両方ある場合→0
	double attusevalue; //全属性値の使用　|全属性値 - 使用している属性値 / 全属性値|
	double pruningvalue; //枝刈りの一意性　|比較回数 - 判断可能なパターン / 比較回数|
	double evaluatevalue; //評価値
};
