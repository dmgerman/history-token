multiline_comment|/**&n; * &bslash;file drm_drv.h &n; * Generic driver template&n; *&n; * &bslash;author Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &bslash;author Gareth Hughes &lt;gareth@valinux.com&gt;&n; *&n; * To use this template, you must at least define the following (samples&n; * given for the MGA driver):&n; *&n; * &bslash;code&n; * #define DRIVER_AUTHOR&t;&quot;VA Linux Systems, Inc.&quot;&n; *&n; * #define DRIVER_NAME&t;&t;&quot;mga&quot;&n; * #define DRIVER_DESC&t;&t;&quot;Matrox G200/G400&quot;&n; * #define DRIVER_DATE&t;&t;&quot;20001127&quot;&n; *&n; * #define DRIVER_MAJOR&t;&t;2&n; * #define DRIVER_MINOR&t;&t;0&n; * #define DRIVER_PATCHLEVEL&t;2&n; *&n; * #define DRIVER_IOCTL_COUNT&t;DRM_ARRAY_SIZE( mga_ioctls )&n; *&n; * #define drm_x&t;&t;mga_##x&n; * &bslash;endcode&n; */
multiline_comment|/*&n; * Created: Thu Nov 23 03:10:50 2000 by gareth@valinux.com&n; *&n; * Copyright 1999, 2000 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;drm_core.h&quot;
multiline_comment|/** Ioctl table */
DECL|variable|drm_ioctls
id|drm_ioctl_desc_t
id|drm_ioctls
(braket
)braket
op_assign
(brace
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_VERSION
)paren
)braket
op_assign
(brace
id|drm_version
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_GET_UNIQUE
)paren
)braket
op_assign
(brace
id|drm_getunique
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_GET_MAGIC
)paren
)braket
op_assign
(brace
id|drm_getmagic
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_IRQ_BUSID
)paren
)braket
op_assign
(brace
id|drm_irq_by_busid
comma
l_int|0
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_GET_MAP
)paren
)braket
op_assign
(brace
id|drm_getmap
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_GET_CLIENT
)paren
)braket
op_assign
(brace
id|drm_getclient
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_GET_STATS
)paren
)braket
op_assign
(brace
id|drm_getstats
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_SET_VERSION
)paren
)braket
op_assign
(brace
id|drm_setversion
comma
l_int|0
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_SET_UNIQUE
)paren
)braket
op_assign
(brace
id|drm_setunique
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_BLOCK
)paren
)braket
op_assign
(brace
id|drm_noop
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_UNBLOCK
)paren
)braket
op_assign
(brace
id|drm_noop
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AUTH_MAGIC
)paren
)braket
op_assign
(brace
id|drm_authmagic
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_ADD_MAP
)paren
)braket
op_assign
(brace
id|drm_addmap
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_RM_MAP
)paren
)braket
op_assign
(brace
id|drm_rmmap
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_SET_SAREA_CTX
)paren
)braket
op_assign
(brace
id|drm_setsareactx
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_GET_SAREA_CTX
)paren
)braket
op_assign
(brace
id|drm_getsareactx
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_ADD_CTX
)paren
)braket
op_assign
(brace
id|drm_addctx
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_RM_CTX
)paren
)braket
op_assign
(brace
id|drm_rmctx
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_MOD_CTX
)paren
)braket
op_assign
(brace
id|drm_modctx
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_GET_CTX
)paren
)braket
op_assign
(brace
id|drm_getctx
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_SWITCH_CTX
)paren
)braket
op_assign
(brace
id|drm_switchctx
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_NEW_CTX
)paren
)braket
op_assign
(brace
id|drm_newctx
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_RES_CTX
)paren
)braket
op_assign
(brace
id|drm_resctx
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_ADD_DRAW
)paren
)braket
op_assign
(brace
id|drm_adddraw
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_RM_DRAW
)paren
)braket
op_assign
(brace
id|drm_rmdraw
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_LOCK
)paren
)braket
op_assign
(brace
id|drm_lock
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_UNLOCK
)paren
)braket
op_assign
(brace
id|drm_unlock
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_FINISH
)paren
)braket
op_assign
(brace
id|drm_noop
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_ADD_BUFS
)paren
)braket
op_assign
(brace
id|drm_addbufs
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_MARK_BUFS
)paren
)braket
op_assign
(brace
id|drm_markbufs
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_INFO_BUFS
)paren
)braket
op_assign
(brace
id|drm_infobufs
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_MAP_BUFS
)paren
)braket
op_assign
(brace
id|drm_mapbufs
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_FREE_BUFS
)paren
)braket
op_assign
(brace
id|drm_freebufs
comma
l_int|1
comma
l_int|0
)brace
comma
multiline_comment|/* The DRM_IOCTL_DMA ioctl should be defined by the driver. */
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_CONTROL
)paren
)braket
op_assign
(brace
id|drm_control
comma
l_int|1
comma
l_int|1
)brace
comma
macro_line|#if __OS_HAS_AGP
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_ACQUIRE
)paren
)braket
op_assign
(brace
id|drm_agp_acquire
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_RELEASE
)paren
)braket
op_assign
(brace
id|drm_agp_release
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_ENABLE
)paren
)braket
op_assign
(brace
id|drm_agp_enable
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_INFO
)paren
)braket
op_assign
(brace
id|drm_agp_info
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_ALLOC
)paren
)braket
op_assign
(brace
id|drm_agp_alloc
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_FREE
)paren
)braket
op_assign
(brace
id|drm_agp_free
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_BIND
)paren
)braket
op_assign
(brace
id|drm_agp_bind
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_UNBIND
)paren
)braket
op_assign
(brace
id|drm_agp_unbind
comma
l_int|1
comma
l_int|1
)brace
comma
macro_line|#endif
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_SG_ALLOC
)paren
)braket
op_assign
(brace
id|drm_sg_alloc
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_SG_FREE
)paren
)braket
op_assign
(brace
id|drm_sg_free
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_WAIT_VBLANK
)paren
)braket
op_assign
(brace
id|drm_wait_vblank
comma
l_int|0
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|macro|DRIVER_IOCTL_COUNT
mdefine_line|#define DRIVER_IOCTL_COUNT&t;DRM_ARRAY_SIZE( drm_ioctls )
multiline_comment|/**&n; * Take down the DRM device.&n; *&n; * &bslash;param dev DRM device structure.&n; *&n; * Frees every resource in &bslash;p dev.&n; *&n; * &bslash;sa drm_device and setup().&n; */
DECL|function|drm_takedown
r_int
id|drm_takedown
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_magic_entry_t
op_star
id|pt
comma
op_star
id|next
suffix:semicolon
id|drm_map_t
op_star
id|map
suffix:semicolon
id|drm_map_list_t
op_star
id|r_list
suffix:semicolon
r_struct
id|list_head
op_star
id|list
comma
op_star
id|list_next
suffix:semicolon
id|drm_vma_entry_t
op_star
id|vma
comma
op_star
id|vma_next
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;pretakedown
)paren
id|dev-&gt;driver
op_member_access_from_pointer
id|pretakedown
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq_enabled
)paren
id|drm_irq_uninstall
c_func
(paren
id|dev
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|dev-&gt;timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;devname
)paren
(brace
id|drm_free
c_func
(paren
id|dev-&gt;devname
comma
id|strlen
c_func
(paren
id|dev-&gt;devname
)paren
op_plus
l_int|1
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
id|dev-&gt;devname
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;unique
)paren
(brace
id|drm_free
c_func
(paren
id|dev-&gt;unique
comma
id|strlen
c_func
(paren
id|dev-&gt;unique
)paren
op_plus
l_int|1
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
id|dev-&gt;unique
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;unique_len
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Clear pid list */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|DRM_HASH_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|pt
op_assign
id|dev-&gt;magiclist
(braket
id|i
)braket
dot
id|head
suffix:semicolon
id|pt
suffix:semicolon
id|pt
op_assign
id|next
)paren
(brace
id|next
op_assign
id|pt-&gt;next
suffix:semicolon
id|drm_free
c_func
(paren
id|pt
comma
r_sizeof
(paren
op_star
id|pt
)paren
comma
id|DRM_MEM_MAGIC
)paren
suffix:semicolon
)brace
id|dev-&gt;magiclist
(braket
id|i
)braket
dot
id|head
op_assign
id|dev-&gt;magiclist
(braket
id|i
)braket
dot
id|tail
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Clear AGP information */
r_if
c_cond
(paren
id|drm_core_has_AGP
c_func
(paren
id|dev
)paren
op_logical_and
id|dev-&gt;agp
)paren
(brace
id|drm_agp_mem_t
op_star
id|entry
suffix:semicolon
id|drm_agp_mem_t
op_star
id|nexte
suffix:semicolon
multiline_comment|/* Remove AGP resources, but leave dev-&gt;agp&n;                                   intact until drv_cleanup is called. */
r_for
c_loop
(paren
id|entry
op_assign
id|dev-&gt;agp-&gt;memory
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|nexte
)paren
(brace
id|nexte
op_assign
id|entry-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;bound
)paren
id|drm_unbind_agp
c_func
(paren
id|entry-&gt;memory
)paren
suffix:semicolon
id|drm_free_agp
c_func
(paren
id|entry-&gt;memory
comma
id|entry-&gt;pages
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|entry
comma
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|DRM_MEM_AGPLISTS
)paren
suffix:semicolon
)brace
id|dev-&gt;agp-&gt;memory
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;agp-&gt;acquired
)paren
id|drm_agp_do_release
c_func
(paren
)paren
suffix:semicolon
id|dev-&gt;agp-&gt;acquired
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;agp-&gt;enabled
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Clear vma list (only built for debugging) */
r_if
c_cond
(paren
id|dev-&gt;vmalist
)paren
(brace
r_for
c_loop
(paren
id|vma
op_assign
id|dev-&gt;vmalist
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma_next
)paren
(brace
id|vma_next
op_assign
id|vma-&gt;next
suffix:semicolon
id|drm_free
c_func
(paren
id|vma
comma
r_sizeof
(paren
op_star
id|vma
)paren
comma
id|DRM_MEM_VMAS
)paren
suffix:semicolon
)brace
id|dev-&gt;vmalist
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;maplist
)paren
(brace
id|list_for_each_safe
c_func
(paren
id|list
comma
id|list_next
comma
op_amp
id|dev-&gt;maplist-&gt;head
)paren
(brace
id|r_list
op_assign
(paren
id|drm_map_list_t
op_star
)paren
id|list
suffix:semicolon
r_if
c_cond
(paren
(paren
id|map
op_assign
id|r_list-&gt;map
)paren
)paren
(brace
r_switch
c_cond
(paren
id|map-&gt;type
)paren
(brace
r_case
id|_DRM_REGISTERS
suffix:colon
r_case
id|_DRM_FRAME_BUFFER
suffix:colon
r_if
c_cond
(paren
id|drm_core_has_MTRR
c_func
(paren
id|dev
)paren
)paren
(brace
r_if
c_cond
(paren
id|map-&gt;mtrr
op_ge
l_int|0
)paren
(brace
r_int
id|retcode
suffix:semicolon
id|retcode
op_assign
id|mtrr_del
c_func
(paren
id|map-&gt;mtrr
comma
id|map-&gt;offset
comma
id|map-&gt;size
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;mtrr_del=%d&bslash;n&quot;
comma
id|retcode
)paren
suffix:semicolon
)brace
)brace
id|drm_ioremapfree
c_func
(paren
id|map-&gt;handle
comma
id|map-&gt;size
comma
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_DRM_SHM
suffix:colon
id|vfree
c_func
(paren
id|map-&gt;handle
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_DRM_AGP
suffix:colon
multiline_comment|/* Do nothing here, because this is all&n;&t;&t;&t;&t;&t; * handled in the AGP/GART driver.&n;&t;&t;&t;&t;&t; */
r_break
suffix:semicolon
r_case
id|_DRM_SCATTER_GATHER
suffix:colon
multiline_comment|/* Handle it */
r_if
c_cond
(paren
id|drm_core_check_feature
c_func
(paren
id|dev
comma
id|DRIVER_SG
)paren
op_logical_and
id|dev-&gt;sg
)paren
(brace
id|drm_sg_cleanup
c_func
(paren
id|dev-&gt;sg
)paren
suffix:semicolon
id|dev-&gt;sg
op_assign
l_int|NULL
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|drm_free
c_func
(paren
id|map
comma
r_sizeof
(paren
op_star
id|map
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
)brace
id|list_del
c_func
(paren
id|list
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|r_list
comma
r_sizeof
(paren
op_star
id|r_list
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
)brace
id|drm_free
c_func
(paren
id|dev-&gt;maplist
comma
r_sizeof
(paren
op_star
id|dev-&gt;maplist
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
id|dev-&gt;maplist
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|drm_core_check_feature
c_func
(paren
id|dev
comma
id|DRIVER_DMA_QUEUE
)paren
op_logical_and
id|dev-&gt;queuelist
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dev-&gt;queue_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;queuelist
(braket
id|i
)braket
)paren
(brace
id|drm_free
c_func
(paren
id|dev-&gt;queuelist
(braket
id|i
)braket
comma
r_sizeof
(paren
op_star
id|dev-&gt;queuelist
(braket
l_int|0
)braket
)paren
comma
id|DRM_MEM_QUEUES
)paren
suffix:semicolon
id|dev-&gt;queuelist
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|drm_free
c_func
(paren
id|dev-&gt;queuelist
comma
id|dev-&gt;queue_slots
op_star
r_sizeof
(paren
op_star
id|dev-&gt;queuelist
)paren
comma
id|DRM_MEM_QUEUES
)paren
suffix:semicolon
id|dev-&gt;queuelist
op_assign
l_int|NULL
suffix:semicolon
)brace
id|dev-&gt;queue_count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|drm_core_check_feature
c_func
(paren
id|dev
comma
id|DRIVER_HAVE_DMA
)paren
)paren
id|drm_dma_takedown
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;lock.hw_lock
)paren
(brace
id|dev-&gt;sigdata.lock
op_assign
id|dev-&gt;lock.hw_lock
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* SHM removed */
id|dev-&gt;lock.filp
op_assign
l_int|NULL
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;lock.lock_queue
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Module initialization. Called via init_module at module load time, or via&n; * linux/init/main.c (this is not currently supported).&n; *&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Initializes an array of drm_device structures, and attempts to&n; * initialize all available devices, using consecutive minors, registering the&n; * stubs and initializing the AGP device.&n; * &n; * Expands the &bslash;c DRIVER_PREINIT and &bslash;c DRIVER_POST_INIT macros before and&n; * after the initialization for driver customization.&n; */
DECL|function|drm_init
r_int
id|drm_init
c_func
(paren
r_struct
id|drm_driver
op_star
id|driver
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|pci_device_id
op_star
id|pid
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|drm_mem_init
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|driver-&gt;pci_driver.id_table
(braket
id|i
)braket
dot
id|vendor
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pid
op_assign
(paren
r_struct
id|pci_device_id
op_star
)paren
op_amp
id|driver-&gt;pci_driver.id_table
(braket
id|i
)braket
suffix:semicolon
id|pdev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* pass back in pdev to account for multiple identical cards */
r_while
c_loop
(paren
(paren
id|pdev
op_assign
id|pci_get_subsys
c_func
(paren
id|pid-&gt;vendor
comma
id|pid-&gt;device
comma
id|pid-&gt;subvendor
comma
id|pid-&gt;subdevice
comma
id|pdev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* stealth mode requires a manual probe */
id|pci_dev_get
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|drm_probe
c_func
(paren
id|pdev
comma
id|pid
comma
id|driver
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|drm_init
id|EXPORT_SYMBOL
c_func
(paren
id|drm_init
)paren
suffix:semicolon
multiline_comment|/**&n; * Called via cleanup_module() at module unload time.&n; *&n; * Cleans up all DRM device, calling takedown().&n; * &n; * &bslash;sa drm_init().&n; */
DECL|function|drm_cleanup
r_static
r_void
id|drm_cleanup
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;cleanup called no dev&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|drm_takedown
c_func
(paren
id|dev
)paren
suffix:semicolon
id|drm_ctxbitmap_cleanup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drm_core_has_MTRR
c_func
(paren
id|dev
)paren
op_logical_and
id|drm_core_has_AGP
c_func
(paren
id|dev
)paren
op_logical_and
id|dev-&gt;agp
op_logical_and
id|dev-&gt;agp-&gt;agp_mtrr
op_ge
l_int|0
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|mtrr_del
c_func
(paren
id|dev-&gt;agp-&gt;agp_mtrr
comma
id|dev-&gt;agp-&gt;agp_info.aper_base
comma
id|dev-&gt;agp-&gt;agp_info.aper_size
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;mtrr_del=%d&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|drm_core_has_AGP
c_func
(paren
id|dev
)paren
op_logical_and
id|dev-&gt;agp
)paren
(brace
id|drm_free
c_func
(paren
id|dev-&gt;agp
comma
r_sizeof
(paren
op_star
id|dev-&gt;agp
)paren
comma
id|DRM_MEM_AGPLISTS
)paren
suffix:semicolon
id|dev-&gt;agp
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;postcleanup
)paren
id|dev-&gt;driver
op_member_access_from_pointer
id|postcleanup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drm_put_minor
c_func
(paren
id|dev
)paren
)paren
id|DRM_ERROR
c_func
(paren
l_string|&quot;Cannot unload module&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|drm_exit
r_void
id|drm_exit
(paren
r_struct
id|drm_driver
op_star
id|driver
)paren
(brace
r_int
id|i
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
id|drm_minor_t
op_star
id|minor
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|drm_cards_limit
suffix:semicolon
id|i
op_increment
)paren
(brace
id|minor
op_assign
op_amp
id|drm_minors
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|minor-&gt;dev
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|minor-&gt;dev-&gt;driver
op_ne
id|driver
)paren
r_continue
suffix:semicolon
id|dev
op_assign
id|minor-&gt;dev
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev
)paren
(brace
multiline_comment|/* release the pci driver */
r_if
c_cond
(paren
id|dev-&gt;pdev
)paren
id|pci_dev_put
c_func
(paren
id|dev-&gt;pdev
)paren
suffix:semicolon
id|drm_cleanup
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|DRM_INFO
c_func
(paren
l_string|&quot;Module unloaded&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|drm_exit
id|EXPORT_SYMBOL
c_func
(paren
id|drm_exit
)paren
suffix:semicolon
multiline_comment|/** File operations structure */
DECL|variable|drm_stub_fops
r_static
r_struct
id|file_operations
id|drm_stub_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|drm_stub_open
)brace
suffix:semicolon
DECL|function|drm_core_init
r_static
r_int
id|__init
id|drm_core_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|drm_cards_limit
op_assign
(paren
id|drm_cards_limit
OL
id|DRM_MAX_MINOR
op_plus
l_int|1
ques
c_cond
id|drm_cards_limit
suffix:colon
id|DRM_MAX_MINOR
op_plus
l_int|1
)paren
suffix:semicolon
id|drm_minors
op_assign
id|drm_calloc
c_func
(paren
id|drm_cards_limit
comma
r_sizeof
(paren
op_star
id|drm_minors
)paren
comma
id|DRM_MEM_STUB
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drm_minors
)paren
(brace
r_goto
id|err_p1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|DRM_MAJOR
comma
l_string|&quot;drm&quot;
comma
op_amp
id|drm_stub_fops
)paren
)paren
r_goto
id|err_p1
suffix:semicolon
id|drm_class
op_assign
id|drm_sysfs_create
c_func
(paren
id|THIS_MODULE
comma
l_string|&quot;drm&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|drm_class
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;DRM: Error creating drm class.&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|drm_class
)paren
suffix:semicolon
r_goto
id|err_p2
suffix:semicolon
)brace
id|drm_proc_root
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;dri&quot;
comma
id|S_IFDIR
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drm_proc_root
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Cannot create /proc/dri&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|err_p3
suffix:semicolon
)brace
id|DRM_INFO
c_func
(paren
l_string|&quot;Initialized %s %d.%d.%d %s&bslash;n&quot;
comma
id|DRIVER_NAME
comma
id|DRIVER_MAJOR
comma
id|DRIVER_MINOR
comma
id|DRIVER_PATCHLEVEL
comma
id|DRIVER_DATE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_p3
suffix:colon
id|drm_sysfs_destroy
c_func
(paren
id|drm_class
)paren
suffix:semicolon
id|err_p2
suffix:colon
id|unregister_chrdev
c_func
(paren
id|DRM_MAJOR
comma
l_string|&quot;drm&quot;
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|drm_minors
comma
r_sizeof
(paren
op_star
id|drm_minors
)paren
op_star
id|drm_cards_limit
comma
id|DRM_MEM_STUB
)paren
suffix:semicolon
id|err_p1
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|drm_core_exit
r_static
r_void
id|__exit
id|drm_core_exit
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;dri&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|drm_sysfs_destroy
c_func
(paren
id|drm_class
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|DRM_MAJOR
comma
l_string|&quot;drm&quot;
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|drm_minors
comma
r_sizeof
(paren
op_star
id|drm_minors
)paren
op_star
id|drm_cards_limit
comma
id|DRM_MEM_STUB
)paren
suffix:semicolon
)brace
DECL|variable|drm_core_init
id|module_init
c_func
(paren
id|drm_core_init
)paren
suffix:semicolon
DECL|variable|drm_core_exit
id|module_exit
c_func
(paren
id|drm_core_exit
)paren
suffix:semicolon
multiline_comment|/**&n; * Get version information&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument, pointing to a drm_version structure.&n; * &bslash;return zero on success or negative number on failure.&n; *&n; * Fills in the version information in &bslash;p arg.&n; */
DECL|function|drm_version
r_int
id|drm_version
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
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_version_t
id|__user
op_star
id|argp
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
id|drm_version_t
id|version
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|version
comma
id|argp
comma
r_sizeof
(paren
id|version
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* version is a required function to return the personality module version */
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|version
c_func
(paren
op_amp
id|version
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|argp
comma
op_amp
id|version
comma
r_sizeof
(paren
id|version
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/** &n; * Called whenever a process performs an ioctl on /dev/drm.&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument.&n; * &bslash;return zero on success or negative number on failure.&n; *&n; * Looks up the ioctl function in the ::ioctls table, checking for root&n; * previleges if so required, and dispatches to the respective function.&n; */
DECL|function|drm_ioctl
r_int
id|drm_ioctl
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
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_ioctl_desc_t
op_star
id|ioctl
suffix:semicolon
id|drm_ioctl_t
op_star
id|func
suffix:semicolon
r_int
r_int
id|nr
op_assign
id|DRM_IOCTL_NR
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_int
id|retcode
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;ioctl_count
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;counts
(braket
id|_DRM_STAT_IOCTLS
)braket
)paren
suffix:semicolon
op_increment
id|priv-&gt;ioctl_count
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;pid=%d, cmd=0x%02x, nr=0x%02x, dev 0x%lx, auth=%d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|cmd
comma
id|nr
comma
(paren
r_int
)paren
id|old_encode_dev
c_func
(paren
id|dev-&gt;device
)paren
comma
id|priv-&gt;authenticated
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
id|DRIVER_IOCTL_COUNT
)paren
id|ioctl
op_assign
op_amp
id|drm_ioctls
(braket
id|nr
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|nr
op_ge
id|DRM_COMMAND_BASE
)paren
op_logical_and
(paren
id|nr
OL
id|DRM_COMMAND_BASE
op_plus
id|dev-&gt;driver-&gt;num_ioctls
)paren
)paren
id|ioctl
op_assign
op_amp
id|dev-&gt;driver-&gt;ioctls
(braket
id|nr
op_minus
id|DRM_COMMAND_BASE
)braket
suffix:semicolon
r_else
r_goto
id|err_i1
suffix:semicolon
id|func
op_assign
id|ioctl-&gt;func
suffix:semicolon
multiline_comment|/* is there a local override? */
r_if
c_cond
(paren
(paren
id|nr
op_eq
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_DMA
)paren
)paren
op_logical_and
id|dev-&gt;driver-&gt;dma_ioctl
)paren
id|func
op_assign
id|dev-&gt;driver-&gt;dma_ioctl
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|func
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;no function&bslash;n&quot;
)paren
suffix:semicolon
id|retcode
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|ioctl-&gt;root_only
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
op_logical_or
(paren
id|ioctl-&gt;auth_needed
op_logical_and
op_logical_neg
id|priv-&gt;authenticated
)paren
)paren
(brace
id|retcode
op_assign
op_minus
id|EACCES
suffix:semicolon
)brace
r_else
(brace
id|retcode
op_assign
id|func
c_func
(paren
id|inode
comma
id|filp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
id|err_i1
suffix:colon
id|atomic_dec
c_func
(paren
op_amp
id|dev-&gt;ioctl_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retcode
)paren
id|DRM_DEBUG
c_func
(paren
l_string|&quot;ret = %x&bslash;n&quot;
comma
id|retcode
)paren
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
DECL|variable|drm_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|drm_ioctl
)paren
suffix:semicolon
eof
