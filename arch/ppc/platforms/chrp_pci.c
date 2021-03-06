multiline_comment|/*&n; * CHRP pci routines.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hydra.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/gg2.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
multiline_comment|/* LongTrail */
DECL|variable|gg2_pci_config_base
r_void
id|__iomem
op_star
id|gg2_pci_config_base
suffix:semicolon
multiline_comment|/*&n; * The VLSI Golden Gate II has only 512K of PCI configuration space, so we&n; * limit the bus number to 3 bits&n; */
DECL|function|gg2_read_config
r_int
id|__chrp
id|gg2_read_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|off
comma
r_int
id|len
comma
id|u32
op_star
id|val
)paren
(brace
r_volatile
r_void
id|__iomem
op_star
id|cfg_data
suffix:semicolon
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|bus-&gt;sysdata
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;number
OG
l_int|7
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
multiline_comment|/*&n;&t; * Note: the caller has already checked that off is&n;&t; * suitably aligned and that len is 1, 2 or 4.&n;&t; */
id|cfg_data
op_assign
id|hose-&gt;cfg_data
op_plus
(paren
(paren
id|bus-&gt;number
op_lshift
l_int|16
)paren
op_or
(paren
id|devfn
op_lshift
l_int|8
)paren
op_or
id|off
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
id|val
op_assign
id|in_8
c_func
(paren
id|cfg_data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|val
op_assign
id|in_le16
c_func
(paren
id|cfg_data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|val
op_assign
id|in_le32
c_func
(paren
id|cfg_data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|gg2_write_config
r_int
id|__chrp
id|gg2_write_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|off
comma
r_int
id|len
comma
id|u32
id|val
)paren
(brace
r_volatile
r_void
id|__iomem
op_star
id|cfg_data
suffix:semicolon
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|bus-&gt;sysdata
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;number
OG
l_int|7
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
multiline_comment|/*&n;&t; * Note: the caller has already checked that off is&n;&t; * suitably aligned and that len is 1, 2 or 4.&n;&t; */
id|cfg_data
op_assign
id|hose-&gt;cfg_data
op_plus
(paren
(paren
id|bus-&gt;number
op_lshift
l_int|16
)paren
op_or
(paren
id|devfn
op_lshift
l_int|8
)paren
op_or
id|off
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
id|out_8
c_func
(paren
id|cfg_data
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|out_le16
c_func
(paren
id|cfg_data
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|out_le32
c_func
(paren
id|cfg_data
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|gg2_pci_ops
r_static
r_struct
id|pci_ops
id|gg2_pci_ops
op_assign
(brace
id|gg2_read_config
comma
id|gg2_write_config
)brace
suffix:semicolon
multiline_comment|/*&n; * Access functions for PCI config space using RTAS calls.&n; */
r_int
id|__chrp
DECL|function|rtas_read_config
id|rtas_read_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|offset
comma
r_int
id|len
comma
id|u32
op_star
id|val
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|bus-&gt;sysdata
suffix:semicolon
r_int
r_int
id|addr
op_assign
(paren
id|offset
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|devfn
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
(paren
id|bus-&gt;number
op_minus
id|hose-&gt;first_busno
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|hose-&gt;index
op_lshift
l_int|24
)paren
suffix:semicolon
r_int
r_int
id|ret
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_int
id|rval
suffix:semicolon
id|rval
op_assign
id|call_rtas
c_func
(paren
l_string|&quot;read-pci-config&quot;
comma
l_int|2
comma
l_int|2
comma
op_amp
id|ret
comma
id|addr
comma
id|len
)paren
suffix:semicolon
op_star
id|val
op_assign
id|ret
suffix:semicolon
r_return
id|rval
ques
c_cond
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:colon
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_int
id|__chrp
DECL|function|rtas_write_config
id|rtas_write_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|offset
comma
r_int
id|len
comma
id|u32
id|val
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|bus-&gt;sysdata
suffix:semicolon
r_int
r_int
id|addr
op_assign
(paren
id|offset
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|devfn
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
(paren
id|bus-&gt;number
op_minus
id|hose-&gt;first_busno
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|hose-&gt;index
op_lshift
l_int|24
)paren
suffix:semicolon
r_int
id|rval
suffix:semicolon
id|rval
op_assign
id|call_rtas
c_func
(paren
l_string|&quot;write-pci-config&quot;
comma
l_int|3
comma
l_int|1
comma
l_int|NULL
comma
id|addr
comma
id|len
comma
id|val
)paren
suffix:semicolon
r_return
id|rval
ques
c_cond
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:colon
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|rtas_pci_ops
r_static
r_struct
id|pci_ops
id|rtas_pci_ops
op_assign
(brace
id|rtas_read_config
comma
id|rtas_write_config
)brace
suffix:semicolon
DECL|variable|Hydra
r_volatile
r_struct
id|Hydra
op_star
id|Hydra
op_assign
l_int|NULL
suffix:semicolon
r_int
id|__init
DECL|function|hydra_init
id|hydra_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;mac-io&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|NULL
op_logical_or
id|np-&gt;n_addrs
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|Hydra
op_assign
id|ioremap
c_func
(paren
id|np-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
id|np-&gt;addrs
(braket
l_int|0
)braket
dot
id|size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Hydra Mac I/O at %x&bslash;n&quot;
comma
id|np-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Hydra Feature_Control was %x&quot;
comma
id|in_le32
c_func
(paren
op_amp
id|Hydra-&gt;Feature_Control
)paren
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|Hydra-&gt;Feature_Control
comma
(paren
id|HYDRA_FC_SCC_CELL_EN
op_or
id|HYDRA_FC_SCSI_CELL_EN
op_or
id|HYDRA_FC_SCCA_ENABLE
op_or
id|HYDRA_FC_SCCB_ENABLE
op_or
id|HYDRA_FC_ARB_BYPASS
op_or
id|HYDRA_FC_MPIC_ENABLE
op_or
id|HYDRA_FC_SLOW_SCC_PCLK
op_or
id|HYDRA_FC_MPIC_IS_MASTER
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;, now %x&bslash;n&quot;
comma
id|in_le32
c_func
(paren
op_amp
id|Hydra-&gt;Feature_Control
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_void
id|__init
DECL|function|chrp_pcibios_fixup
id|chrp_pcibios_fixup
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|device_node
op_star
id|np
suffix:semicolon
multiline_comment|/* PCI interrupts are controlled by the OpenPIC */
id|for_each_pci_dev
c_func
(paren
id|dev
)paren
(brace
id|np
op_assign
id|pci_device_to_OF_node
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|np
op_ne
l_int|0
)paren
op_logical_and
(paren
id|np-&gt;n_intrs
OG
l_int|0
)paren
op_logical_and
(paren
id|np-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
op_ne
l_int|0
)paren
)paren
id|dev-&gt;irq
op_assign
id|np-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
)brace
DECL|macro|PRG_CL_RESET_VALID
mdefine_line|#define PRG_CL_RESET_VALID 0x00010000
r_static
r_void
id|__init
DECL|function|setup_python
id|setup_python
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_struct
id|device_node
op_star
id|dev
)paren
(brace
id|u32
op_star
id|reg
comma
id|val
suffix:semicolon
r_int
r_int
id|addr
op_assign
id|dev-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
suffix:semicolon
id|setup_indirect_pci
c_func
(paren
id|hose
comma
id|addr
op_plus
l_int|0xf8000
comma
id|addr
op_plus
l_int|0xf8010
)paren
suffix:semicolon
multiline_comment|/* Clear the magic go-slow bit */
id|reg
op_assign
(paren
id|u32
op_star
)paren
id|ioremap
c_func
(paren
id|dev-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
op_plus
l_int|0xf6000
comma
l_int|0x40
)paren
suffix:semicolon
id|val
op_assign
id|in_be32
c_func
(paren
op_amp
id|reg
(braket
l_int|12
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|PRG_CL_RESET_VALID
)paren
(brace
id|out_be32
c_func
(paren
op_amp
id|reg
(braket
l_int|12
)braket
comma
id|val
op_amp
op_complement
id|PRG_CL_RESET_VALID
)paren
suffix:semicolon
id|in_be32
c_func
(paren
op_amp
id|reg
(braket
l_int|12
)braket
)paren
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|reg
)paren
suffix:semicolon
)brace
multiline_comment|/* Marvell Discovery II based Pegasos 2 */
DECL|function|setup_peg2
r_static
r_void
id|__init
id|setup_peg2
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_struct
id|device_node
op_star
id|dev
)paren
(brace
r_struct
id|device_node
op_star
id|root
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_struct
id|device_node
op_star
id|rtas
suffix:semicolon
id|rtas
op_assign
id|of_find_node_by_name
(paren
id|root
comma
l_string|&quot;rtas&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtas
)paren
(brace
id|hose-&gt;ops
op_assign
op_amp
id|rtas_pci_ops
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
l_string|&quot;RTAS supporting Pegasos OF not found, please upgrade&quot;
l_string|&quot; your firmware&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|pci_assign_all_busses
op_assign
l_int|1
suffix:semicolon
)brace
r_void
id|__init
DECL|function|chrp_find_bridges
id|chrp_find_bridges
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|dev
suffix:semicolon
r_int
op_star
id|bus_range
suffix:semicolon
r_int
id|len
comma
id|index
op_assign
op_minus
l_int|1
suffix:semicolon
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_int
r_int
op_star
id|dma
suffix:semicolon
r_char
op_star
id|model
comma
op_star
id|machine
suffix:semicolon
r_int
id|is_longtrail
op_assign
l_int|0
comma
id|is_mot
op_assign
l_int|0
comma
id|is_pegasos
op_assign
l_int|0
suffix:semicolon
r_struct
id|device_node
op_star
id|root
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The PCI host bridge nodes on some machines don&squot;t have&n;&t; * properties to adequately identify them, so we have to&n;&t; * look at what sort of machine this is as well.&n;&t; */
id|machine
op_assign
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine
op_ne
l_int|NULL
)paren
(brace
id|is_longtrail
op_assign
id|strncmp
c_func
(paren
id|machine
comma
l_string|&quot;IBM,LongTrail&quot;
comma
l_int|13
)paren
op_eq
l_int|0
suffix:semicolon
id|is_mot
op_assign
id|strncmp
c_func
(paren
id|machine
comma
l_string|&quot;MOT&quot;
comma
l_int|3
)paren
op_eq
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|machine
comma
l_string|&quot;Pegasos2&quot;
comma
l_int|8
)paren
op_eq
l_int|0
)paren
id|is_pegasos
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|machine
comma
l_string|&quot;Pegasos&quot;
comma
l_int|7
)paren
op_eq
l_int|0
)paren
id|is_pegasos
op_assign
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|dev
op_assign
id|root-&gt;child
suffix:semicolon
id|dev
op_ne
l_int|NULL
suffix:semicolon
id|dev
op_assign
id|dev-&gt;sibling
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;type
op_eq
l_int|NULL
op_logical_or
id|strcmp
c_func
(paren
id|dev-&gt;type
comma
l_string|&quot;pci&quot;
)paren
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
op_increment
id|index
suffix:semicolon
multiline_comment|/* The GG2 bridge on the LongTrail doesn&squot;t have an address */
r_if
c_cond
(paren
id|dev-&gt;n_addrs
OL
l_int|1
op_logical_and
op_logical_neg
id|is_longtrail
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can&squot;t use %s: no address&bslash;n&quot;
comma
id|dev-&gt;full_name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|bus_range
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dev
comma
l_string|&quot;bus-range&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus_range
op_eq
l_int|NULL
op_logical_or
id|len
OL
l_int|2
op_star
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can&squot;t get bus-range for %s&bslash;n&quot;
comma
id|dev-&gt;full_name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bus_range
(braket
l_int|1
)braket
op_eq
id|bus_range
(braket
l_int|0
)braket
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI bus %d&quot;
comma
id|bus_range
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI buses %d..%d&quot;
comma
id|bus_range
(braket
l_int|0
)braket
comma
id|bus_range
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; controlled by %s&quot;
comma
id|dev-&gt;type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;n_addrs
OG
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot; at %x&quot;
comma
id|dev-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|hose
op_assign
id|pcibios_alloc_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Can&squot;t allocate PCI controller structure for %s&bslash;n&quot;
comma
id|dev-&gt;full_name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|hose-&gt;arch_data
op_assign
id|dev
suffix:semicolon
id|hose-&gt;first_busno
op_assign
id|bus_range
(braket
l_int|0
)braket
suffix:semicolon
id|hose-&gt;last_busno
op_assign
id|bus_range
(braket
l_int|1
)braket
suffix:semicolon
id|model
op_assign
id|get_property
c_func
(paren
id|dev
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model
op_eq
l_int|NULL
)paren
id|model
op_assign
l_string|&quot;&lt;none&gt;&quot;
suffix:semicolon
r_if
c_cond
(paren
id|device_is_compatible
c_func
(paren
id|dev
comma
l_string|&quot;IBM,python&quot;
)paren
)paren
(brace
id|setup_python
c_func
(paren
id|hose
comma
id|dev
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_mot
op_logical_or
id|strncmp
c_func
(paren
id|model
comma
l_string|&quot;Motorola, Grackle&quot;
comma
l_int|17
)paren
op_eq
l_int|0
)paren
(brace
id|setup_grackle
c_func
(paren
id|hose
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_longtrail
)paren
(brace
r_void
id|__iomem
op_star
id|p
op_assign
id|ioremap
c_func
(paren
id|GG2_PCI_CONFIG_BASE
comma
l_int|0x80000
)paren
suffix:semicolon
id|hose-&gt;ops
op_assign
op_amp
id|gg2_pci_ops
suffix:semicolon
id|hose-&gt;cfg_data
op_assign
id|p
suffix:semicolon
id|gg2_pci_config_base
op_assign
id|p
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_pegasos
op_eq
l_int|1
)paren
(brace
id|setup_indirect_pci
c_func
(paren
id|hose
comma
l_int|0xfec00cf8
comma
l_int|0xfee00cfc
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_pegasos
op_eq
l_int|2
)paren
(brace
id|setup_peg2
c_func
(paren
id|hose
comma
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;No methods for %s (model %s), using RTAS&bslash;n&quot;
comma
id|dev-&gt;full_name
comma
id|model
)paren
suffix:semicolon
id|hose-&gt;ops
op_assign
op_amp
id|rtas_pci_ops
suffix:semicolon
)brace
id|pci_process_bridge_OF_ranges
c_func
(paren
id|hose
comma
id|dev
comma
id|index
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* check the first bridge for a property that we can&n;&t;&t;   use to set pci_dram_offset */
id|dma
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dev
comma
l_string|&quot;ibm,dma-ranges&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
op_eq
l_int|0
op_logical_and
id|dma
op_ne
l_int|NULL
op_logical_and
id|len
op_ge
l_int|6
op_star
r_sizeof
(paren
op_star
id|dma
)paren
)paren
(brace
id|pci_dram_offset
op_assign
id|dma
(braket
l_int|2
)braket
op_minus
id|dma
(braket
l_int|3
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pci_dram_offset = %lx&bslash;n&quot;
comma
id|pci_dram_offset
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Do not fixup interrupts from OF tree on pegasos */
r_if
c_cond
(paren
id|is_pegasos
op_eq
l_int|0
)paren
id|ppc_md.pcibios_fixup
op_assign
id|chrp_pcibios_fixup
suffix:semicolon
)brace
eof
