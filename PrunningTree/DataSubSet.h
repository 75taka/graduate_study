#pragma once

//�Y���P���f�[�^�N���X
/*
�Ƃ���m�[�h�ɂ��ǂ蒅���P���f�[�^������
*/

#include "TestData.h"

class DataSubSet
{
public:
	static TrainingData* trdata;

	DataSubSet(); //��ԏ�̍��m�[�h�̍ۂ̃R���X�g���N�^
	DataSubSet(DataSubSet* parentSet, int attn, int attv); //���m�[�h�ȊO�̃R���X�g���N�^?
	~DataSubSet();
	void showdataDist();

	int** subdata;		// data��trainData�̃��R�[�h���w���|�C���^�̔z��
	int subdataNum;			// �f�[�^��
	int* attValue;			// �e�����̑����l�i����̏ꍇ��-1�j
	int attNum;				// ����ł͂Ȃ������̐�
	int maxNumClass;		// �f�[�^���ł������N���X
	int*** dataDist;		// �����E�����l�E�N���X���Ƃ̃f�[�^��������z��C1�����ڂ������C2�����ڂ������l�C3�����ڂ��N���X�C�e�����͍��v�l

};