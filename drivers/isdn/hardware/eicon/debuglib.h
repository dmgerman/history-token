multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#if !defined(__DEBUGLIB_H__)
DECL|macro|__DEBUGLIB_H__
mdefine_line|#define __DEBUGLIB_H__
macro_line|#include &lt;stdarg.h&gt;
multiline_comment|/*&n; * define global debug priorities&n; */
DECL|macro|DL_LOG
mdefine_line|#define DL_LOG  0x00000001 /* always worth mentioning */
DECL|macro|DL_FTL
mdefine_line|#define DL_FTL  0x00000002 /* always sampled error    */
DECL|macro|DL_ERR
mdefine_line|#define DL_ERR  0x00000004 /* any kind of error       */
DECL|macro|DL_TRC
mdefine_line|#define DL_TRC  0x00000008 /* verbose information     */
DECL|macro|DL_XLOG
mdefine_line|#define DL_XLOG  0x00000010 /* old xlog info           */
DECL|macro|DL_MXLOG
mdefine_line|#define DL_MXLOG 0x00000020 /* maestra xlog info    */
DECL|macro|DL_FTL_MXLOG
mdefine_line|#define DL_FTL_MXLOG 0x00000021 /* fatal maestra xlog info */
DECL|macro|DL_EVL
mdefine_line|#define DL_EVL  0x00000080 /* special NT eventlog msg */
DECL|macro|DL_COMPAT
mdefine_line|#define DL_COMPAT (DL_MXLOG | DL_XLOG)
DECL|macro|DL_PRIOR_MASK
mdefine_line|#define DL_PRIOR_MASK (DL_EVL | DL_COMPAT | DL_TRC | DL_ERR | DL_FTL | DL_LOG)
DECL|macro|DLI_LOG
mdefine_line|#define DLI_LOG  0x0100
DECL|macro|DLI_FTL
mdefine_line|#define DLI_FTL  0x0200
DECL|macro|DLI_ERR
mdefine_line|#define DLI_ERR  0x0300
DECL|macro|DLI_TRC
mdefine_line|#define DLI_TRC  0x0400
DECL|macro|DLI_XLOG
mdefine_line|#define DLI_XLOG 0x0500
DECL|macro|DLI_MXLOG
mdefine_line|#define DLI_MXLOG 0x0600
DECL|macro|DLI_FTL_MXLOG
mdefine_line|#define DLI_FTL_MXLOG 0x0600
DECL|macro|DLI_EVL
mdefine_line|#define DLI_EVL  0x0800
multiline_comment|/*&n; * define OS (operating system interface) debuglevel&n; */
DECL|macro|DL_REG
mdefine_line|#define DL_REG  0x00000100 /* init/query registry     */
DECL|macro|DL_MEM
mdefine_line|#define DL_MEM  0x00000200 /* memory management       */
DECL|macro|DL_SPL
mdefine_line|#define DL_SPL  0x00000400 /* event/spinlock handling */
DECL|macro|DL_IRP
mdefine_line|#define DL_IRP  0x00000800 /* I/O request handling    */
DECL|macro|DL_TIM
mdefine_line|#define DL_TIM  0x00001000 /* timer/watchdog handling */
DECL|macro|DL_BLK
mdefine_line|#define DL_BLK  0x00002000 /* raw data block contents */
DECL|macro|DL_OS_MASK
mdefine_line|#define DL_OS_MASK (DL_BLK | DL_TIM | DL_IRP | DL_SPL | DL_MEM | DL_REG)
DECL|macro|DLI_REG
mdefine_line|#define DLI_REG  0x0900
DECL|macro|DLI_MEM
mdefine_line|#define DLI_MEM  0x0A00
DECL|macro|DLI_SPL
mdefine_line|#define DLI_SPL  0x0B00
DECL|macro|DLI_IRP
mdefine_line|#define DLI_IRP  0x0C00
DECL|macro|DLI_TIM
mdefine_line|#define DLI_TIM  0x0D00
DECL|macro|DLI_BLK
mdefine_line|#define DLI_BLK  0x0E00
multiline_comment|/*&n; * define ISDN (connection interface) debuglevel&n; */
DECL|macro|DL_TAPI
mdefine_line|#define DL_TAPI  0x00010000 /* debug TAPI interface    */
DECL|macro|DL_NDIS
mdefine_line|#define DL_NDIS  0x00020000 /* debug NDIS interface    */
DECL|macro|DL_CONN
mdefine_line|#define DL_CONN  0x00040000 /* connection handling     */
DECL|macro|DL_STAT
mdefine_line|#define DL_STAT  0x00080000 /* trace state machines    */
DECL|macro|DL_SEND
mdefine_line|#define DL_SEND  0x00100000 /* trace raw xmitted data  */
DECL|macro|DL_RECV
mdefine_line|#define DL_RECV  0x00200000 /* trace raw received data */
DECL|macro|DL_DATA
mdefine_line|#define DL_DATA  (DL_SEND | DL_RECV)
DECL|macro|DL_ISDN_MASK
mdefine_line|#define DL_ISDN_MASK (DL_DATA | DL_STAT | DL_CONN | DL_NDIS | DL_TAPI)
DECL|macro|DLI_TAPI
mdefine_line|#define DLI_TAPI 0x1100
DECL|macro|DLI_NDIS
mdefine_line|#define DLI_NDIS 0x1200
DECL|macro|DLI_CONN
mdefine_line|#define DLI_CONN 0x1300
DECL|macro|DLI_STAT
mdefine_line|#define DLI_STAT 0x1400
DECL|macro|DLI_SEND
mdefine_line|#define DLI_SEND 0x1500
DECL|macro|DLI_RECV
mdefine_line|#define DLI_RECV 0x1600
multiline_comment|/*&n; * define some private (unspecified) debuglevel&n; */
DECL|macro|DL_PRV0
mdefine_line|#define DL_PRV0  0x01000000
DECL|macro|DL_PRV1
mdefine_line|#define DL_PRV1  0x02000000
DECL|macro|DL_PRV2
mdefine_line|#define DL_PRV2  0x04000000
DECL|macro|DL_PRV3
mdefine_line|#define DL_PRV3  0x08000000
DECL|macro|DL_PRIV_MASK
mdefine_line|#define DL_PRIV_MASK (DL_PRV0 | DL_PRV1 | DL_PRV2 | DL_PRV3)
DECL|macro|DLI_PRV0
mdefine_line|#define DLI_PRV0 0x1900
DECL|macro|DLI_PRV1
mdefine_line|#define DLI_PRV1 0x1A00
DECL|macro|DLI_PRV2
mdefine_line|#define DLI_PRV2 0x1B00
DECL|macro|DLI_PRV3
mdefine_line|#define DLI_PRV3 0x1C00
DECL|macro|DT_INDEX
mdefine_line|#define DT_INDEX(x)  ((x) &amp; 0x000F)
DECL|macro|DL_INDEX
mdefine_line|#define DL_INDEX(x)  ((((x) &gt;&gt; 8) &amp; 0x00FF) - 1)
DECL|macro|DLI_NAME
mdefine_line|#define DLI_NAME(x)  ((x) &amp; 0xFF00)
multiline_comment|/*&n; * Debug mask for kernel mode tracing, if set the output is also sent to&n; * the system debug function. Requires that the project is compiled&n; * with _KERNEL_DBG_PRINT_&n; */
DECL|macro|DL_TO_KERNEL
mdefine_line|#define DL_TO_KERNEL    0x40000000
multiline_comment|/*&n; * define low level macros for formatted &amp; raw debugging&n; */
DECL|macro|DBG_DECL
mdefine_line|#define DBG_DECL(func) extern void  myDbgPrint_##func (char *, ...) ;
id|DBG_DECL
c_func
(paren
id|LOG
)paren
id|DBG_DECL
c_func
(paren
id|FTL
)paren
id|DBG_DECL
c_func
(paren
id|ERR
)paren
id|DBG_DECL
c_func
(paren
id|TRC
)paren
id|DBG_DECL
c_func
(paren
id|MXLOG
)paren
id|DBG_DECL
c_func
(paren
id|FTL_MXLOG
)paren
r_extern
r_void
id|myDbgPrint_EVL
(paren
r_int
comma
dot
dot
dot
)paren
suffix:semicolon
id|DBG_DECL
c_func
(paren
id|REG
)paren
id|DBG_DECL
c_func
(paren
id|MEM
)paren
id|DBG_DECL
c_func
(paren
id|SPL
)paren
id|DBG_DECL
c_func
(paren
id|IRP
)paren
id|DBG_DECL
c_func
(paren
id|TIM
)paren
id|DBG_DECL
c_func
(paren
id|BLK
)paren
id|DBG_DECL
c_func
(paren
id|TAPI
)paren
id|DBG_DECL
c_func
(paren
id|NDIS
)paren
id|DBG_DECL
c_func
(paren
id|CONN
)paren
id|DBG_DECL
c_func
(paren
id|STAT
)paren
id|DBG_DECL
c_func
(paren
id|SEND
)paren
id|DBG_DECL
c_func
(paren
id|RECV
)paren
id|DBG_DECL
c_func
(paren
id|PRV0
)paren
id|DBG_DECL
c_func
(paren
id|PRV1
)paren
id|DBG_DECL
c_func
(paren
id|PRV2
)paren
id|DBG_DECL
c_func
(paren
id|PRV3
)paren
macro_line|#ifdef  _KERNEL_DBG_PRINT_
multiline_comment|/*&n; * tracing to maint and kernel if selected in the trace mask.&n; */
DECL|macro|DBG_TEST
mdefine_line|#define DBG_TEST(func,args) &bslash;&n;{ if ( (myDriverDebugHandle.dbgMask) &amp; (unsigned long)DL_##func ) &bslash;&n; { &bslash;&n;        if ( (myDriverDebugHandle.dbgMask) &amp; DL_TO_KERNEL ) &bslash;&n;            {DbgPrint args; DbgPrint (&quot;&bslash;r&bslash;n&quot;);} &bslash;&n;        myDbgPrint_##func args ; &bslash;&n;} }
macro_line|#else
multiline_comment|/*&n; * Standard tracing to maint driver.&n; */
mdefine_line|#define DBG_TEST(func,args) &bslash;&n;{ if ( (myDriverDebugHandle.dbgMask) &amp; (unsigned long)DL_##func ) &bslash;&n; { myDbgPrint_##func args ; &bslash;&n;} }
macro_line|#endif
multiline_comment|/*&n; * For event level debug use a separate define, the paramete are&n; * different and cause compiler errors on some systems.&n; */
DECL|macro|DBG_EVL_ID
mdefine_line|#define DBG_EVL_ID(args) &bslash;&n;{ if ( (myDriverDebugHandle.dbgMask) &amp; (unsigned long)DL_EVL ) &bslash;&n; { myDbgPrint_EVL args ; &bslash;&n;} }
DECL|macro|DBG_LOG
mdefine_line|#define DBG_LOG(args)  DBG_TEST(LOG, args)
DECL|macro|DBG_FTL
mdefine_line|#define DBG_FTL(args)  DBG_TEST(FTL, args)
DECL|macro|DBG_ERR
mdefine_line|#define DBG_ERR(args)  DBG_TEST(ERR, args)
DECL|macro|DBG_TRC
mdefine_line|#define DBG_TRC(args)  DBG_TEST(TRC, args)
DECL|macro|DBG_MXLOG
mdefine_line|#define DBG_MXLOG(args)  DBG_TEST(MXLOG, args)
DECL|macro|DBG_FTL_MXLOG
mdefine_line|#define DBG_FTL_MXLOG(args) DBG_TEST(FTL_MXLOG, args)
DECL|macro|DBG_EVL
mdefine_line|#define DBG_EVL(args)  DBG_EVL_ID(args)
DECL|macro|DBG_REG
mdefine_line|#define DBG_REG(args)  DBG_TEST(REG, args)
DECL|macro|DBG_MEM
mdefine_line|#define DBG_MEM(args)  DBG_TEST(MEM, args)
DECL|macro|DBG_SPL
mdefine_line|#define DBG_SPL(args)  DBG_TEST(SPL, args)
DECL|macro|DBG_IRP
mdefine_line|#define DBG_IRP(args)  DBG_TEST(IRP, args)
DECL|macro|DBG_TIM
mdefine_line|#define DBG_TIM(args)  DBG_TEST(TIM, args)
DECL|macro|DBG_BLK
mdefine_line|#define DBG_BLK(args)  DBG_TEST(BLK, args)
DECL|macro|DBG_TAPI
mdefine_line|#define DBG_TAPI(args)  DBG_TEST(TAPI, args)
DECL|macro|DBG_NDIS
mdefine_line|#define DBG_NDIS(args)  DBG_TEST(NDIS, args)
DECL|macro|DBG_CONN
mdefine_line|#define DBG_CONN(args)  DBG_TEST(CONN, args)
DECL|macro|DBG_STAT
mdefine_line|#define DBG_STAT(args)  DBG_TEST(STAT, args)
DECL|macro|DBG_SEND
mdefine_line|#define DBG_SEND(args)  DBG_TEST(SEND, args)
DECL|macro|DBG_RECV
mdefine_line|#define DBG_RECV(args)  DBG_TEST(RECV, args)
DECL|macro|DBG_PRV0
mdefine_line|#define DBG_PRV0(args)  DBG_TEST(PRV0, args)
DECL|macro|DBG_PRV1
mdefine_line|#define DBG_PRV1(args)  DBG_TEST(PRV1, args)
DECL|macro|DBG_PRV2
mdefine_line|#define DBG_PRV2(args)  DBG_TEST(PRV2, args)
DECL|macro|DBG_PRV3
mdefine_line|#define DBG_PRV3(args)  DBG_TEST(PRV3, args)
multiline_comment|/*&n; * prototypes for debug register/deregister functions in &quot;debuglib.c&quot;&n; */
r_extern
r_int
id|DbgRegister
(paren
r_char
op_star
id|drvName
comma
r_char
op_star
id|drvTag
comma
r_int
r_int
id|dbgMask
)paren
suffix:semicolon
r_extern
r_void
id|DbgDeregister
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|DbgSetLevel
(paren
r_int
r_int
id|dbgMask
)paren
suffix:semicolon
multiline_comment|/*&n; * driver internal structure for debug handling;&n; * in client drivers this structure is maintained in &quot;debuglib.c&quot;,&n; * in the debug driver &quot;debug.c&quot; maintains a chain of such structs.&n; */
DECL|typedef|pDbgHandle
r_typedef
r_struct
id|_DbgHandle_
op_star
id|pDbgHandle
suffix:semicolon
DECL|typedef|DbgEnd
r_typedef
r_void
(paren
op_star
id|DbgEnd
)paren
(paren
id|pDbgHandle
)paren
suffix:semicolon
DECL|typedef|DbgLog
r_typedef
r_void
(paren
op_star
id|DbgLog
)paren
(paren
r_int
r_int
comma
r_int
comma
r_char
op_star
comma
id|va_list
)paren
suffix:semicolon
DECL|typedef|DbgOld
r_typedef
r_void
(paren
op_star
id|DbgOld
)paren
(paren
r_int
r_int
comma
r_char
op_star
comma
id|va_list
)paren
suffix:semicolon
DECL|typedef|DbgEv
r_typedef
r_void
(paren
op_star
id|DbgEv
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
id|va_list
)paren
suffix:semicolon
DECL|typedef|DbgIrq
r_typedef
r_void
(paren
op_star
id|DbgIrq
)paren
(paren
r_int
r_int
comma
r_int
comma
r_char
op_star
comma
id|va_list
)paren
suffix:semicolon
DECL|struct|_DbgHandle_
r_typedef
r_struct
id|_DbgHandle_
DECL|member|Registered
(brace
r_char
id|Registered
suffix:semicolon
multiline_comment|/* driver successfull registered */
DECL|macro|DBG_HANDLE_REG_NEW
mdefine_line|#define DBG_HANDLE_REG_NEW 0x01  /* this (new) structure    */
DECL|macro|DBG_HANDLE_REG_OLD
mdefine_line|#define DBG_HANDLE_REG_OLD 0x7f  /* old structure (see below)  */
DECL|member|Version
r_char
id|Version
suffix:semicolon
multiline_comment|/* version of this structure  */
DECL|macro|DBG_HANDLE_VERSION
mdefine_line|#define DBG_HANDLE_VERSION 1   /* contains dbg_old function now */
DECL|macro|DBG_HANDLE_VER_EXT
mdefine_line|#define DBG_HANDLE_VER_EXT  2           /* pReserved points to extended info*/
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* internal id of registered driver */
DECL|member|next
r_struct
id|_DbgHandle_
op_star
id|next
suffix:semicolon
multiline_comment|/* ptr to next registered driver    */
r_struct
multiline_comment|/*LARGE_INTEGER*/
(brace
DECL|member|LowPart
r_int
r_int
id|LowPart
suffix:semicolon
DECL|member|HighPart
r_int
id|HighPart
suffix:semicolon
DECL|member|regTime
)brace
id|regTime
suffix:semicolon
multiline_comment|/* timestamp for registration       */
DECL|member|pIrp
r_void
op_star
id|pIrp
suffix:semicolon
multiline_comment|/* ptr to pending i/o request       */
DECL|member|dbgMask
r_int
r_int
id|dbgMask
suffix:semicolon
multiline_comment|/* current debug mask               */
DECL|member|drvName
r_char
id|drvName
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* ASCII name of registered driver  */
DECL|member|drvTag
r_char
id|drvTag
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* revision string     */
DECL|member|dbg_end
id|DbgEnd
id|dbg_end
suffix:semicolon
multiline_comment|/* function for debug closing       */
DECL|member|dbg_prt
id|DbgLog
id|dbg_prt
suffix:semicolon
multiline_comment|/* function for debug appending     */
DECL|member|dbg_old
id|DbgOld
id|dbg_old
suffix:semicolon
multiline_comment|/* function for old debug appending */
DECL|member|dbg_ev
id|DbgEv
id|dbg_ev
suffix:semicolon
multiline_comment|/* function for Windows NT Eventlog */
DECL|member|dbg_irq
id|DbgIrq
id|dbg_irq
suffix:semicolon
multiline_comment|/* function for irql checked debug  */
DECL|member|pReserved3
r_void
op_star
id|pReserved3
suffix:semicolon
DECL|typedef|_DbgHandle_
)brace
id|_DbgHandle_
suffix:semicolon
r_extern
id|_DbgHandle_
id|myDriverDebugHandle
suffix:semicolon
r_typedef
r_struct
DECL|member|next
(brace
r_struct
id|_OldDbgHandle_
op_star
id|next
suffix:semicolon
DECL|member|pIrp
r_void
op_star
id|pIrp
suffix:semicolon
DECL|member|regTime
r_int
id|regTime
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dbgMask
r_int
r_int
id|dbgMask
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|drvName
r_char
id|drvName
(braket
l_int|78
)braket
suffix:semicolon
DECL|member|dbg_end
id|DbgEnd
id|dbg_end
suffix:semicolon
DECL|member|dbg_prt
id|DbgLog
id|dbg_prt
suffix:semicolon
DECL|typedef|_OldDbgHandle_
)brace
id|_OldDbgHandle_
suffix:semicolon
multiline_comment|/* the differences in DbgHandles&n;   old:    tmp:     new:&n; 0 long next  char Registered  char Registered&n;       char filler   char Version&n;       short id    short id&n; 4 long pIrp  long    regTime.lo  long next&n; 8 long    regTime.lo long    regTime.hi  long    regTime.lo&n; 12 long    regTime.hi long next   long regTime.hi&n; 16 long dbgMask  long pIrp   long pIrp&n; 20 short id   long dbgMask   long dbgMask&n; 22 char    drvName[78] ..&n; 24 ..     char drvName[16]  char drvName[16]&n; 40 ..     char drvTag[64]  char drvTag[64]&n; 100 void *dbg_end ..      ..&n; 104 void *dbg_prt void *dbg_end  void *dbg_end&n; 108 ..     void *dbg_prt  void *dbg_prt&n; 112 ..     ..      void *dbg_old&n; 116 ..     ..      void *dbg_ev&n; 120 ..     ..      void *dbg_irq&n; 124 ..     ..      void *pReserved3&n; ( new-&gt;id == 0 &amp;&amp; *((short *)&amp;new-&gt;dbgMask) == -1 ) identifies &quot;old&quot;,&n; new-&gt;Registered and new-&gt;Version overlay old-&gt;next,&n; new-&gt;next overlays old-&gt;pIrp, new-&gt;regTime matches old-&gt;regTime and&n; thus these fields can be maintained in new struct whithout trouble;&n; id, dbgMask, drvName, dbg_end and dbg_prt need special handling !&n;*/
DECL|macro|DBG_EXT_TYPE_CARD_TRACE
mdefine_line|#define DBG_EXT_TYPE_CARD_TRACE     0x00000001
r_typedef
r_struct
(brace
DECL|member|ExtendedType
r_int
r_int
id|ExtendedType
suffix:semicolon
r_union
(brace
multiline_comment|/* DBG_EXT_TYPE_CARD_TRACE */
r_struct
(brace
DECL|member|MaskChangedNotify
r_void
(paren
op_star
id|MaskChangedNotify
)paren
(paren
r_void
op_star
id|pContext
)paren
suffix:semicolon
DECL|member|ModuleTxtMask
r_int
r_int
id|ModuleTxtMask
suffix:semicolon
DECL|member|DebugLevel
r_int
r_int
id|DebugLevel
suffix:semicolon
DECL|member|B_ChannelMask
r_int
r_int
id|B_ChannelMask
suffix:semicolon
DECL|member|LogBufferSize
r_int
r_int
id|LogBufferSize
suffix:semicolon
DECL|member|CardTrace
)brace
id|CardTrace
suffix:semicolon
DECL|member|u1
)brace
id|u1
suffix:semicolon
DECL|typedef|_DbgExtendedInfo_
)brace
id|_DbgExtendedInfo_
suffix:semicolon
multiline_comment|/* -------------------------------------------------------------&n;    Function used for xlog-style debug&n;   ------------------------------------------------------------- */
DECL|macro|XDI_USE_XLOG
mdefine_line|#define XDI_USE_XLOG 1
r_void
id|xdi_dbg_xlog
(paren
r_char
op_star
id|x
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#endif /* __DEBUGLIB_H__ */
eof
