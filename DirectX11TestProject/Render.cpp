#include "Render.h"
#include "Direct3d.h"

Render::Render(const HWND hWnd) {
	this->d3d = std::make_shared<Direct3d>(hWnd);
}

void Render::init(void) {
	// ���f�����_�f�[�^�쐬
	const float w = 0.5f;
	const VERTEX3D vx[] = {
		// (x, y, z), (r, g, b, a)
		// ����
		{ -w,  w, -w, 1, 1, 1, 1 },
		{  w,  w, -w, 1, 1, 1, 1 },
		{  w, -w, -w, 1, 1, 1, 1 },

		{  w, -w, -w, 1, 1, 1, 1 },
		{ -w, -w, -w, 1, 1, 1, 1 },
		{ -w,  w, -w, 1, 1, 1, 1 },

		// ��
		{ -w,  w, w, 1, 1, 0, 1 },
		{  w,  w, w, 1, 1, 0, 1 },
		{  w, -w, w, 1, 1, 0, 1 },

		{  w, -w, w, 1, 1, 0, 1 },
		{ -w, -w, w, 1, 1, 0, 1 },
		{ -w,  w, w, 1, 1, 0, 1 },

		// ��
		{ -w,  w, w, 1, 0, 1, 1 },
		{ -w,  w,-w, 1, 0, 1, 1 },
		{ -w, -w,-w, 1, 0, 1, 1 },

		{ -w, -w,-w, 1, 0, 1, 1 },
		{ -w, -w, w, 1, 0, 1, 1 },
		{ -w,  w, w, 1, 0, 1, 1 },

		// �E
		{  w,  w,-w, 1, 0, 0, 1 },
		{  w,  w, w, 1, 0, 0, 1 },
		{  w, -w, w, 1, 0, 0, 1 },

		{  w, -w, w, 1, 0, 0, 1 },
		{  w, -w,-w, 1, 0, 0, 1 },
		{  w,  w,-w, 1, 0, 0, 1 },

		// ��
		{ -w,  w,  w, 0, 1, 1, 1 },
		{  w,  w,  w, 0, 1, 1, 1 },
		{  w,  w, -w, 0, 1, 1, 1 },

		{  w,  w, -w, 0, 1, 1, 1 },
		{ -w,  w, -w, 0, 1, 1, 1 },
		{ -w,  w,  w, 0, 1, 1, 1 },

		// ��
		{ -w, -w, -w, 0, 1, 0, 1 },
		{  w, -w, -w, 0, 1, 0, 1 },
		{  w, -w,  w, 0, 1, 0, 1 },

		{  w, -w,  w, 0, 1, 0, 1 },
		{ -w, -w,  w, 0, 1, 0, 1 },
		{ -w, -w, -w, 0, 1, 0, 1 },

	};

	const unsigned int numVertex = sizeof(vx) / sizeof(VERTEX3D); // ���_�����v�Z

	// ���f���p�̒��_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vx);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// �o�b�t�@�̏����l�w��
	D3D11_SUBRESOURCE_DATA initialVertexData;
	// ���_�o�b�t�@�̏����l
	initialVertexData.pSysMem = vx;
	// ���_�o�b�t�@�ł͎g�p���Ȃ�
	initialVertexData.SysMemPitch = 0;
	initialVertexData.SysMemSlicePitch = 0;

	// ���_�o�b�t�@�̍쐬
	HRESULT hr = this->d3d->device->CreateBuffer(&bufferDesc, &initialVertexData, this->d3d->vertexBuffer.GetAddressOf());


	// �`��Ɏg�����_�o�b�t�@���w�肷��
	UINT strides = sizeof(VERTEX3D);
	UINT offsets = 0;
	d3d->context->IASetVertexBuffers(0, 1, this->d3d->vertexBuffer.GetAddressOf(), &strides, &offsets);
}

void Render::update(void) {

}

void Render::draw(void) const {
	// ��ʂ̓h��Ԃ�
	// RGBA
	constexpr float color[4] = { 0.5f, 0.5f , 0.5f , 1.0f };
	//this->d3d->context->ClearRenderTargetView(this->d3d->renderTarget.Get(), color);

	this->d3d->context->Draw(36, 0);

	// �_�u���o�b�t�@�̐؂�ւ�
	this->d3d->swapChain->Present(0, 0);
}
