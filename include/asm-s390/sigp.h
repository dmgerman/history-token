multiline_comment|/*&n; *  include/asm-s390/sigp.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  sigp.h by D.J. Barrow (c) IBM 1999&n; *  contains routines / structures for signalling other S/390 processors in an&n; *  SMP configuration.&n; */
macro_line|#ifndef __SIGP__
DECL|macro|__SIGP__
mdefine_line|#define __SIGP__
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/* get real cpu address from logical cpu number */
r_extern
r_volatile
r_int
id|__cpu_logical_map
(braket
)braket
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|sigp_unassigned
id|sigp_unassigned
op_assign
l_int|0x0
comma
DECL|enumerator|sigp_sense
id|sigp_sense
comma
DECL|enumerator|sigp_external_call
id|sigp_external_call
comma
DECL|enumerator|sigp_emergency_signal
id|sigp_emergency_signal
comma
DECL|enumerator|sigp_start
id|sigp_start
comma
DECL|enumerator|sigp_stop
id|sigp_stop
comma
DECL|enumerator|sigp_restart
id|sigp_restart
comma
DECL|enumerator|sigp_unassigned1
id|sigp_unassigned1
comma
DECL|enumerator|sigp_unassigned2
id|sigp_unassigned2
comma
DECL|enumerator|sigp_stop_and_store_status
id|sigp_stop_and_store_status
comma
DECL|enumerator|sigp_unassigned3
id|sigp_unassigned3
comma
DECL|enumerator|sigp_initial_cpu_reset
id|sigp_initial_cpu_reset
comma
DECL|enumerator|sigp_cpu_reset
id|sigp_cpu_reset
comma
DECL|enumerator|sigp_set_prefix
id|sigp_set_prefix
comma
DECL|enumerator|sigp_store_status_at_address
id|sigp_store_status_at_address
comma
DECL|enumerator|sigp_store_extended_status_at_address
id|sigp_store_extended_status_at_address
DECL|typedef|sigp_order_code
)brace
id|sigp_order_code
suffix:semicolon
DECL|typedef|sigp_status_word
r_typedef
id|__u32
id|sigp_status_word
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|sigp_order_code_accepted
id|sigp_order_code_accepted
op_assign
l_int|0
comma
DECL|enumerator|sigp_status_stored
id|sigp_status_stored
comma
DECL|enumerator|sigp_busy
id|sigp_busy
comma
DECL|enumerator|sigp_not_operational
id|sigp_not_operational
DECL|typedef|sigp_ccode
)brace
id|sigp_ccode
suffix:semicolon
multiline_comment|/*&n; * Definitions for the external call&n; */
multiline_comment|/* &squot;Bit&squot; signals, asynchronous */
r_typedef
r_enum
(brace
DECL|enumerator|ec_schedule
id|ec_schedule
op_assign
l_int|0
comma
DECL|enumerator|ec_call_function
id|ec_call_function
comma
DECL|enumerator|ec_bit_last
id|ec_bit_last
DECL|typedef|ec_bit_sig
)brace
id|ec_bit_sig
suffix:semicolon
multiline_comment|/*&n; * Signal processor&n; */
r_extern
id|__inline__
id|sigp_ccode
DECL|function|signal_processor
id|signal_processor
c_func
(paren
id|__u16
id|cpu_addr
comma
id|sigp_order_code
id|order_code
)paren
(brace
id|sigp_ccode
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
macro_line|#ifndef __s390x__
l_string|&quot;    sr     1,1&bslash;n&quot;
multiline_comment|/* parameter=0 in gpr 1 */
l_string|&quot;    sigp   1,%1,0(%2)&bslash;n&quot;
l_string|&quot;    ipm    %0&bslash;n&quot;
l_string|&quot;    srl    %0,28&bslash;n&quot;
macro_line|#else /* __s390x__ */
l_string|&quot;    sgr    1,1&bslash;n&quot;
multiline_comment|/* parameter=0 in gpr 1 */
l_string|&quot;    sigp   1,%1,0(%2)&bslash;n&quot;
l_string|&quot;    ipm    %0&bslash;n&quot;
l_string|&quot;    srl    %0,28&quot;
macro_line|#endif /* __s390x__ */
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|__cpu_logical_map
(braket
id|cpu_addr
)braket
)paren
comma
l_string|&quot;a&quot;
(paren
id|order_code
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
multiline_comment|/*&n; * Signal processor with parameter&n; */
r_extern
id|__inline__
id|sigp_ccode
DECL|function|signal_processor_p
id|signal_processor_p
c_func
(paren
r_int
r_int
id|parameter
comma
id|__u16
id|cpu_addr
comma
id|sigp_order_code
id|order_code
)paren
(brace
id|sigp_ccode
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
macro_line|#ifndef __s390x__
l_string|&quot;    lr     1,%1&bslash;n&quot;
multiline_comment|/* parameter in gpr 1 */
l_string|&quot;    sigp   1,%2,0(%3)&bslash;n&quot;
l_string|&quot;    ipm    %0&bslash;n&quot;
l_string|&quot;    srl    %0,28&bslash;n&quot;
macro_line|#else /* __s390x__ */
l_string|&quot;    lgr    1,%1&bslash;n&quot;
multiline_comment|/* parameter in gpr 1 */
l_string|&quot;    sigp   1,%2,0(%3)&bslash;n&quot;
l_string|&quot;    ipm    %0&bslash;n&quot;
l_string|&quot;    srl    %0,28&bslash;n&quot;
macro_line|#endif /* __s390x__ */
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|parameter
)paren
comma
l_string|&quot;d&quot;
(paren
id|__cpu_logical_map
(braket
id|cpu_addr
)braket
)paren
comma
l_string|&quot;a&quot;
(paren
id|order_code
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
multiline_comment|/*&n; * Signal processor with parameter and return status&n; */
r_extern
id|__inline__
id|sigp_ccode
DECL|function|signal_processor_ps
id|signal_processor_ps
c_func
(paren
r_int
r_int
op_star
id|statusptr
comma
r_int
r_int
id|parameter
comma
id|__u16
id|cpu_addr
comma
id|sigp_order_code
id|order_code
)paren
(brace
id|sigp_ccode
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
macro_line|#ifndef __s390x__
l_string|&quot;    sr     2,2&bslash;n&quot;
multiline_comment|/* clear status so it doesn&squot;t contain rubbish if not saved. */
l_string|&quot;    lr     3,%2&bslash;n&quot;
multiline_comment|/* parameter in gpr 3 */
l_string|&quot;    sigp   2,%3,0(%4)&bslash;n&quot;
l_string|&quot;    st     2,%1&bslash;n&quot;
l_string|&quot;    ipm    %0&bslash;n&quot;
l_string|&quot;    srl    %0,28&bslash;n&quot;
macro_line|#else /* __s390x__ */
l_string|&quot;    sgr    2,2&bslash;n&quot;
multiline_comment|/* clear status so it doesn&squot;t contain rubbish if not saved. */
l_string|&quot;    lgr    3,%2&bslash;n&quot;
multiline_comment|/* parameter in gpr 3 */
l_string|&quot;    sigp   2,%3,0(%4)&bslash;n&quot;
l_string|&quot;    stg    2,%1&bslash;n&quot;
l_string|&quot;    ipm    %0&bslash;n&quot;
l_string|&quot;    srl    %0,28&bslash;n&quot;
macro_line|#endif /* __s390x__ */
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|statusptr
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|parameter
)paren
comma
l_string|&quot;d&quot;
(paren
id|__cpu_logical_map
(braket
id|cpu_addr
)braket
)paren
comma
l_string|&quot;a&quot;
(paren
id|order_code
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
macro_line|#endif /* __SIGP__ */
eof
