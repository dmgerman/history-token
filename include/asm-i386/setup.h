multiline_comment|/*&n; *&t;Just a place holder. We don&squot;t want to have to test x86 before&n; *&t;we include stuff&n; */
macro_line|#ifndef _i386_SETUP_H
DECL|macro|_i386_SETUP_H
mdefine_line|#define _i386_SETUP_H
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)&t;(((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_DOWN
mdefine_line|#define PFN_DOWN(x)&t;((x) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_PHYS
mdefine_line|#define PFN_PHYS(x)&t;((x) &lt;&lt; PAGE_SHIFT)
multiline_comment|/*&n; * Reserved space for vmalloc and iomap - defined in asm/page.h&n; */
DECL|macro|MAXMEM_PFN
mdefine_line|#define MAXMEM_PFN&t;PFN_DOWN(MAXMEM)
DECL|macro|MAX_NONPAE_PFN
mdefine_line|#define MAX_NONPAE_PFN&t;(1 &lt;&lt; 20)
multiline_comment|/*&n; * This is set up by the setup-routine at boot-time&n; */
DECL|macro|PARAM
mdefine_line|#define PARAM&t;((unsigned char *)empty_zero_page)
DECL|macro|SCREEN_INFO
mdefine_line|#define SCREEN_INFO (*(struct screen_info *) (PARAM+0))
DECL|macro|EXT_MEM_K
mdefine_line|#define EXT_MEM_K (*(unsigned short *) (PARAM+2))
DECL|macro|ALT_MEM_K
mdefine_line|#define ALT_MEM_K (*(unsigned long *) (PARAM+0x1e0))
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
DECL|macro|VIDEO_MODE
mdefine_line|#define VIDEO_MODE (*(unsigned short *) (PARAM+0x1FA))
DECL|macro|ORIG_ROOT_DEV
mdefine_line|#define ORIG_ROOT_DEV (*(unsigned short *) (PARAM+0x1FC))
DECL|macro|AUX_DEVICE_INFO
mdefine_line|#define AUX_DEVICE_INFO (*(unsigned char *) (PARAM+0x1FF))
DECL|macro|LOADER_TYPE
mdefine_line|#define LOADER_TYPE (*(unsigned char *) (PARAM+0x210))
DECL|macro|KERNEL_START
mdefine_line|#define KERNEL_START (*(unsigned long *) (PARAM+0x214))
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START (*(unsigned long *) (PARAM+0x218))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE (*(unsigned long *) (PARAM+0x21c))
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE ((char *) (PARAM+2048))
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 256
macro_line|#endif /* _i386_SETUP_H */
eof
