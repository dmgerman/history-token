multiline_comment|/*&n; * eeh.c&n; * Copyright (C) 2001 Dave Engebretsen &amp; Todd Inglett IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/* Change Activity:&n; * 2001/10/27 : engebret : Created.&n; * End Change Activity &n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|macro|BUID_HI
mdefine_line|#define BUID_HI(buid) ((buid) &gt;&gt; 32)
DECL|macro|BUID_LO
mdefine_line|#define BUID_LO(buid) ((buid) &amp; 0xffffffff)
DECL|macro|CONFIG_ADDR
mdefine_line|#define CONFIG_ADDR(busno, devfn) (((((busno) &amp; 0xff) &lt;&lt; 8) | ((devfn) &amp; 0xf8)) &lt;&lt; 8)
DECL|variable|eeh_total_mmio_ffs
r_int
r_int
id|eeh_total_mmio_ffs
suffix:semicolon
DECL|variable|eeh_false_positives
r_int
r_int
id|eeh_false_positives
suffix:semicolon
multiline_comment|/* RTAS tokens */
DECL|variable|ibm_set_eeh_option
r_static
r_int
id|ibm_set_eeh_option
suffix:semicolon
DECL|variable|ibm_set_slot_reset
r_static
r_int
id|ibm_set_slot_reset
suffix:semicolon
DECL|variable|ibm_read_slot_reset_state
r_static
r_int
id|ibm_read_slot_reset_state
suffix:semicolon
DECL|variable|eeh_implemented
r_int
id|eeh_implemented
suffix:semicolon
DECL|macro|EEH_MAX_OPTS
mdefine_line|#define EEH_MAX_OPTS 4096
DECL|variable|eeh_opts
r_static
r_char
op_star
id|eeh_opts
suffix:semicolon
DECL|variable|eeh_opts_last
r_static
r_int
id|eeh_opts_last
suffix:semicolon
r_static
r_int
id|eeh_check_opts_config
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|default_state
)paren
suffix:semicolon
DECL|function|eeh_token
r_int
r_int
id|eeh_token
c_func
(paren
r_int
r_int
id|phb
comma
r_int
r_int
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
r_int
id|offset
)paren
(brace
r_if
c_cond
(paren
id|phb
OG
l_int|0xff
)paren
id|panic
c_func
(paren
l_string|&quot;eeh_token: phb 0x%lx is too large&bslash;n&quot;
comma
id|phb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_amp
l_int|0x0fffffff00000000
)paren
id|panic
c_func
(paren
l_string|&quot;eeh_token: offset 0x%lx is out of range&bslash;n&quot;
comma
id|offset
)paren
suffix:semicolon
r_return
(paren
(paren
id|IO_UNMAPPED_REGION_ID
op_lshift
l_int|60
)paren
op_or
(paren
id|phb
op_lshift
l_int|48UL
)paren
op_or
(paren
(paren
id|bus
op_amp
l_int|0xff
)paren
op_lshift
l_int|40UL
)paren
op_or
(paren
id|devfn
op_lshift
l_int|32UL
)paren
op_or
(paren
id|offset
op_amp
l_int|0xffffffff
)paren
)paren
suffix:semicolon
)brace
DECL|function|eeh_get_state
r_int
id|eeh_get_state
c_func
(paren
r_int
r_int
id|ea
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Check for an eeh failure at the given token address.&n; * The given value has been read and it should be 1&squot;s (0xff, 0xffff or&n; * 0xffffffff).&n; *&n; * Probe to determine if an error actually occurred.  If not return val.&n; * Otherwise panic.&n; */
DECL|function|eeh_check_failure
r_int
r_int
id|eeh_check_failure
c_func
(paren
r_void
op_star
id|token
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|config_addr
op_assign
(paren
r_int
r_int
)paren
id|token
op_rshift
l_int|24
suffix:semicolon
multiline_comment|/* PPBBDDRR */
r_int
r_int
id|phbidx
op_assign
(paren
id|config_addr
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
r_struct
id|pci_controller
op_star
id|phb
suffix:semicolon
r_int
r_int
id|ret
comma
id|rets
(braket
l_int|2
)braket
suffix:semicolon
id|config_addr
op_and_assign
l_int|0xffff00
suffix:semicolon
multiline_comment|/* 00BBDD00 */
r_if
c_cond
(paren
id|phbidx
op_ge
id|global_phb_number
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;EEH: checking token %p phb index of %ld is greater than max of %d&bslash;n&quot;
comma
id|token
comma
id|phbidx
comma
id|global_phb_number
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|phb
op_assign
id|phbtab
(braket
id|phbidx
)braket
suffix:semicolon
id|ret
op_assign
id|rtas_call
c_func
(paren
id|ibm_read_slot_reset_state
comma
l_int|3
comma
l_int|3
comma
id|rets
comma
id|config_addr
comma
id|BUID_HI
c_func
(paren
id|phb-&gt;buid
)paren
comma
id|BUID_LO
c_func
(paren
id|phb-&gt;buid
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
op_logical_and
id|rets
(braket
l_int|1
)braket
op_eq
l_int|1
op_logical_and
id|rets
(braket
l_int|0
)braket
op_ge
l_int|2
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|bus
op_assign
(paren
(paren
r_int
r_int
)paren
id|token
op_rshift
l_int|40
)paren
op_amp
l_int|0xffff
suffix:semicolon
multiline_comment|/* include PHB# in bus */
r_int
id|devfn
op_assign
(paren
id|config_addr
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|dev
op_assign
id|pci_find_slot
c_func
(paren
id|bus
comma
id|devfn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EEH:  MMIO failure (%ld) on device:&bslash;n  %s %s&bslash;n&quot;
comma
id|rets
(braket
l_int|0
)braket
comma
id|dev-&gt;slot_name
comma
id|dev-&gt;dev.name
)paren
suffix:semicolon
id|PPCDBG_ENTER_DEBUGGER
c_func
(paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;EEH:  MMIO failure (%ld) on device:&bslash;n  %s %s&bslash;n&quot;
comma
id|rets
(braket
l_int|0
)braket
comma
id|dev-&gt;slot_name
comma
id|dev-&gt;dev.name
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EEH:  MMIO failure (%ld) on device buid %lx, config_addr %lx&bslash;n&quot;
comma
id|rets
(braket
l_int|0
)braket
comma
id|phb-&gt;buid
comma
id|config_addr
)paren
suffix:semicolon
id|PPCDBG_ENTER_DEBUGGER
c_func
(paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;EEH:  MMIO failure (%ld) on device buid %lx, config_addr %lx&bslash;n&quot;
comma
id|rets
(braket
l_int|0
)braket
comma
id|phb-&gt;buid
comma
id|config_addr
)paren
suffix:semicolon
)brace
)brace
id|eeh_false_positives
op_increment
suffix:semicolon
r_return
id|val
suffix:semicolon
multiline_comment|/* good case */
)brace
DECL|struct|eeh_early_enable_info
r_struct
id|eeh_early_enable_info
(brace
DECL|member|buid_hi
r_int
r_int
id|buid_hi
suffix:semicolon
DECL|member|buid_lo
r_int
r_int
id|buid_lo
suffix:semicolon
DECL|member|adapters_enabled
r_int
id|adapters_enabled
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Enable eeh for the given device node. */
DECL|function|early_enable_eeh
r_static
r_void
op_star
id|early_enable_eeh
c_func
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|eeh_early_enable_info
op_star
id|info
op_assign
id|data
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* Try to enable eeh */
id|ret
op_assign
id|rtas_call
c_func
(paren
id|ibm_set_eeh_option
comma
l_int|4
comma
l_int|1
comma
l_int|NULL
comma
id|CONFIG_ADDR
c_func
(paren
id|dn-&gt;busno
comma
id|dn-&gt;devfn
)paren
comma
id|info-&gt;buid_hi
comma
id|info-&gt;buid_lo
comma
id|EEH_ENABLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|info-&gt;adapters_enabled
op_increment
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize eeh by trying to enable it for all of the adapters in the system.&n; * As a side effect we can determine here if eeh is supported at all.&n; * Note that we leave EEH on so failed config cycles won&squot;t cause a machine&n; * check.  If a user turns off EEH for a particular adapter they are really&n; * telling Linux to ignore errors.&n; *&n; * We should probably distinguish between &quot;ignore errors&quot; and &quot;turn EEH off&quot;&n; * but for now disabling EEH for adapters is mostly to work around drivers that&n; * directly access mmio space (without using the macros).&n; *&n; * The eeh-force-off/on option does literally what it says, so if Linux must&n; * avoid enabling EEH this must be done.&n; */
DECL|function|eeh_init
r_void
id|eeh_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|phb
suffix:semicolon
r_struct
id|eeh_early_enable_info
id|info
suffix:semicolon
r_extern
r_char
id|cmd_line
(braket
)braket
suffix:semicolon
multiline_comment|/* Very early cmd line parse.  Cheap, but works. */
r_char
op_star
id|eeh_force_off
op_assign
id|strstr
c_func
(paren
id|cmd_line
comma
l_string|&quot;eeh-force-off&quot;
)paren
suffix:semicolon
r_char
op_star
id|eeh_force_on
op_assign
id|strstr
c_func
(paren
id|cmd_line
comma
l_string|&quot;eeh-force-on&quot;
)paren
suffix:semicolon
id|ibm_set_eeh_option
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,set-eeh-option&quot;
)paren
suffix:semicolon
id|ibm_set_slot_reset
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,set-slot-reset&quot;
)paren
suffix:semicolon
id|ibm_read_slot_reset_state
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,read-slot-reset-state&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ibm_set_eeh_option
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|eeh_force_off
OG
id|eeh_force_on
)paren
(brace
multiline_comment|/* User is forcing EEH off.  Be noisy if it is implemented. */
r_if
c_cond
(paren
id|eeh_implemented
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;EEH: WARNING: PCI Enhanced I/O Error Handling is user disabled&bslash;n&quot;
)paren
suffix:semicolon
id|eeh_implemented
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|eeh_force_on
OG
id|eeh_force_off
)paren
id|eeh_implemented
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* User is forcing it on. */
multiline_comment|/* Enable EEH for all adapters.  Note that eeh requires buid&squot;s */
id|info.adapters_enabled
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|phb
op_assign
id|find_devices
c_func
(paren
l_string|&quot;pci&quot;
)paren
suffix:semicolon
id|phb
suffix:semicolon
id|phb
op_assign
id|phb-&gt;next
)paren
(brace
r_int
id|len
suffix:semicolon
r_int
op_star
id|buid_vals
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|phb
comma
l_string|&quot;ibm,fw-phb-id&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buid_vals
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|info.buid_lo
op_assign
id|buid_vals
(braket
l_int|0
)braket
suffix:semicolon
id|info.buid_hi
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|len
op_eq
r_sizeof
(paren
r_int
)paren
op_star
l_int|2
)paren
(brace
id|info.buid_hi
op_assign
id|buid_vals
(braket
l_int|0
)braket
suffix:semicolon
id|info.buid_lo
op_assign
id|buid_vals
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;EEH: odd ibm,fw-phb-id len returned: %d&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|traverse_pci_devices
c_func
(paren
id|phb
comma
id|early_enable_eeh
comma
l_int|NULL
comma
op_amp
id|info
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info.adapters_enabled
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;EEH: PCI Enhanced I/O Error Handling Enabled&bslash;n&quot;
)paren
suffix:semicolon
id|eeh_implemented
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* Given a PCI device check if eeh should be configured or not.&n; * This may look at firmware properties and/or kernel cmdline options.&n; */
DECL|function|is_eeh_configured
r_int
id|is_eeh_configured
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|device_node
op_star
id|dn
op_assign
id|pci_device_to_OF_node
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|pci_controller
op_star
id|phb
op_assign
id|PCI_GET_PHB_PTR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|ret
comma
id|rets
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|eeh_capable
suffix:semicolon
r_int
id|default_state
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* default enable EEH if we can. */
r_if
c_cond
(paren
id|dn
op_eq
l_int|NULL
op_logical_or
id|phb
op_eq
l_int|NULL
op_logical_or
op_logical_neg
id|eeh_implemented
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Hack: turn off eeh for display class devices by default.&n;&t; * This fixes matrox accel framebuffer.&n;&t; */
r_if
c_cond
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|16
)paren
op_eq
id|PCI_BASE_CLASS_DISPLAY
)paren
id|default_state
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Ignore known PHBs and EADs bridges */
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_IBM
op_logical_and
(paren
id|dev-&gt;device
op_eq
l_int|0x0102
op_logical_or
id|dev-&gt;device
op_eq
l_int|0x008b
)paren
)paren
id|default_state
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eeh_check_opts_config
c_func
(paren
id|dev
comma
id|default_state
)paren
)paren
(brace
r_if
c_cond
(paren
id|default_state
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;EEH: %s %s user requested to run without EEH.&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|dev-&gt;dev.name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ret
op_assign
id|rtas_call
c_func
(paren
id|ibm_read_slot_reset_state
comma
l_int|3
comma
l_int|3
comma
id|rets
comma
id|CONFIG_ADDR
c_func
(paren
id|dn-&gt;busno
comma
id|dn-&gt;devfn
)paren
comma
id|BUID_HI
c_func
(paren
id|phb-&gt;buid
)paren
comma
id|BUID_LO
c_func
(paren
id|phb-&gt;buid
)paren
)paren
suffix:semicolon
id|eeh_capable
op_assign
(paren
id|ret
op_eq
l_int|0
op_logical_and
id|rets
(braket
l_int|1
)braket
op_eq
l_int|1
)paren
suffix:semicolon
r_return
id|eeh_capable
suffix:semicolon
)brace
DECL|function|eeh_set_option
r_int
id|eeh_set_option
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|option
)paren
(brace
r_struct
id|device_node
op_star
id|dn
op_assign
id|pci_device_to_OF_node
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|pci_controller
op_star
id|phb
op_assign
id|PCI_GET_PHB_PTR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn
op_eq
l_int|NULL
op_logical_or
id|phb
op_eq
l_int|NULL
op_logical_or
id|phb-&gt;buid
op_eq
l_int|0
op_logical_or
op_logical_neg
id|eeh_implemented
)paren
r_return
op_minus
l_int|2
suffix:semicolon
r_return
id|rtas_call
c_func
(paren
id|ibm_set_eeh_option
comma
l_int|4
comma
l_int|1
comma
l_int|NULL
comma
id|CONFIG_ADDR
c_func
(paren
id|dn-&gt;busno
comma
id|dn-&gt;devfn
)paren
comma
id|BUID_HI
c_func
(paren
id|phb-&gt;buid
)paren
comma
id|BUID_LO
c_func
(paren
id|phb-&gt;buid
)paren
comma
id|option
)paren
suffix:semicolon
)brace
DECL|function|eeh_proc_falsepositive_read
r_static
r_int
id|eeh_proc_falsepositive_read
c_func
(paren
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
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;eeh_false_positives=%ld&bslash;n&quot;
l_string|&quot;eeh_total_mmio_ffs=%ld&bslash;n&quot;
comma
id|eeh_false_positives
comma
id|eeh_total_mmio_ffs
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* Implementation of /proc/ppc64/eeh&n; * For now it is one file showing false positives.&n; */
DECL|function|eeh_init_proc
r_static
r_int
id|__init
id|eeh_init_proc
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;ppc64/eeh&quot;
comma
id|S_IRUGO
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|ent-&gt;data
op_assign
l_int|NULL
suffix:semicolon
id|ent-&gt;read_proc
op_assign
(paren
r_void
op_star
)paren
id|eeh_proc_falsepositive_read
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Test if &quot;dev&quot; should be configured on or off.&n; * This processes the options literally from left to right.&n; * This lets the user specify stupid combinations of options,&n; * but at least the result should be very predictable.&n; */
DECL|function|eeh_check_opts_config
r_static
r_int
id|eeh_check_opts_config
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|default_state
)paren
(brace
r_struct
id|device_node
op_star
id|dn
op_assign
id|pci_device_to_OF_node
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|pci_controller
op_star
id|phb
op_assign
id|PCI_GET_PHB_PTR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_char
id|devname
(braket
l_int|32
)braket
comma
id|classname
(braket
l_int|32
)braket
comma
id|phbname
(braket
l_int|32
)braket
suffix:semicolon
r_char
op_star
id|strs
(braket
l_int|8
)braket
comma
op_star
id|s
suffix:semicolon
r_int
id|nstrs
comma
id|i
suffix:semicolon
r_int
id|ret
op_assign
id|default_state
suffix:semicolon
r_if
c_cond
(paren
id|dn
op_eq
l_int|NULL
op_logical_or
id|phb
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Build list of strings to match */
id|nstrs
op_assign
l_int|0
suffix:semicolon
id|s
op_assign
(paren
r_char
op_star
)paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;ibm,loc-code&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
id|strs
(braket
id|nstrs
op_increment
)braket
op_assign
id|s
suffix:semicolon
id|sprintf
c_func
(paren
id|devname
comma
l_string|&quot;dev%04x:%04x&quot;
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
)paren
suffix:semicolon
id|strs
(braket
id|nstrs
op_increment
)braket
op_assign
id|devname
suffix:semicolon
id|sprintf
c_func
(paren
id|classname
comma
l_string|&quot;class%04x&quot;
comma
id|dev
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
id|strs
(braket
id|nstrs
op_increment
)braket
op_assign
id|classname
suffix:semicolon
id|sprintf
c_func
(paren
id|phbname
comma
l_string|&quot;pci@%lx&quot;
comma
id|phb-&gt;buid
)paren
suffix:semicolon
id|strs
(braket
id|nstrs
op_increment
)braket
op_assign
id|phbname
suffix:semicolon
id|strs
(braket
id|nstrs
op_increment
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
multiline_comment|/* yes, this matches the empty string */
multiline_comment|/* Now see if any string matches the eeh_opts list.&n;&t; * The eeh_opts list entries start with + or -.&n;&t; */
r_for
c_loop
(paren
id|s
op_assign
id|eeh_opts
suffix:semicolon
id|s
op_logical_and
(paren
id|s
OL
(paren
id|eeh_opts
op_plus
id|eeh_opts_last
)paren
)paren
suffix:semicolon
id|s
op_add_assign
id|strlen
c_func
(paren
id|s
)paren
op_plus
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nstrs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcasecmp
c_func
(paren
id|strs
(braket
id|i
)braket
comma
id|s
op_plus
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|ret
op_assign
(paren
id|strs
(braket
id|i
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;+&squot;
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Handle kernel eeh-on &amp; eeh-off cmd line options for eeh.&n; *&n; * We support:&n; *&t;eeh-off=loc1,loc2,loc3...&n; *&n; * and this option can be repeated so&n; *      eeh-off=loc1,loc2 eeh-off=loc3&n; * is the same as eeh-off=loc1,loc2,loc3&n; *&n; * loc is an IBM location code that can be found in a manual or&n; * via openfirmware (or the Hardware Management Console).&n; *&n; * We also support these additional &quot;loc&quot; values:&n; *&n; *&t;dev#:#    vendor:device id in hex (e.g. dev1022:2000)&n; *&t;class#    class id in hex (e.g. class0200)&n; *&t;pci@buid  all devices under phb (e.g. pci@fef00000)&n; *&n; * If no location code is specified all devices are assumed&n; * so eeh-off means eeh by default is off.&n; */
multiline_comment|/* This is implemented as a null separated list of strings.&n; * Each string looks like this:  &quot;+X&quot; or &quot;-X&quot;&n; * where X is a loc code, dev, class or pci string (as shown above)&n; * or empty which is used to indicate all.&n; *&n; * We interpret this option string list during the buswalk&n; * so that it will literally behave left-to-right even if&n; * some combinations don&squot;t make sense.  Give the user exactly&n; * what they want! :)&n; */
DECL|function|eeh_parm
r_static
r_int
id|__init
id|eeh_parm
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|state
)paren
(brace
r_char
op_star
id|s
comma
op_star
id|cur
comma
op_star
id|curend
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eeh_opts
)paren
(brace
id|eeh_opts
op_assign
id|alloc_bootmem
c_func
(paren
id|EEH_MAX_OPTS
)paren
suffix:semicolon
id|eeh_opts
(braket
id|eeh_opts_last
op_increment
)braket
op_assign
l_char|&squot;+&squot;
suffix:semicolon
multiline_comment|/* default */
id|eeh_opts
(braket
id|eeh_opts_last
op_increment
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|eeh_opts
(braket
id|eeh_opts_last
op_increment
)braket
op_assign
id|state
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|eeh_opts
(braket
id|eeh_opts_last
op_increment
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;=&squot;
)paren
id|str
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|str
suffix:semicolon
id|s
op_logical_and
op_star
id|s
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|s
op_assign
id|curend
)paren
(brace
id|cur
op_assign
id|s
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cur
op_eq
l_char|&squot;,&squot;
)paren
id|cur
op_increment
suffix:semicolon
multiline_comment|/* ignore empties.  Don&squot;t treat as &quot;all-on&quot; or &quot;all-off&quot; */
id|curend
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|curend
)paren
id|curend
op_assign
id|cur
op_plus
id|strlen
c_func
(paren
id|cur
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cur
)paren
(brace
r_int
id|curlen
op_assign
id|curend
op_minus
id|cur
suffix:semicolon
r_if
c_cond
(paren
id|eeh_opts_last
op_plus
id|curlen
OG
id|EEH_MAX_OPTS
op_minus
l_int|2
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;EEH: sorry...too many eeh cmd line options&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|eeh_opts
(braket
id|eeh_opts_last
op_increment
)braket
op_assign
id|state
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|strncpy
c_func
(paren
id|eeh_opts
op_plus
id|eeh_opts_last
comma
id|cur
comma
id|curlen
)paren
suffix:semicolon
id|eeh_opts_last
op_add_assign
id|curlen
suffix:semicolon
id|eeh_opts
(braket
id|eeh_opts_last
op_increment
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|eehoff_parm
r_static
r_int
id|__init
id|eehoff_parm
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
id|eeh_parm
c_func
(paren
id|str
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|eehon_parm
r_static
r_int
id|__init
id|eehon_parm
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
id|eeh_parm
c_func
(paren
id|str
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|eeh_init_proc
id|__initcall
c_func
(paren
id|eeh_init_proc
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;eeh-off&quot;
comma
id|eehoff_parm
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;eeh-on&quot;
comma
id|eehon_parm
)paren
suffix:semicolon
eof
