#pragma once
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//�P���f�[�^�N���X

/*
�P���f�[�^�S�̂�\��
����V�X�e������o�͂����t�@�C����ǂݍ���ŁC
�g�����U�N�V������ԍ��ɂ������X�g���쐬����@
�쐬�������X�g�́C�e�X�g�f�[�^�̐����ɗp����
*/

class TrainingData
{
public:
	TrainingData(const char* dname); //�R���X�g���N�^
	~TrainingData();
	void showTrainingData();		//�g���[�j���O�f�[�^�̕\��

	char dataname[64];		// �f�[�^�̖��O(�����炭�t�@�C����)

	//�ȉ���3�����X�g�ƂȂ肻��
	//attname[0]���u�N��v�Ƃ��uattvaluename[0][0]���u20��v�Ƃ��͂ł���ۂ�
	char** attname;			// ������
	char*** attvaluename;	// �����l��
	char** classname;		// �N���X��

	int AttNum;				// ������
	int* attvalueNum;		// �����l��
	int ClassNum;			// �N���X���i���C�������ɑ΂��āu�͂��vor�u�������v�j
	int trainDataNum;		// �P���f�[�^��
	int** trainData;		// �P���f�[�^
};

/*
�^��_
�E�i�S�̓I�ɂ����邱�Ƃ����jpublic��private�̎g���������ق��Ŏg�����ǂ����H
*/