multiline_comment|/* tdfx_drv.c -- tdfx driver -*- linux-c -*-&n; * Created: Thu Oct  7 10:38:32 1999 by faith@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *    Daryll Strauss &lt;daryll@valinux.com&gt;&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;tdfx.h&quot;
macro_line|#include &quot;drmP.h&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;VA Linux Systems Inc.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;tdfx&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;3dfx Banshee/Voodoo3+&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20010216&quot;
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;0
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;0
macro_line|#ifndef PCI_VENDOR_ID_3DFX
DECL|macro|PCI_VENDOR_ID_3DFX
mdefine_line|#define PCI_VENDOR_ID_3DFX 0x121A
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_3DFX_VOODOO5
DECL|macro|PCI_DEVICE_ID_3DFX_VOODOO5
mdefine_line|#define PCI_DEVICE_ID_3DFX_VOODOO5 0x0009
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_3DFX_VOODOO4
DECL|macro|PCI_DEVICE_ID_3DFX_VOODOO4
mdefine_line|#define PCI_DEVICE_ID_3DFX_VOODOO4 0x0007
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_3DFX_VOODOO3_3000 /* Voodoo3 3000 */
DECL|macro|PCI_DEVICE_ID_3DFX_VOODOO3_3000
mdefine_line|#define PCI_DEVICE_ID_3DFX_VOODOO3_3000 0x0005
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_3DFX_VOODOO3_2000 /* Voodoo3 3000 */
DECL|macro|PCI_DEVICE_ID_3DFX_VOODOO3_2000
mdefine_line|#define PCI_DEVICE_ID_3DFX_VOODOO3_2000 0x0004
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_3DFX_BANSHEE
DECL|macro|PCI_DEVICE_ID_3DFX_BANSHEE
mdefine_line|#define PCI_DEVICE_ID_3DFX_BANSHEE 0x0003
macro_line|#endif
r_static
id|drm_pci_list_t
id|DRM
c_func
(paren
id|idlist
)paren
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_3DFX
comma
id|PCI_DEVICE_ID_3DFX_BANSHEE
)brace
comma
(brace
id|PCI_VENDOR_ID_3DFX
comma
id|PCI_DEVICE_ID_3DFX_VOODOO3_2000
)brace
comma
(brace
id|PCI_VENDOR_ID_3DFX
comma
id|PCI_DEVICE_ID_3DFX_VOODOO3_3000
)brace
comma
(brace
id|PCI_VENDOR_ID_3DFX
comma
id|PCI_DEVICE_ID_3DFX_VOODOO4
)brace
comma
(brace
id|PCI_VENDOR_ID_3DFX
comma
id|PCI_DEVICE_ID_3DFX_VOODOO5
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|DRIVER_CARD_LIST
mdefine_line|#define DRIVER_CARD_LIST DRM(idlist)
macro_line|#include &quot;drm_auth.h&quot;
macro_line|#include &quot;drm_bufs.h&quot;
macro_line|#include &quot;drm_context.h&quot;
macro_line|#include &quot;drm_dma.h&quot;
macro_line|#include &quot;drm_drawable.h&quot;
macro_line|#include &quot;drm_drv.h&quot;
macro_line|#include &quot;drm_fops.h&quot;
macro_line|#include &quot;drm_init.h&quot;
macro_line|#include &quot;drm_ioctl.h&quot;
macro_line|#include &quot;drm_lock.h&quot;
macro_line|#include &quot;drm_memory.h&quot;
macro_line|#include &quot;drm_proc.h&quot;
macro_line|#include &quot;drm_vm.h&quot;
macro_line|#include &quot;drm_stub.h&quot;
eof
