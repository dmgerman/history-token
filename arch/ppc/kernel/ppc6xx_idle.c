multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * power_save() rountine for classic PPC CPUs.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/stringify.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
DECL|variable|powersave_nap
r_int
r_int
id|powersave_nap
op_assign
l_int|0
suffix:semicolon
DECL|macro|DSSALL
mdefine_line|#define DSSALL&t;&t;.long&t;(0x1f&lt;&lt;26)+(0x10&lt;&lt;21)+(0x336&lt;&lt;1)
r_void
DECL|function|ppc6xx_idle
id|ppc6xx_idle
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|hid0
suffix:semicolon
r_int
id|nap
op_assign
id|powersave_nap
suffix:semicolon
multiline_comment|/* 7450 has no DOZE mode mode, we return if powersave_nap&n;&t; * isn&squot;t enabled&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|nap
op_logical_or
(paren
id|cur_cpu_spec
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_member_access_from_pointer
id|cpu_features
op_amp
id|CPU_FTR_CAN_DOZE
)paren
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Disable interrupts to prevent a lost wakeup&n;&t; * when going to sleep.  This is necessary even with&n;&t; * RTLinux since we are not guaranteed an interrupt&n;&t; * didn&squot;t come in and is waiting for a __sti() before&n;&t; * emulating one.  This way, we really do hard disable.&n;&t; *&n;&t; * We assume that we&squot;re sti-ed when we come in here.  We&n;&t; * are in the idle loop so if we&squot;re cli-ed then it&squot;s a bug&n;&t; * anyway.&n;&t; *  -- Cort&n;&t; */
id|_nmask_and_or_msr
c_func
(paren
id|MSR_EE
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mfspr %0,1008&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|hid0
)paren
suffix:colon
)paren
suffix:semicolon
id|hid0
op_and_assign
op_complement
(paren
id|HID0_NAP
op_or
id|HID0_SLEEP
op_or
id|HID0_DOZE
)paren
suffix:semicolon
id|hid0
op_or_assign
(paren
id|powersave_nap
ques
c_cond
id|HID0_NAP
suffix:colon
id|HID0_DOZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cur_cpu_spec
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_member_access_from_pointer
id|cpu_features
op_amp
id|CPU_FTR_NO_DPM
)paren
)paren
id|hid0
op_or_assign
id|HID0_DPM
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mtspr 1008,%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|hid0
)paren
)paren
suffix:semicolon
multiline_comment|/* Flush pending data streams, consider this instruction&n;&t;&t; * exist on all altivec capable CPUs&n;&t;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;98:&t;&quot;
id|__stringify
c_func
(paren
id|DSSALL
)paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;sync&bslash;n&quot;
l_string|&quot;99:&bslash;n&quot;
l_string|&quot;.section __ftr_fixup,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.long %0&bslash;n&quot;
l_string|&quot;&t;.long %1&bslash;n&quot;
l_string|&quot;&t;.long 98b&bslash;n&quot;
l_string|&quot;&t;.long 99b&bslash;n&quot;
l_string|&quot;.previous&quot;
op_scope_resolution
l_string|&quot;i&quot;
(paren
id|CPU_FTR_ALTIVEC
)paren
comma
l_string|&quot;i&quot;
(paren
id|CPU_FTR_ALTIVEC
)paren
)paren
suffix:semicolon
multiline_comment|/* set the POW bit in the MSR, and enable interrupts&n;&t;&t; * so we wake up sometime! */
id|_nmask_and_or_msr
c_func
(paren
l_int|0
comma
id|MSR_POW
op_or
id|MSR_EE
)paren
suffix:semicolon
)brace
id|_nmask_and_or_msr
c_func
(paren
l_int|0
comma
id|MSR_EE
)paren
suffix:semicolon
)brace
eof
