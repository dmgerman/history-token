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
DECL|macro|SYS
mdefine_line|#define  SYS  0x00000002
DECL|macro|USR
mdefine_line|#define  USR  0x00000004
multiline_comment|/* Pic.S0 Selection Bit Field Encoding, Ultra-I/II  */
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
multiline_comment|/* Pic.S0 Selection Bit Field Encoding, Ultra-III  */
DECL|macro|US3_CYCLE_CNT
mdefine_line|#define  US3_CYCLE_CNT&t;      &t;0x00000000
DECL|macro|US3_INSTR_CNT
mdefine_line|#define  US3_INSTR_CNT&t;      &t;0x00000010
DECL|macro|US3_DISPATCH0_IC_MISS
mdefine_line|#define  US3_DISPATCH0_IC_MISS&t;0x00000020
DECL|macro|US3_DISPATCH0_BR_TGT
mdefine_line|#define  US3_DISPATCH0_BR_TGT&t;0x00000030
DECL|macro|US3_DISPATCH0_2ND_BR
mdefine_line|#define  US3_DISPATCH0_2ND_BR&t;0x00000040
DECL|macro|US3_RSTALL_STOREQ
mdefine_line|#define  US3_RSTALL_STOREQ&t;0x00000050
DECL|macro|US3_RSTALL_IU_USE
mdefine_line|#define  US3_RSTALL_IU_USE&t;0x00000060
DECL|macro|US3_IC_REF
mdefine_line|#define  US3_IC_REF&t;&t;0x00000080
DECL|macro|US3_DC_RD
mdefine_line|#define  US3_DC_RD&t;&t;0x00000090
DECL|macro|US3_DC_WR
mdefine_line|#define  US3_DC_WR&t;&t;0x000000a0
DECL|macro|US3_EC_REF
mdefine_line|#define  US3_EC_REF&t;&t;0x000000c0
DECL|macro|US3_EC_WR_HIT_RTO
mdefine_line|#define  US3_EC_WR_HIT_RTO&t;0x000000d0
DECL|macro|US3_EC_SNOOP_INV
mdefine_line|#define  US3_EC_SNOOP_INV&t;0x000000e0
DECL|macro|US3_EC_RD_MISS
mdefine_line|#define  US3_EC_RD_MISS&t;&t;0x000000f0
DECL|macro|US3_PC_PORT0_RD
mdefine_line|#define  US3_PC_PORT0_RD&t;0x00000100
DECL|macro|US3_SI_SNOOP
mdefine_line|#define  US3_SI_SNOOP&t;&t;0x00000110
DECL|macro|US3_SI_CIQ_FLOW
mdefine_line|#define  US3_SI_CIQ_FLOW&t;0x00000120
DECL|macro|US3_SI_OWNED
mdefine_line|#define  US3_SI_OWNED&t;&t;0x00000130
DECL|macro|US3_SW_COUNT_0
mdefine_line|#define  US3_SW_COUNT_0&t;&t;0x00000140
DECL|macro|US3_IU_BR_MISS_TAKEN
mdefine_line|#define  US3_IU_BR_MISS_TAKEN&t;0x00000150
DECL|macro|US3_IU_BR_COUNT_TAKEN
mdefine_line|#define  US3_IU_BR_COUNT_TAKEN&t;0x00000160
DECL|macro|US3_DISP_RS_MISPRED
mdefine_line|#define  US3_DISP_RS_MISPRED&t;0x00000170
DECL|macro|US3_FA_PIPE_COMPL
mdefine_line|#define  US3_FA_PIPE_COMPL&t;0x00000180
DECL|macro|US3_MC_READS_0
mdefine_line|#define  US3_MC_READS_0&t;&t;0x00000200
DECL|macro|US3_MC_READS_1
mdefine_line|#define  US3_MC_READS_1&t;&t;0x00000210
DECL|macro|US3_MC_READS_2
mdefine_line|#define  US3_MC_READS_2&t;&t;0x00000220
DECL|macro|US3_MC_READS_3
mdefine_line|#define  US3_MC_READS_3&t;&t;0x00000230
DECL|macro|US3_MC_STALLS_0
mdefine_line|#define  US3_MC_STALLS_0&t;0x00000240
DECL|macro|US3_MC_STALLS_2
mdefine_line|#define  US3_MC_STALLS_2&t;0x00000250
multiline_comment|/* Pic.S1 Selection Bit Field Encoding, Ultra-I/II  */
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
multiline_comment|/* Pic.S1 Selection Bit Field Encoding, Ultra-III  */
DECL|macro|US3_CYCLE_CNT_D1
mdefine_line|#define  US3_CYCLE_CNT_D1&t;0x00000000
DECL|macro|US3_INSTR_CNT_D1
mdefine_line|#define  US3_INSTR_CNT_D1&t;0x00000800
DECL|macro|US3_DISPATCH0_MISPRED
mdefine_line|#define  US3_DISPATCH0_MISPRED&t;0x00001000
DECL|macro|US3_IC_MISS_CANCELLED
mdefine_line|#define  US3_IC_MISS_CANCELLED&t;0x00001800
DECL|macro|US3_RE_ENDIAN_MISS
mdefine_line|#define  US3_RE_ENDIAN_MISS&t;0x00002000
DECL|macro|US3_RE_FPU_BYPASS
mdefine_line|#define  US3_RE_FPU_BYPASS&t;0x00002800
DECL|macro|US3_RE_DC_MISS
mdefine_line|#define  US3_RE_DC_MISS&t;&t;0x00003000
DECL|macro|US3_RE_EC_MISS
mdefine_line|#define  US3_RE_EC_MISS&t;&t;0x00003800
DECL|macro|US3_IC_MISS
mdefine_line|#define  US3_IC_MISS&t;&t;0x00004000
DECL|macro|US3_DC_RD_MISS
mdefine_line|#define  US3_DC_RD_MISS&t;&t;0x00004800
DECL|macro|US3_DC_WR_MISS
mdefine_line|#define  US3_DC_WR_MISS&t;&t;0x00005000
DECL|macro|US3_RSTALL_FP_USE
mdefine_line|#define  US3_RSTALL_FP_USE&t;0x00005800
DECL|macro|US3_EC_MISSES
mdefine_line|#define  US3_EC_MISSES&t;&t;0x00006000
DECL|macro|US3_EC_WB
mdefine_line|#define  US3_EC_WB&t;&t;0x00006800
DECL|macro|US3_EC_SNOOP_CB
mdefine_line|#define  US3_EC_SNOOP_CB&t;0x00007000
DECL|macro|US3_EC_IC_MISS
mdefine_line|#define  US3_EC_IC_MISS&t;&t;0x00007800
DECL|macro|US3_RE_PC_MISS
mdefine_line|#define  US3_RE_PC_MISS&t;&t;0x00008000
DECL|macro|US3_ITLB_MISS
mdefine_line|#define  US3_ITLB_MISS&t;&t;0x00008800
DECL|macro|US3_DTLB_MISS
mdefine_line|#define  US3_DTLB_MISS&t;&t;0x00009000
DECL|macro|US3_WC_MISS
mdefine_line|#define  US3_WC_MISS&t;&t;0x00009800
DECL|macro|US3_WC_SNOOP_CB
mdefine_line|#define  US3_WC_SNOOP_CB&t;0x0000a000
DECL|macro|US3_WC_SCRUBBED
mdefine_line|#define  US3_WC_SCRUBBED&t;0x0000a800
DECL|macro|US3_WC_WB_WO_READ
mdefine_line|#define  US3_WC_WB_WO_READ&t;0x0000b000
DECL|macro|US3_PC_SOFT_HIT
mdefine_line|#define  US3_PC_SOFT_HIT&t;0x0000c000
DECL|macro|US3_PC_SNOOP_INV
mdefine_line|#define  US3_PC_SNOOP_INV&t;0x0000c800
DECL|macro|US3_PC_HARD_HIT
mdefine_line|#define  US3_PC_HARD_HIT&t;0x0000d000
DECL|macro|US3_PC_PORT1_RD
mdefine_line|#define  US3_PC_PORT1_RD&t;0x0000d800
DECL|macro|US3_SW_COUNT_1
mdefine_line|#define  US3_SW_COUNT_1&t;&t;0x0000e000
DECL|macro|US3_IU_STAT_BR_MIS_UNTAKEN
mdefine_line|#define  US3_IU_STAT_BR_MIS_UNTAKEN&t;0x0000e800
DECL|macro|US3_IU_STAT_BR_COUNT_UNTAKEN
mdefine_line|#define  US3_IU_STAT_BR_COUNT_UNTAKEN&t;0x0000f000
DECL|macro|US3_PC_MS_MISSES
mdefine_line|#define  US3_PC_MS_MISSES&t;0x0000f800
DECL|macro|US3_MC_WRITES_0
mdefine_line|#define  US3_MC_WRITES_0&t;0x00010800
DECL|macro|US3_MC_WRITES_1
mdefine_line|#define  US3_MC_WRITES_1&t;0x00011000
DECL|macro|US3_MC_WRITES_2
mdefine_line|#define  US3_MC_WRITES_2&t;0x00011800
DECL|macro|US3_MC_WRITES_3
mdefine_line|#define  US3_MC_WRITES_3&t;0x00012000
DECL|macro|US3_MC_STALLS_1
mdefine_line|#define  US3_MC_STALLS_1&t;0x00012800
DECL|macro|US3_MC_STALLS_3
mdefine_line|#define  US3_MC_STALLS_3&t;0x00013000
DECL|macro|US3_RE_RAW_MISS
mdefine_line|#define  US3_RE_RAW_MISS&t;0x00013800
DECL|macro|US3_FM_PIPE_COMPLETION
mdefine_line|#define  US3_FM_PIPE_COMPLETION&t;0x00014000
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
