multiline_comment|/* gamma_drv.h -- Private header for 3dlabs GMX 2000 driver -*- linux-c -*-&n; * Created: Mon Jan  4 10:05:05 1999 by faith@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *&n; */
macro_line|#ifndef _GAMMA_DRV_H_
DECL|macro|_GAMMA_DRV_H_
mdefine_line|#define _GAMMA_DRV_H_
DECL|struct|drm_gamma_private
r_typedef
r_struct
id|drm_gamma_private
(brace
DECL|member|sarea_priv
id|drm_gamma_sarea_t
op_star
id|sarea_priv
suffix:semicolon
DECL|member|sarea
id|drm_map_t
op_star
id|sarea
suffix:semicolon
DECL|member|buffers
id|drm_map_t
op_star
id|buffers
suffix:semicolon
DECL|member|mmio0
id|drm_map_t
op_star
id|mmio0
suffix:semicolon
DECL|member|mmio1
id|drm_map_t
op_star
id|mmio1
suffix:semicolon
DECL|member|mmio2
id|drm_map_t
op_star
id|mmio2
suffix:semicolon
DECL|member|mmio3
id|drm_map_t
op_star
id|mmio3
suffix:semicolon
DECL|typedef|drm_gamma_private_t
)brace
id|drm_gamma_private_t
suffix:semicolon
DECL|macro|LOCK_TEST_WITH_RETURN
mdefine_line|#define LOCK_TEST_WITH_RETURN( dev )&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( !_DRM_LOCK_IS_HELD( dev-&gt;lock.hw_lock-&gt;lock ) ||&t;&t;&bslash;&n;&t;     dev-&gt;lock.pid != current-&gt;pid ) {&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_ERROR( &quot;%s called without lock held&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;&t;   __FUNCTION__ );&t;&t;&t;&t;&bslash;&n;&t;&t;return -EINVAL;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* gamma_dma.c */
r_extern
r_int
id|gamma_dma_init
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
id|gamma_dma_copy
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
id|gamma_dma_ready
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|gamma_dma_quiescent_single
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|gamma_dma_quiescent_dual
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* gamma_dma.c */
r_extern
r_int
id|gamma_dma_schedule
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
id|gamma_dma
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
id|gamma_find_devices
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|gamma_found
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|GLINT_DRI_BUF_COUNT
mdefine_line|#define GLINT_DRI_BUF_COUNT 256
DECL|macro|GAMMA_OFF
mdefine_line|#define GAMMA_OFF(reg)&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;((reg &lt; 0x1000)&t;&t;&t;&t;&t;&t;   &bslash;&n;&t; ? reg&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t; : ((reg &lt; 0x10000)&t;&t;&t;&t;&t;   &bslash;&n;&t;    ? (reg - 0x1000)&t;&t;&t;&t;&t;   &bslash;&n;&t;    : ((reg &lt; 0x11000)&t;&t;&t;&t;&t;   &bslash;&n;&t;       ? (reg - 0x10000)&t;&t;&t;&t;   &bslash;&n;&t;       : (reg - 0x11000))))
DECL|macro|GAMMA_BASE
mdefine_line|#define GAMMA_BASE(reg)&t; ((unsigned long)&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;  ((reg &lt; 0x1000)    ? dev_priv-&gt;mmio0-&gt;handle :     &bslash;&n;&t;&t;&t;   ((reg &lt; 0x10000)  ? dev_priv-&gt;mmio1-&gt;handle :     &bslash;&n;&t;&t;&t;    ((reg &lt; 0x11000) ? dev_priv-&gt;mmio2-&gt;handle :     &bslash;&n;&t;&t;&t;&t;&t;       dev_priv-&gt;mmio3-&gt;handle))))
DECL|macro|GAMMA_ADDR
mdefine_line|#define GAMMA_ADDR(reg)&t; (GAMMA_BASE(reg) + GAMMA_OFF(reg))
DECL|macro|GAMMA_DEREF
mdefine_line|#define GAMMA_DEREF(reg) *(__volatile__ int *)GAMMA_ADDR(reg)
DECL|macro|GAMMA_READ
mdefine_line|#define GAMMA_READ(reg)&t; GAMMA_DEREF(reg)
DECL|macro|GAMMA_WRITE
mdefine_line|#define GAMMA_WRITE(reg,val) do { GAMMA_DEREF(reg) = val; } while (0)
DECL|macro|GAMMA_BROADCASTMASK
mdefine_line|#define GAMMA_BROADCASTMASK    0x9378
DECL|macro|GAMMA_COMMANDINTENABLE
mdefine_line|#define GAMMA_COMMANDINTENABLE 0x0c48
DECL|macro|GAMMA_DMAADDRESS
mdefine_line|#define GAMMA_DMAADDRESS       0x0028
DECL|macro|GAMMA_DMACOUNT
mdefine_line|#define GAMMA_DMACOUNT&t;       0x0030
DECL|macro|GAMMA_FILTERMODE
mdefine_line|#define GAMMA_FILTERMODE       0x8c00
DECL|macro|GAMMA_GCOMMANDINTFLAGS
mdefine_line|#define GAMMA_GCOMMANDINTFLAGS 0x0c50
DECL|macro|GAMMA_GCOMMANDMODE
mdefine_line|#define GAMMA_GCOMMANDMODE     0x0c40
DECL|macro|GAMMA_QUEUED_DMA_MODE
mdefine_line|#define&t;&t;GAMMA_QUEUED_DMA_MODE&t;&t;1&lt;&lt;1
DECL|macro|GAMMA_GCOMMANDSTATUS
mdefine_line|#define GAMMA_GCOMMANDSTATUS   0x0c60
DECL|macro|GAMMA_GDELAYTIMER
mdefine_line|#define GAMMA_GDELAYTIMER      0x0c38
DECL|macro|GAMMA_GDMACONTROL
mdefine_line|#define GAMMA_GDMACONTROL      0x0060
DECL|macro|GAMMA_USE_AGP
mdefine_line|#define &t;GAMMA_USE_AGP&t;&t;&t;1&lt;&lt;1
DECL|macro|GAMMA_GINTENABLE
mdefine_line|#define GAMMA_GINTENABLE       0x0808
DECL|macro|GAMMA_GINTFLAGS
mdefine_line|#define GAMMA_GINTFLAGS&t;       0x0810
DECL|macro|GAMMA_INFIFOSPACE
mdefine_line|#define GAMMA_INFIFOSPACE      0x0018
DECL|macro|GAMMA_OUTFIFOWORDS
mdefine_line|#define GAMMA_OUTFIFOWORDS     0x0020
DECL|macro|GAMMA_OUTPUTFIFO
mdefine_line|#define GAMMA_OUTPUTFIFO       0x2000
DECL|macro|GAMMA_SYNC
mdefine_line|#define GAMMA_SYNC&t;       0x8c40
DECL|macro|GAMMA_SYNC_TAG
mdefine_line|#define GAMMA_SYNC_TAG&t;       0x0188
DECL|macro|GAMMA_PAGETABLEADDR
mdefine_line|#define GAMMA_PAGETABLEADDR    0x0C00
DECL|macro|GAMMA_PAGETABLELENGTH
mdefine_line|#define GAMMA_PAGETABLELENGTH  0x0C08
DECL|macro|GAMMA_PASSTHROUGH
mdefine_line|#define GAMMA_PASSTHROUGH&t;0x1FE
DECL|macro|GAMMA_DMAADDRTAG
mdefine_line|#define GAMMA_DMAADDRTAG&t;0x530
DECL|macro|GAMMA_DMACOUNTTAG
mdefine_line|#define GAMMA_DMACOUNTTAG&t;0x531
DECL|macro|GAMMA_COMMANDINTTAG
mdefine_line|#define GAMMA_COMMANDINTTAG&t;0x532
macro_line|#endif
eof
