multiline_comment|/*&n; * init.c: PROM library initialisation code.&n; *&n; * Copyright (C) 1998 Harald Koerfgen&n; * Copyright (C) 2002  Maciej W. Rozycki&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/dec/prom.h&gt;
DECL|variable|__rex_bootinit
r_int
(paren
op_star
id|__rex_bootinit
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__rex_bootread
r_int
(paren
op_star
id|__rex_bootread
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__rex_getbitmap
r_int
(paren
op_star
id|__rex_getbitmap
)paren
(paren
id|memmap
op_star
)paren
suffix:semicolon
DECL|variable|__rex_slot_address
r_int
r_int
op_star
(paren
op_star
id|__rex_slot_address
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|variable|__rex_gettcinfo
r_void
op_star
(paren
op_star
id|__rex_gettcinfo
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__rex_getsysid
r_int
(paren
op_star
id|__rex_getsysid
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__rex_clear_cache
r_void
(paren
op_star
id|__rex_clear_cache
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__prom_getchar
r_int
(paren
op_star
id|__prom_getchar
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__prom_getenv
r_char
op_star
(paren
op_star
id|__prom_getenv
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|variable|__prom_printf
r_int
(paren
op_star
id|__prom_printf
)paren
(paren
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|variable|__pmax_open
r_int
(paren
op_star
id|__pmax_open
)paren
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|__pmax_lseek
r_int
(paren
op_star
id|__pmax_lseek
)paren
(paren
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|variable|__pmax_read
r_int
(paren
op_star
id|__pmax_read
)paren
(paren
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|__pmax_close
r_int
(paren
op_star
id|__pmax_close
)paren
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Detect which PROM&squot;s the DECSTATION has, and set the callback vectors&n; * appropriately.&n; */
DECL|function|which_prom
r_void
id|__init
id|which_prom
c_func
(paren
id|s32
id|magic
comma
id|s32
op_star
id|prom_vec
)paren
(brace
multiline_comment|/*&n;&t; * No sign of the REX PROM&squot;s magic number means we assume a non-REX&n;&t; * machine (i.e. we&squot;re on a DS2100/3100, DS5100 or DS5000/2xx)&n;&t; */
r_if
c_cond
(paren
id|prom_is_rex
c_func
(paren
id|magic
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Set up prom abstraction structure with REX entry points.&n;&t;&t; */
id|__rex_bootinit
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
op_star
(paren
id|prom_vec
op_plus
id|REX_PROM_BOOTINIT
)paren
suffix:semicolon
id|__rex_bootread
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
op_star
(paren
id|prom_vec
op_plus
id|REX_PROM_BOOTREAD
)paren
suffix:semicolon
id|__rex_getbitmap
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
op_star
(paren
id|prom_vec
op_plus
id|REX_PROM_GETBITMAP
)paren
suffix:semicolon
id|__prom_getchar
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
op_star
(paren
id|prom_vec
op_plus
id|REX_PROM_GETCHAR
)paren
suffix:semicolon
id|__prom_getenv
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
op_star
(paren
id|prom_vec
op_plus
id|REX_PROM_GETENV
)paren
suffix:semicolon
id|__rex_getsysid
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
op_star
(paren
id|prom_vec
op_plus
id|REX_PROM_GETSYSID
)paren
suffix:semicolon
id|__rex_gettcinfo
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
op_star
(paren
id|prom_vec
op_plus
id|REX_PROM_GETTCINFO
)paren
suffix:semicolon
id|__prom_printf
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
op_star
(paren
id|prom_vec
op_plus
id|REX_PROM_PRINTF
)paren
suffix:semicolon
id|__rex_slot_address
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
op_star
(paren
id|prom_vec
op_plus
id|REX_PROM_SLOTADDR
)paren
suffix:semicolon
id|__rex_clear_cache
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
op_star
(paren
id|prom_vec
op_plus
id|REX_PROM_CLEARCACHE
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Set up prom abstraction structure with non-REX entry points.&n;&t;&t; */
id|__prom_getchar
op_assign
(paren
r_void
op_star
)paren
id|PMAX_PROM_GETCHAR
suffix:semicolon
id|__prom_getenv
op_assign
(paren
r_void
op_star
)paren
id|PMAX_PROM_GETENV
suffix:semicolon
id|__prom_printf
op_assign
(paren
r_void
op_star
)paren
id|PMAX_PROM_PRINTF
suffix:semicolon
id|__pmax_open
op_assign
(paren
r_void
op_star
)paren
id|PMAX_PROM_OPEN
suffix:semicolon
id|__pmax_lseek
op_assign
(paren
r_void
op_star
)paren
id|PMAX_PROM_LSEEK
suffix:semicolon
id|__pmax_read
op_assign
(paren
r_void
op_star
)paren
id|PMAX_PROM_READ
suffix:semicolon
id|__pmax_close
op_assign
(paren
r_void
op_star
)paren
id|PMAX_PROM_CLOSE
suffix:semicolon
)brace
)brace
DECL|function|prom_init
r_int
id|__init
id|prom_init
c_func
(paren
id|s32
id|argc
comma
id|s32
op_star
id|argv
comma
id|u32
id|magic
comma
id|s32
op_star
id|prom_vec
)paren
(brace
r_extern
r_void
id|dec_machine_halt
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Determine which PROM&squot;s we have&n;&t; * (and therefore which machine we&squot;re on!)&n;&t; */
id|which_prom
c_func
(paren
id|magic
comma
id|prom_vec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prom_is_rex
c_func
(paren
id|magic
)paren
)paren
id|rex_clear_cache
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Were we compiled with the right CPU option? */
macro_line|#if defined(CONFIG_CPU_R3000)
r_if
c_cond
(paren
(paren
id|current_cpu_data.cputype
op_eq
id|CPU_R4000SC
)paren
op_logical_or
(paren
id|current_cpu_data.cputype
op_eq
id|CPU_R4400SC
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Sorry, this kernel is compiled for the wrong CPU type!&bslash;n&quot;
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;Please recompile with &bslash;&quot;CONFIG_CPU_R4x00 = y&bslash;&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|dec_machine_halt
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_R4X00)
r_if
c_cond
(paren
(paren
id|current_cpu_data.cputype
op_eq
id|CPU_R3000
)paren
op_logical_or
(paren
id|current_cpu_data.cputype
op_eq
id|CPU_R3000A
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Sorry, this kernel is compiled for the wrong CPU type!&bslash;n&quot;
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;Please recompile with &bslash;&quot;CONFIG_CPU_R3000 = y&bslash;&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|dec_machine_halt
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|prom_meminit
c_func
(paren
id|magic
)paren
suffix:semicolon
id|prom_identify_arch
c_func
(paren
id|magic
)paren
suffix:semicolon
id|prom_init_cmdline
c_func
(paren
id|argc
comma
id|argv
comma
id|magic
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
