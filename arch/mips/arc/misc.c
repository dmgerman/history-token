multiline_comment|/*&n; * misc.c: Miscellaneous ARCS PROM routines.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/bcache.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_extern
r_void
op_star
id|sgiwd93_host
suffix:semicolon
r_extern
r_void
id|reset_wd33c93
c_func
(paren
r_void
op_star
id|instance
)paren
suffix:semicolon
DECL|function|prom_halt
r_void
id|prom_halt
c_func
(paren
r_void
)paren
(brace
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SCSI_SGIWD93
id|reset_wd33c93
c_func
(paren
id|sgiwd93_host
)paren
suffix:semicolon
macro_line|#endif
id|romvec
op_member_access_from_pointer
id|halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|prom_powerdown
r_void
id|prom_powerdown
c_func
(paren
r_void
)paren
(brace
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SCSI_SGIWD93
id|reset_wd33c93
c_func
(paren
id|sgiwd93_host
)paren
suffix:semicolon
macro_line|#endif
id|romvec
op_member_access_from_pointer
id|pdown
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX is this a soft reset basically? XXX */
DECL|function|prom_restart
r_void
id|prom_restart
c_func
(paren
r_void
)paren
(brace
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SCSI_SGIWD93
id|reset_wd33c93
c_func
(paren
id|sgiwd93_host
)paren
suffix:semicolon
macro_line|#endif
id|romvec
op_member_access_from_pointer
id|restart
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|prom_reboot
r_void
id|prom_reboot
c_func
(paren
r_void
)paren
(brace
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SCSI_SGIWD93
id|reset_wd33c93
c_func
(paren
id|sgiwd93_host
)paren
suffix:semicolon
macro_line|#endif
id|romvec
op_member_access_from_pointer
id|reboot
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ArcEnterInteractiveMode
r_void
id|ArcEnterInteractiveMode
c_func
(paren
r_void
)paren
(brace
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SCSI_SGIWD93
id|reset_wd33c93
c_func
(paren
id|sgiwd93_host
)paren
suffix:semicolon
macro_line|#endif
id|romvec
op_member_access_from_pointer
id|imode
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|prom_cfgsave
r_int
id|prom_cfgsave
c_func
(paren
r_void
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|cfg_save
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|prom_getsysid
r_struct
id|linux_sysid
op_star
id|prom_getsysid
c_func
(paren
r_void
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|get_sysid
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|prom_cacheflush
r_void
id|__init
id|prom_cacheflush
c_func
(paren
r_void
)paren
(brace
id|romvec
op_member_access_from_pointer
id|cache_flush
c_func
(paren
)paren
suffix:semicolon
)brace
eof
