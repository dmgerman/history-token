multiline_comment|/*&n; *&t;Routines to manage notifier chains for passing status changes to any&n; *&t;interested routines. We need this instead of hard coded call lists so&n; *&t;that modules can poke their nose into the innards. The network devices&n; *&t;needed them so here they are for the rest of you.&n; *&n; *&t;&t;&t;&t;Alan Cox &lt;Alan.Cox@linux.org&gt;&n; */
macro_line|#ifndef _LINUX_NOTIFIER_H
DECL|macro|_LINUX_NOTIFIER_H
mdefine_line|#define _LINUX_NOTIFIER_H
macro_line|#include &lt;linux/errno.h&gt;
DECL|struct|notifier_block
r_struct
id|notifier_block
(brace
DECL|member|notifier_call
r_int
(paren
op_star
id|notifier_call
)paren
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|next
r_struct
id|notifier_block
op_star
id|next
suffix:semicolon
DECL|member|priority
r_int
id|priority
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|notifier_chain_register
c_func
(paren
r_struct
id|notifier_block
op_star
op_star
id|list
comma
r_struct
id|notifier_block
op_star
id|n
)paren
suffix:semicolon
r_extern
r_int
id|notifier_chain_unregister
c_func
(paren
r_struct
id|notifier_block
op_star
op_star
id|nl
comma
r_struct
id|notifier_block
op_star
id|n
)paren
suffix:semicolon
r_extern
r_int
id|notifier_call_chain
c_func
(paren
r_struct
id|notifier_block
op_star
op_star
id|n
comma
r_int
r_int
id|val
comma
r_void
op_star
id|v
)paren
suffix:semicolon
DECL|macro|NOTIFY_DONE
mdefine_line|#define NOTIFY_DONE&t;&t;0x0000&t;&t;/* Don&squot;t care */
DECL|macro|NOTIFY_OK
mdefine_line|#define NOTIFY_OK&t;&t;0x0001&t;&t;/* Suits me */
DECL|macro|NOTIFY_STOP_MASK
mdefine_line|#define NOTIFY_STOP_MASK&t;0x8000&t;&t;/* Don&squot;t call further */
DECL|macro|NOTIFY_BAD
mdefine_line|#define NOTIFY_BAD&t;&t;(NOTIFY_STOP_MASK|0x0002)&t;/* Bad/Veto action&t;*/
multiline_comment|/*&n; *&t;Declared notifiers so far. I can imagine quite a few more chains&n; *&t;over time (eg laptop power reset chains, reboot chain (to clean &n; *&t;device units up), device [un]mount chain, module load/unload chain,&n; *&t;low memory chain, screenblank chain (for plug in modular screenblankers) &n; *&t;VC switch chains (for loadable kernel svgalib VC switch helpers) etc...&n; */
multiline_comment|/* netdevice notifier chain */
DECL|macro|NETDEV_UP
mdefine_line|#define NETDEV_UP&t;0x0001&t;/* For now you can&squot;t veto a device up/down */
DECL|macro|NETDEV_DOWN
mdefine_line|#define NETDEV_DOWN&t;0x0002
DECL|macro|NETDEV_REBOOT
mdefine_line|#define NETDEV_REBOOT&t;0x0003&t;/* Tell a protocol stack a network interface&n;&t;&t;&t;&t;   detected a hardware crash and restarted&n;&t;&t;&t;&t;   - we can use this eg to kick tcp sessions&n;&t;&t;&t;&t;   once done */
DECL|macro|NETDEV_CHANGE
mdefine_line|#define NETDEV_CHANGE&t;0x0004&t;/* Notify device state change */
DECL|macro|NETDEV_REGISTER
mdefine_line|#define NETDEV_REGISTER 0x0005
DECL|macro|NETDEV_UNREGISTER
mdefine_line|#define NETDEV_UNREGISTER&t;0x0006
DECL|macro|NETDEV_CHANGEMTU
mdefine_line|#define NETDEV_CHANGEMTU&t;0x0007
DECL|macro|NETDEV_CHANGEADDR
mdefine_line|#define NETDEV_CHANGEADDR&t;0x0008
DECL|macro|NETDEV_GOING_DOWN
mdefine_line|#define NETDEV_GOING_DOWN&t;0x0009
DECL|macro|NETDEV_CHANGENAME
mdefine_line|#define NETDEV_CHANGENAME&t;0x000A
DECL|macro|SYS_DOWN
mdefine_line|#define SYS_DOWN&t;0x0001&t;/* Notify of system down */
DECL|macro|SYS_RESTART
mdefine_line|#define SYS_RESTART&t;SYS_DOWN
DECL|macro|SYS_HALT
mdefine_line|#define SYS_HALT&t;0x0002&t;/* Notify of system halt */
DECL|macro|SYS_POWER_OFF
mdefine_line|#define SYS_POWER_OFF&t;0x0003&t;/* Notify of system power off */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_NOTIFIER_H */
eof
