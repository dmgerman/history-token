multiline_comment|/*&n;   sata_via.c - VIA Serial ATA controllers&n;&n;   Copyright 2003-2004 Red Hat, Inc.  All rights reserved.&n;   Copyright 2003-2004 Jeff Garzik&n;&n;   The contents of this file are subject to the Open&n;   Software License version 1.1 that can be found at&n;   http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n;   by reference.&n;&n;   Alternatively, the contents of this file may be used under the terms&n;   of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n;   in the kernel source COPYING file, in which case the provisions of&n;   the GPL are applicable instead of the above.  If you wish to allow&n;   the use of your version of this file only under the terms of the&n;   GPL and not to allow others to use your version of this file under&n;   the OSL, indicate your decision by deleting the provisions above and&n;   replace them with the notice and other provisions required by the GPL.&n;   If you do not delete the provisions above, a recipient may use your&n;   version of this file under either the OSL or the GPL.&n;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &lt;linux/libata.h&gt;
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME&t;&quot;sata_via&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;0.11&quot;
r_enum
(brace
DECL|enumerator|via_sata
id|via_sata
op_assign
l_int|0
comma
)brace
suffix:semicolon
r_static
r_int
id|svia_init_one
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
suffix:semicolon
r_static
r_void
id|svia_sata_phy_reset
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
r_static
r_void
id|svia_port_disable
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
DECL|variable|in_module_init
r_static
r_int
r_int
id|in_module_init
op_assign
l_int|1
suffix:semicolon
DECL|variable|svia_pci_tbl
r_static
r_struct
id|pci_device_id
id|svia_pci_tbl
(braket
)braket
op_assign
(brace
(brace
l_int|0x1106
comma
l_int|0x3149
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|via_sata
)brace
comma
(brace
)brace
multiline_comment|/* terminate list */
)brace
suffix:semicolon
DECL|variable|svia_pci_driver
r_static
r_struct
id|pci_driver
id|svia_pci_driver
op_assign
(brace
dot
id|name
op_assign
id|DRV_NAME
comma
dot
id|id_table
op_assign
id|svia_pci_tbl
comma
dot
id|probe
op_assign
id|svia_init_one
comma
dot
id|remove
op_assign
id|ata_pci_remove_one
comma
)brace
suffix:semicolon
DECL|variable|svia_sht
r_static
id|Scsi_Host_Template
id|svia_sht
op_assign
(brace
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
id|DRV_NAME
comma
dot
id|queuecommand
op_assign
id|ata_scsi_queuecmd
comma
dot
id|eh_strategy_handler
op_assign
id|ata_scsi_error
comma
dot
id|can_queue
op_assign
id|ATA_DEF_QUEUE
comma
dot
id|this_id
op_assign
id|ATA_SHT_THIS_ID
comma
dot
id|sg_tablesize
op_assign
id|LIBATA_MAX_PRD
comma
dot
id|max_sectors
op_assign
id|ATA_MAX_SECTORS
comma
dot
id|cmd_per_lun
op_assign
id|ATA_SHT_CMD_PER_LUN
comma
dot
id|emulated
op_assign
id|ATA_SHT_EMULATED
comma
dot
id|use_clustering
op_assign
id|ATA_SHT_USE_CLUSTERING
comma
dot
id|proc_name
op_assign
id|DRV_NAME
comma
dot
id|dma_boundary
op_assign
id|ATA_DMA_BOUNDARY
comma
dot
id|slave_configure
op_assign
id|ata_scsi_slave_config
comma
dot
id|bios_param
op_assign
id|ata_std_bios_param
comma
)brace
suffix:semicolon
DECL|variable|svia_sata_ops
r_static
r_struct
id|ata_port_operations
id|svia_sata_ops
op_assign
(brace
dot
id|port_disable
op_assign
id|svia_port_disable
comma
dot
id|tf_load
op_assign
id|ata_tf_load_pio
comma
dot
id|tf_read
op_assign
id|ata_tf_read_pio
comma
dot
id|check_status
op_assign
id|ata_check_status_pio
comma
dot
id|exec_command
op_assign
id|ata_exec_command_pio
comma
dot
id|phy_reset
op_assign
id|svia_sata_phy_reset
comma
dot
id|phy_config
op_assign
id|pata_phy_config
comma
multiline_comment|/* not a typo */
dot
id|bmdma_start
op_assign
id|ata_bmdma_start_pio
comma
dot
id|fill_sg
op_assign
id|ata_fill_sg
comma
dot
id|eng_timeout
op_assign
id|ata_eng_timeout
comma
dot
id|irq_handler
op_assign
id|ata_interrupt
comma
dot
id|port_start
op_assign
id|ata_port_start
comma
dot
id|port_stop
op_assign
id|ata_port_stop
comma
)brace
suffix:semicolon
DECL|variable|svia_port_info
r_static
r_struct
id|ata_port_info
id|svia_port_info
(braket
)braket
op_assign
(brace
multiline_comment|/* via_sata */
(brace
dot
id|sht
op_assign
op_amp
id|svia_sht
comma
dot
id|host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_NO_LEGACY
op_or
id|ATA_FLAG_SRST
comma
dot
id|pio_mask
op_assign
l_int|0x03
comma
multiline_comment|/* pio3-4 */
dot
id|udma_mask
op_assign
l_int|0x7f
comma
multiline_comment|/* udma0-6 ; FIXME */
dot
id|port_ops
op_assign
op_amp
id|svia_sata_ops
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|svia_enable_bits
r_static
r_struct
id|pci_bits
id|svia_enable_bits
(braket
)braket
op_assign
(brace
(brace
l_int|0x40U
comma
l_int|1U
comma
l_int|0x02UL
comma
l_int|0x02UL
)brace
comma
multiline_comment|/* port 0 */
(brace
l_int|0x40U
comma
l_int|1U
comma
l_int|0x01UL
comma
l_int|0x01UL
)brace
comma
multiline_comment|/* port 1 */
)brace
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jeff Garzik&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SCSI low-level driver for VIA SATA controllers&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|svia_pci_tbl
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;svia_sata_phy_reset -&n; *&t;@ap:&n; *&n; *&t;LOCKING:&n; *&n; */
DECL|function|svia_sata_phy_reset
r_static
r_void
id|svia_sata_phy_reset
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pci_test_config_bits
c_func
(paren
id|ap-&gt;host_set-&gt;pdev
comma
op_amp
id|svia_enable_bits
(braket
id|ap-&gt;port_no
)braket
)paren
)paren
(brace
id|ata_port_disable
c_func
(paren
id|ap
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ata%u: port disabled. ignoring.&bslash;n&quot;
comma
id|ap-&gt;id
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ata_port_probe
c_func
(paren
id|ap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ap-&gt;flags
op_amp
id|ATA_FLAG_PORT_DISABLED
)paren
r_return
suffix:semicolon
id|ata_bus_reset
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;svia_port_disable -&n; *&t;@ap:&n; *&n; *&t;LOCKING:&n; *&n; */
DECL|function|svia_port_disable
r_static
r_void
id|svia_port_disable
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
id|ata_port_disable
c_func
(paren
id|ap
)paren
suffix:semicolon
multiline_comment|/* FIXME */
)brace
multiline_comment|/**&n; *&t;svia_init_one -&n; *&t;@pdev:&n; *&t;@ent:&n; *&n; *&t;LOCKING:&n; *&n; *&t;RETURNS:&n; *&n; */
DECL|function|svia_init_one
r_static
r_int
id|svia_init_one
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_static
r_int
id|printed_version
suffix:semicolon
r_struct
id|ata_port_info
op_star
id|port_info
(braket
l_int|1
)braket
suffix:semicolon
r_int
r_int
id|n_ports
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|printed_version
op_increment
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
id|DRV_NAME
l_string|&quot; version &quot;
id|DRV_VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* no hotplugging support (FIXME) */
r_if
c_cond
(paren
op_logical_neg
id|in_module_init
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|port_info
(braket
l_int|0
)braket
op_assign
op_amp
id|svia_port_info
(braket
id|ent-&gt;driver_data
)braket
suffix:semicolon
r_return
id|ata_pci_init_one
c_func
(paren
id|pdev
comma
id|port_info
comma
id|n_ports
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;svia_init -&n; *&n; *&t;LOCKING:&n; *&n; *&t;RETURNS:&n; *&n; */
DECL|function|svia_init
r_static
r_int
id|__init
id|svia_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;pci_module_init&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
id|pci_module_init
c_func
(paren
op_amp
id|svia_pci_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|in_module_init
op_assign
l_int|0
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;done&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;svia_exit -&n; *&n; *&t;LOCKING:&n; *&n; */
DECL|function|svia_exit
r_static
r_void
id|__exit
id|svia_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|svia_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|svia_init
id|module_init
c_func
(paren
id|svia_init
)paren
suffix:semicolon
DECL|variable|svia_exit
id|module_exit
c_func
(paren
id|svia_exit
)paren
suffix:semicolon
eof
