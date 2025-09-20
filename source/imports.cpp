#include "types.h"
#include "imports.h"


//notifications
int (*sceSysUtilSendSystemNotificationWithText)(int messageType, const char *message);
#define resolve(module, name) orbis_syscall(591, module, #name, &name);

//libc
void *(*mmap)(void *addr, size_t len, int prot, int	flags, int fd, off_t offset);
//int(*access)(const char *path, int mode);
// int (*close)(int fd);
// ssize_t (*read)(int fd, void *buf, size_t nbyte);
// ssize_t (*write)(int fd, const void *buf, size_t count);
int (*open)(const char *path, int flags, int mode);
int(*islower)(int c);
int(*toupper)(int c);
int(*tolower)(int c);

int getpid() {
	return orbis_syscall(20);
}

void *sys_mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset) {
	return (void *)orbis_syscall(477, addr, len, prot, flags, fd, offset);
}

void *sys_munmap(void *addr, size_t len) {
	return (void *)orbis_syscall(479, addr, len);
}



void initImports() {
	int h = 0;
	//int kern;
	//orbis_syscall(594, "libkernel.sprx", 0, &kern, 0);
	//resolve(kern, open); 
	//kernel
	//sys_dynlib_load_prx("libkernel.sprx", &h);
	//sys_dynlib_dlsym(h, "access", &access);
	//sys_dynlib_dlsym(h, "sceKernelSleep", &sceKernelSleep);
	//sys_dynlib_dlsym(h, "sceKernelUsleep", &sceKernelUsleep);
	//sys_dynlib_dlsym(h, "sceKernelGetCpuTemperature", &sceKernelGetCpuTemperature);
	//sys_dynlib_dlsym(h, "sceKernelGetSocSensorTemperature", &sceKernelGetSocSensorTemperature);
	//sys_dynlib_dlsym(h, "read", &read);
	//sys_dynlib_dlsym(h, "write", &write);
	//sys_dynlib_dlsym(h, "open", &open);
	//sys_dynlib_dlsym(h, "close", &close);
	//sys_dynlib_dlsym(h, "stat", &stat);
	//sys_dynlib_dlsym(h, "unlink", &unlink);
	//sys_dynlib_dlsym(h, "usleep", &usleep);

	//threads
	//sys_dynlib_dlsym(h, "scePthreadCreate", &scePthreadCreate);
	//sys_dynlib_dlsym(h, "scePthreadExit", &scePthreadExit);
	//sys_dynlib_dlsym(h, "scePthreadDetach", &scePthreadDetach);
	//sys_dynlib_dlsym(h, "scePthreadJoin", &scePthreadJoin);
	//sys_dynlib_dlsym(h, "scePthreadGetprio", &scePthreadGetprio);

	//notify
	//int sysKern = sceKernelLoadStartModule("libkernel.sprx", 0, NULL, 0, 0, 0);
	//sys_dynlib_dlsym(sysKern, "open", &open);

	//libc
	sys_dynlib_load_prx("libSceLibcInternal.sprx", &h);
	// sys_dynlib_dlsym(h, "read", &read);
	// sys_dynlib_dlsym(h, "write", &write);
	// sys_dynlib_dlsym(h, "open", &open);
	// sys_dynlib_dlsym(h, "close", &close);
	sys_dynlib_dlsym(h, "isspace", &isspace);
	sys_dynlib_dlsym(h, "isupper", &isupper);
	sys_dynlib_dlsym(h, "islower", &islower);
	sys_dynlib_dlsym(h, "toupper", &toupper);
	//sys_dynlib_dlsym(h, "tolower", &tolower);

	//sys
	
	
	//notify
	int sysUtilHandle = sceKernelLoadStartModule("libSceSysUtil.sprx", 0, NULL, 0, 0, 0);
	sys_dynlib_dlsym(sysUtilHandle, "sceSysUtilSendSystemNotificationWithText", &sceSysUtilSendSystemNotificationWithText);
	
	//libc
	int sysLibc = sceKernelLoadStartModule("libSceLibcInternal.sprx", 0, NULL, 0, 0, 0);
	sys_dynlib_dlsym(sysLibc, "tolower", &tolower);
}
