#pragma once

//粒子群クラス
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
	double* gBestPos;	//グローバルベストの位置
	double gBestValue;	//グローバルベストの評価値
};