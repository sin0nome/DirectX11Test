#pragma once


#include <d3d11.h>
#include <wrl/client.h>	
#include <optional>
#include <memory>


constexpr int ScreenWidth = 640;
constexpr int ScreenHeight = 480;

// �e�X�g�p�Ȃ̂Ńt�B�[���h�͑S��public�ɂ��Ă܂�
class Direct3d {
private:
	static std::optional<Direct3d*> instance;

	void createDevice(void) noexcept(false);
	void createRenderTarget(void) noexcept(false);
	void createShader(void) noexcept(false);
	void createViewPort(void) noexcept(false);

	const HWND handle;

	int screenWidth;
	int screenHeight;

public:

	explicit Direct3d(const HWND hWnd);
	inline static const Direct3d* getInstance(void) {
		return Direct3d::instance.value();
	}

	Microsoft::WRL::ComPtr<ID3D11Device> device;					// �f�o�C�X
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;			// �R���e�L�X�g
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;				// �X���b�v�`�F�C��
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget;	// �����_�[�^�[�Q�b�g
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;		// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;			// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;			// �C���v�b�g���C�A�E�g

	// �ȉ��V�F�[�_�֘A
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;


	/*
	ID3D11BlendState* blendAlpha;  // �A���t�@�u�����f�B���O�p�u�����h�X�e�[�g
	ID3D11SamplerState* samplerPoint; // �|�C���g�⊮�p�T���v���[
	ID3D11Texture2D*        depthStencilTexture;
	ID3D11DepthStencilView* depthStencilView;
	*/
};


struct VERTEX3D {
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float a;
};

