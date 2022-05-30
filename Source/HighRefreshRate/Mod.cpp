#include "Config.h"

bool* vsyncAddr;
uint32_t* capAddr;

// v1.0.0: 0x1402B6CA0
SIG_SCAN
(
	sigSetFramerate,
	"\x48\x83\xEC\x28\x33\xC0\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x0F\x57\xC0\x48\x89\x05\x00\x00\x00\x00\xF3\x0F\x11\x05\x00\x00\x00\x00\x89\x05\x00\x00\x00\x00\x88\x05\x00\x00\x00\x00\x88\x05\x00\x00\x00\x00\x89\x05\x00\x00\x00\x00\x89\x05\x00\x00\x00\x00\x88\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x48\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xC6\x05\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x75\x2C\xE8\x00\x00\x00\x00\x84\xC0\x75\x07\xE8\x00\x00\x00\x00\xEB\x1C\xE8\x00\x00\x00\x00\x44\x8B\xC8\xE8\x00\x00\x00\x00\x8B\xD0\x41\x8B\xC9\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8B\xC8\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x33\xD2\x33\xC9\xFF\x15\x00\x00\x00\x00\x48\x8D\x0D\x00\x00\x00\x00\x48\x83\xC4\x28\xE9\x00\x00\x00\x00",
	"xxxxxxxx????????xxxxxx????xxxx????xx????xx????xx????xx????xx????xx????xxx????xxx????xxx????xxx????xxx????xxx????xxx????xxx????xxx????xxx????xxx????xxx????xx????????xx????????xxx????????xx????????xx????????xx?????x????x????xxxxx????xxxxx????xxx????xxxx????xxxxxx????x????x????xxxx????x????x????x????x????x????x????x????x????x????xxxxxx????xxx????xxxxx????"
);

// v1.0.0: 0x1402B6EF0
HOOK(void, __fastcall, _SetFramerate, (char*)sigSetFramerate() + 0x250)
{
	// v1.0.0: 0x1414B2A74 and 0x1414B2A78
	*(bool*)vsyncAddr = Config::enableVSync;
	*(uint32_t*)capAddr = Config::framerateCap;
}

extern "C" __declspec(dllexport) void Init()
{
	Config::init();

	uint8_t* instrAddr = (uint8_t*)sigSetFramerate() + 0x250;
	vsyncAddr = (bool*)(instrAddr + readUnalignedU32(instrAddr + 0x2) + 0x6);
	instrAddr += 0x6;
	capAddr = (uint32_t*)(instrAddr + readUnalignedU32(instrAddr + 0x2) + 0xA);

	INSTALL_HOOK(_SetFramerate);
}
