multiline_comment|/* r128_drv.h -- Private header for r128 driver -*- linux-c -*-&n; * Created: Mon Dec 13 09:51:11 1999 by faith@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *    Kevin E. Martin &lt;martin@valinux.com&gt;&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; *    Michel D&#xfffd;nzer &lt;daenzerm@student.ethz.ch&gt;&n; */
macro_line|#ifndef __R128_DRV_H__
DECL|macro|__R128_DRV_H__
mdefine_line|#define __R128_DRV_H__
DECL|macro|GET_RING_HEAD
mdefine_line|#define GET_RING_HEAD( ring )&t;&t;le32_to_cpu( *(ring)-&gt;head )
DECL|macro|SET_RING_HEAD
mdefine_line|#define SET_RING_HEAD( ring, val )&t;*(ring)-&gt;head = cpu_to_le32( val )
DECL|struct|drm_r128_freelist
r_typedef
r_struct
id|drm_r128_freelist
(brace
DECL|member|age
r_int
r_int
id|age
suffix:semicolon
DECL|member|buf
id|drm_buf_t
op_star
id|buf
suffix:semicolon
DECL|member|next
r_struct
id|drm_r128_freelist
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|drm_r128_freelist
op_star
id|prev
suffix:semicolon
DECL|typedef|drm_r128_freelist_t
)brace
id|drm_r128_freelist_t
suffix:semicolon
DECL|struct|drm_r128_ring_buffer
r_typedef
r_struct
id|drm_r128_ring_buffer
(brace
DECL|member|start
id|u32
op_star
id|start
suffix:semicolon
DECL|member|end
id|u32
op_star
id|end
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|size_l2qw
r_int
id|size_l2qw
suffix:semicolon
DECL|member|head
r_volatile
id|u32
op_star
id|head
suffix:semicolon
DECL|member|tail
id|u32
id|tail
suffix:semicolon
DECL|member|tail_mask
id|u32
id|tail_mask
suffix:semicolon
DECL|member|space
r_int
id|space
suffix:semicolon
DECL|member|high_mark
r_int
id|high_mark
suffix:semicolon
DECL|typedef|drm_r128_ring_buffer_t
)brace
id|drm_r128_ring_buffer_t
suffix:semicolon
DECL|struct|drm_r128_private
r_typedef
r_struct
id|drm_r128_private
(brace
DECL|member|ring
id|drm_r128_ring_buffer_t
id|ring
suffix:semicolon
DECL|member|sarea_priv
id|drm_r128_sarea_t
op_star
id|sarea_priv
suffix:semicolon
DECL|member|cce_mode
r_int
id|cce_mode
suffix:semicolon
DECL|member|cce_fifo_size
r_int
id|cce_fifo_size
suffix:semicolon
DECL|member|cce_running
r_int
id|cce_running
suffix:semicolon
DECL|member|head
id|drm_r128_freelist_t
op_star
id|head
suffix:semicolon
DECL|member|tail
id|drm_r128_freelist_t
op_star
id|tail
suffix:semicolon
DECL|member|usec_timeout
r_int
id|usec_timeout
suffix:semicolon
DECL|member|is_pci
r_int
id|is_pci
suffix:semicolon
DECL|member|phys_pci_gart
r_int
r_int
id|phys_pci_gart
suffix:semicolon
DECL|member|bus_pci_gart
id|dma_addr_t
id|bus_pci_gart
suffix:semicolon
DECL|member|cce_buffers_offset
r_int
r_int
id|cce_buffers_offset
suffix:semicolon
DECL|member|idle_count
id|atomic_t
id|idle_count
suffix:semicolon
DECL|member|page_flipping
r_int
id|page_flipping
suffix:semicolon
DECL|member|current_page
r_int
id|current_page
suffix:semicolon
DECL|member|crtc_offset
id|u32
id|crtc_offset
suffix:semicolon
DECL|member|crtc_offset_cntl
id|u32
id|crtc_offset_cntl
suffix:semicolon
DECL|member|color_fmt
id|u32
id|color_fmt
suffix:semicolon
DECL|member|front_offset
r_int
r_int
id|front_offset
suffix:semicolon
DECL|member|front_pitch
r_int
r_int
id|front_pitch
suffix:semicolon
DECL|member|back_offset
r_int
r_int
id|back_offset
suffix:semicolon
DECL|member|back_pitch
r_int
r_int
id|back_pitch
suffix:semicolon
DECL|member|depth_fmt
id|u32
id|depth_fmt
suffix:semicolon
DECL|member|depth_offset
r_int
r_int
id|depth_offset
suffix:semicolon
DECL|member|depth_pitch
r_int
r_int
id|depth_pitch
suffix:semicolon
DECL|member|span_offset
r_int
r_int
id|span_offset
suffix:semicolon
DECL|member|front_pitch_offset_c
id|u32
id|front_pitch_offset_c
suffix:semicolon
DECL|member|back_pitch_offset_c
id|u32
id|back_pitch_offset_c
suffix:semicolon
DECL|member|depth_pitch_offset_c
id|u32
id|depth_pitch_offset_c
suffix:semicolon
DECL|member|span_pitch_offset_c
id|u32
id|span_pitch_offset_c
suffix:semicolon
DECL|member|sarea
id|drm_map_t
op_star
id|sarea
suffix:semicolon
DECL|member|fb
id|drm_map_t
op_star
id|fb
suffix:semicolon
DECL|member|mmio
id|drm_map_t
op_star
id|mmio
suffix:semicolon
DECL|member|cce_ring
id|drm_map_t
op_star
id|cce_ring
suffix:semicolon
DECL|member|ring_rptr
id|drm_map_t
op_star
id|ring_rptr
suffix:semicolon
DECL|member|buffers
id|drm_map_t
op_star
id|buffers
suffix:semicolon
DECL|member|agp_textures
id|drm_map_t
op_star
id|agp_textures
suffix:semicolon
DECL|typedef|drm_r128_private_t
)brace
id|drm_r128_private_t
suffix:semicolon
DECL|struct|drm_r128_buf_priv
r_typedef
r_struct
id|drm_r128_buf_priv
(brace
DECL|member|age
id|u32
id|age
suffix:semicolon
DECL|member|prim
r_int
id|prim
suffix:semicolon
DECL|member|discard
r_int
id|discard
suffix:semicolon
DECL|member|dispatched
r_int
id|dispatched
suffix:semicolon
DECL|member|list_entry
id|drm_r128_freelist_t
op_star
id|list_entry
suffix:semicolon
DECL|typedef|drm_r128_buf_priv_t
)brace
id|drm_r128_buf_priv_t
suffix:semicolon
multiline_comment|/* r128_cce.c */
r_extern
r_int
id|r128_cce_init
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_cce_start
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_cce_stop
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_cce_reset
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_cce_idle
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_engine_reset
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_fullscreen
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_cce_buffers
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|r128_freelist_reset
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
id|drm_buf_t
op_star
id|r128_freelist_get
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|r128_wait_ring
c_func
(paren
id|drm_r128_private_t
op_star
id|dev_priv
comma
r_int
id|n
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|r128_update_ring_snapshot
id|r128_update_ring_snapshot
c_func
(paren
id|drm_r128_ring_buffer_t
op_star
id|ring
)paren
(brace
id|ring-&gt;space
op_assign
(paren
id|GET_RING_HEAD
c_func
(paren
id|ring
)paren
op_minus
id|ring-&gt;tail
)paren
op_star
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ring-&gt;space
op_le
l_int|0
)paren
id|ring-&gt;space
op_add_assign
id|ring-&gt;size
suffix:semicolon
)brace
r_extern
r_int
id|r128_do_cce_idle
c_func
(paren
id|drm_r128_private_t
op_star
id|dev_priv
)paren
suffix:semicolon
r_extern
r_int
id|r128_do_cleanup_cce
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|r128_do_cleanup_pageflip
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* r128_state.c */
r_extern
r_int
id|r128_cce_clear
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_cce_swap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_cce_vertex
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_cce_indices
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_cce_blit
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_cce_depth
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_cce_stipple
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|r128_cce_indirect
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* Register definitions, register access macros and drmAddMap constants&n; * for Rage 128 kernel driver.&n; */
DECL|macro|R128_AUX_SC_CNTL
mdefine_line|#define R128_AUX_SC_CNTL&t;&t;0x1660
DECL|macro|R128_AUX1_SC_EN
macro_line|#&t;define R128_AUX1_SC_EN&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|R128_AUX1_SC_MODE_OR
macro_line|#&t;define R128_AUX1_SC_MODE_OR&t;&t;(0 &lt;&lt; 1)
DECL|macro|R128_AUX1_SC_MODE_NAND
macro_line|#&t;define R128_AUX1_SC_MODE_NAND&t;&t;(1 &lt;&lt; 1)
DECL|macro|R128_AUX2_SC_EN
macro_line|#&t;define R128_AUX2_SC_EN&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|R128_AUX2_SC_MODE_OR
macro_line|#&t;define R128_AUX2_SC_MODE_OR&t;&t;(0 &lt;&lt; 3)
DECL|macro|R128_AUX2_SC_MODE_NAND
macro_line|#&t;define R128_AUX2_SC_MODE_NAND&t;&t;(1 &lt;&lt; 3)
DECL|macro|R128_AUX3_SC_EN
macro_line|#&t;define R128_AUX3_SC_EN&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|R128_AUX3_SC_MODE_OR
macro_line|#&t;define R128_AUX3_SC_MODE_OR&t;&t;(0 &lt;&lt; 5)
DECL|macro|R128_AUX3_SC_MODE_NAND
macro_line|#&t;define R128_AUX3_SC_MODE_NAND&t;&t;(1 &lt;&lt; 5)
DECL|macro|R128_AUX1_SC_LEFT
mdefine_line|#define R128_AUX1_SC_LEFT&t;&t;0x1664
DECL|macro|R128_AUX1_SC_RIGHT
mdefine_line|#define R128_AUX1_SC_RIGHT&t;&t;0x1668
DECL|macro|R128_AUX1_SC_TOP
mdefine_line|#define R128_AUX1_SC_TOP&t;&t;0x166c
DECL|macro|R128_AUX1_SC_BOTTOM
mdefine_line|#define R128_AUX1_SC_BOTTOM&t;&t;0x1670
DECL|macro|R128_AUX2_SC_LEFT
mdefine_line|#define R128_AUX2_SC_LEFT&t;&t;0x1674
DECL|macro|R128_AUX2_SC_RIGHT
mdefine_line|#define R128_AUX2_SC_RIGHT&t;&t;0x1678
DECL|macro|R128_AUX2_SC_TOP
mdefine_line|#define R128_AUX2_SC_TOP&t;&t;0x167c
DECL|macro|R128_AUX2_SC_BOTTOM
mdefine_line|#define R128_AUX2_SC_BOTTOM&t;&t;0x1680
DECL|macro|R128_AUX3_SC_LEFT
mdefine_line|#define R128_AUX3_SC_LEFT&t;&t;0x1684
DECL|macro|R128_AUX3_SC_RIGHT
mdefine_line|#define R128_AUX3_SC_RIGHT&t;&t;0x1688
DECL|macro|R128_AUX3_SC_TOP
mdefine_line|#define R128_AUX3_SC_TOP&t;&t;0x168c
DECL|macro|R128_AUX3_SC_BOTTOM
mdefine_line|#define R128_AUX3_SC_BOTTOM&t;&t;0x1690
DECL|macro|R128_BRUSH_DATA0
mdefine_line|#define R128_BRUSH_DATA0&t;&t;0x1480
DECL|macro|R128_BUS_CNTL
mdefine_line|#define R128_BUS_CNTL&t;&t;&t;0x0030
DECL|macro|R128_BUS_MASTER_DIS
macro_line|#&t;define R128_BUS_MASTER_DIS&t;&t;(1 &lt;&lt; 6)
DECL|macro|R128_CLOCK_CNTL_INDEX
mdefine_line|#define R128_CLOCK_CNTL_INDEX&t;&t;0x0008
DECL|macro|R128_CLOCK_CNTL_DATA
mdefine_line|#define R128_CLOCK_CNTL_DATA&t;&t;0x000c
DECL|macro|R128_PLL_WR_EN
macro_line|#&t;define R128_PLL_WR_EN&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|R128_CONSTANT_COLOR_C
mdefine_line|#define R128_CONSTANT_COLOR_C&t;&t;0x1d34
DECL|macro|R128_CRTC_OFFSET
mdefine_line|#define R128_CRTC_OFFSET&t;&t;0x0224
DECL|macro|R128_CRTC_OFFSET_CNTL
mdefine_line|#define R128_CRTC_OFFSET_CNTL&t;&t;0x0228
DECL|macro|R128_CRTC_OFFSET_FLIP_CNTL
macro_line|#&t;define R128_CRTC_OFFSET_FLIP_CNTL&t;(1 &lt;&lt; 16)
DECL|macro|R128_DP_GUI_MASTER_CNTL
mdefine_line|#define R128_DP_GUI_MASTER_CNTL&t;&t;0x146c
DECL|macro|R128_GMC_SRC_PITCH_OFFSET_CNTL
macro_line|#       define R128_GMC_SRC_PITCH_OFFSET_CNTL&t;(1    &lt;&lt;  0)
DECL|macro|R128_GMC_DST_PITCH_OFFSET_CNTL
macro_line|#       define R128_GMC_DST_PITCH_OFFSET_CNTL&t;(1    &lt;&lt;  1)
DECL|macro|R128_GMC_BRUSH_SOLID_COLOR
macro_line|#&t;define R128_GMC_BRUSH_SOLID_COLOR&t;(13   &lt;&lt;  4)
DECL|macro|R128_GMC_BRUSH_NONE
macro_line|#&t;define R128_GMC_BRUSH_NONE&t;&t;(15   &lt;&lt;  4)
DECL|macro|R128_GMC_DST_16BPP
macro_line|#&t;define R128_GMC_DST_16BPP&t;&t;(4    &lt;&lt;  8)
DECL|macro|R128_GMC_DST_24BPP
macro_line|#&t;define R128_GMC_DST_24BPP&t;&t;(5    &lt;&lt;  8)
DECL|macro|R128_GMC_DST_32BPP
macro_line|#&t;define R128_GMC_DST_32BPP&t;&t;(6    &lt;&lt;  8)
DECL|macro|R128_GMC_DST_DATATYPE_SHIFT
macro_line|#       define R128_GMC_DST_DATATYPE_SHIFT&t;8
DECL|macro|R128_GMC_SRC_DATATYPE_COLOR
macro_line|#&t;define R128_GMC_SRC_DATATYPE_COLOR&t;(3    &lt;&lt; 12)
DECL|macro|R128_DP_SRC_SOURCE_MEMORY
macro_line|#&t;define R128_DP_SRC_SOURCE_MEMORY&t;(2    &lt;&lt; 24)
DECL|macro|R128_DP_SRC_SOURCE_HOST_DATA
macro_line|#&t;define R128_DP_SRC_SOURCE_HOST_DATA&t;(3    &lt;&lt; 24)
DECL|macro|R128_GMC_CLR_CMP_CNTL_DIS
macro_line|#&t;define R128_GMC_CLR_CMP_CNTL_DIS&t;(1    &lt;&lt; 28)
DECL|macro|R128_GMC_AUX_CLIP_DIS
macro_line|#&t;define R128_GMC_AUX_CLIP_DIS&t;&t;(1    &lt;&lt; 29)
DECL|macro|R128_GMC_WR_MSK_DIS
macro_line|#&t;define R128_GMC_WR_MSK_DIS&t;&t;(1    &lt;&lt; 30)
DECL|macro|R128_ROP3_S
macro_line|#&t;define R128_ROP3_S&t;&t;&t;0x00cc0000
DECL|macro|R128_ROP3_P
macro_line|#&t;define R128_ROP3_P&t;&t;&t;0x00f00000
DECL|macro|R128_DP_WRITE_MASK
mdefine_line|#define R128_DP_WRITE_MASK&t;&t;0x16cc
DECL|macro|R128_DST_PITCH_OFFSET_C
mdefine_line|#define R128_DST_PITCH_OFFSET_C&t;&t;0x1c80
DECL|macro|R128_DST_TILE
macro_line|#&t;define R128_DST_TILE&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|R128_GEN_RESET_CNTL
mdefine_line|#define R128_GEN_RESET_CNTL&t;&t;0x00f0
DECL|macro|R128_SOFT_RESET_GUI
macro_line|#&t;define R128_SOFT_RESET_GUI&t;&t;(1 &lt;&lt;  0)
DECL|macro|R128_GUI_SCRATCH_REG0
mdefine_line|#define R128_GUI_SCRATCH_REG0&t;&t;0x15e0
DECL|macro|R128_GUI_SCRATCH_REG1
mdefine_line|#define R128_GUI_SCRATCH_REG1&t;&t;0x15e4
DECL|macro|R128_GUI_SCRATCH_REG2
mdefine_line|#define R128_GUI_SCRATCH_REG2&t;&t;0x15e8
DECL|macro|R128_GUI_SCRATCH_REG3
mdefine_line|#define R128_GUI_SCRATCH_REG3&t;&t;0x15ec
DECL|macro|R128_GUI_SCRATCH_REG4
mdefine_line|#define R128_GUI_SCRATCH_REG4&t;&t;0x15f0
DECL|macro|R128_GUI_SCRATCH_REG5
mdefine_line|#define R128_GUI_SCRATCH_REG5&t;&t;0x15f4
DECL|macro|R128_GUI_STAT
mdefine_line|#define R128_GUI_STAT&t;&t;&t;0x1740
DECL|macro|R128_GUI_FIFOCNT_MASK
macro_line|#&t;define R128_GUI_FIFOCNT_MASK&t;&t;0x0fff
DECL|macro|R128_GUI_ACTIVE
macro_line|#&t;define R128_GUI_ACTIVE&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|R128_MCLK_CNTL
mdefine_line|#define R128_MCLK_CNTL&t;&t;&t;0x000f
DECL|macro|R128_FORCE_GCP
macro_line|#&t;define R128_FORCE_GCP&t;&t;&t;(1 &lt;&lt; 16)
DECL|macro|R128_FORCE_PIPE3D_CP
macro_line|#&t;define R128_FORCE_PIPE3D_CP&t;&t;(1 &lt;&lt; 17)
DECL|macro|R128_FORCE_RCP
macro_line|#&t;define R128_FORCE_RCP&t;&t;&t;(1 &lt;&lt; 18)
DECL|macro|R128_PC_GUI_CTLSTAT
mdefine_line|#define R128_PC_GUI_CTLSTAT&t;&t;0x1748
DECL|macro|R128_PC_NGUI_CTLSTAT
mdefine_line|#define R128_PC_NGUI_CTLSTAT&t;&t;0x0184
DECL|macro|R128_PC_FLUSH_GUI
macro_line|#&t;define R128_PC_FLUSH_GUI&t;&t;(3 &lt;&lt; 0)
DECL|macro|R128_PC_RI_GUI
macro_line|#&t;define R128_PC_RI_GUI&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|R128_PC_FLUSH_ALL
macro_line|#&t;define R128_PC_FLUSH_ALL&t;&t;0x00ff
DECL|macro|R128_PC_BUSY
macro_line|#&t;define R128_PC_BUSY&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|R128_PCI_GART_PAGE
mdefine_line|#define R128_PCI_GART_PAGE&t;&t;0x017c
DECL|macro|R128_PRIM_TEX_CNTL_C
mdefine_line|#define R128_PRIM_TEX_CNTL_C&t;&t;0x1cb0
DECL|macro|R128_SCALE_3D_CNTL
mdefine_line|#define R128_SCALE_3D_CNTL&t;&t;0x1a00
DECL|macro|R128_SEC_TEX_CNTL_C
mdefine_line|#define R128_SEC_TEX_CNTL_C&t;&t;0x1d00
DECL|macro|R128_SEC_TEXTURE_BORDER_COLOR_C
mdefine_line|#define R128_SEC_TEXTURE_BORDER_COLOR_C&t;0x1d3c
DECL|macro|R128_SETUP_CNTL
mdefine_line|#define R128_SETUP_CNTL&t;&t;&t;0x1bc4
DECL|macro|R128_STEN_REF_MASK_C
mdefine_line|#define R128_STEN_REF_MASK_C&t;&t;0x1d40
DECL|macro|R128_TEX_CNTL_C
mdefine_line|#define R128_TEX_CNTL_C&t;&t;&t;0x1c9c
DECL|macro|R128_TEX_CACHE_FLUSH
macro_line|#&t;define R128_TEX_CACHE_FLUSH&t;&t;(1 &lt;&lt; 23)
DECL|macro|R128_WAIT_UNTIL
mdefine_line|#define R128_WAIT_UNTIL&t;&t;&t;0x1720
DECL|macro|R128_EVENT_CRTC_OFFSET
macro_line|#&t;define R128_EVENT_CRTC_OFFSET&t;&t;(1 &lt;&lt; 0)
DECL|macro|R128_WINDOW_XY_OFFSET
mdefine_line|#define R128_WINDOW_XY_OFFSET&t;&t;0x1bcc
multiline_comment|/* CCE registers&n; */
DECL|macro|R128_PM4_BUFFER_OFFSET
mdefine_line|#define R128_PM4_BUFFER_OFFSET&t;&t;0x0700
DECL|macro|R128_PM4_BUFFER_CNTL
mdefine_line|#define R128_PM4_BUFFER_CNTL&t;&t;0x0704
DECL|macro|R128_PM4_MASK
macro_line|#&t;define R128_PM4_MASK&t;&t;&t;(15 &lt;&lt; 28)
DECL|macro|R128_PM4_NONPM4
macro_line|#&t;define R128_PM4_NONPM4&t;&t;&t;(0  &lt;&lt; 28)
DECL|macro|R128_PM4_192PIO
macro_line|#&t;define R128_PM4_192PIO&t;&t;&t;(1  &lt;&lt; 28)
DECL|macro|R128_PM4_192BM
macro_line|#&t;define R128_PM4_192BM&t;&t;&t;(2  &lt;&lt; 28)
DECL|macro|R128_PM4_128PIO_64INDBM
macro_line|#&t;define R128_PM4_128PIO_64INDBM&t;&t;(3  &lt;&lt; 28)
DECL|macro|R128_PM4_128BM_64INDBM
macro_line|#&t;define R128_PM4_128BM_64INDBM&t;&t;(4  &lt;&lt; 28)
DECL|macro|R128_PM4_64PIO_128INDBM
macro_line|#&t;define R128_PM4_64PIO_128INDBM&t;&t;(5  &lt;&lt; 28)
DECL|macro|R128_PM4_64BM_128INDBM
macro_line|#&t;define R128_PM4_64BM_128INDBM&t;&t;(6  &lt;&lt; 28)
DECL|macro|R128_PM4_64PIO_64VCBM_64INDBM
macro_line|#&t;define R128_PM4_64PIO_64VCBM_64INDBM&t;(7  &lt;&lt; 28)
DECL|macro|R128_PM4_64BM_64VCBM_64INDBM
macro_line|#&t;define R128_PM4_64BM_64VCBM_64INDBM&t;(8  &lt;&lt; 28)
DECL|macro|R128_PM4_64PIO_64VCPIO_64INDPIO
macro_line|#&t;define R128_PM4_64PIO_64VCPIO_64INDPIO&t;(15 &lt;&lt; 28)
DECL|macro|R128_PM4_BUFFER_WM_CNTL
mdefine_line|#define R128_PM4_BUFFER_WM_CNTL&t;&t;0x0708
DECL|macro|R128_WMA_SHIFT
macro_line|#&t;define R128_WMA_SHIFT&t;&t;&t;0
DECL|macro|R128_WMB_SHIFT
macro_line|#&t;define R128_WMB_SHIFT&t;&t;&t;8
DECL|macro|R128_WMC_SHIFT
macro_line|#&t;define R128_WMC_SHIFT&t;&t;&t;16
DECL|macro|R128_WB_WM_SHIFT
macro_line|#&t;define R128_WB_WM_SHIFT&t;&t;&t;24
DECL|macro|R128_PM4_BUFFER_DL_RPTR_ADDR
mdefine_line|#define R128_PM4_BUFFER_DL_RPTR_ADDR&t;0x070c
DECL|macro|R128_PM4_BUFFER_DL_RPTR
mdefine_line|#define R128_PM4_BUFFER_DL_RPTR&t;&t;0x0710
DECL|macro|R128_PM4_BUFFER_DL_WPTR
mdefine_line|#define R128_PM4_BUFFER_DL_WPTR&t;&t;0x0714
DECL|macro|R128_PM4_BUFFER_DL_DONE
macro_line|#&t;define R128_PM4_BUFFER_DL_DONE&t;&t;(1 &lt;&lt; 31)
DECL|macro|R128_PM4_VC_FPU_SETUP
mdefine_line|#define R128_PM4_VC_FPU_SETUP&t;&t;0x071c
DECL|macro|R128_PM4_IW_INDOFF
mdefine_line|#define R128_PM4_IW_INDOFF&t;&t;0x0738
DECL|macro|R128_PM4_IW_INDSIZE
mdefine_line|#define R128_PM4_IW_INDSIZE&t;&t;0x073c
DECL|macro|R128_PM4_STAT
mdefine_line|#define R128_PM4_STAT&t;&t;&t;0x07b8
DECL|macro|R128_PM4_FIFOCNT_MASK
macro_line|#&t;define R128_PM4_FIFOCNT_MASK&t;&t;0x0fff
DECL|macro|R128_PM4_BUSY
macro_line|#&t;define R128_PM4_BUSY&t;&t;&t;(1 &lt;&lt; 16)
DECL|macro|R128_PM4_GUI_ACTIVE
macro_line|#&t;define R128_PM4_GUI_ACTIVE&t;&t;(1 &lt;&lt; 31)
DECL|macro|R128_PM4_MICROCODE_ADDR
mdefine_line|#define R128_PM4_MICROCODE_ADDR&t;&t;0x07d4
DECL|macro|R128_PM4_MICROCODE_RADDR
mdefine_line|#define R128_PM4_MICROCODE_RADDR&t;0x07d8
DECL|macro|R128_PM4_MICROCODE_DATAH
mdefine_line|#define R128_PM4_MICROCODE_DATAH&t;0x07dc
DECL|macro|R128_PM4_MICROCODE_DATAL
mdefine_line|#define R128_PM4_MICROCODE_DATAL&t;0x07e0
DECL|macro|R128_PM4_BUFFER_ADDR
mdefine_line|#define R128_PM4_BUFFER_ADDR&t;&t;0x07f0
DECL|macro|R128_PM4_MICRO_CNTL
mdefine_line|#define R128_PM4_MICRO_CNTL&t;&t;0x07fc
DECL|macro|R128_PM4_MICRO_FREERUN
macro_line|#&t;define R128_PM4_MICRO_FREERUN&t;&t;(1 &lt;&lt; 30)
DECL|macro|R128_PM4_FIFO_DATA_EVEN
mdefine_line|#define R128_PM4_FIFO_DATA_EVEN&t;&t;0x1000
DECL|macro|R128_PM4_FIFO_DATA_ODD
mdefine_line|#define R128_PM4_FIFO_DATA_ODD&t;&t;0x1004
multiline_comment|/* CCE command packets&n; */
DECL|macro|R128_CCE_PACKET0
mdefine_line|#define R128_CCE_PACKET0&t;&t;0x00000000
DECL|macro|R128_CCE_PACKET1
mdefine_line|#define R128_CCE_PACKET1&t;&t;0x40000000
DECL|macro|R128_CCE_PACKET2
mdefine_line|#define R128_CCE_PACKET2&t;&t;0x80000000
DECL|macro|R128_CCE_PACKET3
mdefine_line|#define R128_CCE_PACKET3&t;&t;0xC0000000
DECL|macro|R128_CNTL_HOSTDATA_BLT
macro_line|#&t;define R128_CNTL_HOSTDATA_BLT&t;&t;0x00009400
DECL|macro|R128_CNTL_PAINT_MULTI
macro_line|#&t;define R128_CNTL_PAINT_MULTI&t;&t;0x00009A00
DECL|macro|R128_CNTL_BITBLT_MULTI
macro_line|#&t;define R128_CNTL_BITBLT_MULTI&t;&t;0x00009B00
DECL|macro|R128_3D_RNDR_GEN_INDX_PRIM
macro_line|#&t;define R128_3D_RNDR_GEN_INDX_PRIM&t;0x00002300
DECL|macro|R128_CCE_PACKET_MASK
mdefine_line|#define R128_CCE_PACKET_MASK&t;&t;0xC0000000
DECL|macro|R128_CCE_PACKET_COUNT_MASK
mdefine_line|#define R128_CCE_PACKET_COUNT_MASK&t;0x3fff0000
DECL|macro|R128_CCE_PACKET0_REG_MASK
mdefine_line|#define R128_CCE_PACKET0_REG_MASK&t;0x000007ff
DECL|macro|R128_CCE_PACKET1_REG0_MASK
mdefine_line|#define R128_CCE_PACKET1_REG0_MASK&t;0x000007ff
DECL|macro|R128_CCE_PACKET1_REG1_MASK
mdefine_line|#define R128_CCE_PACKET1_REG1_MASK&t;0x003ff800
DECL|macro|R128_CCE_VC_CNTL_PRIM_TYPE_NONE
mdefine_line|#define R128_CCE_VC_CNTL_PRIM_TYPE_NONE&t;&t;0x00000000
DECL|macro|R128_CCE_VC_CNTL_PRIM_TYPE_POINT
mdefine_line|#define R128_CCE_VC_CNTL_PRIM_TYPE_POINT&t;0x00000001
DECL|macro|R128_CCE_VC_CNTL_PRIM_TYPE_LINE
mdefine_line|#define R128_CCE_VC_CNTL_PRIM_TYPE_LINE&t;&t;0x00000002
DECL|macro|R128_CCE_VC_CNTL_PRIM_TYPE_POLY_LINE
mdefine_line|#define R128_CCE_VC_CNTL_PRIM_TYPE_POLY_LINE&t;0x00000003
DECL|macro|R128_CCE_VC_CNTL_PRIM_TYPE_TRI_LIST
mdefine_line|#define R128_CCE_VC_CNTL_PRIM_TYPE_TRI_LIST&t;0x00000004
DECL|macro|R128_CCE_VC_CNTL_PRIM_TYPE_TRI_FAN
mdefine_line|#define R128_CCE_VC_CNTL_PRIM_TYPE_TRI_FAN&t;0x00000005
DECL|macro|R128_CCE_VC_CNTL_PRIM_TYPE_TRI_STRIP
mdefine_line|#define R128_CCE_VC_CNTL_PRIM_TYPE_TRI_STRIP&t;0x00000006
DECL|macro|R128_CCE_VC_CNTL_PRIM_TYPE_TRI_TYPE2
mdefine_line|#define R128_CCE_VC_CNTL_PRIM_TYPE_TRI_TYPE2&t;0x00000007
DECL|macro|R128_CCE_VC_CNTL_PRIM_WALK_IND
mdefine_line|#define R128_CCE_VC_CNTL_PRIM_WALK_IND&t;&t;0x00000010
DECL|macro|R128_CCE_VC_CNTL_PRIM_WALK_LIST
mdefine_line|#define R128_CCE_VC_CNTL_PRIM_WALK_LIST&t;&t;0x00000020
DECL|macro|R128_CCE_VC_CNTL_PRIM_WALK_RING
mdefine_line|#define R128_CCE_VC_CNTL_PRIM_WALK_RING&t;&t;0x00000030
DECL|macro|R128_CCE_VC_CNTL_NUM_SHIFT
mdefine_line|#define R128_CCE_VC_CNTL_NUM_SHIFT&t;&t;16
DECL|macro|R128_DATATYPE_CI8
mdefine_line|#define R128_DATATYPE_CI8&t;&t;2
DECL|macro|R128_DATATYPE_ARGB1555
mdefine_line|#define R128_DATATYPE_ARGB1555&t;&t;3
DECL|macro|R128_DATATYPE_RGB565
mdefine_line|#define R128_DATATYPE_RGB565&t;&t;4
DECL|macro|R128_DATATYPE_RGB888
mdefine_line|#define R128_DATATYPE_RGB888&t;&t;5
DECL|macro|R128_DATATYPE_ARGB8888
mdefine_line|#define R128_DATATYPE_ARGB8888&t;&t;6
DECL|macro|R128_DATATYPE_RGB332
mdefine_line|#define R128_DATATYPE_RGB332&t;&t;7
DECL|macro|R128_DATATYPE_RGB8
mdefine_line|#define R128_DATATYPE_RGB8&t;&t;9
DECL|macro|R128_DATATYPE_ARGB4444
mdefine_line|#define R128_DATATYPE_ARGB4444&t;&t;15
multiline_comment|/* Constants */
DECL|macro|R128_AGP_OFFSET
mdefine_line|#define R128_AGP_OFFSET&t;&t;&t;0x02000000
DECL|macro|R128_WATERMARK_L
mdefine_line|#define R128_WATERMARK_L&t;&t;16
DECL|macro|R128_WATERMARK_M
mdefine_line|#define R128_WATERMARK_M&t;&t;8
DECL|macro|R128_WATERMARK_N
mdefine_line|#define R128_WATERMARK_N&t;&t;8
DECL|macro|R128_WATERMARK_K
mdefine_line|#define R128_WATERMARK_K&t;&t;128
DECL|macro|R128_MAX_USEC_TIMEOUT
mdefine_line|#define R128_MAX_USEC_TIMEOUT&t;&t;100000&t;/* 100 ms */
DECL|macro|R128_LAST_FRAME_REG
mdefine_line|#define R128_LAST_FRAME_REG&t;&t;R128_GUI_SCRATCH_REG0
DECL|macro|R128_LAST_DISPATCH_REG
mdefine_line|#define R128_LAST_DISPATCH_REG&t;&t;R128_GUI_SCRATCH_REG1
DECL|macro|R128_MAX_VB_AGE
mdefine_line|#define R128_MAX_VB_AGE&t;&t;&t;0x7fffffff
DECL|macro|R128_MAX_VB_VERTS
mdefine_line|#define R128_MAX_VB_VERTS&t;&t;(0xffff)
DECL|macro|R128_RING_HIGH_MARK
mdefine_line|#define R128_RING_HIGH_MARK&t;&t;128
DECL|macro|R128_PERFORMANCE_BOXES
mdefine_line|#define R128_PERFORMANCE_BOXES&t;&t;0
DECL|macro|R128_BASE
mdefine_line|#define R128_BASE(reg)&t;&t;((unsigned long)(dev_priv-&gt;mmio-&gt;handle))
DECL|macro|R128_ADDR
mdefine_line|#define R128_ADDR(reg)&t;&t;(R128_BASE( reg ) + reg)
DECL|macro|R128_DEREF
mdefine_line|#define R128_DEREF(reg)&t;&t;*(volatile u32 *)R128_ADDR( reg )
macro_line|#ifdef __alpha__
DECL|macro|R128_READ
mdefine_line|#define R128_READ(reg)&t;&t;(_R128_READ((u32 *)R128_ADDR(reg)))
DECL|function|_R128_READ
r_static
r_inline
id|u32
id|_R128_READ
c_func
(paren
id|u32
op_star
id|addr
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
r_return
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|macro|R128_WRITE
mdefine_line|#define R128_WRITE(reg,val)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wmb();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;R128_DEREF(reg) = val;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else
DECL|macro|R128_READ
mdefine_line|#define R128_READ(reg)&t;&t;le32_to_cpu( R128_DEREF( reg ) )
DECL|macro|R128_WRITE
mdefine_line|#define R128_WRITE(reg,val)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;R128_DEREF( reg ) = cpu_to_le32( val );&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif
DECL|macro|R128_DEREF8
mdefine_line|#define R128_DEREF8(reg)&t;*(volatile u8 *)R128_ADDR( reg )
macro_line|#ifdef __alpha__
DECL|macro|R128_READ8
mdefine_line|#define R128_READ8(reg)&t;&t;_R128_READ8((u8 *)R128_ADDR(reg))
DECL|function|_R128_READ8
r_static
r_inline
id|u8
id|_R128_READ8
c_func
(paren
id|u8
op_star
id|addr
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
r_return
op_star
(paren
r_volatile
id|u8
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|macro|R128_WRITE8
mdefine_line|#define R128_WRITE8(reg,val)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wmb();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;R128_DEREF8(reg) = val;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else
DECL|macro|R128_READ8
mdefine_line|#define R128_READ8(reg)&t;&t;R128_DEREF8( reg )
DECL|macro|R128_WRITE8
mdefine_line|#define R128_WRITE8(reg,val)&t;do { R128_DEREF8( reg ) = val; } while (0)
macro_line|#endif
DECL|macro|R128_WRITE_PLL
mdefine_line|#define R128_WRITE_PLL(addr,val)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;R128_WRITE8(R128_CLOCK_CNTL_INDEX,&t;&t;&t;&t;&bslash;&n;&t;&t;    ((addr) &amp; 0x1f) | R128_PLL_WR_EN);&t;&t;&t;&bslash;&n;&t;R128_WRITE(R128_CLOCK_CNTL_DATA, (val));&t;&t;&t;&bslash;&n;} while (0)
r_extern
r_int
id|R128_READ_PLL
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|addr
)paren
suffix:semicolon
DECL|macro|CCE_PACKET0
mdefine_line|#define CCE_PACKET0( reg, n )&t;&t;(R128_CCE_PACKET0 |&t;&t;&bslash;&n;&t;&t;&t;&t;&t; ((n) &lt;&lt; 16) | ((reg) &gt;&gt; 2))
DECL|macro|CCE_PACKET1
mdefine_line|#define CCE_PACKET1( reg0, reg1 )&t;(R128_CCE_PACKET1 |&t;&t;&bslash;&n;&t;&t;&t;&t;&t; (((reg1) &gt;&gt; 2) &lt;&lt; 11) | ((reg0) &gt;&gt; 2))
DECL|macro|CCE_PACKET2
mdefine_line|#define CCE_PACKET2()&t;&t;&t;(R128_CCE_PACKET2)
DECL|macro|CCE_PACKET3
mdefine_line|#define CCE_PACKET3( pkt, n )&t;&t;(R128_CCE_PACKET3 |&t;&t;&bslash;&n;&t;&t;&t;&t;&t; (pkt) | ((n) &lt;&lt; 16))
multiline_comment|/* ================================================================&n; * Misc helper macros&n; */
DECL|macro|LOCK_TEST_WITH_RETURN
mdefine_line|#define LOCK_TEST_WITH_RETURN( dev )&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( !_DRM_LOCK_IS_HELD( dev-&gt;lock.hw_lock-&gt;lock ) ||&t;&t;&bslash;&n;&t;     dev-&gt;lock.pid != current-&gt;pid ) {&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_ERROR( &quot;%s called without lock held&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&t;   __FUNCTION__ );&t;&t;&t;&t;&bslash;&n;&t;&t;return -EINVAL;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RING_SPACE_TEST_WITH_RETURN
mdefine_line|#define RING_SPACE_TEST_WITH_RETURN( dev_priv )&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;drm_r128_ring_buffer_t *ring = &amp;dev_priv-&gt;ring; int i;&t;&t;&bslash;&n;&t;if ( ring-&gt;space &lt; ring-&gt;high_mark ) {&t;&t;&t;&t;&bslash;&n;&t;&t;for ( i = 0 ; i &lt; dev_priv-&gt;usec_timeout ; i++ ) {&t;&bslash;&n;&t;&t;&t;r128_update_ring_snapshot( ring );&t;&t;&bslash;&n;&t;&t;&t;if ( ring-&gt;space &gt;= ring-&gt;high_mark )&t;&t;&bslash;&n;&t;&t;&t;&t;goto __ring_space_done;&t;&t;&t;&bslash;&n;&t;&t;&t;udelay( 1 );&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_ERROR( &quot;ring space check failed!&bslash;n&quot; );&t;&t;&bslash;&n;&t;&t;return -EBUSY;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; __ring_space_done:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|VB_AGE_TEST_WITH_RETURN
mdefine_line|#define VB_AGE_TEST_WITH_RETURN( dev_priv )&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;drm_r128_sarea_t *sarea_priv = dev_priv-&gt;sarea_priv;&t;&t;&bslash;&n;&t;if ( sarea_priv-&gt;last_dispatch &gt;= R128_MAX_VB_AGE ) {&t;&t;&bslash;&n;&t;&t;int __ret = r128_do_cce_idle( dev_priv );&t;&t;&bslash;&n;&t;&t;if ( __ret &lt; 0 ) return __ret;&t;&t;&t;&t;&bslash;&n;&t;&t;sarea_priv-&gt;last_dispatch = 0;&t;&t;&t;&t;&bslash;&n;&t;&t;r128_freelist_reset( dev );&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|R128_WAIT_UNTIL_PAGE_FLIPPED
mdefine_line|#define R128_WAIT_UNTIL_PAGE_FLIPPED() do {&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CCE_PACKET0( R128_WAIT_UNTIL, 0 ) );&t;&t;&t;&bslash;&n;&t;OUT_RING( R128_EVENT_CRTC_OFFSET );&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* ================================================================&n; * Ring control&n; */
DECL|macro|r128_flush_write_combine
mdefine_line|#define r128_flush_write_combine()&t;mb()
DECL|macro|R128_VERBOSE
mdefine_line|#define R128_VERBOSE&t;0
DECL|macro|RING_LOCALS
mdefine_line|#define RING_LOCALS&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int write; unsigned int tail_mask; volatile u32 *ring;
DECL|macro|BEGIN_RING
mdefine_line|#define BEGIN_RING( n ) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( R128_VERBOSE ) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( &quot;BEGIN_RING( %d ) in %s&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;&t;   (n), __FUNCTION__ );&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( dev_priv-&gt;ring.space &lt;= (n) * sizeof(u32) ) {&t;&t;&bslash;&n;&t;&t;r128_wait_ring( dev_priv, (n) * sizeof(u32) );&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;dev_priv-&gt;ring.space -= (n) * sizeof(u32);&t;&t;&t;&bslash;&n;&t;ring = dev_priv-&gt;ring.start;&t;&t;&t;&t;&t;&bslash;&n;&t;write = dev_priv-&gt;ring.tail;&t;&t;&t;&t;&t;&bslash;&n;&t;tail_mask = dev_priv-&gt;ring.tail_mask;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* You can set this to zero if you want.  If the card locks up, you&squot;ll&n; * need to keep this set.  It works around a bug in early revs of the&n; * Rage 128 chipset, where the CCE would read 32 dwords past the end of&n; * the ring buffer before wrapping around.&n; */
DECL|macro|R128_BROKEN_CCE
mdefine_line|#define R128_BROKEN_CCE&t;1
DECL|macro|ADVANCE_RING
mdefine_line|#define ADVANCE_RING() do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( R128_VERBOSE ) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( &quot;ADVANCE_RING() wr=0x%06x tail=0x%06x&bslash;n&quot;,&t;&bslash;&n;&t;&t;&t;  write, dev_priv-&gt;ring.tail );&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( R128_BROKEN_CCE &amp;&amp; write &lt; 32 ) {&t;&t;&t;&t;&bslash;&n;&t;&t;memcpy( dev_priv-&gt;ring.end,&t;&t;&t;&t;&bslash;&n;&t;&t;&t;dev_priv-&gt;ring.start,&t;&t;&t;&t;&bslash;&n;&t;&t;&t;write * sizeof(u32) );&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;r128_flush_write_combine();&t;&t;&t;&t;&t;&bslash;&n;&t;dev_priv-&gt;ring.tail = write;&t;&t;&t;&t;&t;&bslash;&n;&t;R128_WRITE( R128_PM4_BUFFER_DL_WPTR, write );&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|OUT_RING
mdefine_line|#define OUT_RING( x ) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( R128_VERBOSE ) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( &quot;   OUT_RING( 0x%08x ) at 0x%x&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&t;   (unsigned int)(x), write );&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ring[write++] = cpu_to_le32( x );&t;&t;&t;&t;&bslash;&n;&t;write &amp;= tail_mask;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* __R128_DRV_H__ */
eof
