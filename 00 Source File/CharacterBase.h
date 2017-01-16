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
	/*�L�����N�^�[�x�[�X*/
	//=======================================================================================
	float m_Hp;				//�̗�
	float m_Attack;			//�U����
	BOOL m_Deathflg = 0;	//����ł��邩�@0:����ł��Ȃ��@1:����ł���
	BOOL m_Moveflg = 0;		//�����Ă��邩�@0:�����Ă��Ȃ��@1:�����Ă���
	D3DXVECTOR3 NowVec;		//�������Ă������
	D3DXVECTOR3 ToVec;		//������������
	D3DXVECTOR3 vCross;		//�O�ϗp�ϐ�
	D3DXVECTOR3 tmpVec;		//
	D3DXMATRIX mTrans;		//�L�����N�^�[��Trans
	D3DXMATRIX mRot;		//
	
	//===========================================================================
	//�֐�
	//===========================================================================

	virtual void Init();
	virtual void Update();
	virtual void Render();


	/*�����Ă��邩*/
	void move();

	/*����ł��邩*/
	void Death();

	
	

	
};