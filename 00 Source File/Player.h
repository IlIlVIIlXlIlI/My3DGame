#pragma once
#include "BASE.h"
#include "CharacterBase.h"
#include "CAMERA.h"


class Player : public ChrBase
{
public:
	

	/*プレイヤーのステータス*/
	enum Player_Status
	{
		SQUAT_STATUS,			//0:しゃがむ

		JOGGING_STATUS,			//1:ジョギング

		STANDING_STATUS,		//2:通常(立ち)

		SQUAT_FORWARD_STATUS,	//3:しゃがむ(前に動く)

		SQUAT_RIGHT_STATUS,		//4:しゃがむ(右に動く)

		SQUAT_BACK_STATUS,		//5:しゃがむ(後ろに動く)

		SQUAT_LEFT_STATUS,		//6:しゃがむ(左に動く)

		BOW_READY_STATUS,		//7:弓を構える

		RUNNING_STATUS,			//8:走る

		CLIMING_STATUS,			//9:登る

		JUMP_STATUS,			//10:ジャンプ

		COVER_LEFT_STATUS,		//11:左壁歩き

		COVER_RIGHT_STATUS,		//12:右壁歩き

		GETTING_UP_STATUS,		//13:立ち上がる(最初のモーション)

		PUSH_ROCK_STATUS,		//14:岩を押す

		PUSHING_ROCK_STATUS,	//15:岩を押す2(強く押す)

		CLIMING_END_STATUS,		//16:崖を登り終える

		SHIMMY_STATUS,			//17:ぶら下がる

		SHIMMY_LEFT_STATUS,		//18:ぶら下がる左に動く

		SHIMMY_RIGHT_STATUS,	//19:ぶら下がる右に動く

		FALL_STATUS,			//20:落ちる
	};
	

	/*現在のアニメーションを立ちに*/
	
	
	/*カメラの奥が常にZ軸でキャラクターを動かした時に違和感ないようにする*/
	void TransformNomalToVec(D3DXVECTOR3);

	float tmpRot = 0.0f;

public:
	Player();

	Player_Status m_PlayerStatus = STANDING_STATUS;

	float camRadian = 0.0f;
	float chrRadian = 0.0f;

	D3DXVECTOR3 tmpVec;
	D3DXMATRIX  mRot;
	D3DXMATRIX  m_CamRad;			//カメラの角度

	BOOL squatStatusFlg = FALSE;	//しゃがんでいるか
	BOOL bowStatusFlg	= FALSE;	//弓を構えているか
	BOOL m_ClimingFlg = FALSE;		//クライミング中か
	BOOL m_CoverFlg = FALSE;		//壁歩き中か
	BOOL m_GettingUpFlg = TRUE;		//立ち上がり中か
	BOOL m_PushRockFlg = FALSE;		//岩を押している状態か
	BOOL m_PushNow = FALSE;			//今押しているか
	BOOL m_PushinFlg = FALSE;		//今押しているか
	BOOL m_ClimeEndFlg = FALSE;		//登り終えるか
	BOOL m_ShimmyFlg = FALSE;		//ぶら下がっているか

	float m_GettingUpCount = 0.0f;	//立ち上がる用のモーションカウント

	float m_ClimeEndCount = 0.0f;	//登り終える用のモーションカウント

	float move;						//動く用の変数

	float KeyPanch = 0.0f;			//岩を押すときの連打カウント

	bool m_OperationPossible = TRUE;	//操作できる状態かどうか

	float m_AnimFarstCount = 0.0f;


	float m_Distance;				//距離

	float playerHeight = 1.0f;		//プレイヤーの高さ	

	float m_groundDis = 0.0f;		//地面までの距離

	float m_gravity = 0.0f;			//重力
	//============================================================================
	//メソッド
	//============================================================================

	/*動いている*/
	void Move();

	/*更新*/
	void Update()override;

	/*カメラの回転*/
	void CameraRotate();

	/*ジョギング-前進-*/
	void JogForward();
	/*ジョギング-右-*/
	void JogRight();
	/*ジョギング-後退-*/
	void JogBack();
	/*ジョギング-左-*/
	void JogLeft();
	/*走る*/
	void Running();
	/*走る-ジャンプ-*/
	void RunningJump();
	/*クライミング-UP-*/
	void Climing();
	/*クライミング-DOWN-*/
	void ClimingDown();

	/*しゃがむ-前進-*/
	void SquadForward();
	/*しゃがむ-右-*/
	void SquadRight();
	/*しゃがむ-後退-*/
	void SquadBack();
	/*しゃがむ-左-*/
	void SquadLeft();

	/*弓を構える*/
	void BowReady();

	/*左壁歩き*/
	void CoverLeft();

	/*右壁歩き*/
	void CoverRight();

	/*立ちあがる*/
	void GettingUp();

	/*岩を押す*/
	void PushRock();

	/*岩を押す2*/
	void PushingRock();

	/*崖を登り終える*/
	void ClimingEnd();

	/*ぶら下がる*/
	void Shimmy();

	/*ぶら下がる左に動く*/
	void ShimmyLeft();

	/*ぶら下がる右に動く*/
	void ShimmyRight();

	/*落ちる*/
	void Fall();
	
};