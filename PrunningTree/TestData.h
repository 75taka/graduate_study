#pragma once

//�e�X�g�f�[�^�N���X�i�e�X�g�f�[�^�S�̂�\��)
#include "TrainingData.h"

class TestData
{
public:
	static TrainingData* data; //�P���f�[�^������

	TestData();	//�R���X�g���N�^�@�e�X�g�f�[�^��������������
	~TestData();	//�f�X�g���N�^
	void ShowTestData();	//�e�X�g�f�[�^��\��

	int AttNum;				// ������
	int* attvalueNum;		// �����l��
	int ClassNum;		// �N���X���i���C�������ɑ΂��āu�͂��vor�u�������v�j

	int testDataNum;		// �e�X�g�f�[�^��
	int** testData;			// �e�X�g�f�[�^
};

/*
�EtestData�ŕ��ѕς���K�v������̂��ǂ�������
*/