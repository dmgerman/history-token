multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Miscellaneous ARCS PROM routines.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/bcache.h&gt;
macro_line|#include &lt;asm/arc/types.h&gt;
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
id|VOID
DECL|function|ArcHalt
id|ArcHalt
c_func
(paren
id|VOID
)paren
(brace
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
id|local_irq_disable
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
id|ARC_CALL0
c_func
(paren
id|halt
)paren
suffix:semicolon
id|never
suffix:colon
r_goto
id|never
suffix:semicolon
)brace
id|VOID
DECL|function|ArcPowerDown
id|ArcPowerDown
c_func
(paren
id|VOID
)paren
(brace
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
id|local_irq_disable
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
id|ARC_CALL0
c_func
(paren
id|pdown
)paren
suffix:semicolon
id|never
suffix:colon
r_goto
id|never
suffix:semicolon
)brace
multiline_comment|/* XXX is this a soft reset basically? XXX */
id|VOID
DECL|function|ArcRestart
id|ArcRestart
c_func
(paren
id|VOID
)paren
(brace
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
id|local_irq_disable
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
id|ARC_CALL0
c_func
(paren
id|restart
)paren
suffix:semicolon
id|never
suffix:colon
r_goto
id|never
suffix:semicolon
)brace
id|VOID
DECL|function|ArcReboot
id|ArcReboot
c_func
(paren
id|VOID
)paren
(brace
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
id|local_irq_disable
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
id|ARC_CALL0
c_func
(paren
id|reboot
)paren
suffix:semicolon
id|never
suffix:colon
r_goto
id|never
suffix:semicolon
)brace
id|VOID
DECL|function|ArcEnterInteractiveMode
id|ArcEnterInteractiveMode
c_func
(paren
id|VOID
)paren
(brace
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
id|local_irq_disable
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
id|ARC_CALL0
c_func
(paren
id|imode
)paren
suffix:semicolon
id|never
suffix:colon
r_goto
id|never
suffix:semicolon
)brace
id|LONG
DECL|function|ArcSaveConfiguration
id|ArcSaveConfiguration
c_func
(paren
id|VOID
)paren
(brace
r_return
id|ARC_CALL0
c_func
(paren
id|cfg_save
)paren
suffix:semicolon
)brace
r_struct
id|linux_sysid
op_star
DECL|function|ArcGetSystemId
id|ArcGetSystemId
c_func
(paren
id|VOID
)paren
(brace
r_return
(paren
r_struct
id|linux_sysid
op_star
)paren
id|ARC_CALL0
c_func
(paren
id|get_sysid
)paren
suffix:semicolon
)brace
id|VOID
id|__init
DECL|function|ArcFlushAllCaches
id|ArcFlushAllCaches
c_func
(paren
id|VOID
)paren
(brace
id|ARC_CALL0
c_func
(paren
id|cache_flush
)paren
suffix:semicolon
)brace
eof
