multiline_comment|/*&n; * arch/ia64/boot/bootloader.c&n; *&n; * Loads an ELF kernel.&n; *&n; * Copyright (C) 1998-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&t;Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; *&n; * 01/07/99 S.Eranian modified to pass command line arguments to kernel&n; */
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* forward declaration for elf.h */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/pal.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* Simulator system calls: */
DECL|macro|SSC_CONSOLE_INIT
mdefine_line|#define SSC_CONSOLE_INIT&t;&t;20
DECL|macro|SSC_GETCHAR
mdefine_line|#define SSC_GETCHAR&t;&t;&t;21
DECL|macro|SSC_PUTCHAR
mdefine_line|#define SSC_PUTCHAR&t;&t;&t;31
DECL|macro|SSC_OPEN
mdefine_line|#define SSC_OPEN&t;&t;&t;50
DECL|macro|SSC_CLOSE
mdefine_line|#define SSC_CLOSE&t;&t;&t;51
DECL|macro|SSC_READ
mdefine_line|#define SSC_READ&t;&t;&t;52
DECL|macro|SSC_WRITE
mdefine_line|#define SSC_WRITE&t;&t;&t;53
DECL|macro|SSC_GET_COMPLETION
mdefine_line|#define SSC_GET_COMPLETION&t;&t;54
DECL|macro|SSC_WAIT_COMPLETION
mdefine_line|#define SSC_WAIT_COMPLETION&t;&t;55
DECL|macro|SSC_CONNECT_INTERRUPT
mdefine_line|#define SSC_CONNECT_INTERRUPT&t;&t;58
DECL|macro|SSC_GENERATE_INTERRUPT
mdefine_line|#define SSC_GENERATE_INTERRUPT&t;&t;59
DECL|macro|SSC_SET_PERIODIC_INTERRUPT
mdefine_line|#define SSC_SET_PERIODIC_INTERRUPT&t;60
DECL|macro|SSC_GET_RTC
mdefine_line|#define SSC_GET_RTC&t;&t;&t;65
DECL|macro|SSC_EXIT
mdefine_line|#define SSC_EXIT&t;&t;&t;66
DECL|macro|SSC_LOAD_SYMBOLS
mdefine_line|#define SSC_LOAD_SYMBOLS&t;&t;69
DECL|macro|SSC_GET_TOD
mdefine_line|#define SSC_GET_TOD&t;&t;&t;74
DECL|macro|SSC_GET_ARGS
mdefine_line|#define SSC_GET_ARGS&t;&t;&t;75
DECL|struct|disk_req
r_struct
id|disk_req
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|disk_stat
r_struct
id|disk_stat
(brace
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
macro_line|#include &quot;../kernel/fw-emu.c&quot;
multiline_comment|/* This needs to be defined because lib/string.c:strlcat() calls it in case of error... */
id|asm
(paren
l_string|&quot;.global printk; printk = 0&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Set a break point on this function so that symbols are available to set breakpoints in&n; * the kernel being debugged.&n; */
r_static
r_void
DECL|function|debug_break
id|debug_break
(paren
r_void
)paren
(brace
)brace
r_static
r_void
DECL|function|cons_write
id|cons_write
(paren
r_const
r_char
op_star
id|buf
)paren
(brace
r_int
r_int
id|ch
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|buf
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|ssc
c_func
(paren
id|ch
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_PUTCHAR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|ssc
c_func
(paren
l_char|&squot;&bslash;r&squot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_PUTCHAR
)paren
suffix:semicolon
)brace
)brace
DECL|macro|MAX_ARGS
mdefine_line|#define MAX_ARGS 32
r_void
DECL|function|_start
id|_start
(paren
r_void
)paren
(brace
r_static
r_char
id|stack
(braket
l_int|16384
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
r_static
r_char
id|mem
(braket
l_int|4096
)braket
suffix:semicolon
r_static
r_char
id|buffer
(braket
l_int|1024
)braket
suffix:semicolon
r_int
r_int
id|off
suffix:semicolon
r_int
id|fd
comma
id|i
suffix:semicolon
r_struct
id|disk_req
id|req
suffix:semicolon
r_struct
id|disk_stat
id|stat
suffix:semicolon
r_struct
id|elfhdr
op_star
id|elf
suffix:semicolon
r_struct
id|elf_phdr
op_star
id|elf_phdr
suffix:semicolon
multiline_comment|/* program header */
r_int
r_int
id|e_entry
comma
id|e_phoff
comma
id|e_phnum
suffix:semicolon
r_register
r_struct
id|ia64_boot_param
op_star
id|bp
suffix:semicolon
r_char
op_star
id|kpath
comma
op_star
id|args
suffix:semicolon
r_int
id|arglen
op_assign
l_int|0
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl gp=__gp;;&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mov sp=%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|stack
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;bsw.1;;&quot;
)paren
suffix:semicolon
id|ssc
c_func
(paren
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_CONSOLE_INIT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * S.Eranian: extract the commandline argument from the simulator&n;&t; *&n;&t; * The expected format is as follows:&n;         *&n;&t; *&t;kernelname args...&n;&t; *&n;&t; * Both are optional but you can&squot;t have the second one without the first.&n;&t; */
id|arglen
op_assign
id|ssc
c_func
(paren
(paren
r_int
)paren
id|buffer
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_GET_ARGS
)paren
suffix:semicolon
id|kpath
op_assign
l_string|&quot;vmlinux&quot;
suffix:semicolon
id|args
op_assign
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|arglen
OG
l_int|0
)paren
(brace
id|kpath
op_assign
id|buffer
suffix:semicolon
r_while
c_loop
(paren
op_star
id|args
op_ne
l_char|&squot; &squot;
op_logical_and
op_star
id|args
op_ne
l_char|&squot;&bslash;0&squot;
)paren
op_increment
id|args
comma
op_decrement
id|arglen
suffix:semicolon
r_if
c_cond
(paren
op_star
id|args
op_eq
l_char|&squot; &squot;
)paren
op_star
id|args
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
comma
op_decrement
id|arglen
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arglen
op_le
l_int|0
)paren
(brace
id|args
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|arglen
op_assign
l_int|1
suffix:semicolon
)brace
id|fd
op_assign
id|ssc
c_func
(paren
(paren
r_int
)paren
id|kpath
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
id|SSC_OPEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|cons_write
c_func
(paren
id|kpath
)paren
suffix:semicolon
id|cons_write
c_func
(paren
l_string|&quot;: file not found, reboot now&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
)brace
id|stat.fd
op_assign
id|fd
suffix:semicolon
id|off
op_assign
l_int|0
suffix:semicolon
id|req.len
op_assign
r_sizeof
(paren
id|mem
)paren
suffix:semicolon
id|req.addr
op_assign
(paren
r_int
)paren
id|mem
suffix:semicolon
id|ssc
c_func
(paren
id|fd
comma
l_int|1
comma
(paren
r_int
)paren
op_amp
id|req
comma
id|off
comma
id|SSC_READ
)paren
suffix:semicolon
id|ssc
c_func
(paren
(paren
r_int
)paren
op_amp
id|stat
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_WAIT_COMPLETION
)paren
suffix:semicolon
id|elf
op_assign
(paren
r_struct
id|elfhdr
op_star
)paren
id|mem
suffix:semicolon
r_if
c_cond
(paren
id|elf-&gt;e_ident
(braket
l_int|0
)braket
op_eq
l_int|0x7f
op_logical_and
id|strncmp
c_func
(paren
id|elf-&gt;e_ident
op_plus
l_int|1
comma
l_string|&quot;ELF&quot;
comma
l_int|3
)paren
op_ne
l_int|0
)paren
(brace
id|cons_write
c_func
(paren
l_string|&quot;not an ELF file&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|elf-&gt;e_type
op_ne
id|ET_EXEC
)paren
(brace
id|cons_write
c_func
(paren
l_string|&quot;not an ELF executable&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|elf_check_arch
c_func
(paren
id|elf
)paren
)paren
(brace
id|cons_write
c_func
(paren
l_string|&quot;kernel not for this processor&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|e_entry
op_assign
id|elf-&gt;e_entry
suffix:semicolon
id|e_phnum
op_assign
id|elf-&gt;e_phnum
suffix:semicolon
id|e_phoff
op_assign
id|elf-&gt;e_phoff
suffix:semicolon
id|cons_write
c_func
(paren
l_string|&quot;loading &quot;
)paren
suffix:semicolon
id|cons_write
c_func
(paren
id|kpath
)paren
suffix:semicolon
id|cons_write
c_func
(paren
l_string|&quot;...&bslash;n&quot;
)paren
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
id|e_phnum
suffix:semicolon
op_increment
id|i
)paren
(brace
id|req.len
op_assign
r_sizeof
(paren
op_star
id|elf_phdr
)paren
suffix:semicolon
id|req.addr
op_assign
(paren
r_int
)paren
id|mem
suffix:semicolon
id|ssc
c_func
(paren
id|fd
comma
l_int|1
comma
(paren
r_int
)paren
op_amp
id|req
comma
id|e_phoff
comma
id|SSC_READ
)paren
suffix:semicolon
id|ssc
c_func
(paren
(paren
r_int
)paren
op_amp
id|stat
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_WAIT_COMPLETION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat.count
op_ne
r_sizeof
(paren
op_star
id|elf_phdr
)paren
)paren
(brace
id|cons_write
c_func
(paren
l_string|&quot;failed to read phdr&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|e_phoff
op_add_assign
r_sizeof
(paren
op_star
id|elf_phdr
)paren
suffix:semicolon
id|elf_phdr
op_assign
(paren
r_struct
id|elf_phdr
op_star
)paren
id|mem
suffix:semicolon
r_if
c_cond
(paren
id|elf_phdr-&gt;p_type
op_ne
id|PT_LOAD
)paren
r_continue
suffix:semicolon
id|req.len
op_assign
id|elf_phdr-&gt;p_filesz
suffix:semicolon
id|req.addr
op_assign
id|__pa
c_func
(paren
id|elf_phdr-&gt;p_paddr
)paren
suffix:semicolon
id|ssc
c_func
(paren
id|fd
comma
l_int|1
comma
(paren
r_int
)paren
op_amp
id|req
comma
id|elf_phdr-&gt;p_offset
comma
id|SSC_READ
)paren
suffix:semicolon
id|ssc
c_func
(paren
(paren
r_int
)paren
op_amp
id|stat
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_WAIT_COMPLETION
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|__pa
c_func
(paren
id|elf_phdr-&gt;p_paddr
)paren
op_plus
id|elf_phdr-&gt;p_filesz
comma
l_int|0
comma
id|elf_phdr-&gt;p_memsz
op_minus
id|elf_phdr-&gt;p_filesz
)paren
suffix:semicolon
)brace
id|ssc
c_func
(paren
id|fd
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_CLOSE
)paren
suffix:semicolon
id|cons_write
c_func
(paren
l_string|&quot;starting kernel...&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* fake an I/O base address: */
id|asm
r_volatile
(paren
l_string|&quot;mov ar.k0=%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
l_int|0xffffc000000UL
)paren
)paren
suffix:semicolon
id|bp
op_assign
id|sys_fw_init
c_func
(paren
id|args
comma
id|arglen
)paren
suffix:semicolon
id|ssc
c_func
(paren
l_int|0
comma
(paren
r_int
)paren
id|kpath
comma
l_int|0
comma
l_int|0
comma
id|SSC_LOAD_SYMBOLS
)paren
suffix:semicolon
id|debug_break
c_func
(paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mov sp=%2; mov r28=%1; br.sptk.few %0&quot;
op_scope_resolution
l_string|&quot;b&quot;
(paren
id|e_entry
)paren
comma
l_string|&quot;r&quot;
(paren
id|bp
)paren
comma
l_string|&quot;r&quot;
(paren
id|__pa
c_func
(paren
op_amp
id|stack
)paren
)paren
)paren
suffix:semicolon
id|cons_write
c_func
(paren
l_string|&quot;kernel returned!&bslash;n&quot;
)paren
suffix:semicolon
id|ssc
c_func
(paren
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_EXIT
)paren
suffix:semicolon
)brace
eof
