// DInputWrapper.cpp : Defines the exported functions for the DLL application.
//

#include "pch.h"

#include "HookedDirectInput8.h"

typedef HRESULT(WINAPI* directInput8Create_t)(HINSTANCE, DWORD, REFIID, LPVOID, LPUNKNOWN);

static auto loadOriginalDll() -> HMODULE {
	WCHAR dllpath[320];
	if (!GetSystemDirectory(dllpath, 320)) {
		return NULL;
	}
	wcsncat_s(dllpath, 320, L"\\dinput8.dll", _TRUNCATE);

	return LoadLibrary(dllpath);
}

static auto getOriginalDirectInput8Create() {
	auto dll = loadOriginalDll();
	auto ptr = GetProcAddress(dll, "DirectInput8Create");
	return reinterpret_cast<directInput8Create_t>(ptr);
}

HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter) {
	static const auto origCall = getOriginalDirectInput8Create();
	if (!origCall) {
		return E_FAIL;
	}

	IDirectInput8* origOut = nullptr;
	HRESULT res = origCall(hinst, dwVersion, riidltf, &origOut, punkOuter);
	if (FAILED(res)) {
		return res;
	}

	*ppvOut = new HookedDirectInput8(origOut);

	return res;
}
