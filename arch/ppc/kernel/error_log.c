multiline_comment|/*&n; * BK Id: SCCS/s.error_log.c 1.6 05/17/01 18:14:21 cort&n; */
multiline_comment|/*&n; *  arch/ppc/kernel/error_log.c&n; *  &n; *  Copyright (c) 2000 Tilmann Bitterberg&n; *  (tilmann@bitterberg.de)&n; *&n; *  Error processing of errors found by rtas even-scan routine&n; *  which is done with every heartbeat. (chrp_setup.c)&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &quot;error_log.h&quot;
multiline_comment|/* ****************************************************************** */
multiline_comment|/* &n; * EVENT-SCAN&n; * The whole stuff below here doesn&squot;t take any action when it found&n; * an error, it just prints as much information as possible and &n; * then its up to the user to decide what to do.&n; *&n; * Returns 0 if no errors were found&n; * Returns 1 if there may be more errors&n; */
DECL|function|ppc_rtas_errorlog_scan
r_int
id|ppc_rtas_errorlog_scan
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|_errlog_severity
(braket
)braket
op_assign
(brace
macro_line|#ifdef VERBOSE_ERRORS
l_string|&quot;No Error&bslash;n&bslash;t&bslash;&n;Should require no further information&quot;
comma
l_string|&quot;Event&bslash;n&bslash;t&bslash;&n;This is not really an error, it is an event. I use events&bslash;n&bslash;t&bslash;&n;to communicate with RTAS back and forth.&quot;
comma
l_string|&quot;Warning&bslash;n&bslash;t&bslash;&n;Indicates a non-state-losing error, either fully recovered&bslash;n&bslash;t&bslash;&n;by RTAS or not needing recovery. Ignore it.&quot;
comma
l_string|&quot;Error sync&bslash;n&bslash;t&bslash;&n;May only be fatal to a certain program or thread. Recovery&bslash;n&bslash;t&bslash;&n;and continuation is possible, if I only had a handler for&bslash;n&bslash;t&bslash;&n;this. Less serious&quot;
comma
l_string|&quot;Error&bslash;n&bslash;t&bslash;&n;Less serious, but still causing a loss of data and state.&bslash;n&bslash;t&bslash;&n;I can&squot;t tell you exactly what to do, You have to decide&bslash;n&bslash;t&bslash;&n;with help from the target and initiator field, what kind&bslash;n&bslash;t&bslash;&n;of further actions may take place.&quot;
comma
l_string|&quot;Fatal&bslash;n&bslash;t&bslash;&n;Represent a permanent hardware failure and I believe this&bslash;n&bslash;t&bslash;&n;affects my overall performance and behaviour. I would not&bslash;n&bslash;t&bslash;&n;attempt to continue normal operation.&quot;
macro_line|#else
l_string|&quot;No Error&quot;
comma
l_string|&quot;Event&quot;
comma
l_string|&quot;Warning&quot;
comma
l_string|&quot;Error sync&quot;
comma
l_string|&quot;Error&quot;
comma
l_string|&quot;Fatal&quot;
macro_line|#endif /* VERBOSE_ERRORS */
)brace
suffix:semicolon
macro_line|#if 0 /* unused?? */
r_const
r_char
op_star
id|_errlog_disposition
(braket
)braket
op_assign
(brace
macro_line|#ifdef VERBOSE_ERRORS
l_string|&quot;Fully recovered&bslash;n&bslash;t&bslash;&n;There was an error, but it is fully recovered by RTAS.&quot;
comma
l_string|&quot;Limited recovery&bslash;n&bslash;t&bslash;&n;RTAS was able to recover the state of the machine, but some&bslash;n&bslash;t&bslash;&n;feature of the machine has been disabled or lost (for example&bslash;n&bslash;t&bslash;&n;error checking) or performance may suffer.&quot;
comma
l_string|&quot;Not recovered&bslash;n&bslash;t&bslash;&n;Whether RTAS did not try to recover anything or recovery failed:&bslash;n&bslash;t&bslash;&n;HOUSTON, WE HAVE A PROBLEM!&quot;
macro_line|#else
l_string|&quot;Fully recovered&quot;
comma
l_string|&quot;Limited recovery&quot;
comma
l_string|&quot;Not recovered&quot;
macro_line|#endif /* VERBOSE_ERRORS */
)brace
suffix:semicolon
macro_line|#endif
r_const
r_char
op_star
id|_errlog_extended
(braket
)braket
op_assign
(brace
macro_line|#ifdef VERBOSE_ERRORS
l_string|&quot;Not present&bslash;n&bslash;t&bslash;&n;Sad, the RTAS call didn&squot;t return an extended error log.&quot;
comma
l_string|&quot;Present&bslash;n&bslash;t&bslash;&n;The extended log is present and hopefully it contains a lot of&bslash;n&bslash;t&bslash;&n;useful information, which leads to the solution of the problem.&quot;
macro_line|#else
l_string|&quot;Not present&quot;
comma
l_string|&quot;Present&quot;
macro_line|#endif /* VERBOSE_ERRORS */
)brace
suffix:semicolon
r_const
r_char
op_star
id|_errlog_initiator
(braket
)braket
op_assign
(brace
l_string|&quot;Unknown or not applicable&quot;
comma
l_string|&quot;CPU&quot;
comma
l_string|&quot;PCI&quot;
comma
l_string|&quot;ISA&quot;
comma
l_string|&quot;Memory&quot;
comma
l_string|&quot;Power management&quot;
)brace
suffix:semicolon
r_const
r_char
op_star
id|_errlog_target
(braket
)braket
op_assign
(brace
l_string|&quot;Unknown or not applicable&quot;
comma
l_string|&quot;CPU&quot;
comma
l_string|&quot;PCI&quot;
comma
l_string|&quot;ISA&quot;
comma
l_string|&quot;Memory&quot;
comma
l_string|&quot;Power management&quot;
)brace
suffix:semicolon
id|rtas_error_log
id|error_log
suffix:semicolon
r_char
id|logdata
(braket
l_int|1024
)braket
suffix:semicolon
r_int
id|error
suffix:semicolon
macro_line|#if 0 /* unused?? */
r_int
id|retries
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* if HW error, try 10 times */
macro_line|#endif
id|error
op_assign
id|call_rtas
(paren
l_string|&quot;event-scan&quot;
comma
l_int|4
comma
l_int|1
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|error_log
comma
id|INTERNAL_ERROR
op_or
id|EPOW_WARNING
comma
l_int|0
comma
id|__pa
c_func
(paren
id|logdata
)paren
comma
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|1
)paren
multiline_comment|/* no errors found */
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to get errors. Do you a favor and throw this box away&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error_log.version
op_ne
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Unknown version (%d), please implement me&bslash;n&quot;
comma
id|error_log.version
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|error_log.disposition
)paren
(brace
r_case
id|DISP_FULLY_RECOVERED
suffix:colon
multiline_comment|/* there was an error, but everything is fine now */
r_return
l_int|0
suffix:semicolon
r_case
id|DISP_NOT_RECOVERED
suffix:colon
id|printk
c_func
(paren
l_string|&quot;We have a really serious Problem!&bslash;n&quot;
)paren
suffix:semicolon
r_case
id|DISP_LIMITED_RECOVERY
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Error classification&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Severity  : %s&bslash;n&quot;
comma
id|ppc_rtas_errorlog_check_severity
(paren
id|error_log
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Initiator : %s&bslash;n&quot;
comma
id|ppc_rtas_errorlog_check_initiator
(paren
id|error_log
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Target    : %s&bslash;n&quot;
comma
id|ppc_rtas_errorlog_check_target
(paren
id|error_log
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Type      : %s&bslash;n&quot;
comma
id|ppc_rtas_errorlog_check_type
(paren
id|error_log
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Ext. log  : %s&bslash;n&quot;
comma
id|ppc_rtas_errorlog_check_extended
(paren
id|error_log
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error_log.extended
)paren
id|ppc_rtas_errorlog_disect_extended
(paren
id|logdata
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* nothing */
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ****************************************************************** */
DECL|function|ppc_rtas_errorlog_check_type
r_const
r_char
op_star
id|ppc_rtas_errorlog_check_type
(paren
id|rtas_error_log
id|error_log
)paren
(brace
r_const
r_char
op_star
id|_errlog_type
(braket
)braket
op_assign
(brace
l_string|&quot;unknown type&quot;
comma
l_string|&quot;too many tries failed&quot;
comma
l_string|&quot;TCE error&quot;
comma
l_string|&quot;RTAS device failed&quot;
comma
l_string|&quot;target timed out&quot;
comma
l_string|&quot;parity error on data&quot;
comma
multiline_comment|/* 5 */
l_string|&quot;parity error on address&quot;
comma
l_string|&quot;parity error on external cache&quot;
comma
l_string|&quot;access to invalid address&quot;
comma
l_string|&quot;uncorrectable ECC error&quot;
comma
l_string|&quot;corrected ECC error&quot;
multiline_comment|/* 10 */
)brace
suffix:semicolon
r_if
c_cond
(paren
id|error_log.type
op_eq
id|TYPE_EPOW
)paren
r_return
l_string|&quot;EPOW&quot;
suffix:semicolon
r_if
c_cond
(paren
id|error_log.type
op_ge
id|TYPE_PMGM_POWER_SW_ON
)paren
r_return
l_string|&quot;PowerMGM Event (not handled right now)&quot;
suffix:semicolon
r_return
id|_errlog_type
(braket
id|error_log.type
)braket
suffix:semicolon
)brace
eof
