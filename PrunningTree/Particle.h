#pragma once

//���q�N���X
#include "Tree.h"
#include "Swarm.h"
class Swarm;

//�ȉ���̓I�Ȑ��l�͉�
#define TIME_MAX	1000 //�ŏI����
#define SWARM_SIZE	100  //���q�Q�̃T�C�Y
#define INERTIA		0.9  //�����W��
#define ACCEL_P		0.8  //�����W���i�p�[�\�i���x�X�g�j
#define ACCEL_G		0.8  //�����W���i�O���[�o���x�X�g�j

class Particle
{
public:
	Particle(Swarm* argPS);
	~Particle();
	void move();

	Swarm* swarm;		//�������Ă��闱�q�Q
	double* pos;		//���q�̈ʒu
	double* velocity;	//���q�̑��x
	double value;		//�]���l

private:
	void evaluate();	//�]���l�Z�o

	double* pBestPos;	//�p�[�\�i���x�X�g�̈ʒu
	double pBestValue;	//�p�[�\�i���x�X�g�̕]���l
};