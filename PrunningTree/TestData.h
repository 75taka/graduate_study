#pragma once

//�e�X�g�f�[�^�N���X�i�e�X�g�f�[�^�S�̂�\��)
#include "TrainingData.h"

#define TESTDATA_MIN 10 //�e�X�g�f�[�^���̉���

class TestData
{
public:
	static TrainingData* data; //�P���f�[�^������

	TestData();	//�R���X�g���N�^�@�����擾
	~TestData();	//�f�X�g���N�^

	void makeTestData();	//TestData�̏�������
	void ShowTestData();	//�e�X�g�f�[�^��\��

	int AttNum;				// ������
	int* attvalueNum;		// �����l��
	int ClassNum;		// �N���X���i���C�������ɑ΂��āu�͂��vor�u�������v�j
	int testDataNum_max;		// �e�X�g�f�[�^���̏��(=�P���f�[�^��)
	int** testData_max;			// �e�X�g�f�[�^
};

