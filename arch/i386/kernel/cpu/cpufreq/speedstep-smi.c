multiline_comment|/*&n; * Intel SpeedStep SMI driver.&n; *&n; * (C) 2003  Hiroshi Miura &lt;miura@da-cha.org&gt;&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *&n; */
multiline_comment|/*********************************************************************&n; *                        SPEEDSTEP - DEFINITIONS                    *&n; *********************************************************************/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &lt;linux/moduleparam.h&gt; 
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/ist.h&gt;
macro_line|#include &quot;speedstep-lib.h&quot;
DECL|macro|PFX
mdefine_line|#define PFX &quot;speedstep-smi: &quot;
multiline_comment|/* speedstep system management interface port/command.&n; *&n; * These parameters are got from IST-SMI BIOS call.&n; * If user gives it, these are used.&n; * &n; */
DECL|variable|smi_port
r_static
r_int
id|smi_port
op_assign
l_int|0
suffix:semicolon
DECL|variable|smi_cmd
r_static
r_int
id|smi_cmd
op_assign
l_int|0
suffix:semicolon
DECL|variable|smi_sig
r_static
r_int
r_int
id|smi_sig
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n; *   There are only two frequency states for each processor. Values&n; * are in kHz for the time being.&n; */
DECL|variable|speedstep_freqs
r_static
r_struct
id|cpufreq_frequency_table
id|speedstep_freqs
(braket
)braket
op_assign
(brace
(brace
id|SPEEDSTEP_HIGH
comma
l_int|0
)brace
comma
(brace
id|SPEEDSTEP_LOW
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
id|CPUFREQ_TABLE_END
)brace
comma
)brace
suffix:semicolon
DECL|macro|GET_SPEEDSTEP_OWNER
mdefine_line|#define GET_SPEEDSTEP_OWNER 0
DECL|macro|GET_SPEEDSTEP_STATE
mdefine_line|#define GET_SPEEDSTEP_STATE 1
DECL|macro|SET_SPEEDSTEP_STATE
mdefine_line|#define SET_SPEEDSTEP_STATE 2
DECL|macro|GET_SPEEDSTEP_FREQS
mdefine_line|#define GET_SPEEDSTEP_FREQS 4
multiline_comment|/* how often shall the SMI call be tried if it failed, e.g. because&n; * of DMA activity going on? */
DECL|macro|SMI_TRIES
mdefine_line|#define SMI_TRIES 5
multiline_comment|/* DEBUG&n; *   Define it if you want verbose debug output, e.g. for bug reporting&n; */
singleline_comment|//#define SPEEDSTEP_DEBUG
macro_line|#ifdef SPEEDSTEP_DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) printk(msg)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) do { } while(0)
macro_line|#endif
multiline_comment|/**&n; * speedstep_smi_ownership&n; */
DECL|function|speedstep_smi_ownership
r_static
r_int
id|speedstep_smi_ownership
(paren
r_void
)paren
(brace
id|u32
id|command
comma
id|result
comma
id|magic
suffix:semicolon
id|u32
id|function
op_assign
id|GET_SPEEDSTEP_OWNER
suffix:semicolon
r_int
r_char
id|magic_data
(braket
)braket
op_assign
l_string|&quot;Copyright (c) 1999 Intel Corporation&quot;
suffix:semicolon
id|command
op_assign
(paren
id|smi_sig
op_amp
l_int|0xffffff00
)paren
op_or
(paren
id|smi_cmd
op_amp
l_int|0xff
)paren
suffix:semicolon
id|magic
op_assign
id|virt_to_phys
c_func
(paren
id|magic_data
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;out %%al, (%%dx)&bslash;n&quot;
suffix:colon
l_string|&quot;=D&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|command
)paren
comma
l_string|&quot;b&quot;
(paren
id|function
)paren
comma
l_string|&quot;c&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;d&quot;
(paren
id|smi_port
)paren
comma
l_string|&quot;D&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;S&quot;
(paren
id|magic
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_smi_get_freqs - get SpeedStep preferred &amp; current freq.&n; * @low: the low frequency value is placed here&n; * @high: the high frequency value is placed here&n; *&n; * Only available on later SpeedStep-enabled systems, returns false results or&n; * even hangs [cf. bugme.osdl.org # 1422] on earlier systems. Empirical testing&n; * shows that the latter occurs if !(ist_info.event &amp; 0xFFFF).&n; */
DECL|function|speedstep_smi_get_freqs
r_static
r_int
id|speedstep_smi_get_freqs
(paren
r_int
r_int
op_star
id|low
comma
r_int
r_int
op_star
id|high
)paren
(brace
id|u32
id|command
comma
id|result
comma
id|edi
comma
id|high_mhz
comma
id|low_mhz
suffix:semicolon
id|u32
id|state
op_assign
l_int|0
suffix:semicolon
id|u32
id|function
op_assign
id|GET_SPEEDSTEP_FREQS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ist_info.event
op_amp
l_int|0xFFFF
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|command
op_assign
(paren
id|smi_sig
op_amp
l_int|0xffffff00
)paren
op_or
(paren
id|smi_cmd
op_amp
l_int|0xff
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movl $0, %%edi&bslash;n&quot;
l_string|&quot;out %%al, (%%dx)&bslash;n&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|result
)paren
comma
l_string|&quot;=b&quot;
(paren
id|high_mhz
)paren
comma
l_string|&quot;=c&quot;
(paren
id|low_mhz
)paren
comma
l_string|&quot;=d&quot;
(paren
id|state
)paren
comma
l_string|&quot;=D&quot;
(paren
id|edi
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|command
)paren
comma
l_string|&quot;b&quot;
(paren
id|function
)paren
comma
l_string|&quot;c&quot;
(paren
id|state
)paren
comma
l_string|&quot;d&quot;
(paren
id|smi_port
)paren
comma
l_string|&quot;S&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
op_star
id|high
op_assign
id|high_mhz
op_star
l_int|1000
suffix:semicolon
op_star
id|low
op_assign
id|low_mhz
op_star
l_int|1000
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_get_state - set the SpeedStep state&n; * @state: processor frequency state (SPEEDSTEP_LOW or SPEEDSTEP_HIGH)&n; *&n; */
DECL|function|speedstep_get_state
r_static
r_int
id|speedstep_get_state
(paren
r_void
)paren
(brace
id|u32
id|function
op_assign
id|GET_SPEEDSTEP_STATE
suffix:semicolon
id|u32
id|result
comma
id|state
comma
id|edi
comma
id|command
suffix:semicolon
id|command
op_assign
(paren
id|smi_sig
op_amp
l_int|0xffffff00
)paren
op_or
(paren
id|smi_cmd
op_amp
l_int|0xff
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movl $0, %%edi&bslash;n&quot;
l_string|&quot;out %%al, (%%dx)&bslash;n&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|result
)paren
comma
l_string|&quot;=b&quot;
(paren
id|state
)paren
comma
l_string|&quot;=D&quot;
(paren
id|edi
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|command
)paren
comma
l_string|&quot;b&quot;
(paren
id|function
)paren
comma
l_string|&quot;c&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;d&quot;
(paren
id|smi_port
)paren
comma
l_string|&quot;S&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|state
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_set_state - set the SpeedStep state&n; * @state: new processor frequency state (SPEEDSTEP_LOW or SPEEDSTEP_HIGH)&n; * @notify: whether to call cpufreq_notify_transition&n; *&n; */
DECL|function|speedstep_set_state
r_static
r_void
id|speedstep_set_state
(paren
r_int
r_int
id|state
comma
r_int
r_int
id|notify
)paren
(brace
r_int
r_int
id|old_state
comma
id|result
op_assign
l_int|0
comma
id|command
comma
id|new_state
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
r_int
r_int
id|function
op_assign
id|SET_SPEEDSTEP_STATE
suffix:semicolon
r_int
r_int
id|retry
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|state
OG
l_int|0x1
)paren
r_return
suffix:semicolon
id|old_state
op_assign
id|speedstep_get_state
c_func
(paren
)paren
suffix:semicolon
id|freqs.old
op_assign
id|speedstep_freqs
(braket
id|old_state
)braket
dot
id|frequency
suffix:semicolon
id|freqs
dot
r_new
op_assign
id|speedstep_freqs
(braket
id|state
)braket
dot
id|frequency
suffix:semicolon
id|freqs.cpu
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* speedstep.c is UP only driver */
r_if
c_cond
(paren
id|old_state
op_eq
id|state
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|notify
)paren
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
multiline_comment|/* Disable IRQs */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|command
op_assign
(paren
id|smi_sig
op_amp
l_int|0xffffff00
)paren
op_or
(paren
id|smi_cmd
op_amp
l_int|0xff
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|retry
)paren
(brace
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: retry %u, previous result %u&bslash;n&quot;
comma
id|retry
comma
id|result
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|retry
op_star
l_int|50
)paren
suffix:semicolon
)brace
id|retry
op_increment
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movl $0, %%edi&bslash;n&quot;
l_string|&quot;out %%al, (%%dx)&bslash;n&quot;
suffix:colon
l_string|&quot;=b&quot;
(paren
id|new_state
)paren
comma
l_string|&quot;=D&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|command
)paren
comma
l_string|&quot;b&quot;
(paren
id|function
)paren
comma
l_string|&quot;c&quot;
(paren
id|state
)paren
comma
l_string|&quot;d&quot;
(paren
id|smi_port
)paren
comma
l_string|&quot;S&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|new_state
op_ne
id|state
)paren
op_logical_and
(paren
id|retry
op_le
id|SMI_TRIES
)paren
)paren
suffix:semicolon
multiline_comment|/* enable IRQs */
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_state
op_eq
id|state
)paren
(brace
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: change to %u MHz succeeded after %u tries with result %u&bslash;n&quot;
comma
(paren
id|freqs
dot
r_new
op_div
l_int|1000
)paren
comma
id|retry
comma
id|result
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpufreq: change failed with new_state %u and result %u&bslash;n&quot;
comma
id|new_state
comma
id|result
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|notify
)paren
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_POSTCHANGE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_target - set a new CPUFreq policy&n; * @policy: new policy&n; * @target_freq: new freq&n; * @relation: &n; *&n; * Sets a new CPUFreq policy/freq.&n; */
DECL|function|speedstep_target
r_static
r_int
id|speedstep_target
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_int
r_int
id|target_freq
comma
r_int
r_int
id|relation
)paren
(brace
r_int
r_int
id|newstate
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cpufreq_frequency_table_target
c_func
(paren
id|policy
comma
op_amp
id|speedstep_freqs
(braket
l_int|0
)braket
comma
id|target_freq
comma
id|relation
comma
op_amp
id|newstate
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|speedstep_set_state
c_func
(paren
id|newstate
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_verify - verifies a new CPUFreq policy&n; * @policy: new policy&n; *&n; * Limit must be within speedstep_low_freq and speedstep_high_freq, with&n; * at least one border included.&n; */
DECL|function|speedstep_verify
r_static
r_int
id|speedstep_verify
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_return
id|cpufreq_frequency_table_verify
c_func
(paren
id|policy
comma
op_amp
id|speedstep_freqs
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
DECL|function|speedstep_cpu_init
r_static
r_int
id|speedstep_cpu_init
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
id|result
suffix:semicolon
r_int
r_int
id|speed
comma
id|state
suffix:semicolon
multiline_comment|/* capability check */
r_if
c_cond
(paren
id|policy-&gt;cpu
op_ne
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|result
op_assign
id|speedstep_smi_ownership
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: fails an aquiring ownership of a SMI interface.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* detect low and high frequency */
id|result
op_assign
id|speedstep_smi_get_freqs
c_func
(paren
op_amp
id|speedstep_freqs
(braket
id|SPEEDSTEP_LOW
)braket
dot
id|frequency
comma
op_amp
id|speedstep_freqs
(braket
id|SPEEDSTEP_HIGH
)braket
dot
id|frequency
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
multiline_comment|/* fall back to speedstep_lib.c dection mechanism: try both states out */
r_int
r_int
id|speedstep_processor
op_assign
id|speedstep_detect_processor
c_func
(paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;could not detect low and high frequencies by SMI call.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|speedstep_processor
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|result
op_assign
id|speedstep_get_freqs
c_func
(paren
id|speedstep_processor
comma
op_amp
id|speedstep_freqs
(braket
id|SPEEDSTEP_LOW
)braket
dot
id|frequency
comma
op_amp
id|speedstep_freqs
(braket
id|SPEEDSTEP_HIGH
)braket
dot
id|frequency
comma
op_amp
id|speedstep_set_state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|dprintk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;could not detect two different speeds -- aborting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_else
id|dprintk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;workaround worked.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* get current speed setting */
id|state
op_assign
id|speedstep_get_state
c_func
(paren
)paren
suffix:semicolon
id|speed
op_assign
id|speedstep_freqs
(braket
id|state
)braket
dot
id|frequency
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: currently at %s speed setting - %i MHz&bslash;n&quot;
comma
(paren
id|speed
op_eq
id|speedstep_freqs
(braket
id|SPEEDSTEP_LOW
)braket
dot
id|frequency
)paren
ques
c_cond
l_string|&quot;low&quot;
suffix:colon
l_string|&quot;high&quot;
comma
(paren
id|speed
op_div
l_int|1000
)paren
)paren
suffix:semicolon
multiline_comment|/* cpuinfo and default policy values */
id|policy-&gt;governor
op_assign
id|CPUFREQ_DEFAULT_GOVERNOR
suffix:semicolon
id|policy-&gt;cpuinfo.transition_latency
op_assign
id|CPUFREQ_ETERNAL
suffix:semicolon
id|policy-&gt;cur
op_assign
id|speed
suffix:semicolon
id|result
op_assign
id|cpufreq_frequency_table_cpuinfo
c_func
(paren
id|policy
comma
id|speedstep_freqs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
(paren
id|result
)paren
suffix:semicolon
id|cpufreq_frequency_table_get_attr
c_func
(paren
id|speedstep_freqs
comma
id|policy-&gt;cpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|speedstep_cpu_exit
r_static
r_int
id|speedstep_cpu_exit
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
id|cpufreq_frequency_table_put_attr
c_func
(paren
id|policy-&gt;cpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|speedstep_resume
r_static
r_int
id|speedstep_resume
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
id|result
op_assign
id|speedstep_smi_ownership
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: fails an aquiring ownership of a SMI interface.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|variable|speedstep_attr
r_static
r_struct
id|freq_attr
op_star
id|speedstep_attr
(braket
)braket
op_assign
(brace
op_amp
id|cpufreq_freq_attr_scaling_available_freqs
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|speedstep_driver
r_static
r_struct
id|cpufreq_driver
id|speedstep_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;speedstep-smi&quot;
comma
dot
id|verify
op_assign
id|speedstep_verify
comma
dot
id|target
op_assign
id|speedstep_target
comma
dot
id|init
op_assign
id|speedstep_cpu_init
comma
dot
m_exit
op_assign
id|speedstep_cpu_exit
comma
dot
id|resume
op_assign
id|speedstep_resume
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|attr
op_assign
id|speedstep_attr
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * speedstep_init - initializes the SpeedStep CPUFreq driver&n; *&n; *   Initializes the SpeedStep support. Returns -ENODEV on unsupported&n; * BIOS, -EINVAL on problems during initiatization, and zero on&n; * success.&n; */
DECL|function|speedstep_init
r_static
r_int
id|__init
id|speedstep_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
id|cpu_data
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86_vendor
op_ne
id|X86_VENDOR_INTEL
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;No Intel CPU detected.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|dprintk
c_func
(paren
id|KERN_DEBUG
id|PFX
l_string|&quot;signature:0x%.8lx, command:0x%.8lx, event:0x%.8lx, perf_level:0x%.8lx.&bslash;n&quot;
comma
id|ist_info.signature
comma
id|ist_info.command
comma
id|ist_info.event
comma
id|ist_info.perf_level
)paren
suffix:semicolon
multiline_comment|/* Error if no IST-SMI BIOS or no PARM &n;&t;&t; sig= &squot;ISGE&squot; aka &squot;Intel Speedstep Gate E&squot; */
r_if
c_cond
(paren
(paren
id|ist_info.signature
op_ne
l_int|0x47534943
)paren
op_logical_and
(paren
(paren
id|smi_port
op_eq
l_int|0
)paren
op_logical_or
(paren
id|smi_cmd
op_eq
l_int|0
)paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|smi_sig
op_eq
l_int|1
)paren
id|smi_sig
op_assign
l_int|0x47534943
suffix:semicolon
r_else
id|smi_sig
op_assign
id|ist_info.signature
suffix:semicolon
multiline_comment|/* setup smi_port from MODLULE_PARM or BIOS */
r_if
c_cond
(paren
(paren
id|smi_port
OG
l_int|0xff
)paren
op_logical_or
(paren
id|smi_port
OL
l_int|0
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|smi_port
op_eq
l_int|0
)paren
(brace
id|smi_port
op_assign
id|ist_info.command
op_amp
l_int|0xff
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|smi_cmd
OG
l_int|0xff
)paren
op_logical_or
(paren
id|smi_cmd
OL
l_int|0
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|smi_cmd
op_eq
l_int|0
)paren
(brace
id|smi_cmd
op_assign
(paren
id|ist_info.command
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
r_return
id|cpufreq_register_driver
c_func
(paren
op_amp
id|speedstep_driver
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_exit - unregisters SpeedStep support&n; *&n; *   Unregisters SpeedStep support.&n; */
DECL|function|speedstep_exit
r_static
r_void
id|__exit
id|speedstep_exit
c_func
(paren
r_void
)paren
(brace
id|cpufreq_unregister_driver
c_func
(paren
op_amp
id|speedstep_driver
)paren
suffix:semicolon
)brace
id|module_param
c_func
(paren
id|smi_port
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|smi_cmd
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|smi_sig
comma
id|uint
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|smi_port
comma
l_string|&quot;Override the BIOS-given IST port with this value -- Intel&squot;s default setting is 0xb2&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|smi_cmd
comma
l_string|&quot;Override the BIOS-given IST command with this value -- Intel&squot;s default setting is 0x82&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|smi_sig
comma
l_string|&quot;Set to 1 to fake the IST signature when using the SMI interface.&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
(paren
l_string|&quot;Hiroshi Miura&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;Speedstep driver for IST applet SMI interface.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|speedstep_init
id|module_init
c_func
(paren
id|speedstep_init
)paren
suffix:semicolon
DECL|variable|speedstep_exit
id|module_exit
c_func
(paren
id|speedstep_exit
)paren
suffix:semicolon
eof
