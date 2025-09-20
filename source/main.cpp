// Game Patch: Patches game before boot.
// Author: illusion0001 @ https://github.com/illusion0001
// Repository: https://github.com/GoldHEN/GoldHEN_Plugins_Repository

#include <stdint.h>
#include <stdarg.h>
#include "detour.h"
#include "utility.h"
#include "offsets.h"
#include "hooks.h"
#include "imports.h"
#include "types.h"
#define PLUGIN_NAME (const char*) "ProjectV"
#define PLUGIN_DESC (const char*) "GTA V Modifications"
#define PLUGIN_AUTH (const char*) "rfoodxmodz"
#define PLUGIN_VER 0x130 // 1.10

#define NO_ASLR_ADDR 0x00400000

attr_public const char *g_pluginName = PLUGIN_NAME;
attr_public const char *g_pluginDesc = PLUGIN_DESC;
attr_public const char *g_pluginAuth = PLUGIN_AUTH;
attr_public u32 g_pluginVersion = PLUGIN_VER;

char titleid[16] = {0};
char game_elf[32] = {0};
char game_prx[MAX_PATH_] = {0};
char game_ver[8] = {0};

u64 module_base = 0;
u32 module_size = 0;
// unused for now
u64 PRX_module_base = 0;
u32 PRX_module_size = 0;
struct proc_info procInfo;


void mkdir_chmod(const char *path, OrbisKernelMode mode) {
   // sceKernelMkdir(path, mode);
   // sceKernelChmod(path, mode);
    return;
}


long APP_BASE = 0x400000;
/*
char msgB[255];
void setupHook() {
	
	u64 gfx_addr = (uint64_t)PatternScan(APP_BASE, 0x3000000, "55 48 89 E5 41 57 41 56 53 50 49 89 D7 49 89 F6 48 8B ? ? ? ? 89 C1 FF ? ?");
	memcpy((void *)(gfx_addr), "\x55\x48\x89\xE5\x41\x57\x41\x56\x53\x50\x49\x89\xD7\x49\x89\xF6", 16);
	Hooks::gfxLoader_Stub = (Hooks::gfxLoader_t)DetourFunction((gfx_addr), (void *)Hooks::gfxLoader_hook, 16);
	
	
	u64 xml_omt_addr = (uint64_t)PatternScan(0x1F00000, 0x3250000, "55 48 89 E5 41 57 41 56 41 54 53 48 81 EC 10 01 00 00 49 89 CC");
	memcpy((void *)(xml_omt_addr), "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x54\x53\x48\x81\xEC\x10\x01\x00\x00\x49\x89\xCC", 21);
	Hooks::xml_omt_Loader_Stub = (Hooks::xml_omt_Loader_t)DetourFunction((xml_omt_addr), (void *)Hooks::xml_omt_Loader_hook, 21);
	
	
	u64 gxt2_addr = (uint64_t)PatternScan(0x2100000, 0x3000000, "95 30 FF FF FF 4C 8B ? ? ? ? ? 49 8B ? 48 89 45 E8 C5 ? 57 C0 C5 F8 29 45 D0 48 C7 45 E0 00 00 00 00 48 8D 85 20 FF FF FF 48 89 45 E0 48 8D 45 10 48 89 45 D8 C7 45 D4 30 00 00 00 C7 45 D0 10 00 00 00 48 8D 4D D0 48 89 DF BE 40 00 00") - 0x60;
	//sprintf(msgB, "gxt2_addr: %llx", gxt2_addr);
	//sceSysUtilSendSystemNotificationWithText(222, msgB);
	
	memcpy((void *)(gxt2_addr), "\x55\x48\x89\xE5\x41\x56\x53\x48\x81\xEC\xD0\x00\x00\x00\x49\x89\xF2\x48\x89\xFB", 20);
	Hooks::GXT2_Stub = (Hooks::GXT2_t)DetourFunction((gxt2_addr), (void *)Hooks::GXT2_hook, 20);
	
	
	
	Hooks::SUB_19E03E0_ADDR = (int64_t)PatternScan(0x1200000, 0x3000000, "55 48 89 E5 41 56 53 48 81 EC 10 01 00 00 48 89 D0");
	Hooks::SUB_19E0200_ADDR = (int64_t)PatternScan(0x1200000, 0x3000000, "55 48 89 E5 41 57 41 56 41 55 41 54 53 48 81 EC 08 01 00 00 49 89 D6 49 89 ? 49 89 ? 48");
	Hooks::v_gameDir = (int64_t)PatternScan(0x3000000, 0x5000000, "2F 61 70 70 30 2F 00");
	WriteJump((uint64_t)PatternScan(APP_BASE, 0x1400000, "48 89 F0 48 89 FE 40 B7 01 48 85 C0 74 4D 45 30"), (uint64_t)Hooks::DataFunc_hook);

	
	memcpy((void *)(Hooks::SUB_19E0200_ADDR), "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x81\xEC\x08\x01\x00\x00", 20);
	Hooks::omtLoader_Stub = (Hooks::omtLoader_t)DetourFunction((Hooks::SUB_19E0200_ADDR), (void *)Hooks::omtLoader_hook, 20);
	
	
	u32 xml_func_inst[0x301];
	u64 xml_addr = (uint64_t)PatternScan(0x1800000, 0x3000000, "E8 ? ? 05 00 88 D8 48  83 C4 18 5B 41 5C 41 5D 41 5E 41 5F 5D C3 66 2E  0F 1F 84 00 00 00 00 00") + 0x20;
	for(int i = 0; i <= 0x256; i++) {
	xml_func_inst[i] = *(u32*)(xml_addr + (i * 4));
	*(u32*)(xml_addr + (i * 4)) = xml_func_inst[i];
	}
	Hooks::xmlLoader_Stub = (Hooks::xmlLoader_t)DetourFunction((xml_addr), (void *)Hooks::xmlLoader_hook, 0x22);
	
}
*/

// https://github.com/bucanero/apollo-ps4/blob/a530cae3c81639eedebac606c67322acd6fa8965/source/orbis_jbc.c#L62
int get_module_info(OrbisKernelModuleInfo moduleInfo, const char* name, uint64_t *base, uint32_t *size)
{
    OrbisKernelModule handles[256];
    size_t numModules;
    int ret = 0;
    ret = sceKernelGetModuleList(handles, sizeof(handles), &numModules);
    if (ret)
    {
        final_printf("sceKernelGetModuleList (0x%08x)\n", ret);
        return ret;
    }
    final_printf("numModules: %li\n", numModules);
    for (size_t i = 0; i < numModules; ++i)
    {
        ret = sceKernelGetModuleInfo(handles[i], &moduleInfo);
        final_printf("ret 0x%x\n", ret);
        final_printf("module %li\n", i);
        final_printf("name: %s\n", moduleInfo.name);
        final_printf("start: 0x%lx\n", (uint64_t)moduleInfo.segmentInfo[0].address);
        final_printf("size: %u (0x%x)\n", moduleInfo.segmentInfo[0].size, moduleInfo.segmentInfo[0].size);
        if (ret)
        {
            final_printf("sceKernelGetModuleInfo (%X)\n", ret);
            return ret;
        }

        if (strcmp(moduleInfo.name, name) == 0 || name[0] == '0')
        {
            if (base)
                *base = (uint64_t)moduleInfo.segmentInfo[0].address;

            if (size)
                *size = moduleInfo.segmentInfo[0].size;
            return 1;
        }
    }
    return 0;
}


void* my_thread(void* args)
{
    
	// u64 presetsFilePath_addr = (uint64_t)PatternScan(0x2600000, 0x3600000, "70 6C 61 74 66 6F 72 6D 3A 2F 64 61 74 61 2F 70 72 65 73 65 74 73 2E 6D 65 74 61 00");
	// if(presetsFilePath_addr > 0x1337) {
		// memcpy_p(presetsFilePath_addr,"\x2F\x64\x61\x74\x61\x2F\x67\x74\x61\x35\x2F\x70\x72\x65\x73\x65\x74\x73\x2E\x6D\x65\x74\x61\x00", 24);
	// }
	
  //  u64  gfx_addr = (uint64_t)PatternScan(0x1A00000, 0x2500000, "55 48 89 E5 41 57 41 56 53 50 49 89 D7 49 89 F6 48 8B ? ? ? ? 89 C1 FF ? ?");
   // memcpy_p((gfx_addr), "\x55\x48\x89\xE5\x41\x57\x41\x56\x53\x50\x49\x89\xD7\x49\x89\xF6", 16);
  //  Hooks::gfxLoader_Stub = (Hooks::gfxLoader_t)DetourFunction((gfx_addr), (void *)Hooks::gfxLoader_hook, 16);
	

	
	//XML LOADER
	//u64 xml_omt_addr = (uint64_t)PatternScan(0x1F00000, 0x3250000, "55 48 89 E5 41 57 41 56 41 54 53 48 81 EC 10 01 00 00 49 89 CC");
	memcpy_p((OMT_XML_OFFSET + APP_BASE), "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x81\xEC\x28\x01\x00\x00", 20);
	Hooks::xml_omt_Loader_Stub = (Hooks::xml_omt_Loader_t)DetourFunction((OMT_XML_OFFSET + APP_BASE), (void *)Hooks::xml_omt_Loader_hook, 20);
	
	
	
	// // [GXT2 LOADER] 
	// u64 gxt2_addr = (uint64_t)PatternScan(0x2100000, 0x2700000, "95 30 FF FF FF 4C 8B ? ? ? ? ? 49 8B ? 48 89 45 E8 C5 ? 57 C0 C5 F8 29 45 D0 48 C7 45 E0 00 00 00 00 48 8D 85 20 FF FF FF 48 89 45 E0 48 8D 45 10 48 89 45 D8 C7 45 D4 30 00 00 00 C7 45 D0 10 00 00 00 48 8D 4D D0 48 89 DF BE 40 00 00") - 0x60;
	 //memcpy_p((0x33B5E0 + APP_BASE), "\x55\x48\x89\xE5\x41\x56\x53\x48\x81\xEC\xD0\x00\x00\x00\x49\x89\xF2", 17);
	 //Hooks::GXT2_Stub = (Hooks::GXT2_t)DetourFunction(((0x33B5E0 + APP_BASE)), (void *)Hooks::GXT2_hook, 17);//OLD GTA V GXT2 LOADER (SEEMS SRPINTF) NOT USEFUL HERE FOR THE LANG TXTS BUT FOR OTHER THINGS MAYBE
	 
	 
	memcpy_p((0x4EE4390 + APP_BASE), "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x81\xEC\x28\x01\x00\x00", 20);
	 Hooks::GXT2_Stub = (Hooks::GXT2_t)DetourFunction(((0x4EE4390 + APP_BASE)), (void *)Hooks::GXT2_hook, 20);
	// u64 dlc_gxt2_addr;
	// if(!dlc_gxt2_addr)
	 // dlc_gxt2_addr = (uint64_t)PatternScan(0x1300000, 0x2200000, "53 48 81 EC ? 02 00 00 41 89 ? 89  95") - 0xC;
	// if(!dlc_gxt2_addr)
	 // dlc_gxt2_addr = (uint64_t)PatternScan(0x1300000, 0x2200000, "FF FF FF ? ? ? ? ? ? ? 00 55 48 89 E5 41 57 41 56  41 55 41 54 53 48 81 EC 58 02 00 00 ?") + 0xB;
	// memcpy_p((dlc_gxt2_addr), "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x81\xEC\x58\x02\x00\x00", 20);
	// Hooks::DLC_GXT2_Stub = (Hooks::DLC_GXT2_t)DetourFunction((dlc_gxt2_addr), (void *)Hooks::DLC_GXT2_hook, 20);
	// u64 dlc_gxt2_loader_addr = (uint64_t)PatternScan(0x1A00000, 0x2700000, "55 48 89 E5 41 57 41 56  41 55 41 54 53 48 81 EC 08 01 00 00 41 89 ? 49  89 ? 48 89 ? 48 8B 05 ? ? ? ? 48 ? 00 48") ;
	// memcpy_p((dlc_gxt2_loader_addr), "\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x81\xEC\x08\x01\x00\x00", 20);
	// Hooks::DLC_GXT2_Loader_Stub = (Hooks::DLC_GXT2_Loader_t)DetourFunction((dlc_gxt2_loader_addr), (void *)Hooks::DLC_GXT2_Loader_hook, 20);
	// u64 dlc_gxt2_loader2_addr = (uint64_t)PatternScan(0x1A00000, 0x2700000, "48  89 F3 49 89 FE 48 89 DF 4C 89 F6 BA 01 00 00 00 E8 ? ? FF FF 88 C1 30 C0 84 ? 74 15 31 C0 48  85 DB 74 ? 48 89 DF E8 ? ? ? 00 ? 89 46 58  B0 01") - 7;
	// memcpy_p((dlc_gxt2_loader2_addr), "\x55\x48\x89\xE5\x41\x56\x53\x48\x89\xF3\x49\x89\xFE\x48\x89\xDF\x4C\x89\xF6\xBA\x01\x00\x00\x00", 24);
	// Hooks::DLC_GXT2_Loader2_Stub = (Hooks::DLC_GXT2_Loader2_t)DetourFunction((dlc_gxt2_loader2_addr), (void *)Hooks::DLC_GXT2_Loader2_hook, 24);
	
	// //[DATA LOADER] 
	// Hooks::SUB_19E03E0_ADDR = (int64_t)PatternScan(0x1900000, 0x2200000, "55 48 89 E5 41 56 53 48 81 EC 10 01 00 00 48 89 D0");
	// Hooks::SUB_19E0200_ADDR = (int64_t)PatternScan(0x1900000, 0x2200000, "55 48 89 E5 41 57 41 56 41 55 41 54 53 48 81 EC 08 01 00 00 49 89 D6 49 89 ? 49 89 ? 48");

	// /* [OMT | METADATA LOADER] */
	// u64 v_instruction_addr = (int64_t)PatternScan(0x425000, 0x452000, "49 C7 06 00 00 00 00 41 C7 46 08 00 00 00 00 48 8D 3D") + 0xF;
	// u64 instructionBytes =  *(u32*)(v_instruction_addr + 0x3);
	// Hooks::v_gameDir = instructionBytes + v_instruction_addr + 7;
	// WriteJump((uint64_t)PatternScan(0xE00000, 0x1200000, "48 89 F0 48 89 FE 40 B7 01 48 85 C0 74 4D 45 30"), (uint64_t)Hooks::DataFunc_hook);
	
		
	 //u64 omt_addr = (uint64_t)PatternScan(0x1200000, 0x3000000, "55 48 89 E5 41 57 41 56 41 55 41 54 53 48 81 EC 08 01 00 00 49 89 D6 49 89 ? 49 89 ? 48");
	 memcpy_p(OMT_OFFSET + APP_BASE,"\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x83\xEC\x28", 17);
	 Hooks::omtLoader_Stub = (Hooks::omtLoader_t)DetourFunction((OMT_OFFSET + APP_BASE), (void *)Hooks::omtLoader_hook, 17);
	 
	 memcpy_p(OMT2_OFFSET + APP_BASE,"\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x83\xEC\x48", 17);
	 Hooks::omtLoader_Stub = (Hooks::omtLoader_t)DetourFunction((OMT2_OFFSET + APP_BASE), (void *)Hooks::omtLoader_hook, 17);
	

			
	// // PAYLOAD INJECTION - TEST
	// //00286B001

	// //memcpy_p((0x2E367AC + 0x400000), "\x02", 1);//LOADING SCREEN PATCHES
	// //memcpy_p((0x1B56D30 + 0x400000), "\xFF\x22", 2);//WRITE TO CHECK IF IT CRASHES ON STARTUP
	// //memcpy_p((0x002DEBD70 + 0x400000), "\xC3\x90\x90\x90\x90\x90\x90\x90", 8);//WRITE retn on freespace (ModMenu)
	// //memcpy_p((0x31EBD7E), "\xC3\x90\x90\x90\x90\x90\x90\x90", 8);//WRITE end of (ModMenu)
	// //memcpy_p((0x002DEBD70 + 0x400000), "\x55\x48\x8D\x15\xF3\xFF\xFF\xFF\x41\x54\x49\xBB\x00\x00\x00\x00\x00\x00\x00\x00\x55\x53\x48\x83\xEC\x08\x4C\x01\xDA\x81\xBF\x3C\x3E\x75\x00\x37\x13\x00\x00\x4C\x8D\xAF\xA0\x3A\x75\x00\x4C\x8D\xA7\x80\x3A\x75\x00\x4D\x89\x6C\x24\x10\x48\x89\xFB\x4C\x89\xAF\x80\x3A\x75\x00\x48\x8D\xAF\x3C\x3E\x75\x00\x74\x25\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00\xC5\xF9\x6F\x04\x02\x48\xB8\x01\x00\x00\x00\x01\x00\x00\x00\xC5\xF8\x11\x87\x3C\x3E\x75\x00\x48\x89\x45\x10\x48\x8D\x83\x40\x4D\x37\xFE\x4C\x89\xE7\xFF\xD0\x48\x8B\x83\xA0\x3A\x75\x00\x39\x45\x04\x7D\x15\x89\x45\x04\x4C\x89\xE7\x48\x8D\x83\xB0\x2F\x45\xFE\xFF\xD0\x83\x7D\x08\x01\x74\x10\x48\x83\xC4\x08\xB8\x01\x00\x00\x00\x5B\x5D\x41\x5C\x41\x5D\xC3\x48\x63\x83\xA0\x3A\x75\x00\x4C\x89\xE7\x48\x89\x83\xA0\x3A\x75\x00\x48\x8D\x83\x10\x91\x42\xFE\xFF\xD0\x48\x63\x83\xA0\x3A\x75\x00\x4C\x89\xE7\x48\x81\xEB\x20\xFC\xCC\x01\x48\x89\x83\xC0\x36\x42\x02\x49\xC7\x45\x08\x01\x00\x00\x00\xFF\xD3\x48\x83\xC4\x08\xB8\x01\x00\x00\x00\x5B\x5D\x41\x5C\x41\x5D\xC3\x90\x90\x90\x90\x90\x90\x90", 258);//WRITE retn on freespace (ModMenu)
	// int fd;
	// //char payloadArr[0x40000];
	// // int v_payloadSize = 0x40000;
	// // unsigned char *payloadArr = (unsigned char*)malloc(v_payloadSize);
	// // fd = sceKernelOpen("/data/GoldHEN/plugins/gtapayload", O_RDONLY, 0);
	// // if(fd) {
		// // for(int i = 0; i < v_payloadSize; i++)
		// // sceKernelRead(fd, &payloadArr[i], sizeof *payloadArr);
		// // WriteMemory((0x002DEBD70 + 0x400000), payloadArr, v_payloadSize);
	// // }
	
	// //memcpy_p((0x002DEBD70 + 0x400000), "\x41\x56\x4C\x8D\xB7\xE0\x9B\x87\x00\x41\x55\x41\x54\x55\x48\x8D\xAF\xC0\x9B\x87\x00\x53\x4C\x89\x75\x10\x80\xBF\x7C\x9F\x87\x00\x00\x4C\x89\xB7\xC0\x9B\x87\x00\x48\x89\xFB\x4C\x8D\xAF\x7C\x9F\x87\x00\x75\x15\x48\xB8\x00\x00\x00\x00\x01\x01\x01\x01\x49\x89\x45\x04\xC6\x87\x7C\x9F\x87\x00\x01\x48\x8D\x83\xB0\xF3\x29\xFE\x48\x89\xEF\xFF\xD0\x4C\x8B\xA3\xE0\x9B\x87\x00\x45\x39\x65\x04\x7D\x2C\x41\x80\x7D\x08\x01\x0F\x84\x8B\x00\x00\x00\x41\x80\x7D\x09\x01\x0F\x84\xD3\x00\x00\x00\x41\x80\x7D\x0A\x01\x0F\x84\xF9\x00\x00\x00\x41\x80\x7D\x0B\x01\x74\x16\x45\x89\x65\x04\x5B\xB8\x01\x00\x00\x00\x5D\x41\x5C\x41\x5D\x41\x5E\xC3\x0F\x1F\x40\x00\x48\x8D\x83\xC0\x2E\x35\xFE\x48\x89\xEF\xFF\xD0\x48\x63\x83\xE0\x9B\x87\x00\x48\x89\xEF\x48\x89\x83\xE0\x9B\x87\x00\x48\x8D\x83\x20\x12\x35\xFE\xFF\xD0\x48\x63\x83\xE0\x9B\x87\x00\x48\x89\xEF\x48\x81\xEB\xB0\x1C\xC2\x01\x48\x89\x83\x90\xB8\x49\x02\x49\xC7\x46\x08\x01\x00\x00\x00\x49\xC7\x46\x10\x00\x00\x00\x00\xFF\xD3\xEB\x98\x66\x0F\x1F\x44\x00\x00\x48\x8D\x83\xC0\x2E\x35\xFE\x48\x89\xEF\xFF\xD0\x48\x63\x83\xE0\x9B\x87\x00\x48\x89\xEF\x48\x89\x83\xE0\x9B\x87\x00\x48\x8D\x83\x20\x12\x35\xFE\xFF\xD0\x48\x63\x83\xE0\x9B\x87\x00\x48\x89\xEF\x48\x89\x83\xE0\x9B\x87\x00\x48\x8D\x83\x40\xEC\x25\xFE\x49\xC7\x46\x08\x01\x00\x00\x00\xFF\xD0\x41\x80\x7D\x09\x01\x0F\x85\x2D\xFF\xFF\xFF\x48\x8D\x83\xC0\x2E\x35\xFE\x48\x89\xEF\xFF\xD0\x48\x63\x83\xE0\x9B\x87\x00\x48\x89\xEF\x48\x89\x83\xE0\x9B\x87\x00\x48\x8D\x83\x10\x3B\x2A\xFE\xFF\xD0\x41\x80\x7D\x0A\x01\x0F\x85\x07\xFF\xFF\xFF\x48\x8D\x83\xC0\x2E\x35\xFE\x48\x89\xEF\xFF\xD0\x48\x63\x83\xE0\x9B\x87\x00\x48\x89\xEF\x48\x89\x83\xE0\x9B\x87\x00\x48\x8D\x83\xD0\x3A\x2A\xFE\xFF\xD0\x41\x80\x7D\x0B\x01\x0F\x85\xDD\xFE\xFF\xFF\xE9\xEE\xFE\xFF\xFF", 434);//WRITE PAYLOAD
// //	memcpy_p((0x100F789), "\xE8\xC2\x4E\xBD\x01\x48\x89\xC7\xE8\xDA\xC5\x1D\x02\x48\x8B\x0B\x89\x01\x48\x83\xC4\x08\x5B\x5D\xC3", 25);//WRITE HOOK INSTRUCTIONS ON IS_PLAYER_ONLINE
	// //WriteJump(0x002DEBD70 + 0x400000, (uint64_t)Hooks::ModMenu_hook);//Hook ModMenu (works)
	
	// /* [SHADER READER] */
	// // WriteJump(0x1AE1070 + 0x400000, (uint64_t)Hooks::shaderValueReader_hook);//1.46
	// // WriteJump(0x1AD2150 + 0x400000, (uint64_t)Hooks::shaderValueReader2_hook);//1.46
	// // WriteJump(0x1AD2110 + 0x400000, (uint64_t)Hooks::shaderValueReader3_hook);//1.46
	
   // // [XML | METADATA LOADER] 
	// u32 xml_func_inst[0x301];
	// u64 xml_addr = (uint64_t)PatternScan(0x1800000, 0x2400000, "E8 ? ? 05 00 88 D8 48  83 C4 18 5B 41 5C 41 5D 41 5E 41 5F 5D C3 66 2E 0F 1F 84 00 00 00 00 00") + 0x20;
	// for(int i = 0; i <= 0x256; i++) {
	// xml_func_inst[i] = *(u32*)(xml_addr + (i * 4));
	// sceKernelMprotect((void*)(xml_addr + (i * 4)), 4, VM_PROT_ALL);
	// *(u32*)(xml_addr + (i * 4)) = xml_func_inst[i];
	// }
	memcpy_p(XML_OFFSET + APP_BASE,"\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x83\xEC\x18", 17);
	Hooks::xmlLoader_Stub = (Hooks::xmlLoader_t)DetourFunction((XML_OFFSET + APP_BASE), (void *)Hooks::xmlLoader_hook, 17);
    scePthreadExit(NULL);
    return NULL;
}
void *thread_func(void *arg) {
	
	
	return NULL;
}
char msg_0[255];
extern "C" {
s32 attr_module_hidden module_start(size_t argc, const void *args) {
    final_printf("[GoldHEN] <%s\\Ver.0x%08x> %s\n", g_pluginName, g_pluginVersion, __func__);
    final_printf("[GoldHEN] Plugin Author(s): %s\n", g_pluginAuth);
    boot_ver();
    struct proc_info procInfo;
    OrbisKernelModuleInfo CurrentModuleInfo;
    CurrentModuleInfo.size = sizeof(OrbisKernelModuleInfo);
    if(!get_module_info(CurrentModuleInfo, "0", &module_base, &module_size) && module_base && module_size)
    {
        final_printf("Could not find module info for current process\n");
        return -1;
    }
    if (sys_sdk_proc_info(&procInfo) == 0) {
    initImports();
    sprintf(msg_0, "Coded By @rfoodxmodz.");
    u32 crc32_hash = CRC32(msg_0);
    if(crc32_hash != 0xEB8BB9CB)
		goto end;
    sceSysUtilSendSystemNotificationWithText(222, "[RDR2] - WildRAGE\nVersion: 1.0");
    sceSysUtilSendSystemNotificationWithText(222, msg_0);
     print_proc_info();
	 OrbisPthread thread;
     scePthreadCreate(&thread, NULL, my_thread, NULL, "my_thread");
     end:
        return 0;
    }
    NotifyStatic(TEX_ICON_SYSTEM, "Unable to get process info from " STRINGIFY(sys_sdk_proc_info));
    return -1;
}
}

extern "C" {
s32 attr_module_hidden module_stop(s64 argc, const void *args) {
    final_printf("[GoldHEN] <%s\\Ver.0x%08x> %s\n", g_pluginName, g_pluginVersion, __func__);
    return 0;
}
}
