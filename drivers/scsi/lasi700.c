multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/* PARISC LASI driver for the 53c700 chip&n; *&n; * Copyright (C) 2001 by James.Bottomley@HansenPartnership.com&n;**-----------------------------------------------------------------------------&n;**  &n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n; */
multiline_comment|/*&n; * Many thanks to Richard Hirst &lt;rhirst@linuxcare.com&gt; for patiently&n; * debugging this driver on the parisc architecture and suggesting&n; * many improvements and bug fixes.&n; *&n; * Thanks also go to Linuxcare Inc. for providing several PARISC&n; * machines for me to debug the driver on.&n; */
macro_line|#ifndef __hppa__
macro_line|#error &quot;lasi700 only compiles on hppa architecture&quot;
macro_line|#endif
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/parisc-device.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;lasi700.h&quot;
macro_line|#include &quot;53c700.h&quot;
macro_line|#ifdef MODULE
DECL|variable|lasi700
r_char
op_star
id|lasi700
suffix:semicolon
multiline_comment|/* command line from insmod */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;James Bottomley&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;lasi700 SCSI Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|lasi700
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MODULE
DECL|macro|ARG_SEP
mdefine_line|#define ARG_SEP &squot; &squot;
macro_line|#else
DECL|macro|ARG_SEP
mdefine_line|#define ARG_SEP &squot;,&squot;
macro_line|#endif
DECL|variable|opt_base
r_static
r_int
r_int
id|__initdata
id|opt_base
suffix:semicolon
DECL|variable|opt_irq
r_static
r_int
id|__initdata
id|opt_irq
suffix:semicolon
r_static
r_int
id|__init
DECL|function|param_setup
id|param_setup
c_func
(paren
r_char
op_star
id|string
)paren
(brace
r_char
op_star
id|pos
op_assign
id|string
comma
op_star
id|next
suffix:semicolon
r_while
c_loop
(paren
id|pos
op_ne
l_int|NULL
op_logical_and
(paren
id|next
op_assign
id|strchr
c_func
(paren
id|pos
comma
l_char|&squot;:&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|val
op_assign
(paren
r_int
)paren
id|simple_strtoul
c_func
(paren
op_increment
id|next
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|pos
comma
l_string|&quot;addr:&quot;
comma
l_int|5
)paren
)paren
(brace
id|opt_base
op_assign
id|val
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|pos
comma
l_string|&quot;irq:&quot;
comma
l_int|4
)paren
)paren
(brace
id|opt_irq
op_assign
id|val
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pos
op_assign
id|strchr
c_func
(paren
id|pos
comma
id|ARG_SEP
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|pos
op_increment
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifndef MODULE
id|__setup
c_func
(paren
l_string|&quot;lasi700=&quot;
comma
id|param_setup
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|host_tpnt
r_static
id|Scsi_Host_Template
id|__initdata
op_star
id|host_tpnt
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|host_count
r_static
r_int
id|__initdata
id|host_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|lasi700_scsi_tbl
r_static
r_struct
id|parisc_device_id
id|lasi700_scsi_tbl
(braket
)braket
op_assign
(brace
id|LASI700_ID_TABLE
comma
id|LASI710_ID_TABLE
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|parisc
comma
id|lasi700_scsi_tbl
)paren
suffix:semicolon
DECL|variable|lasi700_driver
r_static
r_struct
id|parisc_driver
id|lasi700_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Lasi SCSI&quot;
comma
dot
id|id_table
op_assign
id|lasi700_scsi_tbl
comma
dot
id|probe
op_assign
id|lasi700_driver_callback
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|lasi700_detect
id|lasi700_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
id|host_tpnt
op_assign
id|tpnt
suffix:semicolon
macro_line|#ifdef MODULE
r_if
c_cond
(paren
id|lasi700
)paren
(brace
id|param_setup
c_func
(paren
id|lasi700
)paren
suffix:semicolon
)brace
macro_line|#endif
id|register_parisc_driver
c_func
(paren
op_amp
id|lasi700_driver
)paren
suffix:semicolon
r_return
(paren
id|host_count
op_ne
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|lasi700_driver_callback
id|lasi700_driver_callback
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|base
op_assign
id|dev-&gt;hpa
op_plus
id|LASI_SCSI_CORE_OFFSET
suffix:semicolon
r_char
op_star
id|driver_name
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
r_struct
id|NCR_700_Host_Parameters
op_star
id|hostdata
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|NCR_700_Host_Parameters
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;id.sversion
op_eq
id|LASI_700_SVERSION
)paren
(brace
id|driver_name
op_assign
l_string|&quot;lasi700&quot;
suffix:semicolon
)brace
r_else
(brace
id|driver_name
op_assign
l_string|&quot;lasi710&quot;
suffix:semicolon
)brace
id|snprintf
c_func
(paren
id|dev-&gt;dev.name
comma
r_sizeof
(paren
id|dev-&gt;dev.name
)paren
comma
l_string|&quot;%s&quot;
comma
id|driver_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hostdata
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Failed to allocate host data&bslash;n&quot;
comma
id|driver_name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|memset
c_func
(paren
id|hostdata
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|NCR_700_Host_Parameters
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_mem_region
c_func
(paren
id|base
comma
l_int|64
comma
id|driver_name
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Failed to claim memory region&bslash;n&quot;
comma
id|driver_name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|hostdata
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|hostdata-&gt;base
op_assign
id|base
suffix:semicolon
id|hostdata-&gt;differential
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;id.sversion
op_eq
id|LASI_700_SVERSION
)paren
(brace
id|hostdata-&gt;clock
op_assign
id|LASI700_CLOCK
suffix:semicolon
id|hostdata-&gt;force_le_on_be
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|hostdata-&gt;clock
op_assign
id|LASI710_CLOCK
suffix:semicolon
id|hostdata-&gt;force_le_on_be
op_assign
l_int|0
suffix:semicolon
id|hostdata-&gt;chip710
op_assign
l_int|1
suffix:semicolon
id|hostdata-&gt;dmode_extra
op_assign
id|DMODE_FC2
suffix:semicolon
)brace
id|hostdata-&gt;dev
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|dma_set_mask
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_int|0xffffffffUL
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|host
op_assign
id|NCR_700_detect
c_func
(paren
id|host_tpnt
comma
id|hostdata
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|hostdata
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|host-&gt;base
comma
l_int|64
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|scsi_set_device
c_func
(paren
id|host
comma
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
id|host-&gt;irq
op_assign
id|dev-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|NCR_700_intr
comma
id|SA_SHIRQ
comma
id|driver_name
comma
id|host
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: irq problem, detaching&bslash;n&quot;
comma
id|driver_name
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|host
)paren
suffix:semicolon
id|NCR_700_release
c_func
(paren
id|host
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|host_count
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|lasi700_release
id|lasi700_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_struct
id|D700_Host_Parameters
op_star
id|hostdata
op_assign
(paren
r_struct
id|D700_Host_Parameters
op_star
)paren
id|host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
id|NCR_700_release
c_func
(paren
id|host
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|hostdata
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|host-&gt;irq
comma
id|host
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|host-&gt;base
comma
l_int|64
)paren
suffix:semicolon
id|unregister_parisc_driver
c_func
(paren
op_amp
id|lasi700_driver
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;LASI SCSI 53c700&quot;
comma
dot
id|proc_name
op_assign
l_string|&quot;lasi700&quot;
comma
dot
id|detect
op_assign
id|lasi700_detect
comma
dot
id|release
op_assign
id|lasi700_release
comma
dot
id|this_id
op_assign
l_int|7
comma
)brace
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
eof
