multiline_comment|/*&t;From: if_pppvar.h,v 1.2 1995/06/12 11:36:51 paulus Exp */
multiline_comment|/*&n; * if_pppvar.h - private structures and declarations for PPP.&n; *&n; * Copyright (c) 1994 The Australian National University.&n; * All rights reserved.&n; *&n; * Permission to use, copy, modify, and distribute this software and its&n; * documentation is hereby granted, provided that the above copyright&n; * notice appears in all copies.  This software is provided without any&n; * warranty, express or implied. The Australian National University&n; * makes no representations about the suitability of this software for&n; * any purpose.&n; *&n; * IN NO EVENT SHALL THE AUSTRALIAN NATIONAL UNIVERSITY BE LIABLE TO ANY&n; * PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES&n; * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF&n; * THE AUSTRALIAN NATIONAL UNIVERSITY HAVE BEEN ADVISED OF THE POSSIBILITY&n; * OF SUCH DAMAGE.&n; *&n; * THE AUSTRALIAN NATIONAL UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,&n; * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY&n; * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS&n; * ON AN &quot;AS IS&quot; BASIS, AND THE AUSTRALIAN NATIONAL UNIVERSITY HAS NO&n; * OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,&n; * OR MODIFICATIONS.&n; *&n; * Copyright (c) 1989 Carnegie Mellon University.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms are permitted&n; * provided that the above copyright notice and this paragraph are&n; * duplicated in all such forms and that any documentation,&n; * advertising materials, and other materials related to such&n; * distribution and use acknowledge that the software was developed&n; * by Carnegie Mellon University.  The name of the&n; * University may not be used to endorse or promote products derived&n; * from this software without specific prior written permission.&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND WITHOUT ANY EXPRESS OR&n; * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED&n; * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.&n; */
multiline_comment|/*&n; *  ==FILEVERSION 990806==&n; *&n; *  NOTE TO MAINTAINERS:&n; *   If you modify this file at all, please set the above date.&n; *   if_pppvar.h is shipped with a PPP distribution as well as with the kernel;&n; *   if everyone increases the FILEVERSION number above, then scripts&n; *   can do the right thing when deciding whether to install a new if_pppvar.h&n; *   file.  Don&squot;t change the format of that line otherwise, so the&n; *   installation script can recognize it.&n; */
multiline_comment|/*&n; * Supported network protocols.  These values are used for&n; * indexing sc_npmode.&n; */
DECL|macro|NP_IP
mdefine_line|#define NP_IP&t;0&t;&t;/* Internet Protocol */
DECL|macro|NP_IPX
mdefine_line|#define NP_IPX&t;1&t;&t;/* IPX protocol */
DECL|macro|NP_AT
mdefine_line|#define NP_AT&t;2&t;&t;/* Appletalk protocol */
DECL|macro|NP_IPV6
mdefine_line|#define NP_IPV6&t;3&t;&t;/* Internet Protocol */
DECL|macro|NUM_NP
mdefine_line|#define NUM_NP&t;4&t;&t;/* Number of NPs. */
DECL|macro|OBUFSIZE
mdefine_line|#define OBUFSIZE&t;256&t;/* # chars of output buffering */
DECL|macro|PPP_MAGIC
mdefine_line|#define PPP_MAGIC&t;0x5002
DECL|macro|PPP_VERSION
mdefine_line|#define PPP_VERSION&t;&quot;2.3.7&quot;
eof
