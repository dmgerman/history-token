macro_line|#ifndef __BEN_VLAN_PROC_INC__
DECL|macro|__BEN_VLAN_PROC_INC__
mdefine_line|#define __BEN_VLAN_PROC_INC__
macro_line|#ifdef CONFIG_PROC_FS
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
macro_line|#else /* No CONFIG_PROC_FS */
DECL|macro|vlan_proc_init
mdefine_line|#define vlan_proc_init()&t;(0)
DECL|macro|vlan_proc_cleanup
mdefine_line|#define vlan_proc_cleanup()&t;do {} while(0)
DECL|macro|vlan_proc_add_dev
mdefine_line|#define vlan_proc_add_dev(dev)&t;({(void)(dev), 0;})
DECL|macro|vlan_proc_rem_dev
mdefine_line|#define vlan_proc_rem_dev(dev)&t;({(void)(dev), 0;})
macro_line|#endif
macro_line|#endif /* !(__BEN_VLAN_PROC_INC__) */
eof
