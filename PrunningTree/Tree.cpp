#include "Tree.h"

//決定木クラスのソース
TrainingData* Tree::trdata = nullptr;

//コンストラクタ
Tree::Tree()
{
	DataSubSet* subset;
	subset = new DataSubSet();
	TreeNode::stdClassNo = subset->maxNumClass; //一番多いクラスの設定
	//根ノードから下の記述　終わったらsubsetの消去
	root = new TreeNode(subset, NULL); //親ノードなし→NULL
	countnode();
	setDepth();
	calcScore();
	printf("ノード数%d\n",nodeNum);
	printf("木の深さ%d\n", depth);
	printf("計算スコア%lf\n", TreeScore);
	delete subset;
}

Tree::~Tree()
{
	if (root)
		delete root;
	//printf("木を消せたよ");
}

void Tree::countnode()
{
	nodeNum = root->countNode();
}

void Tree::setDepth()
{
	depth = root->maxLevel();
}

void Tree::calcScore()
{
	TreeScore = root->countScore();
}

double Tree::ScoreReturn()
{
	return TreeScore;
}