multiline_comment|/* -*- linux-c -*-&n; * sysctl_net_core.c: sysctl interface to net core subsystem.&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/core directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SYSCTL
r_extern
r_int
id|netdev_max_backlog
suffix:semicolon
r_extern
r_int
id|weight_p
suffix:semicolon
r_extern
r_int
id|no_cong_thresh
suffix:semicolon
r_extern
r_int
id|no_cong
suffix:semicolon
r_extern
r_int
id|lo_cong
suffix:semicolon
r_extern
r_int
id|mod_cong
suffix:semicolon
r_extern
r_int
id|netdev_fastroute
suffix:semicolon
r_extern
r_int
id|net_msg_cost
suffix:semicolon
r_extern
r_int
id|net_msg_burst
suffix:semicolon
r_extern
id|__u32
id|sysctl_wmem_max
suffix:semicolon
r_extern
id|__u32
id|sysctl_rmem_max
suffix:semicolon
r_extern
id|__u32
id|sysctl_wmem_default
suffix:semicolon
r_extern
id|__u32
id|sysctl_rmem_default
suffix:semicolon
r_extern
r_int
id|sysctl_core_destroy_delay
suffix:semicolon
r_extern
r_int
id|sysctl_optmem_max
suffix:semicolon
r_extern
r_int
id|sysctl_hot_list_len
suffix:semicolon
macro_line|#ifdef CONFIG_NET_DIVERT
r_extern
r_char
id|sysctl_divert_version
(braket
)braket
suffix:semicolon
macro_line|#endif /* CONFIG_NET_DIVERT */
DECL|variable|core_table
id|ctl_table
id|core_table
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_NET
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_WMEM_MAX
comma
dot
id|procname
op_assign
l_string|&quot;wmem_max&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_wmem_max
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_RMEM_MAX
comma
dot
id|procname
op_assign
l_string|&quot;rmem_max&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_rmem_max
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_WMEM_DEFAULT
comma
dot
id|procname
op_assign
l_string|&quot;wmem_default&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_wmem_default
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_RMEM_DEFAULT
comma
dot
id|procname
op_assign
l_string|&quot;rmem_default&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_rmem_default
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_DEV_WEIGHT
comma
dot
id|procname
op_assign
l_string|&quot;dev_weight&quot;
comma
dot
id|data
op_assign
op_amp
id|weight_p
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_MAX_BACKLOG
comma
dot
id|procname
op_assign
l_string|&quot;netdev_max_backlog&quot;
comma
dot
id|data
op_assign
op_amp
id|netdev_max_backlog
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_NO_CONG_THRESH
comma
dot
id|procname
op_assign
l_string|&quot;no_cong_thresh&quot;
comma
dot
id|data
op_assign
op_amp
id|no_cong
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_NO_CONG
comma
dot
id|procname
op_assign
l_string|&quot;no_cong&quot;
comma
dot
id|data
op_assign
op_amp
id|no_cong
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_LO_CONG
comma
dot
id|procname
op_assign
l_string|&quot;lo_cong&quot;
comma
dot
id|data
op_assign
op_amp
id|lo_cong
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_MOD_CONG
comma
dot
id|procname
op_assign
l_string|&quot;mod_cong&quot;
comma
dot
id|data
op_assign
op_amp
id|mod_cong
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
macro_line|#ifdef CONFIG_NET_FASTROUTE
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_FASTROUTE
comma
dot
id|procname
op_assign
l_string|&quot;netdev_fastroute&quot;
comma
dot
id|data
op_assign
op_amp
id|netdev_fastroute
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
macro_line|#endif
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_MSG_COST
comma
dot
id|procname
op_assign
l_string|&quot;message_cost&quot;
comma
dot
id|data
op_assign
op_amp
id|net_msg_cost
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_MSG_BURST
comma
dot
id|procname
op_assign
l_string|&quot;message_burst&quot;
comma
dot
id|data
op_assign
op_amp
id|net_msg_burst
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_OPTMEM_MAX
comma
dot
id|procname
op_assign
l_string|&quot;optmem_max&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_optmem_max
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_HOT_LIST_LENGTH
comma
dot
id|procname
op_assign
l_string|&quot;hot_list_length&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_hot_list_len
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
macro_line|#ifdef CONFIG_NET_DIVERT
(brace
dot
id|ctl_name
op_assign
id|NET_CORE_DIVERT_VERSION
comma
dot
id|procname
op_assign
l_string|&quot;divert_version&quot;
comma
dot
id|data
op_assign
(paren
r_void
op_star
)paren
id|sysctl_divert_version
comma
dot
id|maxlen
op_assign
l_int|32
comma
dot
id|mode
op_assign
l_int|0444
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dostring
)brace
comma
macro_line|#endif /* CONFIG_NET_DIVERT */
macro_line|#endif /* CONFIG_NET */
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#endif
eof
