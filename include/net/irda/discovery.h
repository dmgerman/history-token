multiline_comment|/*********************************************************************&n; *                &n; * Filename:      discovery.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Apr  6 16:53:53 1999&n; * Modified at:   Tue Oct  5 10:05:10 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#ifndef DISCOVERY_H
DECL|macro|DISCOVERY_H
mdefine_line|#define DISCOVERY_H
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
DECL|macro|DISCOVERY_EXPIRE_TIMEOUT
mdefine_line|#define DISCOVERY_EXPIRE_TIMEOUT 6*HZ
DECL|macro|DISCOVERY_DEFAULT_SLOTS
mdefine_line|#define DISCOVERY_DEFAULT_SLOTS  0
DECL|macro|NICKNAME_MAX_LEN
mdefine_line|#define NICKNAME_MAX_LEN 21
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
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* Which link the device was discovered */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Remote device address */
DECL|member|condition
id|LAP_REASON
id|condition
suffix:semicolon
multiline_comment|/* More info about the discovery */
DECL|member|hints
id|__u16_host_order
id|hints
suffix:semicolon
multiline_comment|/* Discovery hint bits */
DECL|member|charset
id|__u8
id|charset
suffix:semicolon
multiline_comment|/* Encoding of nickname */
DECL|member|nickname
r_char
id|nickname
(braket
l_int|22
)braket
suffix:semicolon
multiline_comment|/* The name of the device (21 bytes + &bslash;0) */
DECL|member|name_len
r_int
id|name_len
suffix:semicolon
multiline_comment|/* Lenght of nickname */
DECL|member|gen_addr_bit
r_int
id|gen_addr_bit
suffix:semicolon
multiline_comment|/* Need to generate a new device address? */
DECL|member|nslots
r_int
id|nslots
suffix:semicolon
multiline_comment|/* Number of slots to use when discovering */
DECL|member|timestamp
r_int
r_int
id|timestamp
suffix:semicolon
multiline_comment|/* Time discovered */
DECL|member|first_timestamp
r_int
r_int
id|first_timestamp
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
)paren
suffix:semicolon
macro_line|#endif
eof
