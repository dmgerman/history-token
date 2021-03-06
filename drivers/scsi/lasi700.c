multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/* PARISC LASI driver for the 53c700 chip&n; *&n; * Copyright (C) 2001 by James.Bottomley@HansenPartnership.com&n;**-----------------------------------------------------------------------------&n;**  &n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n; */
multiline_comment|/*&n; * Many thanks to Richard Hirst &lt;rhirst@linuxcare.com&gt; for patiently&n; * debugging this driver on the parisc architecture and suggesting&n; * many improvements and bug fixes.&n; *&n; * Thanks also go to Linuxcare Inc. for providing several PARISC&n; * machines for me to debug the driver on.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/parisc-device.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_transport.h&gt;
macro_line|#include &lt;scsi/scsi_transport_spi.h&gt;
macro_line|#include &quot;53c700.h&quot;
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
DECL|macro|LASI_700_SVERSION
mdefine_line|#define LASI_700_SVERSION 0x00071
DECL|macro|LASI_710_SVERSION
mdefine_line|#define LASI_710_SVERSION 0x00082
DECL|macro|LASI700_ID_TABLE
mdefine_line|#define LASI700_ID_TABLE {&t;&t;&t;&bslash;&n;&t;.hw_type&t;= HPHW_FIO,&t;&t;&bslash;&n;&t;.sversion&t;= LASI_700_SVERSION,&t;&bslash;&n;&t;.hversion&t;= HVERSION_ANY_ID,&t;&bslash;&n;&t;.hversion_rev&t;= HVERSION_REV_ANY_ID,&t;&bslash;&n;}
DECL|macro|LASI710_ID_TABLE
mdefine_line|#define LASI710_ID_TABLE {&t;&t;&t;&bslash;&n;&t;.hw_type&t;= HPHW_FIO,&t;&t;&bslash;&n;&t;.sversion&t;= LASI_710_SVERSION,&t;&bslash;&n;&t;.hversion&t;= HVERSION_ANY_ID,&t;&bslash;&n;&t;.hversion_rev&t;= HVERSION_REV_ANY_ID,&t;&bslash;&n;}
DECL|macro|LASI700_CLOCK
mdefine_line|#define LASI700_CLOCK&t;25
DECL|macro|LASI710_CLOCK
mdefine_line|#define LASI710_CLOCK&t;40
DECL|macro|LASI_SCSI_CORE_OFFSET
mdefine_line|#define LASI_SCSI_CORE_OFFSET 0x100
DECL|variable|lasi700_ids
r_static
r_struct
id|parisc_device_id
id|lasi700_ids
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
DECL|variable|lasi700_template
r_static
r_struct
id|scsi_host_template
id|lasi700_template
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
id|this_id
op_assign
l_int|7
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|parisc
comma
id|lasi700_ids
)paren
suffix:semicolon
r_static
r_int
id|__init
DECL|function|lasi700_probe
id|lasi700_probe
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
r_struct
id|NCR_700_Host_Parameters
op_star
id|hostdata
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
id|hostdata
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|hostdata
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hostdata
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Failed to allocate host data&bslash;n&quot;
comma
id|dev-&gt;dev.bus_id
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
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
id|DMA_32BIT_MASK
)paren
suffix:semicolon
id|hostdata-&gt;base
op_assign
id|ioremap
c_func
(paren
id|base
comma
l_int|0x100
)paren
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
id|NCR_700_set_mem_mapped
c_func
(paren
id|hostdata
)paren
suffix:semicolon
id|host
op_assign
id|NCR_700_detect
c_func
(paren
op_amp
id|lasi700_template
comma
id|hostdata
comma
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
r_goto
id|out_kfree
suffix:semicolon
id|host-&gt;this_id
op_assign
l_int|7
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
l_string|&quot;lasi700&quot;
comma
id|host
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;lasi700: request_irq failed!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_put_host
suffix:semicolon
)brace
id|dev_set_drvdata
c_func
(paren
op_amp
id|dev-&gt;dev
comma
id|host
)paren
suffix:semicolon
id|scsi_scan_host
c_func
(paren
id|host
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_put_host
suffix:colon
id|scsi_host_put
c_func
(paren
id|host
)paren
suffix:semicolon
id|out_kfree
suffix:colon
id|iounmap
c_func
(paren
id|hostdata-&gt;base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|hostdata
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_static
r_int
id|__exit
DECL|function|lasi700_driver_remove
id|lasi700_driver_remove
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
op_assign
id|dev_get_drvdata
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
r_struct
id|NCR_700_Host_Parameters
op_star
id|hostdata
op_assign
(paren
r_struct
id|NCR_700_Host_Parameters
op_star
)paren
id|host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
id|scsi_remove_host
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
id|free_irq
c_func
(paren
id|host-&gt;irq
comma
id|host
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|hostdata-&gt;base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|hostdata
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|lasi700_ids
comma
dot
id|probe
op_assign
id|lasi700_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|lasi700_driver_remove
)paren
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|lasi700_init
id|lasi700_init
c_func
(paren
r_void
)paren
(brace
r_return
id|register_parisc_driver
c_func
(paren
op_amp
id|lasi700_driver
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|lasi700_exit
id|lasi700_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_parisc_driver
c_func
(paren
op_amp
id|lasi700_driver
)paren
suffix:semicolon
)brace
DECL|variable|lasi700_init
id|module_init
c_func
(paren
id|lasi700_init
)paren
suffix:semicolon
DECL|variable|lasi700_exit
id|module_exit
c_func
(paren
id|lasi700_exit
)paren
suffix:semicolon
eof
