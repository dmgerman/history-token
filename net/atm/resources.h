multiline_comment|/* net/atm/resources.h - ATM-related resources */
multiline_comment|/* Written 1995-1998 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef NET_ATM_RESOURCES_H
DECL|macro|NET_ATM_RESOURCES_H
mdefine_line|#define NET_ATM_RESOURCES_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
r_extern
r_struct
id|atm_dev
op_star
id|atm_devs
suffix:semicolon
r_extern
r_struct
id|atm_vcc
op_star
id|nodev_vccs
suffix:semicolon
multiline_comment|/* VCCs not linked to any device */
r_struct
id|sock
op_star
id|alloc_atm_vcc_sk
c_func
(paren
r_int
id|family
)paren
suffix:semicolon
r_void
id|free_atm_vcc_sk
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#include &lt;linux/proc_fs.h&gt;
r_int
id|atm_proc_dev_register
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|atm_proc_dev_deregister
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
