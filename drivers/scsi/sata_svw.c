multiline_comment|/*&n; *  sata_svw.c - ServerWorks / Apple K2 SATA&n; *&n; *  Maintained by: Benjamin Herrenschmidt &lt;benh@kernel.crashing.org&gt; and&n; *&t;&t;   Jeff Garzik &lt;jgarzik@pobox.com&gt;&n; *  &t;&t;    Please ALWAYS copy linux-ide@vger.kernel.org&n; *&t;&t;    on emails.&n; *&n; *  Copyright 2003 Benjamin Herrenschmidt &lt;benh@kernel.crashing.org&gt;&n; *&n; *  Bits from Jeff Garzik, Copyright RedHat, Inc.&n; *&n; *  This driver probably works with non-Apple versions of the&n; *  Broadcom chipset...&n; *&n; *  The contents of this file are subject to the Open&n; *  Software License version 1.1 that can be found at&n; *  http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n; *  by reference.&n; *&n; *  Alternatively, the contents of this file may be used under the terms&n; *  of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n; *  in the kernel source COPYING file, in which case the provisions of&n; *  the GPL are applicable instead of the above.  If you wish to allow&n; *  the use of your version of this file only under the terms of the&n; *  GPL and not to allow others to use your version of this file under&n; *  the OSL, indicate your decision by deleting the provisions above and&n; *  replace them with the notice and other provisions required by the GPL.&n; *  If you do not delete the provisions above, a recipient may use your&n; *  version of this file under either the OSL or the GPL.&n; *&n; */
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
macro_line|#ifdef CONFIG_PPC_OF
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#endif /* CONFIG_PPC_OF */
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME&t;&quot;sata_svw&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;1.05&quot;
multiline_comment|/* Taskfile registers offsets */
DECL|macro|K2_SATA_TF_CMD_OFFSET
mdefine_line|#define K2_SATA_TF_CMD_OFFSET&t;&t;0x00
DECL|macro|K2_SATA_TF_DATA_OFFSET
mdefine_line|#define K2_SATA_TF_DATA_OFFSET&t;&t;0x00
DECL|macro|K2_SATA_TF_ERROR_OFFSET
mdefine_line|#define K2_SATA_TF_ERROR_OFFSET&t;&t;0x04
DECL|macro|K2_SATA_TF_NSECT_OFFSET
mdefine_line|#define K2_SATA_TF_NSECT_OFFSET&t;&t;0x08
DECL|macro|K2_SATA_TF_LBAL_OFFSET
mdefine_line|#define K2_SATA_TF_LBAL_OFFSET&t;&t;0x0c
DECL|macro|K2_SATA_TF_LBAM_OFFSET
mdefine_line|#define K2_SATA_TF_LBAM_OFFSET&t;&t;0x10
DECL|macro|K2_SATA_TF_LBAH_OFFSET
mdefine_line|#define K2_SATA_TF_LBAH_OFFSET&t;&t;0x14
DECL|macro|K2_SATA_TF_DEVICE_OFFSET
mdefine_line|#define K2_SATA_TF_DEVICE_OFFSET&t;0x18
DECL|macro|K2_SATA_TF_CMDSTAT_OFFSET
mdefine_line|#define K2_SATA_TF_CMDSTAT_OFFSET      &t;0x1c
DECL|macro|K2_SATA_TF_CTL_OFFSET
mdefine_line|#define K2_SATA_TF_CTL_OFFSET&t;&t;0x20
multiline_comment|/* DMA base */
DECL|macro|K2_SATA_DMA_CMD_OFFSET
mdefine_line|#define K2_SATA_DMA_CMD_OFFSET&t;&t;0x30
multiline_comment|/* SCRs base */
DECL|macro|K2_SATA_SCR_STATUS_OFFSET
mdefine_line|#define K2_SATA_SCR_STATUS_OFFSET&t;0x40
DECL|macro|K2_SATA_SCR_ERROR_OFFSET
mdefine_line|#define K2_SATA_SCR_ERROR_OFFSET&t;0x44
DECL|macro|K2_SATA_SCR_CONTROL_OFFSET
mdefine_line|#define K2_SATA_SCR_CONTROL_OFFSET&t;0x48
multiline_comment|/* Others */
DECL|macro|K2_SATA_SICR1_OFFSET
mdefine_line|#define K2_SATA_SICR1_OFFSET&t;&t;0x80
DECL|macro|K2_SATA_SICR2_OFFSET
mdefine_line|#define K2_SATA_SICR2_OFFSET&t;&t;0x84
DECL|macro|K2_SATA_SIM_OFFSET
mdefine_line|#define K2_SATA_SIM_OFFSET&t;&t;0x88
multiline_comment|/* Port stride */
DECL|macro|K2_SATA_PORT_OFFSET
mdefine_line|#define K2_SATA_PORT_OFFSET&t;&t;0x100
DECL|function|k2_sata_scr_read
r_static
id|u32
id|k2_sata_scr_read
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
DECL|function|k2_sata_scr_write
r_static
r_void
id|k2_sata_scr_write
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
DECL|function|k2_sata_tf_load
r_static
r_void
id|k2_sata_tf_load
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
r_if
c_cond
(paren
id|tf-&gt;ctl
op_ne
id|ap-&gt;last_ctl
)paren
(brace
id|writeb
c_func
(paren
id|tf-&gt;ctl
comma
id|ioaddr-&gt;ctl_addr
)paren
suffix:semicolon
id|ap-&gt;last_ctl
op_assign
id|tf-&gt;ctl
suffix:semicolon
id|ata_wait_idle
c_func
(paren
id|ap
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
DECL|function|k2_sata_tf_read
r_static
r_void
id|k2_sata_tf_read
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
id|readw
c_func
(paren
id|ioaddr-&gt;error_addr
)paren
op_rshift
l_int|8
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
multiline_comment|/**&n; *&t;k2_bmdma_setup_mmio - Set up PCI IDE BMDMA transaction (MMIO)&n; *&t;@qc: Info associated with this ATA transaction.&n; *&n; *&t;LOCKING:&n; *&t;spin_lock_irqsave(host_set lock)&n; */
DECL|function|k2_bmdma_setup_mmio
r_void
id|k2_bmdma_setup_mmio
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
(brace
r_struct
id|ata_port
op_star
id|ap
op_assign
id|qc-&gt;ap
suffix:semicolon
r_int
r_int
id|rw
op_assign
(paren
id|qc-&gt;tf.flags
op_amp
id|ATA_TFLAG_WRITE
)paren
suffix:semicolon
id|u8
id|dmactl
suffix:semicolon
r_void
op_star
id|mmio
op_assign
(paren
r_void
op_star
)paren
id|ap-&gt;ioaddr.bmdma_addr
suffix:semicolon
multiline_comment|/* load PRD table addr. */
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* make sure PRD table writes are visible to controller */
id|writel
c_func
(paren
id|ap-&gt;prd_dma
comma
id|mmio
op_plus
id|ATA_DMA_TABLE_OFS
)paren
suffix:semicolon
multiline_comment|/* specify data direction, triple-check start bit is clear */
id|dmactl
op_assign
id|readb
c_func
(paren
id|mmio
op_plus
id|ATA_DMA_CMD
)paren
suffix:semicolon
id|dmactl
op_and_assign
op_complement
(paren
id|ATA_DMA_WR
op_or
id|ATA_DMA_START
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rw
)paren
id|dmactl
op_or_assign
id|ATA_DMA_WR
suffix:semicolon
id|writeb
c_func
(paren
id|dmactl
comma
id|mmio
op_plus
id|ATA_DMA_CMD
)paren
suffix:semicolon
multiline_comment|/* issue r/w command if this is not a ATA DMA command*/
r_if
c_cond
(paren
id|qc-&gt;tf.protocol
op_ne
id|ATA_PROT_DMA
)paren
id|ap-&gt;ops
op_member_access_from_pointer
id|exec_command
c_func
(paren
id|ap
comma
op_amp
id|qc-&gt;tf
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;k2_bmdma_start_mmio - Start a PCI IDE BMDMA transaction (MMIO)&n; *&t;@qc: Info associated with this ATA transaction.&n; *&n; *&t;LOCKING:&n; *&t;spin_lock_irqsave(host_set lock)&n; */
DECL|function|k2_bmdma_start_mmio
r_void
id|k2_bmdma_start_mmio
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
(brace
r_struct
id|ata_port
op_star
id|ap
op_assign
id|qc-&gt;ap
suffix:semicolon
r_void
op_star
id|mmio
op_assign
(paren
r_void
op_star
)paren
id|ap-&gt;ioaddr.bmdma_addr
suffix:semicolon
id|u8
id|dmactl
suffix:semicolon
multiline_comment|/* start host DMA transaction */
id|dmactl
op_assign
id|readb
c_func
(paren
id|mmio
op_plus
id|ATA_DMA_CMD
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|dmactl
op_or
id|ATA_DMA_START
comma
id|mmio
op_plus
id|ATA_DMA_CMD
)paren
suffix:semicolon
multiline_comment|/* There is a race condition in certain SATA controllers that can &n;&t;   be seen when the r/w command is given to the controller before the &n;&t;   host DMA is started. On a Read command, the controller would initiate&n;&t;   the command to the drive even before it sees the DMA start. When there&n;&t;   are very fast drives connected to the controller, or when the data request &n;&t;   hits in the drive cache, there is the possibility that the drive returns a part&n;&t;   or all of the requested data to the controller before the DMA start is issued.&n;&t;   In this case, the controller would become confused as to what to do with the data.&n;&t;   In the worst case when all the data is returned back to the controller, the&n;&t;   controller could hang. In other cases it could return partial data returning&n;&t;   in data corruption. This problem has been seen in PPC systems and can also appear&n;&t;   on an system with very fast disks, where the SATA controller is sitting behind a &n;&t;   number of bridges, and hence there is significant latency between the r/w command&n;&t;   and the start command. */
multiline_comment|/* issue r/w command if the access is to ATA*/
r_if
c_cond
(paren
id|qc-&gt;tf.protocol
op_eq
id|ATA_PROT_DMA
)paren
id|ap-&gt;ops
op_member_access_from_pointer
id|exec_command
c_func
(paren
id|ap
comma
op_amp
id|qc-&gt;tf
)paren
suffix:semicolon
)brace
DECL|function|k2_stat_check_status
r_static
id|u8
id|k2_stat_check_status
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_return
id|readl
c_func
(paren
(paren
r_void
op_star
)paren
id|ap-&gt;ioaddr.status_addr
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PPC_OF
multiline_comment|/*&n; * k2_sata_proc_info&n; * inout : decides on the direction of the dataflow and the meaning of the&n; *&t;   variables&n; * buffer: If inout==FALSE data is being written to it else read from it&n; * *start: If inout==FALSE start of the valid data in the buffer&n; * offset: If inout==FALSE offset from the beginning of the imaginary file&n; *&t;   from which we start writing into the buffer&n; * length: If inout==FALSE max number of bytes to be written into the buffer&n; *&t;   else number of bytes in the buffer&n; */
DECL|function|k2_sata_proc_info
r_static
r_int
id|k2_sata_proc_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|count
comma
r_int
id|inout
)paren
(brace
r_struct
id|ata_port
op_star
id|ap
suffix:semicolon
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_int
id|len
comma
id|index
suffix:semicolon
multiline_comment|/* Find  the ata_port */
id|ap
op_assign
(paren
r_struct
id|ata_port
op_star
)paren
op_amp
id|shost-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ap
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Find the OF node for the PCI device proper */
id|np
op_assign
id|pci_device_to_OF_node
c_func
(paren
id|to_pci_dev
c_func
(paren
id|ap-&gt;host_set-&gt;dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Match it to a port node */
id|index
op_assign
(paren
id|ap
op_eq
id|ap-&gt;host_set-&gt;ports
(braket
l_int|0
)braket
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|np
op_assign
id|np-&gt;child
suffix:semicolon
id|np
op_ne
l_int|NULL
suffix:semicolon
id|np
op_assign
id|np-&gt;sibling
)paren
(brace
id|u32
op_star
id|reg
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;reg&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reg
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|index
op_eq
op_star
id|reg
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|np
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;devspec: %s&bslash;n&quot;
comma
id|np-&gt;full_name
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_OF */
DECL|variable|k2_sata_sht
r_static
id|Scsi_Host_Template
id|k2_sata_sht
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
macro_line|#ifdef CONFIG_PPC_OF
dot
id|proc_info
op_assign
id|k2_sata_proc_info
comma
macro_line|#endif
dot
id|bios_param
op_assign
id|ata_std_bios_param
comma
)brace
suffix:semicolon
DECL|variable|k2_sata_ops
r_static
r_struct
id|ata_port_operations
id|k2_sata_ops
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
id|k2_sata_tf_load
comma
dot
id|tf_read
op_assign
id|k2_sata_tf_read
comma
dot
id|check_status
op_assign
id|k2_stat_check_status
comma
dot
id|exec_command
op_assign
id|ata_exec_command
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
id|k2_bmdma_setup_mmio
comma
dot
id|bmdma_start
op_assign
id|k2_bmdma_start_mmio
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
id|ata_interrupt
comma
dot
id|irq_clear
op_assign
id|ata_bmdma_irq_clear
comma
dot
id|scr_read
op_assign
id|k2_sata_scr_read
comma
dot
id|scr_write
op_assign
id|k2_sata_scr_write
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
DECL|function|k2_sata_setup_port
r_static
r_void
id|k2_sata_setup_port
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
id|K2_SATA_TF_CMD_OFFSET
suffix:semicolon
id|port-&gt;data_addr
op_assign
id|base
op_plus
id|K2_SATA_TF_DATA_OFFSET
suffix:semicolon
id|port-&gt;feature_addr
op_assign
id|port-&gt;error_addr
op_assign
id|base
op_plus
id|K2_SATA_TF_ERROR_OFFSET
suffix:semicolon
id|port-&gt;nsect_addr
op_assign
id|base
op_plus
id|K2_SATA_TF_NSECT_OFFSET
suffix:semicolon
id|port-&gt;lbal_addr
op_assign
id|base
op_plus
id|K2_SATA_TF_LBAL_OFFSET
suffix:semicolon
id|port-&gt;lbam_addr
op_assign
id|base
op_plus
id|K2_SATA_TF_LBAM_OFFSET
suffix:semicolon
id|port-&gt;lbah_addr
op_assign
id|base
op_plus
id|K2_SATA_TF_LBAH_OFFSET
suffix:semicolon
id|port-&gt;device_addr
op_assign
id|base
op_plus
id|K2_SATA_TF_DEVICE_OFFSET
suffix:semicolon
id|port-&gt;command_addr
op_assign
id|port-&gt;status_addr
op_assign
id|base
op_plus
id|K2_SATA_TF_CMDSTAT_OFFSET
suffix:semicolon
id|port-&gt;altstatus_addr
op_assign
id|port-&gt;ctl_addr
op_assign
id|base
op_plus
id|K2_SATA_TF_CTL_OFFSET
suffix:semicolon
id|port-&gt;bmdma_addr
op_assign
id|base
op_plus
id|K2_SATA_DMA_CMD_OFFSET
suffix:semicolon
id|port-&gt;scr_addr
op_assign
id|base
op_plus
id|K2_SATA_SCR_STATUS_OFFSET
suffix:semicolon
)brace
DECL|function|k2_sata_init_one
r_static
r_int
id|k2_sata_init_one
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
id|pci_dev_busy
op_assign
l_int|0
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
multiline_comment|/*&n;&t; * If this driver happens to only be useful on Apple&squot;s K2, then&n;&t; * we should check that here as it has a normal Serverworks ID&n;&t; */
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
multiline_comment|/*&n;&t; * Check if we have resources mapped at all (second function may&n;&t; * have been disabled by firmware)&n;&t; */
r_if
c_cond
(paren
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|5
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Request PCI regions */
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
(brace
id|pci_dev_busy
op_assign
l_int|1
suffix:semicolon
r_goto
id|err_out
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
id|probe_ent-&gt;dev
op_assign
id|pci_dev_to_dev
c_func
(paren
id|pdev
)paren
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
multiline_comment|/* Clear a magic bit in SCR1 according to Darwin, those help&n;&t; * some funky seagate drives (though so far, those were already&n;&t; * set by the firmware on the machines I had access to&n;&t; */
id|writel
c_func
(paren
id|readl
c_func
(paren
id|mmio_base
op_plus
id|K2_SATA_SICR1_OFFSET
)paren
op_amp
op_complement
l_int|0x00040000
comma
id|mmio_base
op_plus
id|K2_SATA_SICR1_OFFSET
)paren
suffix:semicolon
multiline_comment|/* Clear SATA error &amp; interrupts we don&squot;t use */
id|writel
c_func
(paren
l_int|0xffffffff
comma
id|mmio_base
op_plus
id|K2_SATA_SCR_ERROR_OFFSET
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0x0
comma
id|mmio_base
op_plus
id|K2_SATA_SIM_OFFSET
)paren
suffix:semicolon
id|probe_ent-&gt;sht
op_assign
op_amp
id|k2_sata_sht
suffix:semicolon
id|probe_ent-&gt;host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_SATA_RESET
op_or
id|ATA_FLAG_NO_LEGACY
op_or
id|ATA_FLAG_MMIO
suffix:semicolon
id|probe_ent-&gt;port_ops
op_assign
op_amp
id|k2_sata_ops
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
id|probe_ent-&gt;mwdma_mask
op_assign
l_int|0x7
suffix:semicolon
id|probe_ent-&gt;udma_mask
op_assign
l_int|0x7f
suffix:semicolon
multiline_comment|/* We have 4 ports per PCI function */
id|k2_sata_setup_port
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
l_int|0
op_star
id|K2_SATA_PORT_OFFSET
)paren
suffix:semicolon
id|k2_sata_setup_port
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
l_int|1
op_star
id|K2_SATA_PORT_OFFSET
)paren
suffix:semicolon
id|k2_sata_setup_port
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
l_int|2
op_star
id|K2_SATA_PORT_OFFSET
)paren
suffix:semicolon
id|k2_sata_setup_port
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
l_int|3
op_star
id|K2_SATA_PORT_OFFSET
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
r_if
c_cond
(paren
op_logical_neg
id|pci_dev_busy
)paren
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
DECL|variable|k2_sata_pci_tbl
r_static
r_struct
id|pci_device_id
id|k2_sata_pci_tbl
(braket
)braket
op_assign
(brace
(brace
l_int|0x1166
comma
l_int|0x0240
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0x1166
comma
l_int|0x0241
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0x1166
comma
l_int|0x0242
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
)brace
)brace
suffix:semicolon
DECL|variable|k2_sata_pci_driver
r_static
r_struct
id|pci_driver
id|k2_sata_pci_driver
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
id|k2_sata_pci_tbl
comma
dot
id|probe
op_assign
id|k2_sata_init_one
comma
dot
id|remove
op_assign
id|ata_pci_remove_one
comma
)brace
suffix:semicolon
DECL|function|k2_sata_init
r_static
r_int
id|__init
id|k2_sata_init
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
id|k2_sata_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|k2_sata_exit
r_static
r_void
id|__exit
id|k2_sata_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|k2_sata_pci_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Benjamin Herrenschmidt&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;low-level driver for K2 SATA controller&quot;
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
id|k2_sata_pci_tbl
)paren
suffix:semicolon
DECL|variable|DRV_VERSION
id|MODULE_VERSION
c_func
(paren
id|DRV_VERSION
)paren
suffix:semicolon
DECL|variable|k2_sata_init
id|module_init
c_func
(paren
id|k2_sata_init
)paren
suffix:semicolon
DECL|variable|k2_sata_exit
id|module_exit
c_func
(paren
id|k2_sata_exit
)paren
suffix:semicolon
eof
