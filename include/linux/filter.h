multiline_comment|/*&n; * Linux Socket Filter Data Structures&n; */
macro_line|#ifndef __LINUX_FILTER_H__
DECL|macro|__LINUX_FILTER_H__
mdefine_line|#define __LINUX_FILTER_H__
multiline_comment|/*&n; * Current version of the filter code architecture.&n; */
DECL|macro|BPF_MAJOR_VERSION
mdefine_line|#define BPF_MAJOR_VERSION 1
DECL|macro|BPF_MINOR_VERSION
mdefine_line|#define BPF_MINOR_VERSION 1
multiline_comment|/*&n; *&t;Try and keep these values and structures similar to BSD, especially&n; *&t;the BPF code definitions which need to match so you can share filters&n; */
DECL|struct|sock_filter
r_struct
id|sock_filter
multiline_comment|/* Filter block */
(brace
DECL|member|code
id|__u16
id|code
suffix:semicolon
multiline_comment|/* Actual filter code */
DECL|member|jt
id|__u8
id|jt
suffix:semicolon
multiline_comment|/* Jump true */
DECL|member|jf
id|__u8
id|jf
suffix:semicolon
multiline_comment|/* Jump false */
DECL|member|k
id|__u32
id|k
suffix:semicolon
multiline_comment|/* Generic multiuse field */
)brace
suffix:semicolon
DECL|struct|sock_fprog
r_struct
id|sock_fprog
multiline_comment|/* Required for SO_ATTACH_FILTER. */
(brace
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* Number of filter blocks */
DECL|member|filter
r_struct
id|sock_filter
op_star
id|filter
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|sk_filter
r_struct
id|sk_filter
(brace
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* Number of filter blocks */
DECL|member|insns
r_struct
id|sock_filter
id|insns
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|sk_filter_len
r_static
r_inline
r_int
r_int
id|sk_filter_len
c_func
(paren
r_struct
id|sk_filter
op_star
id|fp
)paren
(brace
r_return
id|fp-&gt;len
op_star
r_sizeof
(paren
r_struct
id|sock_filter
)paren
op_plus
r_sizeof
(paren
op_star
id|fp
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Instruction classes&n; */
DECL|macro|BPF_CLASS
mdefine_line|#define BPF_CLASS(code) ((code) &amp; 0x07)
DECL|macro|BPF_LD
mdefine_line|#define         BPF_LD          0x00
DECL|macro|BPF_LDX
mdefine_line|#define         BPF_LDX         0x01
DECL|macro|BPF_ST
mdefine_line|#define         BPF_ST          0x02
DECL|macro|BPF_STX
mdefine_line|#define         BPF_STX         0x03
DECL|macro|BPF_ALU
mdefine_line|#define         BPF_ALU         0x04
DECL|macro|BPF_JMP
mdefine_line|#define         BPF_JMP         0x05
DECL|macro|BPF_RET
mdefine_line|#define         BPF_RET         0x06
DECL|macro|BPF_MISC
mdefine_line|#define         BPF_MISC        0x07
multiline_comment|/* ld/ldx fields */
DECL|macro|BPF_SIZE
mdefine_line|#define BPF_SIZE(code)  ((code) &amp; 0x18)
DECL|macro|BPF_W
mdefine_line|#define         BPF_W           0x00
DECL|macro|BPF_H
mdefine_line|#define         BPF_H           0x08
DECL|macro|BPF_B
mdefine_line|#define         BPF_B           0x10
DECL|macro|BPF_MODE
mdefine_line|#define BPF_MODE(code)  ((code) &amp; 0xe0)
DECL|macro|BPF_IMM
mdefine_line|#define         BPF_IMM         0x00
DECL|macro|BPF_ABS
mdefine_line|#define         BPF_ABS         0x20
DECL|macro|BPF_IND
mdefine_line|#define         BPF_IND         0x40
DECL|macro|BPF_MEM
mdefine_line|#define         BPF_MEM         0x60
DECL|macro|BPF_LEN
mdefine_line|#define         BPF_LEN         0x80
DECL|macro|BPF_MSH
mdefine_line|#define         BPF_MSH         0xa0
multiline_comment|/* alu/jmp fields */
DECL|macro|BPF_OP
mdefine_line|#define BPF_OP(code)    ((code) &amp; 0xf0)
DECL|macro|BPF_ADD
mdefine_line|#define         BPF_ADD         0x00
DECL|macro|BPF_SUB
mdefine_line|#define         BPF_SUB         0x10
DECL|macro|BPF_MUL
mdefine_line|#define         BPF_MUL         0x20
DECL|macro|BPF_DIV
mdefine_line|#define         BPF_DIV         0x30
DECL|macro|BPF_OR
mdefine_line|#define         BPF_OR          0x40
DECL|macro|BPF_AND
mdefine_line|#define         BPF_AND         0x50
DECL|macro|BPF_LSH
mdefine_line|#define         BPF_LSH         0x60
DECL|macro|BPF_RSH
mdefine_line|#define         BPF_RSH         0x70
DECL|macro|BPF_NEG
mdefine_line|#define         BPF_NEG         0x80
DECL|macro|BPF_JA
mdefine_line|#define         BPF_JA          0x00
DECL|macro|BPF_JEQ
mdefine_line|#define         BPF_JEQ         0x10
DECL|macro|BPF_JGT
mdefine_line|#define         BPF_JGT         0x20
DECL|macro|BPF_JGE
mdefine_line|#define         BPF_JGE         0x30
DECL|macro|BPF_JSET
mdefine_line|#define         BPF_JSET        0x40
DECL|macro|BPF_SRC
mdefine_line|#define BPF_SRC(code)   ((code) &amp; 0x08)
DECL|macro|BPF_K
mdefine_line|#define         BPF_K           0x00
DECL|macro|BPF_X
mdefine_line|#define         BPF_X           0x08
multiline_comment|/* ret - BPF_K and BPF_X also apply */
DECL|macro|BPF_RVAL
mdefine_line|#define BPF_RVAL(code)  ((code) &amp; 0x18)
DECL|macro|BPF_A
mdefine_line|#define         BPF_A           0x10
multiline_comment|/* misc */
DECL|macro|BPF_MISCOP
mdefine_line|#define BPF_MISCOP(code) ((code) &amp; 0xf8)
DECL|macro|BPF_TAX
mdefine_line|#define         BPF_TAX         0x00
DECL|macro|BPF_TXA
mdefine_line|#define         BPF_TXA         0x80
macro_line|#ifndef BPF_MAXINSNS
DECL|macro|BPF_MAXINSNS
mdefine_line|#define BPF_MAXINSNS 4096
macro_line|#endif
multiline_comment|/*&n; * Macros for filter block array initializers.&n; */
macro_line|#ifndef BPF_STMT
DECL|macro|BPF_STMT
mdefine_line|#define BPF_STMT(code, k) { (unsigned short)(code), 0, 0, k }
macro_line|#endif
macro_line|#ifndef BPF_JUMP
DECL|macro|BPF_JUMP
mdefine_line|#define BPF_JUMP(code, k, jt, jf) { (unsigned short)(code), jt, jf, k }
macro_line|#endif
multiline_comment|/*&n; * Number of scratch memory words for: BPF_ST and BPF_STX&n; */
DECL|macro|BPF_MEMWORDS
mdefine_line|#define BPF_MEMWORDS 16
multiline_comment|/* RATIONALE. Negative offsets are invalid in BPF.&n;   We use them to reference ancillary data.&n;   Unlike introduction new instructions, it does not break&n;   existing compilers/optimizers.&n; */
DECL|macro|SKF_AD_OFF
mdefine_line|#define SKF_AD_OFF    (-0x1000)
DECL|macro|SKF_AD_PROTOCOL
mdefine_line|#define SKF_AD_PROTOCOL 0
DECL|macro|SKF_AD_PKTTYPE
mdefine_line|#define SKF_AD_PKTTYPE &t;4
DECL|macro|SKF_AD_IFINDEX
mdefine_line|#define SKF_AD_IFINDEX &t;8
DECL|macro|SKF_AD_MAX
mdefine_line|#define SKF_AD_MAX &t;12
DECL|macro|SKF_NET_OFF
mdefine_line|#define SKF_NET_OFF   (-0x100000)
DECL|macro|SKF_LL_OFF
mdefine_line|#define SKF_LL_OFF    (-0x200000)
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|sk_run_filter
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|sock_filter
op_star
id|filter
comma
r_int
id|flen
)paren
suffix:semicolon
r_extern
r_int
id|sk_attach_filter
c_func
(paren
r_struct
id|sock_fprog
op_star
id|fprog
comma
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
id|sk_chk_filter
c_func
(paren
r_struct
id|sock_filter
op_star
id|filter
comma
r_int
id|flen
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __LINUX_FILTER_H__ */
eof
