multiline_comment|/*&n; * $Id: ixp4xx.c,v 1.1 2004/05/13 22:21:26 dsaxena Exp $&n; *&n; * drivers/mtd/maps/ixp4xx.c&n; *&n; * MTD Map file for IXP4XX based systems. Please do not make per-board&n; * changes in here. If your board needs special setup, do it in your&n; * platform level code in arch/arm/mach-ixp4xx/board-setup.c&n; *&n; * Original Author: Intel Corporation&n; * Maintainer: Deepak Saxena &lt;dsaxena@mvista.com&gt;&n; *&n; * Copyright (C) 2002 Intel Corporation&n; * Copyright (C) 2003-2004 MontaVista Software, Inc.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/flash.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#ifndef __ARMEB__
DECL|macro|BYTE0
mdefine_line|#define&t;BYTE0(h)&t;((h) &amp; 0xFF)
DECL|macro|BYTE1
mdefine_line|#define&t;BYTE1(h)&t;(((h) &gt;&gt; 8) &amp; 0xFF)
macro_line|#else
DECL|macro|BYTE0
mdefine_line|#define&t;BYTE0(h)&t;(((h) &gt;&gt; 8) &amp; 0xFF)
DECL|macro|BYTE1
mdefine_line|#define&t;BYTE1(h)&t;((h) &amp; 0xFF)
macro_line|#endif
r_static
id|__u16
DECL|function|ixp4xx_read16
id|ixp4xx_read16
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|ofs
)paren
(brace
r_return
op_star
(paren
id|__u16
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|ofs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The IXP4xx expansion bus only allows 16-bit wide acceses&n; * when attached to a 16-bit wide device (such as the 28F128J3A),&n; * so we can&squot;t just memcpy_fromio().&n; */
r_static
r_void
DECL|function|ixp4xx_copy_from
id|ixp4xx_copy_from
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_void
op_star
id|to
comma
r_int
r_int
id|from
comma
id|ssize_t
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
id|u8
op_star
id|dest
op_assign
(paren
id|u8
op_star
)paren
id|to
suffix:semicolon
id|u16
op_star
id|src
op_assign
(paren
id|u16
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|from
)paren
suffix:semicolon
id|u16
id|data
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
(paren
id|len
op_div
l_int|2
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|data
op_assign
id|src
(braket
id|i
)braket
suffix:semicolon
id|dest
(braket
id|i
op_star
l_int|2
)braket
op_assign
id|BYTE0
c_func
(paren
id|data
)paren
suffix:semicolon
id|dest
(braket
id|i
op_star
l_int|2
op_plus
l_int|1
)braket
op_assign
id|BYTE1
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_amp
l_int|1
)paren
id|dest
(braket
id|len
op_minus
l_int|1
)braket
op_assign
id|BYTE0
c_func
(paren
id|src
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ixp4xx_write16
id|ixp4xx_write16
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u16
id|d
comma
r_int
r_int
id|adr
)paren
(brace
op_star
(paren
id|__u16
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|adr
)paren
op_assign
id|d
suffix:semicolon
)brace
DECL|struct|ixp4xx_flash_info
r_struct
id|ixp4xx_flash_info
(brace
DECL|member|mtd
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
DECL|member|map
r_struct
id|map_info
id|map
suffix:semicolon
DECL|member|partitions
r_struct
id|mtd_partition
op_star
id|partitions
suffix:semicolon
DECL|member|res
r_struct
id|resource
op_star
id|res
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|probes
r_static
r_const
r_char
op_star
id|probes
(braket
)braket
op_assign
(brace
l_string|&quot;RedBoot&quot;
comma
l_string|&quot;cmdlinepart&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_static
r_int
DECL|function|ixp4xx_flash_remove
id|ixp4xx_flash_remove
c_func
(paren
r_struct
id|device
op_star
id|_dev
)paren
(brace
r_struct
id|platform_device
op_star
id|dev
op_assign
id|to_platform_device
c_func
(paren
id|_dev
)paren
suffix:semicolon
r_struct
id|flash_platform_data
op_star
id|plat
op_assign
id|dev-&gt;dev.platform_data
suffix:semicolon
r_struct
id|ixp4xx_flash_info
op_star
id|info
op_assign
id|dev_get_drvdata
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This is required for a soft reboot to work.&n;&t; */
id|ixp4xx_write16
c_func
(paren
op_amp
id|info-&gt;map
comma
l_int|0xff
comma
l_int|0x55
op_star
l_int|0x2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;mtd
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|info-&gt;mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|info-&gt;mtd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;map.map_priv_1
)paren
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|info-&gt;map.map_priv_1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;partitions
)paren
id|kfree
c_func
(paren
id|info-&gt;partitions
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;res
)paren
(brace
id|release_resource
c_func
(paren
id|info-&gt;res
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info-&gt;res
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|plat
op_member_access_from_pointer
m_exit
)paren
id|plat
op_member_access_from_pointer
m_exit
(paren
)paren
suffix:semicolon
multiline_comment|/* Disable flash write */
op_star
id|IXP4XX_EXP_CS0
op_and_assign
op_complement
id|IXP4XX_FLASH_WRITABLE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ixp4xx_flash_probe
r_static
r_int
id|ixp4xx_flash_probe
c_func
(paren
r_struct
id|device
op_star
id|_dev
)paren
(brace
r_struct
id|platform_device
op_star
id|dev
op_assign
id|to_platform_device
c_func
(paren
id|_dev
)paren
suffix:semicolon
r_struct
id|flash_platform_data
op_star
id|plat
op_assign
id|dev-&gt;dev.platform_data
suffix:semicolon
r_struct
id|ixp4xx_flash_info
op_star
id|info
suffix:semicolon
r_int
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|plat
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|plat-&gt;init
)paren
(brace
id|err
op_assign
id|plat
op_member_access_from_pointer
id|init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
)brace
id|info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ixp4xx_flash_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|Error
suffix:semicolon
)brace
id|memzero
c_func
(paren
id|info
comma
r_sizeof
(paren
r_struct
id|ixp4xx_flash_info
)paren
)paren
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
op_amp
id|dev-&gt;dev
comma
id|info
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Enable flash write &n;&t; * TODO: Move this out to board specific code&n;&t; */
op_star
id|IXP4XX_EXP_CS0
op_or_assign
id|IXP4XX_FLASH_WRITABLE
suffix:semicolon
multiline_comment|/*&n;&t; * Tell the MTD layer we&squot;re not 1:1 mapped so that it does&n;&t; * not attempt to do a direct access on us.&n;&t; */
id|info-&gt;map.phys
op_assign
id|NO_XIP
suffix:semicolon
id|info-&gt;map.size
op_assign
id|dev-&gt;resource-&gt;end
op_minus
id|dev-&gt;resource-&gt;start
op_plus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * We only support 16-bit accesses for now. If and when&n;&t; * any board use 8-bit access, we&squot;ll fixup the driver to&n;&t; * handle that.&n;&t; */
id|info-&gt;map.buswidth
op_assign
l_int|2
suffix:semicolon
id|info-&gt;map.name
op_assign
id|dev-&gt;dev.bus_id
suffix:semicolon
id|info-&gt;map.read16
op_assign
id|ixp4xx_read16
comma
id|info-&gt;map.write16
op_assign
id|ixp4xx_write16
comma
id|info-&gt;map.copy_from
op_assign
id|ixp4xx_copy_from
comma
id|info-&gt;res
op_assign
id|request_mem_region
c_func
(paren
id|dev-&gt;resource-&gt;start
comma
id|dev-&gt;resource-&gt;end
op_minus
id|dev-&gt;resource-&gt;start
op_plus
l_int|1
comma
l_string|&quot;IXP4XXFlash&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;res
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;IXP4XXFlash: Could not reserve memory region&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|Error
suffix:semicolon
)brace
id|info-&gt;map.map_priv_1
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|dev-&gt;resource-&gt;start
comma
id|dev-&gt;resource-&gt;end
op_minus
id|dev-&gt;resource-&gt;start
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;map.map_priv_1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;IXP4XXFlash: Failed to ioremap region&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|Error
suffix:semicolon
)brace
id|info-&gt;mtd
op_assign
id|do_map_probe
c_func
(paren
id|plat-&gt;map_name
comma
op_amp
id|info-&gt;map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;mtd
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;IXP4XXFlash: map_probe failed&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_goto
id|Error
suffix:semicolon
)brace
id|info-&gt;mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|err
op_assign
id|parse_mtd_partitions
c_func
(paren
id|info-&gt;mtd
comma
id|probes
comma
op_amp
id|info-&gt;partitions
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OG
l_int|0
)paren
(brace
id|err
op_assign
id|add_mtd_partitions
c_func
(paren
id|info-&gt;mtd
comma
id|info-&gt;partitions
comma
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Could not parse partitions&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|err
)paren
r_goto
id|Error
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|Error
suffix:colon
id|ixp4xx_flash_remove
c_func
(paren
id|_dev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|ixp4xx_flash_driver
r_static
r_struct
id|device_driver
id|ixp4xx_flash_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;IXP4XX-Flash&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
comma
dot
id|probe
op_assign
id|ixp4xx_flash_probe
comma
dot
id|remove
op_assign
id|ixp4xx_flash_remove
comma
)brace
suffix:semicolon
DECL|function|ixp4xx_flash_init
r_static
r_int
id|__init
id|ixp4xx_flash_init
c_func
(paren
r_void
)paren
(brace
r_return
id|driver_register
c_func
(paren
op_amp
id|ixp4xx_flash_driver
)paren
suffix:semicolon
)brace
DECL|function|ixp4xx_flash_exit
r_static
r_void
id|__exit
id|ixp4xx_flash_exit
c_func
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|ixp4xx_flash_driver
)paren
suffix:semicolon
)brace
DECL|variable|ixp4xx_flash_init
id|module_init
c_func
(paren
id|ixp4xx_flash_init
)paren
suffix:semicolon
DECL|variable|ixp4xx_flash_exit
id|module_exit
c_func
(paren
id|ixp4xx_flash_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for Intel IXP4xx systems&quot;
)paren
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Deepak Saxena&quot;
)paren
suffix:semicolon
eof
