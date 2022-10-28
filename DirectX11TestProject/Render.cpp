#include "Render.h"
#include "Direct3d.h"

Render::Render(const HWND hWnd) {
	this->d3d = std::make_shared<Direct3d>(hWnd);
}

void Render::init(void) {
	// モデル頂点データ作成
	const float w = 0.5f;
	const VERTEX3D vx[] = {
		// (x, y, z), (r, g, b, a)
		// 正面
		{ -w,  w, -w, 1, 1, 1, 1 },
		{  w,  w, -w, 1, 1, 1, 1 },
		{  w, -w, -w, 1, 1, 1, 1 },

		{  w, -w, -w, 1, 1, 1, 1 },
		{ -w, -w, -w, 1, 1, 1, 1 },
		{ -w,  w, -w, 1, 1, 1, 1 },

		// 奥
		{ -w,  w, w, 1, 1, 0, 1 },
		{  w,  w, w, 1, 1, 0, 1 },
		{  w, -w, w, 1, 1, 0, 1 },

		{  w, -w, w, 1, 1, 0, 1 },
		{ -w, -w, w, 1, 1, 0, 1 },
		{ -w,  w, w, 1, 1, 0, 1 },

		// 左
		{ -w,  w, w, 1, 0, 1, 1 },
		{ -w,  w,-w, 1, 0, 1, 1 },
		{ -w, -w,-w, 1, 0, 1, 1 },

		{ -w, -w,-w, 1, 0, 1, 1 },
		{ -w, -w, w, 1, 0, 1, 1 },
		{ -w,  w, w, 1, 0, 1, 1 },

		// 右
		{  w,  w,-w, 1, 0, 0, 1 },
		{  w,  w, w, 1, 0, 0, 1 },
		{  w, -w, w, 1, 0, 0, 1 },

		{  w, -w, w, 1, 0, 0, 1 },
		{  w, -w,-w, 1, 0, 0, 1 },
		{  w,  w,-w, 1, 0, 0, 1 },

		// 上
		{ -w,  w,  w, 0, 1, 1, 1 },
		{  w,  w,  w, 0, 1, 1, 1 },
		{  w,  w, -w, 0, 1, 1, 1 },

		{  w,  w, -w, 0, 1, 1, 1 },
		{ -w,  w, -w, 0, 1, 1, 1 },
		{ -w,  w,  w, 0, 1, 1, 1 },

		// 下
		{ -w, -w, -w, 0, 1, 0, 1 },
		{  w, -w, -w, 0, 1, 0, 1 },
		{  w, -w,  w, 0, 1, 0, 1 },

		{  w, -w,  w, 0, 1, 0, 1 },
		{ -w, -w,  w, 0, 1, 0, 1 },
		{ -w, -w, -w, 0, 1, 0, 1 },

	};

	const unsigned int numVertex = sizeof(vx) / sizeof(VERTEX3D); // 頂点数を計算

	// モデル用の頂点バッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vx);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// バッファの初期値指定
	D3D11_SUBRESOURCE_DATA initialVertexData;
	// 頂点バッファの初期値
	initialVertexData.pSysMem = vx;
	// 頂点バッファでは使用しない
	initialVertexData.SysMemPitch = 0;
	initialVertexData.SysMemSlicePitch = 0;

	// 頂点バッファの作成
	HRESULT hr = this->d3d->device->CreateBuffer(&bufferDesc, &initialVertexData, this->d3d->vertexBuffer.GetAddressOf());


	// 描画に使う頂点バッファを指定する
	UINT strides = sizeof(VERTEX3D);
	UINT offsets = 0;
	d3d->context->IASetVertexBuffers(0, 1, this->d3d->vertexBuffer.GetAddressOf(), &strides, &offsets);
}

void Render::update(void) {

}

void Render::draw(void) const {
	// 画面の塗りつぶし
	// RGBA
	constexpr float color[4] = { 0.5f, 0.5f , 0.5f , 1.0f };
	//this->d3d->context->ClearRenderTargetView(this->d3d->renderTarget.Get(), color);

	this->d3d->context->Draw(36, 0);

	// ダブルバッファの切り替え
	this->d3d->swapChain->Present(0, 0);
}
