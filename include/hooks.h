#include <Common.h>
#include "plugin_common.h"
#include "types.h"
#include "utility.h"

namespace Hooks {
extern uint64_t v_gameDir;
extern int64_t SUB_19E03E0_ADDR;
extern int64_t SUB_19E0200_ADDR;
typedef uint64_t(*gfxLoader_t)(long long a1, const char *path, long long a3, unsigned int a4, unsigned int a5);
typedef u64(*xml_omt_Loader_t)(long long a1,  char *path, char* ex, long long a4, long long a5);
typedef char(*GXT2_t)(char *filepath, char *filename, bool unk0, bool unk1);
typedef uint64_t(*DLC_GXT2_t)(int64_t a1, const char *a2, char a3, char a4);
typedef uint64_t(*DLC_GXT2_Loader_t)(char *a1, u32 *a2, int a3);
typedef char(*DLC_GXT2_Loader2_t)(int64_t a1, char* a2);
typedef char*(*DataFunc_t)(char* a1, _BYTE* a2);
typedef uint32_t(*shaderValueReader_t)(u64 a1, u64 a2, u64 a3, u64 a4);
typedef u8(*contentIsExist_t)(long long a1, char *path, long long a3);
typedef char(*omtLoader_t)(u8 *a1, int a2, char *path, char *ex, int a5);
typedef char(*xmlLoader_t)(uint64_t a1, char* path, uint64_t a3, uint64_t a4, uint64_t a5, char a6, uint64_t a7);
extern gfxLoader_t gfxLoader_Stub;
extern GXT2_t GXT2_Stub;
extern DLC_GXT2_t DLC_GXT2_Stub;
extern DLC_GXT2_Loader_t DLC_GXT2_Loader_Stub;
extern DLC_GXT2_Loader2_t DLC_GXT2_Loader2_Stub;
extern DataFunc_t DataFunc_Stub;
extern shaderValueReader_t shaderValueReader_Stub;
extern contentIsExist_t contentIsExist_Stub;
extern omtLoader_t omtLoader_Stub;
extern xml_omt_Loader_t xml_omt_Loader_Stub;
extern xmlLoader_t xmlLoader_Stub;
uint64_t gfxLoader_hook(long long a1, const char *path, long long a3, unsigned int a4, unsigned int a5);
u64 xml_omt_Loader_hook(long long a1, char *path, char* ex, long long a4, long long a5);
char GXT2_hook(char *filepath, char *filename, bool unk0, bool unk1);
uint64_t DLC_GXT2_hook(int64_t a1, const char *a2, char a3, char a4);
uint64_t DLC_GXT2_Loader_hook(char *a1, u32 *a2, int a3);
char DLC_GXT2_Loader2_hook(int64_t a1, char* a2) ;
char* DataFunc_hook(char* a1, _BYTE* a2);
BOOL ModMenu_hook(u64 RDI, u64 RSI);
uint32_t shaderValueReader_hook(char* a1);
uint32_t shaderValueReader2_hook(u64 pointer, char* shader, u64 unk);
uint32_t shaderValueReader3_hook(u64 pointer, char* shader);
u8 contentIsExist_hook(long long a1, char *path, long long a3);
char omtLoader_hook(u8 *a1, int a2, char *path, char *ex, int a5);
char xmlLoader_hook(uint64_t a1,  char* path, uint64_t a3, uint64_t a4, uint64_t a5, char a6, uint64_t a7);
};
