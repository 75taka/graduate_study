#include "TreeNode.h"

//一つのノードを指すクラスのソース

//static宣言
TrainingData* TreeNode::trdata = nullptr;
int TreeNode::stdClassNo = -1;
//double* TreeNode::calcpoint = 0;

TreeNode::TreeNode(DataSubSet* subset, TreeNode* aParent)
{
	DataSubSet* subset2; //下にたどり着くデータ
	
	///////// 終端・非終端共通の値を設定 ////////////
	parent = aParent; //親ノード設定

	//木の深さ判定用
	if (parent){
		level = parent->level + 1;
	}
	else{
		level = 0;
	}
	evalInitA2(); //評価用変数初期化

	/////////// 終端・非終端を決定 attribute:属性 /////////////
		//ノードにたどり着くデータのクラスが全て同じ　||　属性集合の要素が0
	if ((subset->subdataNum == subset->dataDist[trdata->AttNum][0][subset->maxNumClass]) || (subset->attNum == 0)) {
		attribute = -1; //葉っぱの意味
		classNo = subset->maxNumClass; //終端用にクラスの設定
	}
	//そもそもデータがもうない時
	else if (subset->subdataNum == 0) {
		attribute = -1; //葉っぱの意味
		classNo = stdClassNo;
	}
	//↑以外
	else {
		attribute = selectAtt(subset); //分岐に適切な属性選択
		//適切な属性がもしなければ
		if (attribute == -1)
			classNo = subset->maxNumClass;
	}

	///////////// 終端・非終端に応じた値を設定 ///////////////
	//終端ノードの場合　子ノードの数を0にする(クラス決定→childNum = 0)
	if (attribute == -1) {
		childNum = 0;
		child = NULL;
	}

	//非終端ノードの場合　改めて木の作成で再帰処理
	else {
		childNum = trdata->attvalueNum[attribute]; //子ノード数＝属性値数
		child = new TreeNode * [childNum]; //子ノード分のTreeNodeオブジェクト作成
		for (int i = 0; i < childNum; i++) {
			subset2 = new DataSubSet(subset, attribute, i);
			child[i] = new TreeNode(subset2, this);
			delete subset2;
		}
	}
}

TreeNode::~TreeNode()
{
	if (child) {
		for (int i = 0; i < childNum; i++)
			delete child[i];
		delete[] child;
	}
}

// 情報利得比に基づいて属性を選択
// subset : 訓練例
int TreeNode::selectAtt(DataSubSet* subset)
{
	double e1, e2, gain, sinfo, gainR, maxGainR;
	int i, j, k, att;
	int a, b;
	
	//値初期化 att:返す属性番号 maxGainR:
	att = -1;
	maxGainR = 0.0;
	calcpoint = 0.0;
	
	// 事例集合subsetのクラスに関するエントロピーE1
	e1 = 0.0;
	
	// e1を求めるとき：約分無．同類項有，掛け算有，最後の足し算
	// e2を求めるとき：約分有，同類項有，掛け算有，最後の足し算

	// e1を求めるフェイズ & 計算量を求めるフェイズ

	for (i = 0; i < trdata->ClassNum; i++) {
		if (subset->dataDist[trdata->AttNum][0][i]) {
			e1 -= ((double)subset->dataDist[trdata->AttNum][0][i] / (double)subset->subdataNum)
				* log2((double)subset->dataDist[trdata->AttNum][0][i] / (double)subset->subdataNum);
			//同類項を纏める
			judge_term(subset->dataDist[trdata->AttNum][0][i]); 
			judge_term(subset->subdataNum);
			//約分判定
			if (jugde_reduction(subset->dataDist[trdata->AttNum][0][i], subset->subdataNum) == true)
				calcpoint += REDUC_SCORE_EASY;
		}
	}

	printf("e1:%lf\n", e1);

	score_measure();
	//printf("e1:%lf\n", calcpoint);

	// e2を求めるフェイズ
	for (i = 0; i < trdata->AttNum; i++) {
		if (subset->attValue[i] == -1) {
			e2 = 0.0;
			for (j = 0; j < trdata->attvalueNum[i]; j++) {
				for (k = 0; k < trdata->ClassNum; k++) {
					if (!(subset->dataDist[i][j][k] == 0 || subset->dataDist[i][j][k] == subset->dataDist[i][j][trdata->ClassNum])) {
						e2 -= ((double)subset->dataDist[i][j][trdata->ClassNum] / (double)subset->subdataNum)
							* ((double)subset->dataDist[i][j][k] / (double)subset->dataDist[i][j][trdata->ClassNum])
							* log2((double)subset->dataDist[i][j][k] / (double)subset->dataDist[i][j][trdata->ClassNum]);
						//同類項を纏める
						judge_term(subset->dataDist[i][j][k]);
						judge_term(subset->dataDist[i][j][trdata->ClassNum]);
						//約分判定(e2の時は必ず約分発生)
						calcpoint += REDUC_SCORE_EASY;
					}
				}
			}

			score_measure();
			printf("e2:%lf\n", e2);

			// 情報利得
			gain = e1 - e2;
			printf("gain:%lf\n", gain);
			calcpoint += CALC_SCORE_EASY;

			// sinfo:分割情報量，gainR:情報利得比
			// 残りの属性がもうなければ繰り返さないを入れたい　if (gain > 0 &&  まだ分けられる属性が残っている時)みたいな
			if (gain > 0) {
				sinfo = 0.0;
				for (j = 0; j < trdata->attvalueNum[i]; j++) {
					if (subset->dataDist[i][j][trdata->ClassNum] != 0) {
						sinfo -= ((double)subset->dataDist[i][j][trdata->ClassNum] / (double)subset->subdataNum)
							* log2((double)subset->dataDist[i][j][trdata->ClassNum] / (double)subset->subdataNum);
						//同類項を纏める
						judge_term(subset->dataDist[i][j][trdata->ClassNum]);
						judge_term(subset->subdataNum);
						//約分判定
						if (jugde_reduction(subset->dataDist[i][j][trdata->ClassNum], subset->subdataNum) == true)
							calcpoint += REDUC_SCORE_EASY;
					}
				}

				printf("sinfo:%lf\n", sinfo);

				score_measure();
				//printf("sinfo:%lf\n", calcpoint);

				// 情報利得比
				gainR = gain / sinfo;
				calcpoint += CALC_SCORE_EASY;
				printf("gainR:%lf\n", gainR);

				// 戻り値とする属性(gainRが大きい属性iを戻り値とする)
				if (gainR > maxGainR) {
					maxGainR = gainR;
					att = i;
				}
			}
		}

		//printf("属性別スコア:%lf\n", calcpoint);
	}

	//score_measure();
	//printf("ノード別スコア:%lf\n", calcpoint);
	printf("-------------------------\n");
	return att;
}

// 木のノード数を数える
int TreeNode::countNode()
{
	int ret = 1;
	if (child) {
		for (int i = 0; i < childNum; i++)
			ret += child[i]->countNode();
	}
	return ret;
}

// ノードのレベルを設定する
void TreeNode::setLevel()
{
	if (parent)
		level = parent->level + 1;
	else
		level = 0;
	if (child) {
		for (int i = 0; i < childNum; i++)
			child[i]->setLevel();
	}
}

// 木の深さを調べる
int TreeNode::maxLevel()
{
	int max, x, i;

	if (child) {
		for (i = 0, max = -1; i < childNum; i++) {
			x = child[i]->maxLevel();
			if (max < x)
				max = x;
		}
		return max;
	}
	else {
		return level;
	}
}

// 木を探索
// data : データ
// return : 正解なら1，不正解なら0
int traverse(int* adata) {
	return 0;
}

void evalInitA() {

}

// 計算スコア合算
double TreeNode::countScore() {
	double score = calcpoint;
	if (child) {
		for (int i = 0; i < childNum; i++) {
			score += child[i]->countScore();
		}
	}
	return score;
}


void Pruning()
{

}

// 評価用変数の初期化
void TreeNode::evalInitA2()
{
	calcpoint = 0.0;
	term_count = 0;
}

// 約分判定
bool TreeNode::jugde_reduction(int a, int b) 
{
	while (a != b) {
		if (a < b) b -= a;
		else a -= b;
	}
	if (a != 1)
		return true;
	else
		return false;
}

// 2のべき乗判定
bool TreeNode::judge_pow2(unsigned int x)
{
	if (x == 0) {
		return false;
	}

	return (x & (x - 1)) == 0;
}

// 同類項を纏める関数
void TreeNode::judge_term(int term_num) {
	int i;
	if (term_num != 1) {
		for (i = 0; i < term_count; i++) {
			if (number_count[i][0] == term_num)
				break;
		}

		if (i == term_count) {
			number_count[i][0] = term_num;
			number_count[i][1] = 1;
			term_count++;
		}
		else {
			number_count[i][1]++;
		}
	}
}

//計算スコア測定
void TreeNode::score_measure()
{
	int i,j;
	int plusnum = 0;

	//同類項の計算スコア
	for (i = 0; i < term_count; i++) {
		for (j = 0; j < number_count[i][1] - 1; j++) {
			calcpoint += CALC_SCORE_EASY;
		}
	}

	//対数計算スコア
	for (i = 0; i < term_count; i++) {
		if (judge_pow2(number_count[i][0]) == true && number_count[i][1] != 0) {
			calcpoint += LOG_SCORE_EASY;
		}
		else if(judge_pow2(number_count[i][0]) == false && number_count[i][1] != 0){
			calcpoint += LOG_SCORE;
		}
	}

	//最後の足し算
	for (i = 0; i < term_count; i++) {
		if (number_count[i][1] != 0)
			plusnum++;
	}
	for (i = 0; i < plusnum - 1; i++) {
		calcpoint += CALC_SCORE_EASY;
	}

	//リセット
	for (i = 0; i < term_count; i++) {
		number_count[i][1] = 0;
	}
}