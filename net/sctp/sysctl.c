multiline_comment|/* SCTP kernel reference Implementation&n; * (C) Copyright IBM Corp. 2002, 2004&n; * Copyright (c) 2002 Intel Corp.&n; *&n; * This file is part of the SCTP kernel reference Implementation&n; *&n; * Sysctl related interfaces for SCTP.&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    Mingqin Liu           &lt;liuming@us.ibm.com&gt;&n; *    Jon Grimm             &lt;jgrimm@us.ibm.com&gt;&n; *    Ardelle Fan           &lt;ardelle.fan@intel.com&gt;&n; *    Ryan Layer            &lt;rmlayer@us.ibm.com&gt;&n; *    Sridhar Samudrala     &lt;sri@us.ibm.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;net/sctp/structs.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
DECL|variable|sctp_sysctl_jiffies_ms
r_static
id|ctl_handler
id|sctp_sysctl_jiffies_ms
suffix:semicolon
DECL|variable|rto_timer_min
r_static
r_int
id|rto_timer_min
op_assign
l_int|1
suffix:semicolon
DECL|variable|rto_timer_max
r_static
r_int
id|rto_timer_max
op_assign
l_int|86400000
suffix:semicolon
multiline_comment|/* One day */
DECL|variable|sctp_table
r_static
id|ctl_table
id|sctp_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|NET_SCTP_RTO_INITIAL
comma
dot
id|procname
op_assign
l_string|&quot;rto_initial&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_rto_initial
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
id|proc_doulongvec_ms_jiffies_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sctp_sysctl_jiffies_ms
comma
dot
id|extra1
op_assign
op_amp
id|rto_timer_min
comma
dot
id|extra2
op_assign
op_amp
id|rto_timer_max
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_SCTP_RTO_MIN
comma
dot
id|procname
op_assign
l_string|&quot;rto_min&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_rto_min
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
id|proc_doulongvec_ms_jiffies_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sctp_sysctl_jiffies_ms
comma
dot
id|extra1
op_assign
op_amp
id|rto_timer_min
comma
dot
id|extra2
op_assign
op_amp
id|rto_timer_max
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_SCTP_RTO_MAX
comma
dot
id|procname
op_assign
l_string|&quot;rto_max&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_rto_max
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
id|proc_doulongvec_ms_jiffies_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sctp_sysctl_jiffies_ms
comma
dot
id|extra1
op_assign
op_amp
id|rto_timer_min
comma
dot
id|extra2
op_assign
op_amp
id|rto_timer_max
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_SCTP_VALID_COOKIE_LIFE
comma
dot
id|procname
op_assign
l_string|&quot;valid_cookie_life&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_valid_cookie_life
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
id|proc_doulongvec_ms_jiffies_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sctp_sysctl_jiffies_ms
comma
dot
id|extra1
op_assign
op_amp
id|rto_timer_min
comma
dot
id|extra2
op_assign
op_amp
id|rto_timer_max
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_SCTP_MAX_BURST
comma
dot
id|procname
op_assign
l_string|&quot;max_burst&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_max_burst
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
id|NET_SCTP_ASSOCIATION_MAX_RETRANS
comma
dot
id|procname
op_assign
l_string|&quot;association_max_retrans&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_max_retrans_association
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
id|NET_SCTP_PATH_MAX_RETRANS
comma
dot
id|procname
op_assign
l_string|&quot;path_max_retrans&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_max_retrans_path
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
id|NET_SCTP_MAX_INIT_RETRANSMITS
comma
dot
id|procname
op_assign
l_string|&quot;max_init_retransmits&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_max_retrans_init
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
id|NET_SCTP_HB_INTERVAL
comma
dot
id|procname
op_assign
l_string|&quot;hb_interval&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_hb_interval
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
id|proc_doulongvec_ms_jiffies_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sctp_sysctl_jiffies_ms
comma
dot
id|extra1
op_assign
op_amp
id|rto_timer_min
comma
dot
id|extra2
op_assign
op_amp
id|rto_timer_max
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_SCTP_PRESERVE_ENABLE
comma
dot
id|procname
op_assign
l_string|&quot;cookie_preserve_enable&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_cookie_preserve_enable
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
id|proc_doulongvec_ms_jiffies_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sctp_sysctl_jiffies_ms
comma
dot
id|extra1
op_assign
op_amp
id|rto_timer_min
comma
dot
id|extra2
op_assign
op_amp
id|rto_timer_max
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_SCTP_RTO_ALPHA
comma
dot
id|procname
op_assign
l_string|&quot;rto_alpha_exp_divisor&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_rto_alpha
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
id|NET_SCTP_RTO_BETA
comma
dot
id|procname
op_assign
l_string|&quot;rto_beta_exp_divisor&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_rto_beta
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
id|NET_SCTP_ADDIP_ENABLE
comma
dot
id|procname
op_assign
l_string|&quot;addip_enable&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_addip_enable
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
id|NET_SCTP_PRSCTP_ENABLE
comma
dot
id|procname
op_assign
l_string|&quot;prsctp_enable&quot;
comma
dot
id|data
op_assign
op_amp
id|sctp_prsctp_enable
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
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|sctp_net_table
r_static
id|ctl_table
id|sctp_net_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|NET_SCTP
comma
dot
id|procname
op_assign
l_string|&quot;sctp&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|sctp_table
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|sctp_root_table
r_static
id|ctl_table
id|sctp_root_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|CTL_NET
comma
dot
id|procname
op_assign
l_string|&quot;net&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|sctp_net_table
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|sctp_sysctl_header
r_static
r_struct
id|ctl_table_header
op_star
id|sctp_sysctl_header
suffix:semicolon
multiline_comment|/* Sysctl registration.  */
DECL|function|sctp_sysctl_register
r_void
id|sctp_sysctl_register
c_func
(paren
r_void
)paren
(brace
id|sctp_sysctl_header
op_assign
id|register_sysctl_table
c_func
(paren
id|sctp_root_table
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Sysctl deregistration.  */
DECL|function|sctp_sysctl_unregister
r_void
id|sctp_sysctl_unregister
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|sctp_sysctl_header
)paren
suffix:semicolon
)brace
multiline_comment|/* Strategy function to convert jiffies to milliseconds.  */
DECL|function|sctp_sysctl_jiffies_ms
r_static
r_int
id|sctp_sysctl_jiffies_ms
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
id|__user
op_star
id|name
comma
r_int
id|nlen
comma
r_void
id|__user
op_star
id|oldval
comma
r_int
id|__user
op_star
id|oldlenp
comma
r_void
id|__user
op_star
id|newval
comma
r_int
id|newlen
comma
r_void
op_star
op_star
id|context
)paren
(brace
r_if
c_cond
(paren
id|oldval
)paren
(brace
r_int
id|olen
suffix:semicolon
r_if
c_cond
(paren
id|oldlenp
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|olen
comma
id|oldlenp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|olen
op_ne
r_sizeof
(paren
r_int
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
(paren
op_star
(paren
r_int
op_star
)paren
(paren
id|table-&gt;data
)paren
op_star
l_int|1000
)paren
op_div
id|HZ
comma
(paren
r_int
id|__user
op_star
)paren
id|oldval
)paren
op_logical_or
(paren
id|oldlenp
op_logical_and
id|put_user
c_func
(paren
r_sizeof
(paren
r_int
)paren
comma
id|oldlenp
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|newval
op_logical_and
id|newlen
)paren
(brace
r_int
r_new
suffix:semicolon
r_if
c_cond
(paren
id|newlen
op_ne
r_sizeof
(paren
r_int
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
r_new
comma
(paren
r_int
id|__user
op_star
)paren
id|newval
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
(paren
id|table-&gt;data
)paren
op_assign
(paren
r_new
op_star
id|HZ
)paren
op_div
l_int|1000
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
eof
