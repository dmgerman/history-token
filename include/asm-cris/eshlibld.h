multiline_comment|/*!**************************************************************************&n;*!&n;*! FILE NAME  : eshlibld.h&n;*!&n;*! DESCRIPTION: Prototypes for exported shared library functions&n;*!&n;*! FUNCTIONS  : perform_cris_aout_relocations, shlibmod_fork, shlibmod_exit&n;*! (EXPORTED)&n;*!&n;*!---------------------------------------------------------------------------&n;*!&n;*! (C) Copyright 1998, 1999 Axis Communications AB, LUND, SWEDEN&n;*!&n;*!**************************************************************************/
multiline_comment|/* $Id: eshlibld.h,v 1.1 2000/07/10 16:32:31 bjornw Exp $ */
macro_line|#ifndef _cris_relocate_h
DECL|macro|_cris_relocate_h
mdefine_line|#define _cris_relocate_h
multiline_comment|/* Please note that this file is also compiled into the xsim simulator.&n;   Try to avoid breaking its double use (only works on a little-endian&n;   32-bit machine such as the i386 anyway).&n;&n;   Use __KERNEL__ when you&squot;re about to use kernel functions,&n;       (which you should not do here anyway, since this file is&n;       used by glibc).&n;   Use defined(__KERNEL__) || defined(__elinux__) when doing&n;       things that only makes sense on an elinux system.&n;   Use __CRIS__ when you&squot;re about to do (really) CRIS-specific code.&n;*/
multiline_comment|/* We have dependencies all over the place for the host system&n;   for xsim being a linux system, so let&squot;s not pretend anything&n;   else with #ifdef:s here until fixed.  */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/limits.h&gt;
multiline_comment|/* Maybe do sanity checking if file input. */
DECL|macro|SANITYCHECK_RELOC
macro_line|#undef SANITYCHECK_RELOC
multiline_comment|/* Maybe output debug messages. */
DECL|macro|RELOC_DEBUG
macro_line|#undef RELOC_DEBUG
multiline_comment|/* Maybe we want to share core as well as disk space.&n;   Mainly depends on the config macro CONFIG_SHARE_SHLIB_CORE, but it is&n;   assumed that we want to share code when debugging (exposes more&n;   trouble). */
macro_line|#ifndef SHARE_LIB_CORE
macro_line|# if (defined(__KERNEL__) || !defined(RELOC_DEBUG)) &bslash;&n;     &amp;&amp; !defined(CONFIG_SHARE_SHLIB_CORE)
DECL|macro|SHARE_LIB_CORE
macro_line|#  define SHARE_LIB_CORE 0
macro_line|# else
DECL|macro|SHARE_LIB_CORE
macro_line|#  define SHARE_LIB_CORE 1
macro_line|# endif /* __KERNEL__ etc */
macro_line|#endif /* SHARE_LIB_CORE */
multiline_comment|/* Main exported function; supposed to be called when the program a.out&n;   has been read in. */
r_extern
r_int
id|perform_cris_aout_relocations
c_func
(paren
r_int
r_int
id|text
comma
r_int
r_int
id|tlength
comma
r_int
r_int
id|data
comma
r_int
r_int
id|dlength
comma
r_int
r_int
id|baddr
comma
r_int
r_int
id|blength
comma
multiline_comment|/* These may be zero when there&squot;s &quot;perfect&quot;&n;&t;&t;&t;&t; position-independent code. */
r_int
r_char
op_star
id|trel
comma
r_int
r_int
id|tsrel
comma
r_int
r_int
id|dsrel
comma
multiline_comment|/* These will be zero at a first try, to see&n;&t;&t;&t;&t; if code is statically linked.  Else a&n;&t;&t;&t;&t; second try, with the symbol table and&n;&t;&t;&t;&t; string table nonzero should be done. */
r_int
r_char
op_star
id|symbols
comma
r_int
r_int
id|symlength
comma
r_int
r_char
op_star
id|strings
comma
r_int
r_int
id|stringlength
comma
multiline_comment|/* These will only be used when symbol table&n;&t;&t;&t;       information is present. */
r_char
op_star
op_star
id|env
comma
r_int
id|envc
comma
r_int
id|euid
comma
r_int
id|is_suid
)paren
suffix:semicolon
macro_line|#ifdef RELOC_DEBUG
multiline_comment|/* Task-specific debug stuff. */
DECL|struct|task_reloc_debug
r_struct
id|task_reloc_debug
(brace
DECL|member|alloclast
r_struct
id|memdebug
op_star
id|alloclast
suffix:semicolon
DECL|member|alloc_total
r_int
r_int
id|alloc_total
suffix:semicolon
DECL|member|export_total
r_int
r_int
id|export_total
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* RELOC_DEBUG */
macro_line|#if SHARE_LIB_CORE
multiline_comment|/* When code (and some very specific data) is shared and not just&n;   dynamically linked, we need to export hooks for exec beginning and&n;   end. */
r_struct
id|shlibdep
suffix:semicolon
r_extern
r_void
id|shlibmod_exit
c_func
(paren
r_struct
id|shlibdep
op_star
op_star
id|deps
)paren
suffix:semicolon
multiline_comment|/* Returns 0 if failure, nonzero for ok. */
r_extern
r_int
id|shlibmod_fork
c_func
(paren
r_struct
id|shlibdep
op_star
op_star
id|deps
)paren
suffix:semicolon
macro_line|#else  /* ! SHARE_LIB_CORE */
DECL|macro|shlibmod_exit
macro_line|# define shlibmod_exit(x)
DECL|macro|shlibmod_fork
macro_line|# define shlibmod_fork(x) 1
macro_line|#endif /* ! SHARE_LIB_CORE */
macro_line|#endif _cris_relocate_h
multiline_comment|/********************** END OF FILE eshlibld.h *****************************/
eof
