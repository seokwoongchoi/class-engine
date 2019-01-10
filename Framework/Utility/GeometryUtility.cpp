#include "stdafx.h"
#include "GeometryUtility.h"

void GeometryUtility::CreateQuad(Mesh<Vertex>* mesh)
{
	mesh->AddVertex(Vertex(-0.5f, -0.5f, 0.0f)); //0
	mesh->AddVertex(Vertex(-0.5f, 0.5f, 0.0f)); //1
	mesh->AddVertex(Vertex(0.5f, -0.5f, 0.0f)); //2
	mesh->AddVertex(Vertex(0.5f, 0.5f, 0.0f)); //3

	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(2);
	mesh->AddIndex(2); mesh->AddIndex(1); mesh->AddIndex(3);
}
void GeometryUtility::CreateQuad(Mesh<VertexColor>* mesh)
{
	mesh->AddVertex(VertexColor(-0.5f, -0.5f, 0.0f,0,0,0,1)); //0
	mesh->AddVertex(VertexColor(-0.5f, 0.5f, 0.0f, 0,0,0,1)); //1
	mesh->AddVertex(VertexColor(0.5f, -0.5f, 0.0f, 0,0,0,1)); //2
	mesh->AddVertex(VertexColor(0.5f, 0.5f, 0.0f, 0,0,0,1)); //3

	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(2);
	mesh->AddIndex(2); mesh->AddIndex(1); mesh->AddIndex(3);
}
void GeometryUtility::CreateQuad(Mesh<VertexTexture>* mesh)
{
	//mesh사각형 
	mesh->AddVertex(VertexTexture(-0.5f, -0.5f, 0.0f, 0, 1)); //0
	mesh->AddVertex(VertexTexture(-0.5f, 0.5f, 0.0f, 0, 0)); //1
	mesh->AddVertex(VertexTexture(0.5f, -0.5f, 0.0f, 1, 1)); //2
	mesh->AddVertex(VertexTexture(0.5f, 0.5f, 0.0f, 1, 0)); //3
		
	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(2);
	mesh->AddIndex(2); mesh->AddIndex(1); mesh->AddIndex(3);

}

void GeometryUtility::CreateScreednQuad(Mesh<Vertex>* mesh) //화면 사이즈
{
	float halfWidth = Settings::Get()-> GetWidth()*0.5f;
	float halfHeight = Settings::Get()->GetHeight()*0.5f;
	mesh->AddVertex(Vertex(-halfWidth, -halfHeight, 0.0f)); //0
	mesh->AddVertex(Vertex(-halfWidth, halfHeight, 0.0f)); //1
	mesh->AddVertex(Vertex(halfWidth, -halfHeight, 0.0f)); //2
	mesh->AddVertex(Vertex(halfWidth, halfHeight, 0.0f)); //3

	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(2);
	mesh->AddIndex(2); mesh->AddIndex(1); mesh->AddIndex(3);
}

void GeometryUtility::CreateScreednQuad(Mesh<VertexTexture>* mesh)
{
	float halfWidth = Settings::Get()->GetWidth()*0.5f;
	float halfHeight = Settings::Get()->GetHeight()*0.5f;
	mesh->AddVertex(VertexTexture(-halfWidth, -halfHeight, 0.0f,0,1)); //0
	mesh->AddVertex(VertexTexture(-halfWidth, halfHeight, 0.0f,0,0)); //1
	mesh->AddVertex(VertexTexture(halfWidth, -halfHeight, 0.0f,1,1)); //2
	mesh->AddVertex(VertexTexture(halfWidth, halfHeight, 0.0f,1,0)); //3

	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(2);
	mesh->AddIndex(2); mesh->AddIndex(1); mesh->AddIndex(3);
}

void GeometryUtility::CreateCircle(Mesh<Vertex>* mesh)
{
	float angle = static_cast<float>((2 * D3DX_PI) / 36);
	D3DXVECTOR3 position[37];
	for (int i = 0; i <= 36; i++)
	{
		position[i].x = cosf(i * angle);
		position[i].y = sinf(i * angle);
		position[i].z = 0.0f;

		
	}
	mesh->AddVertex(Vertex(0.0f, 0.0f, 0.0f));//0
		mesh->AddVertex(Vertex(position[0].x, position[0].y, 0.0f));//1
		mesh->AddVertex(Vertex(position[1].x, position[1].y, 0.0f));//2
		mesh->AddVertex(Vertex(position[2].x, position[2].y, 0.0f));//3
		mesh->AddVertex(Vertex(position[3].x, position[3].y, 0.0f));//4
		mesh->AddVertex(Vertex(position[4].x, position[4].y, 0.0f));//5
		mesh->AddVertex(Vertex(position[5].x, position[5].y, 0.0f));//6
		mesh->AddVertex(Vertex(position[6].x, position[6].y, 0.0f));//7
		mesh->AddVertex(Vertex(position[7].x, position[7].y, 0.0f));//8
		mesh->AddVertex(Vertex(position[8].x, position[8].y, 0.0f));//9
		mesh->AddVertex(Vertex(position[9].x, position[9].y, 0.0f));//10
		mesh->AddVertex(Vertex(position[10].x, position[10].y, 0.0f));//11
		mesh->AddVertex(Vertex(position[11].x, position[11].y, 0.0f));//12
		mesh->AddVertex(Vertex(position[12].x, position[12].y, 0.0f));//13
		mesh->AddVertex(Vertex(position[13].x, position[13].y, 0.0f));//14
		mesh->AddVertex(Vertex(position[14].x, position[14].y, 0.0f));//15
		mesh->AddVertex(Vertex(position[15].x, position[15].y, 0.0f));//16
		mesh->AddVertex(Vertex(position[16].x, position[16].y, 0.0f));//17
		mesh->AddVertex(Vertex(position[17].x, position[17].y, 0.0f));//18
		mesh->AddVertex(Vertex(position[18].x, position[18].y, 0.0f));//19
		mesh->AddVertex(Vertex(position[19].x, position[19].y, 0.0f));//20
		mesh->AddVertex(Vertex(position[20].x, position[20].y, 0.0f));//21
		mesh->AddVertex(Vertex(position[21].x, position[21].y, 0.0f));//22
		mesh->AddVertex(Vertex(position[22].x, position[22].y, 0.0f));//23
		mesh->AddVertex(Vertex(position[23].x, position[23].y, 0.0f));//24
		mesh->AddVertex(Vertex(position[24].x, position[24].y, 0.0f));//25
		mesh->AddVertex(Vertex(position[25].x, position[25].y, 0.0f));//26
		mesh->AddVertex(Vertex(position[26].x, position[26].y, 0.0f));//27
		mesh->AddVertex(Vertex(position[27].x, position[27].y, 0.0f));//28
		mesh->AddVertex(Vertex(position[28].x, position[28].y, 0.0f));//29
		mesh->AddVertex(Vertex(position[29].x, position[29].y, 0.0f));//30
		mesh->AddVertex(Vertex(position[30].x, position[30].y, 0.0f));//31
		mesh->AddVertex(Vertex(position[31].x, position[31].y, 0.0f));//32
		mesh->AddVertex(Vertex(position[32].x, position[32].y, 0.0f));//33
		mesh->AddVertex(Vertex(position[33].x, position[33].y, 0.0f));//34
		mesh->AddVertex(Vertex(position[34].x, position[34].y, 0.0f));//35
		mesh->AddVertex(Vertex(position[35].x, position[35].y, 0.0f));//35
		mesh->AddVertex(Vertex(position[36].x, position[36].y, 0.0f));//36
		
		
		mesh->AddIndex(0); mesh->AddIndex(2); mesh->AddIndex(1);
		mesh->AddIndex(0); mesh->AddIndex(3); mesh->AddIndex(2);
		mesh->AddIndex(0); mesh->AddIndex(4); mesh->AddIndex(3);
		mesh->AddIndex(0); mesh->AddIndex(5); mesh->AddIndex(4);
		mesh->AddIndex(0); mesh->AddIndex(6); mesh->AddIndex(5);
		mesh->AddIndex(0); mesh->AddIndex(7); mesh->AddIndex(6);
		mesh->AddIndex(0); mesh->AddIndex(8); mesh->AddIndex(7);
		mesh->AddIndex(0); mesh->AddIndex(9); mesh->AddIndex(8);
		mesh->AddIndex(0); mesh->AddIndex(10); mesh->AddIndex(9);
		mesh->AddIndex(0); mesh->AddIndex(11); mesh->AddIndex(10);
		mesh->AddIndex(0); mesh->AddIndex(12); mesh->AddIndex(11);
		mesh->AddIndex(0); mesh->AddIndex(13); mesh->AddIndex(12);
		mesh->AddIndex(0); mesh->AddIndex(14); mesh->AddIndex(13);
		mesh->AddIndex(0); mesh->AddIndex(15); mesh->AddIndex(14);
		mesh->AddIndex(0); mesh->AddIndex(16); mesh->AddIndex(15);
		mesh->AddIndex(0); mesh->AddIndex(17); mesh->AddIndex(16);
		mesh->AddIndex(0); mesh->AddIndex(18); mesh->AddIndex(17);
		mesh->AddIndex(0); mesh->AddIndex(19); mesh->AddIndex(18);
		mesh->AddIndex(0); mesh->AddIndex(20); mesh->AddIndex(19);
		mesh->AddIndex(0); mesh->AddIndex(21); mesh->AddIndex(20);
		mesh->AddIndex(0); mesh->AddIndex(22); mesh->AddIndex(21);
		mesh->AddIndex(0); mesh->AddIndex(23); mesh->AddIndex(22);
		mesh->AddIndex(0); mesh->AddIndex(24); mesh->AddIndex(23);
		mesh->AddIndex(0); mesh->AddIndex(25); mesh->AddIndex(24);
		mesh->AddIndex(0); mesh->AddIndex(26); mesh->AddIndex(25);
		mesh->AddIndex(0); mesh->AddIndex(27); mesh->AddIndex(26);
		mesh->AddIndex(0); mesh->AddIndex(28); mesh->AddIndex(27);
		mesh->AddIndex(0); mesh->AddIndex(29); mesh->AddIndex(28);
		mesh->AddIndex(0); mesh->AddIndex(30); mesh->AddIndex(29);
		mesh->AddIndex(0); mesh->AddIndex(31); mesh->AddIndex(30);
		mesh->AddIndex(0); mesh->AddIndex(32); mesh->AddIndex(31);
		mesh->AddIndex(0); mesh->AddIndex(33); mesh->AddIndex(32);
		mesh->AddIndex(0); mesh->AddIndex(34); mesh->AddIndex(33);
		mesh->AddIndex(0); mesh->AddIndex(35); mesh->AddIndex(34);
		mesh->AddIndex(0); mesh->AddIndex(36); mesh->AddIndex(35);
		mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(36);
}


void GeometryUtility::CreateCircle(Mesh<VertexColor>* mesh)
{
	float angle = static_cast<float>((2 * D3DX_PI) / 36);
	D3DXVECTOR3 position[37];
	for (int i = 0; i <= 36; i++)
	{
		position[i].x = cosf(i * angle);
		position[i].y = sinf(i * angle);
		position[i].z = 0.0f;


	}
	mesh->AddVertex(VertexColor(0.0f, 0.0f, 0.0f,0,0,0,1));//0
	mesh->AddVertex(VertexColor(position[0].x, position[0].y, 0.0f, 0, 0, 0, 1));//1
	mesh->AddVertex(VertexColor(position[1].x, position[1].y, 0.0f, 0, 0, 0, 1));//2
	mesh->AddVertex(VertexColor(position[2].x, position[2].y, 0.0f, 0, 0, 0, 1));//3
	mesh->AddVertex(VertexColor(position[3].x, position[3].y, 0.0f, 0, 0, 0, 1));//4
	mesh->AddVertex(VertexColor(position[4].x, position[4].y, 0.0f, 0, 0, 0, 1));//5
	mesh->AddVertex(VertexColor(position[5].x, position[5].y, 0.0f, 0, 0, 0, 1));//6
	mesh->AddVertex(VertexColor(position[6].x, position[6].y, 0.0f, 0, 0, 0, 1));//7
	mesh->AddVertex(VertexColor(position[7].x, position[7].y, 0.0f, 0, 0, 0, 1));//8
	mesh->AddVertex(VertexColor(position[8].x, position[8].y, 0.0f, 0, 0, 0, 1));//9
	mesh->AddVertex(VertexColor(position[9].x, position[9].y, 0.0f, 0, 0, 0, 1));//10
	mesh->AddVertex(VertexColor(position[10].x, position[10].y, 0.0f, 0, 0, 0, 1));//11
	mesh->AddVertex(VertexColor(position[11].x, position[11].y, 0.0f, 0, 0, 0, 1));//12
	mesh->AddVertex(VertexColor(position[12].x, position[12].y, 0.0f, 0, 0, 0, 1));//13
	mesh->AddVertex(VertexColor(position[13].x, position[13].y, 0.0f, 0, 0, 0, 1));//14
	mesh->AddVertex(VertexColor(position[14].x, position[14].y, 0.0f, 0, 0, 0, 1));//15
	mesh->AddVertex(VertexColor(position[15].x, position[15].y, 0.0f, 0, 0, 0, 1));//16
	mesh->AddVertex(VertexColor(position[16].x, position[16].y, 0.0f, 0, 0, 0, 1));//17
	mesh->AddVertex(VertexColor(position[17].x, position[17].y, 0.0f, 0, 0, 0, 1));//18
	mesh->AddVertex(VertexColor(position[18].x, position[18].y, 0.0f, 0, 0, 0, 1));//19
	mesh->AddVertex(VertexColor(position[19].x, position[19].y, 0.0f, 0, 0, 0, 1));//20
	mesh->AddVertex(VertexColor(position[20].x, position[20].y, 0.0f, 0, 0, 0, 1));//21
	mesh->AddVertex(VertexColor(position[21].x, position[21].y, 0.0f, 0, 0, 0, 1));//22
	mesh->AddVertex(VertexColor(position[22].x, position[22].y, 0.0f, 0, 0, 0, 1));//23
	mesh->AddVertex(VertexColor(position[23].x, position[23].y, 0.0f, 0, 0, 0, 1));//24
	mesh->AddVertex(VertexColor(position[24].x, position[24].y, 0.0f, 0, 0, 0, 1));//25
	mesh->AddVertex(VertexColor(position[25].x, position[25].y, 0.0f, 0, 0, 0, 1));//26
	mesh->AddVertex(VertexColor(position[26].x, position[26].y, 0.0f, 0, 0, 0, 1));//27
	mesh->AddVertex(VertexColor(position[27].x, position[27].y, 0.0f, 0, 0, 0, 1));//28
	mesh->AddVertex(VertexColor(position[28].x, position[28].y, 0.0f, 0, 0, 0, 1));//29
	mesh->AddVertex(VertexColor(position[29].x, position[29].y, 0.0f, 0, 0, 0, 1));//30
	mesh->AddVertex(VertexColor(position[30].x, position[30].y, 0.0f, 0, 0, 0, 1));//31
	mesh->AddVertex(VertexColor(position[31].x, position[31].y, 0.0f, 0, 0, 0, 1));//32
	mesh->AddVertex(VertexColor(position[32].x, position[32].y, 0.0f, 0, 0, 0, 1));//33
	mesh->AddVertex(VertexColor(position[33].x, position[33].y, 0.0f, 0, 0, 0, 1));//34
	mesh->AddVertex(VertexColor(position[34].x, position[34].y, 0.0f, 0, 0, 0, 1));//35
	mesh->AddVertex(VertexColor(position[35].x, position[35].y, 0.0f, 0, 0, 0, 1));//35
	mesh->AddVertex(VertexColor(position[36].x, position[36].y, 0.0f,0,0,0,1));//36


	mesh->AddIndex(0); mesh->AddIndex(2); mesh->AddIndex(1);
	mesh->AddIndex(0); mesh->AddIndex(3); mesh->AddIndex(2);
	mesh->AddIndex(0); mesh->AddIndex(4); mesh->AddIndex(3);
	mesh->AddIndex(0); mesh->AddIndex(5); mesh->AddIndex(4);
	mesh->AddIndex(0); mesh->AddIndex(6); mesh->AddIndex(5);
	mesh->AddIndex(0); mesh->AddIndex(7); mesh->AddIndex(6);
	mesh->AddIndex(0); mesh->AddIndex(8); mesh->AddIndex(7);
	mesh->AddIndex(0); mesh->AddIndex(9); mesh->AddIndex(8);
	mesh->AddIndex(0); mesh->AddIndex(10); mesh->AddIndex(9);
	mesh->AddIndex(0); mesh->AddIndex(11); mesh->AddIndex(10);
	mesh->AddIndex(0); mesh->AddIndex(12); mesh->AddIndex(11);
	mesh->AddIndex(0); mesh->AddIndex(13); mesh->AddIndex(12);
	mesh->AddIndex(0); mesh->AddIndex(14); mesh->AddIndex(13);
	mesh->AddIndex(0); mesh->AddIndex(15); mesh->AddIndex(14);
	mesh->AddIndex(0); mesh->AddIndex(16); mesh->AddIndex(15);
	mesh->AddIndex(0); mesh->AddIndex(17); mesh->AddIndex(16);
	mesh->AddIndex(0); mesh->AddIndex(18); mesh->AddIndex(17);
	mesh->AddIndex(0); mesh->AddIndex(19); mesh->AddIndex(18);
	mesh->AddIndex(0); mesh->AddIndex(20); mesh->AddIndex(19);
	mesh->AddIndex(0); mesh->AddIndex(21); mesh->AddIndex(20);
	mesh->AddIndex(0); mesh->AddIndex(22); mesh->AddIndex(21);
	mesh->AddIndex(0); mesh->AddIndex(23); mesh->AddIndex(22);
	mesh->AddIndex(0); mesh->AddIndex(24); mesh->AddIndex(23);
	mesh->AddIndex(0); mesh->AddIndex(25); mesh->AddIndex(24);
	mesh->AddIndex(0); mesh->AddIndex(26); mesh->AddIndex(25);
	mesh->AddIndex(0); mesh->AddIndex(27); mesh->AddIndex(26);
	mesh->AddIndex(0); mesh->AddIndex(28); mesh->AddIndex(27);
	mesh->AddIndex(0); mesh->AddIndex(29); mesh->AddIndex(28);
	mesh->AddIndex(0); mesh->AddIndex(30); mesh->AddIndex(29);
	mesh->AddIndex(0); mesh->AddIndex(31); mesh->AddIndex(30);
	mesh->AddIndex(0); mesh->AddIndex(32); mesh->AddIndex(31);
	mesh->AddIndex(0); mesh->AddIndex(33); mesh->AddIndex(32);
	mesh->AddIndex(0); mesh->AddIndex(34); mesh->AddIndex(33);
	mesh->AddIndex(0); mesh->AddIndex(35); mesh->AddIndex(34);
	mesh->AddIndex(0); mesh->AddIndex(36); mesh->AddIndex(35);
	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(36);
}

void GeometryUtility::CreateCircle(Mesh<VertexTexture>* mesh)
{
	float angle = static_cast<float>((2 * D3DX_PI) / 36);
	D3DXVECTOR3 position[37];
	for (int i = 0; i <= 36; i++)
	{
		position[i].x = cosf(i * angle);
		position[i].y = sinf(i * angle);
		position[i].z = 0.0f;

		
	}
	mesh->AddVertex(VertexTexture(0.0f, 0.0f, 0.0f,0,0));//0
		mesh->AddVertex(VertexTexture(position[0].x, position[0].y, 0.0f,0,0));//1
		mesh->AddVertex(VertexTexture(position[1].x, position[1].y, 0.0f,0, 0));//2
		mesh->AddVertex(VertexTexture(position[2].x, position[2].y, 0.0f,0, 0));//3
		mesh->AddVertex(VertexTexture(position[3].x, position[3].y, 0.0f,0, 0));//4
		mesh->AddVertex(VertexTexture(position[4].x, position[4].y, 0.0f,0, 0));//5
		mesh->AddVertex(VertexTexture(position[5].x, position[5].y, 0.0f,0, 0));//6
		mesh->AddVertex(VertexTexture(position[6].x, position[6].y, 0.0f, 0, 0));//7
		mesh->AddVertex(VertexTexture(position[7].x, position[7].y, 0.0f, 0, 0));//8
		mesh->AddVertex(VertexTexture(position[8].x, position[8].y, 0.0f, 0, 0));//9
		mesh->AddVertex(VertexTexture(position[9].x, position[9].y, 0.0f, 0, 0));//10
		mesh->AddVertex(VertexTexture(position[10].x, position[10].y, 0.0f, 0, 0));//11
		mesh->AddVertex(VertexTexture(position[11].x, position[11].y, 0.0f, 0, 0));//12
		mesh->AddVertex(VertexTexture(position[12].x, position[12].y, 0.0f, 0, 0));//13
		mesh->AddVertex(VertexTexture(position[13].x, position[13].y, 0.0f, 0, 0));//14
		mesh->AddVertex(VertexTexture(position[14].x, position[14].y, 0.0f, 0, 0));//15
		mesh->AddVertex(VertexTexture(position[15].x, position[15].y, 0.0f, 0, 0));//16
		mesh->AddVertex(VertexTexture(position[16].x, position[16].y, 0.0f, 0, 0));//17
		mesh->AddVertex(VertexTexture(position[17].x, position[17].y, 0.0f, 0, 0));//18
		mesh->AddVertex(VertexTexture(position[18].x, position[18].y, 0.0f, 0, 0));//19
		mesh->AddVertex(VertexTexture(position[19].x, position[19].y, 0.0f, 0, 0));//20
		mesh->AddVertex(VertexTexture(position[20].x, position[20].y, 0.0f, 0, 0));//21
		mesh->AddVertex(VertexTexture(position[21].x, position[21].y, 0.0f, 0, 0));//22
		mesh->AddVertex(VertexTexture(position[22].x, position[22].y, 0.0f, 0, 0));//23
		mesh->AddVertex(VertexTexture(position[23].x, position[23].y, 0.0f, 0, 0));//24
		mesh->AddVertex(VertexTexture(position[24].x, position[24].y, 0.0f, 0, 0));//25
		mesh->AddVertex(VertexTexture(position[25].x, position[25].y, 0.0f, 0, 0));//26
		mesh->AddVertex(VertexTexture(position[26].x, position[26].y, 0.0f, 0, 0));//27
		mesh->AddVertex(VertexTexture(position[27].x, position[27].y, 0.0f, 0, 0));//28
		mesh->AddVertex(VertexTexture(position[28].x, position[28].y, 0.0f, 0, 0));//29
		mesh->AddVertex(VertexTexture(position[29].x, position[29].y, 0.0f, 0, 0));//30
		mesh->AddVertex(VertexTexture(position[30].x, position[30].y, 0.0f, 0, 0));//31
		mesh->AddVertex(VertexTexture(position[31].x, position[31].y, 0.0f, 0, 0));//32
		mesh->AddVertex(VertexTexture(position[32].x, position[32].y, 0.0f, 0, 0));//33
		mesh->AddVertex(VertexTexture(position[33].x, position[33].y, 0.0f, 0, 0));//34
		mesh->AddVertex(VertexTexture(position[34].x, position[34].y, 0.0f, 0, 0));//35
		mesh->AddVertex(VertexTexture(position[35].x, position[35].y, 0.0f, 0, 0));//35
		mesh->AddVertex(VertexTexture(position[36].x, position[36].y, 0.0f, 0, 0));//36
		
		
		mesh->AddIndex(0); mesh->AddIndex(2); mesh->AddIndex(1);
		mesh->AddIndex(0); mesh->AddIndex(3); mesh->AddIndex(2);
		mesh->AddIndex(0); mesh->AddIndex(4); mesh->AddIndex(3);
		mesh->AddIndex(0); mesh->AddIndex(5); mesh->AddIndex(4);
		mesh->AddIndex(0); mesh->AddIndex(6); mesh->AddIndex(5);
		mesh->AddIndex(0); mesh->AddIndex(7); mesh->AddIndex(6);
		mesh->AddIndex(0); mesh->AddIndex(8); mesh->AddIndex(7);
		mesh->AddIndex(0); mesh->AddIndex(9); mesh->AddIndex(8);
		mesh->AddIndex(0); mesh->AddIndex(10); mesh->AddIndex(9);
		mesh->AddIndex(0); mesh->AddIndex(11); mesh->AddIndex(10);
		mesh->AddIndex(0); mesh->AddIndex(12); mesh->AddIndex(11);
		mesh->AddIndex(0); mesh->AddIndex(13); mesh->AddIndex(12);
		mesh->AddIndex(0); mesh->AddIndex(14); mesh->AddIndex(13);
		mesh->AddIndex(0); mesh->AddIndex(15); mesh->AddIndex(14);
		mesh->AddIndex(0); mesh->AddIndex(16); mesh->AddIndex(15);
		mesh->AddIndex(0); mesh->AddIndex(17); mesh->AddIndex(16);
		mesh->AddIndex(0); mesh->AddIndex(18); mesh->AddIndex(17);
		mesh->AddIndex(0); mesh->AddIndex(19); mesh->AddIndex(18);
		mesh->AddIndex(0); mesh->AddIndex(20); mesh->AddIndex(19);
		mesh->AddIndex(0); mesh->AddIndex(21); mesh->AddIndex(20);
		mesh->AddIndex(0); mesh->AddIndex(22); mesh->AddIndex(21);
		mesh->AddIndex(0); mesh->AddIndex(23); mesh->AddIndex(22);
		mesh->AddIndex(0); mesh->AddIndex(24); mesh->AddIndex(23);
		mesh->AddIndex(0); mesh->AddIndex(25); mesh->AddIndex(24);
		mesh->AddIndex(0); mesh->AddIndex(26); mesh->AddIndex(25);
		mesh->AddIndex(0); mesh->AddIndex(27); mesh->AddIndex(26);
		mesh->AddIndex(0); mesh->AddIndex(28); mesh->AddIndex(27);
		mesh->AddIndex(0); mesh->AddIndex(29); mesh->AddIndex(28);
		mesh->AddIndex(0); mesh->AddIndex(30); mesh->AddIndex(29);
		mesh->AddIndex(0); mesh->AddIndex(31); mesh->AddIndex(30);
		mesh->AddIndex(0); mesh->AddIndex(32); mesh->AddIndex(31);
		mesh->AddIndex(0); mesh->AddIndex(33); mesh->AddIndex(32);
		mesh->AddIndex(0); mesh->AddIndex(34); mesh->AddIndex(33);
		mesh->AddIndex(0); mesh->AddIndex(35); mesh->AddIndex(34);
		mesh->AddIndex(0); mesh->AddIndex(36); mesh->AddIndex(35);
		mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(36);

}

