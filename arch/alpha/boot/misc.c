multiline_comment|/*&n; * misc.c&n; * &n; * This is a collection of several routines from gzip-1.0.3 &n; * adapted for Linux.&n; *&n; * malloc by Hannu Savolainen 1993 and Matthias Urlichs 1994&n; *&n; * Modified for ARM Linux by Russell King&n; *&n; * Nicolas Pitre &lt;nico@visuaide.com&gt;  1999/04/14 :&n; *  For this code to run directly from Flash, all constant variables must&n; *  be marked with &squot;const&squot; and all other variables initialized at run-time &n; *  only.  This way all non constant variables will end up in the bss segment,&n; *  which should point to addresses in RAM and cleared to 0 on start.&n; *  This allows for a much quicker boot time.&n; *&n; * Modified for Alpha, from the ARM version, by Jay Estabrook 2003.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|memzero
mdefine_line|#define memzero(s,n)&t;memset ((s),0,(n))
DECL|macro|puts
mdefine_line|#define puts&t;&t;srm_printk
r_extern
r_int
id|srm_printk
c_func
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
suffix:semicolon
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
op_star
id|window
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
DECL|variable|input_data
r_static
r_char
op_star
id|input_data
suffix:semicolon
DECL|variable|input_data_size
r_static
r_int
id|input_data_size
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
macro_line|#include &quot;../../../lib/inflate.c&quot;
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
id|input_data_size
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
multiline_comment|/*&t;puts(&quot;.&quot;); */
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
r_int
r_int
DECL|function|decompress_kernel
id|decompress_kernel
c_func
(paren
r_void
op_star
id|output_start
comma
r_void
op_star
id|input_start
comma
r_int
id|ksize
comma
r_int
id|kzsize
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
id|input_data
op_assign
(paren
id|uch
op_star
)paren
id|input_start
suffix:semicolon
id|input_data_size
op_assign
id|kzsize
suffix:semicolon
multiline_comment|/* use compressed size */
multiline_comment|/* FIXME FIXME FIXME */
id|free_mem_ptr
op_assign
(paren
id|ulg
)paren
id|output_start
op_plus
id|ksize
suffix:semicolon
id|free_mem_ptr_end
op_assign
(paren
id|ulg
)paren
id|output_start
op_plus
id|ksize
op_plus
l_int|0x200000
suffix:semicolon
multiline_comment|/* FIXME FIXME FIXME */
multiline_comment|/* put in temp area to reduce initial footprint */
id|window
op_assign
id|malloc
c_func
(paren
id|WSIZE
)paren
suffix:semicolon
id|makecrc
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&t;puts(&quot;Uncompressing Linux...&quot;); */
id|gunzip
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&t;puts(&quot; done, booting the kernel.&bslash;n&quot;); */
r_return
id|output_ptr
suffix:semicolon
)brace
multiline_comment|/* dummy-up printk */
DECL|function|printk
id|asmlinkage
r_int
id|printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|ret
op_assign
id|srm_printk
c_func
(paren
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
