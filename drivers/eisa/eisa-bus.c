multiline_comment|/*&n; * EISA bus support functions for sysfs.&n; *&n; * (C) 2002 Marc Zyngier &lt;maz@wild-wind.fr.eu.org&gt;&n; *&n; * This code is released under the GPL version 2.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/eisa.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|SLOT_ADDRESS
mdefine_line|#define SLOT_ADDRESS(r,n) (r-&gt;bus_base_addr + (0x1000 * n))
DECL|macro|EISA_DEVINFO
mdefine_line|#define EISA_DEVINFO(i,s) { .id = { .sig = i }, .name = s }
DECL|struct|eisa_device_info
r_struct
id|eisa_device_info
(brace
DECL|member|id
r_struct
id|eisa_device_id
id|id
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|DEVICE_NAME_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|eisa_table
r_struct
id|eisa_device_info
id|__initdata
id|eisa_table
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_EISA_NAMES
macro_line|#include &quot;devlist.h&quot;
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|EISA_INFOS
mdefine_line|#define EISA_INFOS (sizeof (eisa_table) / (sizeof (struct eisa_device_info)))
DECL|function|eisa_name_device
r_static
r_void
id|__init
id|eisa_name_device
(paren
r_struct
id|eisa_device
op_star
id|edev
)paren
(brace
r_int
id|i
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
id|EISA_INFOS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
(paren
id|edev-&gt;id.sig
comma
id|eisa_table
(braket
id|i
)braket
dot
id|id.sig
)paren
)paren
(brace
id|strncpy
(paren
id|edev-&gt;dev.name
comma
id|eisa_table
(braket
id|i
)braket
dot
id|name
comma
id|DEVICE_NAME_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* No name was found */
id|sprintf
(paren
id|edev-&gt;dev.name
comma
l_string|&quot;EISA device %.7s&quot;
comma
id|edev-&gt;id.sig
)paren
suffix:semicolon
)brace
DECL|function|decode_eisa_sig
r_static
r_char
id|__init
op_star
id|decode_eisa_sig
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_static
r_char
id|sig_str
(braket
id|EISA_SIG_LEN
)braket
suffix:semicolon
id|u8
id|sig
(braket
l_int|4
)braket
suffix:semicolon
id|u16
id|rev
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sig
(braket
l_int|0
)braket
op_assign
id|inb
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
(braket
l_int|0
)braket
op_amp
l_int|0x80
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|sig
(braket
id|i
)braket
op_assign
id|inb
(paren
id|addr
op_plus
id|i
)paren
suffix:semicolon
id|sig_str
(braket
l_int|0
)braket
op_assign
(paren
(paren
id|sig
(braket
l_int|0
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|0x1f
)paren
op_plus
(paren
l_char|&squot;A&squot;
op_minus
l_int|1
)paren
suffix:semicolon
id|sig_str
(braket
l_int|1
)braket
op_assign
(paren
(paren
(paren
id|sig
(braket
l_int|0
)braket
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
op_or
(paren
id|sig
(braket
l_int|1
)braket
op_rshift
l_int|5
)paren
)paren
op_plus
(paren
l_char|&squot;A&squot;
op_minus
l_int|1
)paren
suffix:semicolon
id|sig_str
(braket
l_int|2
)braket
op_assign
(paren
id|sig
(braket
l_int|1
)braket
op_amp
l_int|0x1f
)paren
op_plus
(paren
l_char|&squot;A&squot;
op_minus
l_int|1
)paren
suffix:semicolon
id|rev
op_assign
(paren
id|sig
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|sig
(braket
l_int|3
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|sig_str
op_plus
l_int|3
comma
l_string|&quot;%04X&quot;
comma
id|rev
)paren
suffix:semicolon
r_return
id|sig_str
suffix:semicolon
)brace
DECL|function|eisa_bus_match
r_static
r_int
id|eisa_bus_match
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|eisa_device
op_star
id|edev
op_assign
id|to_eisa_device
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|eisa_driver
op_star
id|edrv
op_assign
id|to_eisa_driver
(paren
id|drv
)paren
suffix:semicolon
r_const
r_struct
id|eisa_device_id
op_star
id|eids
op_assign
id|edrv-&gt;id_table
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eids
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|strlen
(paren
id|eids-&gt;sig
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
(paren
id|eids-&gt;sig
comma
id|edev-&gt;id.sig
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|eids
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|eisa_bus_type
r_struct
id|bus_type
id|eisa_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;eisa&quot;
comma
dot
id|match
op_assign
id|eisa_bus_match
comma
)brace
suffix:semicolon
DECL|function|eisa_driver_register
r_int
id|eisa_driver_register
(paren
r_struct
id|eisa_driver
op_star
id|edrv
)paren
(brace
r_int
id|r
suffix:semicolon
id|edrv-&gt;driver.bus
op_assign
op_amp
id|eisa_bus_type
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|driver_register
(paren
op_amp
id|edrv-&gt;driver
)paren
)paren
OL
l_int|0
)paren
r_return
id|r
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|eisa_driver_unregister
r_void
id|eisa_driver_unregister
(paren
r_struct
id|eisa_driver
op_star
id|edrv
)paren
(brace
id|driver_unregister
(paren
op_amp
id|edrv-&gt;driver
)paren
suffix:semicolon
)brace
DECL|function|eisa_show_sig
r_static
id|ssize_t
id|eisa_show_sig
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|eisa_device
op_star
id|edev
op_assign
id|to_eisa_device
(paren
id|dev
)paren
suffix:semicolon
r_return
id|sprintf
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|edev-&gt;id.sig
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|signature
comma
id|S_IRUGO
comma
id|eisa_show_sig
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|eisa_register_device
r_static
r_void
id|__init
id|eisa_register_device
(paren
r_struct
id|eisa_root_device
op_star
id|root
comma
r_char
op_star
id|sig
comma
r_int
id|slot
)paren
(brace
r_struct
id|eisa_device
op_star
id|edev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|edev
op_assign
id|kmalloc
(paren
r_sizeof
(paren
op_star
id|edev
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
suffix:semicolon
id|memset
(paren
id|edev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|edev
)paren
)paren
suffix:semicolon
id|memcpy
(paren
id|edev-&gt;id.sig
comma
id|sig
comma
l_int|7
)paren
suffix:semicolon
id|edev-&gt;slot
op_assign
id|slot
suffix:semicolon
id|edev-&gt;base_addr
op_assign
id|SLOT_ADDRESS
(paren
id|root
comma
id|slot
)paren
suffix:semicolon
id|eisa_name_device
(paren
id|edev
)paren
suffix:semicolon
id|edev-&gt;dev.parent
op_assign
id|root-&gt;dev
suffix:semicolon
id|edev-&gt;dev.bus
op_assign
op_amp
id|eisa_bus_type
suffix:semicolon
id|sprintf
(paren
id|edev-&gt;dev.bus_id
comma
l_string|&quot;%02X:%02X&quot;
comma
id|root-&gt;bus_nr
comma
id|slot
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t register resource for slot 0, since this will surely&n;&t; * fail... :-( */
r_if
c_cond
(paren
id|slot
)paren
(brace
id|edev-&gt;res.name
op_assign
id|edev-&gt;dev.name
suffix:semicolon
id|edev-&gt;res.start
op_assign
id|edev-&gt;base_addr
suffix:semicolon
id|edev-&gt;res.end
op_assign
id|edev-&gt;res.start
op_plus
l_int|0xfff
suffix:semicolon
id|edev-&gt;res.flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
(paren
id|root-&gt;res
comma
op_amp
id|edev-&gt;res
)paren
)paren
(brace
id|printk
(paren
id|KERN_WARNING
"&bslash;"
l_string|&quot;Cannot allocate resource for EISA slot %d&bslash;n&quot;
comma
id|slot
)paren
suffix:semicolon
id|kfree
(paren
id|edev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|device_register
(paren
op_amp
id|edev-&gt;dev
)paren
)paren
(brace
id|kfree
(paren
id|edev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|device_create_file
(paren
op_amp
id|edev-&gt;dev
comma
op_amp
id|dev_attr_signature
)paren
suffix:semicolon
)brace
DECL|function|eisa_probe
r_static
r_int
id|__init
id|eisa_probe
(paren
r_struct
id|eisa_root_device
op_star
id|root
)paren
(brace
r_int
id|i
comma
id|c
suffix:semicolon
r_char
op_star
id|str
suffix:semicolon
r_int
r_int
id|sig_addr
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;EISA: Probing bus %d at %s&bslash;n&quot;
comma
id|root-&gt;bus_nr
comma
id|root-&gt;dev-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|c
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|root-&gt;slots
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sig_addr
op_assign
id|SLOT_ADDRESS
(paren
id|root
comma
id|i
)paren
op_plus
id|EISA_VENDOR_ID_OFFSET
suffix:semicolon
r_if
c_cond
(paren
(paren
id|str
op_assign
id|decode_eisa_sig
(paren
id|sig_addr
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;EISA: Motherboard %s detected&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_else
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;EISA: slot %d : %s detected.&bslash;n&quot;
comma
id|i
comma
id|str
)paren
suffix:semicolon
id|c
op_increment
suffix:semicolon
)brace
id|eisa_register_device
(paren
id|root
comma
id|str
comma
id|i
)paren
suffix:semicolon
)brace
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;EISA: Detected %d card%s.&bslash;n&quot;
comma
id|c
comma
id|c
OL
l_int|2
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;s&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|LIST_HEAD
(paren
id|eisa_root_head
)paren
suffix:semicolon
DECL|variable|eisa_bus_count
r_static
r_int
id|eisa_bus_count
suffix:semicolon
DECL|function|eisa_root_register
r_int
id|eisa_root_register
(paren
r_struct
id|eisa_root_device
op_star
id|root
)paren
(brace
r_struct
id|list_head
op_star
id|node
suffix:semicolon
r_struct
id|eisa_root_device
op_star
id|tmp_root
suffix:semicolon
multiline_comment|/* Check if this bus base address has been already&n;&t; * registered. This prevents the virtual root device from&n;&t; * registering after the real one has, for example... */
id|list_for_each
(paren
id|node
comma
op_amp
id|eisa_root_head
)paren
(brace
id|tmp_root
op_assign
id|list_entry
(paren
id|node
comma
r_struct
id|eisa_root_device
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp_root-&gt;bus_base_addr
op_eq
id|root-&gt;bus_base_addr
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Space already taken, buddy... */
)brace
id|root-&gt;bus_nr
op_assign
id|eisa_bus_count
op_increment
suffix:semicolon
id|list_add_tail
(paren
op_amp
id|root-&gt;node
comma
op_amp
id|eisa_root_head
)paren
suffix:semicolon
r_return
id|eisa_probe
(paren
id|root
)paren
suffix:semicolon
)brace
DECL|function|eisa_init
r_static
r_int
id|__init
id|eisa_init
(paren
r_void
)paren
(brace
r_int
id|r
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|bus_register
(paren
op_amp
id|eisa_bus_type
)paren
)paren
)paren
r_return
id|r
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;EISA bus registered&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|eisa_init
id|postcore_initcall
(paren
id|eisa_init
)paren
suffix:semicolon
DECL|variable|eisa_bus_type
id|EXPORT_SYMBOL
(paren
id|eisa_bus_type
)paren
suffix:semicolon
DECL|variable|eisa_driver_register
id|EXPORT_SYMBOL
(paren
id|eisa_driver_register
)paren
suffix:semicolon
DECL|variable|eisa_driver_unregister
id|EXPORT_SYMBOL
(paren
id|eisa_driver_unregister
)paren
suffix:semicolon
eof
