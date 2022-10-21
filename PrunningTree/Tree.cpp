#include "Tree.h"

//����؃N���X�̃\�[�X
TrainingData* Tree::trdata = nullptr;

//�R���X�g���N�^
Tree::Tree()
{
	DataSubSet* subset;
	subset = new DataSubSet();
	TreeNode::stdClassNo = subset->maxNumClass; //��ԑ����N���X�̐ݒ�
	//���m�[�h���牺�̋L�q�@�I�������subset�̏���
	root = new TreeNode(subset, NULL); //�e�m�[�h�Ȃ���NULL
	countnode();
	setDepth();
	calcScore();
	printf("�m�[�h��%d\n",nodeNum);
	printf("�؂̐[��%d\n", depth);
	printf("�v�Z�X�R�A%lf\n", TreeScore);
	delete subset;
}

Tree::~Tree()
{
	if (root)
		delete root;
	//printf("�؂���������");
}

void Tree::countnode()
{
	nodeNum = root->countNode();
}

void Tree::setDepth()
{
	depth = root->maxLevel();
}

void Tree::calcScore()
{
	TreeScore = root->countScore();
}

double Tree::ScoreReturn()
{
	return TreeScore;
}