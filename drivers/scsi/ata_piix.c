multiline_comment|/*&n;&n;    ata_piix.c - Intel PATA/SATA controllers&n;&n;&n;&t;Copyright 2003-2004 Red Hat Inc&n;&t;Copyright 2003-2004 Jeff Garzik&n;&n;&n;&t;Copyright header from piix.c:&n;&n;    Copyright (C) 1998-1999 Andrzej Krzysztofowicz, Author and Maintainer&n;    Copyright (C) 1998-2000 Andre Hedrick &lt;andre@linux-ide.org&gt;&n;    Copyright (C) 2003 Red Hat Inc &lt;alan@redhat.com&gt;&n;&n;    May be copied or modified under the terms of the GNU General Public License&n;&n; */
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
mdefine_line|#define DRV_NAME&t;&quot;ata_piix&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;1.00&quot;
r_enum
(brace
DECL|enumerator|PIIX_IOCFG
id|PIIX_IOCFG
op_assign
l_int|0x54
comma
multiline_comment|/* IDE I/O configuration register */
DECL|enumerator|ICH5_PCS
id|ICH5_PCS
op_assign
l_int|0x92
comma
multiline_comment|/* port control and status */
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
DECL|enumerator|PIIX_COMB_PRI
id|PIIX_COMB_PRI
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* combined mode, PATA primary */
DECL|enumerator|PIIX_COMB_SEC
id|PIIX_COMB_SEC
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* combined mode, PATA secondary */
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
id|piix_sata_port_disable
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
comma
r_int
r_int
id|pio
)paren
suffix:semicolon
r_static
r_void
id|piix_set_udmamode
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
comma
r_int
r_int
id|udma
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
multiline_comment|/* ICH6 operates in two modes, &quot;looks-like-ICH5&quot; mode,&n;&t; * and enhanced mode, with queueing and other fancy stuff.&n;&t; * This is distinguished by PCI class code.&n;&t; */
(brace
l_int|0x8086
comma
l_int|0x2652
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|PCI_CLASS_STORAGE_IDE
op_lshift
l_int|8
comma
l_int|0xffff00
comma
id|ich5_sata
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
id|set_udmamode
op_assign
id|piix_set_udmamode
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
id|piix_pata_phy_reset
comma
dot
id|phy_config
op_assign
id|pata_phy_config
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
id|piix_sata_port_disable
comma
dot
id|set_piomode
op_assign
id|piix_set_piomode
comma
dot
id|set_udmamode
op_assign
id|piix_set_udmamode
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
id|piix_sata_phy_reset
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
id|ATA_UDMA_MASK_40C
comma
multiline_comment|/* FIXME: cbl det */
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
id|PIIX_FLAG_COMBINED
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
l_int|0x03
comma
multiline_comment|/* pio3-4 */
dot
id|udma_mask
op_assign
id|ATA_UDMA_MASK_40C
comma
multiline_comment|/* FIXME: cbl det */
dot
id|port_ops
op_assign
op_amp
id|piix_pata_ops
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
multiline_comment|/**&n; *&t;piix_pata_cbl_detect - Probe host controller cable detect info&n; *&t;@ap: Port for which cable detect info is desired&n; *&n; *&t;Read 80c cable indicator from SATA PCI device&squot;s PCI config&n; *&t;register.  This register is normally set by firmware (BIOS).&n; *&n; *&t;LOCKING:&n; *&t;None (inherited from caller).&n; */
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
id|ap-&gt;host_set-&gt;pdev
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
id|ap-&gt;port_no
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
id|piix_enable_bits
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
multiline_comment|/**&n; *&t;piix_pcs_probe - Probe SATA port configuration and status register&n; *&t;@ap: Port to probe&n; *&t;@have_port: (output) Non-zero if SATA port is enabled&n; *&t;@have_device: (output) Non-zero if SATA phy indicates device present&n; *&n; *&t;Reads SATA PCI device&squot;s PCI config register Port Configuration&n; *&t;and Status (PCS) to determine port and device availability.&n; *&n; *&t;LOCKING:&n; *&t;None (inherited from caller).&n; */
DECL|function|piix_pcs_probe
r_static
r_void
id|piix_pcs_probe
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
op_star
id|have_port
comma
r_int
r_int
op_star
id|have_device
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|ap-&gt;host_set-&gt;pdev
suffix:semicolon
id|u16
id|pcs
suffix:semicolon
id|pci_read_config_word
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
multiline_comment|/* is SATA port enabled? */
r_if
c_cond
(paren
id|pcs
op_amp
(paren
l_int|1
op_lshift
id|ap-&gt;port_no
)paren
)paren
(brace
op_star
id|have_port
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pcs
op_amp
(paren
l_int|1
op_lshift
(paren
id|ap-&gt;port_no
op_plus
l_int|4
)paren
)paren
)paren
op_star
id|have_device
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;piix_pcs_disable - Disable SATA port&n; *&t;@ap: Port to disable&n; *&n; *&t;Disable SATA phy for specified port.&n; *&n; *&t;LOCKING:&n; *&t;None (inherited from caller).&n; */
DECL|function|piix_pcs_disable
r_static
r_void
id|piix_pcs_disable
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
id|ap-&gt;host_set-&gt;pdev
suffix:semicolon
id|u16
id|pcs
suffix:semicolon
id|pci_read_config_word
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
r_if
c_cond
(paren
id|pcs
op_amp
(paren
l_int|1
op_lshift
id|ap-&gt;port_no
)paren
)paren
(brace
id|pcs
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|ap-&gt;port_no
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|pdev
comma
id|ICH5_PCS
comma
id|pcs
)paren
suffix:semicolon
)brace
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
r_int
r_int
id|have_port
op_assign
l_int|0
comma
id|have_dev
op_assign
l_int|0
suffix:semicolon
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
id|piix_enable_bits
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
id|piix_pcs_probe
c_func
(paren
id|ap
comma
op_amp
id|have_port
comma
op_amp
id|have_dev
)paren
suffix:semicolon
multiline_comment|/* if port not enabled, exit */
r_if
c_cond
(paren
op_logical_neg
id|have_port
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
l_string|&quot;ata%u: SATA port disabled. ignoring.&bslash;n&quot;
comma
id|ap-&gt;id
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* if port enabled but no device, disable port and exit */
r_if
c_cond
(paren
op_logical_neg
id|have_dev
)paren
(brace
id|piix_sata_port_disable
c_func
(paren
id|ap
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ata%u: SATA port has no device. disabling.&bslash;n&quot;
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
multiline_comment|/**&n; *&t;piix_sata_port_disable - Disable SATA port&n; *&t;@ap: Port to disable.&n; *&n; *&t;Disable SATA port.&n; *&n; *&t;LOCKING:&n; *&t;None (inherited from caller).&n; */
DECL|function|piix_sata_port_disable
r_static
r_void
id|piix_sata_port_disable
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
id|piix_pcs_disable
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
comma
r_int
r_int
id|pio
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|ap-&gt;host_set-&gt;pdev
suffix:semicolon
r_int
r_int
id|is_slave
op_assign
(paren
id|adev-&gt;flags
op_amp
id|ATA_DFLAG_MASTER
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_int
r_int
id|master_port
op_assign
id|ap-&gt;port_no
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
id|ap-&gt;port_no
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
id|ap-&gt;port_no
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
multiline_comment|/**&n; *&t;piix_set_udmamode - Initialize host controller PATA PIO timings&n; *&t;@ap: Port whose timings we are configuring&n; *&t;@adev: um&n; *&t;@udma: udma mode, 0 - 6&n; *&n; *&t;Set UDMA mode for device, in host controller PCI config space.&n; *&n; *&t;LOCKING:&n; *&t;None (inherited from caller).&n; */
DECL|function|piix_set_udmamode
r_static
r_void
id|piix_set_udmamode
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
comma
r_int
r_int
id|udma
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|ap-&gt;host_set-&gt;pdev
suffix:semicolon
id|u8
id|maslave
op_assign
id|ap-&gt;port_no
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
id|ap-&gt;port_no
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
id|reg44
comma
id|reg48
comma
id|reg4a
comma
id|reg54
suffix:semicolon
id|u8
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
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x44
comma
op_amp
id|reg44
)paren
suffix:semicolon
id|pci_read_config_word
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
id|pci_read_config_word
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
op_logical_neg
(paren
id|reg48
op_amp
id|u_flag
)paren
)paren
id|pci_write_config_word
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
op_logical_neg
(paren
id|reg4a
op_amp
id|u_speed
)paren
)paren
(brace
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
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
id|reg4a
op_or
id|u_speed
)paren
suffix:semicolon
)brace
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
(brace
id|pci_write_config_word
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
)brace
r_else
(brace
id|pci_write_config_word
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
)brace
multiline_comment|/**&n; *&t;piix_probe_combined - Determine if PATA and SATA are combined&n; *&t;@pdev: PCI device to examine&n; *&t;@mask: (output) zero, %PIIX_COMB_PRI or %PIIX_COMB_SEC&n; *&n; *&t;Determine if BIOS has secretly stuffed a PATA port into our&n; *&t;otherwise-beautiful SATA PCI device.&n; *&n; *&t;LOCKING:&n; *&t;Inherited from PCI layer (may sleep).&n; */
DECL|function|piix_probe_combined
r_static
r_void
id|piix_probe_combined
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
r_int
op_star
id|mask
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
l_int|0x90
comma
op_amp
id|tmp
)paren
suffix:semicolon
multiline_comment|/* combined mode reg */
id|tmp
op_and_assign
l_int|0x6
suffix:semicolon
multiline_comment|/* interesting bits 2:1, PATA primary/secondary */
multiline_comment|/* backwards from what one might expect */
r_if
c_cond
(paren
id|tmp
op_eq
l_int|0x4
)paren
multiline_comment|/* bits 10x */
op_star
id|mask
op_or_assign
id|PIIX_COMB_SEC
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|0x6
)paren
multiline_comment|/* bits 11x */
op_star
id|mask
op_or_assign
id|PIIX_COMB_PRI
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
id|pata_comb
op_assign
l_int|0
comma
id|sata_comb
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
id|PIIX_FLAG_COMBINED
)paren
id|piix_probe_combined
c_func
(paren
id|pdev
comma
op_amp
id|combined
)paren
suffix:semicolon
r_if
c_cond
(paren
id|combined
op_amp
id|PIIX_COMB_PRI
)paren
id|sata_comb
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|combined
op_amp
id|PIIX_COMB_SEC
)paren
id|pata_comb
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pata_comb
op_logical_or
id|sata_comb
)paren
(brace
id|port_info
(braket
id|sata_comb
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
id|sata_comb
)braket
op_member_access_from_pointer
id|host_flags
op_or_assign
id|ATA_FLAG_SLAVE_POSS
suffix:semicolon
multiline_comment|/* sigh */
id|port_info
(braket
id|pata_comb
)braket
op_assign
op_amp
id|piix_port_info
(braket
id|ich5_pata
)braket
suffix:semicolon
multiline_comment|/*ich5-specific*/
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
