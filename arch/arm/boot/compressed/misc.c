multiline_comment|/*&n; * misc.c&n; * &n; * This is a collection of several routines from gzip-1.0.3 &n; * adapted for Linux.&n; *&n; * malloc by Hannu Savolainen 1993 and Matthias Urlichs 1994&n; *&n; * Modified for ARM Linux by Russell King&n; *&n; * Nicolas Pitre &lt;nico@visuaide.com&gt;  1999/04/14 :&n; *  For this code to run directly from Flash, all constant variables must&n; *  be marked with &squot;const&squot; and all other variables initialized at run-time &n; *  only.  This way all non constant variables will end up in the bss segment,&n; *  which should point to addresses in RAM and cleared to 0 on start.&n; *  This allows for a much quicker boot time.&n; */
DECL|variable|__machine_arch_type
r_int
r_int
id|__machine_arch_type
suffix:semicolon
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/arch/uncompress.h&gt;
macro_line|#ifdef STANDALONE_DEBUG
DECL|macro|puts
mdefine_line|#define puts printf
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUG_ICEDCC
DECL|macro|puts
mdefine_line|#define puts icedcc_puts
DECL|macro|putc
mdefine_line|#define putc icedcc_putc
r_extern
r_void
id|idedcc_putc
c_func
(paren
r_int
id|ch
)paren
suffix:semicolon
r_static
r_void
DECL|function|icedcc_puts
id|icedcc_puts
c_func
(paren
r_const
r_char
op_star
id|ptr
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
op_star
id|ptr
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|ptr
op_increment
)paren
(brace
id|icedcc_putc
c_func
(paren
op_star
id|ptr
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|macro|__ptr_t
mdefine_line|#define __ptr_t void *
multiline_comment|/*&n; * Optimised C version of memzero for the ARM.&n; */
DECL|function|__memzero
r_void
id|__memzero
(paren
id|__ptr_t
id|s
comma
r_int
id|n
)paren
(brace
r_union
(brace
r_void
op_star
id|vp
suffix:semicolon
r_int
r_int
op_star
id|ulp
suffix:semicolon
r_int
r_char
op_star
id|ucp
suffix:semicolon
)brace
id|u
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u.vp
op_assign
id|s
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|n
op_rshift
l_int|5
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_amp
l_int|1
op_lshift
l_int|4
)paren
(brace
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_amp
l_int|1
op_lshift
l_int|3
)paren
(brace
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_amp
l_int|1
op_lshift
l_int|2
)paren
op_star
id|u.ulp
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|n
op_amp
l_int|1
op_lshift
l_int|1
)paren
(brace
op_star
id|u.ucp
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|u.ucp
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_amp
l_int|1
)paren
op_star
id|u.ucp
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|memcpy
r_static
r_inline
id|__ptr_t
id|memcpy
c_func
(paren
id|__ptr_t
id|__dest
comma
id|__const
id|__ptr_t
id|__src
comma
r_int
id|__n
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
r_char
op_star
id|d
op_assign
(paren
r_int
r_char
op_star
)paren
id|__dest
comma
op_star
id|s
op_assign
(paren
r_int
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
id|__n
op_rshift
l_int|3
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|__n
op_amp
l_int|1
op_lshift
l_int|2
)paren
(brace
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|__n
op_amp
l_int|1
op_lshift
l_int|1
)paren
(brace
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|__n
op_amp
l_int|1
)paren
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_return
id|__dest
suffix:semicolon
)brace
multiline_comment|/*&n; * gzip delarations&n; */
DECL|macro|OF
mdefine_line|#define OF(args)  args
DECL|macro|STATIC
mdefine_line|#define STATIC static
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
suffix:semicolon
multiline_comment|/* valid bytes in inbuf */
DECL|variable|inptr
r_static
r_int
id|inptr
suffix:semicolon
multiline_comment|/* index of next byte to be processed in inbuf */
DECL|variable|outcnt
r_static
r_int
id|outcnt
suffix:semicolon
multiline_comment|/* bytes in output buffer */
multiline_comment|/* gzip flag byte */
DECL|macro|ASCII_FLAG
mdefine_line|#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
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
r_char
id|input_data_end
(braket
)braket
suffix:semicolon
DECL|variable|output_data
r_static
id|uch
op_star
id|output_data
suffix:semicolon
DECL|variable|output_ptr
r_static
id|ulg
id|output_ptr
suffix:semicolon
DECL|variable|bytes_out
r_static
id|ulg
id|bytes_out
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
id|end
suffix:semicolon
DECL|variable|free_mem_ptr
r_static
id|ulg
id|free_mem_ptr
suffix:semicolon
DECL|variable|free_mem_ptr_end
r_static
id|ulg
id|free_mem_ptr_end
suffix:semicolon
DECL|macro|HEAP_SIZE
mdefine_line|#define HEAP_SIZE 0x2000
macro_line|#include &quot;../../../../lib/inflate.c&quot;
macro_line|#ifndef STANDALONE_DEBUG
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
id|free_mem_ptr_end
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
multiline_comment|/* gzip_mark &amp; gzip_release do the free */
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
id|arch_decomp_wdog
c_func
(paren
)paren
suffix:semicolon
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
id|arch_decomp_wdog
c_func
(paren
)paren
suffix:semicolon
id|free_mem_ptr
op_assign
(paren
r_int
)paren
op_star
id|ptr
suffix:semicolon
)brace
macro_line|#else
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
)brace
macro_line|#endif
multiline_comment|/* ===========================================================================&n; * Fill the input buffer. This is called only when the buffer is empty&n; * and at least one byte is really needed.&n; */
DECL|function|fill_inbuf
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
id|error
c_func
(paren
l_string|&quot;ran out of input data&quot;
)paren
suffix:semicolon
id|inbuf
op_assign
id|input_data
suffix:semicolon
id|insize
op_assign
op_amp
id|input_data_end
(braket
l_int|0
)braket
op_minus
op_amp
id|input_data
(braket
l_int|0
)braket
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
id|puts
c_func
(paren
l_string|&quot;.&quot;
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
macro_line|#ifndef STANDALONE_DEBUG
id|ulg
DECL|function|decompress_kernel
id|decompress_kernel
c_func
(paren
id|ulg
id|output_start
comma
id|ulg
id|free_mem_ptr_p
comma
id|ulg
id|free_mem_ptr_end_p
comma
r_int
id|arch_id
)paren
(brace
id|output_data
op_assign
(paren
id|uch
op_star
)paren
id|output_start
suffix:semicolon
multiline_comment|/* Points to kernel start */
id|free_mem_ptr
op_assign
id|free_mem_ptr_p
suffix:semicolon
id|free_mem_ptr_end
op_assign
id|free_mem_ptr_end_p
suffix:semicolon
id|__machine_arch_type
op_assign
id|arch_id
suffix:semicolon
id|arch_decomp_setup
c_func
(paren
)paren
suffix:semicolon
id|makecrc
c_func
(paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;Uncompressing Linux...&quot;
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
l_string|&quot; done, booting the kernel.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|output_ptr
suffix:semicolon
)brace
macro_line|#else
DECL|variable|output_buffer
r_char
id|output_buffer
(braket
l_int|1500
op_star
l_int|1024
)braket
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
)paren
(brace
id|output_data
op_assign
id|output_buffer
suffix:semicolon
id|makecrc
c_func
(paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;Uncompressing Linux...&quot;
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
l_string|&quot;done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
