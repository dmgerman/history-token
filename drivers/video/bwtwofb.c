multiline_comment|/* $Id: bwtwofb.c,v 1.14 2001/02/13 01:17:14 davem Exp $&n; * bwtwofb.c: BWtwo frame buffer driver&n; *&n; * Copyright (C) 1998 Jakub Jelinek   (jj@ultra.linux.cz)&n; * Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; * Copyright (C) 1997 Eddie C. Dost   (ecd@skynet.be)&n; * Copyright (C) 1998 Pavel Machek    (pavel@ucw.cz)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;video/sbusfb.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#if !defined(__sparc_v9__) &amp;&amp; !defined(__mc68000__)
macro_line|#include &lt;asm/sun4paddr.h&gt;
macro_line|#endif
macro_line|#include &lt;video/fbcon-mfb.h&gt;
multiline_comment|/* OBio addresses for the bwtwo registers */
DECL|macro|BWTWO_REGISTER_OFFSET
mdefine_line|#define BWTWO_REGISTER_OFFSET 0x400000
DECL|struct|bw2_regs
r_struct
id|bw2_regs
(brace
DECL|member|bt
r_struct
id|bt_regs
id|bt
suffix:semicolon
DECL|member|control
r_volatile
id|u8
id|control
suffix:semicolon
DECL|member|status
r_volatile
id|u8
id|status
suffix:semicolon
DECL|member|cursor_start
r_volatile
id|u8
id|cursor_start
suffix:semicolon
DECL|member|cursor_end
r_volatile
id|u8
id|cursor_end
suffix:semicolon
DECL|member|h_blank_start
r_volatile
id|u8
id|h_blank_start
suffix:semicolon
DECL|member|h_blank_end
r_volatile
id|u8
id|h_blank_end
suffix:semicolon
DECL|member|h_sync_start
r_volatile
id|u8
id|h_sync_start
suffix:semicolon
DECL|member|h_sync_end
r_volatile
id|u8
id|h_sync_end
suffix:semicolon
DECL|member|comp_sync_end
r_volatile
id|u8
id|comp_sync_end
suffix:semicolon
DECL|member|v_blank_start_high
r_volatile
id|u8
id|v_blank_start_high
suffix:semicolon
DECL|member|v_blank_start_low
r_volatile
id|u8
id|v_blank_start_low
suffix:semicolon
DECL|member|v_blank_end
r_volatile
id|u8
id|v_blank_end
suffix:semicolon
DECL|member|v_sync_start
r_volatile
id|u8
id|v_sync_start
suffix:semicolon
DECL|member|v_sync_end
r_volatile
id|u8
id|v_sync_end
suffix:semicolon
DECL|member|xfer_holdoff_start
r_volatile
id|u8
id|xfer_holdoff_start
suffix:semicolon
DECL|member|xfer_holdoff_end
r_volatile
id|u8
id|xfer_holdoff_end
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Status Register Constants */
DECL|macro|BWTWO_SR_RES_MASK
mdefine_line|#define BWTWO_SR_RES_MASK&t;0x70
DECL|macro|BWTWO_SR_1600_1280
mdefine_line|#define BWTWO_SR_1600_1280&t;0x50
DECL|macro|BWTWO_SR_1152_900_76_A
mdefine_line|#define BWTWO_SR_1152_900_76_A&t;0x40
DECL|macro|BWTWO_SR_1152_900_76_B
mdefine_line|#define BWTWO_SR_1152_900_76_B&t;0x60
DECL|macro|BWTWO_SR_ID_MASK
mdefine_line|#define BWTWO_SR_ID_MASK&t;0x0f
DECL|macro|BWTWO_SR_ID_MONO
mdefine_line|#define BWTWO_SR_ID_MONO&t;0x02
DECL|macro|BWTWO_SR_ID_MONO_ECL
mdefine_line|#define BWTWO_SR_ID_MONO_ECL&t;0x03
DECL|macro|BWTWO_SR_ID_MSYNC
mdefine_line|#define BWTWO_SR_ID_MSYNC&t;0x04
DECL|macro|BWTWO_SR_ID_NOCONN
mdefine_line|#define BWTWO_SR_ID_NOCONN&t;0x0a
multiline_comment|/* Control Register Constants */
DECL|macro|BWTWO_CTL_ENABLE_INTS
mdefine_line|#define BWTWO_CTL_ENABLE_INTS   0x80
DECL|macro|BWTWO_CTL_ENABLE_VIDEO
mdefine_line|#define BWTWO_CTL_ENABLE_VIDEO  0x40
DECL|macro|BWTWO_CTL_ENABLE_TIMING
mdefine_line|#define BWTWO_CTL_ENABLE_TIMING 0x20
DECL|macro|BWTWO_CTL_ENABLE_CURCMP
mdefine_line|#define BWTWO_CTL_ENABLE_CURCMP 0x10
DECL|macro|BWTWO_CTL_XTAL_MASK
mdefine_line|#define BWTWO_CTL_XTAL_MASK     0x0C
DECL|macro|BWTWO_CTL_DIVISOR_MASK
mdefine_line|#define BWTWO_CTL_DIVISOR_MASK  0x03
multiline_comment|/* Status Register Constants */
DECL|macro|BWTWO_STAT_PENDING_INT
mdefine_line|#define BWTWO_STAT_PENDING_INT  0x80
DECL|macro|BWTWO_STAT_MSENSE_MASK
mdefine_line|#define BWTWO_STAT_MSENSE_MASK  0x70
DECL|macro|BWTWO_STAT_ID_MASK
mdefine_line|#define BWTWO_STAT_ID_MASK      0x0f
DECL|variable|bw2_mmap_map
r_static
r_struct
id|sbus_mmap_map
id|bw2_mmap_map
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|1
)paren
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|bw2_blank
r_static
r_void
id|bw2_blank
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|tmp
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|fb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|tmp
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|fb-&gt;s.bw2.regs-&gt;control
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
id|BWTWO_CTL_ENABLE_VIDEO
suffix:semicolon
id|sbus_writeb
c_func
(paren
id|tmp
comma
op_amp
id|fb-&gt;s.bw2.regs-&gt;control
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|fb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|bw2_unblank
r_static
r_void
id|bw2_unblank
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|tmp
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|fb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|tmp
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|fb-&gt;s.bw2.regs-&gt;control
)paren
suffix:semicolon
id|tmp
op_or_assign
id|BWTWO_CTL_ENABLE_VIDEO
suffix:semicolon
id|sbus_writeb
c_func
(paren
id|tmp
comma
op_amp
id|fb-&gt;s.bw2.regs-&gt;control
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|fb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|bw2_margins
r_static
r_void
id|bw2_margins
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|x_margin
comma
r_int
id|y_margin
)paren
(brace
id|p-&gt;screen_base
op_add_assign
(paren
id|y_margin
op_minus
id|fb-&gt;y_margin
)paren
op_star
id|p-&gt;line_length
op_plus
(paren
(paren
id|x_margin
op_minus
id|fb-&gt;x_margin
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
id|u8
id|bw2regs_1600
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x14
comma
l_int|0x8b
comma
l_int|0x15
comma
l_int|0x28
comma
l_int|0x16
comma
l_int|0x03
comma
l_int|0x17
comma
l_int|0x13
comma
l_int|0x18
comma
l_int|0x7b
comma
l_int|0x19
comma
l_int|0x05
comma
l_int|0x1a
comma
l_int|0x34
comma
l_int|0x1b
comma
l_int|0x2e
comma
l_int|0x1c
comma
l_int|0x00
comma
l_int|0x1d
comma
l_int|0x0a
comma
l_int|0x1e
comma
l_int|0xff
comma
l_int|0x1f
comma
l_int|0x01
comma
l_int|0x10
comma
l_int|0x21
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u8
id|bw2regs_ecl
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x14
comma
l_int|0x65
comma
l_int|0x15
comma
l_int|0x1e
comma
l_int|0x16
comma
l_int|0x04
comma
l_int|0x17
comma
l_int|0x0c
comma
l_int|0x18
comma
l_int|0x5e
comma
l_int|0x19
comma
l_int|0x03
comma
l_int|0x1a
comma
l_int|0xa7
comma
l_int|0x1b
comma
l_int|0x23
comma
l_int|0x1c
comma
l_int|0x00
comma
l_int|0x1d
comma
l_int|0x08
comma
l_int|0x1e
comma
l_int|0xff
comma
l_int|0x1f
comma
l_int|0x01
comma
l_int|0x10
comma
l_int|0x20
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u8
id|bw2regs_analog
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x14
comma
l_int|0xbb
comma
l_int|0x15
comma
l_int|0x2b
comma
l_int|0x16
comma
l_int|0x03
comma
l_int|0x17
comma
l_int|0x13
comma
l_int|0x18
comma
l_int|0xb0
comma
l_int|0x19
comma
l_int|0x03
comma
l_int|0x1a
comma
l_int|0xa6
comma
l_int|0x1b
comma
l_int|0x22
comma
l_int|0x1c
comma
l_int|0x01
comma
l_int|0x1d
comma
l_int|0x05
comma
l_int|0x1e
comma
l_int|0xff
comma
l_int|0x1f
comma
l_int|0x01
comma
l_int|0x10
comma
l_int|0x20
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u8
id|bw2regs_76hz
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x14
comma
l_int|0xb7
comma
l_int|0x15
comma
l_int|0x27
comma
l_int|0x16
comma
l_int|0x03
comma
l_int|0x17
comma
l_int|0x0f
comma
l_int|0x18
comma
l_int|0xae
comma
l_int|0x19
comma
l_int|0x03
comma
l_int|0x1a
comma
l_int|0xae
comma
l_int|0x1b
comma
l_int|0x2a
comma
l_int|0x1c
comma
l_int|0x01
comma
l_int|0x1d
comma
l_int|0x09
comma
l_int|0x1e
comma
l_int|0xff
comma
l_int|0x1f
comma
l_int|0x01
comma
l_int|0x10
comma
l_int|0x24
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u8
id|bw2regs_66hz
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x14
comma
l_int|0xbb
comma
l_int|0x15
comma
l_int|0x2b
comma
l_int|0x16
comma
l_int|0x04
comma
l_int|0x17
comma
l_int|0x14
comma
l_int|0x18
comma
l_int|0xae
comma
l_int|0x19
comma
l_int|0x03
comma
l_int|0x1a
comma
l_int|0xa8
comma
l_int|0x1b
comma
l_int|0x24
comma
l_int|0x1c
comma
l_int|0x01
comma
l_int|0x1d
comma
l_int|0x05
comma
l_int|0x1e
comma
l_int|0xff
comma
l_int|0x1f
comma
l_int|0x01
comma
l_int|0x10
comma
l_int|0x20
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|idstring
(braket
l_int|60
)braket
id|__initdata
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|function|bwtwofb_init
r_char
id|__init
op_star
id|bwtwofb_init
c_func
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_struct
id|fb_fix_screeninfo
op_star
id|fix
op_assign
op_amp
id|fb-&gt;fix
suffix:semicolon
r_struct
id|display
op_star
id|disp
op_assign
op_amp
id|fb-&gt;disp
suffix:semicolon
r_struct
id|fbtype
op_star
id|type
op_assign
op_amp
id|fb-&gt;type
suffix:semicolon
macro_line|#ifdef CONFIG_SUN4
r_int
r_int
id|phys
op_assign
id|sun4_bwtwo_physaddr
suffix:semicolon
r_struct
id|resource
id|res
suffix:semicolon
macro_line|#else
r_int
r_int
id|phys
op_assign
id|fb-&gt;sbdp-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
suffix:semicolon
macro_line|#endif
r_struct
id|resource
op_star
id|resp
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
macro_line|#ifndef FBCON_HAS_MFB
r_return
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SUN4
id|res.start
op_assign
id|phys
suffix:semicolon
id|res.end
op_assign
id|res.start
op_plus
id|BWTWO_REGISTER_OFFSET
op_plus
r_sizeof
(paren
r_struct
id|bw2_regs
)paren
op_minus
l_int|1
suffix:semicolon
id|res.flags
op_assign
id|IORESOURCE_IO
op_or
(paren
id|fb-&gt;iospace
op_amp
l_int|0xff
)paren
suffix:semicolon
id|resp
op_assign
op_amp
id|res
suffix:semicolon
macro_line|#else
id|resp
op_assign
op_amp
id|fb-&gt;sbdp-&gt;resource
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|fb-&gt;s.bw2.regs
)paren
(brace
id|fb-&gt;s.bw2.regs
op_assign
(paren
r_struct
id|bw2_regs
op_star
)paren
id|sbus_ioremap
c_func
(paren
id|resp
comma
id|BWTWO_REGISTER_OFFSET
comma
r_sizeof
(paren
r_struct
id|bw2_regs
)paren
comma
l_string|&quot;bw2 regs&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|ARCH_SUN4
)paren
op_logical_and
(paren
op_logical_neg
id|prom_getbool
c_func
(paren
id|fb-&gt;prom_node
comma
l_string|&quot;width&quot;
)paren
)paren
)paren
(brace
multiline_comment|/* Ugh, broken PROM didn&squot;t initialize us.&n;&t;&t;&t; * Let&squot;s deal with this ourselves.&n;&t;&t;&t; */
id|u8
id|status
comma
id|mon
suffix:semicolon
id|u8
op_star
id|p
suffix:semicolon
r_int
id|sizechange
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|fb-&gt;s.bw2.regs-&gt;status
)paren
suffix:semicolon
id|mon
op_assign
id|status
op_amp
id|BWTWO_SR_RES_MASK
suffix:semicolon
r_switch
c_cond
(paren
id|status
op_amp
id|BWTWO_SR_ID_MASK
)paren
(brace
r_case
id|BWTWO_SR_ID_MONO_ECL
suffix:colon
r_if
c_cond
(paren
id|mon
op_eq
id|BWTWO_SR_1600_1280
)paren
(brace
id|p
op_assign
id|bw2regs_1600
suffix:semicolon
id|fb-&gt;type.fb_width
op_assign
l_int|1600
suffix:semicolon
id|fb-&gt;type.fb_height
op_assign
l_int|1280
suffix:semicolon
id|sizechange
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|p
op_assign
id|bw2regs_ecl
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BWTWO_SR_ID_MONO
suffix:colon
id|p
op_assign
id|bw2regs_analog
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BWTWO_SR_ID_MSYNC
suffix:colon
r_if
c_cond
(paren
id|mon
op_eq
id|BWTWO_SR_1152_900_76_A
op_logical_or
id|mon
op_eq
id|BWTWO_SR_1152_900_76_B
)paren
id|p
op_assign
id|bw2regs_76hz
suffix:semicolon
r_else
id|p
op_assign
id|bw2regs_66hz
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BWTWO_SR_ID_NOCONN
suffix:colon
r_return
l_int|NULL
suffix:semicolon
r_default
suffix:colon
macro_line|#ifndef CONFIG_FB_SUN3
id|prom_printf
c_func
(paren
l_string|&quot;bw2: can&squot;t handle SR %02x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;&t;
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* fool gcc. */
)brace
r_for
c_loop
(paren
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_add_assign
l_int|2
)paren
(brace
id|u8
op_star
id|regp
op_assign
op_amp
(paren
(paren
id|u8
op_star
)paren
id|fb-&gt;s.bw2.regs
)paren
(braket
id|p
(braket
l_int|0
)braket
)braket
suffix:semicolon
id|sbus_writeb
c_func
(paren
id|p
(braket
l_int|1
)braket
comma
id|regp
)paren
suffix:semicolon
)brace
)brace
)brace
id|strcpy
c_func
(paren
id|fb-&gt;info.modename
comma
l_string|&quot;BWtwo&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;BWtwo&quot;
)paren
suffix:semicolon
id|fix-&gt;line_length
op_assign
id|fb-&gt;var.xres_virtual
op_rshift
l_int|3
suffix:semicolon
id|fix-&gt;accel
op_assign
id|FB_ACCEL_SUN_BWTWO
suffix:semicolon
id|disp-&gt;scrollmode
op_assign
id|SCROLL_YREDRAW
suffix:semicolon
id|disp-&gt;inverse
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|disp-&gt;screen_base
)paren
(brace
id|disp-&gt;screen_base
op_assign
(paren
r_char
op_star
)paren
id|sbus_ioremap
c_func
(paren
id|resp
comma
l_int|0
comma
id|type-&gt;fb_size
comma
l_string|&quot;bw2 ram&quot;
)paren
suffix:semicolon
)brace
id|disp-&gt;screen_base
op_add_assign
id|fix-&gt;line_length
op_star
id|fb-&gt;y_margin
op_plus
(paren
id|fb-&gt;x_margin
op_rshift
l_int|3
)paren
suffix:semicolon
id|fb-&gt;dispsw
op_assign
id|fbcon_mfb
suffix:semicolon
id|fix-&gt;visual
op_assign
id|FB_VISUAL_MONO01
suffix:semicolon
macro_line|#ifndef CONFIG_SUN4
id|fb-&gt;blank
op_assign
id|bw2_blank
suffix:semicolon
id|fb-&gt;unblank
op_assign
id|bw2_unblank
suffix:semicolon
id|prom_getproperty
c_func
(paren
id|fb-&gt;sbdp-&gt;prom_node
comma
l_string|&quot;address&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|vaddr
comma
r_sizeof
(paren
id|vaddr
)paren
)paren
suffix:semicolon
id|fb-&gt;physbase
op_assign
id|__get_phys
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
)paren
suffix:semicolon
macro_line|#endif
id|fb-&gt;margins
op_assign
id|bw2_margins
suffix:semicolon
id|fb-&gt;mmap_map
op_assign
id|bw2_mmap_map
suffix:semicolon
macro_line|#ifdef __sparc_v9__
id|sprintf
c_func
(paren
id|idstring
comma
l_string|&quot;bwtwo at %016lx&quot;
comma
id|phys
)paren
suffix:semicolon
macro_line|#else&t;
id|sprintf
c_func
(paren
id|idstring
comma
l_string|&quot;bwtwo at %x.%08lx&quot;
comma
id|fb-&gt;iospace
comma
id|phys
)paren
suffix:semicolon
macro_line|#endif
r_return
id|idstring
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
