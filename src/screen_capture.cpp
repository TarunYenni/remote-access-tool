#include "screen_capture.h"
#include <iostream>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

ScreenCapture::ScreenCapture() {
    Initialize();
}

ScreenCapture::~ScreenCapture() {
    if (deskDupl) {
        deskDupl->Release();
    }
}

void ScreenCapture::Initialize() {
    HRESULT hr;
    Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
    Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
    Microsoft::WRL::ComPtr<IDXGIOutput> dxgiOutput;
    Microsoft::WRL::ComPtr<IDXGIOutput1> dxgiOutput1;

    // Create D3D11 Device
    hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, 
                           D3D11_SDK_VERSION, &d3dDevice, nullptr, &d3dContext);
    if (FAILED(hr)) {
        std::cerr << "Failed to create D3D11 device!" << std::endl;
        return;
    }

    // Get DXGI Device
    hr = d3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(dxgiDevice.GetAddressOf()));
    if (FAILED(hr)) {
        std::cerr << "Failed to get DXGI device!" << std::endl;
        return;
    }

    // Get DXGI Adapter
    hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(dxgiAdapter.GetAddressOf()));
    if (FAILED(hr)) {
        std::cerr << "Failed to get DXGI adapter!" << std::endl;
        return;
    }

    // Get DXGI Output
    hr = dxgiAdapter->EnumOutputs(0, dxgiOutput.GetAddressOf());
    if (FAILED(hr)) {
        std::cerr << "Failed to enumerate outputs!" << std::endl;
        return;
    }

    // Get DXGI Output 1
    hr = dxgiOutput->QueryInterface(__uuidof(IDXGIOutput1), reinterpret_cast<void**>(dxgiOutput1.GetAddressOf()));
    if (FAILED(hr)) {
        std::cerr << "Failed to get DXGI Output 1!" << std::endl;
        return;
    }

    // Duplicate Output
    hr = dxgiOutput1->DuplicateOutput(d3dDevice.Get(), &deskDupl);
    if (FAILED(hr)) {
        std::cerr << "Failed to duplicate output!" << std::endl;
        return;
    }

    std::cout << "Screen capture initialized!" << std::endl;
}

bool ScreenCapture::CaptureFrame() {
    Microsoft::WRL::ComPtr<IDXGIResource> pDesktopResource;
    DXGI_OUTDUPL_FRAME_INFO frameInfo;
    HRESULT hr = deskDupl->AcquireNextFrame(1000, &frameInfo, &pDesktopResource);

    if (FAILED(hr)) {
        std::cerr << "⚠ No new frame available." << std::endl;
        return false;
    }

    std::cout << "Captured a frame!" << std::endl;
    deskDupl->ReleaseFrame();
    return true;
}
