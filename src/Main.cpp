#include "../include/HeaderApp.hpp"
#include "../include/resource.hpp"
#include "../include/Scene.hpp"
#include "../include/GameManager.hpp"
#include "../include/ObjectGame.hpp"

int main() {
    Deb::cout("CONSOLE LAUNCHED");
    return Deb::cout(WinMain(GetModuleHandle(NULL), NULL, NULL, SW_SHOWDEFAULT));
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPInst, LPSTR pCmd, int cmdShow) {

    Sleep(120);

    LPCWSTR kNameWnd = L"テスト";
    LPCWSTR kNameWndClass = L"DX11_CLASS";
    const unsigned int kWidth = WindowSize::width;
    const unsigned int kHeight = WindowSize::height;
    const bool kWindowed = MessageBoxW(nullptr, L"フルスクリーンで起動しますか", L"確認", MB_YESNO) == IDNO;

    // D3DManager
    D3DManager* dmanager = D3DManager::getPtrD3DManager();
    dmanager->init(hInst, cmdShow, kNameWnd, kNameWndClass, kWidth, kHeight, kWindowed);

    MSG msg;

    // inputManager

    // camera
    Camera camera = Camera();
    dmanager->createCamera(kWidth, kHeight, &camera);
    camera.posZ = -20.f;
    dmanager->applyCamera(&camera);

    // input
    InputManager* imanager = InputManager::getPtrImanager();
    imanager->addKeycode(KEY::LEFT, VK_LEFT, GAMEPAD_KEYTYPE::ThumbLL, XINPUT_GAMEPAD_DPAD_LEFT);
    imanager->addKeycode(KEY::RIGHT, VK_RIGHT, GAMEPAD_KEYTYPE::ThumbLR, XINPUT_GAMEPAD_DPAD_RIGHT);
    imanager->addKeycode(KEY::UP, VK_UP, GAMEPAD_KEYTYPE::ThumbLR, XINPUT_GAMEPAD_DPAD_UP);
    imanager->addKeycode(KEY::DOWN, VK_DOWN, GAMEPAD_KEYTYPE::ThumbLR, XINPUT_GAMEPAD_DPAD_DOWN);
    imanager->addKeycode(KEY::C, 0x43, GAMEPAD_KEYTYPE::RTrigger, XINPUT_GAMEPAD_B);
    imanager->addKeycode(KEY::Z, 0x5A, GAMEPAD_KEYTYPE::LTrigger, XINPUT_GAMEPAD_A);

    // gameManager
    GameManager gmanager;
    gmanager.initManager(dmanager, imanager);

    // firstScene
    SceneStageSample* sample = new SceneStageSample();
    sample->initScene(&gmanager, dmanager);
    Deb::cout("complete init scene");
    gmanager.changeCurrent(sample);
    Deb::cout("complete change scene");

    // main loop
    float Time = 0.;
    while (true) {
        if (PeekMessageW(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                return 1;
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        } else {
            dmanager->drawBegin();
            gmanager.updateScene();
            dmanager->drawEnd();
        }
    }
    std::cout << "PROGRAM STOPPED";
    UnregisterClassW(kNameWndClass, hInst);
    return 0;
}