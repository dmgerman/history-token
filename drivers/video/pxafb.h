macro_line|#ifndef __PXAFB_H__
DECL|macro|__PXAFB_H__
mdefine_line|#define __PXAFB_H__
multiline_comment|/*&n; * linux/drivers/video/pxafb.h&n; *    -- Intel PXA250/210 LCD Controller Frame Buffer Device&n; *&n; *  Copyright (C) 1999 Eric A. Thomas.&n; *  Copyright (C) 2004 Jean-Frederic Clere.&n; *  Copyright (C) 2004 Ian Campbell.&n; *  Copyright (C) 2004 Jeff Lackey.&n; *   Based on sa1100fb.c Copyright (C) 1999 Eric A. Thomas&n; *  which in turn is&n; *   Based on acornfb.c Copyright (C) Russell King.&n; *&n; *  2001-08-03: Cliff Brake &lt;cbrake@acclent.com&gt;&n; *&t; - ported SA1100 code to PXA&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/* Shadows for LCD controller registers */
DECL|struct|pxafb_lcd_reg
r_struct
id|pxafb_lcd_reg
(brace
DECL|member|lccr0
r_int
r_int
id|lccr0
suffix:semicolon
DECL|member|lccr1
r_int
r_int
id|lccr1
suffix:semicolon
DECL|member|lccr2
r_int
r_int
id|lccr2
suffix:semicolon
DECL|member|lccr3
r_int
r_int
id|lccr3
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* PXA LCD DMA descriptor */
DECL|struct|pxafb_dma_descriptor
r_struct
id|pxafb_dma_descriptor
(brace
DECL|member|fdadr
r_int
r_int
id|fdadr
suffix:semicolon
DECL|member|fsadr
r_int
r_int
id|fsadr
suffix:semicolon
DECL|member|fidr
r_int
r_int
id|fidr
suffix:semicolon
DECL|member|ldcmd
r_int
r_int
id|ldcmd
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pxafb_info
r_struct
id|pxafb_info
(brace
DECL|member|fb
r_struct
id|fb_info
id|fb
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|max_bpp
id|u_int
id|max_bpp
suffix:semicolon
DECL|member|max_xres
id|u_int
id|max_xres
suffix:semicolon
DECL|member|max_yres
id|u_int
id|max_yres
suffix:semicolon
multiline_comment|/*&n;&t; * These are the addresses we mapped&n;&t; * the framebuffer memory region to.&n;&t; */
multiline_comment|/* raw memory addresses */
DECL|member|map_dma
id|dma_addr_t
id|map_dma
suffix:semicolon
multiline_comment|/* physical */
DECL|member|map_cpu
id|u_char
op_star
id|map_cpu
suffix:semicolon
multiline_comment|/* virtual */
DECL|member|map_size
id|u_int
id|map_size
suffix:semicolon
multiline_comment|/* addresses of pieces placed in raw buffer */
DECL|member|screen_cpu
id|u_char
op_star
id|screen_cpu
suffix:semicolon
multiline_comment|/* virtual address of frame buffer */
DECL|member|screen_dma
id|dma_addr_t
id|screen_dma
suffix:semicolon
multiline_comment|/* physical address of frame buffer */
DECL|member|palette_cpu
id|u16
op_star
id|palette_cpu
suffix:semicolon
multiline_comment|/* virtual address of palette memory */
DECL|member|palette_dma
id|dma_addr_t
id|palette_dma
suffix:semicolon
multiline_comment|/* physical address of palette memory */
DECL|member|palette_size
id|u_int
id|palette_size
suffix:semicolon
multiline_comment|/* DMA descriptors */
DECL|member|dmadesc_fblow_cpu
r_struct
id|pxafb_dma_descriptor
op_star
id|dmadesc_fblow_cpu
suffix:semicolon
DECL|member|dmadesc_fblow_dma
id|dma_addr_t
id|dmadesc_fblow_dma
suffix:semicolon
DECL|member|dmadesc_fbhigh_cpu
r_struct
id|pxafb_dma_descriptor
op_star
id|dmadesc_fbhigh_cpu
suffix:semicolon
DECL|member|dmadesc_fbhigh_dma
id|dma_addr_t
id|dmadesc_fbhigh_dma
suffix:semicolon
DECL|member|dmadesc_palette_cpu
r_struct
id|pxafb_dma_descriptor
op_star
id|dmadesc_palette_cpu
suffix:semicolon
DECL|member|dmadesc_palette_dma
id|dma_addr_t
id|dmadesc_palette_dma
suffix:semicolon
DECL|member|fdadr0
id|dma_addr_t
id|fdadr0
suffix:semicolon
DECL|member|fdadr1
id|dma_addr_t
id|fdadr1
suffix:semicolon
DECL|member|lccr0
id|u_int
id|lccr0
suffix:semicolon
DECL|member|lccr3
id|u_int
id|lccr3
suffix:semicolon
DECL|member|cmap_inverse
id|u_int
id|cmap_inverse
suffix:colon
l_int|1
comma
DECL|member|cmap_static
id|cmap_static
suffix:colon
l_int|1
comma
DECL|member|unused
id|unused
suffix:colon
l_int|30
suffix:semicolon
DECL|member|reg_lccr0
id|u_int
id|reg_lccr0
suffix:semicolon
DECL|member|reg_lccr1
id|u_int
id|reg_lccr1
suffix:semicolon
DECL|member|reg_lccr2
id|u_int
id|reg_lccr2
suffix:semicolon
DECL|member|reg_lccr3
id|u_int
id|reg_lccr3
suffix:semicolon
DECL|member|state
r_volatile
id|u_char
id|state
suffix:semicolon
DECL|member|task_state
r_volatile
id|u_char
id|task_state
suffix:semicolon
DECL|member|ctrlr_sem
r_struct
id|semaphore
id|ctrlr_sem
suffix:semicolon
DECL|member|ctrlr_wait
id|wait_queue_head_t
id|ctrlr_wait
suffix:semicolon
DECL|member|task
r_struct
id|work_struct
id|task
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ
DECL|member|freq_transition
r_struct
id|notifier_block
id|freq_transition
suffix:semicolon
DECL|member|freq_policy
r_struct
id|notifier_block
id|freq_policy
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|TO_INF
mdefine_line|#define TO_INF(ptr,member) container_of(ptr,struct pxafb_info,member)
multiline_comment|/*&n; * These are the actions for set_ctrlr_state&n; */
DECL|macro|C_DISABLE
mdefine_line|#define C_DISABLE&t;&t;(0)
DECL|macro|C_ENABLE
mdefine_line|#define C_ENABLE&t;&t;(1)
DECL|macro|C_DISABLE_CLKCHANGE
mdefine_line|#define C_DISABLE_CLKCHANGE&t;(2)
DECL|macro|C_ENABLE_CLKCHANGE
mdefine_line|#define C_ENABLE_CLKCHANGE&t;(3)
DECL|macro|C_REENABLE
mdefine_line|#define C_REENABLE&t;&t;(4)
DECL|macro|C_DISABLE_PM
mdefine_line|#define C_DISABLE_PM&t;&t;(5)
DECL|macro|C_ENABLE_PM
mdefine_line|#define C_ENABLE_PM&t;&t;(6)
DECL|macro|C_STARTUP
mdefine_line|#define C_STARTUP&t;&t;(7)
DECL|macro|PXA_NAME
mdefine_line|#define PXA_NAME&t;&quot;PXA&quot;
multiline_comment|/*&n; *  Debug macros&n; */
macro_line|#if DEBUG
DECL|macro|DPRINTK
macro_line|#  define DPRINTK(fmt, args...)&t;printk(&quot;%s: &quot; fmt, __FUNCTION__ , ## args)
macro_line|#else
DECL|macro|DPRINTK
macro_line|#  define DPRINTK(fmt, args...)
macro_line|#endif
multiline_comment|/*&n; * Minimum X and Y resolutions&n; */
DECL|macro|MIN_XRES
mdefine_line|#define MIN_XRES&t;64
DECL|macro|MIN_YRES
mdefine_line|#define MIN_YRES&t;64
macro_line|#endif /* __PXAFB_H__ */
eof
