multiline_comment|/*&n; * System Abstraction Layer (SAL) interface routines.&n; *&n; * Copyright (C) 1998, 1999, 2001, 2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 VA Linux Systems&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/pal.h&gt;
DECL|variable|__cacheline_aligned
id|spinlock_t
id|sal_lock
id|__cacheline_aligned
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|sal_platform_features
r_int
r_int
id|sal_platform_features
suffix:semicolon
r_static
r_struct
(brace
DECL|member|addr
r_void
op_star
id|addr
suffix:semicolon
multiline_comment|/* function entry point */
DECL|member|gpval
r_void
op_star
id|gpval
suffix:semicolon
multiline_comment|/* gp value to use */
DECL|variable|pdesc
)brace
id|pdesc
suffix:semicolon
r_static
r_int
DECL|function|default_handler
id|default_handler
(paren
r_void
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|ia64_sal
id|ia64_sal_handler
id|ia64_sal
op_assign
(paren
id|ia64_sal_handler
)paren
id|default_handler
suffix:semicolon
DECL|variable|ia64_ptc_domain_info
id|ia64_sal_desc_ptc_t
op_star
id|ia64_ptc_domain_info
suffix:semicolon
r_const
r_char
op_star
DECL|function|ia64_sal_strerror
id|ia64_sal_strerror
(paren
r_int
id|status
)paren
(brace
r_const
r_char
op_star
id|str
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
l_int|0
suffix:colon
id|str
op_assign
l_string|&quot;Call completed without error&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|str
op_assign
l_string|&quot;Effect a warm boot of the system to complete &quot;
l_string|&quot;the update&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|1
suffix:colon
id|str
op_assign
l_string|&quot;Not implemented&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|2
suffix:colon
id|str
op_assign
l_string|&quot;Invalid argument&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|3
suffix:colon
id|str
op_assign
l_string|&quot;Call completed with error&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|4
suffix:colon
id|str
op_assign
l_string|&quot;Virtual address not registered&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|5
suffix:colon
id|str
op_assign
l_string|&quot;No information available&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|6
suffix:colon
id|str
op_assign
l_string|&quot;Insufficient space to add the entry&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|7
suffix:colon
id|str
op_assign
l_string|&quot;Invalid entry_addr value&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|8
suffix:colon
id|str
op_assign
l_string|&quot;Invalid interrupt vector&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|9
suffix:colon
id|str
op_assign
l_string|&quot;Requested memory not available&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|10
suffix:colon
id|str
op_assign
l_string|&quot;Unable to write to the NVM device&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|11
suffix:colon
id|str
op_assign
l_string|&quot;Invalid partition type specified&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|12
suffix:colon
id|str
op_assign
l_string|&quot;Invalid NVM_Object id specified&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|13
suffix:colon
id|str
op_assign
l_string|&quot;NVM_Object already has the maximum number &quot;
l_string|&quot;of partitions&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|14
suffix:colon
id|str
op_assign
l_string|&quot;Insufficient space in partition for the &quot;
l_string|&quot;requested write sub-function&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|15
suffix:colon
id|str
op_assign
l_string|&quot;Insufficient data buffer space for the &quot;
l_string|&quot;requested read record sub-function&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|16
suffix:colon
id|str
op_assign
l_string|&quot;Scratch buffer required for the write/delete &quot;
l_string|&quot;sub-function&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|17
suffix:colon
id|str
op_assign
l_string|&quot;Insufficient space in the NVM_Object for the &quot;
l_string|&quot;requested create sub-function&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|18
suffix:colon
id|str
op_assign
l_string|&quot;Invalid value specified in the partition_rec &quot;
l_string|&quot;argument&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|19
suffix:colon
id|str
op_assign
l_string|&quot;Record oriented I/O not supported for this &quot;
l_string|&quot;partition&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|20
suffix:colon
id|str
op_assign
l_string|&quot;Bad format of record to be written or &quot;
l_string|&quot;required keyword variable not &quot;
l_string|&quot;specified&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|str
op_assign
l_string|&quot;Unknown SAL status code&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|str
suffix:semicolon
)brace
r_void
id|__init
DECL|function|ia64_sal_handler_init
id|ia64_sal_handler_init
(paren
r_void
op_star
id|entry_point
comma
r_void
op_star
id|gpval
)paren
(brace
multiline_comment|/* fill in the SAL procedure descriptor and point ia64_sal to it: */
id|pdesc.addr
op_assign
id|entry_point
suffix:semicolon
id|pdesc.gpval
op_assign
id|gpval
suffix:semicolon
id|ia64_sal
op_assign
(paren
id|ia64_sal_handler
)paren
op_amp
id|pdesc
suffix:semicolon
)brace
r_void
id|__init
DECL|function|ia64_sal_init
id|ia64_sal_init
(paren
r_struct
id|ia64_sal_systab
op_star
id|systab
)paren
(brace
r_int
r_int
id|min
comma
id|max
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_struct
id|ia64_sal_desc_entry_point
op_star
id|ep
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|systab
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Hmm, no SAL System Table.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|systab-&gt;signature
comma
l_string|&quot;SST_&quot;
comma
l_int|4
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bad signature in system table!&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * revisions are coded in BCD, so %x does the job for us&n;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SAL v%x.%02x: oem=%.32s, product=%.32s&bslash;n&quot;
comma
id|systab-&gt;sal_rev_major
comma
id|systab-&gt;sal_rev_minor
comma
id|systab-&gt;oem_id
comma
id|systab-&gt;product_id
)paren
suffix:semicolon
id|min
op_assign
op_complement
l_int|0UL
suffix:semicolon
id|max
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
id|systab
op_plus
l_int|1
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
id|systab-&gt;entry_count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t; * The first byte of each entry type contains the type desciptor.&n;&t;&t; */
r_switch
c_cond
(paren
op_star
id|p
)paren
(brace
r_case
id|SAL_DESC_ENTRY_POINT
suffix:colon
id|ep
op_assign
(paren
r_struct
id|ia64_sal_desc_entry_point
op_star
)paren
id|p
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SAL: entry: pal_proc=0x%lx, sal_proc=0x%lx&bslash;n&quot;
comma
id|ep-&gt;pal_proc
comma
id|ep-&gt;sal_proc
)paren
suffix:semicolon
id|ia64_pal_handler_init
c_func
(paren
id|__va
c_func
(paren
id|ep-&gt;pal_proc
)paren
)paren
suffix:semicolon
id|ia64_sal_handler_init
c_func
(paren
id|__va
c_func
(paren
id|ep-&gt;sal_proc
)paren
comma
id|__va
c_func
(paren
id|ep-&gt;gp
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAL_DESC_PTC
suffix:colon
id|ia64_ptc_domain_info
op_assign
(paren
id|ia64_sal_desc_ptc_t
op_star
)paren
id|p
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAL_DESC_AP_WAKEUP
suffix:colon
macro_line|#ifdef CONFIG_SMP
(brace
r_struct
id|ia64_sal_desc_ap_wakeup
op_star
id|ap
op_assign
(paren
r_void
op_star
)paren
id|p
suffix:semicolon
r_switch
c_cond
(paren
id|ap-&gt;mechanism
)paren
(brace
r_case
id|IA64_SAL_AP_EXTERNAL_INT
suffix:colon
id|ap_wakeup_vector
op_assign
id|ap-&gt;vector
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SAL: AP wakeup using external interrupt &quot;
l_string|&quot;vector 0x%lx&bslash;n&quot;
comma
id|ap_wakeup_vector
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SAL: AP wakeup mechanism unsupported!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
macro_line|#endif
r_case
id|SAL_DESC_PLATFORM_FEATURE
suffix:colon
(brace
r_struct
id|ia64_sal_desc_platform_feature
op_star
id|pf
op_assign
(paren
r_void
op_star
)paren
id|p
suffix:semicolon
id|sal_platform_features
op_assign
id|pf-&gt;feature_mask
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SAL: Platform features &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pf-&gt;feature_mask
op_amp
id|IA64_SAL_PLATFORM_FEATURE_BUS_LOCK
)paren
id|printk
c_func
(paren
l_string|&quot;BusLock &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pf-&gt;feature_mask
op_amp
id|IA64_SAL_PLATFORM_FEATURE_IRQ_REDIR_HINT
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;IRQ_Redirection &quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|no_int_routing
)paren
id|smp_int_redirect
op_and_assign
op_complement
id|SMP_IRQ_REDIRECTION
suffix:semicolon
r_else
id|smp_int_redirect
op_or_assign
id|SMP_IRQ_REDIRECTION
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|pf-&gt;feature_mask
op_amp
id|IA64_SAL_PLATFORM_FEATURE_IPI_REDIR_HINT
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;IPI_Redirection &quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|no_int_routing
)paren
id|smp_int_redirect
op_and_assign
op_complement
id|SMP_IPI_REDIRECTION
suffix:semicolon
r_else
id|smp_int_redirect
op_or_assign
id|SMP_IPI_REDIRECTION
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|pf-&gt;feature_mask
op_amp
id|IA64_SAL_PLATFORM_FEATURE_ITC_DRIFT
)paren
id|printk
c_func
(paren
l_string|&quot;ITC_Drift &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|p
op_add_assign
id|SAL_DESC_SIZE
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
)brace
)brace
eof
