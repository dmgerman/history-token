macro_line|#ifndef __NET_PKT_ACT_H
DECL|macro|__NET_PKT_ACT_H
mdefine_line|#define __NET_PKT_ACT_H
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
DECL|macro|tca_st
mdefine_line|#define tca_st(val) (struct tcf_##val *)
DECL|macro|PRIV
mdefine_line|#define PRIV(a,name) ( tca_st(name) (a)-&gt;priv)
macro_line|#if 0 /* control */
mdefine_line|#define DPRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...)
macro_line|#endif
macro_line|#if 0 /* data */
mdefine_line|#define D2PRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|D2PRINTK
mdefine_line|#define D2PRINTK(format,args...)
macro_line|#endif
r_static
id|__inline__
r_int
DECL|function|tcf_hash
id|tcf_hash
c_func
(paren
id|u32
id|index
)paren
(brace
r_return
id|index
op_amp
id|MY_TAB_MASK
suffix:semicolon
)brace
multiline_comment|/* probably move this from being inline&n; * and put into act_generic&n;*/
r_static
r_inline
r_void
DECL|function|tcf_hash_destroy
id|tcf_hash_destroy
c_func
(paren
r_struct
id|tcf_st
op_star
id|p
)paren
(brace
r_int
id|h
op_assign
id|tcf_hash
c_func
(paren
id|p-&gt;index
)paren
suffix:semicolon
r_struct
id|tcf_st
op_star
op_star
id|p1p
suffix:semicolon
r_for
c_loop
(paren
id|p1p
op_assign
op_amp
id|tcf_ht
(braket
id|h
)braket
suffix:semicolon
op_star
id|p1p
suffix:semicolon
id|p1p
op_assign
op_amp
(paren
op_star
id|p1p
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_if
c_cond
(paren
op_star
id|p1p
op_eq
id|p
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|tcf_t_lock
)paren
suffix:semicolon
op_star
id|p1p
op_assign
id|p-&gt;next
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|tcf_t_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_ESTIMATOR
id|qdisc_kill_estimator
c_func
(paren
op_amp
id|p-&gt;stats
)paren
suffix:semicolon
macro_line|#endif
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|BUG_TRAP
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|tcf_hash_release
id|tcf_hash_release
c_func
(paren
r_struct
id|tcf_st
op_star
id|p
comma
r_int
id|bind
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|bind
)paren
(brace
id|p-&gt;bindcnt
op_decrement
suffix:semicolon
)brace
id|p-&gt;refcnt
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;bindcnt
op_le
l_int|0
op_logical_and
id|p-&gt;refcnt
op_le
l_int|0
)paren
(brace
id|tcf_hash_destroy
c_func
(paren
id|p
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
id|__inline__
r_int
DECL|function|tcf_dump_walker
id|tcf_dump_walker
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
comma
r_struct
id|tc_action
op_star
id|a
)paren
(brace
r_struct
id|tcf_st
op_star
id|p
suffix:semicolon
r_int
id|err
op_assign
l_int|0
comma
id|index
op_assign
op_minus
l_int|1
comma
id|i
op_assign
l_int|0
comma
id|s_i
op_assign
l_int|0
comma
id|n_i
op_assign
l_int|0
suffix:semicolon
r_struct
id|rtattr
op_star
id|r
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tcf_t_lock
)paren
suffix:semicolon
id|s_i
op_assign
id|cb-&gt;args
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MY_TAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
id|tcf_ht
(braket
id|tcf_hash
c_func
(paren
id|i
)paren
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
id|index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
id|s_i
)paren
r_continue
suffix:semicolon
id|a-&gt;priv
op_assign
id|p
suffix:semicolon
id|a-&gt;order
op_assign
id|n_i
suffix:semicolon
id|r
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|skb-&gt;tail
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|a-&gt;order
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|err
op_assign
id|tcf_action_dump_1
c_func
(paren
id|skb
comma
id|a
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OG
id|err
)paren
(brace
id|index
op_decrement
suffix:semicolon
id|skb_trim
c_func
(paren
id|skb
comma
(paren
id|u8
op_star
)paren
id|r
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|r-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
(paren
id|u8
op_star
)paren
id|r
suffix:semicolon
id|n_i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|n_i
op_ge
id|TCA_ACT_MAX_PRIO
)paren
(brace
r_goto
id|done
suffix:semicolon
)brace
)brace
)brace
id|done
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|tcf_t_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n_i
)paren
id|cb-&gt;args
(braket
l_int|0
)braket
op_add_assign
id|n_i
suffix:semicolon
r_return
id|n_i
suffix:semicolon
id|rtattr_failure
suffix:colon
id|skb_trim
c_func
(paren
id|skb
comma
(paren
id|u8
op_star
)paren
id|r
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_static
id|__inline__
r_int
DECL|function|tcf_del_walker
id|tcf_del_walker
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tc_action
op_star
id|a
)paren
(brace
r_struct
id|tcf_st
op_star
id|p
comma
op_star
id|s_p
suffix:semicolon
r_struct
id|rtattr
op_star
id|r
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|n_i
op_assign
l_int|0
suffix:semicolon
id|r
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|skb-&gt;tail
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|a-&gt;order
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_KIND
comma
id|IFNAMSIZ
comma
id|a-&gt;ops-&gt;kind
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MY_TAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
id|tcf_ht
(braket
id|tcf_hash
c_func
(paren
id|i
)paren
)braket
suffix:semicolon
r_while
c_loop
(paren
id|p
op_ne
l_int|NULL
)paren
(brace
id|s_p
op_assign
id|p-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|ACT_P_DELETED
op_eq
id|tcf_hash_release
c_func
(paren
id|p
comma
l_int|0
)paren
)paren
(brace
id|module_put
c_func
(paren
id|a-&gt;ops-&gt;owner
)paren
suffix:semicolon
)brace
id|n_i
op_increment
suffix:semicolon
id|p
op_assign
id|s_p
suffix:semicolon
)brace
)brace
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_FCNT
comma
l_int|4
comma
op_amp
id|n_i
)paren
suffix:semicolon
id|r-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
(paren
id|u8
op_star
)paren
id|r
suffix:semicolon
r_return
id|n_i
suffix:semicolon
id|rtattr_failure
suffix:colon
id|skb_trim
c_func
(paren
id|skb
comma
(paren
id|u8
op_star
)paren
id|r
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
id|__inline__
r_int
DECL|function|tcf_generic_walker
id|tcf_generic_walker
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
comma
r_int
id|type
comma
r_struct
id|tc_action
op_star
id|a
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|RTM_DELACTION
)paren
(brace
r_return
id|tcf_del_walker
c_func
(paren
id|skb
comma
id|a
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|RTM_GETACTION
)paren
(brace
r_return
id|tcf_dump_walker
c_func
(paren
id|skb
comma
id|cb
comma
id|a
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;tcf_generic_walker: unknown action %d&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_static
id|__inline__
r_struct
id|tcf_st
op_star
DECL|function|tcf_hash_lookup
id|tcf_hash_lookup
c_func
(paren
id|u32
id|index
)paren
(brace
r_struct
id|tcf_st
op_star
id|p
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tcf_t_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|tcf_ht
(braket
id|tcf_hash
c_func
(paren
id|index
)paren
)braket
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;index
op_eq
id|index
)paren
r_break
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|tcf_t_lock
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_static
id|__inline__
id|u32
DECL|function|tcf_hash_new_index
id|tcf_hash_new_index
c_func
(paren
r_void
)paren
(brace
r_do
(brace
r_if
c_cond
(paren
op_increment
id|idx_gen
op_eq
l_int|0
)paren
id|idx_gen
op_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|tcf_hash_lookup
c_func
(paren
id|idx_gen
)paren
)paren
suffix:semicolon
r_return
id|idx_gen
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|tcf_hash_search
id|tcf_hash_search
c_func
(paren
r_struct
id|tc_action
op_star
id|a
comma
id|u32
id|index
)paren
(brace
r_struct
id|tcf_st
op_star
id|p
op_assign
id|tcf_hash_lookup
c_func
(paren
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
l_int|NULL
)paren
(brace
id|a-&gt;priv
op_assign
id|p
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NET_ACT_INIT
r_static
r_inline
r_struct
id|tcf_st
op_star
DECL|function|tcf_hash_check
id|tcf_hash_check
c_func
(paren
r_struct
id|tc_st
op_star
id|parm
comma
r_struct
id|tc_action
op_star
id|a
comma
r_int
id|ovr
comma
r_int
id|bind
)paren
(brace
r_struct
id|tcf_st
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|parm-&gt;index
op_logical_and
(paren
id|p
op_assign
id|tcf_hash_lookup
c_func
(paren
id|parm-&gt;index
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bind
)paren
(brace
id|p-&gt;bindcnt
op_increment
suffix:semicolon
id|p-&gt;refcnt
op_increment
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
id|a-&gt;priv
op_assign
(paren
r_void
op_star
)paren
id|p
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|tcf_st
op_star
DECL|function|tcf_hash_create
id|tcf_hash_create
c_func
(paren
r_struct
id|tc_st
op_star
id|parm
comma
r_struct
id|rtattr
op_star
id|est
comma
r_struct
id|tc_action
op_star
id|a
comma
r_int
id|size
comma
r_int
id|ovr
comma
r_int
id|bind
)paren
(brace
r_int
id|h
suffix:semicolon
r_struct
id|tcf_st
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
id|p
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
id|p
suffix:semicolon
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|p-&gt;refcnt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bind
)paren
(brace
id|p-&gt;bindcnt
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_lock_init
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
id|p-&gt;stats_lock
op_assign
op_amp
id|p-&gt;lock
suffix:semicolon
id|p-&gt;index
op_assign
id|parm-&gt;index
ques
c_cond
suffix:colon
id|tcf_hash_new_index
c_func
(paren
)paren
suffix:semicolon
id|p-&gt;tm.install
op_assign
id|jiffies
suffix:semicolon
id|p-&gt;tm.lastuse
op_assign
id|jiffies
suffix:semicolon
macro_line|#ifdef CONFIG_NET_ESTIMATOR
r_if
c_cond
(paren
id|est
)paren
(brace
id|qdisc_new_estimator
c_func
(paren
op_amp
id|p-&gt;stats
comma
id|p-&gt;stats_lock
comma
id|est
)paren
suffix:semicolon
)brace
macro_line|#endif
id|h
op_assign
id|tcf_hash
c_func
(paren
id|p-&gt;index
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|tcf_t_lock
)paren
suffix:semicolon
id|p-&gt;next
op_assign
id|tcf_ht
(braket
id|h
)braket
suffix:semicolon
id|tcf_ht
(braket
id|h
)braket
op_assign
id|p
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|tcf_t_lock
)paren
suffix:semicolon
id|a-&gt;priv
op_assign
(paren
r_void
op_star
)paren
id|p
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|tcf_st
op_star
DECL|function|tcf_hash_init
id|tcf_hash_init
c_func
(paren
r_struct
id|tc_st
op_star
id|parm
comma
r_struct
id|rtattr
op_star
id|est
comma
r_struct
id|tc_action
op_star
id|a
comma
r_int
id|size
comma
r_int
id|ovr
comma
r_int
id|bind
)paren
(brace
r_struct
id|tcf_st
op_star
id|p
op_assign
id|tcf_hash_check
(paren
id|parm
comma
id|a
comma
id|ovr
comma
id|bind
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|p
op_assign
id|tcf_hash_create
c_func
(paren
id|parm
comma
id|est
comma
id|a
comma
id|size
comma
id|ovr
comma
id|bind
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
