multiline_comment|/*&n; *  sata_sis.c - Silicon Integrated Systems SATA&n; *&n; *  Maintained by:  Uwe Koziolek&n; *  &t;&t;    Please ALWAYS copy linux-ide@vger.kernel.org&n; *&t;&t;    on emails.&n; *&n; *  Copyright 2004 Uwe Koziolek&n; *&n; *  The contents of this file are subject to the Open&n; *  Software License version 1.1 that can be found at&n; *  http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n; *  by reference.&n; *&n; *  Alternatively, the contents of this file may be used under the terms&n; *  of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n; *  in the kernel source COPYING file, in which case the provisions of&n; *  the GPL are applicable instead of the above.  If you wish to allow&n; *  the use of your version of this file only under the terms of the&n; *  GPL and not to allow others to use your version of this file under&n; *  the OSL, indicate your decision by deleting the provisions above and&n; *  replace them with the notice and other provisions required by the GPL.&n; *  If you do not delete the provisions above, a recipient may use your&n; *  version of this file under either the OSL or the GPL.&n; *&n; */
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
mdefine_line|#define DRV_NAME&t;&quot;sata_sis&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;0.10&quot;
r_enum
(brace
DECL|enumerator|sis_180
id|sis_180
op_assign
l_int|0
comma
DECL|enumerator|SIS_SCR_PCI_BAR
id|SIS_SCR_PCI_BAR
op_assign
l_int|5
comma
multiline_comment|/* PCI configuration registers */
DECL|enumerator|SIS_GENCTL
id|SIS_GENCTL
op_assign
l_int|0x54
comma
multiline_comment|/* IDE General Control register */
DECL|enumerator|SIS_SCR_BASE
id|SIS_SCR_BASE
op_assign
l_int|0xc0
comma
multiline_comment|/* sata0 phy SCR registers */
DECL|enumerator|SIS_SATA1_OFS
id|SIS_SATA1_OFS
op_assign
l_int|0x10
comma
multiline_comment|/* offset from sata0-&gt;sata1 phy regs */
multiline_comment|/* random bits */
DECL|enumerator|SIS_FLAG_CFGSCR
id|SIS_FLAG_CFGSCR
op_assign
(paren
l_int|1
op_lshift
l_int|30
)paren
comma
multiline_comment|/* host flag: SCRs via PCI cfg */
DECL|enumerator|GENCTL_IOMAPPED_SCR
id|GENCTL_IOMAPPED_SCR
op_assign
(paren
l_int|1
op_lshift
l_int|26
)paren
comma
multiline_comment|/* if set, SCRs are in IO space */
)brace
suffix:semicolon
r_static
r_int
id|sis_init_one
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
id|sis_scr_read
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
id|sis_scr_write
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
DECL|variable|sis_pci_tbl
r_static
r_struct
id|pci_device_id
id|sis_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_SI
comma
l_int|0x180
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|sis_180
)brace
comma
(brace
id|PCI_VENDOR_ID_SI
comma
l_int|0x181
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|sis_180
)brace
comma
(brace
)brace
multiline_comment|/* terminate list */
)brace
suffix:semicolon
DECL|variable|sis_pci_driver
r_static
r_struct
id|pci_driver
id|sis_pci_driver
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
id|sis_pci_tbl
comma
dot
id|probe
op_assign
id|sis_init_one
comma
dot
id|remove
op_assign
id|ata_pci_remove_one
comma
)brace
suffix:semicolon
DECL|variable|sis_sht
r_static
id|Scsi_Host_Template
id|sis_sht
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
DECL|variable|sis_ops
r_static
r_struct
id|ata_port_operations
id|sis_ops
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
id|sis_scr_read
comma
dot
id|scr_write
op_assign
id|sis_scr_write
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
l_string|&quot;Uwe Koziolek&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;low-level driver for Silicon Integratad Systems SATA controller&quot;
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
id|sis_pci_tbl
)paren
suffix:semicolon
DECL|function|get_scr_cfg_addr
r_static
r_int
r_int
id|get_scr_cfg_addr
c_func
(paren
r_int
r_int
id|port_no
comma
r_int
r_int
id|sc_reg
)paren
(brace
r_int
r_int
id|addr
op_assign
id|SIS_SCR_BASE
op_plus
(paren
l_int|4
op_star
id|sc_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port_no
)paren
id|addr
op_add_assign
id|SIS_SATA1_OFS
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
DECL|function|sis_scr_cfg_read
r_static
id|u32
id|sis_scr_cfg_read
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
id|cfg_addr
op_assign
id|get_scr_cfg_addr
c_func
(paren
id|ap-&gt;port_no
comma
id|sc_reg
)paren
suffix:semicolon
id|u32
id|val
suffix:semicolon
r_if
c_cond
(paren
id|sc_reg
op_eq
id|SCR_ERROR
)paren
multiline_comment|/* doesn&squot;t exist in PCI cfg space */
r_return
l_int|0xffffffff
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|ap-&gt;host_set-&gt;pdev
comma
id|cfg_addr
comma
op_amp
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|sis_scr_cfg_write
r_static
r_void
id|sis_scr_cfg_write
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|scr
comma
id|u32
id|val
)paren
(brace
r_int
r_int
id|cfg_addr
op_assign
id|get_scr_cfg_addr
c_func
(paren
id|ap-&gt;port_no
comma
id|scr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scr
op_eq
id|SCR_ERROR
)paren
multiline_comment|/* doesn&squot;t exist in PCI cfg space */
r_return
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|ap-&gt;host_set-&gt;pdev
comma
id|cfg_addr
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|sis_scr_read
r_static
id|u32
id|sis_scr_read
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
r_if
c_cond
(paren
id|ap-&gt;flags
op_amp
id|SIS_FLAG_CFGSCR
)paren
r_return
id|sis_scr_cfg_read
c_func
(paren
id|ap
comma
id|sc_reg
)paren
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
DECL|function|sis_scr_write
r_static
r_void
id|sis_scr_write
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
r_if
c_cond
(paren
id|ap-&gt;flags
op_amp
id|SIS_FLAG_CFGSCR
)paren
id|sis_scr_cfg_write
c_func
(paren
id|ap
comma
id|sc_reg
comma
id|val
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
DECL|function|sis_init_one
r_static
r_int
id|sis_init_one
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
r_struct
id|ata_probe_ent
op_star
id|probe_ent
op_assign
l_int|NULL
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|u32
id|genctl
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
id|probe_ent-&gt;sht
op_assign
op_amp
id|sis_sht
suffix:semicolon
id|probe_ent-&gt;host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_SATA_RESET
op_or
id|ATA_FLAG_NO_LEGACY
suffix:semicolon
multiline_comment|/* check and see if the SCRs are in IO space or PCI cfg space */
id|pci_read_config_dword
c_func
(paren
id|pdev
comma
id|SIS_GENCTL
comma
op_amp
id|genctl
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|genctl
op_amp
id|GENCTL_IOMAPPED_SCR
)paren
op_eq
l_int|0
)paren
id|probe_ent-&gt;host_flags
op_or_assign
id|SIS_FLAG_CFGSCR
suffix:semicolon
multiline_comment|/* if hardware thinks SCRs are in IO space, but there are&n;&t; * no IO resources assigned, change to PCI cfg space.&n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|probe_ent-&gt;host_flags
op_amp
id|SIS_FLAG_CFGSCR
)paren
)paren
op_logical_and
(paren
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
id|SIS_SCR_PCI_BAR
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
id|SIS_SCR_PCI_BAR
)paren
OL
l_int|128
)paren
)paren
)paren
(brace
id|genctl
op_and_assign
op_complement
id|GENCTL_IOMAPPED_SCR
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|pdev
comma
id|SIS_GENCTL
comma
id|genctl
)paren
suffix:semicolon
id|probe_ent-&gt;host_flags
op_or_assign
id|SIS_FLAG_CFGSCR
suffix:semicolon
)brace
id|probe_ent-&gt;pio_mask
op_assign
l_int|0x03
suffix:semicolon
id|probe_ent-&gt;udma_mask
op_assign
l_int|0x7f
suffix:semicolon
id|probe_ent-&gt;port_ops
op_assign
op_amp
id|sis_ops
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|probe_ent-&gt;host_flags
op_amp
id|SIS_FLAG_CFGSCR
)paren
)paren
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
id|SIS_SCR_PCI_BAR
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|probe_ent-&gt;host_flags
op_amp
id|SIS_FLAG_CFGSCR
)paren
)paren
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
id|SIS_SCR_PCI_BAR
)paren
op_plus
l_int|64
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
id|pci_set_master
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|pci_enable_intx
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
DECL|function|sis_init
r_static
r_int
id|__init
id|sis_init
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
id|sis_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|sis_exit
r_static
r_void
id|__exit
id|sis_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|sis_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|sis_init
id|module_init
c_func
(paren
id|sis_init
)paren
suffix:semicolon
DECL|variable|sis_exit
id|module_exit
c_func
(paren
id|sis_exit
)paren
suffix:semicolon
eof
