multiline_comment|/*&n; *  sata_promise.c - Promise SATA&n; *&n; *  Maintained by:  Jeff Garzik &lt;jgarzik@pobox.com&gt;&n; *  &t;&t;    Please ALWAYS copy linux-ide@vger.kernel.org&n; *&t;&t;    on emails.&n; *&n; *  Copyright 2003-2004 Red Hat, Inc.&n; *&n; *  The contents of this file are subject to the Open&n; *  Software License version 1.1 that can be found at&n; *  http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n; *  by reference.&n; *&n; *  Alternatively, the contents of this file may be used under the terms&n; *  of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n; *  in the kernel source COPYING file, in which case the provisions of&n; *  the GPL are applicable instead of the above.  If you wish to allow&n; *  the use of your version of this file only under the terms of the&n; *  GPL and not to allow others to use your version of this file under&n; *  the OSL, indicate your decision by deleting the provisions above and&n; *  replace them with the notice and other provisions required by the GPL.&n; *  If you do not delete the provisions above, a recipient may use your&n; *  version of this file under either the OSL or the GPL.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;linux/libata.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;sata_promise.h&quot;
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME&t;&quot;sata_promise&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;1.00&quot;
r_enum
(brace
DECL|enumerator|PDC_PKT_SUBMIT
id|PDC_PKT_SUBMIT
op_assign
l_int|0x40
comma
multiline_comment|/* Command packet pointer addr */
DECL|enumerator|PDC_INT_SEQMASK
id|PDC_INT_SEQMASK
op_assign
l_int|0x40
comma
multiline_comment|/* Mask of asserted SEQ INTs */
DECL|enumerator|PDC_TBG_MODE
id|PDC_TBG_MODE
op_assign
l_int|0x41
comma
multiline_comment|/* TBG mode */
DECL|enumerator|PDC_FLASH_CTL
id|PDC_FLASH_CTL
op_assign
l_int|0x44
comma
multiline_comment|/* Flash control register */
DECL|enumerator|PDC_PCI_CTL
id|PDC_PCI_CTL
op_assign
l_int|0x48
comma
multiline_comment|/* PCI control and status register */
DECL|enumerator|PDC_GLOBAL_CTL
id|PDC_GLOBAL_CTL
op_assign
l_int|0x48
comma
multiline_comment|/* Global control/status (per port) */
DECL|enumerator|PDC_CTLSTAT
id|PDC_CTLSTAT
op_assign
l_int|0x60
comma
multiline_comment|/* IDE control and status (per port) */
DECL|enumerator|PDC_SATA_PLUG_CSR
id|PDC_SATA_PLUG_CSR
op_assign
l_int|0x6C
comma
multiline_comment|/* SATA Plug control/status reg */
DECL|enumerator|PDC_SLEW_CTL
id|PDC_SLEW_CTL
op_assign
l_int|0x470
comma
multiline_comment|/* slew rate control reg */
DECL|enumerator|PDC_ERR_MASK
id|PDC_ERR_MASK
op_assign
(paren
l_int|1
op_lshift
l_int|19
)paren
op_or
(paren
l_int|1
op_lshift
l_int|20
)paren
op_or
(paren
l_int|1
op_lshift
l_int|21
)paren
op_or
(paren
l_int|1
op_lshift
l_int|22
)paren
op_or
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
(paren
l_int|1
op_lshift
l_int|9
)paren
op_or
(paren
l_int|1
op_lshift
l_int|10
)paren
comma
DECL|enumerator|board_2037x
id|board_2037x
op_assign
l_int|0
comma
multiline_comment|/* FastTrak S150 TX2plus */
DECL|enumerator|board_20319
id|board_20319
op_assign
l_int|1
comma
multiline_comment|/* FastTrak S150 TX4 */
DECL|enumerator|PDC_HAS_PATA
id|PDC_HAS_PATA
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* PDC20375 has PATA */
DECL|enumerator|PDC_RESET
id|PDC_RESET
op_assign
(paren
l_int|1
op_lshift
l_int|11
)paren
comma
multiline_comment|/* HDMA reset */
)brace
suffix:semicolon
DECL|struct|pdc_port_priv
r_struct
id|pdc_port_priv
(brace
DECL|member|pkt
id|u8
op_star
id|pkt
suffix:semicolon
DECL|member|pkt_dma
id|dma_addr_t
id|pkt_dma
suffix:semicolon
)brace
suffix:semicolon
r_static
id|u32
id|pdc_sata_scr_read
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
id|pdc_sata_scr_write
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
r_int
id|pdc_ata_init_one
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
id|irqreturn_t
id|pdc_interrupt
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
r_void
id|pdc_eng_timeout
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
r_static
r_int
id|pdc_port_start
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
id|pdc_port_stop
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
id|pdc_phy_reset
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
id|pdc_qc_prep
c_func
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
suffix:semicolon
r_static
r_void
id|pdc_tf_load_mmio
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
suffix:semicolon
r_static
r_void
id|pdc_exec_command_mmio
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
suffix:semicolon
r_static
r_void
id|pdc_irq_clear
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
r_static
r_int
id|pdc_qc_issue_prot
c_func
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
suffix:semicolon
DECL|variable|pdc_ata_sht
r_static
id|Scsi_Host_Template
id|pdc_ata_sht
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
DECL|variable|pdc_ata_ops
r_static
r_struct
id|ata_port_operations
id|pdc_ata_ops
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
id|pdc_tf_load_mmio
comma
dot
id|tf_read
op_assign
id|ata_tf_read
comma
dot
id|check_status
op_assign
id|ata_check_status
comma
dot
id|exec_command
op_assign
id|pdc_exec_command_mmio
comma
dot
id|dev_select
op_assign
id|ata_std_dev_select
comma
dot
id|phy_reset
op_assign
id|pdc_phy_reset
comma
dot
id|qc_prep
op_assign
id|pdc_qc_prep
comma
dot
id|qc_issue
op_assign
id|pdc_qc_issue_prot
comma
dot
id|eng_timeout
op_assign
id|pdc_eng_timeout
comma
dot
id|irq_handler
op_assign
id|pdc_interrupt
comma
dot
id|irq_clear
op_assign
id|pdc_irq_clear
comma
dot
id|scr_read
op_assign
id|pdc_sata_scr_read
comma
dot
id|scr_write
op_assign
id|pdc_sata_scr_write
comma
dot
id|port_start
op_assign
id|pdc_port_start
comma
dot
id|port_stop
op_assign
id|pdc_port_stop
comma
)brace
suffix:semicolon
DECL|variable|pdc_port_info
r_static
r_struct
id|ata_port_info
id|pdc_port_info
(braket
)braket
op_assign
(brace
multiline_comment|/* board_2037x */
(brace
dot
id|sht
op_assign
op_amp
id|pdc_ata_sht
comma
dot
id|host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_NO_LEGACY
op_or
id|ATA_FLAG_SRST
op_or
id|ATA_FLAG_MMIO
comma
dot
id|pio_mask
op_assign
l_int|0x1f
comma
multiline_comment|/* pio0-4 */
dot
id|mwdma_mask
op_assign
l_int|0x07
comma
multiline_comment|/* mwdma0-2 */
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
id|pdc_ata_ops
comma
)brace
comma
multiline_comment|/* board_20319 */
(brace
dot
id|sht
op_assign
op_amp
id|pdc_ata_sht
comma
dot
id|host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_NO_LEGACY
op_or
id|ATA_FLAG_SRST
op_or
id|ATA_FLAG_MMIO
comma
dot
id|pio_mask
op_assign
l_int|0x1f
comma
multiline_comment|/* pio0-4 */
dot
id|mwdma_mask
op_assign
l_int|0x07
comma
multiline_comment|/* mwdma0-2 */
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
id|pdc_ata_ops
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|pdc_ata_pci_tbl
r_static
r_struct
id|pci_device_id
id|pdc_ata_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_PROMISE
comma
l_int|0x3371
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|board_2037x
)brace
comma
(brace
id|PCI_VENDOR_ID_PROMISE
comma
l_int|0x3373
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|board_2037x
)brace
comma
(brace
id|PCI_VENDOR_ID_PROMISE
comma
l_int|0x3375
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|board_2037x
)brace
comma
(brace
id|PCI_VENDOR_ID_PROMISE
comma
l_int|0x3376
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|board_2037x
)brace
comma
(brace
id|PCI_VENDOR_ID_PROMISE
comma
l_int|0x3318
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|board_20319
)brace
comma
(brace
id|PCI_VENDOR_ID_PROMISE
comma
l_int|0x3319
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|board_20319
)brace
comma
(brace
)brace
multiline_comment|/* terminate list */
)brace
suffix:semicolon
DECL|variable|pdc_ata_pci_driver
r_static
r_struct
id|pci_driver
id|pdc_ata_pci_driver
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
id|pdc_ata_pci_tbl
comma
dot
id|probe
op_assign
id|pdc_ata_init_one
comma
dot
id|remove
op_assign
id|ata_pci_remove_one
comma
)brace
suffix:semicolon
DECL|function|pdc_port_start
r_static
r_int
id|pdc_port_start
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|ap-&gt;host_set-&gt;dev
suffix:semicolon
r_struct
id|pdc_port_priv
op_star
id|pp
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|ata_port_start
c_func
(paren
id|ap
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
id|pp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|pp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pp
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|memset
c_func
(paren
id|pp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|pp
)paren
)paren
suffix:semicolon
id|pp-&gt;pkt
op_assign
id|dma_alloc_coherent
c_func
(paren
id|dev
comma
l_int|128
comma
op_amp
id|pp-&gt;pkt_dma
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pp-&gt;pkt
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_out_kfree
suffix:semicolon
)brace
id|ap-&gt;private_data
op_assign
id|pp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_kfree
suffix:colon
id|kfree
c_func
(paren
id|pp
)paren
suffix:semicolon
id|err_out
suffix:colon
id|ata_port_stop
c_func
(paren
id|ap
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|pdc_port_stop
r_static
r_void
id|pdc_port_stop
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|ap-&gt;host_set-&gt;dev
suffix:semicolon
r_struct
id|pdc_port_priv
op_star
id|pp
op_assign
id|ap-&gt;private_data
suffix:semicolon
id|ap-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
id|dma_free_coherent
c_func
(paren
id|dev
comma
l_int|128
comma
id|pp-&gt;pkt
comma
id|pp-&gt;pkt_dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pp
)paren
suffix:semicolon
id|ata_port_stop
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
DECL|function|pdc_reset_port
r_static
r_void
id|pdc_reset_port
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_void
op_star
id|mmio
op_assign
(paren
r_void
op_star
)paren
id|ap-&gt;ioaddr.cmd_addr
op_plus
id|PDC_CTLSTAT
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|11
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|tmp
op_assign
id|readl
c_func
(paren
id|mmio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|PDC_RESET
)paren
r_break
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|tmp
op_or_assign
id|PDC_RESET
suffix:semicolon
id|writel
c_func
(paren
id|tmp
comma
id|mmio
)paren
suffix:semicolon
)brace
id|tmp
op_and_assign
op_complement
id|PDC_RESET
suffix:semicolon
id|writel
c_func
(paren
id|tmp
comma
id|mmio
)paren
suffix:semicolon
id|readl
c_func
(paren
id|mmio
)paren
suffix:semicolon
multiline_comment|/* flush */
)brace
DECL|function|pdc_phy_reset
r_static
r_void
id|pdc_phy_reset
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
id|pdc_reset_port
c_func
(paren
id|ap
)paren
suffix:semicolon
id|sata_phy_reset
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
DECL|function|pdc_sata_scr_read
r_static
id|u32
id|pdc_sata_scr_read
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
DECL|function|pdc_sata_scr_write
r_static
r_void
id|pdc_sata_scr_write
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
DECL|function|pdc_qc_prep
r_static
r_void
id|pdc_qc_prep
c_func
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
(brace
r_struct
id|pdc_port_priv
op_star
id|pp
op_assign
id|qc-&gt;ap-&gt;private_data
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|VPRINTK
c_func
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|qc-&gt;tf.protocol
)paren
(brace
r_case
id|ATA_PROT_DMA
suffix:colon
id|ata_qc_prep
c_func
(paren
id|qc
)paren
suffix:semicolon
multiline_comment|/* fall through */
r_case
id|ATA_PROT_NODATA
suffix:colon
id|i
op_assign
id|pdc_pkt_header
c_func
(paren
op_amp
id|qc-&gt;tf
comma
id|qc-&gt;ap-&gt;prd_dma
comma
id|qc-&gt;dev-&gt;devno
comma
id|pp-&gt;pkt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qc-&gt;tf.flags
op_amp
id|ATA_TFLAG_LBA48
)paren
id|i
op_assign
id|pdc_prep_lba48
c_func
(paren
op_amp
id|qc-&gt;tf
comma
id|pp-&gt;pkt
comma
id|i
)paren
suffix:semicolon
r_else
id|i
op_assign
id|pdc_prep_lba28
c_func
(paren
op_amp
id|qc-&gt;tf
comma
id|pp-&gt;pkt
comma
id|i
)paren
suffix:semicolon
id|pdc_pkt_footer
c_func
(paren
op_amp
id|qc-&gt;tf
comma
id|pp-&gt;pkt
comma
id|i
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
DECL|function|pdc_eng_timeout
r_static
r_void
id|pdc_eng_timeout
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
id|u8
id|drv_stat
suffix:semicolon
r_struct
id|ata_queued_cmd
op_star
id|qc
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
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
op_logical_neg
id|qc
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ata%u: BUG: timeout without command&bslash;n&quot;
comma
id|ap-&gt;id
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* hack alert!  We cannot use the supplied completion&n;&t; * function from inside the -&gt;eh_strategy_handler() thread.&n;&t; * libata is the only user of -&gt;eh_strategy_handler() in&n;&t; * any kernel, so the default scsi_done() assumes it is&n;&t; * not being called from the SCSI EH.&n;&t; */
id|qc-&gt;scsidone
op_assign
id|scsi_finish_command
suffix:semicolon
r_switch
c_cond
(paren
id|qc-&gt;tf.protocol
)paren
(brace
r_case
id|ATA_PROT_DMA
suffix:colon
r_case
id|ATA_PROT_NODATA
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ata%u: command timeout&bslash;n&quot;
comma
id|ap-&gt;id
)paren
suffix:semicolon
id|ata_qc_complete
c_func
(paren
id|qc
comma
id|ata_wait_idle
c_func
(paren
id|ap
)paren
op_or
id|ATA_ERR
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|drv_stat
op_assign
id|ata_busy_wait
c_func
(paren
id|ap
comma
id|ATA_BUSY
op_or
id|ATA_DRQ
comma
l_int|1000
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ata%u: unknown timeout, cmd 0x%x stat 0x%x&bslash;n&quot;
comma
id|ap-&gt;id
comma
id|qc-&gt;tf.command
comma
id|drv_stat
)paren
suffix:semicolon
id|ata_qc_complete
c_func
(paren
id|qc
comma
id|drv_stat
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out
suffix:colon
id|DPRINTK
c_func
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|pdc_host_intr
r_static
r_inline
r_int
r_int
id|pdc_host_intr
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
(brace
id|u8
id|status
suffix:semicolon
r_int
r_int
id|handled
op_assign
l_int|0
comma
id|have_err
op_assign
l_int|0
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
r_void
op_star
id|mmio
op_assign
(paren
r_void
op_star
)paren
id|ap-&gt;ioaddr.cmd_addr
op_plus
id|PDC_GLOBAL_CTL
suffix:semicolon
id|tmp
op_assign
id|readl
c_func
(paren
id|mmio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|PDC_ERR_MASK
)paren
(brace
id|have_err
op_assign
l_int|1
suffix:semicolon
id|pdc_reset_port
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|qc-&gt;tf.protocol
)paren
(brace
r_case
id|ATA_PROT_DMA
suffix:colon
r_case
id|ATA_PROT_NODATA
suffix:colon
id|status
op_assign
id|ata_wait_idle
c_func
(paren
id|ap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|have_err
)paren
id|status
op_or_assign
id|ATA_ERR
suffix:semicolon
id|ata_qc_complete
c_func
(paren
id|qc
comma
id|status
)paren
suffix:semicolon
id|handled
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ap-&gt;stats.idle_irq
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|handled
suffix:semicolon
)brace
DECL|function|pdc_irq_clear
r_static
r_void
id|pdc_irq_clear
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_struct
id|ata_host_set
op_star
id|host_set
op_assign
id|ap-&gt;host_set
suffix:semicolon
r_void
op_star
id|mmio
op_assign
id|host_set-&gt;mmio_base
suffix:semicolon
id|readl
c_func
(paren
id|mmio
op_plus
id|PDC_INT_SEQMASK
)paren
suffix:semicolon
)brace
DECL|function|pdc_interrupt
r_static
id|irqreturn_t
id|pdc_interrupt
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
id|ata_port
op_star
id|ap
suffix:semicolon
id|u32
id|mask
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
comma
id|tmp
suffix:semicolon
r_int
r_int
id|handled
op_assign
l_int|0
suffix:semicolon
r_void
op_star
id|mmio_base
suffix:semicolon
id|VPRINTK
c_func
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host_set
op_logical_or
op_logical_neg
id|host_set-&gt;mmio_base
)paren
(brace
id|VPRINTK
c_func
(paren
l_string|&quot;QUICK EXIT&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
id|mmio_base
op_assign
id|host_set-&gt;mmio_base
suffix:semicolon
multiline_comment|/* reading should also clear interrupts */
id|mask
op_assign
id|readl
c_func
(paren
id|mmio_base
op_plus
id|PDC_INT_SEQMASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_eq
l_int|0xffffffff
)paren
(brace
id|VPRINTK
c_func
(paren
l_string|&quot;QUICK EXIT 2&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
id|mask
op_and_assign
l_int|0xffff
suffix:semicolon
multiline_comment|/* only 16 tags possible */
r_if
c_cond
(paren
op_logical_neg
id|mask
)paren
(brace
id|VPRINTK
c_func
(paren
l_string|&quot;QUICK EXIT 3&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|host_set-&gt;lock
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
id|VPRINTK
c_func
(paren
l_string|&quot;port %u&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|ap
op_assign
id|host_set-&gt;ports
(braket
id|i
)braket
suffix:semicolon
id|tmp
op_assign
id|mask
op_amp
(paren
l_int|1
op_lshift
(paren
id|i
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
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
id|pdc_host_intr
c_func
(paren
id|ap
comma
id|qc
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|host_set-&gt;lock
)paren
suffix:semicolon
id|VPRINTK
c_func
(paren
l_string|&quot;EXIT&bslash;n&quot;
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
DECL|function|pdc_packet_start
r_static
r_inline
r_void
id|pdc_packet_start
c_func
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
r_struct
id|pdc_port_priv
op_star
id|pp
op_assign
id|ap-&gt;private_data
suffix:semicolon
r_int
r_int
id|port_no
op_assign
id|ap-&gt;port_no
suffix:semicolon
id|u8
id|seq
op_assign
(paren
id|u8
)paren
(paren
id|port_no
op_plus
l_int|1
)paren
suffix:semicolon
id|VPRINTK
c_func
(paren
l_string|&quot;ENTER, ap %p&bslash;n&quot;
comma
id|ap
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0x00000001
comma
id|ap-&gt;host_set-&gt;mmio_base
op_plus
(paren
id|seq
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|readl
c_func
(paren
id|ap-&gt;host_set-&gt;mmio_base
op_plus
(paren
id|seq
op_star
l_int|4
)paren
)paren
suffix:semicolon
multiline_comment|/* flush */
id|pp-&gt;pkt
(braket
l_int|2
)braket
op_assign
id|seq
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* flush PRD, pkt writes */
id|writel
c_func
(paren
id|pp-&gt;pkt_dma
comma
(paren
r_void
op_star
)paren
id|ap-&gt;ioaddr.cmd_addr
op_plus
id|PDC_PKT_SUBMIT
)paren
suffix:semicolon
id|readl
c_func
(paren
(paren
r_void
op_star
)paren
id|ap-&gt;ioaddr.cmd_addr
op_plus
id|PDC_PKT_SUBMIT
)paren
suffix:semicolon
multiline_comment|/* flush */
)brace
DECL|function|pdc_qc_issue_prot
r_static
r_int
id|pdc_qc_issue_prot
c_func
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
(brace
r_switch
c_cond
(paren
id|qc-&gt;tf.protocol
)paren
(brace
r_case
id|ATA_PROT_DMA
suffix:colon
r_case
id|ATA_PROT_NODATA
suffix:colon
id|pdc_packet_start
c_func
(paren
id|qc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|ATA_PROT_ATAPI_DMA
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|ata_qc_issue_prot
c_func
(paren
id|qc
)paren
suffix:semicolon
)brace
DECL|function|pdc_tf_load_mmio
r_static
r_void
id|pdc_tf_load_mmio
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
id|WARN_ON
(paren
id|tf-&gt;protocol
op_eq
id|ATA_PROT_DMA
op_logical_or
id|tf-&gt;protocol
op_eq
id|ATA_PROT_NODATA
)paren
suffix:semicolon
id|ata_tf_load
c_func
(paren
id|ap
comma
id|tf
)paren
suffix:semicolon
)brace
DECL|function|pdc_exec_command_mmio
r_static
r_void
id|pdc_exec_command_mmio
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
id|WARN_ON
(paren
id|tf-&gt;protocol
op_eq
id|ATA_PROT_DMA
op_logical_or
id|tf-&gt;protocol
op_eq
id|ATA_PROT_NODATA
)paren
suffix:semicolon
id|ata_exec_command
c_func
(paren
id|ap
comma
id|tf
)paren
suffix:semicolon
)brace
DECL|function|pdc_ata_setup_port
r_static
r_void
id|pdc_ata_setup_port
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
suffix:semicolon
id|port-&gt;data_addr
op_assign
id|base
suffix:semicolon
id|port-&gt;feature_addr
op_assign
id|port-&gt;error_addr
op_assign
id|base
op_plus
l_int|0x4
suffix:semicolon
id|port-&gt;nsect_addr
op_assign
id|base
op_plus
l_int|0x8
suffix:semicolon
id|port-&gt;lbal_addr
op_assign
id|base
op_plus
l_int|0xc
suffix:semicolon
id|port-&gt;lbam_addr
op_assign
id|base
op_plus
l_int|0x10
suffix:semicolon
id|port-&gt;lbah_addr
op_assign
id|base
op_plus
l_int|0x14
suffix:semicolon
id|port-&gt;device_addr
op_assign
id|base
op_plus
l_int|0x18
suffix:semicolon
id|port-&gt;command_addr
op_assign
id|port-&gt;status_addr
op_assign
id|base
op_plus
l_int|0x1c
suffix:semicolon
id|port-&gt;altstatus_addr
op_assign
id|port-&gt;ctl_addr
op_assign
id|base
op_plus
l_int|0x38
suffix:semicolon
)brace
DECL|function|pdc_host_init
r_static
r_void
id|pdc_host_init
c_func
(paren
r_int
r_int
id|chip_id
comma
r_struct
id|ata_probe_ent
op_star
id|pe
)paren
(brace
r_void
op_star
id|mmio
op_assign
id|pe-&gt;mmio_base
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
multiline_comment|/*&n;&t; * Except for the hotplug stuff, this is voodoo from the&n;&t; * Promise driver.  Label this entire section&n;&t; * &quot;TODO: figure out why we do this&quot;&n;&t; */
multiline_comment|/* change FIFO_SHD to 8 dwords, enable BMR_BURST */
id|tmp
op_assign
id|readl
c_func
(paren
id|mmio
op_plus
id|PDC_FLASH_CTL
)paren
suffix:semicolon
id|tmp
op_or_assign
l_int|0x12000
suffix:semicolon
multiline_comment|/* bit 16 (fifo 8 dw) and 13 (bmr burst?) */
id|writel
c_func
(paren
id|tmp
comma
id|mmio
op_plus
id|PDC_FLASH_CTL
)paren
suffix:semicolon
multiline_comment|/* clear plug/unplug flags for all ports */
id|tmp
op_assign
id|readl
c_func
(paren
id|mmio
op_plus
id|PDC_SATA_PLUG_CSR
)paren
suffix:semicolon
id|writel
c_func
(paren
id|tmp
op_or
l_int|0xff
comma
id|mmio
op_plus
id|PDC_SATA_PLUG_CSR
)paren
suffix:semicolon
multiline_comment|/* mask plug/unplug ints */
id|tmp
op_assign
id|readl
c_func
(paren
id|mmio
op_plus
id|PDC_SATA_PLUG_CSR
)paren
suffix:semicolon
id|writel
c_func
(paren
id|tmp
op_or
l_int|0xff0000
comma
id|mmio
op_plus
id|PDC_SATA_PLUG_CSR
)paren
suffix:semicolon
multiline_comment|/* reduce TBG clock to 133 Mhz. */
id|tmp
op_assign
id|readl
c_func
(paren
id|mmio
op_plus
id|PDC_TBG_MODE
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
l_int|0x30000
suffix:semicolon
multiline_comment|/* clear bit 17, 16*/
id|tmp
op_or_assign
l_int|0x10000
suffix:semicolon
multiline_comment|/* set bit 17:16 = 0:1 */
id|writel
c_func
(paren
id|tmp
comma
id|mmio
op_plus
id|PDC_TBG_MODE
)paren
suffix:semicolon
id|readl
c_func
(paren
id|mmio
op_plus
id|PDC_TBG_MODE
)paren
suffix:semicolon
multiline_comment|/* flush */
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* adjust slew rate control register. */
id|tmp
op_assign
id|readl
c_func
(paren
id|mmio
op_plus
id|PDC_SLEW_CTL
)paren
suffix:semicolon
id|tmp
op_and_assign
l_int|0xFFFFF03F
suffix:semicolon
multiline_comment|/* clear bit 11 ~ 6 */
id|tmp
op_or_assign
l_int|0x00000900
suffix:semicolon
multiline_comment|/* set bit 11-9 = 100b , bit 8-6 = 100 */
id|writel
c_func
(paren
id|tmp
comma
id|mmio
op_plus
id|PDC_SLEW_CTL
)paren
suffix:semicolon
)brace
DECL|function|pdc_ata_init_one
r_static
r_int
id|pdc_ata_init_one
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
r_int
id|board_idx
op_assign
(paren
r_int
r_int
)paren
id|ent-&gt;driver_data
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
l_int|3
)paren
comma
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|3
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
id|probe_ent-&gt;sht
op_assign
id|pdc_port_info
(braket
id|board_idx
)braket
dot
id|sht
suffix:semicolon
id|probe_ent-&gt;host_flags
op_assign
id|pdc_port_info
(braket
id|board_idx
)braket
dot
id|host_flags
suffix:semicolon
id|probe_ent-&gt;pio_mask
op_assign
id|pdc_port_info
(braket
id|board_idx
)braket
dot
id|pio_mask
suffix:semicolon
id|probe_ent-&gt;mwdma_mask
op_assign
id|pdc_port_info
(braket
id|board_idx
)braket
dot
id|mwdma_mask
suffix:semicolon
id|probe_ent-&gt;udma_mask
op_assign
id|pdc_port_info
(braket
id|board_idx
)braket
dot
id|udma_mask
suffix:semicolon
id|probe_ent-&gt;port_ops
op_assign
id|pdc_port_info
(braket
id|board_idx
)braket
dot
id|port_ops
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
id|pdc_ata_setup_port
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
l_int|0x200
)paren
suffix:semicolon
id|pdc_ata_setup_port
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
l_int|0x280
)paren
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
l_int|0x400
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
l_int|0x500
suffix:semicolon
multiline_comment|/* notice 4-port boards */
r_switch
c_cond
(paren
id|board_idx
)paren
(brace
r_case
id|board_20319
suffix:colon
id|probe_ent-&gt;n_ports
op_assign
l_int|4
suffix:semicolon
id|pdc_ata_setup_port
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
l_int|0x300
)paren
suffix:semicolon
id|pdc_ata_setup_port
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
l_int|0x380
)paren
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|2
)braket
dot
id|scr_addr
op_assign
id|base
op_plus
l_int|0x600
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|3
)braket
dot
id|scr_addr
op_assign
id|base
op_plus
l_int|0x700
suffix:semicolon
r_break
suffix:semicolon
r_case
id|board_2037x
suffix:colon
id|probe_ent-&gt;n_ports
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pci_set_master
c_func
(paren
id|pdev
)paren
suffix:semicolon
multiline_comment|/* initialize adapter */
id|pdc_host_init
c_func
(paren
id|board_idx
comma
id|probe_ent
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
DECL|function|pdc_ata_init
r_static
r_int
id|__init
id|pdc_ata_init
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
id|pdc_ata_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|pdc_ata_exit
r_static
r_void
id|__exit
id|pdc_ata_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|pdc_ata_pci_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jeff Garzik&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Promise SATA TX2/TX4 low-level driver&quot;
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
id|pdc_ata_pci_tbl
)paren
suffix:semicolon
DECL|variable|pdc_ata_init
id|module_init
c_func
(paren
id|pdc_ata_init
)paren
suffix:semicolon
DECL|variable|pdc_ata_exit
id|module_exit
c_func
(paren
id|pdc_ata_exit
)paren
suffix:semicolon
eof
