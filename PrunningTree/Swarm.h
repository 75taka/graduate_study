#pragma once

//���q�Q�N���X
#include "Particle.h"
class Particle;

class Swarm
{
public:
	Swarm();
	~Swarm();
	void move();
	void printResult();

	TestData* dataset;
	Particle** particle;
	double* gBestPos;	//�O���[�o���x�X�g�̈ʒu
	double gBestValue;	//�O���[�o���x�X�g�̕]���l
};