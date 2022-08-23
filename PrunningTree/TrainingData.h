#pragma once

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
	TrainingData(char* dname); //コンストラクタ
	~TrainingData();
	void showTrainingData();		//トレーニングデータの表示

	char dataname[64];		// データの名前(おそらくファイル名)
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