#pragma once
#include "BASE.h"
#include "CharacterBase.h"
#include "CAMERA.h"


class Player : public ChrBase
{
public:
	

	/*�v���C���[�̃X�e�[�^�X*/
	enum Player_Status
	{
		SQUAT_STATUS,			//0:���Ⴊ��

		JOGGING_STATUS,			//1:�W���M���O

		STANDING_STATUS,		//2:�ʏ�(����)

		SQUAT_FORWARD_STATUS,	//3:���Ⴊ��(�O�ɓ���)

		SQUAT_RIGHT_STATUS,		//4:���Ⴊ��(�E�ɓ���)

		SQUAT_BACK_STATUS,		//5:���Ⴊ��(���ɓ���)

		SQUAT_LEFT_STATUS,		//6:���Ⴊ��(���ɓ���)

		BOW_READY_STATUS,		//7:�|���\����

		RUNNING_STATUS,			//8:����

		CLIMING_STATUS,			//9:�o��

		JUMP_STATUS,			//10:�W�����v

		COVER_LEFT_STATUS,		//11:���Ǖ���

		COVER_RIGHT_STATUS,		//12:�E�Ǖ���

		GETTING_UP_STATUS,		//13:�����オ��(�ŏ��̃��[�V����)

		PUSH_ROCK_STATUS,		//14:�������

		PUSHING_ROCK_STATUS,	//15:�������2(��������)

		CLIMING_END_STATUS,		//16:�R��o��I����

		SHIMMY_STATUS,			//17:�Ԃ牺����

		SHIMMY_LEFT_STATUS,		//18:�Ԃ牺���鍶�ɓ���

		SHIMMY_RIGHT_STATUS,	//19:�Ԃ牺����E�ɓ���

		FALL_STATUS,			//20:������
	};
	

	/*���݂̃A�j���[�V�����𗧂���*/
	
	
	/*�J�����̉������Z���ŃL�����N�^�[�𓮂��������Ɉ�a���Ȃ��悤�ɂ���*/
	void TransformNomalToVec(D3DXVECTOR3);

	float tmpRot = 0.0f;

public:
	Player();

	Player_Status m_PlayerStatus = STANDING_STATUS;

	float camRadian = 0.0f;
	float chrRadian = 0.0f;

	D3DXVECTOR3 tmpVec;
	D3DXMATRIX  mRot;
	D3DXMATRIX  m_CamRad;			//�J�����̊p�x

	BOOL squatStatusFlg = FALSE;	//���Ⴊ��ł��邩
	BOOL bowStatusFlg	= FALSE;	//�|���\���Ă��邩
	BOOL m_ClimingFlg = FALSE;		//�N���C�~���O����
	BOOL m_CoverFlg = FALSE;		//�Ǖ�������
	BOOL m_GettingUpFlg = TRUE;		//�����オ�蒆��
	BOOL m_PushRockFlg = FALSE;		//��������Ă����Ԃ�
	BOOL m_PushNow = FALSE;			//�������Ă��邩
	BOOL m_PushinFlg = FALSE;		//�������Ă��邩
	BOOL m_ClimeEndFlg = FALSE;		//�o��I���邩
	BOOL m_ShimmyFlg = FALSE;		//�Ԃ牺�����Ă��邩

	float m_GettingUpCount = 0.0f;	//�����オ��p�̃��[�V�����J�E���g

	float m_ClimeEndCount = 0.0f;	//�o��I����p�̃��[�V�����J�E���g

	float move;						//�����p�̕ϐ�

	float KeyPanch = 0.0f;			//��������Ƃ��̘A�ŃJ�E���g

	bool m_OperationPossible = TRUE;	//����ł����Ԃ��ǂ���

	float m_AnimFarstCount = 0.0f;


	float m_Distance;				//����

	float playerHeight = 1.0f;		//�v���C���[�̍���	

	float m_groundDis = 0.0f;		//�n�ʂ܂ł̋���

	float m_gravity = 0.0f;			//�d��
	//============================================================================
	//���\�b�h
	//============================================================================

	/*�����Ă���*/
	void Move();

	/*�X�V*/
	void Update()override;

	/*�J�����̉�]*/
	void CameraRotate();

	/*�W���M���O-�O�i-*/
	void JogForward();
	/*�W���M���O-�E-*/
	void JogRight();
	/*�W���M���O-���-*/
	void JogBack();
	/*�W���M���O-��-*/
	void JogLeft();
	/*����*/
	void Running();
	/*����-�W�����v-*/
	void RunningJump();
	/*�N���C�~���O-UP-*/
	void Climing();
	/*�N���C�~���O-DOWN-*/
	void ClimingDown();

	/*���Ⴊ��-�O�i-*/
	void SquadForward();
	/*���Ⴊ��-�E-*/
	void SquadRight();
	/*���Ⴊ��-���-*/
	void SquadBack();
	/*���Ⴊ��-��-*/
	void SquadLeft();

	/*�|���\����*/
	void BowReady();

	/*���Ǖ���*/
	void CoverLeft();

	/*�E�Ǖ���*/
	void CoverRight();

	/*����������*/
	void GettingUp();

	/*�������*/
	void PushRock();

	/*�������2*/
	void PushingRock();

	/*�R��o��I����*/
	void ClimingEnd();

	/*�Ԃ牺����*/
	void Shimmy();

	/*�Ԃ牺���鍶�ɓ���*/
	void ShimmyLeft();

	/*�Ԃ牺����E�ɓ���*/
	void ShimmyRight();

	/*������*/
	void Fall();
	
};