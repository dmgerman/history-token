multiline_comment|/*&n; *  ata_sil.c - Silicon Image SATA&n; *&n; *  Copyright 2003 Red Hat, Inc.&n; *  Copyright 2003 Benjamin Herrenschmidt &lt;benh@kernel.crashing.org&gt;&n; *&n; *  The contents of this file are subject to the Open&n; *  Software License version 1.1 that can be found at&n; *  http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n; *  by reference.&n; *&n; *  Alternatively, the contents of this file may be used under the terms&n; *  of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n; *  in the kernel source COPYING file, in which case the provisions of&n; *  the GPL are applicable instead of the above.  If you wish to allow&n; *  the use of your version of this file only under the terms of the&n; *  GPL and not to allow others to use your version of this file under&n; *  the OSL, indicate your decision by deleting the provisions above and&n; *  replace them with the notice and other provisions required by the GPL.&n; *  If you do not delete the provisions above, a recipient may use your&n; *  version of this file under either the OSL or the GPL.&n; *&n; */
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
mdefine_line|#define DRV_NAME&t;&quot;sata_sil&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;0.54&quot;
r_enum
(brace
DECL|enumerator|sil_3112
id|sil_3112
op_assign
l_int|0
comma
DECL|enumerator|sil_3114
id|sil_3114
op_assign
l_int|1
comma
DECL|enumerator|SIL_SYSCFG
id|SIL_SYSCFG
op_assign
l_int|0x48
comma
DECL|enumerator|SIL_MASK_IDE0_INT
id|SIL_MASK_IDE0_INT
op_assign
(paren
l_int|1
op_lshift
l_int|22
)paren
comma
DECL|enumerator|SIL_MASK_IDE1_INT
id|SIL_MASK_IDE1_INT
op_assign
(paren
l_int|1
op_lshift
l_int|23
)paren
comma
DECL|enumerator|SIL_MASK_IDE2_INT
id|SIL_MASK_IDE2_INT
op_assign
(paren
l_int|1
op_lshift
l_int|24
)paren
comma
DECL|enumerator|SIL_MASK_IDE3_INT
id|SIL_MASK_IDE3_INT
op_assign
(paren
l_int|1
op_lshift
l_int|25
)paren
comma
DECL|enumerator|SIL_MASK_2PORT
id|SIL_MASK_2PORT
op_assign
id|SIL_MASK_IDE0_INT
op_or
id|SIL_MASK_IDE1_INT
comma
DECL|enumerator|SIL_MASK_4PORT
id|SIL_MASK_4PORT
op_assign
id|SIL_MASK_2PORT
op_or
id|SIL_MASK_IDE2_INT
op_or
id|SIL_MASK_IDE3_INT
comma
DECL|enumerator|SIL_IDE2_BMDMA
id|SIL_IDE2_BMDMA
op_assign
l_int|0x200
comma
DECL|enumerator|SIL_INTR_STEERING
id|SIL_INTR_STEERING
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
DECL|enumerator|SIL_QUIRK_MOD15WRITE
id|SIL_QUIRK_MOD15WRITE
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
DECL|enumerator|SIL_QUIRK_UDMA5MAX
id|SIL_QUIRK_UDMA5MAX
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
)brace
suffix:semicolon
r_static
r_int
id|sil_init_one
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
id|sil_dev_config
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_device
op_star
id|dev
)paren
suffix:semicolon
r_static
id|u32
id|sil_scr_read
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
id|sil_scr_write
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
DECL|variable|sil_pci_tbl
r_static
r_struct
id|pci_device_id
id|sil_pci_tbl
(braket
)braket
op_assign
(brace
(brace
l_int|0x1095
comma
l_int|0x3112
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|sil_3112
)brace
comma
(brace
l_int|0x1095
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
id|sil_3112
)brace
comma
(brace
l_int|0x1095
comma
l_int|0x3512
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|sil_3112
)brace
comma
(brace
l_int|0x1095
comma
l_int|0x3114
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|sil_3114
)brace
comma
(brace
)brace
multiline_comment|/* terminate list */
)brace
suffix:semicolon
multiline_comment|/* TODO firmware versions should be added - eric */
DECL|struct|sil_drivelist
r_struct
id|sil_drivelist
(brace
DECL|member|product
r_const
r_char
op_star
id|product
suffix:semicolon
DECL|member|quirk
r_int
r_int
id|quirk
suffix:semicolon
DECL|variable|sil_blacklist
)brace
id|sil_blacklist
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;ST320012AS&quot;
comma
id|SIL_QUIRK_MOD15WRITE
)brace
comma
(brace
l_string|&quot;ST330013AS&quot;
comma
id|SIL_QUIRK_MOD15WRITE
)brace
comma
(brace
l_string|&quot;ST340017AS&quot;
comma
id|SIL_QUIRK_MOD15WRITE
)brace
comma
(brace
l_string|&quot;ST360015AS&quot;
comma
id|SIL_QUIRK_MOD15WRITE
)brace
comma
(brace
l_string|&quot;ST380023AS&quot;
comma
id|SIL_QUIRK_MOD15WRITE
)brace
comma
(brace
l_string|&quot;ST3120023AS&quot;
comma
id|SIL_QUIRK_MOD15WRITE
)brace
comma
(brace
l_string|&quot;ST340014ASL&quot;
comma
id|SIL_QUIRK_MOD15WRITE
)brace
comma
(brace
l_string|&quot;ST360014ASL&quot;
comma
id|SIL_QUIRK_MOD15WRITE
)brace
comma
(brace
l_string|&quot;ST380011ASL&quot;
comma
id|SIL_QUIRK_MOD15WRITE
)brace
comma
(brace
l_string|&quot;ST3120022ASL&quot;
comma
id|SIL_QUIRK_MOD15WRITE
)brace
comma
(brace
l_string|&quot;ST3160021ASL&quot;
comma
id|SIL_QUIRK_MOD15WRITE
)brace
comma
(brace
l_string|&quot;Maxtor 4D060H3&quot;
comma
id|SIL_QUIRK_UDMA5MAX
)brace
comma
(brace
)brace
)brace
suffix:semicolon
DECL|variable|sil_pci_driver
r_static
r_struct
id|pci_driver
id|sil_pci_driver
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
id|sil_pci_tbl
comma
dot
id|probe
op_assign
id|sil_init_one
comma
dot
id|remove
op_assign
id|ata_pci_remove_one
comma
)brace
suffix:semicolon
DECL|variable|sil_sht
r_static
id|Scsi_Host_Template
id|sil_sht
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
DECL|variable|sil_ops
r_static
r_struct
id|ata_port_operations
id|sil_ops
op_assign
(brace
dot
id|port_disable
op_assign
id|ata_port_disable
comma
dot
id|dev_config
op_assign
id|sil_dev_config
comma
dot
id|tf_load
op_assign
id|ata_tf_load_mmio
comma
dot
id|tf_read
op_assign
id|ata_tf_read_mmio
comma
dot
id|check_status
op_assign
id|ata_check_status_mmio
comma
dot
id|exec_command
op_assign
id|ata_exec_command_mmio
comma
dot
id|phy_reset
op_assign
id|sata_phy_reset
comma
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
id|ata_interrupt
comma
dot
id|scr_read
op_assign
id|sil_scr_read
comma
dot
id|scr_write
op_assign
id|sil_scr_write
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
DECL|variable|sil_port_info
r_static
r_struct
id|ata_port_info
id|sil_port_info
(braket
)braket
op_assign
(brace
multiline_comment|/* sil_3112 */
(brace
dot
id|sht
op_assign
op_amp
id|sil_sht
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
l_int|0x03
comma
multiline_comment|/* pio3-4 */
dot
id|udma_mask
op_assign
l_int|0x7f
comma
multiline_comment|/* udma0-6; FIXME */
dot
id|port_ops
op_assign
op_amp
id|sil_ops
comma
)brace
comma
multiline_comment|/* sil_3114 */
(brace
dot
id|sht
op_assign
op_amp
id|sil_sht
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
l_int|0x03
comma
multiline_comment|/* pio3-4 */
dot
id|udma_mask
op_assign
l_int|0x7f
comma
multiline_comment|/* udma0-6; FIXME */
dot
id|port_ops
op_assign
op_amp
id|sil_ops
comma
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* per-port register offsets */
multiline_comment|/* TODO: we can probably calculate rather than use a table */
r_static
r_const
r_struct
(brace
DECL|member|tf
r_int
r_int
id|tf
suffix:semicolon
multiline_comment|/* ATA taskfile register block */
DECL|member|ctl
r_int
r_int
id|ctl
suffix:semicolon
multiline_comment|/* ATA control/altstatus register block */
DECL|member|bmdma
r_int
r_int
id|bmdma
suffix:semicolon
multiline_comment|/* DMA register block */
DECL|member|scr
r_int
r_int
id|scr
suffix:semicolon
multiline_comment|/* SATA control register block */
DECL|member|sien
r_int
r_int
id|sien
suffix:semicolon
multiline_comment|/* SATA Interrupt Enable register */
DECL|variable|sil_port
)brace
id|sil_port
(braket
)braket
op_assign
(brace
(brace
l_int|0x80
comma
l_int|0x8A
comma
l_int|0x00
comma
l_int|0x100
comma
l_int|0x148
)brace
comma
multiline_comment|/* port 0 ... */
(brace
l_int|0xC0
comma
l_int|0xCA
comma
l_int|0x08
comma
l_int|0x180
comma
l_int|0x1c8
)brace
comma
(brace
l_int|0x280
comma
l_int|0x28A
comma
l_int|0x200
comma
l_int|0x300
comma
l_int|0x348
)brace
comma
(brace
l_int|0x2C0
comma
l_int|0x2CA
comma
l_int|0x208
comma
l_int|0x380
comma
l_int|0x3c8
)brace
comma
multiline_comment|/* ... port 3 */
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
l_string|&quot;low-level driver for Silicon Image SATA controller&quot;
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
id|sil_pci_tbl
)paren
suffix:semicolon
DECL|function|sil_scr_addr
r_static
r_inline
r_int
r_int
id|sil_scr_addr
c_func
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
r_int
r_int
id|offset
op_assign
id|ap-&gt;ioaddr.scr_addr
suffix:semicolon
r_switch
c_cond
(paren
id|sc_reg
)paren
(brace
r_case
id|SCR_STATUS
suffix:colon
r_return
id|offset
op_plus
l_int|4
suffix:semicolon
r_case
id|SCR_ERROR
suffix:colon
r_return
id|offset
op_plus
l_int|8
suffix:semicolon
r_case
id|SCR_CONTROL
suffix:colon
r_return
id|offset
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* do nothing */
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sil_scr_read
r_static
id|u32
id|sil_scr_read
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
r_void
op_star
id|mmio
op_assign
(paren
r_void
op_star
)paren
id|sil_scr_addr
c_func
(paren
id|ap
comma
id|sc_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mmio
)paren
r_return
id|readl
c_func
(paren
id|mmio
)paren
suffix:semicolon
r_return
l_int|0xffffffffU
suffix:semicolon
)brace
DECL|function|sil_scr_write
r_static
r_void
id|sil_scr_write
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
r_void
op_star
id|mmio
op_assign
(paren
r_void
op_star
)paren
id|sil_scr_addr
c_func
(paren
id|ap
comma
id|sc_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mmio
)paren
id|writel
c_func
(paren
id|val
comma
id|mmio
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sil_dev_config - Apply device/host-specific errata fixups&n; *&t;@ap: Port containing device to be examined&n; *&t;@dev: Device to be examined&n; *&n; *&t;After the IDENTIFY [PACKET] DEVICE step is complete, and a&n; *&t;device is known to be present, this function is called.&n; *&t;We apply two errata fixups which are specific to Silicon Image,&n; *&t;a Seagate and a Maxtor fixup.&n; *&n; *&t;For certain Seagate devices, we must limit the maximum sectors&n; *&t;to under 8K.&n; *&n; *&t;For certain Maxtor devices, we must not program the drive&n; *&t;beyond udma5.&n; *&n; *&t;Both fixups are unfairly pessimistic.  As soon as I get more&n; *&t;information on these errata, I will create a more exhaustive&n; *&t;list, and apply the fixups to only the specific&n; *&t;devices/hosts/firmwares that need it.&n; *&n; *&t;20040111 - Seagate drives affected by the Mod15Write bug are blacklisted&n; *&t;The Maxtor quirk is in the blacklist, but I&squot;m keeping the original&n; *&t;pessimistic fix for the following reasons:&n; *&t;- There seems to be less info on it, only one device gleaned off the&n; *&t;Windows&t;driver, maybe only one is affected.  More info would be greatly&n; *&t;appreciated.&n; *&t;- But then again UDMA5 is hardly anything to complain about&n; */
DECL|function|sil_dev_config
r_static
r_void
id|sil_dev_config
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|n
comma
id|quirks
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|s
op_assign
op_amp
id|dev-&gt;product
(braket
l_int|0
)braket
suffix:semicolon
r_int
r_int
id|len
op_assign
id|strnlen
c_func
(paren
id|s
comma
r_sizeof
(paren
id|dev-&gt;product
)paren
)paren
suffix:semicolon
multiline_comment|/* ATAPI specifies that empty space is blank-filled; remove blanks */
r_while
c_loop
(paren
(paren
id|len
OG
l_int|0
)paren
op_logical_and
(paren
id|s
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot; &squot;
)paren
)paren
id|len
op_decrement
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|sil_blacklist
(braket
id|n
)braket
dot
id|product
suffix:semicolon
id|n
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|sil_blacklist
(braket
id|n
)braket
dot
id|product
comma
id|s
comma
id|strlen
c_func
(paren
id|sil_blacklist
(braket
id|n
)braket
dot
id|product
)paren
)paren
)paren
(brace
id|quirks
op_assign
id|sil_blacklist
(braket
id|n
)braket
dot
id|quirk
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* limit requests to 15 sectors */
r_if
c_cond
(paren
id|quirks
op_amp
id|SIL_QUIRK_MOD15WRITE
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ata%u(%u): applying Seagate errata fix&bslash;n&quot;
comma
id|ap-&gt;id
comma
id|dev-&gt;devno
)paren
suffix:semicolon
id|ap-&gt;host-&gt;max_sectors
op_assign
l_int|15
suffix:semicolon
id|ap-&gt;host-&gt;hostt-&gt;max_sectors
op_assign
l_int|15
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* limit to udma5 */
r_if
c_cond
(paren
id|quirks
op_amp
id|SIL_QUIRK_UDMA5MAX
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ata%u(%u): applying Maxtor errata fix %s&bslash;n&quot;
comma
id|ap-&gt;id
comma
id|dev-&gt;devno
comma
id|s
)paren
suffix:semicolon
id|ap-&gt;udma_mask
op_and_assign
id|ATA_UDMA5
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|sil_init_one
r_static
r_int
id|sil_init_one
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
r_int
r_int
id|i
suffix:semicolon
id|u32
id|tmp
comma
id|irq_mask
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
id|probe_ent-&gt;port_ops
op_assign
id|sil_port_info
(braket
id|ent-&gt;driver_data
)braket
dot
id|port_ops
suffix:semicolon
id|probe_ent-&gt;sht
op_assign
id|sil_port_info
(braket
id|ent-&gt;driver_data
)braket
dot
id|sht
suffix:semicolon
id|probe_ent-&gt;n_ports
op_assign
(paren
id|ent-&gt;driver_data
op_eq
id|sil_3114
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|2
suffix:semicolon
id|probe_ent-&gt;pio_mask
op_assign
id|sil_port_info
(braket
id|ent-&gt;driver_data
)braket
dot
id|pio_mask
suffix:semicolon
id|probe_ent-&gt;udma_mask
op_assign
id|sil_port_info
(braket
id|ent-&gt;driver_data
)braket
dot
id|udma_mask
suffix:semicolon
id|probe_ent-&gt;irq
op_assign
id|pdev-&gt;irq
suffix:semicolon
id|probe_ent-&gt;irq_flags
op_assign
id|SA_SHIRQ
suffix:semicolon
id|probe_ent-&gt;host_flags
op_assign
id|sil_port_info
(braket
id|ent-&gt;driver_data
)braket
dot
id|host_flags
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
id|probe_ent-&gt;mmio_base
op_assign
id|mmio_base
suffix:semicolon
id|base
op_assign
(paren
r_int
r_int
)paren
id|mmio_base
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
id|probe_ent-&gt;n_ports
suffix:semicolon
id|i
op_increment
)paren
(brace
id|probe_ent-&gt;port
(braket
id|i
)braket
dot
id|cmd_addr
op_assign
id|base
op_plus
id|sil_port
(braket
id|i
)braket
dot
id|tf
suffix:semicolon
id|probe_ent-&gt;port
(braket
id|i
)braket
dot
id|altstatus_addr
op_assign
id|probe_ent-&gt;port
(braket
id|i
)braket
dot
id|ctl_addr
op_assign
id|base
op_plus
id|sil_port
(braket
id|i
)braket
dot
id|ctl
suffix:semicolon
id|probe_ent-&gt;port
(braket
id|i
)braket
dot
id|bmdma_addr
op_assign
id|base
op_plus
id|sil_port
(braket
id|i
)braket
dot
id|bmdma
suffix:semicolon
id|probe_ent-&gt;port
(braket
id|i
)braket
dot
id|scr_addr
op_assign
id|base
op_plus
id|sil_port
(braket
id|i
)braket
dot
id|scr
suffix:semicolon
id|ata_std_ports
c_func
(paren
op_amp
id|probe_ent-&gt;port
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ent-&gt;driver_data
op_eq
id|sil_3114
)paren
(brace
id|irq_mask
op_assign
id|SIL_MASK_4PORT
suffix:semicolon
multiline_comment|/* flip the magic &quot;make 4 ports work&quot; bit */
id|tmp
op_assign
id|readl
c_func
(paren
id|mmio_base
op_plus
id|SIL_IDE2_BMDMA
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp
op_amp
id|SIL_INTR_STEERING
)paren
op_eq
l_int|0
)paren
id|writel
c_func
(paren
id|tmp
op_or
id|SIL_INTR_STEERING
comma
id|mmio_base
op_plus
id|SIL_IDE2_BMDMA
)paren
suffix:semicolon
)brace
r_else
(brace
id|irq_mask
op_assign
id|SIL_MASK_2PORT
suffix:semicolon
)brace
multiline_comment|/* make sure IDE0/1/2/3 interrupts are not masked */
id|tmp
op_assign
id|readl
c_func
(paren
id|mmio_base
op_plus
id|SIL_SYSCFG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|irq_mask
)paren
(brace
id|tmp
op_and_assign
op_complement
id|irq_mask
suffix:semicolon
id|writel
c_func
(paren
id|tmp
comma
id|mmio_base
op_plus
id|SIL_SYSCFG
)paren
suffix:semicolon
id|readl
c_func
(paren
id|mmio_base
op_plus
id|SIL_SYSCFG
)paren
suffix:semicolon
multiline_comment|/* flush */
)brace
multiline_comment|/* mask all SATA phy-related interrupts */
multiline_comment|/* TODO: unmask bit 6 (SError N bit) for hotplug */
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
id|writel
c_func
(paren
l_int|0
comma
id|mmio_base
op_plus
id|sil_port
(braket
id|i
)braket
dot
id|sien
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
DECL|function|sil_init
r_static
r_int
id|__init
id|sil_init
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
id|sil_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|sil_exit
r_static
r_void
id|__exit
id|sil_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|sil_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|sil_init
id|module_init
c_func
(paren
id|sil_init
)paren
suffix:semicolon
DECL|variable|sil_exit
id|module_exit
c_func
(paren
id|sil_exit
)paren
suffix:semicolon
eof
