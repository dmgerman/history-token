multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * identify.c: identify machine by looking up system identifier&n; *&n; * Copyright (C) 1998 Thomas Bogendoerfer&n; *&n; * This code is based on arch/mips/sgi/kernel/system.c, which is&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
DECL|struct|smatch
r_struct
id|smatch
(brace
DECL|member|arcname
r_char
op_star
id|arcname
suffix:semicolon
DECL|member|liname
r_char
op_star
id|liname
suffix:semicolon
DECL|member|group
r_int
id|group
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|mach_table
r_static
r_struct
id|smatch
id|mach_table
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;SGI-IP22&quot;
comma
l_string|&quot;SGI Indy&quot;
comma
id|MACH_GROUP_SGI
comma
id|MACH_SGI_IP22
comma
id|PROM_FLAG_ARCS
)brace
comma
(brace
l_string|&quot;SGI-IP27&quot;
comma
l_string|&quot;SGI Origin&quot;
comma
id|MACH_GROUP_SGI
comma
id|MACH_SGI_IP27
comma
id|PROM_FLAG_ARCS
)brace
comma
(brace
l_string|&quot;SGI-IP28&quot;
comma
l_string|&quot;SGI IP28&quot;
comma
id|MACH_GROUP_SGI
comma
id|MACH_SGI_IP28
comma
id|PROM_FLAG_ARCS
)brace
comma
(brace
l_string|&quot;SGI-IP32&quot;
comma
l_string|&quot;SGI O2&quot;
comma
id|MACH_GROUP_SGI
comma
id|MACH_SGI_IP32
comma
id|PROM_FLAG_ARCS
)brace
comma
(brace
l_string|&quot;Microsoft-Jazz&quot;
comma
l_string|&quot;Jazz MIPS_Magnum_4000&quot;
comma
id|MACH_GROUP_JAZZ
comma
id|MACH_MIPS_MAGNUM_4000
comma
l_int|0
)brace
comma
(brace
l_string|&quot;PICA-61&quot;
comma
l_string|&quot;Jazz Acer_PICA_61&quot;
comma
id|MACH_GROUP_JAZZ
comma
id|MACH_ACER_PICA_61
comma
l_int|0
)brace
comma
(brace
l_string|&quot;RM200PCI&quot;
comma
l_string|&quot;SNI RM200_PCI&quot;
comma
id|MACH_GROUP_SNI_RM
comma
id|MACH_SNI_RM200_PCI
comma
id|PROM_FLAG_DONT_FREE_TEMP
)brace
)brace
suffix:semicolon
DECL|variable|prom_flags
r_int
id|prom_flags
suffix:semicolon
DECL|function|string_to_mach
r_static
r_struct
id|smatch
op_star
id|__init
id|string_to_mach
c_func
(paren
r_const
r_char
op_star
id|s
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
(paren
r_sizeof
(paren
id|mach_table
)paren
op_div
r_sizeof
(paren
id|mach_table
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|s
comma
id|mach_table
(braket
id|i
)braket
dot
id|arcname
)paren
)paren
r_return
op_amp
id|mach_table
(braket
id|i
)braket
suffix:semicolon
)brace
id|panic
c_func
(paren
l_string|&quot;Yeee, could not determine architecture type &lt;%s&gt;&quot;
comma
id|s
)paren
suffix:semicolon
)brace
DECL|variable|system_type
r_char
op_star
id|system_type
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
r_return
id|system_type
suffix:semicolon
)brace
DECL|function|prom_identify_arch
r_void
id|__init
id|prom_identify_arch
c_func
(paren
r_void
)paren
(brace
id|pcomponent
op_star
id|p
suffix:semicolon
r_struct
id|smatch
op_star
id|mach
suffix:semicolon
r_const
r_char
op_star
id|iname
suffix:semicolon
multiline_comment|/*&n;&t; * The root component tells us what machine architecture we have here.&n;&t; */
id|p
op_assign
id|ArcGetChild
c_func
(paren
id|PROM_NULL_COMPONENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
(brace
macro_line|#ifdef CONFIG_SGI_IP27
multiline_comment|/* IP27 PROM misbehaves, seems to not implement ARC&n;&t;&t;   GetChild().  So we just assume it&squot;s an IP27.  */
id|iname
op_assign
l_string|&quot;SGI-IP27&quot;
suffix:semicolon
macro_line|#else
id|iname
op_assign
l_string|&quot;Unknown&quot;
suffix:semicolon
macro_line|#endif
)brace
r_else
id|iname
op_assign
(paren
r_char
op_star
)paren
(paren
r_int
)paren
id|p-&gt;iname
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ARCH: %s&bslash;n&quot;
comma
id|iname
)paren
suffix:semicolon
id|mach
op_assign
id|string_to_mach
c_func
(paren
id|iname
)paren
suffix:semicolon
id|system_type
op_assign
id|mach-&gt;liname
suffix:semicolon
id|mips_machgroup
op_assign
id|mach-&gt;group
suffix:semicolon
id|mips_machtype
op_assign
id|mach-&gt;type
suffix:semicolon
id|prom_flags
op_assign
id|mach-&gt;flags
suffix:semicolon
)brace
eof
