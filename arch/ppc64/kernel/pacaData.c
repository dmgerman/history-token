multiline_comment|/*&n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
DECL|macro|__KERNEL__
mdefine_line|#define __KERNEL__ 1
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpPaca.h&gt;
macro_line|#include &lt;asm/Paca.h&gt;
multiline_comment|/* The Paca is an array with one entry per processor.  Each contains an &n; * ItLpPaca, which contains the information shared between the &n; * hypervisor and Linux.  Each also contains an ItLpRegSave area which&n; * is used by the hypervisor to save registers.&n; * On systems with hardware multi-threading, there are two threads&n; * per processor.  The Paca array must contain an entry for each thread.&n; * The VPD Areas will give a max logical processors = 2 * max physical&n; * processors.  The processor VPD array needs one entry per physical&n; * processor (not thread).&n; */
DECL|macro|PACAINITDATA
mdefine_line|#define PACAINITDATA(number,start,lpq,asrr,asrv) &bslash;&n;{                                                                          &bslash;&n;        xLpPacaPtr: &amp;xPaca[number].xLpPaca,                                 &bslash;&n;        xLpRegSavePtr: &amp;xPaca[number].xRegSav,                              &bslash;&n;        xPacaIndex: (number),           /* Paca Index        */             &bslash;&n;        default_decr: 0x00ff0000,       /* Initial Decr      */             &bslash;&n;        xStab_data: {                                                       &bslash;&n;                real: (asrr),           /* Real pointer to segment table */ &bslash;&n;                virt: (asrv),           /* Virt pointer to segment table */ &bslash;&n;                next_round_robin: 1     /* Round robin index */             &bslash;&n;        },                                                                  &bslash;&n;        lpQueuePtr: (lpq),              /* &amp;xItLpQueue,                  */ &bslash;&n;        xRtas: {                                                            &bslash;&n;                lock: SPIN_LOCK_UNLOCKED                                    &bslash;&n;        },                                                                  &bslash;&n;        xProcStart: (start),            /* Processor start */               &bslash;&n;        xLpPaca: {                                                          &bslash;&n;                xDesc: 0xd397d781,      /* &quot;LpPa&quot;          */               &bslash;&n;                xSize: sizeof(struct ItLpPaca),                             &bslash;&n;                xFPRegsInUse: 1,                                            &bslash;&n;                xDynProcStatus: 2,                                          &bslash;&n;&t;&t;xDecrVal: 0x00ff0000,&t;&t;&t;&t;&t;    &bslash;&n;                xEndOfQuantum: 0xffffffffffffffff                           &bslash;&n;        },                                                                  &bslash;&n;        xRegSav: {                                                          &bslash;&n;                xDesc: 0xd397d9e2,      /* &quot;LpRS&quot;          */               &bslash;&n;                xSize: sizeof(struct ItLpRegSave)                           &bslash;&n;        },                                                                  &bslash;&n;        exception_sp:                                                       &bslash;&n;                (&amp;xPaca[number].exception_stack[0]) - EXC_FRAME_SIZE,       &bslash;&n;}
DECL|variable|__page_aligned
r_struct
id|Paca
id|xPaca
(braket
id|maxPacas
)braket
id|__page_aligned
op_assign
(brace
macro_line|#ifdef CONFIG_PPC_ISERIES
id|PACAINITDATA
c_func
(paren
l_int|0
comma
l_int|1
comma
op_amp
id|xItLpQueue
comma
l_int|0
comma
l_int|0xc000000000005000
)paren
comma
macro_line|#else
id|PACAINITDATA
c_func
(paren
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0x5000
comma
l_int|0xc000000000005000
)paren
comma
macro_line|#endif
id|PACAINITDATA
c_func
(paren
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|3
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|4
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|5
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|6
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|7
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|8
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|9
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|10
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|11
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|12
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|13
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|14
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|15
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|16
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|17
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|18
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|19
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|20
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|21
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|22
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|23
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|24
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|25
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|26
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|27
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|28
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|29
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|30
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|31
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|32
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|33
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|34
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|35
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|36
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|37
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|38
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|39
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|40
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|41
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|42
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|43
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|44
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|45
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|46
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
comma
id|PACAINITDATA
c_func
(paren
l_int|47
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
)brace
suffix:semicolon
eof
