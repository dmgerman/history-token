macro_line|#ifndef _LINUX_REBOOT_H
DECL|macro|_LINUX_REBOOT_H
mdefine_line|#define _LINUX_REBOOT_H
multiline_comment|/*&n; * Magic values required to use _reboot() system call.&n; */
DECL|macro|LINUX_REBOOT_MAGIC1
mdefine_line|#define&t;LINUX_REBOOT_MAGIC1&t;0xfee1dead
DECL|macro|LINUX_REBOOT_MAGIC2
mdefine_line|#define&t;LINUX_REBOOT_MAGIC2&t;672274793
DECL|macro|LINUX_REBOOT_MAGIC2A
mdefine_line|#define&t;LINUX_REBOOT_MAGIC2A&t;85072278
DECL|macro|LINUX_REBOOT_MAGIC2B
mdefine_line|#define&t;LINUX_REBOOT_MAGIC2B&t;369367448
multiline_comment|/*&n; * Commands accepted by the _reboot() system call.&n; *&n; * RESTART     Restart system using default command and mode.&n; * HALT        Stop OS and give system control to ROM monitor, if any.&n; * CAD_ON      Ctrl-Alt-Del sequence causes RESTART command.&n; * CAD_OFF     Ctrl-Alt-Del sequence sends SIGINT to init task.&n; * POWER_OFF   Stop OS and remove all power from system, if possible.&n; * RESTART2    Restart system using given command string.&n; * SW_SUSPEND  Suspend system using Software Suspend if compiled in&n; */
DECL|macro|LINUX_REBOOT_CMD_RESTART
mdefine_line|#define&t;LINUX_REBOOT_CMD_RESTART&t;0x01234567
DECL|macro|LINUX_REBOOT_CMD_HALT
mdefine_line|#define&t;LINUX_REBOOT_CMD_HALT&t;&t;0xCDEF0123
DECL|macro|LINUX_REBOOT_CMD_CAD_ON
mdefine_line|#define&t;LINUX_REBOOT_CMD_CAD_ON&t;&t;0x89ABCDEF
DECL|macro|LINUX_REBOOT_CMD_CAD_OFF
mdefine_line|#define&t;LINUX_REBOOT_CMD_CAD_OFF&t;0x00000000
DECL|macro|LINUX_REBOOT_CMD_POWER_OFF
mdefine_line|#define&t;LINUX_REBOOT_CMD_POWER_OFF&t;0x4321FEDC
DECL|macro|LINUX_REBOOT_CMD_RESTART2
mdefine_line|#define&t;LINUX_REBOOT_CMD_RESTART2&t;0xA1B2C3D4
DECL|macro|LINUX_REBOOT_CMD_SW_SUSPEND
mdefine_line|#define&t;LINUX_REBOOT_CMD_SW_SUSPEND&t;0xD000FCE2
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/notifier.h&gt;
r_extern
r_int
id|register_reboot_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
)paren
suffix:semicolon
r_extern
r_int
id|unregister_reboot_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Architecture-specific implementations of sys_reboot commands.&n; */
r_extern
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_void
id|machine_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Architecture-independent suspend facility&n; */
r_extern
r_void
id|software_suspend
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|software_suspend_enabled
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _LINUX_REBOOT_H */
eof
