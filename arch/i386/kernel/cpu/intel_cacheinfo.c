macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
DECL|macro|LVL_1_INST
mdefine_line|#define LVL_1_INST&t;1
DECL|macro|LVL_1_DATA
mdefine_line|#define LVL_1_DATA&t;2
DECL|macro|LVL_2
mdefine_line|#define LVL_2&t;&t;3
DECL|macro|LVL_3
mdefine_line|#define LVL_3&t;&t;4
DECL|macro|LVL_TRACE
mdefine_line|#define LVL_TRACE&t;5
DECL|struct|_cache_table
r_struct
id|_cache_table
(brace
DECL|member|descriptor
r_int
r_char
id|descriptor
suffix:semicolon
DECL|member|cache_type
r_char
id|cache_type
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* all the cache descriptor types we care about (no TLB or trace cache entries) */
DECL|variable|__initdata
r_static
r_struct
id|_cache_table
id|cache_table
(braket
)braket
id|__initdata
op_assign
(brace
(brace
l_int|0x06
comma
id|LVL_1_INST
comma
l_int|8
)brace
comma
multiline_comment|/* 4-way set assoc, 32 byte line size */
(brace
l_int|0x08
comma
id|LVL_1_INST
comma
l_int|16
)brace
comma
multiline_comment|/* 4-way set assoc, 32 byte line size */
(brace
l_int|0x0a
comma
id|LVL_1_DATA
comma
l_int|8
)brace
comma
multiline_comment|/* 2 way set assoc, 32 byte line size */
(brace
l_int|0x0c
comma
id|LVL_1_DATA
comma
l_int|16
)brace
comma
multiline_comment|/* 4-way set assoc, 32 byte line size */
(brace
l_int|0x22
comma
id|LVL_3
comma
l_int|512
)brace
comma
multiline_comment|/* 4-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x23
comma
id|LVL_3
comma
l_int|1024
)brace
comma
multiline_comment|/* 8-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x25
comma
id|LVL_3
comma
l_int|2048
)brace
comma
multiline_comment|/* 8-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x29
comma
id|LVL_3
comma
l_int|4096
)brace
comma
multiline_comment|/* 8-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x2c
comma
id|LVL_1_DATA
comma
l_int|32
)brace
comma
multiline_comment|/* 8-way set assoc, 64 byte line size */
(brace
l_int|0x30
comma
id|LVL_1_INST
comma
l_int|32
)brace
comma
multiline_comment|/* 8-way set assoc, 64 byte line size */
(brace
l_int|0x39
comma
id|LVL_2
comma
l_int|128
)brace
comma
multiline_comment|/* 4-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x3b
comma
id|LVL_2
comma
l_int|128
)brace
comma
multiline_comment|/* 2-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x3c
comma
id|LVL_2
comma
l_int|256
)brace
comma
multiline_comment|/* 4-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x41
comma
id|LVL_2
comma
l_int|128
)brace
comma
multiline_comment|/* 4-way set assoc, 32 byte line size */
(brace
l_int|0x42
comma
id|LVL_2
comma
l_int|256
)brace
comma
multiline_comment|/* 4-way set assoc, 32 byte line size */
(brace
l_int|0x43
comma
id|LVL_2
comma
l_int|512
)brace
comma
multiline_comment|/* 4-way set assoc, 32 byte line size */
(brace
l_int|0x44
comma
id|LVL_2
comma
l_int|1024
)brace
comma
multiline_comment|/* 4-way set assoc, 32 byte line size */
(brace
l_int|0x45
comma
id|LVL_2
comma
l_int|2048
)brace
comma
multiline_comment|/* 4-way set assoc, 32 byte line size */
(brace
l_int|0x60
comma
id|LVL_1_DATA
comma
l_int|16
)brace
comma
multiline_comment|/* 8-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x66
comma
id|LVL_1_DATA
comma
l_int|8
)brace
comma
multiline_comment|/* 4-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x67
comma
id|LVL_1_DATA
comma
l_int|16
)brace
comma
multiline_comment|/* 4-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x68
comma
id|LVL_1_DATA
comma
l_int|32
)brace
comma
multiline_comment|/* 4-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x70
comma
id|LVL_TRACE
comma
l_int|12
)brace
comma
multiline_comment|/* 8-way set assoc */
(brace
l_int|0x71
comma
id|LVL_TRACE
comma
l_int|16
)brace
comma
multiline_comment|/* 8-way set assoc */
(brace
l_int|0x72
comma
id|LVL_TRACE
comma
l_int|32
)brace
comma
multiline_comment|/* 8-way set assoc */
(brace
l_int|0x78
comma
id|LVL_2
comma
l_int|1024
)brace
comma
multiline_comment|/* 4-way set assoc, 64 byte line size */
(brace
l_int|0x79
comma
id|LVL_2
comma
l_int|128
)brace
comma
multiline_comment|/* 8-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x7a
comma
id|LVL_2
comma
l_int|256
)brace
comma
multiline_comment|/* 8-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x7b
comma
id|LVL_2
comma
l_int|512
)brace
comma
multiline_comment|/* 8-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x7c
comma
id|LVL_2
comma
l_int|1024
)brace
comma
multiline_comment|/* 8-way set assoc, sectored cache, 64 byte line size */
(brace
l_int|0x7d
comma
id|LVL_2
comma
l_int|2048
)brace
comma
multiline_comment|/* 8-way set assoc, 64 byte line size */
(brace
l_int|0x7f
comma
id|LVL_2
comma
l_int|512
)brace
comma
multiline_comment|/* 2-way set assoc, 64 byte line size */
(brace
l_int|0x82
comma
id|LVL_2
comma
l_int|256
)brace
comma
multiline_comment|/* 8-way set assoc, 32 byte line size */
(brace
l_int|0x83
comma
id|LVL_2
comma
l_int|512
)brace
comma
multiline_comment|/* 8-way set assoc, 32 byte line size */
(brace
l_int|0x84
comma
id|LVL_2
comma
l_int|1024
)brace
comma
multiline_comment|/* 8-way set assoc, 32 byte line size */
(brace
l_int|0x85
comma
id|LVL_2
comma
l_int|2048
)brace
comma
multiline_comment|/* 8-way set assoc, 32 byte line size */
(brace
l_int|0x86
comma
id|LVL_2
comma
l_int|512
)brace
comma
multiline_comment|/* 4-way set assoc, 64 byte line size */
(brace
l_int|0x87
comma
id|LVL_2
comma
l_int|1024
)brace
comma
multiline_comment|/* 8-way set assoc, 64 byte line size */
(brace
l_int|0x00
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|init_intel_cacheinfo
r_int
r_int
id|__init
id|init_intel_cacheinfo
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_int
r_int
id|trace
op_assign
l_int|0
comma
id|l1i
op_assign
l_int|0
comma
id|l1d
op_assign
l_int|0
comma
id|l2
op_assign
l_int|0
comma
id|l3
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Cache sizes */
r_if
c_cond
(paren
id|c-&gt;cpuid_level
OG
l_int|1
)paren
(brace
multiline_comment|/* supports eax=2  call */
r_int
id|i
comma
id|j
comma
id|n
suffix:semicolon
r_int
id|regs
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_char
op_star
id|dp
op_assign
(paren
r_int
r_char
op_star
)paren
id|regs
suffix:semicolon
multiline_comment|/* Number of times to iterate */
id|n
op_assign
id|cpuid_eax
c_func
(paren
l_int|2
)paren
op_amp
l_int|0xFF
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cpuid
c_func
(paren
l_int|2
comma
op_amp
id|regs
(braket
l_int|0
)braket
comma
op_amp
id|regs
(braket
l_int|1
)braket
comma
op_amp
id|regs
(braket
l_int|2
)braket
comma
op_amp
id|regs
(braket
l_int|3
)braket
)paren
suffix:semicolon
multiline_comment|/* If bit 31 is set, this is an unknown format */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|3
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|regs
(braket
id|j
)braket
OL
l_int|0
)paren
id|regs
(braket
id|j
)braket
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Byte 0 is level count, not a descriptor */
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
l_int|16
suffix:semicolon
id|j
op_increment
)paren
(brace
r_int
r_char
id|des
op_assign
id|dp
(braket
id|j
)braket
suffix:semicolon
r_int
r_char
id|k
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* look up this descriptor in the table */
r_while
c_loop
(paren
id|cache_table
(braket
id|k
)braket
dot
id|descriptor
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|cache_table
(braket
id|k
)braket
dot
id|descriptor
op_eq
id|des
)paren
(brace
r_switch
c_cond
(paren
id|cache_table
(braket
id|k
)braket
dot
id|cache_type
)paren
(brace
r_case
id|LVL_1_INST
suffix:colon
id|l1i
op_add_assign
id|cache_table
(braket
id|k
)braket
dot
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LVL_1_DATA
suffix:colon
id|l1d
op_add_assign
id|cache_table
(braket
id|k
)braket
dot
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LVL_2
suffix:colon
id|l2
op_add_assign
id|cache_table
(braket
id|k
)braket
dot
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LVL_3
suffix:colon
id|l3
op_add_assign
id|cache_table
(braket
id|k
)braket
dot
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LVL_TRACE
suffix:colon
id|trace
op_add_assign
id|cache_table
(braket
id|k
)braket
dot
id|size
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|k
op_increment
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|trace
)paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;CPU: Trace cache: %dK uops&quot;
comma
id|trace
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|l1i
)paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;CPU: L1 I cache: %dK&quot;
comma
id|l1i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l1d
)paren
id|printk
c_func
(paren
l_string|&quot;, L1 D cache: %dK&bslash;n&quot;
comma
id|l1d
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l2
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU: L2 cache: %dK&bslash;n&quot;
comma
id|l2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l3
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU: L3 cache: %dK&bslash;n&quot;
comma
id|l3
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * This assumes the L3 cache is shared; it typically lives in&n;&t;&t; * the northbridge.  The L1 caches are included by the L2&n;&t;&t; * cache, and so should not be included for the purpose of&n;&t;&t; * SMP switching weights.&n;&t;&t; */
id|c-&gt;x86_cache_size
op_assign
id|l2
ques
c_cond
id|l2
suffix:colon
(paren
id|l1i
op_plus
id|l1d
)paren
suffix:semicolon
)brace
r_return
id|l2
suffix:semicolon
)brace
eof
