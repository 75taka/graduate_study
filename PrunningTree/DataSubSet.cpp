#include "DataSubSet.h"

//該当データクラスのソース

//static使うときはこれで初期化するルール
TrainingData* DataSubSet::trdata = nullptr;

//コンストラクタ1　根ノードのパターン　
//全ての訓練事例をデータ集合に入れる
DataSubSet::DataSubSet()
{
	int i, j, k;

	subdataNum = trdata->trainDataNum; //データ数

	// 領域確保
	subdata = new int* [trdata->trainDataNum]; //データ数
	attValue = new int[trdata->AttNum]; // 各属性の属性値
	dataDist = new int** [trdata->AttNum + 1]; //それぞれのデータ数

	//属性種類数繰り返す
	for (i = 0; i < trdata->AttNum; i++) {
		dataDist[i] = new int* [trdata->attvalueNum[i] + 1]; //i番目の属性に対して属性値の数+1個の配列
		//属性値種類数+1回分繰り返す
		for (j = 0; j < trdata->attvalueNum[i] + 1; j++) {
			dataDist[i][j] = new int[trdata->ClassNum + 1];
			//クラス種類数+1回繰り返す
			for (k = 0; k < trdata->ClassNum + 1; k++)
				dataDist[i][j][k] = 0; //初期化　その数だけ入れる
		}
	}

	//クラスのはなし
	dataDist[i] = new int* [1];
	dataDist[i][0] = new int[trdata->ClassNum];
	for (k = 0; k < trdata->ClassNum; k++)
		dataDist[i][0][k] = 0;//初期化　あったときに1

	// 各配列の値を設定　ここも難しい
	for (i = 0; i < trdata->trainDataNum; i++) {
		subdata[i] = trdata->trainData[i];
		for (j = 0; j < trdata->AttNum; j++) {
			dataDist[j][subdata[i][j]][subdata[i][trdata->AttNum]]++;
			dataDist[j][subdata[i][j]][trdata->ClassNum]++;
			dataDist[j][trdata->attvalueNum[j]][subdata[i][trdata->AttNum]]++;
		}
		dataDist[trdata->AttNum][0][subdata[i][trdata->AttNum]]++;
	}
	for (i = 0; i < trdata->AttNum; i++)
		attValue[i] = -1;
	attNum = trdata->AttNum;
	maxNumClass = 0;
	for (i = 1; i < trdata->ClassNum; i++) {
		if (dataDist[trdata->AttNum][0][maxNumClass] < dataDist[trdata->AttNum][0][i])
			maxNumClass = i;
	}

	/*showdataDist
	for (i = 0; i < 3; i++) {
		for (j = 0; j < trdata->attvalueNum[i] + 1; j++) {
			for (k = 0; k < 3; k++) {
				printf("%d\n",dataDist[i][j][k]);
			}
		}
	}
	printf("%d\n", dataDist[3][0][0]);
	printf("%d\n", dataDist[3][0][1]);
	*/
}

DataSubSet::DataSubSet(DataSubSet* parentSet, int attn, int attv)
{
	int i, j, k;

	// 該当するデータ数を数える
	subdataNum = 0;
	for (i = 0; i < parentSet->subdataNum; i++) {
		if (parentSet->subdata[i][attn] == attv)
			subdataNum++;
	}

	// 領域確保
	subdata = new int* [subdataNum];
	attValue = new int[trdata->AttNum];
	dataDist = new int** [trdata->AttNum + 1];
	for (i = 0; i < trdata->AttNum; i++) {
		dataDist[i] = new int* [trdata->attvalueNum[i] + 1];
		for (j = 0; j < trdata->attvalueNum[i] + 1; j++) {
			dataDist[i][j] = new int[trdata->ClassNum + 1];
			for (k = 0; k < trdata->ClassNum + 1; k++)
				dataDist[i][j][k] = 0;
		}
	}
	dataDist[i] = new int* [1];
	dataDist[i][0] = new int[trdata->ClassNum];
	for (k = 0; k < trdata->ClassNum; k++)
		dataDist[i][0][k] = 0;

	// 各配列の値を設定
	//attn 親の属性　attv　自分の属性
	for (i = 0, k = 0; i < parentSet->subdataNum; i++) {
		if (parentSet->subdata[i][attn] == attv) {
			subdata[k] = parentSet->subdata[i];
			for (j = 0; j < trdata->AttNum; j++) {
				dataDist[j][subdata[k][j]][subdata[k][trdata->AttNum]]++;
				dataDist[j][subdata[k][j]][trdata->ClassNum]++;
				dataDist[j][trdata->attvalueNum[j]][subdata[k][trdata->AttNum]]++;
			}
			dataDist[trdata->AttNum][0][subdata[k][trdata->AttNum]]++;
			k++;
		}
	}
	for (i = 0; i < trdata->AttNum; i++)
		attValue[i] = parentSet->attValue[i];
	attValue[attn] = attv;
	attNum = parentSet->attNum - 1;
	maxNumClass = 0;
	for (i = 1; i < trdata->ClassNum; i++) {
		if (dataDist[trdata->AttNum][0][maxNumClass] < dataDist[trdata->AttNum][0][i])
			maxNumClass = i;
	}
}

void showdatadist()
{
}

DataSubSet::~DataSubSet()
{
	delete[] subdata;
	delete[] attValue;
	for (int i = 0; i < trdata->AttNum; i++) {
		for (int j = 0; j < trdata->attvalueNum[i] + 1; j++)
			delete[] dataDist[i][j];
		delete[] dataDist[i];
	}
	delete[] dataDist[trdata->AttNum][0];
	delete[] dataDist[trdata->AttNum];
	delete[] dataDist;
	//printf("subset消せたよ");
}