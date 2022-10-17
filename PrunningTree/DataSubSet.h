#pragma once

//該当訓練データクラス
/*
とあるノードにたどり着く訓練データを示す
*/

#include "TestData.h"

class DataSubSet
{
public:
	static TrainingData* trdata;

	DataSubSet(); //一番上の根ノードの際のコンストラクタ
	DataSubSet(DataSubSet* parentSet, int attn, int attv); //根ノード以外のコンストラクタ?
	~DataSubSet();
	void showdataDist();

	int** subdata;		// dataのtrainDataのレコードを指すポインタの配列
	int subdataNum;			// データ数
	int* attValue;			// 各属性の属性値（未定の場合は-1）
	int attNum;				// 未定ではない属性の数
	int maxNumClass;		// データが最も多いクラス
	int*** dataDist;		// 属性・属性値・クラスごとのデータ数を入れる配列，1次元目が属性，2次元目が属性値，3次元目がクラス，各末尾は合計値

};