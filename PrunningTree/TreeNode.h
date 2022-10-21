#pragma once

// 一つのノードを指すクラス
#include "DataSubSet.h"

// 定数の宣言
#define LOG_SCORE 1.0		//対数計算時の計算ポイント
#define LOG_SCORE_EASY 0.5	//簡単な対数計算時の計算ポイント
#define CALC_SCORE_EASY 0.5		//四則演算の計算ポイント
#define REDUC_SCORE_EASY 0.5		//約分の計算ポイント

class TreeNode
{
public:
	static TrainingData* trdata;
	static int stdClassNo; //困ったときの判断に使う

	TreeNode(DataSubSet* subset, TreeNode* aParent);
	~TreeNode();
	int countNode();	//ノード数カウント
	void setLevel();	//ノードのレベルを設定する
	int maxLevel();		//木の深さを調べる
	int traverse(int* adata);	//木を探索する
	void evalInitA();			//評価用変数の初期化
	double countScore();		//計算スコアを調べる
	void Pruning();			//枝刈り用

	int childNum;
	int attribute;
	int classNo;
	int level;
	TreeNode* parent;
	TreeNode** child;
	int processNum;
	int correctNum;
	double calcpoint; //計算スコア
	int number_count[32][2];	//同類項による計算スコア測定用 1次元目：同類項の種類，2次元目：その数
	int term_count;				//同類項の数(↑の1次元目の要素数)

private:
	int selectAtt(DataSubSet* subset);			//情報利得比に基づいて属性を選択
	void evalInitA2();							//評価用変数の初期化
	bool jugde_reduction(int a, int b);			//約分判定
	bool judge_pow2(unsigned int x);			//2のべき乗を判定
	void judge_term(int term_num);				//number_countに同類項の数字を入れていく関数
	void score_measure();						//calcpointに加算していく関数
};