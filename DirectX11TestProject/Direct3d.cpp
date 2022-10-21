#include "Direct3d.h"
#include <stdexcept>
#include "vs.h"
#include "ps.h"

// DirectX11�̃��C�u�����������N�w��
#pragma comment (lib, "d3d11.lib")

std::optional<Direct3d*> Direct3d::instance;


void Direct3d::createDevice(void) noexcept(false) {
	UINT flags = 0;
	// Graphic Tool���g���ăf�o�b�O���s���ꍇ�́A���̍s�̃R�����g���O���ăf�o�b�O���[�h�Ńf�o�C�X���쐬����B
	flags |= D3D11_CREATE_DEVICE_DEBUG;

	D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL level;

	RECT                rect;
	DXGI_SWAP_CHAIN_DESC scDesc;

	// �E�C���h�E�̃N���C�A���g�̈�i���ۂɕ`��ł���͈́j�̃T�C�Y���擾
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
	scDesc.Windowed = TRUE; // �E�C���h�E���[�h�ƃt���X�N���[�����[�h�؂�ւ�

	HRESULT  hr;
	// DirectX11�f�o�C�X�A�R���e�L�X�g�A�X���b�v�`�F�C���̍쐬
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
	// �o�b�N�o�b�t�@�擾
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
	HRESULT hr;
	hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)pBackBuffer.GetAddressOf());

	if (FAILED(hr)) {
		throw std::runtime_error("failed to create BuckBuffer");
	}

	// �����_�[�^�[�Q�b�g�r���[���쐬
	hr = this->device->CreateRenderTargetView(pBackBuffer.Get(), NULL, this->renderTarget.GetAddressOf());
	if (FAILED(hr)) {
		throw std::runtime_error("failed to create RenderTargetView");
	}

	// �����_�����O�^�[�Q�b�g��ݒ�@����2D�Ȃ̂�Z�o�b�t�@�����ɂ��Ă���
	this->context->OMSetRenderTargets(1, this->renderTarget.GetAddressOf(), NULL);
}

void Direct3d::createShader(void) noexcept(false) {
	HRESULT hr;
	//���_�V�F�[�_�[����
	hr = this->device->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, this->vertexShader.GetAddressOf());
	if (FAILED(hr)) {
		throw std::runtime_error("failed to create VertexShader");
	}

	//�s�N�Z���V�F�[�_�[����
	hr = this->device->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, this->pixelShader.GetAddressOf());
	if (FAILED(hr)) {
		throw std::runtime_error("failed to create PixelShader");
	}

	// ���_�V�F�[�_�[�̃p�����[�^�Z�b�g
	this->context->VSSetShader(this->vertexShader.Get(), NULL, 0);
	// �s�N�Z���V�F�[�_�[�̃p�����[�^�Z�b�g
	this->context->PSSetShader(this->pixelShader.Get(), NULL, 0);

	//���_���C�A�E�g�쐬�@�����_�f�[�^��ύX������A���̔z����ύX����
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },// xy
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },// rgba
	};

	hr = this->device->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), g_vs_main, sizeof(g_vs_main), this->inputLayout.GetAddressOf());
	if (FAILED(hr)) {
		throw std::runtime_error("failed to create InputLayout");
	}

	// ���_���C�A�E�g���Z�b�g
	this->context->IASetInputLayout(this->inputLayout.Get());
	// �g�|���W�[�i�v���~�e�B�u�^�C�v�j���Z�b�g
	this->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g���w��
}

void Direct3d::createViewPort(void) noexcept(false) {
	//�r���[�|�[�g�ݒ�
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
