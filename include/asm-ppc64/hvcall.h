DECL|macro|H_Success
mdefine_line|#define H_Success&t;0
DECL|macro|H_Busy
mdefine_line|#define H_Busy&t;&t;1&t;/* Hardware busy -- retry later */
DECL|macro|H_Hardware
mdefine_line|#define H_Hardware&t;-1&t;/* Hardware error */
DECL|macro|H_Function
mdefine_line|#define H_Function&t;-2&t;/* Function not supported */
DECL|macro|H_Privilege
mdefine_line|#define H_Privilege&t;-3&t;/* Caller not privileged */
DECL|macro|H_Parameter
mdefine_line|#define H_Parameter&t;-4&t;/* Parameter invalid, out-of-range or conflicting */
DECL|macro|H_Bad_Mode
mdefine_line|#define H_Bad_Mode&t;-5&t;/* Illegal msr value */
DECL|macro|H_PTEG_Full
mdefine_line|#define H_PTEG_Full&t;-6&t;/* PTEG is full */
DECL|macro|H_Not_Found
mdefine_line|#define H_Not_Found&t;-7&t;/* PTE was not found&quot; */
DECL|macro|H_Reserved_DABR
mdefine_line|#define H_Reserved_DABR&t;-8&t;/* DABR address is reserved by the hypervisor on this processor&quot; */
multiline_comment|/* Flags */
DECL|macro|H_LARGE_PAGE
mdefine_line|#define H_LARGE_PAGE&t;&t;(1UL&lt;&lt;(63-16))
DECL|macro|H_EXACT
mdefine_line|#define H_EXACT&t;&t;    (1UL&lt;&lt;(63-24))&t;/* Use exact PTE or return H_PTEG_FULL */
DECL|macro|H_R_XLATE
mdefine_line|#define H_R_XLATE&t;&t;(1UL&lt;&lt;(63-25))&t;/* include a valid logical page num in the pte if the valid bit is set */
DECL|macro|H_READ_4
mdefine_line|#define H_READ_4&t;&t;(1UL&lt;&lt;(63-26))&t;/* Return 4 PTEs */
DECL|macro|H_AVPN
mdefine_line|#define H_AVPN&t;&t;&t;(1UL&lt;&lt;(63-32))&t;/* An avpn is provided as a sanity test */
DECL|macro|H_ANDCOND
mdefine_line|#define H_ANDCOND&t;&t;(1UL&lt;&lt;(63-33))
DECL|macro|H_ICACHE_INVALIDATE
mdefine_line|#define H_ICACHE_INVALIDATE&t;(1UL&lt;&lt;(63-40))&t;/* icbi, etc.  (ignored for IO pages) */
DECL|macro|H_ICACHE_SYNCHRONIZE
mdefine_line|#define H_ICACHE_SYNCHRONIZE&t;(1UL&lt;&lt;(63-41))&t;/* dcbst, icbi, etc (ignored for IO pages */
DECL|macro|H_ZERO_PAGE
mdefine_line|#define H_ZERO_PAGE&t;&t;(1UL&lt;&lt;(63-48))&t;/* zero the page before mapping (ignored for IO pages) */
DECL|macro|H_COPY_PAGE
mdefine_line|#define H_COPY_PAGE&t;&t;(1UL&lt;&lt;(63-49))
DECL|macro|H_N
mdefine_line|#define H_N&t;&t;&t;(1UL&lt;&lt;(63-61))
DECL|macro|H_PP1
mdefine_line|#define H_PP1&t;&t;&t;(1UL&lt;&lt;(63-62))
DECL|macro|H_PP2
mdefine_line|#define H_PP2&t;&t;&t;(1UL&lt;&lt;(63-63))
multiline_comment|/* pSeries hypervisor opcodes */
DECL|macro|H_REMOVE
mdefine_line|#define H_REMOVE&t;&t;0x04
DECL|macro|H_ENTER
mdefine_line|#define H_ENTER&t;&t;&t;0x08
DECL|macro|H_READ
mdefine_line|#define H_READ&t;&t;&t;0x0c
DECL|macro|H_CLEAR_MOD
mdefine_line|#define H_CLEAR_MOD&t;&t;0x10
DECL|macro|H_CLEAR_REF
mdefine_line|#define H_CLEAR_REF&t;&t;0x14
DECL|macro|H_PROTECT
mdefine_line|#define H_PROTECT&t;&t;0x18
DECL|macro|H_GET_TCE
mdefine_line|#define H_GET_TCE&t;&t;0x1c
DECL|macro|H_PUT_TCE
mdefine_line|#define H_PUT_TCE&t;&t;0x20
DECL|macro|H_SET_SPRG0
mdefine_line|#define H_SET_SPRG0&t;&t;0x24
DECL|macro|H_SET_DABR
mdefine_line|#define H_SET_DABR&t;&t;0x28
DECL|macro|H_PAGE_INIT
mdefine_line|#define H_PAGE_INIT&t;&t;0x2c
DECL|macro|H_SET_ASR
mdefine_line|#define H_SET_ASR&t;&t;0x30
DECL|macro|H_ASR_ON
mdefine_line|#define H_ASR_ON&t;&t;0x34
DECL|macro|H_ASR_OFF
mdefine_line|#define H_ASR_OFF&t;&t;0x38
DECL|macro|H_LOGICAL_CI_LOAD
mdefine_line|#define H_LOGICAL_CI_LOAD&t;0x3c
DECL|macro|H_LOGICAL_CI_STORE
mdefine_line|#define H_LOGICAL_CI_STORE&t;0x40
DECL|macro|H_LOGICAL_CACHE_LOAD
mdefine_line|#define H_LOGICAL_CACHE_LOAD&t;0x44
DECL|macro|H_LOGICAL_CACHE_STORE
mdefine_line|#define H_LOGICAL_CACHE_STORE&t;0x48
DECL|macro|H_LOGICAL_ICBI
mdefine_line|#define H_LOGICAL_ICBI&t;&t;0x4c
DECL|macro|H_LOGICAL_DCBF
mdefine_line|#define H_LOGICAL_DCBF&t;&t;0x50
DECL|macro|H_GET_TERM_CHAR
mdefine_line|#define H_GET_TERM_CHAR&t;&t;0x54
DECL|macro|H_PUT_TERM_CHAR
mdefine_line|#define H_PUT_TERM_CHAR&t;&t;0x58
DECL|macro|H_REAL_TO_LOGICAL
mdefine_line|#define H_REAL_TO_LOGICAL&t;0x5c
DECL|macro|H_HYPERVISOR_DATA
mdefine_line|#define H_HYPERVISOR_DATA&t;0x60
DECL|macro|H_EOI
mdefine_line|#define H_EOI&t;&t;&t;0x64
DECL|macro|H_CPPR
mdefine_line|#define H_CPPR&t;&t;&t;0x68
DECL|macro|H_IPI
mdefine_line|#define H_IPI&t;&t;&t;0x6c
DECL|macro|H_IPOLL
mdefine_line|#define H_IPOLL&t;&t;&t;0x70
DECL|macro|H_XIRR
mdefine_line|#define H_XIRR&t;&t;&t;0x74
DECL|macro|HSC
mdefine_line|#define HSC&t;&t;&t;&quot;.long 0x44000022&bslash;n&quot;
DECL|macro|H_ENTER_r3
mdefine_line|#define H_ENTER_r3&t;&t;&quot;li&t;3, 0x08&bslash;n&quot;
multiline_comment|/* plpar_hcall() -- Generic call interface using above opcodes&n; *&n; * The actual call interface is a hypervisor call instruction with&n; * the opcode in R3 and input args in R4-R7.&n; * Status is returned in R3 with variable output values in R4-R11.&n; * Only H_PTE_READ with H_READ_4 uses R6-R11 so we ignore it for now&n; * and return only two out args which MUST ALWAYS BE PROVIDED.&n; */
r_int
id|plpar_hcall
c_func
(paren
r_int
r_int
id|opcode
comma
r_int
r_int
id|arg1
comma
r_int
r_int
id|arg2
comma
r_int
r_int
id|arg3
comma
r_int
r_int
id|arg4
comma
r_int
r_int
op_star
id|out1
comma
r_int
r_int
op_star
id|out2
comma
r_int
r_int
op_star
id|out3
)paren
suffix:semicolon
multiline_comment|/* Same as plpar_hcall but for those opcodes that return no values&n; * other than status.  Slightly more efficient.&n; */
r_int
id|plpar_hcall_norets
c_func
(paren
r_int
r_int
id|opcode
comma
dot
dot
dot
)paren
suffix:semicolon
eof
