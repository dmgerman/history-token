multiline_comment|/*&n; * linux/arch/arm/mach-omap/common.c&n; *&n; * Code common to all OMAP machines.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/arch/clocks.h&gt;
macro_line|#include &lt;asm/arch/board.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * OMAP I/O mapping&n; *&n; * The machine specific code may provide the extra mapping besides the&n; * default mapping provided here.&n; * ----------------------------------------------------------------------------&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|omap_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|IO_VIRT
comma
id|IO_PHYS
comma
id|IO_SIZE
comma
id|MT_DEVICE
)brace
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_OMAP730
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|omap730_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|OMAP730_DSP_BASE
comma
id|OMAP730_DSP_START
comma
id|OMAP730_DSP_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|OMAP730_DSPREG_BASE
comma
id|OMAP730_DSPREG_START
comma
id|OMAP730_DSPREG_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|OMAP730_SRAM_BASE
comma
id|OMAP730_SRAM_START
comma
id|OMAP730_SRAM_SIZE
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP1510
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|omap1510_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|OMAP1510_DSP_BASE
comma
id|OMAP1510_DSP_START
comma
id|OMAP1510_DSP_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|OMAP1510_DSPREG_BASE
comma
id|OMAP1510_DSPREG_START
comma
id|OMAP1510_DSPREG_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|OMAP1510_SRAM_BASE
comma
id|OMAP1510_SRAM_START
comma
id|OMAP1510_SRAM_SIZE
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP1610
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|omap1610_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|OMAP1610_DSP_BASE
comma
id|OMAP1610_DSP_START
comma
id|OMAP1610_DSP_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|OMAP1610_DSPREG_BASE
comma
id|OMAP1610_DSPREG_START
comma
id|OMAP1610_DSPREG_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|OMAP1610_SRAM_BASE
comma
id|OMAP1610_SRAM_START
comma
id|OMAP1610_SRAM_SIZE
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP5912
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|omap5912_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|OMAP5912_DSP_BASE
comma
id|OMAP5912_DSP_START
comma
id|OMAP5912_DSP_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|OMAP5912_DSPREG_BASE
comma
id|OMAP5912_DSPREG_START
comma
id|OMAP5912_DSPREG_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|OMAP5912_SRAM_BASE
comma
id|OMAP5912_SRAM_START
comma
id|OMAP5912_SRAM_SIZE
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|initialized
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
DECL|function|_omap_map_io
r_static
r_void
id|__init
id|_omap_map_io
c_func
(paren
r_void
)paren
(brace
id|initialized
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We have to initialize the IO space mapping before we can run&n;&t; * cpu_is_omapxxx() macros. */
id|iotable_init
c_func
(paren
id|omap_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|omap_io_desc
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_OMAP730
r_if
c_cond
(paren
id|cpu_is_omap730
c_func
(paren
)paren
)paren
(brace
id|iotable_init
c_func
(paren
id|omap730_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|omap730_io_desc
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP1510
r_if
c_cond
(paren
id|cpu_is_omap1510
c_func
(paren
)paren
)paren
(brace
id|iotable_init
c_func
(paren
id|omap1510_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|omap1510_io_desc
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP1610
r_if
c_cond
(paren
id|cpu_is_omap1610
c_func
(paren
)paren
)paren
(brace
id|iotable_init
c_func
(paren
id|omap1610_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|omap1610_io_desc
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP5912
r_if
c_cond
(paren
id|cpu_is_omap5912
c_func
(paren
)paren
)paren
(brace
id|iotable_init
c_func
(paren
id|omap5912_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|omap5912_io_desc
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* REVISIT: Refer to OMAP5910 Errata, Advisory SYS_1: &quot;Timeout Abort&n;&t; * on a Posted Write in the TIPB Bridge&quot;.&n;&t; */
id|omap_writew
c_func
(paren
l_int|0x0
comma
id|MPU_PUBLIC_TIPB_CNTL_REG
)paren
suffix:semicolon
id|omap_writew
c_func
(paren
l_int|0x0
comma
id|MPU_PRIVATE_TIPB_CNTL_REG
)paren
suffix:semicolon
multiline_comment|/* Must init clocks early to assure that timer interrupt works&n;&t; */
id|init_ck
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This should only get called from board specific init&n; */
DECL|function|omap_map_io
r_void
id|omap_map_io
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
id|_omap_map_io
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_int
id|omap_bootloader_tag_len
suffix:semicolon
r_extern
id|u8
id|omap_bootloader_tag
(braket
)braket
suffix:semicolon
DECL|function|__omap_get_per_info
r_const
r_void
op_star
id|__omap_get_per_info
c_func
(paren
id|u16
id|tag
comma
r_int
id|len
)paren
(brace
r_struct
id|omap_board_info_entry
op_star
id|info
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_OMAP_BOOT_TAG
r_if
c_cond
(paren
id|omap_bootloader_tag_len
OG
l_int|4
)paren
id|info
op_assign
(paren
r_struct
id|omap_board_info_entry
op_star
)paren
id|omap_bootloader_tag
suffix:semicolon
r_while
c_loop
(paren
id|info
op_ne
l_int|NULL
)paren
(brace
id|u8
op_star
id|next
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;tag
op_eq
id|tag
)paren
r_break
suffix:semicolon
id|next
op_assign
(paren
id|u8
op_star
)paren
id|info
op_plus
r_sizeof
(paren
op_star
id|info
)paren
op_plus
id|info-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|next
op_ge
id|omap_bootloader_tag
op_plus
id|omap_bootloader_tag_len
)paren
id|info
op_assign
l_int|NULL
suffix:semicolon
r_else
id|info
op_assign
(paren
r_struct
id|omap_board_info_entry
op_star
)paren
id|next
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|info
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;len
op_ne
id|len
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;OMAP per_info: Length mismatch with tag %x (want %d, got %d)&bslash;n&quot;
comma
id|tag
comma
id|len
comma
id|info-&gt;len
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|info-&gt;data
suffix:semicolon
)brace
DECL|variable|__omap_get_per_info
id|EXPORT_SYMBOL
c_func
(paren
id|__omap_get_per_info
)paren
suffix:semicolon
DECL|function|omap_add_serial_console
r_static
r_int
id|__init
id|omap_add_serial_console
c_func
(paren
r_void
)paren
(brace
r_const
r_struct
id|omap_uart_info
op_star
id|info
suffix:semicolon
id|info
op_assign
id|omap_get_per_info
c_func
(paren
id|OMAP_TAG_UART
comma
r_struct
id|omap_uart_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
op_ne
l_int|NULL
op_logical_and
id|info-&gt;console_uart
)paren
(brace
r_static
r_char
id|speed
(braket
l_int|11
)braket
comma
op_star
id|opt
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;console_speed
)paren
(brace
id|snprintf
c_func
(paren
id|speed
comma
r_sizeof
(paren
id|speed
)paren
comma
l_string|&quot;%u&quot;
comma
id|info-&gt;console_speed
)paren
suffix:semicolon
id|opt
op_assign
id|speed
suffix:semicolon
)brace
r_return
id|add_preferred_console
c_func
(paren
l_string|&quot;ttyS&quot;
comma
id|info-&gt;console_uart
op_minus
l_int|1
comma
id|opt
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|omap_add_serial_console
id|console_initcall
c_func
(paren
id|omap_add_serial_console
)paren
suffix:semicolon
eof
