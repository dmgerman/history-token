multiline_comment|/*&n; *  drivers/s390/s390mach.c&n; *   S/390 machine check handler&n; *&n; *  S390 version&n; *    Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; *&t;&t; Martin Schwidefsky (schwidefsky@de.ibm.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#include &quot;s390mach.h&quot;
DECL|macro|DBG
mdefine_line|#define DBG printk
singleline_comment|// #define DBG(args,...) do {} while (0);
r_extern
r_void
id|css_process_crw
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|chsc_process_crw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|chp_process_crw
c_func
(paren
r_int
)paren
suffix:semicolon
r_static
r_void
DECL|function|s390_handle_damage
id|s390_handle_damage
c_func
(paren
r_char
op_star
id|msg
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;%s&bslash;n&quot;
comma
id|msg
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_send_stop
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|disabled_wait
c_func
(paren
(paren
r_int
r_int
)paren
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Retrieve CRWs and call function to handle event.&n; *&n; * Note : we currently process CRWs for io and chsc subchannels only&n; */
r_static
r_void
DECL|function|s390_collect_crw_info
id|s390_collect_crw_info
c_func
(paren
r_void
)paren
(brace
r_struct
id|crw
id|crw
suffix:semicolon
r_int
id|ccode
suffix:semicolon
r_do
(brace
id|ccode
op_assign
id|stcrw
c_func
(paren
op_amp
id|crw
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccode
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;crw_info : CRW reports slct=%d, oflw=%d, &quot;
l_string|&quot;chn=%d, rsc=%X, anc=%d, erc=%X, rsid=%X&bslash;n&quot;
comma
id|crw.slct
comma
id|crw.oflw
comma
id|crw.chn
comma
id|crw.rsc
comma
id|crw.anc
comma
id|crw.erc
comma
id|crw.rsid
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|crw.rsc
)paren
(brace
r_case
id|CRW_RSC_SCH
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;source is subchannel %04X&bslash;n&quot;
comma
id|crw.rsid
)paren
suffix:semicolon
id|css_process_crw
(paren
id|crw.rsid
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CRW_RSC_MONITOR
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;source is monitoring facility&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CRW_RSC_CPATH
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;source is channel path %02X&bslash;n&quot;
comma
id|crw.rsid
)paren
suffix:semicolon
id|chp_process_crw
c_func
(paren
id|crw.rsid
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CRW_RSC_CONFIG
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;source is configuration-alert facility&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CRW_RSC_CSS
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;source is channel subsystem&bslash;n&quot;
)paren
suffix:semicolon
id|chsc_process_crw
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;unknown source&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|crw.chn
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * machine check handler.&n; */
r_void
DECL|function|s390_do_machine_check
id|s390_do_machine_check
c_func
(paren
r_void
)paren
(brace
r_struct
id|mci
op_star
id|mci
suffix:semicolon
id|mci
op_assign
(paren
r_struct
id|mci
op_star
)paren
op_amp
id|S390_lowcore.mcck_interruption_code
suffix:semicolon
r_if
c_cond
(paren
id|mci-&gt;sd
)paren
multiline_comment|/* system damage */
id|s390_handle_damage
c_func
(paren
l_string|&quot;received system damage machine check&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mci-&gt;pd
)paren
multiline_comment|/* instruction processing damage */
id|s390_handle_damage
c_func
(paren
l_string|&quot;received instruction processing &quot;
l_string|&quot;damage machine check&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mci-&gt;se
)paren
multiline_comment|/* storage error uncorrected */
id|s390_handle_damage
c_func
(paren
l_string|&quot;received storage error uncorrected &quot;
l_string|&quot;machine check&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mci-&gt;sc
)paren
multiline_comment|/* storage error corrected */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;received storage error corrected machine check&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mci-&gt;ke
)paren
multiline_comment|/* storage key-error uncorrected */
id|s390_handle_damage
c_func
(paren
l_string|&quot;received storage key-error uncorrected &quot;
l_string|&quot;machine check&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mci-&gt;ds
op_logical_and
id|mci-&gt;fa
)paren
multiline_comment|/* storage degradation */
id|s390_handle_damage
c_func
(paren
l_string|&quot;received storage degradation machine &quot;
l_string|&quot;check&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mci-&gt;cp
)paren
multiline_comment|/* channel report word pending */
id|s390_collect_crw_info
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MACHCHK_WARNING
multiline_comment|/*&n; * The warning may remain for a prolonged period on the bare iron.&n; * (actually till the machine is powered off, or until the problem is gone)&n; * So we just stop listening for the WARNING MCH and prevent continuously&n; * being interrupted.  One caveat is however, that we must do this per&n; * processor and cannot use the smp version of ctl_clear_bit().&n; * On VM we only get one interrupt per virtally presented machinecheck.&n; * Though one suffices, we may get one interrupt per (virtual) processor.&n; */
r_if
c_cond
(paren
id|mci-&gt;w
)paren
(brace
multiline_comment|/* WARNING pending ? */
r_static
r_int
id|mchchk_wng_posted
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Use single machine clear, as we cannot handle smp right now&n;&t;&t; */
id|__ctl_clear_bit
c_func
(paren
l_int|14
comma
l_int|24
)paren
suffix:semicolon
multiline_comment|/* Disable WARNING MCH */
r_if
c_cond
(paren
id|xchg
c_func
(paren
op_amp
id|mchchk_wng_posted
comma
l_int|1
)paren
op_eq
l_int|0
)paren
id|kill_proc
c_func
(paren
l_int|1
comma
id|SIGPWR
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/*&n; * s390_init_machine_check&n; *&n; * initialize machine check handling&n; */
r_static
r_int
DECL|function|machine_check_init
id|machine_check_init
c_func
(paren
r_void
)paren
(brace
id|ctl_clear_bit
c_func
(paren
l_int|14
comma
l_int|25
)paren
suffix:semicolon
multiline_comment|/* disable damage MCH */
id|ctl_set_bit
c_func
(paren
l_int|14
comma
l_int|26
)paren
suffix:semicolon
multiline_comment|/* enable degradation MCH */
id|ctl_set_bit
c_func
(paren
l_int|14
comma
l_int|27
)paren
suffix:semicolon
multiline_comment|/* enable system recovery MCH */
macro_line|#ifdef CONFIG_MACHCHK_WARNING
id|ctl_set_bit
c_func
(paren
l_int|14
comma
l_int|24
)paren
suffix:semicolon
multiline_comment|/* enable warning MCH */
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the machine check handler really early to be able to&n; * catch all machine checks that happen during boot&n; */
DECL|variable|machine_check_init
id|arch_initcall
c_func
(paren
id|machine_check_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Machine checks for the channel subsystem must be enabled&n; * after the channel subsystem is initialized&n; */
r_static
r_int
id|__init
DECL|function|machine_check_crw_init
id|machine_check_crw_init
(paren
r_void
)paren
(brace
id|ctl_set_bit
c_func
(paren
l_int|14
comma
l_int|28
)paren
suffix:semicolon
multiline_comment|/* enable channel report MCH */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|machine_check_crw_init
id|device_initcall
(paren
id|machine_check_crw_init
)paren
suffix:semicolon
eof
