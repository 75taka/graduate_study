#pragma once

//テストデータクラス（テストデータ全体を表す)
#include "TrainingData.h"

#define TESTDATA_MIN 10 //テストデータ数の下限

class TestData
{
public:
	static TrainingData* data; //訓練データを示す

	TestData();	//コンストラクタ　数を取得
	~TestData();	//デストラクタ

	void makeTestData();	//TestDataの初期生成
	void ShowTestData();	//テストデータを表示

	int AttNum;				// 属性数
	int* attvalueNum;		// 属性値数
	int ClassNum;		// クラス数（ワイン買うに対して「はい」or「いいえ」）
	int testDataNum_max;		// テストデータ数の上限(=訓練データ数)
	int** testData_max;			// テストデータ
};

