#include "TrainingData.h"

//�P���f�[�^�N���X�̃\�[�X
//if(!strcmp(trainDataStr[i][j], trainDataStr[k][j])) ��1�����Ƒ�2��������v��������s

//�R���X�g���N�^
//fname:�f�[�^cc�t�@�C����

TrainingData::TrainingData(const char* dname)
{
	int i, j, k,columnN;
	char fname[256];
	char line[1024];
	FILE* dataS;
	char* pos;
	char* pos1;
	char*** trainDataStr;

	strcpy(dataname, dname); //�t�@�C������dataname��

	//�������ƃf�[�^���̎擾 csv�f�[�^��data�f�B���N�g���̔z���ɒu��
	sprintf(fname, "data/%s.csv", dname);
	if ((dataS = fopen(fname, "r")) == 0) {
		printf("%s���J���܂���D\n", fname);
		exit(1);
	}
	
	//�ϐ��̏������@�������ƌP������̐�
	AttNum = -1; 
	trainDataNum = -1;

	//������ސ�(AttNum),������ސ�+�N���X(columnN),�f�[�^���擾
	//fgets�֐��@line��dataS����1�s���擾���Ă���
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
			printf("%s�̗񐔂ɕs��������܂��D", fname);
			exit(1);
		}
		trainDataNum++;
	}
	fclose(dataS);

	// �̈�m��
	trainDataStr = new char** [trainDataNum]; //�f�[�^�̐������̈�m��
	trainData = new int* [trainDataNum]; //����
	attname = new char* [AttNum]; //�����������̈�m��
	attvaluename = new char** [AttNum]; //����
	attvalueNum = new int[AttNum]; //����

	//�f�[�^�ǂݍ��ݏ���
	if ((dataS = fopen(fname, "r")) == 0) {
		printf("%s���J���܂���D\n", fname);
		exit(1);
	}

	//�f�[�^�ǂݍ��� 1�s�ڂ̑�����
	fgets(line, 1024, dataS);
	pos1 = line;
	ClassNum = 0;
	for (j = 0; j < AttNum; j++) {
		attvalueNum[j] = 0;
		attname[j] = new char[64]; //�������p�ɗ̈�m��
		pos = strchr(pos1, ',');
		*pos = '\0';
		strcpy(attname[j], pos1); //�m�ۂ����̈�ɑ�����������
		pos1 = pos + 1;
	}

	//2�s�ڈȍ~�̃f�[�^�ɂ���
	for (i = 0; i < trainDataNum; i++) {
		fgets(line, 1024, dataS);
		trainDataStr[i] = new char* [AttNum + 1]; //i�Ԗڂ̃f�[�^�ɑ΂��đ�����+�N���X���̗̈�m��
		trainData[i] = new int[AttNum + 1]; //i�Ԗڂ̃f�[�^�ɑ΂��đ�����+�N���X���̗̈�m��
		pos1 = line;
		//1�̃f�[�^�ɂ��ĉ��Ɍ��Ă���
		for (j = 0; j < AttNum; j++) {
			trainDataStr[i][j] = new char[64]; //i�Ԗڂ̃f�[�^��j�Ԗڂ̑����l���p�̗̈�m��
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
		//�ȉ��N���X�p
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

	// �̈�m��
	//���attvalueNum�������̂ŁC�ȉ��ł��̐������̈���m�ۂ��ă��X�g���쐬����
	for (i = 0; i < AttNum; i++) {
		attvaluename[i] = new char* [attvalueNum[i]]; //i�Ԗڂ̑����̑����l�����̗̈���m�ۂ���
		for (j = 0; j < attvalueNum[i]; j++)
			attvaluename[i][j] = new char[64]; //i�Ԗڂ̑�����j�Ԗڂ̑����l�p�̗̈�m��
		attvalueNum[i] = 0;
	}
	//�ȉ��N���X�̘b
	classname = new char* [ClassNum];
	for (i = 0; i < ClassNum; i++) {
		classname[i] = new char[64];
	}
	ClassNum = 0;

	//�����l�����N���X���ɔԍ��𓖂ĂĂ���
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

	// allData�쐬
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
	//printf("�ǂݍ��݊���");
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
