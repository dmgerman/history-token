multiline_comment|/*&n; * sim710.c - Copyright (C) 1999 Richard Hirst &lt;richard@sleepie.demon.co.uk&gt;&n; *&n; *----------------------------------------------------------------------------&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by &n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *----------------------------------------------------------------------------&n; *&n; * MCA card detection code by Trent McNair.&n; * Fixes to not explicitly nul bss data from Xavier Bestel.&n; * Some multiboard fixes from Rolf Eike Beer.&n; * Auto probing of EISA config space from Trevor Hemsley.&n; *&n; * Rewritten to use 53c700.c by James.Bottomley@SteelEye.com&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mca.h&gt;
macro_line|#include &lt;linux/eisa.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;53c700.h&quot;
multiline_comment|/* Must be enough for both EISA and MCA */
DECL|macro|MAX_SLOTS
mdefine_line|#define MAX_SLOTS 8
DECL|variable|id_array
r_static
id|__u8
id|__initdata
id|id_array
(braket
id|MAX_SLOTS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|MAX_SLOTS
op_minus
l_int|1
)braket
op_assign
l_int|7
)brace
suffix:semicolon
DECL|variable|sim710
r_char
op_star
id|sim710
suffix:semicolon
multiline_comment|/* command line passed by insmod */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Richard Hirst&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Simple NCR53C710 driver&quot;
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
id|sim710
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|macro|ARG_SEP
mdefine_line|#define ARG_SEP &squot; &squot;
macro_line|#else
DECL|macro|ARG_SEP
mdefine_line|#define ARG_SEP &squot;,&squot;
macro_line|#endif
id|__init
r_int
DECL|function|param_setup
id|param_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_char
op_star
id|pos
op_assign
id|str
comma
op_star
id|next
suffix:semicolon
r_int
id|slot
op_assign
op_minus
l_int|1
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
l_string|&quot;slot:&quot;
comma
l_int|5
)paren
)paren
(brace
id|slot
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
l_string|&quot;id:&quot;
comma
l_int|3
)paren
)paren
(brace
r_if
c_cond
(paren
id|slot
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sim710: Must specify slot for id parameter&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|slot
OG
id|MAX_SLOTS
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sim710: Illegal slot %d for id %d&bslash;n&quot;
comma
id|slot
comma
id|val
)paren
suffix:semicolon
)brace
r_else
(brace
id|id_array
(braket
id|slot
)braket
op_assign
id|val
suffix:semicolon
)brace
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
id|__setup
c_func
(paren
l_string|&quot;sim710=&quot;
comma
id|param_setup
)paren
suffix:semicolon
DECL|variable|sim710_driver_template
r_static
id|Scsi_Host_Template
id|sim710_driver_template
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;LSI (Symbios) 710 MCA/EISA&quot;
comma
dot
id|proc_name
op_assign
l_string|&quot;sim710&quot;
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
r_static
id|__devinit
r_int
DECL|function|sim710_probe_common
id|sim710_probe_common
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|base_addr
comma
r_int
id|irq
comma
r_int
id|clock
comma
r_int
id|differential
comma
r_int
id|scsi_id
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
op_assign
l_int|NULL
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
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;sim710: %s&bslash;n&quot;
comma
id|dev-&gt;bus_id
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;sim710: irq = %d, clock = %d, base = 0x%lx, scsi_id = %d&bslash;n&quot;
comma
id|irq
comma
id|clock
comma
id|base_addr
comma
id|scsi_id
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
l_string|&quot;sim710: Failed to allocate host data&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
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
id|request_region
c_func
(paren
id|base_addr
comma
l_int|64
comma
l_string|&quot;sim710&quot;
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sim710: Failed to reserve IO region 0x%lx&bslash;n&quot;
comma
id|base_addr
)paren
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
multiline_comment|/* Fill in the three required pieces of hostdata */
id|hostdata-&gt;base
op_assign
id|base_addr
suffix:semicolon
id|hostdata-&gt;differential
op_assign
id|differential
suffix:semicolon
id|hostdata-&gt;clock
op_assign
id|clock
suffix:semicolon
id|hostdata-&gt;chip710
op_assign
l_int|1
suffix:semicolon
id|NCR_700_set_io_mapped
c_func
(paren
id|hostdata
)paren
suffix:semicolon
multiline_comment|/* and register the chip */
r_if
c_cond
(paren
(paren
id|host
op_assign
id|NCR_700_detect
c_func
(paren
op_amp
id|sim710_driver_template
comma
id|hostdata
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sim710: No host detected; card configuration problem?&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_release
suffix:semicolon
)brace
id|host-&gt;irq
op_assign
id|irq
suffix:semicolon
id|host-&gt;this_id
op_assign
id|scsi_id
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
id|NCR_700_intr
comma
id|SA_SHIRQ
comma
l_string|&quot;sim710&quot;
comma
id|host
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sim710: irq problem with %d, detaching&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_goto
id|out_unregister
suffix:semicolon
)brace
id|scsi_add_host
c_func
(paren
id|host
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* XXX handle failure */
id|scsi_scan_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|hostdata-&gt;dev
op_assign
id|dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_unregister
suffix:colon
id|scsi_host_put
c_func
(paren
id|host
)paren
suffix:semicolon
id|out_release
suffix:colon
id|release_region
c_func
(paren
id|host-&gt;base
comma
l_int|64
)paren
suffix:semicolon
id|out_free
suffix:colon
id|kfree
c_func
(paren
id|hostdata
)paren
suffix:semicolon
id|out
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_static
id|__devexit
r_int
DECL|function|sim710_device_remove
id|sim710_device_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
op_assign
id|dev_to_shost
c_func
(paren
id|dev
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
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MCA
multiline_comment|/* CARD ID 01BB and 01BA use the same pos values */
DECL|macro|MCA_01BB_IO_PORTS
mdefine_line|#define MCA_01BB_IO_PORTS { 0x0000, 0x0000, 0x0800, 0x0C00, 0x1000, 0x1400, &bslash;&n;&t;&t;&t;    0x1800, 0x1C00, 0x2000, 0x2400, 0x2800, &bslash;&n;&t;&t;&t;    0x2C00, 0x3000, 0x3400, 0x3800, 0x3C00, &bslash;&n;&t;&t;&t;    0x4000, 0x4400, 0x4800, 0x4C00, 0x5000  }
DECL|macro|MCA_01BB_IRQS
mdefine_line|#define MCA_01BB_IRQS { 3, 5, 11, 14 }
multiline_comment|/* CARD ID 004f */
DECL|macro|MCA_004F_IO_PORTS
mdefine_line|#define MCA_004F_IO_PORTS { 0x0000, 0x0200, 0x0300, 0x0400, 0x0500,  0x0600 }
DECL|macro|MCA_004F_IRQS
mdefine_line|#define MCA_004F_IRQS { 5, 9, 14 }
DECL|variable|sim710_mca_id_table
r_static
r_int
id|sim710_mca_id_table
(braket
)braket
op_assign
(brace
l_int|0x01bb
comma
l_int|0x01ba
comma
l_int|0x004f
comma
l_int|0
)brace
suffix:semicolon
r_static
id|__init
r_int
DECL|function|sim710_mca_probe
id|sim710_mca_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|to_mca_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|slot
op_assign
id|mca_dev-&gt;slot
suffix:semicolon
r_int
id|pos
(braket
l_int|3
)braket
suffix:semicolon
r_int
r_int
id|base
suffix:semicolon
r_int
id|irq_vector
suffix:semicolon
r_int
id|id
op_assign
id|sim710_mca_id_table
(braket
id|mca_dev-&gt;index
)braket
suffix:semicolon
r_static
r_int
id|io_004f_by_pos
(braket
)braket
op_assign
id|MCA_004F_IO_PORTS
suffix:semicolon
r_static
r_int
id|irq_004f_by_pos
(braket
)braket
op_assign
id|MCA_004F_IRQS
suffix:semicolon
r_static
r_int
id|io_01bb_by_pos
(braket
)braket
op_assign
id|MCA_01BB_IO_PORTS
suffix:semicolon
r_static
r_int
id|irq_01bb_by_pos
(braket
)braket
op_assign
id|MCA_01BB_IRQS
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|clock
suffix:semicolon
id|pos
(braket
l_int|0
)braket
op_assign
id|mca_device_read_stored_pos
c_func
(paren
id|mca_dev
comma
l_int|2
)paren
suffix:semicolon
id|pos
(braket
l_int|1
)braket
op_assign
id|mca_device_read_stored_pos
c_func
(paren
id|mca_dev
comma
l_int|3
)paren
suffix:semicolon
id|pos
(braket
l_int|2
)braket
op_assign
id|mca_device_read_stored_pos
c_func
(paren
id|mca_dev
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * 01BB &amp; 01BA port base by bits 7,6,5,4,3,2 in pos[2]&n;&t; *&n;&t; *    000000  &lt;disabled&gt;   001010  0x2800&n;&t; *    000001  &lt;invalid&gt;    001011  0x2C00&n;&t; *    000010  0x0800       001100  0x3000&n;&t; *    000011  0x0C00       001101  0x3400&n;&t; *    000100  0x1000       001110  0x3800&n;&t; *    000101  0x1400       001111  0x3C00&n;&t; *    000110  0x1800       010000  0x4000&n;&t; *    000111  0x1C00       010001  0x4400&n;&t; *    001000  0x2000       010010  0x4800&n;&t; *    001001  0x2400       010011  0x4C00&n;&t; *                         010100  0x5000&n;&t; *&n;&t; * 00F4 port base by bits 3,2,1 in pos[0]&n;&t; *&n;&t; *    000  &lt;disabled&gt;      001    0x200&n;&t; *    010  0x300           011    0x400&n;&t; *    100  0x500           101    0x600&n;&t; *&n;&t; * 01BB &amp; 01BA IRQ is specified in pos[0] bits 7 and 6:&n;&t; *&n;&t; *    00   3               10   11&n;&t; *    01   5               11   14&n;&t; *&n;&t; * 00F4 IRQ specified by bits 6,5,4 in pos[0]&n;&t; *&n;&t; *    100   5              101    9&n;&t; *    110   14&n;&t; */
r_if
c_cond
(paren
id|id
op_eq
l_int|0x01bb
op_logical_or
id|id
op_eq
l_int|0x01ba
)paren
(brace
id|base
op_assign
id|io_01bb_by_pos
(braket
(paren
id|pos
(braket
l_int|2
)braket
op_amp
l_int|0xFC
)paren
op_rshift
l_int|2
)braket
suffix:semicolon
id|irq_vector
op_assign
id|irq_01bb_by_pos
(braket
(paren
(paren
id|pos
(braket
l_int|0
)braket
op_amp
l_int|0xC0
)paren
op_rshift
l_int|6
)paren
)braket
suffix:semicolon
id|clock
op_assign
l_int|50
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
l_int|0x01bb
)paren
id|name
op_assign
l_string|&quot;NCR 3360/3430 SCSI SubSystem&quot;
suffix:semicolon
r_else
id|name
op_assign
l_string|&quot;NCR Dual SIOP SCSI Host Adapter Board&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|id
op_eq
l_int|0x004f
)paren
(brace
id|base
op_assign
id|io_004f_by_pos
(braket
(paren
(paren
id|pos
(braket
l_int|0
)braket
op_amp
l_int|0x0E
)paren
op_rshift
l_int|1
)paren
)braket
suffix:semicolon
id|irq_vector
op_assign
id|irq_004f_by_pos
(braket
(paren
(paren
id|pos
(braket
l_int|0
)braket
op_amp
l_int|0x70
)paren
op_rshift
l_int|4
)paren
op_minus
l_int|4
)braket
suffix:semicolon
id|clock
op_assign
l_int|50
suffix:semicolon
id|name
op_assign
l_string|&quot;NCR 53c710 SCSI Host Adapter Board&quot;
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|mca_device_set_name
c_func
(paren
id|mca_dev
comma
id|name
)paren
suffix:semicolon
id|mca_device_set_claim
c_func
(paren
id|mca_dev
comma
l_int|1
)paren
suffix:semicolon
id|base
op_assign
id|mca_device_transform_ioport
c_func
(paren
id|mca_dev
comma
id|base
)paren
suffix:semicolon
id|irq_vector
op_assign
id|mca_device_transform_irq
c_func
(paren
id|mca_dev
comma
id|irq_vector
)paren
suffix:semicolon
r_return
id|sim710_probe_common
c_func
(paren
id|dev
comma
id|base
comma
id|irq_vector
comma
id|clock
comma
l_int|0
comma
id|id_array
(braket
id|slot
)braket
)paren
suffix:semicolon
)brace
DECL|variable|sim710_mca_driver
r_static
r_struct
id|mca_driver
id|sim710_mca_driver
op_assign
(brace
dot
id|id_table
op_assign
id|sim710_mca_id_table
comma
dot
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sim710&quot;
comma
dot
id|bus
op_assign
op_amp
id|mca_bus_type
comma
dot
id|probe
op_assign
id|sim710_mca_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|sim710_device_remove
)paren
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_MCA */
macro_line|#ifdef CONFIG_EISA
DECL|variable|sim710_eisa_ids
r_static
r_struct
id|eisa_device_id
id|sim710_eisa_ids
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;CPQ4410&quot;
)brace
comma
(brace
l_string|&quot;CPQ4411&quot;
)brace
comma
(brace
l_string|&quot;HWP0C80&quot;
)brace
comma
(brace
l_string|&quot;&quot;
)brace
)brace
suffix:semicolon
r_static
id|__init
r_int
DECL|function|sim710_eisa_probe
id|sim710_eisa_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|eisa_device
op_star
id|edev
op_assign
id|to_eisa_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|io_addr
op_assign
id|edev-&gt;base_addr
suffix:semicolon
r_char
id|eisa_cpq_irqs
(braket
)braket
op_assign
(brace
l_int|11
comma
l_int|14
comma
l_int|15
comma
l_int|10
comma
l_int|9
comma
l_int|0
)brace
suffix:semicolon
r_char
id|eisa_hwp_irqs
(braket
)braket
op_assign
(brace
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|7
comma
l_int|12
comma
l_int|10
comma
l_int|11
comma
l_int|0
)brace
suffix:semicolon
r_char
op_star
id|eisa_irqs
suffix:semicolon
r_int
r_char
id|irq_index
suffix:semicolon
r_int
r_char
id|irq
comma
id|differential
op_assign
l_int|0
comma
id|scsi_id
op_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|edev-&gt;id.sig
comma
l_string|&quot;HWP0C80&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|__u8
id|val
suffix:semicolon
id|eisa_irqs
op_assign
id|eisa_hwp_irqs
suffix:semicolon
id|irq_index
op_assign
(paren
id|inb
c_func
(paren
id|io_addr
op_plus
l_int|0xc85
)paren
op_amp
l_int|0x7
)paren
op_minus
l_int|1
suffix:semicolon
id|val
op_assign
id|inb
c_func
(paren
id|io_addr
op_plus
l_int|0x4
)paren
suffix:semicolon
id|scsi_id
op_assign
id|ffs
c_func
(paren
id|val
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|scsi_id
OG
l_int|7
op_logical_or
(paren
id|val
op_amp
op_complement
(paren
l_int|1
op_lshift
id|scsi_id
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sim710.c, EISA card %s has incorrect scsi_id, setting to 7&bslash;n&quot;
comma
id|dev-&gt;bus_id
)paren
suffix:semicolon
id|scsi_id
op_assign
l_int|7
suffix:semicolon
)brace
)brace
r_else
(brace
id|eisa_irqs
op_assign
id|eisa_cpq_irqs
suffix:semicolon
id|irq_index
op_assign
id|inb
c_func
(paren
id|io_addr
op_plus
l_int|0xc88
)paren
op_amp
l_int|0x07
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq_index
op_ge
id|strlen
c_func
(paren
id|eisa_irqs
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sim710.c: irq nasty&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|irq
op_assign
id|eisa_irqs
(braket
id|irq_index
)braket
suffix:semicolon
r_return
id|sim710_probe_common
c_func
(paren
id|dev
comma
id|io_addr
comma
id|irq
comma
l_int|50
comma
id|differential
comma
id|scsi_id
)paren
suffix:semicolon
)brace
DECL|variable|sim710_eisa_driver
r_struct
id|eisa_driver
id|sim710_eisa_driver
op_assign
(brace
dot
id|id_table
op_assign
id|sim710_eisa_ids
comma
dot
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sim710&quot;
comma
dot
id|probe
op_assign
id|sim710_eisa_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|sim710_device_remove
)paren
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_EISA */
DECL|function|sim710_init
r_static
r_int
id|__init
id|sim710_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
macro_line|#ifdef MODULE
r_if
c_cond
(paren
id|sim710
)paren
id|param_setup
c_func
(paren
id|sim710
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MCA
id|err
op_assign
id|mca_register_driver
c_func
(paren
op_amp
id|sim710_mca_driver
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_EISA
id|err
op_assign
id|eisa_driver_register
c_func
(paren
op_amp
id|sim710_eisa_driver
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* FIXME: what we&squot;d really like to return here is -ENODEV if&n;&t; * no devices have actually been found.  Instead, the err&n;&t; * above actually only reports problems with kobject_register,&n;&t; * so for the moment return success */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sim710_exit
r_static
r_void
id|__exit
id|sim710_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_MCA
r_if
c_cond
(paren
id|MCA_bus
)paren
id|mca_unregister_driver
c_func
(paren
op_amp
id|sim710_mca_driver
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_EISA
id|eisa_driver_unregister
c_func
(paren
op_amp
id|sim710_eisa_driver
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|sim710_init
id|module_init
c_func
(paren
id|sim710_init
)paren
suffix:semicolon
DECL|variable|sim710_exit
id|module_exit
c_func
(paren
id|sim710_exit
)paren
suffix:semicolon
eof
