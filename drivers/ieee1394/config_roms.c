multiline_comment|/*&n; * IEEE 1394 for Linux&n; *&n; * ConfigROM  entries&n; *&n; * Copyright (C) 2004 Ben Collins&n; *&n; * This code is licensed under the GPL.  See the file COPYING in the root&n; * directory of the kernel sources for details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &quot;csr1212.h&quot;
macro_line|#include &quot;ieee1394.h&quot;
macro_line|#include &quot;ieee1394_types.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;ieee1394_core.h&quot;
macro_line|#include &quot;highlevel.h&quot;
macro_line|#include &quot;csr.h&quot;
macro_line|#include &quot;config_roms.h&quot;
DECL|struct|hpsb_config_rom_entry
r_struct
id|hpsb_config_rom_entry
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Base initialization, called at module load */
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Add entry to specified host */
DECL|member|add
r_int
(paren
op_star
id|add
)paren
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
suffix:semicolon
multiline_comment|/* Remove entry from specified host */
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
suffix:semicolon
multiline_comment|/* Cleanup called at module exit */
DECL|member|cleanup
r_void
(paren
op_star
id|cleanup
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* The flag added to host-&gt;config_roms */
DECL|member|flag
r_int
r_int
id|flag
suffix:semicolon
)brace
suffix:semicolon
DECL|function|hpsb_default_host_entry
r_int
id|hpsb_default_host_entry
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|csr1212_keyval
op_star
id|root
suffix:semicolon
r_struct
id|csr1212_keyval
op_star
id|vend_id
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|csr1212_keyval
op_star
id|text
op_assign
l_int|NULL
suffix:semicolon
r_char
id|csr_name
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|sprintf
c_func
(paren
id|csr_name
comma
l_string|&quot;Linux - %s&quot;
comma
id|host-&gt;driver-&gt;name
)paren
suffix:semicolon
id|root
op_assign
id|host-&gt;csr.rom-&gt;root_kv
suffix:semicolon
id|vend_id
op_assign
id|csr1212_new_immediate
c_func
(paren
id|CSR1212_KV_ID_VENDOR
comma
id|host-&gt;csr.guid_hi
op_rshift
l_int|8
)paren
suffix:semicolon
id|text
op_assign
id|csr1212_new_string_descriptor_leaf
c_func
(paren
id|csr_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vend_id
op_logical_or
op_logical_neg
id|text
)paren
(brace
r_if
c_cond
(paren
id|vend_id
)paren
id|csr1212_release_keyval
c_func
(paren
id|vend_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|text
)paren
id|csr1212_release_keyval
c_func
(paren
id|text
)paren
suffix:semicolon
id|csr1212_destroy_csr
c_func
(paren
id|host-&gt;csr.rom
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ret
op_assign
id|csr1212_associate_keyval
c_func
(paren
id|vend_id
comma
id|text
)paren
suffix:semicolon
id|csr1212_release_keyval
c_func
(paren
id|text
)paren
suffix:semicolon
id|ret
op_or_assign
id|csr1212_attach_keyval_to_directory
c_func
(paren
id|root
comma
id|vend_id
)paren
suffix:semicolon
id|csr1212_release_keyval
c_func
(paren
id|vend_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|CSR1212_SUCCESS
)paren
(brace
id|csr1212_destroy_csr
c_func
(paren
id|host-&gt;csr.rom
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|host-&gt;update_config_rom
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IEEE1394_CONFIG_ROM_IP1394
macro_line|#include &quot;eth1394.h&quot;
DECL|variable|ip1394_ud
r_static
r_struct
id|csr1212_keyval
op_star
id|ip1394_ud
suffix:semicolon
DECL|function|config_rom_ip1394_init
r_static
r_int
id|config_rom_ip1394_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|csr1212_keyval
op_star
id|spec_id
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|csr1212_keyval
op_star
id|spec_desc
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|csr1212_keyval
op_star
id|ver
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|csr1212_keyval
op_star
id|ver_desc
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|ip1394_ud
op_assign
id|csr1212_new_directory
c_func
(paren
id|CSR1212_KV_ID_UNIT
)paren
suffix:semicolon
id|spec_id
op_assign
id|csr1212_new_immediate
c_func
(paren
id|CSR1212_KV_ID_SPECIFIER_ID
comma
id|ETHER1394_GASP_SPECIFIER_ID
)paren
suffix:semicolon
id|spec_desc
op_assign
id|csr1212_new_string_descriptor_leaf
c_func
(paren
l_string|&quot;IANA&quot;
)paren
suffix:semicolon
id|ver
op_assign
id|csr1212_new_immediate
c_func
(paren
id|CSR1212_KV_ID_VERSION
comma
id|ETHER1394_GASP_VERSION
)paren
suffix:semicolon
id|ver_desc
op_assign
id|csr1212_new_string_descriptor_leaf
c_func
(paren
l_string|&quot;IPv4&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ip1394_ud
op_logical_or
op_logical_neg
id|spec_id
op_logical_or
op_logical_neg
id|spec_desc
op_logical_or
op_logical_neg
id|ver
op_logical_or
op_logical_neg
id|ver_desc
)paren
r_goto
id|ip1394_fail
suffix:semicolon
r_if
c_cond
(paren
id|csr1212_associate_keyval
c_func
(paren
id|spec_id
comma
id|spec_desc
)paren
op_eq
id|CSR1212_SUCCESS
op_logical_and
id|csr1212_associate_keyval
c_func
(paren
id|ver
comma
id|ver_desc
)paren
op_eq
id|CSR1212_SUCCESS
op_logical_and
id|csr1212_attach_keyval_to_directory
c_func
(paren
id|ip1394_ud
comma
id|spec_id
)paren
op_eq
id|CSR1212_SUCCESS
op_logical_and
id|csr1212_attach_keyval_to_directory
c_func
(paren
id|ip1394_ud
comma
id|ver
)paren
op_eq
id|CSR1212_SUCCESS
)paren
id|ret
op_assign
l_int|0
suffix:semicolon
id|ip1394_fail
suffix:colon
r_if
c_cond
(paren
id|ret
op_logical_and
id|ip1394_ud
)paren
(brace
id|csr1212_release_keyval
c_func
(paren
id|ip1394_ud
)paren
suffix:semicolon
id|ip1394_ud
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|spec_id
)paren
id|csr1212_release_keyval
c_func
(paren
id|spec_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|spec_desc
)paren
id|csr1212_release_keyval
c_func
(paren
id|spec_desc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ver
)paren
id|csr1212_release_keyval
c_func
(paren
id|ver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ver_desc
)paren
id|csr1212_release_keyval
c_func
(paren
id|ver_desc
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|config_rom_ip1394_cleanup
r_static
r_void
id|config_rom_ip1394_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ip1394_ud
)paren
(brace
id|csr1212_release_keyval
c_func
(paren
id|ip1394_ud
)paren
suffix:semicolon
id|ip1394_ud
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|config_rom_ip1394_add
r_static
r_int
id|config_rom_ip1394_add
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ip1394_ud
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|csr1212_attach_keyval_to_directory
c_func
(paren
id|host-&gt;csr.rom-&gt;root_kv
comma
id|ip1394_ud
)paren
op_ne
id|CSR1212_SUCCESS
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|config_rom_ip1394_remove
r_static
r_void
id|config_rom_ip1394_remove
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
id|csr1212_detach_keyval_from_directory
c_func
(paren
id|host-&gt;csr.rom-&gt;root_kv
comma
id|ip1394_ud
)paren
suffix:semicolon
)brace
DECL|variable|ip1394_entry
r_static
r_struct
id|hpsb_config_rom_entry
id|ip1394_entry
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ip1394&quot;
comma
dot
id|init
op_assign
id|config_rom_ip1394_init
comma
dot
id|add
op_assign
id|config_rom_ip1394_add
comma
dot
id|remove
op_assign
id|config_rom_ip1394_remove
comma
dot
id|cleanup
op_assign
id|config_rom_ip1394_cleanup
comma
dot
id|flag
op_assign
id|HPSB_CONFIG_ROM_ENTRY_IP1394
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_IEEE1394_CONFIG_ROM_IP1394 */
DECL|variable|config_rom_entries
r_static
r_struct
id|hpsb_config_rom_entry
op_star
r_const
id|config_rom_entries
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_IEEE1394_CONFIG_ROM_IP1394
op_amp
id|ip1394_entry
comma
macro_line|#endif
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|hpsb_init_config_roms
r_int
id|hpsb_init_config_roms
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|error
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|config_rom_entries
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|config_rom_entries
(braket
id|i
)braket
op_member_access_from_pointer
id|init
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|config_rom_entries
(braket
id|i
)braket
op_member_access_from_pointer
id|init
c_func
(paren
)paren
)paren
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;Failed to initialize config rom entry `%s&squot;&quot;
comma
id|config_rom_entries
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|error
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;Initialized config rom entry `%s&squot;&quot;
comma
id|config_rom_entries
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|hpsb_cleanup_config_roms
r_void
id|hpsb_cleanup_config_roms
c_func
(paren
r_void
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
id|config_rom_entries
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|config_rom_entries
(braket
id|i
)braket
op_member_access_from_pointer
id|cleanup
)paren
id|config_rom_entries
(braket
id|i
)braket
op_member_access_from_pointer
id|cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|hpsb_add_extra_config_roms
r_int
id|hpsb_add_extra_config_roms
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_int
id|i
comma
id|error
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|config_rom_entries
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|config_rom_entries
(braket
id|i
)braket
op_member_access_from_pointer
id|add
c_func
(paren
id|host
)paren
)paren
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;fw-host%d: Failed to attach config rom entry `%s&squot;&quot;
comma
id|host-&gt;id
comma
id|config_rom_entries
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|error
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|host-&gt;config_roms
op_or_assign
id|config_rom_entries
(braket
id|i
)braket
op_member_access_from_pointer
id|flag
suffix:semicolon
id|host-&gt;update_config_rom
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|hpsb_remove_extra_config_roms
r_void
id|hpsb_remove_extra_config_roms
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
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
id|config_rom_entries
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|host-&gt;config_roms
op_amp
id|config_rom_entries
(braket
id|i
)braket
op_member_access_from_pointer
id|flag
)paren
)paren
r_continue
suffix:semicolon
id|config_rom_entries
(braket
id|i
)braket
op_member_access_from_pointer
id|remove
c_func
(paren
id|host
)paren
suffix:semicolon
id|host-&gt;config_roms
op_and_assign
op_complement
id|config_rom_entries
(braket
id|i
)braket
op_member_access_from_pointer
id|flag
suffix:semicolon
id|host-&gt;update_config_rom
op_assign
l_int|1
suffix:semicolon
)brace
)brace
eof
