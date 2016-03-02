multiline_comment|/*********************************************************************&n; *                &n; * Filename:      discovery.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Apr  6 16:53:53 1999&n; * Modified at:   Tue Oct  5 10:05:10 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *     Copyright (c) 2000-2002 Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#ifndef DISCOVERY_H
DECL|macro|DISCOVERY_H
mdefine_line|#define DISCOVERY_H
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;&t;&t;/* irda_queue_t */
macro_line|#include &lt;net/irda/irlap_event.h&gt;&t;/* LAP_REASON */
DECL|macro|DISCOVERY_EXPIRE_TIMEOUT
mdefine_line|#define DISCOVERY_EXPIRE_TIMEOUT (2*sysctl_discovery_timeout*HZ)
DECL|macro|DISCOVERY_DEFAULT_SLOTS
mdefine_line|#define DISCOVERY_DEFAULT_SLOTS  0
multiline_comment|/*&n; *  This type is used by the protocols that transmit 16 bits words in &n; *  little endian format. A little endian machine stores MSB of word in&n; *  byte[1] and LSB in byte[0]. A big endian machine stores MSB in byte[0] &n; *  and LSB in byte[1].&n; *&n; * This structure is used in the code for things that are endian neutral&n; * but that fit in a word so that we can manipulate them efficiently.&n; * By endian neutral, I mean things that are really an array of bytes,&n; * and always used as such, for example the hint bits. Jean II&n; */
r_typedef
r_union
(brace
DECL|member|word
id|__u16
id|word
suffix:semicolon
DECL|member|byte
id|__u8
id|byte
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|__u16_host_order
)brace
id|__u16_host_order
suffix:semicolon
multiline_comment|/* Same purpose, different application */
DECL|macro|u16ho
mdefine_line|#define u16ho(array) (* ((__u16 *) array))
multiline_comment|/* Types of discovery */
r_typedef
r_enum
(brace
DECL|enumerator|DISCOVERY_LOG
id|DISCOVERY_LOG
comma
multiline_comment|/* What&squot;s in our discovery log */
DECL|enumerator|DISCOVERY_ACTIVE
id|DISCOVERY_ACTIVE
comma
multiline_comment|/* Doing our own discovery on the medium */
DECL|enumerator|DISCOVERY_PASSIVE
id|DISCOVERY_PASSIVE
comma
multiline_comment|/* Peer doing discovery on the medium */
DECL|enumerator|EXPIRY_TIMEOUT
id|EXPIRY_TIMEOUT
comma
multiline_comment|/* Entry expired due to timeout */
DECL|typedef|DISCOVERY_MODE
)brace
id|DISCOVERY_MODE
suffix:semicolon
DECL|macro|NICKNAME_MAX_LEN
mdefine_line|#define NICKNAME_MAX_LEN 21
multiline_comment|/* Basic discovery information about a peer */
DECL|typedef|discinfo_t
r_typedef
r_struct
id|irda_device_info
id|discinfo_t
suffix:semicolon
multiline_comment|/* linux/irda.h */
multiline_comment|/*&n; * The DISCOVERY structure is used for both discovery requests and responses&n; */
DECL|struct|discovery_t
r_typedef
r_struct
id|discovery_t
(brace
DECL|member|q
id|irda_queue_t
id|q
suffix:semicolon
multiline_comment|/* Must be first! */
DECL|member|data
id|discinfo_t
id|data
suffix:semicolon
multiline_comment|/* Basic discovery information */
DECL|member|name_len
r_int
id|name_len
suffix:semicolon
multiline_comment|/* Lenght of nickname */
DECL|member|condition
id|LAP_REASON
id|condition
suffix:semicolon
multiline_comment|/* More info about the discovery */
DECL|member|gen_addr_bit
r_int
id|gen_addr_bit
suffix:semicolon
multiline_comment|/* Need to generate a new device&n;&t;&t;&t;&t;&t; * address? */
DECL|member|nslots
r_int
id|nslots
suffix:semicolon
multiline_comment|/* Number of slots to use when&n;&t;&t;&t;&t;&t; * discovering */
DECL|member|timestamp
r_int
r_int
id|timestamp
suffix:semicolon
multiline_comment|/* Last time discovered */
DECL|member|firststamp
r_int
r_int
id|firststamp
suffix:semicolon
multiline_comment|/* First time discovered */
DECL|typedef|discovery_t
)brace
id|discovery_t
suffix:semicolon
r_void
id|irlmp_add_discovery
c_func
(paren
id|hashbin_t
op_star
id|cachelog
comma
id|discovery_t
op_star
id|discovery
)paren
suffix:semicolon
r_void
id|irlmp_add_discovery_log
c_func
(paren
id|hashbin_t
op_star
id|cachelog
comma
id|hashbin_t
op_star
id|log
)paren
suffix:semicolon
r_void
id|irlmp_expire_discoveries
c_func
(paren
id|hashbin_t
op_star
id|log
comma
id|__u32
id|saddr
comma
r_int
id|force
)paren
suffix:semicolon
r_struct
id|irda_device_info
op_star
id|irlmp_copy_discoveries
c_func
(paren
id|hashbin_t
op_star
id|log
comma
r_int
op_star
id|pn
comma
id|__u16
id|mask
comma
r_int
id|old_entries
)paren
suffix:semicolon
macro_line|#endif
eof
