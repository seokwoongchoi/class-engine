#pragma once
#include "stdafx.h"

enum class ShaderType :uint
{
	VS,PS,GS,CS //GS=������Ʈ��,CS,DS,HS, ->3D��
};

struct CameraData
{
	Matrix View;
	Matrix Proj;
};
struct TransformData
{
	Matrix World;
};

struct SpriteData
{
	Vector2 TextureSize;
	Vector2 SpriteOffset;
	Vector2 SpriteSize;
	float Padding[2]; //����ִ°��� �ΰ�������༭ 16����Ʈ�� �����Ͱ� ���� ���ش�. 16����Ʈ���ȵ����ϸ� ������.
};
//#endif // !_BACK_END