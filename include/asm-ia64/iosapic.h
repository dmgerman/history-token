macro_line|#ifndef __ASM_IA64_IOSAPIC_H
DECL|macro|__ASM_IA64_IOSAPIC_H
mdefine_line|#define __ASM_IA64_IOSAPIC_H
DECL|macro|IOSAPIC_DEFAULT_ADDR
mdefine_line|#define&t;IOSAPIC_DEFAULT_ADDR&t;0xFEC00000
DECL|macro|IOSAPIC_REG_SELECT
mdefine_line|#define&t;IOSAPIC_REG_SELECT&t;0x0
DECL|macro|IOSAPIC_WINDOW
mdefine_line|#define&t;IOSAPIC_WINDOW&t;&t;0x10
DECL|macro|IOSAPIC_EOI
mdefine_line|#define&t;IOSAPIC_EOI&t;&t;0x40
DECL|macro|IOSAPIC_VERSION
mdefine_line|#define&t;IOSAPIC_VERSION&t;0x1
multiline_comment|/*&n; * Redirection table entry&n; */
DECL|macro|IOSAPIC_RTE_LOW
mdefine_line|#define&t;IOSAPIC_RTE_LOW(i)&t;(0x10+i*2)
DECL|macro|IOSAPIC_RTE_HIGH
mdefine_line|#define&t;IOSAPIC_RTE_HIGH(i)&t;(0x11+i*2)
DECL|macro|IOSAPIC_DEST_SHIFT
mdefine_line|#define&t;IOSAPIC_DEST_SHIFT&t;&t;16
multiline_comment|/*&n; * Delivery mode&n; */
DECL|macro|IOSAPIC_DELIVERY_SHIFT
mdefine_line|#define&t;IOSAPIC_DELIVERY_SHIFT&t;&t;8
DECL|macro|IOSAPIC_FIXED
mdefine_line|#define&t;IOSAPIC_FIXED&t;&t;&t;0x0
DECL|macro|IOSAPIC_LOWEST_PRIORITY
mdefine_line|#define&t;IOSAPIC_LOWEST_PRIORITY&t;0x1
DECL|macro|IOSAPIC_PMI
mdefine_line|#define&t;IOSAPIC_PMI&t;&t;&t;0x2
DECL|macro|IOSAPIC_NMI
mdefine_line|#define&t;IOSAPIC_NMI&t;&t;&t;0x4
DECL|macro|IOSAPIC_INIT
mdefine_line|#define&t;IOSAPIC_INIT&t;&t;&t;0x5
DECL|macro|IOSAPIC_EXTINT
mdefine_line|#define&t;IOSAPIC_EXTINT&t;&t;&t;0x7
multiline_comment|/*&n; * Interrupt polarity&n; */
DECL|macro|IOSAPIC_POLARITY_SHIFT
mdefine_line|#define&t;IOSAPIC_POLARITY_SHIFT&t;&t;13
DECL|macro|IOSAPIC_POL_HIGH
mdefine_line|#define&t;IOSAPIC_POL_HIGH&t;&t;0
DECL|macro|IOSAPIC_POL_LOW
mdefine_line|#define&t;IOSAPIC_POL_LOW&t;&t;1
multiline_comment|/*&n; * Trigger mode&n; */
DECL|macro|IOSAPIC_TRIGGER_SHIFT
mdefine_line|#define&t;IOSAPIC_TRIGGER_SHIFT&t;&t;15
DECL|macro|IOSAPIC_EDGE
mdefine_line|#define&t;IOSAPIC_EDGE&t;&t;&t;0
DECL|macro|IOSAPIC_LEVEL
mdefine_line|#define&t;IOSAPIC_LEVEL&t;&t;&t;1
multiline_comment|/*&n; * Mask bit&n; */
DECL|macro|IOSAPIC_MASK_SHIFT
mdefine_line|#define&t;IOSAPIC_MASK_SHIFT&t;&t;16
DECL|macro|IOSAPIC_UNMASK
mdefine_line|#define&t;IOSAPIC_UNMASK&t;&t;&t;0
DECL|macro|IOSAPIC_MSAK
mdefine_line|#define&t;IOSAPIC_MSAK&t;&t;&t;1
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|__init
id|iosapic_init
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|base_irq
)paren
suffix:semicolon
r_extern
r_void
id|iosapic_register_legacy_irq
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|pin
comma
r_int
r_int
id|polarity
comma
r_int
r_int
id|trigger
)paren
suffix:semicolon
r_extern
r_void
id|iosapic_pci_fixup
(paren
r_int
)paren
suffix:semicolon
macro_line|# endif /* !__ASSEMBLY__ */
macro_line|#endif /* __ASM_IA64_IOSAPIC_H */
eof
