multiline_comment|/*&n; * linux/arch/arm/boot/compressed/ofw-shark.c&n; *&n; * by Alexander Schulz&n; *&n; * This file is used to get some basic information&n; * about the memory layout of the shark we are running&n; * on. Memory is usually divided in blocks a 8 MB.&n; * And bootargs are copied from OpenFirmware.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
id|asmlinkage
r_void
DECL|function|create_params
id|create_params
(paren
r_int
r_int
op_star
id|buffer
)paren
(brace
multiline_comment|/* Is there a better address? Also change in mach-shark/arch.c */
r_struct
id|tag
op_star
id|tag
op_assign
(paren
r_struct
id|tag
op_star
)paren
l_int|0x08003000
suffix:semicolon
r_int
id|j
comma
id|i
comma
id|m
comma
id|k
comma
id|nr_banks
comma
id|size
suffix:semicolon
r_int
r_char
op_star
id|c
suffix:semicolon
multiline_comment|/* Head of the taglist */
id|tag-&gt;hdr.tag
op_assign
id|ATAG_CORE
suffix:semicolon
id|tag-&gt;hdr.size
op_assign
id|tag_size
c_func
(paren
id|tag_core
)paren
suffix:semicolon
id|tag-&gt;u.core.flags
op_assign
id|FLAG_READONLY
suffix:semicolon
id|tag-&gt;u.core.pagesize
op_assign
id|PAGE_SIZE
suffix:semicolon
id|tag-&gt;u.core.rootdev
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Build up one tagged block for each memory region */
id|size
op_assign
l_int|0
suffix:semicolon
id|nr_banks
op_assign
(paren
r_int
r_int
)paren
id|buffer
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|nr_banks
suffix:semicolon
id|j
op_increment
)paren
(brace
multiline_comment|/* search the lowest address and put it into the next entry   */
multiline_comment|/* not a fast sort algorithm, but there are at most 8 entries */
multiline_comment|/* and this is used only once anyway                          */
id|m
op_assign
l_int|0xffffffff
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
r_int
r_int
)paren
id|buffer
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|buffer
(braket
l_int|2
op_star
id|i
op_plus
l_int|1
)braket
OL
id|m
)paren
(brace
id|m
op_assign
id|buffer
(braket
l_int|2
op_star
id|i
op_plus
l_int|1
)braket
suffix:semicolon
id|k
op_assign
id|i
suffix:semicolon
)brace
)brace
id|tag
op_assign
id|tag_next
c_func
(paren
id|tag
)paren
suffix:semicolon
id|tag-&gt;hdr.tag
op_assign
id|ATAG_MEM
suffix:semicolon
id|tag-&gt;hdr.size
op_assign
id|tag_size
c_func
(paren
id|tag_mem32
)paren
suffix:semicolon
id|tag-&gt;u.mem.size
op_assign
id|buffer
(braket
l_int|2
op_star
id|k
op_plus
l_int|2
)braket
suffix:semicolon
id|tag-&gt;u.mem.start
op_assign
id|buffer
(braket
l_int|2
op_star
id|k
op_plus
l_int|1
)braket
suffix:semicolon
id|size
op_add_assign
id|buffer
(braket
l_int|2
op_star
id|k
op_plus
l_int|2
)braket
suffix:semicolon
id|buffer
(braket
l_int|2
op_star
id|k
op_plus
l_int|1
)braket
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* mark as copied */
)brace
multiline_comment|/* The command line */
id|tag
op_assign
id|tag_next
c_func
(paren
id|tag
)paren
suffix:semicolon
id|tag-&gt;hdr.tag
op_assign
id|ATAG_CMDLINE
suffix:semicolon
id|c
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
op_amp
id|buffer
(braket
l_int|34
)braket
)paren
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|c
)paren
id|tag-&gt;u.cmdline.cmdline
(braket
id|j
op_increment
)braket
op_assign
op_star
id|c
op_increment
suffix:semicolon
id|tag-&gt;u.cmdline.cmdline
(braket
id|j
)braket
op_assign
l_int|0
suffix:semicolon
id|tag-&gt;hdr.size
op_assign
(paren
id|j
op_plus
l_int|7
op_plus
r_sizeof
(paren
r_struct
id|tag_header
)paren
)paren
op_rshift
l_int|2
suffix:semicolon
multiline_comment|/* Hardware revision */
id|tag
op_assign
id|tag_next
c_func
(paren
id|tag
)paren
suffix:semicolon
id|tag-&gt;hdr.tag
op_assign
id|ATAG_REVISION
suffix:semicolon
id|tag-&gt;hdr.size
op_assign
id|tag_size
c_func
(paren
id|tag_revision
)paren
suffix:semicolon
id|tag-&gt;u.revision.rev
op_assign
(paren
(paren
r_int
r_char
)paren
id|buffer
(braket
l_int|33
)braket
)paren
op_minus
l_char|&squot;0&squot;
suffix:semicolon
multiline_comment|/* End of the taglist */
id|tag
op_assign
id|tag_next
c_func
(paren
id|tag
)paren
suffix:semicolon
id|tag-&gt;hdr.tag
op_assign
l_int|0
suffix:semicolon
id|tag-&gt;hdr.size
op_assign
l_int|0
suffix:semicolon
)brace
DECL|typedef|ofw_handle_t
r_typedef
r_int
(paren
op_star
id|ofw_handle_t
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* Everything below is called with a wrong MMU setting.&n; * This means: no string constants, no initialization of&n; * arrays, no global variables! This is ugly but I didn&squot;t&n; * want to write this in assembler :-)&n; */
r_int
DECL|function|of_decode_int
id|of_decode_int
c_func
(paren
r_const
r_int
r_char
op_star
id|p
)paren
(brace
r_int
r_int
id|i
op_assign
op_star
id|p
op_increment
op_lshift
l_int|8
suffix:semicolon
id|i
op_assign
(paren
id|i
op_plus
op_star
id|p
op_increment
)paren
op_lshift
l_int|8
suffix:semicolon
id|i
op_assign
(paren
id|i
op_plus
op_star
id|p
op_increment
)paren
op_lshift
l_int|8
suffix:semicolon
r_return
(paren
id|i
op_plus
op_star
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|OF_finddevice
id|OF_finddevice
c_func
(paren
id|ofw_handle_t
id|openfirmware
comma
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|args
(braket
l_int|8
)braket
suffix:semicolon
r_char
id|service
(braket
l_int|12
)braket
suffix:semicolon
id|service
(braket
l_int|0
)braket
op_assign
l_char|&squot;f&squot;
suffix:semicolon
id|service
(braket
l_int|1
)braket
op_assign
l_char|&squot;i&squot;
suffix:semicolon
id|service
(braket
l_int|2
)braket
op_assign
l_char|&squot;n&squot;
suffix:semicolon
id|service
(braket
l_int|3
)braket
op_assign
l_char|&squot;d&squot;
suffix:semicolon
id|service
(braket
l_int|4
)braket
op_assign
l_char|&squot;d&squot;
suffix:semicolon
id|service
(braket
l_int|5
)braket
op_assign
l_char|&squot;e&squot;
suffix:semicolon
id|service
(braket
l_int|6
)braket
op_assign
l_char|&squot;v&squot;
suffix:semicolon
id|service
(braket
l_int|7
)braket
op_assign
l_char|&squot;i&squot;
suffix:semicolon
id|service
(braket
l_int|8
)braket
op_assign
l_char|&squot;c&squot;
suffix:semicolon
id|service
(braket
l_int|9
)braket
op_assign
l_char|&squot;e&squot;
suffix:semicolon
id|service
(braket
l_int|10
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|args
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|service
suffix:semicolon
id|args
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
id|args
(braket
l_int|2
)braket
op_assign
l_int|1
suffix:semicolon
id|args
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|name
suffix:semicolon
r_if
c_cond
(paren
id|openfirmware
c_func
(paren
id|args
)paren
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|args
(braket
l_int|4
)braket
suffix:semicolon
)brace
r_int
DECL|function|OF_getproplen
id|OF_getproplen
c_func
(paren
id|ofw_handle_t
id|openfirmware
comma
r_int
id|handle
comma
r_char
op_star
id|prop
)paren
(brace
r_int
r_int
id|args
(braket
l_int|8
)braket
suffix:semicolon
r_char
id|service
(braket
l_int|12
)braket
suffix:semicolon
id|service
(braket
l_int|0
)braket
op_assign
l_char|&squot;g&squot;
suffix:semicolon
id|service
(braket
l_int|1
)braket
op_assign
l_char|&squot;e&squot;
suffix:semicolon
id|service
(braket
l_int|2
)braket
op_assign
l_char|&squot;t&squot;
suffix:semicolon
id|service
(braket
l_int|3
)braket
op_assign
l_char|&squot;p&squot;
suffix:semicolon
id|service
(braket
l_int|4
)braket
op_assign
l_char|&squot;r&squot;
suffix:semicolon
id|service
(braket
l_int|5
)braket
op_assign
l_char|&squot;o&squot;
suffix:semicolon
id|service
(braket
l_int|6
)braket
op_assign
l_char|&squot;p&squot;
suffix:semicolon
id|service
(braket
l_int|7
)braket
op_assign
l_char|&squot;l&squot;
suffix:semicolon
id|service
(braket
l_int|8
)braket
op_assign
l_char|&squot;e&squot;
suffix:semicolon
id|service
(braket
l_int|9
)braket
op_assign
l_char|&squot;n&squot;
suffix:semicolon
id|service
(braket
l_int|10
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|args
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|service
suffix:semicolon
id|args
(braket
l_int|1
)braket
op_assign
l_int|2
suffix:semicolon
id|args
(braket
l_int|2
)braket
op_assign
l_int|1
suffix:semicolon
id|args
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|handle
suffix:semicolon
id|args
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_int
)paren
id|prop
suffix:semicolon
r_if
c_cond
(paren
id|openfirmware
c_func
(paren
id|args
)paren
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|args
(braket
l_int|5
)braket
suffix:semicolon
)brace
r_int
DECL|function|OF_getprop
id|OF_getprop
c_func
(paren
id|ofw_handle_t
id|openfirmware
comma
r_int
id|handle
comma
r_char
op_star
id|prop
comma
r_void
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_int
r_int
id|args
(braket
l_int|8
)braket
suffix:semicolon
r_char
id|service
(braket
l_int|8
)braket
suffix:semicolon
id|service
(braket
l_int|0
)braket
op_assign
l_char|&squot;g&squot;
suffix:semicolon
id|service
(braket
l_int|1
)braket
op_assign
l_char|&squot;e&squot;
suffix:semicolon
id|service
(braket
l_int|2
)braket
op_assign
l_char|&squot;t&squot;
suffix:semicolon
id|service
(braket
l_int|3
)braket
op_assign
l_char|&squot;p&squot;
suffix:semicolon
id|service
(braket
l_int|4
)braket
op_assign
l_char|&squot;r&squot;
suffix:semicolon
id|service
(braket
l_int|5
)braket
op_assign
l_char|&squot;o&squot;
suffix:semicolon
id|service
(braket
l_int|6
)braket
op_assign
l_char|&squot;p&squot;
suffix:semicolon
id|service
(braket
l_int|7
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|args
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|service
suffix:semicolon
id|args
(braket
l_int|1
)braket
op_assign
l_int|4
suffix:semicolon
id|args
(braket
l_int|2
)braket
op_assign
l_int|1
suffix:semicolon
id|args
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|handle
suffix:semicolon
id|args
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_int
)paren
id|prop
suffix:semicolon
id|args
(braket
l_int|5
)braket
op_assign
(paren
r_int
r_int
)paren
id|buf
suffix:semicolon
id|args
(braket
l_int|6
)braket
op_assign
id|buflen
suffix:semicolon
r_if
c_cond
(paren
id|openfirmware
c_func
(paren
id|args
)paren
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|args
(braket
l_int|7
)braket
suffix:semicolon
)brace
DECL|function|ofw_init
id|asmlinkage
r_void
id|ofw_init
c_func
(paren
id|ofw_handle_t
id|o
comma
r_int
op_star
id|nomr
comma
r_int
op_star
id|pointer
)paren
(brace
r_int
id|phandle
comma
id|i
comma
id|mem_len
comma
id|buffer
(braket
l_int|32
)braket
suffix:semicolon
r_char
id|temp
(braket
l_int|15
)braket
suffix:semicolon
id|temp
(braket
l_int|0
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|temp
(braket
l_int|1
)braket
op_assign
l_char|&squot;m&squot;
suffix:semicolon
id|temp
(braket
l_int|2
)braket
op_assign
l_char|&squot;e&squot;
suffix:semicolon
id|temp
(braket
l_int|3
)braket
op_assign
l_char|&squot;m&squot;
suffix:semicolon
id|temp
(braket
l_int|4
)braket
op_assign
l_char|&squot;o&squot;
suffix:semicolon
id|temp
(braket
l_int|5
)braket
op_assign
l_char|&squot;r&squot;
suffix:semicolon
id|temp
(braket
l_int|6
)braket
op_assign
l_char|&squot;y&squot;
suffix:semicolon
id|temp
(braket
l_int|7
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|phandle
op_assign
id|OF_finddevice
c_func
(paren
id|o
comma
id|temp
)paren
suffix:semicolon
id|temp
(braket
l_int|0
)braket
op_assign
l_char|&squot;r&squot;
suffix:semicolon
id|temp
(braket
l_int|1
)braket
op_assign
l_char|&squot;e&squot;
suffix:semicolon
id|temp
(braket
l_int|2
)braket
op_assign
l_char|&squot;g&squot;
suffix:semicolon
id|temp
(braket
l_int|3
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|mem_len
op_assign
id|OF_getproplen
c_func
(paren
id|o
comma
id|phandle
comma
id|temp
)paren
suffix:semicolon
id|OF_getprop
c_func
(paren
id|o
comma
id|phandle
comma
id|temp
comma
id|buffer
comma
id|mem_len
)paren
suffix:semicolon
op_star
id|nomr
op_assign
id|mem_len
op_rshift
l_int|3
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|mem_len
op_div
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|pointer
(braket
id|i
)braket
op_assign
id|of_decode_int
c_func
(paren
(paren
r_const
r_int
r_char
op_star
)paren
op_amp
id|buffer
(braket
id|i
)braket
)paren
suffix:semicolon
id|temp
(braket
l_int|0
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|temp
(braket
l_int|1
)braket
op_assign
l_char|&squot;c&squot;
suffix:semicolon
id|temp
(braket
l_int|2
)braket
op_assign
l_char|&squot;h&squot;
suffix:semicolon
id|temp
(braket
l_int|3
)braket
op_assign
l_char|&squot;o&squot;
suffix:semicolon
id|temp
(braket
l_int|4
)braket
op_assign
l_char|&squot;s&squot;
suffix:semicolon
id|temp
(braket
l_int|5
)braket
op_assign
l_char|&squot;e&squot;
suffix:semicolon
id|temp
(braket
l_int|6
)braket
op_assign
l_char|&squot;n&squot;
suffix:semicolon
id|temp
(braket
l_int|7
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|phandle
op_assign
id|OF_finddevice
c_func
(paren
id|o
comma
id|temp
)paren
suffix:semicolon
id|temp
(braket
l_int|0
)braket
op_assign
l_char|&squot;b&squot;
suffix:semicolon
id|temp
(braket
l_int|1
)braket
op_assign
l_char|&squot;o&squot;
suffix:semicolon
id|temp
(braket
l_int|2
)braket
op_assign
l_char|&squot;o&squot;
suffix:semicolon
id|temp
(braket
l_int|3
)braket
op_assign
l_char|&squot;t&squot;
suffix:semicolon
id|temp
(braket
l_int|4
)braket
op_assign
l_char|&squot;a&squot;
suffix:semicolon
id|temp
(braket
l_int|5
)braket
op_assign
l_char|&squot;r&squot;
suffix:semicolon
id|temp
(braket
l_int|6
)braket
op_assign
l_char|&squot;g&squot;
suffix:semicolon
id|temp
(braket
l_int|7
)braket
op_assign
l_char|&squot;s&squot;
suffix:semicolon
id|temp
(braket
l_int|8
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|mem_len
op_assign
id|OF_getproplen
c_func
(paren
id|o
comma
id|phandle
comma
id|temp
)paren
suffix:semicolon
id|OF_getprop
c_func
(paren
id|o
comma
id|phandle
comma
id|temp
comma
id|buffer
comma
id|mem_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_len
OG
l_int|128
)paren
id|mem_len
op_assign
l_int|128
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|mem_len
op_div
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|pointer
(braket
id|i
op_plus
l_int|33
)braket
op_assign
id|buffer
(braket
id|i
)braket
suffix:semicolon
id|pointer
(braket
id|i
op_plus
l_int|33
)braket
op_assign
l_int|0
suffix:semicolon
id|temp
(braket
l_int|0
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|temp
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|phandle
op_assign
id|OF_finddevice
c_func
(paren
id|o
comma
id|temp
)paren
suffix:semicolon
id|temp
(braket
l_int|0
)braket
op_assign
l_char|&squot;b&squot;
suffix:semicolon
id|temp
(braket
l_int|1
)braket
op_assign
l_char|&squot;a&squot;
suffix:semicolon
id|temp
(braket
l_int|2
)braket
op_assign
l_char|&squot;n&squot;
suffix:semicolon
id|temp
(braket
l_int|3
)braket
op_assign
l_char|&squot;n&squot;
suffix:semicolon
id|temp
(braket
l_int|4
)braket
op_assign
l_char|&squot;e&squot;
suffix:semicolon
id|temp
(braket
l_int|5
)braket
op_assign
l_char|&squot;r&squot;
suffix:semicolon
id|temp
(braket
l_int|6
)braket
op_assign
l_char|&squot;-&squot;
suffix:semicolon
id|temp
(braket
l_int|7
)braket
op_assign
l_char|&squot;n&squot;
suffix:semicolon
id|temp
(braket
l_int|8
)braket
op_assign
l_char|&squot;a&squot;
suffix:semicolon
id|temp
(braket
l_int|9
)braket
op_assign
l_char|&squot;m&squot;
suffix:semicolon
id|temp
(braket
l_int|10
)braket
op_assign
l_char|&squot;e&squot;
suffix:semicolon
id|temp
(braket
l_int|11
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|mem_len
op_assign
id|OF_getproplen
c_func
(paren
id|o
comma
id|phandle
comma
id|temp
)paren
suffix:semicolon
id|OF_getprop
c_func
(paren
id|o
comma
id|phandle
comma
id|temp
comma
id|buffer
comma
id|mem_len
)paren
suffix:semicolon
(paren
r_int
r_char
)paren
id|pointer
(braket
l_int|32
)braket
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|buffer
)paren
(braket
id|mem_len
op_minus
l_int|2
)braket
suffix:semicolon
)brace
eof
