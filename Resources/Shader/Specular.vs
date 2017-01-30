//************************************************************************//
//	Specular Vertex Shader
//	2016-11-25
//	Irene Gersenowies
//************************************************************************//

//=======================================================================//
//		�O���[�o���ϐ�
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

	//��ʂɑ΂��ăs�N�Z���̈ʒu���v�Z����
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	//UV���W��ۑ�����
	output.tex = input.tex;

	//�@���x�N�g�������[���h�s��Ɗ|���Z����
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);


	//�r���[�ɂ�钸�_�̈ʒu�����߂�
	worldPosition = mul(input.position, worldMatrix);
	output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	output.viewDirection = normalize(output.viewDirection);

	return output;
}