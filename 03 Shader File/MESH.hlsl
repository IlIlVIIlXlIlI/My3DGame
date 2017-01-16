Texture2D g_texColor: register(t0);
Texture2D g_texNormal: register(t1);
SamplerState g_samLinear : register(s0);

cbuffer global_0: register(b0)
{
	matrix g_mW;//���[���h�s��
	matrix g_mWIT;//���[���h�̋t�̓]�u�s��
	matrix g_mWVP;//���[���h����ˉe�܂ł̕ϊ��s��
	float4 g_vLightDir;//���C�g�̕����x�N�g��
	float4 g_vEye;//���_�A�J�����ʒu
};

cbuffer global_1: register(b1)
{
	float4 g_Ambient = float4(1,1,1,1);//�A���r�G���g��
	float4 g_Diffuse;//�g�U����(�F�j
	float4 g_Specular;//���ʔ���
};

//
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float3 Light : TEXCOORD0;
	float3 Normal : TEXCOORD1;
	float3 HalfVector : TEXCOORD2;
	float3 EyeVector : TEXCOORD3;
	float2 Tex : TEXCOORD4;
};

//
//
//�o�[�e�b�N�X�V�F�[�_�[
VS_OUTPUT VS(float4 Pos : POSITION, float4 Normal : NORMAL
	, float2 Tex : TEXCOORD, float4 Tangent : TANGENT)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float3 worldPos = mul(Pos, g_mW).xyz;
	float3 LightVector = normalize(g_vLightDir);
	float3 EyeVector = normalize(g_vEye.xyz - worldPos);
	float3 HalfVector = normalize(LightVector + EyeVector);

	float3 T = mul(Tangent.xyz, (float3x3)g_mWIT);
	float3 N = mul(Normal, (float3x3)g_mWIT);
	float3 B = cross(N, T) * Tangent.w;

	float3x3 TangentToObject = float3x3(T.x, B.x, N.x,
		T.y, B.y, N.y,
		T.z, B.z, N.z);
	output.Normal = mul(Normal, g_mW);
	output.Pos = mul(Pos, g_mWVP);
	output.Tex = Tex;
	output.HalfVector = mul(HalfVector, TangentToObject);
	output.Light = mul(LightVector, TangentToObject);

	return output;
}

//
//
//�s�N�Z���V�F�[�_�[
float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 HalfVector = normalize(input.HalfVector);
	float3 Light = normalize(input.Light);
	float3 Normal = normalize(g_texNormal.Sample(g_samLinear,input.Tex).rgb*2.0f - 1.0f);
	float NH = saturate(dot(Normal, HalfVector));
	float NL = saturate(dot(Normal, Light));
	float Power = (NL == 0.0f) ? 0.0f : pow(NH,4);

	float4 FinalColor = g_Ambient + (g_Diffuse * NL) + g_Specular*Power + g_texColor.Sample(g_samLinear,input.Tex) / 2;

	return FinalColor;
}