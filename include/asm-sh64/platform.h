macro_line|#ifndef __ASM_SH64_PLATFORM_H
DECL|macro|__ASM_SH64_PLATFORM_H
mdefine_line|#define __ASM_SH64_PLATFORM_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/platform.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; *&n; * benedict.gaster@superh.com:&t; 3rd May 2002&n; *    Added support for ramdisk, removing statically linked romfs at the same time.&n; */
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * Platform definition structure.&n; */
DECL|struct|sh64_platform
r_struct
id|sh64_platform
(brace
DECL|member|readonly_rootfs
r_int
r_int
id|readonly_rootfs
suffix:semicolon
DECL|member|ramdisk_flags
r_int
r_int
id|ramdisk_flags
suffix:semicolon
DECL|member|initial_root_dev
r_int
r_int
id|initial_root_dev
suffix:semicolon
DECL|member|loader_type
r_int
r_int
id|loader_type
suffix:semicolon
DECL|member|initrd_start
r_int
r_int
id|initrd_start
suffix:semicolon
DECL|member|initrd_size
r_int
r_int
id|initrd_size
suffix:semicolon
DECL|member|fpu_flags
r_int
r_int
id|fpu_flags
suffix:semicolon
DECL|member|io_res_count
r_int
r_int
id|io_res_count
suffix:semicolon
DECL|member|kram_res_count
r_int
r_int
id|kram_res_count
suffix:semicolon
DECL|member|xram_res_count
r_int
r_int
id|xram_res_count
suffix:semicolon
DECL|member|rom_res_count
r_int
r_int
id|rom_res_count
suffix:semicolon
DECL|member|io_res_p
r_struct
id|resource
op_star
id|io_res_p
suffix:semicolon
DECL|member|kram_res_p
r_struct
id|resource
op_star
id|kram_res_p
suffix:semicolon
DECL|member|xram_res_p
r_struct
id|resource
op_star
id|xram_res_p
suffix:semicolon
DECL|member|rom_res_p
r_struct
id|resource
op_star
id|rom_res_p
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sh64_platform
id|platform_parms
suffix:semicolon
r_extern
r_int
r_int
r_int
id|memory_start
comma
id|memory_end
suffix:semicolon
r_extern
r_int
r_int
r_int
id|fpu_in_use
suffix:semicolon
r_extern
r_int
id|platform_int_priority
(braket
id|NR_INTC_IRQS
)braket
suffix:semicolon
DECL|macro|FPU_FLAGS
mdefine_line|#define FPU_FLAGS&t;&t;(platform_parms.fpu_flags)
DECL|macro|STANDARD_IO_RESOURCES
mdefine_line|#define STANDARD_IO_RESOURCES&t;(platform_parms.io_res_count)
DECL|macro|STANDARD_KRAM_RESOURCES
mdefine_line|#define STANDARD_KRAM_RESOURCES&t;(platform_parms.kram_res_count)
DECL|macro|STANDARD_XRAM_RESOURCES
mdefine_line|#define STANDARD_XRAM_RESOURCES&t;(platform_parms.xram_res_count)
DECL|macro|STANDARD_ROM_RESOURCES
mdefine_line|#define STANDARD_ROM_RESOURCES&t;(platform_parms.rom_res_count)
multiline_comment|/*&n; * Kernel Memory description, Respectively:&n; * code = last but one memory descriptor&n; * data = last memory descriptor&n; */
DECL|macro|code_resource
mdefine_line|#define code_resource (platform_parms.kram_res_p[STANDARD_KRAM_RESOURCES - 2])
DECL|macro|data_resource
mdefine_line|#define data_resource (platform_parms.kram_res_p[STANDARD_KRAM_RESOURCES - 1])
multiline_comment|/* Be prepared to 64-bit sign extensions */
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)       ((((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT) &amp; 0x000fffff)
DECL|macro|PFN_DOWN
mdefine_line|#define PFN_DOWN(x)     (((x) &gt;&gt; PAGE_SHIFT) &amp; 0x000fffff)
DECL|macro|PFN_PHYS
mdefine_line|#define PFN_PHYS(x)     ((x) &lt;&lt; PAGE_SHIFT)
macro_line|#endif&t;/* __ASM_SH64_PLATFORM_H */
eof
