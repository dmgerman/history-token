multiline_comment|/*&n; * &t;Format of an ARP firewall descriptor&n; *&n; * &t;src, tgt, src_mask, tgt_mask, arpop, arpop_mask are always stored in&n; *&t;network byte order.&n; * &t;flags are stored in host byte order (of course).&n; */
macro_line|#ifndef _ARPTABLES_H
DECL|macro|_ARPTABLES_H
mdefine_line|#define _ARPTABLES_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/netfilter_arp.h&gt;
DECL|macro|ARPT_FUNCTION_MAXNAMELEN
mdefine_line|#define ARPT_FUNCTION_MAXNAMELEN 30
DECL|macro|ARPT_TABLE_MAXNAMELEN
mdefine_line|#define ARPT_TABLE_MAXNAMELEN 32
DECL|macro|ARPT_DEV_ADDR_LEN_MAX
mdefine_line|#define ARPT_DEV_ADDR_LEN_MAX 16
DECL|struct|arpt_devaddr_info
r_struct
id|arpt_devaddr_info
(brace
DECL|member|addr
r_char
id|addr
(braket
id|ARPT_DEV_ADDR_LEN_MAX
)braket
suffix:semicolon
DECL|member|mask
r_char
id|mask
(braket
id|ARPT_DEV_ADDR_LEN_MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Yes, Virginia, you have to zero the padding. */
DECL|struct|arpt_arp
r_struct
id|arpt_arp
(brace
multiline_comment|/* Source and target IP addr */
DECL|member|src
DECL|member|tgt
r_struct
id|in_addr
id|src
comma
id|tgt
suffix:semicolon
multiline_comment|/* Mask for src and target IP addr */
DECL|member|smsk
DECL|member|tmsk
r_struct
id|in_addr
id|smsk
comma
id|tmsk
suffix:semicolon
multiline_comment|/* Device hw address length, src+target device addresses */
DECL|member|arhln
DECL|member|arhln_mask
id|u_int8_t
id|arhln
comma
id|arhln_mask
suffix:semicolon
DECL|member|src_devaddr
r_struct
id|arpt_devaddr_info
id|src_devaddr
suffix:semicolon
DECL|member|tgt_devaddr
r_struct
id|arpt_devaddr_info
id|tgt_devaddr
suffix:semicolon
multiline_comment|/* ARP operation code. */
DECL|member|arpop
DECL|member|arpop_mask
id|u_int16_t
id|arpop
comma
id|arpop_mask
suffix:semicolon
multiline_comment|/* ARP hardware address and protocol address format. */
DECL|member|arhrd
DECL|member|arhrd_mask
id|u_int16_t
id|arhrd
comma
id|arhrd_mask
suffix:semicolon
DECL|member|arpro
DECL|member|arpro_mask
id|u_int16_t
id|arpro
comma
id|arpro_mask
suffix:semicolon
multiline_comment|/* The protocol address length is only accepted if it is 4&n;&t; * so there is no use in offering a way to do filtering on it.&n;&t; */
DECL|member|iniface
DECL|member|outiface
r_char
id|iniface
(braket
id|IFNAMSIZ
)braket
comma
id|outiface
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|iniface_mask
DECL|member|outiface_mask
r_int
r_char
id|iniface_mask
(braket
id|IFNAMSIZ
)braket
comma
id|outiface_mask
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* Flags word */
DECL|member|flags
id|u_int8_t
id|flags
suffix:semicolon
multiline_comment|/* Inverse flags */
DECL|member|invflags
id|u_int16_t
id|invflags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arpt_entry_target
r_struct
id|arpt_entry_target
(brace
r_union
(brace
r_struct
(brace
DECL|member|target_size
id|u_int16_t
id|target_size
suffix:semicolon
multiline_comment|/* Used by userspace */
DECL|member|name
r_char
id|name
(braket
id|ARPT_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|user
)brace
id|user
suffix:semicolon
r_struct
(brace
DECL|member|target_size
id|u_int16_t
id|target_size
suffix:semicolon
multiline_comment|/* Used inside the kernel */
DECL|member|target
r_struct
id|arpt_target
op_star
id|target
suffix:semicolon
DECL|member|kernel
)brace
id|kernel
suffix:semicolon
multiline_comment|/* Total length */
DECL|member|target_size
id|u_int16_t
id|target_size
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arpt_standard_target
r_struct
id|arpt_standard_target
(brace
DECL|member|target
r_struct
id|arpt_entry_target
id|target
suffix:semicolon
DECL|member|verdict
r_int
id|verdict
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arpt_counters
r_struct
id|arpt_counters
(brace
DECL|member|pcnt
DECL|member|bcnt
id|u_int64_t
id|pcnt
comma
id|bcnt
suffix:semicolon
multiline_comment|/* Packet and byte counters */
)brace
suffix:semicolon
multiline_comment|/* Values for &quot;flag&quot; field in struct arpt_ip (general arp structure).&n; * No flags defined yet.&n; */
DECL|macro|ARPT_F_MASK
mdefine_line|#define ARPT_F_MASK&t;&t;0x00&t;/* All possible flag bits mask. */
multiline_comment|/* Values for &quot;inv&quot; field in struct arpt_arp. */
DECL|macro|ARPT_INV_VIA_IN
mdefine_line|#define ARPT_INV_VIA_IN&t;&t;0x0001&t;/* Invert the sense of IN IFACE. */
DECL|macro|ARPT_INV_VIA_OUT
mdefine_line|#define ARPT_INV_VIA_OUT&t;0x0002&t;/* Invert the sense of OUT IFACE */
DECL|macro|ARPT_INV_SRCIP
mdefine_line|#define ARPT_INV_SRCIP&t;&t;0x0004&t;/* Invert the sense of SRC IP. */
DECL|macro|ARPT_INV_TGTIP
mdefine_line|#define ARPT_INV_TGTIP&t;&t;0x0008&t;/* Invert the sense of TGT IP. */
DECL|macro|ARPT_INV_SRCDEVADDR
mdefine_line|#define ARPT_INV_SRCDEVADDR&t;0x0010&t;/* Invert the sense of SRC DEV ADDR. */
DECL|macro|ARPT_INV_TGTDEVADDR
mdefine_line|#define ARPT_INV_TGTDEVADDR&t;0x0020&t;/* Invert the sense of TGT DEV ADDR. */
DECL|macro|ARPT_INV_ARPOP
mdefine_line|#define ARPT_INV_ARPOP&t;&t;0x0040&t;/* Invert the sense of ARP OP. */
DECL|macro|ARPT_INV_ARPHRD
mdefine_line|#define ARPT_INV_ARPHRD&t;&t;0x0080&t;/* Invert the sense of ARP HRD. */
DECL|macro|ARPT_INV_ARPPRO
mdefine_line|#define ARPT_INV_ARPPRO&t;&t;0x0100&t;/* Invert the sense of ARP PRO. */
DECL|macro|ARPT_INV_ARPHLN
mdefine_line|#define ARPT_INV_ARPHLN&t;&t;0x0200&t;/* Invert the sense of ARP HLN. */
DECL|macro|ARPT_INV_MASK
mdefine_line|#define ARPT_INV_MASK&t;&t;0x007F&t;/* All possible flag bits mask. */
multiline_comment|/* This structure defines each of the firewall rules.  Consists of 3&n;   parts which are 1) general ARP header stuff 2) match specific&n;   stuff 3) the target to perform if the rule matches */
DECL|struct|arpt_entry
r_struct
id|arpt_entry
(brace
DECL|member|arp
r_struct
id|arpt_arp
id|arp
suffix:semicolon
multiline_comment|/* Size of arpt_entry + matches */
DECL|member|target_offset
id|u_int16_t
id|target_offset
suffix:semicolon
multiline_comment|/* Size of arpt_entry + matches + target */
DECL|member|next_offset
id|u_int16_t
id|next_offset
suffix:semicolon
multiline_comment|/* Back pointer */
DECL|member|comefrom
r_int
r_int
id|comefrom
suffix:semicolon
multiline_comment|/* Packet and byte counters. */
DECL|member|counters
r_struct
id|arpt_counters
id|counters
suffix:semicolon
multiline_comment|/* The matches (if any), then the target. */
DECL|member|elems
r_int
r_char
id|elems
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * New IP firewall options for [gs]etsockopt at the RAW IP level.&n; * Unlike BSD Linux inherits IP options so you don&squot;t have to use a raw&n; * socket for this. Instead we check rights in the calls.&n; */
DECL|macro|ARPT_BASE_CTL
mdefine_line|#define ARPT_BASE_CTL&t;&t;96&t;/* base for firewall socket options */
DECL|macro|ARPT_SO_SET_REPLACE
mdefine_line|#define ARPT_SO_SET_REPLACE&t;&t;(ARPT_BASE_CTL)
DECL|macro|ARPT_SO_SET_ADD_COUNTERS
mdefine_line|#define ARPT_SO_SET_ADD_COUNTERS&t;(ARPT_BASE_CTL + 1)
DECL|macro|ARPT_SO_SET_MAX
mdefine_line|#define ARPT_SO_SET_MAX&t;&t;&t;ARPT_SO_SET_ADD_COUNTERS
DECL|macro|ARPT_SO_GET_INFO
mdefine_line|#define ARPT_SO_GET_INFO&t;&t;(ARPT_BASE_CTL)
DECL|macro|ARPT_SO_GET_ENTRIES
mdefine_line|#define ARPT_SO_GET_ENTRIES&t;&t;(ARPT_BASE_CTL + 1)
DECL|macro|ARPT_SO_GET_MAX
mdefine_line|#define ARPT_SO_GET_MAX&t;&t;&t;ARPT_SO_GET_ENTRIES
multiline_comment|/* CONTINUE verdict for targets */
DECL|macro|ARPT_CONTINUE
mdefine_line|#define ARPT_CONTINUE 0xFFFFFFFF
multiline_comment|/* For standard target */
DECL|macro|ARPT_RETURN
mdefine_line|#define ARPT_RETURN (-NF_MAX_VERDICT - 1)
multiline_comment|/* The argument to ARPT_SO_GET_INFO */
DECL|struct|arpt_getinfo
r_struct
id|arpt_getinfo
(brace
multiline_comment|/* Which table: caller fills this in. */
DECL|member|name
r_char
id|name
(braket
id|ARPT_TABLE_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* Kernel fills these in. */
multiline_comment|/* Which hook entry points are valid: bitmask */
DECL|member|valid_hooks
r_int
r_int
id|valid_hooks
suffix:semicolon
multiline_comment|/* Hook entry points: one per netfilter hook. */
DECL|member|hook_entry
r_int
r_int
id|hook_entry
(braket
id|NF_ARP_NUMHOOKS
)braket
suffix:semicolon
multiline_comment|/* Underflow points. */
DECL|member|underflow
r_int
r_int
id|underflow
(braket
id|NF_ARP_NUMHOOKS
)braket
suffix:semicolon
multiline_comment|/* Number of entries */
DECL|member|num_entries
r_int
r_int
id|num_entries
suffix:semicolon
multiline_comment|/* Size of entries. */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The argument to ARPT_SO_SET_REPLACE. */
DECL|struct|arpt_replace
r_struct
id|arpt_replace
(brace
multiline_comment|/* Which table. */
DECL|member|name
r_char
id|name
(braket
id|ARPT_TABLE_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* Which hook entry points are valid: bitmask.  You can&squot;t&n;           change this. */
DECL|member|valid_hooks
r_int
r_int
id|valid_hooks
suffix:semicolon
multiline_comment|/* Number of entries */
DECL|member|num_entries
r_int
r_int
id|num_entries
suffix:semicolon
multiline_comment|/* Total size of new entries */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* Hook entry points. */
DECL|member|hook_entry
r_int
r_int
id|hook_entry
(braket
id|NF_ARP_NUMHOOKS
)braket
suffix:semicolon
multiline_comment|/* Underflow points. */
DECL|member|underflow
r_int
r_int
id|underflow
(braket
id|NF_ARP_NUMHOOKS
)braket
suffix:semicolon
multiline_comment|/* Information about old entries: */
multiline_comment|/* Number of counters (must be equal to current number of entries). */
DECL|member|num_counters
r_int
r_int
id|num_counters
suffix:semicolon
multiline_comment|/* The old entries&squot; counters. */
DECL|member|counters
r_struct
id|arpt_counters
op_star
id|counters
suffix:semicolon
multiline_comment|/* The entries (hang off end: not really an array). */
DECL|member|entries
r_struct
id|arpt_entry
id|entries
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The argument to ARPT_SO_ADD_COUNTERS. */
DECL|struct|arpt_counters_info
r_struct
id|arpt_counters_info
(brace
multiline_comment|/* Which table. */
DECL|member|name
r_char
id|name
(braket
id|ARPT_TABLE_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|num_counters
r_int
r_int
id|num_counters
suffix:semicolon
multiline_comment|/* The counters (actually `number&squot; of these). */
DECL|member|counters
r_struct
id|arpt_counters
id|counters
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The argument to ARPT_SO_GET_ENTRIES. */
DECL|struct|arpt_get_entries
r_struct
id|arpt_get_entries
(brace
multiline_comment|/* Which table: user fills this in. */
DECL|member|name
r_char
id|name
(braket
id|ARPT_TABLE_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* User fills this in: total entry size. */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* The entries. */
DECL|member|entrytable
r_struct
id|arpt_entry
id|entrytable
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Standard return verdict, or do jump. */
DECL|macro|ARPT_STANDARD_TARGET
mdefine_line|#define ARPT_STANDARD_TARGET &quot;&quot;
multiline_comment|/* Error verdict. */
DECL|macro|ARPT_ERROR_TARGET
mdefine_line|#define ARPT_ERROR_TARGET &quot;ERROR&quot;
multiline_comment|/* Helper functions */
DECL|function|arpt_get_target
r_static
id|__inline__
r_struct
id|arpt_entry_target
op_star
id|arpt_get_target
c_func
(paren
r_struct
id|arpt_entry
op_star
id|e
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|e
op_plus
id|e-&gt;target_offset
suffix:semicolon
)brace
multiline_comment|/* fn returns 0 to continue iteration */
DECL|macro|ARPT_ENTRY_ITERATE
mdefine_line|#define ARPT_ENTRY_ITERATE(entries, size, fn, args...)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int __i;&t;&t;&t;&t;&t;&bslash;&n;&t;int __ret = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct arpt_entry *__entry;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (__i = 0; __i &lt; (size); __i += __entry-&gt;next_offset) { &bslash;&n;&t;&t;__entry = (void *)(entries) + __i;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__ret = fn(__entry , ## args);&t;&t;&t;&bslash;&n;&t;&t;if (__ret != 0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; *&t;Main firewall chains definitions and global var&squot;s definitions.&n; */
macro_line|#ifdef __KERNEL__
multiline_comment|/* Registration hooks for targets. */
DECL|struct|arpt_target
r_struct
id|arpt_target
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|name
r_const
r_char
id|name
(braket
id|ARPT_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* Returns verdict. */
DECL|member|target
r_int
r_int
(paren
op_star
id|target
)paren
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
id|hooknum
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_const
r_void
op_star
id|targinfo
comma
r_void
op_star
id|userdata
)paren
suffix:semicolon
multiline_comment|/* Called when user tries to insert an entry of this type:&n;           hook_mask is a bitmask of hooks from which it can be&n;           called. */
multiline_comment|/* Should return true or false. */
DECL|member|checkentry
r_int
(paren
op_star
id|checkentry
)paren
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|arpt_entry
op_star
id|e
comma
r_void
op_star
id|targinfo
comma
r_int
r_int
id|targinfosize
comma
r_int
r_int
id|hook_mask
)paren
suffix:semicolon
multiline_comment|/* Called when entry of this type deleted. */
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_void
op_star
id|targinfo
comma
r_int
r_int
id|targinfosize
)paren
suffix:semicolon
multiline_comment|/* Set this to THIS_MODULE if you are a module, otherwise NULL */
DECL|member|me
r_struct
id|module
op_star
id|me
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|arpt_register_target
c_func
(paren
r_struct
id|arpt_target
op_star
id|target
)paren
suffix:semicolon
r_extern
r_void
id|arpt_unregister_target
c_func
(paren
r_struct
id|arpt_target
op_star
id|target
)paren
suffix:semicolon
multiline_comment|/* Furniture shopping... */
DECL|struct|arpt_table
r_struct
id|arpt_table
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* A unique name... */
DECL|member|name
r_char
id|name
(braket
id|ARPT_TABLE_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* Seed table: copied in register_table */
DECL|member|table
r_struct
id|arpt_replace
op_star
id|table
suffix:semicolon
multiline_comment|/* What hooks you will enter on */
DECL|member|valid_hooks
r_int
r_int
id|valid_hooks
suffix:semicolon
multiline_comment|/* Lock for the curtain */
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
multiline_comment|/* Man behind the curtain... */
DECL|member|private
r_struct
id|arpt_table_info
op_star
r_private
suffix:semicolon
multiline_comment|/* Set this to THIS_MODULE if you are a module, otherwise NULL */
DECL|member|me
r_struct
id|module
op_star
id|me
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|arpt_register_table
c_func
(paren
r_struct
id|arpt_table
op_star
id|table
)paren
suffix:semicolon
r_extern
r_void
id|arpt_unregister_table
c_func
(paren
r_struct
id|arpt_table
op_star
id|table
)paren
suffix:semicolon
r_extern
r_int
r_int
id|arpt_do_table
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
id|hook
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_struct
id|arpt_table
op_star
id|table
comma
r_void
op_star
id|userdata
)paren
suffix:semicolon
DECL|macro|ARPT_ALIGN
mdefine_line|#define ARPT_ALIGN(s) (((s) + (__alignof__(struct arpt_entry)-1)) &amp; ~(__alignof__(struct arpt_entry)-1))
macro_line|#endif /*__KERNEL__*/
macro_line|#endif /* _ARPTABLES_H */
eof
