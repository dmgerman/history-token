multiline_comment|/*&n; *  linux/include/asm-arm/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/* s390 does not have IDE */
macro_line|#ifndef __ASMS390_IDE_H
DECL|macro|__ASMS390_IDE_H
mdefine_line|#define __ASMS390_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;0
macro_line|#endif
DECL|macro|ide__sti
mdefine_line|#define ide__sti()&t;do {} while (0)
r_typedef
r_union
(brace
r_int
id|all
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all of the bits together */
r_struct
(brace
DECL|member|head
r_int
id|head
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* always zeros here */
DECL|member|unit
r_int
id|unit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive select number, 0 or 1 */
DECL|member|bit5
r_int
id|bit5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|lba
r_int
id|lba
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* using LBA instead of CHS */
DECL|member|bit7
r_int
id|bit7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|select_t
)brace
id|select_t
suffix:semicolon
DECL|macro|ide_request_irq
mdefine_line|#define ide_request_irq(irq,hand,flg,dev,id)&t;do {} while (0)
DECL|macro|ide_free_irq
mdefine_line|#define ide_free_irq(irq,dev_id)&t;&t;do {} while (0)
DECL|macro|ide_check_region
mdefine_line|#define ide_check_region(from,extent)&t;&t;do {} while (0)
DECL|macro|ide_request_region
mdefine_line|#define ide_request_region(from,extent,name)&t;do {} while (0)
DECL|macro|ide_release_region
mdefine_line|#define ide_release_region(from,extent)&t;&t;do {} while (0)
multiline_comment|/*&n; * The following are not needed for the non-m68k ports&n; */
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(hwif)&t;&t;(1)
DECL|macro|ide_fix_driveid
mdefine_line|#define ide_fix_driveid(id)&t;&t;do {} while (0)
DECL|macro|ide_release_lock
mdefine_line|#define ide_release_lock(lock)&t;&t;do {} while (0)
DECL|macro|ide_get_lock
mdefine_line|#define ide_get_lock(lock, hdlr, data)&t;do {} while (0)
multiline_comment|/*&n; * We always use the new IDE port registering,&n; * so these are fixed here.&n; */
DECL|macro|ide_default_io_base
mdefine_line|#define ide_default_io_base(i)&t;&t;((ide_ioreg_t)0)
DECL|macro|ide_default_irq
mdefine_line|#define ide_default_irq(b)&t;&t;(0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMARM_IDE_H */
eof
