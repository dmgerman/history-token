multiline_comment|/*&n; * pnpacpi -- PnP ACPI driver&n; *&n; * Copyright (c) 2004 Matthieu Castet &lt;castet.matthieu@free.fr&gt;&n; * Copyright (c) 2004 Li Shaohua &lt;shaohua.li@intel.com&gt;&n; * &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;acpi/acpi_bus.h&gt;
macro_line|#include &quot;pnpacpi.h&quot;
DECL|variable|num
r_static
r_int
id|num
op_assign
l_int|0
suffix:semicolon
DECL|variable|excluded_id_list
r_static
r_char
id|__initdata
id|excluded_id_list
(braket
)braket
op_assign
l_string|&quot;PNP0C0A,&quot;
multiline_comment|/* Battery */
l_string|&quot;PNP0C0C,PNP0C0E,PNP0C0D,&quot;
multiline_comment|/* Button */
l_string|&quot;PNP0C09,&quot;
multiline_comment|/* EC */
l_string|&quot;PNP0C0B,&quot;
multiline_comment|/* Fan */
l_string|&quot;PNP0A03,&quot;
multiline_comment|/* PCI root */
l_string|&quot;PNP0C0F,&quot;
multiline_comment|/* Link device */
l_string|&quot;PNP0000,&quot;
multiline_comment|/* PIC */
l_string|&quot;PNP0100,&quot;
multiline_comment|/* Timer */
suffix:semicolon
DECL|function|is_exclusive_device
r_static
r_inline
r_int
id|is_exclusive_device
c_func
(paren
r_struct
id|acpi_device
op_star
id|dev
)paren
(brace
r_return
(paren
op_logical_neg
id|acpi_match_ids
c_func
(paren
id|dev
comma
id|excluded_id_list
)paren
)paren
suffix:semicolon
)brace
DECL|function|pnpacpi_kmalloc
r_void
op_star
id|pnpacpi_kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|f
)paren
(brace
r_void
op_star
id|p
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Compatible Device IDs&n; */
DECL|macro|TEST_HEX
mdefine_line|#define TEST_HEX(c) &bslash;&n;&t;if (!((&squot;0&squot; &lt;= (c) &amp;&amp; (c) &lt;= &squot;9&squot;) || (&squot;A&squot; &lt;= (c) &amp;&amp; (c) &lt;= &squot;F&squot;))) &bslash;&n;&t;&t;return 0
DECL|macro|TEST_ALPHA
mdefine_line|#define TEST_ALPHA(c) &bslash;&n;&t;if (!(&squot;@&squot; &lt;= (c) || (c) &lt;= &squot;Z&squot;)) &bslash;&n;&t;&t;return 0
DECL|function|ispnpidacpi
r_static
r_int
id|__init
id|ispnpidacpi
c_func
(paren
r_char
op_star
id|id
)paren
(brace
id|TEST_ALPHA
c_func
(paren
id|id
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|TEST_ALPHA
c_func
(paren
id|id
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|TEST_ALPHA
c_func
(paren
id|id
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|TEST_HEX
c_func
(paren
id|id
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|TEST_HEX
c_func
(paren
id|id
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|TEST_HEX
c_func
(paren
id|id
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|TEST_HEX
c_func
(paren
id|id
(braket
l_int|6
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
(braket
l_int|7
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pnpidacpi_to_pnpid
r_static
r_void
id|__init
id|pnpidacpi_to_pnpid
c_func
(paren
r_char
op_star
id|id
comma
r_char
op_star
id|str
)paren
(brace
id|str
(braket
l_int|0
)braket
op_assign
id|id
(braket
l_int|0
)braket
suffix:semicolon
id|str
(braket
l_int|1
)braket
op_assign
id|id
(braket
l_int|1
)braket
suffix:semicolon
id|str
(braket
l_int|2
)braket
op_assign
id|id
(braket
l_int|2
)braket
suffix:semicolon
id|str
(braket
l_int|3
)braket
op_assign
id|tolower
c_func
(paren
id|id
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|str
(braket
l_int|4
)braket
op_assign
id|tolower
c_func
(paren
id|id
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|str
(braket
l_int|5
)braket
op_assign
id|tolower
c_func
(paren
id|id
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|str
(braket
l_int|6
)braket
op_assign
id|tolower
c_func
(paren
id|id
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|str
(braket
l_int|7
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|function|pnpacpi_get_resources
r_static
r_int
id|pnpacpi_get_resources
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_resource_table
op_star
id|res
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|status
op_assign
id|pnpacpi_parse_allocated_resource
c_func
(paren
(paren
id|acpi_handle
)paren
id|dev-&gt;data
comma
op_amp
id|dev-&gt;res
)paren
suffix:semicolon
r_return
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
ques
c_cond
op_minus
id|ENODEV
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|pnpacpi_set_resources
r_static
r_int
id|pnpacpi_set_resources
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_resource_table
op_star
id|res
)paren
(brace
id|acpi_handle
id|handle
op_assign
id|dev-&gt;data
suffix:semicolon
r_struct
id|acpi_buffer
id|buffer
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ret
op_assign
id|pnpacpi_build_resource_template
c_func
(paren
id|handle
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|ret
op_assign
id|pnpacpi_encode_resources
c_func
(paren
id|res
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|kfree
c_func
(paren
id|buffer.pointer
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|status
op_assign
id|acpi_set_current_resources
c_func
(paren
id|handle
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|kfree
c_func
(paren
id|buffer.pointer
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pnpacpi_disable_resources
r_static
r_int
id|pnpacpi_disable_resources
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
multiline_comment|/* acpi_unregister_gsi(pnp_irq(dev, 0)); */
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
(paren
id|acpi_handle
)paren
id|dev-&gt;data
comma
l_string|&quot;_DIS&quot;
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
ques
c_cond
op_minus
id|ENODEV
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|variable|pnpacpi_protocol
r_struct
id|pnp_protocol
id|pnpacpi_protocol
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Plug and Play ACPI&quot;
comma
dot
id|get
op_assign
id|pnpacpi_get_resources
comma
dot
id|set
op_assign
id|pnpacpi_set_resources
comma
dot
id|disable
op_assign
id|pnpacpi_disable_resources
comma
)brace
suffix:semicolon
DECL|function|pnpacpi_add_device
r_static
r_int
id|__init
id|pnpacpi_add_device
c_func
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
id|acpi_handle
id|temp
op_assign
l_int|NULL
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_struct
id|pnp_id
op_star
id|dev_id
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ispnpidacpi
c_func
(paren
id|acpi_device_hid
c_func
(paren
id|device
)paren
)paren
op_logical_or
id|is_exclusive_device
c_func
(paren
id|device
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|pnp_dbg
c_func
(paren
l_string|&quot;ACPI device : hid %s&quot;
comma
id|acpi_device_hid
c_func
(paren
id|device
)paren
)paren
suffix:semicolon
id|dev
op_assign
id|pnpacpi_kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pnp_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|pnp_err
c_func
(paren
l_string|&quot;Out of memory&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dev-&gt;data
op_assign
id|device-&gt;handle
suffix:semicolon
multiline_comment|/* .enabled means if the device can decode the resources */
id|dev-&gt;active
op_assign
id|device-&gt;status.enabled
suffix:semicolon
id|status
op_assign
id|acpi_get_handle
c_func
(paren
id|device-&gt;handle
comma
l_string|&quot;_SRS&quot;
comma
op_amp
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
id|dev-&gt;capabilities
op_or_assign
id|PNP_CONFIGURABLE
suffix:semicolon
id|dev-&gt;capabilities
op_or_assign
id|PNP_READ
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;flags.dynamic_status
)paren
id|dev-&gt;capabilities
op_or_assign
id|PNP_WRITE
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;flags.removable
)paren
id|dev-&gt;capabilities
op_or_assign
id|PNP_REMOVABLE
suffix:semicolon
id|status
op_assign
id|acpi_get_handle
c_func
(paren
id|device-&gt;handle
comma
l_string|&quot;_DIS&quot;
comma
op_amp
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
id|dev-&gt;capabilities
op_or_assign
id|PNP_DISABLE
suffix:semicolon
id|dev-&gt;protocol
op_assign
op_amp
id|pnpacpi_protocol
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|acpi_device_name
c_func
(paren
id|device
)paren
)paren
)paren
id|strncpy
c_func
(paren
id|dev-&gt;name
comma
id|acpi_device_name
c_func
(paren
id|device
)paren
comma
r_sizeof
(paren
id|dev-&gt;name
)paren
)paren
suffix:semicolon
r_else
id|strncpy
c_func
(paren
id|dev-&gt;name
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
r_sizeof
(paren
id|dev-&gt;name
)paren
)paren
suffix:semicolon
id|dev-&gt;number
op_assign
id|num
suffix:semicolon
multiline_comment|/* set the initial values for the PnP device */
id|dev_id
op_assign
id|pnpacpi_kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pnp_id
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_id
)paren
r_goto
id|err
suffix:semicolon
id|pnpidacpi_to_pnpid
c_func
(paren
id|acpi_device_hid
c_func
(paren
id|device
)paren
comma
id|dev_id-&gt;id
)paren
suffix:semicolon
id|pnp_add_id
c_func
(paren
id|dev_id
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;active
)paren
(brace
multiline_comment|/* parse allocated resource */
id|status
op_assign
id|pnpacpi_parse_allocated_resource
c_func
(paren
id|device-&gt;handle
comma
op_amp
id|dev-&gt;res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
op_logical_and
(paren
id|status
op_ne
id|AE_NOT_FOUND
)paren
)paren
(brace
id|pnp_err
c_func
(paren
l_string|&quot;PnPACPI: METHOD_NAME__CRS failure for %s&quot;
comma
id|dev_id-&gt;id
)paren
suffix:semicolon
r_goto
id|err1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dev-&gt;capabilities
op_amp
id|PNP_CONFIGURABLE
)paren
(brace
id|status
op_assign
id|pnpacpi_parse_resource_option_data
c_func
(paren
id|device-&gt;handle
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
op_logical_and
(paren
id|status
op_ne
id|AE_NOT_FOUND
)paren
)paren
(brace
id|pnp_err
c_func
(paren
l_string|&quot;PnPACPI: METHOD_NAME__PRS failure for %s&quot;
comma
id|dev_id-&gt;id
)paren
suffix:semicolon
r_goto
id|err1
suffix:semicolon
)brace
)brace
multiline_comment|/* parse compatible ids */
r_if
c_cond
(paren
id|device-&gt;flags.compatible_ids
)paren
(brace
r_struct
id|acpi_compatible_id_list
op_star
id|cid_list
op_assign
id|device-&gt;pnp.cid_list
suffix:semicolon
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
id|cid_list-&gt;count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ispnpidacpi
c_func
(paren
id|cid_list-&gt;id
(braket
id|i
)braket
dot
id|value
)paren
)paren
r_continue
suffix:semicolon
id|dev_id
op_assign
id|pnpacpi_kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pnp_id
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_id
)paren
r_continue
suffix:semicolon
id|pnpidacpi_to_pnpid
c_func
(paren
id|cid_list-&gt;id
(braket
id|i
)braket
dot
id|value
comma
id|dev_id-&gt;id
)paren
suffix:semicolon
id|pnp_add_id
c_func
(paren
id|dev_id
comma
id|dev
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* clear out the damaged flags */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;active
)paren
id|pnp_init_resource_table
c_func
(paren
op_amp
id|dev-&gt;res
)paren
suffix:semicolon
id|pnp_add_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|num
op_increment
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
id|err1
suffix:colon
id|kfree
c_func
(paren
id|dev_id
)paren
suffix:semicolon
id|err
suffix:colon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|pnpacpi_add_device_handler
r_static
id|acpi_status
id|__init
id|pnpacpi_add_device_handler
c_func
(paren
id|acpi_handle
id|handle
comma
id|u32
id|lvl
comma
r_void
op_star
id|context
comma
r_void
op_star
op_star
id|rv
)paren
(brace
r_struct
id|acpi_device
op_star
id|device
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_bus_get_device
c_func
(paren
id|handle
comma
op_amp
id|device
)paren
)paren
id|pnpacpi_add_device
c_func
(paren
id|device
)paren
suffix:semicolon
r_else
r_return
id|AE_CTRL_DEPTH
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
DECL|variable|__initdata
r_int
id|pnpacpi_disabled
id|__initdata
suffix:semicolon
DECL|function|pnpacpi_init
r_int
id|__init
id|pnpacpi_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|acpi_disabled
op_logical_or
id|pnpacpi_disabled
)paren
(brace
id|pnp_info
c_func
(paren
l_string|&quot;PnP ACPI: disabled&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pnp_info
c_func
(paren
l_string|&quot;PnP ACPI init&quot;
)paren
suffix:semicolon
id|pnp_register_protocol
c_func
(paren
op_amp
id|pnpacpi_protocol
)paren
suffix:semicolon
id|acpi_get_devices
c_func
(paren
l_int|NULL
comma
id|pnpacpi_add_device_handler
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|pnp_info
c_func
(paren
l_string|&quot;PnP ACPI: found %d devices&quot;
comma
id|num
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pnpacpi_init
id|subsys_initcall
c_func
(paren
id|pnpacpi_init
)paren
suffix:semicolon
DECL|function|pnpacpi_setup
r_static
r_int
id|__init
id|pnpacpi_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
id|str
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;off&quot;
comma
l_int|3
)paren
)paren
id|pnpacpi_disabled
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;pnpacpi=&quot;
comma
id|pnpacpi_setup
)paren
suffix:semicolon
DECL|variable|pnpacpi_protocol
id|EXPORT_SYMBOL
c_func
(paren
id|pnpacpi_protocol
)paren
suffix:semicolon
eof
