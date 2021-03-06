multiline_comment|/*&n; *  sata_uli.c - ULi Electronics SATA&n; *&n; *  The contents of this file are subject to the Open&n; *  Software License version 1.1 that can be found at&n; *  http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n; *  by reference.&n; *&n; *  Alternatively, the contents of this file may be used under the terms&n; *  of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n; *  in the kernel source COPYING file, in which case the provisions of&n; *  the GPL are applicable instead of the above.  If you wish to allow&n; *  the use of your version of this file only under the terms of the&n; *  GPL and not to allow others to use your version of this file under&n; *  the OSL, indicate your decision by deleting the provisions above and&n; *  replace them with the notice and other provisions required by the GPL.&n; *  If you do not delete the provisions above, a recipient may use your&n; *  version of this file under either the OSL or the GPL.&n; *&n; */
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
mdefine_line|#define DRV_NAME&t;&quot;sata_uli&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;0.5&quot;
r_enum
(brace
DECL|enumerator|uli_5289
id|uli_5289
op_assign
l_int|0
comma
DECL|enumerator|uli_5287
id|uli_5287
op_assign
l_int|1
comma
DECL|enumerator|uli_5281
id|uli_5281
op_assign
l_int|2
comma
multiline_comment|/* PCI configuration registers */
DECL|enumerator|ULI5287_BASE
id|ULI5287_BASE
op_assign
l_int|0x90
comma
multiline_comment|/* sata0 phy SCR registers */
DECL|enumerator|ULI5287_OFFS
id|ULI5287_OFFS
op_assign
l_int|0x10
comma
multiline_comment|/* offset from sata0-&gt;sata1 phy regs */
DECL|enumerator|ULI5281_BASE
id|ULI5281_BASE
op_assign
l_int|0x60
comma
multiline_comment|/* sata0 phy SCR  registers */
DECL|enumerator|ULI5281_OFFS
id|ULI5281_OFFS
op_assign
l_int|0x60
comma
multiline_comment|/* offset from sata0-&gt;sata1 phy regs */
)brace
suffix:semicolon
r_static
r_int
id|uli_init_one
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
id|uli_scr_read
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
id|uli_scr_write
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
DECL|variable|uli_pci_tbl
r_static
r_struct
id|pci_device_id
id|uli_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_AL
comma
l_int|0x5289
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|uli_5289
)brace
comma
(brace
id|PCI_VENDOR_ID_AL
comma
l_int|0x5287
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|uli_5287
)brace
comma
(brace
id|PCI_VENDOR_ID_AL
comma
l_int|0x5281
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|uli_5281
)brace
comma
(brace
)brace
multiline_comment|/* terminate list */
)brace
suffix:semicolon
DECL|variable|uli_pci_driver
r_static
r_struct
id|pci_driver
id|uli_pci_driver
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
id|uli_pci_tbl
comma
dot
id|probe
op_assign
id|uli_init_one
comma
dot
id|remove
op_assign
id|ata_pci_remove_one
comma
)brace
suffix:semicolon
DECL|variable|uli_sht
r_static
id|Scsi_Host_Template
id|uli_sht
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
DECL|variable|uli_ops
r_static
r_struct
id|ata_port_operations
id|uli_ops
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
id|scr_read
op_assign
id|uli_scr_read
comma
dot
id|scr_write
op_assign
id|uli_scr_write
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
DECL|variable|uli_port_info
r_static
r_struct
id|ata_port_info
id|uli_port_info
op_assign
(brace
dot
id|sht
op_assign
op_amp
id|uli_sht
comma
dot
id|host_flags
op_assign
id|ATA_FLAG_SATA
op_or
id|ATA_FLAG_SATA_RESET
op_or
id|ATA_FLAG_NO_LEGACY
comma
dot
id|pio_mask
op_assign
l_int|0x03
comma
singleline_comment|//support pio mode 4 (FIXME)
dot
id|udma_mask
op_assign
l_int|0x7f
comma
singleline_comment|//support udma mode 6
dot
id|port_ops
op_assign
op_amp
id|uli_ops
comma
)brace
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Peer Chen&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;low-level driver for ULi Electronics SATA controller&quot;
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
id|uli_pci_tbl
)paren
suffix:semicolon
DECL|variable|DRV_VERSION
id|MODULE_VERSION
c_func
(paren
id|DRV_VERSION
)paren
suffix:semicolon
DECL|function|get_scr_cfg_addr
r_static
r_int
r_int
id|get_scr_cfg_addr
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
r_return
id|ap-&gt;ioaddr.scr_addr
op_plus
(paren
l_int|4
op_star
id|sc_reg
)paren
suffix:semicolon
)brace
DECL|function|uli_scr_cfg_read
r_static
id|u32
id|uli_scr_cfg_read
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
r_int
id|cfg_addr
op_assign
id|get_scr_cfg_addr
c_func
(paren
id|ap
comma
id|sc_reg
)paren
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|pdev
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
DECL|function|uli_scr_cfg_write
r_static
r_void
id|uli_scr_cfg_write
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
r_int
id|cfg_addr
op_assign
id|get_scr_cfg_addr
c_func
(paren
id|ap
comma
id|scr
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|pdev
comma
id|cfg_addr
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|uli_scr_read
r_static
id|u32
id|uli_scr_read
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
id|uli_scr_cfg_read
c_func
(paren
id|ap
comma
id|sc_reg
)paren
suffix:semicolon
)brace
DECL|function|uli_scr_write
r_static
r_void
id|uli_scr_write
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
singleline_comment|//SCR_CONTROL=2, SCR_ERROR=1, SCR_STATUS=0
r_return
suffix:semicolon
id|uli_scr_cfg_write
c_func
(paren
id|ap
comma
id|sc_reg
comma
id|val
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
DECL|function|uli_init_one
r_static
r_int
id|uli_init_one
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
suffix:semicolon
r_struct
id|ata_port_info
op_star
id|ppi
suffix:semicolon
r_int
id|rc
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
id|pci_dev_busy
op_assign
l_int|0
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
id|ppi
op_assign
op_amp
id|uli_port_info
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
r_switch
c_cond
(paren
id|board_idx
)paren
(brace
r_case
id|uli_5287
suffix:colon
id|probe_ent-&gt;port
(braket
l_int|0
)braket
dot
id|scr_addr
op_assign
id|ULI5287_BASE
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|1
)braket
dot
id|scr_addr
op_assign
id|ULI5287_BASE
op_plus
id|ULI5287_OFFS
suffix:semicolon
id|probe_ent-&gt;n_ports
op_assign
l_int|4
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|2
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
op_plus
l_int|8
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|2
)braket
dot
id|altstatus_addr
op_assign
id|probe_ent-&gt;port
(braket
l_int|2
)braket
dot
id|ctl_addr
op_assign
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|1
)paren
op_or
id|ATA_PCI_CTL_OFS
)paren
op_plus
l_int|4
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|2
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
l_int|16
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|2
)braket
dot
id|scr_addr
op_assign
id|ULI5287_BASE
op_plus
id|ULI5287_OFFS
op_star
l_int|4
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|3
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
op_plus
l_int|8
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|3
)braket
dot
id|altstatus_addr
op_assign
id|probe_ent-&gt;port
(braket
l_int|3
)braket
dot
id|ctl_addr
op_assign
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|3
)paren
op_or
id|ATA_PCI_CTL_OFS
)paren
op_plus
l_int|4
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|3
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
l_int|24
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|3
)braket
dot
id|scr_addr
op_assign
id|ULI5287_BASE
op_plus
id|ULI5287_OFFS
op_star
l_int|5
suffix:semicolon
id|ata_std_ports
c_func
(paren
op_amp
id|probe_ent-&gt;port
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|ata_std_ports
c_func
(paren
op_amp
id|probe_ent-&gt;port
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|uli_5289
suffix:colon
id|probe_ent-&gt;port
(braket
l_int|0
)braket
dot
id|scr_addr
op_assign
id|ULI5287_BASE
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|1
)braket
dot
id|scr_addr
op_assign
id|ULI5287_BASE
op_plus
id|ULI5287_OFFS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|uli_5281
suffix:colon
id|probe_ent-&gt;port
(braket
l_int|0
)braket
dot
id|scr_addr
op_assign
id|ULI5281_BASE
suffix:semicolon
id|probe_ent-&gt;port
(braket
l_int|1
)braket
dot
id|scr_addr
op_assign
id|ULI5281_BASE
op_plus
id|ULI5281_OFFS
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
DECL|function|uli_init
r_static
r_int
id|__init
id|uli_init
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
id|uli_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|uli_exit
r_static
r_void
id|__exit
id|uli_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|uli_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|uli_init
id|module_init
c_func
(paren
id|uli_init
)paren
suffix:semicolon
DECL|variable|uli_exit
id|module_exit
c_func
(paren
id|uli_exit
)paren
suffix:semicolon
eof
