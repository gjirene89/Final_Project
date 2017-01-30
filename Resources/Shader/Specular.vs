//************************************************************************//
//	Specular Vertex Shader
//	2016-11-25
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		グローバル変数
//=======================================================================//
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer CameraBuffer
{
	float3 cameraPosition;
	float camPadding;
};

//=======================================================================//
//		TypeDef
//=======================================================================//
struct VertexInputType
{
	float4 position: POSITION;
	float2 tex : TEXCOORD0; 
	float3 normal : NORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 viewDirection : TEXCOORD1;
};

//=======================================================================//
//		Specular Vertex Shader
//=======================================================================//
PixelInputType SpecularVertexShader(VertexInputType input)
{
	PixelInputType output;
	float4 worldPosition;

	input.position.w = 1.0f;

	//画面に対してピクセルの位置を計算する
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	//UV座標を保存する
	output.tex = input.tex;

	//法線ベクトルをワールド行列と掛け算する
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);


	//ビューによる頂点の位置を求める
	worldPosition = mul(input.position, worldMatrix);
	output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	output.viewDirection = normalize(output.viewDirection);

	return output;
}