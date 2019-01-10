#include "stdafx.h"
#include "Renderable.h"
#include "Transform.h"

Renderable::Renderable(Context * context, GameObject * gameobject, Transform * transform)
	:IComponent(context,gameobject,transform)
	,material(nullptr)
	,vertexBuffer(nullptr)
	,indexBuffer(nullptr)
	,topology(nullptr)
	,renderType(RenderType::DrawIndexed)
	,modelType(ModelType::Custom)
{
	material = new Material(context);
	material->SetShader("Default.hlsl");
	
	topology = new PrimitiveTopology(context);
}

Renderable::~Renderable()
{
	SAFE_DELETE(topology);
	SAFE_DELETE(material);
}

void Renderable::OnInitialize()
{
}

void Renderable::OnStart()
{
}

void Renderable::OnUpdate()
{
}

void Renderable::OnStop()
{
}

void Renderable::OnDestroy()
{
}



void Renderable::SetModelType(const ModelType & modelType)
{
	this->modelType = modelType;
	
	SetGeometry(modelType);
}

void Renderable::SetGeometry(const ModelType & type)
{
	//수정필요
	vertexBuffer = new VertexBuffer(context);
	indexBuffer = new IndexBuffer(context);
	
	switch (type)
	{
	case ModelType::Quad: GeometryUtility::CreateQuad(&mesh); break;

	case ModelType::ScreenQuad:GeometryUtility::CreateScreednQuad(&mesh); break;

	case ModelType::Circle:GeometryUtility::CreateCircle(&mesh); break;
	
	}

	boundBox = BoundBox(mesh.AppendVertices());
	boundBox.Transformed(transform->GetWorldMatrix());
	
	
	vertexBuffer->Create<VertexTexture>(mesh.AppendVertices());
	indexBuffer->Create(mesh.AppendIndices());
}
