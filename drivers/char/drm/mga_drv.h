multiline_comment|/* mga_drv.h -- Private header for the Matrox G200/G400 driver -*- linux-c -*-&n; * Created: Mon Dec 13 01:50:01 1999 by jhartmann@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#ifndef __MGA_DRV_H__
DECL|macro|__MGA_DRV_H__
mdefine_line|#define __MGA_DRV_H__
DECL|struct|drm_mga_primary_buffer
r_typedef
r_struct
id|drm_mga_primary_buffer
(brace
DECL|member|start
id|u8
op_star
id|start
suffix:semicolon
DECL|member|end
id|u8
op_star
id|end
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|tail
id|u32
id|tail
suffix:semicolon
DECL|member|space
r_int
id|space
suffix:semicolon
DECL|member|wrapped
r_volatile
r_int
id|wrapped
suffix:semicolon
DECL|member|status
r_volatile
id|u32
op_star
id|status
suffix:semicolon
DECL|member|last_flush
id|u32
id|last_flush
suffix:semicolon
DECL|member|last_wrap
id|u32
id|last_wrap
suffix:semicolon
DECL|member|high_mark
id|u32
id|high_mark
suffix:semicolon
DECL|member|list_lock
id|spinlock_t
id|list_lock
suffix:semicolon
DECL|typedef|drm_mga_primary_buffer_t
)brace
id|drm_mga_primary_buffer_t
suffix:semicolon
DECL|struct|drm_mga_freelist
r_typedef
r_struct
id|drm_mga_freelist
(brace
DECL|member|next
r_struct
id|drm_mga_freelist
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|drm_mga_freelist
op_star
id|prev
suffix:semicolon
DECL|member|age
id|drm_mga_age_t
id|age
suffix:semicolon
DECL|member|buf
id|drm_buf_t
op_star
id|buf
suffix:semicolon
DECL|typedef|drm_mga_freelist_t
)brace
id|drm_mga_freelist_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|list_entry
id|drm_mga_freelist_t
op_star
id|list_entry
suffix:semicolon
DECL|member|discard
r_int
id|discard
suffix:semicolon
DECL|member|dispatched
r_int
id|dispatched
suffix:semicolon
DECL|typedef|drm_mga_buf_priv_t
)brace
id|drm_mga_buf_priv_t
suffix:semicolon
DECL|struct|drm_mga_private
r_typedef
r_struct
id|drm_mga_private
(brace
DECL|member|prim
id|drm_mga_primary_buffer_t
id|prim
suffix:semicolon
DECL|member|sarea_priv
id|drm_mga_sarea_t
op_star
id|sarea_priv
suffix:semicolon
DECL|member|head
id|drm_mga_freelist_t
op_star
id|head
suffix:semicolon
DECL|member|tail
id|drm_mga_freelist_t
op_star
id|tail
suffix:semicolon
DECL|member|warp_pipe
r_int
r_int
id|warp_pipe
suffix:semicolon
DECL|member|warp_pipe_phys
r_int
r_int
id|warp_pipe_phys
(braket
id|MGA_MAX_WARP_PIPES
)braket
suffix:semicolon
DECL|member|chipset
r_int
id|chipset
suffix:semicolon
DECL|member|usec_timeout
r_int
id|usec_timeout
suffix:semicolon
DECL|member|clear_cmd
id|u32
id|clear_cmd
suffix:semicolon
DECL|member|maccess
id|u32
id|maccess
suffix:semicolon
DECL|member|fb_cpp
r_int
r_int
id|fb_cpp
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
DECL|member|depth_cpp
r_int
r_int
id|depth_cpp
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
DECL|member|texture_offset
r_int
r_int
id|texture_offset
suffix:semicolon
DECL|member|texture_size
r_int
r_int
id|texture_size
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
DECL|member|status
id|drm_map_t
op_star
id|status
suffix:semicolon
DECL|member|warp
id|drm_map_t
op_star
id|warp
suffix:semicolon
DECL|member|primary
id|drm_map_t
op_star
id|primary
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
DECL|typedef|drm_mga_private_t
)brace
id|drm_mga_private_t
suffix:semicolon
multiline_comment|/* mga_dma.c */
r_extern
r_int
id|mga_dma_init
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
id|mga_dma_flush
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
id|mga_dma_reset
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
id|mga_dma_buffers
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
id|mga_do_wait_for_idle
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
suffix:semicolon
r_extern
r_int
id|mga_do_dma_idle
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
suffix:semicolon
r_extern
r_int
id|mga_do_dma_reset
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
suffix:semicolon
r_extern
r_int
id|mga_do_engine_reset
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
suffix:semicolon
r_extern
r_int
id|mga_do_cleanup_dma
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|mga_do_dma_flush
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
suffix:semicolon
r_extern
r_void
id|mga_do_dma_wrap_start
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
suffix:semicolon
r_extern
r_void
id|mga_do_dma_wrap_end
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
suffix:semicolon
r_extern
r_int
id|mga_freelist_put
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|drm_buf_t
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/* mga_state.c */
r_extern
r_int
id|mga_dma_clear
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
id|mga_dma_swap
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
id|mga_dma_vertex
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
id|mga_dma_indices
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
id|mga_dma_iload
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
id|mga_dma_blit
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
multiline_comment|/* mga_warp.c */
r_extern
r_int
id|mga_warp_install_microcode
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
suffix:semicolon
r_extern
r_int
id|mga_warp_init
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
suffix:semicolon
DECL|macro|mga_flush_write_combine
mdefine_line|#define mga_flush_write_combine()&t;mb()
DECL|macro|MGA_BASE
mdefine_line|#define MGA_BASE( reg )&t;&t;((u32)(dev_priv-&gt;mmio-&gt;handle))
DECL|macro|MGA_ADDR
mdefine_line|#define MGA_ADDR( reg )&t;&t;(MGA_BASE(reg) + reg)
DECL|macro|MGA_DEREF
mdefine_line|#define MGA_DEREF( reg )&t;*(volatile u32 *)MGA_ADDR( reg )
DECL|macro|MGA_READ
mdefine_line|#define MGA_READ( reg )&t;&t;MGA_DEREF( reg )
DECL|macro|MGA_WRITE
mdefine_line|#define MGA_WRITE( reg, val )&t;do { MGA_DEREF( reg ) = val; } while (0)
DECL|macro|MGA_DEREF8
mdefine_line|#define MGA_DEREF8( reg )&t;*(volatile u8 *)MGA_ADDR( reg )
DECL|macro|MGA_WRITE8
mdefine_line|#define MGA_WRITE8( reg, val )  do { MGA_DEREF8( reg ) = val; } while (0)
DECL|macro|DWGREG0
mdefine_line|#define DWGREG0 &t;0x1c00
DECL|macro|DWGREG0_END
mdefine_line|#define DWGREG0_END &t;0x1dff
DECL|macro|DWGREG1
mdefine_line|#define DWGREG1&t;&t;0x2c00
DECL|macro|DWGREG1_END
mdefine_line|#define DWGREG1_END&t;0x2dff
DECL|macro|ISREG0
mdefine_line|#define ISREG0(r)&t;(r &gt;= DWGREG0 &amp;&amp; r &lt;= DWGREG0_END)
DECL|macro|DMAREG0
mdefine_line|#define DMAREG0(r)&t;(u8)((r - DWGREG0) &gt;&gt; 2)
DECL|macro|DMAREG1
mdefine_line|#define DMAREG1(r)&t;(u8)(((r - DWGREG1) &gt;&gt; 2) | 0x80)
DECL|macro|DMAREG
mdefine_line|#define DMAREG(r)&t;(ISREG0(r) ? DMAREG0(r) : DMAREG1(r))
multiline_comment|/* ================================================================&n; * Helper macross...&n; */
DECL|macro|MGA_EMIT_STATE
mdefine_line|#define MGA_EMIT_STATE( dev_priv, dirty )&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( (dirty) &amp; ~MGA_UPLOAD_CLIPRECTS ) {&t;&t;&t;&bslash;&n;&t;&t;if ( dev_priv-&gt;chipset == MGA_CARD_TYPE_G400 ) {&t;&bslash;&n;&t;&t;&t;mga_g400_emit_state( dev_priv );&t;&t;&bslash;&n;&t;&t;} else {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;mga_g200_emit_state( dev_priv );&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|LOCK_TEST_WITH_RETURN
mdefine_line|#define LOCK_TEST_WITH_RETURN( dev )&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( !_DRM_LOCK_IS_HELD( dev-&gt;lock.hw_lock-&gt;lock ) ||&t;&t;&bslash;&n;&t;     dev-&gt;lock.pid != current-&gt;pid ) {&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_ERROR( &quot;%s called without lock held&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&t;   __FUNCTION__ );&t;&t;&t;&t;&bslash;&n;&t;&t;return -EINVAL;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|WRAP_TEST_WITH_RETURN
mdefine_line|#define WRAP_TEST_WITH_RETURN( dev_priv )&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( test_bit( 0, &amp;dev_priv-&gt;prim.wrapped ) ) {&t;&t;&t;&bslash;&n;&t;&t;if ( mga_is_idle( dev_priv ) ) {&t;&t;&t;&bslash;&n;&t;&t;&t;mga_do_dma_wrap_end( dev_priv );&t;&t;&bslash;&n;&t;&t;} else if ( dev_priv-&gt;prim.space &lt;&t;&t;&t;&bslash;&n;&t;&t;&t;    dev_priv-&gt;prim.high_mark ) {&t;&t;&bslash;&n;&t;&t;&t;if ( MGA_DMA_DEBUG )&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;DRM_INFO( __FUNCTION__&quot;: wrap...&bslash;n&quot; );&t;&bslash;&n;&t;&t;&t;return -EBUSY;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|WRAP_WAIT_WITH_RETURN
mdefine_line|#define WRAP_WAIT_WITH_RETURN( dev_priv )&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( test_bit( 0, &amp;dev_priv-&gt;prim.wrapped ) ) {&t;&t;&t;&bslash;&n;&t;&t;if ( mga_do_wait_for_idle( dev_priv ) &lt; 0 ) {&t;&t;&bslash;&n;&t;&t;&t;if ( MGA_DMA_DEBUG )&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;DRM_INFO( __FUNCTION__&quot;: wrap...&bslash;n&quot; );&t;&bslash;&n;&t;&t;&t;return -EBUSY;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;mga_do_dma_wrap_end( dev_priv );&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* ================================================================&n; * Primary DMA command stream&n; */
DECL|macro|MGA_VERBOSE
mdefine_line|#define MGA_VERBOSE&t;0
DECL|macro|DMA_LOCALS
mdefine_line|#define DMA_LOCALS&t;unsigned int write; volatile u8 *prim;
DECL|macro|DMA_BLOCK_SIZE
mdefine_line|#define DMA_BLOCK_SIZE&t;(5 * sizeof(u32))
DECL|macro|BEGIN_DMA
mdefine_line|#define BEGIN_DMA( n )&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( MGA_VERBOSE ) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( &quot;BEGIN_DMA( %d ) in %s&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;&t;  (n), __FUNCTION__ );&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( &quot;   space=0x%x req=0x%x&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;&t;  dev_priv-&gt;prim.space, (n) * DMA_BLOCK_SIZE );&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;prim = dev_priv-&gt;prim.start;&t;&t;&t;&t;&t;&bslash;&n;&t;write = dev_priv-&gt;prim.tail;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|BEGIN_DMA_WRAP
mdefine_line|#define BEGIN_DMA_WRAP()&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( MGA_VERBOSE ) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( &quot;BEGIN_DMA() in %s&bslash;n&quot;, __FUNCTION__ );&t;&bslash;&n;&t;&t;DRM_INFO( &quot;   space=0x%x&bslash;n&quot;, dev_priv-&gt;prim.space );&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;prim = dev_priv-&gt;prim.start;&t;&t;&t;&t;&t;&bslash;&n;&t;write = dev_priv-&gt;prim.tail;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|ADVANCE_DMA
mdefine_line|#define ADVANCE_DMA()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;dev_priv-&gt;prim.tail = write;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( MGA_VERBOSE ) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( &quot;ADVANCE_DMA() tail=0x%05x sp=0x%x&bslash;n&quot;,&t;&bslash;&n;&t;&t;&t;  write, dev_priv-&gt;prim.space );&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|FLUSH_DMA
mdefine_line|#define FLUSH_DMA()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( 0 ) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( __FUNCTION__ &quot;:&bslash;n&quot; );&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( &quot;   tail=0x%06x head=0x%06lx&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&t;  dev_priv-&gt;prim.tail,&t;&t;&t;&t;&bslash;&n;&t;&t;&t;  MGA_READ( MGA_PRIMADDRESS ) -&t;&t;&t;&bslash;&n;&t;&t;&t;  dev_priv-&gt;primary-&gt;offset );&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( !test_bit( 0, &amp;dev_priv-&gt;prim.wrapped ) ) {&t;&t;&bslash;&n;&t;&t;if ( dev_priv-&gt;prim.space &lt;&t;&t;&t;&t;&bslash;&n;&t;&t;     dev_priv-&gt;prim.high_mark ) {&t;&t;&t;&bslash;&n;&t;&t;&t;mga_do_dma_wrap_start( dev_priv );&t;&t;&bslash;&n;&t;&t;} else {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;mga_do_dma_flush( dev_priv );&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Never use this, always use DMA_BLOCK(...) for primary DMA output.&n; */
DECL|macro|DMA_WRITE
mdefine_line|#define DMA_WRITE( offset, val )&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( MGA_VERBOSE ) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_INFO( &quot;   DMA_WRITE( 0x%08x ) at 0x%04x&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&t;  (u32)(val), write + (offset) * sizeof(u32) );&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(volatile u32 *)(prim + write + (offset) * sizeof(u32)) = val;&t;&bslash;&n;} while (0)
DECL|macro|DMA_BLOCK
mdefine_line|#define DMA_BLOCK( reg0, val0, reg1, val1, reg2, val2, reg3, val3 )&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DMA_WRITE( 0, ((DMAREG( reg0 ) &lt;&lt; 0) |&t;&t;&t;&t;&bslash;&n;&t;&t;       (DMAREG( reg1 ) &lt;&lt; 8) |&t;&t;&t;&t;&bslash;&n;&t;&t;       (DMAREG( reg2 ) &lt;&lt; 16) |&t;&t;&t;&t;&bslash;&n;&t;&t;       (DMAREG( reg3 ) &lt;&lt; 24)) );&t;&t;&t;&bslash;&n;&t;DMA_WRITE( 1, val0 );&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DMA_WRITE( 2, val1 );&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DMA_WRITE( 3, val2 );&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DMA_WRITE( 4, val3 );&t;&t;&t;&t;&t;&t;&bslash;&n;&t;write += DMA_BLOCK_SIZE;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Buffer aging via primary DMA stream head pointer.&n; */
DECL|macro|SET_AGE
mdefine_line|#define SET_AGE( age, h, w )&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(age)-&gt;head = h;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(age)-&gt;wrap = w;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|TEST_AGE
mdefine_line|#define TEST_AGE( age, h, w )&t;&t;( (age)-&gt;wrap &lt; w ||&t;&t;&bslash;&n;&t;&t;&t;&t;&t;  ( (age)-&gt;wrap == w &amp;&amp;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;    (age)-&gt;head &lt; h ) )
DECL|macro|AGE_BUFFER
mdefine_line|#define AGE_BUFFER( buf_priv )&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;drm_mga_freelist_t *entry = (buf_priv)-&gt;list_entry;&t;&t;&bslash;&n;&t;if ( (buf_priv)-&gt;dispatched ) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;entry-&gt;age.head = (dev_priv-&gt;prim.tail +&t;&t;&bslash;&n;&t;&t;&t;&t;   dev_priv-&gt;primary-&gt;offset);&t;&t;&bslash;&n;&t;&t;entry-&gt;age.wrap = dev_priv-&gt;sarea_priv-&gt;last_wrap;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;entry-&gt;age.head = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;entry-&gt;age.wrap = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|MGA_ENGINE_IDLE_MASK
mdefine_line|#define MGA_ENGINE_IDLE_MASK&t;&t;(MGA_SOFTRAPEN |&t;&t;&bslash;&n;&t;&t;&t;&t;&t; MGA_DWGENGSTS |&t;&t;&bslash;&n;&t;&t;&t;&t;&t; MGA_ENDPRDMASTS)
DECL|macro|MGA_DMA_IDLE_MASK
mdefine_line|#define MGA_DMA_IDLE_MASK&t;&t;(MGA_SOFTRAPEN |&t;&t;&bslash;&n;&t;&t;&t;&t;&t; MGA_ENDPRDMASTS)
DECL|macro|MGA_DMA_DEBUG
mdefine_line|#define MGA_DMA_DEBUG&t;&t;&t;0
multiline_comment|/* A reduced set of the mga registers.&n; */
DECL|macro|MGA_CRTC_INDEX
mdefine_line|#define MGA_CRTC_INDEX&t;&t;&t;0x1fd4
DECL|macro|MGA_ALPHACTRL
mdefine_line|#define MGA_ALPHACTRL &t;&t;&t;0x2c7c
DECL|macro|MGA_AR0
mdefine_line|#define MGA_AR0 &t;&t;&t;0x1c60
DECL|macro|MGA_AR1
mdefine_line|#define MGA_AR1 &t;&t;&t;0x1c64
DECL|macro|MGA_AR2
mdefine_line|#define MGA_AR2 &t;&t;&t;0x1c68
DECL|macro|MGA_AR3
mdefine_line|#define MGA_AR3 &t;&t;&t;0x1c6c
DECL|macro|MGA_AR4
mdefine_line|#define MGA_AR4 &t;&t;&t;0x1c70
DECL|macro|MGA_AR5
mdefine_line|#define MGA_AR5 &t;&t;&t;0x1c74
DECL|macro|MGA_AR6
mdefine_line|#define MGA_AR6 &t;&t;&t;0x1c78
DECL|macro|MGA_CXBNDRY
mdefine_line|#define MGA_CXBNDRY&t;&t;&t;0x1c80
DECL|macro|MGA_CXLEFT
mdefine_line|#define MGA_CXLEFT &t;&t;&t;0x1ca0
DECL|macro|MGA_CXRIGHT
mdefine_line|#define MGA_CXRIGHT&t;&t;&t;0x1ca4
DECL|macro|MGA_DMAPAD
mdefine_line|#define MGA_DMAPAD &t;&t;&t;0x1c54
DECL|macro|MGA_DSTORG
mdefine_line|#define MGA_DSTORG &t;&t;&t;0x2cb8
DECL|macro|MGA_DWGCTL
mdefine_line|#define MGA_DWGCTL &t;&t;&t;0x1c00
DECL|macro|MGA_OPCOD_MASK
macro_line|#&t;define MGA_OPCOD_MASK&t;&t;&t;(15 &lt;&lt; 0)
DECL|macro|MGA_OPCOD_TRAP
macro_line|#&t;define MGA_OPCOD_TRAP&t;&t;&t;(4 &lt;&lt; 0)
DECL|macro|MGA_OPCOD_TEXTURE_TRAP
macro_line|#&t;define MGA_OPCOD_TEXTURE_TRAP&t;&t;(6 &lt;&lt; 0)
DECL|macro|MGA_OPCOD_BITBLT
macro_line|#&t;define MGA_OPCOD_BITBLT&t;&t;&t;(8 &lt;&lt; 0)
DECL|macro|MGA_OPCOD_ILOAD
macro_line|#&t;define MGA_OPCOD_ILOAD&t;&t;&t;(9 &lt;&lt; 0)
DECL|macro|MGA_ATYPE_MASK
macro_line|#&t;define MGA_ATYPE_MASK&t;&t;&t;(7 &lt;&lt; 4)
DECL|macro|MGA_ATYPE_RPL
macro_line|#&t;define MGA_ATYPE_RPL&t;&t;&t;(0 &lt;&lt; 4)
DECL|macro|MGA_ATYPE_RSTR
macro_line|#&t;define MGA_ATYPE_RSTR&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|MGA_ATYPE_ZI
macro_line|#&t;define MGA_ATYPE_ZI&t;&t;&t;(3 &lt;&lt; 4)
DECL|macro|MGA_ATYPE_BLK
macro_line|#&t;define MGA_ATYPE_BLK&t;&t;&t;(4 &lt;&lt; 4)
DECL|macro|MGA_ATYPE_I
macro_line|#&t;define MGA_ATYPE_I&t;&t;&t;(7 &lt;&lt; 4)
DECL|macro|MGA_LINEAR
macro_line|#&t;define MGA_LINEAR&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|MGA_ZMODE_MASK
macro_line|#&t;define MGA_ZMODE_MASK&t;&t;&t;(7 &lt;&lt; 8)
DECL|macro|MGA_ZMODE_NOZCMP
macro_line|#&t;define MGA_ZMODE_NOZCMP&t;&t;&t;(0 &lt;&lt; 8)
DECL|macro|MGA_ZMODE_ZE
macro_line|#&t;define MGA_ZMODE_ZE&t;&t;&t;(2 &lt;&lt; 8)
DECL|macro|MGA_ZMODE_ZNE
macro_line|#&t;define MGA_ZMODE_ZNE&t;&t;&t;(3 &lt;&lt; 8)
DECL|macro|MGA_ZMODE_ZLT
macro_line|#&t;define MGA_ZMODE_ZLT&t;&t;&t;(4 &lt;&lt; 8)
DECL|macro|MGA_ZMODE_ZLTE
macro_line|#&t;define MGA_ZMODE_ZLTE&t;&t;&t;(5 &lt;&lt; 8)
DECL|macro|MGA_ZMODE_ZGT
macro_line|#&t;define MGA_ZMODE_ZGT&t;&t;&t;(6 &lt;&lt; 8)
DECL|macro|MGA_ZMODE_ZGTE
macro_line|#&t;define MGA_ZMODE_ZGTE&t;&t;&t;(7 &lt;&lt; 8)
DECL|macro|MGA_SOLID
macro_line|#&t;define MGA_SOLID&t;&t;&t;(1 &lt;&lt; 11)
DECL|macro|MGA_ARZERO
macro_line|#&t;define MGA_ARZERO&t;&t;&t;(1 &lt;&lt; 12)
DECL|macro|MGA_SGNZERO
macro_line|#&t;define MGA_SGNZERO&t;&t;&t;(1 &lt;&lt; 13)
DECL|macro|MGA_SHIFTZERO
macro_line|#&t;define MGA_SHIFTZERO&t;&t;&t;(1 &lt;&lt; 14)
DECL|macro|MGA_BOP_MASK
macro_line|#&t;define MGA_BOP_MASK&t;&t;&t;(15 &lt;&lt; 16)
DECL|macro|MGA_BOP_ZERO
macro_line|#&t;define MGA_BOP_ZERO&t;&t;&t;(0 &lt;&lt; 16)
DECL|macro|MGA_BOP_DST
macro_line|#&t;define MGA_BOP_DST&t;&t;&t;(10 &lt;&lt; 16)
DECL|macro|MGA_BOP_SRC
macro_line|#&t;define MGA_BOP_SRC&t;&t;&t;(12 &lt;&lt; 16)
DECL|macro|MGA_BOP_ONE
macro_line|#&t;define MGA_BOP_ONE&t;&t;&t;(15 &lt;&lt; 16)
DECL|macro|MGA_TRANS_SHIFT
macro_line|#&t;define MGA_TRANS_SHIFT&t;&t;&t;20
DECL|macro|MGA_TRANS_MASK
macro_line|#&t;define MGA_TRANS_MASK&t;&t;&t;(15 &lt;&lt; 20)
DECL|macro|MGA_BLTMOD_MASK
macro_line|#&t;define MGA_BLTMOD_MASK&t;&t;&t;(15 &lt;&lt; 25)
DECL|macro|MGA_BLTMOD_BMONOLEF
macro_line|#&t;define MGA_BLTMOD_BMONOLEF&t;&t;(0 &lt;&lt; 25)
DECL|macro|MGA_BLTMOD_BMONOWF
macro_line|#&t;define MGA_BLTMOD_BMONOWF&t;&t;(4 &lt;&lt; 25)
DECL|macro|MGA_BLTMOD_PLAN
macro_line|#&t;define MGA_BLTMOD_PLAN&t;&t;&t;(1 &lt;&lt; 25)
DECL|macro|MGA_BLTMOD_BFCOL
macro_line|#&t;define MGA_BLTMOD_BFCOL&t;&t;&t;(2 &lt;&lt; 25)
DECL|macro|MGA_BLTMOD_BU32BGR
macro_line|#&t;define MGA_BLTMOD_BU32BGR&t;&t;(3 &lt;&lt; 25)
DECL|macro|MGA_BLTMOD_BU32RGB
macro_line|#&t;define MGA_BLTMOD_BU32RGB&t;&t;(7 &lt;&lt; 25)
DECL|macro|MGA_BLTMOD_BU24BGR
macro_line|#&t;define MGA_BLTMOD_BU24BGR&t;&t;(11 &lt;&lt; 25)
DECL|macro|MGA_BLTMOD_BU24RGB
macro_line|#&t;define MGA_BLTMOD_BU24RGB&t;&t;(15 &lt;&lt; 25)
DECL|macro|MGA_PATTERN
macro_line|#&t;define MGA_PATTERN&t;&t;&t;(1 &lt;&lt; 29)
DECL|macro|MGA_TRANSC
macro_line|#&t;define MGA_TRANSC&t;&t;&t;(1 &lt;&lt; 30)
DECL|macro|MGA_CLIPDIS
macro_line|#&t;define MGA_CLIPDIS&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|MGA_DWGSYNC
mdefine_line|#define MGA_DWGSYNC&t;&t;&t;0x2c4c
DECL|macro|MGA_FCOL
mdefine_line|#define MGA_FCOL &t;&t;&t;0x1c24
DECL|macro|MGA_FIFOSTATUS
mdefine_line|#define MGA_FIFOSTATUS &t;&t;&t;0x1e10
DECL|macro|MGA_FOGCOL
mdefine_line|#define MGA_FOGCOL &t;&t;&t;0x1cf4
DECL|macro|MGA_FXBNDRY
mdefine_line|#define MGA_FXBNDRY&t;&t;&t;0x1c84
DECL|macro|MGA_FXLEFT
mdefine_line|#define MGA_FXLEFT &t;&t;&t;0x1ca8
DECL|macro|MGA_FXRIGHT
mdefine_line|#define MGA_FXRIGHT&t;&t;&t;0x1cac
DECL|macro|MGA_ICLEAR
mdefine_line|#define MGA_ICLEAR &t;&t;&t;0x1e18
DECL|macro|MGA_SOFTRAPICLR
macro_line|#&t;define MGA_SOFTRAPICLR&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_IEN
mdefine_line|#define MGA_IEN &t;&t;&t;0x1e1c
DECL|macro|MGA_SOFTRAPIEN
macro_line|#&t;define MGA_SOFTRAPIEN&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_LEN
mdefine_line|#define MGA_LEN &t;&t;&t;0x1c5c
DECL|macro|MGA_MACCESS
mdefine_line|#define MGA_MACCESS&t;&t;&t;0x1c04
DECL|macro|MGA_PITCH
mdefine_line|#define MGA_PITCH &t;&t;&t;0x1c8c
DECL|macro|MGA_PLNWT
mdefine_line|#define MGA_PLNWT &t;&t;&t;0x1c1c
DECL|macro|MGA_PRIMADDRESS
mdefine_line|#define MGA_PRIMADDRESS &t;&t;0x1e58
DECL|macro|MGA_DMA_GENERAL
macro_line|#&t;define MGA_DMA_GENERAL&t;&t;&t;(0 &lt;&lt; 0)
DECL|macro|MGA_DMA_BLIT
macro_line|#&t;define MGA_DMA_BLIT&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_DMA_VECTOR
macro_line|#&t;define MGA_DMA_VECTOR&t;&t;&t;(2 &lt;&lt; 0)
DECL|macro|MGA_DMA_VERTEX
macro_line|#&t;define MGA_DMA_VERTEX&t;&t;&t;(3 &lt;&lt; 0)
DECL|macro|MGA_PRIMEND
mdefine_line|#define MGA_PRIMEND&t;&t;&t;0x1e5c
DECL|macro|MGA_PRIMNOSTART
macro_line|#&t;define MGA_PRIMNOSTART&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_PAGPXFER
macro_line|#&t;define MGA_PAGPXFER&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|MGA_PRIMPTR
mdefine_line|#define MGA_PRIMPTR&t;&t;&t;0x1e50
DECL|macro|MGA_PRIMPTREN0
macro_line|#&t;define MGA_PRIMPTREN0&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_PRIMPTREN1
macro_line|#&t;define MGA_PRIMPTREN1&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|MGA_RST
mdefine_line|#define MGA_RST &t;&t;&t;0x1e40
DECL|macro|MGA_SOFTRESET
macro_line|#&t;define MGA_SOFTRESET&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_SOFTEXTRST
macro_line|#&t;define MGA_SOFTEXTRST&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|MGA_SECADDRESS
mdefine_line|#define MGA_SECADDRESS &t;&t;&t;0x2c40
DECL|macro|MGA_SECEND
mdefine_line|#define MGA_SECEND &t;&t;&t;0x2c44
DECL|macro|MGA_SETUPADDRESS
mdefine_line|#define MGA_SETUPADDRESS &t;&t;0x2cd0
DECL|macro|MGA_SETUPEND
mdefine_line|#define MGA_SETUPEND &t;&t;&t;0x2cd4
DECL|macro|MGA_SGN
mdefine_line|#define MGA_SGN&t;&t;&t;&t;0x1c58
DECL|macro|MGA_SOFTRAP
mdefine_line|#define MGA_SOFTRAP&t;&t;&t;0x2c48
DECL|macro|MGA_SRCORG
mdefine_line|#define MGA_SRCORG &t;&t;&t;0x2cb4
DECL|macro|MGA_SRMMAP_MASK
macro_line|#&t;define MGA_SRMMAP_MASK&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_SRCMAP_FB
macro_line|#&t;define MGA_SRCMAP_FB&t;&t;&t;(0 &lt;&lt; 0)
DECL|macro|MGA_SRCMAP_SYSMEM
macro_line|#&t;define MGA_SRCMAP_SYSMEM&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_SRCACC_MASK
macro_line|#&t;define MGA_SRCACC_MASK&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|MGA_SRCACC_PCI
macro_line|#&t;define MGA_SRCACC_PCI&t;&t;&t;(0 &lt;&lt; 1)
DECL|macro|MGA_SRCACC_AGP
macro_line|#&t;define MGA_SRCACC_AGP&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|MGA_STATUS
mdefine_line|#define MGA_STATUS &t;&t;&t;0x1e14
DECL|macro|MGA_SOFTRAPEN
macro_line|#&t;define MGA_SOFTRAPEN&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_DWGENGSTS
macro_line|#&t;define MGA_DWGENGSTS&t;&t;&t;(1 &lt;&lt; 16)
DECL|macro|MGA_ENDPRDMASTS
macro_line|#&t;define MGA_ENDPRDMASTS&t;&t;&t;(1 &lt;&lt; 17)
DECL|macro|MGA_STENCIL
mdefine_line|#define MGA_STENCIL&t;&t;&t;0x2cc8
DECL|macro|MGA_STENCILCTL
mdefine_line|#define MGA_STENCILCTL &t;&t;&t;0x2ccc
DECL|macro|MGA_TDUALSTAGE0
mdefine_line|#define MGA_TDUALSTAGE0 &t;&t;0x2cf8
DECL|macro|MGA_TDUALSTAGE1
mdefine_line|#define MGA_TDUALSTAGE1 &t;&t;0x2cfc
DECL|macro|MGA_TEXBORDERCOL
mdefine_line|#define MGA_TEXBORDERCOL &t;&t;0x2c5c
DECL|macro|MGA_TEXCTL
mdefine_line|#define MGA_TEXCTL &t;&t;&t;0x2c30
DECL|macro|MGA_TEXCTL2
mdefine_line|#define MGA_TEXCTL2&t;&t;&t;0x2c3c
DECL|macro|MGA_DUALTEX
macro_line|#&t;define MGA_DUALTEX&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|MGA_G400_TC2_MAGIC
macro_line|#&t;define MGA_G400_TC2_MAGIC&t;&t;(1 &lt;&lt; 15)
DECL|macro|MGA_MAP1_ENABLE
macro_line|#&t;define MGA_MAP1_ENABLE&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|MGA_TEXFILTER
mdefine_line|#define MGA_TEXFILTER &t;&t;&t;0x2c58
DECL|macro|MGA_TEXHEIGHT
mdefine_line|#define MGA_TEXHEIGHT &t;&t;&t;0x2c2c
DECL|macro|MGA_TEXORG
mdefine_line|#define MGA_TEXORG &t;&t;&t;0x2c24
DECL|macro|MGA_TEXORGMAP_MASK
macro_line|#&t;define MGA_TEXORGMAP_MASK&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_TEXORGMAP_FB
macro_line|#&t;define MGA_TEXORGMAP_FB&t;&t;&t;(0 &lt;&lt; 0)
DECL|macro|MGA_TEXORGMAP_SYSMEM
macro_line|#&t;define MGA_TEXORGMAP_SYSMEM&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_TEXORGACC_MASK
macro_line|#&t;define MGA_TEXORGACC_MASK&t;&t;(1 &lt;&lt; 1)
DECL|macro|MGA_TEXORGACC_PCI
macro_line|#&t;define MGA_TEXORGACC_PCI&t;&t;(0 &lt;&lt; 1)
DECL|macro|MGA_TEXORGACC_AGP
macro_line|#&t;define MGA_TEXORGACC_AGP&t;&t;(1 &lt;&lt; 1)
DECL|macro|MGA_TEXORG1
mdefine_line|#define MGA_TEXORG1&t;&t;&t;0x2ca4
DECL|macro|MGA_TEXORG2
mdefine_line|#define MGA_TEXORG2&t;&t;&t;0x2ca8
DECL|macro|MGA_TEXORG3
mdefine_line|#define MGA_TEXORG3&t;&t;&t;0x2cac
DECL|macro|MGA_TEXORG4
mdefine_line|#define MGA_TEXORG4&t;&t;&t;0x2cb0
DECL|macro|MGA_TEXTRANS
mdefine_line|#define MGA_TEXTRANS &t;&t;&t;0x2c34
DECL|macro|MGA_TEXTRANSHIGH
mdefine_line|#define MGA_TEXTRANSHIGH &t;&t;0x2c38
DECL|macro|MGA_TEXWIDTH
mdefine_line|#define MGA_TEXWIDTH &t;&t;&t;0x2c28
DECL|macro|MGA_WACCEPTSEQ
mdefine_line|#define MGA_WACCEPTSEQ &t;&t;&t;0x1dd4
DECL|macro|MGA_WCODEADDR
mdefine_line|#define MGA_WCODEADDR &t;&t;&t;0x1e6c
DECL|macro|MGA_WFLAG
mdefine_line|#define MGA_WFLAG &t;&t;&t;0x1dc4
DECL|macro|MGA_WFLAG1
mdefine_line|#define MGA_WFLAG1 &t;&t;&t;0x1de0
DECL|macro|MGA_WFLAGNB
mdefine_line|#define MGA_WFLAGNB&t;&t;&t;0x1e64
DECL|macro|MGA_WFLAGNB1
mdefine_line|#define MGA_WFLAGNB1 &t;&t;&t;0x1e08
DECL|macro|MGA_WGETMSB
mdefine_line|#define MGA_WGETMSB&t;&t;&t;0x1dc8
DECL|macro|MGA_WIADDR
mdefine_line|#define MGA_WIADDR &t;&t;&t;0x1dc0
DECL|macro|MGA_WIADDR2
mdefine_line|#define MGA_WIADDR2&t;&t;&t;0x1dd8
DECL|macro|MGA_WMODE_SUSPEND
macro_line|#&t;define MGA_WMODE_SUSPEND&t;&t;(0 &lt;&lt; 0)
DECL|macro|MGA_WMODE_RESUME
macro_line|#&t;define MGA_WMODE_RESUME&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_WMODE_JUMP
macro_line|#&t;define MGA_WMODE_JUMP&t;&t;&t;(2 &lt;&lt; 0)
DECL|macro|MGA_WMODE_START
macro_line|#&t;define MGA_WMODE_START&t;&t;&t;(3 &lt;&lt; 0)
DECL|macro|MGA_WAGP_ENABLE
macro_line|#&t;define MGA_WAGP_ENABLE&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|MGA_WMISC
mdefine_line|#define MGA_WMISC &t;&t;&t;0x1e70
DECL|macro|MGA_WUCODECACHE_ENABLE
macro_line|#&t;define MGA_WUCODECACHE_ENABLE&t;&t;(1 &lt;&lt; 0)
DECL|macro|MGA_WMASTER_ENABLE
macro_line|#&t;define MGA_WMASTER_ENABLE&t;&t;(1 &lt;&lt; 1)
DECL|macro|MGA_WCACHEFLUSH_ENABLE
macro_line|#&t;define MGA_WCACHEFLUSH_ENABLE&t;&t;(1 &lt;&lt; 3)
DECL|macro|MGA_WVRTXSZ
mdefine_line|#define MGA_WVRTXSZ&t;&t;&t;0x1dcc
DECL|macro|MGA_YBOT
mdefine_line|#define MGA_YBOT &t;&t;&t;0x1c9c
DECL|macro|MGA_YDST
mdefine_line|#define MGA_YDST &t;&t;&t;0x1c90
DECL|macro|MGA_YDSTLEN
mdefine_line|#define MGA_YDSTLEN&t;&t;&t;0x1c88
DECL|macro|MGA_YDSTORG
mdefine_line|#define MGA_YDSTORG&t;&t;&t;0x1c94
DECL|macro|MGA_YTOP
mdefine_line|#define MGA_YTOP &t;&t;&t;0x1c98
DECL|macro|MGA_ZORG
mdefine_line|#define MGA_ZORG &t;&t;&t;0x1c0c
multiline_comment|/* This finishes the current batch of commands&n; */
DECL|macro|MGA_EXEC
mdefine_line|#define MGA_EXEC &t;&t;&t;0x0100
multiline_comment|/* Warp registers&n; */
DECL|macro|MGA_WR0
mdefine_line|#define MGA_WR0&t;&t;&t;&t;0x2d00
DECL|macro|MGA_WR1
mdefine_line|#define MGA_WR1&t;&t;&t;&t;0x2d04
DECL|macro|MGA_WR2
mdefine_line|#define MGA_WR2&t;&t;&t;&t;0x2d08
DECL|macro|MGA_WR3
mdefine_line|#define MGA_WR3&t;&t;&t;&t;0x2d0c
DECL|macro|MGA_WR4
mdefine_line|#define MGA_WR4&t;&t;&t;&t;0x2d10
DECL|macro|MGA_WR5
mdefine_line|#define MGA_WR5&t;&t;&t;&t;0x2d14
DECL|macro|MGA_WR6
mdefine_line|#define MGA_WR6&t;&t;&t;&t;0x2d18
DECL|macro|MGA_WR7
mdefine_line|#define MGA_WR7&t;&t;&t;&t;0x2d1c
DECL|macro|MGA_WR8
mdefine_line|#define MGA_WR8&t;&t;&t;&t;0x2d20
DECL|macro|MGA_WR9
mdefine_line|#define MGA_WR9&t;&t;&t;&t;0x2d24
DECL|macro|MGA_WR10
mdefine_line|#define MGA_WR10&t;&t;&t;0x2d28
DECL|macro|MGA_WR11
mdefine_line|#define MGA_WR11&t;&t;&t;0x2d2c
DECL|macro|MGA_WR12
mdefine_line|#define MGA_WR12&t;&t;&t;0x2d30
DECL|macro|MGA_WR13
mdefine_line|#define MGA_WR13&t;&t;&t;0x2d34
DECL|macro|MGA_WR14
mdefine_line|#define MGA_WR14&t;&t;&t;0x2d38
DECL|macro|MGA_WR15
mdefine_line|#define MGA_WR15&t;&t;&t;0x2d3c
DECL|macro|MGA_WR16
mdefine_line|#define MGA_WR16&t;&t;&t;0x2d40
DECL|macro|MGA_WR17
mdefine_line|#define MGA_WR17&t;&t;&t;0x2d44
DECL|macro|MGA_WR18
mdefine_line|#define MGA_WR18&t;&t;&t;0x2d48
DECL|macro|MGA_WR19
mdefine_line|#define MGA_WR19&t;&t;&t;0x2d4c
DECL|macro|MGA_WR20
mdefine_line|#define MGA_WR20&t;&t;&t;0x2d50
DECL|macro|MGA_WR21
mdefine_line|#define MGA_WR21&t;&t;&t;0x2d54
DECL|macro|MGA_WR22
mdefine_line|#define MGA_WR22&t;&t;&t;0x2d58
DECL|macro|MGA_WR23
mdefine_line|#define MGA_WR23&t;&t;&t;0x2d5c
DECL|macro|MGA_WR24
mdefine_line|#define MGA_WR24&t;&t;&t;0x2d60
DECL|macro|MGA_WR25
mdefine_line|#define MGA_WR25&t;&t;&t;0x2d64
DECL|macro|MGA_WR26
mdefine_line|#define MGA_WR26&t;&t;&t;0x2d68
DECL|macro|MGA_WR27
mdefine_line|#define MGA_WR27&t;&t;&t;0x2d6c
DECL|macro|MGA_WR28
mdefine_line|#define MGA_WR28&t;&t;&t;0x2d70
DECL|macro|MGA_WR29
mdefine_line|#define MGA_WR29&t;&t;&t;0x2d74
DECL|macro|MGA_WR30
mdefine_line|#define MGA_WR30&t;&t;&t;0x2d78
DECL|macro|MGA_WR31
mdefine_line|#define MGA_WR31&t;&t;&t;0x2d7c
DECL|macro|MGA_WR32
mdefine_line|#define MGA_WR32&t;&t;&t;0x2d80
DECL|macro|MGA_WR33
mdefine_line|#define MGA_WR33&t;&t;&t;0x2d84
DECL|macro|MGA_WR34
mdefine_line|#define MGA_WR34&t;&t;&t;0x2d88
DECL|macro|MGA_WR35
mdefine_line|#define MGA_WR35&t;&t;&t;0x2d8c
DECL|macro|MGA_WR36
mdefine_line|#define MGA_WR36&t;&t;&t;0x2d90
DECL|macro|MGA_WR37
mdefine_line|#define MGA_WR37&t;&t;&t;0x2d94
DECL|macro|MGA_WR38
mdefine_line|#define MGA_WR38&t;&t;&t;0x2d98
DECL|macro|MGA_WR39
mdefine_line|#define MGA_WR39&t;&t;&t;0x2d9c
DECL|macro|MGA_WR40
mdefine_line|#define MGA_WR40&t;&t;&t;0x2da0
DECL|macro|MGA_WR41
mdefine_line|#define MGA_WR41&t;&t;&t;0x2da4
DECL|macro|MGA_WR42
mdefine_line|#define MGA_WR42&t;&t;&t;0x2da8
DECL|macro|MGA_WR43
mdefine_line|#define MGA_WR43&t;&t;&t;0x2dac
DECL|macro|MGA_WR44
mdefine_line|#define MGA_WR44&t;&t;&t;0x2db0
DECL|macro|MGA_WR45
mdefine_line|#define MGA_WR45&t;&t;&t;0x2db4
DECL|macro|MGA_WR46
mdefine_line|#define MGA_WR46&t;&t;&t;0x2db8
DECL|macro|MGA_WR47
mdefine_line|#define MGA_WR47&t;&t;&t;0x2dbc
DECL|macro|MGA_WR48
mdefine_line|#define MGA_WR48&t;&t;&t;0x2dc0
DECL|macro|MGA_WR49
mdefine_line|#define MGA_WR49&t;&t;&t;0x2dc4
DECL|macro|MGA_WR50
mdefine_line|#define MGA_WR50&t;&t;&t;0x2dc8
DECL|macro|MGA_WR51
mdefine_line|#define MGA_WR51&t;&t;&t;0x2dcc
DECL|macro|MGA_WR52
mdefine_line|#define MGA_WR52&t;&t;&t;0x2dd0
DECL|macro|MGA_WR53
mdefine_line|#define MGA_WR53&t;&t;&t;0x2dd4
DECL|macro|MGA_WR54
mdefine_line|#define MGA_WR54&t;&t;&t;0x2dd8
DECL|macro|MGA_WR55
mdefine_line|#define MGA_WR55&t;&t;&t;0x2ddc
DECL|macro|MGA_WR56
mdefine_line|#define MGA_WR56&t;&t;&t;0x2de0
DECL|macro|MGA_WR57
mdefine_line|#define MGA_WR57&t;&t;&t;0x2de4
DECL|macro|MGA_WR58
mdefine_line|#define MGA_WR58&t;&t;&t;0x2de8
DECL|macro|MGA_WR59
mdefine_line|#define MGA_WR59&t;&t;&t;0x2dec
DECL|macro|MGA_WR60
mdefine_line|#define MGA_WR60&t;&t;&t;0x2df0
DECL|macro|MGA_WR61
mdefine_line|#define MGA_WR61&t;&t;&t;0x2df4
DECL|macro|MGA_WR62
mdefine_line|#define MGA_WR62&t;&t;&t;0x2df8
DECL|macro|MGA_WR63
mdefine_line|#define MGA_WR63&t;&t;&t;0x2dfc
DECL|macro|MGA_G400_WR_MAGIC
macro_line|#&t;define MGA_G400_WR_MAGIC&t;&t;(1 &lt;&lt; 6)
DECL|macro|MGA_G400_WR56_MAGIC
macro_line|#&t;define MGA_G400_WR56_MAGIC&t;&t;0x46480000&t;/* 12800.0f */
DECL|macro|MGA_ILOAD_ALIGN
mdefine_line|#define MGA_ILOAD_ALIGN&t;&t;64
DECL|macro|MGA_ILOAD_MASK
mdefine_line|#define MGA_ILOAD_MASK&t;&t;(MGA_ILOAD_ALIGN - 1)
DECL|macro|MGA_DWGCTL_FLUSH
mdefine_line|#define MGA_DWGCTL_FLUSH&t;(MGA_OPCOD_TEXTURE_TRAP |&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_ATYPE_I |&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_ZMODE_NOZCMP |&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_ARZERO |&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_SGNZERO |&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_BOP_SRC |&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; (15 &lt;&lt; MGA_TRANS_SHIFT))
DECL|macro|MGA_DWGCTL_CLEAR
mdefine_line|#define MGA_DWGCTL_CLEAR&t;(MGA_OPCOD_TRAP |&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_ZMODE_NOZCMP |&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_SOLID |&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_ARZERO |&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_SGNZERO |&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_SHIFTZERO |&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_BOP_SRC |&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; (0 &lt;&lt; MGA_TRANS_SHIFT) |&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_BLTMOD_BMONOLEF |&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_TRANSC |&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_CLIPDIS)
DECL|macro|MGA_DWGCTL_COPY
mdefine_line|#define MGA_DWGCTL_COPY&t;&t;(MGA_OPCOD_BITBLT |&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_ATYPE_RPL |&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_SGNZERO |&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_SHIFTZERO |&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_BOP_SRC |&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; (0 &lt;&lt; MGA_TRANS_SHIFT) |&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_BLTMOD_BFCOL |&t;&t;&t;&bslash;&n;&t;&t;&t;&t; MGA_CLIPDIS)
multiline_comment|/* Simple idle test.&n; */
DECL|function|mga_is_idle
r_static
r_inline
r_int
id|mga_is_idle
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
(brace
id|u32
id|status
op_assign
id|MGA_READ
c_func
(paren
id|MGA_STATUS
)paren
op_amp
id|MGA_ENGINE_IDLE_MASK
suffix:semicolon
r_return
(paren
id|status
op_eq
id|MGA_ENDPRDMASTS
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
