multiline_comment|/*&n; *&t;Cyrix MediaGX and NatSemi Geode Suspend Modulation&n; *&t;(C) 2002 Zwane Mwaikambo &lt;zwane@commfireservices.com&gt;&n; *&t;(C) 2002 Hiroshi Miura   &lt;miura@da-cha.org&gt;&n; *&t;All Rights Reserved&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      version 2 as published by the Free Software Foundation &n; *&n; *      The author(s) of this software shall not be held liable for damages&n; *      of any nature resulting due to the use of this software. This&n; *      software is provided AS-IS with no warranties.&n; *&t;&n; * Theoritical note:&n; *&n; *&t;(see Geode(tm) CS5530 manual (rev.4.1) page.56)&n; *&n; *&t;CPU frequency control on NatSemi Geode GX1/GXLV processor and CS55x0&n; *&t;are based on Suspend Moduration.&n; *&n; *&t;Suspend Modulation works by asserting and de-asserting the SUSP# pin&n; *&t;to CPU(GX1/GXLV) for configurable durations. When asserting SUSP#&n; *&t;the CPU enters an idle state. GX1 stops its core clock when SUSP# is &n; *&t;asserted then power consumption is reduced.&n; *&n; *&t;Suspend Modulation&squot;s OFF/ON duration are configurable &n; *&t;with &squot;Suspend Modulation OFF Count Register&squot;&n; *&t;and &squot;Suspend Modulation ON Count Register&squot;.&n; *&t;These registers are 8bit counters that represent the number of &n; *&t;32us intervals which the SUSP# pin is asserted(ON)/de-asserted(OFF)&n; *&t;to the processor.&n; *&n; *&t;These counters define a ratio which is the effective frequency &n; * &t;of operation of the system.&n; *&n; *&t;&t;&t;       OFF Count&n; *&t;F_eff = Fgx * ----------------------&n; *&t;                OFF Count + ON Count&n; *&n; *&t;0 &lt;= On Count, Off Count &lt;= 255&n; *&n; *&t;From these limits, we can get register values &n; *&n; *&t;off_duration + on_duration &lt;= MAX_DURATION&n; *&t;on_duration = off_duration * (stock_freq - freq) / freq&n; *&n; *      off_duration  =  (freq * DURATION) / stock_freq &n; *      on_duration = DURATION - off_duration &n; *&n; *&n; *---------------------------------------------------------------------------&n; *&n; * ChangeLog:&n; *  &t;Dec. 12, 2003&t;Hiroshi Miura &lt;miura@da-cha.org&gt;&n; *  &t;&t;- fix on/off register mistake&n; *  &t;&t;- fix cpu_khz calc when it stops cpu modulation.&n; *&n; *&t;Dec. 11, 2002 &t;Hiroshi Miura &lt;miura@da-cha.org&gt;&n; *&t;&t;- rewrite for Cyrix MediaGX Cx5510/5520 and &n; *&t;&t;  NatSemi Geode Cs5530(A).&n; *&n; *&t;Jul. ??, 2002  Zwane Mwaikambo &lt;zwane@commfireservices.com&gt;&n; *&t;&t;- cs5530_mod patch for 2.4.19-rc1.&n; *&n; *---------------------------------------------------------------------------&n; *&n; * Todo&n; *&t;Test on machines with 5510, 5530, 5530A&n; */
multiline_comment|/************************************************************************&n; *&t;&t;&t;Suspend Modulation - Definitions&t;&t;*&n; ************************************************************************/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/processor.h&gt; 
macro_line|#include &lt;asm/errno.h&gt;
multiline_comment|/* PCI config registers, all at F0 */
DECL|macro|PCI_PMER1
mdefine_line|#define PCI_PMER1              0x80    /* power management enable register 1 */
DECL|macro|PCI_PMER2
mdefine_line|#define PCI_PMER2              0x81    /* power management enable register 2 */
DECL|macro|PCI_PMER3
mdefine_line|#define PCI_PMER3              0x82    /* power management enable register 3 */
DECL|macro|PCI_IRQTC
mdefine_line|#define PCI_IRQTC              0x8c    /* irq speedup timer counter register:typical 2 to 4ms */
DECL|macro|PCI_VIDTC
mdefine_line|#define PCI_VIDTC              0x8d    /* video speedup timer counter register: typical 50 to 100ms */
DECL|macro|PCI_MODOFF
mdefine_line|#define PCI_MODOFF             0x94    /* suspend modulation OFF counter register, 1 = 32us */
DECL|macro|PCI_MODON
mdefine_line|#define PCI_MODON              0x95    /* suspend modulation ON counter register */
DECL|macro|PCI_SUSCFG
mdefine_line|#define PCI_SUSCFG             0x96    /* suspend configuration register */
multiline_comment|/* PMER1 bits */
DECL|macro|GPM
mdefine_line|#define GPM                    (1&lt;&lt;0)  /* global power management */
DECL|macro|GIT
mdefine_line|#define GIT                    (1&lt;&lt;1)  /* globally enable PM device idle timers */
DECL|macro|GTR
mdefine_line|#define GTR                    (1&lt;&lt;2)  /* globally enable IO traps */
DECL|macro|IRQ_SPDUP
mdefine_line|#define IRQ_SPDUP              (1&lt;&lt;3)  /* disable clock throttle during interrupt handling */
DECL|macro|VID_SPDUP
mdefine_line|#define VID_SPDUP              (1&lt;&lt;4)  /* disable clock throttle during vga video handling */
multiline_comment|/* SUSCFG bits */
DECL|macro|SUSMOD
mdefine_line|#define SUSMOD                 (1&lt;&lt;0)  /* enable/disable suspend modulation */
multiline_comment|/* the belows support only with cs5530 (after rev.1.2)/cs5530A */
DECL|macro|SMISPDUP
mdefine_line|#define SMISPDUP               (1&lt;&lt;1)  /* select how SMI re-enable suspend modulation: */
multiline_comment|/* IRQTC timer or read SMI speedup disable reg.(F1BAR[08-09h]) */
DECL|macro|SUSCFG
mdefine_line|#define SUSCFG                 (1&lt;&lt;2)  /* enable powering down a GXLV processor. &quot;Special 3Volt Suspend&quot; mode */
multiline_comment|/* the belows support only with cs5530A */
DECL|macro|PWRSVE_ISA
mdefine_line|#define PWRSVE_ISA             (1&lt;&lt;3)  /* stop ISA clock  */
DECL|macro|PWRSVE
mdefine_line|#define PWRSVE                 (1&lt;&lt;4)  /* active idle */
DECL|struct|gxfreq_params
r_struct
id|gxfreq_params
(brace
DECL|member|on_duration
id|u8
id|on_duration
suffix:semicolon
DECL|member|off_duration
id|u8
id|off_duration
suffix:semicolon
DECL|member|pci_suscfg
id|u8
id|pci_suscfg
suffix:semicolon
DECL|member|pci_pmer1
id|u8
id|pci_pmer1
suffix:semicolon
DECL|member|pci_pmer2
id|u8
id|pci_pmer2
suffix:semicolon
DECL|member|pci_rev
id|u8
id|pci_rev
suffix:semicolon
DECL|member|cs55x0
r_struct
id|pci_dev
op_star
id|cs55x0
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|gx_params
r_static
r_struct
id|gxfreq_params
op_star
id|gx_params
suffix:semicolon
DECL|variable|stock_freq
r_static
r_int
id|stock_freq
suffix:semicolon
multiline_comment|/* PCI bus clock - defaults to 30.000 if cpu_khz is not available */
DECL|variable|pci_busclk
r_static
r_int
id|pci_busclk
op_assign
l_int|0
suffix:semicolon
id|module_param
(paren
id|pci_busclk
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
multiline_comment|/* maximum duration for which the cpu may be suspended&n; * (32us * MAX_DURATION). If no parameter is given, this defaults&n; * to 255. &n; * Note that this leads to a maximum of 8 ms(!) where the CPU clock&n; * is suspended -- processing power is just 0.39% of what it used to be,&n; * though. 781.25 kHz(!) for a 200 MHz processor -- wow. */
DECL|variable|max_duration
r_static
r_int
id|max_duration
op_assign
l_int|255
suffix:semicolon
id|module_param
(paren
id|max_duration
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
multiline_comment|/* For the default policy, we want at least some processing power&n; * - let&squot;s say 5%. (min = maxfreq / POLICY_MIN_DIV)&n; */
DECL|macro|POLICY_MIN_DIV
mdefine_line|#define POLICY_MIN_DIV 20
multiline_comment|/* DEBUG&n; *   Define it if you want verbose debug output&n; */
DECL|macro|SUSPMOD_DEBUG
mdefine_line|#define SUSPMOD_DEBUG 1
macro_line|#ifdef SUSPMOD_DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) printk(KERN_DEBUG &quot;cpufreq:&quot; msg)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) do { } while(0)
macro_line|#endif
multiline_comment|/**&n; *      we can detect a core multipiler from dir0_lsb &n; *      from GX1 datasheet p.56, &n; *&t;   MULT[3:0]:&n; *&t;   0000 = SYSCLK multiplied by 4 (test only)&n; *&t;   0001 = SYSCLK multiplied by 10&n; *&t;   0010 = SYSCLK multiplied by 4&n; *&t;   0011 = SYSCLK multiplied by 6&n; *&t;   0100 = SYSCLK multiplied by 9&n; *&t;   0101 = SYSCLK multiplied by 5&n; *&t;   0110 = SYSCLK multiplied by 7&n; *&t;   0111 = SYSCLK multiplied by 8&n; *              of 33.3MHz&n; **/
DECL|variable|gx_freq_mult
r_static
r_int
id|gx_freq_mult
(braket
l_int|16
)braket
op_assign
(brace
l_int|4
comma
l_int|10
comma
l_int|4
comma
l_int|6
comma
l_int|9
comma
l_int|5
comma
l_int|7
comma
l_int|8
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/****************************************************************&n; * &t;Low Level chipset interface&t;&t;&t;&t;*&n; ****************************************************************/
DECL|variable|__initdata
r_static
r_struct
id|pci_device_id
id|gx_chipset_tbl
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_CYRIX
comma
id|PCI_DEVICE_ID_CYRIX_5530_LEGACY
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
)brace
comma
(brace
id|PCI_VENDOR_ID_CYRIX
comma
id|PCI_DEVICE_ID_CYRIX_5520
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
)brace
comma
(brace
id|PCI_VENDOR_ID_CYRIX
comma
id|PCI_DEVICE_ID_CYRIX_5510
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *     gx_detect_chipset:&n; *&n; **/
DECL|function|gx_detect_chipset
r_static
id|__init
r_struct
id|pci_dev
op_star
id|gx_detect_chipset
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|gx_pci
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* check if CPU is a MediaGX or a Geode. */
r_if
c_cond
(paren
(paren
id|current_cpu_data.x86_vendor
op_ne
id|X86_VENDOR_NSC
)paren
op_logical_and
(paren
id|current_cpu_data.x86_vendor
op_ne
id|X86_VENDOR_CYRIX
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;gx-suspmod: error: no MediaGX/Geode processor found!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* detect which companion chip is used */
r_while
c_loop
(paren
(paren
id|gx_pci
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|gx_pci
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|pci_match_device
(paren
id|gx_chipset_tbl
comma
id|gx_pci
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_return
id|gx_pci
suffix:semicolon
)brace
)brace
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;gx-suspmod: error: no supported chipset found!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; *      gx_get_cpuspeed:&n; *&n; * Finds out at which efficient frequency the Cyrix MediaGX/NatSemi Geode CPU runs.&n; */
DECL|function|gx_get_cpuspeed
r_static
r_int
r_int
id|gx_get_cpuspeed
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
(paren
id|gx_params-&gt;pci_suscfg
op_amp
id|SUSMOD
)paren
op_eq
l_int|0
)paren
r_return
id|stock_freq
suffix:semicolon
r_return
(paren
id|stock_freq
op_star
id|gx_params-&gt;on_duration
)paren
op_div
(paren
id|gx_params-&gt;on_duration
op_plus
id|gx_params-&gt;off_duration
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *      gx_validate_speed:&n; *      determine current cpu speed&n; *       &n;**/
DECL|function|gx_validate_speed
r_static
r_int
r_int
id|gx_validate_speed
c_func
(paren
r_int
r_int
id|khz
comma
id|u8
op_star
id|on_duration
comma
id|u8
op_star
id|off_duration
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|u8
id|tmp_on
comma
id|tmp_off
suffix:semicolon
r_int
id|old_tmp_freq
op_assign
id|stock_freq
suffix:semicolon
r_int
id|tmp_freq
suffix:semicolon
op_star
id|off_duration
op_assign
l_int|1
suffix:semicolon
op_star
id|on_duration
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|max_duration
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|tmp_off
op_assign
(paren
(paren
id|khz
op_star
id|i
)paren
op_div
id|stock_freq
)paren
op_amp
l_int|0xff
suffix:semicolon
id|tmp_on
op_assign
id|i
op_minus
id|tmp_off
suffix:semicolon
id|tmp_freq
op_assign
(paren
id|stock_freq
op_star
id|tmp_off
)paren
op_div
id|i
suffix:semicolon
multiline_comment|/* if this relation is closer to khz, use this. If it&squot;s equal,&n;&t;&t; * prefer it, too - lower latency */
r_if
c_cond
(paren
id|abs
c_func
(paren
id|tmp_freq
op_minus
id|khz
)paren
op_le
id|abs
c_func
(paren
id|old_tmp_freq
op_minus
id|khz
)paren
)paren
(brace
op_star
id|on_duration
op_assign
id|tmp_on
suffix:semicolon
op_star
id|off_duration
op_assign
id|tmp_off
suffix:semicolon
id|old_tmp_freq
op_assign
id|tmp_freq
suffix:semicolon
)brace
)brace
r_return
id|old_tmp_freq
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;gx_set_cpuspeed:&n; *&t;&t;set cpu speed in khz.&n; **/
DECL|function|gx_set_cpuspeed
r_static
r_void
id|gx_set_cpuspeed
c_func
(paren
r_int
r_int
id|khz
)paren
(brace
id|u8
id|suscfg
comma
id|pmer1
suffix:semicolon
r_int
r_int
id|new_khz
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
id|freqs.cpu
op_assign
l_int|0
suffix:semicolon
id|freqs.old
op_assign
id|gx_get_cpuspeed
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|new_khz
op_assign
id|gx_validate_speed
c_func
(paren
id|khz
comma
op_amp
id|gx_params-&gt;on_duration
comma
op_amp
id|gx_params-&gt;off_duration
)paren
suffix:semicolon
id|freqs
dot
r_new
op_assign
id|new_khz
suffix:semicolon
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_khz
op_ne
id|stock_freq
)paren
(brace
multiline_comment|/* if new khz == 100% of CPU speed, it is special case */
r_switch
c_cond
(paren
id|gx_params-&gt;cs55x0-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_CYRIX_5530_LEGACY
suffix:colon
id|pmer1
op_assign
id|gx_params-&gt;pci_pmer1
op_or
id|IRQ_SPDUP
op_or
id|VID_SPDUP
suffix:semicolon
multiline_comment|/* FIXME: need to test other values -- Zwane,Miura */
id|pci_write_config_byte
c_func
(paren
id|gx_params-&gt;cs55x0
comma
id|PCI_IRQTC
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* typical 2 to 4ms */
id|pci_write_config_byte
c_func
(paren
id|gx_params-&gt;cs55x0
comma
id|PCI_VIDTC
comma
l_int|100
)paren
suffix:semicolon
multiline_comment|/* typical 50 to 100ms */
id|pci_write_config_byte
c_func
(paren
id|gx_params-&gt;cs55x0
comma
id|PCI_PMER1
comma
id|pmer1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gx_params-&gt;pci_rev
OL
l_int|0x10
)paren
(brace
multiline_comment|/* CS5530(rev 1.2, 1.3) */
id|suscfg
op_assign
id|gx_params-&gt;pci_suscfg
op_or
id|SUSMOD
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* CS5530A,B.. */
id|suscfg
op_assign
id|gx_params-&gt;pci_suscfg
op_or
id|SUSMOD
op_or
id|PWRSVE
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PCI_DEVICE_ID_CYRIX_5520
suffix:colon
r_case
id|PCI_DEVICE_ID_CYRIX_5510
suffix:colon
id|suscfg
op_assign
id|gx_params-&gt;pci_suscfg
op_or
id|SUSMOD
suffix:semicolon
r_default
suffix:colon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;fatal: try to set unknown chipset.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_else
(brace
id|suscfg
op_assign
id|gx_params-&gt;pci_suscfg
op_amp
op_complement
(paren
id|SUSMOD
)paren
suffix:semicolon
id|gx_params-&gt;off_duration
op_assign
l_int|0
suffix:semicolon
id|gx_params-&gt;on_duration
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;suspend modulation disabled: cpu runs 100 percent speed.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|pci_write_config_byte
c_func
(paren
id|gx_params-&gt;cs55x0
comma
id|PCI_MODOFF
comma
id|gx_params-&gt;off_duration
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|gx_params-&gt;cs55x0
comma
id|PCI_MODON
comma
id|gx_params-&gt;on_duration
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|gx_params-&gt;cs55x0
comma
id|PCI_SUSCFG
comma
id|suscfg
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|gx_params-&gt;cs55x0
comma
id|PCI_SUSCFG
comma
op_amp
id|suscfg
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|gx_params-&gt;pci_suscfg
op_assign
id|suscfg
suffix:semicolon
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_POSTCHANGE
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;suspend modulation w/ duration of ON:%d us, OFF:%d us&bslash;n&quot;
comma
id|gx_params-&gt;on_duration
op_star
l_int|32
comma
id|gx_params-&gt;off_duration
op_star
l_int|32
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;suspend modulation w/ clock speed: %d kHz.&bslash;n&quot;
comma
id|freqs
dot
r_new
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; *             High level functions                             *&n; ****************************************************************/
multiline_comment|/*&n; *&t;cpufreq_gx_verify: test if frequency range is valid &n; *&n; *&t;This function checks if a given frequency range in kHz is valid &n; *      for the hardware supported by the driver. &n; */
DECL|function|cpufreq_gx_verify
r_static
r_int
id|cpufreq_gx_verify
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
r_int
id|tmp_freq
op_assign
l_int|0
suffix:semicolon
id|u8
id|tmp1
comma
id|tmp2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stock_freq
op_logical_or
op_logical_neg
id|policy
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|policy-&gt;cpu
op_assign
l_int|0
suffix:semicolon
id|cpufreq_verify_within_limits
c_func
(paren
id|policy
comma
(paren
id|stock_freq
op_div
id|max_duration
)paren
comma
id|stock_freq
)paren
suffix:semicolon
multiline_comment|/* it needs to be assured that at least one supported frequency is&n;&t; * within policy-&gt;min and policy-&gt;max. If it is not, policy-&gt;max&n;&t; * needs to be increased until one freuqency is supported.&n;&t; * policy-&gt;min may not be decreased, though. This way we guarantee a &n;&t; * specific processing capacity.&n;&t; */
id|tmp_freq
op_assign
id|gx_validate_speed
c_func
(paren
id|policy-&gt;min
comma
op_amp
id|tmp1
comma
op_amp
id|tmp2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp_freq
OL
id|policy-&gt;min
)paren
id|tmp_freq
op_add_assign
id|stock_freq
op_div
id|max_duration
suffix:semicolon
id|policy-&gt;min
op_assign
id|tmp_freq
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;min
OG
id|policy-&gt;max
)paren
id|policy-&gt;max
op_assign
id|tmp_freq
suffix:semicolon
id|tmp_freq
op_assign
id|gx_validate_speed
c_func
(paren
id|policy-&gt;max
comma
op_amp
id|tmp1
comma
op_amp
id|tmp2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp_freq
OG
id|policy-&gt;max
)paren
id|tmp_freq
op_sub_assign
id|stock_freq
op_div
id|max_duration
suffix:semicolon
id|policy-&gt;max
op_assign
id|tmp_freq
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;max
OL
id|policy-&gt;min
)paren
id|policy-&gt;max
op_assign
id|policy-&gt;min
suffix:semicolon
id|cpufreq_verify_within_limits
c_func
(paren
id|policy
comma
(paren
id|stock_freq
op_div
id|max_duration
)paren
comma
id|stock_freq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *      cpufreq_gx_target:  &n; *&n; */
DECL|function|cpufreq_gx_target
r_static
r_int
id|cpufreq_gx_target
c_func
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
id|u8
id|tmp1
comma
id|tmp2
suffix:semicolon
r_int
r_int
id|tmp_freq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stock_freq
op_logical_or
op_logical_neg
id|policy
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|policy-&gt;cpu
op_assign
l_int|0
suffix:semicolon
id|tmp_freq
op_assign
id|gx_validate_speed
c_func
(paren
id|target_freq
comma
op_amp
id|tmp1
comma
op_amp
id|tmp2
)paren
suffix:semicolon
r_while
c_loop
(paren
id|tmp_freq
OL
id|policy-&gt;min
)paren
(brace
id|tmp_freq
op_add_assign
id|stock_freq
op_div
id|max_duration
suffix:semicolon
id|tmp_freq
op_assign
id|gx_validate_speed
c_func
(paren
id|tmp_freq
comma
op_amp
id|tmp1
comma
op_amp
id|tmp2
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|tmp_freq
OG
id|policy-&gt;max
)paren
(brace
id|tmp_freq
op_sub_assign
id|stock_freq
op_div
id|max_duration
suffix:semicolon
id|tmp_freq
op_assign
id|gx_validate_speed
c_func
(paren
id|tmp_freq
comma
op_amp
id|tmp1
comma
op_amp
id|tmp2
)paren
suffix:semicolon
)brace
id|gx_set_cpuspeed
c_func
(paren
id|tmp_freq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpufreq_gx_cpu_init
r_static
r_int
id|cpufreq_gx_cpu_init
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
r_int
id|maxfreq
comma
id|curfreq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|policy
op_logical_or
id|policy-&gt;cpu
op_ne
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* determine maximum frequency */
r_if
c_cond
(paren
id|pci_busclk
)paren
(brace
id|maxfreq
op_assign
id|pci_busclk
op_star
id|gx_freq_mult
(braket
id|getCx86
c_func
(paren
id|CX86_DIR1
)paren
op_amp
l_int|0x0f
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cpu_khz
)paren
(brace
id|maxfreq
op_assign
id|cpu_khz
suffix:semicolon
)brace
r_else
(brace
id|maxfreq
op_assign
l_int|30000
op_star
id|gx_freq_mult
(braket
id|getCx86
c_func
(paren
id|CX86_DIR1
)paren
op_amp
l_int|0x0f
)braket
suffix:semicolon
)brace
id|stock_freq
op_assign
id|maxfreq
suffix:semicolon
id|curfreq
op_assign
id|gx_get_cpuspeed
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;cpu max frequency is %d.&bslash;n&quot;
comma
id|maxfreq
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;cpu current frequency is %dkHz.&bslash;n&quot;
comma
id|curfreq
)paren
suffix:semicolon
multiline_comment|/* setup basic struct for cpufreq API */
id|policy-&gt;cpu
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|max_duration
OL
id|POLICY_MIN_DIV
)paren
id|policy-&gt;min
op_assign
id|maxfreq
op_div
id|max_duration
suffix:semicolon
r_else
id|policy-&gt;min
op_assign
id|maxfreq
op_div
id|POLICY_MIN_DIV
suffix:semicolon
id|policy-&gt;max
op_assign
id|maxfreq
suffix:semicolon
id|policy-&gt;cur
op_assign
id|curfreq
suffix:semicolon
id|policy-&gt;governor
op_assign
id|CPUFREQ_DEFAULT_GOVERNOR
suffix:semicolon
id|policy-&gt;cpuinfo.min_freq
op_assign
id|maxfreq
op_div
id|max_duration
suffix:semicolon
id|policy-&gt;cpuinfo.max_freq
op_assign
id|maxfreq
suffix:semicolon
id|policy-&gt;cpuinfo.transition_latency
op_assign
id|CPUFREQ_ETERNAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * cpufreq_gx_init:&n; *   MediaGX/Geode GX initialize cpufreq driver&n; */
DECL|variable|gx_suspmod_driver
r_static
r_struct
id|cpufreq_driver
id|gx_suspmod_driver
op_assign
(brace
dot
id|get
op_assign
id|gx_get_cpuspeed
comma
dot
id|verify
op_assign
id|cpufreq_gx_verify
comma
dot
id|target
op_assign
id|cpufreq_gx_target
comma
dot
id|init
op_assign
id|cpufreq_gx_cpu_init
comma
dot
id|name
op_assign
l_string|&quot;gx-suspmod&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|cpufreq_gx_init
r_static
r_int
id|__init
id|cpufreq_gx_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|gxfreq_params
op_star
id|params
suffix:semicolon
r_struct
id|pci_dev
op_star
id|gx_pci
suffix:semicolon
id|u32
id|class_rev
suffix:semicolon
multiline_comment|/* Test if we have the right hardware */
r_if
c_cond
(paren
(paren
id|gx_pci
op_assign
id|gx_detect_chipset
c_func
(paren
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* check whether module parameters are sane */
r_if
c_cond
(paren
id|max_duration
OG
l_int|0xff
)paren
id|max_duration
op_assign
l_int|0xff
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;geode suspend modulation available.&bslash;n&quot;
)paren
suffix:semicolon
id|params
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|gxfreq_params
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|params
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|params
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|gxfreq_params
)paren
)paren
suffix:semicolon
id|params-&gt;cs55x0
op_assign
id|gx_pci
suffix:semicolon
id|gx_params
op_assign
id|params
suffix:semicolon
multiline_comment|/* keep cs55x0 configurations */
id|pci_read_config_byte
c_func
(paren
id|params-&gt;cs55x0
comma
id|PCI_SUSCFG
comma
op_amp
(paren
id|params-&gt;pci_suscfg
)paren
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|params-&gt;cs55x0
comma
id|PCI_PMER1
comma
op_amp
(paren
id|params-&gt;pci_pmer1
)paren
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|params-&gt;cs55x0
comma
id|PCI_PMER2
comma
op_amp
(paren
id|params-&gt;pci_pmer2
)paren
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|params-&gt;cs55x0
comma
id|PCI_MODON
comma
op_amp
(paren
id|params-&gt;on_duration
)paren
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|params-&gt;cs55x0
comma
id|PCI_MODOFF
comma
op_amp
(paren
id|params-&gt;off_duration
)paren
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|params-&gt;cs55x0
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|class_rev
)paren
suffix:semicolon
id|params-&gt;pci_rev
op_assign
id|class_rev
op_logical_and
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|cpufreq_register_driver
c_func
(paren
op_amp
id|gx_suspmod_driver
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|params
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
multiline_comment|/* register error! */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpufreq_gx_exit
r_static
r_void
id|__exit
id|cpufreq_gx_exit
c_func
(paren
r_void
)paren
(brace
id|cpufreq_unregister_driver
c_func
(paren
op_amp
id|gx_suspmod_driver
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|gx_params
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Hiroshi Miura &lt;miura@da-cha.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;Cpufreq driver for Cyrix MediaGX and NatSemi Geode&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|cpufreq_gx_init
id|module_init
c_func
(paren
id|cpufreq_gx_init
)paren
suffix:semicolon
DECL|variable|cpufreq_gx_exit
id|module_exit
c_func
(paren
id|cpufreq_gx_exit
)paren
suffix:semicolon
eof
