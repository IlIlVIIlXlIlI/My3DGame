#pragma once
#include "BASE.h"
#include "CD3DXSKINMESH.h"



class ChrBase : public CD3DXSKINMESH
{
private:
	
public:
	ChrBase();
	virtual ~ChrBase();

	//=======================================================================================
	/*キャラクターベース*/
	//=======================================================================================
	float m_Hp;				//体力
	float m_Attack;			//攻撃力
	BOOL m_Deathflg = 0;	//死んでいるか　0:死んでいない　1:死んでいる
	BOOL m_Moveflg = 0;		//動いているか　0:動いていない　1:動いている
	D3DXVECTOR3 NowVec;		//今向いている方向
	D3DXVECTOR3 ToVec;		//向きたい方向
	D3DXVECTOR3 vCross;		//外積用変数
	D3DXVECTOR3 tmpVec;		//
	D3DXMATRIX mTrans;		//キャラクターのTrans
	D3DXMATRIX mRot;		//
	
	//===========================================================================
	//関数
	//===========================================================================

	virtual void Init();
	virtual void Update();
	virtual void Render();


	/*動いているか*/
	void move();

	/*死んでいるか*/
	void Death();

	
	

	
};