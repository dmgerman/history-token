multiline_comment|/*&n; *  (C) 2001-2003  Dave Jones. &lt;davej@codemonkey.org.uk&gt;&n; *  (C) 2002  Padraig Brady. &lt;padraig@antefacto.com&gt;&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *  Based upon datasheets &amp; sample CPUs kindly provided by VIA.&n; *&n; *  VIA have currently 2 different versions of Longhaul.&n; *  Version 1 (Longhaul) uses the BCR2 MSR at 0x1147.&n; *   It is present only in Samuel 1, Samuel 2 and Ezra.&n; *  Version 2 (Powersaver) uses the POWERSAVER MSR at 0x110a.&n; *   It is present in Ezra-T, Nehemiah and above.&n; *   In addition to scaling multiplier, it can also scale voltage.&n; *   There is provision for scaling FSB too, but this doesn&squot;t work&n; *   too well in practice.&n; *&n; *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/timex.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;longhaul.h&quot;
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#ifdef DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) printk(msg)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) do { } while(0)
macro_line|#endif
DECL|macro|PFX
mdefine_line|#define PFX &quot;longhaul: &quot;
DECL|variable|numscales
DECL|variable|numvscales
r_static
r_int
r_int
id|numscales
op_assign
l_int|16
comma
id|numvscales
suffix:semicolon
DECL|variable|minvid
DECL|variable|maxvid
r_static
r_int
id|minvid
comma
id|maxvid
suffix:semicolon
DECL|variable|can_scale_voltage
r_static
r_int
id|can_scale_voltage
suffix:semicolon
DECL|variable|vrmrev
r_static
r_int
id|vrmrev
suffix:semicolon
multiline_comment|/* Module parameters */
DECL|variable|dont_scale_voltage
r_static
r_int
id|dont_scale_voltage
suffix:semicolon
DECL|variable|fsb
r_static
r_int
r_int
id|fsb
suffix:semicolon
DECL|macro|__hlt
mdefine_line|#define __hlt()     __asm__ __volatile__(&quot;hlt&quot;: : :&quot;memory&quot;)
multiline_comment|/* Clock ratios multiplied by 10 */
DECL|variable|clock_ratio
r_static
r_int
id|clock_ratio
(braket
l_int|32
)braket
suffix:semicolon
DECL|variable|eblcr_table
r_static
r_int
id|eblcr_table
(braket
l_int|32
)braket
suffix:semicolon
DECL|variable|voltage_table
r_static
r_int
id|voltage_table
(braket
l_int|32
)braket
suffix:semicolon
DECL|variable|highest_speed
DECL|variable|lowest_speed
r_static
r_int
r_int
id|highest_speed
comma
id|lowest_speed
suffix:semicolon
multiline_comment|/* kHz */
DECL|variable|longhaul_version
r_static
r_int
id|longhaul_version
suffix:semicolon
DECL|variable|longhaul_table
r_static
r_struct
id|cpufreq_frequency_table
op_star
id|longhaul_table
suffix:semicolon
DECL|function|calc_speed
r_static
r_int
r_int
id|calc_speed
(paren
r_int
id|mult
comma
r_int
id|fsb
)paren
(brace
r_int
id|mhz
suffix:semicolon
id|mhz
op_assign
(paren
id|mult
op_div
l_int|10
)paren
op_star
id|fsb
suffix:semicolon
r_if
c_cond
(paren
id|mult
op_mod
l_int|10
)paren
id|mhz
op_add_assign
id|fsb
op_div
l_int|2
suffix:semicolon
r_return
id|mhz
suffix:semicolon
)brace
DECL|function|longhaul_get_cpu_mult
r_static
r_int
id|longhaul_get_cpu_mult
(paren
r_void
)paren
(brace
r_int
r_int
id|invalue
op_assign
l_int|0
comma
id|lo
comma
id|hi
suffix:semicolon
id|rdmsr
(paren
id|MSR_IA32_EBL_CR_POWERON
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|invalue
op_assign
(paren
id|lo
op_amp
(paren
l_int|1
op_lshift
l_int|22
op_or
l_int|1
op_lshift
l_int|23
op_or
l_int|1
op_lshift
l_int|24
op_or
l_int|1
op_lshift
l_int|25
)paren
)paren
op_rshift
l_int|22
suffix:semicolon
r_if
c_cond
(paren
id|longhaul_version
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|lo
op_amp
(paren
l_int|1
op_lshift
l_int|27
)paren
)paren
id|invalue
op_add_assign
l_int|16
suffix:semicolon
)brace
r_return
id|eblcr_table
(braket
id|invalue
)braket
suffix:semicolon
)brace
multiline_comment|/**&n; * longhaul_set_cpu_frequency()&n; * @clock_ratio_index : bitpattern of the new multiplier.&n; *&n; * Sets a new clock ratio, and -if applicable- a new Front Side Bus&n; */
DECL|function|longhaul_setstate
r_static
r_void
id|longhaul_setstate
(paren
r_int
r_int
id|clock_ratio_index
)paren
(brace
r_int
id|speed
comma
id|mult
suffix:semicolon
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
r_union
id|msr_longhaul
id|longhaul
suffix:semicolon
r_union
id|msr_bcr2
id|bcr2
suffix:semicolon
id|mult
op_assign
id|clock_ratio
(braket
id|clock_ratio_index
)braket
suffix:semicolon
r_if
c_cond
(paren
id|mult
op_eq
op_minus
l_int|1
)paren
r_return
suffix:semicolon
id|speed
op_assign
id|calc_speed
(paren
id|mult
comma
id|fsb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|speed
OG
id|highest_speed
)paren
op_logical_or
(paren
id|speed
OL
id|lowest_speed
)paren
)paren
r_return
suffix:semicolon
id|freqs.old
op_assign
id|calc_speed
(paren
id|longhaul_get_cpu_mult
c_func
(paren
)paren
comma
id|fsb
)paren
suffix:semicolon
id|freqs
dot
r_new
op_assign
id|speed
suffix:semicolon
id|freqs.cpu
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* longhaul.c is UP only driver */
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;FSB:%d Mult:%d.%dx&bslash;n&quot;
comma
id|fsb
comma
id|mult
op_div
l_int|10
comma
id|mult
op_mod
l_int|10
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|longhaul_version
)paren
(brace
r_case
l_int|1
suffix:colon
id|rdmsrl
(paren
id|MSR_VIA_BCR2
comma
id|bcr2.val
)paren
suffix:semicolon
multiline_comment|/* Enable software clock multiplier */
id|bcr2.bits.ESOFTBF
op_assign
l_int|1
suffix:semicolon
id|bcr2.bits.CLOCKMUL
op_assign
id|clock_ratio_index
suffix:semicolon
id|wrmsrl
(paren
id|MSR_VIA_BCR2
comma
id|bcr2.val
)paren
suffix:semicolon
id|__hlt
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Disable software clock multiplier */
id|rdmsrl
(paren
id|MSR_VIA_BCR2
comma
id|bcr2.val
)paren
suffix:semicolon
id|bcr2.bits.ESOFTBF
op_assign
l_int|0
suffix:semicolon
id|wrmsrl
(paren
id|MSR_VIA_BCR2
comma
id|bcr2.val
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t; * Powersaver. (Ezra-T [C5M], Nehemiah [C5N])&n;&t; * We can scale voltage with this too, but that&squot;s currently&n;&t; * disabled until we come up with a decent &squot;match freq to voltage&squot;&n;&t; * algorithm.&n;&t; * We also need to do the voltage/freq setting in order depending&n;&t; * on the direction of scaling (like we do in powernow-k7.c)&n;&t; * Ezra-T was alleged to do FSB scaling too, but it never worked in practice.&n;&t; */
r_case
l_int|2
suffix:colon
id|rdmsrl
(paren
id|MSR_VIA_LONGHAUL
comma
id|longhaul.val
)paren
suffix:semicolon
id|longhaul.bits.SoftBusRatio
op_assign
id|clock_ratio_index
op_amp
l_int|0xf
suffix:semicolon
id|longhaul.bits.SoftBusRatio4
op_assign
(paren
id|clock_ratio_index
op_amp
l_int|0x10
)paren
op_rshift
l_int|4
suffix:semicolon
id|longhaul.bits.EnableSoftBusRatio
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We must program the revision key only with values we&n;&t;&t; * know about, not blindly copy it from 0:3 */
id|longhaul.bits.RevisionKey
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* SoftVID &amp; SoftBSEL */
id|wrmsrl
c_func
(paren
id|MSR_VIA_LONGHAUL
comma
id|longhaul.val
)paren
suffix:semicolon
id|__hlt
c_func
(paren
)paren
suffix:semicolon
id|rdmsrl
(paren
id|MSR_VIA_LONGHAUL
comma
id|longhaul.val
)paren
suffix:semicolon
id|longhaul.bits.EnableSoftBusRatio
op_assign
l_int|0
suffix:semicolon
id|longhaul.bits.RevisionKey
op_assign
l_int|3
suffix:semicolon
id|wrmsrl
(paren
id|MSR_VIA_LONGHAUL
comma
id|longhaul.val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_POSTCHANGE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Centaur decided to make life a little more tricky.&n; * Only longhaul v1 is allowed to read EBLCR BSEL[0:1].&n; * Samuel2 and above have to try and guess what the FSB is.&n; * We do this by assuming we booted at maximum multiplier, and interpolate&n; * between that value multiplied by possible FSBs and cpu_mhz which&n; * was calculated at boot time. Really ugly, but no other way to do this.&n; */
DECL|function|_guess
r_static
r_int
id|_guess
(paren
r_int
id|guess
comma
r_int
id|maxmult
)paren
(brace
r_int
id|target
suffix:semicolon
id|target
op_assign
(paren
(paren
id|maxmult
op_div
l_int|10
)paren
op_star
id|guess
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maxmult
op_mod
l_int|10
op_ne
l_int|0
)paren
id|target
op_add_assign
(paren
id|guess
op_div
l_int|2
)paren
suffix:semicolon
id|target
op_and_assign
op_complement
l_int|0xf
suffix:semicolon
r_return
id|target
suffix:semicolon
)brace
DECL|function|guess_fsb
r_static
r_int
id|guess_fsb
c_func
(paren
r_int
id|maxmult
)paren
(brace
r_int
id|speed
op_assign
(paren
id|cpu_khz
op_div
l_int|1000
)paren
op_amp
op_complement
l_int|0xf
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|speeds
(braket
l_int|3
)braket
op_assign
(brace
l_int|66
comma
l_int|100
comma
l_int|133
)brace
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|_guess
c_func
(paren
id|speeds
(braket
id|i
)braket
comma
id|maxmult
)paren
op_eq
id|speed
)paren
r_return
id|speeds
(braket
id|i
)braket
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|longhaul_get_ranges
r_static
r_int
id|__init
id|longhaul_get_ranges
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
r_int
r_int
id|invalue
suffix:semicolon
r_int
r_int
id|minmult
op_assign
l_int|0
comma
id|maxmult
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|multipliers
(braket
l_int|32
)braket
op_assign
(brace
l_int|50
comma
l_int|30
comma
l_int|40
comma
l_int|100
comma
l_int|55
comma
l_int|35
comma
l_int|45
comma
l_int|95
comma
l_int|90
comma
l_int|70
comma
l_int|80
comma
l_int|60
comma
l_int|120
comma
l_int|75
comma
l_int|85
comma
l_int|65
comma
op_minus
l_int|1
comma
l_int|110
comma
l_int|120
comma
op_minus
l_int|1
comma
l_int|135
comma
l_int|115
comma
l_int|125
comma
l_int|105
comma
l_int|130
comma
l_int|150
comma
l_int|160
comma
l_int|140
comma
op_minus
l_int|1
comma
l_int|155
comma
op_minus
l_int|1
comma
l_int|145
)brace
suffix:semicolon
r_int
r_int
id|j
comma
id|k
op_assign
l_int|0
suffix:semicolon
r_union
id|msr_longhaul
id|longhaul
suffix:semicolon
r_int
r_int
id|lo
comma
id|hi
suffix:semicolon
r_int
r_int
id|eblcr_fsb_table
(braket
)braket
op_assign
(brace
l_int|66
comma
l_int|133
comma
l_int|100
comma
op_minus
l_int|1
)brace
suffix:semicolon
r_switch
c_cond
(paren
id|longhaul_version
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* Ugh, Longhaul v1 didn&squot;t have the min/max MSRs.&n;&t;&t;   Assume min=3.0x &amp; max = whatever we booted at. */
id|minmult
op_assign
l_int|30
suffix:semicolon
id|maxmult
op_assign
id|longhaul_get_cpu_mult
c_func
(paren
)paren
suffix:semicolon
id|rdmsr
(paren
id|MSR_IA32_EBL_CR_POWERON
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|invalue
op_assign
(paren
id|lo
op_amp
(paren
l_int|1
op_lshift
l_int|18
op_or
l_int|1
op_lshift
l_int|19
)paren
)paren
op_rshift
l_int|18
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86_model
op_eq
l_int|6
)paren
id|fsb
op_assign
id|eblcr_fsb_table
(braket
id|invalue
)braket
suffix:semicolon
r_else
id|fsb
op_assign
id|guess_fsb
c_func
(paren
id|maxmult
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|rdmsrl
(paren
id|MSR_VIA_LONGHAUL
comma
id|longhaul.val
)paren
suffix:semicolon
id|invalue
op_assign
id|longhaul.bits.MaxMHzBR
suffix:semicolon
r_if
c_cond
(paren
id|longhaul.bits.MaxMHzBR4
)paren
id|invalue
op_add_assign
l_int|16
suffix:semicolon
id|maxmult
op_assign
id|multipliers
(braket
id|invalue
)braket
suffix:semicolon
id|invalue
op_assign
id|longhaul.bits.MinMHzBR
suffix:semicolon
r_if
c_cond
(paren
id|longhaul.bits.MinMHzBR4
op_eq
l_int|1
)paren
id|minmult
op_assign
l_int|30
suffix:semicolon
r_else
id|minmult
op_assign
id|multipliers
(braket
id|invalue
)braket
suffix:semicolon
id|fsb
op_assign
id|guess_fsb
c_func
(paren
id|maxmult
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;MinMult=%d.%dx MaxMult=%d.%dx&bslash;n&quot;
comma
id|minmult
op_div
l_int|10
comma
id|minmult
op_mod
l_int|10
comma
id|maxmult
op_div
l_int|10
comma
id|maxmult
op_mod
l_int|10
)paren
suffix:semicolon
id|highest_speed
op_assign
id|calc_speed
(paren
id|maxmult
comma
id|fsb
)paren
suffix:semicolon
id|lowest_speed
op_assign
id|calc_speed
(paren
id|minmult
comma
id|fsb
)paren
suffix:semicolon
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;FSB: %dMHz Lowestspeed=%dMHz Highestspeed=%dMHz&bslash;n&quot;
comma
id|fsb
comma
id|lowest_speed
comma
id|highest_speed
)paren
suffix:semicolon
id|longhaul_table
op_assign
id|kmalloc
c_func
(paren
(paren
id|numscales
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|cpufreq_frequency_table
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|longhaul_table
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|numscales
suffix:semicolon
id|j
op_increment
)paren
(brace
r_int
r_int
id|ratio
suffix:semicolon
id|ratio
op_assign
id|clock_ratio
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ratio
op_eq
op_minus
l_int|1
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OG
id|maxmult
op_logical_or
id|ratio
OL
id|minmult
)paren
r_continue
suffix:semicolon
id|longhaul_table
(braket
id|k
)braket
dot
id|frequency
op_assign
id|calc_speed
(paren
id|ratio
comma
id|fsb
)paren
suffix:semicolon
id|longhaul_table
(braket
id|k
)braket
dot
id|index
op_assign
(paren
id|j
op_lshift
l_int|8
)paren
suffix:semicolon
id|k
op_increment
suffix:semicolon
)brace
id|longhaul_table
(braket
id|k
)braket
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|k
)paren
(brace
id|kfree
(paren
id|longhaul_table
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|longhaul_setup_voltagescaling
r_static
r_void
id|__init
id|longhaul_setup_voltagescaling
c_func
(paren
r_void
)paren
(brace
r_union
id|msr_longhaul
id|longhaul
suffix:semicolon
id|rdmsrl
(paren
id|MSR_VIA_LONGHAUL
comma
id|longhaul.val
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|longhaul.bits.RevisionID
op_amp
l_int|1
)paren
)paren
r_return
suffix:semicolon
id|minvid
op_assign
id|longhaul.bits.MinimumVID
suffix:semicolon
id|maxvid
op_assign
id|longhaul.bits.MaximumVID
suffix:semicolon
id|vrmrev
op_assign
id|longhaul.bits.VRMRev
suffix:semicolon
r_if
c_cond
(paren
id|minvid
op_eq
l_int|0
op_logical_or
id|maxvid
op_eq
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Bogus values Min:%d.%03d Max:%d.%03d. &quot;
l_string|&quot;Voltage scaling disabled.&bslash;n&quot;
comma
id|minvid
op_div
l_int|1000
comma
id|minvid
op_mod
l_int|1000
comma
id|maxvid
op_div
l_int|1000
comma
id|maxvid
op_mod
l_int|1000
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|minvid
op_eq
id|maxvid
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Claims to support voltage scaling but min &amp; max are &quot;
l_string|&quot;both %d.%03d. Voltage scaling disabled&bslash;n&quot;
comma
id|maxvid
op_div
l_int|1000
comma
id|maxvid
op_mod
l_int|1000
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vrmrev
op_eq
l_int|0
)paren
(brace
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;VRM 8.5 : &quot;
)paren
suffix:semicolon
id|memcpy
(paren
id|voltage_table
comma
id|vrm85scales
comma
r_sizeof
(paren
id|voltage_table
)paren
)paren
suffix:semicolon
id|numvscales
op_assign
(paren
id|voltage_table
(braket
id|maxvid
)braket
op_minus
id|voltage_table
(braket
id|minvid
)braket
)paren
op_div
l_int|25
suffix:semicolon
)brace
r_else
(brace
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Mobile VRM : &quot;
)paren
suffix:semicolon
id|memcpy
(paren
id|voltage_table
comma
id|mobilevrmscales
comma
r_sizeof
(paren
id|voltage_table
)paren
)paren
suffix:semicolon
id|numvscales
op_assign
(paren
id|voltage_table
(braket
id|maxvid
)braket
op_minus
id|voltage_table
(braket
id|minvid
)braket
)paren
op_div
l_int|5
suffix:semicolon
)brace
multiline_comment|/* Current voltage isn&squot;t readable at first, so we need to&n;&t;   set it to a known value. The spec says to use maxvid */
id|longhaul.bits.RevisionKey
op_assign
id|longhaul.bits.RevisionID
suffix:semicolon
multiline_comment|/* FIXME: This is bad. */
id|longhaul.bits.EnableSoftVID
op_assign
l_int|1
suffix:semicolon
id|longhaul.bits.SoftVID
op_assign
id|maxvid
suffix:semicolon
id|wrmsrl
(paren
id|MSR_VIA_LONGHAUL
comma
id|longhaul.val
)paren
suffix:semicolon
id|minvid
op_assign
id|voltage_table
(braket
id|minvid
)braket
suffix:semicolon
id|maxvid
op_assign
id|voltage_table
(braket
id|maxvid
)braket
suffix:semicolon
id|dprintk
(paren
l_string|&quot;Min VID=%d.%03d Max VID=%d.%03d, %d possible voltage scales&bslash;n&quot;
comma
id|maxvid
op_div
l_int|1000
comma
id|maxvid
op_mod
l_int|1000
comma
id|minvid
op_div
l_int|1000
comma
id|minvid
op_mod
l_int|1000
comma
id|numvscales
)paren
suffix:semicolon
id|can_scale_voltage
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|longhaul_verify
r_static
r_int
id|longhaul_verify
c_func
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
id|longhaul_table
)paren
suffix:semicolon
)brace
DECL|function|longhaul_target
r_static
r_int
id|longhaul_target
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
id|table_index
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|new_clock_ratio
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
id|longhaul_table
comma
id|target_freq
comma
id|relation
comma
op_amp
id|table_index
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|new_clock_ratio
op_assign
id|longhaul_table
(braket
id|table_index
)braket
dot
id|index
op_amp
l_int|0xFF
suffix:semicolon
id|longhaul_setstate
c_func
(paren
id|new_clock_ratio
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|longhaul_cpu_init
r_static
r_int
id|longhaul_cpu_init
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
id|cpu_data
suffix:semicolon
r_char
op_star
id|cpuname
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|c-&gt;x86_model
)paren
(brace
r_case
l_int|6
suffix:colon
id|cpuname
op_assign
l_string|&quot;C3 &squot;Samuel&squot; [C5A]&quot;
suffix:semicolon
id|longhaul_version
op_assign
l_int|1
suffix:semicolon
id|memcpy
(paren
id|clock_ratio
comma
id|samuel1_clock_ratio
comma
r_sizeof
(paren
id|samuel1_clock_ratio
)paren
)paren
suffix:semicolon
id|memcpy
(paren
id|eblcr_table
comma
id|samuel1_eblcr
comma
r_sizeof
(paren
id|samuel1_eblcr
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* C5B / C5C */
id|longhaul_version
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|c-&gt;x86_mask
)paren
(brace
r_case
l_int|0
suffix:colon
id|cpuname
op_assign
l_string|&quot;C3 &squot;Samuel 2&squot; [C5B]&quot;
suffix:semicolon
multiline_comment|/* Note, this is not a typo, early Samuel2&squot;s had Samuel1 ratios. */
id|memcpy
(paren
id|clock_ratio
comma
id|samuel1_clock_ratio
comma
r_sizeof
(paren
id|samuel1_clock_ratio
)paren
)paren
suffix:semicolon
id|memcpy
(paren
id|eblcr_table
comma
id|samuel2_eblcr
comma
r_sizeof
(paren
id|samuel2_eblcr
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
dot
dot
dot
l_int|15
suffix:colon
r_if
c_cond
(paren
id|c-&gt;x86_mask
OL
l_int|8
)paren
id|cpuname
op_assign
l_string|&quot;C3 &squot;Samuel 2&squot; [C5B]&quot;
suffix:semicolon
r_else
id|cpuname
op_assign
l_string|&quot;C3 &squot;Ezra&squot; [C5C]&quot;
suffix:semicolon
id|memcpy
(paren
id|clock_ratio
comma
id|ezra_clock_ratio
comma
r_sizeof
(paren
id|ezra_clock_ratio
)paren
)paren
suffix:semicolon
id|memcpy
(paren
id|eblcr_table
comma
id|ezra_eblcr
comma
r_sizeof
(paren
id|ezra_eblcr
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|cpuname
op_assign
l_string|&quot;C3 &squot;Ezra-T&squot; [C5M]&quot;
suffix:semicolon
id|longhaul_version
op_assign
l_int|2
suffix:semicolon
id|numscales
op_assign
l_int|32
suffix:semicolon
id|memcpy
(paren
id|clock_ratio
comma
id|ezrat_clock_ratio
comma
r_sizeof
(paren
id|ezrat_clock_ratio
)paren
)paren
suffix:semicolon
id|memcpy
(paren
id|eblcr_table
comma
id|ezrat_eblcr
comma
r_sizeof
(paren
id|ezrat_eblcr
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;case 9:&n;&t;&t;cpuname = &quot;C3 &squot;Nehemiah&squot; [C5N]&quot;;&n;&t;&t;longhaul_version=2;&n;&t;&t;numscales=32;&n;&t;&t;memcpy (clock_ratio, nehemiah_clock_ratio, sizeof(nehemiah_clock_ratio));&n;&t;&t;memcpy (eblcr_table, nehemiah_eblcr, sizeof(nehemiah_eblcr));&n;&t;*/
r_default
suffix:colon
id|cpuname
op_assign
l_string|&quot;Unknown&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;VIA %s CPU detected. Longhaul v%d supported.&bslash;n&quot;
comma
id|cpuname
comma
id|longhaul_version
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|longhaul_version
op_eq
l_int|2
)paren
op_logical_and
(paren
id|dont_scale_voltage
op_eq
l_int|0
)paren
)paren
id|longhaul_setup_voltagescaling
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|longhaul_get_ranges
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
r_return
id|ret
suffix:semicolon
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
id|calc_speed
(paren
id|longhaul_get_cpu_mult
c_func
(paren
)paren
comma
id|fsb
)paren
suffix:semicolon
r_return
id|cpufreq_frequency_table_cpuinfo
c_func
(paren
id|policy
comma
id|longhaul_table
)paren
suffix:semicolon
)brace
DECL|variable|longhaul_driver
r_static
r_struct
id|cpufreq_driver
id|longhaul_driver
op_assign
(brace
dot
id|verify
op_assign
id|longhaul_verify
comma
dot
id|target
op_assign
id|longhaul_target
comma
dot
id|init
op_assign
id|longhaul_cpu_init
comma
dot
id|name
op_assign
l_string|&quot;longhaul&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|longhaul_init
r_static
r_int
id|__init
id|longhaul_init
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
id|X86_VENDOR_CENTAUR
op_logical_or
id|c-&gt;x86
op_ne
l_int|6
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_switch
c_cond
(paren
id|c-&gt;x86_model
)paren
(brace
r_case
l_int|6
dot
dot
dot
l_int|8
suffix:colon
r_return
id|cpufreq_register_driver
c_func
(paren
op_amp
id|longhaul_driver
)paren
suffix:semicolon
r_case
l_int|9
suffix:colon
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Nehemiah unsupported: Waiting on working silicon &quot;
l_string|&quot;from VIA before this is usable.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Unknown VIA CPU. Contact davej@codemonkey.org.uk&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|longhaul_exit
r_static
r_void
id|__exit
id|longhaul_exit
(paren
r_void
)paren
(brace
id|cpufreq_unregister_driver
c_func
(paren
op_amp
id|longhaul_driver
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|longhaul_table
)paren
suffix:semicolon
)brace
id|MODULE_PARM
(paren
id|dont_scale_voltage
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
(paren
l_string|&quot;Dave Jones &lt;davej@codemonkey.org.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;Longhaul driver for VIA Cyrix processors.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|longhaul_init
id|module_init
c_func
(paren
id|longhaul_init
)paren
suffix:semicolon
DECL|variable|longhaul_exit
id|module_exit
c_func
(paren
id|longhaul_exit
)paren
suffix:semicolon
eof
