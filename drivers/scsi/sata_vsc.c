multiline_comment|/*&n; *  sata_vsc.c - Vitesse VSC7174 4 port DPA SATA&n; *&n; *  Copyright 2004 SGI&n; *&n; *  Bits from Jeff Garzik, Copyright RedHat, Inc.&n; *&n; *  The contents of this file are subject to the Open&n; *  Software License version 1.1 that can be found at&n; *  http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n; *  by reference.&n; *&n; *  Alternatively, the contents of this file may be used under the terms&n; *  of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n; *  in the kernel source COPYING file, in which case the provisions of&n; *  the GPL are applicable instead of the above.  If you wish to allow&n; *  the use of your version of this file only under the terms of the&n; *  GPL and not to allow others to use your version of this file under&n; *  the OSL, indicate your decision by deleting the provisions above and&n; *  replace them with the notice and other provisions required by the GPL.&n; *  If you do not delete the provisions above, a recipient may use your&n; *  version of this file under either the OSL or the GPL.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &lt;linux/libata.h&gt;
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME&t;&quot;sata_vsc&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;0.01&quot;
multiline_comment|/* Interrupt register offsets (from chip base address) */
DECL|macro|VSC_SATA_INT_STAT_OFFSET
mdefine_line|#define VSC_SATA_INT_STAT_OFFSET&t;0x00
DECL|macro|VSC_SATA_INT_MASK_OFFSET
mdefine_line|#define VSC_SATA_INT_MASK_OFFSET&t;0x04
multiline_comment|/* Taskfile registers offsets */
DECL|macro|VSC_SATA_TF_CMD_OFFSET
mdefine_line|#define VSC_SATA_TF_CMD_OFFSET&t;&t;0x00
DECL|macro|VSC_SATA_TF_DATA_OFFSET
mdefine_line|#define VSC_SATA_TF_DATA_OFFSET&t;&t;0x00
DECL|macro|VSC_SATA_TF_ERROR_OFFSET
mdefine_line|#define VSC_SATA_TF_ERROR_OFFSET&t;0x04
DECL|macro|VSC_SATA_TF_FEATURE_OFFSET
mdefine_line|#define VSC_SATA_TF_FEATURE_OFFSET&t;0x06
DECL|macro|VSC_SATA_TF_NSECT_OFFSET
mdefine_line|#define VSC_SATA_TF_NSECT_OFFSET&t;0x08
DECL|macro|VSC_SATA_TF_LBAL_OFFSET
mdefine_line|#define VSC_SATA_TF_LBAL_OFFSET&t;&t;0x0c
DECL|macro|VSC_SATA_TF_LBAM_OFFSET
mdefine_line|#define VSC_SATA_TF_LBAM_OFFSET&t;&t;0x10
DECL|macro|VSC_SATA_TF_LBAH_OFFSET
mdefine_line|#define VSC_SATA_TF_LBAH_OFFSET&t;&t;0x14
DECL|macro|VSC_SATA_TF_DEVICE_OFFSET
mdefine_line|#define VSC_SATA_TF_DEVICE_OFFSET&t;0x18
DECL|macro|VSC_SATA_TF_STATUS_OFFSET
mdefine_line|#define VSC_SATA_TF_STATUS_OFFSET&t;0x1c
DECL|macro|VSC_SATA_TF_COMMAND_OFFSET
mdefine_line|#define VSC_SATA_TF_COMMAND_OFFSET&t;0x1d
DECL|macro|VSC_SATA_TF_ALTSTATUS_OFFSET
mdefine_line|#define VSC_SATA_TF_ALTSTATUS_OFFSET&t;0x28
DECL|macro|VSC_SATA_TF_CTL_OFFSET
mdefine_line|#define VSC_SATA_TF_CTL_OFFSET&t;&t;0x29
multiline_comment|/* DMA base */
DECL|macro|VSC_SATA_DMA_CMD_OFFSET
mdefine_line|#define VSC_SATA_DMA_CMD_OFFSET&t;&t;0x70
multiline_comment|/* SCRs base */
DECL|macro|VSC_SATA_SCR_STATUS_OFFSET
mdefine_line|#define VSC_SATA_SCR_STATUS_OFFSET&t;0x100
DECL|macro|VSC_SATA_SCR_ERROR_OFFSET
mdefine_line|#define VSC_SATA_SCR_ERROR_OFFSET&t;0x104
DECL|macro|VSC_SATA_SCR_CONTROL_OFFSET
mdefine_line|#define VSC_SATA_SCR_CONTROL_OFFSET&t;0x108
multiline_comment|/* Port stride */
DECL|macro|VSC_SATA_PORT_OFFSET
mdefine_line|#define VSC_SATA_PORT_OFFSET&t;&t;0x200
DECL|function|vsc_sata_scr_read
r_static
id|u32
id|vsc_sata_scr_read
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
id|readl
c_func
(paren
(paren
r_void
op_star
)paren
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
DECL|function|vsc_sata_scr_write
r_static
r_void
id|vsc_sata_scr_write
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
id|writel
c_func
(paren
id|val
comma
(paren
r_void
op_star
)paren
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
DECL|function|vsc_intr_mask_update
r_static
r_void
id|vsc_intr_mask_update
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
id|u8
id|ctl
)paren
(brace
r_int
r_int
id|mask_addr
suffix:semicolon
id|u8
id|mask
suffix:semicolon
id|mask_addr
op_assign
(paren
r_int
r_int
)paren
id|ap-&gt;host_set-&gt;mmio_base
op_plus
id|VSC_SATA_INT_MASK_OFFSET
op_plus
id|ap-&gt;port_no
suffix:semicolon
id|mask
op_assign
id|readb
c_func
(paren
id|mask_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctl
op_amp
id|ATA_NIEN
)paren
id|mask
op_or_assign
l_int|0x80
suffix:semicolon
r_else
id|mask
op_and_assign
l_int|0x7F
suffix:semicolon
id|writeb
c_func
(paren
id|mask
comma
id|mask_addr
)paren
suffix:semicolon
)brace
DECL|function|vsc_sata_tf_load
r_static
r_void
id|vsc_sata_tf_load
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
)paren
(brace
r_struct
id|ata_ioports
op_star
id|ioaddr
op_assign
op_amp
id|ap-&gt;ioaddr
suffix:semicolon
r_int
r_int
id|is_addr
op_assign
id|tf-&gt;flags
op_amp
id|ATA_TFLAG_ISADDR
suffix:semicolon
multiline_comment|/*&n;&t; * The only thing the ctl register is used for is SRST.&n;&t; * That is not enabled or disabled via tf_load.&n;&t; * However, if ATA_NIEN is changed, then we need to change the interrupt register.&n;&t; */
r_if
c_cond
(paren
(paren
id|tf-&gt;ctl
op_amp
id|ATA_NIEN
)paren
op_ne
(paren
id|ap-&gt;last_ctl
op_amp
id|ATA_NIEN
)paren
)paren
(brace
id|ap-&gt;last_ctl
op_assign
id|tf-&gt;ctl
suffix:semicolon
id|vsc_intr_mask_update
c_func
(paren
id|ap
comma
id|tf-&gt;ctl
op_amp
id|ATA_NIEN
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_addr
op_logical_and
(paren
id|tf-&gt;flags
op_amp
id|ATA_TFLAG_LBA48
)paren
)paren
(brace
id|writew
c_func
(paren
id|tf-&gt;feature
op_or
(paren
(paren
(paren
id|u16
)paren
id|tf-&gt;hob_feature
)paren
op_lshift
l_int|8
)paren
comma
id|ioaddr-&gt;feature_addr
)paren
suffix:semicolon
id|writew
c_func
(paren
id|tf-&gt;nsect
op_or
(paren
(paren
(paren
id|u16
)paren
id|tf-&gt;hob_nsect
)paren
op_lshift
l_int|8
)paren
comma
id|ioaddr-&gt;nsect_addr
)paren
suffix:semicolon
id|writew
c_func
(paren
id|tf-&gt;lbal
op_or
(paren
(paren
(paren
id|u16
)paren
id|tf-&gt;hob_lbal
)paren
op_lshift
l_int|8
)paren
comma
id|ioaddr-&gt;lbal_addr
)paren
suffix:semicolon
id|writew
c_func
(paren
id|tf-&gt;lbam
op_or
(paren
(paren
(paren
id|u16
)paren
id|tf-&gt;hob_lbam
)paren
op_lshift
l_int|8
)paren
comma
id|ioaddr-&gt;lbam_addr
)paren
suffix:semicolon
id|writew
c_func
(paren
id|tf-&gt;lbah
op_or
(paren
(paren
(paren
id|u16
)paren
id|tf-&gt;hob_lbah
)paren
op_lshift
l_int|8
)paren
comma
id|ioaddr-&gt;lbah_addr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_addr
)paren
(brace
id|writew
c_func
(paren
id|tf-&gt;feature
comma
id|ioaddr-&gt;feature_addr
)paren
suffix:semicolon
id|writew
c_func
(paren
id|tf-&gt;nsect
comma
id|ioaddr-&gt;nsect_addr
)paren
suffix:semicolon
id|writew
c_func
(paren
id|tf-&gt;lbal
comma
id|ioaddr-&gt;lbal_addr
)paren
suffix:semicolon
id|writew
c_func
(paren
id|tf-&gt;lbam
comma
id|ioaddr-&gt;lbam_addr
)paren
suffix:semicolon
id|writew
c_func
(paren
id|tf-&gt;lbah
comma
id|ioaddr-&gt;lbah_addr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tf-&gt;flags
op_amp
id|ATA_TFLAG_DEVICE
)paren
id|writeb
c_func
(paren
id|tf-&gt;device
comma
id|ioaddr-&gt;device_addr
)paren
suffix:semicolon
id|ata_wait_idle
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
DECL|function|vsc_sata_tf_read
r_static
r_void
id|vsc_sata_tf_read
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
)paren
(brace
r_struct
id|ata_ioports
op_star
id|ioaddr
op_assign
op_amp
id|ap-&gt;ioaddr
suffix:semicolon
id|u16
id|nsect
comma
id|lbal
comma
id|lbam
comma
id|lbah
suffix:semicolon
id|nsect
op_assign
id|tf-&gt;nsect
op_assign
id|readw
c_func
(paren
id|ioaddr-&gt;nsect_addr
)paren
suffix:semicolon
id|lbal
op_assign
id|tf-&gt;lbal
op_assign
id|readw
c_func
(paren
id|ioaddr-&gt;lbal_addr
)paren
suffix:semicolon
id|lbam
op_assign
id|tf-&gt;lbam
op_assign
id|readw
c_func
(paren
id|ioaddr-&gt;lbam_addr
)paren
suffix:semicolon
id|lbah
op_assign
id|tf-&gt;lbah
op_assign
id|readw
c_func
(paren
id|ioaddr-&gt;lbah_addr
)paren
suffix:semicolon
id|tf-&gt;device
op_assign
id|readw
c_func
(paren
id|ioaddr-&gt;device_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tf-&gt;flags
op_amp
id|ATA_TFLAG_LBA48
)paren
(brace
id|tf-&gt;hob_feature
op_assign
id|readb
c_func
(paren
id|ioaddr-&gt;error_addr
)paren
suffix:semicolon
id|tf-&gt;hob_nsect
op_assign
id|nsect
op_rshift
l_int|8
suffix:semicolon
id|tf-&gt;hob_lbal
op_assign
id|lbal
op_rshift
l_int|8
suffix:semicolon
id|tf-&gt;hob_lbam
op_assign
id|lbam
op_rshift
l_int|8
suffix:semicolon
id|tf-&gt;hob_lbah
op_assign
id|lbah
op_rshift
l_int|8
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * vsc_sata_interrupt&n; *&n; * Read the interrupt register and process for the devices that have them pending.&n; */
DECL|function|vsc_sata_interrupt
id|irqreturn_t
id|vsc_sata_interrupt
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
id|u32
id|int_status
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|host_set-&gt;lock
)paren
suffix:semicolon
id|int_status
op_assign
id|readl
c_func
(paren
id|host_set-&gt;mmio_base
op_plus
id|VSC_SATA_INT_STAT_OFFSET
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
r_if
c_cond
(paren
id|int_status
op_amp
(paren
(paren
id|u32
)paren
l_int|0xFF
op_lshift
(paren
l_int|8
op_star
id|i
)paren
)paren
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
(paren
id|qc-&gt;flags
op_amp
id|ATA_QCFLAG_POLL
)paren
op_eq
l_int|0
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
)brace
id|spin_unlock
c_func
(paren
op_amp
id|host_set-&gt;lock
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
DECL|variable|vsc_sata_sht
r_static
id|Scsi_Host_Template
id|vsc_sata_sht
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
DECL|variable|vsc_sata_ops
r_static
r_struct
id|ata_port_operations
id|vsc_sata_ops
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
id|vsc_sata_tf_load
comma
dot
id|tf_read
op_assign
id|vsc_sata_tf_read
comma
dot
id|exec_command
op_assign
id|ata_exec_command_mmio
comma
dot
id|check_status
op_assign
id|ata_check_status_mmio
comma
dot
id|phy_reset
op_assign
id|sata_phy_reset
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
id|ata_bmdma_start_mmio
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
id|vsc_sata_interrupt
comma
dot
id|scr_read
op_assign
id|vsc_sata_scr_read
comma
dot
id|scr_write
op_assign
id|vsc_sata_scr_write
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
DECL|function|vsc_sata_setup_port
r_static
r_void
id|vsc_sata_setup_port
c_func
(paren
r_struct
id|ata_ioports
op_star
id|port
comma
r_int
r_int
id|base
)paren
(brace
id|port-&gt;cmd_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_CMD_OFFSET
suffix:semicolon
id|port-&gt;data_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_DATA_OFFSET
suffix:semicolon
id|port-&gt;error_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_ERROR_OFFSET
suffix:semicolon
id|port-&gt;feature_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_FEATURE_OFFSET
suffix:semicolon
id|port-&gt;nsect_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_NSECT_OFFSET
suffix:semicolon
id|port-&gt;lbal_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_LBAL_OFFSET
suffix:semicolon
id|port-&gt;lbam_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_LBAM_OFFSET
suffix:semicolon
id|port-&gt;lbah_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_LBAH_OFFSET
suffix:semicolon
id|port-&gt;device_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_DEVICE_OFFSET
suffix:semicolon
id|port-&gt;status_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_STATUS_OFFSET
suffix:semicolon
id|port-&gt;command_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_COMMAND_OFFSET
suffix:semicolon
id|port-&gt;altstatus_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_ALTSTATUS_OFFSET
suffix:semicolon
id|port-&gt;ctl_addr
op_assign
id|base
op_plus
id|VSC_SATA_TF_CTL_OFFSET
suffix:semicolon
id|port-&gt;bmdma_addr
op_assign
id|base
op_plus
id|VSC_SATA_DMA_CMD_OFFSET
suffix:semicolon
id|port-&gt;scr_addr
op_assign
id|base
op_plus
id|VSC_SATA_SCR_STATUS_OFFSET
suffix:semicolon
)brace
DECL|function|vsc_sata_init_one
r_static
r_int
id|vsc_sata_init_one
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
id|ata_probe_ent
op_star
id|probe_ent
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|base
suffix:semicolon
r_void
op_star
id|mmio_base
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
multiline_comment|/*&n;&t; * Check if we have needed resource mapped.&n;&t; */
r_if
c_cond
(paren
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|0
)paren
op_eq
l_int|0
)paren
(brace
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
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
multiline_comment|/*&n;&t; * Use 32 bit DMA mask, because 64 bit address support is poor.&n;&t; */
id|rc
op_assign
id|pci_set_dma_mask
c_func
(paren
id|pdev
comma
l_int|0xFFFFFFFF
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
l_int|0xFFFFFFFF
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
id|probe_ent
op_eq
l_int|NULL
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
id|probe_ent-&gt;pdev
op_assign
id|pdev
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|probe_ent-&gt;node
)paren
suffix:semicolon
id|mmio_base
op_assign
id|ioremap
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
comma
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mmio_base
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_out_free_ent
suffix:semicolon
)brace
id|base
op_assign
(paren
r_int
r_int
)paren
id|mmio_base
suffix:semicolon
multiline_comment|/*&n;&t; * Due to a bug in the chip, the default cache line size can&squot;t be used&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
id|PCI_CACHE_LINE_SIZE
comma
l_int|0x80
)paren
suffix:semicolon
id|probe_ent-&gt;sht
op_assign
op_amp
id|vsc_sata_sht
suffix:semicolon
id|probe_ent-&gt;host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_NO_LEGACY
op_or
id|ATA_FLAG_MMIO
op_or
id|ATA_FLAG_SATA_RESET
suffix:semicolon
id|probe_ent-&gt;port_ops
op_assign
op_amp
id|vsc_sata_ops
suffix:semicolon
id|probe_ent-&gt;n_ports
op_assign
l_int|4
suffix:semicolon
id|probe_ent-&gt;irq
op_assign
id|pdev-&gt;irq
suffix:semicolon
id|probe_ent-&gt;irq_flags
op_assign
id|SA_SHIRQ
suffix:semicolon
id|probe_ent-&gt;mmio_base
op_assign
id|mmio_base
suffix:semicolon
multiline_comment|/* We don&squot;t care much about the PIO/UDMA masks, but the core won&squot;t like us&n;&t; * if we don&squot;t fill these&n;&t; */
id|probe_ent-&gt;pio_mask
op_assign
l_int|0x1f
suffix:semicolon
id|probe_ent-&gt;udma_mask
op_assign
l_int|0x3f
suffix:semicolon
multiline_comment|/* We have 4 ports per PCI function */
id|vsc_sata_setup_port
c_func
(paren
op_amp
id|probe_ent-&gt;port
(braket
l_int|0
)braket
comma
id|base
op_plus
l_int|1
op_star
id|VSC_SATA_PORT_OFFSET
)paren
suffix:semicolon
id|vsc_sata_setup_port
c_func
(paren
op_amp
id|probe_ent-&gt;port
(braket
l_int|1
)braket
comma
id|base
op_plus
l_int|2
op_star
id|VSC_SATA_PORT_OFFSET
)paren
suffix:semicolon
id|vsc_sata_setup_port
c_func
(paren
op_amp
id|probe_ent-&gt;port
(braket
l_int|2
)braket
comma
id|base
op_plus
l_int|3
op_star
id|VSC_SATA_PORT_OFFSET
)paren
suffix:semicolon
id|vsc_sata_setup_port
c_func
(paren
op_amp
id|probe_ent-&gt;port
(braket
l_int|3
)braket
comma
id|base
op_plus
l_int|4
op_star
id|VSC_SATA_PORT_OFFSET
)paren
suffix:semicolon
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
DECL|variable|vsc_sata_pci_tbl
r_static
r_struct
id|pci_device_id
id|vsc_sata_pci_tbl
(braket
)braket
op_assign
(brace
(brace
l_int|0x1725
comma
l_int|0x7174
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0x10600
comma
l_int|0xFFFFFF
comma
l_int|0
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x3200
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0x10600
comma
l_int|0xFFFFFF
comma
l_int|0
)brace
comma
(brace
)brace
)brace
suffix:semicolon
DECL|variable|vsc_sata_pci_driver
r_static
r_struct
id|pci_driver
id|vsc_sata_pci_driver
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
id|vsc_sata_pci_tbl
comma
dot
id|probe
op_assign
id|vsc_sata_init_one
comma
dot
id|remove
op_assign
id|ata_pci_remove_one
comma
)brace
suffix:semicolon
DECL|function|vsc_sata_init
r_static
r_int
id|__init
id|vsc_sata_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|pci_module_init
c_func
(paren
op_amp
id|vsc_sata_pci_driver
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vsc_sata_exit
r_static
r_void
id|__exit
id|vsc_sata_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|vsc_sata_pci_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jeremy Higdon&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;low-level driver for Vitesse VSC7174 SATA controller&quot;
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
id|vsc_sata_pci_tbl
)paren
suffix:semicolon
DECL|variable|vsc_sata_init
id|module_init
c_func
(paren
id|vsc_sata_init
)paren
suffix:semicolon
DECL|variable|vsc_sata_exit
id|module_exit
c_func
(paren
id|vsc_sata_exit
)paren
suffix:semicolon
eof
