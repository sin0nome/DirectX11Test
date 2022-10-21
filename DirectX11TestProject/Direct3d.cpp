#include "Direct3d.h"
#include <stdexcept>
#include "vs.h"
#include "ps.h"

// DirectX11のライブラリをリンク指定
#pragma comment (lib, "d3d11.lib")

std::optional<Direct3d*> Direct3d::instance;


void Direct3d::createDevice(void) noexcept(false) {
	UINT flags = 0;
	// Graphic Toolを使ってデバッグを行う場合は、下の行のコメントを外してデバッグモードでデバイスを作成する。
	flags |= D3D11_CREATE_DEVICE_DEBUG;

	D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL level;

	RECT                rect;
	DXGI_SWAP_CHAIN_DESC scDesc;

	// ウインドウのクライアント領域（実際に描画できる範囲）のサイズを取得
	GetClientRect(this->handle, &rect);
	ZeroMemory(&scDesc, sizeof(scDesc));

	this->screenWidth = (UINT)(rect.right - rect.left);
	this->screenHeight = (UINT)(rect.bottom - rect.top);

	scDesc.BufferCount = 1;
	scDesc.BufferDesc.Width = this->screenWidth;
	scDesc.BufferDesc.Height = this->screenHeight;
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.OutputWindow = this->handle;
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;
	scDesc.Windowed = TRUE; // ウインドウモードとフルスクリーンモード切り替え

	HRESULT  hr;
	// DirectX11デバイス、コンテキスト、スワップチェインの作成
	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		flags,
		pLevels,
		1,
		D3D11_SDK_VERSION,
		&scDesc,
		this->swapChain.GetAddressOf(),
		this->device.GetAddressOf(),
		&level,
		this->context.GetAddressOf());

}

void Direct3d::createRenderTarget(void) noexcept(false) {
	// バックバッファ取得
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
	HRESULT hr;
	hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)pBackBuffer.GetAddressOf());

	if (FAILED(hr)) {
		throw std::runtime_error("failed to create BuckBuffer");
	}

	// レンダーターゲットビューを作成
	hr = this->device->CreateRenderTargetView(pBackBuffer.Get(), NULL, this->renderTarget.GetAddressOf());
	if (FAILED(hr)) {
		throw std::runtime_error("failed to create RenderTargetView");
	}

	// レンダリングターゲットを設定　今は2DなのでZバッファ無効にしておく
	this->context->OMSetRenderTargets(1, this->renderTarget.GetAddressOf(), NULL);
}

void Direct3d::createShader(void) noexcept(false) {
	HRESULT hr;
	//頂点シェーダー生成
	hr = this->device->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, this->vertexShader.GetAddressOf());
	if (FAILED(hr)) {
		throw std::runtime_error("failed to create VertexShader");
	}

	//ピクセルシェーダー生成
	hr = this->device->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, this->pixelShader.GetAddressOf());
	if (FAILED(hr)) {
		throw std::runtime_error("failed to create PixelShader");
	}

	// 頂点シェーダーのパラメータセット
	this->context->VSSetShader(this->vertexShader.Get(), NULL, 0);
	// ピクセルシェーダーのパラメータセット
	this->context->PSSetShader(this->pixelShader.Get(), NULL, 0);

	//頂点レイアウト作成　※頂点データを変更したら、この配列も変更する
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },// xy
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },// rgba
	};

	hr = this->device->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), g_vs_main, sizeof(g_vs_main), this->inputLayout.GetAddressOf());
	if (FAILED(hr)) {
		throw std::runtime_error("failed to create InputLayout");
	}

	// 頂点レイアウトをセット
	this->context->IASetInputLayout(this->inputLayout.Get());
	// トポロジー（プリミティブタイプ）をセット
	this->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リストを指定
}

void Direct3d::createViewPort(void) noexcept(false) {
	//ビューポート設定
	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = this->screenWidth;
	viewport.Height = this->screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	this->context->RSSetViewports(1, &viewport);
}

Direct3d::Direct3d(const HWND hWnd) : handle(hWnd) {
	if (Direct3d::instance.has_value()) {
		return;
	}

	Direct3d::instance = this;

	try {
		this->createDevice();

		this->createRenderTarget();

		this->createShader();

		this->createViewPort();

	} catch (const std::exception& e) {

	}

}
