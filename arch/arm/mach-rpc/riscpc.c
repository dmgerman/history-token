multiline_comment|/*&n; *  linux/arch/arm/mach-rpc/riscpc.c&n; *&n; *  Copyright (C) 1998-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Architecture specific fixups.&n; */
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/proc/domain.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
r_extern
r_void
id|rpc_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|vram_size
suffix:semicolon
macro_line|#if 0
r_int
r_int
id|memc_ctrl_reg
suffix:semicolon
r_int
r_int
id|number_mfm_drives
suffix:semicolon
r_static
r_int
id|__init
id|parse_tag_acorn
c_func
(paren
r_const
r_struct
id|tag
op_star
id|tag
)paren
(brace
id|memc_ctrl_reg
op_assign
id|tag-&gt;u.acorn.memc_control_reg
suffix:semicolon
id|number_mfm_drives
op_assign
id|tag-&gt;u.acorn.adfsdrives
suffix:semicolon
r_switch
c_cond
(paren
id|tag-&gt;u.acorn.vram_pages
)paren
(brace
r_case
l_int|512
suffix:colon
id|vram_size
op_add_assign
id|PAGE_SIZE
op_star
l_int|256
suffix:semicolon
r_case
l_int|256
suffix:colon
id|vram_size
op_add_assign
id|PAGE_SIZE
op_star
l_int|256
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
macro_line|#if 0
r_if
c_cond
(paren
id|vram_size
)paren
(brace
id|desc-&gt;video_start
op_assign
l_int|0x02000000
suffix:semicolon
id|desc-&gt;video_end
op_assign
l_int|0x02000000
op_plus
id|vram_size
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
id|__tagtable
c_func
(paren
id|ATAG_ACORN
comma
id|parse_tag_acorn
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|__init
DECL|function|fixup_riscpc
id|fixup_riscpc
c_func
(paren
r_struct
id|machine_desc
op_star
id|desc
comma
r_struct
id|param_struct
op_star
id|unusd
comma
r_char
op_star
op_star
id|cmdline
comma
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
multiline_comment|/*&n;&t; * RiscPC can&squot;t handle half-word loads and stores&n;&t; */
id|elf_hwcap
op_and_assign
op_complement
id|HWCAP_HALF
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|rpc_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|SCREEN_BASE
comma
id|SCREEN_START
comma
l_int|2
op_star
l_int|1048576
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* VRAM&t;&t;*/
(brace
id|IO_BASE
comma
id|IO_START
comma
id|IO_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IO space&t;&t;*/
(brace
id|EASI_BASE
comma
id|EASI_START
comma
id|EASI_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* EASI space&t;*/
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|rpc_map_io
r_void
id|__init
id|rpc_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|rpc_io_desc
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|RISCPC
comma
l_string|&quot;Acorn-RiscPC&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x10000000
comma
l_int|0x03000000
comma
l_int|0xe0000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x10000100
)paren
id|DISABLE_PARPORT
c_func
(paren
l_int|0
)paren
id|DISABLE_PARPORT
c_func
(paren
l_int|1
)paren
id|FIXUP
c_func
(paren
id|fixup_riscpc
)paren
id|MAPIO
c_func
(paren
id|rpc_map_io
)paren
id|INITIRQ
c_func
(paren
id|rpc_init_irq
)paren
id|MACHINE_END
eof
