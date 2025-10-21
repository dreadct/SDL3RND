#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR pCmdLine,
	_In_ int nCmdShow
) {
    std::cout << "Hello SDL3 on Windows" << std::endl;
    return 0;
}
