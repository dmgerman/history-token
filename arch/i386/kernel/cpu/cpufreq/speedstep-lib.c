multiline_comment|/*&n; * (C) 2002 - 2003 Dominik Brodowski &lt;linux@brodo.de&gt;&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *&n; *  Library for common functions for Intel SpeedStep v.1 and v.2 support&n; *&n; *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &quot;speedstep-lib.h&quot;
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) cpufreq_debug_printk(CPUFREQ_DEBUG_DRIVER, &quot;speedstep-lib&quot;, msg)
macro_line|#ifdef CONFIG_X86_SPEEDSTEP_RELAXED_CAP_CHECK
DECL|variable|relaxed_check
r_static
r_int
id|relaxed_check
op_assign
l_int|0
suffix:semicolon
macro_line|#else
DECL|macro|relaxed_check
mdefine_line|#define relaxed_check 0
macro_line|#endif
multiline_comment|/*********************************************************************&n; *                   GET PROCESSOR CORE SPEED IN KHZ                 *&n; *********************************************************************/
DECL|function|pentium3_get_frequency
r_static
r_int
r_int
id|pentium3_get_frequency
(paren
r_int
r_int
id|processor
)paren
(brace
multiline_comment|/* See table 14 of p3_ds.pdf and table 22 of 29834003.pdf */
r_struct
(brace
r_int
r_int
id|ratio
suffix:semicolon
multiline_comment|/* Frequency Multiplier (x10) */
id|u8
id|bitmap
suffix:semicolon
multiline_comment|/* power on configuration bits&n;&t;&t;&t;&t;&t;   [27, 25:22] (in MSR 0x2a) */
)brace
id|msr_decode_mult
(braket
)braket
op_assign
(brace
(brace
l_int|30
comma
l_int|0x01
)brace
comma
(brace
l_int|35
comma
l_int|0x05
)brace
comma
(brace
l_int|40
comma
l_int|0x02
)brace
comma
(brace
l_int|45
comma
l_int|0x06
)brace
comma
(brace
l_int|50
comma
l_int|0x00
)brace
comma
(brace
l_int|55
comma
l_int|0x04
)brace
comma
(brace
l_int|60
comma
l_int|0x0b
)brace
comma
(brace
l_int|65
comma
l_int|0x0f
)brace
comma
(brace
l_int|70
comma
l_int|0x09
)brace
comma
(brace
l_int|75
comma
l_int|0x0d
)brace
comma
(brace
l_int|80
comma
l_int|0x0a
)brace
comma
(brace
l_int|85
comma
l_int|0x26
)brace
comma
(brace
l_int|90
comma
l_int|0x20
)brace
comma
(brace
l_int|100
comma
l_int|0x2b
)brace
comma
(brace
l_int|0
comma
l_int|0xff
)brace
multiline_comment|/* error or unknown value */
)brace
suffix:semicolon
multiline_comment|/* PIII(-M) FSB settings: see table b1-b of 24547206.pdf */
r_struct
(brace
r_int
r_int
id|value
suffix:semicolon
multiline_comment|/* Front Side Bus speed in MHz */
id|u8
id|bitmap
suffix:semicolon
multiline_comment|/* power on configuration bits [18: 19]&n;&t;&t;&t;&t;&t;   (in MSR 0x2a) */
)brace
id|msr_decode_fsb
(braket
)braket
op_assign
(brace
(brace
l_int|66
comma
l_int|0x0
)brace
comma
(brace
l_int|100
comma
l_int|0x2
)brace
comma
(brace
l_int|133
comma
l_int|0x1
)brace
comma
(brace
l_int|0
comma
l_int|0xff
)brace
)brace
suffix:semicolon
id|u32
id|msr_lo
comma
id|msr_tmp
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|j
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* read MSR 0x2a - we only need the low 32 bits */
id|rdmsr
c_func
(paren
id|MSR_IA32_EBL_CR_POWERON
comma
id|msr_lo
comma
id|msr_tmp
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;P3 - MSR_IA32_EBL_CR_POWERON: 0x%x 0x%x&bslash;n&quot;
comma
id|msr_lo
comma
id|msr_tmp
)paren
suffix:semicolon
id|msr_tmp
op_assign
id|msr_lo
suffix:semicolon
multiline_comment|/* decode the FSB */
id|msr_tmp
op_and_assign
l_int|0x00c0000
suffix:semicolon
id|msr_tmp
op_rshift_assign
l_int|18
suffix:semicolon
r_while
c_loop
(paren
id|msr_tmp
op_ne
id|msr_decode_fsb
(braket
id|i
)braket
dot
id|bitmap
)paren
(brace
r_if
c_cond
(paren
id|msr_decode_fsb
(braket
id|i
)braket
dot
id|bitmap
op_eq
l_int|0xff
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
multiline_comment|/* decode the multiplier */
r_if
c_cond
(paren
id|processor
op_eq
id|SPEEDSTEP_PROCESSOR_PIII_C_EARLY
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;workaround for early PIIIs&bslash;n&quot;
)paren
suffix:semicolon
id|msr_lo
op_and_assign
l_int|0x03c00000
suffix:semicolon
)brace
r_else
id|msr_lo
op_and_assign
l_int|0x0bc00000
suffix:semicolon
id|msr_lo
op_rshift_assign
l_int|22
suffix:semicolon
r_while
c_loop
(paren
id|msr_lo
op_ne
id|msr_decode_mult
(braket
id|j
)braket
dot
id|bitmap
)paren
(brace
r_if
c_cond
(paren
id|msr_decode_mult
(braket
id|j
)braket
dot
id|bitmap
op_eq
l_int|0xff
)paren
r_return
l_int|0
suffix:semicolon
id|j
op_increment
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;speed is %u&bslash;n&quot;
comma
(paren
id|msr_decode_mult
(braket
id|j
)braket
dot
id|ratio
op_star
id|msr_decode_fsb
(braket
id|i
)braket
dot
id|value
op_star
l_int|100
)paren
)paren
suffix:semicolon
r_return
(paren
id|msr_decode_mult
(braket
id|j
)braket
dot
id|ratio
op_star
id|msr_decode_fsb
(braket
id|i
)braket
dot
id|value
op_star
l_int|100
)paren
suffix:semicolon
)brace
DECL|function|pentiumM_get_frequency
r_static
r_int
r_int
id|pentiumM_get_frequency
c_func
(paren
r_void
)paren
(brace
id|u32
id|msr_lo
comma
id|msr_tmp
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_EBL_CR_POWERON
comma
id|msr_lo
comma
id|msr_tmp
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;PM - MSR_IA32_EBL_CR_POWERON: 0x%x 0x%x&bslash;n&quot;
comma
id|msr_lo
comma
id|msr_tmp
)paren
suffix:semicolon
multiline_comment|/* see table B-2 of 24547212.pdf */
r_if
c_cond
(paren
id|msr_lo
op_amp
l_int|0x00040000
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;speedstep-lib: PM - invalid FSB: 0x%x 0x%x&bslash;n&quot;
comma
id|msr_lo
comma
id|msr_tmp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|msr_tmp
op_assign
(paren
id|msr_lo
op_rshift
l_int|22
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;bits 22-26 are 0x%x, speed is %u&bslash;n&quot;
comma
id|msr_tmp
comma
(paren
id|msr_tmp
op_star
l_int|100
op_star
l_int|1000
)paren
)paren
suffix:semicolon
r_return
(paren
id|msr_tmp
op_star
l_int|100
op_star
l_int|1000
)paren
suffix:semicolon
)brace
DECL|function|pentium4_get_frequency
r_static
r_int
r_int
id|pentium4_get_frequency
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
op_amp
id|boot_cpu_data
suffix:semicolon
id|u32
id|msr_lo
comma
id|msr_hi
comma
id|mult
suffix:semicolon
r_int
r_int
id|fsb
op_assign
l_int|0
suffix:semicolon
id|rdmsr
c_func
(paren
l_int|0x2c
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;P4 - MSR_EBC_FREQUENCY_ID: 0x%x 0x%x&bslash;n&quot;
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
multiline_comment|/* decode the FSB: see IA-32 Intel (C) Architecture Software &n;&t; * Developer&squot;s Manual, Volume 3: System Prgramming Guide,&n;&t; * revision #12 in Table B-1: MSRs in the Pentium 4 and&n;&t; * Intel Xeon Processors, on page B-4 and B-5.&n;&t; */
r_if
c_cond
(paren
id|c-&gt;x86_model
OL
l_int|2
)paren
id|fsb
op_assign
l_int|100
op_star
l_int|1000
suffix:semicolon
r_else
(brace
id|u8
id|fsb_code
op_assign
(paren
id|msr_lo
op_rshift
l_int|16
)paren
op_amp
l_int|0x7
suffix:semicolon
r_switch
c_cond
(paren
id|fsb_code
)paren
(brace
r_case
l_int|0
suffix:colon
id|fsb
op_assign
l_int|100
op_star
l_int|1000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|fsb
op_assign
l_int|13333
op_star
l_int|10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|fsb
op_assign
l_int|200
op_star
l_int|1000
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|fsb
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;speedstep-lib: couldn&squot;t detect FSB speed. Please send an e-mail to &lt;linux@brodo.de&gt;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Multiplier. */
r_if
c_cond
(paren
id|c-&gt;x86_model
OL
l_int|2
)paren
id|mult
op_assign
id|msr_lo
op_rshift
l_int|27
suffix:semicolon
r_else
id|mult
op_assign
id|msr_lo
op_rshift
l_int|24
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;P4 - FSB %u kHz; Multiplier %u; Speed %u kHz&bslash;n&quot;
comma
id|fsb
comma
id|mult
comma
(paren
id|fsb
op_star
id|mult
)paren
)paren
suffix:semicolon
r_return
(paren
id|fsb
op_star
id|mult
)paren
suffix:semicolon
)brace
DECL|function|speedstep_get_processor_frequency
r_int
r_int
id|speedstep_get_processor_frequency
c_func
(paren
r_int
r_int
id|processor
)paren
(brace
r_switch
c_cond
(paren
id|processor
)paren
(brace
r_case
id|SPEEDSTEP_PROCESSOR_PM
suffix:colon
r_return
id|pentiumM_get_frequency
c_func
(paren
)paren
suffix:semicolon
r_case
id|SPEEDSTEP_PROCESSOR_P4D
suffix:colon
r_case
id|SPEEDSTEP_PROCESSOR_P4M
suffix:colon
r_return
id|pentium4_get_frequency
c_func
(paren
)paren
suffix:semicolon
r_case
id|SPEEDSTEP_PROCESSOR_PIII_T
suffix:colon
r_case
id|SPEEDSTEP_PROCESSOR_PIII_C
suffix:colon
r_case
id|SPEEDSTEP_PROCESSOR_PIII_C_EARLY
suffix:colon
r_return
id|pentium3_get_frequency
c_func
(paren
id|processor
)paren
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|speedstep_get_processor_frequency
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|speedstep_get_processor_frequency
)paren
suffix:semicolon
multiline_comment|/*********************************************************************&n; *                 DETECT SPEEDSTEP-CAPABLE PROCESSOR                *&n; *********************************************************************/
DECL|function|speedstep_detect_processor
r_int
r_int
id|speedstep_detect_processor
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
id|u32
id|ebx
comma
id|msr_lo
comma
id|msr_hi
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;x86: %x, model: %x&bslash;n&quot;
comma
id|c-&gt;x86
comma
id|c-&gt;x86_model
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c-&gt;x86_vendor
op_ne
id|X86_VENDOR_INTEL
)paren
op_logical_or
(paren
(paren
id|c-&gt;x86
op_ne
l_int|6
)paren
op_logical_and
(paren
id|c-&gt;x86
op_ne
l_int|0xF
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|0xF
)paren
(brace
multiline_comment|/* Intel Mobile Pentium 4-M&n;&t;&t; * or Intel Mobile Pentium 4 with 533 MHz FSB */
r_if
c_cond
(paren
id|c-&gt;x86_model
op_ne
l_int|2
)paren
r_return
l_int|0
suffix:semicolon
id|ebx
op_assign
id|cpuid_ebx
c_func
(paren
l_int|0x00000001
)paren
suffix:semicolon
id|ebx
op_and_assign
l_int|0x000000FF
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;ebx value is %x, x86_mask is %x&bslash;n&quot;
comma
id|ebx
comma
id|c-&gt;x86_mask
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|c-&gt;x86_mask
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * B-stepping [M-P4-M] &n;&t;&t;&t; * sample has ebx = 0x0f, production has 0x0e.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|ebx
op_eq
l_int|0x0e
)paren
op_logical_or
(paren
id|ebx
op_eq
l_int|0x0f
)paren
)paren
r_return
id|SPEEDSTEP_PROCESSOR_P4M
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * C-stepping [M-P4-M]&n;&t;&t;&t; * needs to have ebx=0x0e, else it&squot;s a celeron:&n;&t;&t;&t; * cf. 25130917.pdf / page 7, footnote 5 even&n;&t;&t;&t; * though 25072120.pdf / page 7 doesn&squot;t say&n;&t;&t;&t; * samples are only of B-stepping...&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ebx
op_eq
l_int|0x0e
)paren
r_return
id|SPEEDSTEP_PROCESSOR_P4M
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * D-stepping [M-P4-M or M-P4/533]&n;&t;&t;&t; *&n;&t;&t;&t; * this is totally strange: CPUID 0x0F29 is&n;&t;&t;&t; * used by M-P4-M, M-P4/533 and(!) Celeron CPUs.&n;&t;&t;&t; * The latter need to be sorted out as they don&squot;t&n;&t;&t;&t; * support speedstep.&n;&t;&t;&t; * Celerons with CPUID 0x0F29 may have either&n;&t;&t;&t; * ebx=0x8 or 0xf -- 25130917.pdf doesn&squot;t say anything&n;&t;&t;&t; * specific.&n;&t;&t;&t; * M-P4-Ms may have either ebx=0xe or 0xf [see above]&n;&t;&t;&t; * M-P4/533 have either ebx=0xe or 0xf. [25317607.pdf]&n;&t;&t;&t; * also, M-P4M HTs have ebx=0x8, too&n;&t;&t;&t; * For now, they are distinguished by the model_id string&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|ebx
op_eq
l_int|0x0e
)paren
op_logical_or
(paren
id|strstr
c_func
(paren
id|c-&gt;x86_model_id
comma
l_string|&quot;Mobile Intel(R) Pentium(R) 4&quot;
)paren
op_ne
l_int|NULL
)paren
)paren
r_return
id|SPEEDSTEP_PROCESSOR_P4M
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|c-&gt;x86_model
)paren
(brace
r_case
l_int|0x0B
suffix:colon
multiline_comment|/* Intel PIII [Tualatin] */
multiline_comment|/* cpuid_ebx(1) is 0x04 for desktop PIII, &n;&t;&t;                   0x06 for mobile PIII-M */
id|ebx
op_assign
id|cpuid_ebx
c_func
(paren
l_int|0x00000001
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;ebx is %x&bslash;n&quot;
comma
id|ebx
)paren
suffix:semicolon
id|ebx
op_and_assign
l_int|0x000000FF
suffix:semicolon
r_if
c_cond
(paren
id|ebx
op_ne
l_int|0x06
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* So far all PIII-M processors support SpeedStep. See&n;&t;&t; * Intel&squot;s 24540640.pdf of June 2003 &n;&t;&t; */
r_return
id|SPEEDSTEP_PROCESSOR_PIII_T
suffix:semicolon
r_case
l_int|0x08
suffix:colon
multiline_comment|/* Intel PIII [Coppermine] */
multiline_comment|/* all mobile PIII Coppermines have FSB 100 MHz&n;&t;&t; * ==&gt; sort out a few desktop PIIIs. */
id|rdmsr
c_func
(paren
id|MSR_IA32_EBL_CR_POWERON
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;Coppermine: MSR_IA32_EBL_CR_POWERON is 0x%x, 0x%x&bslash;n&quot;
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|msr_lo
op_and_assign
l_int|0x00c0000
suffix:semicolon
r_if
c_cond
(paren
id|msr_lo
op_ne
l_int|0x0080000
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the processor is a mobile version,&n;&t;&t; * platform ID has bit 50 set&n;&t;&t; * it has SpeedStep technology if either&n;&t;&t; * bit 56 or 57 is set&n;&t;&t; */
id|rdmsr
c_func
(paren
id|MSR_IA32_PLATFORM_ID
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;Coppermine: MSR_IA32_PLATFORM ID is 0x%x, 0x%x&bslash;n&quot;
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|msr_hi
op_amp
(paren
l_int|1
op_lshift
l_int|18
)paren
)paren
op_logical_and
(paren
id|relaxed_check
ques
c_cond
l_int|1
suffix:colon
(paren
id|msr_hi
op_amp
(paren
l_int|3
op_lshift
l_int|24
)paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|c-&gt;x86_mask
op_eq
l_int|0x01
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;early PIII version&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|SPEEDSTEP_PROCESSOR_PIII_C_EARLY
suffix:semicolon
)brace
r_else
r_return
id|SPEEDSTEP_PROCESSOR_PIII_C
suffix:semicolon
)brace
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|speedstep_detect_processor
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|speedstep_detect_processor
)paren
suffix:semicolon
multiline_comment|/*********************************************************************&n; *                     DETECT SPEEDSTEP SPEEDS                       *&n; *********************************************************************/
DECL|function|speedstep_get_freqs
r_int
r_int
id|speedstep_get_freqs
c_func
(paren
r_int
r_int
id|processor
comma
r_int
r_int
op_star
id|low_speed
comma
r_int
r_int
op_star
id|high_speed
comma
r_void
(paren
op_star
id|set_state
)paren
(paren
r_int
r_int
id|state
)paren
)paren
(brace
r_int
r_int
id|prev_speed
suffix:semicolon
r_int
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|processor
)paren
op_logical_or
(paren
op_logical_neg
id|low_speed
)paren
op_logical_or
(paren
op_logical_neg
id|high_speed
)paren
op_logical_or
(paren
op_logical_neg
id|set_state
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;trying to determine both speeds&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* get current speed */
id|prev_speed
op_assign
id|speedstep_get_processor_frequency
c_func
(paren
id|processor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prev_speed
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;previous seped is %u&bslash;n&quot;
comma
id|prev_speed
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* switch to low state */
id|set_state
c_func
(paren
id|SPEEDSTEP_LOW
)paren
suffix:semicolon
op_star
id|low_speed
op_assign
id|speedstep_get_processor_frequency
c_func
(paren
id|processor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|low_speed
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;low seped is %u&bslash;n&quot;
comma
op_star
id|low_speed
)paren
suffix:semicolon
multiline_comment|/* switch to high state */
id|set_state
c_func
(paren
id|SPEEDSTEP_HIGH
)paren
suffix:semicolon
op_star
id|high_speed
op_assign
id|speedstep_get_processor_frequency
c_func
(paren
id|processor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|high_speed
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;high seped is %u&bslash;n&quot;
comma
op_star
id|high_speed
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|low_speed
op_eq
op_star
id|high_speed
)paren
(brace
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* switch to previous state, if necessary */
r_if
c_cond
(paren
op_star
id|high_speed
op_ne
id|prev_speed
)paren
id|set_state
c_func
(paren
id|SPEEDSTEP_LOW
)paren
suffix:semicolon
id|out
suffix:colon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
DECL|variable|speedstep_get_freqs
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|speedstep_get_freqs
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_SPEEDSTEP_RELAXED_CAP_CHECK
id|module_param
c_func
(paren
id|relaxed_check
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|relaxed_check
comma
l_string|&quot;Don&squot;t do all checks for speedstep capability.&quot;
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_AUTHOR
(paren
l_string|&quot;Dominik Brodowski &lt;linux@brodo.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;Library for Intel SpeedStep 1 or 2 cpufreq drivers.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
