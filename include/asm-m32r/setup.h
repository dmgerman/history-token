multiline_comment|/*&n; * This is set up by the setup-routine at boot-time&n; */
DECL|macro|PARAM
mdefine_line|#define PARAM&t;&t;&t;((unsigned char *)empty_zero_page)
DECL|macro|MOUNT_ROOT_RDONLY
mdefine_line|#define MOUNT_ROOT_RDONLY&t;(*(unsigned long *) (PARAM+0x000))
DECL|macro|RAMDISK_FLAGS
mdefine_line|#define RAMDISK_FLAGS&t;&t;(*(unsigned long *) (PARAM+0x004))
DECL|macro|ORIG_ROOT_DEV
mdefine_line|#define ORIG_ROOT_DEV&t;&t;(*(unsigned long *) (PARAM+0x008))
DECL|macro|LOADER_TYPE
mdefine_line|#define LOADER_TYPE&t;&t;(*(unsigned long *) (PARAM+0x00c))
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START&t;&t;(*(unsigned long *) (PARAM+0x010))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE&t;&t;(*(unsigned long *) (PARAM+0x014))
DECL|macro|M32R_CPUCLK
mdefine_line|#define M32R_CPUCLK&t;&t;(*(unsigned long *) (PARAM+0x018))
DECL|macro|M32R_BUSCLK
mdefine_line|#define M32R_BUSCLK&t;&t;(*(unsigned long *) (PARAM+0x01c))
DECL|macro|M32R_TIMER_DIVIDE
mdefine_line|#define M32R_TIMER_DIVIDE&t;(*(unsigned long *) (PARAM+0x020))
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE&t;&t;((char *) (PARAM+0x100))
DECL|macro|SCREEN_INFO
mdefine_line|#define SCREEN_INFO&t;&t;(*(struct screen_info *) (PARAM+0x200))
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE&t;(256)
DECL|macro|RAMDISK_IMAGE_START_MASK
mdefine_line|#define RAMDISK_IMAGE_START_MASK&t;(0x07FF)
DECL|macro|RAMDISK_PROMPT_FLAG
mdefine_line|#define RAMDISK_PROMPT_FLAG&t;&t;(0x8000)
DECL|macro|RAMDISK_LOAD_FLAG
mdefine_line|#define RAMDISK_LOAD_FLAG&t;&t;(0x4000)
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)&t;(((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_DOWN
mdefine_line|#define PFN_DOWN(x)&t;((x) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_PHYS
mdefine_line|#define PFN_PHYS(x)&t;((x) &lt;&lt; PAGE_SHIFT)
r_extern
r_int
r_int
id|memory_start
suffix:semicolon
r_extern
r_int
r_int
id|memory_end
suffix:semicolon
eof
