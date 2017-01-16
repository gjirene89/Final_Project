//************************************************************************//
//	Color Vertex Shader
//	2016-11-08
//	2016-12-04 revisited
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		Constant　バッファ
//=======================================================================//
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};


//=======================================================================//
//		TypeDef
//=======================================================================//
struct VertexInputType
{
	float4 position: POSITION;
	float4 color : COLOR; 
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

//=======================================================================//
//		VertexShader
//=======================================================================//
PixelInputType ColorVertexShader(VertexInputType input)
{
	PixelInputType output;

	input.position.w = 1.0f;

	//画面に対してピクセルの位置を計算する
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	//UV座標を保存する
	output.color = input.color;

	return output;
}

