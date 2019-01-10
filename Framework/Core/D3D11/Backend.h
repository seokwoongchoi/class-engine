#pragma once
#include "stdafx.h"

enum class ShaderType :uint
{
	VS,PS,GS,CS //GS=지오메트리,CS,DS,HS, ->3D용
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
	float Padding[2]; //비어있는공간 두개만들어줘서 16바이트씩 데이터가 들어가게 해준다. 16바이트씩안들어가게하면 터진다.
};
//#endif // !_BACK_END