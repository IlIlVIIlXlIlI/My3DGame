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
//3点から平面方程式を求める
float4 CalcPlane(float3 vA,float3 vB,float3 vC)
{
	float4 plane=float4(0,0,0,0);
	//辺ベクトル
	float3 vAB,vBC;
	vAB=vB-vA;
	vBC=vC-vB;
	//平面法線ベクトル
	float3 vNormal;
	vNormal=cross(vAB,vBC);
	// 法線は平面の傾きでもあるので、そのまま代入
	plane.x=vNormal.x;
	plane.y=vNormal.y;
	plane.z=vNormal.z;
	// d を計算
	plane.w=-(plane.x*vA.x + plane.y*vA.y+plane.z*vA.z);

	return plane;
}
//
//
// 交点が面の内にあるときはtrueを、外にあるときはfalseを返す
bool IsInside(float3 vI,float3 vA,float3 vB,float3 vC)
{
	//辺ベクトル
	float3 vAB,vBC,vCA;
	vAB=vB-vA;
	vBC=vC-vB;
	vCA=vA-vC;
	//辺ベクトルと「頂点から交点へ向かうベクトル」との、それぞれの外積用
	float3 vCrossAB,vCrossBC,vCrossCA;
	//「外積結果のベクトル」と平面法線ベクトルとの、それぞれの内積用
	float fAB,fBC,fCA;
	// 法線用
	float3 vNormal;
	// まず、3頂点から平面方程式を求める。これは、同時に平面の法線を求めることでもある
	float4 pln;
	pln=CalcPlane(vA,vB,vC);
	vNormal.x=pln.x;//法線のx成分は平面方程式のx係数
	vNormal.y=pln.y;//法線のy成分は平面方程式のy係数
	vNormal.z=pln.z;//法線のz成分は平面方程式のz係数
	vNormal=normalize(vNormal);

	// 各頂点から交点Iに向かうベクトルをvVとする
	float3 vV;
	// 辺ABベクトル（頂点Bベクトル-頂点Aベクトル)と、頂点Aから交点Iへ向かうベクトル、の外積を求める
	vV=vI-vA;
	vCrossAB=cross(vAB,vV);
	// 辺BCベクトル（頂点Cベクトル-頂点Bベクトル)と、頂点Bから交点Iへ向かうベクトル、の外積を求める
	vV=vI-vB;
	vCrossBC=cross(vBC,vV);
	// 辺CAベクトル（頂点Aベクトル-頂点Cベクトル)と、頂点Cから交点Iへ向かうベクトル、の外積を求める
	vV=vI-vC;
	vCrossCA=cross(vCA,vV);
	// それぞれの、外積ベクトルとの内積を計算する
	fAB=dot(vNormal,vCrossAB);
	fBC=dot(vNormal,vCrossBC);
	fCA=dot(vNormal,vCrossCA);
	
	// ３つの内積結果のうち、一つでもマイナス符号のものがあれば、交点は外にある。
	if(fAB>=0 && fBC>=0 && fCA>=0)
	{
		// 交点は、面の内にある
		return true;
	}
	// 交点は面の外にある
	return false;
}
//
//
//その面と交差していれば true  でなければ false
float Intersect(float4 p,float3 vStart,float3 vEnd,float3 v1,float3 v2,float3 v3)
{
	float fLength=0;
	//パラメトリック方程式の媒介変数” t "を解く。
	float t=- ( ( p.x * vEnd.x) + (p.y*vEnd.y)+(p.z*vEnd.z)+p.w ) / 
				( ( (p.x*vStart.x)+(p.y*vStart.y)+(p.z*vStart.z) ) - ( (p.x*vEnd.x)+(p.y*vEnd.y)+(p.z*vEnd.z) ) ); 
	// t が０から１の間であるなら交差していることになる（この時点では、まだ無限遠平面との交差）
	if(t>=0 && t<=1.0)
	{
		//交点座標を得る　ｔが分かっていれば両端点から簡単に求まる
		float3 v;
		v.x = t*vStart.x+(1-t)*vEnd.x;
		v.y = t*vStart.y+(1-t)*vEnd.y;
		v.z = t*vStart.z+(1-t)*vEnd.z;
		//交点が三角形の内か外かを判定　（ここで内部となれば、完全な交差となる）
		if(IsInside(v,v1,v2,v3)==true)
		{
			//レイ始点と交点の距離を計算
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
//スレッド数はメッシュポリゴン数で変わる値なので、シェーダー内でスレッド数を指定できない。なのでスレッドは(1,1,1)　アプリ側（Dispatch)で複数回数を指定。
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


















