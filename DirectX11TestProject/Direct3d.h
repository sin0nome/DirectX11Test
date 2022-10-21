#pragma once


#include <d3d11.h>
#include <wrl/client.h>	
#include <optional>
#include <memory>


constexpr int ScreenWidth = 640;
constexpr int ScreenHeight = 480;

// テスト用なのでフィールドは全てpublicにしてます
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

	Microsoft::WRL::ComPtr<ID3D11Device> device;					// デバイス
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;			// コンテキスト
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;				// スワップチェイン
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget;	// レンダーターゲット
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;		// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;			// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;			// インプットレイアウト

	// 以下シェーダ関連
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;


	/*
	ID3D11BlendState* blendAlpha;  // アルファブレンディング用ブレンドステート
	ID3D11SamplerState* samplerPoint; // ポイント補完用サンプラー
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

