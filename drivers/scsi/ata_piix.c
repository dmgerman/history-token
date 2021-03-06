multiline_comment|/*&n;&n;    ata_piix.c - Intel PATA/SATA controllers&n;&n;    Maintained by:  Jeff Garzik &lt;jgarzik@pobox.com&gt;&n;    &t;&t;    Please ALWAYS copy linux-ide@vger.kernel.org&n;&t;&t;    on emails.&n;&n;&n;&t;Copyright 2003-2004 Red Hat Inc&n;&t;Copyright 2003-2004 Jeff Garzik&n;&n;&n;&t;Copyright header from piix.c:&n;&n;    Copyright (C) 1998-1999 Andrzej Krzysztofowicz, Author and Maintainer&n;    Copyright (C) 1998-2000 Andre Hedrick &lt;andre@linux-ide.org&gt;&n;    Copyright (C) 2003 Red Hat Inc &lt;alan@redhat.com&gt;&n;&n;    May be copied or modified under the terms of the GNU General Public License&n;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;linux/libata.h&gt;
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME&t;&quot;ata_piix&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;1.03&quot;
r_enum
(brace
DECL|enumerator|PIIX_IOCFG
id|PIIX_IOCFG
op_assign
l_int|0x54
comma
multiline_comment|/* IDE I/O configuration register */
DECL|enumerator|ICH5_PMR
id|ICH5_PMR
op_assign
l_int|0x90
comma
multiline_comment|/* port mapping register */
DECL|enumerator|ICH5_PCS
id|ICH5_PCS
op_assign
l_int|0x92
comma
multiline_comment|/* port control and status */
DECL|enumerator|PIIX_FLAG_AHCI
id|PIIX_FLAG_AHCI
op_assign
(paren
l_int|1
op_lshift
l_int|28
)paren
comma
multiline_comment|/* AHCI possible */
DECL|enumerator|PIIX_FLAG_CHECKINTR
id|PIIX_FLAG_CHECKINTR
op_assign
(paren
l_int|1
op_lshift
l_int|29
)paren
comma
multiline_comment|/* make sure PCI INTx enabled */
DECL|enumerator|PIIX_FLAG_COMBINED
id|PIIX_FLAG_COMBINED
op_assign
(paren
l_int|1
op_lshift
l_int|30
)paren
comma
multiline_comment|/* combined mode possible */
multiline_comment|/* combined mode.  if set, PATA is channel 0.&n;&t; * if clear, PATA is channel 1.&n;&t; */
DECL|enumerator|PIIX_COMB_PATA_P0
id|PIIX_COMB_PATA_P0
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
DECL|enumerator|PIIX_COMB
id|PIIX_COMB
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* combined mode enabled? */
DECL|enumerator|PIIX_PORT_PRESENT
id|PIIX_PORT_PRESENT
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
DECL|enumerator|PIIX_PORT_ENABLED
id|PIIX_PORT_ENABLED
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
DECL|enumerator|PIIX_80C_PRI
id|PIIX_80C_PRI
op_assign
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
DECL|enumerator|PIIX_80C_SEC
id|PIIX_80C_SEC
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
comma
DECL|enumerator|ich5_pata
id|ich5_pata
op_assign
l_int|0
comma
DECL|enumerator|ich5_sata
id|ich5_sata
op_assign
l_int|1
comma
DECL|enumerator|piix4_pata
id|piix4_pata
op_assign
l_int|2
comma
DECL|enumerator|ich6_sata
id|ich6_sata
op_assign
l_int|3
comma
DECL|enumerator|ich6_sata_rm
id|ich6_sata_rm
op_assign
l_int|4
comma
DECL|enumerator|ich7_sata
id|ich7_sata
op_assign
l_int|5
comma
)brace
suffix:semicolon
r_static
r_int
id|piix_init_one
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
id|piix_pata_phy_reset
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
id|piix_sata_phy_reset
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
id|piix_set_piomode
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_device
op_star
id|adev
)paren
suffix:semicolon
r_static
r_void
id|piix_set_dmamode
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_device
op_star
id|adev
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
DECL|variable|piix_pci_tbl
r_static
r_struct
id|pci_device_id
id|piix_pci_tbl
(braket
)braket
op_assign
(brace
macro_line|#ifdef ATA_ENABLE_PATA
(brace
l_int|0x8086
comma
l_int|0x7111
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|piix4_pata
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x24db
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ich5_pata
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x25a2
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ich5_pata
)brace
comma
macro_line|#endif
multiline_comment|/* NOTE: The following PCI ids must be kept in sync with the&n;&t; * list in drivers/pci/quirks.c.&n;&t; */
(brace
l_int|0x8086
comma
l_int|0x24d1
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ich5_sata
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x24df
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ich5_sata
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x25a3
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ich5_sata
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x25b0
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ich5_sata
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x2651
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ich6_sata
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x2652
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ich6_sata_rm
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x2653
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ich6_sata_rm
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x27c0
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ich7_sata
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x27c4
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ich7_sata
)brace
comma
(brace
)brace
multiline_comment|/* terminate list */
)brace
suffix:semicolon
DECL|variable|piix_pci_driver
r_static
r_struct
id|pci_driver
id|piix_pci_driver
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
id|piix_pci_tbl
comma
dot
id|probe
op_assign
id|piix_init_one
comma
dot
id|remove
op_assign
id|ata_pci_remove_one
comma
)brace
suffix:semicolon
DECL|variable|piix_sht
r_static
id|Scsi_Host_Template
id|piix_sht
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
dot
id|ordered_flush
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|piix_pata_ops
r_static
r_struct
id|ata_port_operations
id|piix_pata_ops
op_assign
(brace
dot
id|port_disable
op_assign
id|ata_port_disable
comma
dot
id|set_piomode
op_assign
id|piix_set_piomode
comma
dot
id|set_dmamode
op_assign
id|piix_set_dmamode
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
id|check_status
op_assign
id|ata_check_status
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
id|piix_pata_phy_reset
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
id|bmdma_stop
op_assign
id|ata_bmdma_stop
comma
dot
id|bmdma_status
op_assign
id|ata_bmdma_status
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
DECL|variable|piix_sata_ops
r_static
r_struct
id|ata_port_operations
id|piix_sata_ops
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
id|check_status
op_assign
id|ata_check_status
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
id|piix_sata_phy_reset
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
id|bmdma_stop
op_assign
id|ata_bmdma_stop
comma
dot
id|bmdma_status
op_assign
id|ata_bmdma_status
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
DECL|variable|piix_port_info
r_static
r_struct
id|ata_port_info
id|piix_port_info
(braket
)braket
op_assign
(brace
multiline_comment|/* ich5_pata */
(brace
dot
id|sht
op_assign
op_amp
id|piix_sht
comma
dot
id|host_flags
op_assign
id|ATA_FLAG_SLAVE_POSS
op_or
id|ATA_FLAG_SRST
op_or
id|PIIX_FLAG_CHECKINTR
comma
dot
id|pio_mask
op_assign
l_int|0x1f
comma
multiline_comment|/* pio0-4 */
macro_line|#if 0
dot
id|mwdma_mask
op_assign
l_int|0x06
comma
multiline_comment|/* mwdma1-2 */
macro_line|#else
dot
id|mwdma_mask
op_assign
l_int|0x00
comma
multiline_comment|/* mwdma broken */
macro_line|#endif
dot
id|udma_mask
op_assign
l_int|0x3f
comma
multiline_comment|/* udma0-5 */
dot
id|port_ops
op_assign
op_amp
id|piix_pata_ops
comma
)brace
comma
multiline_comment|/* ich5_sata */
(brace
dot
id|sht
op_assign
op_amp
id|piix_sht
comma
dot
id|host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_SRST
op_or
id|PIIX_FLAG_COMBINED
op_or
id|PIIX_FLAG_CHECKINTR
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
multiline_comment|/* udma0-6 */
dot
id|port_ops
op_assign
op_amp
id|piix_sata_ops
comma
)brace
comma
multiline_comment|/* piix4_pata */
(brace
dot
id|sht
op_assign
op_amp
id|piix_sht
comma
dot
id|host_flags
op_assign
id|ATA_FLAG_SLAVE_POSS
op_or
id|ATA_FLAG_SRST
comma
dot
id|pio_mask
op_assign
l_int|0x1f
comma
multiline_comment|/* pio0-4 */
macro_line|#if 0
dot
id|mwdma_mask
op_assign
l_int|0x06
comma
multiline_comment|/* mwdma1-2 */
macro_line|#else
dot
id|mwdma_mask
op_assign
l_int|0x00
comma
multiline_comment|/* mwdma broken */
macro_line|#endif
dot
id|udma_mask
op_assign
id|ATA_UDMA_MASK_40C
comma
dot
id|port_ops
op_assign
op_amp
id|piix_pata_ops
comma
)brace
comma
multiline_comment|/* ich6_sata */
(brace
dot
id|sht
op_assign
op_amp
id|piix_sht
comma
dot
id|host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_SRST
op_or
id|PIIX_FLAG_COMBINED
op_or
id|PIIX_FLAG_CHECKINTR
op_or
id|ATA_FLAG_SLAVE_POSS
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
multiline_comment|/* udma0-6 */
dot
id|port_ops
op_assign
op_amp
id|piix_sata_ops
comma
)brace
comma
multiline_comment|/* ich6_sata_rm */
(brace
dot
id|sht
op_assign
op_amp
id|piix_sht
comma
dot
id|host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_SRST
op_or
id|PIIX_FLAG_COMBINED
op_or
id|PIIX_FLAG_CHECKINTR
op_or
id|ATA_FLAG_SLAVE_POSS
op_or
id|PIIX_FLAG_AHCI
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
multiline_comment|/* udma0-6 */
dot
id|port_ops
op_assign
op_amp
id|piix_sata_ops
comma
)brace
comma
multiline_comment|/* ich7_sata */
(brace
dot
id|sht
op_assign
op_amp
id|piix_sht
comma
dot
id|host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_SRST
op_or
id|PIIX_FLAG_COMBINED
op_or
id|PIIX_FLAG_CHECKINTR
op_or
id|ATA_FLAG_SLAVE_POSS
op_or
id|PIIX_FLAG_AHCI
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
multiline_comment|/* udma0-6 */
dot
id|port_ops
op_assign
op_amp
id|piix_sata_ops
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|piix_enable_bits
r_static
r_struct
id|pci_bits
id|piix_enable_bits
(braket
)braket
op_assign
(brace
(brace
l_int|0x41U
comma
l_int|1U
comma
l_int|0x80UL
comma
l_int|0x80UL
)brace
comma
multiline_comment|/* port 0 */
(brace
l_int|0x43U
comma
l_int|1U
comma
l_int|0x80UL
comma
l_int|0x80UL
)brace
comma
multiline_comment|/* port 1 */
)brace
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andre Hedrick, Alan Cox, Andrzej Krzysztofowicz, Jeff Garzik&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SCSI low-level driver for Intel PIIX/ICH ATA controllers&quot;
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
id|piix_pci_tbl
)paren
suffix:semicolon
DECL|variable|DRV_VERSION
id|MODULE_VERSION
c_func
(paren
id|DRV_VERSION
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;piix_pata_cbl_detect - Probe host controller cable detect info&n; *&t;@ap: Port for which cable detect info is desired&n; *&n; *&t;Read 80c cable indicator from ATA PCI device&squot;s PCI config&n; *&t;register.  This register is normally set by firmware (BIOS).&n; *&n; *&t;LOCKING:&n; *&t;None (inherited from caller).&n; */
DECL|function|piix_pata_cbl_detect
r_static
r_void
id|piix_pata_cbl_detect
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|to_pci_dev
c_func
(paren
id|ap-&gt;host_set-&gt;dev
)paren
suffix:semicolon
id|u8
id|tmp
comma
id|mask
suffix:semicolon
multiline_comment|/* no 80c support in host controller? */
r_if
c_cond
(paren
(paren
id|ap-&gt;udma_mask
op_amp
op_complement
id|ATA_UDMA_MASK_40C
)paren
op_eq
l_int|0
)paren
r_goto
id|cbl40
suffix:semicolon
multiline_comment|/* check BIOS cable detect results */
id|mask
op_assign
id|ap-&gt;hard_port_no
op_eq
l_int|0
ques
c_cond
id|PIIX_80C_PRI
suffix:colon
id|PIIX_80C_SEC
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
id|PIIX_IOCFG
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp
op_amp
id|mask
)paren
op_eq
l_int|0
)paren
r_goto
id|cbl40
suffix:semicolon
id|ap-&gt;cbl
op_assign
id|ATA_CBL_PATA80
suffix:semicolon
r_return
suffix:semicolon
id|cbl40
suffix:colon
id|ap-&gt;cbl
op_assign
id|ATA_CBL_PATA40
suffix:semicolon
id|ap-&gt;udma_mask
op_and_assign
id|ATA_UDMA_MASK_40C
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;piix_pata_phy_reset - Probe specified port on PATA host controller&n; *&t;@ap: Port to probe&n; *&n; *&t;Probe PATA phy.&n; *&n; *&t;LOCKING:&n; *&t;None (inherited from caller).&n; */
DECL|function|piix_pata_phy_reset
r_static
r_void
id|piix_pata_phy_reset
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|to_pci_dev
c_func
(paren
id|ap-&gt;host_set-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_test_config_bits
c_func
(paren
id|pdev
comma
op_amp
id|piix_enable_bits
(braket
id|ap-&gt;hard_port_no
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
id|piix_pata_cbl_detect
c_func
(paren
id|ap
)paren
suffix:semicolon
id|ata_port_probe
c_func
(paren
id|ap
)paren
suffix:semicolon
id|ata_bus_reset
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;piix_sata_probe - Probe PCI device for present SATA devices&n; *&t;@ap: Port associated with the PCI device we wish to probe&n; *&n; *&t;Reads SATA PCI device&squot;s PCI config register Port Configuration&n; *&t;and Status (PCS) to determine port and device availability.&n; *&n; *&t;LOCKING:&n; *&t;None (inherited from caller).&n; *&n; *&t;RETURNS:&n; *&t;Non-zero if device detected, zero otherwise.&n; */
DECL|function|piix_sata_probe
r_static
r_int
id|piix_sata_probe
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|to_pci_dev
c_func
(paren
id|ap-&gt;host_set-&gt;dev
)paren
suffix:semicolon
r_int
id|combined
op_assign
(paren
id|ap-&gt;flags
op_amp
id|ATA_FLAG_SLAVE_POSS
)paren
suffix:semicolon
r_int
id|orig_mask
comma
id|mask
comma
id|i
suffix:semicolon
id|u8
id|pcs
suffix:semicolon
id|mask
op_assign
(paren
id|PIIX_PORT_PRESENT
op_lshift
id|ap-&gt;hard_port_no
)paren
op_or
(paren
id|PIIX_PORT_ENABLED
op_lshift
id|ap-&gt;hard_port_no
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
id|ICH5_PCS
comma
op_amp
id|pcs
)paren
suffix:semicolon
id|orig_mask
op_assign
(paren
r_int
)paren
id|pcs
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* TODO: this is vaguely wrong for ICH6 combined mode,&n;&t; * where only two of the four SATA ports are mapped&n;&t; * onto a single ATA channel.  It is also vaguely inaccurate&n;&t; * for ICH5, which has only two ports.  However, this is ok,&n;&t; * as further device presence detection code will handle&n;&t; * any false positives produced here.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mask
op_assign
(paren
id|PIIX_PORT_PRESENT
op_lshift
id|i
)paren
op_or
(paren
id|PIIX_PORT_ENABLED
op_lshift
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|orig_mask
op_amp
id|mask
)paren
op_eq
id|mask
)paren
r_if
c_cond
(paren
id|combined
op_logical_or
(paren
id|i
op_eq
id|ap-&gt;hard_port_no
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;piix_sata_phy_reset - Probe specified port on SATA host controller&n; *&t;@ap: Port to probe&n; *&n; *&t;Probe SATA phy.&n; *&n; *&t;LOCKING:&n; *&t;None (inherited from caller).&n; */
DECL|function|piix_sata_phy_reset
r_static
r_void
id|piix_sata_phy_reset
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
id|piix_sata_probe
c_func
(paren
id|ap
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
l_string|&quot;ata%u: SATA port has no device.&bslash;n&quot;
comma
id|ap-&gt;id
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ap-&gt;cbl
op_assign
id|ATA_CBL_SATA
suffix:semicolon
id|ata_port_probe
c_func
(paren
id|ap
)paren
suffix:semicolon
id|ata_bus_reset
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;piix_set_piomode - Initialize host controller PATA PIO timings&n; *&t;@ap: Port whose timings we are configuring&n; *&t;@adev: um&n; *&t;@pio: PIO mode, 0 - 4&n; *&n; *&t;Set PIO mode for device, in host controller PCI config space.&n; *&n; *&t;LOCKING:&n; *&t;None (inherited from caller).&n; */
DECL|function|piix_set_piomode
r_static
r_void
id|piix_set_piomode
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_device
op_star
id|adev
)paren
(brace
r_int
r_int
id|pio
op_assign
id|adev-&gt;pio_mode
op_minus
id|XFER_PIO_0
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|to_pci_dev
c_func
(paren
id|ap-&gt;host_set-&gt;dev
)paren
suffix:semicolon
r_int
r_int
id|is_slave
op_assign
(paren
id|adev-&gt;devno
op_ne
l_int|0
)paren
suffix:semicolon
r_int
r_int
id|master_port
op_assign
id|ap-&gt;hard_port_no
ques
c_cond
l_int|0x42
suffix:colon
l_int|0x40
suffix:semicolon
r_int
r_int
id|slave_port
op_assign
l_int|0x44
suffix:semicolon
id|u16
id|master_data
suffix:semicolon
id|u8
id|slave_data
suffix:semicolon
r_static
r_const
multiline_comment|/* ISP  RTC */
id|u8
id|timings
(braket
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|2
comma
l_int|1
)brace
comma
(brace
l_int|2
comma
l_int|3
)brace
comma
)brace
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|master_port
comma
op_amp
id|master_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_slave
)paren
(brace
id|master_data
op_or_assign
l_int|0x4000
suffix:semicolon
multiline_comment|/* enable PPE, IE and TIME */
id|master_data
op_or_assign
l_int|0x0070
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|slave_port
comma
op_amp
id|slave_data
)paren
suffix:semicolon
id|slave_data
op_and_assign
(paren
id|ap-&gt;hard_port_no
ques
c_cond
l_int|0x0f
suffix:colon
l_int|0xf0
)paren
suffix:semicolon
id|slave_data
op_or_assign
(paren
id|timings
(braket
id|pio
)braket
(braket
l_int|0
)braket
op_lshift
l_int|2
)paren
op_or
(paren
id|timings
(braket
id|pio
)braket
(braket
l_int|1
)braket
op_lshift
(paren
id|ap-&gt;hard_port_no
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|master_data
op_and_assign
l_int|0xccf8
suffix:semicolon
multiline_comment|/* enable PPE, IE and TIME */
id|master_data
op_or_assign
l_int|0x0007
suffix:semicolon
id|master_data
op_or_assign
(paren
id|timings
(braket
id|pio
)braket
(braket
l_int|0
)braket
op_lshift
l_int|12
)paren
op_or
(paren
id|timings
(braket
id|pio
)braket
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|master_port
comma
id|master_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_slave
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|slave_port
comma
id|slave_data
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;piix_set_dmamode - Initialize host controller PATA PIO timings&n; *&t;@ap: Port whose timings we are configuring&n; *&t;@adev: um&n; *&t;@udma: udma mode, 0 - 6&n; *&n; *&t;Set UDMA mode for device, in host controller PCI config space.&n; *&n; *&t;LOCKING:&n; *&t;None (inherited from caller).&n; */
DECL|function|piix_set_dmamode
r_static
r_void
id|piix_set_dmamode
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_device
op_star
id|adev
)paren
(brace
r_int
r_int
id|udma
op_assign
id|adev-&gt;dma_mode
suffix:semicolon
multiline_comment|/* FIXME: MWDMA too */
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|to_pci_dev
c_func
(paren
id|ap-&gt;host_set-&gt;dev
)paren
suffix:semicolon
id|u8
id|maslave
op_assign
id|ap-&gt;hard_port_no
ques
c_cond
l_int|0x42
suffix:colon
l_int|0x40
suffix:semicolon
id|u8
id|speed
op_assign
id|udma
suffix:semicolon
r_int
r_int
id|drive_dn
op_assign
(paren
id|ap-&gt;hard_port_no
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
op_plus
id|adev-&gt;devno
suffix:semicolon
r_int
id|a_speed
op_assign
l_int|3
op_lshift
(paren
id|drive_dn
op_star
l_int|4
)paren
suffix:semicolon
r_int
id|u_flag
op_assign
l_int|1
op_lshift
id|drive_dn
suffix:semicolon
r_int
id|v_flag
op_assign
l_int|0x01
op_lshift
id|drive_dn
suffix:semicolon
r_int
id|w_flag
op_assign
l_int|0x10
op_lshift
id|drive_dn
suffix:semicolon
r_int
id|u_speed
op_assign
l_int|0
suffix:semicolon
r_int
id|sitre
suffix:semicolon
id|u16
id|reg4042
comma
id|reg4a
suffix:semicolon
id|u8
id|reg48
comma
id|reg54
comma
id|reg55
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|maslave
comma
op_amp
id|reg4042
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;reg4042 = 0x%04x&bslash;n&quot;
comma
id|reg4042
)paren
suffix:semicolon
id|sitre
op_assign
(paren
id|reg4042
op_amp
l_int|0x4000
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x48
comma
op_amp
id|reg48
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
op_amp
id|reg4a
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x54
comma
op_amp
id|reg54
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x55
comma
op_amp
id|reg55
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|speed
)paren
(brace
r_case
id|XFER_UDMA_4
suffix:colon
r_case
id|XFER_UDMA_2
suffix:colon
id|u_speed
op_assign
l_int|2
op_lshift
(paren
id|drive_dn
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_6
suffix:colon
r_case
id|XFER_UDMA_5
suffix:colon
r_case
id|XFER_UDMA_3
suffix:colon
r_case
id|XFER_UDMA_1
suffix:colon
id|u_speed
op_assign
l_int|1
op_lshift
(paren
id|drive_dn
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_0
suffix:colon
id|u_speed
op_assign
l_int|0
op_lshift
(paren
id|drive_dn
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_2
suffix:colon
r_case
id|XFER_MW_DMA_1
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|speed
op_ge
id|XFER_UDMA_0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg48
op_amp
id|u_flag
)paren
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x48
comma
id|reg48
op_or
id|u_flag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|speed
op_eq
id|XFER_UDMA_5
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x55
comma
(paren
id|u8
)paren
id|reg55
op_or
id|w_flag
)paren
suffix:semicolon
)brace
r_else
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x55
comma
(paren
id|u8
)paren
id|reg55
op_amp
op_complement
id|w_flag
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|reg4a
op_amp
id|a_speed
)paren
op_ne
id|u_speed
)paren
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
(paren
id|reg4a
op_amp
op_complement
id|a_speed
)paren
op_or
id|u_speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|speed
OG
id|XFER_UDMA_2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg54
op_amp
id|v_flag
)paren
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x54
comma
id|reg54
op_or
id|v_flag
)paren
suffix:semicolon
)brace
r_else
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x54
comma
id|reg54
op_amp
op_complement
id|v_flag
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|reg48
op_amp
id|u_flag
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x48
comma
id|reg48
op_amp
op_complement
id|u_flag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg4a
op_amp
id|a_speed
)paren
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
id|reg4a
op_amp
op_complement
id|a_speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg54
op_amp
id|v_flag
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x54
comma
id|reg54
op_amp
op_complement
id|v_flag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg55
op_amp
id|w_flag
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x55
comma
(paren
id|u8
)paren
id|reg55
op_amp
op_complement
id|w_flag
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* move to PCI layer, integrate w/ MSI stuff */
DECL|function|pci_enable_intx
r_static
r_void
id|pci_enable_intx
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|u16
id|pci_command
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|pdev
comma
id|PCI_COMMAND
comma
op_amp
id|pci_command
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_command
op_amp
id|PCI_COMMAND_INTX_DISABLE
)paren
(brace
id|pci_command
op_and_assign
op_complement
id|PCI_COMMAND_INTX_DISABLE
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|pdev
comma
id|PCI_COMMAND
comma
id|pci_command
)paren
suffix:semicolon
)brace
)brace
DECL|macro|AHCI_PCI_BAR
mdefine_line|#define AHCI_PCI_BAR 5
DECL|macro|AHCI_GLOBAL_CTL
mdefine_line|#define AHCI_GLOBAL_CTL 0x04
DECL|macro|AHCI_ENABLE
mdefine_line|#define AHCI_ENABLE (1 &lt;&lt; 31)
DECL|function|piix_disable_ahci
r_static
r_int
id|piix_disable_ahci
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_void
op_star
id|mmio
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* BUG: pci_enable_device has not yet been called.  This&n;&t; * works because this device is usually set up by BIOS.&n;&t; */
id|addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
id|AHCI_PCI_BAR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
op_logical_or
op_logical_neg
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|AHCI_PCI_BAR
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|mmio
op_assign
id|ioremap
c_func
(paren
id|addr
comma
l_int|64
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mmio
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|tmp
op_assign
id|readl
c_func
(paren
id|mmio
op_plus
id|AHCI_GLOBAL_CTL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AHCI_ENABLE
)paren
(brace
id|tmp
op_and_assign
op_complement
id|AHCI_ENABLE
suffix:semicolon
id|writel
c_func
(paren
id|tmp
comma
id|mmio
op_plus
id|AHCI_GLOBAL_CTL
)paren
suffix:semicolon
id|tmp
op_assign
id|readl
c_func
(paren
id|mmio
op_plus
id|AHCI_GLOBAL_CTL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AHCI_ENABLE
)paren
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|mmio
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;piix_init_one - Register PIIX ATA PCI device with kernel services&n; *&t;@pdev: PCI device to register&n; *&t;@ent: Entry in piix_pci_tbl matching with @pdev&n; *&n; *&t;Called from kernel PCI layer.  We probe for combined mode (sigh),&n; *&t;and then hand over control to libata, for it to do the rest.&n; *&n; *&t;LOCKING:&n; *&t;Inherited from PCI layer (may sleep).&n; *&n; *&t;RETURNS:&n; *&t;Zero on success, or -ERRNO value.&n; */
DECL|function|piix_init_one
r_static
r_int
id|piix_init_one
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
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|combined
op_assign
l_int|0
comma
id|n_ports
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|pata_chan
op_assign
l_int|0
comma
id|sata_chan
op_assign
l_int|0
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
id|piix_port_info
(braket
id|ent-&gt;driver_data
)braket
suffix:semicolon
id|port_info
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|port_info
(braket
l_int|0
)braket
op_member_access_from_pointer
id|host_flags
op_amp
id|PIIX_FLAG_AHCI
)paren
(brace
r_int
id|rc
op_assign
id|piix_disable_ahci
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
)brace
r_if
c_cond
(paren
id|port_info
(braket
l_int|0
)braket
op_member_access_from_pointer
id|host_flags
op_amp
id|PIIX_FLAG_COMBINED
)paren
(brace
id|u8
id|tmp
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
id|ICH5_PMR
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|PIIX_COMB
)paren
(brace
id|combined
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|PIIX_COMB_PATA_P0
)paren
id|sata_chan
op_assign
l_int|1
suffix:semicolon
r_else
id|pata_chan
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* On ICH5, some BIOSen disable the interrupt using the&n;&t; * PCI_COMMAND_INTX_DISABLE bit added in PCI 2.3.&n;&t; * On ICH6, this bit has the same effect, but only when&n;&t; * MSI is disabled (and it is disabled, as we don&squot;t use&n;&t; * message-signalled interrupts currently).&n;&t; */
r_if
c_cond
(paren
id|port_info
(braket
l_int|0
)braket
op_member_access_from_pointer
id|host_flags
op_amp
id|PIIX_FLAG_CHECKINTR
)paren
id|pci_enable_intx
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|combined
)paren
(brace
id|port_info
(braket
id|sata_chan
)braket
op_assign
op_amp
id|piix_port_info
(braket
id|ent-&gt;driver_data
)braket
suffix:semicolon
id|port_info
(braket
id|sata_chan
)braket
op_member_access_from_pointer
id|host_flags
op_or_assign
id|ATA_FLAG_SLAVE_POSS
suffix:semicolon
id|port_info
(braket
id|pata_chan
)braket
op_assign
op_amp
id|piix_port_info
(braket
id|ich5_pata
)braket
suffix:semicolon
id|n_ports
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
id|DRV_NAME
l_string|&quot;: combined mode detected&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
multiline_comment|/**&n; *&t;piix_init -&n; *&n; *&t;LOCKING:&n; *&n; *&t;RETURNS:&n; *&n; */
DECL|function|piix_init
r_static
r_int
id|__init
id|piix_init
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
id|piix_pci_driver
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
multiline_comment|/**&n; *&t;piix_exit -&n; *&n; *&t;LOCKING:&n; *&n; */
DECL|function|piix_exit
r_static
r_void
id|__exit
id|piix_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|piix_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|piix_init
id|module_init
c_func
(paren
id|piix_init
)paren
suffix:semicolon
DECL|variable|piix_exit
id|module_exit
c_func
(paren
id|piix_exit
)paren
suffix:semicolon
eof
