multiline_comment|/*&n; *  sata_nv.c - NVIDIA nForce SATA&n; *&n; *  Copyright 2004 NVIDIA Corp.  All rights reserved.&n; *  Copyright 2004 Andrew Chew&n; *&n; *  The contents of this file are subject to the Open&n; *  Software License version 1.1 that can be found at&n; *  http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n; *  by reference.&n; *&n; *  Alternatively, the contents of this file may be used under the terms&n; *  of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n; *  in the kernel source COPYING file, in which case the provisions of&n; *  the GPL are applicable instead of the above.  If you wish to allow&n; *  the use of your version of this file only under the terms of the&n; *  GPL and not to allow others to use your version of this file under&n; *  the OSL, indicate your decision by deleting the provisions above and&n; *  replace them with the notice and other provisions required by the GPL.&n; *  If you do not delete the provisions above, a recipient may use your&n; *  version of this file under either the OSL or the GPL.&n; *&n; *  0.03&n; *     - Fixed a bug where the hotplug handlers for non-CK804/MCP04 were using&n; *       mmio_base, which is only set for the CK804/MCP04 case.&n; *&n; *  0.02&n; *     - Added support for CK804 SATA controller.&n; *&n; *  0.01&n; *     - Initial revision.&n; */
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
mdefine_line|#define DRV_VERSION&t;&t;&t;&quot;0.03&quot;
DECL|macro|NV_PORTS
mdefine_line|#define NV_PORTS&t;&t;&t;2
DECL|macro|NV_PIO_MASK
mdefine_line|#define NV_PIO_MASK&t;&t;&t;0x1f
DECL|macro|NV_MWDMA_MASK
mdefine_line|#define NV_MWDMA_MASK&t;&t;&t;0x07
DECL|macro|NV_UDMA_MASK
mdefine_line|#define NV_UDMA_MASK&t;&t;&t;0x7f
DECL|macro|NV_PORT0_SCR_REG_OFFSET
mdefine_line|#define NV_PORT0_SCR_REG_OFFSET&t;&t;0x00
DECL|macro|NV_PORT1_SCR_REG_OFFSET
mdefine_line|#define NV_PORT1_SCR_REG_OFFSET&t;&t;0x40
DECL|macro|NV_INT_STATUS
mdefine_line|#define NV_INT_STATUS&t;&t;&t;0x10
DECL|macro|NV_INT_STATUS_CK804
mdefine_line|#define NV_INT_STATUS_CK804&t;&t;0x440
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
DECL|macro|NV_INT_ENABLE_CK804
mdefine_line|#define NV_INT_ENABLE_CK804&t;&t;0x441
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
singleline_comment|// For PCI config register 20
DECL|macro|NV_MCP_SATA_CFG_20
mdefine_line|#define NV_MCP_SATA_CFG_20&t;&t;0x50
DECL|macro|NV_MCP_SATA_CFG_20_SATA_SPACE_EN
mdefine_line|#define NV_MCP_SATA_CFG_20_SATA_SPACE_EN&t;0x04
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
r_static
r_void
id|nv_enable_hotplug
c_func
(paren
r_struct
id|ata_probe_ent
op_star
id|probe_ent
)paren
suffix:semicolon
r_static
r_void
id|nv_disable_hotplug
c_func
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
suffix:semicolon
r_static
r_void
id|nv_check_hotplug
c_func
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
suffix:semicolon
r_static
r_void
id|nv_enable_hotplug_ck804
c_func
(paren
r_struct
id|ata_probe_ent
op_star
id|probe_ent
)paren
suffix:semicolon
r_static
r_void
id|nv_disable_hotplug_ck804
c_func
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
suffix:semicolon
r_static
r_void
id|nv_check_hotplug_ck804
c_func
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
suffix:semicolon
DECL|enum|nv_host_type
r_enum
id|nv_host_type
(brace
DECL|enumerator|NFORCE2
id|NFORCE2
comma
DECL|enumerator|NFORCE3
id|NFORCE3
comma
DECL|enumerator|CK804
id|CK804
)brace
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
l_int|0
comma
l_int|0
comma
id|NFORCE2
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
l_int|0
comma
l_int|0
comma
id|NFORCE3
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
l_int|0
comma
l_int|0
comma
id|NFORCE3
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
l_int|0
comma
l_int|0
comma
id|CK804
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
l_int|0
comma
l_int|0
comma
id|CK804
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
l_int|0
comma
l_int|0
comma
id|CK804
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
l_int|0
comma
l_int|0
comma
id|CK804
)brace
comma
(brace
l_int|0
comma
)brace
multiline_comment|/* terminate list */
)brace
suffix:semicolon
DECL|macro|NV_HOST_FLAGS_SCR_MMIO
mdefine_line|#define NV_HOST_FLAGS_SCR_MMIO&t;0x00000001
DECL|struct|nv_host_desc
r_struct
id|nv_host_desc
(brace
DECL|member|host_type
r_enum
id|nv_host_type
id|host_type
suffix:semicolon
DECL|member|host_flags
r_int
r_int
id|host_flags
suffix:semicolon
DECL|member|enable_hotplug
r_void
(paren
op_star
id|enable_hotplug
)paren
(paren
r_struct
id|ata_probe_ent
op_star
id|probe_ent
)paren
suffix:semicolon
DECL|member|disable_hotplug
r_void
(paren
op_star
id|disable_hotplug
)paren
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
suffix:semicolon
DECL|member|check_hotplug
r_void
(paren
op_star
id|check_hotplug
)paren
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|nv_device_tbl
r_static
r_struct
id|nv_host_desc
id|nv_device_tbl
(braket
)braket
op_assign
(brace
(brace
dot
id|host_type
op_assign
id|NFORCE2
comma
dot
id|host_flags
op_assign
l_int|0x00000000
comma
dot
id|enable_hotplug
op_assign
id|nv_enable_hotplug
comma
dot
id|disable_hotplug
op_assign
id|nv_disable_hotplug
comma
dot
id|check_hotplug
op_assign
id|nv_check_hotplug
comma
)brace
comma
(brace
dot
id|host_type
op_assign
id|NFORCE3
comma
dot
id|host_flags
op_assign
l_int|0x00000000
comma
dot
id|enable_hotplug
op_assign
id|nv_enable_hotplug
comma
dot
id|disable_hotplug
op_assign
id|nv_disable_hotplug
comma
dot
id|check_hotplug
op_assign
id|nv_check_hotplug
comma
)brace
comma
(brace
dot
id|host_type
op_assign
id|CK804
comma
dot
id|host_flags
op_assign
id|NV_HOST_FLAGS_SCR_MMIO
comma
dot
id|enable_hotplug
op_assign
id|nv_enable_hotplug_ck804
comma
dot
id|disable_hotplug
op_assign
id|nv_disable_hotplug_ck804
comma
dot
id|check_hotplug
op_assign
id|nv_check_hotplug_ck804
comma
)brace
comma
)brace
suffix:semicolon
DECL|struct|nv_host
r_struct
id|nv_host
(brace
DECL|member|host_desc
r_struct
id|nv_host_desc
op_star
id|host_desc
suffix:semicolon
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
id|ioctl
op_assign
id|ata_scsi_ioctl
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
id|ata_tf_load
comma
dot
id|tf_read
op_assign
id|ata_tf_read
comma
dot
id|exec_command
op_assign
id|ata_exec_command
comma
dot
id|check_status
op_assign
id|ata_check_status
comma
dot
id|dev_select
op_assign
id|ata_std_dev_select
comma
dot
id|phy_reset
op_assign
id|sata_phy_reset
comma
dot
id|bmdma_setup
op_assign
id|ata_bmdma_setup
comma
dot
id|bmdma_start
op_assign
id|ata_bmdma_start
comma
dot
id|qc_prep
op_assign
id|ata_qc_prep
comma
dot
id|qc_issue
op_assign
id|ata_qc_issue_prot
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
id|irq_clear
op_assign
id|ata_bmdma_irq_clear
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
DECL|variable|nv_port_info
r_static
r_struct
id|ata_port_info
id|nv_port_info
op_assign
(brace
dot
id|sht
op_assign
op_amp
id|nv_sht
comma
dot
id|host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_SATA_RESET
op_or
id|ATA_FLAG_SRST
op_or
id|ATA_FLAG_NO_LEGACY
comma
dot
id|pio_mask
op_assign
id|NV_PIO_MASK
comma
dot
id|mwdma_mask
op_assign
id|NV_MWDMA_MASK
comma
dot
id|udma_mask
op_assign
id|NV_UDMA_MASK
comma
dot
id|port_ops
op_assign
op_amp
id|nv_ops
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
r_struct
id|nv_host
op_star
id|host
op_assign
id|host_set-&gt;private_data
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
)brace
r_if
c_cond
(paren
id|host-&gt;host_desc-&gt;check_hotplug
)paren
id|host-&gt;host_desc
op_member_access_from_pointer
id|check_hotplug
c_func
(paren
id|host_set
)paren
suffix:semicolon
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
r_struct
id|ata_host_set
op_star
id|host_set
op_assign
id|ap-&gt;host_set
suffix:semicolon
r_struct
id|nv_host
op_star
id|host
op_assign
id|host_set-&gt;private_data
suffix:semicolon
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
r_if
c_cond
(paren
id|host-&gt;host_desc-&gt;host_flags
op_amp
id|NV_HOST_FLAGS_SCR_MMIO
)paren
r_return
id|readl
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
r_else
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
r_struct
id|ata_host_set
op_star
id|host_set
op_assign
id|ap-&gt;host_set
suffix:semicolon
r_struct
id|nv_host
op_star
id|host
op_assign
id|host_set-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|sc_reg
OG
id|SCR_CONTROL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;host_desc-&gt;host_flags
op_amp
id|NV_HOST_FLAGS_SCR_MMIO
)paren
id|writel
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
r_else
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
r_struct
id|nv_host
op_star
id|host
op_assign
id|host_set-&gt;private_data
suffix:semicolon
singleline_comment|// Disable hotplug event interrupts.
r_if
c_cond
(paren
id|host-&gt;host_desc-&gt;disable_hotplug
)paren
id|host-&gt;host_desc
op_member_access_from_pointer
id|disable_hotplug
c_func
(paren
id|host_set
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|host
)paren
suffix:semicolon
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
id|nv_host
op_star
id|host
suffix:semicolon
r_struct
id|ata_port_info
op_star
id|ppi
suffix:semicolon
r_struct
id|ata_probe_ent
op_star
id|probe_ent
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
r_goto
id|err_out
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
id|err_out_disable
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
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|ppi
op_assign
op_amp
id|nv_port_info
suffix:semicolon
id|probe_ent
op_assign
id|ata_pci_init_native_mode
c_func
(paren
id|pdev
comma
op_amp
id|ppi
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|probe_ent
)paren
r_goto
id|err_out_regions
suffix:semicolon
id|host
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|nv_host
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
r_goto
id|err_out_free_ent
suffix:semicolon
id|host-&gt;host_desc
op_assign
op_amp
id|nv_device_tbl
(braket
id|ent-&gt;driver_data
)braket
suffix:semicolon
id|probe_ent-&gt;private_data
op_assign
id|host
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;host_desc-&gt;host_flags
op_amp
id|NV_HOST_FLAGS_SCR_MMIO
)paren
(brace
r_int
r_int
id|base
suffix:semicolon
id|probe_ent-&gt;mmio_base
op_assign
id|ioremap
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
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|5
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|probe_ent-&gt;mmio_base
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err_out_free_host
suffix:semicolon
)brace
id|base
op_assign
(paren
r_int
r_int
)paren
id|probe_ent-&gt;mmio_base
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|0
)braket
dot
id|scr_addr
op_assign
id|base
op_plus
id|NV_PORT0_SCR_REG_OFFSET
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|1
)braket
dot
id|scr_addr
op_assign
id|base
op_plus
id|NV_PORT1_SCR_REG_OFFSET
suffix:semicolon
)brace
r_else
(brace
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
)brace
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
id|err_out_iounmap
suffix:semicolon
singleline_comment|// Enable hotplug event interrupts.
r_if
c_cond
(paren
id|host-&gt;host_desc-&gt;enable_hotplug
)paren
id|host-&gt;host_desc
op_member_access_from_pointer
id|enable_hotplug
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
id|err_out_iounmap
suffix:colon
r_if
c_cond
(paren
id|host-&gt;host_desc-&gt;host_flags
op_amp
id|NV_HOST_FLAGS_SCR_MMIO
)paren
id|iounmap
c_func
(paren
id|probe_ent-&gt;mmio_base
)paren
suffix:semicolon
id|err_out_free_host
suffix:colon
id|kfree
c_func
(paren
id|host
)paren
suffix:semicolon
id|err_out_free_ent
suffix:colon
id|kfree
c_func
(paren
id|probe_ent
)paren
suffix:semicolon
id|err_out_regions
suffix:colon
id|pci_release_regions
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|err_out_disable
suffix:colon
id|pci_disable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|err_out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|nv_enable_hotplug
r_static
r_void
id|nv_enable_hotplug
c_func
(paren
r_struct
id|ata_probe_ent
op_star
id|probe_ent
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
l_int|0
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
l_int|0
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
l_int|0
)braket
dot
id|scr_addr
op_plus
id|NV_INT_ENABLE
)paren
suffix:semicolon
)brace
DECL|function|nv_disable_hotplug
r_static
r_void
id|nv_disable_hotplug
c_func
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
(brace
id|u8
id|intr_mask
suffix:semicolon
id|intr_mask
op_assign
id|inb
c_func
(paren
id|host_set-&gt;ports
(braket
l_int|0
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
l_int|0
)braket
op_member_access_from_pointer
id|ioaddr.scr_addr
op_plus
id|NV_INT_ENABLE
)paren
suffix:semicolon
)brace
DECL|function|nv_check_hotplug
r_static
r_void
id|nv_check_hotplug
c_func
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
(brace
id|u8
id|intr_status
suffix:semicolon
id|intr_status
op_assign
id|inb
c_func
(paren
id|host_set-&gt;ports
(braket
l_int|0
)braket
op_member_access_from_pointer
id|ioaddr.scr_addr
op_plus
id|NV_INT_STATUS
)paren
suffix:semicolon
singleline_comment|// Clear interrupt status.
id|outb
c_func
(paren
l_int|0xff
comma
id|host_set-&gt;ports
(braket
l_int|0
)braket
op_member_access_from_pointer
id|ioaddr.scr_addr
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
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nv_sata: &quot;
l_string|&quot;Primary device added&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr_status
op_amp
id|NV_INT_STATUS_PDEV_REMOVED
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nv_sata: &quot;
l_string|&quot;Primary device removed&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr_status
op_amp
id|NV_INT_STATUS_SDEV_ADDED
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nv_sata: &quot;
l_string|&quot;Secondary device added&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr_status
op_amp
id|NV_INT_STATUS_SDEV_REMOVED
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nv_sata: &quot;
l_string|&quot;Secondary device removed&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|nv_enable_hotplug_ck804
r_static
r_void
id|nv_enable_hotplug_ck804
c_func
(paren
r_struct
id|ata_probe_ent
op_star
id|probe_ent
)paren
(brace
id|u8
id|intr_mask
suffix:semicolon
id|u8
id|regval
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|probe_ent-&gt;pdev
comma
id|NV_MCP_SATA_CFG_20
comma
op_amp
id|regval
)paren
suffix:semicolon
id|regval
op_or_assign
id|NV_MCP_SATA_CFG_20_SATA_SPACE_EN
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|probe_ent-&gt;pdev
comma
id|NV_MCP_SATA_CFG_20
comma
id|regval
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|NV_INT_STATUS_HOTPLUG
comma
id|probe_ent-&gt;mmio_base
op_plus
id|NV_INT_STATUS_CK804
)paren
suffix:semicolon
id|intr_mask
op_assign
id|readb
c_func
(paren
id|probe_ent-&gt;mmio_base
op_plus
id|NV_INT_ENABLE_CK804
)paren
suffix:semicolon
id|intr_mask
op_or_assign
id|NV_INT_ENABLE_HOTPLUG
suffix:semicolon
id|writeb
c_func
(paren
id|intr_mask
comma
id|probe_ent-&gt;mmio_base
op_plus
id|NV_INT_ENABLE_CK804
)paren
suffix:semicolon
)brace
DECL|function|nv_disable_hotplug_ck804
r_static
r_void
id|nv_disable_hotplug_ck804
c_func
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
(brace
id|u8
id|intr_mask
suffix:semicolon
id|u8
id|regval
suffix:semicolon
id|intr_mask
op_assign
id|readb
c_func
(paren
id|host_set-&gt;mmio_base
op_plus
id|NV_INT_ENABLE_CK804
)paren
suffix:semicolon
id|intr_mask
op_and_assign
op_complement
(paren
id|NV_INT_ENABLE_HOTPLUG
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|intr_mask
comma
id|host_set-&gt;mmio_base
op_plus
id|NV_INT_ENABLE_CK804
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|host_set-&gt;pdev
comma
id|NV_MCP_SATA_CFG_20
comma
op_amp
id|regval
)paren
suffix:semicolon
id|regval
op_and_assign
op_complement
id|NV_MCP_SATA_CFG_20_SATA_SPACE_EN
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|host_set-&gt;pdev
comma
id|NV_MCP_SATA_CFG_20
comma
id|regval
)paren
suffix:semicolon
)brace
DECL|function|nv_check_hotplug_ck804
r_static
r_void
id|nv_check_hotplug_ck804
c_func
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
(brace
id|u8
id|intr_status
suffix:semicolon
id|intr_status
op_assign
id|readb
c_func
(paren
id|host_set-&gt;mmio_base
op_plus
id|NV_INT_STATUS_CK804
)paren
suffix:semicolon
singleline_comment|// Clear interrupt status.
id|writeb
c_func
(paren
l_int|0xff
comma
id|host_set-&gt;mmio_base
op_plus
id|NV_INT_STATUS_CK804
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
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nv_sata: &quot;
l_string|&quot;Primary device added&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr_status
op_amp
id|NV_INT_STATUS_PDEV_REMOVED
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nv_sata: &quot;
l_string|&quot;Primary device removed&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr_status
op_amp
id|NV_INT_STATUS_SDEV_ADDED
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nv_sata: &quot;
l_string|&quot;Secondary device added&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr_status
op_amp
id|NV_INT_STATUS_SDEV_REMOVED
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nv_sata: &quot;
l_string|&quot;Secondary device removed&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
