multiline_comment|/* $Id: upa.h,v 1.3 1999/09/21 14:39:47 davem Exp $ */
macro_line|#ifndef _SPARC64_UPA_H
DECL|macro|_SPARC64_UPA_H
mdefine_line|#define _SPARC64_UPA_H
macro_line|#include &lt;asm/asi.h&gt;
multiline_comment|/* UPA level registers and defines. */
multiline_comment|/* UPA Config Register */
DECL|macro|UPA_CONFIG_RESV
mdefine_line|#define UPA_CONFIG_RESV&t;&t;0xffffffffc0000000 /* Reserved.                    */
DECL|macro|UPA_CONFIG_PCON
mdefine_line|#define UPA_CONFIG_PCON&t;&t;0x000000003fc00000 /* Depth of various sys queues. */
DECL|macro|UPA_CONFIG_MID
mdefine_line|#define UPA_CONFIG_MID&t;&t;0x00000000003e0000 /* Module ID.                   */
DECL|macro|UPA_CONFIG_PCAP
mdefine_line|#define UPA_CONFIG_PCAP&t;&t;0x000000000001ffff /* Port Capabilities.           */
multiline_comment|/* UPA Port ID Register */
DECL|macro|UPA_PORTID_FNP
mdefine_line|#define UPA_PORTID_FNP&t;&t;0xff00000000000000 /* Hardcoded to 0xfc on ultra.  */
DECL|macro|UPA_PORTID_RESV
mdefine_line|#define UPA_PORTID_RESV&t;&t;0x00fffff800000000 /* Reserved.                    */
DECL|macro|UPA_PORTID_ECCVALID
mdefine_line|#define UPA_PORTID_ECCVALID     0x0000000400000000 /* Zero if mod can generate ECC */
DECL|macro|UPA_PORTID_ONEREAD
mdefine_line|#define UPA_PORTID_ONEREAD      0x0000000200000000 /* Set if mod generates P_RASB  */
DECL|macro|UPA_PORTID_PINTRDQ
mdefine_line|#define UPA_PORTID_PINTRDQ      0x0000000180000000 /* # outstanding P_INT_REQ&squot;s    */
DECL|macro|UPA_PORTID_PREQDQ
mdefine_line|#define UPA_PORTID_PREQDQ       0x000000007e000000 /* slave-wr&squot;s to mod supported  */
DECL|macro|UPA_PORTID_PREQRD
mdefine_line|#define UPA_PORTID_PREQRD       0x0000000001e00000 /* # incoming P_REQ&squot;s supported */
DECL|macro|UPA_PORTID_UPACAP
mdefine_line|#define UPA_PORTID_UPACAP       0x00000000001f0000 /* UPA capabilities of mod      */
DECL|macro|UPA_PORTID_ID
mdefine_line|#define UPA_PORTID_ID           0x000000000000ffff /* Module Indentification bits  */
multiline_comment|/* UPA I/O space accessors */
macro_line|#if defined(__KERNEL__) &amp;&amp; !defined(__ASSEMBLY__)
DECL|function|_upa_readb
r_extern
id|__inline__
r_int
r_char
id|_upa_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_char
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduba&bslash;t[%1] %2, %0&bslash;t/* upa_readb */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_upa_readw
r_extern
id|__inline__
r_int
r_int
id|_upa_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduha&bslash;t[%1] %2, %0&bslash;t/* upa_readw */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_upa_readl
r_extern
id|__inline__
r_int
r_int
id|_upa_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduwa&bslash;t[%1] %2, %0&bslash;t/* upa_readl */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_upa_readq
r_extern
id|__inline__
r_int
r_int
id|_upa_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldxa&bslash;t[%1] %2, %0&bslash;t/* upa_readq */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_upa_writeb
r_extern
id|__inline__
r_void
id|_upa_writeb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stba&bslash;t%0, [%1] %2&bslash;t/* upa_writeb */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|b
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|function|_upa_writew
r_extern
id|__inline__
r_void
id|_upa_writew
c_func
(paren
r_int
r_int
id|w
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stha&bslash;t%0, [%1] %2&bslash;t/* upa_writew */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|w
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|function|_upa_writel
r_extern
id|__inline__
r_void
id|_upa_writel
c_func
(paren
r_int
r_int
id|l
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stwa&bslash;t%0, [%1] %2&bslash;t/* upa_writel */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|l
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|function|_upa_writeq
r_extern
id|__inline__
r_void
id|_upa_writeq
c_func
(paren
r_int
r_int
id|q
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stxa&bslash;t%0, [%1] %2&bslash;t/* upa_writeq */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|q
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|macro|upa_readb
mdefine_line|#define upa_readb(__addr)&t;&t;(_upa_readb((unsigned long)(__addr)))
DECL|macro|upa_readw
mdefine_line|#define upa_readw(__addr)&t;&t;(_upa_readw((unsigned long)(__addr)))
DECL|macro|upa_readl
mdefine_line|#define upa_readl(__addr)&t;&t;(_upa_readl((unsigned long)(__addr)))
DECL|macro|upa_readq
mdefine_line|#define upa_readq(__addr)&t;&t;(_upa_readq((unsigned long)(__addr)))
DECL|macro|upa_writeb
mdefine_line|#define upa_writeb(__b, __addr)&t;&t;(_upa_writeb((__b), (unsigned long)(__addr)))
DECL|macro|upa_writew
mdefine_line|#define upa_writew(__w, __addr)&t;&t;(_upa_writew((__w), (unsigned long)(__addr)))
DECL|macro|upa_writel
mdefine_line|#define upa_writel(__l, __addr)&t;&t;(_upa_writel((__l), (unsigned long)(__addr)))
DECL|macro|upa_writeq
mdefine_line|#define upa_writeq(__q, __addr)&t;&t;(_upa_writeq((__q), (unsigned long)(__addr)))
macro_line|#endif /* __KERNEL__ &amp;&amp; !__ASSEMBLY__ */
macro_line|#endif /* !(_SPARC64_UPA_H) */
eof
