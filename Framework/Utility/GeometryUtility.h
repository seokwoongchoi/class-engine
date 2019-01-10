#pragma once
class GeometryUtility
{
public:
	static void CreateQuad(class Mesh<Vertex>*mesh);
	static void CreateQuad(class Mesh<VertexColor>*mesh);
	static void CreateQuad(class Mesh<VertexTexture>*mesh);

	static void CreateScreednQuad(class Mesh<Vertex>*mesh);
	static void CreateScreednQuad(class Mesh<VertexColor>*mesh);
	static void CreateScreednQuad(class Mesh<VertexTexture>*mesh);

	static void CreateCircle(class Mesh<Vertex>*mesh);
	static void CreateCircle(class Mesh<VertexColor>*mesh);
	static void CreateCircle(class Mesh<VertexTexture>*mesh);
};