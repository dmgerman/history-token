multiline_comment|/*&n; *  linux/arch/arm/mach-rpc/riscpc.c&n; *&n; *  Copyright (C) 1998-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Architecture specific fixups.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/serial_8250.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/domain.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
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
id|MT_DEVICE
)brace
comma
multiline_comment|/* VRAM&t;&t;*/
(brace
(paren
id|u32
)paren
id|IO_BASE
comma
id|IO_START
comma
id|IO_SIZE
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* IO space&t;*/
(brace
id|EASI_BASE
comma
id|EASI_START
comma
id|EASI_SIZE
comma
id|MT_DEVICE
)brace
multiline_comment|/* EASI space&t;*/
)brace
suffix:semicolon
DECL|function|rpc_map_io
r_static
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
comma
id|ARRAY_SIZE
c_func
(paren
id|rpc_io_desc
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Turn off floppy.&n;&t; */
id|outb
c_func
(paren
l_int|0xc
comma
l_int|0x3f2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * RiscPC can&squot;t handle half-word loads and stores&n;&t; */
id|elf_hwcap
op_and_assign
op_complement
id|HWCAP_HALF
suffix:semicolon
)brace
DECL|variable|acornfb_resources
r_static
r_struct
id|resource
id|acornfb_resources
(braket
)braket
op_assign
(brace
(brace
multiline_comment|/* VIDC */
dot
id|start
op_assign
l_int|0x03400000
comma
dot
id|end
op_assign
l_int|0x035fffff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|IRQ_VSYNCPULSE
comma
dot
id|end
op_assign
id|IRQ_VSYNCPULSE
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|acornfb_device
r_static
r_struct
id|platform_device
id|acornfb_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;acornfb&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|dev
op_assign
(brace
dot
id|coherent_dma_mask
op_assign
l_int|0xffffffff
comma
)brace
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|acornfb_resources
)paren
comma
dot
id|resource
op_assign
id|acornfb_resources
comma
)brace
suffix:semicolon
DECL|variable|iomd_resources
r_static
r_struct
id|resource
id|iomd_resources
(braket
)braket
op_assign
(brace
(brace
dot
id|start
op_assign
l_int|0x03200000
comma
dot
id|end
op_assign
l_int|0x0320ffff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|iomd_device
r_static
r_struct
id|platform_device
id|iomd_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;iomd&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|iomd_resources
)paren
comma
dot
id|resource
op_assign
id|iomd_resources
comma
)brace
suffix:semicolon
DECL|variable|kbd_device
r_static
r_struct
id|platform_device
id|kbd_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;kart&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|dev
op_assign
(brace
dot
id|parent
op_assign
op_amp
id|iomd_device.dev
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|serial_platform_data
r_static
r_struct
id|plat_serial8250_port
id|serial_platform_data
(braket
)braket
op_assign
(brace
(brace
dot
id|mapbase
op_assign
l_int|0x03010fe0
comma
dot
id|irq
op_assign
l_int|10
comma
dot
id|uartclk
op_assign
l_int|1843200
comma
dot
id|regshift
op_assign
l_int|2
comma
dot
id|iotype
op_assign
id|UPIO_MEM
comma
dot
id|flags
op_assign
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_IOREMAP
op_or
id|UPF_SKIP_TEST
comma
)brace
comma
(brace
)brace
comma
)brace
suffix:semicolon
DECL|variable|serial_device
r_static
r_struct
id|platform_device
id|serial_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;serial8250&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|dev
op_assign
(brace
dot
id|platform_data
op_assign
id|serial_platform_data
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|devs
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|iomd_device
comma
op_amp
id|kbd_device
comma
op_amp
id|serial_device
comma
op_amp
id|acornfb_device
comma
)brace
suffix:semicolon
DECL|function|rpc_init
r_static
r_int
id|__init
id|rpc_init
c_func
(paren
r_void
)paren
(brace
r_return
id|platform_add_devices
c_func
(paren
id|devs
comma
id|ARRAY_SIZE
c_func
(paren
id|devs
)paren
)paren
suffix:semicolon
)brace
DECL|variable|rpc_init
id|arch_initcall
c_func
(paren
id|rpc_init
)paren
suffix:semicolon
r_extern
r_struct
id|sys_timer
id|ioc_timer
suffix:semicolon
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
dot
id|timer
op_assign
op_amp
id|ioc_timer
comma
id|MACHINE_END
eof
