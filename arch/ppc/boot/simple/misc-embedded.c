multiline_comment|/*&n; * Originally adapted by Gary Thomas.  Much additional work by&n; * Cort Dougan &lt;cort@fsmlabs.com&gt;.  On top of that still more work by&n; * Dan Malek &lt;dmalek@jlc.net&gt;.&n; *&n; * Currently maintained by: Tom Rini &lt;trini@kernel.crashing.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/ibm4xx.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/mpc8xx.h&gt;
macro_line|#include &lt;asm/mpc8260.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &quot;nonstdio.h&quot;
macro_line|#include &quot;zlib.h&quot;
multiline_comment|/* The linker tells us where the image is. */
r_extern
r_char
id|__image_begin
comma
id|__image_end
suffix:semicolon
r_extern
r_char
id|__ramdisk_begin
comma
id|__ramdisk_end
suffix:semicolon
r_extern
r_char
id|_end
(braket
)braket
suffix:semicolon
multiline_comment|/* Because of the limited amount of memory on embedded, it presents&n; * loading problems.  The biggest is that we load this boot program&n; * into a relatively low memory address, and the Linux kernel Bss often&n; * extends into this space when it get loaded.  When the kernel starts&n; * and zeros the BSS space, it also writes over the information we&n; * save here and pass to the kernel (usually board info).&n; * On these boards, we grab some known memory holes to hold this information.&n; */
DECL|variable|cmd_buf
r_char
id|cmd_buf
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|cmd_line
r_char
op_star
id|cmd_line
op_assign
id|cmd_buf
suffix:semicolon
DECL|variable|avail_ram
r_char
op_star
id|avail_ram
suffix:semicolon
DECL|variable|end_avail
r_char
op_star
id|end_avail
suffix:semicolon
DECL|variable|zimage_start
r_char
op_star
id|zimage_start
suffix:semicolon
multiline_comment|/* This is for 4xx treeboot.  It provides a place for the bootrom&n; * give us a pointer to a rom environment command line.&n; */
DECL|variable|bootrom_cmdline
r_char
op_star
id|bootrom_cmdline
op_assign
l_string|&quot;&quot;
suffix:semicolon
multiline_comment|/* This is the default cmdline that will be given to the user at boot time..&n; * If none was specified at compile time, we&squot;ll give it one that should work.&n; * -- Tom */
macro_line|#ifdef CONFIG_CMDLINE_BOOL
DECL|variable|compiled_string
r_char
id|compiled_string
(braket
)braket
op_assign
id|CONFIG_CMDLINE
suffix:semicolon
macro_line|#endif
DECL|variable|ramroot_string
r_char
id|ramroot_string
(braket
)braket
op_assign
l_string|&quot;root=/dev/ram&quot;
suffix:semicolon
DECL|variable|netroot_string
r_char
id|netroot_string
(braket
)braket
op_assign
l_string|&quot;root=/dev/nfs rw ip=on&quot;
suffix:semicolon
multiline_comment|/* Serial port to use. */
DECL|variable|com_port
r_int
r_int
id|com_port
suffix:semicolon
multiline_comment|/* We need to make sure that this is before the images to ensure&n; * that it&squot;s in a mapped location. - Tom */
DECL|variable|hold_resid_buf
id|bd_t
id|hold_resid_buf
id|__attribute__
(paren
(paren
id|__section__
(paren
l_string|&quot;.data.boot&quot;
)paren
)paren
)paren
suffix:semicolon
DECL|variable|hold_residual
id|bd_t
op_star
id|hold_residual
op_assign
op_amp
id|hold_resid_buf
suffix:semicolon
r_extern
r_int
r_int
id|serial_init
c_func
(paren
r_int
id|chan
comma
id|bd_t
op_star
id|bp
)paren
suffix:semicolon
r_extern
r_void
id|serial_close
c_func
(paren
r_int
r_int
id|com_port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|start
suffix:semicolon
r_extern
r_void
id|flush_instruction_cache
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gunzip
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bp
)paren
suffix:semicolon
r_int
r_int
DECL|function|decompress_kernel
id|decompress_kernel
c_func
(paren
r_int
r_int
id|load_addr
comma
r_int
id|num_words
comma
r_int
r_int
id|cksum
comma
id|bd_t
op_star
id|bp
)paren
(brace
r_char
op_star
id|cp
comma
id|ch
suffix:semicolon
r_int
id|timer
op_assign
l_int|0
comma
id|zimage_size
suffix:semicolon
r_int
r_int
id|initrd_size
suffix:semicolon
multiline_comment|/* First, capture the embedded board information.  Then&n;&t; * initialize the serial console port.&n;&t; */
id|embed_config
c_func
(paren
op_amp
id|bp
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SERIAL_CONSOLE) || defined(CONFIG_SERIAL_8250_CONSOLE)
id|com_port
op_assign
id|serial_init
c_func
(paren
l_int|0
comma
id|bp
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Grab some space for the command line and board info.  Since&n;&t; * we no longer use the ELF header, but it was loaded, grab&n;&t; * that space.&n;&t; */
macro_line|#ifdef CONFIG_MBX
multiline_comment|/* Because of the way the MBX loads the ELF image, we can&squot;t&n;&t; * tell where we started.  We read a magic variable from the NVRAM&n;&t; * that gives us the intermediate buffer load address.&n;&t; */
id|load_addr
op_assign
op_star
(paren
id|uint
op_star
)paren
l_int|0xfa000020
suffix:semicolon
id|load_addr
op_add_assign
l_int|0x10000
suffix:semicolon
multiline_comment|/* Skip ELF header */
macro_line|#endif
multiline_comment|/* copy board data */
r_if
c_cond
(paren
id|bp
)paren
id|memcpy
c_func
(paren
id|hold_residual
comma
id|bp
comma
r_sizeof
(paren
id|bd_t
)paren
)paren
suffix:semicolon
multiline_comment|/* Set end of memory available to us.  It is always the highest&n;&t; * memory address provided by the board information.&n;&t; */
id|end_avail
op_assign
(paren
r_char
op_star
)paren
(paren
id|bp-&gt;bi_memsize
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;nloaded at:     &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
id|load_addr
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|load_addr
op_plus
(paren
l_int|4
op_star
id|num_words
)paren
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|load_addr
op_ne
(paren
r_int
r_int
)paren
op_amp
id|start
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;relocated to:  &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|start
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
(paren
r_int
r_int
)paren
op_amp
id|start
op_plus
(paren
l_int|4
op_star
id|num_words
)paren
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bp
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;board data at: &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|bp
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
(paren
r_int
r_int
)paren
id|bp
op_plus
r_sizeof
(paren
id|bd_t
)paren
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;nrelocated to:  &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|hold_residual
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
(paren
r_int
r_int
)paren
id|hold_residual
op_plus
r_sizeof
(paren
id|bd_t
)paren
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We link ourself to an arbitrary low address.  When we run, we&n;&t; * relocate outself to that address.  __image_being points to&n;&t; * the part of the image where the zImage is. -- Tom&n;&t; */
id|zimage_start
op_assign
(paren
r_char
op_star
)paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__image_begin
)paren
suffix:semicolon
id|zimage_size
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|__image_end
)paren
op_minus
(paren
r_int
r_int
)paren
(paren
op_amp
id|__image_begin
)paren
suffix:semicolon
id|initrd_size
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_end
)paren
op_minus
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_begin
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The zImage and initrd will be between start and _end, so they&squot;ve&n;&t; * already been moved once.  We&squot;re good to go now. -- Tom&n;&t; */
id|puts
c_func
(paren
l_string|&quot;zimage at:     &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|zimage_start
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|zimage_size
op_plus
id|zimage_start
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initrd_size
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;initrd at:     &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_begin
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_end
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * setup avail_ram - this is the first part of ram usable&n;&t; * by the uncompress code.  Anything after this program in RAM&n;&t; * is now fair game. -- Tom&n;&t; */
id|avail_ram
op_assign
(paren
r_char
op_star
)paren
id|PAGE_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
id|_end
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;avail ram:     &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|avail_ram
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|end_avail
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;nLinux/PPC load: &quot;
)paren
suffix:semicolon
id|cp
op_assign
id|cmd_line
suffix:semicolon
multiline_comment|/* This is where we try and pick the right command line for booting.&n;&t; * If we were given one at compile time, use it.  It Is Right.&n;&t; * If we weren&squot;t, see if we have a ramdisk.  If so, thats root.&n;&t; * When in doubt, give them the netroot (root=/dev/nfs rw) -- Tom&n;&t; */
macro_line|#ifdef CONFIG_CMDLINE_BOOL
id|memcpy
(paren
id|cmd_line
comma
id|compiled_string
comma
r_sizeof
(paren
id|compiled_string
)paren
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|initrd_size
)paren
id|memcpy
(paren
id|cmd_line
comma
id|ramroot_string
comma
r_sizeof
(paren
id|ramroot_string
)paren
)paren
suffix:semicolon
r_else
id|memcpy
(paren
id|cmd_line
comma
id|netroot_string
comma
r_sizeof
(paren
id|netroot_string
)paren
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
op_star
id|cp
)paren
id|putc
c_func
(paren
op_star
id|cp
op_increment
)paren
suffix:semicolon
r_while
c_loop
(paren
id|timer
op_increment
OL
l_int|5
op_star
l_int|1000
)paren
(brace
r_if
c_cond
(paren
id|tstc
c_func
(paren
)paren
)paren
(brace
r_while
c_loop
(paren
(paren
id|ch
op_assign
id|getc
c_func
(paren
)paren
)paren
op_ne
l_char|&squot;&bslash;n&squot;
op_logical_and
id|ch
op_ne
l_char|&squot;&bslash;r&squot;
)paren
(brace
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;&bslash;b&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;&bslash;177&squot;
)paren
(brace
r_if
c_cond
(paren
id|cp
op_ne
id|cmd_line
)paren
(brace
id|cp
op_decrement
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;b &bslash;b&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;&bslash;030&squot;
multiline_comment|/* ^x */
op_logical_or
id|ch
op_eq
l_char|&squot;&bslash;025&squot;
)paren
(brace
multiline_comment|/* ^u */
r_while
c_loop
(paren
id|cp
op_ne
id|cmd_line
)paren
(brace
id|cp
op_decrement
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;b &bslash;b&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
op_star
id|cp
op_increment
op_assign
id|ch
suffix:semicolon
id|putc
c_func
(paren
id|ch
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
multiline_comment|/* Exit &squot;timer&squot; loop */
)brace
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* 1 msec */
)brace
op_star
id|cp
op_assign
l_int|0
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;nUncompressing Linux...&quot;
)paren
suffix:semicolon
id|gunzip
c_func
(paren
l_int|0
comma
l_int|0x400000
comma
id|zimage_start
comma
op_amp
id|zimage_size
)paren
suffix:semicolon
id|flush_instruction_cache
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
(brace
r_struct
id|bi_record
op_star
id|rec
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
id|_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
id|zimage_size
op_plus
(paren
l_int|1
op_lshift
l_int|20
)paren
op_minus
l_int|1
comma
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_FIRST
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_CMD_LINE
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|rec-&gt;data
comma
id|cmd_line
comma
id|strlen
c_func
(paren
id|cmd_line
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
id|strlen
c_func
(paren
id|cmd_line
)paren
op_plus
l_int|1
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initrd_size
)paren
(brace
id|rec-&gt;tag
op_assign
id|BI_INITRD
suffix:semicolon
id|rec-&gt;data
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_begin
)paren
suffix:semicolon
id|rec-&gt;data
(braket
l_int|1
)braket
op_assign
id|initrd_size
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
l_int|2
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
)brace
id|rec-&gt;tag
op_assign
id|BI_LAST
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
)brace
id|puts
c_func
(paren
l_string|&quot;Now booting the kernel&bslash;n&quot;
)paren
suffix:semicolon
id|serial_close
c_func
(paren
id|com_port
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|hold_residual
suffix:semicolon
)brace
eof
