macro_line|#ifndef __ASM_SH64_SETUP_H
DECL|macro|__ASM_SH64_SETUP_H
mdefine_line|#define __ASM_SH64_SETUP_H
DECL|macro|PARAM
mdefine_line|#define PARAM ((unsigned char *)empty_zero_page)
DECL|macro|MOUNT_ROOT_RDONLY
mdefine_line|#define MOUNT_ROOT_RDONLY (*(unsigned long *) (PARAM+0x000))
DECL|macro|RAMDISK_FLAGS
mdefine_line|#define RAMDISK_FLAGS (*(unsigned long *) (PARAM+0x004))
DECL|macro|ORIG_ROOT_DEV
mdefine_line|#define ORIG_ROOT_DEV (*(unsigned long *) (PARAM+0x008))
DECL|macro|LOADER_TYPE
mdefine_line|#define LOADER_TYPE (*(unsigned long *) (PARAM+0x00c))
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START (*(unsigned long *) (PARAM+0x010))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE (*(unsigned long *) (PARAM+0x014))
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE ((char *) (PARAM+256))
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 256
macro_line|#endif /* __ASM_SH64_SETUP_H */
eof
