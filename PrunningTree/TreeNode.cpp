#include "TreeNode.h"

//��̃m�[�h���w���N���X�̃\�[�X

//static�錾
TrainingData* TreeNode::trdata = nullptr;
int TreeNode::stdClassNo = -1;
//double* TreeNode::calcpoint = 0;

TreeNode::TreeNode(DataSubSet* subset, TreeNode* aParent)
{
	DataSubSet* subset2; //���ɂ��ǂ蒅���f�[�^
	
	///////// �I�[�E��I�[���ʂ̒l��ݒ� ////////////
	parent = aParent; //�e�m�[�h�ݒ�

	//�؂̐[������p
	if (parent){
		level = parent->level + 1;
	}
	else{
		level = 0;
	}
	evalInitA2(); //�]���p�ϐ�������

	/////////// �I�[�E��I�[������ attribute:���� /////////////
		//�m�[�h�ɂ��ǂ蒅���f�[�^�̃N���X���S�ē����@||�@�����W���̗v�f��0
	if ((subset->subdataNum == subset->dataDist[trdata->AttNum][0][subset->maxNumClass]) || (subset->attNum == 0)) {
		attribute = -1; //�t���ς̈Ӗ�
		classNo = subset->maxNumClass; //�I�[�p�ɃN���X�̐ݒ�
	}
	//���������f�[�^�������Ȃ���
	else if (subset->subdataNum == 0) {
		attribute = -1; //�t���ς̈Ӗ�
		classNo = stdClassNo;
	}
	//���ȊO
	else {
		attribute = selectAtt(subset); //����ɓK�؂ȑ����I��
		//�K�؂ȑ����������Ȃ����
		if (attribute == -1)
			classNo = subset->maxNumClass;
	}

	///////////// �I�[�E��I�[�ɉ������l��ݒ� ///////////////
	//�I�[�m�[�h�̏ꍇ�@�q�m�[�h�̐���0�ɂ���(�N���X���聨childNum = 0)
	if (attribute == -1) {
		childNum = 0;
		child = NULL;
	}

	//��I�[�m�[�h�̏ꍇ�@���߂Ė؂̍쐬�ōċA����
	else {
		childNum = trdata->attvalueNum[attribute]; //�q�m�[�h���������l��
		child = new TreeNode * [childNum]; //�q�m�[�h����TreeNode�I�u�W�F�N�g�쐬
		for (int i = 0; i < childNum; i++) {
			subset2 = new DataSubSet(subset, attribute, i);
			child[i] = new TreeNode(subset2, this);
			delete subset2;
		}
	}
}

TreeNode::~TreeNode()
{
	if (child) {
		for (int i = 0; i < childNum; i++)
			delete child[i];
		delete[] child;
	}
}

// ��񗘓���Ɋ�Â��đ�����I��
// subset : �P����
int TreeNode::selectAtt(DataSubSet* subset)
{
	double e1, e2, gain, sinfo, gainR, maxGainR;
	int i, j, k, att;
	int a, b;
	
	//�l������ att:�Ԃ������ԍ� maxGainR:
	att = -1;
	maxGainR = 0.0;
	calcpoint = 0.0;
	
	// ����W��subset�̃N���X�Ɋւ���G���g���s�[E1
	e1 = 0.0;
	
	// e1�����߂�Ƃ��F�񕪖��D���ލ��L�C�|���Z�L�C�Ō�̑����Z
	// e2�����߂�Ƃ��F�񕪗L�C���ލ��L�C�|���Z�L�C�Ō�̑����Z

	// e1�����߂�t�F�C�Y & �v�Z�ʂ����߂�t�F�C�Y

	for (i = 0; i < trdata->ClassNum; i++) {
		if (subset->dataDist[trdata->AttNum][0][i]) {
			e1 -= ((double)subset->dataDist[trdata->AttNum][0][i] / (double)subset->subdataNum)
				* log2((double)subset->dataDist[trdata->AttNum][0][i] / (double)subset->subdataNum);
			//���ލ���Z�߂�
			judge_term(subset->dataDist[trdata->AttNum][0][i]); 
			judge_term(subset->subdataNum);
			//�񕪔���
			if (jugde_reduction(subset->dataDist[trdata->AttNum][0][i], subset->subdataNum) == true)
				calcpoint += REDUC_SCORE_EASY;
		}
	}

	printf("e1:%lf\n", e1);

	score_measure();
	//printf("e1:%lf\n", calcpoint);

	// e2�����߂�t�F�C�Y
	for (i = 0; i < trdata->AttNum; i++) {
		if (subset->attValue[i] == -1) {
			e2 = 0.0;
			for (j = 0; j < trdata->attvalueNum[i]; j++) {
				for (k = 0; k < trdata->ClassNum; k++) {
					if (!(subset->dataDist[i][j][k] == 0 || subset->dataDist[i][j][k] == subset->dataDist[i][j][trdata->ClassNum])) {
						e2 -= ((double)subset->dataDist[i][j][trdata->ClassNum] / (double)subset->subdataNum)
							* ((double)subset->dataDist[i][j][k] / (double)subset->dataDist[i][j][trdata->ClassNum])
							* log2((double)subset->dataDist[i][j][k] / (double)subset->dataDist[i][j][trdata->ClassNum]);
						//���ލ���Z�߂�
						judge_term(subset->dataDist[i][j][k]);
						judge_term(subset->dataDist[i][j][trdata->ClassNum]);
						//�񕪔���(e2�̎��͕K���񕪔���)
						calcpoint += REDUC_SCORE_EASY;
					}
				}
			}

			score_measure();
			printf("e2:%lf\n", e2);

			// ��񗘓�
			gain = e1 - e2;
			printf("gain:%lf\n", gain);
			calcpoint += CALC_SCORE_EASY;

			// sinfo:�������ʁCgainR:��񗘓���
			// �c��̑����������Ȃ���ΌJ��Ԃ��Ȃ�����ꂽ���@if (gain > 0 &&  �܂��������鑮�����c���Ă��鎞)�݂�����
			if (gain > 0) {
				sinfo = 0.0;
				for (j = 0; j < trdata->attvalueNum[i]; j++) {
					if (subset->dataDist[i][j][trdata->ClassNum] != 0) {
						sinfo -= ((double)subset->dataDist[i][j][trdata->ClassNum] / (double)subset->subdataNum)
							* log2((double)subset->dataDist[i][j][trdata->ClassNum] / (double)subset->subdataNum);
						//���ލ���Z�߂�
						judge_term(subset->dataDist[i][j][trdata->ClassNum]);
						judge_term(subset->subdataNum);
						//�񕪔���
						if (jugde_reduction(subset->dataDist[i][j][trdata->ClassNum], subset->subdataNum) == true)
							calcpoint += REDUC_SCORE_EASY;
					}
				}

				printf("sinfo:%lf\n", sinfo);

				score_measure();
				//printf("sinfo:%lf\n", calcpoint);

				// ��񗘓���
				gainR = gain / sinfo;
				calcpoint += CALC_SCORE_EASY;
				printf("gainR:%lf\n", gainR);

				// �߂�l�Ƃ��鑮��(gainR���傫������i��߂�l�Ƃ���)
				if (gainR > maxGainR) {
					maxGainR = gainR;
					att = i;
				}
			}
		}

		//printf("�����ʃX�R�A:%lf\n", calcpoint);
	}

	//score_measure();
	//printf("�m�[�h�ʃX�R�A:%lf\n", calcpoint);
	printf("-------------------------\n");
	return att;
}

// �؂̃m�[�h���𐔂���
int TreeNode::countNode()
{
	int ret = 1;
	if (child) {
		for (int i = 0; i < childNum; i++)
			ret += child[i]->countNode();
	}
	return ret;
}

// �m�[�h�̃��x����ݒ肷��
void TreeNode::setLevel()
{
	if (parent)
		level = parent->level + 1;
	else
		level = 0;
	if (child) {
		for (int i = 0; i < childNum; i++)
			child[i]->setLevel();
	}
}

// �؂̐[���𒲂ׂ�
int TreeNode::maxLevel()
{
	int max, x, i;

	if (child) {
		for (i = 0, max = -1; i < childNum; i++) {
			x = child[i]->maxLevel();
			if (max < x)
				max = x;
		}
		return max;
	}
	else {
		return level;
	}
}

// �؂�T��
// data : �f�[�^
// return : �����Ȃ�1�C�s�����Ȃ�0
int traverse(int* adata) {
	return 0;
}

void evalInitA() {

}

// �v�Z�X�R�A���Z
double TreeNode::countScore() {
	double score = calcpoint;
	if (child) {
		for (int i = 0; i < childNum; i++) {
			score += child[i]->countScore();
		}
	}
	return score;
}


void Pruning()
{

}

// �]���p�ϐ��̏�����
void TreeNode::evalInitA2()
{
	calcpoint = 0.0;
	term_count = 0;
}

// �񕪔���
bool TreeNode::jugde_reduction(int a, int b) 
{
	while (a != b) {
		if (a < b) b -= a;
		else a -= b;
	}
	if (a != 1)
		return true;
	else
		return false;
}

// 2�ׂ̂��攻��
bool TreeNode::judge_pow2(unsigned int x)
{
	if (x == 0) {
		return false;
	}

	return (x & (x - 1)) == 0;
}

// ���ލ���Z�߂�֐�
void TreeNode::judge_term(int term_num) {
	int i;
	if (term_num != 1) {
		for (i = 0; i < term_count; i++) {
			if (number_count[i][0] == term_num)
				break;
		}

		if (i == term_count) {
			number_count[i][0] = term_num;
			number_count[i][1] = 1;
			term_count++;
		}
		else {
			number_count[i][1]++;
		}
	}
}

//�v�Z�X�R�A����
void TreeNode::score_measure()
{
	int i,j;
	int plusnum = 0;

	//���ލ��̌v�Z�X�R�A
	for (i = 0; i < term_count; i++) {
		for (j = 0; j < number_count[i][1] - 1; j++) {
			calcpoint += CALC_SCORE_EASY;
		}
	}

	//�ΐ��v�Z�X�R�A
	for (i = 0; i < term_count; i++) {
		if (judge_pow2(number_count[i][0]) == true && number_count[i][1] != 0) {
			calcpoint += LOG_SCORE_EASY;
		}
		else if(judge_pow2(number_count[i][0]) == false && number_count[i][1] != 0){
			calcpoint += LOG_SCORE;
		}
	}

	//�Ō�̑����Z
	for (i = 0; i < term_count; i++) {
		if (number_count[i][1] != 0)
			plusnum++;
	}
	for (i = 0; i < plusnum - 1; i++) {
		calcpoint += CALC_SCORE_EASY;
	}

	//���Z�b�g
	for (i = 0; i < term_count; i++) {
		number_count[i][1] = 0;
	}
}