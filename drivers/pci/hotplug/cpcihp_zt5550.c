multiline_comment|/*&n; * cpcihp_zt5550.c&n; *&n; * Intel/Ziatech ZT5550 CompactPCI Host Controller driver&n; *&n; * Copyright 2002 SOMA Networks, Inc.&n; * Copyright 2001 Intel San Luis Obispo&n; * Copyright 2000,2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES,&n; * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY &n; * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL &n; * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, &n; * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, &n; * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR &n; * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF &n; * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING &n; * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS &n; * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;scottm@somanetworks.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;cpci_hotplug.h&quot;
macro_line|#include &quot;cpcihp_zt5550.h&quot;
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION&t;&quot;0.2&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&quot;Scott Murray &lt;scottm@somanetworks.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&quot;ZT5550 CompactPCI Hot Plug Driver&quot;
macro_line|#if !defined(CONFIG_HOTPLUG_PCI_CPCI_ZT5550_MODULE)
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME&t;&quot;cpcihp_zt5550&quot;
macro_line|#else
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME&t;THIS_MODULE-&gt;name
macro_line|#endif
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if(debug)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk (KERN_DEBUG &quot;%s: &quot; format &quot;&bslash;n&quot;,&t;&bslash;&n;&t;&t;&t;&t;MY_NAME , ## arg); &t;&t;&bslash;&n;&t;} while(0)
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR &quot;%s: &quot; format &quot;&bslash;n&quot;, MY_NAME , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO &quot;%s: &quot; format &quot;&bslash;n&quot;, MY_NAME , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING &quot;%s: &quot; format &quot;&bslash;n&quot;, MY_NAME , ## arg)
multiline_comment|/* local variables */
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
DECL|variable|poll
r_static
r_int
id|poll
suffix:semicolon
DECL|variable|zt5550_hpc_ops
r_static
r_struct
id|cpci_hp_controller_ops
id|zt5550_hpc_ops
suffix:semicolon
DECL|variable|zt5550_hpc
r_static
r_struct
id|cpci_hp_controller
id|zt5550_hpc
suffix:semicolon
multiline_comment|/* Primary cPCI bus bridge device */
DECL|variable|bus0_dev
r_static
r_struct
id|pci_dev
op_star
id|bus0_dev
suffix:semicolon
DECL|variable|bus0
r_static
r_struct
id|pci_bus
op_star
id|bus0
suffix:semicolon
multiline_comment|/* Host controller device */
DECL|variable|hc_dev
r_static
r_struct
id|pci_dev
op_star
id|hc_dev
suffix:semicolon
multiline_comment|/* Host controller register addresses */
DECL|variable|hc_registers
r_static
r_void
op_star
id|hc_registers
suffix:semicolon
DECL|variable|csr_hc_index
r_static
r_void
op_star
id|csr_hc_index
suffix:semicolon
DECL|variable|csr_hc_data
r_static
r_void
op_star
id|csr_hc_data
suffix:semicolon
DECL|variable|csr_int_status
r_static
r_void
op_star
id|csr_int_status
suffix:semicolon
DECL|variable|csr_int_mask
r_static
r_void
op_star
id|csr_int_mask
suffix:semicolon
DECL|function|zt5550_hc_config
r_static
r_int
id|zt5550_hc_config
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
multiline_comment|/* Since we know that no boards exist with two HC chips, treat it as an error */
r_if
c_cond
(paren
id|hc_dev
)paren
(brace
id|err
c_func
(paren
l_string|&quot;too many host controller devices?&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|hc_dev
op_assign
id|pdev
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;hc_dev = %p&quot;
comma
id|hc_dev
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;pci resource start %lx&quot;
comma
id|pci_resource_start
c_func
(paren
id|hc_dev
comma
l_int|1
)paren
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;pci resource len %lx&quot;
comma
id|pci_resource_len
c_func
(paren
id|hc_dev
comma
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|hc_dev
comma
l_int|1
)paren
comma
id|pci_resource_len
c_func
(paren
id|hc_dev
comma
l_int|1
)paren
comma
id|MY_NAME
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;cannot reserve MMIO region&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|hc_registers
op_assign
id|ioremap
c_func
(paren
id|pci_resource_start
c_func
(paren
id|hc_dev
comma
l_int|1
)paren
comma
id|pci_resource_len
c_func
(paren
id|hc_dev
comma
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hc_registers
)paren
(brace
id|err
c_func
(paren
l_string|&quot;cannot remap MMIO region %lx @ %lx&quot;
comma
id|pci_resource_len
c_func
(paren
id|hc_dev
comma
l_int|1
)paren
comma
id|pci_resource_start
c_func
(paren
id|hc_dev
comma
l_int|1
)paren
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|hc_dev
comma
l_int|1
)paren
comma
id|pci_resource_len
c_func
(paren
id|hc_dev
comma
l_int|1
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|csr_hc_index
op_assign
id|hc_registers
op_plus
id|CSR_HCINDEX
suffix:semicolon
id|csr_hc_data
op_assign
id|hc_registers
op_plus
id|CSR_HCDATA
suffix:semicolon
id|csr_int_status
op_assign
id|hc_registers
op_plus
id|CSR_INTSTAT
suffix:semicolon
id|csr_int_mask
op_assign
id|hc_registers
op_plus
id|CSR_INTMASK
suffix:semicolon
multiline_comment|/*&n;&t; * Disable host control, fault and serial interrupts&n;&t; */
id|dbg
c_func
(paren
l_string|&quot;disabling host control, fault and serial interrupts&quot;
)paren
suffix:semicolon
id|writeb
c_func
(paren
(paren
id|u8
)paren
id|HC_INT_MASK_REG
comma
id|csr_hc_index
)paren
suffix:semicolon
id|writeb
c_func
(paren
(paren
id|u8
)paren
id|ALL_INDEXED_INTS_MASK
comma
id|csr_hc_data
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;disabled host control, fault and serial interrupts&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable timer0, timer1 and ENUM interrupts&n;&t; */
id|dbg
c_func
(paren
l_string|&quot;disabling timer0, timer1 and ENUM interrupts&quot;
)paren
suffix:semicolon
id|writeb
c_func
(paren
(paren
id|u8
)paren
id|ALL_DIRECT_INTS_MASK
comma
id|csr_int_mask
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;disabled timer0, timer1 and ENUM interrupts&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|zt5550_hc_cleanup
r_static
r_int
id|zt5550_hc_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hc_dev
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|release_mem_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|hc_dev
comma
l_int|1
)paren
comma
id|pci_resource_len
c_func
(paren
id|hc_dev
comma
l_int|1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|zt5550_hc_query_enum
r_static
r_int
id|zt5550_hc_query_enum
c_func
(paren
r_void
)paren
(brace
id|u8
id|value
suffix:semicolon
id|value
op_assign
id|inb_p
c_func
(paren
id|ENUM_PORT
)paren
suffix:semicolon
r_return
(paren
(paren
id|value
op_amp
id|ENUM_MASK
)paren
op_eq
id|ENUM_MASK
)paren
suffix:semicolon
)brace
DECL|function|zt5550_hc_check_irq
r_static
r_int
id|zt5550_hc_check_irq
c_func
(paren
r_void
op_star
id|dev_id
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|reg
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev_id
op_eq
id|zt5550_hpc.dev_id
)paren
(brace
id|reg
op_assign
id|readb
c_func
(paren
id|csr_int_status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
)paren
(brace
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|zt5550_hc_enable_irq
r_static
r_int
id|zt5550_hc_enable_irq
c_func
(paren
r_void
)paren
(brace
id|u8
id|reg
suffix:semicolon
r_if
c_cond
(paren
id|hc_dev
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|reg
op_assign
id|readb
c_func
(paren
id|csr_int_mask
)paren
suffix:semicolon
id|reg
op_assign
id|reg
op_amp
op_complement
id|ENUM_INT_MASK
suffix:semicolon
id|writeb
c_func
(paren
id|reg
comma
id|csr_int_mask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|zt5550_hc_disable_irq
r_int
id|zt5550_hc_disable_irq
c_func
(paren
r_void
)paren
(brace
id|u8
id|reg
suffix:semicolon
r_if
c_cond
(paren
id|hc_dev
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|reg
op_assign
id|readb
c_func
(paren
id|csr_int_mask
)paren
suffix:semicolon
id|reg
op_assign
id|reg
op_or
id|ENUM_INT_MASK
suffix:semicolon
id|writeb
c_func
(paren
id|reg
comma
id|csr_int_mask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|zt5550_hc_init_one
r_static
r_int
id|zt5550_hc_init_one
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
r_int
id|status
suffix:semicolon
id|status
op_assign
id|zt5550_hc_config
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
r_return
id|status
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;returned from zt5550_hc_config&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|zt5550_hpc
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cpci_hp_controller
)paren
)paren
suffix:semicolon
id|zt5550_hpc_ops.query_enum
op_assign
id|zt5550_hc_query_enum
suffix:semicolon
id|zt5550_hpc.ops
op_assign
op_amp
id|zt5550_hpc_ops
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|poll
)paren
(brace
id|zt5550_hpc.irq
op_assign
id|hc_dev-&gt;irq
suffix:semicolon
id|zt5550_hpc.irq_flags
op_assign
id|SA_SHIRQ
suffix:semicolon
id|zt5550_hpc.dev_id
op_assign
id|hc_dev
suffix:semicolon
id|zt5550_hpc_ops.enable_irq
op_assign
id|zt5550_hc_enable_irq
suffix:semicolon
id|zt5550_hpc_ops.disable_irq
op_assign
id|zt5550_hc_disable_irq
suffix:semicolon
id|zt5550_hpc_ops.check_irq
op_assign
id|zt5550_hc_check_irq
suffix:semicolon
)brace
r_else
(brace
id|info
c_func
(paren
l_string|&quot;using ENUM# polling mode&quot;
)paren
suffix:semicolon
)brace
id|status
op_assign
id|cpci_hp_register_controller
c_func
(paren
op_amp
id|zt5550_hpc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
id|err
c_func
(paren
l_string|&quot;could not register cPCI hotplug controller&quot;
)paren
suffix:semicolon
r_goto
id|init_hc_error
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;registered controller&quot;
)paren
suffix:semicolon
multiline_comment|/* Look for first device matching cPCI bus&squot;s bridge vendor and device IDs */
r_if
c_cond
(paren
op_logical_neg
(paren
id|bus0_dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_DEC
comma
id|PCI_DEVICE_ID_DEC_21154
comma
l_int|NULL
)paren
)paren
)paren
(brace
id|status
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|init_register_error
suffix:semicolon
)brace
id|bus0
op_assign
id|bus0_dev-&gt;subordinate
suffix:semicolon
id|status
op_assign
id|cpci_hp_register_bus
c_func
(paren
id|bus0
comma
l_int|0x0a
comma
l_int|0x0f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
id|err
c_func
(paren
l_string|&quot;could not register cPCI hotplug bus&quot;
)paren
suffix:semicolon
r_goto
id|init_register_error
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;registered bus&quot;
)paren
suffix:semicolon
id|status
op_assign
id|cpci_hp_start
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
id|err
c_func
(paren
l_string|&quot;could not started cPCI hotplug system&quot;
)paren
suffix:semicolon
id|cpci_hp_unregister_bus
c_func
(paren
id|bus0
)paren
suffix:semicolon
r_goto
id|init_register_error
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;started cpci hp system&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|init_register_error
suffix:colon
id|cpci_hp_unregister_controller
c_func
(paren
op_amp
id|zt5550_hpc
)paren
suffix:semicolon
id|init_hc_error
suffix:colon
id|err
c_func
(paren
l_string|&quot;status = %d&quot;
comma
id|status
)paren
suffix:semicolon
id|zt5550_hc_cleanup
c_func
(paren
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|zt5550_hc_remove_one
r_static
r_void
id|__devexit
id|zt5550_hc_remove_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|cpci_hp_stop
c_func
(paren
)paren
suffix:semicolon
id|cpci_hp_unregister_bus
c_func
(paren
id|bus0
)paren
suffix:semicolon
id|cpci_hp_unregister_controller
c_func
(paren
op_amp
id|zt5550_hpc
)paren
suffix:semicolon
id|zt5550_hc_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|zt5550_hc_pci_tbl
r_static
r_struct
id|pci_device_id
id|zt5550_hc_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_ZIATECH
comma
id|PCI_DEVICE_ID_ZIATECH_5550_HC
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|zt5550_hc_pci_tbl
)paren
suffix:semicolon
DECL|variable|zt5550_hc_driver
r_static
r_struct
id|pci_driver
id|zt5550_hc_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;zt5550_hc&quot;
comma
dot
id|id_table
op_assign
id|zt5550_hc_pci_tbl
comma
dot
id|probe
op_assign
id|zt5550_hc_init_one
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|zt5550_hc_remove_one
)paren
comma
)brace
suffix:semicolon
DECL|function|zt5550_init
r_static
r_int
id|__init
id|zt5550_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|resource
op_star
id|r
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_DESC
l_string|&quot; version: &quot;
id|DRIVER_VERSION
)paren
suffix:semicolon
id|r
op_assign
id|request_region
c_func
(paren
id|ENUM_PORT
comma
l_int|1
comma
l_string|&quot;#ENUM hotswap signal register&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_return
id|pci_module_init
c_func
(paren
op_amp
id|zt5550_hc_driver
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|zt5550_exit
id|zt5550_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|zt5550_hc_driver
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|ENUM_PORT
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|zt5550_init
id|module_init
c_func
(paren
id|zt5550_init
)paren
suffix:semicolon
DECL|variable|zt5550_exit
id|module_exit
c_func
(paren
id|zt5550_exit
)paren
suffix:semicolon
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;Debugging mode enabled or not&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|poll
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|poll
comma
l_string|&quot;#ENUM polling mode enabled or not&quot;
)paren
suffix:semicolon
eof
