multiline_comment|/*&n; *  (C) 2001-2003  Dave Jones. &lt;davej@suse.de&gt;&n; *  (C) 2002  Padraig Brady. &lt;padraig@antefacto.com&gt;&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *  Based upon datasheets &amp; sample CPUs kindly provided by VIA.&n; *&n; *  VIA have currently 3 different versions of Longhaul.&n; *&n; *  +---------------------+----------+---------------------------------+&n; *  | Marketing name      | Codename | longhaul version / features.    |&n; *  +---------------------+----------+---------------------------------+&n; *  |  Samuel/CyrixIII    |   C5A    | v1 : multipliers only           |&n; *  |  Samuel2/C3         | C3E/C5B  | v1 : multiplier only            |&n; *  |  Ezra               |   C5C    | v2 : multipliers &amp; voltage      |&n; *  |  Ezra-T             | C5M/C5N  | v3 : multipliers, voltage &amp; FSB |&n; *  +---------------------+----------+---------------------------------+&n; *&n; *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/timex.h&gt;
macro_line|#include &lt;asm/io.h&gt;
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
multiline_comment|/*&n; * Clock ratio tables.&n; * The eblcr ones specify the ratio read from the CPU.&n; * The clock_ratio ones specify what to write to the CPU.&n; */
multiline_comment|/* VIA C3 Samuel 1  &amp; Samuel 2 (stepping 0)*/
DECL|variable|longhaul1_clock_ratio
r_static
r_int
id|__initdata
id|longhaul1_clock_ratio
(braket
l_int|16
)braket
op_assign
(brace
op_minus
l_int|1
comma
multiline_comment|/* 0000 -&gt; RESERVED */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
op_minus
l_int|1
comma
multiline_comment|/* 0011 -&gt; RESERVED */
op_minus
l_int|1
comma
multiline_comment|/* 0100 -&gt; RESERVED */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
l_int|55
comma
multiline_comment|/* 0111 -&gt;  5.5x */
l_int|60
comma
multiline_comment|/* 1000 -&gt;  6.0x */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|50
comma
multiline_comment|/* 1011 -&gt;  5.0x */
l_int|65
comma
multiline_comment|/* 1100 -&gt;  6.5x */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
op_minus
l_int|1
comma
multiline_comment|/* 1110 -&gt; RESERVED */
op_minus
l_int|1
comma
multiline_comment|/* 1111 -&gt; RESERVED */
)brace
suffix:semicolon
DECL|variable|samuel1_eblcr
r_static
r_int
id|__initdata
id|samuel1_eblcr
(braket
l_int|16
)braket
op_assign
(brace
l_int|50
comma
multiline_comment|/* 0000 -&gt; RESERVED */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
op_minus
l_int|1
comma
multiline_comment|/* 0011 -&gt; RESERVED */
l_int|55
comma
multiline_comment|/* 0100 -&gt;  5.5x */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
op_minus
l_int|1
comma
multiline_comment|/* 0111 -&gt; RESERVED */
op_minus
l_int|1
comma
multiline_comment|/* 1000 -&gt; RESERVED */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|60
comma
multiline_comment|/* 1011 -&gt;  6.0x */
op_minus
l_int|1
comma
multiline_comment|/* 1100 -&gt; RESERVED */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
op_minus
l_int|1
comma
multiline_comment|/* 1110 -&gt; RESERVED */
l_int|65
comma
multiline_comment|/* 1111 -&gt;  6.5x */
)brace
suffix:semicolon
multiline_comment|/* VIA C3 Samuel2 Stepping 1-&gt;15 &amp; VIA C3 Ezra */
DECL|variable|longhaul2_clock_ratio
r_static
r_int
id|__initdata
id|longhaul2_clock_ratio
(braket
l_int|16
)braket
op_assign
(brace
l_int|100
comma
multiline_comment|/* 0000 -&gt; 10.0x */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
l_int|90
comma
multiline_comment|/* 0011 -&gt;  9.0x */
l_int|95
comma
multiline_comment|/* 0100 -&gt;  9.5x */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
l_int|55
comma
multiline_comment|/* 0111 -&gt;  5.5x */
l_int|60
comma
multiline_comment|/* 1000 -&gt;  6.0x */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|50
comma
multiline_comment|/* 1011 -&gt;  5.0x */
l_int|65
comma
multiline_comment|/* 1100 -&gt;  6.5x */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
l_int|85
comma
multiline_comment|/* 1110 -&gt;  8.5x */
l_int|120
comma
multiline_comment|/* 1111 -&gt; 12.0x */
)brace
suffix:semicolon
DECL|variable|samuel2_eblcr
r_static
r_int
id|__initdata
id|samuel2_eblcr
(braket
l_int|16
)braket
op_assign
(brace
l_int|50
comma
multiline_comment|/* 0000 -&gt;  5.0x */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
l_int|100
comma
multiline_comment|/* 0011 -&gt; 10.0x */
l_int|55
comma
multiline_comment|/* 0100 -&gt;  5.5x */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
l_int|110
comma
multiline_comment|/* 0111 -&gt; 11.0x */
l_int|90
comma
multiline_comment|/* 1000 -&gt;  9.0x */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|60
comma
multiline_comment|/* 1011 -&gt;  6.0x */
l_int|120
comma
multiline_comment|/* 1100 -&gt; 12.0x */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
l_int|130
comma
multiline_comment|/* 1110 -&gt; 13.0x */
l_int|65
comma
multiline_comment|/* 1111 -&gt;  6.5x */
)brace
suffix:semicolon
DECL|variable|ezra_eblcr
r_static
r_int
id|__initdata
id|ezra_eblcr
(braket
l_int|16
)braket
op_assign
(brace
l_int|50
comma
multiline_comment|/* 0000 -&gt;  5.0x */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
l_int|100
comma
multiline_comment|/* 0011 -&gt; 10.0x */
l_int|55
comma
multiline_comment|/* 0100 -&gt;  5.5x */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
l_int|95
comma
multiline_comment|/* 0111 -&gt;  9.5x */
l_int|90
comma
multiline_comment|/* 1000 -&gt;  9.0x */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|60
comma
multiline_comment|/* 1011 -&gt;  6.0x */
l_int|120
comma
multiline_comment|/* 1100 -&gt; 12.0x */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
l_int|85
comma
multiline_comment|/* 1110 -&gt;  8.5x */
l_int|65
comma
multiline_comment|/* 1111 -&gt;  6.5x */
)brace
suffix:semicolon
multiline_comment|/* VIA C5M. */
DECL|variable|longhaul3_clock_ratio
r_static
r_int
id|__initdata
id|longhaul3_clock_ratio
(braket
l_int|32
)braket
op_assign
(brace
l_int|100
comma
multiline_comment|/* 0000 -&gt; 10.0x */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
l_int|90
comma
multiline_comment|/* 0011 -&gt;  9.0x */
l_int|95
comma
multiline_comment|/* 0100 -&gt;  9.5x */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
l_int|55
comma
multiline_comment|/* 0111 -&gt;  5.5x */
l_int|60
comma
multiline_comment|/* 1000 -&gt;  6.0x */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|50
comma
multiline_comment|/* 1011 -&gt;  5.0x */
l_int|65
comma
multiline_comment|/* 1100 -&gt;  6.5x */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
l_int|85
comma
multiline_comment|/* 1110 -&gt;  8.5x */
l_int|120
comma
multiline_comment|/* 1111 -&gt;  12.0x */
op_minus
l_int|1
comma
multiline_comment|/* 0000 -&gt; RESERVED (10.0x) */
l_int|110
comma
multiline_comment|/* 0001 -&gt; 11.0x */
l_int|120
comma
multiline_comment|/* 0010 -&gt; 12.0x */
op_minus
l_int|1
comma
multiline_comment|/* 0011 -&gt; RESERVED (9.0x)*/
l_int|105
comma
multiline_comment|/* 0100 -&gt; 10.5x */
l_int|115
comma
multiline_comment|/* 0101 -&gt; 11.5x */
l_int|125
comma
multiline_comment|/* 0110 -&gt; 12.5x */
l_int|135
comma
multiline_comment|/* 0111 -&gt; 13.5x */
l_int|140
comma
multiline_comment|/* 1000 -&gt; 14.0x */
l_int|150
comma
multiline_comment|/* 1001 -&gt; 15.0x */
l_int|160
comma
multiline_comment|/* 1010 -&gt; 16.0x */
l_int|130
comma
multiline_comment|/* 1011 -&gt; 13.0x */
l_int|145
comma
multiline_comment|/* 1100 -&gt; 14.5x */
l_int|155
comma
multiline_comment|/* 1101 -&gt; 15.5x */
op_minus
l_int|1
comma
multiline_comment|/* 1110 -&gt; RESERVED (13.0x) */
op_minus
l_int|1
comma
multiline_comment|/* 1111 -&gt; RESERVED (12.0x) */
)brace
suffix:semicolon
DECL|variable|c5m_eblcr
r_static
r_int
id|__initdata
id|c5m_eblcr
(braket
l_int|32
)braket
op_assign
(brace
l_int|50
comma
multiline_comment|/* 0000 -&gt;  5.0x */
l_int|30
comma
multiline_comment|/* 0001 -&gt;  3.0x */
l_int|40
comma
multiline_comment|/* 0010 -&gt;  4.0x */
l_int|100
comma
multiline_comment|/* 0011 -&gt; 10.0x */
l_int|55
comma
multiline_comment|/* 0100 -&gt;  5.5x */
l_int|35
comma
multiline_comment|/* 0101 -&gt;  3.5x */
l_int|45
comma
multiline_comment|/* 0110 -&gt;  4.5x */
l_int|95
comma
multiline_comment|/* 0111 -&gt;  9.5x */
l_int|90
comma
multiline_comment|/* 1000 -&gt;  9.0x */
l_int|70
comma
multiline_comment|/* 1001 -&gt;  7.0x */
l_int|80
comma
multiline_comment|/* 1010 -&gt;  8.0x */
l_int|60
comma
multiline_comment|/* 1011 -&gt;  6.0x */
l_int|120
comma
multiline_comment|/* 1100 -&gt; 12.0x */
l_int|75
comma
multiline_comment|/* 1101 -&gt;  7.5x */
l_int|85
comma
multiline_comment|/* 1110 -&gt;  8.5x */
l_int|65
comma
multiline_comment|/* 1111 -&gt;  6.5x */
op_minus
l_int|1
comma
multiline_comment|/* 0000 -&gt; RESERVED (9.0x) */
l_int|110
comma
multiline_comment|/* 0001 -&gt; 11.0x */
l_int|120
comma
multiline_comment|/* 0010 -&gt; 12.0x */
op_minus
l_int|1
comma
multiline_comment|/* 0011 -&gt; RESERVED (10.0x)*/
l_int|135
comma
multiline_comment|/* 0100 -&gt; 13.5x */
l_int|115
comma
multiline_comment|/* 0101 -&gt; 11.5x */
l_int|125
comma
multiline_comment|/* 0110 -&gt; 12.5x */
l_int|105
comma
multiline_comment|/* 0111 -&gt; 10.5x */
l_int|130
comma
multiline_comment|/* 1000 -&gt; 13.0x */
l_int|150
comma
multiline_comment|/* 1001 -&gt; 15.0x */
l_int|160
comma
multiline_comment|/* 1010 -&gt; 16.0x */
l_int|140
comma
multiline_comment|/* 1011 -&gt; 14.0x */
op_minus
l_int|1
comma
multiline_comment|/* 1100 -&gt; RESERVED (12.0x) */
l_int|155
comma
multiline_comment|/* 1101 -&gt; 15.5x */
op_minus
l_int|1
comma
multiline_comment|/* 1110 -&gt; RESERVED (13.0x) */
l_int|145
comma
multiline_comment|/* 1111 -&gt; 14.5x */
)brace
suffix:semicolon
multiline_comment|/* Voltage scales. Div by 1000 to get actual voltage. */
DECL|variable|vrm85scales
r_static
r_int
id|__initdata
id|vrm85scales
(braket
l_int|32
)braket
op_assign
(brace
l_int|1250
comma
l_int|1200
comma
l_int|1150
comma
l_int|1100
comma
l_int|1050
comma
l_int|1800
comma
l_int|1750
comma
l_int|1700
comma
l_int|1650
comma
l_int|1600
comma
l_int|1550
comma
l_int|1500
comma
l_int|1450
comma
l_int|1400
comma
l_int|1350
comma
l_int|1300
comma
l_int|1275
comma
l_int|1225
comma
l_int|1175
comma
l_int|1125
comma
l_int|1075
comma
l_int|1825
comma
l_int|1775
comma
l_int|1725
comma
l_int|1675
comma
l_int|1625
comma
l_int|1575
comma
l_int|1525
comma
l_int|1475
comma
l_int|1425
comma
l_int|1375
comma
l_int|1325
comma
)brace
suffix:semicolon
DECL|variable|mobilevrmscales
r_static
r_int
id|__initdata
id|mobilevrmscales
(braket
l_int|32
)braket
op_assign
(brace
l_int|2000
comma
l_int|1950
comma
l_int|1900
comma
l_int|1850
comma
l_int|1800
comma
l_int|1750
comma
l_int|1700
comma
l_int|1650
comma
l_int|1600
comma
l_int|1550
comma
l_int|1500
comma
l_int|1450
comma
l_int|1500
comma
l_int|1350
comma
l_int|1300
comma
op_minus
l_int|1
comma
l_int|1275
comma
l_int|1250
comma
l_int|1225
comma
l_int|1200
comma
l_int|1175
comma
l_int|1150
comma
l_int|1125
comma
l_int|1100
comma
l_int|1075
comma
l_int|1050
comma
l_int|1025
comma
l_int|1000
comma
l_int|975
comma
l_int|950
comma
l_int|925
comma
op_minus
l_int|1
comma
)brace
suffix:semicolon
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
DECL|variable|longhaul
r_static
r_int
id|longhaul
suffix:semicolon
multiline_comment|/* version. */
DECL|variable|longhaul_table
r_static
r_struct
id|cpufreq_frequency_table
op_star
id|longhaul_table
suffix:semicolon
DECL|function|longhaul_get_cpu_fsb
r_static
r_int
id|longhaul_get_cpu_fsb
(paren
r_void
)paren
(brace
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
r_if
c_cond
(paren
id|fsb
op_eq
l_int|0
)paren
(brace
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
r_return
id|eblcr_fsb_table
(braket
id|invalue
)braket
suffix:semicolon
)brace
r_else
(brace
r_return
id|fsb
suffix:semicolon
)brace
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
id|longhaul
op_eq
l_int|3
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
multiline_comment|/**&n; * longhaul_set_cpu_frequency()&n; * @clock_ratio_index : index of clock_ratio[] for new frequency&n; *&n; * Sets a new clock ratio, and -if applicable- a new Front Side Bus&n; */
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
r_int
id|lo
comma
id|hi
suffix:semicolon
r_int
r_int
id|bits
suffix:semicolon
r_int
id|vidindex
comma
id|i
suffix:semicolon
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
r_if
c_cond
(paren
id|clock_ratio
(braket
id|clock_ratio_index
)braket
op_eq
op_minus
l_int|1
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|clock_ratio
(braket
id|clock_ratio_index
)braket
op_star
id|fsb
op_star
l_int|100
)paren
OG
id|highest_speed
)paren
op_logical_or
(paren
(paren
id|clock_ratio
(braket
id|clock_ratio_index
)braket
op_star
id|fsb
op_star
l_int|100
)paren
OL
id|lowest_speed
)paren
)paren
r_return
suffix:semicolon
id|freqs.old
op_assign
id|longhaul_get_cpu_mult
c_func
(paren
)paren
op_star
id|longhaul_get_cpu_fsb
c_func
(paren
)paren
op_star
l_int|100
suffix:semicolon
id|freqs
dot
r_new
op_assign
id|clock_ratio
(braket
id|clock_ratio_index
)braket
op_star
id|fsb
op_star
l_int|100
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
l_string|&quot;FSB:%d Mult(x10):%d&bslash;n&quot;
comma
id|fsb
op_star
l_int|100
comma
id|clock_ratio
(braket
id|clock_ratio_index
)braket
)paren
suffix:semicolon
id|bits
op_assign
id|clock_ratio_index
suffix:semicolon
multiline_comment|/* &quot;bits&quot; contains the bitpattern of the new multiplier.&n;&t;   we now need to transform it to the desired format. */
r_switch
c_cond
(paren
id|longhaul
)paren
(brace
r_case
l_int|1
suffix:colon
id|rdmsr
(paren
id|MSR_VIA_BCR2
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
multiline_comment|/* Enable software clock multiplier */
id|lo
op_or_assign
(paren
l_int|1
op_lshift
l_int|19
)paren
suffix:semicolon
multiline_comment|/* desired multiplier */
id|lo
op_and_assign
op_complement
(paren
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
op_or
l_int|1
op_lshift
l_int|26
)paren
suffix:semicolon
id|lo
op_or_assign
(paren
id|bits
op_lshift
l_int|23
)paren
suffix:semicolon
id|wrmsr
(paren
id|MSR_VIA_BCR2
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|__hlt
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Disable software clock multiplier */
id|rdmsr
(paren
id|MSR_VIA_BCR2
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|lo
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|19
)paren
suffix:semicolon
id|wrmsr
(paren
id|MSR_VIA_BCR2
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|rdmsr
(paren
id|MSR_VIA_LONGHAUL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|lo
op_and_assign
l_int|0xfff0bf0f
suffix:semicolon
multiline_comment|/* reset [19:16,14](bus ratio) and [7:4](rev key) to 0 */
id|lo
op_or_assign
(paren
id|bits
op_lshift
l_int|16
)paren
suffix:semicolon
id|lo
op_or_assign
(paren
l_int|1
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* EnableSoftBusRatio */
multiline_comment|/* We must program the revision key only with values we&n;&t;&t; * know about, not blindly copy it from 0:3 */
id|lo
op_or_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|can_scale_voltage
)paren
(brace
multiline_comment|/* PB: TODO fix this up */
id|vidindex
op_assign
(paren
(paren
(paren
id|highest_speed
op_minus
id|lowest_speed
)paren
op_div
(paren
id|fsb
op_div
l_int|2
)paren
)paren
op_minus
(paren
(paren
id|highest_speed
op_minus
(paren
(paren
id|clock_ratio
(braket
id|clock_ratio_index
)braket
op_star
id|fsb
op_star
l_int|100
)paren
op_div
l_int|1000
)paren
)paren
op_div
(paren
id|fsb
op_div
l_int|2
)paren
)paren
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dprintk
(paren
id|KERN_INFO
l_string|&quot;VID hunting. Looking for %d, found %d&bslash;n&quot;
comma
id|minvid
op_plus
(paren
id|vidindex
op_star
l_int|25
)paren
comma
id|voltage_table
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|voltage_table
(braket
id|i
)braket
op_eq
(paren
id|minvid
op_plus
(paren
id|vidindex
op_star
l_int|25
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|32
)paren
r_goto
id|bad_voltage
suffix:semicolon
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Desired vid index=%d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
macro_line|#if 0
id|lo
op_and_assign
l_int|0xfe0fffff
suffix:semicolon
multiline_comment|/* reset [24:20](voltage) to 0 */
id|lo
op_or_assign
(paren
id|i
op_lshift
l_int|20
)paren
suffix:semicolon
multiline_comment|/* set voltage */
id|lo
op_or_assign
(paren
l_int|1
op_lshift
l_int|9
)paren
suffix:semicolon
multiline_comment|/* EnableSoftVID */
macro_line|#endif
)brace
id|bad_voltage
suffix:colon
id|wrmsr
(paren
id|MSR_VIA_LONGHAUL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|__hlt
c_func
(paren
)paren
suffix:semicolon
id|rdmsr
(paren
id|MSR_VIA_LONGHAUL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|lo
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|can_scale_voltage
)paren
id|lo
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|9
)paren
suffix:semicolon
id|lo
op_or_assign
l_int|1
suffix:semicolon
multiline_comment|/* Revision Key */
id|wrmsr
(paren
id|MSR_VIA_LONGHAUL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|rdmsr
(paren
id|MSR_VIA_LONGHAUL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|lo
op_and_assign
l_int|0xfff0bf0f
suffix:semicolon
multiline_comment|/* reset longhaul[19:16,14] to 0 */
id|lo
op_or_assign
(paren
id|bits
op_lshift
l_int|16
)paren
suffix:semicolon
id|lo
op_or_assign
(paren
l_int|1
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* EnableSoftBusRatio */
multiline_comment|/* We must program the revision key only with values we&n;&t;&t; * know about, not blindly copy it from 0:3 */
id|lo
op_or_assign
l_int|3
suffix:semicolon
multiline_comment|/* SoftVID &amp; SoftBSEL */
id|wrmsr
(paren
id|MSR_VIA_LONGHAUL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|__hlt
c_func
(paren
)paren
suffix:semicolon
id|rdmsr
(paren
id|MSR_VIA_LONGHAUL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|lo
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|8
)paren
suffix:semicolon
id|lo
op_or_assign
l_int|3
suffix:semicolon
id|wrmsr
(paren
id|MSR_VIA_LONGHAUL
comma
id|lo
comma
id|hi
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
DECL|function|longhaul_get_ranges
r_static
r_int
id|__init
id|longhaul_get_ranges
(paren
r_void
)paren
(brace
r_int
r_int
id|lo
comma
id|hi
comma
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
r_switch
c_cond
(paren
id|longhaul
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
r_break
suffix:semicolon
r_case
l_int|2
dot
dot
dot
l_int|3
suffix:colon
id|rdmsr
(paren
id|MSR_VIA_LONGHAUL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|invalue
op_assign
(paren
id|hi
op_amp
(paren
l_int|1
op_lshift
l_int|0
op_or
l_int|1
op_lshift
l_int|1
op_or
l_int|1
op_lshift
l_int|2
op_or
l_int|1
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi
op_amp
(paren
l_int|1
op_lshift
l_int|11
)paren
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
macro_line|#if 0&t;/* This is MaxMhz @ Min Voltage. Ignore for now */
id|invalue
op_assign
(paren
id|hi
op_amp
(paren
l_int|1
op_lshift
l_int|16
op_or
l_int|1
op_lshift
l_int|17
op_or
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
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|hi
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
id|minmult
op_assign
id|multipliers
(braket
id|invalue
)braket
suffix:semicolon
macro_line|#else
id|minmult
op_assign
l_int|30
suffix:semicolon
multiline_comment|/* as per spec */
macro_line|#endif
r_break
suffix:semicolon
)brace
id|highest_speed
op_assign
id|maxmult
op_star
id|fsb
op_star
l_int|100
suffix:semicolon
id|lowest_speed
op_assign
id|minmult
op_star
id|fsb
op_star
l_int|100
suffix:semicolon
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;MinMult(x10)=%d MaxMult(x10)=%d&bslash;n&quot;
comma
id|minmult
comma
id|maxmult
)paren
suffix:semicolon
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Lowestspeed=%d Highestspeed=%d&bslash;n&quot;
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
(paren
id|j
OL
id|numscales
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|clock_ratio
(braket
id|j
)braket
op_eq
op_minus
l_int|1
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|clock_ratio
(braket
id|j
)braket
OG
id|maxmult
)paren
op_logical_or
(paren
(paren
r_int
r_int
)paren
id|clock_ratio
(braket
id|j
)braket
OL
id|minmult
)paren
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
id|clock_ratio
(braket
id|j
)braket
op_star
id|fsb
op_star
l_int|100
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
(paren
r_int
r_int
id|lo
comma
r_int
r_int
id|hi
)paren
(brace
r_int
id|revkey
suffix:semicolon
id|minvid
op_assign
(paren
id|hi
op_amp
(paren
l_int|1
op_lshift
l_int|20
op_or
l_int|1
op_lshift
l_int|21
op_or
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
)paren
)paren
op_rshift
l_int|20
suffix:semicolon
multiline_comment|/* 56:52 */
id|maxvid
op_assign
(paren
id|hi
op_amp
(paren
l_int|1
op_lshift
l_int|4
op_or
l_int|1
op_lshift
l_int|5
op_or
l_int|1
op_lshift
l_int|6
op_or
l_int|1
op_lshift
l_int|7
op_or
l_int|1
op_lshift
l_int|8
)paren
)paren
op_rshift
l_int|4
suffix:semicolon
multiline_comment|/* 40:36 */
id|vrmrev
op_assign
(paren
id|lo
op_amp
(paren
l_int|1
op_lshift
l_int|15
)paren
)paren
op_rshift
l_int|15
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
id|revkey
op_assign
(paren
id|lo
op_amp
l_int|0xf
)paren
op_lshift
l_int|4
suffix:semicolon
multiline_comment|/* Rev key. */
id|lo
op_or_assign
id|revkey
suffix:semicolon
multiline_comment|/* Reinsert key FIXME: This is bad. */
id|lo
op_and_assign
l_int|0xfe0fff0f
suffix:semicolon
multiline_comment|/* Mask unneeded bits */
id|lo
op_or_assign
(paren
l_int|1
op_lshift
l_int|9
)paren
suffix:semicolon
multiline_comment|/* EnableSoftVID */
id|lo
op_or_assign
id|maxvid
op_lshift
l_int|20
suffix:semicolon
id|wrmsr
(paren
id|MSR_VIA_LONGHAUL
comma
id|lo
comma
id|hi
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
multiline_comment|/* VIA C3 Samuel C5A */
id|longhaul
op_assign
l_int|1
suffix:semicolon
id|memcpy
(paren
id|clock_ratio
comma
id|longhaul1_clock_ratio
comma
r_sizeof
(paren
id|longhaul1_clock_ratio
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
r_switch
c_cond
(paren
id|c-&gt;x86_mask
)paren
(brace
r_case
l_int|0
suffix:colon
id|longhaul
op_assign
l_int|1
suffix:semicolon
id|memcpy
(paren
id|clock_ratio
comma
id|longhaul1_clock_ratio
comma
r_sizeof
(paren
id|longhaul1_clock_ratio
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
id|longhaul
op_assign
l_int|2
suffix:semicolon
id|memcpy
(paren
id|clock_ratio
comma
id|longhaul2_clock_ratio
comma
r_sizeof
(paren
id|longhaul2_clock_ratio
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
multiline_comment|/* C5M/C5N */
r_return
op_minus
id|ENODEV
suffix:semicolon
singleline_comment|// Waiting on updated docs from VIA before this is usable
id|longhaul
op_assign
l_int|3
suffix:semicolon
id|numscales
op_assign
l_int|32
suffix:semicolon
id|memcpy
(paren
id|clock_ratio
comma
id|longhaul3_clock_ratio
comma
r_sizeof
(paren
id|longhaul3_clock_ratio
)paren
)paren
suffix:semicolon
id|memcpy
(paren
id|eblcr_table
comma
id|c5m_eblcr
comma
r_sizeof
(paren
id|c5m_eblcr
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;VIA CPU detected. Longhaul version %d supported&bslash;n&quot;
comma
id|longhaul
)paren
suffix:semicolon
r_if
c_cond
(paren
id|longhaul
op_eq
l_int|2
op_logical_or
id|longhaul
op_eq
l_int|3
)paren
(brace
r_int
r_int
id|lo
comma
id|hi
suffix:semicolon
id|rdmsr
(paren
id|MSR_VIA_LONGHAUL
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lo
op_amp
(paren
l_int|1
op_lshift
l_int|0
)paren
)paren
op_logical_and
(paren
id|dont_scale_voltage
op_eq
l_int|0
)paren
)paren
id|longhaul_setup_voltagescaling
(paren
id|lo
comma
id|hi
)paren
suffix:semicolon
)brace
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
id|policy-&gt;policy
op_assign
id|CPUFREQ_POLICY_PERFORMANCE
suffix:semicolon
id|policy-&gt;cpuinfo.transition_latency
op_assign
id|CPUFREQ_ETERNAL
suffix:semicolon
id|policy-&gt;cur
op_assign
(paren
r_int
r_int
)paren
(paren
id|longhaul_get_cpu_fsb
c_func
(paren
)paren
op_star
id|longhaul_get_cpu_mult
c_func
(paren
)paren
op_star
l_int|100
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
(paren
id|c-&gt;x86_vendor
op_ne
id|X86_VENDOR_CENTAUR
)paren
op_logical_or
(paren
id|c-&gt;x86
op_ne
l_int|6
)paren
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
l_int|7
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
l_int|8
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Unknown VIA CPU. Contact davej@suse.de&bslash;n&quot;
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
l_string|&quot;Dave Jones &lt;davej@suse.de&gt;&quot;
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
