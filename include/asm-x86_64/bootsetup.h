macro_line|#ifndef _X86_64_BOOTSETUP_H
DECL|macro|_X86_64_BOOTSETUP_H
mdefine_line|#define _X86_64_BOOTSETUP_H 1
r_extern
r_char
id|x86_boot_params
(braket
l_int|2048
)braket
suffix:semicolon
multiline_comment|/*&n; * This is set up by the setup-routine at boot-time&n; */
DECL|macro|PARAM
mdefine_line|#define PARAM&t;((unsigned char *)x86_boot_params)
DECL|macro|SCREEN_INFO
mdefine_line|#define SCREEN_INFO (*(struct screen_info *) (PARAM+0))
DECL|macro|EXT_MEM_K
mdefine_line|#define EXT_MEM_K (*(unsigned short *) (PARAM+2))
DECL|macro|ALT_MEM_K
mdefine_line|#define ALT_MEM_K (*(unsigned int *) (PARAM+0x1e0))
DECL|macro|E820_MAP_NR
mdefine_line|#define E820_MAP_NR (*(char*) (PARAM+E820NR))
DECL|macro|E820_MAP
mdefine_line|#define E820_MAP    ((struct e820entry *) (PARAM+E820MAP))
DECL|macro|APM_BIOS_INFO
mdefine_line|#define APM_BIOS_INFO (*(struct apm_bios_info *) (PARAM+0x40))
DECL|macro|DRIVE_INFO
mdefine_line|#define DRIVE_INFO (*(struct drive_info_struct *) (PARAM+0x80))
DECL|macro|SYS_DESC_TABLE
mdefine_line|#define SYS_DESC_TABLE (*(struct sys_desc_table_struct*)(PARAM+0xa0))
DECL|macro|MOUNT_ROOT_RDONLY
mdefine_line|#define MOUNT_ROOT_RDONLY (*(unsigned short *) (PARAM+0x1F2))
DECL|macro|RAMDISK_FLAGS
mdefine_line|#define RAMDISK_FLAGS (*(unsigned short *) (PARAM+0x1F8))
DECL|macro|ORIG_ROOT_DEV
mdefine_line|#define ORIG_ROOT_DEV (*(unsigned short *) (PARAM+0x1FC))
DECL|macro|AUX_DEVICE_INFO
mdefine_line|#define AUX_DEVICE_INFO (*(unsigned char *) (PARAM+0x1FF))
DECL|macro|LOADER_TYPE
mdefine_line|#define LOADER_TYPE (*(unsigned char *) (PARAM+0x210))
DECL|macro|KERNEL_START
mdefine_line|#define KERNEL_START (*(unsigned int *) (PARAM+0x214))
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START (*(unsigned int *) (PARAM+0x218))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE (*(unsigned int *) (PARAM+0x21c))
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE saved_command_line
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 256
DECL|macro|RAMDISK_IMAGE_START_MASK
mdefine_line|#define RAMDISK_IMAGE_START_MASK  &t;0x07FF
DECL|macro|RAMDISK_PROMPT_FLAG
mdefine_line|#define RAMDISK_PROMPT_FLAG&t;&t;0x8000
DECL|macro|RAMDISK_LOAD_FLAG
mdefine_line|#define RAMDISK_LOAD_FLAG&t;&t;0x4000&t;
macro_line|#endif
eof
