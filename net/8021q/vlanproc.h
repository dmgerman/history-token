macro_line|#ifndef __BEN_VLAN_PROC_INC__
DECL|macro|__BEN_VLAN_PROC_INC__
mdefine_line|#define __BEN_VLAN_PROC_INC__
r_int
id|vlan_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|vlan_proc_rem_dev
c_func
(paren
r_struct
id|net_device
op_star
id|vlandev
)paren
suffix:semicolon
r_int
id|vlan_proc_add_dev
(paren
r_struct
id|net_device
op_star
id|vlandev
)paren
suffix:semicolon
r_void
id|vlan_proc_cleanup
(paren
r_void
)paren
suffix:semicolon
DECL|macro|VLAN_PROC_BUFSZ
mdefine_line|#define&t;VLAN_PROC_BUFSZ&t;(4096)&t;/* buffer size for printing proc info */
macro_line|#endif /* !(__BEN_VLAN_PROC_INC__) */
eof
