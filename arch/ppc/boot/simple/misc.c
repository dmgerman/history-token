multiline_comment|/*&n; * arch/ppc/simple/misc.c&n; *&n; * Misc. bootloader code for many machines.  This assumes you have are using&n; * a 6xx/7xx/74xx CPU in your machine.  This assumes the chunk of memory&n; * below 8MB is free.  Finally, it assumes you have a NS16550-style uart for&n; * your serial console.  If a machine meets these requirements, it can quite&n; * likely use this code during boot.&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; * Derived from arch/ppc/boot/prep/misc.c&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#ifdef CONFIG_44x
macro_line|#include &lt;asm/ibm4xx.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/reg.h&gt;
macro_line|#include &quot;nonstdio.h&quot;
macro_line|#include &quot;zlib.h&quot;
multiline_comment|/* Default cmdline */
macro_line|#ifdef CONFIG_CMDLINE
DECL|macro|CMDLINE
mdefine_line|#define CMDLINE CONFIG_CMDLINE
macro_line|#else
DECL|macro|CMDLINE
mdefine_line|#define CMDLINE &quot;&quot;
macro_line|#endif
multiline_comment|/* Keyboard (and VGA console)? */
macro_line|#ifdef CONFIG_VGA_CONSOLE
DECL|macro|HAS_KEYB
mdefine_line|#define HAS_KEYB 1
macro_line|#else
DECL|macro|HAS_KEYB
mdefine_line|#define HAS_KEYB 0
macro_line|#endif
multiline_comment|/* Will / Can the user give input?&n; * Val Henson has requested that Gemini doesn&squot;t wait for the&n; * user to edit the cmdline or not.&n; */
macro_line|#if (defined(CONFIG_SERIAL_8250_CONSOLE) || defined(CONFIG_VGA_CONSOLE)) &bslash;&n;&t;&amp;&amp; !defined(CONFIG_GEMINI)
DECL|macro|INTERACTIVE_CONSOLE
mdefine_line|#define INTERACTIVE_CONSOLE&t;1
macro_line|#endif
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
DECL|variable|cmd_preset
r_char
id|cmd_preset
(braket
)braket
op_assign
id|CMDLINE
suffix:semicolon
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
DECL|variable|keyb_present
r_int
id|keyb_present
op_assign
id|HAS_KEYB
suffix:semicolon
DECL|variable|zimage_size
r_int
id|zimage_size
suffix:semicolon
DECL|variable|com_port
r_int
r_int
id|com_port
suffix:semicolon
DECL|variable|initrd_size
r_int
r_int
id|initrd_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The linker tells us various locations in the image */
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
multiline_comment|/* Original location */
r_extern
r_int
r_int
id|start
suffix:semicolon
r_extern
r_int
id|CRT_tstc
c_func
(paren
r_void
)paren
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
r_void
op_star
id|ignored
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
id|serial_fixups
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Allow get_mem_size to be hooked into.  This is the default. */
r_int
r_int
id|__attribute__
(paren
(paren
id|weak
)paren
)paren
DECL|function|get_mem_size
id|get_mem_size
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_struct
id|bi_record
op_star
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
)paren
(brace
macro_line|#ifdef INTERACTIVE_CONSOLE
r_int
id|timer
op_assign
l_int|0
suffix:semicolon
r_char
id|ch
suffix:semicolon
macro_line|#endif
r_char
op_star
id|cp
suffix:semicolon
r_struct
id|bi_record
op_star
id|rec
suffix:semicolon
r_int
r_int
id|initrd_loc
comma
id|TotalMemory
op_assign
l_int|0
suffix:semicolon
id|serial_fixups
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_8250_CONSOLE
id|com_port
op_assign
id|serial_init
c_func
(paren
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_44x
multiline_comment|/* Reset MAL */
id|mtdcr
c_func
(paren
id|DCRN_MALCR
c_func
(paren
id|DCRN_MAL_BASE
)paren
comma
id|MALCR_MMSR
)paren
suffix:semicolon
multiline_comment|/* Wait for reset */
r_while
c_loop
(paren
id|mfdcr
c_func
(paren
id|DCRN_MALCR
c_func
(paren
id|DCRN_MAL_BASE
)paren
)paren
op_amp
id|MALCR_MMSR
)paren
(brace
)brace
suffix:semicolon
multiline_comment|/* Reset EMAC */
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PPC44x_EMAC0_MR0
op_assign
l_int|0x20000000
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;eieio&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Call get_mem_size(), which is memory controller dependent,&n;&t; * and we must have the correct file linked in here.&n;&t; */
id|TotalMemory
op_assign
id|get_mem_size
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* assume the chunk below 8M is free */
id|end_avail
op_assign
(paren
r_char
op_star
)paren
l_int|0x00800000
suffix:semicolon
multiline_comment|/*&n;&t; * Reveal where we were loaded at and where we&n;&t; * were relocated to.&n;&t; */
id|puts
c_func
(paren
l_string|&quot;loaded at:     &quot;
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
multiline_comment|/*&n;&t; * We link ourself to 0x00800000.  When we run, we relocate&n;&t; * ourselves there.  So we just need __image_begin for the&n;&t; * start. -- Tom&n;&t; */
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
id|avail_ram
op_assign
(paren
r_char
op_star
)paren
l_int|0x00400000
suffix:semicolon
id|end_avail
op_assign
(paren
r_char
op_star
)paren
l_int|0x00800000
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
r_if
c_cond
(paren
id|keyb_present
)paren
id|CRT_tstc
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Forces keyboard to be initialized */
macro_line|#ifdef CONFIG_GEMINI
multiline_comment|/*&n;&t; * If cmd_line is empty and cmd_preset is not, copy cmd_preset&n;&t; * to cmd_line.  This way we can override cmd_preset with the&n;&t; * command line from Smon.&n;&t; */
r_if
c_cond
(paren
(paren
id|cmd_line
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
op_logical_and
(paren
id|cmd_preset
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
)paren
id|memcpy
(paren
id|cmd_line
comma
id|cmd_preset
comma
r_sizeof
(paren
id|cmd_preset
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Display standard Linux/PPC boot prompt for kernel args */
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
id|memcpy
(paren
id|cmd_line
comma
id|cmd_preset
comma
r_sizeof
(paren
id|cmd_preset
)paren
)paren
suffix:semicolon
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
macro_line|#ifdef INTERACTIVE_CONSOLE
multiline_comment|/*&n;&t; * If they have a console, allow them to edit the command line.&n;&t; * Otherwise, don&squot;t bother wasting the five seconds.&n;&t; */
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
multiline_comment|/* Test for backspace/delete */
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
multiline_comment|/* Test for ^x/^u (and wipe the line) */
)brace
r_else
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;&bslash;030&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;&bslash;025&squot;
)paren
(brace
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
macro_line|#endif
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
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
id|puts
c_func
(paren
l_string|&quot;done.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* get the bi_rec address */
id|rec
op_assign
id|bootinfo_addr
c_func
(paren
id|zimage_size
)paren
suffix:semicolon
multiline_comment|/* We need to make sure that the initrd and bi_recs do not&n;&t; * overlap. */
r_if
c_cond
(paren
id|initrd_size
)paren
(brace
r_int
r_int
id|rec_loc
op_assign
(paren
r_int
r_int
)paren
id|rec
suffix:semicolon
id|initrd_loc
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
multiline_comment|/* If the bi_recs are in the middle of the current&n;&t;&t; * initrd, move the initrd to the next MB&n;&t;&t; * boundary. */
r_if
c_cond
(paren
(paren
id|rec_loc
OG
id|initrd_loc
)paren
op_logical_and
(paren
(paren
id|initrd_loc
op_plus
id|initrd_size
)paren
OG
id|rec_loc
)paren
)paren
(brace
id|initrd_loc
op_assign
id|_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|zimage_size
)paren
op_plus
(paren
l_int|2
op_lshift
l_int|20
)paren
op_minus
l_int|1
comma
(paren
l_int|2
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
id|memmove
c_func
(paren
(paren
r_void
op_star
)paren
id|initrd_loc
comma
op_amp
id|__ramdisk_begin
comma
id|initrd_size
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;initrd moved:  &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
id|initrd_loc
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
id|initrd_loc
op_plus
id|initrd_size
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|bootinfo_init
c_func
(paren
id|rec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TotalMemory
)paren
id|bootinfo_append
c_func
(paren
id|BI_MEMSIZE
comma
r_sizeof
(paren
r_int
)paren
comma
(paren
r_void
op_star
)paren
op_amp
id|TotalMemory
)paren
suffix:semicolon
id|bootinfo_append
c_func
(paren
id|BI_CMD_LINE
comma
id|strlen
c_func
(paren
id|cmd_line
)paren
op_plus
l_int|1
comma
(paren
r_void
op_star
)paren
id|cmd_line
)paren
suffix:semicolon
multiline_comment|/* add a bi_rec for the initrd if it exists */
r_if
c_cond
(paren
id|initrd_size
)paren
(brace
r_int
r_int
id|initrd
(braket
l_int|2
)braket
suffix:semicolon
id|initrd
(braket
l_int|0
)braket
op_assign
id|initrd_loc
suffix:semicolon
id|initrd
(braket
l_int|1
)braket
op_assign
id|initrd_size
suffix:semicolon
id|bootinfo_append
c_func
(paren
id|BI_INITRD
comma
r_sizeof
(paren
id|initrd
)paren
comma
op_amp
id|initrd
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
id|rec
suffix:semicolon
)brace
multiline_comment|/* Allow decompress_kernel to be hooked into.  This is the default. */
r_void
op_star
id|__attribute__
(paren
(paren
id|weak
)paren
)paren
DECL|function|load_kernel
id|load_kernel
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
r_void
op_star
id|ign1
comma
r_void
op_star
id|ign2
)paren
(brace
r_return
id|decompress_kernel
c_func
(paren
id|load_addr
comma
id|num_words
comma
id|cksum
)paren
suffix:semicolon
)brace
eof
