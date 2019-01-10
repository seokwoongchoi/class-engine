#include "stdafx.h"
#include "Tool_Script.h"

void Tool_Script::Initialize(Context * context)
{
	this->context = context;
	filePath = "";
	bVisible = false;

	auto language = TextEditor::LanguageDefinition::AngelScript();
	{
		/*static const char* ppnames[] =
		{
		   "NULL",
		   "PM_REMOVE",
		   "ZeroMemory",
		   "DXGI_SWAP_EFFECT_DISCARD",
		   "D3D_FEATURE_LEVEL",
		   "D3D_DRIVER_TYPE_HARDWARE",
		   "WINAPI",
		   "D3D11_SDK_VERSION",
		   "assert"
		};

		static const char* ppvalues[] =
		{
		   "#define NULL ((void*)0)",
		   "#define PM_REMOVE (0x0001)",
		   "Microsoft's own memory zapper function\n(which is a macro actually)\nvoid ZeroMemory(\n\t[in] PVOID  Destination,\n\t[in] SIZE_T Length\n); ",
		   "enum DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD = 0",
		   "enum D3D_FEATURE_LEVEL",
		   "enum D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE  = ( D3D_DRIVER_TYPE_UNKNOWN + 1 )",
		   "#define WINAPI __stdcall",
		   "#define D3D11_SDK_VERSION (7)",
		   " #define assert(expression) (void)(                                                  \n"
		   "    (!!(expression)) ||                                                              \n"
		   "    (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \n"
		   " )"
		};

		for (int i = 0; i < ARRAYSIZE(ppnames); i++)
		{
			TextEditor::Identifier id;
			id.mDeclaration = ppvalues[i];
			language.mPreprocIdentifiers.insert(make_pair(string(ppnames[i]), id));
		}

		static const char* identifiers[] =
		{
		   "HWND", "HRESULT", "LPRESULT","D3D11_RENDER_TARGET_VIEW_DESC", "DXGI_SWAP_CHAIN_DESC","MSG","LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
		   "ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
		   "ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
		   "IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "TextEditor"
		};

		static const char* idecls[] =
		{
		   "typedef HWND_* HWND", "typedef long HRESULT", "typedef long* LPRESULT", "struct D3D11_RENDER_TARGET_VIEW_DESC", "struct DXGI_SWAP_CHAIN_DESC",
		   "typedef tagMSG MSG\n * Message structure","typedef LONG_PTR LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
		   "ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
		   "ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
		   "IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "class TextEditor"
		};

		for (int i = 0; i < ARRAYSIZE(identifiers); i++)
		{
			TextEditor::Identifier id;
			id.mDeclaration = string(idecls[i]);
			language.mIdentifiers.insert(make_pair(string(identifiers[i]), id));
		}*/
	}
	textEditor.SetLanguageDefinition(language);
	/*markers.insert(make_pair(11, "Error!!!!!!"));
	markers.insert(make_pair(31, "Error!!!!!!"));
	textEditor.SetErrorMarkers(markers);
	SetScript("./Editor/ImGui/TextEditor.cpp");*/
}

void Tool_Script::Render()
{
	if (!bVisible) return;

	auto cursorPos = textEditor.GetCursorPosition();

	ImGui::Begin("ScriptTool", &bVisible, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
	{
		ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
		//�ƹ��͵� ������ ù��°�������.
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save"))
				{
					auto text = textEditor.GetText();
					auto scriptname = this->filePath;
					ofstream out(scriptname);
					{
						if (out.good())
						{
							out.write(text.c_str(), text.length());
						}
					}
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				bool bReadOnly = textEditor.IsReadOnly();
				if (ImGui::MenuItem("ReadOnly Mode", nullptr, &bReadOnly))
					textEditor.SetReadOnly(bReadOnly);

				ImGui::Separator();
				if (ImGui::MenuItem("Undo", "Alt+<-", nullptr, !bReadOnly&&textEditor.CanUndo()))
					textEditor.Undo();
				if (ImGui::MenuItem("Redo", "Ctrl+Y", nullptr, !bReadOnly&&textEditor.CanRedo()))
					textEditor.Redo();

				ImGui::Separator();

				if (ImGui::MenuItem("Copy", "Ctrl+C", nullptr, textEditor.HasSelection()))
					textEditor.Copy();
				if (ImGui::MenuItem("Cut", "Ctrl+X", nullptr, !bReadOnly&&textEditor.HasSelection()))
					textEditor.Cut();
				if (ImGui::MenuItem("Delete", "Del", nullptr, !bReadOnly&&textEditor.HasSelection()))
					textEditor.Delete();
				if (ImGui::MenuItem("Paste", "Ctrl+V", nullptr, !bReadOnly&& ImGui::GetClipboardText() != nullptr))
					textEditor.Paste();

				ImGui::Separator();

				if (ImGui::MenuItem("Select All", "Ctrl+A", nullptr))
				{
					textEditor.SelectAll();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Dark"))
					textEditor.SetPalette(TextEditor::GetDarkPalette());
				if (ImGui::MenuItem("Light"))
					textEditor.SetPalette(TextEditor::GetLightPalette());
				if (ImGui::MenuItem("Retro Blue"))
					textEditor.SetPalette(TextEditor::GetRetroBluePalette());
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Text
		(
			"%6d/%-6d%6d lines |%s|%s|%s|%s",
			//���� ����,�����̵���. 3���� 6d�� ��������
			cursorPos.mLine + 1,
			cursorPos.mColumn + 1,
			textEditor.GetTotalLines(),
			textEditor.IsOverwrite() ? "Ovr" : "Ins",
			textEditor.CanUndo() ? "*" : " ",
			textEditor.GetLanguageDefinition().mName.c_str(),//���⼭���� ���� �Ÿ������
			filePath.c_str()//��θ�
		);
		textEditor.Render("ScriptTool");
	}
	//������ ��ũ�ѹٸ� ������. �޴��ٵ� ������.
	ImGui::End();
}

void Tool_Script::SetScript(const string & filePath)
{
	this->filePath = filePath;
	ifstream in(filePath); //��ǲ���Ͻ�Ʈ�� Ư���������޾Ƶ��̴°�, in�ȿ� ���ϵ����Ͱ� ����.
	if (in.good())
	{
		//������ ���������� �ߵ��Դ�
		string str((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
		//���Ͻ�Ʈ���ȿ��ִ� ���۰� ������ �������� in�� �ڷ��� ũ�⸸ŭ char�� ��ŭ�� �����͵��� ����.
		textEditor.SetText(str);
	}
}




Tool_Script::Tool_Script()
{
}

Tool_Script::~Tool_Script()
{
}
