#pragma once

#include "pch.h"

class HookedDirectInput8 : public IDirectInput8 {
private:
	IDirectInput8* original;

public:
	constexpr HookedDirectInput8(IDirectInput8* original) : original(original) {
	}
	virtual ~HookedDirectInput8(void) {
	}

	ULONG	WINAPI AddRef(void) {
		return original->AddRef();
	}
	ULONG	WINAPI Release(void) {
		return original->Release();
	}
	HRESULT	WINAPI ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMS lpdiCDParams, DWORD dwFlags, LPVOID pvRefData) {
		return original->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
	}
	HRESULT	WINAPI CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8* lpDirectInputDevice, LPUNKNOWN pUnkOuter) {
		return original->CreateDevice(rguid, lpDirectInputDevice, pUnkOuter);
	}
	HRESULT	WINAPI EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags) {
		if (dwDevType == DI8DEVCLASS_GAMECTRL) {
			return original->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
		}

		auto res = original->EnumDevices(DI8DEVCLASS_KEYBOARD, lpCallback, pvRef, dwFlags);
		if (FAILED(res)) {
			return res;
		}
		return original->EnumDevices(DI8DEVCLASS_POINTER, lpCallback, pvRef, dwFlags);
	}
	HRESULT WINAPI EnumDevicesBySemantics(LPCTSTR ptszUserName, LPDIACTIONFORMAT lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCB lpCallback, LPVOID pvRef, DWORD dwFlags) {
		return original->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, lpCallback, pvRef, dwFlags);
	}
	HRESULT	WINAPI FindDevice(REFGUID rguidClass, LPCTSTR ptszName, LPGUID pguidInstance) {
		return original->FindDevice(rguidClass, ptszName, pguidInstance);
	}
	HRESULT	WINAPI GetDeviceStatus(REFGUID rguidInstance) {
		return original->GetDeviceStatus(rguidInstance);
	}
	HRESULT	WINAPI Initialize(HINSTANCE hinst, DWORD dwVersion) {
		return original->Initialize(hinst, dwVersion);
	}
	HRESULT	WINAPI QueryInterface(REFIID iid, void** ppvObject) {
		return original->QueryInterface(iid, ppvObject);
	}
	HRESULT	WINAPI RunControlPanel(HWND hwndOwner, DWORD dwFlags) {
		return original->RunControlPanel(hwndOwner, dwFlags);
	}
};
