multiline_comment|/*&n; *  sata_nv.c - NVIDIA nForce SATA&n; *&n; *  Copyright 2004 NVIDIA Corp.  All rights reserved.&n; *  Copyright 2004 Andrew Chew&n; *&n; *  The contents of this file are subject to the Open&n; *  Software License version 1.1 that can be found at&n; *  http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n; *  by reference.&n; *&n; *  Alternatively, the contents of this file may be used under the terms&n; *  of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n; *  in the kernel source COPYING file, in which case the provisions of&n; *  the GPL are applicable instead of the above.  If you wish to allow&n; *  the use of your version of this file only under the terms of the&n; *  GPL and not to allow others to use your version of this file under&n; *  the OSL, indicate your decision by deleting the provisions above and&n; *  replace them with the notice and other provisions required by the GPL.&n; *  If you do not delete the provisions above, a recipient may use your&n; *  version of this file under either the OSL or the GPL.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;linux/libata.h&gt;
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME&t;&t;&t;&quot;sata_nv&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&t;&t;&quot;0.01&quot;
DECL|macro|NV_PORTS
mdefine_line|#define NV_PORTS&t;&t;&t;2
DECL|macro|NV_PIO_MASK
mdefine_line|#define NV_PIO_MASK&t;&t;&t;0x1f
DECL|macro|NV_UDMA_MASK
mdefine_line|#define NV_UDMA_MASK&t;&t;&t;0x7f
DECL|macro|NV_PORT0_BMDMA_REG_OFFSET
mdefine_line|#define NV_PORT0_BMDMA_REG_OFFSET&t;0x00
DECL|macro|NV_PORT1_BMDMA_REG_OFFSET
mdefine_line|#define NV_PORT1_BMDMA_REG_OFFSET&t;0x08
DECL|macro|NV_PORT0_SCR_REG_OFFSET
mdefine_line|#define NV_PORT0_SCR_REG_OFFSET&t;&t;0x00
DECL|macro|NV_PORT1_SCR_REG_OFFSET
mdefine_line|#define NV_PORT1_SCR_REG_OFFSET&t;&t;0x40
DECL|macro|NV_INT_STATUS
mdefine_line|#define NV_INT_STATUS&t;&t;&t;0x10
DECL|macro|NV_INT_STATUS_PDEV_INT
mdefine_line|#define NV_INT_STATUS_PDEV_INT&t;&t;0x01
DECL|macro|NV_INT_STATUS_PDEV_PM
mdefine_line|#define NV_INT_STATUS_PDEV_PM&t;&t;0x02
DECL|macro|NV_INT_STATUS_PDEV_ADDED
mdefine_line|#define NV_INT_STATUS_PDEV_ADDED&t;0x04
DECL|macro|NV_INT_STATUS_PDEV_REMOVED
mdefine_line|#define NV_INT_STATUS_PDEV_REMOVED&t;0x08
DECL|macro|NV_INT_STATUS_SDEV_INT
mdefine_line|#define NV_INT_STATUS_SDEV_INT&t;&t;0x10
DECL|macro|NV_INT_STATUS_SDEV_PM
mdefine_line|#define NV_INT_STATUS_SDEV_PM&t;&t;0x20
DECL|macro|NV_INT_STATUS_SDEV_ADDED
mdefine_line|#define NV_INT_STATUS_SDEV_ADDED&t;0x40
DECL|macro|NV_INT_STATUS_SDEV_REMOVED
mdefine_line|#define NV_INT_STATUS_SDEV_REMOVED&t;0x80
DECL|macro|NV_INT_STATUS_PDEV_HOTPLUG
mdefine_line|#define NV_INT_STATUS_PDEV_HOTPLUG&t;(NV_INT_STATUS_PDEV_ADDED | &bslash;&n;&t;&t;&t;&t;&t;NV_INT_STATUS_PDEV_REMOVED)
DECL|macro|NV_INT_STATUS_SDEV_HOTPLUG
mdefine_line|#define NV_INT_STATUS_SDEV_HOTPLUG&t;(NV_INT_STATUS_SDEV_ADDED | &bslash;&n;&t;&t;&t;&t;&t;NV_INT_STATUS_SDEV_REMOVED)
DECL|macro|NV_INT_STATUS_HOTPLUG
mdefine_line|#define NV_INT_STATUS_HOTPLUG&t;&t;(NV_INT_STATUS_PDEV_HOTPLUG | &bslash;&n;&t;&t;&t;&t;&t;NV_INT_STATUS_SDEV_HOTPLUG)
DECL|macro|NV_INT_ENABLE
mdefine_line|#define NV_INT_ENABLE&t;&t;&t;0x11
DECL|macro|NV_INT_ENABLE_PDEV_MASK
mdefine_line|#define NV_INT_ENABLE_PDEV_MASK&t;&t;0x01
DECL|macro|NV_INT_ENABLE_PDEV_PM
mdefine_line|#define NV_INT_ENABLE_PDEV_PM&t;&t;0x02
DECL|macro|NV_INT_ENABLE_PDEV_ADDED
mdefine_line|#define NV_INT_ENABLE_PDEV_ADDED&t;0x04
DECL|macro|NV_INT_ENABLE_PDEV_REMOVED
mdefine_line|#define NV_INT_ENABLE_PDEV_REMOVED&t;0x08
DECL|macro|NV_INT_ENABLE_SDEV_MASK
mdefine_line|#define NV_INT_ENABLE_SDEV_MASK&t;&t;0x10
DECL|macro|NV_INT_ENABLE_SDEV_PM
mdefine_line|#define NV_INT_ENABLE_SDEV_PM&t;&t;0x20
DECL|macro|NV_INT_ENABLE_SDEV_ADDED
mdefine_line|#define NV_INT_ENABLE_SDEV_ADDED&t;0x40
DECL|macro|NV_INT_ENABLE_SDEV_REMOVED
mdefine_line|#define NV_INT_ENABLE_SDEV_REMOVED&t;0x80
DECL|macro|NV_INT_ENABLE_PDEV_HOTPLUG
mdefine_line|#define NV_INT_ENABLE_PDEV_HOTPLUG&t;(NV_INT_ENABLE_PDEV_ADDED | &bslash;&n;&t;&t;&t;&t;&t;NV_INT_ENABLE_PDEV_REMOVED)
DECL|macro|NV_INT_ENABLE_SDEV_HOTPLUG
mdefine_line|#define NV_INT_ENABLE_SDEV_HOTPLUG&t;(NV_INT_ENABLE_SDEV_ADDED | &bslash;&n;&t;&t;&t;&t;&t;NV_INT_ENABLE_SDEV_REMOVED)
DECL|macro|NV_INT_ENABLE_HOTPLUG
mdefine_line|#define NV_INT_ENABLE_HOTPLUG&t;&t;(NV_INT_ENABLE_PDEV_HOTPLUG | &bslash;&n;&t;&t;&t;&t;&t;NV_INT_ENABLE_SDEV_HOTPLUG)
DECL|macro|NV_INT_CONFIG
mdefine_line|#define NV_INT_CONFIG&t;&t;&t;0x12
DECL|macro|NV_INT_CONFIG_METHD
mdefine_line|#define NV_INT_CONFIG_METHD&t;&t;0x01 
singleline_comment|// 0 = INT, 1 = SMI
r_static
r_int
id|nv_init_one
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
id|irqreturn_t
id|nv_interrupt
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_instance
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
id|u32
id|nv_scr_read
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
id|nv_scr_write
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
r_static
r_void
id|nv_host_stop
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
suffix:semicolon
DECL|variable|nv_pci_tbl
r_static
r_struct
id|pci_device_id
id|nv_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_NVIDIA
comma
id|PCI_DEVICE_ID_NVIDIA_NFORCE2S_SATA
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
id|PCI_VENDOR_ID_NVIDIA
comma
id|PCI_DEVICE_ID_NVIDIA_NFORCE3S_SATA
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
id|PCI_VENDOR_ID_NVIDIA
comma
id|PCI_DEVICE_ID_NVIDIA_NFORCE3S_SATA2
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
id|PCI_VENDOR_ID_NVIDIA
comma
id|PCI_DEVICE_ID_NVIDIA_NFORCE_CK804_SATA
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
id|PCI_VENDOR_ID_NVIDIA
comma
id|PCI_DEVICE_ID_NVIDIA_NFORCE_CK804_SATA2
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
id|PCI_VENDOR_ID_NVIDIA
comma
id|PCI_DEVICE_ID_NVIDIA_NFORCE_MCP04_SATA
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
id|PCI_VENDOR_ID_NVIDIA
comma
id|PCI_DEVICE_ID_NVIDIA_NFORCE_MCP04_SATA2
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
l_int|0
comma
)brace
multiline_comment|/* terminate list */
)brace
suffix:semicolon
DECL|variable|nv_pci_driver
r_static
r_struct
id|pci_driver
id|nv_pci_driver
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
id|nv_pci_tbl
comma
dot
id|probe
op_assign
id|nv_init_one
comma
dot
id|remove
op_assign
id|ata_pci_remove_one
comma
)brace
suffix:semicolon
DECL|variable|nv_sht
r_static
id|Scsi_Host_Template
id|nv_sht
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
id|ATA_MAX_PRD
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
DECL|variable|nv_ops
r_static
r_struct
id|ata_port_operations
id|nv_ops
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
id|exec_command
op_assign
id|ata_exec_command_pio
comma
dot
id|check_status
op_assign
id|ata_check_status_pio
comma
dot
id|phy_reset
op_assign
id|sata_phy_reset
comma
dot
id|bmdma_setup
op_assign
id|ata_bmdma_setup_pio
comma
dot
id|bmdma_start
op_assign
id|ata_bmdma_start_pio
comma
dot
id|qc_prep
op_assign
id|ata_qc_prep
comma
dot
id|eng_timeout
op_assign
id|ata_eng_timeout
comma
dot
id|irq_handler
op_assign
id|nv_interrupt
comma
dot
id|scr_read
op_assign
id|nv_scr_read
comma
dot
id|scr_write
op_assign
id|nv_scr_write
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
dot
id|host_stop
op_assign
id|nv_host_stop
comma
)brace
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;NVIDIA&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;low-level driver for NVIDIA nForce SATA controller&quot;
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
id|nv_pci_tbl
)paren
suffix:semicolon
DECL|function|nv_interrupt
id|irqreturn_t
id|nv_interrupt
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_instance
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|ata_host_set
op_star
id|host_set
op_assign
id|dev_instance
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
r_int
id|handled
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|intr_status
suffix:semicolon
id|u8
id|intr_enable
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|host_set-&gt;lock
comma
id|flags
)paren
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
id|host_set-&gt;n_ports
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|ata_port
op_star
id|ap
suffix:semicolon
id|ap
op_assign
id|host_set-&gt;ports
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ap
op_logical_and
(paren
op_logical_neg
(paren
id|ap-&gt;flags
op_amp
id|ATA_FLAG_PORT_DISABLED
)paren
)paren
)paren
(brace
r_struct
id|ata_queued_cmd
op_star
id|qc
suffix:semicolon
id|qc
op_assign
id|ata_qc_from_tag
c_func
(paren
id|ap
comma
id|ap-&gt;active_tag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qc
op_logical_and
(paren
op_logical_neg
(paren
id|qc-&gt;tf.ctl
op_amp
id|ATA_NIEN
)paren
)paren
)paren
id|handled
op_add_assign
id|ata_host_intr
c_func
(paren
id|ap
comma
id|qc
)paren
suffix:semicolon
)brace
id|intr_status
op_assign
id|inb
c_func
(paren
id|ap-&gt;ioaddr.scr_addr
op_plus
id|NV_INT_STATUS
)paren
suffix:semicolon
id|intr_enable
op_assign
id|inb
c_func
(paren
id|ap-&gt;ioaddr.scr_addr
op_plus
id|NV_INT_ENABLE
)paren
suffix:semicolon
singleline_comment|// Clear interrupt status.
id|outb
c_func
(paren
l_int|0xff
comma
id|ap-&gt;ioaddr.scr_addr
op_plus
id|NV_INT_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr_status
op_amp
id|NV_INT_STATUS_HOTPLUG
)paren
(brace
r_if
c_cond
(paren
id|intr_status
op_amp
id|NV_INT_STATUS_PDEV_ADDED
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ata%u: &quot;
l_string|&quot;Primary device added&bslash;n&quot;
comma
id|ap-&gt;id
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|intr_status
op_amp
id|NV_INT_STATUS_PDEV_REMOVED
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ata%u: &quot;
l_string|&quot;Primary device removed&bslash;n&quot;
comma
id|ap-&gt;id
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|intr_status
op_amp
id|NV_INT_STATUS_SDEV_ADDED
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ata%u: &quot;
l_string|&quot;Secondary device added&bslash;n&quot;
comma
id|ap-&gt;id
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|intr_status
op_amp
id|NV_INT_STATUS_SDEV_REMOVED
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ata%u: &quot;
l_string|&quot;Secondary device removed&bslash;n&quot;
comma
id|ap-&gt;id
)paren
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|host_set-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|IRQ_RETVAL
c_func
(paren
id|handled
)paren
suffix:semicolon
)brace
DECL|function|nv_scr_read
r_static
id|u32
id|nv_scr_read
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
id|sc_reg
op_star
l_int|4
)paren
)paren
suffix:semicolon
)brace
DECL|function|nv_scr_write
r_static
r_void
id|nv_scr_write
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
id|sc_reg
op_star
l_int|4
)paren
)paren
suffix:semicolon
)brace
DECL|function|nv_host_stop
r_static
r_void
id|nv_host_stop
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
(brace
r_int
id|i
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
id|host_set-&gt;n_ports
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u8
id|intr_mask
suffix:semicolon
singleline_comment|// Disable hotplug event interrupts.
id|intr_mask
op_assign
id|inb
c_func
(paren
id|host_set-&gt;ports
(braket
id|i
)braket
op_member_access_from_pointer
id|ioaddr.scr_addr
op_plus
id|NV_INT_ENABLE
)paren
suffix:semicolon
id|intr_mask
op_and_assign
op_complement
(paren
id|NV_INT_ENABLE_HOTPLUG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|intr_mask
comma
id|host_set-&gt;ports
(braket
id|i
)braket
op_member_access_from_pointer
id|ioaddr.scr_addr
op_plus
id|NV_INT_ENABLE
)paren
suffix:semicolon
)brace
)brace
DECL|function|nv_init_one
r_static
r_int
id|nv_init_one
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
op_assign
l_int|0
suffix:semicolon
r_struct
id|ata_probe_ent
op_star
id|probe_ent
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|rc
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
id|nv_sht
suffix:semicolon
id|probe_ent-&gt;host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_SATA_RESET
op_or
id|ATA_FLAG_SRST
op_or
id|ATA_FLAG_NO_LEGACY
suffix:semicolon
id|probe_ent-&gt;port_ops
op_assign
op_amp
id|nv_ops
suffix:semicolon
id|probe_ent-&gt;n_ports
op_assign
id|NV_PORTS
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
id|NV_PIO_MASK
suffix:semicolon
id|probe_ent-&gt;udma_mask
op_assign
id|NV_UDMA_MASK
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
op_or
id|NV_PORT0_BMDMA_REG_OFFSET
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|0
)braket
dot
id|scr_addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|5
)paren
op_or
id|NV_PORT0_SCR_REG_OFFSET
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
op_or
id|NV_PORT1_BMDMA_REG_OFFSET
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|1
)braket
dot
id|scr_addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|5
)paren
op_or
id|NV_PORT1_SCR_REG_OFFSET
suffix:semicolon
id|pci_set_master
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|rc
op_assign
id|ata_device_add
c_func
(paren
id|probe_ent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|NV_PORTS
)paren
r_goto
id|err_out_regions
suffix:semicolon
singleline_comment|// Enable hotplug event interrupts.
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|probe_ent-&gt;n_ports
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u8
id|intr_mask
suffix:semicolon
id|outb
c_func
(paren
id|NV_INT_STATUS_HOTPLUG
comma
id|probe_ent-&gt;port
(braket
id|i
)braket
dot
id|scr_addr
op_plus
id|NV_INT_STATUS
)paren
suffix:semicolon
id|intr_mask
op_assign
id|inb
c_func
(paren
id|probe_ent-&gt;port
(braket
id|i
)braket
dot
id|scr_addr
op_plus
id|NV_INT_ENABLE
)paren
suffix:semicolon
id|intr_mask
op_or_assign
id|NV_INT_ENABLE_HOTPLUG
suffix:semicolon
id|outb
c_func
(paren
id|intr_mask
comma
id|probe_ent-&gt;port
(braket
id|i
)braket
dot
id|scr_addr
op_plus
id|NV_INT_ENABLE
)paren
suffix:semicolon
)brace
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
DECL|function|nv_init
r_static
r_int
id|__init
id|nv_init
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
id|nv_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|nv_exit
r_static
r_void
id|__exit
id|nv_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|nv_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|nv_init
id|module_init
c_func
(paren
id|nv_init
)paren
suffix:semicolon
DECL|variable|nv_exit
id|module_exit
c_func
(paren
id|nv_exit
)paren
suffix:semicolon
eof
