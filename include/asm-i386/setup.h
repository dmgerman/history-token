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
DECL|macro|PARAM_SIZE
mdefine_line|#define PARAM_SIZE 2048
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 2048
DECL|macro|OLD_CL_MAGIC_ADDR
mdefine_line|#define OLD_CL_MAGIC_ADDR&t;0x90020
DECL|macro|OLD_CL_MAGIC
mdefine_line|#define OLD_CL_MAGIC&t;&t;0xA33F
DECL|macro|OLD_CL_BASE_ADDR
mdefine_line|#define OLD_CL_BASE_ADDR&t;0x90000
DECL|macro|OLD_CL_OFFSET
mdefine_line|#define OLD_CL_OFFSET&t;&t;0x90022
DECL|macro|NEW_CL_POINTER
mdefine_line|#define NEW_CL_POINTER&t;&t;0x228&t;/* Relative to real mode data */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * This is set up by the setup-routine at boot-time&n; */
r_extern
r_int
r_char
id|boot_params
(braket
id|PARAM_SIZE
)braket
suffix:semicolon
DECL|macro|PARAM
mdefine_line|#define PARAM&t;(boot_params)
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
DECL|macro|IST_INFO
mdefine_line|#define IST_INFO   (*(struct ist_info *) (PARAM+0x60))
DECL|macro|DRIVE_INFO
mdefine_line|#define DRIVE_INFO (*(struct drive_info_struct *) (PARAM+0x80))
DECL|macro|SYS_DESC_TABLE
mdefine_line|#define SYS_DESC_TABLE (*(struct sys_desc_table_struct*)(PARAM+0xa0))
DECL|macro|EFI_SYSTAB
mdefine_line|#define EFI_SYSTAB ((efi_system_table_t *) *((unsigned long *)(PARAM+0x1c4)))
DECL|macro|EFI_MEMDESC_SIZE
mdefine_line|#define EFI_MEMDESC_SIZE (*((unsigned long *) (PARAM+0x1c8)))
DECL|macro|EFI_MEMDESC_VERSION
mdefine_line|#define EFI_MEMDESC_VERSION (*((unsigned long *) (PARAM+0x1cc)))
DECL|macro|EFI_MEMMAP
mdefine_line|#define EFI_MEMMAP ((efi_memory_desc_t *) *((unsigned long *)(PARAM+0x1d0)))
DECL|macro|EFI_MEMMAP_SIZE
mdefine_line|#define EFI_MEMMAP_SIZE (*((unsigned long *) (PARAM+0x1d4)))
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
DECL|macro|EDID_INFO
mdefine_line|#define EDID_INFO   (*(struct edid_info *) (PARAM+0x140))
DECL|macro|EDD_NR
mdefine_line|#define EDD_NR     (*(unsigned char *) (PARAM+EDDNR))
DECL|macro|EDD_MBR_SIG_NR
mdefine_line|#define EDD_MBR_SIG_NR (*(unsigned char *) (PARAM+EDD_MBR_SIG_NR_BUF))
DECL|macro|EDD_MBR_SIGNATURE
mdefine_line|#define EDD_MBR_SIGNATURE ((unsigned int *) (PARAM+EDD_MBR_SIG_BUF))
DECL|macro|EDD_BUF
mdefine_line|#define EDD_BUF     ((struct edd_info *) (PARAM+EDDBUF))
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _i386_SETUP_H */
eof
