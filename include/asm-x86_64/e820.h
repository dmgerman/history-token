multiline_comment|/*&n; * structures and definitions for the int 15, ax=e820 memory map&n; * scheme.&n; *&n; * In a nutshell, setup.S populates a scratch table in the&n; * empty_zero_block that contains a list of usable address/size&n; * duples.  setup.c, this information is transferred into the e820map,&n; * and in init.c/numa.c, that new information is used to mark pages&n; * reserved or not.&n; */
macro_line|#ifndef __E820_HEADER
DECL|macro|__E820_HEADER
mdefine_line|#define __E820_HEADER
macro_line|#include &lt;linux/mmzone.h&gt;
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
DECL|macro|LOWMEMSIZE
mdefine_line|#define LOWMEMSIZE()&t;(0x9f000)
macro_line|#ifndef __ASSEMBLY__
DECL|struct|e820entry
r_struct
id|e820entry
(brace
DECL|member|addr
id|u64
id|addr
suffix:semicolon
multiline_comment|/* start of memory segment */
DECL|member|size
id|u64
id|size
suffix:semicolon
multiline_comment|/* size of memory segment */
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* type of memory segment */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|e820map
r_struct
id|e820map
(brace
DECL|member|nr_map
r_int
id|nr_map
suffix:semicolon
DECL|member|map
r_struct
id|e820entry
id|map
(braket
id|E820MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
r_int
id|find_e820_area
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|add_memory_region
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_void
id|setup_memory_region
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|contig_e820_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|e820_end_of_ram
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|e820_reserve_resources
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|e820_print_map
c_func
(paren
r_char
op_star
id|who
)paren
suffix:semicolon
r_extern
r_int
id|e820_mapped
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_void
id|e820_bootmem_free
c_func
(paren
id|pg_data_t
op_star
id|pgdat
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|parse_memopt
c_func
(paren
r_char
op_star
id|p
comma
r_char
op_star
op_star
id|end
)paren
suffix:semicolon
r_extern
r_struct
id|e820map
id|e820
suffix:semicolon
macro_line|#endif/*!__ASSEMBLY__*/
macro_line|#endif/*__E820_HEADER*/
eof
