//************************************************************************//
//	Texture Vertex Shader
//	2016-11-09
//	2016-12-04 revisited
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		Constant バッファ
//=======================================================================//
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer UVRepeat
{
	float uRepeat;
	float vRepeat;
	float2 padding;
};

//=======================================================================//
//		TypeDef
//=======================================================================//
struct VertexInputType
{
	float4 position: POSITION;
	float2 tex : TEXCOORD0; 
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

//=======================================================================//
//		Vertex Shader
//=======================================================================//
PixelInputType TextureVertexShader(VertexInputType input)
{
	PixelInputType output;
	input.position.w = 1.0f;

	//画面に対してピクセルの位置を計算する
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	//UV座標を保存する
	//output.tex = input.tex;
	output.tex = float2(input.tex.x * uRepeat, input.tex.y * vRepeat);

	return output;
}