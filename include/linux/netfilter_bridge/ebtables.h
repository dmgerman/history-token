multiline_comment|/*&n; *  ebtables&n; *&n; *&t;Authors:&n; *&t;Bart De Schuymer&t;&t;&lt;bdschuym@pandora.be&gt;&n; *&n; *  ebtables.c,v 2.0, April, 2002&n; *&n; *  This code is stongly inspired on the iptables code which is&n; *  Copyright (C) 1999 Paul `Rusty&squot; Russell &amp; Michael J. Neuling&n; */
macro_line|#ifndef __LINUX_BRIDGE_EFF_H
DECL|macro|__LINUX_BRIDGE_EFF_H
mdefine_line|#define __LINUX_BRIDGE_EFF_H
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/netfilter_bridge.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
DECL|macro|EBT_TABLE_MAXNAMELEN
mdefine_line|#define EBT_TABLE_MAXNAMELEN 32
DECL|macro|EBT_CHAIN_MAXNAMELEN
mdefine_line|#define EBT_CHAIN_MAXNAMELEN EBT_TABLE_MAXNAMELEN
DECL|macro|EBT_FUNCTION_MAXNAMELEN
mdefine_line|#define EBT_FUNCTION_MAXNAMELEN EBT_TABLE_MAXNAMELEN
multiline_comment|/* verdicts &gt;0 are &quot;branches&quot; */
DECL|macro|EBT_ACCEPT
mdefine_line|#define EBT_ACCEPT   -1
DECL|macro|EBT_DROP
mdefine_line|#define EBT_DROP     -2
DECL|macro|EBT_CONTINUE
mdefine_line|#define EBT_CONTINUE -3
DECL|macro|EBT_RETURN
mdefine_line|#define EBT_RETURN   -4
DECL|macro|NUM_STANDARD_TARGETS
mdefine_line|#define NUM_STANDARD_TARGETS   4
DECL|struct|ebt_counter
r_struct
id|ebt_counter
(brace
DECL|member|pcnt
r_uint64
id|pcnt
suffix:semicolon
DECL|member|bcnt
r_uint64
id|bcnt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ebt_entries
r_struct
id|ebt_entries
(brace
multiline_comment|/* this field is always set to zero&n;&t; * See EBT_ENTRY_OR_ENTRIES.&n;&t; * Must be same size as ebt_entry.bitmask */
DECL|member|distinguisher
r_int
r_int
id|distinguisher
suffix:semicolon
multiline_comment|/* the chain name */
DECL|member|name
r_char
id|name
(braket
id|EBT_CHAIN_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* counter offset for this chain */
DECL|member|counter_offset
r_int
r_int
id|counter_offset
suffix:semicolon
multiline_comment|/* one standard (accept, drop, return) per hook */
DECL|member|policy
r_int
id|policy
suffix:semicolon
multiline_comment|/* nr. of entries */
DECL|member|nentries
r_int
r_int
id|nentries
suffix:semicolon
multiline_comment|/* entry list */
DECL|member|data
r_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* used for the bitmask of struct ebt_entry */
multiline_comment|/* This is a hack to make a difference between an ebt_entry struct and an&n; * ebt_entries struct when traversing the entries from start to end.&n; * Using this simplifies the code alot, while still being able to use&n; * ebt_entries.&n; * Contrary, iptables doesn&squot;t use something like ebt_entries and therefore uses&n; * different techniques for naming the policy and such. So, iptables doesn&squot;t&n; * need a hack like this.&n; */
DECL|macro|EBT_ENTRY_OR_ENTRIES
mdefine_line|#define EBT_ENTRY_OR_ENTRIES 0x01
multiline_comment|/* these are the normal masks */
DECL|macro|EBT_NOPROTO
mdefine_line|#define EBT_NOPROTO 0x02
DECL|macro|EBT_802_3
mdefine_line|#define EBT_802_3 0x04
DECL|macro|EBT_SOURCEMAC
mdefine_line|#define EBT_SOURCEMAC 0x08
DECL|macro|EBT_DESTMAC
mdefine_line|#define EBT_DESTMAC 0x10
DECL|macro|EBT_F_MASK
mdefine_line|#define EBT_F_MASK (EBT_NOPROTO | EBT_802_3 | EBT_SOURCEMAC | EBT_DESTMAC &bslash;&n;   | EBT_ENTRY_OR_ENTRIES)
DECL|macro|EBT_IPROTO
mdefine_line|#define EBT_IPROTO 0x01
DECL|macro|EBT_IIN
mdefine_line|#define EBT_IIN 0x02
DECL|macro|EBT_IOUT
mdefine_line|#define EBT_IOUT 0x04
DECL|macro|EBT_ISOURCE
mdefine_line|#define EBT_ISOURCE 0x8
DECL|macro|EBT_IDEST
mdefine_line|#define EBT_IDEST 0x10
DECL|macro|EBT_ILOGICALIN
mdefine_line|#define EBT_ILOGICALIN 0x20
DECL|macro|EBT_ILOGICALOUT
mdefine_line|#define EBT_ILOGICALOUT 0x40
DECL|macro|EBT_INV_MASK
mdefine_line|#define EBT_INV_MASK (EBT_IPROTO | EBT_IIN | EBT_IOUT | EBT_ILOGICALIN &bslash;&n;   | EBT_ILOGICALOUT | EBT_ISOURCE | EBT_IDEST)
DECL|struct|ebt_entry_match
r_struct
id|ebt_entry_match
(brace
r_union
(brace
DECL|member|name
r_char
id|name
(braket
id|EBT_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|match
r_struct
id|ebt_match
op_star
id|match
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
multiline_comment|/* size of data */
DECL|member|match_size
r_int
r_int
id|match_size
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
DECL|struct|ebt_entry_watcher
r_struct
id|ebt_entry_watcher
(brace
r_union
(brace
DECL|member|name
r_char
id|name
(braket
id|EBT_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|watcher
r_struct
id|ebt_watcher
op_star
id|watcher
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
multiline_comment|/* size of data */
DECL|member|watcher_size
r_int
r_int
id|watcher_size
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
DECL|struct|ebt_entry_target
r_struct
id|ebt_entry_target
(brace
r_union
(brace
DECL|member|name
r_char
id|name
(braket
id|EBT_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|target
r_struct
id|ebt_target
op_star
id|target
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
multiline_comment|/* size of data */
DECL|member|target_size
r_int
r_int
id|target_size
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
DECL|macro|EBT_STANDARD_TARGET
mdefine_line|#define EBT_STANDARD_TARGET &quot;standard&quot;
DECL|struct|ebt_standard_target
r_struct
id|ebt_standard_target
(brace
DECL|member|target
r_struct
id|ebt_entry_target
id|target
suffix:semicolon
DECL|member|verdict
r_int
id|verdict
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* one entry */
DECL|struct|ebt_entry
r_struct
id|ebt_entry
(brace
multiline_comment|/* this needs to be the first field */
DECL|member|bitmask
r_int
r_int
id|bitmask
suffix:semicolon
DECL|member|invflags
r_int
r_int
id|invflags
suffix:semicolon
DECL|member|ethproto
r_uint16
id|ethproto
suffix:semicolon
multiline_comment|/* the physical in-dev */
DECL|member|in
r_char
id|in
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* the logical in-dev */
DECL|member|logical_in
r_char
id|logical_in
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* the physical out-dev */
DECL|member|out
r_char
id|out
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* the logical out-dev */
DECL|member|logical_out
r_char
id|logical_out
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|sourcemac
r_int
r_char
id|sourcemac
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|sourcemsk
r_int
r_char
id|sourcemsk
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|destmac
r_int
r_char
id|destmac
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|destmsk
r_int
r_char
id|destmsk
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* sizeof ebt_entry + matches */
DECL|member|watchers_offset
r_int
r_int
id|watchers_offset
suffix:semicolon
multiline_comment|/* sizeof ebt_entry + matches + watchers */
DECL|member|target_offset
r_int
r_int
id|target_offset
suffix:semicolon
multiline_comment|/* sizeof ebt_entry + matches + watchers + target */
DECL|member|next_offset
r_int
r_int
id|next_offset
suffix:semicolon
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
DECL|struct|ebt_replace
r_struct
id|ebt_replace
(brace
DECL|member|name
r_char
id|name
(braket
id|EBT_TABLE_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|valid_hooks
r_int
r_int
id|valid_hooks
suffix:semicolon
multiline_comment|/* nr of rules in the table */
DECL|member|nentries
r_int
r_int
id|nentries
suffix:semicolon
multiline_comment|/* total size of the entries */
DECL|member|entries_size
r_int
r_int
id|entries_size
suffix:semicolon
multiline_comment|/* start of the chains */
DECL|member|hook_entry
r_struct
id|ebt_entries
op_star
id|hook_entry
(braket
id|NF_BR_NUMHOOKS
)braket
suffix:semicolon
multiline_comment|/* nr of counters userspace expects back */
DECL|member|num_counters
r_int
r_int
id|num_counters
suffix:semicolon
multiline_comment|/* where the kernel will put the old counters */
DECL|member|counters
r_struct
id|ebt_counter
op_star
id|counters
suffix:semicolon
DECL|member|entries
r_char
op_star
id|entries
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* {g,s}etsockopt numbers */
DECL|macro|EBT_BASE_CTL
mdefine_line|#define EBT_BASE_CTL            128
DECL|macro|EBT_SO_SET_ENTRIES
mdefine_line|#define EBT_SO_SET_ENTRIES      (EBT_BASE_CTL)
DECL|macro|EBT_SO_SET_COUNTERS
mdefine_line|#define EBT_SO_SET_COUNTERS     (EBT_SO_SET_ENTRIES+1)
DECL|macro|EBT_SO_SET_MAX
mdefine_line|#define EBT_SO_SET_MAX          (EBT_SO_SET_COUNTERS+1)
DECL|macro|EBT_SO_GET_INFO
mdefine_line|#define EBT_SO_GET_INFO         (EBT_BASE_CTL)
DECL|macro|EBT_SO_GET_ENTRIES
mdefine_line|#define EBT_SO_GET_ENTRIES      (EBT_SO_GET_INFO+1)
DECL|macro|EBT_SO_GET_INIT_INFO
mdefine_line|#define EBT_SO_GET_INIT_INFO    (EBT_SO_GET_ENTRIES+1)
DECL|macro|EBT_SO_GET_INIT_ENTRIES
mdefine_line|#define EBT_SO_GET_INIT_ENTRIES (EBT_SO_GET_INIT_INFO+1)
DECL|macro|EBT_SO_GET_MAX
mdefine_line|#define EBT_SO_GET_MAX          (EBT_SO_GET_INIT_ENTRIES+1)
macro_line|#ifdef __KERNEL__
multiline_comment|/* return values for match() functions */
DECL|macro|EBT_MATCH
mdefine_line|#define EBT_MATCH 0
DECL|macro|EBT_NOMATCH
mdefine_line|#define EBT_NOMATCH 1
DECL|struct|ebt_match
r_struct
id|ebt_match
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
id|EBT_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* 0 == it matches */
DECL|member|match
r_int
(paren
op_star
id|match
)paren
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
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
id|matchdata
comma
r_int
r_int
id|datalen
)paren
suffix:semicolon
multiline_comment|/* 0 == let it in */
DECL|member|check
r_int
(paren
op_star
id|check
)paren
(paren
r_const
r_char
op_star
id|tablename
comma
r_int
r_int
id|hookmask
comma
r_const
r_struct
id|ebt_entry
op_star
id|e
comma
r_void
op_star
id|matchdata
comma
r_int
r_int
id|datalen
)paren
suffix:semicolon
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_void
op_star
id|matchdata
comma
r_int
r_int
id|datalen
)paren
suffix:semicolon
DECL|member|me
r_struct
id|module
op_star
id|me
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ebt_watcher
r_struct
id|ebt_watcher
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
id|EBT_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|watcher
r_void
(paren
op_star
id|watcher
)paren
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
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
id|watcherdata
comma
r_int
r_int
id|datalen
)paren
suffix:semicolon
multiline_comment|/* 0 == let it in */
DECL|member|check
r_int
(paren
op_star
id|check
)paren
(paren
r_const
r_char
op_star
id|tablename
comma
r_int
r_int
id|hookmask
comma
r_const
r_struct
id|ebt_entry
op_star
id|e
comma
r_void
op_star
id|watcherdata
comma
r_int
r_int
id|datalen
)paren
suffix:semicolon
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_void
op_star
id|watcherdata
comma
r_int
r_int
id|datalen
)paren
suffix:semicolon
DECL|member|me
r_struct
id|module
op_star
id|me
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ebt_target
r_struct
id|ebt_target
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
id|EBT_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* returns one of the standard verdicts */
DECL|member|target
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
id|hooknr
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
id|targetdata
comma
r_int
r_int
id|datalen
)paren
suffix:semicolon
multiline_comment|/* 0 == let it in */
DECL|member|check
r_int
(paren
op_star
id|check
)paren
(paren
r_const
r_char
op_star
id|tablename
comma
r_int
r_int
id|hookmask
comma
r_const
r_struct
id|ebt_entry
op_star
id|e
comma
r_void
op_star
id|targetdata
comma
r_int
r_int
id|datalen
)paren
suffix:semicolon
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_void
op_star
id|targetdata
comma
r_int
r_int
id|datalen
)paren
suffix:semicolon
DECL|member|me
r_struct
id|module
op_star
id|me
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* used for jumping from and into user defined chains (udc) */
DECL|struct|ebt_chainstack
r_struct
id|ebt_chainstack
(brace
DECL|member|chaininfo
r_struct
id|ebt_entries
op_star
id|chaininfo
suffix:semicolon
multiline_comment|/* pointer to chain data */
DECL|member|e
r_struct
id|ebt_entry
op_star
id|e
suffix:semicolon
multiline_comment|/* pointer to entry data */
DECL|member|n
r_int
r_int
id|n
suffix:semicolon
multiline_comment|/* n&squot;th entry */
)brace
suffix:semicolon
DECL|struct|ebt_table_info
r_struct
id|ebt_table_info
(brace
multiline_comment|/* total size of the entries */
DECL|member|entries_size
r_int
r_int
id|entries_size
suffix:semicolon
DECL|member|nentries
r_int
r_int
id|nentries
suffix:semicolon
multiline_comment|/* pointers to the start of the chains */
DECL|member|hook_entry
r_struct
id|ebt_entries
op_star
id|hook_entry
(braket
id|NF_BR_NUMHOOKS
)braket
suffix:semicolon
multiline_comment|/* room to maintain the stack used for jumping from and into udc */
DECL|member|chainstack
r_struct
id|ebt_chainstack
op_star
op_star
id|chainstack
suffix:semicolon
DECL|member|entries
r_char
op_star
id|entries
suffix:semicolon
DECL|member|____cacheline_aligned
r_struct
id|ebt_counter
id|counters
(braket
l_int|0
)braket
id|____cacheline_aligned
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ebt_table
r_struct
id|ebt_table
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|EBT_TABLE_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|table
r_struct
id|ebt_replace
op_star
id|table
suffix:semicolon
DECL|member|valid_hooks
r_int
r_int
id|valid_hooks
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
multiline_comment|/* e.g. could be the table explicitly only allows certain&n;&t; * matches, targets, ... 0 == let it in */
DECL|member|check
r_int
(paren
op_star
id|check
)paren
(paren
r_const
r_struct
id|ebt_table_info
op_star
id|info
comma
r_int
r_int
id|valid_hooks
)paren
suffix:semicolon
multiline_comment|/* the data used by the kernel */
DECL|member|private
r_struct
id|ebt_table_info
op_star
r_private
suffix:semicolon
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
id|ebt_register_table
c_func
(paren
r_struct
id|ebt_table
op_star
id|table
)paren
suffix:semicolon
r_extern
r_void
id|ebt_unregister_table
c_func
(paren
r_struct
id|ebt_table
op_star
id|table
)paren
suffix:semicolon
r_extern
r_int
id|ebt_register_match
c_func
(paren
r_struct
id|ebt_match
op_star
id|match
)paren
suffix:semicolon
r_extern
r_void
id|ebt_unregister_match
c_func
(paren
r_struct
id|ebt_match
op_star
id|match
)paren
suffix:semicolon
r_extern
r_int
id|ebt_register_watcher
c_func
(paren
r_struct
id|ebt_watcher
op_star
id|watcher
)paren
suffix:semicolon
r_extern
r_void
id|ebt_unregister_watcher
c_func
(paren
r_struct
id|ebt_watcher
op_star
id|watcher
)paren
suffix:semicolon
r_extern
r_int
id|ebt_register_target
c_func
(paren
r_struct
id|ebt_target
op_star
id|target
)paren
suffix:semicolon
r_extern
r_void
id|ebt_unregister_target
c_func
(paren
r_struct
id|ebt_target
op_star
id|target
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ebt_do_table
c_func
(paren
r_int
r_int
id|hook
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
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
id|ebt_table
op_star
id|table
)paren
suffix:semicolon
multiline_comment|/* Used in the kernel match() functions */
DECL|macro|FWINV
mdefine_line|#define FWINV(bool,invflg) ((bool) ^ !!(info-&gt;invflags &amp; invflg))
multiline_comment|/* True if the hook mask denotes that the rule is in a base chain,&n; * used in the check() functions */
DECL|macro|BASE_CHAIN
mdefine_line|#define BASE_CHAIN (hookmask &amp; (1 &lt;&lt; NF_BR_NUMHOOKS))
multiline_comment|/* Clear the bit in the hook mask that tells if the rule is on a base chain */
DECL|macro|CLEAR_BASE_CHAIN_BIT
mdefine_line|#define CLEAR_BASE_CHAIN_BIT (hookmask &amp;= ~(1 &lt;&lt; NF_BR_NUMHOOKS))
multiline_comment|/* True if the target is not a standard target */
DECL|macro|INVALID_TARGET
mdefine_line|#define INVALID_TARGET (info-&gt;target &lt; -NUM_STANDARD_TARGETS || info-&gt;target &gt;= 0)
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* blatently stolen from ip_tables.h&n; * fn returns 0 to continue iteration */
DECL|macro|EBT_MATCH_ITERATE
mdefine_line|#define EBT_MATCH_ITERATE(e, fn, args...)                   &bslash;&n;({                                                          &bslash;&n;&t;unsigned int __i;                                   &bslash;&n;&t;int __ret = 0;                                      &bslash;&n;&t;struct ebt_entry_match *__match;                    &bslash;&n;&t;                                                    &bslash;&n;&t;for (__i = sizeof(struct ebt_entry);                &bslash;&n;&t;     __i &lt; (e)-&gt;watchers_offset;                    &bslash;&n;&t;     __i += __match-&gt;match_size +                   &bslash;&n;&t;     sizeof(struct ebt_entry_match)) {              &bslash;&n;&t;&t;__match = (void *)(e) + __i;                &bslash;&n;&t;&t;                                            &bslash;&n;&t;&t;__ret = fn(__match , ## args);              &bslash;&n;&t;&t;if (__ret != 0)                             &bslash;&n;&t;&t;&t;break;                              &bslash;&n;&t;}                                                   &bslash;&n;&t;if (__ret == 0) {                                   &bslash;&n;&t;&t;if (__i != (e)-&gt;watchers_offset)            &bslash;&n;&t;&t;&t;__ret = -EINVAL;                    &bslash;&n;&t;}                                                   &bslash;&n;&t;__ret;                                              &bslash;&n;})
DECL|macro|EBT_WATCHER_ITERATE
mdefine_line|#define EBT_WATCHER_ITERATE(e, fn, args...)                 &bslash;&n;({                                                          &bslash;&n;&t;unsigned int __i;                                   &bslash;&n;&t;int __ret = 0;                                      &bslash;&n;&t;struct ebt_entry_watcher *__watcher;                &bslash;&n;&t;                                                    &bslash;&n;&t;for (__i = e-&gt;watchers_offset;                      &bslash;&n;&t;     __i &lt; (e)-&gt;target_offset;                      &bslash;&n;&t;     __i += __watcher-&gt;watcher_size +               &bslash;&n;&t;     sizeof(struct ebt_entry_watcher)) {            &bslash;&n;&t;&t;__watcher = (void *)(e) + __i;              &bslash;&n;&t;&t;                                            &bslash;&n;&t;&t;__ret = fn(__watcher , ## args);            &bslash;&n;&t;&t;if (__ret != 0)                             &bslash;&n;&t;&t;&t;break;                              &bslash;&n;&t;}                                                   &bslash;&n;&t;if (__ret == 0) {                                   &bslash;&n;&t;&t;if (__i != (e)-&gt;target_offset)              &bslash;&n;&t;&t;&t;__ret = -EINVAL;                    &bslash;&n;&t;}                                                   &bslash;&n;&t;__ret;                                              &bslash;&n;})
DECL|macro|EBT_ENTRY_ITERATE
mdefine_line|#define EBT_ENTRY_ITERATE(entries, size, fn, args...)       &bslash;&n;({                                                          &bslash;&n;&t;unsigned int __i;                                   &bslash;&n;&t;int __ret = 0;                                      &bslash;&n;&t;struct ebt_entry *__entry;                          &bslash;&n;&t;                                                    &bslash;&n;&t;for (__i = 0; __i &lt; (size);) {                      &bslash;&n;&t;&t;__entry = (void *)(entries) + __i;          &bslash;&n;&t;&t;__ret = fn(__entry , ## args);              &bslash;&n;&t;&t;if (__ret != 0)                             &bslash;&n;&t;&t;&t;break;                              &bslash;&n;&t;&t;if (__entry-&gt;bitmask != 0)                  &bslash;&n;&t;&t;&t;__i += __entry-&gt;next_offset;        &bslash;&n;&t;&t;else                                        &bslash;&n;&t;&t;&t;__i += sizeof(struct ebt_entries);  &bslash;&n;&t;}                                                   &bslash;&n;&t;if (__ret == 0) {                                   &bslash;&n;&t;&t;if (__i != (size))                          &bslash;&n;&t;&t;&t;__ret = -EINVAL;                    &bslash;&n;&t;}                                                   &bslash;&n;&t;__ret;                                              &bslash;&n;})
macro_line|#endif
eof
