multiline_comment|/*&n; * structures and definitions for the int 15, ax=e820 memory map&n; * scheme.&n; *&n; * In a nutshell, arch/i386/boot/setup.S populates a scratch table&n; * in the empty_zero_block that contains a list of usable address/size&n; * duples.   In arch/i386/kernel/setup.c, this information is&n; * transferred into the e820map, and in arch/i386/mm/init.c, that&n; * new information is used to mark pages reserved or not.&n; *&n; */
macro_line|#ifndef __E820_HEADER
DECL|macro|__E820_HEADER
mdefine_line|#define __E820_HEADER
DECL|macro|E820MAP
mdefine_line|#define E820MAP&t;0x2d0&t;&t;/* our map */
DECL|macro|E820MAX
mdefine_line|#define E820MAX&t;32&t;&t;/* number of entries in E820MAP */
DECL|macro|E820NR
mdefine_line|#define E820NR&t;0x1e8&t;&t;/* # entries in E820MAP */
DECL|macro|E820_RAM
mdefine_line|#define E820_RAM&t;1
DECL|macro|E820_RESERVED
mdefine_line|#define E820_RESERVED&t;2
DECL|macro|E820_ACPI
mdefine_line|#define E820_ACPI&t;3 /* usable as RAM once ACPI tables have been read */
DECL|macro|E820_NVS
mdefine_line|#define E820_NVS&t;4
DECL|macro|HIGH_MEMORY
mdefine_line|#define HIGH_MEMORY&t;(1024*1024)
macro_line|#ifndef __ASSEMBLY__
DECL|struct|e820map
r_struct
id|e820map
(brace
DECL|member|nr_map
r_int
id|nr_map
suffix:semicolon
DECL|struct|e820entry
r_struct
id|e820entry
(brace
DECL|member|addr
r_int
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* start of memory segment */
DECL|member|size
r_int
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of memory segment */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* type of memory segment */
DECL|member|map
)brace
id|map
(braket
id|E820MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|e820map
id|e820
suffix:semicolon
macro_line|#endif/*!__ASSEMBLY__*/
macro_line|#endif/*__E820_HEADER*/
eof
