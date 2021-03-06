multiline_comment|/*&n; * drivers/video/geode/display_gx1.c&n; *   -- Geode GX1 display controller&n; *&n; * Copyright (C) 2005 Arcom Control Systems Ltd.&n; *&n; * Based on AMD&squot;s original 2.4 driver:&n; *   Copyright (C) 2004 Advanced Micro Devices, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &quot;geodefb.h&quot;
macro_line|#include &quot;display_gx1.h&quot;
DECL|variable|gx1_conf_reg_lock
r_static
id|spinlock_t
id|gx1_conf_reg_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|gx1_read_conf_reg
r_static
id|u8
id|gx1_read_conf_reg
c_func
(paren
id|u8
id|reg
)paren
(brace
id|u8
id|val
comma
id|ccr3
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gx1_conf_reg_lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
id|CONFIG_CCR3
comma
l_int|0x22
)paren
suffix:semicolon
id|ccr3
op_assign
id|inb
c_func
(paren
l_int|0x23
)paren
suffix:semicolon
id|outb
c_func
(paren
id|CONFIG_CCR3
comma
l_int|0x22
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ccr3
op_or
id|CONFIG_CCR3_MAPEN
comma
l_int|0x23
)paren
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
l_int|0x22
)paren
suffix:semicolon
id|val
op_assign
id|inb
c_func
(paren
l_int|0x23
)paren
suffix:semicolon
id|outb
c_func
(paren
id|CONFIG_CCR3
comma
l_int|0x22
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ccr3
comma
l_int|0x23
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gx1_conf_reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|gx1_gx_base
r_int
id|gx1_gx_base
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|gx1_read_conf_reg
c_func
(paren
id|CONFIG_GCR
)paren
op_amp
l_int|0x03
)paren
op_lshift
l_int|30
suffix:semicolon
)brace
DECL|function|gx1_frame_buffer_size
r_int
id|gx1_frame_buffer_size
c_func
(paren
r_void
)paren
(brace
r_void
id|__iomem
op_star
id|mc_regs
suffix:semicolon
id|u32
id|bank_cfg
suffix:semicolon
r_int
id|d
suffix:semicolon
r_int
id|dram_size
op_assign
l_int|0
comma
id|fb_base
suffix:semicolon
id|mc_regs
op_assign
id|ioremap
c_func
(paren
id|gx1_gx_base
c_func
(paren
)paren
op_plus
l_int|0x8400
comma
l_int|0x100
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mc_regs
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Calculate the total size of both DIMM0 and DIMM1. */
id|bank_cfg
op_assign
id|readl
c_func
(paren
id|mc_regs
op_plus
id|MC_BANK_CFG
)paren
suffix:semicolon
r_for
c_loop
(paren
id|d
op_assign
l_int|0
suffix:semicolon
id|d
OL
l_int|2
suffix:semicolon
id|d
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|bank_cfg
op_amp
id|MC_BCFG_DIMM0_PG_SZ_MASK
)paren
op_ne
id|MC_BCFG_DIMM0_PG_SZ_NO_DIMM
)paren
id|dram_size
op_add_assign
l_int|0x400000
op_lshift
(paren
(paren
id|bank_cfg
op_amp
id|MC_BCFG_DIMM0_SZ_MASK
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|bank_cfg
op_rshift_assign
l_int|16
suffix:semicolon
multiline_comment|/* look at DIMM1 next */
)brace
id|fb_base
op_assign
(paren
id|readl
c_func
(paren
id|mc_regs
op_plus
id|MC_GBASE_ADD
)paren
op_amp
id|MC_GADD_GBADD_MASK
)paren
op_lshift
l_int|19
suffix:semicolon
id|iounmap
c_func
(paren
id|mc_regs
)paren
suffix:semicolon
r_return
id|dram_size
op_minus
id|fb_base
suffix:semicolon
)brace
DECL|function|gx1_set_mode
r_static
r_void
id|gx1_set_mode
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|geodefb_par
op_star
id|par
op_assign
id|info-&gt;par
suffix:semicolon
id|u32
id|gcfg
comma
id|tcfg
comma
id|ocfg
comma
id|dclk_div
comma
id|val
suffix:semicolon
r_int
id|hactive
comma
id|hblankstart
comma
id|hsyncstart
comma
id|hsyncend
comma
id|hblankend
comma
id|htotal
suffix:semicolon
r_int
id|vactive
comma
id|vblankstart
comma
id|vsyncstart
comma
id|vsyncend
comma
id|vblankend
comma
id|vtotal
suffix:semicolon
multiline_comment|/* Unlock the display controller registers. */
id|readl
c_func
(paren
id|par-&gt;dc_regs
op_plus
id|DC_UNLOCK
)paren
suffix:semicolon
id|writel
c_func
(paren
id|DC_UNLOCK_CODE
comma
id|par-&gt;dc_regs
op_plus
id|DC_UNLOCK
)paren
suffix:semicolon
id|gcfg
op_assign
id|readl
c_func
(paren
id|par-&gt;dc_regs
op_plus
id|DC_GENERAL_CFG
)paren
suffix:semicolon
id|tcfg
op_assign
id|readl
c_func
(paren
id|par-&gt;dc_regs
op_plus
id|DC_TIMING_CFG
)paren
suffix:semicolon
multiline_comment|/* Blank the display and disable the timing generator. */
id|tcfg
op_and_assign
op_complement
(paren
id|DC_TCFG_BLKE
op_or
id|DC_TCFG_TGEN
)paren
suffix:semicolon
id|writel
c_func
(paren
id|tcfg
comma
id|par-&gt;dc_regs
op_plus
id|DC_TIMING_CFG
)paren
suffix:semicolon
multiline_comment|/* Wait for pending memory requests before disabling the FIFO load. */
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/* Disable FIFO load and compression. */
id|gcfg
op_and_assign
op_complement
(paren
id|DC_GCFG_DFLE
op_or
id|DC_GCFG_CMPE
op_or
id|DC_GCFG_DECE
)paren
suffix:semicolon
id|writel
c_func
(paren
id|gcfg
comma
id|par-&gt;dc_regs
op_plus
id|DC_GENERAL_CFG
)paren
suffix:semicolon
multiline_comment|/* Setup DCLK and its divisor. */
id|gcfg
op_and_assign
op_complement
id|DC_GCFG_DCLK_MASK
suffix:semicolon
id|writel
c_func
(paren
id|gcfg
comma
id|par-&gt;dc_regs
op_plus
id|DC_GENERAL_CFG
)paren
suffix:semicolon
id|par-&gt;vid_ops
op_member_access_from_pointer
id|set_dclk
c_func
(paren
id|info
)paren
suffix:semicolon
id|dclk_div
op_assign
id|DC_GCFG_DCLK_DIV_1
suffix:semicolon
multiline_comment|/* FIXME: may need to divide DCLK by 2 sometimes? */
id|gcfg
op_or_assign
id|dclk_div
suffix:semicolon
id|writel
c_func
(paren
id|gcfg
comma
id|par-&gt;dc_regs
op_plus
id|DC_GENERAL_CFG
)paren
suffix:semicolon
multiline_comment|/* Wait for the clock generatation to settle.  This is needed since&n;&t; * some of the register writes that follow require that clock to be&n;&t; * present. */
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* FIXME: seems a little long */
multiline_comment|/*&n;&t; * Setup new mode.&n;&t; */
multiline_comment|/* Clear all unused feature bits. */
id|gcfg
op_assign
id|DC_GCFG_VRDY
op_or
id|dclk_div
suffix:semicolon
multiline_comment|/* Set FIFO priority (default 6/5) and enable. */
multiline_comment|/* FIXME: increase fifo priority for 1280x1024 modes? */
id|gcfg
op_or_assign
(paren
l_int|6
op_lshift
id|DC_GCFG_DFHPEL_POS
)paren
op_or
(paren
l_int|5
op_lshift
id|DC_GCFG_DFHPSL_POS
)paren
op_or
id|DC_GCFG_DFLE
suffix:semicolon
multiline_comment|/* FIXME: Set pixel and line double bits if necessary. */
multiline_comment|/* Framebuffer start offset. */
id|writel
c_func
(paren
l_int|0
comma
id|par-&gt;dc_regs
op_plus
id|DC_FB_ST_OFFSET
)paren
suffix:semicolon
multiline_comment|/* Line delta and line buffer length. */
id|writel
c_func
(paren
id|info-&gt;fix.line_length
op_rshift
l_int|2
comma
id|par-&gt;dc_regs
op_plus
id|DC_LINE_DELTA
)paren
suffix:semicolon
id|writel
c_func
(paren
(paren
(paren
id|info-&gt;var.xres
op_star
id|info-&gt;var.bits_per_pixel
op_div
l_int|8
)paren
op_rshift
l_int|3
)paren
op_plus
l_int|2
comma
id|par-&gt;dc_regs
op_plus
id|DC_BUF_SIZE
)paren
suffix:semicolon
multiline_comment|/* Output configuration. Enable panel data, set pixel format. */
id|ocfg
op_assign
id|DC_OCFG_PCKE
op_or
id|DC_OCFG_PDEL
op_or
id|DC_OCFG_PDEH
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;var.bits_per_pixel
op_eq
l_int|8
)paren
id|ocfg
op_or_assign
id|DC_OCFG_8BPP
suffix:semicolon
multiline_comment|/* Enable timing generator, sync and FP data. */
id|tcfg
op_assign
id|DC_TCFG_FPPE
op_or
id|DC_TCFG_HSYE
op_or
id|DC_TCFG_VSYE
op_or
id|DC_TCFG_BLKE
op_or
id|DC_TCFG_TGEN
suffix:semicolon
multiline_comment|/* Horizontal and vertical timings. */
id|hactive
op_assign
id|info-&gt;var.xres
suffix:semicolon
id|hblankstart
op_assign
id|hactive
suffix:semicolon
id|hsyncstart
op_assign
id|hblankstart
op_plus
id|info-&gt;var.right_margin
suffix:semicolon
id|hsyncend
op_assign
id|hsyncstart
op_plus
id|info-&gt;var.hsync_len
suffix:semicolon
id|hblankend
op_assign
id|hsyncend
op_plus
id|info-&gt;var.left_margin
suffix:semicolon
id|htotal
op_assign
id|hblankend
suffix:semicolon
id|vactive
op_assign
id|info-&gt;var.yres
suffix:semicolon
id|vblankstart
op_assign
id|vactive
suffix:semicolon
id|vsyncstart
op_assign
id|vblankstart
op_plus
id|info-&gt;var.lower_margin
suffix:semicolon
id|vsyncend
op_assign
id|vsyncstart
op_plus
id|info-&gt;var.vsync_len
suffix:semicolon
id|vblankend
op_assign
id|vsyncend
op_plus
id|info-&gt;var.upper_margin
suffix:semicolon
id|vtotal
op_assign
id|vblankend
suffix:semicolon
id|val
op_assign
(paren
id|hactive
op_minus
l_int|1
)paren
op_or
(paren
(paren
id|htotal
op_minus
l_int|1
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|par-&gt;dc_regs
op_plus
id|DC_H_TIMING_1
)paren
suffix:semicolon
id|val
op_assign
(paren
id|hblankstart
op_minus
l_int|1
)paren
op_or
(paren
(paren
id|hblankend
op_minus
l_int|1
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|par-&gt;dc_regs
op_plus
id|DC_H_TIMING_2
)paren
suffix:semicolon
id|val
op_assign
(paren
id|hsyncstart
op_minus
l_int|1
)paren
op_or
(paren
(paren
id|hsyncend
op_minus
l_int|1
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|par-&gt;dc_regs
op_plus
id|DC_H_TIMING_3
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|par-&gt;dc_regs
op_plus
id|DC_FP_H_TIMING
)paren
suffix:semicolon
id|val
op_assign
(paren
id|vactive
op_minus
l_int|1
)paren
op_or
(paren
(paren
id|vtotal
op_minus
l_int|1
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|par-&gt;dc_regs
op_plus
id|DC_V_TIMING_1
)paren
suffix:semicolon
id|val
op_assign
(paren
id|vblankstart
op_minus
l_int|1
)paren
op_or
(paren
(paren
id|vblankend
op_minus
l_int|1
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|par-&gt;dc_regs
op_plus
id|DC_V_TIMING_2
)paren
suffix:semicolon
id|val
op_assign
(paren
id|vsyncstart
op_minus
l_int|1
)paren
op_or
(paren
(paren
id|vsyncend
op_minus
l_int|1
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|par-&gt;dc_regs
op_plus
id|DC_V_TIMING_3
)paren
suffix:semicolon
id|val
op_assign
(paren
id|vsyncstart
op_minus
l_int|2
)paren
op_or
(paren
(paren
id|vsyncend
op_minus
l_int|2
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|par-&gt;dc_regs
op_plus
id|DC_FP_V_TIMING
)paren
suffix:semicolon
multiline_comment|/* Write final register values. */
id|writel
c_func
(paren
id|ocfg
comma
id|par-&gt;dc_regs
op_plus
id|DC_OUTPUT_CFG
)paren
suffix:semicolon
id|writel
c_func
(paren
id|tcfg
comma
id|par-&gt;dc_regs
op_plus
id|DC_TIMING_CFG
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* delay after TIMING_CFG. FIXME: perhaps a little long */
id|writel
c_func
(paren
id|gcfg
comma
id|par-&gt;dc_regs
op_plus
id|DC_GENERAL_CFG
)paren
suffix:semicolon
id|par-&gt;vid_ops
op_member_access_from_pointer
id|configure_display
c_func
(paren
id|info
)paren
suffix:semicolon
multiline_comment|/* Relock display controller registers */
id|writel
c_func
(paren
l_int|0
comma
id|par-&gt;dc_regs
op_plus
id|DC_UNLOCK
)paren
suffix:semicolon
multiline_comment|/* FIXME: write line_length and bpp to Graphics Pipeline GP_BLT_STATUS&n;&t; * register. */
)brace
DECL|function|gx1_set_hw_palette_reg
r_static
r_void
id|gx1_set_hw_palette_reg
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|regno
comma
r_int
id|red
comma
r_int
id|green
comma
r_int
id|blue
)paren
(brace
r_struct
id|geodefb_par
op_star
id|par
op_assign
id|info-&gt;par
suffix:semicolon
r_int
id|val
suffix:semicolon
multiline_comment|/* Hardware palette is in RGB 6-6-6 format. */
id|val
op_assign
(paren
id|red
op_lshift
l_int|2
)paren
op_amp
l_int|0x3f000
suffix:semicolon
id|val
op_or_assign
(paren
id|green
op_rshift
l_int|4
)paren
op_amp
l_int|0x00fc0
suffix:semicolon
id|val
op_or_assign
(paren
id|blue
op_rshift
l_int|10
)paren
op_amp
l_int|0x0003f
suffix:semicolon
id|writel
c_func
(paren
id|regno
comma
id|par-&gt;dc_regs
op_plus
id|DC_PAL_ADDRESS
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|par-&gt;dc_regs
op_plus
id|DC_PAL_DATA
)paren
suffix:semicolon
)brace
DECL|variable|gx1_dc_ops
r_struct
id|geode_dc_ops
id|gx1_dc_ops
op_assign
(brace
dot
id|set_mode
op_assign
id|gx1_set_mode
comma
dot
id|set_palette_reg
op_assign
id|gx1_set_hw_palette_reg
comma
)brace
suffix:semicolon
eof
