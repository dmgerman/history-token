multiline_comment|/*----------------------------------------&n;  PERFORMANCE INSTRUMENTATION  &n;  Guillaume Thouvenin           08/10/98&n;  David S. Miller               10/06/98&n;  ---------------------------------------*/
macro_line|#ifndef PERF_COUNTER_API
DECL|macro|PERF_COUNTER_API
mdefine_line|#define PERF_COUNTER_API
multiline_comment|/* sys_perfctr() interface.  First arg is operation code&n; * from enumeration below.  The meaning of further arguments&n; * are determined by the operation code.&n; *&n; * int sys_perfctr(int opcode, unsigned long arg0,&n; *                 unsigned long arg1, unsigned long arg2)&n; *&n; * Pointers which are passed by the user are pointers to 64-bit&n; * integers.&n; *&n; * Once enabled, performance counter state is retained until the&n; * process either exits or performs an exec.  That is, performance&n; * counters remain enabled for fork/clone children.&n; */
DECL|enum|perfctr_opcode
r_enum
id|perfctr_opcode
(brace
multiline_comment|/* Enable UltraSparc performance counters, ARG0 is pointer&n;&t; * to 64-bit accumulator for D0 counter in PIC, ARG1 is pointer&n;&t; * to 64-bit accumulator for D1 counter.  ARG2 is a pointer to&n;&t; * the initial PCR register value to use.&n;&t; */
DECL|enumerator|PERFCTR_ON
id|PERFCTR_ON
comma
multiline_comment|/* Disable UltraSparc performance counters.  The PCR is written&n;&t; * with zero and the user counter accumulator pointers and&n;&t; * working PCR register value are forgotten.&n;&t; */
DECL|enumerator|PERFCTR_OFF
id|PERFCTR_OFF
comma
multiline_comment|/* Add current D0 and D1 PIC values into user pointers given&n;&t; * in PERFCTR_ON operation.  The PIC is cleared before returning.&n;&t; */
DECL|enumerator|PERFCTR_READ
id|PERFCTR_READ
comma
multiline_comment|/* Clear the PIC register. */
DECL|enumerator|PERFCTR_CLRPIC
id|PERFCTR_CLRPIC
comma
multiline_comment|/* Begin using a new PCR value, the pointer to which is passed&n;&t; * in ARG0.  The PIC is also cleared after the new PCR value is&n;&t; * written.&n;&t; */
DECL|enumerator|PERFCTR_SETPCR
id|PERFCTR_SETPCR
comma
multiline_comment|/* Store in pointer given in ARG0 the current PCR register value&n;&t; * being used.&n;&t; */
DECL|enumerator|PERFCTR_GETPCR
id|PERFCTR_GETPCR
)brace
suffix:semicolon
multiline_comment|/* I don&squot;t want the kernel&squot;s namespace to be polluted with this&n; * stuff when this file is included.  --DaveM&n; */
macro_line|#ifndef __KERNEL__
DECL|macro|PRIV
mdefine_line|#define  PRIV 0x00000001
DECL|macro|USR
mdefine_line|#define  USR  0x00000002
DECL|macro|SYS
mdefine_line|#define  SYS  0x00000004
multiline_comment|/* Pic.S0 Selection Bit Field Encoding  */
DECL|macro|CYCLE_CNT
mdefine_line|#define  CYCLE_CNT            0x00000000
DECL|macro|INSTR_CNT
mdefine_line|#define  INSTR_CNT            0x00000010
DECL|macro|DISPATCH0_IC_MISS
mdefine_line|#define  DISPATCH0_IC_MISS    0x00000020
DECL|macro|DISPATCH0_STOREBUF
mdefine_line|#define  DISPATCH0_STOREBUF   0x00000030
DECL|macro|IC_REF
mdefine_line|#define  IC_REF               0x00000080
DECL|macro|DC_RD
mdefine_line|#define  DC_RD                0x00000090
DECL|macro|DC_WR
mdefine_line|#define  DC_WR                0x000000A0
DECL|macro|LOAD_USE
mdefine_line|#define  LOAD_USE             0x000000B0
DECL|macro|EC_REF
mdefine_line|#define  EC_REF               0x000000C0
DECL|macro|EC_WRITE_HIT_RDO
mdefine_line|#define  EC_WRITE_HIT_RDO     0x000000D0
DECL|macro|EC_SNOOP_INV
mdefine_line|#define  EC_SNOOP_INV         0x000000E0
DECL|macro|EC_RD_HIT
mdefine_line|#define  EC_RD_HIT            0x000000F0
multiline_comment|/* Pic.S1 Selection Bit Field Encoding  */
DECL|macro|CYCLE_CNT_D1
mdefine_line|#define  CYCLE_CNT_D1         0x00000000
DECL|macro|INSTR_CNT_D1
mdefine_line|#define  INSTR_CNT_D1         0x00000800
DECL|macro|DISPATCH0_IC_MISPRED
mdefine_line|#define  DISPATCH0_IC_MISPRED 0x00001000
DECL|macro|DISPATCH0_FP_USE
mdefine_line|#define  DISPATCH0_FP_USE     0x00001800
DECL|macro|IC_HIT
mdefine_line|#define  IC_HIT               0x00004000
DECL|macro|DC_RD_HIT
mdefine_line|#define  DC_RD_HIT            0x00004800
DECL|macro|DC_WR_HIT
mdefine_line|#define  DC_WR_HIT            0x00005000
DECL|macro|LOAD_USE_RAW
mdefine_line|#define  LOAD_USE_RAW         0x00005800
DECL|macro|EC_HIT
mdefine_line|#define  EC_HIT               0x00006000
DECL|macro|EC_WB
mdefine_line|#define  EC_WB                0x00006800
DECL|macro|EC_SNOOP_CB
mdefine_line|#define  EC_SNOOP_CB          0x00007000
DECL|macro|EC_IT_HIT
mdefine_line|#define  EC_IT_HIT            0x00007800
DECL|struct|vcounter_struct
r_struct
id|vcounter_struct
(brace
DECL|member|vcnt0
r_int
r_int
r_int
id|vcnt0
suffix:semicolon
DECL|member|vcnt1
r_int
r_int
r_int
id|vcnt1
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(__KERNEL__) */
macro_line|#endif /* !(PERF_COUNTER_API) */
eof
