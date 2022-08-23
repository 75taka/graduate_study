#pragma once

//粒子クラス
#include "Tree.h"
#include "Swarm.h"
class Swarm;

//以下具体的な数値は仮
#define TIME_MAX	1000 //最終時刻
#define SWARM_SIZE	100  //粒子群のサイズ
#define INERTIA		0.9  //慣性係数
#define ACCEL_P		0.8  //加速係数（パーソナルベスト）
#define ACCEL_G		0.8  //加速係数（グローバルベスト）

class Particle
{
public:
	Particle(Swarm* argPS);
	~Particle();
	void move();

	Swarm* swarm;		//所属している粒子群
	double* pos;		//粒子の位置
	double* velocity;	//粒子の速度
	double value;		//評価値

private:
	void evaluate();	//評価値算出

	double* pBestPos;	//パーソナルベストの位置
	double pBestValue;	//パーソナルベストの評価値
};