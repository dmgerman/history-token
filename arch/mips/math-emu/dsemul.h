DECL|typedef|vaddr_t
r_typedef
r_void
op_star
id|vaddr_t
suffix:semicolon
DECL|macro|REG_TO_VA
mdefine_line|#define REG_TO_VA (vaddr_t)
DECL|macro|VA_TO_REG
mdefine_line|#define VA_TO_REG (gpreg_t)
r_int
id|mips_dsemul
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|mips_instruction
id|ir
comma
id|gpreg_t
id|cpc
)paren
suffix:semicolon
r_int
id|do_dsemulret
c_func
(paren
r_struct
id|pt_regs
op_star
id|xcp
)paren
suffix:semicolon
multiline_comment|/* Instruction which will always cause an address error */
DECL|macro|AdELOAD
mdefine_line|#define AdELOAD 0x8c000001&t;/* lw $0,1($0) */
multiline_comment|/* Instruction which will plainly cause a CP1 exception when FPU is disabled */
DECL|macro|CP1UNDEF
mdefine_line|#define CP1UNDEF 0x44400001    /* cfc1 $0,$0 undef  */
multiline_comment|/* Instruction inserted following the badinst to further tag the sequence */
DECL|macro|BD_COOKIE
mdefine_line|#define BD_COOKIE 0x0000bd36 /* tne $0,$0 with baggage */
multiline_comment|/* Setup which instruction to use for trampoline */
macro_line|#ifdef STANDALONE_EMULATOR
DECL|macro|BADINST
mdefine_line|#define BADINST CP1UNDEF
macro_line|#else
DECL|macro|BADINST
mdefine_line|#define BADINST AdELOAD
macro_line|#endif
eof
