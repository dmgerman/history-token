multiline_comment|/*&t;BSDI osd_util.h,v 1.8 1998/06/03 19:14:58 karels Exp&t;*/
multiline_comment|/*&n; * Copyright (c) 1996-1999 Distributed Processing Technology Corporation&n; * All rights reserved.&n; *&n; * Redistribution and use in source form, with or without modification, are&n; * permitted provided that redistributions of source code must retain the&n; * above copyright notice, this list of conditions and the following disclaimer.&n; *&n; * This software is provided `as is&squot; by Distributed Processing Technology and&n; * any express or implied warranties, including, but not limited to, the&n; * implied warranties of merchantability and fitness for a particular purpose,&n; * are disclaimed. In no event shall Distributed Processing Technology be&n; * liable for any direct, indirect, incidental, special, exemplary or&n; * consequential damages (including, but not limited to, procurement of&n; * substitute goods or services; loss of use, data, or profits; or business&n; * interruptions) however caused and on any theory of liability, whether in&n; * contract, strict liability, or tort (including negligence or otherwise)&n; * arising in any way out of the use of this driver software, even if advised&n; * of the possibility of such damage.&n; *&n; */
macro_line|#ifndef         __OSD_UTIL_H
DECL|macro|__OSD_UTIL_H
mdefine_line|#define         __OSD_UTIL_H
multiline_comment|/*File - OSD_UTIL.H&n; ****************************************************************************&n; *&n; *Description:&n; *&n; *      This file contains defines and function prototypes that are&n; *operating system dependent.  The resources defined in this file&n; *are not specific to any particular application.&n; *&n; *Copyright Distributed Processing Technology, Corp.&n; *        140 Candace Dr.&n; *        Maitland, Fl. 32751   USA&n; *        Phone: (407) 830-5522  Fax: (407) 260-5366&n; *        All Rights Reserved&n; *&n; *Author:       Doug Anderson&n; *Date:         1/7/94&n; *&n; *Editors:&n; *&n; *Remarks:&n; *&n; *&n; *****************************************************************************/
multiline_comment|/*Definitions - Defines &amp; Constants ----------------------------------------- */
multiline_comment|/*----------------------------- */
multiline_comment|/* Operating system selections: */
multiline_comment|/*----------------------------- */
multiline_comment|/*#define               _DPT_MSDOS      */
multiline_comment|/*#define               _DPT_WIN_3X     */
multiline_comment|/*#define               _DPT_WIN_4X     */
multiline_comment|/*#define               _DPT_WIN_NT     */
multiline_comment|/*#define               _DPT_NETWARE    */
multiline_comment|/*#define               _DPT_OS2        */
multiline_comment|/*#define               _DPT_SCO        */
multiline_comment|/*#define               _DPT_UNIXWARE   */
multiline_comment|/*#define               _DPT_SOLARIS    */
multiline_comment|/*#define               _DPT_NEXTSTEP   */
multiline_comment|/*#define               _DPT_BANYAN     */
multiline_comment|/*-------------------------------- */
multiline_comment|/* Include the OS specific defines */
multiline_comment|/*-------------------------------- */
multiline_comment|/*#define       OS_SELECTION    From Above List */
multiline_comment|/*#define       SEMAPHORE_T     ??? */
multiline_comment|/*#define       DLL_HANDLE_T    ??? */
macro_line|#if (defined(KERNEL) &amp;&amp; (defined(__FreeBSD__) || defined(__bsdi__)))
macro_line|# include        &quot;i386/isa/dpt_osd_defs.h&quot;
macro_line|#else
macro_line|# include        &quot;osd_defs.h&quot;
macro_line|#endif
macro_line|#ifndef DPT_UNALIGNED
DECL|macro|DPT_UNALIGNED
mdefine_line|#define      DPT_UNALIGNED
macro_line|#endif
macro_line|#ifndef DPT_EXPORT
DECL|macro|DPT_EXPORT
mdefine_line|#define      DPT_EXPORT
macro_line|#endif
macro_line|#ifndef DPT_IMPORT
DECL|macro|DPT_IMPORT
mdefine_line|#define      DPT_IMPORT
macro_line|#endif
macro_line|#ifndef DPT_RUNTIME_IMPORT
DECL|macro|DPT_RUNTIME_IMPORT
mdefine_line|#define      DPT_RUNTIME_IMPORT  DPT_IMPORT
macro_line|#endif
multiline_comment|/*--------------------- */
multiline_comment|/* OS dependent defines */
multiline_comment|/*--------------------- */
macro_line|#if defined (_DPT_MSDOS) || defined (_DPT_WIN_3X)
DECL|macro|_DPT_16_BIT
mdefine_line|#define      _DPT_16_BIT
macro_line|#else
DECL|macro|_DPT_32_BIT
mdefine_line|#define      _DPT_32_BIT
macro_line|#endif
macro_line|#if defined (_DPT_SCO) || defined (_DPT_UNIXWARE) || defined (_DPT_SOLARIS) || defined (_DPT_AIX) || defined (SNI_MIPS) || defined (_DPT_BSDI) || defined (_DPT_FREE_BSD) || defined(_DPT_LINUX)
DECL|macro|_DPT_UNIX
mdefine_line|#define      _DPT_UNIX
macro_line|#endif
macro_line|#if defined (_DPT_WIN_3x) || defined (_DPT_WIN_4X) || defined (_DPT_WIN_NT) &bslash;&n;&t;    || defined (_DPT_OS2)
DECL|macro|_DPT_DLL_SUPPORT
mdefine_line|#define      _DPT_DLL_SUPPORT
macro_line|#endif
macro_line|#if !defined (_DPT_MSDOS) &amp;&amp; !defined (_DPT_WIN_3X) &amp;&amp; !defined (_DPT_NETWARE)
DECL|macro|_DPT_PREEMPTIVE
mdefine_line|#define      _DPT_PREEMPTIVE
macro_line|#endif
macro_line|#if !defined (_DPT_MSDOS) &amp;&amp; !defined (_DPT_WIN_3X)
DECL|macro|_DPT_MULTI_THREADED
mdefine_line|#define      _DPT_MULTI_THREADED
macro_line|#endif
macro_line|#if !defined (_DPT_MSDOS)
DECL|macro|_DPT_MULTI_TASKING
mdefine_line|#define      _DPT_MULTI_TASKING
macro_line|#endif
multiline_comment|/* These exist for platforms that   */
multiline_comment|/* chunk when accessing mis-aligned */
multiline_comment|/* data                             */
macro_line|#if defined (SNI_MIPS) || defined (_DPT_SOLARIS)
macro_line|#if defined (_DPT_BIG_ENDIAN)
macro_line|#if !defined (_DPT_STRICT_ALIGN)
DECL|macro|_DPT_STRICT_ALIGN
mdefine_line|#define _DPT_STRICT_ALIGN
macro_line|#endif
macro_line|#endif
macro_line|#endif
multiline_comment|/* Determine if in C or C++ mode */
macro_line|#ifdef  __cplusplus
DECL|macro|_DPT_CPP
mdefine_line|#define      _DPT_CPP
macro_line|#else
DECL|macro|_DPT_C
mdefine_line|#define      _DPT_C
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------*/
multiline_comment|/* Under Solaris the compiler refuses to accept code like:           */
multiline_comment|/*   { {&quot;DPT&quot;}, 0, NULL .... },                                      */
multiline_comment|/* and complains about the {&quot;DPT&quot;} part by saying &quot;cannot use { }    */
multiline_comment|/* to initialize char*&quot;.                                             */
multiline_comment|/*                                                                   */
multiline_comment|/* By defining these ugly macros we can get around this and also     */
multiline_comment|/* not have to copy and #ifdef large sections of code.  I know that  */
multiline_comment|/* these macros are *really* ugly, but they should help reduce       */
multiline_comment|/* maintenance in the long run.                                      */
multiline_comment|/*                                                                   */
multiline_comment|/*-------------------------------------------------------------------*/
macro_line|#if !defined (DPTSQO)
macro_line|#if defined (_DPT_SOLARIS)
DECL|macro|DPTSQO
mdefine_line|#define DPTSQO
DECL|macro|DPTSQC
mdefine_line|#define DPTSQC
macro_line|#else
DECL|macro|DPTSQO
mdefine_line|#define DPTSQO {
DECL|macro|DPTSQC
mdefine_line|#define DPTSQC }
macro_line|#endif  /* solaris */
macro_line|#endif  /* DPTSQO */
multiline_comment|/*---------------------- */
multiline_comment|/* OS dependent typedefs */
multiline_comment|/*---------------------- */
macro_line|#if defined (_DPT_MSDOS) || defined (_DPT_SCO)
DECL|macro|BYTE
mdefine_line|#define BYTE unsigned char
DECL|macro|WORD
mdefine_line|#define WORD unsigned short
macro_line|#endif
macro_line|#ifndef _DPT_TYPEDEFS
DECL|macro|_DPT_TYPEDEFS
mdefine_line|#define _DPT_TYPEDEFS
DECL|typedef|uCHAR
r_typedef
r_int
r_char
id|uCHAR
suffix:semicolon
DECL|typedef|uSHORT
r_typedef
r_int
r_int
id|uSHORT
suffix:semicolon
DECL|typedef|uINT
r_typedef
r_int
r_int
id|uINT
suffix:semicolon
DECL|typedef|uLONG
r_typedef
r_int
r_int
id|uLONG
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|u8
id|uCHAR
id|u8
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|u16
id|uSHORT
id|u16
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|u32
id|uLONG
id|u32
suffix:semicolon
DECL|typedef|access_U
)brace
id|access_U
suffix:semicolon
macro_line|#endif
macro_line|#if !defined (NULL)
DECL|macro|NULL
mdefine_line|#define      NULL    0
macro_line|#endif
multiline_comment|/*Prototypes - function ----------------------------------------------------- */
macro_line|#ifdef  __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
multiline_comment|/* Declare all these functions as &quot;C&quot; functions */
macro_line|#endif
multiline_comment|/*------------------------ */
multiline_comment|/* Byte reversal functions */
multiline_comment|/*------------------------ */
multiline_comment|/* Reverses the byte ordering of a 2 byte variable */
macro_line|#if (!defined(osdSwap2))
id|uSHORT
id|osdSwap2
c_func
(paren
id|DPT_UNALIGNED
id|uSHORT
op_star
)paren
suffix:semicolon
macro_line|#endif  
singleline_comment|// !osdSwap2
multiline_comment|/* Reverses the byte ordering of a 4 byte variable and shifts left 8 bits */
macro_line|#if (!defined(osdSwap3))
id|uLONG
id|osdSwap3
c_func
(paren
id|DPT_UNALIGNED
id|uLONG
op_star
)paren
suffix:semicolon
macro_line|#endif  
singleline_comment|// !osdSwap3
macro_line|#ifdef  _DPT_NETWARE
macro_line|#include &quot;novpass.h&quot; /* For DPT_Bswapl() prototype */
multiline_comment|/* Inline the byte swap */
macro_line|#ifdef __cplusplus
DECL|function|osdSwap4
r_inline
id|uLONG
id|osdSwap4
c_func
(paren
id|uLONG
op_star
id|inLong
)paren
(brace
r_return
op_star
id|inLong
op_assign
id|DPT_Bswapl
c_func
(paren
op_star
id|inLong
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|osdSwap4
mdefine_line|#define osdSwap4(inLong)       DPT_Bswapl(inLong)
macro_line|#endif  
singleline_comment|// cplusplus
macro_line|#else
multiline_comment|/* Reverses the byte ordering of a 4 byte variable */
macro_line|# if (!defined(osdSwap4))
id|uLONG
id|osdSwap4
c_func
(paren
id|DPT_UNALIGNED
id|uLONG
op_star
)paren
suffix:semicolon
macro_line|# endif  
singleline_comment|// !osdSwap4
multiline_comment|/* The following functions ALWAYS swap regardless of the *&n;   * presence of DPT_BIG_ENDIAN                            */
id|uSHORT
id|trueSwap2
c_func
(paren
id|DPT_UNALIGNED
id|uSHORT
op_star
)paren
suffix:semicolon
id|uLONG
id|trueSwap4
c_func
(paren
id|DPT_UNALIGNED
id|uLONG
op_star
)paren
suffix:semicolon
macro_line|#endif  
singleline_comment|// netware
multiline_comment|/*-------------------------------------*&n; * Network order swap functions        *&n; *                                     *&n; * These functions/macros will be used *&n; * by the structure insert()/extract() *&n; * functions.                          *&n; *&n; * We will enclose all structure       *&n; * portability modifications inside    *&n; * #ifdefs.  When we are ready, we     *&n; * will #define DPT_PORTABLE to begin  *&n; * using the modifications.            *&n; *-------------------------------------*/
id|uLONG
id|netSwap4
c_func
(paren
id|uLONG
id|val
)paren
suffix:semicolon
macro_line|#if defined (_DPT_BIG_ENDIAN)
singleline_comment|// for big-endian we need to swap
macro_line|#ifndef NET_SWAP_2
DECL|macro|NET_SWAP_2
mdefine_line|#define NET_SWAP_2(x) (((x) &gt;&gt; 8) | ((x) &lt;&lt; 8))
macro_line|#endif  
singleline_comment|// NET_SWAP_2
macro_line|#ifndef NET_SWAP_4
DECL|macro|NET_SWAP_4
mdefine_line|#define NET_SWAP_4(x) netSwap4((x))
macro_line|#endif  
singleline_comment|// NET_SWAP_4
macro_line|#else
singleline_comment|// for little-endian we don&squot;t need to do anything
macro_line|#ifndef NET_SWAP_2
DECL|macro|NET_SWAP_2
mdefine_line|#define NET_SWAP_2(x) (x)
macro_line|#endif  
singleline_comment|// NET_SWAP_2
macro_line|#ifndef NET_SWAP_4
DECL|macro|NET_SWAP_4
mdefine_line|#define NET_SWAP_4(x) (x)
macro_line|#endif  
singleline_comment|// NET_SWAP_4
macro_line|#endif  
singleline_comment|// big endian
multiline_comment|/*----------------------------------- */
multiline_comment|/* Run-time loadable module functions */
multiline_comment|/*----------------------------------- */
multiline_comment|/* Loads the specified run-time loadable DLL */
id|DLL_HANDLE_T
id|osdLoadModule
c_func
(paren
id|uCHAR
op_star
)paren
suffix:semicolon
multiline_comment|/* Unloads the specified run-time loadable DLL */
id|uSHORT
id|osdUnloadModule
c_func
(paren
id|DLL_HANDLE_T
)paren
suffix:semicolon
multiline_comment|/* Returns a pointer to a function inside a run-time loadable DLL */
r_void
op_star
id|osdGetFnAddr
c_func
(paren
id|DLL_HANDLE_T
comma
id|uCHAR
op_star
)paren
suffix:semicolon
multiline_comment|/*--------------------------------------- */
multiline_comment|/* Mutually exclusive semaphore functions */
multiline_comment|/*--------------------------------------- */
multiline_comment|/* Create a named semaphore */
id|SEMAPHORE_T
id|osdCreateNamedSemaphore
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* Create a mutually exlusive semaphore */
id|SEMAPHORE_T
id|osdCreateSemaphore
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* create an event semaphore */
id|SEMAPHORE_T
id|osdCreateEventSemaphore
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* create a named event semaphore */
id|SEMAPHORE_T
id|osdCreateNamedEventSemaphore
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* Destroy the specified mutually exclusive semaphore object */
id|uSHORT
id|osdDestroySemaphore
c_func
(paren
id|SEMAPHORE_T
)paren
suffix:semicolon
multiline_comment|/* Request access to the specified mutually exclusive semaphore */
id|uLONG
id|osdRequestSemaphore
c_func
(paren
id|SEMAPHORE_T
comma
id|uLONG
)paren
suffix:semicolon
multiline_comment|/* Release access to the specified mutually exclusive semaphore */
id|uSHORT
id|osdReleaseSemaphore
c_func
(paren
id|SEMAPHORE_T
)paren
suffix:semicolon
multiline_comment|/* wait for a event to happen */
id|uLONG
id|osdWaitForEventSemaphore
c_func
(paren
id|SEMAPHORE_T
comma
id|uLONG
)paren
suffix:semicolon
multiline_comment|/* signal an event */
id|uLONG
id|osdSignalEventSemaphore
c_func
(paren
id|SEMAPHORE_T
)paren
suffix:semicolon
multiline_comment|/* reset the event */
id|uLONG
id|osdResetEventSemaphore
c_func
(paren
id|SEMAPHORE_T
)paren
suffix:semicolon
multiline_comment|/*----------------- */
multiline_comment|/* Thread functions */
multiline_comment|/*----------------- */
multiline_comment|/* Releases control to the task switcher in non-preemptive */
multiline_comment|/* multitasking operating systems. */
r_void
id|osdSwitchThreads
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Starts a thread function */
id|uLONG
id|osdStartThread
c_func
(paren
r_void
op_star
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* what is my thread id */
id|uLONG
id|osdGetThreadID
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* wakes up the specifed thread */
r_void
id|osdWakeThread
c_func
(paren
id|uLONG
)paren
suffix:semicolon
multiline_comment|/* osd sleep for x miliseconds */
r_void
id|osdSleep
c_func
(paren
id|uLONG
)paren
suffix:semicolon
DECL|macro|DPT_THREAD_PRIORITY_LOWEST
mdefine_line|#define DPT_THREAD_PRIORITY_LOWEST 0x00
DECL|macro|DPT_THREAD_PRIORITY_NORMAL
mdefine_line|#define DPT_THREAD_PRIORITY_NORMAL 0x01
DECL|macro|DPT_THREAD_PRIORITY_HIGHEST
mdefine_line|#define DPT_THREAD_PRIORITY_HIGHEST 0x02
id|uCHAR
id|osdSetThreadPriority
c_func
(paren
id|uLONG
id|tid
comma
id|uCHAR
id|priority
)paren
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
multiline_comment|/* end the xtern &quot;C&quot; declaration */
macro_line|#endif
macro_line|#endif  /* osd_util_h */
eof
