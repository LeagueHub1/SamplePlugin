#include "pch.h"

extern "C" __declspec(dllexport) bool onLoadSDK(SDK* sdk)
{
	sdk->initialize();

	menuManager->createMenu("testmenu", "testmenu");

	return true;
}


