macro_line|#ifndef _IEEE1394_CONFIG_ROMS_H
DECL|macro|_IEEE1394_CONFIG_ROMS_H
mdefine_line|#define _IEEE1394_CONFIG_ROMS_H
macro_line|#include &quot;ieee1394_types.h&quot;
macro_line|#include &quot;hosts.h&quot;
multiline_comment|/* The default host entry. This must succeed. */
r_int
id|hpsb_default_host_entry
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
suffix:semicolon
multiline_comment|/* Initialize all config roms */
r_int
id|hpsb_init_config_roms
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Cleanup all config roms */
r_void
id|hpsb_cleanup_config_roms
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Add extra config roms to specified host */
r_int
id|hpsb_add_extra_config_roms
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
suffix:semicolon
multiline_comment|/* Remove extra config roms from specified host */
r_void
id|hpsb_remove_extra_config_roms
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
suffix:semicolon
multiline_comment|/* List of flags to check if a host contains a certain extra config rom&n; * entry. Available in the host-&gt;config_roms member. */
DECL|macro|HPSB_CONFIG_ROM_ENTRY_IP1394
mdefine_line|#define HPSB_CONFIG_ROM_ENTRY_IP1394&t;&t;0x00000001
macro_line|#endif /* _IEEE1394_CONFIG_ROMS_H */
eof
