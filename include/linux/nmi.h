multiline_comment|/*&n; *  linux/include/linux/nmi.h&n; */
macro_line|#ifndef LINUX_NMI_H
DECL|macro|LINUX_NMI_H
mdefine_line|#define LINUX_NMI_H
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/**&n; * touch_nmi_watchdog - restart NMI watchdog timeout.&n; * &n; * If the architecture supports the NMI watchdog, touch_nmi_watchdog()&n; * may be used to reset the timeout - for code which intentionally&n; * disables interrupts for a long time. This call is stateless.&n; */
macro_line|#ifdef ARCH_HAS_NMI_WATCHDOG
r_extern
r_void
id|touch_nmi_watchdog
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|touch_nmi_watchdog
macro_line|# define touch_nmi_watchdog() do { } while(0)
macro_line|#endif
macro_line|#endif
eof
