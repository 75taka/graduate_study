#include "DataSubSet.h"

//�Y���f�[�^�N���X�̃\�[�X

//static�g���Ƃ��͂���ŏ��������郋�[��
TrainingData* DataSubSet::trdata = nullptr;

//�R���X�g���N�^1�@���m�[�h�̃p�^�[���@
//�S�Ă̌P��������f�[�^�W���ɓ����
DataSubSet::DataSubSet()
{
	int i, j, k;

	subdataNum = trdata->trainDataNum; //�f�[�^��

	// �̈�m��
	subdata = new int* [trdata->trainDataNum]; //�f�[�^��
	attValue = new int[trdata->AttNum]; // �e�����̑����l
	dataDist = new int** [trdata->AttNum + 1]; //���ꂼ��̃f�[�^��

	//������ސ��J��Ԃ�
	for (i = 0; i < trdata->AttNum; i++) {
		dataDist[i] = new int* [trdata->attvalueNum[i] + 1]; //i�Ԗڂ̑����ɑ΂��đ����l�̐�+1�̔z��
		//�����l��ސ�+1�񕪌J��Ԃ�
		for (j = 0; j < trdata->attvalueNum[i] + 1; j++) {
			dataDist[i][j] = new int[trdata->ClassNum + 1];
			//�N���X��ސ�+1��J��Ԃ�
			for (k = 0; k < trdata->ClassNum + 1; k++)
				dataDist[i][j][k] = 0; //�������@���̐����������
		}
	}

	//�N���X�̂͂Ȃ�
	dataDist[i] = new int* [1];
	dataDist[i][0] = new int[trdata->ClassNum];
	for (k = 0; k < trdata->ClassNum; k++)
		dataDist[i][0][k] = 0;//�������@�������Ƃ���1

	// �e�z��̒l��ݒ�@���������
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

	// �Y������f�[�^���𐔂���
	subdataNum = 0;
	for (i = 0; i < parentSet->subdataNum; i++) {
		if (parentSet->subdata[i][attn] == attv)
			subdataNum++;
	}

	// �̈�m��
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

	// �e�z��̒l��ݒ�
	//attn �e�̑����@attv�@�����̑���
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
	//printf("subset��������");
}