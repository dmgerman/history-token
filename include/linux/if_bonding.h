multiline_comment|/*&n; * Bond several ethernet interfaces into a Cisco, running &squot;Etherchannel&squot;.&n; *&n; * &n; * Portions are (c) Copyright 1995 Simon &quot;Guru Aleph-Null&quot; Janes&n; * NCM: Network and Communications Management, Inc.&n; *&n; * BUT, I&squot;m the one who modified it for ethernet, so:&n; * (c) Copyright 1999, Thomas Davis, tadavis@lbl.gov&n; *&n; *&t;This software may be used and distributed according to the terms&n; *&t;of the GNU General Public License, incorporated herein by reference.&n; * &n; */
macro_line|#ifndef _LINUX_IF_BONDING_H
DECL|macro|_LINUX_IF_BONDING_H
mdefine_line|#define _LINUX_IF_BONDING_H
DECL|macro|BOND_ENSLAVE
mdefine_line|#define BOND_ENSLAVE     (SIOCDEVPRIVATE)
DECL|macro|BOND_RELEASE
mdefine_line|#define BOND_RELEASE     (SIOCDEVPRIVATE + 1)
DECL|macro|BOND_SETHWADDR
mdefine_line|#define BOND_SETHWADDR   (SIOCDEVPRIVATE + 2)
macro_line|#endif /* _LINUX_BOND_H */
multiline_comment|/*&n; * Local variables:&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  c-indent-level: 8&n; *  c-basic-offset: 8&n; *  tab-width: 8&n; * End:&n; */
eof
