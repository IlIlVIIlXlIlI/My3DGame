#include "CharacterBase.h"

ChrBase::ChrBase()
{
	//m_pMesh = new XSKINMESH;
	//�L�����N�^�[�̊�{
	m_Hp = 100;			
	m_Attack = 30;
}

ChrBase::~ChrBase()
{

}

/*�L�����N�^�[�x�[�X�̏�����*/
void ChrBase::Init()
{

}

/*�L�����N�^�[�x�[�X�̍X�V*/
void ChrBase::Update()
{

}


/*����ł��邩*/
void ChrBase::Death()
{

}

void ChrBase::Render()
{

}

/*�����Ă��邩*/
void ChrBase::move()
{
	m_Pos += ToVec;
}

