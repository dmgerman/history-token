macro_line|#ifndef _PPC64_PACA_H
DECL|macro|_PPC64_PACA_H
mdefine_line|#define _PPC64_PACA_H
multiline_comment|/*============================================================================&n; *                                                         Header File Id&n; * Name______________:&t;paca.h&n; *&n; * Description_______:&n; *&n; * This control block defines the PACA which defines the processor &n; * specific data for each logical processor on the system.  &n; * There are some pointers defined that are utilized by PLIC.&n; *&n; * C 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include&t;&lt;asm/types.h&gt;
DECL|macro|N_EXC_STACK
mdefine_line|#define N_EXC_STACK    2
multiline_comment|/*-----------------------------------------------------------------------------&n; * Other Includes&n; *-----------------------------------------------------------------------------&n; */
macro_line|#include&t;&lt;asm/iSeries/ItLpPaca.h&gt;
macro_line|#include&t;&lt;asm/iSeries/ItLpRegSave.h&gt;
macro_line|#include&t;&lt;asm/iSeries/ItLpQueue.h&gt;
macro_line|#include&t;&lt;asm/rtas.h&gt;
macro_line|#include&t;&lt;asm/mmu.h&gt;
macro_line|#include&t;&lt;asm/processor.h&gt;
multiline_comment|/* A paca entry is required for each logical processor.  On systems&n; * that support hardware multi-threading, this is equal to twice the&n; * number of physical processors.  On LPAR systems, we are required&n; * to have space for the maximum number of logical processors we&n; * could ever possibly have.  Currently, we are limited to allocating&n; * 24 processors to a partition which gives 48 logical processors on&n; * an HMT box.  Therefore, we reserve this many paca entries.&n; */
DECL|macro|MAX_PROCESSORS
mdefine_line|#define MAX_PROCESSORS 24
DECL|macro|MAX_PACAS
mdefine_line|#define MAX_PACAS MAX_PROCESSORS * 2
r_extern
r_struct
id|paca_struct
id|paca
(braket
)braket
suffix:semicolon
DECL|macro|get_paca
mdefine_line|#define get_paca() ((struct paca_struct *)mfspr(SPRG3))
multiline_comment|/*============================================================================&n; * Name_______:&t;paca&n; *&n; * Description:&n; *&n; *&t;Defines the layout of the paca.  &n; *&n; *&t;This structure is not directly accessed by PLIC or the SP except&n; *&t;for the first two pointers that point to the ItLpPaca area and the&n; *&t;ItLpRegSave area for this processor.  Both the ItLpPaca and&n; *&t;ItLpRegSave objects are currently contained within the&n; *&t;PACA but they do not need to be.&n; *&n; *============================================================================&n; */
DECL|struct|paca_struct
r_struct
id|paca_struct
(brace
multiline_comment|/*=====================================================================================&n; * CACHE_LINE_1 0x0000 - 0x007F&n; *=====================================================================================&n; */
DECL|member|xLpPacaPtr
r_struct
id|ItLpPaca
op_star
id|xLpPacaPtr
suffix:semicolon
multiline_comment|/* Pointer to LpPaca for PLIC&t;&t;0x00 */
DECL|member|xLpRegSavePtr
r_struct
id|ItLpRegSave
op_star
id|xLpRegSavePtr
suffix:semicolon
multiline_comment|/* Pointer to LpRegSave for PLIC&t;0x08 */
DECL|member|xCurrent
id|u64
id|xCurrent
suffix:semicolon
multiline_comment|/* Pointer to current&t;&t;&t;0x10 */
DECL|member|xPacaIndex
id|u16
id|xPacaIndex
suffix:semicolon
multiline_comment|/* Logical processor number&t;&t;0x18 */
DECL|member|xHwProcNum
id|u16
id|xHwProcNum
suffix:semicolon
multiline_comment|/* Actual Hardware Processor Number&t;0x1a */
DECL|member|default_decr
id|u32
id|default_decr
suffix:semicolon
multiline_comment|/* Default decrementer value&t;&t;0x1c */
DECL|member|xHrdIntStack
id|u64
id|xHrdIntStack
suffix:semicolon
multiline_comment|/* Stack for hardware interrupts&t;0x20 */
DECL|member|xKsave
id|u64
id|xKsave
suffix:semicolon
multiline_comment|/* Saved Kernel stack addr or zero&t;0x28 */
DECL|member|pvr
id|u64
id|pvr
suffix:semicolon
multiline_comment|/* Processor version register&t;&t;0x30 */
DECL|member|exception_sp
id|u8
op_star
id|exception_sp
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;&t;0x38 */
DECL|member|lpQueuePtr
r_struct
id|ItLpQueue
op_star
id|lpQueuePtr
suffix:semicolon
multiline_comment|/* LpQueue handled by this processor    0x40 */
DECL|member|xTOC
id|u64
id|xTOC
suffix:semicolon
multiline_comment|/* Kernel TOC address&t;&t;&t;0x48 */
DECL|member|xStab_data
id|STAB
id|xStab_data
suffix:semicolon
multiline_comment|/* Segment table information&t;&t;0x50,0x58,0x60 */
DECL|member|xSegments
id|u8
id|xSegments
(braket
id|STAB_CACHE_SIZE
)braket
suffix:semicolon
multiline_comment|/* Cache of used stab entries&t;&t;0x68,0x70 */
DECL|member|xProcEnabled
id|u8
id|xProcEnabled
suffix:semicolon
multiline_comment|/* 1=soft enabled&t;&t;&t;0x78 */
DECL|member|xHrdIntCount
id|u8
id|xHrdIntCount
suffix:semicolon
multiline_comment|/* Count of active hardware interrupts  0x79  */
DECL|member|prof_enabled
id|u8
id|prof_enabled
suffix:semicolon
multiline_comment|/* 1=iSeries profiling enabled          0x7A */
DECL|member|resv1
id|u8
id|resv1
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;&t;0x7B-0x7F */
multiline_comment|/*=====================================================================================&n; * CACHE_LINE_2 0x0080 - 0x00FF&n; *=====================================================================================&n; */
DECL|member|spare1
id|u64
id|spare1
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;&t;0x00 */
DECL|member|spare2
id|u64
id|spare2
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;&t;0x08 */
DECL|member|spare3
id|u64
id|spare3
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;&t;0x10 */
DECL|member|spare4
id|u64
id|spare4
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;&t;0x18 */
DECL|member|next_jiffy_update_tb
id|u64
id|next_jiffy_update_tb
suffix:semicolon
multiline_comment|/* TB value for next jiffy update&t;0x20 */
DECL|member|lpEvent_count
id|u32
id|lpEvent_count
suffix:semicolon
multiline_comment|/* lpEvents processed&t;&t;&t;0x28 */
DECL|member|prof_multiplier
id|u32
id|prof_multiplier
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;&t;0x2C */
DECL|member|prof_counter
id|u32
id|prof_counter
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;&t;0x30 */
DECL|member|prof_shift
id|u32
id|prof_shift
suffix:semicolon
multiline_comment|/* iSeries shift for profile bucket size0x34 */
DECL|member|prof_buffer
id|u32
op_star
id|prof_buffer
suffix:semicolon
multiline_comment|/* iSeries profiling buffer&t;&t;0x38 */
DECL|member|prof_stext
id|u32
op_star
id|prof_stext
suffix:semicolon
multiline_comment|/* iSeries start of kernel text&t;&t;0x40 */
DECL|member|prof_len
id|u32
id|prof_len
suffix:semicolon
multiline_comment|/* iSeries length of profile buffer -1&t;0x48 */
DECL|member|rsvd2
id|u8
id|rsvd2
(braket
l_int|128
op_minus
l_int|76
)braket
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;&t;0x4C */
multiline_comment|/*=====================================================================================&n; * CACHE_LINE_3 0x0100 - 0x017F&n; *=====================================================================================&n; */
DECL|member|xProcStart
id|u8
id|xProcStart
suffix:semicolon
multiline_comment|/* At startup, processor spins until&t;0x100 */
multiline_comment|/* xProcStart becomes non-zero. */
DECL|member|rsvd3
id|u8
id|rsvd3
(braket
l_int|127
)braket
suffix:semicolon
multiline_comment|/*=====================================================================================&n; * CACHE_LINE_4-8  0x0180 - 0x03FF Contains ItLpPaca&n; *=====================================================================================&n; */
DECL|member|xLpPaca
r_struct
id|ItLpPaca
id|xLpPaca
suffix:semicolon
multiline_comment|/* Space for ItLpPaca */
multiline_comment|/*=====================================================================================&n; * CACHE_LINE_9-16 0x0400 - 0x07FF Contains ItLpRegSave&n; *=====================================================================================&n; */
DECL|member|xRegSav
r_struct
id|ItLpRegSave
id|xRegSav
suffix:semicolon
multiline_comment|/* Register save for proc */
multiline_comment|/*=====================================================================================&n; * CACHE_LINE_17-18 0x0800 - 0x0EFF Reserved&n; *=====================================================================================&n; */
DECL|member|xRtas
r_struct
id|rtas_args
id|xRtas
suffix:semicolon
multiline_comment|/* Per processor RTAS struct */
DECL|member|xR1
id|u64
id|xR1
suffix:semicolon
multiline_comment|/* r1 save for RTAS calls */
DECL|member|xSavedMsr
id|u64
id|xSavedMsr
suffix:semicolon
multiline_comment|/* Old msr saved here by HvCall */
DECL|member|rsvd5
id|u8
id|rsvd5
(braket
l_int|256
op_minus
l_int|16
op_minus
r_sizeof
(paren
r_struct
id|rtas_args
)paren
)braket
suffix:semicolon
multiline_comment|/*=====================================================================================&n; * CACHE_LINE_19-30 0x0800 - 0x0EFF Reserved&n; *=====================================================================================&n; */
DECL|member|rsvd6
id|u8
id|rsvd6
(braket
l_int|0x600
)braket
suffix:semicolon
multiline_comment|/*=====================================================================================&n; * CACHE_LINE_31 0x0F00 - 0x0F7F Exception stack&n; *=====================================================================================&n; */
DECL|member|exception_stack
id|u8
id|exception_stack
(braket
id|N_EXC_STACK
op_star
id|EXC_FRAME_SIZE
)braket
suffix:semicolon
multiline_comment|/*=====================================================================================&n; * CACHE_LINE_32 0x0F80 - 0x0FFF Reserved&n; *=====================================================================================&n; */
DECL|member|rsvd7
id|u8
id|rsvd7
(braket
l_int|0x80
)braket
suffix:semicolon
multiline_comment|/* Give the stack some rope ... */
multiline_comment|/*=====================================================================================&n; * Page 2 Reserved for guard page.  Also used as a stack early in SMP boots before&n; *        relocation is enabled.&n; *=====================================================================================&n; */
DECL|member|guard
id|u8
id|guard
(braket
l_int|0x1000
)braket
suffix:semicolon
multiline_comment|/* ... and then hang &squot;em         */
)brace
suffix:semicolon
macro_line|#endif /* _PPC64_PACA_H */
eof
