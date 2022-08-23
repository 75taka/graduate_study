#pragma once

//テストデータクラス（テストデータ全体を表す)
#include "TrainingData.h"

class TestData
{
public:
	static TrainingData* data; //訓練データを示す

	TestData();	//コンストラクタ　テストデータを自動生成する
	~TestData();	//デストラクタ
	void ShowTestData();	//テストデータを表示

	int AttNum;				// 属性数
	int* attvalueNum;		// 属性値数
	int ClassNum;		// クラス数（ワイン買うに対して「はい」or「いいえ」）

	int testDataNum;		// テストデータ数
	int** testData;			// テストデータ
};

/*
・testDataで並び変える必要性あるのかどうか→無
*/