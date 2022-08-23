#pragma once

//��̃m�[�h���w���N���X
#include "DataSubSet.h"

class TreeNode
{
	static int stdClassNo;

	TreeNode(DataSubSet* subset, TreeNode* aParent);
	~TreeNode();
	int countNode();	//�m�[�h���J�E���g
	void setLevel();	//�m�[�h�̃��x����ݒ肷��
	int maxLevel();		//�؂̐[���𒲂ׂ�
	int traverse(int* adata);	//�؂�T������
	void evalInitA();			//�]���p�ϐ��̏�����
	void Prunning();			//�}����p

	int childNum;
	int attribute;
	int classNo;
	int level;
	TreeNode* parent;
	TreeNode** child;
	int processNum;
	int correctNum;

private:
	int selectAtt(DataSubSet* subset);	//��񗘓���ъ�Â��đ�����I��
	void evalInitA2();					//�]���p�ϐ��̏�����
};