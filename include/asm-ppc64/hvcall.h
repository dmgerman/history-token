macro_line|#ifndef _PPC64_HVCALL_H
DECL|macro|_PPC64_HVCALL_H
mdefine_line|#define _PPC64_HVCALL_H
DECL|macro|H_Success
mdefine_line|#define H_Success&t;0
DECL|macro|H_Busy
mdefine_line|#define H_Busy&t;&t;1&t;/* Hardware busy -- retry later */
DECL|macro|H_Constrained
mdefine_line|#define H_Constrained&t;4&t;/* Resource request constrained to max allowed */
DECL|macro|H_LongBusyStartRange
mdefine_line|#define H_LongBusyStartRange   9900  /* Start of long busy range */
DECL|macro|H_LongBusyOrder1msec
mdefine_line|#define H_LongBusyOrder1msec   9900  /* Long busy, hint that 1msec is a good time to retry */
DECL|macro|H_LongBusyOrder10msec
mdefine_line|#define H_LongBusyOrder10msec  9901  /* Long busy, hint that 10msec is a good time to retry */
DECL|macro|H_LongBusyOrder100msec
mdefine_line|#define H_LongBusyOrder100msec 9902  /* Long busy, hint that 100msec is a good time to retry */
DECL|macro|H_LongBusyOrder1sec
mdefine_line|#define H_LongBusyOrder1sec    9903  /* Long busy, hint that 1sec is a good time to retry */
DECL|macro|H_LongBusyOrder10sec
mdefine_line|#define H_LongBusyOrder10sec   9904  /* Long busy, hint that 10sec is a good time to retry */
DECL|macro|H_LongBusyOrder100sec
mdefine_line|#define H_LongBusyOrder100sec  9905  /* Long busy, hint that 100sec is a good time to retry */
DECL|macro|H_LongBusyEndRange
mdefine_line|#define H_LongBusyEndRange     9905  /* End of long busy range */
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
DECL|macro|H_NoMem
mdefine_line|#define H_NoMem                 -9
DECL|macro|H_Authority
mdefine_line|#define H_Authority            -10
DECL|macro|H_Permission
mdefine_line|#define H_Permission           -11
DECL|macro|H_Dropped
mdefine_line|#define H_Dropped              -12
DECL|macro|H_SourceParm
mdefine_line|#define H_SourceParm           -13
DECL|macro|H_DestParm
mdefine_line|#define H_DestParm             -14
DECL|macro|H_RemoteParm
mdefine_line|#define H_RemoteParm           -15
DECL|macro|H_Resource
mdefine_line|#define H_Resource             -16
multiline_comment|/* Long Busy is a condition that can be returned by the firmware&n; * when a call cannot be completed now, but the identical call&n; * should be retried later.  This prevents calls blocking in the&n; * firmware for long periods of time. Annoyingly the firmware can return&n; * a range of return codes, hinting at how long we should wait before&n; * retrying.  If you don&squot;t care for the hint, the macro below is a good&n; * way to check for the long_busy return codes&n; */
DECL|macro|H_isLongBusy
mdefine_line|#define H_isLongBusy(x)  ((x &gt;= H_LongBusyStartRange) &amp;&amp; (x &lt;= H_LongBusyEndRange))
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
DECL|macro|H_PERFMON
mdefine_line|#define H_PERFMON&t;&t;0x7c
DECL|macro|H_MIGRATE_DMA
mdefine_line|#define H_MIGRATE_DMA&t;&t;0x78
DECL|macro|H_REGISTER_VPA
mdefine_line|#define H_REGISTER_VPA&t;&t;0xDC
DECL|macro|H_CEDE
mdefine_line|#define H_CEDE&t;&t;        0xE0
DECL|macro|H_CONFER
mdefine_line|#define H_CONFER&t;&t;0xE4
DECL|macro|H_PROD
mdefine_line|#define H_PROD&t;&t;        0xE8
DECL|macro|H_GET_PPP
mdefine_line|#define H_GET_PPP&t;&t;0xEC
DECL|macro|H_SET_PPP
mdefine_line|#define H_SET_PPP&t;&t;0xF0
DECL|macro|H_PURR
mdefine_line|#define H_PURR&t;&t;&t;0xF4
DECL|macro|H_PIC
mdefine_line|#define H_PIC&t;&t;        0xF8
DECL|macro|H_REG_CRQ
mdefine_line|#define H_REG_CRQ&t;&t;0xFC
DECL|macro|H_FREE_CRQ
mdefine_line|#define H_FREE_CRQ&t;&t;0x100
DECL|macro|H_VIO_SIGNAL
mdefine_line|#define H_VIO_SIGNAL&t;&t;0x104
DECL|macro|H_SEND_CRQ
mdefine_line|#define H_SEND_CRQ&t;&t;0x108
DECL|macro|H_COPY_RDMA
mdefine_line|#define H_COPY_RDMA             0x110
DECL|macro|H_STUFF_TCE
mdefine_line|#define H_STUFF_TCE&t;&t;0x138
DECL|macro|H_PUT_TCE_INDIRECT
mdefine_line|#define H_PUT_TCE_INDIRECT&t;0x13C
DECL|macro|H_VTERM_PARTNER_INFO
mdefine_line|#define H_VTERM_PARTNER_INFO&t;0x150
DECL|macro|H_REGISTER_VTERM
mdefine_line|#define H_REGISTER_VTERM&t;0x154
DECL|macro|H_FREE_VTERM
mdefine_line|#define H_FREE_VTERM&t;&t;0x158
DECL|macro|H_POLL_PENDING
mdefine_line|#define H_POLL_PENDING&t;        0x1D8
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
DECL|macro|HVSC
mdefine_line|#define HVSC&t;&t;&t;&quot;.long 0x44000022&bslash;n&quot;
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
multiline_comment|/* &n; * Special hcall interface for ibmveth support.&n; * Takes 8 input parms. Returns a rc and stores the&n; * R4 return value in *out1.&n; */
r_int
id|plpar_hcall_8arg_2ret
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
id|arg5
comma
r_int
r_int
id|arg6
comma
r_int
r_int
id|arg7
comma
r_int
r_int
id|arg8
comma
r_int
r_int
op_star
id|out1
)paren
suffix:semicolon
multiline_comment|/* plpar_hcall_4out()&n; *&n; * same as plpar_hcall except with 4 output arguments.  &n; * &n; */
r_int
id|plpar_hcall_4out
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
comma
r_int
r_int
op_star
id|out4
)paren
suffix:semicolon
macro_line|#endif /* _PPC64_HVCALL_H */
eof
