multiline_comment|/*&n; * Bond several ethernet interfaces into a Cisco, running &squot;Etherchannel&squot;.&n; *&n; * &n; * Portions are (c) Copyright 1995 Simon &quot;Guru Aleph-Null&quot; Janes&n; * NCM: Network and Communications Management, Inc.&n; *&n; * BUT, I&squot;m the one who modified it for ethernet, so:&n; * (c) Copyright 1999, Thomas Davis, tadavis@lbl.gov&n; *&n; *&t;This software may be used and distributed according to the terms&n; *&t;of the GNU Public License, incorporated herein by reference.&n; * &n; */
macro_line|#ifndef _LINUX_IF_BONDING_H
DECL|macro|_LINUX_IF_BONDING_H
mdefine_line|#define _LINUX_IF_BONDING_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#endif /* __KERNEL__ */
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * We can remove these ioctl definitions in 2.5.  People should use the&n; * SIOC*** versions of them instead&n; */
DECL|macro|BOND_ENSLAVE_OLD
mdefine_line|#define BOND_ENSLAVE_OLD&t;&t;(SIOCDEVPRIVATE)
DECL|macro|BOND_RELEASE_OLD
mdefine_line|#define BOND_RELEASE_OLD&t;&t;(SIOCDEVPRIVATE + 1)
DECL|macro|BOND_SETHWADDR_OLD
mdefine_line|#define BOND_SETHWADDR_OLD&t;&t;(SIOCDEVPRIVATE + 2)
DECL|macro|BOND_SLAVE_INFO_QUERY_OLD
mdefine_line|#define BOND_SLAVE_INFO_QUERY_OLD&t;(SIOCDEVPRIVATE + 11)
DECL|macro|BOND_INFO_QUERY_OLD
mdefine_line|#define BOND_INFO_QUERY_OLD&t;&t;(SIOCDEVPRIVATE + 12)
DECL|macro|BOND_CHANGE_ACTIVE_OLD
mdefine_line|#define BOND_CHANGE_ACTIVE_OLD&t;&t;(SIOCDEVPRIVATE + 13)
DECL|macro|BOND_CHECK_MII_STATUS
mdefine_line|#define BOND_CHECK_MII_STATUS&t;(SIOCGMIIPHY)
DECL|macro|BOND_MODE_ROUNDROBIN
mdefine_line|#define BOND_MODE_ROUNDROBIN    0
DECL|macro|BOND_MODE_ACTIVEBACKUP
mdefine_line|#define BOND_MODE_ACTIVEBACKUP  1
DECL|macro|BOND_MODE_XOR
mdefine_line|#define BOND_MODE_XOR           2 
multiline_comment|/* each slave&squot;s link has 4 states */
DECL|macro|BOND_LINK_UP
mdefine_line|#define BOND_LINK_UP    0           /* link is up and running */
DECL|macro|BOND_LINK_FAIL
mdefine_line|#define BOND_LINK_FAIL  1           /* link has just gone down */
DECL|macro|BOND_LINK_DOWN
mdefine_line|#define BOND_LINK_DOWN  2           /* link has been down for too long time */
DECL|macro|BOND_LINK_BACK
mdefine_line|#define BOND_LINK_BACK  3           /* link is going back */
multiline_comment|/* each slave has several states */
DECL|macro|BOND_STATE_ACTIVE
mdefine_line|#define BOND_STATE_ACTIVE       0   /* link is active */
DECL|macro|BOND_STATE_BACKUP
mdefine_line|#define BOND_STATE_BACKUP       1   /* link is backup */
DECL|macro|MAX_BONDS
mdefine_line|#define MAX_BONDS               1   /* Maximum number of devices to support */
DECL|struct|ifbond
r_typedef
r_struct
id|ifbond
(brace
DECL|member|bond_mode
id|__s32
id|bond_mode
suffix:semicolon
DECL|member|num_slaves
id|__s32
id|num_slaves
suffix:semicolon
DECL|member|miimon
id|__s32
id|miimon
suffix:semicolon
DECL|typedef|ifbond
)brace
id|ifbond
suffix:semicolon
DECL|struct|ifslave
r_typedef
r_struct
id|ifslave
(brace
DECL|member|slave_id
id|__s32
id|slave_id
suffix:semicolon
multiline_comment|/* Used as an IN param to the BOND_SLAVE_INFO_QUERY ioctl */
DECL|member|slave_name
r_char
id|slave_name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|link
r_char
id|link
suffix:semicolon
DECL|member|state
r_char
id|state
suffix:semicolon
DECL|member|link_failure_count
id|__u32
id|link_failure_count
suffix:semicolon
DECL|typedef|ifslave
)brace
id|ifslave
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|slave
r_typedef
r_struct
id|slave
(brace
DECL|member|next
r_struct
id|slave
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|slave
op_star
id|prev
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|delay
r_int
id|delay
suffix:semicolon
DECL|member|link
r_char
id|link
suffix:semicolon
multiline_comment|/* one of BOND_LINK_XXXX */
DECL|member|state
r_char
id|state
suffix:semicolon
multiline_comment|/* one of BOND_STATE_XXXX */
DECL|member|link_failure_count
id|u32
id|link_failure_count
suffix:semicolon
DECL|typedef|slave_t
)brace
id|slave_t
suffix:semicolon
DECL|struct|bonding
r_typedef
r_struct
id|bonding
(brace
DECL|member|next
id|slave_t
op_star
id|next
suffix:semicolon
DECL|member|prev
id|slave_t
op_star
id|prev
suffix:semicolon
DECL|member|current_slave
id|slave_t
op_star
id|current_slave
suffix:semicolon
DECL|member|slave_cnt
id|__s32
id|slave_cnt
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|ptrlock
id|rwlock_t
id|ptrlock
suffix:semicolon
DECL|member|mii_timer
r_struct
id|timer_list
id|mii_timer
suffix:semicolon
DECL|member|arp_timer
r_struct
id|timer_list
id|arp_timer
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
op_star
id|stats
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|member|bond_proc_dir
r_struct
id|proc_dir_entry
op_star
id|bond_proc_dir
suffix:semicolon
DECL|member|bond_proc_info_file
r_struct
id|proc_dir_entry
op_star
id|bond_proc_info_file
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
DECL|member|next_bond
r_struct
id|bonding
op_star
id|next_bond
suffix:semicolon
DECL|member|device
r_struct
id|net_device
op_star
id|device
suffix:semicolon
DECL|typedef|bonding_t
)brace
id|bonding_t
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_BOND_H */
multiline_comment|/*&n; * Local variables:&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  c-indent-level: 8&n; *  c-basic-offset: 8&n; *  tab-width: 8&n; * End:&n; */
eof
