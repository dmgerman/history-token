multiline_comment|/*&n;   sata_via.c - VIA Serial ATA controllers&n;&n;   Copyright 2003-2004 Red Hat, Inc.  All rights reserved.&n;   Copyright 2003-2004 Jeff Garzik&n;&n;   The contents of this file are subject to the Open&n;   Software License version 1.1 that can be found at&n;   http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n;   by reference.&n;&n;   Alternatively, the contents of this file may be used under the terms&n;   of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n;   in the kernel source COPYING file, in which case the provisions of&n;   the GPL are applicable instead of the above.  If you wish to allow&n;   the use of your version of this file only under the terms of the&n;   GPL and not to allow others to use your version of this file under&n;   the OSL, indicate your decision by deleting the provisions above and&n;   replace them with the notice and other provisions required by the GPL.&n;   If you do not delete the provisions above, a recipient may use your&n;   version of this file under either the OSL or the GPL.&n;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &lt;linux/libata.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME&t;&quot;sata_via&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;0.20&quot;
r_enum
(brace
DECL|enumerator|via_sata
id|via_sata
op_assign
l_int|0
comma
DECL|enumerator|SATA_CHAN_ENAB
id|SATA_CHAN_ENAB
op_assign
l_int|0x40
comma
DECL|enumerator|SATA_INT_GATE
id|SATA_INT_GATE
op_assign
l_int|0x41
comma
DECL|enumerator|SATA_NATIVE_MODE
id|SATA_NATIVE_MODE
op_assign
l_int|0x42
comma
DECL|enumerator|PORT0
id|PORT0
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
DECL|enumerator|PORT1
id|PORT1
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
DECL|enumerator|ENAB_ALL
id|ENAB_ALL
op_assign
id|PORT0
op_or
id|PORT1
comma
DECL|enumerator|INT_GATE_ALL
id|INT_GATE_ALL
op_assign
id|PORT0
op_or
id|PORT1
comma
DECL|enumerator|NATIVE_MODE_ALL
id|NATIVE_MODE_ALL
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
op_or
(paren
l_int|1
op_lshift
l_int|6
)paren
op_or
(paren
l_int|1
op_lshift
l_int|5
)paren
op_or
(paren
l_int|1
op_lshift
l_int|4
)paren
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
id|u32
id|svia_scr_read
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|sc_reg
)paren
suffix:semicolon
r_static
r_void
id|svia_scr_write
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|sc_reg
comma
id|u32
id|val
)paren
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
id|ata_port_disable
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
id|sata_phy_reset
comma
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
id|scr_read
op_assign
id|svia_scr_read
comma
dot
id|scr_write
op_assign
id|svia_scr_write
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
DECL|function|svia_scr_read
r_static
id|u32
id|svia_scr_read
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|sc_reg
)paren
(brace
r_if
c_cond
(paren
id|sc_reg
OG
id|SCR_CONTROL
)paren
r_return
l_int|0xffffffffU
suffix:semicolon
r_return
id|inl
c_func
(paren
id|ap-&gt;ioaddr.scr_addr
op_plus
(paren
l_int|4
op_star
id|sc_reg
)paren
)paren
suffix:semicolon
)brace
DECL|function|svia_scr_write
r_static
r_void
id|svia_scr_write
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|sc_reg
comma
id|u32
id|val
)paren
(brace
r_if
c_cond
(paren
id|sc_reg
OG
id|SCR_CONTROL
)paren
r_return
suffix:semicolon
id|outl
c_func
(paren
id|val
comma
id|ap-&gt;ioaddr.scr_addr
op_plus
(paren
l_int|4
op_star
id|sc_reg
)paren
)paren
suffix:semicolon
)brace
DECL|variable|svia_bar_sizes
r_static
r_const
r_int
r_int
id|svia_bar_sizes
(braket
)braket
op_assign
(brace
l_int|8
comma
l_int|4
comma
l_int|8
comma
l_int|4
comma
l_int|16
comma
l_int|256
)brace
suffix:semicolon
DECL|function|svia_scr_addr
r_static
r_int
r_int
id|svia_scr_addr
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
l_int|4
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* invalid port */
id|addr
op_and_assign
op_complement
(paren
(paren
l_int|1
op_lshift
l_int|7
)paren
op_or
(paren
l_int|1
op_lshift
l_int|6
)paren
)paren
suffix:semicolon
id|addr
op_or_assign
(paren
(paren
r_int
r_int
)paren
id|port
op_lshift
l_int|6
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
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
r_int
r_int
id|i
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_struct
id|ata_probe_ent
op_star
id|probe_ent
suffix:semicolon
id|u8
id|tmp8
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
id|rc
op_assign
id|pci_enable_device
c_func
(paren
id|pdev
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
id|rc
op_assign
id|pci_request_regions
c_func
(paren
id|pdev
comma
id|DRV_NAME
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|err_out
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
id|ARRAY_SIZE
c_func
(paren
id|svia_bar_sizes
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
id|i
)paren
op_eq
l_int|0
)paren
op_logical_or
(paren
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|i
)paren
OL
id|svia_bar_sizes
(braket
id|i
)braket
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|DRV_NAME
l_string|&quot;(%s): invalid PCI BAR %u (sz 0x%lx, val 0x%lx)&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|pdev
)paren
comma
id|i
comma
id|pci_resource_start
c_func
(paren
id|pdev
comma
id|i
)paren
comma
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|i
)paren
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err_out_regions
suffix:semicolon
)brace
id|rc
op_assign
id|pci_set_dma_mask
c_func
(paren
id|pdev
comma
id|ATA_DMA_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|err_out_regions
suffix:semicolon
id|rc
op_assign
id|pci_set_consistent_dma_mask
c_func
(paren
id|pdev
comma
id|ATA_DMA_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|err_out_regions
suffix:semicolon
id|probe_ent
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|probe_ent
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|probe_ent
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|DRV_NAME
l_string|&quot;(%s): out of memory&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|pdev
)paren
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_out_regions
suffix:semicolon
)brace
id|memset
c_func
(paren
id|probe_ent
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|probe_ent
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|probe_ent-&gt;node
)paren
suffix:semicolon
id|probe_ent-&gt;pdev
op_assign
id|pdev
suffix:semicolon
id|probe_ent-&gt;sht
op_assign
op_amp
id|svia_sht
suffix:semicolon
id|probe_ent-&gt;host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_SRST
op_or
id|ATA_FLAG_NO_LEGACY
suffix:semicolon
id|probe_ent-&gt;port_ops
op_assign
op_amp
id|svia_sata_ops
suffix:semicolon
id|probe_ent-&gt;n_ports
op_assign
l_int|2
suffix:semicolon
id|probe_ent-&gt;irq
op_assign
id|pdev-&gt;irq
suffix:semicolon
id|probe_ent-&gt;irq_flags
op_assign
id|SA_SHIRQ
suffix:semicolon
id|probe_ent-&gt;pio_mask
op_assign
l_int|0x1f
suffix:semicolon
id|probe_ent-&gt;udma_mask
op_assign
l_int|0x7f
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|0
)braket
dot
id|cmd_addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
id|ata_std_ports
c_func
(paren
op_amp
id|probe_ent-&gt;port
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|0
)braket
dot
id|altstatus_addr
op_assign
id|probe_ent-&gt;port
(braket
l_int|0
)braket
dot
id|ctl_addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|1
)paren
op_or
id|ATA_PCI_CTL_OFS
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|0
)braket
dot
id|bmdma_addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|4
)paren
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|0
)braket
dot
id|scr_addr
op_assign
id|svia_scr_addr
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|5
)paren
comma
l_int|0
)paren
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|1
)braket
dot
id|cmd_addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|2
)paren
suffix:semicolon
id|ata_std_ports
c_func
(paren
op_amp
id|probe_ent-&gt;port
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|1
)braket
dot
id|altstatus_addr
op_assign
id|probe_ent-&gt;port
(braket
l_int|1
)braket
dot
id|ctl_addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|3
)paren
op_or
id|ATA_PCI_CTL_OFS
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|1
)braket
dot
id|bmdma_addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|4
)paren
op_plus
l_int|8
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|1
)braket
dot
id|scr_addr
op_assign
id|svia_scr_addr
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|5
)paren
comma
l_int|1
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|tmp8
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|DRV_NAME
l_string|&quot;(%s): routed to hard irq line %d&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|pdev
)paren
comma
(paren
r_int
)paren
(paren
id|tmp8
op_amp
l_int|0xf0
)paren
op_eq
l_int|0xf0
ques
c_cond
l_int|0
suffix:colon
id|tmp8
op_amp
l_int|0x0f
)paren
suffix:semicolon
multiline_comment|/* make sure SATA channels are enabled */
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
id|SATA_CHAN_ENAB
comma
op_amp
id|tmp8
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp8
op_amp
id|ENAB_ALL
)paren
op_ne
id|ENAB_ALL
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|DRV_NAME
l_string|&quot;(%s): enabling SATA channels (0x%x)&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|pdev
)paren
comma
(paren
r_int
)paren
id|tmp8
)paren
suffix:semicolon
id|tmp8
op_or_assign
id|ENAB_ALL
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
id|SATA_CHAN_ENAB
comma
id|tmp8
)paren
suffix:semicolon
)brace
multiline_comment|/* make sure interrupts for each channel sent to us */
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
id|SATA_INT_GATE
comma
op_amp
id|tmp8
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp8
op_amp
id|INT_GATE_ALL
)paren
op_ne
id|INT_GATE_ALL
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|DRV_NAME
l_string|&quot;(%s): enabling SATA channel interrupts (0x%x)&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|pdev
)paren
comma
(paren
r_int
)paren
id|tmp8
)paren
suffix:semicolon
id|tmp8
op_or_assign
id|INT_GATE_ALL
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
id|SATA_INT_GATE
comma
id|tmp8
)paren
suffix:semicolon
)brace
multiline_comment|/* make sure native mode is enabled */
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
id|SATA_NATIVE_MODE
comma
op_amp
id|tmp8
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp8
op_amp
id|NATIVE_MODE_ALL
)paren
op_ne
id|NATIVE_MODE_ALL
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|DRV_NAME
l_string|&quot;(%s): enabling SATA channel native mode (0x%x)&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|pdev
)paren
comma
(paren
r_int
)paren
id|tmp8
)paren
suffix:semicolon
id|tmp8
op_or_assign
id|NATIVE_MODE_ALL
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
id|SATA_NATIVE_MODE
comma
id|tmp8
)paren
suffix:semicolon
)brace
id|pci_set_master
c_func
(paren
id|pdev
)paren
suffix:semicolon
multiline_comment|/* FIXME: check ata_device_add return value */
id|ata_device_add
c_func
(paren
id|probe_ent
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|probe_ent
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_regions
suffix:colon
id|pci_release_regions
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|err_out
suffix:colon
id|pci_disable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_return
id|rc
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
r_return
id|pci_module_init
c_func
(paren
op_amp
id|svia_pci_driver
)paren
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
