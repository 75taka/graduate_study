#pragma once
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//訓練データクラス

/*
訓練データ全体を表す
今野システムから出力されるファイルを読み込んで，
トランザクションを番号にしたリストを作成する　
作成したリストは，テストデータの生成に用いる
*/

class TrainingData
{
public:
	TrainingData(const char* dname); //コンストラクタ
	~TrainingData();
	void showTrainingData();		//トレーニングデータの表示

	char dataname[64];		// データの名前(おそらくファイル名)

	//以下の3つがリストとなりそう
	//attname[0]→「年齢」とか「attvaluename[0][0]→「20代」とかはでるっぽい
	char** attname;			// 属性名
	char*** attvaluename;	// 属性値名
	char** classname;		// クラス名

	int AttNum;				// 属性数
	int* attvalueNum;		// 属性値数
	int ClassNum;			// クラス数（ワイン買うに対して「はい」or「いいえ」）
	int trainDataNum;		// 訓練データ数
	int** trainData;		// 訓練データ
};

/*
疑問点
・（全体的にいえることだが）publicとprivateの使い分け→ほかで使うかどうか？
*/