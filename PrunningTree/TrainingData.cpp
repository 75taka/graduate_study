#include "TrainingData.h"

//訓練データクラスのソース
//if(!strcmp(trainDataStr[i][j], trainDataStr[k][j])) 第1引数と第2引数が一致したら実行

//コンストラクタ
//fname:データccファイル名

TrainingData::TrainingData(const char* dname)
{
	int i, j, k,columnN;
	char fname[256];
	char line[1024];
	FILE* dataS;
	char* pos;
	char* pos1;
	char*** trainDataStr;

	strcpy(dataname, dname); //ファイル名をdatanameへ

	//属性数とデータ数の取得 csvデータをdataディレクトリの配下に置く
	sprintf(fname, "data/%s.csv", dname);
	if ((dataS = fopen(fname, "r")) == 0) {
		printf("%sが開けません．\n", fname);
		exit(1);
	}
	
	//変数の初期化　属性数と訓練事例の数
	AttNum = -1; 
	trainDataNum = -1;

	//属性種類数(AttNum),属性種類数+クラス(columnN),データ数取得
	//fgets関数　lineにdataSから1行ずつ取得していく
	while (fgets(line, 1024, dataS)) {
		columnN = 1;
		pos1 = line - 1;
		do {
			pos = pos1 + 1;
			pos1 = strchr(pos, ',');
			if (pos1){
				columnN++;
			}
		} while (pos1);
		if (AttNum == -1){
			AttNum = columnN - 1;
		}
		else if(AttNum != columnN - 1){
			printf("%sの列数に不備があります．", fname);
			exit(1);
		}
		trainDataNum++;
	}
	fclose(dataS);

	// 領域確保
	trainDataStr = new char** [trainDataNum]; //データの数だけ領域確保
	trainData = new int* [trainDataNum]; //同上
	attname = new char* [AttNum]; //属性数だけ領域確保
	attvaluename = new char** [AttNum]; //同上
	attvalueNum = new int[AttNum]; //同上

	//データ読み込み準備
	if ((dataS = fopen(fname, "r")) == 0) {
		printf("%sが開けません．\n", fname);
		exit(1);
	}

	//データ読み込み 1行目の属性名
	fgets(line, 1024, dataS);
	pos1 = line;
	ClassNum = 0;
	for (j = 0; j < AttNum; j++) {
		attvalueNum[j] = 0;
		attname[j] = new char[64]; //属性名用に領域確保
		pos = strchr(pos1, ',');
		*pos = '\0';
		strcpy(attname[j], pos1); //確保した領域に属性名を入れる
		pos1 = pos + 1;
	}

	//2行目以降のデータについて
	for (i = 0; i < trainDataNum; i++) {
		fgets(line, 1024, dataS);
		trainDataStr[i] = new char* [AttNum + 1]; //i番目のデータに対して属性数+クラス分の領域確保
		trainData[i] = new int[AttNum + 1]; //i番目のデータに対して属性数+クラス分の領域確保
		pos1 = line;
		//1つのデータについて横に見ていく
		for (j = 0; j < AttNum; j++) {
			trainDataStr[i][j] = new char[64]; //i番目のデータのj番目の属性値名用の領域確保
			pos = strchr(pos1, ',');
			*pos = '\0';
			strcpy(trainDataStr[i][j], pos1);
			pos1 = pos + 1;
			for (k = 0; k < i; k++) {
				if (!strcmp(trainDataStr[i][j], trainDataStr[k][j])) {
					break;
				}
			}
			if (k == i) {
				attvalueNum[j]++;
			}
		}
		//以下クラス用
		trainDataStr[i][j] = new char[64];
		pos = strchr(pos1, '\n');
		*pos = '\0';
		strcpy(trainDataStr[i][j], pos1);
		for (k = 0; k < i; k++) {
			if (!strcmp(trainDataStr[i][j], trainDataStr[k][j])) {
				break;
			}
		}
		if (k == i) {
			ClassNum++;
		}
	}
	fclose(dataS);

	// 領域確保
	//上でattvalueNumを見たので，以下でその数だけ領域を確保してリストを作成する
	for (i = 0; i < AttNum; i++) {
		attvaluename[i] = new char* [attvalueNum[i]]; //i番目の属性の属性値数分の領域を確保する
		for (j = 0; j < attvalueNum[i]; j++)
			attvaluename[i][j] = new char[64]; //i番目の属性のj番目の属性値用の領域確保
		attvalueNum[i] = 0;
	}
	//以下クラスの話
	classname = new char* [ClassNum];
	for (i = 0; i < ClassNum; i++) {
		classname[i] = new char[64];
	}
	ClassNum = 0;

	//属性値名をクラス名に番号を当てていく
	for (i = 0; i < trainDataNum; i++) {
		for (j = 0; j < AttNum; j++) {
			for (k = 0; k < attvalueNum[j]; k++) {
				if (!strcmp(trainDataStr[i][j], attvaluename[j][k])) {
					break;
				}
			}
			if (k == attvalueNum[j]) {
				strcpy(attvaluename[j][attvalueNum[j]], trainDataStr[i][j]);
				attvalueNum[j]++;
			}
		}
		for (k = 0; k < ClassNum; k++) {
			if (!strcmp(trainDataStr[i][j], classname[k]))
				break;
		}
		if (k == ClassNum) {
			strcpy(classname[ClassNum], trainDataStr[i][j]);
			ClassNum++;
		}
	}

	// allData作成
	for (i = 0; i < trainDataNum; i++) {
		for (j = 0; j < AttNum; j++) {
			for (k = 0; k < attvalueNum[j]; k++) {
				if (!strcmp(trainDataStr[i][j], attvaluename[j][k])) {
					trainData[i][j] = k;
					break;
				}
			}
		}
		for (k = 0; k < ClassNum; k++) {
			if (!strcmp(trainDataStr[i][j], classname[k])) {
				trainData[i][j] = k;
				break;
			}
		}
	}
	//printf("読み込み完了");
}

TrainingData::~TrainingData()
{
}

void TrainingData::showTrainingData()
{
	int i, j;

	for (i = 0; i < trainDataNum; i++) {
		for (j = 0; j < AttNum; j++) {
			printf("%d ", trainData[i][j]);
		}
		printf("\n");
	}
}
