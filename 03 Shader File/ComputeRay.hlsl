//
//


struct Buff
{
	float3 v1;
	float3 v2;
	float3 v3;
	float fLength;
	bool Hit;
};

cbuffer global: register(b0)
{
	float4 g_vStart;
	float4 g_vEnd;
};

StructuredBuffer<Buff> BufferInput : register(t0);
RWStructuredBuffer<Buff> BufferOut : register(u0);
//
//
//3�_���畽�ʕ����������߂�
float4 CalcPlane(float3 vA,float3 vB,float3 vC)
{
	float4 plane=float4(0,0,0,0);
	//�Ӄx�N�g��
	float3 vAB,vBC;
	vAB=vB-vA;
	vBC=vC-vB;
	//���ʖ@���x�N�g��
	float3 vNormal;
	vNormal=cross(vAB,vBC);
	// �@���͕��ʂ̌X���ł�����̂ŁA���̂܂ܑ��
	plane.x=vNormal.x;
	plane.y=vNormal.y;
	plane.z=vNormal.z;
	// d ���v�Z
	plane.w=-(plane.x*vA.x + plane.y*vA.y+plane.z*vA.z);

	return plane;
}
//
//
// ��_���ʂ̓��ɂ���Ƃ���true���A�O�ɂ���Ƃ���false��Ԃ�
bool IsInside(float3 vI,float3 vA,float3 vB,float3 vC)
{
	//�Ӄx�N�g��
	float3 vAB,vBC,vCA;
	vAB=vB-vA;
	vBC=vC-vB;
	vCA=vA-vC;
	//�Ӄx�N�g���Ɓu���_�����_�֌������x�N�g���v�Ƃ́A���ꂼ��̊O�ϗp
	float3 vCrossAB,vCrossBC,vCrossCA;
	//�u�O�ό��ʂ̃x�N�g���v�ƕ��ʖ@���x�N�g���Ƃ́A���ꂼ��̓��ϗp
	float fAB,fBC,fCA;
	// �@���p
	float3 vNormal;
	// �܂��A3���_���畽�ʕ����������߂�B����́A�����ɕ��ʂ̖@�������߂邱�Ƃł�����
	float4 pln;
	pln=CalcPlane(vA,vB,vC);
	vNormal.x=pln.x;//�@����x�����͕��ʕ�������x�W��
	vNormal.y=pln.y;//�@����y�����͕��ʕ�������y�W��
	vNormal.z=pln.z;//�@����z�����͕��ʕ�������z�W��
	vNormal=normalize(vNormal);

	// �e���_�����_I�Ɍ������x�N�g����vV�Ƃ���
	float3 vV;
	// ��AB�x�N�g���i���_B�x�N�g��-���_A�x�N�g��)�ƁA���_A�����_I�֌������x�N�g���A�̊O�ς����߂�
	vV=vI-vA;
	vCrossAB=cross(vAB,vV);
	// ��BC�x�N�g���i���_C�x�N�g��-���_B�x�N�g��)�ƁA���_B�����_I�֌������x�N�g���A�̊O�ς����߂�
	vV=vI-vB;
	vCrossBC=cross(vBC,vV);
	// ��CA�x�N�g���i���_A�x�N�g��-���_C�x�N�g��)�ƁA���_C�����_I�֌������x�N�g���A�̊O�ς����߂�
	vV=vI-vC;
	vCrossCA=cross(vCA,vV);
	// ���ꂼ��́A�O�σx�N�g���Ƃ̓��ς��v�Z����
	fAB=dot(vNormal,vCrossAB);
	fBC=dot(vNormal,vCrossBC);
	fCA=dot(vNormal,vCrossCA);
	
	// �R�̓��ό��ʂ̂����A��ł��}�C�i�X�����̂��̂�����΁A��_�͊O�ɂ���B
	if(fAB>=0 && fBC>=0 && fCA>=0)
	{
		// ��_�́A�ʂ̓��ɂ���
		return true;
	}
	// ��_�͖ʂ̊O�ɂ���
	return false;
}
//
//
//���̖ʂƌ������Ă���� true  �łȂ���� false
float Intersect(float4 p,float3 vStart,float3 vEnd,float3 v1,float3 v2,float3 v3)
{
	float fLength=0;
	//�p�����g���b�N�������̔}��ϐ��h t "�������B
	float t=- ( ( p.x * vEnd.x) + (p.y*vEnd.y)+(p.z*vEnd.z)+p.w ) / 
				( ( (p.x*vStart.x)+(p.y*vStart.y)+(p.z*vStart.z) ) - ( (p.x*vEnd.x)+(p.y*vEnd.y)+(p.z*vEnd.z) ) ); 
	// t ���O����P�̊Ԃł���Ȃ�������Ă��邱�ƂɂȂ�i���̎��_�ł́A�܂����������ʂƂ̌����j
	if(t>=0 && t<=1.0)
	{
		//��_���W�𓾂�@�����������Ă���Η��[�_����ȒP�ɋ��܂�
		float3 v;
		v.x = t*vStart.x+(1-t)*vEnd.x;
		v.y = t*vStart.y+(1-t)*vEnd.y;
		v.z = t*vStart.z+(1-t)*vEnd.z;
		//��_���O�p�`�̓����O���𔻒�@�i�����œ����ƂȂ�΁A���S�Ȍ����ƂȂ�j
		if(IsInside(v,v1,v2,v3)==true)
		{
			//���C�n�_�ƌ�_�̋������v�Z
			fLength=length( v-vStart );
			return fLength;
		}
		return 0;
	}
	return 0;
}

[numthreads(1, 1, 1)]
//
//
//�X���b�h���̓��b�V���|���S�����ŕς��l�Ȃ̂ŁA�V�F�[�_�[���ŃX���b�h�����w��ł��Ȃ��B�Ȃ̂ŃX���b�h��(1,1,1)�@�A�v�����iDispatch)�ŕ����񐔂��w��B
void CS( uint3 id : SV_DispatchThreadID ,uint3 gid : SV_GroupID )
{
	float4 plane;
	float3 v1=BufferInput[id.x].v1;
	float3 v2=BufferInput[id.x].v2;
	float3 v3=BufferInput[id.x].v3;
	float3 vStart=(float3)g_vStart;
	float3 vEnd=(float3)g_vEnd;
	float fLength=0;

	plane=CalcPlane(v1,v2,v3);

	fLength=Intersect(plane,vStart,vEnd,v1,v2,v3);
	if(fLength != 0)
	{
		BufferOut[id.x].Hit=true;
	}
	else
	{
		BufferOut[id.x].Hit=false;
	}
	BufferOut[id.x].fLength=fLength;
}


















