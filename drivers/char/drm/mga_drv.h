multiline_comment|/* mga_drv.h -- Private header for the Matrox g200/g400 driver -*- linux-c -*-&n; * Created: Mon Dec 13 01:50:01 1999 by jhartmann@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors: Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &t;    Jeff Hartmann &lt;jhartmann@valinux.com&gt;&n; *&n; */
macro_line|#ifndef _MGA_DRV_H_
DECL|macro|_MGA_DRV_H_
mdefine_line|#define _MGA_DRV_H_
DECL|macro|MGA_BUF_IN_USE
mdefine_line|#define MGA_BUF_IN_USE         0
DECL|macro|MGA_BUF_SWAP_PENDING
mdefine_line|#define MGA_BUF_SWAP_PENDING   1
DECL|macro|MGA_BUF_FORCE_FIRE
mdefine_line|#define MGA_BUF_FORCE_FIRE     2
DECL|macro|MGA_BUF_NEEDS_OVERFLOW
mdefine_line|#define MGA_BUF_NEEDS_OVERFLOW 3
r_typedef
r_struct
(brace
DECL|member|buffer_status
r_int
id|buffer_status
suffix:semicolon
multiline_comment|/* long req&squot;d for set_bit() --RR */
DECL|member|num_dwords
r_int
id|num_dwords
suffix:semicolon
DECL|member|max_dwords
r_int
id|max_dwords
suffix:semicolon
DECL|member|current_dma_ptr
id|u32
op_star
id|current_dma_ptr
suffix:semicolon
DECL|member|head
id|u32
op_star
id|head
suffix:semicolon
DECL|member|phys_head
id|u32
id|phys_head
suffix:semicolon
DECL|member|prim_age
r_int
r_int
id|prim_age
suffix:semicolon
DECL|member|sec_used
r_int
id|sec_used
suffix:semicolon
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|typedef|drm_mga_prim_buf_t
)brace
id|drm_mga_prim_buf_t
suffix:semicolon
DECL|struct|_drm_mga_freelist
r_typedef
r_struct
id|_drm_mga_freelist
(brace
DECL|member|age
id|__volatile__
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
id|_drm_mga_freelist
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|_drm_mga_freelist
op_star
id|prev
suffix:semicolon
DECL|typedef|drm_mga_freelist_t
)brace
id|drm_mga_freelist_t
suffix:semicolon
DECL|macro|MGA_IN_DISPATCH
mdefine_line|#define MGA_IN_DISPATCH   0
DECL|macro|MGA_IN_FLUSH
mdefine_line|#define MGA_IN_FLUSH      1
DECL|macro|MGA_IN_WAIT
mdefine_line|#define MGA_IN_WAIT       2
DECL|macro|MGA_IN_GETBUF
mdefine_line|#define MGA_IN_GETBUF&t;  3
DECL|struct|_drm_mga_private
r_typedef
r_struct
id|_drm_mga_private
(brace
DECL|member|dispatch_status
r_int
id|dispatch_status
suffix:semicolon
multiline_comment|/* long req&squot;d for set_bit() --RR */
DECL|member|next_prim_age
r_int
r_int
id|next_prim_age
suffix:semicolon
DECL|member|last_prim_age
id|__volatile__
r_int
r_int
id|last_prim_age
suffix:semicolon
DECL|member|reserved_map_idx
r_int
id|reserved_map_idx
suffix:semicolon
DECL|member|buffer_map_idx
r_int
id|buffer_map_idx
suffix:semicolon
DECL|member|sarea_priv
id|drm_mga_sarea_t
op_star
id|sarea_priv
suffix:semicolon
DECL|member|primary_size
r_int
id|primary_size
suffix:semicolon
DECL|member|warp_ucode_size
r_int
id|warp_ucode_size
suffix:semicolon
DECL|member|chipset
r_int
id|chipset
suffix:semicolon
DECL|member|frontOffset
r_int
r_int
id|frontOffset
suffix:semicolon
DECL|member|backOffset
r_int
r_int
id|backOffset
suffix:semicolon
DECL|member|depthOffset
r_int
r_int
id|depthOffset
suffix:semicolon
DECL|member|textureOffset
r_int
r_int
id|textureOffset
suffix:semicolon
DECL|member|textureSize
r_int
r_int
id|textureSize
suffix:semicolon
DECL|member|cpp
r_int
id|cpp
suffix:semicolon
DECL|member|stride
r_int
r_int
id|stride
suffix:semicolon
DECL|member|sgram
r_int
id|sgram
suffix:semicolon
DECL|member|use_agp
r_int
id|use_agp
suffix:semicolon
DECL|member|WarpIndex
id|drm_mga_warp_index_t
id|WarpIndex
(braket
id|MGA_MAX_G400_PIPES
)braket
suffix:semicolon
DECL|member|WarpPipe
r_int
r_int
id|WarpPipe
suffix:semicolon
DECL|member|vertexsize
r_int
r_int
id|vertexsize
suffix:semicolon
DECL|member|pending_bufs
id|atomic_t
id|pending_bufs
suffix:semicolon
DECL|member|status_page
r_void
op_star
id|status_page
suffix:semicolon
DECL|member|real_status_page
r_int
r_int
id|real_status_page
suffix:semicolon
DECL|member|ioremap
id|u8
op_star
id|ioremap
suffix:semicolon
DECL|member|prim_bufs
id|drm_mga_prim_buf_t
op_star
op_star
id|prim_bufs
suffix:semicolon
DECL|member|next_prim
id|drm_mga_prim_buf_t
op_star
id|next_prim
suffix:semicolon
DECL|member|last_prim
id|drm_mga_prim_buf_t
op_star
id|last_prim
suffix:semicolon
DECL|member|current_prim
id|drm_mga_prim_buf_t
op_star
id|current_prim
suffix:semicolon
DECL|member|current_prim_idx
r_int
id|current_prim_idx
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
DECL|member|flush_queue
id|wait_queue_head_t
id|flush_queue
suffix:semicolon
multiline_comment|/* Processes waiting until flush    */
DECL|member|wait_queue
id|wait_queue_head_t
id|wait_queue
suffix:semicolon
multiline_comment|/* Processes waiting until interrupt */
DECL|member|buf_queue
id|wait_queue_head_t
id|buf_queue
suffix:semicolon
multiline_comment|/* Processes waiting for a free buf */
multiline_comment|/* Some validated register values:&n;&t; */
DECL|member|mAccess
id|u32
id|mAccess
suffix:semicolon
DECL|typedef|drm_mga_private_t
)brace
id|drm_mga_private_t
suffix:semicolon
multiline_comment|/* mga_drv.c */
r_extern
r_int
id|mga_version
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
id|mga_open
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
)paren
suffix:semicolon
r_extern
r_int
id|mga_release
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
)paren
suffix:semicolon
r_extern
r_int
id|mga_ioctl
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
id|mga_unlock
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
multiline_comment|/* mga_dma.c */
r_extern
r_int
id|mga_dma_schedule
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|locked
)paren
suffix:semicolon
r_extern
r_int
id|mga_dma
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
id|mga_irq_install
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
id|mga_irq_uninstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|mga_control
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
id|mga_lock
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
multiline_comment|/* mga_dma_init does init and release */
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
id|mga_dma_cleanup
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|mga_flush_ioctl
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
r_int
id|mga_create_sync_tag
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
id|mga_freelist_get
c_func
(paren
id|drm_device_t
op_star
id|dev
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
r_extern
r_int
id|mga_advance_primary
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|mga_reclaim_buffers
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|pid_t
id|pid
)paren
suffix:semicolon
multiline_comment|/* mga_bufs.c */
r_extern
r_int
id|mga_addbufs
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
id|mga_infobufs
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
id|mga_markbufs
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
id|mga_freebufs
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
id|mga_mapbufs
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
id|mga_addmap
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
multiline_comment|/* mga_state.c */
r_extern
r_int
id|mga_clear_bufs
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
id|mga_swap_bufs
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
id|mga_iload
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
id|mga_vertex
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
id|mga_indices
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
multiline_comment|/* mga_context.c */
r_extern
r_int
id|mga_resctx
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
id|mga_addctx
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
id|mga_modctx
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
id|mga_getctx
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
id|mga_switchctx
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
id|mga_newctx
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
id|mga_rmctx
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
id|mga_context_switch
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|old
comma
r_int
r_new
)paren
suffix:semicolon
r_extern
r_int
id|mga_context_switch_complete
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
r_new
)paren
suffix:semicolon
DECL|macro|mga_flush_write_combine
mdefine_line|#define mga_flush_write_combine()&t;mb()
r_typedef
r_enum
(brace
DECL|enumerator|TT_GENERAL
id|TT_GENERAL
comma
DECL|enumerator|TT_BLIT
id|TT_BLIT
comma
DECL|enumerator|TT_VECTOR
id|TT_VECTOR
comma
DECL|enumerator|TT_VERTEX
id|TT_VERTEX
DECL|typedef|transferType_t
)brace
id|transferType_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|my_freelist
id|drm_mga_freelist_t
op_star
id|my_freelist
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
DECL|macro|ADRINDEX0
mdefine_line|#define ADRINDEX0(r)&t;(u8)((r - DWGREG0) &gt;&gt; 2)
DECL|macro|ADRINDEX1
mdefine_line|#define ADRINDEX1(r)&t;(u8)(((r - DWGREG1) &gt;&gt; 2) | 0x80)
DECL|macro|ADRINDEX
mdefine_line|#define ADRINDEX(r)&t;(ISREG0(r) ? ADRINDEX0(r) : ADRINDEX1(r))
DECL|macro|MGA_VERBOSE
mdefine_line|#define MGA_VERBOSE 0
DECL|macro|MGA_NUM_PRIM_BUFS
mdefine_line|#define MGA_NUM_PRIM_BUFS &t;8
DECL|macro|PRIMLOCALS
mdefine_line|#define PRIMLOCALS&t;u8 tempIndex[4]; u32 *dma_ptr; u32 phys_head; &bslash;&n;&t;&t;&t;int outcount, num_dwords
DECL|macro|PRIM_OVERFLOW
mdefine_line|#define PRIM_OVERFLOW(dev, dev_priv, length) do {&t;&t;&t;   &bslash;&n;&t;drm_mga_prim_buf_t *tmp_buf =&t;&t;&t;&t;&t;   &bslash;&n; &t;&t;dev_priv-&gt;prim_bufs[dev_priv-&gt;current_prim_idx];&t;   &bslash;&n;&t;if( test_bit(MGA_BUF_NEEDS_OVERFLOW, &amp;tmp_buf-&gt;buffer_status)) {   &bslash;&n; &t;&t;mga_advance_primary(dev);&t;&t;&t;&t;   &bslash;&n; &t;&t;mga_dma_schedule(dev, 1);&t;&t;&t;&t;   &bslash;&n;&t;&t;tmp_buf = dev_priv-&gt;prim_bufs[dev_priv-&gt;current_prim_idx]; &bslash;&n; &t;} else if( tmp_buf-&gt;max_dwords - tmp_buf-&gt;num_dwords &lt; length ||   &bslash;&n; &t;           tmp_buf-&gt;sec_used &gt; MGA_DMA_BUF_NR/2) {&t;&t;   &bslash;&n;&t;&t;set_bit(MGA_BUF_FORCE_FIRE, &amp;tmp_buf-&gt;buffer_status);&t;   &bslash;&n; &t;&t;mga_advance_primary(dev);&t;&t;&t;&t;   &bslash;&n; &t;&t;mga_dma_schedule(dev, 1);&t;&t;&t;&t;   &bslash;&n;&t;&t;tmp_buf = dev_priv-&gt;prim_bufs[dev_priv-&gt;current_prim_idx]; &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;if(MGA_VERBOSE)&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;DRM_DEBUG(&quot;PRIMGETPTR in %s&bslash;n&quot;, __FUNCTION__);&t;&t;   &bslash;&n;&t;dma_ptr = tmp_buf-&gt;current_dma_ptr;&t;&t;&t;&t;   &bslash;&n;&t;num_dwords = tmp_buf-&gt;num_dwords;&t;&t;&t;&t;   &bslash;&n;&t;phys_head = tmp_buf-&gt;phys_head;&t;&t;&t;&t;&t;   &bslash;&n;&t;outcount = 0;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;} while(0)
DECL|macro|PRIMGETPTR
mdefine_line|#define PRIMGETPTR(dev_priv) do {&t;&t;&t;&t;&t;&bslash;&n;&t;drm_mga_prim_buf_t *tmp_buf =&t;&t;&t;&t;&t;&bslash;&n;&t;&t;dev_priv-&gt;prim_bufs[dev_priv-&gt;current_prim_idx];&t;&bslash;&n;&t;if(MGA_VERBOSE)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_DEBUG(&quot;PRIMGETPTR in %s&bslash;n&quot;, __FUNCTION__);&t;&t;&bslash;&n;&t;dma_ptr = tmp_buf-&gt;current_dma_ptr;&t;&t;&t;&t;&bslash;&n;&t;num_dwords = tmp_buf-&gt;num_dwords;&t;&t;&t;&t;&bslash;&n;&t;phys_head = tmp_buf-&gt;phys_head;&t;&t;&t;&t;&t;&bslash;&n;&t;outcount = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|PRIMPTR
mdefine_line|#define PRIMPTR(prim_buf) do {&t;&t;&t;&t;&t;&bslash;&n;&t;if(MGA_VERBOSE)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_DEBUG(&quot;PRIMPTR in %s&bslash;n&quot;, __FUNCTION__);&t;&bslash;&n;&t;dma_ptr = prim_buf-&gt;current_dma_ptr;&t;&t;&t;&bslash;&n;&t;num_dwords = prim_buf-&gt;num_dwords;&t;&t;&t;&bslash;&n;&t;phys_head = prim_buf-&gt;phys_head;&t;&t;&t;&bslash;&n;&t;outcount = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|PRIMFINISH
mdefine_line|#define PRIMFINISH(prim_buf) do {&t;&t;&t;&t;&bslash;&n;&t;if (MGA_VERBOSE) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_DEBUG( &quot;PRIMFINISH in %s&bslash;n&quot;, __FUNCTION__);&t;&bslash;&n;                if (outcount &amp; 3)&t;&t;&t;&t;&bslash;&n;                      DRM_DEBUG(&quot; --- truncation&bslash;n&quot;);&t;        &bslash;&n;        }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;prim_buf-&gt;num_dwords = num_dwords;&t;&t;&t;&bslash;&n;&t;prim_buf-&gt;current_dma_ptr = dma_ptr;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|PRIMADVANCE
mdefine_line|#define PRIMADVANCE(dev_priv)&t;do {&t;&t;&t;&t;&bslash;&n;drm_mga_prim_buf_t *tmp_buf = &t;&t;&t;&t;&t;&bslash;&n;&t;dev_priv-&gt;prim_bufs[dev_priv-&gt;current_prim_idx];&t;&bslash;&n;&t;if (MGA_VERBOSE) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_DEBUG(&quot;PRIMADVANCE in %s&bslash;n&quot;, __FUNCTION__);&t;&bslash;&n;                if (outcount &amp; 3)&t;&t;&t;&t;&bslash;&n;                      DRM_DEBUG(&quot; --- truncation&bslash;n&quot;);&t;&bslash;&n;        }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;tmp_buf-&gt;num_dwords = num_dwords;      &t;&t;&t;&bslash;&n;&t;tmp_buf-&gt;current_dma_ptr = dma_ptr;    &t;&t;&t;&bslash;&n;} while (0)
DECL|macro|PRIMUPDATE
mdefine_line|#define PRIMUPDATE(dev_priv)&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;drm_mga_prim_buf_t *tmp_buf =&t;&t;&t;&t;&t;&bslash;&n;&t;&t;dev_priv-&gt;prim_bufs[dev_priv-&gt;current_prim_idx];&t;&bslash;&n;&t;tmp_buf-&gt;sec_used++;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|AGEBUF
mdefine_line|#define AGEBUF(dev_priv, buf_priv)&t;do {&t;&t;&t;&t;&bslash;&n;&t;drm_mga_prim_buf_t *tmp_buf =&t;&t;&t;&t;&t;&bslash;&n;&t;&t;dev_priv-&gt;prim_bufs[dev_priv-&gt;current_prim_idx];&t;&bslash;&n;&t;buf_priv-&gt;my_freelist-&gt;age = tmp_buf-&gt;prim_age;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|PRIMOUTREG
mdefine_line|#define PRIMOUTREG(reg, val) do {&t;&t;&t;&t;&t;&bslash;&n;&t;tempIndex[outcount]=ADRINDEX(reg);&t;&t;&t;&t;&bslash;&n;&t;dma_ptr[1+outcount] = val;&t;&t;&t;&t;&t;&bslash;&n;&t;if (MGA_VERBOSE)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_DEBUG(&quot;   PRIMOUT %d: 0x%x -- 0x%x&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;       num_dwords + 1 + outcount, ADRINDEX(reg), val);&t;&bslash;&n;&t;if( ++outcount == 4) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;outcount = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;dma_ptr[0] = *(unsigned long *)tempIndex;&t;&t;&bslash;&n;&t;&t;dma_ptr+=5;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;num_dwords += 5;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}while (0)
multiline_comment|/* A reduced set of the mga registers.&n; */
DECL|macro|MGAREG_MGA_EXEC
mdefine_line|#define MGAREG_MGA_EXEC &t;&t;&t;0x0100
DECL|macro|MGAREG_ALPHACTRL
mdefine_line|#define MGAREG_ALPHACTRL &t;&t;&t;0x2c7c
DECL|macro|MGAREG_AR0
mdefine_line|#define MGAREG_AR0 &t;&t;&t;&t;0x1c60
DECL|macro|MGAREG_AR1
mdefine_line|#define MGAREG_AR1 &t;&t;&t;&t;0x1c64
DECL|macro|MGAREG_AR2
mdefine_line|#define MGAREG_AR2 &t;&t;&t;&t;0x1c68
DECL|macro|MGAREG_AR3
mdefine_line|#define MGAREG_AR3 &t;&t;&t;&t;0x1c6c
DECL|macro|MGAREG_AR4
mdefine_line|#define MGAREG_AR4 &t;&t;&t;&t;0x1c70
DECL|macro|MGAREG_AR5
mdefine_line|#define MGAREG_AR5 &t;&t;&t;&t;0x1c74
DECL|macro|MGAREG_AR6
mdefine_line|#define MGAREG_AR6 &t;&t;&t;&t;0x1c78
DECL|macro|MGAREG_CXBNDRY
mdefine_line|#define MGAREG_CXBNDRY&t;&t;&t;&t;0x1c80
DECL|macro|MGAREG_CXLEFT
mdefine_line|#define MGAREG_CXLEFT &t;&t;&t;&t;0x1ca0
DECL|macro|MGAREG_CXRIGHT
mdefine_line|#define MGAREG_CXRIGHT&t;&t;&t;&t;0x1ca4
DECL|macro|MGAREG_DMAPAD
mdefine_line|#define MGAREG_DMAPAD &t;&t;&t;&t;0x1c54
DECL|macro|MGAREG_DSTORG
mdefine_line|#define MGAREG_DSTORG &t;&t;&t;&t;0x2cb8
DECL|macro|MGAREG_DWGCTL
mdefine_line|#define MGAREG_DWGCTL &t;&t;&t;&t;0x1c00
DECL|macro|MGAREG_DWGSYNC
mdefine_line|#define MGAREG_DWGSYNC&t;&t;&t;&t;0x2c4c
DECL|macro|MGAREG_FCOL
mdefine_line|#define MGAREG_FCOL &t;&t;&t;&t;0x1c24
DECL|macro|MGAREG_FIFOSTATUS
mdefine_line|#define MGAREG_FIFOSTATUS &t;&t;&t;0x1e10
DECL|macro|MGAREG_FOGCOL
mdefine_line|#define MGAREG_FOGCOL &t;&t;&t;&t;0x1cf4
DECL|macro|MGAREG_FXBNDRY
mdefine_line|#define MGAREG_FXBNDRY&t;&t;&t;&t;0x1c84
DECL|macro|MGAREG_FXLEFT
mdefine_line|#define MGAREG_FXLEFT &t;&t;&t;&t;0x1ca8
DECL|macro|MGAREG_FXRIGHT
mdefine_line|#define MGAREG_FXRIGHT&t;&t;&t;&t;0x1cac
DECL|macro|MGAREG_ICLEAR
mdefine_line|#define MGAREG_ICLEAR &t;&t;&t;&t;0x1e18
DECL|macro|MGAREG_IEN
mdefine_line|#define MGAREG_IEN &t;&t;&t;&t;0x1e1c
DECL|macro|MGAREG_LEN
mdefine_line|#define MGAREG_LEN &t;&t;&t;&t;0x1c5c
DECL|macro|MGAREG_MACCESS
mdefine_line|#define MGAREG_MACCESS&t;&t;&t;&t;0x1c04
DECL|macro|MGAREG_PITCH
mdefine_line|#define MGAREG_PITCH &t;&t;&t;&t;0x1c8c
DECL|macro|MGAREG_PLNWT
mdefine_line|#define MGAREG_PLNWT &t;&t;&t;&t;0x1c1c
DECL|macro|MGAREG_PRIMADDRESS
mdefine_line|#define MGAREG_PRIMADDRESS &t;&t;&t;0x1e58
DECL|macro|MGAREG_PRIMEND
mdefine_line|#define MGAREG_PRIMEND&t;&t;&t;&t;0x1e5c
DECL|macro|MGAREG_PRIMPTR
mdefine_line|#define MGAREG_PRIMPTR&t;&t;&t;&t;0x1e50
DECL|macro|MGAREG_SECADDRESS
mdefine_line|#define MGAREG_SECADDRESS &t;&t;&t;0x2c40
DECL|macro|MGAREG_SECEND
mdefine_line|#define MGAREG_SECEND &t;&t;&t;&t;0x2c44
DECL|macro|MGAREG_SETUPADDRESS
mdefine_line|#define MGAREG_SETUPADDRESS &t;&t;&t;0x2cd0
DECL|macro|MGAREG_SETUPEND
mdefine_line|#define MGAREG_SETUPEND &t;&t;&t;0x2cd4
DECL|macro|MGAREG_SOFTRAP
mdefine_line|#define MGAREG_SOFTRAP&t;&t;&t;&t;0x2c48
DECL|macro|MGAREG_SRCORG
mdefine_line|#define MGAREG_SRCORG &t;&t;&t;&t;0x2cb4
DECL|macro|MGAREG_STATUS
mdefine_line|#define MGAREG_STATUS &t;&t;&t;&t;0x1e14
DECL|macro|MGAREG_STENCIL
mdefine_line|#define MGAREG_STENCIL&t;&t;&t;&t;0x2cc8
DECL|macro|MGAREG_STENCILCTL
mdefine_line|#define MGAREG_STENCILCTL &t;&t;&t;0x2ccc
DECL|macro|MGAREG_TDUALSTAGE0
mdefine_line|#define MGAREG_TDUALSTAGE0 &t;&t;&t;0x2cf8
DECL|macro|MGAREG_TDUALSTAGE1
mdefine_line|#define MGAREG_TDUALSTAGE1 &t;&t;&t;0x2cfc
DECL|macro|MGAREG_TEXBORDERCOL
mdefine_line|#define MGAREG_TEXBORDERCOL &t;&t;&t;0x2c5c
DECL|macro|MGAREG_TEXCTL
mdefine_line|#define MGAREG_TEXCTL &t;&t;&t;&t;0x2c30
DECL|macro|MGAREG_TEXCTL2
mdefine_line|#define MGAREG_TEXCTL2&t;&t;&t;&t;0x2c3c
DECL|macro|MGAREG_TEXFILTER
mdefine_line|#define MGAREG_TEXFILTER &t;&t;&t;0x2c58
DECL|macro|MGAREG_TEXHEIGHT
mdefine_line|#define MGAREG_TEXHEIGHT &t;&t;&t;0x2c2c
DECL|macro|MGAREG_TEXORG
mdefine_line|#define MGAREG_TEXORG &t;&t;&t;&t;0x2c24
DECL|macro|MGAREG_TEXORG1
mdefine_line|#define MGAREG_TEXORG1&t;&t;&t;&t;0x2ca4
DECL|macro|MGAREG_TEXORG2
mdefine_line|#define MGAREG_TEXORG2&t;&t;&t;&t;0x2ca8
DECL|macro|MGAREG_TEXORG3
mdefine_line|#define MGAREG_TEXORG3&t;&t;&t;&t;0x2cac
DECL|macro|MGAREG_TEXORG4
mdefine_line|#define MGAREG_TEXORG4&t;&t;&t;&t;0x2cb0
DECL|macro|MGAREG_TEXTRANS
mdefine_line|#define MGAREG_TEXTRANS &t;&t;&t;0x2c34
DECL|macro|MGAREG_TEXTRANSHIGH
mdefine_line|#define MGAREG_TEXTRANSHIGH &t;&t;&t;0x2c38
DECL|macro|MGAREG_TEXWIDTH
mdefine_line|#define MGAREG_TEXWIDTH &t;&t;&t;0x2c28
DECL|macro|MGAREG_WACCEPTSEQ
mdefine_line|#define MGAREG_WACCEPTSEQ &t;&t;&t;0x1dd4
DECL|macro|MGAREG_WCODEADDR
mdefine_line|#define MGAREG_WCODEADDR &t;&t;&t;0x1e6c
DECL|macro|MGAREG_WFLAG
mdefine_line|#define MGAREG_WFLAG &t;&t;&t;&t;0x1dc4
DECL|macro|MGAREG_WFLAG1
mdefine_line|#define MGAREG_WFLAG1 &t;&t;&t;&t;0x1de0
DECL|macro|MGAREG_WFLAGNB
mdefine_line|#define MGAREG_WFLAGNB&t;&t;&t;&t;0x1e64
DECL|macro|MGAREG_WFLAGNB1
mdefine_line|#define MGAREG_WFLAGNB1 &t;&t;&t;0x1e08
DECL|macro|MGAREG_WGETMSB
mdefine_line|#define MGAREG_WGETMSB&t;&t;&t;&t;0x1dc8
DECL|macro|MGAREG_WIADDR
mdefine_line|#define MGAREG_WIADDR &t;&t;&t;&t;0x1dc0
DECL|macro|MGAREG_WIADDR2
mdefine_line|#define MGAREG_WIADDR2&t;&t;&t;&t;0x1dd8
DECL|macro|MGAREG_WMISC
mdefine_line|#define MGAREG_WMISC &t;&t;&t;&t;0x1e70
DECL|macro|MGAREG_WVRTXSZ
mdefine_line|#define MGAREG_WVRTXSZ&t;&t;&t;&t;0x1dcc
DECL|macro|MGAREG_YBOT
mdefine_line|#define MGAREG_YBOT &t;&t;&t;&t;0x1c9c
DECL|macro|MGAREG_YDST
mdefine_line|#define MGAREG_YDST &t;&t;&t;&t;0x1c90
DECL|macro|MGAREG_YDSTLEN
mdefine_line|#define MGAREG_YDSTLEN&t;&t;&t;&t;0x1c88
DECL|macro|MGAREG_YDSTORG
mdefine_line|#define MGAREG_YDSTORG&t;&t;&t;&t;0x1c94
DECL|macro|MGAREG_YTOP
mdefine_line|#define MGAREG_YTOP &t;&t;&t;&t;0x1c98
DECL|macro|MGAREG_ZORG
mdefine_line|#define MGAREG_ZORG &t;&t;&t;&t;0x1c0c
multiline_comment|/* Warp registers */
DECL|macro|MGAREG_WR0
mdefine_line|#define MGAREG_WR0                              0x2d00
DECL|macro|MGAREG_WR1
mdefine_line|#define MGAREG_WR1                              0x2d04
DECL|macro|MGAREG_WR2
mdefine_line|#define MGAREG_WR2                              0x2d08
DECL|macro|MGAREG_WR3
mdefine_line|#define MGAREG_WR3                              0x2d0c
DECL|macro|MGAREG_WR4
mdefine_line|#define MGAREG_WR4                              0x2d10
DECL|macro|MGAREG_WR5
mdefine_line|#define MGAREG_WR5                              0x2d14
DECL|macro|MGAREG_WR6
mdefine_line|#define MGAREG_WR6                              0x2d18
DECL|macro|MGAREG_WR7
mdefine_line|#define MGAREG_WR7                              0x2d1c
DECL|macro|MGAREG_WR8
mdefine_line|#define MGAREG_WR8                              0x2d20
DECL|macro|MGAREG_WR9
mdefine_line|#define MGAREG_WR9                              0x2d24
DECL|macro|MGAREG_WR10
mdefine_line|#define MGAREG_WR10                             0x2d28
DECL|macro|MGAREG_WR11
mdefine_line|#define MGAREG_WR11                             0x2d2c
DECL|macro|MGAREG_WR12
mdefine_line|#define MGAREG_WR12                             0x2d30
DECL|macro|MGAREG_WR13
mdefine_line|#define MGAREG_WR13                             0x2d34
DECL|macro|MGAREG_WR14
mdefine_line|#define MGAREG_WR14                             0x2d38
DECL|macro|MGAREG_WR15
mdefine_line|#define MGAREG_WR15                             0x2d3c
DECL|macro|MGAREG_WR16
mdefine_line|#define MGAREG_WR16                             0x2d40
DECL|macro|MGAREG_WR17
mdefine_line|#define MGAREG_WR17                             0x2d44
DECL|macro|MGAREG_WR18
mdefine_line|#define MGAREG_WR18                             0x2d48
DECL|macro|MGAREG_WR19
mdefine_line|#define MGAREG_WR19                             0x2d4c
DECL|macro|MGAREG_WR20
mdefine_line|#define MGAREG_WR20                             0x2d50
DECL|macro|MGAREG_WR21
mdefine_line|#define MGAREG_WR21                             0x2d54
DECL|macro|MGAREG_WR22
mdefine_line|#define MGAREG_WR22                             0x2d58
DECL|macro|MGAREG_WR23
mdefine_line|#define MGAREG_WR23                             0x2d5c
DECL|macro|MGAREG_WR24
mdefine_line|#define MGAREG_WR24                             0x2d60
DECL|macro|MGAREG_WR25
mdefine_line|#define MGAREG_WR25                             0x2d64
DECL|macro|MGAREG_WR26
mdefine_line|#define MGAREG_WR26                             0x2d68
DECL|macro|MGAREG_WR27
mdefine_line|#define MGAREG_WR27                             0x2d6c
DECL|macro|MGAREG_WR28
mdefine_line|#define MGAREG_WR28                             0x2d70
DECL|macro|MGAREG_WR29
mdefine_line|#define MGAREG_WR29                             0x2d74
DECL|macro|MGAREG_WR30
mdefine_line|#define MGAREG_WR30                             0x2d78
DECL|macro|MGAREG_WR31
mdefine_line|#define MGAREG_WR31                             0x2d7c
DECL|macro|MGAREG_WR32
mdefine_line|#define MGAREG_WR32                             0x2d80
DECL|macro|MGAREG_WR33
mdefine_line|#define MGAREG_WR33                             0x2d84
DECL|macro|MGAREG_WR34
mdefine_line|#define MGAREG_WR34                             0x2d88
DECL|macro|MGAREG_WR35
mdefine_line|#define MGAREG_WR35                             0x2d8c
DECL|macro|MGAREG_WR36
mdefine_line|#define MGAREG_WR36                             0x2d90
DECL|macro|MGAREG_WR37
mdefine_line|#define MGAREG_WR37                             0x2d94
DECL|macro|MGAREG_WR38
mdefine_line|#define MGAREG_WR38                             0x2d98
DECL|macro|MGAREG_WR39
mdefine_line|#define MGAREG_WR39                             0x2d9c
DECL|macro|MGAREG_WR40
mdefine_line|#define MGAREG_WR40                             0x2da0
DECL|macro|MGAREG_WR41
mdefine_line|#define MGAREG_WR41                             0x2da4
DECL|macro|MGAREG_WR42
mdefine_line|#define MGAREG_WR42                             0x2da8
DECL|macro|MGAREG_WR43
mdefine_line|#define MGAREG_WR43                             0x2dac
DECL|macro|MGAREG_WR44
mdefine_line|#define MGAREG_WR44                             0x2db0
DECL|macro|MGAREG_WR45
mdefine_line|#define MGAREG_WR45                             0x2db4
DECL|macro|MGAREG_WR46
mdefine_line|#define MGAREG_WR46                             0x2db8
DECL|macro|MGAREG_WR47
mdefine_line|#define MGAREG_WR47                             0x2dbc
DECL|macro|MGAREG_WR48
mdefine_line|#define MGAREG_WR48                             0x2dc0
DECL|macro|MGAREG_WR49
mdefine_line|#define MGAREG_WR49                             0x2dc4
DECL|macro|MGAREG_WR50
mdefine_line|#define MGAREG_WR50                             0x2dc8
DECL|macro|MGAREG_WR51
mdefine_line|#define MGAREG_WR51                             0x2dcc
DECL|macro|MGAREG_WR52
mdefine_line|#define MGAREG_WR52                             0x2dd0
DECL|macro|MGAREG_WR53
mdefine_line|#define MGAREG_WR53                             0x2dd4
DECL|macro|MGAREG_WR54
mdefine_line|#define MGAREG_WR54                             0x2dd8
DECL|macro|MGAREG_WR55
mdefine_line|#define MGAREG_WR55                             0x2ddc
DECL|macro|MGAREG_WR56
mdefine_line|#define MGAREG_WR56                             0x2de0
DECL|macro|MGAREG_WR57
mdefine_line|#define MGAREG_WR57                             0x2de4
DECL|macro|MGAREG_WR58
mdefine_line|#define MGAREG_WR58                             0x2de8
DECL|macro|MGAREG_WR59
mdefine_line|#define MGAREG_WR59                             0x2dec
DECL|macro|MGAREG_WR60
mdefine_line|#define MGAREG_WR60                             0x2df0
DECL|macro|MGAREG_WR61
mdefine_line|#define MGAREG_WR61                             0x2df4
DECL|macro|MGAREG_WR62
mdefine_line|#define MGAREG_WR62                             0x2df8
DECL|macro|MGAREG_WR63
mdefine_line|#define MGAREG_WR63                             0x2dfc
DECL|macro|PDEA_pagpxfer_enable
mdefine_line|#define PDEA_pagpxfer_enable&t;&t;&t;0x2
DECL|macro|WIA_wmode_suspend
mdefine_line|#define WIA_wmode_suspend&t;&t;&t;0x0
DECL|macro|WIA_wmode_start
mdefine_line|#define WIA_wmode_start &t;&t;&t;0x3
DECL|macro|WIA_wagp_agp
mdefine_line|#define WIA_wagp_agp&t;&t;&t;&t;0x4
DECL|macro|DC_opcod_line_open
mdefine_line|#define DC_opcod_line_open &t;&t;&t;0x0
DECL|macro|DC_opcod_autoline_open
mdefine_line|#define DC_opcod_autoline_open &t;&t;&t;0x1
DECL|macro|DC_opcod_line_close
mdefine_line|#define DC_opcod_line_close &t;&t;&t;0x2
DECL|macro|DC_opcod_autoline_close
mdefine_line|#define DC_opcod_autoline_close &t;&t;0x3
DECL|macro|DC_opcod_trap
mdefine_line|#define DC_opcod_trap &t;&t;&t;&t;0x4
DECL|macro|DC_opcod_texture_trap
mdefine_line|#define DC_opcod_texture_trap &t;&t;&t;0x6
DECL|macro|DC_opcod_bitblt
mdefine_line|#define DC_opcod_bitblt &t;&t;&t;0x8
DECL|macro|DC_opcod_iload
mdefine_line|#define DC_opcod_iload &t;&t;&t;&t;0x9
DECL|macro|DC_atype_rpl
mdefine_line|#define DC_atype_rpl &t;&t;&t;&t;0x0
DECL|macro|DC_atype_rstr
mdefine_line|#define DC_atype_rstr &t;&t;&t;&t;0x10
DECL|macro|DC_atype_zi
mdefine_line|#define DC_atype_zi &t;&t;&t;&t;0x30
DECL|macro|DC_atype_blk
mdefine_line|#define DC_atype_blk &t;&t;&t;&t;0x40
DECL|macro|DC_atype_i
mdefine_line|#define DC_atype_i &t;&t;&t;&t;0x70
DECL|macro|DC_linear_xy
mdefine_line|#define DC_linear_xy &t;&t;&t;&t;0x0
DECL|macro|DC_linear_linear
mdefine_line|#define DC_linear_linear &t;&t;&t;0x80
DECL|macro|DC_zmode_nozcmp
mdefine_line|#define DC_zmode_nozcmp &t;&t;&t;0x0
DECL|macro|DC_zmode_ze
mdefine_line|#define DC_zmode_ze &t;&t;&t;&t;0x200
DECL|macro|DC_zmode_zne
mdefine_line|#define DC_zmode_zne &t;&t;&t;&t;0x300
DECL|macro|DC_zmode_zlt
mdefine_line|#define DC_zmode_zlt &t;&t;&t;&t;0x400
DECL|macro|DC_zmode_zlte
mdefine_line|#define DC_zmode_zlte &t;&t;&t;&t;0x500
DECL|macro|DC_zmode_zgt
mdefine_line|#define DC_zmode_zgt &t;&t;&t;&t;0x600
DECL|macro|DC_zmode_zgte
mdefine_line|#define DC_zmode_zgte &t;&t;&t;&t;0x700
DECL|macro|DC_solid_disable
mdefine_line|#define DC_solid_disable &t;&t;&t;0x0
DECL|macro|DC_solid_enable
mdefine_line|#define DC_solid_enable &t;&t;&t;0x800
DECL|macro|DC_arzero_disable
mdefine_line|#define DC_arzero_disable &t;&t;&t;0x0
DECL|macro|DC_arzero_enable
mdefine_line|#define DC_arzero_enable &t;&t;&t;0x1000
DECL|macro|DC_sgnzero_disable
mdefine_line|#define DC_sgnzero_disable &t;&t;&t;0x0
DECL|macro|DC_sgnzero_enable
mdefine_line|#define DC_sgnzero_enable &t;&t;&t;0x2000
DECL|macro|DC_shftzero_disable
mdefine_line|#define DC_shftzero_disable &t;&t;&t;0x0
DECL|macro|DC_shftzero_enable
mdefine_line|#define DC_shftzero_enable &t;&t;&t;0x4000
DECL|macro|DC_bop_SHIFT
mdefine_line|#define DC_bop_SHIFT &t;&t;&t;&t;16
DECL|macro|DC_trans_SHIFT
mdefine_line|#define DC_trans_SHIFT &t;&t;&t;&t;20
DECL|macro|DC_bltmod_bmonolef
mdefine_line|#define DC_bltmod_bmonolef &t;&t;&t;0x0
DECL|macro|DC_bltmod_bmonowf
mdefine_line|#define DC_bltmod_bmonowf &t;&t;&t;0x8000000
DECL|macro|DC_bltmod_bplan
mdefine_line|#define DC_bltmod_bplan &t;&t;&t;0x2000000
DECL|macro|DC_bltmod_bfcol
mdefine_line|#define DC_bltmod_bfcol &t;&t;&t;0x4000000
DECL|macro|DC_bltmod_bu32bgr
mdefine_line|#define DC_bltmod_bu32bgr &t;&t;&t;0x6000000
DECL|macro|DC_bltmod_bu32rgb
mdefine_line|#define DC_bltmod_bu32rgb &t;&t;&t;0xe000000
DECL|macro|DC_bltmod_bu24bgr
mdefine_line|#define DC_bltmod_bu24bgr &t;&t;&t;0x16000000
DECL|macro|DC_bltmod_bu24rgb
mdefine_line|#define DC_bltmod_bu24rgb &t;&t;&t;0x1e000000
DECL|macro|DC_pattern_disable
mdefine_line|#define DC_pattern_disable &t;&t;&t;0x0
DECL|macro|DC_pattern_enable
mdefine_line|#define DC_pattern_enable &t;&t;&t;0x20000000
DECL|macro|DC_transc_disable
mdefine_line|#define DC_transc_disable &t;&t;&t;0x0
DECL|macro|DC_transc_enable
mdefine_line|#define DC_transc_enable &t;&t;&t;0x40000000
DECL|macro|DC_clipdis_disable
mdefine_line|#define DC_clipdis_disable &t;&t;&t;0x0
DECL|macro|DC_clipdis_enable
mdefine_line|#define DC_clipdis_enable &t;&t;&t;0x80000000
DECL|macro|SETADD_mode_vertlist
mdefine_line|#define SETADD_mode_vertlist                   &t;0x0
DECL|macro|MGA_CLEAR_CMD
mdefine_line|#define MGA_CLEAR_CMD (DC_opcod_trap | DC_arzero_enable | &t;&t;&bslash;&n;&t;&t;       DC_sgnzero_enable | DC_shftzero_enable | &t;&bslash;&n;&t;&t;       (0xC &lt;&lt; DC_bop_SHIFT) | DC_clipdis_enable | &t;&bslash;&n;&t;&t;       DC_solid_enable | DC_transc_enable)
DECL|macro|MGA_COPY_CMD
mdefine_line|#define MGA_COPY_CMD (DC_opcod_bitblt | DC_atype_rpl | DC_linear_xy |&t;&bslash;&n;&t;&t;      DC_solid_disable | DC_arzero_disable | &t;&t;&bslash;&n;&t;&t;      DC_sgnzero_enable | DC_shftzero_enable | &t;&t;&bslash;&n;&t;&t;      (0xC &lt;&lt; DC_bop_SHIFT) | DC_bltmod_bfcol | &t;&bslash;&n;&t;&t;      DC_pattern_disable | DC_transc_disable | &t;&t;&bslash;&n;&t;&t;      DC_clipdis_enable)&t;&t;&t;&t;&bslash;&n;
DECL|macro|MGA_FLUSH_CMD
mdefine_line|#define MGA_FLUSH_CMD (DC_opcod_texture_trap | (0xF &lt;&lt; DC_trans_SHIFT) |&bslash;&n;&t;&t;       DC_arzero_enable | DC_sgnzero_enable |&t;&t;&bslash;&n;&t;&t;       DC_atype_i)
macro_line|#endif
eof
