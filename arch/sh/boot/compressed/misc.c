multiline_comment|/*&n; * arch/sh/boot/compressed/misc.c&n; * &n; * This is a collection of several routines from gzip-1.0.3 &n; * adapted for Linux.&n; *&n; * malloc by Hannu Savolainen 1993 and Matthias Urlichs 1994&n; *&n; * Adapted for SH by Stuart Menefy, Aug 1999&n; *&n; * Modified to use standard LinuxSH BIOS by Greg Banks 7Jul2000&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifdef CONFIG_SH_STANDARD_BIOS
macro_line|#include &lt;asm/sh_bios.h&gt;
macro_line|#endif
multiline_comment|/*&n; * gzip declarations&n; */
DECL|macro|OF
mdefine_line|#define OF(args)  args
DECL|macro|STATIC
mdefine_line|#define STATIC static
DECL|macro|memset
macro_line|#undef memset
DECL|macro|memcpy
macro_line|#undef memcpy
DECL|macro|memzero
mdefine_line|#define memzero(s, n)     memset ((s), 0, (n))
DECL|typedef|uch
r_typedef
r_int
r_char
id|uch
suffix:semicolon
DECL|typedef|ush
r_typedef
r_int
r_int
id|ush
suffix:semicolon
DECL|typedef|ulg
r_typedef
r_int
r_int
id|ulg
suffix:semicolon
DECL|macro|WSIZE
mdefine_line|#define WSIZE 0x8000&t;&t;/* Window size must be at least 32k, */
multiline_comment|/* and a power of two */
DECL|variable|inbuf
r_static
id|uch
op_star
id|inbuf
suffix:semicolon
multiline_comment|/* input buffer */
DECL|variable|window
r_static
id|uch
id|window
(braket
id|WSIZE
)braket
suffix:semicolon
multiline_comment|/* Sliding window buffer */
DECL|variable|insize
r_static
r_int
id|insize
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* valid bytes in inbuf */
DECL|variable|inptr
r_static
r_int
id|inptr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* index of next byte to be processed in inbuf */
DECL|variable|outcnt
r_static
r_int
id|outcnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* bytes in output buffer */
multiline_comment|/* gzip flag byte */
DECL|macro|ASCII_FLAG
mdefine_line|#define ASCII_FLAG   0x01 /* bit 0 set: file probably ASCII text */
DECL|macro|CONTINUATION
mdefine_line|#define CONTINUATION 0x02 /* bit 1 set: continuation of multi-part gzip file */
DECL|macro|EXTRA_FIELD
mdefine_line|#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
DECL|macro|ORIG_NAME
mdefine_line|#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
DECL|macro|COMMENT
mdefine_line|#define COMMENT      0x10 /* bit 4 set: file comment present */
DECL|macro|ENCRYPTED
mdefine_line|#define ENCRYPTED    0x20 /* bit 5 set: file is encrypted */
DECL|macro|RESERVED
mdefine_line|#define RESERVED     0xC0 /* bit 6,7:   reserved */
DECL|macro|get_byte
mdefine_line|#define get_byte()  (inptr &lt; insize ? inbuf[inptr++] : fill_inbuf())
multiline_comment|/* Diagnostic functions */
macro_line|#ifdef DEBUG
DECL|macro|Assert
macro_line|#  define Assert(cond,msg) {if(!(cond)) error(msg);}
DECL|macro|Trace
macro_line|#  define Trace(x) fprintf x
DECL|macro|Tracev
macro_line|#  define Tracev(x) {if (verbose) fprintf x ;}
DECL|macro|Tracevv
macro_line|#  define Tracevv(x) {if (verbose&gt;1) fprintf x ;}
DECL|macro|Tracec
macro_line|#  define Tracec(c,x) {if (verbose &amp;&amp; (c)) fprintf x ;}
DECL|macro|Tracecv
macro_line|#  define Tracecv(c,x) {if (verbose&gt;1 &amp;&amp; (c)) fprintf x ;}
macro_line|#else
DECL|macro|Assert
macro_line|#  define Assert(cond,msg)
DECL|macro|Trace
macro_line|#  define Trace(x)
DECL|macro|Tracev
macro_line|#  define Tracev(x)
DECL|macro|Tracevv
macro_line|#  define Tracevv(x)
DECL|macro|Tracec
macro_line|#  define Tracec(c,x)
DECL|macro|Tracecv
macro_line|#  define Tracecv(c,x)
macro_line|#endif
r_static
r_int
id|fill_inbuf
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|flush_window
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|error
c_func
(paren
r_char
op_star
id|m
)paren
suffix:semicolon
r_static
r_void
id|gzip_mark
c_func
(paren
r_void
op_star
op_star
)paren
suffix:semicolon
r_static
r_void
id|gzip_release
c_func
(paren
r_void
op_star
op_star
)paren
suffix:semicolon
r_extern
r_char
id|input_data
(braket
)braket
suffix:semicolon
r_extern
r_int
id|input_len
suffix:semicolon
DECL|variable|bytes_out
r_static
r_int
id|bytes_out
op_assign
l_int|0
suffix:semicolon
DECL|variable|output_data
r_static
id|uch
op_star
id|output_data
suffix:semicolon
DECL|variable|output_ptr
r_static
r_int
r_int
id|output_ptr
op_assign
l_int|0
suffix:semicolon
r_static
r_void
op_star
id|malloc
c_func
(paren
r_int
id|size
)paren
suffix:semicolon
r_static
r_void
id|free
c_func
(paren
r_void
op_star
id|where
)paren
suffix:semicolon
r_static
r_void
id|error
c_func
(paren
r_char
op_star
id|m
)paren
suffix:semicolon
r_static
r_void
id|gzip_mark
c_func
(paren
r_void
op_star
op_star
)paren
suffix:semicolon
r_static
r_void
id|gzip_release
c_func
(paren
r_void
op_star
op_star
)paren
suffix:semicolon
r_static
r_void
id|puts
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|_text
suffix:semicolon
multiline_comment|/* Defined in vmlinux.lds.S */
r_extern
r_int
id|_end
suffix:semicolon
DECL|variable|free_mem_ptr
r_static
r_int
r_int
id|free_mem_ptr
suffix:semicolon
DECL|variable|free_mem_end_ptr
r_static
r_int
r_int
id|free_mem_end_ptr
suffix:semicolon
DECL|macro|HEAP_SIZE
mdefine_line|#define HEAP_SIZE             0x10000
macro_line|#include &quot;../../../../lib/inflate.c&quot;
DECL|function|malloc
r_static
r_void
op_star
id|malloc
c_func
(paren
r_int
id|size
)paren
(brace
r_void
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
id|error
c_func
(paren
l_string|&quot;Malloc error&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_mem_ptr
op_eq
l_int|0
)paren
id|error
c_func
(paren
l_string|&quot;Memory error&quot;
)paren
suffix:semicolon
id|free_mem_ptr
op_assign
(paren
id|free_mem_ptr
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
multiline_comment|/* Align */
id|p
op_assign
(paren
r_void
op_star
)paren
id|free_mem_ptr
suffix:semicolon
id|free_mem_ptr
op_add_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|free_mem_ptr
op_ge
id|free_mem_end_ptr
)paren
id|error
c_func
(paren
l_string|&quot;Out of memory&quot;
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|free
r_static
r_void
id|free
c_func
(paren
r_void
op_star
id|where
)paren
(brace
multiline_comment|/* Don&squot;t care */
)brace
DECL|function|gzip_mark
r_static
r_void
id|gzip_mark
c_func
(paren
r_void
op_star
op_star
id|ptr
)paren
(brace
op_star
id|ptr
op_assign
(paren
r_void
op_star
)paren
id|free_mem_ptr
suffix:semicolon
)brace
DECL|function|gzip_release
r_static
r_void
id|gzip_release
c_func
(paren
r_void
op_star
op_star
id|ptr
)paren
(brace
id|free_mem_ptr
op_assign
(paren
r_int
)paren
op_star
id|ptr
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SH_STANDARD_BIOS
DECL|function|strlen
r_static
r_int
id|strlen
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
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|s
op_increment
)paren
id|i
op_increment
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|puts
r_void
id|puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
id|sh_bios_console_write
c_func
(paren
id|s
comma
id|strlen
c_func
(paren
id|s
)paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|puts
r_void
id|puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
multiline_comment|/* This should be updated to use the sh-sci routines */
)brace
macro_line|#endif
DECL|function|memset
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|c
comma
r_int
id|n
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|ss
op_assign
(paren
r_char
op_star
)paren
id|s
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
id|ss
(braket
id|i
)braket
op_assign
id|c
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|function|memcpy
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
id|__dest
comma
id|__const
r_void
op_star
id|__src
comma
r_int
id|__n
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|d
op_assign
(paren
r_char
op_star
)paren
id|__dest
comma
op_star
id|s
op_assign
(paren
r_char
op_star
)paren
id|__src
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
id|__n
suffix:semicolon
id|i
op_increment
)paren
id|d
(braket
id|i
)braket
op_assign
id|s
(braket
id|i
)braket
suffix:semicolon
r_return
id|__dest
suffix:semicolon
)brace
multiline_comment|/* ===========================================================================&n; * Fill the input buffer. This is called only when the buffer is empty&n; * and at least one byte is really needed.&n; */
DECL|function|fill_inbuf
r_static
r_int
id|fill_inbuf
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|insize
op_ne
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;ran out of input data&quot;
)paren
suffix:semicolon
)brace
id|inbuf
op_assign
id|input_data
suffix:semicolon
id|insize
op_assign
id|input_len
suffix:semicolon
id|inptr
op_assign
l_int|1
suffix:semicolon
r_return
id|inbuf
(braket
l_int|0
)braket
suffix:semicolon
)brace
multiline_comment|/* ===========================================================================&n; * Write the output window window[0..outcnt-1] and update crc and bytes_out.&n; * (Used for the decompressed data only.)&n; */
DECL|function|flush_window
r_static
r_void
id|flush_window
c_func
(paren
r_void
)paren
(brace
id|ulg
id|c
op_assign
id|crc
suffix:semicolon
multiline_comment|/* temporary variable */
r_int
id|n
suffix:semicolon
id|uch
op_star
id|in
comma
op_star
id|out
comma
id|ch
suffix:semicolon
id|in
op_assign
id|window
suffix:semicolon
id|out
op_assign
op_amp
id|output_data
(braket
id|output_ptr
)braket
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|outcnt
suffix:semicolon
id|n
op_increment
)paren
(brace
id|ch
op_assign
op_star
id|out
op_increment
op_assign
op_star
id|in
op_increment
suffix:semicolon
id|c
op_assign
id|crc_32_tab
(braket
(paren
(paren
r_int
)paren
id|c
op_xor
id|ch
)paren
op_amp
l_int|0xff
)braket
op_xor
(paren
id|c
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
id|crc
op_assign
id|c
suffix:semicolon
id|bytes_out
op_add_assign
(paren
id|ulg
)paren
id|outcnt
suffix:semicolon
id|output_ptr
op_add_assign
(paren
id|ulg
)paren
id|outcnt
suffix:semicolon
id|outcnt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|error
r_static
r_void
id|error
c_func
(paren
r_char
op_star
id|x
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|puts
c_func
(paren
id|x
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&bslash;n -- System halted&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Halt */
)brace
DECL|macro|STACK_SIZE
mdefine_line|#define STACK_SIZE (4096)
DECL|variable|user_stack
r_int
id|user_stack
(braket
id|STACK_SIZE
)braket
suffix:semicolon
DECL|variable|stack_start
r_int
op_star
id|stack_start
op_assign
op_amp
id|user_stack
(braket
id|STACK_SIZE
)braket
suffix:semicolon
DECL|function|decompress_kernel
r_void
id|decompress_kernel
c_func
(paren
r_void
)paren
(brace
id|output_data
op_assign
l_int|0
suffix:semicolon
id|output_ptr
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_text
op_plus
l_int|0x20001000
suffix:semicolon
id|free_mem_ptr
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
id|free_mem_end_ptr
op_assign
id|free_mem_ptr
op_plus
id|HEAP_SIZE
suffix:semicolon
id|makecrc
c_func
(paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;Uncompressing Linux... &quot;
)paren
suffix:semicolon
id|gunzip
c_func
(paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;Ok, booting the kernel.&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
