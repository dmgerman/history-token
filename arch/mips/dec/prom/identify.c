multiline_comment|/*&n; * identify.c: machine identification code.&n; *&n; * Copyright (C) 1998 Harald Koerfgen and Paul M. Antoine&n; * Copyright (C) 2002, 2003, 2004  Maciej W. Rozycki&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/dec/ioasic.h&gt;
macro_line|#include &lt;asm/dec/ioasic_addrs.h&gt;
macro_line|#include &lt;asm/dec/kn01.h&gt;
macro_line|#include &lt;asm/dec/kn02.h&gt;
macro_line|#include &lt;asm/dec/kn02ba.h&gt;
macro_line|#include &lt;asm/dec/kn02ca.h&gt;
macro_line|#include &lt;asm/dec/kn03.h&gt;
macro_line|#include &lt;asm/dec/kn230.h&gt;
macro_line|#include &lt;asm/dec/prom.h&gt;
macro_line|#include &quot;dectypes.h&quot;
r_extern
r_int
r_int
id|mips_machgroup
suffix:semicolon
r_extern
r_int
r_int
id|mips_machtype
suffix:semicolon
DECL|variable|dec_system_strings
r_static
r_const
r_char
op_star
id|dec_system_strings
(braket
)braket
op_assign
(brace
(braket
id|MACH_DSUNKNOWN
)braket
l_string|&quot;unknown DECstation&quot;
comma
(braket
id|MACH_DS23100
)braket
l_string|&quot;DECstation 2100/3100&quot;
comma
(braket
id|MACH_DS5100
)braket
l_string|&quot;DECsystem 5100&quot;
comma
(braket
id|MACH_DS5000_200
)braket
l_string|&quot;DECstation 5000/200&quot;
comma
(braket
id|MACH_DS5000_1XX
)braket
l_string|&quot;DECstation 5000/1xx&quot;
comma
(braket
id|MACH_DS5000_XX
)braket
l_string|&quot;Personal DECstation 5000/xx&quot;
comma
(braket
id|MACH_DS5000_2X0
)braket
l_string|&quot;DECstation 5000/2x0&quot;
comma
(braket
id|MACH_DS5400
)braket
l_string|&quot;DECsystem 5400&quot;
comma
(braket
id|MACH_DS5500
)braket
l_string|&quot;DECsystem 5500&quot;
comma
(braket
id|MACH_DS5800
)braket
l_string|&quot;DECsystem 5800&quot;
comma
(braket
id|MACH_DS5900
)braket
l_string|&quot;DECsystem 5900&quot;
comma
)brace
suffix:semicolon
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
DECL|macro|STR_BUF_LEN
mdefine_line|#define STR_BUF_LEN&t;64
r_static
r_char
id|system
(braket
id|STR_BUF_LEN
)braket
suffix:semicolon
r_static
r_int
id|called
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|called
op_eq
l_int|0
)paren
(brace
id|called
op_assign
l_int|1
suffix:semicolon
id|snprintf
c_func
(paren
id|system
comma
id|STR_BUF_LEN
comma
l_string|&quot;Digital %s&quot;
comma
id|dec_system_strings
(braket
id|mips_machtype
)braket
)paren
suffix:semicolon
)brace
r_return
id|system
suffix:semicolon
)brace
multiline_comment|/*&n; * Setup essential system-specific memory addresses.  We need them&n; * early.  Semantically the functions belong to prom/init.c, but they&n; * are compact enough we want them inlined. --macro&n; */
DECL|variable|dec_rtc_base
r_volatile
id|u8
op_star
id|dec_rtc_base
suffix:semicolon
DECL|variable|dec_rtc_base
id|EXPORT_SYMBOL
c_func
(paren
id|dec_rtc_base
)paren
suffix:semicolon
DECL|function|prom_init_kn01
r_static
r_inline
r_void
id|prom_init_kn01
c_func
(paren
r_void
)paren
(brace
id|dec_rtc_base
op_assign
(paren
r_void
op_star
)paren
id|KN01_RTC_BASE
suffix:semicolon
id|dec_kn_slot_size
op_assign
id|KN01_SLOT_SIZE
suffix:semicolon
)brace
DECL|function|prom_init_kn230
r_static
r_inline
r_void
id|prom_init_kn230
c_func
(paren
r_void
)paren
(brace
id|dec_rtc_base
op_assign
(paren
r_void
op_star
)paren
id|KN01_RTC_BASE
suffix:semicolon
id|dec_kn_slot_size
op_assign
id|KN01_SLOT_SIZE
suffix:semicolon
)brace
DECL|function|prom_init_kn02
r_static
r_inline
r_void
id|prom_init_kn02
c_func
(paren
r_void
)paren
(brace
id|dec_rtc_base
op_assign
(paren
r_void
op_star
)paren
id|KN02_RTC_BASE
suffix:semicolon
id|dec_kn_slot_size
op_assign
id|KN02_SLOT_SIZE
suffix:semicolon
)brace
DECL|function|prom_init_kn02xa
r_static
r_inline
r_void
id|prom_init_kn02xa
c_func
(paren
r_void
)paren
(brace
id|ioasic_base
op_assign
(paren
r_void
op_star
)paren
id|KN02XA_IOASIC_BASE
suffix:semicolon
id|dec_rtc_base
op_assign
(paren
r_void
op_star
)paren
id|KN02XA_RTC_BASE
suffix:semicolon
id|dec_kn_slot_size
op_assign
id|IOASIC_SLOT_SIZE
suffix:semicolon
)brace
DECL|function|prom_init_kn03
r_static
r_inline
r_void
id|prom_init_kn03
c_func
(paren
r_void
)paren
(brace
id|ioasic_base
op_assign
(paren
r_void
op_star
)paren
id|KN03_IOASIC_BASE
suffix:semicolon
id|dec_rtc_base
op_assign
(paren
r_void
op_star
)paren
id|KN03_RTC_BASE
suffix:semicolon
id|dec_kn_slot_size
op_assign
id|IOASIC_SLOT_SIZE
suffix:semicolon
)brace
DECL|function|prom_identify_arch
r_void
id|__init
id|prom_identify_arch
c_func
(paren
id|u32
id|magic
)paren
(brace
r_int
r_char
id|dec_cpunum
comma
id|dec_firmrev
comma
id|dec_etc
comma
id|dec_systype
suffix:semicolon
id|u32
id|dec_sysid
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prom_is_rex
c_func
(paren
id|magic
)paren
)paren
(brace
id|dec_sysid
op_assign
id|simple_strtoul
c_func
(paren
id|prom_getenv
c_func
(paren
l_string|&quot;systype&quot;
)paren
comma
(paren
r_char
op_star
op_star
)paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|dec_sysid
op_assign
id|rex_getsysid
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dec_sysid
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Zero sysid returned from PROM! &quot;
l_string|&quot;Assuming a PMAX-like machine.&bslash;n&quot;
)paren
suffix:semicolon
id|dec_sysid
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|dec_cpunum
op_assign
(paren
id|dec_sysid
op_amp
l_int|0xff000000
)paren
op_rshift
l_int|24
suffix:semicolon
id|dec_systype
op_assign
(paren
id|dec_sysid
op_amp
l_int|0xff0000
)paren
op_rshift
l_int|16
suffix:semicolon
id|dec_firmrev
op_assign
(paren
id|dec_sysid
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
suffix:semicolon
id|dec_etc
op_assign
id|dec_sysid
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* We&squot;re obviously one of the DEC machines */
id|mips_machgroup
op_assign
id|MACH_GROUP_DEC
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME: This may not be an exhaustive list of DECStations/Servers!&n;&t; * Put all model-specific initialisation calls here.&n;&t; */
r_switch
c_cond
(paren
id|dec_systype
)paren
(brace
r_case
id|DS2100_3100
suffix:colon
id|mips_machtype
op_assign
id|MACH_DS23100
suffix:semicolon
id|prom_init_kn01
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DS5100
suffix:colon
multiline_comment|/* DS5100 MIPSMATE */
id|mips_machtype
op_assign
id|MACH_DS5100
suffix:semicolon
id|prom_init_kn230
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DS5000_200
suffix:colon
multiline_comment|/* DS5000 3max */
id|mips_machtype
op_assign
id|MACH_DS5000_200
suffix:semicolon
id|prom_init_kn02
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DS5000_1XX
suffix:colon
multiline_comment|/* DS5000/100 3min */
id|mips_machtype
op_assign
id|MACH_DS5000_1XX
suffix:semicolon
id|prom_init_kn02xa
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DS5000_2X0
suffix:colon
multiline_comment|/* DS5000/240 3max+ or DS5900 bigmax */
id|mips_machtype
op_assign
id|MACH_DS5000_2X0
suffix:semicolon
id|prom_init_kn03
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ioasic_read
c_func
(paren
id|IO_REG_SIR
)paren
op_amp
id|KN03_IO_INR_3MAXP
)paren
)paren
id|mips_machtype
op_assign
id|MACH_DS5900
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DS5000_XX
suffix:colon
multiline_comment|/* Personal DS5000/xx maxine */
id|mips_machtype
op_assign
id|MACH_DS5000_XX
suffix:semicolon
id|prom_init_kn02xa
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DS5800
suffix:colon
multiline_comment|/* DS5800 Isis */
id|mips_machtype
op_assign
id|MACH_DS5800
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DS5400
suffix:colon
multiline_comment|/* DS5400 MIPSfair */
id|mips_machtype
op_assign
id|MACH_DS5400
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DS5500
suffix:colon
multiline_comment|/* DS5500 MIPSfair-2 */
id|mips_machtype
op_assign
id|MACH_DS5500
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|mips_machtype
op_assign
id|MACH_DSUNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mips_machtype
op_eq
id|MACH_DSUNKNOWN
)paren
id|printk
c_func
(paren
l_string|&quot;This is an %s, id is %x&bslash;n&quot;
comma
id|dec_system_strings
(braket
id|mips_machtype
)braket
comma
id|dec_systype
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;This is a %s&bslash;n&quot;
comma
id|dec_system_strings
(braket
id|mips_machtype
)braket
)paren
suffix:semicolon
)brace
eof
