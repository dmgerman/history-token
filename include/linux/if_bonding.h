multiline_comment|/*&n; * Bond several ethernet interfaces into a Cisco, running &squot;Etherchannel&squot;.&n; *&n; * &n; * Portions are (c) Copyright 1995 Simon &quot;Guru Aleph-Null&quot; Janes&n; * NCM: Network and Communications Management, Inc.&n; *&n; * BUT, I&squot;m the one who modified it for ethernet, so:&n; * (c) Copyright 1999, Thomas Davis, tadavis@lbl.gov&n; *&n; *&t;This software may be used and distributed according to the terms&n; *&t;of the GNU Public License, incorporated herein by reference.&n; * &n; * 2003/03/18 - Amir Noam &lt;amir.noam at intel dot com&gt;&n; *&t;- Added support for getting slave&squot;s speed and duplex via ethtool.&n; *&t;  Needed for 802.3ad and other future modes.&n; * &n; * 2003/03/18 - Tsippy Mendelson &lt;tsippy.mendelson at intel dot com&gt; and&n; *&t;&t;Shmulik Hen &lt;shmulik.hen at intel dot com&gt;&n; *&t;- Enable support of modes that need to use the unique mac address of&n; *&t;  each slave.&n; *&n; * 2003/03/18 - Tsippy Mendelson &lt;tsippy.mendelson at intel dot com&gt; and&n; *&t;&t;Amir Noam &lt;amir.noam at intel dot com&gt;&n; *&t;- Moved driver&squot;s private data types to bonding.h&n; *&n; * 2003/03/18 - Amir Noam &lt;amir.noam at intel dot com&gt;,&n; *&t;&t;Tsippy Mendelson &lt;tsippy.mendelson at intel dot com&gt; and&n; *&t;&t;Shmulik Hen &lt;shmulik.hen at intel dot com&gt;&n; *&t;- Added support for IEEE 802.3ad Dynamic link aggregation mode.&n; *&n; * 2003/05/01 - Amir Noam &lt;amir.noam at intel dot com&gt;&n; *&t;- Added ABI version control to restore compatibility between&n; *&t;  new/old ifenslave and new/old bonding.&n; */
macro_line|#ifndef _LINUX_IF_BONDING_H
DECL|macro|_LINUX_IF_BONDING_H
mdefine_line|#define _LINUX_IF_BONDING_H
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
multiline_comment|/* userland - kernel ABI version (2003/05/08) */
DECL|macro|BOND_ABI_VERSION
mdefine_line|#define BOND_ABI_VERSION 1
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
mdefine_line|#define BOND_MODE_ROUNDROBIN&t;0
DECL|macro|BOND_MODE_ACTIVEBACKUP
mdefine_line|#define BOND_MODE_ACTIVEBACKUP&t;1
DECL|macro|BOND_MODE_XOR
mdefine_line|#define BOND_MODE_XOR&t;&t;2
DECL|macro|BOND_MODE_BROADCAST
mdefine_line|#define BOND_MODE_BROADCAST&t;3
DECL|macro|BOND_MODE_8023AD
mdefine_line|#define BOND_MODE_8023AD        4
DECL|macro|BOND_MODE_TLB
mdefine_line|#define BOND_MODE_TLB           5
DECL|macro|BOND_MODE_ALB
mdefine_line|#define BOND_MODE_ALB&t;&t;6 /* TLB + RLB (receive load balancing) */
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
DECL|macro|BOND_DEFAULT_MAX_BONDS
mdefine_line|#define BOND_DEFAULT_MAX_BONDS  1   /* Default maximum number of devices to support */
DECL|macro|BOND_MULTICAST_DISABLED
mdefine_line|#define BOND_MULTICAST_DISABLED 0
DECL|macro|BOND_MULTICAST_ACTIVE
mdefine_line|#define BOND_MULTICAST_ACTIVE   1
DECL|macro|BOND_MULTICAST_ALL
mdefine_line|#define BOND_MULTICAST_ALL      2
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
DECL|struct|ad_info
r_struct
id|ad_info
(brace
DECL|member|aggregator_id
id|__u16
id|aggregator_id
suffix:semicolon
DECL|member|ports
id|__u16
id|ports
suffix:semicolon
DECL|member|actor_key
id|__u16
id|actor_key
suffix:semicolon
DECL|member|partner_key
id|__u16
id|partner_key
suffix:semicolon
DECL|member|partner_system
id|__u8
id|partner_system
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_IF_BONDING_H */
multiline_comment|/*&n; * Local variables:&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  c-indent-level: 8&n; *  c-basic-offset: 8&n; *  tab-width: 8&n; * End:&n; */
eof
