multiline_comment|/*&n; *  linux/include/asm-arm/mach/arch.h&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
multiline_comment|/*&n; * The size of struct machine_desc&n; *   (for assembler code)&n; */
DECL|macro|SIZEOF_MACHINE_DESC
mdefine_line|#define SIZEOF_MACHINE_DESC&t;48
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|setup_initrd
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|setup_ramdisk
c_func
(paren
r_int
id|doload
comma
r_int
id|prompt
comma
r_int
id|start
comma
r_int
r_int
id|rd_sz
)paren
suffix:semicolon
r_struct
id|tag
suffix:semicolon
DECL|struct|machine_desc
r_struct
id|machine_desc
(brace
multiline_comment|/*&n;&t; * Note! The first four elements are used&n;&t; * by assembler code in head-armv.S&n;&t; */
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
multiline_comment|/* architecture number&t;*/
DECL|member|phys_ram
r_int
r_int
id|phys_ram
suffix:semicolon
multiline_comment|/* start of physical ram */
DECL|member|phys_io
r_int
r_int
id|phys_io
suffix:semicolon
multiline_comment|/* start of physical io&t;*/
DECL|member|io_pg_offst
r_int
r_int
id|io_pg_offst
suffix:semicolon
multiline_comment|/* byte offset for io &n;&t;&t;&t;&t;&t;&t; * page tabe entry&t;*/
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* architecture name&t;*/
DECL|member|param_offset
r_int
r_int
id|param_offset
suffix:semicolon
multiline_comment|/* parameter page&t;*/
DECL|member|video_start
r_int
r_int
id|video_start
suffix:semicolon
multiline_comment|/* start of video RAM&t;*/
DECL|member|video_end
r_int
r_int
id|video_end
suffix:semicolon
multiline_comment|/* end of video RAM&t;*/
DECL|member|reserve_lp0
r_int
r_int
id|reserve_lp0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* never has lp0&t;*/
DECL|member|reserve_lp1
r_int
r_int
id|reserve_lp1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* never has lp1&t;*/
DECL|member|reserve_lp2
r_int
r_int
id|reserve_lp2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* never has lp2&t;*/
DECL|member|soft_reboot
r_int
r_int
id|soft_reboot
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* soft reboot&t;&t;*/
DECL|member|fixup
r_void
(paren
op_star
id|fixup
)paren
(paren
r_struct
id|machine_desc
op_star
comma
r_struct
id|tag
op_star
comma
r_char
op_star
op_star
comma
r_struct
id|meminfo
op_star
)paren
suffix:semicolon
DECL|member|map_io
r_void
(paren
op_star
id|map_io
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* IO mapping function&t;*/
DECL|member|init_irq
r_void
(paren
op_star
id|init_irq
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Set of macros to define architecture features.  This is built into&n; * a table by the linker.&n; */
DECL|macro|MACHINE_START
mdefine_line|#define MACHINE_START(_type,_name)&t;&t;&bslash;&n;const struct machine_desc __mach_desc_##_type&t;&bslash;&n; __attribute__((__section__(&quot;.arch.info&quot;))) = {&t;&bslash;&n;&t;nr:&t;&t;MACH_TYPE_##_type,&t;&bslash;&n;&t;name:&t;&t;_name,
DECL|macro|MAINTAINER
mdefine_line|#define MAINTAINER(n)
DECL|macro|BOOT_MEM
mdefine_line|#define BOOT_MEM(_pram,_pio,_vio)&t;&t;&bslash;&n;&t;phys_ram:&t;_pram,&t;                &bslash;&n;&t;phys_io:&t;_pio,  &t;                &bslash;&n;&t;io_pg_offst:&t;((_vio)&gt;&gt;18)&amp;0xfffc,
DECL|macro|BOOT_PARAMS
mdefine_line|#define BOOT_PARAMS(_params)&t;&t;&t;&bslash;&n;&t;param_offset:&t;_params,
DECL|macro|VIDEO
mdefine_line|#define VIDEO(_start,_end)&t;&t;&t;&bslash;&n;&t;video_start:&t;_start,&t;&t;&t;&bslash;&n;&t;video_end:&t;_end,
DECL|macro|DISABLE_PARPORT
mdefine_line|#define DISABLE_PARPORT(_n)&t;&t;&t;&bslash;&n;&t;reserve_lp##_n:&t;1,
DECL|macro|BROKEN_HLT
mdefine_line|#define BROKEN_HLT /* unused */
DECL|macro|SOFT_REBOOT
mdefine_line|#define SOFT_REBOOT&t;&t;&t;&t;&bslash;&n;&t;soft_reboot:&t;1,
DECL|macro|FIXUP
mdefine_line|#define FIXUP(_func)&t;&t;&t;&t;&bslash;&n;&t;fixup:&t;&t;_func,
DECL|macro|MAPIO
mdefine_line|#define MAPIO(_func)&t;&t;&t;&t;&bslash;&n;&t;map_io:&t;&t;_func,
DECL|macro|INITIRQ
mdefine_line|#define INITIRQ(_func)&t;&t;&t;&t;&bslash;&n;&t;init_irq:&t;_func,
DECL|macro|MACHINE_END
mdefine_line|#define MACHINE_END&t;&t;&t;&t;&bslash;&n;};
macro_line|#endif
eof
