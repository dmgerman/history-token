multiline_comment|/* sis.c -- sis driver -*- linux-c -*-&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;sis_drm.h&quot;
macro_line|#include &quot;sis_drv.h&quot;
macro_line|#include &quot;drm_pciids.h&quot;
DECL|function|postinit
r_static
r_int
id|postinit
c_func
(paren
r_struct
id|drm_device
op_star
id|dev
comma
r_int
r_int
id|flags
)paren
(brace
id|DRM_INFO
c_func
(paren
l_string|&quot;Initialized %s %d.%d.%d %s on minor %d: %s&bslash;n&quot;
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
comma
id|dev-&gt;minor
comma
id|pci_pretty_name
c_func
(paren
id|dev-&gt;pdev
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|version
r_static
r_int
id|version
c_func
(paren
id|drm_version_t
op_star
id|version
)paren
(brace
r_int
id|len
suffix:semicolon
id|version-&gt;version_major
op_assign
id|DRIVER_MAJOR
suffix:semicolon
id|version-&gt;version_minor
op_assign
id|DRIVER_MINOR
suffix:semicolon
id|version-&gt;version_patchlevel
op_assign
id|DRIVER_PATCHLEVEL
suffix:semicolon
id|DRM_COPY
c_func
(paren
id|version-&gt;name
comma
id|DRIVER_NAME
)paren
suffix:semicolon
id|DRM_COPY
c_func
(paren
id|version-&gt;date
comma
id|DRIVER_DATE
)paren
suffix:semicolon
id|DRM_COPY
c_func
(paren
id|version-&gt;desc
comma
id|DRIVER_DESC
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pciidlist
r_static
r_struct
id|pci_device_id
id|pciidlist
(braket
)braket
op_assign
(brace
id|sisdrv_PCI_IDS
)brace
suffix:semicolon
DECL|variable|ioctls
r_static
id|drm_ioctl_desc_t
id|ioctls
(braket
)braket
op_assign
(brace
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_SIS_FB_ALLOC
)paren
)braket
op_assign
(brace
id|sis_fb_alloc
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
id|DRM_SIS_FB_FREE
)paren
)braket
op_assign
(brace
id|sis_fb_free
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
id|DRM_SIS_AGP_INIT
)paren
)braket
op_assign
(brace
id|sis_ioctl_agp_init
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
id|DRM_SIS_AGP_ALLOC
)paren
)braket
op_assign
(brace
id|sis_ioctl_agp_alloc
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
id|DRM_SIS_AGP_FREE
)paren
)braket
op_assign
(brace
id|sis_ioctl_agp_free
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
id|DRM_SIS_FB_INIT
)paren
)braket
op_assign
(brace
id|sis_fb_init
comma
l_int|1
comma
l_int|1
)brace
)brace
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|drm_driver
id|driver
op_assign
(brace
dot
id|driver_features
op_assign
id|DRIVER_USE_AGP
op_or
id|DRIVER_USE_MTRR
comma
dot
id|context_ctor
op_assign
id|sis_init_context
comma
dot
id|context_dtor
op_assign
id|sis_final_context
comma
dot
id|reclaim_buffers
op_assign
id|drm_core_reclaim_buffers
comma
dot
id|get_map_ofs
op_assign
id|drm_core_get_map_ofs
comma
dot
id|get_reg_ofs
op_assign
id|drm_core_get_reg_ofs
comma
dot
id|postinit
op_assign
id|postinit
comma
dot
id|version
op_assign
id|version
comma
dot
id|ioctls
op_assign
id|ioctls
comma
dot
id|num_ioctls
op_assign
id|DRM_ARRAY_SIZE
c_func
(paren
id|ioctls
)paren
comma
dot
id|pci_driver
op_assign
(brace
dot
id|name
op_assign
id|DRIVER_NAME
comma
dot
id|id_table
op_assign
id|pciidlist
comma
)brace
)brace
suffix:semicolon
DECL|function|sis_init
r_static
r_int
id|__init
id|sis_init
c_func
(paren
r_void
)paren
(brace
r_return
id|drm_init
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|function|sis_exit
r_static
r_void
id|__exit
id|sis_exit
c_func
(paren
r_void
)paren
(brace
id|drm_exit
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|sis_init
id|module_init
c_func
(paren
id|sis_init
)paren
suffix:semicolon
DECL|variable|sis_exit
id|module_exit
c_func
(paren
id|sis_exit
)paren
suffix:semicolon
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
eof
