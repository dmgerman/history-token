multiline_comment|/*&n; * 1. load vmlinuz&n; *&n; * CONFIG_MEMORY_START  &t;+-----------------------+&n; *&t;&t;&t;&t;|        vmlinuz&t;|&n; *&t;&t;&t;&t;+-----------------------+&n; * 2. decompressed&n; *&n; * CONFIG_MEMORY_START  &t;+-----------------------+&n; *&t;&t;&t;&t;|        vmlinuz&t;|&n; *&t;&t;&t;&t;+-----------------------+&n; *&t;&t;&t;&t;|&t;&t;&t;|&n; * BOOT_RELOC_ADDR&t;&t;+-----------------------+&n; *&t;&t;&t;&t;|&t;&t; &t;|&n; * KERNEL_DECOMPRESS_ADDR &t;+-----------------------+&n; *&t;&t;&t;&t;|  &t;vmlinux&t;&t;|&n; *&t;&t;&t;&t;+-----------------------+&n; *&n; * 3. relocate copy &amp; jump code&n; *&n; * CONFIG_MEMORY_START  &t;+-----------------------+&n; *&t;&t;&t;&t;|        vmlinuz&t;|&n; *&t;&t;&t;&t;+-----------------------+&n; *&t;&t;&t;&t;|&t;&t;&t;|&n; * BOOT_RELOC_ADDR&t;&t;+-----------------------+&n; *&t;&t;&t;&t;|    boot(copy&amp;jump)&t;|&n; * KERNEL_DECOMPRESS_ADDR &t;+-----------------------+&n; *&t;&t;&t;&t;|  &t;vmlinux&t;&t;|&n; *&t;&t;&t;&t;+-----------------------+&n; *&n; * 4. relocate decompressed kernel&n; *&n; * CONFIG_MEMORY_START  &t;+-----------------------+&n; *&t;&t;&t;&t;|        vmlinux&t;|&n; *&t;&t;&t;&t;+-----------------------+&n; *&t;&t;&t;&t;|&t;&t;&t;|&n; * BOOT_RELOC_ADDR&t;&t;+-----------------------+&n; *&t;&t;&t;&t;|     boot(copy&amp;jump) &t;|&n; * KERNEL_DECOMPRESS_ADDR &t;+-----------------------+&n; *&t;&t;&t;&t;|  &t;&t;&t;|&n; *&t;&t;&t;&t;+-----------------------+&n; *&n; */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|__val
mdefine_line|#define __val(x)&t;x
macro_line|#else
DECL|macro|__val
mdefine_line|#define __val(x)&t;(x)
macro_line|#endif
DECL|macro|DECOMPRESS_OFFSET_BASE
mdefine_line|#define DECOMPRESS_OFFSET_BASE&t;__val(0x00900000)
DECL|macro|BOOT_RELOC_SIZE
mdefine_line|#define BOOT_RELOC_SIZE&t;&t;__val(0x00001000)
DECL|macro|KERNEL_EXEC_ADDR
mdefine_line|#define KERNEL_EXEC_ADDR&t;__val(CONFIG_MEMORY_START)
DECL|macro|KERNEL_DECOMPRESS_ADDR
mdefine_line|#define KERNEL_DECOMPRESS_ADDR&t;__val(CONFIG_MEMORY_START + &bslash;&n;&t;&t;&t;&t;      DECOMPRESS_OFFSET_BASE + BOOT_RELOC_SIZE)
DECL|macro|KERNEL_ENTRY
mdefine_line|#define KERNEL_ENTRY&t;&t;__val(CONFIG_MEMORY_START + 0x1000)
DECL|macro|BOOT_EXEC_ADDR
mdefine_line|#define BOOT_EXEC_ADDR&t;&t;__val(CONFIG_MEMORY_START)
DECL|macro|BOOT_RELOC_ADDR
mdefine_line|#define BOOT_RELOC_ADDR&t;&t;__val(CONFIG_MEMORY_START + DECOMPRESS_OFFSET_BASE)
eof
