macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;elf.h&gt;
r_int
DECL|function|main
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
r_char
id|ei
(braket
id|EI_NIDENT
)braket
suffix:semicolon
r_union
(brace
r_int
id|s
suffix:semicolon
r_char
id|c
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|endian_test
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Error: no arch&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fread
c_func
(paren
id|ei
comma
l_int|1
comma
id|EI_NIDENT
comma
id|stdin
)paren
op_ne
id|EI_NIDENT
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Error: input truncated&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|ei
comma
id|ELFMAG
comma
id|SELFMAG
)paren
op_ne
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Error: not ELF&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ei
(braket
id|EI_CLASS
)braket
)paren
(brace
r_case
id|ELFCLASS32
suffix:colon
id|printf
c_func
(paren
l_string|&quot;#define KERNEL_ELFCLASS ELFCLASS32&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ELFCLASS64
suffix:colon
id|printf
c_func
(paren
l_string|&quot;#define KERNEL_ELFCLASS ELFCLASS64&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
m_abort
(paren
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ei
(braket
id|EI_DATA
)braket
)paren
(brace
r_case
id|ELFDATA2LSB
suffix:colon
id|printf
c_func
(paren
l_string|&quot;#define KERNEL_ELFDATA ELFDATA2LSB&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ELFDATA2MSB
suffix:colon
id|printf
c_func
(paren
l_string|&quot;#define KERNEL_ELFDATA ELFDATA2MSB&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
m_abort
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_eq
l_int|4
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;#define HOST_ELFCLASS ELFCLASS32&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_eq
l_int|8
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;#define HOST_ELFCLASS ELFCLASS64&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|endian_test.s
op_assign
l_int|0x0102
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|endian_test.c
comma
l_string|&quot;&bslash;x01&bslash;x02&quot;
comma
l_int|2
)paren
op_eq
l_int|0
)paren
id|printf
c_func
(paren
l_string|&quot;#define HOST_ELFDATA ELFDATA2MSB&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|endian_test.c
comma
l_string|&quot;&bslash;x02&bslash;x01&quot;
comma
l_int|2
)paren
op_eq
l_int|0
)paren
id|printf
c_func
(paren
l_string|&quot;#define HOST_ELFDATA ELFDATA2LSB&bslash;n&quot;
)paren
suffix:semicolon
r_else
m_abort
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;v850&quot;
)paren
op_eq
l_int|0
)paren
op_logical_or
(paren
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;h8300&quot;
)paren
op_eq
l_int|0
)paren
)paren
id|printf
c_func
(paren
l_string|&quot;#define MODULE_SYMBOL_PREFIX &bslash;&quot;_&bslash;&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;#define MODULE_SYMBOL_PREFIX &bslash;&quot;&bslash;&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
