multiline_comment|/**&n; * &bslash;file radeon_drv.c&n; * ATI Radeon driver&n; *&n; * &bslash;author Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/*&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;drm.h&quot;
macro_line|#include &quot;radeon_drm.h&quot;
macro_line|#include &quot;radeon_drv.h&quot;
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
id|dev-&gt;primary.minor
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
id|radeon_PCI_IDS
)brace
suffix:semicolon
r_extern
id|drm_ioctl_desc_t
id|radeon_ioctls
(braket
)braket
suffix:semicolon
r_extern
r_int
id|radeon_max_ioctl
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
op_or
id|DRIVER_PCI_DMA
op_or
id|DRIVER_SG
op_or
id|DRIVER_HAVE_IRQ
op_or
id|DRIVER_HAVE_DMA
op_or
id|DRIVER_IRQ_SHARED
op_or
id|DRIVER_IRQ_VBL
comma
dot
id|dev_priv_size
op_assign
r_sizeof
(paren
id|drm_radeon_buf_priv_t
)paren
comma
dot
id|preinit
op_assign
id|radeon_driver_preinit
comma
dot
id|postcleanup
op_assign
id|radeon_driver_postcleanup
comma
dot
id|prerelease
op_assign
id|radeon_driver_prerelease
comma
dot
id|pretakedown
op_assign
id|radeon_driver_pretakedown
comma
dot
id|open_helper
op_assign
id|radeon_driver_open_helper
comma
dot
id|vblank_wait
op_assign
id|radeon_driver_vblank_wait
comma
dot
id|irq_preinstall
op_assign
id|radeon_driver_irq_preinstall
comma
dot
id|irq_postinstall
op_assign
id|radeon_driver_irq_postinstall
comma
dot
id|irq_uninstall
op_assign
id|radeon_driver_irq_uninstall
comma
dot
id|irq_handler
op_assign
id|radeon_driver_irq_handler
comma
dot
id|free_filp_priv
op_assign
id|radeon_driver_free_filp_priv
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
id|radeon_ioctls
comma
dot
id|dma_ioctl
op_assign
id|radeon_cp_buffers
comma
dot
id|fops
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
id|drm_open
comma
dot
id|release
op_assign
id|drm_release
comma
dot
id|ioctl
op_assign
id|drm_ioctl
comma
dot
id|mmap
op_assign
id|drm_mmap
comma
dot
id|poll
op_assign
id|drm_poll
comma
dot
id|fasync
op_assign
id|drm_fasync
comma
)brace
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
DECL|function|radeon_init
r_static
r_int
id|__init
id|radeon_init
c_func
(paren
r_void
)paren
(brace
id|driver.num_ioctls
op_assign
id|radeon_max_ioctl
suffix:semicolon
r_return
id|drm_init
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|function|radeon_exit
r_static
r_void
id|__exit
id|radeon_exit
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
DECL|variable|radeon_init
id|module_init
c_func
(paren
id|radeon_init
)paren
suffix:semicolon
DECL|variable|radeon_exit
id|module_exit
c_func
(paren
id|radeon_exit
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
