multiline_comment|/*&t;BSDI osd_defs.h,v 1.4 1998/06/03 19:14:58 karels Exp&t;*/
multiline_comment|/*&n; * Copyright (c) 1996-1999 Distributed Processing Technology Corporation&n; * All rights reserved.&n; *&n; * Redistribution and use in source form, with or without modification, are&n; * permitted provided that redistributions of source code must retain the&n; * above copyright notice, this list of conditions and the following disclaimer.&n; *&n; * This software is provided `as is&squot; by Distributed Processing Technology and&n; * any express or implied warranties, including, but not limited to, the&n; * implied warranties of merchantability and fitness for a particular purpose,&n; * are disclaimed. In no event shall Distributed Processing Technology be&n; * liable for any direct, indirect, incidental, special, exemplary or&n; * consequential damages (including, but not limited to, procurement of&n; * substitute goods or services; loss of use, data, or profits; or business&n; * interruptions) however caused and on any theory of liability, whether in&n; * contract, strict liability, or tort (including negligence or otherwise)&n; * arising in any way out of the use of this driver software, even if advised&n; * of the possibility of such damage.&n; *&n; */
macro_line|#ifndef&t;&t;_OSD_DEFS_H
DECL|macro|_OSD_DEFS_H
mdefine_line|#define&t;&t;_OSD_DEFS_H
multiline_comment|/*File - OSD_DEFS.H&n; ****************************************************************************&n; *&n; *Description:&n; *&n; *&t;This file contains the OS dependent defines.  This file is included&n; *in osd_util.h and provides the OS specific defines for that file.&n; *&n; *Copyright Distributed Processing Technology, Corp.&n; *&t;  140 Candace Dr.&n; *&t;  Maitland, Fl.&t;32751   USA&n; *&t;  Phone: (407) 830-5522  Fax: (407) 260-5366&n; *&t;  All Rights Reserved&n; *&n; *Author:&t;Doug Anderson&n; *Date:&t;&t;1/31/94&n; *&n; *Editors:&n; *&n; *Remarks:&n; *&n; *&n; *****************************************************************************/
multiline_comment|/*Definitions - Defines &amp; Constants ----------------------------------------- */
multiline_comment|/* Define the operating system */
macro_line|#if (defined(__linux__))
DECL|macro|_DPT_LINUX
macro_line|# define _DPT_LINUX
macro_line|#elif (defined(__bsdi__))
DECL|macro|_DPT_BSDI
macro_line|# define _DPT_BSDI
macro_line|#elif (defined(__FreeBSD__))
DECL|macro|_DPT_FREE_BSD
macro_line|# define _DPT_FREE_BSD
macro_line|#else
DECL|macro|_DPT_SCO
macro_line|# define _DPT_SCO
macro_line|#endif
macro_line|#if defined (ZIL_CURSES)
DECL|macro|_DPT_CURSES
mdefine_line|#define&t;&t;_DPT_CURSES
macro_line|#else
DECL|macro|_DPT_MOTIF
mdefine_line|#define         _DPT_MOTIF
macro_line|#endif
multiline_comment|/* Redefine &squot;far&squot; to nothing - no far pointer type required in UNIX */
DECL|macro|far
mdefine_line|#define&t;&t;far
multiline_comment|/* Define the mutually exclusive semaphore type */
DECL|macro|SEMAPHORE_T
mdefine_line|#define&t;&t;SEMAPHORE_T&t;unsigned int *
multiline_comment|/* Define a handle to a DLL */
DECL|macro|DLL_HANDLE_T
mdefine_line|#define&t;&t;DLL_HANDLE_T&t;unsigned int *
macro_line|#endif
eof
