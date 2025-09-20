#include "hooks.h"
#include "imports.h"
#include "utility.h"
#include "offsets.h"
#include "gfx_list.h"


namespace Hooks {

gfxLoader_t gfxLoader_Stub;
shaderValueReader_t shaderValueReader_Stub;
contentIsExist_t contentIsExist_Stub;
omtLoader_t omtLoader_Stub;
xml_omt_Loader_t xml_omt_Loader_Stub;
GXT2_t GXT2_Stub;
DLC_GXT2_t DLC_GXT2_Stub;
DLC_GXT2_Loader_t DLC_GXT2_Loader_Stub;
DLC_GXT2_Loader2_t DLC_GXT2_Loader2_Stub;
DataFunc_t DataFunc_Stub;
xmlLoader_t xmlLoader_Stub;
uint64_t v_gameDir;
int64_t SUB_19E03E0_ADDR;
int64_t SUB_19E0200_ADDR;
char v_GFX_list[583][255];
bool IS_DLC_GXT2;
bool IS_DLC_GXT2_2;
const char* GXT2_DLC_NAME;


char *stristr(const char *haystack, const char *needle)
{
    char *result = NULL;

    if (haystack && needle) // Ensure neither input is NULL
    {
        if (*needle == '\0') // If the needle is empty
        {
            result = (char *)haystack;
        }
        else
        {
            const char *h = haystack;

            while (*h) 
            {
                const char *h_sub = h;
                const char *n_sub = needle;

                while (*n_sub && *h_sub && tolower((unsigned char)*h_sub) == tolower((unsigned char)*n_sub))
                {
                    ++h_sub;
                    ++n_sub;
                }

                if (*n_sub == '\0')
                {
                    result = (char *)h;
                    break;
                }

                ++h; 
            }
        }
    }

    return result;
}


const char* data_files[] = {
"/camera.meta",//
"/common.meta",//
"/common_cutscene.meta",//
"/coverdestroyableobjects.meta",
"/coverhelpersdata.meta",
"/coverstreamingdata.meta",
"/deadeye.meta",
"/defaulttaskdata.meta",//
"/dispatch.meta",//
"/events.meta",
"/eventscontextdefinitions.meta",//
"/eventtrackers.meta",
"/fluidvessels.meta",//
"/gestureconditions.meta",//
"/gravitywelldefinitions.meta",//
"/handling.meta",//
"/iteminteractioninfo.meta",
"/lighting.meta",//
"/lookintensitytemplatefefinitions.meta"
"/mapdatacullboxes_new.meta",
"/motiontaskdata.meta",//
"/navcapabilities.meta",//
"/objectexplosioninfo.meta",//
"/pedcomponentsets.meta",//
"/pedgesturesettings.meta",//
"/pedhealth.meta",//
"/pediksettings.meta",//
"/pedperception.meta",//
"/pedshotscenes.meta",
"/pedspeeddata.meta",//
"/persistence_constants.meta",
"/persistence_model_aging.meta",
"/propobjectinfo.meta",//
"/relationships.meta",//
"/taskdata.meta"
};

const char* dat_files_list[] = {
"/timescales",
"/visualsettings",
"/visualsettings_ps4"
};


const char* data_meta_files[] = {
"/boathullblacklist.xml",//
"/dlclist.xml",//
"/fragment.xml",//
"/mounttune.xml",//
"/movieVariations",//
"/pedbounds.xml",//
"/regionTemperatureInfo",//
"/ropedata",//
"/scriptedglow",//
"/updategraphprocesscontrol",//
"/watertune.xml",//
"/weatherClimates",//
"/weatherGraph",//
"/weatherRemapTable",//
"/weatherTemperatureConfig"//
};


const char* levels_files_needed[] = {
	"ambientscanner_swaps.meta",
"area.meta",
"barbrawl.meta",
"destruction.meta",
"gtxds.meta",
"interiors.meta",
"missionmetadata.xml",
"archetype_swaps.omt",
"navmeshes_swaps.omt",
"popgroups.omt",
"popzone.omt",
"popzone_core.omt",
"popzone_pedschedule.omt",
"popzone_spawner.omt",
"popzone_volume.omt",
"resident.omt",
"slownesszones.omt",
"trainconfigs.omt",
};


const char* levels_files[] = {
"chmodifiervolumes.meta",
"customcoverpointsets.meta",
"environmentalwaterdisturbers.meta",
"mapzones.meta",
"pathzones.xml",
"vehiclebonecollisionflags.meta",
"terrain.meta",
"water.xml",
"waterguama.xml",
"weather.xml"};


uint32_t shaderValueReader3_hook(u64 pointer, char* shader) {

  return 0;
}
uint32_t shaderValueReader2_hook(u64 pointer, char* shader, u64 unk) {
	
      return 0;
  }
 
uint32_t shaderValueReader_hook(char* a1) {
	
  return 0;
	//return shaderValueReader_Stub(a1, a2, a3, a4);
}
uint64_t gfxLoader_hook(long long a1, const char *path, long long a3, unsigned int a4, unsigned int a5) {
	for(int j=0;j<583;j++) {
		if(gfx_exists_(path, gfx_name_list[j]) ) {
			return gfxLoader_Stub(a1, pprintf("/data/gta5/gfx/%s", gfx_name_list[j]), a3, a4, a5);
		}
	}
	//the below offset will change the loading screen to multiplayer
	//sceKernelMprotect((void*)((0x30AD0CC + 0x400000)), 4, VM_PROT_ALL);
	//*(int*)((0x30AD0CC + 0x400000)) = 3;//block loading
	return gfxLoader_Stub(a1, path, a3, a4, a5);
}

uint64_t DLC_GXT2_hook(int64_t a1, const char *a2, char a3, char a4) {
	
	return 0;
}
char DLC_GXT2_Loader2_hook(int64_t a1, char* a2) {
return 0;
}
uint64_t DLC_GXT2_Loader_hook(char *a1, u32 *a2, int a3) {

	return 0;
}

char GXT2_hook(char *filepath, char *filename, bool unk0, bool unk1) { // registerFile (otd | osc | oft | omt scenarios)
	  if(strstr(filepath, "/rdr3/scenario/")) {
	// sceSysUtilSendSystemNotificationWithText(222, pprintf_dbg("SCEN:%s", filepath));
 }


	return GXT2_Stub(filepath, filename, unk0, unk1);
}
u64 xml_omt_Loader_hook(long long a1, char *path, char* ex, long long a4, long long a5) {
	//sceSysUtilSendSystemNotificationWithText(222, pprintf_dbg("XML:%s", path));
	//if(!strcmp(path, "platformcrc:/data/peds")) {	//	platformcrc:/data/peds.omt
	// return xml_omt_Loader_Stub(a1, file_exists_("/data/gta5/peds", path), ex, a4, a5);
	//}
	     //DATA META FILES
  for(int i = 0; i < sizeof(data_meta_files) / sizeof(data_meta_files[0]); i++) {
  if((stristr(path, "common:/data/") || stristr(path, "commoncrc:/data/") ) && strstr(path, data_meta_files[i])) {
	 sceSysUtilSendSystemNotificationWithText(222, pprintf_dbg("DATA3:\n%s", path));//only mountetune.xml
 }
  }

 
	return xml_omt_Loader_Stub(a1, path, ex, a4, a5);
}
BOOL ModMenu_hook(u64 RDI, u64 RSI) {
	u64 base_address = RDI - 0x27E4660;//sub_27E4660
	sceSysUtilSendSystemNotificationWithText(222, pprintf("RDI: 0x%llx\nbase_address: 0x%llx\n", RDI, base_address));
	return 1;
}
char* DataFunc_hook(char* a1, _BYTE *a2) {
  return "";
}

char omtLoader_hook(u8 *a1, int a2, char *path, char *ex, int a5) {
 //LEVELS/RDR3 FILES
  for(int i = 0; i < sizeof(levels_files_needed) / sizeof(levels_files_needed[0]); i++) {
  if(stristr(path, levels_files_needed[i])) {
	  //will load .omt files
	// sceSysUtilSendSystemNotificationWithText(222, pprintf_dbg("RDR3 OMT:\n%s", path));
 }
  }
  
   //DATA FILES
  for(int i = 0; i < sizeof(data_files) / sizeof(data_files[0]); i++) {
  if((stristr(path, "common:/data/") || stristr(path, "commoncrc:/data/") ) && strstr(path, data_files[i])) {
	// sceSysUtilSendSystemNotificationWithText(222, pprintf_dbg("DATA META:\n%s", path));
 }
  }
  
   //DAT META FILES
  for(int i = 0; i < sizeof(dat_files_list) / sizeof(dat_files_list[0]); i++) {
  if(stristr(path, dat_files_list[i])) {
	// will load the .dat files
 }
  }
	return omtLoader_Stub(a1, a2, path, ex, a5);
}

char xmlLoader_hook(uint64_t a1,  char* path, uint64_t a3, uint64_t a4, uint64_t a5, char a6, uint64_t a7) {
  	     //DAT META FILES

if(strstr(path, "levels/rdr3/rdr3")) {
	return xmlLoader_Stub(a1, file_exists_("/data/WildRAGE/levels/rdr3/rdr3.meta", path), a3, a4, a5, a6, a7);
 }
 for(int i = 0; i < sizeof(levels_files) / sizeof(levels_files[0]); i++) {
 if(stristr(path, levels_files[i])) {
	 //sceSysUtilSendSystemNotificationWithText(222, pprintf_dbg("RDR3 XML:\n%s", path));
	//return xmlLoader_Stub(a1, file_exists_(pprintf("/data/WildRAGE/levels/rdr3/%s", levels_files[i]), path), a3, a4, a5, a6, a7);
 }
 }
 
    //DATA META FILES
  for(int i = 0; i < sizeof(data_meta_files) / sizeof(data_meta_files[0]); i++) {
  if((stristr(path, "common:/data/") || stristr(path, "commoncrc:/data/") ) && strstr(path, data_meta_files[i])) {
	 sceSysUtilSendSystemNotificationWithText(222, pprintf_dbg("DATA:\n%s", path));
	//return xmlLoader_Stub(a1, file_exists_(pprintf("/data/WildRAGE/levels/rdr3/%s", levels_files[i]), path), a3, a4, a5, a6, a7);
 }
  }
// if(strstr(path, "scenariotriggers")) {
	// return xmlLoader_Stub(a1, file_exists_("/data/gta5/scenariotriggers.meta", path), a3, a4, a5, a6, a7);
	// }
	// if(strstr(path, "CloudKeyframes") || strstr(path, "cloudkeyframes"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/cloudkeyframes", path), a3, a4, a5, a6, a7);
	// if(strstr(path, ":/data/clouds"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/clouds", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "procedural.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/procedural.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "rumbleprofiles.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/rumbleprofiles.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, ":/data/lensflare_m"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/lensflare_m", path), a3, a4, a5, a6, a7);
	// if(strstr(path, ":/data/lensflare_f"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/lensflare_f", path), a3, a4, a5, a6, a7);
	// if(strstr(path, ":/data/lensflare_t"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/lensflare_t", path), a3, a4, a5, a6, a7);
	// if(strstr(path, ":/data/watertune"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/watertune", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "hbaosettings") || strstr(path, ":/data/HBAOSettings"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/hbaosettings", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "cpqsmix_ssaosettings") || strstr(path, ":/data/CPQSMix_SSAOSettings"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/cpqsmix_ssaosettings", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "weather.xml")) {
		// sceSysUtilSendSystemNotificationWithText(222, pprintf("weatherPointer: 0x%llx\nweatherPointer2: 0x%llx\nweatherPointer3: 0x%llx\n", a1, a3, a4));
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/levels/weather.xml", path), a3, a4, a5, a6, a7);
	// }
	// if(strstr(path, "commoncrc:/data/ai/weapons.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/ai/weapons.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "commoncrc:/data/ai/weaponcomponents.meta"))
	// return xmlLoader_Stub(a1, file_exists_("/data/gta5/ai/weaponcomponents.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "common:/data/ai/weaponanimations.meta"))
	// return xmlLoader_Stub(a1, file_exists_("/data/gta5/ai/weaponanimations.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "commoncrc:/data/ai/loadouts.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/ai/loadouts.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "common:/data/ai/vehiclemodelsets.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/ai/vehiclemodelsets.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "update:/common/data/shop_vehicle.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/shop_vehicle.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "common:/data/ai/motivations.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/motivations.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "ambientpedmodelsets.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/ai/ambientpedmodelsets.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "defaulttaskdata.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/defaulttaskdata.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "motiontaskdata.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/motiontaskdata.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "pedbrawlingstyle.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/pedbrawlingstyle.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "pedcomponentcloth.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/pedcomponentcloth.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "pedcomponentsets.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/pedcomponentsets.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "pedhealth.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/pedhealth.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "pediksettings.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/pediksettings.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "pedperception.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/pedperception.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, ":/data/playerswitch"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/playerswitch", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "fragment.xml"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/fragment.xml", path), a3, a4, a5, a6, a7);
	// if(strstr(path, ":/data/watertune_heistisland"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/watertune_heistisland", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "/effects/vfxlightningsettings"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/effects/vfxlightningsettings", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "dispatch.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/dispatch.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "events.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/events.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "garages.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/garages.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "carcols_gen9.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/carcols_gen9.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "carmodcols_gen9.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/carmodcols_gen9.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "scriptmetadata.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/scriptmetadata.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "taskdata.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/taskdata.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "tunableobjects.meta"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/tunableobjects.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "pedbounds.xml"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/pedbounds.xml", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "spstatssetup.xml"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/spstatssetup.xml", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "water.xml"))
		// return xmlLoader_Stub(a1, file_exists_("/data/gta5/water.xml", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "combatbehaviour"))
	// return xmlLoader_Stub(a1, file_exists_("/data/gta5/combatbehaviour.meta", path), a3, a4, a5, a6, a7);
	// if(strstr(path, "crimeinformation"))
	// return xmlLoader_Stub(a1, file_exists_("/data/gta5/crimeinformation.meta", path), a3, a4, a5, a6, a7);
 if(strstr(path, "/rdr3/scenario/")) {
	 sceSysUtilSendSystemNotificationWithText(222, pprintf_dbg("XML:%s", path));
		 //return xmlLoader_Stub(a1, file_exists_("/data/rdr3/handling.xml", path), a3, a4, a5, a6, a7);
 }
	return xmlLoader_Stub(a1, path, a3, a4, a5, a6, a7);
}

};

/*
	REFLECTIONS STUFF - Need more researching..
	
//*(uint8*)(0x36F01F0 + 0x400000) = 180; 
	//*(uint32*)(0x3828AD8 + 0x400000) = 180; 
	// *(uint32*)(0x3BFE6BC) = 50; 
	// *(uint32*)(0x3BFE6B4) = 180; 
	// *(uint32*)(0x3BFE6B8) = 180; 
	// *(uint32*)(0x3BFE6A4) = 180; 
	// *(uint32*)(0x3BFE6A8) = 180; 
	// *(uint32*)(0x3BFE6AC) = 180; 
	// *(uint32*)(0x3BFE6B0) = 180; 
	// *(uint32*)(0x3BFE684) = 180; 
	// *(uint32*)(0x3BFE688) = 180; 
	// *(uint32*)(0x3BFE68C) = 180; 
	// *(uint32*)(0x3BFE690) = 180; 
	// *(uint32*)(0x3BFE694) = 180; 
	// *(uint32*)(0x3BFE698) = 180; 
	// *(uint32*)(0x3BFE69C) = 180; 
	// *(uint32*)(0x3BFE6A0) = 180; 
	// *(uint32*)(0x37FE680 + 0x400000) = 180; 
	// *(uint32*)(0x37FEA80 + 0x400000) = 180; 
	// *(uint32*)(0x37FEA78 + 0x400000) = 180; 
	// *(uint32*)(0x37FEA84 + 0x400000) = 180; 
	// *(uint32*)(0x37FEA88 + 0x400000) = 180; 
	// *(uint32*)(0x37FEA8C + 0x400000) = 180; 
	// *(uint32*)(0x37FEA90 + 0x400000) = 180; 
	// *(uint32*)(0x37FEA94 + 0x400000) = 180; 
	// *(uint32*)(0x37FEA98 + 0x400000) = 180; 
	// *(uint32*)(0x37FEA9C + 0x400000) = 180; 
	// *(uint32*)(0x37FEAAC + 0x400000) = 180; 
	// *(uint32*)(0x37FEAB0 + 0x400000) = 180; 
	// *(uint32*)(0x3BFEA6C) = 180; 
	// *(uint32*)(0x312F140 + 0x400000) = 180; 
	// *(uint32*)(0x312F134 + 0x400000) = 180; 
	// *(uint32*)(0x382A6A8 + 0x400000) = 180; 
	
	 // *(uint32*)(0x382A69C + 0x400000) = 0; 
	 // *(uint32*)(0x382A698 + 0x400000) = 0; 
	// // *(uint32*)(0x382A670 + 0x400000) = 180; 
	// // *(uint32*)(0x382A674 + 0x400000) = 180; 
	// // *(uint32*)(0x382A694 + 0x400000) = 180; 
	// *(uint32*)(0x382A554 + 0x400000) = 500; 
	// *(uint32*)(0x37EE840 + 0x400000) = 500; 
	// *(uint32*)(0x37EE844 + 0x400000) = 500; 
	// *(uint32*)(0x37EE850 + 0x400000) = 500; 
	// *(uint32*)(0x37EE854 + 0x400000) = 500; 
	// //*(uint32*)(0x3BFEA4C) = 500; 
	// // *(uint32*)(0x37FE680 + 0x400000 + 15) = 500; 
	// // *(uint32*)(0x37FE680 + 0x400000 + 13) = 500; 
	// // *(uint32*)(0x37FE680 + 0x400000 + 14) = 500; 
	// for(int i = 0; i <= 10; i++) {
	// *(uint32_t*)(0x37FE9F0 + 0x400000 + (i * 4)) = 160;
	// }
	// for(int i = 0; i <= 15; i++) {
	// *(uint32_t*)(0x37FE680 + 0x400000 + (i * 4)) = 500;
	// }
	// fcxValues[0] = *(uint32*)(0x382A510 + 0x400000);//ReflectionTex2 = 147
	// fcxValues[1] = *(uint32*)(0x382A514 + 0x400000);//RefractionTexture - 151
	// fcxValues[2] = *(uint32*)(0x382A518 + 0x400000);//NoiseTexture = 
	// fcxValues[3] = *(uint32*)(0x382A528 + 0x400000);//RefractionDepthTexture
	// fcxValues[4] = *(uint32*)(0x381C5EC + 0x400000);//ReflectionTex = 54
	// fcxValues[5] = *(uint32*)(0x381C5F0 + 0x400000);//gReflectionMipCount
	// fcxValues[6] = *(uint32*)(0x39D2690 + 0x400000);//reflectionMSAA
	// fcxValues[7] = *(uint32*)(0x39D26B8 + 0x400000);//SSAO
	// fcxValues[8] = *(uint32*)(0x39D2960 + 0x400000);//fxaa
	// fcxValues[9] = *(uint32*)(0x39D2988 + 0x400000);//txaa
	// fcxValues[10] = *(uint32*)(0x382F244 + 0x400000);//LightingTexture
	// fcxValues[11] = *(uint32*)(0x382F248 + 0x400000);//ReflectionMatrix
	// fcxValues[12] = *(uint32*)(0x382F24C + 0x400000);//RefractionMatrix
	
	// //sprintf(buff, "ReflectionTex2: %i\nRefractionTexture: %i\n", fcxValues[0], fcxValues[1]);
	// //sceSysUtilSendSystemNotificationWithText(222, buff);
	// //sprintf(buff, "NoiseTexture: %i\nRefractionDepthTexture: %i\n", fcxValues[2], fcxValues[3]);
	// //sceSysUtilSendSystemNotificationWithText(222, buff);
	// //sprintf(buff, "ReflectionTex: %i\ngReflectionMipCount: %i\n", fcxValues[4], fcxValues[5]);
	// //sceSysUtilSendSystemNotificationWithText(222, buff);
	// if(fcxValues[0] > 0 && !fcxBools[0]) {
		// sprintf(buff, "ReflectionTex2: %i", fcxValues[0]);
		 //sceSysUtilSendSystemNotificationWithText(222, "ok"); 
		// *(uint32*)(0x382A510 + 0x400000) = 190; 
		// fcxBools[0] = 1;
	// }
	// if(fcxValues[1] > 0 && !fcxBools[1]) {
		// sprintf(buff, "RefractionTexture: %i", fcxValues[1]);
		// sceSysUtilSendSystemNotificationWithText(222, buff); 
		// *(uint32*)(0x382A514 + 0x400000) = 152; 
		// fcxBools[1] = 1;
	// }
	// if(fcxValues[4] > 0 && !fcxBools[4]) {
		// sprintf(buff, "ReflectionTex: %i", fcxValues[4]);
		// sceSysUtilSendSystemNotificationWithText(222, buff); 
		// //*(uint32*)(0x381C5EC + 0x400000) = 55; 
		// fcxBools[4] = 1;
	// }
	// if(fcxValues[2] > 0 && !fcxBools[2]) {
		// sprintf(buff, "NoiseTexture: %i", fcxValues[2]);
		// sceSysUtilSendSystemNotificationWithText(222, buff); 
		// *(uint32*)(0x382A518 + 0x400000) = 400; 
		// fcxBools[2] = 1;
	// }
	// if(fcxValues[3] > 0 && !fcxBools[3]) {
		// sprintf(buff, "RefractionDepthTexture: %i", fcxValues[3]);
		// sceSysUtilSendSystemNotificationWithText(222, buff); 
		// *(uint32*)(0x382A528 + 0x400000) = 400; 
		// fcxBools[3] = 1;
	// }
	// if(fcxValues[10] > 0 && !fcxBools[10]) {
		// sprintf(buff, "LightingTexture: %i", fcxValues[10]);
		// sceSysUtilSendSystemNotificationWithText(222, buff); 
		// *(uint32*)(0x382F244 + 0x400000) = 300; 
		// fcxBools[10] = 1;
	// }
	// if(fcxValues[11] > 0 && !fcxBools[11]) {
		// sprintf(buff, "ReflectionMatrix: %i", fcxValues[11]);
		// sceSysUtilSendSystemNotificationWithText(222, buff); 
		// //*(uint32*)(0x382F248 + 0x400000) = 250; 
		// fcxBools[11] = 1;
	// }
	// if(fcxValues[12] > 0 && !fcxBools[12]) {
		// sprintf(buff, "RefractionMatrix: %i", fcxValues[12]);
		// sceSysUtilSendSystemNotificationWithText(222, buff); 
		// //*(uint32*)(0x382F24C + 0x400000) = 250; 
		// fcxBools[12] = 1;
	// }
	// if(fcxValues[6] > 0 && !fcxBools[6]) {
		// sprintf(buff, "reflectionMSAA: %i, reflectionMSAA: %f", fcxValues[6], fcxValues[6]);
		// sceSysUtilSendSystemNotificationWithText(222, buff); 
		// *(uint32*)(0x39D2690 + 0x400000) = 48059179; 
		// fcxBools[6] = 1;
	// }
	// if(fcxValues[7] > 0 && !fcxBools[7]) {
		// sprintf(buff, "SSAO: %i, SSAO: %f", fcxValues[7], fcxValues[7]);
		// sceSysUtilSendSystemNotificationWithText(222, buff); 
		// *(uint32*)(0x39D26B8 + 0x400000) = 48059179; 
		// fcxBools[7] = 1;
	// }
	// if(fcxValues[8] > 0 && !fcxBools[8]) {
		// sprintf(buff, "fxaa: %i, fxaa: %f", fcxValues[8], fcxValues[8]);
		// sceSysUtilSendSystemNotificationWithText(222, buff); 
		// *(uint32*)(0x39D2960 + 0x400000) = 48059179; 
		// fcxBools[8] = 1;
	// }
	// if(fcxValues[9] > 0 && !fcxBools[9]) {
		// sprintf(buff, "txaa: %i, txaa: %f", fcxValues[9], fcxValues[9]);
		// sceSysUtilSendSystemNotificationWithText(222, buff); 
		// *(uint32*)(0x39D2988 + 0x400000) = 48059179; 
		// fcxBools[9] = 1;
	// }
	// if(fcxValues[5] > 0 && !fcxBools[5]) {
		// sprintf(buff, "gReflectionMipCount: %i", fcxValues[5]);
		// sceSysUtilSendSystemNotificationWithText(222, buff); 
		// *(uint32*)(0x381C5F0 + 0x400000) = 58; 
		// fcxBools[5] = 1;
	// }
*/
