multiline_comment|/******************************************************************************&n; *&n; * Name: acenv.h - Generation environment specific items&n; *       $Revision: 77 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACENV_H__
DECL|macro|__ACENV_H__
mdefine_line|#define __ACENV_H__
multiline_comment|/*&n; * Configuration for ACPI tools and utilities&n; */
macro_line|#ifdef _ACPI_DUMP_APP
DECL|macro|ACPI_DEBUG
mdefine_line|#define ACPI_DEBUG
DECL|macro|ACPI_APPLICATION
mdefine_line|#define ACPI_APPLICATION
DECL|macro|ENABLE_DEBUGGER
mdefine_line|#define ENABLE_DEBUGGER
DECL|macro|ACPI_USE_SYSTEM_CLIBRARY
mdefine_line|#define ACPI_USE_SYSTEM_CLIBRARY
DECL|macro|PARSER_ONLY
mdefine_line|#define PARSER_ONLY
macro_line|#endif
macro_line|#ifdef _ACPI_EXEC_APP
DECL|macro|DEBUGGER_THREADING
macro_line|#undef DEBUGGER_THREADING
DECL|macro|DEBUGGER_THREADING
mdefine_line|#define DEBUGGER_THREADING      DEBUGGER_SINGLE_THREADED
DECL|macro|ACPI_DEBUG
mdefine_line|#define ACPI_DEBUG
DECL|macro|ACPI_APPLICATION
mdefine_line|#define ACPI_APPLICATION
DECL|macro|ENABLE_DEBUGGER
mdefine_line|#define ENABLE_DEBUGGER
DECL|macro|ACPI_USE_SYSTEM_CLIBRARY
mdefine_line|#define ACPI_USE_SYSTEM_CLIBRARY
macro_line|#endif
macro_line|#ifdef _ACPI_ASL_COMPILER
DECL|macro|ACPI_DEBUG
mdefine_line|#define ACPI_DEBUG
DECL|macro|ACPI_APPLICATION
mdefine_line|#define ACPI_APPLICATION
DECL|macro|ENABLE_DEBUGGER
mdefine_line|#define ENABLE_DEBUGGER
DECL|macro|ACPI_USE_SYSTEM_CLIBRARY
mdefine_line|#define ACPI_USE_SYSTEM_CLIBRARY
macro_line|#endif
multiline_comment|/*&n; * Memory allocation tracking.  Used only if&n; * 1) This is the debug version&n; * 2) This is NOT a 16-bit version of the code (not enough real-mode memory)&n; */
macro_line|#ifdef ACPI_DEBUG
macro_line|#ifndef _IA16
DECL|macro|ACPI_DBG_TRACK_ALLOCATIONS
mdefine_line|#define ACPI_DBG_TRACK_ALLOCATIONS
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Environment configuration.  The purpose of this file is to interface to the&n; * local generation environment.&n; *&n; * 1) ACPI_USE_SYSTEM_CLIBRARY - Define this if linking to an actual C library.&n; *      Otherwise, local versions of string/memory functions will be used.&n; * 2) ACPI_USE_STANDARD_HEADERS - Define this if linking to a C library and&n; *      the standard header files may be used.&n; *&n; * The ACPI subsystem only uses low level C library functions that do not call&n; * operating system services and may therefore be inlined in the code.&n; *&n; * It may be necessary to tailor these include files to the target&n; * generation environment.&n; *&n; *&n; * Functions and constants used from each header:&n; *&n; * string.h:    memcpy&n; *              memset&n; *              strcat&n; *              strcmp&n; *              strcpy&n; *              strlen&n; *              strncmp&n; *              strncat&n; *              strncpy&n; *&n; * stdlib.h:    strtoul&n; *&n; * stdarg.h:    va_list&n; *              va_arg&n; *              va_start&n; *              va_end&n; *&n; */
multiline_comment|/*! [Begin] no source code translation */
macro_line|#ifdef _LINUX
macro_line|#include &quot;aclinux.h&quot;
macro_line|#elif _AED_EFI
macro_line|#include &quot;acefi.h&quot;
macro_line|#elif WIN32
macro_line|#include &quot;acwin.h&quot;
macro_line|#elif __FreeBSD__
macro_line|#include &quot;acfreebsd.h&quot;
macro_line|#else
multiline_comment|/* All other environments */
DECL|macro|ACPI_USE_STANDARD_HEADERS
mdefine_line|#define ACPI_USE_STANDARD_HEADERS
multiline_comment|/* Name of host operating system (returned by the _OS_ namespace object) */
DECL|macro|ACPI_OS_NAME
mdefine_line|#define ACPI_OS_NAME         &quot;Intel ACPI/CA Core Subsystem&quot;
multiline_comment|/* This macro is used to tag functions as &quot;printf-like&quot; because&n; * some compilers can catch printf format string problems. MSVC&n; * doesn&squot;t, so this is proprocessed away.&n; */
DECL|macro|ACPI_PRINTF_LIKE_FUNC
mdefine_line|#define ACPI_PRINTF_LIKE_FUNC
macro_line|#endif
multiline_comment|/*! [End] no source code translation !*/
multiline_comment|/******************************************************************************&n; *&n; * C library configuration&n; *&n; *****************************************************************************/
macro_line|#ifdef ACPI_USE_SYSTEM_CLIBRARY
multiline_comment|/*&n; * Use the standard C library headers.&n; * We want to keep these to a minimum.&n; *&n; */
macro_line|#ifdef ACPI_USE_STANDARD_HEADERS
multiline_comment|/*&n; * Use the standard headers from the standard locations&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;ctype.h&gt;
macro_line|#endif /* ACPI_USE_STANDARD_HEADERS */
multiline_comment|/*&n; * We will be linking to the standard Clib functions&n; */
DECL|macro|STRSTR
mdefine_line|#define STRSTR(s1,s2)   strstr((s1), (s2))
DECL|macro|STRUPR
mdefine_line|#define STRUPR(s)       acpi_ut_strupr ((s))
DECL|macro|STRLEN
mdefine_line|#define STRLEN(s)       (u32) strlen((s))
DECL|macro|STRCPY
mdefine_line|#define STRCPY(d,s)     strcpy((d), (s))
DECL|macro|STRNCPY
mdefine_line|#define STRNCPY(d,s,n)  strncpy((d), (s), (NATIVE_INT)(n))
DECL|macro|STRNCMP
mdefine_line|#define STRNCMP(d,s,n)  strncmp((d), (s), (NATIVE_INT)(n))
DECL|macro|STRCMP
mdefine_line|#define STRCMP(d,s)     strcmp((d), (s))
DECL|macro|STRCAT
mdefine_line|#define STRCAT(d,s)     strcat((d), (s))
DECL|macro|STRNCAT
mdefine_line|#define STRNCAT(d,s,n)  strncat((d), (s), (NATIVE_INT)(n))
DECL|macro|STRTOUL
mdefine_line|#define STRTOUL(d,s,n)  strtoul((d), (s), (NATIVE_INT)(n))
DECL|macro|MEMCPY
mdefine_line|#define MEMCPY(d,s,n)   memcpy((d), (s), (NATIVE_INT)(n))
DECL|macro|MEMSET
mdefine_line|#define MEMSET(d,s,n)   memset((d), (s), (NATIVE_INT)(n))
DECL|macro|TOUPPER
mdefine_line|#define TOUPPER         toupper
DECL|macro|TOLOWER
mdefine_line|#define TOLOWER         tolower
DECL|macro|IS_XDIGIT
mdefine_line|#define IS_XDIGIT       isxdigit
multiline_comment|/******************************************************************************&n; *&n; * Not using native C library, use local implementations&n; *&n; *****************************************************************************/
macro_line|#else
multiline_comment|/*&n; * Use local definitions of C library macros and functions&n; * NOTE: The function implementations may not be as efficient&n; * as an inline or assembly code implementation provided by a&n; * native C library.&n; */
macro_line|#ifndef va_arg
macro_line|#ifndef _VALIST
DECL|macro|_VALIST
mdefine_line|#define _VALIST
DECL|typedef|va_list
r_typedef
r_char
op_star
id|va_list
suffix:semicolon
macro_line|#endif /* _VALIST */
multiline_comment|/*&n; * Storage alignment properties&n; */
DECL|macro|_AUPBND
mdefine_line|#define  _AUPBND         (sizeof (NATIVE_INT) - 1)
DECL|macro|_ADNBND
mdefine_line|#define  _ADNBND         (sizeof (NATIVE_INT) - 1)
multiline_comment|/*&n; * Variable argument list macro definitions&n; */
DECL|macro|_bnd
mdefine_line|#define _bnd(X, bnd)    (((sizeof (X)) + (bnd)) &amp; (~(bnd)))
DECL|macro|va_arg
mdefine_line|#define va_arg(ap, T)   (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND))))
DECL|macro|va_end
mdefine_line|#define va_end(ap)      (void) 0
DECL|macro|va_start
mdefine_line|#define va_start(ap, A) (void) ((ap) = (((char *) &amp;(A)) + (_bnd (A,_AUPBND))))
macro_line|#endif /* va_arg */
DECL|macro|STRSTR
mdefine_line|#define STRSTR(s1,s2)    acpi_ut_strstr ((s1), (s2))
DECL|macro|STRUPR
mdefine_line|#define STRUPR(s)        acpi_ut_strupr ((s))
DECL|macro|STRLEN
mdefine_line|#define STRLEN(s)        acpi_ut_strlen ((s))
DECL|macro|STRCPY
mdefine_line|#define STRCPY(d,s)      acpi_ut_strcpy ((d), (s))
DECL|macro|STRNCPY
mdefine_line|#define STRNCPY(d,s,n)   acpi_ut_strncpy ((d), (s), (n))
DECL|macro|STRNCMP
mdefine_line|#define STRNCMP(d,s,n)   acpi_ut_strncmp ((d), (s), (n))
DECL|macro|STRCMP
mdefine_line|#define STRCMP(d,s)      acpi_ut_strcmp ((d), (s))
DECL|macro|STRCAT
mdefine_line|#define STRCAT(d,s)      acpi_ut_strcat ((d), (s))
DECL|macro|STRNCAT
mdefine_line|#define STRNCAT(d,s,n)   acpi_ut_strncat ((d), (s), (n))
DECL|macro|STRTOUL
mdefine_line|#define STRTOUL(d,s,n)   acpi_ut_strtoul ((d), (s),(n))
DECL|macro|MEMCPY
mdefine_line|#define MEMCPY(d,s,n)    acpi_ut_memcpy ((d), (s), (n))
DECL|macro|MEMSET
mdefine_line|#define MEMSET(d,v,n)    acpi_ut_memset ((d), (v), (n))
DECL|macro|TOUPPER
mdefine_line|#define TOUPPER          acpi_ut_to_upper
DECL|macro|TOLOWER
mdefine_line|#define TOLOWER          acpi_ut_to_lower
macro_line|#endif /* ACPI_USE_SYSTEM_CLIBRARY */
multiline_comment|/******************************************************************************&n; *&n; * Assembly code macros&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Handle platform- and compiler-specific assembly language differences.&n; * These should already have been defined by the platform includes above.&n; *&n; * Notes:&n; * 1) Interrupt 3 is used to break into a debugger&n; * 2) Interrupts are turned off during ACPI register setup&n; */
multiline_comment|/* Unrecognized compiler, use defaults */
macro_line|#ifndef ACPI_ASM_MACROS
DECL|macro|ACPI_ASM_MACROS
mdefine_line|#define ACPI_ASM_MACROS
DECL|macro|causeinterrupt
mdefine_line|#define causeinterrupt(level)
DECL|macro|BREAKPOINT3
mdefine_line|#define BREAKPOINT3
DECL|macro|disable
mdefine_line|#define disable()
DECL|macro|enable
mdefine_line|#define enable()
DECL|macro|halt
mdefine_line|#define halt()
DECL|macro|ACPI_ACQUIRE_GLOBAL_LOCK
mdefine_line|#define ACPI_ACQUIRE_GLOBAL_LOCK(Glptr, acq)
DECL|macro|ACPI_RELEASE_GLOBAL_LOCK
mdefine_line|#define ACPI_RELEASE_GLOBAL_LOCK(Glptr, acq)
macro_line|#endif /* ACPI_ASM_MACROS */
macro_line|#ifdef ACPI_APPLICATION
multiline_comment|/* Don&squot;t want software interrupts within a ring3 application */
DECL|macro|causeinterrupt
macro_line|#undef causeinterrupt
DECL|macro|BREAKPOINT3
macro_line|#undef BREAKPOINT3
DECL|macro|causeinterrupt
mdefine_line|#define causeinterrupt(level)
DECL|macro|BREAKPOINT3
mdefine_line|#define BREAKPOINT3
macro_line|#endif
multiline_comment|/******************************************************************************&n; *&n; * Compiler-specific&n; *&n; *****************************************************************************/
multiline_comment|/* this has been moved to compiler-specific headers, which are included from the&n;   platform header. */
macro_line|#endif /* __ACENV_H__ */
eof
