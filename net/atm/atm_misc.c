multiline_comment|/* net/atm/atm_misc.c - Various functions for use by ATM drivers */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL ICA */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/sonet.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
DECL|function|atm_charge
r_int
id|atm_charge
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|truesize
)paren
(brace
id|atm_force_charge
c_func
(paren
id|vcc
comma
id|truesize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|vcc-&gt;sk-&gt;rmem_alloc
)paren
op_le
id|vcc-&gt;sk-&gt;rcvbuf
)paren
r_return
l_int|1
suffix:semicolon
id|atm_return
c_func
(paren
id|vcc
comma
id|truesize
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|vcc-&gt;stats-&gt;rx_drop
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atm_alloc_charge
r_struct
id|sk_buff
op_star
id|atm_alloc_charge
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|pdu_size
comma
r_int
id|gfp_flags
)paren
(brace
r_int
id|guess
op_assign
id|atm_guess_pdu2truesize
c_func
(paren
id|pdu_size
)paren
suffix:semicolon
id|atm_force_charge
c_func
(paren
id|vcc
comma
id|guess
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|vcc-&gt;sk-&gt;rmem_alloc
)paren
op_le
id|vcc-&gt;sk-&gt;rcvbuf
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|pdu_size
comma
id|gfp_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|atomic_add
c_func
(paren
id|skb-&gt;truesize
op_minus
id|guess
comma
op_amp
id|vcc-&gt;sk-&gt;rmem_alloc
)paren
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
)brace
id|atm_return
c_func
(paren
id|vcc
comma
id|guess
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|vcc-&gt;stats-&gt;rx_drop
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|check_ci
r_static
r_int
id|check_ci
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|vpi
comma
r_int
id|vci
)paren
(brace
r_struct
id|atm_vcc
op_star
id|walk
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|vcc-&gt;dev-&gt;vccs
suffix:semicolon
id|walk
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ATM_VF_ADDR
comma
op_amp
id|walk-&gt;flags
)paren
op_logical_and
id|walk-&gt;vpi
op_eq
id|vpi
op_logical_and
id|walk-&gt;vci
op_eq
id|vci
op_logical_and
(paren
(paren
id|walk-&gt;qos.txtp.traffic_class
op_ne
id|ATM_NONE
op_logical_and
id|vcc-&gt;qos.txtp.traffic_class
op_ne
id|ATM_NONE
)paren
op_logical_or
(paren
id|walk-&gt;qos.rxtp.traffic_class
op_ne
id|ATM_NONE
op_logical_and
id|vcc-&gt;qos.rxtp.traffic_class
op_ne
id|ATM_NONE
)paren
)paren
)paren
r_return
op_minus
id|EADDRINUSE
suffix:semicolon
multiline_comment|/* allow VCCs with same VPI/VCI iff they don&squot;t collide on&n;&t;&t;   TX/RX (but we may refuse such sharing for other reasons,&n;&t;&t;   e.g. if protocol requires to have both channels) */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atm_find_ci
r_int
id|atm_find_ci
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
op_star
id|vpi
comma
r_int
op_star
id|vci
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_static
r_int
id|p
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* poor man&squot;s per-device cache */
r_static
r_int
id|c
op_assign
l_int|0
suffix:semicolon
r_int
id|old_p
suffix:semicolon
r_int
id|old_c
suffix:semicolon
r_int
id|err
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|vcc-&gt;dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|vpi
op_ne
id|ATM_VPI_ANY
op_logical_and
op_star
id|vci
op_ne
id|ATM_VCI_ANY
)paren
(brace
id|err
op_assign
id|check_ci
c_func
(paren
id|vcc
comma
op_star
id|vpi
comma
op_star
id|vci
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|vcc-&gt;dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* last scan may have left values out of bounds for current device */
r_if
c_cond
(paren
op_star
id|vpi
op_ne
id|ATM_VPI_ANY
)paren
id|p
op_assign
op_star
id|vpi
suffix:semicolon
r_else
r_if
c_cond
(paren
id|p
op_ge
l_int|1
op_lshift
id|vcc-&gt;dev-&gt;ci_range.vpi_bits
)paren
id|p
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|vci
op_ne
id|ATM_VCI_ANY
)paren
id|c
op_assign
op_star
id|vci
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
OL
id|ATM_NOT_RSV_VCI
op_logical_or
id|c
op_ge
l_int|1
op_lshift
id|vcc-&gt;dev-&gt;ci_range.vci_bits
)paren
id|c
op_assign
id|ATM_NOT_RSV_VCI
suffix:semicolon
id|old_p
op_assign
id|p
suffix:semicolon
id|old_c
op_assign
id|c
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|check_ci
c_func
(paren
id|vcc
comma
id|p
comma
id|c
)paren
)paren
(brace
op_star
id|vpi
op_assign
id|p
suffix:semicolon
op_star
id|vci
op_assign
id|c
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|vcc-&gt;dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|vci
op_eq
id|ATM_VCI_ANY
)paren
(brace
id|c
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_int|1
op_lshift
id|vcc-&gt;dev-&gt;ci_range.vci_bits
)paren
id|c
op_assign
id|ATM_NOT_RSV_VCI
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|c
op_eq
id|ATM_NOT_RSV_VCI
op_logical_or
op_star
id|vci
op_ne
id|ATM_VCI_ANY
)paren
op_logical_and
op_star
id|vpi
op_eq
id|ATM_VPI_ANY
)paren
(brace
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ge
l_int|1
op_lshift
id|vcc-&gt;dev-&gt;ci_range.vpi_bits
)paren
id|p
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|old_p
op_ne
id|p
op_logical_or
id|old_c
op_ne
id|c
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|vcc-&gt;dev-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EADDRINUSE
suffix:semicolon
)brace
multiline_comment|/*&n; * atm_pcr_goal returns the positive PCR if it should be rounded up, the&n; * negative PCR if it should be rounded down, and zero if the maximum available&n; * bandwidth should be used.&n; *&n; * The rules are as follows (* = maximum, - = absent (0), x = value &quot;x&quot;,&n; * (x+ = x or next value above x, x- = x or next value below):&n; *&n; *&t;min max pcr&t;result&t;&t;min max pcr&t;result&n; *&t;-   -   -&t;* (UBR only)&t;x   -   -&t;x+&n; *&t;-   -   *&t;*&t;&t;x   -   *&t;*&n; *&t;-   -   z&t;z-&t;&t;x   -   z&t;z-&n; *&t;-   *   -&t;*&t;&t;x   *   -&t;x+&n; *&t;-   *   *&t;*&t;&t;x   *   *&t;*&n; *&t;-   *   z&t;z-&t;&t;x   *   z&t;z-&n; *&t;-   y   -&t;y-&t;&t;x   y   -&t;x+&n; *&t;-   y   *&t;y-&t;&t;x   y   *&t;y-&n; *&t;-   y   z&t;z-&t;&t;x   y   z&t;z-&n; *&n; * All non-error cases can be converted with the following simple set of rules:&n; *&n; *   if pcr == z then z-&n; *   else if min == x &amp;&amp; pcr == - then x+&n; *     else if max == y then y-&n; *&t; else *&n; */
DECL|function|atm_pcr_goal
r_int
id|atm_pcr_goal
c_func
(paren
r_struct
id|atm_trafprm
op_star
id|tp
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;pcr
op_logical_and
id|tp-&gt;pcr
op_ne
id|ATM_MAX_PCR
)paren
r_return
op_minus
id|tp-&gt;pcr
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;min_pcr
op_logical_and
op_logical_neg
id|tp-&gt;pcr
)paren
r_return
id|tp-&gt;min_pcr
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;max_pcr
op_ne
id|ATM_MAX_PCR
)paren
r_return
op_minus
id|tp-&gt;max_pcr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sonet_copy_stats
r_void
id|sonet_copy_stats
c_func
(paren
r_struct
id|k_sonet_stats
op_star
id|from
comma
r_struct
id|sonet_stats
op_star
id|to
)paren
(brace
DECL|macro|__HANDLE_ITEM
mdefine_line|#define __HANDLE_ITEM(i) to-&gt;i = atomic_read(&amp;from-&gt;i)
id|__SONET_ITEMS
DECL|macro|__HANDLE_ITEM
macro_line|#undef __HANDLE_ITEM
)brace
DECL|function|sonet_subtract_stats
r_void
id|sonet_subtract_stats
c_func
(paren
r_struct
id|k_sonet_stats
op_star
id|from
comma
r_struct
id|sonet_stats
op_star
id|to
)paren
(brace
DECL|macro|__HANDLE_ITEM
mdefine_line|#define __HANDLE_ITEM(i) atomic_sub(to-&gt;i,&amp;from-&gt;i)
id|__SONET_ITEMS
DECL|macro|__HANDLE_ITEM
macro_line|#undef __HANDLE_ITEM
)brace
DECL|variable|atm_charge
id|EXPORT_SYMBOL
c_func
(paren
id|atm_charge
)paren
suffix:semicolon
DECL|variable|atm_alloc_charge
id|EXPORT_SYMBOL
c_func
(paren
id|atm_alloc_charge
)paren
suffix:semicolon
DECL|variable|atm_find_ci
id|EXPORT_SYMBOL
c_func
(paren
id|atm_find_ci
)paren
suffix:semicolon
DECL|variable|atm_pcr_goal
id|EXPORT_SYMBOL
c_func
(paren
id|atm_pcr_goal
)paren
suffix:semicolon
DECL|variable|sonet_copy_stats
id|EXPORT_SYMBOL
c_func
(paren
id|sonet_copy_stats
)paren
suffix:semicolon
DECL|variable|sonet_subtract_stats
id|EXPORT_SYMBOL
c_func
(paren
id|sonet_subtract_stats
)paren
suffix:semicolon
eof
