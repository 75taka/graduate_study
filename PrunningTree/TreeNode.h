#pragma once

// ��̃m�[�h���w���N���X
#include "DataSubSet.h"

// �萔�̐錾
#define LOG_SCORE 1.0		//�ΐ��v�Z���̌v�Z�|�C���g
#define LOG_SCORE_EASY 0.5	//�ȒP�ȑΐ��v�Z���̌v�Z�|�C���g
#define CALC_SCORE_EASY 0.5		//�l�����Z�̌v�Z�|�C���g
#define REDUC_SCORE_EASY 0.5		//�񕪂̌v�Z�|�C���g

class TreeNode
{
public:
	static TrainingData* trdata;
	static int stdClassNo; //�������Ƃ��̔��f�Ɏg��

	TreeNode(DataSubSet* subset, TreeNode* aParent);
	~TreeNode();
	int countNode();	//�m�[�h���J�E���g
	void setLevel();	//�m�[�h�̃��x����ݒ肷��
	int maxLevel();		//�؂̐[���𒲂ׂ�
	int traverse(int* adata);	//�؂�T������
	void evalInitA();			//�]���p�ϐ��̏�����
	double countScore();		//�v�Z�X�R�A�𒲂ׂ�
	void Pruning();			//�}����p

	int childNum;
	int attribute;
	int classNo;
	int level;
	TreeNode* parent;
	TreeNode** child;
	int processNum;
	int correctNum;
	double calcpoint; //�v�Z�X�R�A
	int number_count[32][2];	//���ލ��ɂ��v�Z�X�R�A����p 1�����ځF���ލ��̎�ށC2�����ځF���̐�
	int term_count;				//���ލ��̐�(����1�����ڂ̗v�f��)

private:
	int selectAtt(DataSubSet* subset);			//��񗘓���Ɋ�Â��đ�����I��
	void evalInitA2();							//�]���p�ϐ��̏�����
	bool jugde_reduction(int a, int b);			//�񕪔���
	bool judge_pow2(unsigned int x);			//2�ׂ̂���𔻒�
	void judge_term(int term_num);				//number_count�ɓ��ލ��̐��������Ă����֐�
	void score_measure();						//calcpoint�ɉ��Z���Ă����֐�
};