multiline_comment|/* gamma.c -- 3dlabs GMX 2000 driver -*- linux-c -*-&n; * Created: Mon Jan  4 08:58:31 1999 by gareth@valinux.com&n; *&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#ifndef __GAMMA_H__
DECL|macro|__GAMMA_H__
mdefine_line|#define __GAMMA_H__
multiline_comment|/* This remains constant for all DRM template files.&n; */
DECL|macro|DRM
mdefine_line|#define DRM(x) gamma_##x
multiline_comment|/* General customization:&n; */
DECL|macro|__HAVE_MTRR
mdefine_line|#define __HAVE_MTRR&t;&t;&t;1
multiline_comment|/* DMA customization:&n; */
DECL|macro|__HAVE_DMA
mdefine_line|#define __HAVE_DMA&t;&t;&t;1
DECL|macro|__HAVE_OLD_DMA
mdefine_line|#define __HAVE_OLD_DMA&t;&t;&t;1
DECL|macro|__HAVE_PCI_DMA
mdefine_line|#define __HAVE_PCI_DMA&t;&t;&t;1
DECL|macro|__HAVE_MULTIPLE_DMA_QUEUES
mdefine_line|#define __HAVE_MULTIPLE_DMA_QUEUES&t;1
DECL|macro|__HAVE_DMA_WAITQUEUE
mdefine_line|#define __HAVE_DMA_WAITQUEUE&t;&t;1
DECL|macro|__HAVE_DMA_WAITLIST
mdefine_line|#define __HAVE_DMA_WAITLIST&t;&t;1
DECL|macro|__HAVE_DMA_FREELIST
mdefine_line|#define __HAVE_DMA_FREELIST&t;&t;1
DECL|macro|__HAVE_DMA_FLUSH
mdefine_line|#define __HAVE_DMA_FLUSH&t;&t;1
DECL|macro|__HAVE_DMA_SCHEDULE
mdefine_line|#define __HAVE_DMA_SCHEDULE&t;&t;1
DECL|macro|__HAVE_DMA_READY
mdefine_line|#define __HAVE_DMA_READY&t;&t;1
DECL|macro|DRIVER_DMA_READY
mdefine_line|#define DRIVER_DMA_READY() do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;gamma_dma_ready(dev);&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__HAVE_DMA_QUIESCENT
mdefine_line|#define __HAVE_DMA_QUIESCENT&t;&t;1
DECL|macro|DRIVER_DMA_QUIESCENT
mdefine_line|#define DRIVER_DMA_QUIESCENT() do {&t;&t;&t;&t;&t;&bslash;&n;&t;/* FIXME ! */ &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;gamma_dma_quiescent_dual(dev);&t;&t;&t;&t;&t;&bslash;&n;&t;return 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__HAVE_DMA_IRQ
mdefine_line|#define __HAVE_DMA_IRQ&t;&t;&t;1
DECL|macro|__HAVE_DMA_IRQ_BH
mdefine_line|#define __HAVE_DMA_IRQ_BH&t;&t;1
DECL|macro|DRIVER_PREINSTALL
mdefine_line|#define DRIVER_PREINSTALL() do {&t;&t;&t;&t;&t;&bslash;&n;&t;drm_gamma_private_t *dev_priv =&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;(drm_gamma_private_t *)dev-&gt;dev_private;&bslash;&n;&t;GAMMA_WRITE( GAMMA_GCOMMANDMODE,&t;0x00000000 );&t;&t;&bslash;&n;&t;GAMMA_WRITE( GAMMA_GDMACONTROL,&t;&t;0x00000000 );&t;&t;&bslash;&n;} while (0)
DECL|macro|DRIVER_POSTINSTALL
mdefine_line|#define DRIVER_POSTINSTALL() do {&t;&t;&t;&t;&t;&bslash;&n;&t;drm_gamma_private_t *dev_priv =&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;(drm_gamma_private_t *)dev-&gt;dev_private;&bslash;&n;&t;GAMMA_WRITE( GAMMA_GINTENABLE,&t;&t;0x00002001 );&t;&t;&bslash;&n;&t;GAMMA_WRITE( GAMMA_COMMANDINTENABLE,&t;0x00000008 );&t;&t;&bslash;&n;&t;GAMMA_WRITE( GAMMA_GDELAYTIMER,&t;&t;0x00039090 );&t;&t;&bslash;&n;} while (0)
DECL|macro|DRIVER_UNINSTALL
mdefine_line|#define DRIVER_UNINSTALL() do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;drm_gamma_private_t *dev_priv =&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;(drm_gamma_private_t *)dev-&gt;dev_private;&bslash;&n;&t;GAMMA_WRITE( GAMMA_GDELAYTIMER,&t;&t;0x00000000 );&t;&t;&bslash;&n;&t;GAMMA_WRITE( GAMMA_COMMANDINTENABLE,&t;0x00000000 );&t;&t;&bslash;&n;&t;GAMMA_WRITE( GAMMA_GINTENABLE,&t;&t;0x00000000 );&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* __GAMMA_H__ */
eof
