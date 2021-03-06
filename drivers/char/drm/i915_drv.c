multiline_comment|/* i915_drv.c -- i830,i845,i855,i865,i915 driver -*- linux-c -*-&n; */
multiline_comment|/**************************************************************************&n; * &n; * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.&n; * All Rights Reserved.&n; * &n; **************************************************************************/
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;drm.h&quot;
macro_line|#include &quot;i915_drm.h&quot;
macro_line|#include &quot;i915_drv.h&quot;
macro_line|#include &quot;drm_pciids.h&quot;
DECL|function|postinit
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
id|dev-&gt;counters
op_add_assign
l_int|4
suffix:semicolon
id|dev-&gt;types
(braket
l_int|6
)braket
op_assign
id|_DRM_STAT_IRQ
suffix:semicolon
id|dev-&gt;types
(braket
l_int|7
)braket
op_assign
id|_DRM_STAT_PRIMARY
suffix:semicolon
id|dev-&gt;types
(braket
l_int|8
)braket
op_assign
id|_DRM_STAT_SECONDARY
suffix:semicolon
id|dev-&gt;types
(braket
l_int|9
)braket
op_assign
id|_DRM_STAT_DMA
suffix:semicolon
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
id|i915_PCI_IDS
)brace
suffix:semicolon
r_extern
id|drm_ioctl_desc_t
id|i915_ioctls
(braket
)braket
suffix:semicolon
r_extern
r_int
id|i915_max_ioctl
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
id|DRIVER_REQUIRE_AGP
op_or
id|DRIVER_USE_MTRR
op_or
id|DRIVER_HAVE_IRQ
op_or
id|DRIVER_IRQ_SHARED
comma
dot
id|pretakedown
op_assign
id|i915_driver_pretakedown
comma
dot
id|prerelease
op_assign
id|i915_driver_prerelease
comma
dot
id|irq_preinstall
op_assign
id|i915_driver_irq_preinstall
comma
dot
id|irq_postinstall
op_assign
id|i915_driver_irq_postinstall
comma
dot
id|irq_uninstall
op_assign
id|i915_driver_irq_uninstall
comma
dot
id|irq_handler
op_assign
id|i915_driver_irq_handler
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
id|i915_ioctls
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
DECL|function|i915_init
r_static
r_int
id|__init
id|i915_init
c_func
(paren
r_void
)paren
(brace
id|driver.num_ioctls
op_assign
id|i915_max_ioctl
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
DECL|function|i915_exit
r_static
r_void
id|__exit
id|i915_exit
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
DECL|variable|i915_init
id|module_init
c_func
(paren
id|i915_init
)paren
suffix:semicolon
DECL|variable|i915_exit
id|module_exit
c_func
(paren
id|i915_exit
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
