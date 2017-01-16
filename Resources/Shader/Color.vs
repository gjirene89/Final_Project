//************************************************************************//
//	Color Vertex Shader
//	2016-11-08
//	2016-12-04 revisited
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		Constant�@�o�b�t�@
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

	//��ʂɑ΂��ăs�N�Z���̈ʒu���v�Z����
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	//UV���W��ۑ�����
	output.color = input.color;

	return output;
}

