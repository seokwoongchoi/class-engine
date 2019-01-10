#pragma once
//버퍼
//를 만들려면 C^Dll - BUFFEtDESC 구조체와 M D l 1_SUBRES0URCE_DATA 구조체
//를 채워서 ID3DllDevice : : CreateBuf fer를 호줄해야 한다.생성된 정점 버퍼는
//ID3DllDeviceContext : : IASetVertexBuf fers 메서드를 이용해서 입력 조립기
//	단계에 묶고) 색인 버퍼는 IMDllDeviceContext : : IASetlndexBuf fer 메서드를
//	이용해서 묶는다.색인화되지 않은 기하구조는 ID3DllDeviceContext : : Draw 메서
//	드로 그리고，색인화된 기하구조는 ID3DllDeviceContext : : Drawlndexed 메서드
//	로그린다.

class VertexBuffer //정점을 만들면 버텍스 버퍼로 만들고 바인드 파이프라인 함수로 파이프라인에 맵핑시킨다.
{
public:
	VertexBuffer(class Context* context);
	virtual ~VertexBuffer();
	
	template<typename T>
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);//DEFAULT는 
	//내가 무엇인가를 넣으면 그것을 적용하고 안넣으면 디폴트된다.
	void Clear();

	void* Map();//처음에 버텍스를 수정할때 updatesubresorce함수를 이용해야 파이프라인에 적용된다.
	//fense개념
	void Unmap();

	void BindPipeline();

private:
	class Graphics* graphics;

	ID3D11Buffer* vbuffer; //정점들을 버퍼형태로 바꿔서 파이프라인에 묶는다.
	uint stride;
	uint offset; //정점 시작점 번호
};

template<typename T> //템플릿함수라서 헤더에 생성됬다.
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE & usage)
{
	assert(!vertices.empty());//만약에 T가 비어있으면 버텍스버퍼를 만들필요가 없으니까 assert로 막는다.
	//vertices.empty 엠티면 트루 어썰트안에께 트루면 그냥패스니까 어썰트안에있는게 펄스로만들어야한다.
	
	Clear(); //클리어로 초기화

	stride = sizeof(T); //T가들어오는 만큼의 사이즈
	

	D3D11_BUFFER_DESC bufferDesc;//ID3D11Buffer로 만들었다->DESC로 연결된다
	
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC)); //USAGE->이버퍼를 어떻게 사용하는가에대한 정보 
	
	if (usage == D3D11_USAGE_DYNAMIC)
	{
		bufferDesc.Usage = usage; //USAGE를 읽기만 할수있게 이프문으로 나누었다.
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
		bufferDesc.Usage = usage;

	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(T)*vertices.size();

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = vertices.data();//자기가 가지고있는 배열의 시작포인트를 넘긴다->&vertices[0]; 버티시즈의 0번의 배열주소
//와 같다	
	HRESULT hr = graphics->GetDevice()->CreateBuffer
	(
		&bufferDesc,
		&subData,
		&vbuffer
	);
	assert(SUCCEEDED(hr));
}
