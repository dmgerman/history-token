macro_line|#ifndef __ASM_ALPHA_FPU_H
DECL|macro|__ASM_ALPHA_FPU_H
mdefine_line|#define __ASM_ALPHA_FPU_H
multiline_comment|/*&n; * Alpha floating-point control register defines:&n; */
DECL|macro|FPCR_DNOD
mdefine_line|#define FPCR_DNOD&t;(1UL&lt;&lt;47)&t;/* denorm INV trap disable */
DECL|macro|FPCR_DNZ
mdefine_line|#define FPCR_DNZ&t;(1UL&lt;&lt;48)&t;/* denorms to zero */
DECL|macro|FPCR_INVD
mdefine_line|#define FPCR_INVD&t;(1UL&lt;&lt;49)&t;/* invalid op disable (opt.) */
DECL|macro|FPCR_DZED
mdefine_line|#define FPCR_DZED&t;(1UL&lt;&lt;50)&t;/* division by zero disable (opt.) */
DECL|macro|FPCR_OVFD
mdefine_line|#define FPCR_OVFD&t;(1UL&lt;&lt;51)&t;/* overflow disable (optional) */
DECL|macro|FPCR_INV
mdefine_line|#define FPCR_INV&t;(1UL&lt;&lt;52)&t;/* invalid operation */
DECL|macro|FPCR_DZE
mdefine_line|#define FPCR_DZE&t;(1UL&lt;&lt;53)&t;/* division by zero */
DECL|macro|FPCR_OVF
mdefine_line|#define FPCR_OVF&t;(1UL&lt;&lt;54)&t;/* overflow */
DECL|macro|FPCR_UNF
mdefine_line|#define FPCR_UNF&t;(1UL&lt;&lt;55)&t;/* underflow */
DECL|macro|FPCR_INE
mdefine_line|#define FPCR_INE&t;(1UL&lt;&lt;56)&t;/* inexact */
DECL|macro|FPCR_IOV
mdefine_line|#define FPCR_IOV&t;(1UL&lt;&lt;57)&t;/* integer overflow */
DECL|macro|FPCR_UNDZ
mdefine_line|#define FPCR_UNDZ&t;(1UL&lt;&lt;60)&t;/* underflow to zero (opt.) */
DECL|macro|FPCR_UNFD
mdefine_line|#define FPCR_UNFD&t;(1UL&lt;&lt;61)&t;/* underflow disable (opt.) */
DECL|macro|FPCR_INED
mdefine_line|#define FPCR_INED&t;(1UL&lt;&lt;62)&t;/* inexact disable (opt.) */
DECL|macro|FPCR_SUM
mdefine_line|#define FPCR_SUM&t;(1UL&lt;&lt;63)&t;/* summary bit */
DECL|macro|FPCR_DYN_SHIFT
mdefine_line|#define FPCR_DYN_SHIFT&t;58&t;&t;/* first dynamic rounding mode bit */
DECL|macro|FPCR_DYN_CHOPPED
mdefine_line|#define FPCR_DYN_CHOPPED (0x0UL &lt;&lt; FPCR_DYN_SHIFT)&t;/* towards 0 */
DECL|macro|FPCR_DYN_MINUS
mdefine_line|#define FPCR_DYN_MINUS&t; (0x1UL &lt;&lt; FPCR_DYN_SHIFT)&t;/* towards -INF */
DECL|macro|FPCR_DYN_NORMAL
mdefine_line|#define FPCR_DYN_NORMAL&t; (0x2UL &lt;&lt; FPCR_DYN_SHIFT)&t;/* towards nearest */
DECL|macro|FPCR_DYN_PLUS
mdefine_line|#define FPCR_DYN_PLUS&t; (0x3UL &lt;&lt; FPCR_DYN_SHIFT)&t;/* towards +INF */
DECL|macro|FPCR_DYN_MASK
mdefine_line|#define FPCR_DYN_MASK&t; (0x3UL &lt;&lt; FPCR_DYN_SHIFT)
DECL|macro|FPCR_MASK
mdefine_line|#define FPCR_MASK&t;0xffff800000000000
multiline_comment|/*&n; * IEEE trap enables are implemented in software.  These per-thread&n; * bits are stored in the &quot;flags&quot; field of &quot;struct thread_struct&quot;.&n; * Thus, the bits are defined so as not to conflict with the&n; * floating-point enable bit (which is architected).  On top of that,&n; * we want to make these bits compatible with OSF/1 so&n; * ieee_set_fp_control() etc. can be implemented easily and&n; * compatibly.  The corresponding definitions are in&n; * /usr/include/machine/fpu.h under OSF/1.&n; */
DECL|macro|IEEE_TRAP_ENABLE_INV
mdefine_line|#define IEEE_TRAP_ENABLE_INV&t;(1UL&lt;&lt;1)&t;/* invalid op */
DECL|macro|IEEE_TRAP_ENABLE_DZE
mdefine_line|#define IEEE_TRAP_ENABLE_DZE&t;(1UL&lt;&lt;2)&t;/* division by zero */
DECL|macro|IEEE_TRAP_ENABLE_OVF
mdefine_line|#define IEEE_TRAP_ENABLE_OVF&t;(1UL&lt;&lt;3)&t;/* overflow */
DECL|macro|IEEE_TRAP_ENABLE_UNF
mdefine_line|#define IEEE_TRAP_ENABLE_UNF&t;(1UL&lt;&lt;4)&t;/* underflow */
DECL|macro|IEEE_TRAP_ENABLE_INE
mdefine_line|#define IEEE_TRAP_ENABLE_INE&t;(1UL&lt;&lt;5)&t;/* inexact */
DECL|macro|IEEE_TRAP_ENABLE_DNO
mdefine_line|#define IEEE_TRAP_ENABLE_DNO&t;(1UL&lt;&lt;6)&t;/* denorm */
DECL|macro|IEEE_TRAP_ENABLE_MASK
mdefine_line|#define IEEE_TRAP_ENABLE_MASK&t;(IEEE_TRAP_ENABLE_INV | IEEE_TRAP_ENABLE_DZE |&bslash;&n;&t;&t;&t;&t; IEEE_TRAP_ENABLE_OVF | IEEE_TRAP_ENABLE_UNF |&bslash;&n;&t;&t;&t;&t; IEEE_TRAP_ENABLE_INE | IEEE_TRAP_ENABLE_DNO)
multiline_comment|/* Denorm and Underflow flushing */
DECL|macro|IEEE_MAP_DMZ
mdefine_line|#define IEEE_MAP_DMZ&t;&t;(1UL&lt;&lt;12)&t;/* Map denorm inputs to zero */
DECL|macro|IEEE_MAP_UMZ
mdefine_line|#define IEEE_MAP_UMZ&t;&t;(1UL&lt;&lt;13)&t;/* Map underflowed outputs to zero */
DECL|macro|IEEE_MAP_MASK
mdefine_line|#define IEEE_MAP_MASK&t;&t;(IEEE_MAP_DMZ | IEEE_MAP_UMZ)
multiline_comment|/* status bits coming from fpcr: */
DECL|macro|IEEE_STATUS_INV
mdefine_line|#define IEEE_STATUS_INV&t;&t;(1UL&lt;&lt;17)
DECL|macro|IEEE_STATUS_DZE
mdefine_line|#define IEEE_STATUS_DZE&t;&t;(1UL&lt;&lt;18)
DECL|macro|IEEE_STATUS_OVF
mdefine_line|#define IEEE_STATUS_OVF&t;&t;(1UL&lt;&lt;19)
DECL|macro|IEEE_STATUS_UNF
mdefine_line|#define IEEE_STATUS_UNF&t;&t;(1UL&lt;&lt;20)
DECL|macro|IEEE_STATUS_INE
mdefine_line|#define IEEE_STATUS_INE&t;&t;(1UL&lt;&lt;21)
DECL|macro|IEEE_STATUS_DNO
mdefine_line|#define IEEE_STATUS_DNO&t;&t;(1UL&lt;&lt;22)
DECL|macro|IEEE_STATUS_MASK
mdefine_line|#define IEEE_STATUS_MASK&t;(IEEE_STATUS_INV | IEEE_STATUS_DZE |&t;&bslash;&n;&t;&t;&t;&t; IEEE_STATUS_OVF | IEEE_STATUS_UNF |&t;&bslash;&n;&t;&t;&t;&t; IEEE_STATUS_INE | IEEE_STATUS_DNO)
DECL|macro|IEEE_SW_MASK
mdefine_line|#define IEEE_SW_MASK&t;&t;(IEEE_TRAP_ENABLE_MASK |&t;&t;&bslash;&n;&t;&t;&t;&t; IEEE_STATUS_MASK | IEEE_MAP_MASK)
DECL|macro|IEEE_CURRENT_RM_SHIFT
mdefine_line|#define IEEE_CURRENT_RM_SHIFT&t;32
DECL|macro|IEEE_CURRENT_RM_MASK
mdefine_line|#define IEEE_CURRENT_RM_MASK&t;(3UL&lt;&lt;IEEE_CURRENT_RM_SHIFT)
DECL|macro|IEEE_STATUS_TO_EXCSUM_SHIFT
mdefine_line|#define IEEE_STATUS_TO_EXCSUM_SHIFT&t;16
DECL|macro|IEEE_INHERIT
mdefine_line|#define IEEE_INHERIT    (1UL&lt;&lt;63)&t;/* inherit on thread create? */
multiline_comment|/*&n; * Convert the software IEEE trap enable and status bits into the&n; * hardware fpcr format. &n; *&n; * Digital Unix engineers receive my thanks for not defining the&n; * software bits identical to the hardware bits.  The chip designers&n; * receive my thanks for making all the not-implemented fpcr bits&n; * RAZ forcing us to use system calls to read/write this value.&n; */
r_static
r_inline
r_int
r_int
DECL|function|ieee_swcr_to_fpcr
id|ieee_swcr_to_fpcr
c_func
(paren
r_int
r_int
id|sw
)paren
(brace
r_int
r_int
id|fp
suffix:semicolon
id|fp
op_assign
(paren
id|sw
op_amp
id|IEEE_STATUS_MASK
)paren
op_lshift
l_int|35
suffix:semicolon
id|fp
op_or_assign
(paren
id|sw
op_amp
id|IEEE_MAP_DMZ
)paren
op_lshift
l_int|36
suffix:semicolon
id|fp
op_or_assign
(paren
id|sw
op_amp
id|IEEE_STATUS_MASK
ques
c_cond
id|FPCR_SUM
suffix:colon
l_int|0
)paren
suffix:semicolon
id|fp
op_or_assign
(paren
op_complement
id|sw
op_amp
(paren
id|IEEE_TRAP_ENABLE_INV
op_or
id|IEEE_TRAP_ENABLE_DZE
op_or
id|IEEE_TRAP_ENABLE_OVF
)paren
)paren
op_lshift
l_int|48
suffix:semicolon
id|fp
op_or_assign
(paren
op_complement
id|sw
op_amp
(paren
id|IEEE_TRAP_ENABLE_UNF
op_or
id|IEEE_TRAP_ENABLE_INE
)paren
)paren
op_lshift
l_int|57
suffix:semicolon
id|fp
op_or_assign
(paren
id|sw
op_amp
id|IEEE_MAP_UMZ
ques
c_cond
id|FPCR_UNDZ
op_or
id|FPCR_UNFD
suffix:colon
l_int|0
)paren
suffix:semicolon
id|fp
op_or_assign
(paren
op_complement
id|sw
op_amp
id|IEEE_TRAP_ENABLE_DNO
)paren
op_lshift
l_int|41
suffix:semicolon
r_return
id|fp
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|ieee_fpcr_to_swcr
id|ieee_fpcr_to_swcr
c_func
(paren
r_int
r_int
id|fp
)paren
(brace
r_int
r_int
id|sw
suffix:semicolon
id|sw
op_assign
(paren
id|fp
op_rshift
l_int|35
)paren
op_amp
id|IEEE_STATUS_MASK
suffix:semicolon
id|sw
op_or_assign
(paren
id|fp
op_rshift
l_int|36
)paren
op_amp
id|IEEE_MAP_DMZ
suffix:semicolon
id|sw
op_or_assign
(paren
op_complement
id|fp
op_rshift
l_int|48
)paren
op_amp
(paren
id|IEEE_TRAP_ENABLE_INV
op_or
id|IEEE_TRAP_ENABLE_DZE
op_or
id|IEEE_TRAP_ENABLE_OVF
)paren
suffix:semicolon
id|sw
op_or_assign
(paren
op_complement
id|fp
op_rshift
l_int|57
)paren
op_amp
(paren
id|IEEE_TRAP_ENABLE_UNF
op_or
id|IEEE_TRAP_ENABLE_INE
)paren
suffix:semicolon
id|sw
op_or_assign
(paren
id|fp
op_rshift
l_int|47
)paren
op_amp
id|IEEE_MAP_UMZ
suffix:semicolon
id|sw
op_or_assign
(paren
op_complement
id|fp
op_rshift
l_int|41
)paren
op_amp
id|IEEE_TRAP_ENABLE_DNO
suffix:semicolon
r_return
id|sw
suffix:semicolon
)brace
macro_line|#ifdef __KERNEL__
multiline_comment|/* The following two functions don&squot;t need trapb/excb instructions&n;   around the mf_fpcr/mt_fpcr instructions because (a) the kernel&n;   never generates arithmetic faults and (b) call_pal instructions&n;   are implied trap barriers.  */
r_static
r_inline
r_int
r_int
DECL|function|rdfpcr
id|rdfpcr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmp
comma
id|ret
suffix:semicolon
macro_line|#if defined(__alpha_cix__) || defined(__alpha_fix__)
id|__asm__
id|__volatile__
(paren
l_string|&quot;ftoit $f0,%0&bslash;n&bslash;t&quot;
l_string|&quot;mf_fpcr $f0&bslash;n&bslash;t&quot;
l_string|&quot;ftoit $f0,%1&bslash;n&bslash;t&quot;
l_string|&quot;itoft %0,$f0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|ret
)paren
)paren
suffix:semicolon
macro_line|#else
id|__asm__
id|__volatile__
(paren
l_string|&quot;stt $f0,%0&bslash;n&bslash;t&quot;
l_string|&quot;mf_fpcr $f0&bslash;n&bslash;t&quot;
l_string|&quot;stt $f0,%1&bslash;n&bslash;t&quot;
l_string|&quot;ldt $f0,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|ret
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|wrfpcr
id|wrfpcr
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
macro_line|#if defined(__alpha_cix__) || defined(__alpha_fix__)
id|__asm__
id|__volatile__
(paren
l_string|&quot;ftoit $f0,%0&bslash;n&bslash;t&quot;
l_string|&quot;itoft %1,$f0&bslash;n&bslash;t&quot;
l_string|&quot;mt_fpcr $f0&bslash;n&bslash;t&quot;
l_string|&quot;itoft %0,$f0&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
macro_line|#else
id|__asm__
id|__volatile__
(paren
l_string|&quot;stt $f0,%0&bslash;n&bslash;t&quot;
l_string|&quot;ldt $f0,%1&bslash;n&bslash;t&quot;
l_string|&quot;mt_fpcr $f0&bslash;n&bslash;t&quot;
l_string|&quot;ldt $f0,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_inline
r_int
r_int
DECL|function|swcr_update_status
id|swcr_update_status
c_func
(paren
r_int
r_int
id|swcr
comma
r_int
r_int
id|fpcr
)paren
(brace
multiline_comment|/* EV6 implements most of the bits in hardware.  Collect&n;&t;   the acrued exception bits from the real fpcr.  */
r_if
c_cond
(paren
id|implver
c_func
(paren
)paren
op_eq
id|IMPLVER_EV6
)paren
(brace
id|swcr
op_and_assign
op_complement
id|IEEE_STATUS_MASK
suffix:semicolon
id|swcr
op_or_assign
(paren
id|fpcr
op_rshift
l_int|35
)paren
op_amp
id|IEEE_STATUS_MASK
suffix:semicolon
)brace
r_return
id|swcr
suffix:semicolon
)brace
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
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_ALPHA_FPU_H */
eof
