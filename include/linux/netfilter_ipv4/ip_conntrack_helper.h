multiline_comment|/* IP connection tracking helpers. */
macro_line|#ifndef _IP_CONNTRACK_HELPER_H
DECL|macro|_IP_CONNTRACK_HELPER_H
mdefine_line|#define _IP_CONNTRACK_HELPER_H
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
r_struct
id|module
suffix:semicolon
DECL|struct|ip_conntrack_helper
r_struct
id|ip_conntrack_helper
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* Internal use. */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name of the module */
DECL|member|me
r_struct
id|module
op_star
id|me
suffix:semicolon
multiline_comment|/* pointer to self */
DECL|member|max_expected
r_int
r_int
id|max_expected
suffix:semicolon
multiline_comment|/* Maximum number of concurrent &n;&t;&t;&t;&t;&t; * expected connections */
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* timeout for expecteds */
multiline_comment|/* Mask of things we will help (compared against server response) */
DECL|member|tuple
r_struct
id|ip_conntrack_tuple
id|tuple
suffix:semicolon
DECL|member|mask
r_struct
id|ip_conntrack_tuple
id|mask
suffix:semicolon
multiline_comment|/* Function to call when data passes; return verdict, or -1 to&n;           invalidate. */
DECL|member|help
r_int
(paren
op_star
id|help
)paren
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|conntrackinfo
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|ip_conntrack_helper_register
c_func
(paren
r_struct
id|ip_conntrack_helper
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ip_conntrack_helper_unregister
c_func
(paren
r_struct
id|ip_conntrack_helper
op_star
)paren
suffix:semicolon
multiline_comment|/* Allocate space for an expectation: this is mandatory before calling &n;   ip_conntrack_expect_related. */
r_extern
r_struct
id|ip_conntrack_expect
op_star
id|ip_conntrack_expect_alloc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ip_conntrack_expect_free
c_func
(paren
r_struct
id|ip_conntrack_expect
op_star
id|exp
)paren
suffix:semicolon
multiline_comment|/* Add an expected connection: can have more than one per connection */
r_extern
r_int
id|ip_conntrack_expect_related
c_func
(paren
r_struct
id|ip_conntrack_expect
op_star
id|exp
)paren
suffix:semicolon
r_extern
r_void
id|ip_conntrack_unexpect_related
c_func
(paren
r_struct
id|ip_conntrack_expect
op_star
id|exp
)paren
suffix:semicolon
macro_line|#endif /*_IP_CONNTRACK_HELPER_H*/
eof
