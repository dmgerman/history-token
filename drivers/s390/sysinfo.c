multiline_comment|/*&n; *  drivers/s390/sysinfo.c&n; *&n; *    Copyright (C) 2001 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Ulrich Weigand (Ulrich.Weigand@de.ibm.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
DECL|struct|sysinfo_1_1_1
r_struct
id|sysinfo_1_1_1
(brace
DECL|member|reserved_0
r_char
id|reserved_0
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|manufacturer
r_char
id|manufacturer
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|type
r_char
id|type
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|reserved_1
r_char
id|reserved_1
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|model
r_char
id|model
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sequence
r_char
id|sequence
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|plant
r_char
id|plant
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sysinfo_1_2_1
r_struct
id|sysinfo_1_2_1
(brace
DECL|member|reserved_0
r_char
id|reserved_0
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|sequence
r_char
id|sequence
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|plant
r_char
id|plant
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|reserved_1
r_char
id|reserved_1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|cpu_address
r_int
r_int
id|cpu_address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sysinfo_1_2_2
r_struct
id|sysinfo_1_2_2
(brace
DECL|member|reserved_0
r_char
id|reserved_0
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|capability
r_int
r_int
id|capability
suffix:semicolon
DECL|member|cpus_total
r_int
r_int
id|cpus_total
suffix:semicolon
DECL|member|cpus_configured
r_int
r_int
id|cpus_configured
suffix:semicolon
DECL|member|cpus_standby
r_int
r_int
id|cpus_standby
suffix:semicolon
DECL|member|cpus_reserved
r_int
r_int
id|cpus_reserved
suffix:semicolon
DECL|member|adjustment
r_int
r_int
id|adjustment
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sysinfo_2_2_1
r_struct
id|sysinfo_2_2_1
(brace
DECL|member|reserved_0
r_char
id|reserved_0
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|sequence
r_char
id|sequence
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|plant
r_char
id|plant
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|cpu_id
r_int
r_int
id|cpu_id
suffix:semicolon
DECL|member|cpu_address
r_int
r_int
id|cpu_address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sysinfo_2_2_2
r_struct
id|sysinfo_2_2_2
(brace
DECL|member|reserved_0
r_char
id|reserved_0
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|lpar_number
r_int
r_int
id|lpar_number
suffix:semicolon
DECL|member|reserved_1
r_char
id|reserved_1
suffix:semicolon
DECL|member|characteristics
r_int
r_char
id|characteristics
suffix:semicolon
DECL|macro|LPAR_CHAR_DEDICATED
mdefine_line|#define LPAR_CHAR_DEDICATED&t;(1 &lt;&lt; 7)
DECL|macro|LPAR_CHAR_SHARED
mdefine_line|#define LPAR_CHAR_SHARED&t;(1 &lt;&lt; 6)
DECL|macro|LPAR_CHAR_LIMITED
mdefine_line|#define LPAR_CHAR_LIMITED&t;(1 &lt;&lt; 5)
DECL|member|cpus_total
r_int
r_int
id|cpus_total
suffix:semicolon
DECL|member|cpus_configured
r_int
r_int
id|cpus_configured
suffix:semicolon
DECL|member|cpus_standby
r_int
r_int
id|cpus_standby
suffix:semicolon
DECL|member|cpus_reserved
r_int
r_int
id|cpus_reserved
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|caf
r_int
r_int
id|caf
suffix:semicolon
DECL|member|reserved_2
r_char
id|reserved_2
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|cpus_dedicated
r_int
r_int
id|cpus_dedicated
suffix:semicolon
DECL|member|cpus_shared
r_int
r_int
id|cpus_shared
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sysinfo_3_2_2
r_struct
id|sysinfo_3_2_2
(brace
DECL|member|reserved_0
r_char
id|reserved_0
(braket
l_int|31
)braket
suffix:semicolon
DECL|member|count
r_int
r_char
id|count
suffix:semicolon
r_struct
(brace
DECL|member|reserved_0
r_char
id|reserved_0
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|cpus_total
r_int
r_int
id|cpus_total
suffix:semicolon
DECL|member|cpus_configured
r_int
r_int
id|cpus_configured
suffix:semicolon
DECL|member|cpus_standby
r_int
r_int
id|cpus_standby
suffix:semicolon
DECL|member|cpus_reserved
r_int
r_int
id|cpus_reserved
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|caf
r_int
r_int
id|caf
suffix:semicolon
DECL|member|cpi
r_char
id|cpi
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|reserved_1
r_char
id|reserved_1
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|vm
)brace
id|vm
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|union|s390_sysinfo
r_union
id|s390_sysinfo
(brace
DECL|member|sysinfo_1_1_1
r_struct
id|sysinfo_1_1_1
id|sysinfo_1_1_1
suffix:semicolon
DECL|member|sysinfo_1_2_1
r_struct
id|sysinfo_1_2_1
id|sysinfo_1_2_1
suffix:semicolon
DECL|member|sysinfo_1_2_2
r_struct
id|sysinfo_1_2_2
id|sysinfo_1_2_2
suffix:semicolon
DECL|member|sysinfo_2_2_1
r_struct
id|sysinfo_2_2_1
id|sysinfo_2_2_1
suffix:semicolon
DECL|member|sysinfo_2_2_2
r_struct
id|sysinfo_2_2_2
id|sysinfo_2_2_2
suffix:semicolon
DECL|member|sysinfo_3_2_2
r_struct
id|sysinfo_3_2_2
id|sysinfo_3_2_2
suffix:semicolon
)brace
suffix:semicolon
DECL|function|stsi
r_static
r_inline
r_int
id|stsi
(paren
r_void
op_star
id|sysinfo
comma
r_int
id|fc
comma
r_int
id|sel1
comma
r_int
id|sel2
)paren
(brace
r_int
id|cc
comma
id|retv
suffix:semicolon
macro_line|#ifndef CONFIG_ARCH_S390X
id|__asm__
id|__volatile__
(paren
l_string|&quot;lr&bslash;t0,%2&bslash;n&quot;
l_string|&quot;&bslash;tlr&bslash;t1,%3&bslash;n&quot;
l_string|&quot;&bslash;tstsi&bslash;t0(%4)&bslash;n&quot;
l_string|&quot;0:&bslash;tipm&bslash;t%0&bslash;n&quot;
l_string|&quot;&bslash;tsrl&bslash;t%0,28&bslash;n&quot;
l_string|&quot;1:lr&bslash;t%1,0&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&bslash;tlhi&bslash;t%0,3&bslash;n&quot;
l_string|&quot;&bslash;tbras&bslash;t1,3f&bslash;n&quot;
l_string|&quot;&bslash;t.long 1b&bslash;n&quot;
l_string|&quot;3:&bslash;tl&bslash;t1,0(1)&bslash;n&quot;
l_string|&quot;&bslash;tbr&bslash;t1&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&bslash;t.align 4&bslash;n&quot;
l_string|&quot;&bslash;t.long 0b,2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
comma
l_string|&quot;=d&quot;
(paren
id|retv
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
(paren
id|fc
op_lshift
l_int|28
)paren
op_or
id|sel1
)paren
comma
l_string|&quot;d&quot;
(paren
id|sel2
)paren
comma
l_string|&quot;a&quot;
(paren
id|sysinfo
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
macro_line|#else
id|__asm__
id|__volatile__
(paren
l_string|&quot;lr&bslash;t0,%2&bslash;n&quot;
l_string|&quot;lr&bslash;t1,%3&bslash;n&quot;
l_string|&quot;&bslash;tstsi&bslash;t0(%4)&bslash;n&quot;
l_string|&quot;0:&bslash;tipm&bslash;t%0&bslash;n&quot;
l_string|&quot;&bslash;tsrl&bslash;t%0,28&bslash;n&quot;
l_string|&quot;1:lr&bslash;t%1,0&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&bslash;tlhi&bslash;t%0,3&bslash;n&quot;
l_string|&quot;&bslash;tjg&bslash;t1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&bslash;t.align 8&bslash;n&quot;
l_string|&quot;&bslash;t.quad 0b,2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
comma
l_string|&quot;=d&quot;
(paren
id|retv
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
(paren
id|fc
op_lshift
l_int|28
)paren
op_or
id|sel1
)paren
comma
l_string|&quot;d&quot;
(paren
id|sel2
)paren
comma
l_string|&quot;a&quot;
(paren
id|sysinfo
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|cc
ques
c_cond
op_minus
l_int|1
suffix:colon
id|retv
suffix:semicolon
)brace
DECL|function|stsi_0
r_static
r_inline
r_int
id|stsi_0
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
id|stsi
(paren
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|rc
op_eq
op_minus
l_int|1
ques
c_cond
id|rc
suffix:colon
(paren
(paren
(paren
r_int
r_int
)paren
id|rc
)paren
op_rshift
l_int|28
)paren
suffix:semicolon
)brace
DECL|function|stsi_1_1_1
r_static
r_inline
r_int
id|stsi_1_1_1
(paren
r_struct
id|sysinfo_1_1_1
op_star
id|info
)paren
(brace
r_int
id|rc
op_assign
id|stsi
(paren
id|info
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
op_minus
l_int|1
)paren
(brace
id|EBCASC
(paren
id|info-&gt;manufacturer
comma
r_sizeof
(paren
id|info-&gt;manufacturer
)paren
)paren
suffix:semicolon
id|EBCASC
(paren
id|info-&gt;type
comma
r_sizeof
(paren
id|info-&gt;type
)paren
)paren
suffix:semicolon
id|EBCASC
(paren
id|info-&gt;model
comma
r_sizeof
(paren
id|info-&gt;model
)paren
)paren
suffix:semicolon
id|EBCASC
(paren
id|info-&gt;sequence
comma
r_sizeof
(paren
id|info-&gt;sequence
)paren
)paren
suffix:semicolon
id|EBCASC
(paren
id|info-&gt;plant
comma
r_sizeof
(paren
id|info-&gt;plant
)paren
)paren
suffix:semicolon
)brace
r_return
id|rc
op_eq
op_minus
l_int|1
ques
c_cond
id|rc
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|stsi_1_2_1
r_static
r_inline
r_int
id|stsi_1_2_1
(paren
r_struct
id|sysinfo_1_2_1
op_star
id|info
)paren
(brace
r_int
id|rc
op_assign
id|stsi
(paren
id|info
comma
l_int|1
comma
l_int|2
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
op_minus
l_int|1
)paren
(brace
id|EBCASC
(paren
id|info-&gt;sequence
comma
r_sizeof
(paren
id|info-&gt;sequence
)paren
)paren
suffix:semicolon
id|EBCASC
(paren
id|info-&gt;plant
comma
r_sizeof
(paren
id|info-&gt;plant
)paren
)paren
suffix:semicolon
)brace
r_return
id|rc
op_eq
op_minus
l_int|1
ques
c_cond
id|rc
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|stsi_1_2_2
r_static
r_inline
r_int
id|stsi_1_2_2
(paren
r_struct
id|sysinfo_1_2_2
op_star
id|info
)paren
(brace
r_int
id|rc
op_assign
id|stsi
(paren
id|info
comma
l_int|1
comma
l_int|2
comma
l_int|2
)paren
suffix:semicolon
r_return
id|rc
op_eq
op_minus
l_int|1
ques
c_cond
id|rc
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|stsi_2_2_1
r_static
r_inline
r_int
id|stsi_2_2_1
(paren
r_struct
id|sysinfo_2_2_1
op_star
id|info
)paren
(brace
r_int
id|rc
op_assign
id|stsi
(paren
id|info
comma
l_int|2
comma
l_int|2
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
op_minus
l_int|1
)paren
(brace
id|EBCASC
(paren
id|info-&gt;sequence
comma
r_sizeof
(paren
id|info-&gt;sequence
)paren
)paren
suffix:semicolon
id|EBCASC
(paren
id|info-&gt;plant
comma
r_sizeof
(paren
id|info-&gt;plant
)paren
)paren
suffix:semicolon
)brace
r_return
id|rc
op_eq
op_minus
l_int|1
ques
c_cond
id|rc
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|stsi_2_2_2
r_static
r_inline
r_int
id|stsi_2_2_2
(paren
r_struct
id|sysinfo_2_2_2
op_star
id|info
)paren
(brace
r_int
id|rc
op_assign
id|stsi
(paren
id|info
comma
l_int|2
comma
l_int|2
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
op_minus
l_int|1
)paren
(brace
id|EBCASC
(paren
id|info-&gt;name
comma
r_sizeof
(paren
id|info-&gt;name
)paren
)paren
suffix:semicolon
)brace
r_return
id|rc
op_eq
op_minus
l_int|1
ques
c_cond
id|rc
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|stsi_3_2_2
r_static
r_inline
r_int
id|stsi_3_2_2
(paren
r_struct
id|sysinfo_3_2_2
op_star
id|info
)paren
(brace
r_int
id|rc
op_assign
id|stsi
(paren
id|info
comma
l_int|3
comma
l_int|2
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
op_minus
l_int|1
)paren
(brace
r_int
id|i
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
id|info-&gt;count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|EBCASC
(paren
id|info-&gt;vm
(braket
id|i
)braket
dot
id|name
comma
r_sizeof
(paren
id|info-&gt;vm
(braket
id|i
)braket
dot
id|name
)paren
)paren
suffix:semicolon
id|EBCASC
(paren
id|info-&gt;vm
(braket
id|i
)braket
dot
id|cpi
comma
r_sizeof
(paren
id|info-&gt;vm
(braket
id|i
)braket
dot
id|cpi
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|rc
op_eq
op_minus
l_int|1
ques
c_cond
id|rc
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|proc_read_sysinfo
r_static
r_int
id|proc_read_sysinfo
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_int
id|info_page
op_assign
id|get_free_page
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_union
id|s390_sysinfo
op_star
id|info
op_assign
(paren
r_union
id|s390_sysinfo
op_star
)paren
id|info_page
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|level
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
r_return
l_int|0
suffix:semicolon
id|level
op_assign
id|stsi_0
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|level
op_ge
l_int|1
op_logical_and
id|stsi_1_1_1
(paren
op_amp
id|info-&gt;sysinfo_1_1_1
)paren
op_eq
l_int|0
)paren
(brace
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Manufacturer:         %-16.16s&bslash;n&quot;
comma
id|info-&gt;sysinfo_1_1_1.manufacturer
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Type:                 %-4.4s&bslash;n&quot;
comma
id|info-&gt;sysinfo_1_1_1.type
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Model:                %-16.16s&bslash;n&quot;
comma
id|info-&gt;sysinfo_1_1_1.model
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Sequence Code:        %-16.16s&bslash;n&quot;
comma
id|info-&gt;sysinfo_1_1_1.sequence
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Plant:                %-4.4s&bslash;n&quot;
comma
id|info-&gt;sysinfo_1_1_1.plant
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|level
op_ge
l_int|1
op_logical_and
id|stsi_1_2_2
(paren
op_amp
id|info-&gt;sysinfo_1_2_2
)paren
op_eq
l_int|0
)paren
(brace
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;CPUs Total:           %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_1_2_2.cpus_total
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;CPUs Configured:      %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_1_2_2.cpus_configured
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;CPUs Standby:         %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_1_2_2.cpus_standby
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;CPUs Reserved:        %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_1_2_2.cpus_reserved
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Capability:           %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_1_2_2.capability
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
op_le
id|info-&gt;sysinfo_1_2_2.cpus_total
suffix:semicolon
id|i
op_increment
)paren
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Adjustment %02d-way:    %d&bslash;n&quot;
comma
id|i
comma
id|info-&gt;sysinfo_1_2_2.adjustment
(braket
id|i
op_minus
l_int|2
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|level
op_ge
l_int|2
op_logical_and
id|stsi_2_2_2
(paren
op_amp
id|info-&gt;sysinfo_2_2_2
)paren
op_eq
l_int|0
)paren
(brace
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;LPAR Number:          %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_2_2_2.lpar_number
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;LPAR Characteristics: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;sysinfo_2_2_2.characteristics
op_amp
id|LPAR_CHAR_DEDICATED
)paren
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Dedicated &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;sysinfo_2_2_2.characteristics
op_amp
id|LPAR_CHAR_SHARED
)paren
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Shared &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;sysinfo_2_2_2.characteristics
op_amp
id|LPAR_CHAR_LIMITED
)paren
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Limited &quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;LPAR Name:            %-8.8s&bslash;n&quot;
comma
id|info-&gt;sysinfo_2_2_2.name
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;LPAR Adjustment:      %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_2_2_2.caf
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;LPAR CPUs Total:      %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_2_2_2.cpus_total
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;LPAR CPUs Configured: %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_2_2_2.cpus_configured
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;LPAR CPUs Standby:    %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_2_2_2.cpus_standby
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;LPAR CPUs Reserved:   %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_2_2_2.cpus_reserved
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;LPAR CPUs Dedicated:  %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_2_2_2.cpus_dedicated
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;LPAR CPUs Shared:     %d&bslash;n&quot;
comma
id|info-&gt;sysinfo_2_2_2.cpus_shared
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|level
op_ge
l_int|3
op_logical_and
id|stsi_3_2_2
(paren
op_amp
id|info-&gt;sysinfo_3_2_2
)paren
op_eq
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|info-&gt;sysinfo_3_2_2.count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;VM%02d Name:            %-8.8s&bslash;n&quot;
comma
id|i
comma
id|info-&gt;sysinfo_3_2_2.vm
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;VM%02d Control Program: %-16.16s&bslash;n&quot;
comma
id|i
comma
id|info-&gt;sysinfo_3_2_2.vm
(braket
id|i
)braket
dot
id|cpi
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;VM%02d Adjustment:      %d&bslash;n&quot;
comma
id|i
comma
id|info-&gt;sysinfo_3_2_2.vm
(braket
id|i
)braket
dot
id|caf
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;VM%02d CPUs Total:      %d&bslash;n&quot;
comma
id|i
comma
id|info-&gt;sysinfo_3_2_2.vm
(braket
id|i
)braket
dot
id|cpus_total
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;VM%02d CPUs Configured: %d&bslash;n&quot;
comma
id|i
comma
id|info-&gt;sysinfo_3_2_2.vm
(braket
id|i
)braket
dot
id|cpus_configured
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;VM%02d CPUs Standby:    %d&bslash;n&quot;
comma
id|i
comma
id|info-&gt;sysinfo_3_2_2.vm
(braket
id|i
)braket
dot
id|cpus_standby
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|len
comma
l_string|&quot;VM%02d CPUs Reserved:   %d&bslash;n&quot;
comma
id|i
comma
id|info-&gt;sysinfo_3_2_2.vm
(braket
id|i
)braket
dot
id|cpus_reserved
)paren
suffix:semicolon
)brace
)brace
id|free_page
(paren
id|info_page
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|create_proc_sysinfo
r_static
id|__init
r_int
id|create_proc_sysinfo
c_func
(paren
r_void
)paren
(brace
id|create_proc_read_entry
(paren
l_string|&quot;sysinfo&quot;
comma
l_int|0444
comma
l_int|NULL
comma
id|proc_read_sysinfo
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|create_proc_sysinfo
id|__initcall
c_func
(paren
id|create_proc_sysinfo
)paren
suffix:semicolon
eof
