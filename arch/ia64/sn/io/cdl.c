multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/pci/bridge.h&gt;
macro_line|#include &quot;asm/sn/ioerror_handling.h&quot;
macro_line|#include &lt;asm/sn/xtalk/xbow.h&gt;
multiline_comment|/* these get called directly in cdl_add_connpt in fops bypass hack */
r_extern
r_int
id|pcibr_attach
c_func
(paren
id|vertex_hdl_t
)paren
suffix:semicolon
r_extern
r_int
id|xbow_attach
c_func
(paren
id|vertex_hdl_t
)paren
suffix:semicolon
r_extern
r_int
id|pic_attach
c_func
(paren
id|vertex_hdl_t
)paren
suffix:semicolon
multiline_comment|/*&n; *    cdl: Connection and Driver List&n; *&n; *&t;We are not porting this to Linux.  Devices are registered via &n; *&t;the normal Linux PCI layer.  This is a very simplified version &n; *&t;of cdl that will allow us to register and call our very own &n; *&t;IO Infrastructure Drivers e.g. pcibr.&n; */
DECL|macro|MAX_SGI_IO_INFRA_DRVR
mdefine_line|#define MAX_SGI_IO_INFRA_DRVR 7
DECL|variable|sgi_infrastructure_drivers
r_static
r_struct
id|cdl
id|sgi_infrastructure_drivers
(braket
id|MAX_SGI_IO_INFRA_DRVR
)braket
op_assign
(brace
(brace
id|XBRIDGE_WIDGET_PART_NUM
comma
id|XBRIDGE_WIDGET_MFGR_NUM
comma
id|pcibr_attach
multiline_comment|/* &amp;pcibr_fops  */
)brace
comma
(brace
id|BRIDGE_WIDGET_PART_NUM
comma
id|BRIDGE_WIDGET_MFGR_NUM
comma
id|pcibr_attach
multiline_comment|/* &amp;pcibr_fops */
)brace
comma
(brace
id|PIC_WIDGET_PART_NUM_BUS0
comma
id|PIC_WIDGET_MFGR_NUM
comma
id|pic_attach
multiline_comment|/* &amp;pic_fops */
)brace
comma
(brace
id|PIC_WIDGET_PART_NUM_BUS1
comma
id|PIC_WIDGET_MFGR_NUM
comma
id|pic_attach
multiline_comment|/* &amp;pic_fops */
)brace
comma
(brace
id|XXBOW_WIDGET_PART_NUM
comma
id|XXBOW_WIDGET_MFGR_NUM
comma
id|xbow_attach
multiline_comment|/* &amp;xbow_fops */
)brace
comma
(brace
id|XBOW_WIDGET_PART_NUM
comma
id|XBOW_WIDGET_MFGR_NUM
comma
id|xbow_attach
multiline_comment|/* &amp;xbow_fops */
)brace
comma
(brace
id|PXBOW_WIDGET_PART_NUM
comma
id|XXBOW_WIDGET_MFGR_NUM
comma
id|xbow_attach
multiline_comment|/* &amp;xbow_fops */
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * cdl_add_connpt: We found a device and it&squot;s connect point.  Call the &n; * attach routine of that driver.&n; *&n; * May need support for pciba registration here ...&n; *&n; * This routine use to create /hw/.id/pci/.../.. that links to &n; * /hw/module/006c06/Pbrick/xtalk/15/pci/&lt;slotnum&gt; .. do we still need &n; * it?  The specified driver attach routine does not reference these &n; * vertices.&n; */
r_int
DECL|function|cdl_add_connpt
id|cdl_add_connpt
c_func
(paren
r_int
id|part_num
comma
r_int
id|mfg_num
comma
id|vertex_hdl_t
id|connpt
comma
r_int
id|drv_flags
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Find the driver entry point and call the attach routine.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_SGI_IO_INFRA_DRVR
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|part_num
op_eq
id|sgi_infrastructure_drivers
(braket
id|i
)braket
dot
id|part_num
)paren
op_logical_and
(paren
id|mfg_num
op_eq
id|sgi_infrastructure_drivers
(braket
id|i
)braket
dot
id|mfg_num
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Call the device attach routines.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|sgi_infrastructure_drivers
(braket
id|i
)braket
dot
id|attach
)paren
(brace
r_return
id|sgi_infrastructure_drivers
(braket
id|i
)braket
dot
id|attach
c_func
(paren
id|connpt
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/* printk(&quot;WARNING: cdl_add_connpt: Driver not found for part_num 0x%x mfg_num 0x%x&bslash;n&quot;, part_num, mfg_num); */
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
