multiline_comment|/*&n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpPaca.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
DECL|variable|naca
r_struct
id|naca_struct
op_star
id|naca
suffix:semicolon
DECL|variable|systemcfg
r_struct
id|systemcfg
op_star
id|systemcfg
suffix:semicolon
multiline_comment|/* The Paca is an array with one entry per processor.  Each contains an &n; * ItLpPaca, which contains the information shared between the &n; * hypervisor and Linux.  Each also contains an ItLpRegSave area which&n; * is used by the hypervisor to save registers.&n; * On systems with hardware multi-threading, there are two threads&n; * per processor.  The Paca array must contain an entry for each thread.&n; * The VPD Areas will give a max logical processors = 2 * max physical&n; * processors.  The processor VPD array needs one entry per physical&n; * processor (not thread).&n; */
DECL|macro|PACAINITDATA
mdefine_line|#define PACAINITDATA(number,start,lpq,asrr,asrv)&t;&t;&t;    &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;.xLpPacaPtr = &amp;paca[number].xLpPaca,&t;&t;&t;&t;    &bslash;&n;&t;.xLpRegSavePtr = &amp;paca[number].xRegSav,&t;&t;&t;&t;    &bslash;&n;&t;.lock_token = 0x8000,&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;.xPacaIndex = (number),&t;&t;/* Paca Index */&t;&t;    &bslash;&n;&t;.default_decr = 0x00ff0000,&t;/* Initial Decr */&t;&t;    &bslash;&n;&t;.xStab_data = {&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;.real = (asrr),&t;&t;/* Real pointer to segment table */ &bslash;&n;&t;&t;.virt = (asrv),&t;&t;/* Virt pointer to segment table */ &bslash;&n;&t;&t;.next_round_robin = 1,&t;&t;&t;&t;&t;    &bslash;&n;&t;},&t;&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;.lpQueuePtr = (lpq),&t;&t;/* &amp;xItLpQueue, */&t;&t;    &bslash;&n;&t;/* .xRtas = {&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;.lock = SPIN_LOCK_UNLOCKED&t;&t;&t;&t;    &bslash;&n;&t;}, */&t;&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;.xProcStart = (start),&t;&t;/* Processor start */&t;&t;    &bslash;&n;&t;.xLpPaca = {&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;.xDesc = 0xd397d781,&t;/* &quot;LpPa&quot; */&t;&t;&t;    &bslash;&n;&t;&t;.xSize = sizeof(struct ItLpPaca),&t;&t;&t;    &bslash;&n;&t;&t;.xFPRegsInUse = 1,&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;.xDynProcStatus = 2,&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;.xDecrVal = 0x00ff0000,&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;.xEndOfQuantum = 0xfffffffffffffffful,&t;&t;&t;    &bslash;&n;&t;&t;.xSLBCount = 64,&t;&t;&t;&t;&t;    &bslash;&n;&t;},&t;&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;.xRegSav = {&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;.xDesc = 0xd397d9e2,&t;/* &quot;LpRS&quot; */&t;&t;&t;    &bslash;&n;&t;&t;.xSize = sizeof(struct ItLpRegSave)&t;&t;&t;    &bslash;&n;&t;},&t;&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;.exception_sp =&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;&t;(&amp;paca[number].exception_stack[0]) - EXC_FRAME_SIZE,&t;    &bslash;&n;}
DECL|variable|__page_aligned
r_struct
id|paca_struct
id|paca
(braket
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
id|STAB0_VIRT_ADDR
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
id|STAB0_PHYS_ADDR
comma
id|STAB0_VIRT_ADDR
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
macro_line|#if NR_CPUS &gt; 32
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
comma
id|PACAINITDATA
c_func
(paren
l_int|48
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
l_int|49
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
l_int|50
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
l_int|51
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
l_int|52
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
l_int|53
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
l_int|54
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
l_int|55
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
l_int|56
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
l_int|57
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
l_int|58
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
l_int|59
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
l_int|60
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
l_int|61
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
l_int|62
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
l_int|63
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
macro_line|#if NR_CPUS &gt; 64
id|PACAINITDATA
c_func
(paren
l_int|64
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
l_int|65
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
l_int|66
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
l_int|67
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
l_int|68
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
l_int|69
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
l_int|70
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
l_int|71
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
l_int|72
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
l_int|73
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
l_int|74
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
l_int|75
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
l_int|76
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
l_int|77
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
l_int|78
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
l_int|79
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
l_int|80
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
l_int|81
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
l_int|82
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
l_int|83
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
l_int|84
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
l_int|85
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
l_int|86
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
l_int|87
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
l_int|88
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
l_int|89
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
l_int|90
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
l_int|91
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
l_int|92
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
l_int|93
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
l_int|94
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
l_int|95
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
l_int|96
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
l_int|97
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
l_int|98
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
l_int|99
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
l_int|100
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
l_int|101
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
l_int|102
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
l_int|103
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
l_int|104
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
l_int|105
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
l_int|106
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
l_int|107
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
l_int|108
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
l_int|109
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
l_int|110
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
l_int|111
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
l_int|112
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
l_int|113
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
l_int|114
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
l_int|115
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
l_int|116
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
l_int|117
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
l_int|118
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
l_int|119
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
l_int|120
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
l_int|121
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
l_int|122
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
l_int|123
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
l_int|124
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
l_int|125
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
l_int|126
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
l_int|127
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
macro_line|#endif
macro_line|#endif
)brace
suffix:semicolon
eof
