#include "CharacterBase.h"

ChrBase::ChrBase()
{
	//m_pMesh = new XSKINMESH;
	//キャラクターの基本
	m_Hp = 100;			
	m_Attack = 30;
}

ChrBase::~ChrBase()
{

}

/*キャラクターベースの初期化*/
void ChrBase::Init()
{

}

/*キャラクターベースの更新*/
void ChrBase::Update()
{

}


/*死んでいるか*/
void ChrBase::Death()
{

}

void ChrBase::Render()
{

}

/*動いているか*/
void ChrBase::move()
{
	m_Pos += ToVec;
}

