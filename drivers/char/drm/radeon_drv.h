multiline_comment|/* radeon_drv.h -- Private header for radeon driver -*- linux-c -*-&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Fremont, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Kevin E. Martin &lt;martin@valinux.com&gt;&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#ifndef __RADEON_DRV_H__
DECL|macro|__RADEON_DRV_H__
mdefine_line|#define __RADEON_DRV_H__
DECL|struct|drm_radeon_freelist
r_typedef
r_struct
id|drm_radeon_freelist
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
id|drm_radeon_freelist
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|drm_radeon_freelist
op_star
id|prev
suffix:semicolon
DECL|typedef|drm_radeon_freelist_t
)brace
id|drm_radeon_freelist_t
suffix:semicolon
DECL|struct|drm_radeon_ring_buffer
r_typedef
r_struct
id|drm_radeon_ring_buffer
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
DECL|typedef|drm_radeon_ring_buffer_t
)brace
id|drm_radeon_ring_buffer_t
suffix:semicolon
DECL|struct|drm_radeon_depth_clear_t
r_typedef
r_struct
id|drm_radeon_depth_clear_t
(brace
DECL|member|rb3d_cntl
id|u32
id|rb3d_cntl
suffix:semicolon
DECL|member|rb3d_zstencilcntl
id|u32
id|rb3d_zstencilcntl
suffix:semicolon
DECL|member|se_cntl
id|u32
id|se_cntl
suffix:semicolon
DECL|typedef|drm_radeon_depth_clear_t
)brace
id|drm_radeon_depth_clear_t
suffix:semicolon
DECL|struct|drm_radeon_private
r_typedef
r_struct
id|drm_radeon_private
(brace
DECL|member|ring
id|drm_radeon_ring_buffer_t
id|ring
suffix:semicolon
DECL|member|sarea_priv
id|drm_radeon_sarea_t
op_star
id|sarea_priv
suffix:semicolon
DECL|member|agp_size
r_int
id|agp_size
suffix:semicolon
DECL|member|agp_vm_start
id|u32
id|agp_vm_start
suffix:semicolon
DECL|member|agp_buffers_offset
r_int
r_int
id|agp_buffers_offset
suffix:semicolon
DECL|member|cp_mode
r_int
id|cp_mode
suffix:semicolon
DECL|member|cp_running
r_int
id|cp_running
suffix:semicolon
DECL|member|head
id|drm_radeon_freelist_t
op_star
id|head
suffix:semicolon
DECL|member|tail
id|drm_radeon_freelist_t
op_star
id|tail
suffix:semicolon
DECL|member|last_buf
r_int
id|last_buf
suffix:semicolon
DECL|member|scratch
r_volatile
id|u32
op_star
id|scratch
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
DECL|member|front_pitch_offset
id|u32
id|front_pitch_offset
suffix:semicolon
DECL|member|back_pitch_offset
id|u32
id|back_pitch_offset
suffix:semicolon
DECL|member|depth_pitch_offset
id|u32
id|depth_pitch_offset
suffix:semicolon
DECL|member|depth_clear
id|drm_radeon_depth_clear_t
id|depth_clear
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
DECL|member|cp_ring
id|drm_map_t
op_star
id|cp_ring
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
DECL|typedef|drm_radeon_private_t
)brace
id|drm_radeon_private_t
suffix:semicolon
DECL|struct|drm_radeon_buf_priv
r_typedef
r_struct
id|drm_radeon_buf_priv
(brace
DECL|member|age
id|u32
id|age
suffix:semicolon
DECL|typedef|drm_radeon_buf_priv_t
)brace
id|drm_radeon_buf_priv_t
suffix:semicolon
multiline_comment|/* radeon_cp.c */
r_extern
r_int
id|radeon_cp_init
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
id|radeon_cp_start
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
id|radeon_cp_stop
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
id|radeon_cp_reset
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
id|radeon_cp_idle
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
id|radeon_engine_reset
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
id|radeon_fullscreen
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
id|radeon_cp_buffers
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
id|radeon_freelist_reset
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
id|radeon_freelist_get
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|radeon_wait_ring
c_func
(paren
id|drm_radeon_private_t
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
DECL|function|radeon_update_ring_snapshot
id|radeon_update_ring_snapshot
c_func
(paren
id|drm_radeon_ring_buffer_t
op_star
id|ring
)paren
(brace
id|ring-&gt;space
op_assign
(paren
op_star
(paren
r_volatile
r_int
op_star
)paren
id|ring-&gt;head
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
id|radeon_do_cp_idle
c_func
(paren
id|drm_radeon_private_t
op_star
id|dev_priv
)paren
suffix:semicolon
r_extern
r_int
id|radeon_do_cleanup_cp
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|radeon_do_cleanup_pageflip
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* radeon_state.c */
r_extern
r_int
id|radeon_cp_clear
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
id|radeon_cp_swap
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
id|radeon_cp_vertex
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
id|radeon_cp_indices
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
id|radeon_cp_texture
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
id|radeon_cp_stipple
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
id|radeon_cp_indirect
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
id|radeon_cp_vertex2
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
id|radeon_cp_cmdbuf
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
id|radeon_cp_getparam
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
id|radeon_cp_flip
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
multiline_comment|/* Register definitions, register access macros and drmAddMap constants&n; * for Radeon kernel driver.&n; */
DECL|macro|RADEON_AGP_COMMAND
mdefine_line|#define RADEON_AGP_COMMAND&t;&t;0x0f60
DECL|macro|RADEON_AUX_SCISSOR_CNTL
mdefine_line|#define RADEON_AUX_SCISSOR_CNTL&t;&t;0x26f0
DECL|macro|RADEON_EXCLUSIVE_SCISSOR_0
macro_line|#&t;define RADEON_EXCLUSIVE_SCISSOR_0&t;(1 &lt;&lt; 24)
DECL|macro|RADEON_EXCLUSIVE_SCISSOR_1
macro_line|#&t;define RADEON_EXCLUSIVE_SCISSOR_1&t;(1 &lt;&lt; 25)
DECL|macro|RADEON_EXCLUSIVE_SCISSOR_2
macro_line|#&t;define RADEON_EXCLUSIVE_SCISSOR_2&t;(1 &lt;&lt; 26)
DECL|macro|RADEON_SCISSOR_0_ENABLE
macro_line|#&t;define RADEON_SCISSOR_0_ENABLE&t;&t;(1 &lt;&lt; 28)
DECL|macro|RADEON_SCISSOR_1_ENABLE
macro_line|#&t;define RADEON_SCISSOR_1_ENABLE&t;&t;(1 &lt;&lt; 29)
DECL|macro|RADEON_SCISSOR_2_ENABLE
macro_line|#&t;define RADEON_SCISSOR_2_ENABLE&t;&t;(1 &lt;&lt; 30)
DECL|macro|RADEON_BUS_CNTL
mdefine_line|#define RADEON_BUS_CNTL&t;&t;&t;0x0030
DECL|macro|RADEON_BUS_MASTER_DIS
macro_line|#&t;define RADEON_BUS_MASTER_DIS&t;&t;(1 &lt;&lt; 6)
DECL|macro|RADEON_CLOCK_CNTL_DATA
mdefine_line|#define RADEON_CLOCK_CNTL_DATA&t;&t;0x000c
DECL|macro|RADEON_PLL_WR_EN
macro_line|#&t;define RADEON_PLL_WR_EN&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|RADEON_CLOCK_CNTL_INDEX
mdefine_line|#define RADEON_CLOCK_CNTL_INDEX&t;&t;0x0008
DECL|macro|RADEON_CONFIG_APER_SIZE
mdefine_line|#define RADEON_CONFIG_APER_SIZE&t;&t;0x0108
DECL|macro|RADEON_CRTC_OFFSET
mdefine_line|#define RADEON_CRTC_OFFSET&t;&t;0x0224
DECL|macro|RADEON_CRTC_OFFSET_CNTL
mdefine_line|#define RADEON_CRTC_OFFSET_CNTL&t;&t;0x0228
DECL|macro|RADEON_CRTC_TILE_EN
macro_line|#&t;define RADEON_CRTC_TILE_EN&t;&t;(1 &lt;&lt; 15)
DECL|macro|RADEON_CRTC_OFFSET_FLIP_CNTL
macro_line|#&t;define RADEON_CRTC_OFFSET_FLIP_CNTL&t;(1 &lt;&lt; 16)
DECL|macro|RADEON_RB3D_COLORPITCH
mdefine_line|#define RADEON_RB3D_COLORPITCH&t;&t;0x1c48
DECL|macro|RADEON_DP_GUI_MASTER_CNTL
mdefine_line|#define RADEON_DP_GUI_MASTER_CNTL&t;0x146c
DECL|macro|RADEON_GMC_SRC_PITCH_OFFSET_CNTL
macro_line|#&t;define RADEON_GMC_SRC_PITCH_OFFSET_CNTL&t;(1 &lt;&lt; 0)
DECL|macro|RADEON_GMC_DST_PITCH_OFFSET_CNTL
macro_line|#&t;define RADEON_GMC_DST_PITCH_OFFSET_CNTL&t;(1 &lt;&lt; 1)
DECL|macro|RADEON_GMC_BRUSH_SOLID_COLOR
macro_line|#&t;define RADEON_GMC_BRUSH_SOLID_COLOR&t;(13 &lt;&lt; 4)
DECL|macro|RADEON_GMC_BRUSH_NONE
macro_line|#&t;define RADEON_GMC_BRUSH_NONE&t;&t;(15 &lt;&lt; 4)
DECL|macro|RADEON_GMC_DST_16BPP
macro_line|#&t;define RADEON_GMC_DST_16BPP&t;&t;(4 &lt;&lt; 8)
DECL|macro|RADEON_GMC_DST_24BPP
macro_line|#&t;define RADEON_GMC_DST_24BPP&t;&t;(5 &lt;&lt; 8)
DECL|macro|RADEON_GMC_DST_32BPP
macro_line|#&t;define RADEON_GMC_DST_32BPP&t;&t;(6 &lt;&lt; 8)
DECL|macro|RADEON_GMC_DST_DATATYPE_SHIFT
macro_line|#&t;define RADEON_GMC_DST_DATATYPE_SHIFT&t;8
DECL|macro|RADEON_GMC_SRC_DATATYPE_COLOR
macro_line|#&t;define RADEON_GMC_SRC_DATATYPE_COLOR&t;(3 &lt;&lt; 12)
DECL|macro|RADEON_DP_SRC_SOURCE_MEMORY
macro_line|#&t;define RADEON_DP_SRC_SOURCE_MEMORY&t;(2 &lt;&lt; 24)
DECL|macro|RADEON_DP_SRC_SOURCE_HOST_DATA
macro_line|#&t;define RADEON_DP_SRC_SOURCE_HOST_DATA&t;(3 &lt;&lt; 24)
DECL|macro|RADEON_GMC_CLR_CMP_CNTL_DIS
macro_line|#&t;define RADEON_GMC_CLR_CMP_CNTL_DIS&t;(1 &lt;&lt; 28)
DECL|macro|RADEON_GMC_WR_MSK_DIS
macro_line|#&t;define RADEON_GMC_WR_MSK_DIS&t;&t;(1 &lt;&lt; 30)
DECL|macro|RADEON_ROP3_S
macro_line|#&t;define RADEON_ROP3_S&t;&t;&t;0x00cc0000
DECL|macro|RADEON_ROP3_P
macro_line|#&t;define RADEON_ROP3_P&t;&t;&t;0x00f00000
DECL|macro|RADEON_DP_WRITE_MASK
mdefine_line|#define RADEON_DP_WRITE_MASK&t;&t;0x16cc
DECL|macro|RADEON_DST_PITCH_OFFSET
mdefine_line|#define RADEON_DST_PITCH_OFFSET&t;&t;0x142c
DECL|macro|RADEON_DST_PITCH_OFFSET_C
mdefine_line|#define RADEON_DST_PITCH_OFFSET_C&t;0x1c80
DECL|macro|RADEON_DST_TILE_LINEAR
macro_line|#&t;define RADEON_DST_TILE_LINEAR&t;&t;(0 &lt;&lt; 30)
DECL|macro|RADEON_DST_TILE_MACRO
macro_line|#&t;define RADEON_DST_TILE_MACRO&t;&t;(1 &lt;&lt; 30)
DECL|macro|RADEON_DST_TILE_MICRO
macro_line|#&t;define RADEON_DST_TILE_MICRO&t;&t;(2 &lt;&lt; 30)
DECL|macro|RADEON_DST_TILE_BOTH
macro_line|#&t;define RADEON_DST_TILE_BOTH&t;&t;(3 &lt;&lt; 30)
DECL|macro|RADEON_SCRATCH_REG0
mdefine_line|#define RADEON_SCRATCH_REG0&t;&t;0x15e0
DECL|macro|RADEON_SCRATCH_REG1
mdefine_line|#define RADEON_SCRATCH_REG1&t;&t;0x15e4
DECL|macro|RADEON_SCRATCH_REG2
mdefine_line|#define RADEON_SCRATCH_REG2&t;&t;0x15e8
DECL|macro|RADEON_SCRATCH_REG3
mdefine_line|#define RADEON_SCRATCH_REG3&t;&t;0x15ec
DECL|macro|RADEON_SCRATCH_REG4
mdefine_line|#define RADEON_SCRATCH_REG4&t;&t;0x15f0
DECL|macro|RADEON_SCRATCH_REG5
mdefine_line|#define RADEON_SCRATCH_REG5&t;&t;0x15f4
DECL|macro|RADEON_SCRATCH_UMSK
mdefine_line|#define RADEON_SCRATCH_UMSK&t;&t;0x0770
DECL|macro|RADEON_SCRATCH_ADDR
mdefine_line|#define RADEON_SCRATCH_ADDR&t;&t;0x0774
DECL|macro|RADEON_HOST_PATH_CNTL
mdefine_line|#define RADEON_HOST_PATH_CNTL&t;&t;0x0130
DECL|macro|RADEON_HDP_SOFT_RESET
macro_line|#&t;define RADEON_HDP_SOFT_RESET&t;&t;(1 &lt;&lt; 26)
DECL|macro|RADEON_HDP_WC_TIMEOUT_MASK
macro_line|#&t;define RADEON_HDP_WC_TIMEOUT_MASK&t;(7 &lt;&lt; 28)
DECL|macro|RADEON_HDP_WC_TIMEOUT_28BCLK
macro_line|#&t;define RADEON_HDP_WC_TIMEOUT_28BCLK&t;(7 &lt;&lt; 28)
DECL|macro|RADEON_ISYNC_CNTL
mdefine_line|#define RADEON_ISYNC_CNTL&t;&t;0x1724
DECL|macro|RADEON_ISYNC_ANY2D_IDLE3D
macro_line|#&t;define RADEON_ISYNC_ANY2D_IDLE3D&t;(1 &lt;&lt; 0)
DECL|macro|RADEON_ISYNC_ANY3D_IDLE2D
macro_line|#&t;define RADEON_ISYNC_ANY3D_IDLE2D&t;(1 &lt;&lt; 1)
DECL|macro|RADEON_ISYNC_TRIG2D_IDLE3D
macro_line|#&t;define RADEON_ISYNC_TRIG2D_IDLE3D&t;(1 &lt;&lt; 2)
DECL|macro|RADEON_ISYNC_TRIG3D_IDLE2D
macro_line|#&t;define RADEON_ISYNC_TRIG3D_IDLE2D&t;(1 &lt;&lt; 3)
DECL|macro|RADEON_ISYNC_WAIT_IDLEGUI
macro_line|#&t;define RADEON_ISYNC_WAIT_IDLEGUI&t;(1 &lt;&lt; 4)
DECL|macro|RADEON_ISYNC_CPSCRATCH_IDLEGUI
macro_line|#&t;define RADEON_ISYNC_CPSCRATCH_IDLEGUI&t;(1 &lt;&lt; 5)
DECL|macro|RADEON_MC_AGP_LOCATION
mdefine_line|#define RADEON_MC_AGP_LOCATION&t;&t;0x014c
DECL|macro|RADEON_MC_FB_LOCATION
mdefine_line|#define RADEON_MC_FB_LOCATION&t;&t;0x0148
DECL|macro|RADEON_MCLK_CNTL
mdefine_line|#define RADEON_MCLK_CNTL&t;&t;0x0012
DECL|macro|RADEON_FORCEON_MCLKA
macro_line|#&t;define RADEON_FORCEON_MCLKA&t;&t;(1 &lt;&lt; 16)
DECL|macro|RADEON_FORCEON_MCLKB
macro_line|#&t;define RADEON_FORCEON_MCLKB&t;&t;(1 &lt;&lt; 17)
DECL|macro|RADEON_FORCEON_YCLKA
macro_line|#&t;define RADEON_FORCEON_YCLKA&t;&t;(1 &lt;&lt; 18)
DECL|macro|RADEON_FORCEON_YCLKB
macro_line|#&t;define RADEON_FORCEON_YCLKB&t;&t;(1 &lt;&lt; 19)
DECL|macro|RADEON_FORCEON_MC
macro_line|#&t;define RADEON_FORCEON_MC&t;&t;(1 &lt;&lt; 20)
DECL|macro|RADEON_FORCEON_AIC
macro_line|#&t;define RADEON_FORCEON_AIC&t;&t;(1 &lt;&lt; 21)
DECL|macro|RADEON_PP_BORDER_COLOR_0
mdefine_line|#define RADEON_PP_BORDER_COLOR_0&t;0x1d40
DECL|macro|RADEON_PP_BORDER_COLOR_1
mdefine_line|#define RADEON_PP_BORDER_COLOR_1&t;0x1d44
DECL|macro|RADEON_PP_BORDER_COLOR_2
mdefine_line|#define RADEON_PP_BORDER_COLOR_2&t;0x1d48
DECL|macro|RADEON_PP_CNTL
mdefine_line|#define RADEON_PP_CNTL&t;&t;&t;0x1c38
DECL|macro|RADEON_SCISSOR_ENABLE
macro_line|#&t;define RADEON_SCISSOR_ENABLE&t;&t;(1 &lt;&lt;  1)
DECL|macro|RADEON_PP_LUM_MATRIX
mdefine_line|#define RADEON_PP_LUM_MATRIX&t;&t;0x1d00
DECL|macro|RADEON_PP_MISC
mdefine_line|#define RADEON_PP_MISC&t;&t;&t;0x1c14
DECL|macro|RADEON_PP_ROT_MATRIX_0
mdefine_line|#define RADEON_PP_ROT_MATRIX_0&t;&t;0x1d58
DECL|macro|RADEON_PP_TXFILTER_0
mdefine_line|#define RADEON_PP_TXFILTER_0&t;&t;0x1c54
DECL|macro|RADEON_PP_TXFILTER_1
mdefine_line|#define RADEON_PP_TXFILTER_1&t;&t;0x1c6c
DECL|macro|RADEON_PP_TXFILTER_2
mdefine_line|#define RADEON_PP_TXFILTER_2&t;&t;0x1c84
DECL|macro|RADEON_RB2D_DSTCACHE_CTLSTAT
mdefine_line|#define RADEON_RB2D_DSTCACHE_CTLSTAT&t;0x342c
DECL|macro|RADEON_RB2D_DC_FLUSH
macro_line|#&t;define RADEON_RB2D_DC_FLUSH&t;&t;(3 &lt;&lt; 0)
DECL|macro|RADEON_RB2D_DC_FREE
macro_line|#&t;define RADEON_RB2D_DC_FREE&t;&t;(3 &lt;&lt; 2)
DECL|macro|RADEON_RB2D_DC_FLUSH_ALL
macro_line|#&t;define RADEON_RB2D_DC_FLUSH_ALL&t;&t;0xf
DECL|macro|RADEON_RB2D_DC_BUSY
macro_line|#&t;define RADEON_RB2D_DC_BUSY&t;&t;(1 &lt;&lt; 31)
DECL|macro|RADEON_RB3D_CNTL
mdefine_line|#define RADEON_RB3D_CNTL&t;&t;0x1c3c
DECL|macro|RADEON_ALPHA_BLEND_ENABLE
macro_line|#&t;define RADEON_ALPHA_BLEND_ENABLE&t;(1 &lt;&lt; 0)
DECL|macro|RADEON_PLANE_MASK_ENABLE
macro_line|#&t;define RADEON_PLANE_MASK_ENABLE&t;&t;(1 &lt;&lt; 1)
DECL|macro|RADEON_DITHER_ENABLE
macro_line|#&t;define RADEON_DITHER_ENABLE&t;&t;(1 &lt;&lt; 2)
DECL|macro|RADEON_ROUND_ENABLE
macro_line|#&t;define RADEON_ROUND_ENABLE&t;&t;(1 &lt;&lt; 3)
DECL|macro|RADEON_SCALE_DITHER_ENABLE
macro_line|#&t;define RADEON_SCALE_DITHER_ENABLE&t;(1 &lt;&lt; 4)
DECL|macro|RADEON_DITHER_INIT
macro_line|#&t;define RADEON_DITHER_INIT&t;&t;(1 &lt;&lt; 5)
DECL|macro|RADEON_ROP_ENABLE
macro_line|#&t;define RADEON_ROP_ENABLE&t;&t;(1 &lt;&lt; 6)
DECL|macro|RADEON_STENCIL_ENABLE
macro_line|#&t;define RADEON_STENCIL_ENABLE&t;&t;(1 &lt;&lt; 7)
DECL|macro|RADEON_Z_ENABLE
macro_line|#&t;define RADEON_Z_ENABLE&t;&t;&t;(1 &lt;&lt; 8)
DECL|macro|RADEON_RB3D_DEPTHOFFSET
mdefine_line|#define RADEON_RB3D_DEPTHOFFSET&t;&t;0x1c24
DECL|macro|RADEON_RB3D_PLANEMASK
mdefine_line|#define RADEON_RB3D_PLANEMASK&t;&t;0x1d84
DECL|macro|RADEON_RB3D_STENCILREFMASK
mdefine_line|#define RADEON_RB3D_STENCILREFMASK&t;0x1d7c
DECL|macro|RADEON_RB3D_ZCACHE_MODE
mdefine_line|#define RADEON_RB3D_ZCACHE_MODE&t;&t;0x3250
DECL|macro|RADEON_RB3D_ZCACHE_CTLSTAT
mdefine_line|#define RADEON_RB3D_ZCACHE_CTLSTAT&t;0x3254
DECL|macro|RADEON_RB3D_ZC_FLUSH
macro_line|#&t;define RADEON_RB3D_ZC_FLUSH&t;&t;(1 &lt;&lt; 0)
DECL|macro|RADEON_RB3D_ZC_FREE
macro_line|#&t;define RADEON_RB3D_ZC_FREE&t;&t;(1 &lt;&lt; 2)
DECL|macro|RADEON_RB3D_ZC_FLUSH_ALL
macro_line|#&t;define RADEON_RB3D_ZC_FLUSH_ALL&t;&t;0x5
DECL|macro|RADEON_RB3D_ZC_BUSY
macro_line|#&t;define RADEON_RB3D_ZC_BUSY&t;&t;(1 &lt;&lt; 31)
DECL|macro|RADEON_RB3D_ZSTENCILCNTL
mdefine_line|#define RADEON_RB3D_ZSTENCILCNTL&t;0x1c2c
DECL|macro|RADEON_Z_TEST_MASK
macro_line|#&t;define RADEON_Z_TEST_MASK&t;&t;(7 &lt;&lt; 4)
DECL|macro|RADEON_Z_TEST_ALWAYS
macro_line|#&t;define RADEON_Z_TEST_ALWAYS&t;&t;(7 &lt;&lt; 4)
DECL|macro|RADEON_STENCIL_TEST_ALWAYS
macro_line|#&t;define RADEON_STENCIL_TEST_ALWAYS&t;(7 &lt;&lt; 12)
DECL|macro|RADEON_STENCIL_S_FAIL_REPLACE
macro_line|#&t;define RADEON_STENCIL_S_FAIL_REPLACE&t;(2 &lt;&lt; 16)
DECL|macro|RADEON_STENCIL_ZPASS_REPLACE
macro_line|#&t;define RADEON_STENCIL_ZPASS_REPLACE&t;(2 &lt;&lt; 20)
DECL|macro|RADEON_STENCIL_ZFAIL_REPLACE
macro_line|#&t;define RADEON_STENCIL_ZFAIL_REPLACE&t;(2 &lt;&lt; 24)
DECL|macro|RADEON_Z_WRITE_ENABLE
macro_line|#&t;define RADEON_Z_WRITE_ENABLE&t;&t;(1 &lt;&lt; 30)
DECL|macro|RADEON_RBBM_SOFT_RESET
mdefine_line|#define RADEON_RBBM_SOFT_RESET&t;&t;0x00f0
DECL|macro|RADEON_SOFT_RESET_CP
macro_line|#&t;define RADEON_SOFT_RESET_CP&t;&t;(1 &lt;&lt;  0)
DECL|macro|RADEON_SOFT_RESET_HI
macro_line|#&t;define RADEON_SOFT_RESET_HI&t;&t;(1 &lt;&lt;  1)
DECL|macro|RADEON_SOFT_RESET_SE
macro_line|#&t;define RADEON_SOFT_RESET_SE&t;&t;(1 &lt;&lt;  2)
DECL|macro|RADEON_SOFT_RESET_RE
macro_line|#&t;define RADEON_SOFT_RESET_RE&t;&t;(1 &lt;&lt;  3)
DECL|macro|RADEON_SOFT_RESET_PP
macro_line|#&t;define RADEON_SOFT_RESET_PP&t;&t;(1 &lt;&lt;  4)
DECL|macro|RADEON_SOFT_RESET_E2
macro_line|#&t;define RADEON_SOFT_RESET_E2&t;&t;(1 &lt;&lt;  5)
DECL|macro|RADEON_SOFT_RESET_RB
macro_line|#&t;define RADEON_SOFT_RESET_RB&t;&t;(1 &lt;&lt;  6)
DECL|macro|RADEON_SOFT_RESET_HDP
macro_line|#&t;define RADEON_SOFT_RESET_HDP&t;&t;(1 &lt;&lt;  7)
DECL|macro|RADEON_RBBM_STATUS
mdefine_line|#define RADEON_RBBM_STATUS&t;&t;0x0e40
DECL|macro|RADEON_RBBM_FIFOCNT_MASK
macro_line|#&t;define RADEON_RBBM_FIFOCNT_MASK&t;&t;0x007f
DECL|macro|RADEON_RBBM_ACTIVE
macro_line|#&t;define RADEON_RBBM_ACTIVE&t;&t;(1 &lt;&lt; 31)
DECL|macro|RADEON_RE_LINE_PATTERN
mdefine_line|#define RADEON_RE_LINE_PATTERN&t;&t;0x1cd0
DECL|macro|RADEON_RE_MISC
mdefine_line|#define RADEON_RE_MISC&t;&t;&t;0x26c4
DECL|macro|RADEON_RE_TOP_LEFT
mdefine_line|#define RADEON_RE_TOP_LEFT&t;&t;0x26c0
DECL|macro|RADEON_RE_WIDTH_HEIGHT
mdefine_line|#define RADEON_RE_WIDTH_HEIGHT&t;&t;0x1c44
DECL|macro|RADEON_RE_STIPPLE_ADDR
mdefine_line|#define RADEON_RE_STIPPLE_ADDR&t;&t;0x1cc8
DECL|macro|RADEON_RE_STIPPLE_DATA
mdefine_line|#define RADEON_RE_STIPPLE_DATA&t;&t;0x1ccc
DECL|macro|RADEON_SCISSOR_TL_0
mdefine_line|#define RADEON_SCISSOR_TL_0&t;&t;0x1cd8
DECL|macro|RADEON_SCISSOR_BR_0
mdefine_line|#define RADEON_SCISSOR_BR_0&t;&t;0x1cdc
DECL|macro|RADEON_SCISSOR_TL_1
mdefine_line|#define RADEON_SCISSOR_TL_1&t;&t;0x1ce0
DECL|macro|RADEON_SCISSOR_BR_1
mdefine_line|#define RADEON_SCISSOR_BR_1&t;&t;0x1ce4
DECL|macro|RADEON_SCISSOR_TL_2
mdefine_line|#define RADEON_SCISSOR_TL_2&t;&t;0x1ce8
DECL|macro|RADEON_SCISSOR_BR_2
mdefine_line|#define RADEON_SCISSOR_BR_2&t;&t;0x1cec
DECL|macro|RADEON_SE_COORD_FMT
mdefine_line|#define RADEON_SE_COORD_FMT&t;&t;0x1c50
DECL|macro|RADEON_SE_CNTL
mdefine_line|#define RADEON_SE_CNTL&t;&t;&t;0x1c4c
DECL|macro|RADEON_FFACE_CULL_CW
macro_line|#&t;define RADEON_FFACE_CULL_CW&t;&t;(0 &lt;&lt; 0)
DECL|macro|RADEON_BFACE_SOLID
macro_line|#&t;define RADEON_BFACE_SOLID&t;&t;(3 &lt;&lt; 1)
DECL|macro|RADEON_FFACE_SOLID
macro_line|#&t;define RADEON_FFACE_SOLID&t;&t;(3 &lt;&lt; 3)
DECL|macro|RADEON_FLAT_SHADE_VTX_LAST
macro_line|#&t;define RADEON_FLAT_SHADE_VTX_LAST&t;(3 &lt;&lt; 6)
DECL|macro|RADEON_DIFFUSE_SHADE_FLAT
macro_line|#&t;define RADEON_DIFFUSE_SHADE_FLAT&t;(1 &lt;&lt; 8)
DECL|macro|RADEON_DIFFUSE_SHADE_GOURAUD
macro_line|#&t;define RADEON_DIFFUSE_SHADE_GOURAUD&t;(2 &lt;&lt; 8)
DECL|macro|RADEON_ALPHA_SHADE_FLAT
macro_line|#&t;define RADEON_ALPHA_SHADE_FLAT&t;&t;(1 &lt;&lt; 10)
DECL|macro|RADEON_ALPHA_SHADE_GOURAUD
macro_line|#&t;define RADEON_ALPHA_SHADE_GOURAUD&t;(2 &lt;&lt; 10)
DECL|macro|RADEON_SPECULAR_SHADE_FLAT
macro_line|#&t;define RADEON_SPECULAR_SHADE_FLAT&t;(1 &lt;&lt; 12)
DECL|macro|RADEON_SPECULAR_SHADE_GOURAUD
macro_line|#&t;define RADEON_SPECULAR_SHADE_GOURAUD&t;(2 &lt;&lt; 12)
DECL|macro|RADEON_FOG_SHADE_FLAT
macro_line|#&t;define RADEON_FOG_SHADE_FLAT&t;&t;(1 &lt;&lt; 14)
DECL|macro|RADEON_FOG_SHADE_GOURAUD
macro_line|#&t;define RADEON_FOG_SHADE_GOURAUD&t;&t;(2 &lt;&lt; 14)
DECL|macro|RADEON_VPORT_XY_XFORM_ENABLE
macro_line|#&t;define RADEON_VPORT_XY_XFORM_ENABLE&t;(1 &lt;&lt; 24)
DECL|macro|RADEON_VPORT_Z_XFORM_ENABLE
macro_line|#&t;define RADEON_VPORT_Z_XFORM_ENABLE&t;(1 &lt;&lt; 25)
DECL|macro|RADEON_VTX_PIX_CENTER_OGL
macro_line|#&t;define RADEON_VTX_PIX_CENTER_OGL&t;(1 &lt;&lt; 27)
DECL|macro|RADEON_ROUND_MODE_TRUNC
macro_line|#&t;define RADEON_ROUND_MODE_TRUNC&t;&t;(0 &lt;&lt; 28)
DECL|macro|RADEON_ROUND_PREC_8TH_PIX
macro_line|#&t;define RADEON_ROUND_PREC_8TH_PIX&t;(1 &lt;&lt; 30)
DECL|macro|RADEON_SE_CNTL_STATUS
mdefine_line|#define RADEON_SE_CNTL_STATUS&t;&t;0x2140
DECL|macro|RADEON_SE_LINE_WIDTH
mdefine_line|#define RADEON_SE_LINE_WIDTH&t;&t;0x1db8
DECL|macro|RADEON_SE_VPORT_XSCALE
mdefine_line|#define RADEON_SE_VPORT_XSCALE&t;&t;0x1d98
DECL|macro|RADEON_SE_ZBIAS_FACTOR
mdefine_line|#define RADEON_SE_ZBIAS_FACTOR&t;&t;0x1db0
DECL|macro|RADEON_SE_TCL_MATERIAL_EMMISSIVE_RED
mdefine_line|#define RADEON_SE_TCL_MATERIAL_EMMISSIVE_RED 0x2210
DECL|macro|RADEON_SE_TCL_OUTPUT_VTX_FMT
mdefine_line|#define RADEON_SE_TCL_OUTPUT_VTX_FMT         0x2254
DECL|macro|RADEON_SE_TCL_VECTOR_INDX_REG
mdefine_line|#define RADEON_SE_TCL_VECTOR_INDX_REG        0x2200
DECL|macro|RADEON_VEC_INDX_OCTWORD_STRIDE_SHIFT
macro_line|#       define RADEON_VEC_INDX_OCTWORD_STRIDE_SHIFT  16
DECL|macro|RADEON_VEC_INDX_DWORD_COUNT_SHIFT
macro_line|#       define RADEON_VEC_INDX_DWORD_COUNT_SHIFT     28
DECL|macro|RADEON_SE_TCL_VECTOR_DATA_REG
mdefine_line|#define RADEON_SE_TCL_VECTOR_DATA_REG       0x2204
DECL|macro|RADEON_SE_TCL_SCALAR_INDX_REG
mdefine_line|#define RADEON_SE_TCL_SCALAR_INDX_REG       0x2208
DECL|macro|RADEON_SCAL_INDX_DWORD_STRIDE_SHIFT
macro_line|#       define RADEON_SCAL_INDX_DWORD_STRIDE_SHIFT  16
DECL|macro|RADEON_SE_TCL_SCALAR_DATA_REG
mdefine_line|#define RADEON_SE_TCL_SCALAR_DATA_REG       0x220C
DECL|macro|RADEON_SURFACE_ACCESS_FLAGS
mdefine_line|#define RADEON_SURFACE_ACCESS_FLAGS&t;0x0bf8
DECL|macro|RADEON_SURFACE_ACCESS_CLR
mdefine_line|#define RADEON_SURFACE_ACCESS_CLR&t;0x0bfc
DECL|macro|RADEON_SURFACE_CNTL
mdefine_line|#define RADEON_SURFACE_CNTL&t;&t;0x0b00
DECL|macro|RADEON_SURF_TRANSLATION_DIS
macro_line|#&t;define RADEON_SURF_TRANSLATION_DIS&t;(1 &lt;&lt; 8)
DECL|macro|RADEON_NONSURF_AP0_SWP_MASK
macro_line|#&t;define RADEON_NONSURF_AP0_SWP_MASK&t;(3 &lt;&lt; 20)
DECL|macro|RADEON_NONSURF_AP0_SWP_LITTLE
macro_line|#&t;define RADEON_NONSURF_AP0_SWP_LITTLE&t;(0 &lt;&lt; 20)
DECL|macro|RADEON_NONSURF_AP0_SWP_BIG16
macro_line|#&t;define RADEON_NONSURF_AP0_SWP_BIG16&t;(1 &lt;&lt; 20)
DECL|macro|RADEON_NONSURF_AP0_SWP_BIG32
macro_line|#&t;define RADEON_NONSURF_AP0_SWP_BIG32&t;(2 &lt;&lt; 20)
DECL|macro|RADEON_NONSURF_AP1_SWP_MASK
macro_line|#&t;define RADEON_NONSURF_AP1_SWP_MASK&t;(3 &lt;&lt; 22)
DECL|macro|RADEON_NONSURF_AP1_SWP_LITTLE
macro_line|#&t;define RADEON_NONSURF_AP1_SWP_LITTLE&t;(0 &lt;&lt; 22)
DECL|macro|RADEON_NONSURF_AP1_SWP_BIG16
macro_line|#&t;define RADEON_NONSURF_AP1_SWP_BIG16&t;(1 &lt;&lt; 22)
DECL|macro|RADEON_NONSURF_AP1_SWP_BIG32
macro_line|#&t;define RADEON_NONSURF_AP1_SWP_BIG32&t;(2 &lt;&lt; 22)
DECL|macro|RADEON_SURFACE0_INFO
mdefine_line|#define RADEON_SURFACE0_INFO&t;&t;0x0b0c
DECL|macro|RADEON_SURF_PITCHSEL_MASK
macro_line|#&t;define RADEON_SURF_PITCHSEL_MASK&t;(0x1ff &lt;&lt; 0)
DECL|macro|RADEON_SURF_TILE_MODE_MASK
macro_line|#&t;define RADEON_SURF_TILE_MODE_MASK&t;(3 &lt;&lt; 16)
DECL|macro|RADEON_SURF_TILE_MODE_MACRO
macro_line|#&t;define RADEON_SURF_TILE_MODE_MACRO&t;(0 &lt;&lt; 16)
DECL|macro|RADEON_SURF_TILE_MODE_MICRO
macro_line|#&t;define RADEON_SURF_TILE_MODE_MICRO&t;(1 &lt;&lt; 16)
DECL|macro|RADEON_SURF_TILE_MODE_32BIT_Z
macro_line|#&t;define RADEON_SURF_TILE_MODE_32BIT_Z&t;(2 &lt;&lt; 16)
DECL|macro|RADEON_SURF_TILE_MODE_16BIT_Z
macro_line|#&t;define RADEON_SURF_TILE_MODE_16BIT_Z&t;(3 &lt;&lt; 16)
DECL|macro|RADEON_SURFACE0_LOWER_BOUND
mdefine_line|#define RADEON_SURFACE0_LOWER_BOUND&t;0x0b04
DECL|macro|RADEON_SURFACE0_UPPER_BOUND
mdefine_line|#define RADEON_SURFACE0_UPPER_BOUND&t;0x0b08
DECL|macro|RADEON_SURFACE1_INFO
mdefine_line|#define RADEON_SURFACE1_INFO&t;&t;0x0b1c
DECL|macro|RADEON_SURFACE1_LOWER_BOUND
mdefine_line|#define RADEON_SURFACE1_LOWER_BOUND&t;0x0b14
DECL|macro|RADEON_SURFACE1_UPPER_BOUND
mdefine_line|#define RADEON_SURFACE1_UPPER_BOUND&t;0x0b18
DECL|macro|RADEON_SURFACE2_INFO
mdefine_line|#define RADEON_SURFACE2_INFO&t;&t;0x0b2c
DECL|macro|RADEON_SURFACE2_LOWER_BOUND
mdefine_line|#define RADEON_SURFACE2_LOWER_BOUND&t;0x0b24
DECL|macro|RADEON_SURFACE2_UPPER_BOUND
mdefine_line|#define RADEON_SURFACE2_UPPER_BOUND&t;0x0b28
DECL|macro|RADEON_SURFACE3_INFO
mdefine_line|#define RADEON_SURFACE3_INFO&t;&t;0x0b3c
DECL|macro|RADEON_SURFACE3_LOWER_BOUND
mdefine_line|#define RADEON_SURFACE3_LOWER_BOUND&t;0x0b34
DECL|macro|RADEON_SURFACE3_UPPER_BOUND
mdefine_line|#define RADEON_SURFACE3_UPPER_BOUND&t;0x0b38
DECL|macro|RADEON_SURFACE4_INFO
mdefine_line|#define RADEON_SURFACE4_INFO&t;&t;0x0b4c
DECL|macro|RADEON_SURFACE4_LOWER_BOUND
mdefine_line|#define RADEON_SURFACE4_LOWER_BOUND&t;0x0b44
DECL|macro|RADEON_SURFACE4_UPPER_BOUND
mdefine_line|#define RADEON_SURFACE4_UPPER_BOUND&t;0x0b48
DECL|macro|RADEON_SURFACE5_INFO
mdefine_line|#define RADEON_SURFACE5_INFO&t;&t;0x0b5c
DECL|macro|RADEON_SURFACE5_LOWER_BOUND
mdefine_line|#define RADEON_SURFACE5_LOWER_BOUND&t;0x0b54
DECL|macro|RADEON_SURFACE5_UPPER_BOUND
mdefine_line|#define RADEON_SURFACE5_UPPER_BOUND&t;0x0b58
DECL|macro|RADEON_SURFACE6_INFO
mdefine_line|#define RADEON_SURFACE6_INFO&t;&t;0x0b6c
DECL|macro|RADEON_SURFACE6_LOWER_BOUND
mdefine_line|#define RADEON_SURFACE6_LOWER_BOUND&t;0x0b64
DECL|macro|RADEON_SURFACE6_UPPER_BOUND
mdefine_line|#define RADEON_SURFACE6_UPPER_BOUND&t;0x0b68
DECL|macro|RADEON_SURFACE7_INFO
mdefine_line|#define RADEON_SURFACE7_INFO&t;&t;0x0b7c
DECL|macro|RADEON_SURFACE7_LOWER_BOUND
mdefine_line|#define RADEON_SURFACE7_LOWER_BOUND&t;0x0b74
DECL|macro|RADEON_SURFACE7_UPPER_BOUND
mdefine_line|#define RADEON_SURFACE7_UPPER_BOUND&t;0x0b78
DECL|macro|RADEON_SW_SEMAPHORE
mdefine_line|#define RADEON_SW_SEMAPHORE&t;&t;0x013c
DECL|macro|RADEON_WAIT_UNTIL
mdefine_line|#define RADEON_WAIT_UNTIL&t;&t;0x1720
DECL|macro|RADEON_WAIT_CRTC_PFLIP
macro_line|#&t;define RADEON_WAIT_CRTC_PFLIP&t;&t;(1 &lt;&lt; 0)
DECL|macro|RADEON_WAIT_2D_IDLECLEAN
macro_line|#&t;define RADEON_WAIT_2D_IDLECLEAN&t;&t;(1 &lt;&lt; 16)
DECL|macro|RADEON_WAIT_3D_IDLECLEAN
macro_line|#&t;define RADEON_WAIT_3D_IDLECLEAN&t;&t;(1 &lt;&lt; 17)
DECL|macro|RADEON_WAIT_HOST_IDLECLEAN
macro_line|#&t;define RADEON_WAIT_HOST_IDLECLEAN&t;(1 &lt;&lt; 18)
DECL|macro|RADEON_RB3D_ZMASKOFFSET
mdefine_line|#define RADEON_RB3D_ZMASKOFFSET&t;&t;0x1c34
DECL|macro|RADEON_RB3D_ZSTENCILCNTL
mdefine_line|#define RADEON_RB3D_ZSTENCILCNTL&t;0x1c2c
DECL|macro|RADEON_DEPTH_FORMAT_16BIT_INT_Z
macro_line|#&t;define RADEON_DEPTH_FORMAT_16BIT_INT_Z&t;(0 &lt;&lt; 0)
DECL|macro|RADEON_DEPTH_FORMAT_24BIT_INT_Z
macro_line|#&t;define RADEON_DEPTH_FORMAT_24BIT_INT_Z&t;(2 &lt;&lt; 0)
multiline_comment|/* CP registers */
DECL|macro|RADEON_CP_ME_RAM_ADDR
mdefine_line|#define RADEON_CP_ME_RAM_ADDR&t;&t;0x07d4
DECL|macro|RADEON_CP_ME_RAM_RADDR
mdefine_line|#define RADEON_CP_ME_RAM_RADDR&t;&t;0x07d8
DECL|macro|RADEON_CP_ME_RAM_DATAH
mdefine_line|#define RADEON_CP_ME_RAM_DATAH&t;&t;0x07dc
DECL|macro|RADEON_CP_ME_RAM_DATAL
mdefine_line|#define RADEON_CP_ME_RAM_DATAL&t;&t;0x07e0
DECL|macro|RADEON_CP_RB_BASE
mdefine_line|#define RADEON_CP_RB_BASE&t;&t;0x0700
DECL|macro|RADEON_CP_RB_CNTL
mdefine_line|#define RADEON_CP_RB_CNTL&t;&t;0x0704
DECL|macro|RADEON_CP_RB_RPTR_ADDR
mdefine_line|#define RADEON_CP_RB_RPTR_ADDR&t;&t;0x070c
DECL|macro|RADEON_CP_RB_RPTR
mdefine_line|#define RADEON_CP_RB_RPTR&t;&t;0x0710
DECL|macro|RADEON_CP_RB_WPTR
mdefine_line|#define RADEON_CP_RB_WPTR&t;&t;0x0714
DECL|macro|RADEON_CP_RB_WPTR_DELAY
mdefine_line|#define RADEON_CP_RB_WPTR_DELAY&t;&t;0x0718
DECL|macro|RADEON_PRE_WRITE_TIMER_SHIFT
macro_line|#&t;define RADEON_PRE_WRITE_TIMER_SHIFT&t;0
DECL|macro|RADEON_PRE_WRITE_LIMIT_SHIFT
macro_line|#&t;define RADEON_PRE_WRITE_LIMIT_SHIFT&t;23
DECL|macro|RADEON_CP_IB_BASE
mdefine_line|#define RADEON_CP_IB_BASE&t;&t;0x0738
DECL|macro|RADEON_CP_CSQ_CNTL
mdefine_line|#define RADEON_CP_CSQ_CNTL&t;&t;0x0740
DECL|macro|RADEON_CSQ_CNT_PRIMARY_MASK
macro_line|#&t;define RADEON_CSQ_CNT_PRIMARY_MASK&t;(0xff &lt;&lt; 0)
DECL|macro|RADEON_CSQ_PRIDIS_INDDIS
macro_line|#&t;define RADEON_CSQ_PRIDIS_INDDIS&t;&t;(0 &lt;&lt; 28)
DECL|macro|RADEON_CSQ_PRIPIO_INDDIS
macro_line|#&t;define RADEON_CSQ_PRIPIO_INDDIS&t;&t;(1 &lt;&lt; 28)
DECL|macro|RADEON_CSQ_PRIBM_INDDIS
macro_line|#&t;define RADEON_CSQ_PRIBM_INDDIS&t;&t;(2 &lt;&lt; 28)
DECL|macro|RADEON_CSQ_PRIPIO_INDBM
macro_line|#&t;define RADEON_CSQ_PRIPIO_INDBM&t;&t;(3 &lt;&lt; 28)
DECL|macro|RADEON_CSQ_PRIBM_INDBM
macro_line|#&t;define RADEON_CSQ_PRIBM_INDBM&t;&t;(4 &lt;&lt; 28)
DECL|macro|RADEON_CSQ_PRIPIO_INDPIO
macro_line|#&t;define RADEON_CSQ_PRIPIO_INDPIO&t;&t;(15 &lt;&lt; 28)
DECL|macro|RADEON_AIC_CNTL
mdefine_line|#define RADEON_AIC_CNTL&t;&t;&t;0x01d0
DECL|macro|RADEON_PCIGART_TRANSLATE_EN
macro_line|#&t;define RADEON_PCIGART_TRANSLATE_EN&t;(1 &lt;&lt; 0)
DECL|macro|RADEON_AIC_STAT
mdefine_line|#define RADEON_AIC_STAT&t;&t;&t;0x01d4
DECL|macro|RADEON_AIC_PT_BASE
mdefine_line|#define RADEON_AIC_PT_BASE&t;&t;0x01d8
DECL|macro|RADEON_AIC_LO_ADDR
mdefine_line|#define RADEON_AIC_LO_ADDR&t;&t;0x01dc
DECL|macro|RADEON_AIC_HI_ADDR
mdefine_line|#define RADEON_AIC_HI_ADDR&t;&t;0x01e0
DECL|macro|RADEON_AIC_TLB_ADDR
mdefine_line|#define RADEON_AIC_TLB_ADDR&t;&t;0x01e4
DECL|macro|RADEON_AIC_TLB_DATA
mdefine_line|#define RADEON_AIC_TLB_DATA&t;&t;0x01e8
multiline_comment|/* CP command packets */
DECL|macro|RADEON_CP_PACKET0
mdefine_line|#define RADEON_CP_PACKET0&t;&t;0x00000000
DECL|macro|RADEON_ONE_REG_WR
macro_line|#&t;define RADEON_ONE_REG_WR&t;&t;(1 &lt;&lt; 15)
DECL|macro|RADEON_CP_PACKET1
mdefine_line|#define RADEON_CP_PACKET1&t;&t;0x40000000
DECL|macro|RADEON_CP_PACKET2
mdefine_line|#define RADEON_CP_PACKET2&t;&t;0x80000000
DECL|macro|RADEON_CP_PACKET3
mdefine_line|#define RADEON_CP_PACKET3&t;&t;0xC0000000
DECL|macro|RADEON_3D_RNDR_GEN_INDX_PRIM
macro_line|#&t;define RADEON_3D_RNDR_GEN_INDX_PRIM&t;0x00002300
DECL|macro|RADEON_WAIT_FOR_IDLE
macro_line|#&t;define RADEON_WAIT_FOR_IDLE&t;&t;0x00002600
DECL|macro|RADEON_3D_DRAW_VBUF
macro_line|#&t;define RADEON_3D_DRAW_VBUF&t;&t;0x00002800
DECL|macro|RADEON_3D_DRAW_IMMD
macro_line|#&t;define RADEON_3D_DRAW_IMMD&t;&t;0x00002900
DECL|macro|RADEON_3D_DRAW_INDX
macro_line|#&t;define RADEON_3D_DRAW_INDX&t;&t;0x00002A00
DECL|macro|RADEON_3D_LOAD_VBPNTR
macro_line|#&t;define RADEON_3D_LOAD_VBPNTR&t;&t;0x00002F00
DECL|macro|RADEON_CNTL_HOSTDATA_BLT
macro_line|#&t;define RADEON_CNTL_HOSTDATA_BLT&t;&t;0x00009400
DECL|macro|RADEON_CNTL_PAINT_MULTI
macro_line|#&t;define RADEON_CNTL_PAINT_MULTI&t;&t;0x00009A00
DECL|macro|RADEON_CNTL_BITBLT_MULTI
macro_line|#&t;define RADEON_CNTL_BITBLT_MULTI&t;&t;0x00009B00
DECL|macro|RADEON_CP_PACKET_MASK
mdefine_line|#define RADEON_CP_PACKET_MASK&t;&t;0xC0000000
DECL|macro|RADEON_CP_PACKET_COUNT_MASK
mdefine_line|#define RADEON_CP_PACKET_COUNT_MASK&t;0x3fff0000
DECL|macro|RADEON_CP_PACKET0_REG_MASK
mdefine_line|#define RADEON_CP_PACKET0_REG_MASK&t;0x000007ff
DECL|macro|RADEON_CP_PACKET1_REG0_MASK
mdefine_line|#define RADEON_CP_PACKET1_REG0_MASK&t;0x000007ff
DECL|macro|RADEON_CP_PACKET1_REG1_MASK
mdefine_line|#define RADEON_CP_PACKET1_REG1_MASK&t;0x003ff800
DECL|macro|RADEON_VTX_Z_PRESENT
mdefine_line|#define RADEON_VTX_Z_PRESENT&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|RADEON_VTX_PKCOLOR_PRESENT
mdefine_line|#define RADEON_VTX_PKCOLOR_PRESENT&t;&t;(1 &lt;&lt; 3)
DECL|macro|RADEON_PRIM_TYPE_NONE
mdefine_line|#define RADEON_PRIM_TYPE_NONE&t;&t;&t;(0 &lt;&lt; 0)
DECL|macro|RADEON_PRIM_TYPE_POINT
mdefine_line|#define RADEON_PRIM_TYPE_POINT&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|RADEON_PRIM_TYPE_LINE
mdefine_line|#define RADEON_PRIM_TYPE_LINE&t;&t;&t;(2 &lt;&lt; 0)
DECL|macro|RADEON_PRIM_TYPE_LINE_STRIP
mdefine_line|#define RADEON_PRIM_TYPE_LINE_STRIP&t;&t;(3 &lt;&lt; 0)
DECL|macro|RADEON_PRIM_TYPE_TRI_LIST
mdefine_line|#define RADEON_PRIM_TYPE_TRI_LIST&t;&t;(4 &lt;&lt; 0)
DECL|macro|RADEON_PRIM_TYPE_TRI_FAN
mdefine_line|#define RADEON_PRIM_TYPE_TRI_FAN&t;&t;(5 &lt;&lt; 0)
DECL|macro|RADEON_PRIM_TYPE_TRI_STRIP
mdefine_line|#define RADEON_PRIM_TYPE_TRI_STRIP&t;&t;(6 &lt;&lt; 0)
DECL|macro|RADEON_PRIM_TYPE_TRI_TYPE2
mdefine_line|#define RADEON_PRIM_TYPE_TRI_TYPE2&t;&t;(7 &lt;&lt; 0)
DECL|macro|RADEON_PRIM_TYPE_RECT_LIST
mdefine_line|#define RADEON_PRIM_TYPE_RECT_LIST&t;&t;(8 &lt;&lt; 0)
DECL|macro|RADEON_PRIM_TYPE_3VRT_POINT_LIST
mdefine_line|#define RADEON_PRIM_TYPE_3VRT_POINT_LIST&t;(9 &lt;&lt; 0)
DECL|macro|RADEON_PRIM_TYPE_3VRT_LINE_LIST
mdefine_line|#define RADEON_PRIM_TYPE_3VRT_LINE_LIST&t;&t;(10 &lt;&lt; 0)
DECL|macro|RADEON_PRIM_TYPE_MASK
mdefine_line|#define RADEON_PRIM_TYPE_MASK                   0xf
DECL|macro|RADEON_PRIM_WALK_IND
mdefine_line|#define RADEON_PRIM_WALK_IND&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|RADEON_PRIM_WALK_LIST
mdefine_line|#define RADEON_PRIM_WALK_LIST&t;&t;&t;(2 &lt;&lt; 4)
DECL|macro|RADEON_PRIM_WALK_RING
mdefine_line|#define RADEON_PRIM_WALK_RING&t;&t;&t;(3 &lt;&lt; 4)
DECL|macro|RADEON_COLOR_ORDER_BGRA
mdefine_line|#define RADEON_COLOR_ORDER_BGRA&t;&t;&t;(0 &lt;&lt; 6)
DECL|macro|RADEON_COLOR_ORDER_RGBA
mdefine_line|#define RADEON_COLOR_ORDER_RGBA&t;&t;&t;(1 &lt;&lt; 6)
DECL|macro|RADEON_MAOS_ENABLE
mdefine_line|#define RADEON_MAOS_ENABLE&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|RADEON_VTX_FMT_R128_MODE
mdefine_line|#define RADEON_VTX_FMT_R128_MODE&t;&t;(0 &lt;&lt; 8)
DECL|macro|RADEON_VTX_FMT_RADEON_MODE
mdefine_line|#define RADEON_VTX_FMT_RADEON_MODE&t;&t;(1 &lt;&lt; 8)
DECL|macro|RADEON_NUM_VERTICES_SHIFT
mdefine_line|#define RADEON_NUM_VERTICES_SHIFT&t;&t;16
DECL|macro|RADEON_COLOR_FORMAT_CI8
mdefine_line|#define RADEON_COLOR_FORMAT_CI8&t;&t;2
DECL|macro|RADEON_COLOR_FORMAT_ARGB1555
mdefine_line|#define RADEON_COLOR_FORMAT_ARGB1555&t;3
DECL|macro|RADEON_COLOR_FORMAT_RGB565
mdefine_line|#define RADEON_COLOR_FORMAT_RGB565&t;4
DECL|macro|RADEON_COLOR_FORMAT_ARGB8888
mdefine_line|#define RADEON_COLOR_FORMAT_ARGB8888&t;6
DECL|macro|RADEON_COLOR_FORMAT_RGB332
mdefine_line|#define RADEON_COLOR_FORMAT_RGB332&t;7
DECL|macro|RADEON_COLOR_FORMAT_RGB8
mdefine_line|#define RADEON_COLOR_FORMAT_RGB8&t;9
DECL|macro|RADEON_COLOR_FORMAT_ARGB4444
mdefine_line|#define RADEON_COLOR_FORMAT_ARGB4444&t;15
DECL|macro|RADEON_TXFORMAT_I8
mdefine_line|#define RADEON_TXFORMAT_I8&t;&t;0
DECL|macro|RADEON_TXFORMAT_AI88
mdefine_line|#define RADEON_TXFORMAT_AI88&t;&t;1
DECL|macro|RADEON_TXFORMAT_RGB332
mdefine_line|#define RADEON_TXFORMAT_RGB332&t;&t;2
DECL|macro|RADEON_TXFORMAT_ARGB1555
mdefine_line|#define RADEON_TXFORMAT_ARGB1555&t;3
DECL|macro|RADEON_TXFORMAT_RGB565
mdefine_line|#define RADEON_TXFORMAT_RGB565&t;&t;4
DECL|macro|RADEON_TXFORMAT_ARGB4444
mdefine_line|#define RADEON_TXFORMAT_ARGB4444&t;5
DECL|macro|RADEON_TXFORMAT_ARGB8888
mdefine_line|#define RADEON_TXFORMAT_ARGB8888&t;6
DECL|macro|RADEON_TXFORMAT_RGBA8888
mdefine_line|#define RADEON_TXFORMAT_RGBA8888&t;7
multiline_comment|/* Constants */
DECL|macro|RADEON_MAX_USEC_TIMEOUT
mdefine_line|#define RADEON_MAX_USEC_TIMEOUT&t;&t;100000&t;/* 100 ms */
DECL|macro|RADEON_LAST_FRAME_REG
mdefine_line|#define RADEON_LAST_FRAME_REG&t;&t;RADEON_SCRATCH_REG0
DECL|macro|RADEON_LAST_DISPATCH_REG
mdefine_line|#define RADEON_LAST_DISPATCH_REG&t;RADEON_SCRATCH_REG1
DECL|macro|RADEON_LAST_CLEAR_REG
mdefine_line|#define RADEON_LAST_CLEAR_REG&t;&t;RADEON_SCRATCH_REG2
DECL|macro|RADEON_LAST_DISPATCH
mdefine_line|#define RADEON_LAST_DISPATCH&t;&t;1
DECL|macro|RADEON_MAX_VB_AGE
mdefine_line|#define RADEON_MAX_VB_AGE&t;&t;0x7fffffff
DECL|macro|RADEON_MAX_VB_VERTS
mdefine_line|#define RADEON_MAX_VB_VERTS&t;&t;(0xffff)
DECL|macro|RADEON_RING_HIGH_MARK
mdefine_line|#define RADEON_RING_HIGH_MARK&t;&t;128
DECL|macro|RADEON_BASE
mdefine_line|#define RADEON_BASE(reg)&t;((unsigned long)(dev_priv-&gt;mmio-&gt;handle))
DECL|macro|RADEON_ADDR
mdefine_line|#define RADEON_ADDR(reg)&t;(RADEON_BASE( reg ) + reg)
DECL|macro|RADEON_DEREF
mdefine_line|#define RADEON_DEREF(reg)&t;*(volatile u32 *)RADEON_ADDR( reg )
macro_line|#ifdef __alpha__
DECL|macro|RADEON_READ
mdefine_line|#define RADEON_READ(reg)&t;(_RADEON_READ((u32 *)RADEON_ADDR( reg )))
DECL|function|_RADEON_READ
r_static
r_inline
id|u32
id|_RADEON_READ
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
DECL|macro|RADEON_WRITE
mdefine_line|#define RADEON_WRITE(reg,val)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wmb();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;RADEON_DEREF(reg) = val;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else
DECL|macro|RADEON_READ
mdefine_line|#define RADEON_READ(reg)&t;RADEON_DEREF( reg )
DECL|macro|RADEON_WRITE
mdefine_line|#define RADEON_WRITE(reg, val)&t;do { RADEON_DEREF( reg ) = val; } while (0)
macro_line|#endif
DECL|macro|RADEON_DEREF8
mdefine_line|#define RADEON_DEREF8(reg)&t;*(volatile u8 *)RADEON_ADDR( reg )
macro_line|#ifdef __alpha__
DECL|macro|RADEON_READ8
mdefine_line|#define RADEON_READ8(reg)&t;_RADEON_READ8((u8 *)RADEON_ADDR( reg ))
DECL|function|_RADEON_READ8
r_static
r_inline
id|u8
id|_RADEON_READ8
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
DECL|macro|RADEON_WRITE8
mdefine_line|#define RADEON_WRITE8(reg,val)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wmb();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;RADEON_DEREF8( reg ) = val;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else
DECL|macro|RADEON_READ8
mdefine_line|#define RADEON_READ8(reg)&t;RADEON_DEREF8( reg )
DECL|macro|RADEON_WRITE8
mdefine_line|#define RADEON_WRITE8(reg, val)&t;do { RADEON_DEREF8( reg ) = val; } while (0)
macro_line|#endif
DECL|macro|RADEON_WRITE_PLL
mdefine_line|#define RADEON_WRITE_PLL( addr, val )&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;RADEON_WRITE8( RADEON_CLOCK_CNTL_INDEX,&t;&t;&t;&t;&bslash;&n;&t;&t;       ((addr) &amp; 0x1f) | RADEON_PLL_WR_EN );&t;&t;&bslash;&n;&t;RADEON_WRITE( RADEON_CLOCK_CNTL_DATA, (val) );&t;&t;&t;&bslash;&n;} while (0)
r_extern
r_int
id|RADEON_READ_PLL
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
DECL|macro|CP_PACKET0
mdefine_line|#define CP_PACKET0( reg, n )&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(RADEON_CP_PACKET0 | ((n) &lt;&lt; 16) | ((reg) &gt;&gt; 2))
DECL|macro|CP_PACKET0_TABLE
mdefine_line|#define CP_PACKET0_TABLE( reg, n )&t;&t;&t;&t;&t;&bslash;&n;&t;(RADEON_CP_PACKET0 | RADEON_ONE_REG_WR | ((n) &lt;&lt; 16) | ((reg) &gt;&gt; 2))
DECL|macro|CP_PACKET1
mdefine_line|#define CP_PACKET1( reg0, reg1 )&t;&t;&t;&t;&t;&bslash;&n;&t;(RADEON_CP_PACKET1 | (((reg1) &gt;&gt; 2) &lt;&lt; 15) | ((reg0) &gt;&gt; 2))
DECL|macro|CP_PACKET2
mdefine_line|#define CP_PACKET2()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(RADEON_CP_PACKET2)
DECL|macro|CP_PACKET3
mdefine_line|#define CP_PACKET3( pkt, n )&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(RADEON_CP_PACKET3 | (pkt) | ((n) &lt;&lt; 16))
multiline_comment|/* ================================================================&n; * Engine control helper macros&n; */
DECL|macro|RADEON_WAIT_UNTIL_2D_IDLE
mdefine_line|#define RADEON_WAIT_UNTIL_2D_IDLE() do {&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CP_PACKET0( RADEON_WAIT_UNTIL, 0 ) );&t;&t;&t;&bslash;&n;&t;OUT_RING( (RADEON_WAIT_2D_IDLECLEAN |&t;&t;&t;&t;&bslash;&n;&t;&t;   RADEON_WAIT_HOST_IDLECLEAN) );&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RADEON_WAIT_UNTIL_3D_IDLE
mdefine_line|#define RADEON_WAIT_UNTIL_3D_IDLE() do {&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CP_PACKET0( RADEON_WAIT_UNTIL, 0 ) );&t;&t;&t;&bslash;&n;&t;OUT_RING( (RADEON_WAIT_3D_IDLECLEAN |&t;&t;&t;&t;&bslash;&n;&t;&t;   RADEON_WAIT_HOST_IDLECLEAN) );&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RADEON_WAIT_UNTIL_IDLE
mdefine_line|#define RADEON_WAIT_UNTIL_IDLE() do {&t;&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CP_PACKET0( RADEON_WAIT_UNTIL, 0 ) );&t;&t;&t;&bslash;&n;&t;OUT_RING( (RADEON_WAIT_2D_IDLECLEAN |&t;&t;&t;&t;&bslash;&n;&t;&t;   RADEON_WAIT_3D_IDLECLEAN |&t;&t;&t;&t;&bslash;&n;&t;&t;   RADEON_WAIT_HOST_IDLECLEAN) );&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RADEON_WAIT_UNTIL_PAGE_FLIPPED
mdefine_line|#define RADEON_WAIT_UNTIL_PAGE_FLIPPED() do {&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CP_PACKET0( RADEON_WAIT_UNTIL, 0 ) );&t;&t;&t;&bslash;&n;&t;OUT_RING( RADEON_WAIT_CRTC_PFLIP );&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RADEON_FLUSH_CACHE
mdefine_line|#define RADEON_FLUSH_CACHE() do {&t;&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CP_PACKET0( RADEON_RB2D_DSTCACHE_CTLSTAT, 0 ) );&t;&bslash;&n;&t;OUT_RING( RADEON_RB2D_DC_FLUSH );&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RADEON_PURGE_CACHE
mdefine_line|#define RADEON_PURGE_CACHE() do {&t;&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CP_PACKET0( RADEON_RB2D_DSTCACHE_CTLSTAT, 0 ) );&t;&bslash;&n;&t;OUT_RING( RADEON_RB2D_DC_FLUSH_ALL );&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RADEON_FLUSH_ZCACHE
mdefine_line|#define RADEON_FLUSH_ZCACHE() do {&t;&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CP_PACKET0( RADEON_RB3D_ZCACHE_CTLSTAT, 0 ) );&t;&bslash;&n;&t;OUT_RING( RADEON_RB3D_ZC_FLUSH );&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RADEON_PURGE_ZCACHE
mdefine_line|#define RADEON_PURGE_ZCACHE() do {&t;&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CP_PACKET0( RADEON_RB3D_ZCACHE_CTLSTAT, 0 ) );&t;&bslash;&n;&t;OUT_RING( RADEON_RB3D_ZC_FLUSH_ALL );&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* ================================================================&n; * Misc helper macros&n; */
DECL|macro|LOCK_TEST_WITH_RETURN
mdefine_line|#define LOCK_TEST_WITH_RETURN( dev )&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( !_DRM_LOCK_IS_HELD( dev-&gt;lock.hw_lock-&gt;lock ) ||&t;&t;&bslash;&n;&t;     dev-&gt;lock.pid != current-&gt;pid ) {&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_ERROR( &quot;%s called without lock held&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&t;   __FUNCTION__ );&t;&t;&t;&t;&bslash;&n;&t;&t;return -EINVAL;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RING_SPACE_TEST_WITH_RETURN
mdefine_line|#define RING_SPACE_TEST_WITH_RETURN( dev_priv )&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;drm_radeon_ring_buffer_t *ring = &amp;dev_priv-&gt;ring; int i;&t;&bslash;&n;&t;if ( ring-&gt;space &lt; ring-&gt;high_mark ) {&t;&t;&t;&t;&bslash;&n;&t;&t;for ( i = 0 ; i &lt; dev_priv-&gt;usec_timeout ; i++ ) {&t;&bslash;&n;&t;&t;&t;radeon_update_ring_snapshot( ring );&t;&t;&bslash;&n;&t;&t;&t;if ( ring-&gt;space &gt;= ring-&gt;high_mark )&t;&t;&bslash;&n;&t;&t;&t;&t;goto __ring_space_done;&t;&t;&t;&bslash;&n;&t;&t;&t;udelay( 1 );&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_ERROR( &quot;ring space check failed!&bslash;n&quot; );&t;&t;&bslash;&n;&t;&t;return -EBUSY;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; __ring_space_done:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|VB_AGE_TEST_WITH_RETURN
mdefine_line|#define VB_AGE_TEST_WITH_RETURN( dev_priv )&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;drm_radeon_sarea_t *sarea_priv = dev_priv-&gt;sarea_priv;&t;&t;&bslash;&n;&t;if ( sarea_priv-&gt;last_dispatch &gt;= RADEON_MAX_VB_AGE ) {&t;&t;&bslash;&n;&t;&t;int __ret = radeon_do_cp_idle( dev_priv );&t;&t;&bslash;&n;&t;&t;if ( __ret &lt; 0 ) return __ret;&t;&t;&t;&t;&bslash;&n;&t;&t;sarea_priv-&gt;last_dispatch = 0;&t;&t;&t;&t;&bslash;&n;&t;&t;radeon_freelist_reset( dev );&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RADEON_DISPATCH_AGE
mdefine_line|#define RADEON_DISPATCH_AGE( age ) do {&t;&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CP_PACKET0( RADEON_LAST_DISPATCH_REG, 0 ) );&t;&t;&bslash;&n;&t;OUT_RING( age );&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RADEON_FRAME_AGE
mdefine_line|#define RADEON_FRAME_AGE( age ) do {&t;&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CP_PACKET0( RADEON_LAST_FRAME_REG, 0 ) );&t;&t;&bslash;&n;&t;OUT_RING( age );&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RADEON_CLEAR_AGE
mdefine_line|#define RADEON_CLEAR_AGE( age ) do {&t;&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CP_PACKET0( RADEON_LAST_CLEAR_REG, 0 ) );&t;&t;&bslash;&n;&t;OUT_RING( age );&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* ================================================================&n; * Ring control&n; */
DECL|macro|radeon_flush_write_combine
mdefine_line|#define radeon_flush_write_combine()&t;mb()
DECL|macro|RADEON_VERBOSE
mdefine_line|#define RADEON_VERBOSE&t;0
DECL|macro|RING_LOCALS
mdefine_line|#define RING_LOCALS&t;int write, _nr; unsigned int mask; volatile u32 *ring;
DECL|macro|BEGIN_RING
mdefine_line|#define BEGIN_RING( n ) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( RADEON_VERBOSE ) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( &quot;BEGIN_RING( %d ) in %s&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;&t;   n, __FUNCTION__ );&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( dev_priv-&gt;ring.space &lt;= (n) * sizeof(u32) ) {&t;&t;&bslash;&n;                COMMIT_RING();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;radeon_wait_ring( dev_priv, (n) * sizeof(u32) );&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_nr = n; dev_priv-&gt;ring.space -= (n) * sizeof(u32);&t;&t;&bslash;&n;&t;ring = dev_priv-&gt;ring.start;&t;&t;&t;&t;&t;&bslash;&n;&t;write = dev_priv-&gt;ring.tail;&t;&t;&t;&t;&t;&bslash;&n;&t;mask = dev_priv-&gt;ring.tail_mask;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|ADVANCE_RING
mdefine_line|#define ADVANCE_RING() do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( RADEON_VERBOSE ) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( &quot;ADVANCE_RING() wr=0x%06x tail=0x%06x&bslash;n&quot;,&t;&bslash;&n;&t;&t;&t;  write, dev_priv-&gt;ring.tail );&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (((dev_priv-&gt;ring.tail + _nr) &amp; mask) != write) {&t;&t;&bslash;&n;&t;&t;DRM_ERROR( &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;ADVANCE_RING(): mismatch: nr: %x write: %x&bslash;n&quot;,&t;&bslash;&n;&t;&t;&t;((dev_priv-&gt;ring.tail + _nr) &amp; mask),&t;&t;&bslash;&n;&t;&t;&t;write);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;dev_priv-&gt;ring.tail = write;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|COMMIT_RING
mdefine_line|#define COMMIT_RING() do {&t;&t;&t;&t;&t;    &bslash;&n;&t;RADEON_WRITE( RADEON_CP_RB_WPTR, dev_priv-&gt;ring.tail );&t;&t;    &bslash;&n;} while (0)
DECL|macro|OUT_RING
mdefine_line|#define OUT_RING( x ) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( RADEON_VERBOSE ) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( &quot;   OUT_RING( 0x%08x ) at 0x%x&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&t;   (unsigned int)(x), write );&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ring[write++] = (x);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;write &amp;= mask;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|OUT_RING_REG
mdefine_line|#define OUT_RING_REG( reg, val ) do {&t;&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( CP_PACKET0( reg, 0 ) );&t;&t;&t;&t;&bslash;&n;&t;OUT_RING( val );&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|OUT_RING_USER_TABLE
mdefine_line|#define OUT_RING_USER_TABLE( tab, sz ) do {&t;&t;&t;&bslash;&n;&t;int _size = (sz);&t;&t;&t;&t;&t;&bslash;&n;&t;int *_tab = (tab);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (write + _size &gt; mask) {&t;&t;&t;&t;&bslash;&n;&t;&t;int i = (mask+1) - write;&t;&t;&t;&bslash;&n;&t;&t;if (__copy_from_user( (int *)(ring+write),&t;&bslash;&n;&t;&t;&t;&t;      _tab, i*4 ))&t;&t;&bslash;&n;&t;&t;&t;return -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;&t;write = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_size -= i;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_tab += i;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (_size &amp;&amp; __copy_from_user( (int *)(ring+write),&t;&bslash;&n;&t;&t;&t;               _tab, _size*4 ))&t;&t;&bslash;&n;&t;&t;return -EFAULT;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;write += _size;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;write &amp;= mask;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|RADEON_PERFORMANCE_BOXES
mdefine_line|#define RADEON_PERFORMANCE_BOXES&t;0
macro_line|#endif /* __RADEON_DRV_H__ */
eof
