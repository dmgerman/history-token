macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;sfp-util.h&quot;
macro_line|#include &lt;math-emu/soft-fp.h&gt;
macro_line|#include &lt;math-emu/single.h&gt;
macro_line|#include &lt;math-emu/double.h&gt;
DECL|macro|OPC_PAL
mdefine_line|#define&t;OPC_PAL&t;&t;0x00
DECL|macro|OPC_INTA
mdefine_line|#define OPC_INTA&t;0x10
DECL|macro|OPC_INTL
mdefine_line|#define OPC_INTL&t;0x11
DECL|macro|OPC_INTS
mdefine_line|#define OPC_INTS&t;0x12
DECL|macro|OPC_INTM
mdefine_line|#define OPC_INTM&t;0x13
DECL|macro|OPC_FLTC
mdefine_line|#define OPC_FLTC&t;0x14
DECL|macro|OPC_FLTV
mdefine_line|#define OPC_FLTV&t;0x15
DECL|macro|OPC_FLTI
mdefine_line|#define OPC_FLTI&t;0x16
DECL|macro|OPC_FLTL
mdefine_line|#define OPC_FLTL&t;0x17
DECL|macro|OPC_MISC
mdefine_line|#define OPC_MISC&t;0x18
DECL|macro|OPC_JSR
mdefine_line|#define&t;OPC_JSR&t;&t;0x1a
DECL|macro|FOP_SRC_S
mdefine_line|#define FOP_SRC_S&t;0
DECL|macro|FOP_SRC_T
mdefine_line|#define FOP_SRC_T&t;2
DECL|macro|FOP_SRC_Q
mdefine_line|#define FOP_SRC_Q&t;3
DECL|macro|FOP_FNC_ADDx
mdefine_line|#define FOP_FNC_ADDx&t;0
DECL|macro|FOP_FNC_CVTQL
mdefine_line|#define FOP_FNC_CVTQL&t;0
DECL|macro|FOP_FNC_SUBx
mdefine_line|#define FOP_FNC_SUBx&t;1
DECL|macro|FOP_FNC_MULx
mdefine_line|#define FOP_FNC_MULx&t;2
DECL|macro|FOP_FNC_DIVx
mdefine_line|#define FOP_FNC_DIVx&t;3
DECL|macro|FOP_FNC_CMPxUN
mdefine_line|#define FOP_FNC_CMPxUN&t;4
DECL|macro|FOP_FNC_CMPxEQ
mdefine_line|#define FOP_FNC_CMPxEQ&t;5
DECL|macro|FOP_FNC_CMPxLT
mdefine_line|#define FOP_FNC_CMPxLT&t;6
DECL|macro|FOP_FNC_CMPxLE
mdefine_line|#define FOP_FNC_CMPxLE&t;7
DECL|macro|FOP_FNC_SQRTx
mdefine_line|#define FOP_FNC_SQRTx&t;11
DECL|macro|FOP_FNC_CVTxS
mdefine_line|#define FOP_FNC_CVTxS&t;12
DECL|macro|FOP_FNC_CVTxT
mdefine_line|#define FOP_FNC_CVTxT&t;14
DECL|macro|FOP_FNC_CVTxQ
mdefine_line|#define FOP_FNC_CVTxQ&t;15
DECL|macro|MISC_TRAPB
mdefine_line|#define MISC_TRAPB&t;0x0000
DECL|macro|MISC_EXCB
mdefine_line|#define MISC_EXCB&t;0x0400
r_extern
r_int
r_int
id|alpha_read_fp_reg
(paren
r_int
r_int
id|reg
)paren
suffix:semicolon
r_extern
r_void
id|alpha_write_fp_reg
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
r_int
id|alpha_read_fp_reg_s
(paren
r_int
r_int
id|reg
)paren
suffix:semicolon
r_extern
r_void
id|alpha_write_fp_reg_s
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|val
)paren
suffix:semicolon
macro_line|#ifdef MODULE
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;FP Software completion module&quot;
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|alpha_fp_emul_imprecise
)paren
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|alpha_fp_emul
)paren
(paren
r_int
r_int
id|pc
)paren
suffix:semicolon
DECL|variable|save_emul_imprecise
r_static
r_int
(paren
op_star
id|save_emul_imprecise
)paren
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|variable|save_emul
r_static
r_int
(paren
op_star
id|save_emul
)paren
(paren
r_int
r_int
id|pc
)paren
suffix:semicolon
r_int
id|do_alpha_fp_emul_imprecise
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|do_alpha_fp_emul
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|save_emul_imprecise
op_assign
id|alpha_fp_emul_imprecise
suffix:semicolon
id|save_emul
op_assign
id|alpha_fp_emul
suffix:semicolon
id|alpha_fp_emul_imprecise
op_assign
id|do_alpha_fp_emul_imprecise
suffix:semicolon
id|alpha_fp_emul
op_assign
id|do_alpha_fp_emul
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|alpha_fp_emul_imprecise
op_assign
id|save_emul_imprecise
suffix:semicolon
id|alpha_fp_emul
op_assign
id|save_emul
suffix:semicolon
)brace
DECL|macro|alpha_fp_emul_imprecise
macro_line|#undef  alpha_fp_emul_imprecise
DECL|macro|alpha_fp_emul_imprecise
mdefine_line|#define alpha_fp_emul_imprecise&t;&t;do_alpha_fp_emul_imprecise
DECL|macro|alpha_fp_emul
macro_line|#undef  alpha_fp_emul
DECL|macro|alpha_fp_emul
mdefine_line|#define alpha_fp_emul&t;&t;&t;do_alpha_fp_emul
macro_line|#endif /* MODULE */
multiline_comment|/*&n; * Emulate the floating point instruction at address PC.  Returns -1 if the&n; * instruction to be emulated is illegal (such as with the opDEC trap), else&n; * the SI_CODE for a SIGFPE signal, else 0 if everything&squot;s ok.&n; *&n; * Notice that the kernel does not and cannot use FP regs.  This is good&n; * because it means that instead of saving/restoring all fp regs, we simply&n; * stick the result of the operation into the appropriate register.&n; */
r_int
DECL|function|alpha_fp_emul
id|alpha_fp_emul
(paren
r_int
r_int
id|pc
)paren
(brace
id|FP_DECL_EX
suffix:semicolon
id|FP_DECL_S
c_func
(paren
id|SA
)paren
suffix:semicolon
id|FP_DECL_S
c_func
(paren
id|SB
)paren
suffix:semicolon
id|FP_DECL_S
c_func
(paren
id|SR
)paren
suffix:semicolon
id|FP_DECL_D
c_func
(paren
id|DA
)paren
suffix:semicolon
id|FP_DECL_D
c_func
(paren
id|DB
)paren
suffix:semicolon
id|FP_DECL_D
c_func
(paren
id|DR
)paren
suffix:semicolon
r_int
r_int
id|fa
comma
id|fb
comma
id|fc
comma
id|func
comma
id|mode
comma
id|src
suffix:semicolon
r_int
r_int
id|res
comma
id|va
comma
id|vb
comma
id|vc
comma
id|swcr
comma
id|fpcr
suffix:semicolon
id|__u32
id|insn
suffix:semicolon
r_int
id|si_code
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|get_user
c_func
(paren
id|insn
comma
(paren
id|__u32
op_star
)paren
id|pc
)paren
suffix:semicolon
id|fc
op_assign
(paren
id|insn
op_rshift
l_int|0
)paren
op_amp
l_int|0x1f
suffix:semicolon
multiline_comment|/* destination register */
id|fb
op_assign
(paren
id|insn
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|fa
op_assign
(paren
id|insn
op_rshift
l_int|21
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|func
op_assign
(paren
id|insn
op_rshift
l_int|5
)paren
op_amp
l_int|0xf
suffix:semicolon
id|src
op_assign
(paren
id|insn
op_rshift
l_int|9
)paren
op_amp
l_int|0x3
suffix:semicolon
id|mode
op_assign
(paren
id|insn
op_rshift
l_int|11
)paren
op_amp
l_int|0x3
suffix:semicolon
id|fpcr
op_assign
id|rdfpcr
c_func
(paren
)paren
suffix:semicolon
id|swcr
op_assign
id|swcr_update_status
c_func
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|ieee_state
comma
id|fpcr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
l_int|3
)paren
(brace
multiline_comment|/* Dynamic -- get rounding mode from fpcr.  */
id|mode
op_assign
(paren
id|fpcr
op_rshift
id|FPCR_DYN_SHIFT
)paren
op_amp
l_int|3
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|src
)paren
(brace
r_case
id|FOP_SRC_S
suffix:colon
id|va
op_assign
id|alpha_read_fp_reg_s
c_func
(paren
id|fa
)paren
suffix:semicolon
id|vb
op_assign
id|alpha_read_fp_reg_s
c_func
(paren
id|fb
)paren
suffix:semicolon
id|FP_UNPACK_SP
c_func
(paren
id|SA
comma
op_amp
id|va
)paren
suffix:semicolon
id|FP_UNPACK_SP
c_func
(paren
id|SB
comma
op_amp
id|vb
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|FOP_FNC_SUBx
suffix:colon
id|FP_SUB_S
c_func
(paren
id|SR
comma
id|SA
comma
id|SB
)paren
suffix:semicolon
r_goto
id|pack_s
suffix:semicolon
r_case
id|FOP_FNC_ADDx
suffix:colon
id|FP_ADD_S
c_func
(paren
id|SR
comma
id|SA
comma
id|SB
)paren
suffix:semicolon
r_goto
id|pack_s
suffix:semicolon
r_case
id|FOP_FNC_MULx
suffix:colon
id|FP_MUL_S
c_func
(paren
id|SR
comma
id|SA
comma
id|SB
)paren
suffix:semicolon
r_goto
id|pack_s
suffix:semicolon
r_case
id|FOP_FNC_DIVx
suffix:colon
id|FP_DIV_S
c_func
(paren
id|SR
comma
id|SA
comma
id|SB
)paren
suffix:semicolon
r_goto
id|pack_s
suffix:semicolon
r_case
id|FOP_FNC_SQRTx
suffix:colon
id|FP_SQRT_S
c_func
(paren
id|SR
comma
id|SB
)paren
suffix:semicolon
r_goto
id|pack_s
suffix:semicolon
)brace
r_goto
id|bad_insn
suffix:semicolon
r_case
id|FOP_SRC_T
suffix:colon
id|va
op_assign
id|alpha_read_fp_reg
c_func
(paren
id|fa
)paren
suffix:semicolon
id|vb
op_assign
id|alpha_read_fp_reg
c_func
(paren
id|fb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|func
op_amp
op_complement
l_int|3
)paren
op_eq
id|FOP_FNC_CMPxUN
)paren
(brace
id|FP_UNPACK_RAW_DP
c_func
(paren
id|DA
comma
op_amp
id|va
)paren
suffix:semicolon
id|FP_UNPACK_RAW_DP
c_func
(paren
id|DB
comma
op_amp
id|vb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DA_e
op_logical_and
op_logical_neg
id|_FP_FRAC_ZEROP_1
c_func
(paren
id|DA
)paren
)paren
(brace
id|FP_SET_EXCEPTION
c_func
(paren
id|FP_EX_DENORM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FP_DENORM_ZERO
)paren
id|_FP_FRAC_SET_1
c_func
(paren
id|DA
comma
id|_FP_ZEROFRAC_1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|DB_e
op_logical_and
op_logical_neg
id|_FP_FRAC_ZEROP_1
c_func
(paren
id|DB
)paren
)paren
(brace
id|FP_SET_EXCEPTION
c_func
(paren
id|FP_EX_DENORM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FP_DENORM_ZERO
)paren
id|_FP_FRAC_SET_1
c_func
(paren
id|DB
comma
id|_FP_ZEROFRAC_1
)paren
suffix:semicolon
)brace
id|FP_CMP_D
c_func
(paren
id|res
comma
id|DA
comma
id|DB
comma
l_int|3
)paren
suffix:semicolon
id|vc
op_assign
l_int|0x4000000000000000
suffix:semicolon
multiline_comment|/* CMPTEQ, CMPTUN don&squot;t trap on QNaN,&n;&t;&t;&t;   while CMPTLT and CMPTLE do */
r_if
c_cond
(paren
id|res
op_eq
l_int|3
op_logical_and
(paren
(paren
id|func
op_amp
l_int|3
)paren
op_ge
l_int|2
op_logical_or
id|FP_ISSIGNAN_D
c_func
(paren
id|DA
)paren
op_logical_or
id|FP_ISSIGNAN_D
c_func
(paren
id|DB
)paren
)paren
)paren
(brace
id|FP_SET_EXCEPTION
c_func
(paren
id|FP_EX_INVALID
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|FOP_FNC_CMPxUN
suffix:colon
r_if
c_cond
(paren
id|res
op_ne
l_int|3
)paren
id|vc
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FOP_FNC_CMPxEQ
suffix:colon
r_if
c_cond
(paren
id|res
)paren
id|vc
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FOP_FNC_CMPxLT
suffix:colon
r_if
c_cond
(paren
id|res
op_ne
op_minus
l_int|1
)paren
id|vc
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FOP_FNC_CMPxLE
suffix:colon
r_if
c_cond
(paren
(paren
r_int
)paren
id|res
OG
l_int|0
)paren
id|vc
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_goto
id|done_d
suffix:semicolon
)brace
id|FP_UNPACK_DP
c_func
(paren
id|DA
comma
op_amp
id|va
)paren
suffix:semicolon
id|FP_UNPACK_DP
c_func
(paren
id|DB
comma
op_amp
id|vb
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|FOP_FNC_SUBx
suffix:colon
id|FP_SUB_D
c_func
(paren
id|DR
comma
id|DA
comma
id|DB
)paren
suffix:semicolon
r_goto
id|pack_d
suffix:semicolon
r_case
id|FOP_FNC_ADDx
suffix:colon
id|FP_ADD_D
c_func
(paren
id|DR
comma
id|DA
comma
id|DB
)paren
suffix:semicolon
r_goto
id|pack_d
suffix:semicolon
r_case
id|FOP_FNC_MULx
suffix:colon
id|FP_MUL_D
c_func
(paren
id|DR
comma
id|DA
comma
id|DB
)paren
suffix:semicolon
r_goto
id|pack_d
suffix:semicolon
r_case
id|FOP_FNC_DIVx
suffix:colon
id|FP_DIV_D
c_func
(paren
id|DR
comma
id|DA
comma
id|DB
)paren
suffix:semicolon
r_goto
id|pack_d
suffix:semicolon
r_case
id|FOP_FNC_SQRTx
suffix:colon
id|FP_SQRT_D
c_func
(paren
id|DR
comma
id|DB
)paren
suffix:semicolon
r_goto
id|pack_d
suffix:semicolon
r_case
id|FOP_FNC_CVTxS
suffix:colon
multiline_comment|/* It is irritating that DEC encoded CVTST with&n;&t;&t;&t;   SRC == T_floating.  It is also interesting that&n;&t;&t;&t;   the bit used to tell the two apart is /U... */
r_if
c_cond
(paren
id|insn
op_amp
l_int|0x2000
)paren
(brace
id|FP_CONV
c_func
(paren
id|S
comma
id|D
comma
l_int|1
comma
l_int|1
comma
id|SR
comma
id|DB
)paren
suffix:semicolon
r_goto
id|pack_s
suffix:semicolon
)brace
r_else
(brace
id|vb
op_assign
id|alpha_read_fp_reg_s
c_func
(paren
id|fb
)paren
suffix:semicolon
id|FP_UNPACK_SP
c_func
(paren
id|SB
comma
op_amp
id|vb
)paren
suffix:semicolon
id|DR_c
op_assign
id|DB_c
suffix:semicolon
id|DR_s
op_assign
id|DB_s
suffix:semicolon
id|DR_e
op_assign
id|DB_e
suffix:semicolon
id|DR_f
op_assign
id|SB_f
op_lshift
(paren
l_int|52
op_minus
l_int|23
)paren
suffix:semicolon
r_goto
id|pack_d
suffix:semicolon
)brace
r_case
id|FOP_FNC_CVTxQ
suffix:colon
r_if
c_cond
(paren
id|DB_c
op_eq
id|FP_CLS_NAN
op_logical_and
(paren
id|_FP_FRAC_HIGH_RAW_D
c_func
(paren
id|DB
)paren
op_amp
id|_FP_QNANBIT_D
)paren
)paren
(brace
multiline_comment|/* AAHB Table B-2 says QNaN should not trigger INV */
id|vc
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|FP_TO_INT_ROUND_D
c_func
(paren
id|vc
comma
id|DB
comma
l_int|64
comma
l_int|2
)paren
suffix:semicolon
r_goto
id|done_d
suffix:semicolon
)brace
r_goto
id|bad_insn
suffix:semicolon
r_case
id|FOP_SRC_Q
suffix:colon
id|vb
op_assign
id|alpha_read_fp_reg
c_func
(paren
id|fb
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|FOP_FNC_CVTQL
suffix:colon
multiline_comment|/* Notice: We can get here only due to an integer&n;&t;&t;&t;   overflow.  Such overflows are reported as invalid&n;&t;&t;&t;   ops.  We return the result the hw would have&n;&t;&t;&t;   computed.  */
id|vc
op_assign
(paren
(paren
id|vb
op_amp
l_int|0xc0000000
)paren
op_lshift
l_int|32
op_or
multiline_comment|/* sign and msb */
(paren
id|vb
op_amp
l_int|0x3fffffff
)paren
op_lshift
l_int|29
)paren
suffix:semicolon
multiline_comment|/* rest of the int */
id|FP_SET_EXCEPTION
(paren
id|FP_EX_INVALID
)paren
suffix:semicolon
r_goto
id|done_d
suffix:semicolon
r_case
id|FOP_FNC_CVTxS
suffix:colon
id|FP_FROM_INT_S
c_func
(paren
id|SR
comma
(paren
(paren
r_int
)paren
id|vb
)paren
comma
l_int|64
comma
r_int
)paren
suffix:semicolon
r_goto
id|pack_s
suffix:semicolon
r_case
id|FOP_FNC_CVTxT
suffix:colon
id|FP_FROM_INT_D
c_func
(paren
id|DR
comma
(paren
(paren
r_int
)paren
id|vb
)paren
comma
l_int|64
comma
r_int
)paren
suffix:semicolon
r_goto
id|pack_d
suffix:semicolon
)brace
r_goto
id|bad_insn
suffix:semicolon
)brace
r_goto
id|bad_insn
suffix:semicolon
id|pack_s
suffix:colon
id|FP_PACK_SP
c_func
(paren
op_amp
id|vc
comma
id|SR
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|_fex
op_amp
id|FP_EX_UNDERFLOW
)paren
op_logical_and
(paren
id|swcr
op_amp
id|IEEE_MAP_UMZ
)paren
)paren
id|vc
op_assign
l_int|0
suffix:semicolon
id|alpha_write_fp_reg_s
c_func
(paren
id|fc
comma
id|vc
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
id|pack_d
suffix:colon
id|FP_PACK_DP
c_func
(paren
op_amp
id|vc
comma
id|DR
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|_fex
op_amp
id|FP_EX_UNDERFLOW
)paren
op_logical_and
(paren
id|swcr
op_amp
id|IEEE_MAP_UMZ
)paren
)paren
id|vc
op_assign
l_int|0
suffix:semicolon
id|done_d
suffix:colon
id|alpha_write_fp_reg
c_func
(paren
id|fc
comma
id|vc
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
multiline_comment|/*&n;&t; * Take the appropriate action for each possible&n;&t; * floating-point result:&n;&t; *&n;&t; *&t;- Set the appropriate bits in the FPCR&n;&t; *&t;- If the specified exception is enabled in the FPCR,&n;&t; *&t;  return.  The caller (entArith) will dispatch&n;&t; *&t;  the appropriate signal to the translated program.&n;&t; *&n;&t; * In addition, properly track the exception state in software&n;&t; * as described in the Alpha Architectre Handbook section 4.7.7.3.&n;&t; */
id|done
suffix:colon
r_if
c_cond
(paren
id|_fex
)paren
(brace
multiline_comment|/* Record exceptions in software control word.  */
id|swcr
op_or_assign
(paren
id|_fex
op_lshift
id|IEEE_STATUS_TO_EXCSUM_SHIFT
)paren
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|ieee_state
op_or_assign
(paren
id|_fex
op_lshift
id|IEEE_STATUS_TO_EXCSUM_SHIFT
)paren
suffix:semicolon
multiline_comment|/* Update hardware control register.  */
id|fpcr
op_and_assign
(paren
op_complement
id|FPCR_MASK
op_or
id|FPCR_DYN_MASK
)paren
suffix:semicolon
id|fpcr
op_or_assign
id|ieee_swcr_to_fpcr
c_func
(paren
id|swcr
)paren
suffix:semicolon
id|wrfpcr
c_func
(paren
id|fpcr
)paren
suffix:semicolon
multiline_comment|/* Do we generate a signal?  */
id|_fex
op_assign
id|_fex
op_amp
id|swcr
op_amp
id|IEEE_TRAP_ENABLE_MASK
suffix:semicolon
id|si_code
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|_fex
)paren
(brace
r_if
c_cond
(paren
id|_fex
op_amp
id|IEEE_TRAP_ENABLE_DNO
)paren
id|si_code
op_assign
id|FPE_FLTUND
suffix:semicolon
r_if
c_cond
(paren
id|_fex
op_amp
id|IEEE_TRAP_ENABLE_INE
)paren
id|si_code
op_assign
id|FPE_FLTRES
suffix:semicolon
r_if
c_cond
(paren
id|_fex
op_amp
id|IEEE_TRAP_ENABLE_UNF
)paren
id|si_code
op_assign
id|FPE_FLTUND
suffix:semicolon
r_if
c_cond
(paren
id|_fex
op_amp
id|IEEE_TRAP_ENABLE_OVF
)paren
id|si_code
op_assign
id|FPE_FLTOVF
suffix:semicolon
r_if
c_cond
(paren
id|_fex
op_amp
id|IEEE_TRAP_ENABLE_DZE
)paren
id|si_code
op_assign
id|FPE_FLTDIV
suffix:semicolon
r_if
c_cond
(paren
id|_fex
op_amp
id|IEEE_TRAP_ENABLE_INV
)paren
id|si_code
op_assign
id|FPE_FLTINV
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|si_code
suffix:semicolon
)brace
multiline_comment|/* We used to write the destination register here, but DEC FORTRAN&n;&t;   requires that the result *always* be written... so we do the write&n;&t;   immediately after the operations above.  */
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bad_insn
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;alpha_fp_emul: Invalid FP insn %#x at %#lx&bslash;n&quot;
comma
id|insn
comma
id|pc
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|alpha_fp_emul_imprecise
id|alpha_fp_emul_imprecise
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|write_mask
)paren
(brace
r_int
r_int
id|trigger_pc
op_assign
id|regs-&gt;pc
op_minus
l_int|4
suffix:semicolon
r_int
r_int
id|insn
comma
id|opcode
comma
id|rc
comma
id|si_code
op_assign
l_int|0
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
multiline_comment|/*&n;&t; * Turn off the bits corresponding to registers that are the&n;&t; * target of instructions that set bits in the exception&n;&t; * summary register.  We have some slack doing this because a&n;&t; * register that is the target of a trapping instruction can&n;&t; * be written at most once in the trap shadow.&n;&t; *&n;&t; * Branches, jumps, TRAPBs, EXCBs and calls to PALcode all&n;&t; * bound the trap shadow, so we need not look any further than&n;&t; * up to the first occurrence of such an instruction.&n;&t; */
r_while
c_loop
(paren
id|write_mask
)paren
(brace
id|get_user
c_func
(paren
id|insn
comma
(paren
id|__u32
op_star
)paren
(paren
id|trigger_pc
)paren
)paren
suffix:semicolon
id|opcode
op_assign
id|insn
op_rshift
l_int|26
suffix:semicolon
id|rc
op_assign
id|insn
op_amp
l_int|0x1f
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|OPC_PAL
suffix:colon
r_case
id|OPC_JSR
suffix:colon
r_case
l_int|0x30
dot
dot
dot
l_int|0x3f
suffix:colon
multiline_comment|/* branches */
r_goto
id|egress
suffix:semicolon
r_case
id|OPC_MISC
suffix:colon
r_switch
c_cond
(paren
id|insn
op_amp
l_int|0xffff
)paren
(brace
r_case
id|MISC_TRAPB
suffix:colon
r_case
id|MISC_EXCB
suffix:colon
r_goto
id|egress
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|OPC_INTA
suffix:colon
r_case
id|OPC_INTL
suffix:colon
r_case
id|OPC_INTS
suffix:colon
r_case
id|OPC_INTM
suffix:colon
id|write_mask
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
id|rc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPC_FLTC
suffix:colon
r_case
id|OPC_FLTV
suffix:colon
r_case
id|OPC_FLTI
suffix:colon
r_case
id|OPC_FLTL
suffix:colon
id|write_mask
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
(paren
id|rc
op_plus
l_int|32
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|write_mask
)paren
(brace
multiline_comment|/* Re-execute insns in the trap-shadow.  */
id|regs-&gt;pc
op_assign
id|trigger_pc
op_plus
l_int|4
suffix:semicolon
id|si_code
op_assign
id|alpha_fp_emul
c_func
(paren
id|trigger_pc
)paren
suffix:semicolon
r_goto
id|egress
suffix:semicolon
)brace
id|trigger_pc
op_sub_assign
l_int|4
suffix:semicolon
)brace
id|egress
suffix:colon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|si_code
suffix:semicolon
)brace
eof
