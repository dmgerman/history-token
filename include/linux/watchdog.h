multiline_comment|/*&n; *&t;Generic watchdog defines. Derived from..&n; *&n; * Berkshire PC Watchdog Defines&n; * by Ken Hollis &lt;khollis@bitgate.com&gt;&n; *&n; */
macro_line|#ifndef _LINUX_WATCHDOG_H
DECL|macro|_LINUX_WATCHDOG_H
mdefine_line|#define _LINUX_WATCHDOG_H
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|WATCHDOG_IOCTL_BASE
mdefine_line|#define&t;WATCHDOG_IOCTL_BASE&t;&squot;W&squot;
DECL|struct|watchdog_info
r_struct
id|watchdog_info
(brace
DECL|member|options
id|__u32
id|options
suffix:semicolon
multiline_comment|/* Options the card/driver supports */
DECL|member|firmware_version
id|__u32
id|firmware_version
suffix:semicolon
multiline_comment|/* Firmware version of the card */
DECL|member|identity
id|__u8
id|identity
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Identity of the board */
)brace
suffix:semicolon
DECL|macro|WDIOC_GETSUPPORT
mdefine_line|#define&t;WDIOC_GETSUPPORT&t;_IOR(WATCHDOG_IOCTL_BASE, 0, struct watchdog_info)
DECL|macro|WDIOC_GETSTATUS
mdefine_line|#define&t;WDIOC_GETSTATUS&t;&t;_IOR(WATCHDOG_IOCTL_BASE, 1, int)
DECL|macro|WDIOC_GETBOOTSTATUS
mdefine_line|#define&t;WDIOC_GETBOOTSTATUS&t;_IOR(WATCHDOG_IOCTL_BASE, 2, int)
DECL|macro|WDIOC_GETTEMP
mdefine_line|#define&t;WDIOC_GETTEMP&t;&t;_IOR(WATCHDOG_IOCTL_BASE, 3, int)
DECL|macro|WDIOC_SETOPTIONS
mdefine_line|#define&t;WDIOC_SETOPTIONS&t;_IOR(WATCHDOG_IOCTL_BASE, 4, int)
DECL|macro|WDIOC_KEEPALIVE
mdefine_line|#define&t;WDIOC_KEEPALIVE&t;&t;_IOR(WATCHDOG_IOCTL_BASE, 5, int)
DECL|macro|WDIOC_SETTIMEOUT
mdefine_line|#define&t;WDIOC_SETTIMEOUT        _IOWR(WATCHDOG_IOCTL_BASE, 6, int)
DECL|macro|WDIOC_GETTIMEOUT
mdefine_line|#define&t;WDIOC_GETTIMEOUT        _IOR(WATCHDOG_IOCTL_BASE, 7, int)
DECL|macro|WDIOF_UNKNOWN
mdefine_line|#define&t;WDIOF_UNKNOWN&t;&t;-1&t;/* Unknown flag error */
DECL|macro|WDIOS_UNKNOWN
mdefine_line|#define&t;WDIOS_UNKNOWN&t;&t;-1&t;/* Unknown status error */
DECL|macro|WDIOF_OVERHEAT
mdefine_line|#define&t;WDIOF_OVERHEAT&t;&t;0x0001&t;/* Reset due to CPU overheat */
DECL|macro|WDIOF_FANFAULT
mdefine_line|#define&t;WDIOF_FANFAULT&t;&t;0x0002&t;/* Fan failed */
DECL|macro|WDIOF_EXTERN1
mdefine_line|#define&t;WDIOF_EXTERN1&t;&t;0x0004&t;/* External relay 1 */
DECL|macro|WDIOF_EXTERN2
mdefine_line|#define&t;WDIOF_EXTERN2&t;&t;0x0008&t;/* External relay 2 */
DECL|macro|WDIOF_POWERUNDER
mdefine_line|#define&t;WDIOF_POWERUNDER&t;0x0010&t;/* Power bad/power fault */
DECL|macro|WDIOF_CARDRESET
mdefine_line|#define&t;WDIOF_CARDRESET&t;&t;0x0020&t;/* Card previously reset the CPU */
DECL|macro|WDIOF_POWEROVER
mdefine_line|#define WDIOF_POWEROVER&t;&t;0x0040&t;/* Power over voltage */
DECL|macro|WDIOF_SETTIMEOUT
mdefine_line|#define WDIOF_SETTIMEOUT&t;0x0080  /* Set timeout (in seconds) */
DECL|macro|WDIOF_KEEPALIVEPING
mdefine_line|#define&t;WDIOF_KEEPALIVEPING&t;0x8000&t;/* Keep alive ping reply */
DECL|macro|WDIOS_DISABLECARD
mdefine_line|#define&t;WDIOS_DISABLECARD&t;0x0001&t;/* Turn off the watchdog timer */
DECL|macro|WDIOS_ENABLECARD
mdefine_line|#define&t;WDIOS_ENABLECARD&t;0x0002&t;/* Turn on the watchdog timer */
DECL|macro|WDIOS_TEMPPANIC
mdefine_line|#define&t;WDIOS_TEMPPANIC&t;&t;0x0004&t;/* Kernel panic on temperature trip */
macro_line|#endif  /* ifndef _LINUX_WATCHDOG_H */
eof
