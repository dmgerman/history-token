multiline_comment|/*&n; * misc.c&n; * &n; * This is a collection of several routines from gzip-1.0.3 &n; * adapted for Linux.&n; *&n; * malloc by Hannu Savolainen 1993 and Matthias Urlichs 1994&n; * puts by Nick Holloway 1993, better puts by Martin Mares 1995&n; * High loaded stuff by Hans Lermen &amp; Werner Almesberger, Feb. 1996&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;video/edid.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * gzip declarations&n; */
DECL|macro|OF
mdefine_line|#define OF(args)  args
DECL|macro|STATIC
mdefine_line|#define STATIC static
DECL|macro|memset
macro_line|#undef memset
DECL|macro|memcpy
macro_line|#undef memcpy
multiline_comment|/*&n; * Why do we do this? Don&squot;t ask me..&n; *&n; * Incomprehensible are the ways of bootloaders.&n; */
r_static
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_static
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
comma
id|__const
r_void
op_star
comma
r_int
)paren
suffix:semicolon
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
multiline_comment|/*&n; * This is set up by the setup-routine at boot-time&n; */
DECL|variable|real_mode
r_static
r_int
r_char
op_star
id|real_mode
suffix:semicolon
multiline_comment|/* Pointer to real-mode data */
DECL|macro|RM_EXT_MEM_K
mdefine_line|#define RM_EXT_MEM_K   (*(unsigned short *)(real_mode + 0x2))
macro_line|#ifndef STANDARD_MEMORY_BIOS_CALL
DECL|macro|RM_ALT_MEM_K
mdefine_line|#define RM_ALT_MEM_K   (*(unsigned long *)(real_mode + 0x1e0))
macro_line|#endif
DECL|macro|RM_SCREEN_INFO
mdefine_line|#define RM_SCREEN_INFO (*(struct screen_info *)(real_mode+0))
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
id|putstr
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|end
suffix:semicolon
DECL|variable|free_mem_ptr
r_static
r_int
id|free_mem_ptr
op_assign
(paren
r_int
)paren
op_amp
id|end
suffix:semicolon
DECL|variable|free_mem_end_ptr
r_static
r_int
id|free_mem_end_ptr
suffix:semicolon
DECL|macro|INPLACE_MOVE_ROUTINE
mdefine_line|#define INPLACE_MOVE_ROUTINE  0x1000
DECL|macro|LOW_BUFFER_START
mdefine_line|#define LOW_BUFFER_START      0x2000
DECL|macro|LOW_BUFFER_MAX
mdefine_line|#define LOW_BUFFER_MAX       0x90000
DECL|macro|HEAP_SIZE
mdefine_line|#define HEAP_SIZE             0x3000
DECL|variable|low_buffer_end
DECL|variable|low_buffer_size
r_static
r_int
r_int
id|low_buffer_end
comma
id|low_buffer_size
suffix:semicolon
DECL|variable|high_loaded
r_static
r_int
id|high_loaded
op_assign
l_int|0
suffix:semicolon
DECL|variable|high_buffer_start
r_static
id|uch
op_star
id|high_buffer_start
multiline_comment|/* = (uch *)(((ulg)&amp;end) + HEAP_SIZE)*/
suffix:semicolon
DECL|variable|vidmem
r_static
r_char
op_star
id|vidmem
op_assign
(paren
r_char
op_star
)paren
l_int|0xb8000
suffix:semicolon
DECL|variable|vidport
r_static
r_int
id|vidport
suffix:semicolon
DECL|variable|lines
DECL|variable|cols
r_static
r_int
id|lines
comma
id|cols
suffix:semicolon
macro_line|#ifdef CONFIG_X86_NUMAQ
DECL|variable|xquad_portio
r_static
r_void
op_star
id|xquad_portio
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
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
op_le
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
DECL|function|scroll
r_static
r_void
id|scroll
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|memcpy
(paren
id|vidmem
comma
id|vidmem
op_plus
id|cols
op_star
l_int|2
comma
(paren
id|lines
op_minus
l_int|1
)paren
op_star
id|cols
op_star
l_int|2
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
(paren
id|lines
op_minus
l_int|1
)paren
op_star
id|cols
op_star
l_int|2
suffix:semicolon
id|i
OL
id|lines
op_star
id|cols
op_star
l_int|2
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
id|vidmem
(braket
id|i
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
DECL|function|putstr
r_static
r_void
id|putstr
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|x
comma
id|y
comma
id|pos
suffix:semicolon
r_char
id|c
suffix:semicolon
id|x
op_assign
id|RM_SCREEN_INFO.orig_x
suffix:semicolon
id|y
op_assign
id|RM_SCREEN_INFO.orig_y
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|y
op_ge
id|lines
)paren
(brace
id|scroll
c_func
(paren
)paren
suffix:semicolon
id|y
op_decrement
suffix:semicolon
)brace
)brace
r_else
(brace
id|vidmem
(braket
(paren
id|x
op_plus
id|cols
op_star
id|y
)paren
op_star
l_int|2
)braket
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|x
op_ge
id|cols
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|y
op_ge
id|lines
)paren
(brace
id|scroll
c_func
(paren
)paren
suffix:semicolon
id|y
op_decrement
suffix:semicolon
)brace
)brace
)brace
)brace
id|RM_SCREEN_INFO.orig_x
op_assign
id|x
suffix:semicolon
id|RM_SCREEN_INFO.orig_y
op_assign
id|y
suffix:semicolon
id|pos
op_assign
(paren
id|x
op_plus
id|cols
op_star
id|y
)paren
op_star
l_int|2
suffix:semicolon
multiline_comment|/* Update cursor position */
id|outb_p
c_func
(paren
l_int|14
comma
id|vidport
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xff
op_amp
(paren
id|pos
op_rshift
l_int|9
)paren
comma
id|vidport
op_plus
l_int|1
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|15
comma
id|vidport
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xff
op_amp
(paren
id|pos
op_rshift
l_int|1
)paren
comma
id|vidport
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|memset
r_static
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
r_static
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
DECL|function|flush_window_low
r_static
r_void
id|flush_window_low
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
DECL|function|flush_window_high
r_static
r_void
id|flush_window_high
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
id|ch
suffix:semicolon
id|in
op_assign
id|window
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
id|output_data
op_increment
op_assign
op_star
id|in
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ulg
)paren
id|output_data
op_eq
id|low_buffer_end
)paren
id|output_data
op_assign
id|high_buffer_start
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
id|outcnt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|flush_window
r_static
r_void
id|flush_window
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|high_loaded
)paren
id|flush_window_high
c_func
(paren
)paren
suffix:semicolon
r_else
id|flush_window_low
c_func
(paren
)paren
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
id|putstr
c_func
(paren
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|putstr
c_func
(paren
id|x
)paren
suffix:semicolon
id|putstr
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
r_struct
(brace
DECL|member|a
r_int
op_star
id|a
suffix:semicolon
DECL|member|b
r_int
id|b
suffix:semicolon
DECL|variable|stack_start
)brace
id|stack_start
op_assign
(brace
op_amp
id|user_stack
(braket
id|STACK_SIZE
)braket
comma
id|__BOOT_DS
)brace
suffix:semicolon
DECL|function|setup_normal_output_buffer
r_static
r_void
id|setup_normal_output_buffer
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef STANDARD_MEMORY_BIOS_CALL
r_if
c_cond
(paren
id|RM_EXT_MEM_K
OL
l_int|1024
)paren
id|error
c_func
(paren
l_string|&quot;Less than 2MB of memory&quot;
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
(paren
id|RM_ALT_MEM_K
OG
id|RM_EXT_MEM_K
ques
c_cond
id|RM_ALT_MEM_K
suffix:colon
id|RM_EXT_MEM_K
)paren
OL
l_int|1024
)paren
id|error
c_func
(paren
l_string|&quot;Less than 2MB of memory&quot;
)paren
suffix:semicolon
macro_line|#endif
id|output_data
op_assign
(paren
r_char
op_star
)paren
l_int|0x100000
suffix:semicolon
multiline_comment|/* Points to 1M */
id|free_mem_end_ptr
op_assign
(paren
r_int
)paren
id|real_mode
suffix:semicolon
)brace
DECL|struct|moveparams
r_struct
id|moveparams
(brace
DECL|member|low_buffer_start
DECL|member|lcount
id|uch
op_star
id|low_buffer_start
suffix:semicolon
r_int
id|lcount
suffix:semicolon
DECL|member|high_buffer_start
DECL|member|hcount
id|uch
op_star
id|high_buffer_start
suffix:semicolon
r_int
id|hcount
suffix:semicolon
)brace
suffix:semicolon
DECL|function|setup_output_buffer_if_we_run_high
r_static
r_void
id|setup_output_buffer_if_we_run_high
c_func
(paren
r_struct
id|moveparams
op_star
id|mv
)paren
(brace
id|high_buffer_start
op_assign
(paren
id|uch
op_star
)paren
(paren
(paren
(paren
id|ulg
)paren
op_amp
id|end
)paren
op_plus
id|HEAP_SIZE
)paren
suffix:semicolon
macro_line|#ifdef STANDARD_MEMORY_BIOS_CALL
r_if
c_cond
(paren
id|RM_EXT_MEM_K
OL
(paren
l_int|3
op_star
l_int|1024
)paren
)paren
id|error
c_func
(paren
l_string|&quot;Less than 4MB of memory&quot;
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
(paren
id|RM_ALT_MEM_K
OG
id|RM_EXT_MEM_K
ques
c_cond
id|RM_ALT_MEM_K
suffix:colon
id|RM_EXT_MEM_K
)paren
OL
(paren
l_int|3
op_star
l_int|1024
)paren
)paren
id|error
c_func
(paren
l_string|&quot;Less than 4MB of memory&quot;
)paren
suffix:semicolon
macro_line|#endif&t;
id|mv-&gt;low_buffer_start
op_assign
id|output_data
op_assign
(paren
r_char
op_star
)paren
id|LOW_BUFFER_START
suffix:semicolon
id|low_buffer_end
op_assign
(paren
(paren
r_int
r_int
)paren
id|real_mode
OG
id|LOW_BUFFER_MAX
ques
c_cond
id|LOW_BUFFER_MAX
suffix:colon
(paren
r_int
r_int
)paren
id|real_mode
)paren
op_amp
op_complement
l_int|0xfff
suffix:semicolon
id|low_buffer_size
op_assign
id|low_buffer_end
op_minus
id|LOW_BUFFER_START
suffix:semicolon
id|high_loaded
op_assign
l_int|1
suffix:semicolon
id|free_mem_end_ptr
op_assign
(paren
r_int
)paren
id|high_buffer_start
suffix:semicolon
r_if
c_cond
(paren
(paren
l_int|0x100000
op_plus
id|low_buffer_size
)paren
OG
(paren
(paren
id|ulg
)paren
id|high_buffer_start
)paren
)paren
(brace
id|high_buffer_start
op_assign
(paren
id|uch
op_star
)paren
(paren
l_int|0x100000
op_plus
id|low_buffer_size
)paren
suffix:semicolon
id|mv-&gt;hcount
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* say: we need not to move high_buffer */
)brace
r_else
id|mv-&gt;hcount
op_assign
op_minus
l_int|1
suffix:semicolon
id|mv-&gt;high_buffer_start
op_assign
id|high_buffer_start
suffix:semicolon
)brace
DECL|function|close_output_buffer_if_we_run_high
r_static
r_void
id|close_output_buffer_if_we_run_high
c_func
(paren
r_struct
id|moveparams
op_star
id|mv
)paren
(brace
r_if
c_cond
(paren
id|bytes_out
OG
id|low_buffer_size
)paren
(brace
id|mv-&gt;lcount
op_assign
id|low_buffer_size
suffix:semicolon
r_if
c_cond
(paren
id|mv-&gt;hcount
)paren
id|mv-&gt;hcount
op_assign
id|bytes_out
op_minus
id|low_buffer_size
suffix:semicolon
)brace
r_else
(brace
id|mv-&gt;lcount
op_assign
id|bytes_out
suffix:semicolon
id|mv-&gt;hcount
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|decompress_kernel
id|asmlinkage
r_int
id|decompress_kernel
c_func
(paren
r_struct
id|moveparams
op_star
id|mv
comma
r_void
op_star
id|rmode
)paren
(brace
id|real_mode
op_assign
id|rmode
suffix:semicolon
r_if
c_cond
(paren
id|RM_SCREEN_INFO.orig_video_mode
op_eq
l_int|7
)paren
(brace
id|vidmem
op_assign
(paren
r_char
op_star
)paren
l_int|0xb0000
suffix:semicolon
id|vidport
op_assign
l_int|0x3b4
suffix:semicolon
)brace
r_else
(brace
id|vidmem
op_assign
(paren
r_char
op_star
)paren
l_int|0xb8000
suffix:semicolon
id|vidport
op_assign
l_int|0x3d4
suffix:semicolon
)brace
id|lines
op_assign
id|RM_SCREEN_INFO.orig_video_lines
suffix:semicolon
id|cols
op_assign
id|RM_SCREEN_INFO.orig_video_cols
suffix:semicolon
r_if
c_cond
(paren
id|free_mem_ptr
OL
l_int|0x100000
)paren
id|setup_normal_output_buffer
c_func
(paren
)paren
suffix:semicolon
r_else
id|setup_output_buffer_if_we_run_high
c_func
(paren
id|mv
)paren
suffix:semicolon
id|makecrc
c_func
(paren
)paren
suffix:semicolon
id|putstr
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
id|putstr
c_func
(paren
l_string|&quot;Ok, booting the kernel.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|high_loaded
)paren
id|close_output_buffer_if_we_run_high
c_func
(paren
id|mv
)paren
suffix:semicolon
r_return
id|high_loaded
suffix:semicolon
)brace
eof
