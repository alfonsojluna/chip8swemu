#include "rom.h"

#include "chip8.h"
#include <stdint.h>
#include <stdio.h>

#ifdef _WIN32

#include <shlobj.h>
#include <commdlg.h>

#endif


static int loadRom(uint8_t* rom, size_t rom_size)
{
	chip8ResetCpu();
	
	return chip8ResetMem(rom, rom_size);
}


int romLoadDefault()
{
	uint8_t logo_rom[] = {
		0x00, 0xFF, 0x60, 0x17, 0x62, 0x20, 0xA2, 0x20,
		0x61, 0x0F, 0xD1, 0x00, 0x71, 0x10, 0xF2, 0x1E,
		0x31, 0x6F, 0x12, 0x0A, 0x12, 0x10, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 0x3C, 0x6F,
		0x7E, 0x7F, 0xE6, 0x71, 0xC0, 0x61, 0xC0, 0x61,
		0xC0, 0x61, 0xC0, 0x61, 0xE6, 0x61, 0x7E, 0x61,
		0x3C, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x18, 0x00, 0x18, 0x00, 0x00, 0x00, 0x19, 0xB8,
		0x99, 0xFC, 0x99, 0xCE, 0x99, 0x86, 0x99, 0x86,
		0x99, 0x86, 0x99, 0x86, 0x99, 0xCE, 0x99, 0xFC,
		0x99, 0xB8, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80,
		0x3C, 0x00, 0x7E, 0x00, 0xC3, 0x00, 0xC3, 0x1F,
		0xC3, 0x3F, 0x7E, 0x31, 0x7E, 0x38, 0xC3, 0x1E,
		0xC3, 0x07, 0xC3, 0x03, 0xC3, 0x31, 0x7E, 0x3F,
		0x3C, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x86,
		0xB1, 0xC6, 0xB1, 0xC6, 0x19, 0x4C, 0x1B, 0x6C,
		0x1B, 0x6C, 0x8A, 0x28, 0x8E, 0x38, 0x8E, 0x38,
		0x06, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x37,
		0x7E, 0x3F, 0xE6, 0x39, 0xC3, 0x31, 0xFF, 0x31,
		0xFF, 0x31, 0xC0, 0x31, 0xE3, 0x31, 0x7E, 0x31,
		0x3C, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xC3,
		0x7C, 0xC3, 0xCC, 0xC3, 0x8C, 0xC3, 0x8C, 0xC3,
		0x8C, 0xC3, 0x8C, 0xC3, 0x8C, 0xC7, 0x8C, 0xFF,
		0x8C, 0x7B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	return loadRom(logo_rom, sizeof(logo_rom));
}


int romLoadFromPath(char* rom_path)
{
	FILE* rom = fopen(rom_path, "rb");

	if (rom == NULL)
	{
		return 1;
	}

	fseek(rom, 0, SEEK_END);
	
	size_t rom_size = ftell(rom);
	
	rewind(rom);

	if (rom_size > 3584)
	{
		fclose(rom);
		return 1;
	}

	uint8_t buffer[rom_size];
	
	size_t copy_size = fread(buffer, sizeof(uint8_t), rom_size, rom);
	
	fclose(rom);
	
	if (copy_size != rom_size)
	{
		return 1;
	}

	return loadRom(buffer, rom_size);
}


int romLoadFromDialog()
{
	#ifdef _WIN32

	char rom_path[260];

	OPENFILENAME ofn;
	
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = rom_path;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(rom_path);
	ofn.lpstrFilter = "CHIP-8 Roms\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "roms";
	ofn.lpstrTitle = "Select ROM";
	ofn.Flags = OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		return romLoadFromPath(rom_path);
	}

	#endif

	return 1;
}