// PruningTree.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "Swarm.h"
#include "TrainingData.h"

/*
main関数内で行うこと
・複数のファイルをここで読み込んで，
それぞれのファイルに対してTreeオブジェクトを生成して，計算の回数を算出
・計算の回数に応じて，枝刈りの回数の指定をする（枝刈り時のなにかしらの関数の引数に使う）
・出力
*/

int main()
{
	int datanum, len, i, kind;
	char** dataFname;
	double* calcScore;
	struct _finddata_t c_file;
	long hFile;

	TrainingData** td = NULL;
	Tree** tree = NULL;

	//エラー処理？
	if ((hFile = _findfirst("data/*.csv", &c_file)) == -1L) {
		printf("ディレクトリdataにはデータが存在しません．\n");
		_findclose(hFile);
		exit(1);
	}

	else {
		for (datanum = 1; _findnext(hFile, &c_file) == 0; datanum++); //数を数える
		_findclose(hFile);

		//ファイル数分の領域確保
		calcScore = new double [datanum];
		td = new TrainingData* [datanum];
		tree = new Tree* [datanum];
		dataFname = new char* [datanum];

		hFile = _findfirst("data/*.csv", &c_file);
		//領域確保
		for (i = 0; i < datanum - 1 ; i++) {
			len = strlen(c_file.name);
			dataFname[i] = new char[len - 3]; //ファイル名格納(-4は.cppの分？)
			strncpy(dataFname[i], c_file.name, len - 4);
			dataFname[i][len - 4] = '\0';
			printf("%s\n", dataFname[i]);
			//決定木形成
			td[i] = new TrainingData(dataFname[i]); //データ読む
			DataSubSet::trdata = td[i]; //DataSubsetクラスのstatic変数trdataにtdを代入
			TreeNode::trdata = td[i]; //TreeNodeクラスのstatic変数trdataにtdを代入
			tree[i] = new Tree();
			printf("\n");
			calcScore[i] = tree[i]->ScoreReturn();
			_findnext(hFile, &c_file);
		}
		len = strlen(c_file.name);
		dataFname[i] = new char[len - 3]; //ファイル名格納(-4は.cppの分？)
		strncpy(dataFname[i], c_file.name, len - 4);
		dataFname[i][len - 4] = '\0';
		printf("%s\n", dataFname[i]);
		//決定木形成
		td[i] = new TrainingData(dataFname[i]); //データ読む
		DataSubSet::trdata = td[i]; //DataSubsetクラスのstatic変数trdataにtdを代入
		TreeNode::trdata = td[i]; //TreeNodeクラスのstatic変数trdataにtdを代入
		tree[i] = new Tree();
		printf("\n");
		calcScore[i] = tree[i]->ScoreReturn();
		_findclose(hFile);


		for (i = 0; i < datanum; i++)
			printf("データ番号%dの計算スコア:%lf\n", i, calcScore[i]);
	}


	/*
	const char* fname = "data003";

	//変数初期化
	TrainingData* td = NULL;
	Tree* tree = NULL; 
	//TreeNode::calcpoint = new double [8]; // これでdouble型のcalcpointが8つ用意された？

	td = new TrainingData(fname); //データ読む
	DataSubSet::trdata = td; //DataSubsetクラスのstatic変数trdataにtdを代入
	TreeNode::trdata = td; //TreeNodeクラスのstatic変数trdataにtdを代入
	tree = new Tree(); 

	*/
	//td->showTrainingData();


	/*
	やりたいこと
	・ファイルの数を数える
	・TrainingData* trdata[ファイル数];
	・Tree* tree[ファイル数分];
	・int calcnum[ファイル数分]; //計算回数

	for(ファイル数分)
	{
		trdata[i] = new ファイル読み込み;
		tree[i] = new tree(trdata[i]);
		calcnum[i] = tree[i]から計算回数を返す;
	}

	・calcnum[i]を整列
	・比較回数を割り当て
	・TestDataオブジェクトの作成・進化
		*/
	return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
