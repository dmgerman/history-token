macro_line|#include &quot;hisax_if.h&quot;
macro_line|#include &quot;hisax_isac.h&quot;
macro_line|#include &lt;linux/pci.h&gt;
DECL|macro|HSCX_BUFMAX
mdefine_line|#define HSCX_BUFMAX&t;4096
r_enum
(brace
DECL|enumerator|AVM_FRITZ_PCI
id|AVM_FRITZ_PCI
comma
DECL|enumerator|AVM_FRITZ_PNP
id|AVM_FRITZ_PNP
comma
DECL|enumerator|AVM_FRITZ_PCIV2
id|AVM_FRITZ_PCIV2
comma
)brace
suffix:semicolon
DECL|struct|hdlc_stat_reg
r_struct
id|hdlc_stat_reg
(brace
macro_line|#ifdef __BIG_ENDIAN
DECL|member|fill
id|u8
id|fill
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|mode
id|u8
id|mode
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|xml
id|u8
id|xml
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|cmd
id|u8
id|cmd
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#else
id|u8
id|cmd
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u8
id|xml
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u8
id|mode
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u8
id|fill
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|fritz_bcs
r_struct
id|fritz_bcs
(brace
DECL|member|b_if
r_struct
id|hisax_b_if
id|b_if
suffix:semicolon
DECL|member|adapter
r_struct
id|fritz_adapter
op_star
id|adapter
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
r_union
(brace
DECL|member|ctrl
id|u_int
id|ctrl
suffix:semicolon
DECL|member|sr
r_struct
id|hdlc_stat_reg
id|sr
suffix:semicolon
DECL|member|ctrl
)brace
id|ctrl
suffix:semicolon
DECL|member|stat
id|u_int
id|stat
suffix:semicolon
DECL|member|rcvidx
r_int
id|rcvidx
suffix:semicolon
DECL|member|rcvbuf
id|u8
id|rcvbuf
(braket
id|HSCX_BUFMAX
)braket
suffix:semicolon
multiline_comment|/* B-Channel receive Buffer */
DECL|member|tx_cnt
r_int
id|tx_cnt
suffix:semicolon
multiline_comment|/* B-Channel transmit counter */
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
multiline_comment|/* B-Channel transmit Buffer */
)brace
suffix:semicolon
DECL|struct|fritz_adapter
r_struct
id|fritz_adapter
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|hw_lock
id|spinlock_t
id|hw_lock
suffix:semicolon
DECL|member|io
r_int
r_int
id|io
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|isac
r_struct
id|isac
id|isac
suffix:semicolon
DECL|member|bcs
r_struct
id|fritz_bcs
id|bcs
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|read_hdlc_status
id|u32
(paren
op_star
id|read_hdlc_status
)paren
(paren
r_struct
id|fritz_adapter
op_star
id|adapter
comma
r_int
id|nr
)paren
suffix:semicolon
DECL|member|write_ctrl
r_void
(paren
op_star
id|write_ctrl
)paren
(paren
r_struct
id|fritz_bcs
op_star
id|bcs
comma
r_int
id|which
)paren
suffix:semicolon
)brace
suffix:semicolon
eof
