#include "stdafx.h"
#include "Model.h"
#include "../Component/Animator.h"
#include "../Component/Transform.h"

Model::Model(Context * context)
	: IResource(context)
{
	//���� ���� �����
	GeometryUtility::CreateQuad(&mesh);

	//���ؽ� ���� �����
	vertexBuffer = new VertexBuffer(context->GetSubsystem<Graphics>());
	vertexBuffer->Create<VertexTexture>(mesh.AppendVertices());

	//�ε��� ���� �����
	indexBuffer = new IndexBuffer(context->GetSubsystem<Graphics>());
	indexBuffer->Create(mesh.AppendIndices());

	auto resourceManager = context->GetSubsystem<ResourceManager>();

	//�ؽ��� �����
	texture = resourceManager->Load<Texture2D>("metalslug.png");

	//���̴� �����
	shader = resourceManager->Load<Shader>("Sprite.hlsl");

	animator = new Animator(context);
	animator->AddAnimation("Metalslug.xml");
	animator->SetCurrentAnimation("Idle");
	animator->Play();


	//
	spriteBuffer = new ConstantBuffer(context->GetSubsystem<Graphics>());
	spriteBuffer->Create<SpriteData>();

	
}

Model::~Model()
{
	
	SAFE_DELETE(spriteBuffer);
	SAFE_DELETE(animator);
	SAFE_DELETE(indexBuffer);
	SAFE_DELETE(vertexBuffer);
}

void Model::Update()
{
	animator->Update();

	auto curKeyframe = animator->GetCurrentKeyframe();

	auto spriteData = static_cast<SpriteData*>(spriteBuffer->Map());
	spriteData->TextureSize = curKeyframe.texture->GetSize();
	spriteData->SpriteOffset = curKeyframe.offset;
	spriteData->SpriteSize = curKeyframe.size;
	spriteBuffer->Unmap();

	
}

void Model::Render()
{
	vertexBuffer->BindPipeline();
	indexBuffer->BindPipeline();

	shader->BindPipeline();

	
	spriteBuffer->SetVS(2);
	texture->SetPS(0);

	auto graphics = context->GetSubsystem<Graphics>();
	graphics->GetDeviceContext()->IASetPrimitiveTopology
	(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	);

	//Draw Call
	graphics->GetDeviceContext()->DrawIndexed
	(
		mesh.IndicesCount(),
		0,
		0
	);
}