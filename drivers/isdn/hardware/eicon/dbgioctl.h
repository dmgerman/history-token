multiline_comment|/*&n; *&n;  Copyright (c) Eicon Technology Corporation, 2000.&n; *&n;  This source file is supplied for the use with Eicon&n;  Technology Corporation&squot;s range of DIVA Server Adapters.&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* file: dbgioctl.h                                                 */
multiline_comment|/*------------------------------------------------------------------*/
macro_line|#if !defined(__DBGIOCTL_H__)
DECL|macro|__DBGIOCTL_H__
mdefine_line|#define __DBGIOCTL_H__
macro_line|#ifdef NOT_YET_NEEDED
multiline_comment|/*&n; * The requested operation is passed in arg0 of DbgIoctlArgs,&n; * additional arguments (if any) in arg1, arg2 and arg3.&n; */
r_typedef
r_struct
DECL|member|arg0
(brace
id|ULONG
id|arg0
suffix:semicolon
DECL|member|arg1
id|ULONG
id|arg1
suffix:semicolon
DECL|member|arg2
id|ULONG
id|arg2
suffix:semicolon
DECL|member|arg3
id|ULONG
id|arg3
suffix:semicolon
DECL|typedef|DbgIoctlArgs
)brace
id|DbgIoctlArgs
suffix:semicolon
DECL|macro|DBG_COPY_LOGS
mdefine_line|#define&t;DBG_COPY_LOGS&t;0&t;/* copy debugs to user until buffer full&t;*/
multiline_comment|/* arg1: size threshold&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* arg2: timeout in milliseconds&t;&t;&t;*/
DECL|macro|DBG_FLUSH_LOGS
mdefine_line|#define DBG_FLUSH_LOGS&t;1&t;/* flush pending debugs to user buffer&t;&t;*/
multiline_comment|/* arg1: internal driver id&t;&t;&t;&t;&t;*/
DECL|macro|DBG_LIST_DRVS
mdefine_line|#define DBG_LIST_DRVS&t;2&t;/* return the list of registered drivers&t;*/
DECL|macro|DBG_GET_MASK
mdefine_line|#define&t;DBG_GET_MASK&t;3&t;/* get current debug mask of driver&t;&t;&t;*/
multiline_comment|/* arg1: internal driver id&t;&t;&t;&t;&t;*/
DECL|macro|DBG_SET_MASK
mdefine_line|#define&t;DBG_SET_MASK&t;4&t;/* set/change debug mask of driver&t;&t;&t;*/
multiline_comment|/* arg1: internal driver id&t;&t;&t;&t;&t;*/
multiline_comment|/* arg2: new debug mask&t;&t;&t;&t;&t;&t;*/
DECL|macro|DBG_GET_BUFSIZE
mdefine_line|#define&t;DBG_GET_BUFSIZE&t;5&t;/* get current buffer size of driver&t;&t;*/
multiline_comment|/* arg1: internal driver id&t;&t;&t;&t;&t;*/
multiline_comment|/* arg2: new debug mask&t;&t;&t;&t;&t;&t;*/
DECL|macro|DBG_SET_BUFSIZE
mdefine_line|#define&t;DBG_SET_BUFSIZE&t;6&t;/* set new buffer size of driver&t;&t;&t;*/
multiline_comment|/* arg1: new buffer size&t;&t;&t;&t;&t;*/
multiline_comment|/*&n; *&t;common internal debug message structure&n; */
r_typedef
r_struct
DECL|member|id
(brace
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* virtual driver id                  */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* special message type               */
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
multiline_comment|/* sequence number of message         */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of message in bytes           */
DECL|member|next
r_int
r_int
id|next
suffix:semicolon
multiline_comment|/* offset to next buffered message    */
DECL|member|NTtime
id|LARGE_INTEGER
id|NTtime
suffix:semicolon
multiline_comment|/* 100 ns  since 1.1.1601             */
DECL|member|data
r_int
r_char
id|data
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* message data                       */
DECL|typedef|OldDbgMessage
)brace
id|OldDbgMessage
suffix:semicolon
r_typedef
r_struct
DECL|member|NTtime
(brace
id|LARGE_INTEGER
id|NTtime
suffix:semicolon
multiline_comment|/* 100 ns  since 1.1.1601             */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of message in bytes           */
DECL|member|ffff
r_int
r_int
id|ffff
suffix:semicolon
multiline_comment|/* always 0xffff to indicate new msg  */
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* virtual driver id                  */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* special message type               */
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
multiline_comment|/* sequence number of message         */
DECL|member|data
r_int
r_char
id|data
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* message data                       */
DECL|typedef|DbgMessage
)brace
id|DbgMessage
suffix:semicolon
macro_line|#endif
DECL|macro|DRV_ID_UNKNOWN
mdefine_line|#define DRV_ID_UNKNOWN&t;&t;0x0C&t;/* for messages via prtComp() */
DECL|macro|MSG_PROC_FLAG
mdefine_line|#define&t;MSG_PROC_FLAG&t;&t;0x80
DECL|macro|MSG_PROC_NO_GET
mdefine_line|#define&t;MSG_PROC_NO_GET(x)&t;(((x) &amp; MSG_PROC_FLAG) ? (((x) &gt;&gt; 4) &amp; 7) : -1)
DECL|macro|MSG_PROC_NO_SET
mdefine_line|#define&t;MSG_PROC_NO_SET(x)&t;(MSG_PROC_FLAG | (((x) &amp; 7) &lt;&lt; 4))
DECL|macro|MSG_TYPE_DRV_ID
mdefine_line|#define MSG_TYPE_DRV_ID&t;&t;0x0001
DECL|macro|MSG_TYPE_FLAGS
mdefine_line|#define MSG_TYPE_FLAGS&t;&t;0x0002
DECL|macro|MSG_TYPE_STRING
mdefine_line|#define MSG_TYPE_STRING&t;&t;0x0003
DECL|macro|MSG_TYPE_BINARY
mdefine_line|#define MSG_TYPE_BINARY&t;&t;0x0004
DECL|macro|MSG_HEAD_SIZE
mdefine_line|#define MSG_HEAD_SIZE&t;((unsigned long)&amp;(((DbgMessage *)0)-&gt;data[0]))
DECL|macro|MSG_ALIGN
mdefine_line|#define MSG_ALIGN(len)&t;(((unsigned long)(len) + MSG_HEAD_SIZE + 3) &amp; ~3)
DECL|macro|MSG_SIZE
mdefine_line|#define MSG_SIZE(pMsg)&t;MSG_ALIGN((pMsg)-&gt;size)
DECL|macro|MSG_NEXT
mdefine_line|#define MSG_NEXT(pMsg)&t;((DbgMessage *)( ((char *)(pMsg)) + MSG_SIZE(pMsg) ))
DECL|macro|OLD_MSG_HEAD_SIZE
mdefine_line|#define OLD_MSG_HEAD_SIZE&t;((unsigned long)&amp;(((OldDbgMessage *)0)-&gt;data[0]))
DECL|macro|OLD_MSG_ALIGN
mdefine_line|#define OLD_MSG_ALIGN(len)&t;(((unsigned long)(len)+OLD_MSG_HEAD_SIZE+3) &amp; ~3)
multiline_comment|/*&n; * manifest constants&n; */
DECL|macro|MSG_FRAME_MAX_SIZE
mdefine_line|#define MSG_FRAME_MAX_SIZE&t;2150&t;&t;/* maximum size of B1 frame&t; */
DECL|macro|MSG_TEXT_MAX_SIZE
mdefine_line|#define MSG_TEXT_MAX_SIZE&t;1024&t;&t;/* maximum size of msg text&t; */
DECL|macro|MSG_MAX_SIZE
mdefine_line|#define MSG_MAX_SIZE&t;&t;MSG_ALIGN(MSG_FRAME_MAX_SIZE)
DECL|macro|DBG_MIN_BUFFER_SIZE
mdefine_line|#define DBG_MIN_BUFFER_SIZE&t;0x00008000&t;/* minimal total buffer size  32 KB */
DECL|macro|DBG_DEF_BUFFER_SIZE
mdefine_line|#define DBG_DEF_BUFFER_SIZE&t;0x00020000&t;/* default total buffer size 128 KB */
DECL|macro|DBG_MAX_BUFFER_SIZE
mdefine_line|#define DBG_MAX_BUFFER_SIZE&t;0x00400000&t;/* maximal total buffer size   4 MB */
DECL|macro|DBGDRV_NAME
mdefine_line|#define DBGDRV_NAME&t;&t;&quot;Diehl_DIMAINT&quot;
DECL|macro|UNIDBG_DRIVER
mdefine_line|#define UNIDBG_DRIVER&t;L&quot;&bslash;&bslash;Device&bslash;&bslash;Diehl_DIMAINT&quot; /* UNICODE name for kernel */
DECL|macro|DEBUG_DRIVER
mdefine_line|#define DEBUG_DRIVER&t;&quot;&bslash;&bslash;&bslash;&bslash;.&bslash;&bslash;&quot; DBGDRV_NAME  /* traditional string for apps */
DECL|macro|DBGVXD_NAME
mdefine_line|#define DBGVXD_NAME&t;&t;&quot;DIMAINT&quot;
DECL|macro|DEBUG_VXD
mdefine_line|#define DEBUG_VXD&t;&t;&quot;&bslash;&bslash;&bslash;&bslash;.&bslash;&bslash;&quot; DBGVXD_NAME  /* traditional string for apps */
multiline_comment|/*&n; *&t;Special IDI interface debug construction&n; */
DECL|macro|DBG_IDI_SIG_REQ
mdefine_line|#define&t;DBG_IDI_SIG_REQ&t;&t;(unsigned long)0xF479C402
DECL|macro|DBG_IDI_SIG_IND
mdefine_line|#define&t;DBG_IDI_SIG_IND&t;&t;(unsigned long)0xF479C403
DECL|macro|DBG_IDI_NL_REQ
mdefine_line|#define&t;DBG_IDI_NL_REQ&t;&t;(unsigned long)0xF479C404
DECL|macro|DBG_IDI_NL_IND
mdefine_line|#define&t;DBG_IDI_NL_IND&t;&t;(unsigned long)0xF479C405
r_typedef
r_struct
DECL|member|magic_type
(brace
r_int
r_int
id|magic_type
suffix:semicolon
DECL|member|data_len
r_int
r_int
id|data_len
suffix:semicolon
DECL|member|layer_ID
r_int
r_char
id|layer_ID
suffix:semicolon
DECL|member|entity_ID
r_int
r_char
id|entity_ID
suffix:semicolon
DECL|member|request
r_int
r_char
id|request
suffix:semicolon
DECL|member|ret_code
r_int
r_char
id|ret_code
suffix:semicolon
DECL|member|indication
r_int
r_char
id|indication
suffix:semicolon
DECL|member|complete
r_int
r_char
id|complete
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|DbgIdiAct
DECL|typedef|DbgIdiAction
)brace
id|DbgIdiAct
comma
op_star
id|DbgIdiAction
suffix:semicolon
multiline_comment|/*&n; * We want to use the same IOCTL codes in Win95 and WinNT.&n; * The official constructor for IOCTL codes is the CTL_CODE macro&n; * from &lt;winoctl.h&gt; (&lt;devioctl.h&gt; in WinNT DDK environment).&n; * The problem here is that we don&squot;t know how to get &lt;winioctl.h&gt;&n; * working in a Win95 DDK environment!&n; */
macro_line|# ifdef CTL_CODE&t;/*{*/
multiline_comment|/* Assert that we have the same idea of the CTL_CODE macro.&t;*/
DECL|macro|CTL_CODE
mdefine_line|#define CTL_CODE( DeviceType, Function, Method, Access ) (                 &bslash;&n;    ((DeviceType) &lt;&lt; 16) | ((Access) &lt;&lt; 14) | ((Function) &lt;&lt; 2) | (Method) &bslash;&n;)
macro_line|# else&t;/* !CTL_CODE */ /*}{*/
multiline_comment|/* Use the definitions stolen from &lt;winioctl.h&gt;.  */
DECL|macro|CTL_CODE
mdefine_line|#define CTL_CODE( DeviceType, Function, Method, Access ) (                 &bslash;&n;    ((DeviceType) &lt;&lt; 16) | ((Access) &lt;&lt; 14) | ((Function) &lt;&lt; 2) | (Method) &bslash;&n;)
DECL|macro|METHOD_BUFFERED
mdefine_line|#define METHOD_BUFFERED                 0
DECL|macro|METHOD_IN_DIRECT
mdefine_line|#define METHOD_IN_DIRECT                1
DECL|macro|METHOD_OUT_DIRECT
mdefine_line|#define METHOD_OUT_DIRECT               2
DECL|macro|METHOD_NEITHER
mdefine_line|#define METHOD_NEITHER                  3
DECL|macro|FILE_ANY_ACCESS
mdefine_line|#define FILE_ANY_ACCESS                 0
DECL|macro|FILE_READ_ACCESS
mdefine_line|#define FILE_READ_ACCESS          ( 0x0001 )    
singleline_comment|// file &amp; pipe
DECL|macro|FILE_WRITE_ACCESS
mdefine_line|#define FILE_WRITE_ACCESS         ( 0x0002 )    
singleline_comment|// file &amp; pipe
macro_line|# endif&t;/* CTL_CODE */ /*}*/
multiline_comment|/*&n; * Now we can define WinNT/Win95 DeviceIoControl codes.&n; *&n; * These codes are defined in di_defs.h too, a possible mismatch will be&n; * detected when the dbgtool is compiled.&n; */
DECL|macro|IOCTL_DRIVER_LNK
mdefine_line|#define IOCTL_DRIVER_LNK &bslash;&n;&t;CTL_CODE(0x8001U,0x701,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)
DECL|macro|IOCTL_DRIVER_DBG
mdefine_line|#define IOCTL_DRIVER_DBG &bslash;&n;&t;CTL_CODE(0x8001U,0x702,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)
macro_line|#endif /* __DBGIOCTL_H__ */
eof
