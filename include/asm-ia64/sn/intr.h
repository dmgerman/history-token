multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_INTR_H
DECL|macro|_ASM_IA64_SN_INTR_H
mdefine_line|#define _ASM_IA64_SN_INTR_H
DECL|macro|SGI_UART_VECTOR
mdefine_line|#define SGI_UART_VECTOR&t;&t;(0xe9)
DECL|macro|SGI_PCIBR_ERROR
mdefine_line|#define SGI_PCIBR_ERROR&t;&t;(0x33)
multiline_comment|/* Reserved IRQs : Note, not to exceed IA64_SN2_FIRST_DEVICE_VECTOR */
DECL|macro|SGI_XPC_ACTIVATE
mdefine_line|#define SGI_XPC_ACTIVATE                (0x30)
DECL|macro|SGI_II_ERROR
mdefine_line|#define SGI_II_ERROR                    (0x31)
DECL|macro|SGI_XBOW_ERROR
mdefine_line|#define SGI_XBOW_ERROR                  (0x32)
DECL|macro|SGI_PCIBR_ERROR
mdefine_line|#define SGI_PCIBR_ERROR                 (0x33)
DECL|macro|SGI_ACPI_SCI_INT
mdefine_line|#define SGI_ACPI_SCI_INT                (0x34)
DECL|macro|SGI_TIOCA_ERROR
mdefine_line|#define SGI_TIOCA_ERROR                 (0x35)
DECL|macro|SGI_TIO_ERROR
mdefine_line|#define SGI_TIO_ERROR                   (0x36)
DECL|macro|SGI_TIOCX_ERROR
mdefine_line|#define SGI_TIOCX_ERROR                 (0x37)
DECL|macro|SGI_MMTIMER_VECTOR
mdefine_line|#define SGI_MMTIMER_VECTOR              (0x38)
DECL|macro|SGI_XPC_NOTIFY
mdefine_line|#define SGI_XPC_NOTIFY                  (0xe7)
DECL|macro|IA64_SN2_FIRST_DEVICE_VECTOR
mdefine_line|#define IA64_SN2_FIRST_DEVICE_VECTOR    (0x3c)
DECL|macro|IA64_SN2_LAST_DEVICE_VECTOR
mdefine_line|#define IA64_SN2_LAST_DEVICE_VECTOR     (0xe6)
DECL|macro|SN2_IRQ_RESERVED
mdefine_line|#define SN2_IRQ_RESERVED        (0x1)
DECL|macro|SN2_IRQ_CONNECTED
mdefine_line|#define SN2_IRQ_CONNECTED       (0x2)
DECL|macro|SN2_IRQ_SHARED
mdefine_line|#define SN2_IRQ_SHARED          (0x4)
singleline_comment|// The SN PROM irq struct
DECL|struct|sn_irq_info
r_struct
id|sn_irq_info
(brace
DECL|member|irq_next
r_struct
id|sn_irq_info
op_star
id|irq_next
suffix:semicolon
multiline_comment|/* sharing irq list&t;     */
DECL|member|irq_nasid
r_int
id|irq_nasid
suffix:semicolon
multiline_comment|/* Nasid IRQ is assigned to  */
DECL|member|irq_slice
r_int
id|irq_slice
suffix:semicolon
multiline_comment|/* slice IRQ is assigned to  */
DECL|member|irq_cpuid
r_int
id|irq_cpuid
suffix:semicolon
multiline_comment|/* kernel logical cpuid&t;     */
DECL|member|irq_irq
r_int
id|irq_irq
suffix:semicolon
multiline_comment|/* the IRQ number */
DECL|member|irq_int_bit
r_int
id|irq_int_bit
suffix:semicolon
multiline_comment|/* Bridge interrupt pin */
DECL|member|irq_xtalkaddr
r_uint64
id|irq_xtalkaddr
suffix:semicolon
multiline_comment|/* xtalkaddr IRQ is sent to  */
DECL|member|irq_bridge_type
r_int
id|irq_bridge_type
suffix:semicolon
multiline_comment|/* pciio asic type (pciio.h) */
DECL|member|irq_bridge
r_void
op_star
id|irq_bridge
suffix:semicolon
multiline_comment|/* bridge generating irq     */
DECL|member|irq_pciioinfo
r_void
op_star
id|irq_pciioinfo
suffix:semicolon
multiline_comment|/* associated pciio_info_t   */
DECL|member|irq_last_intr
r_int
id|irq_last_intr
suffix:semicolon
multiline_comment|/* For Shub lb lost intr WAR */
DECL|member|irq_cookie
r_int
id|irq_cookie
suffix:semicolon
multiline_comment|/* unique cookie &t;     */
DECL|member|irq_flags
r_int
id|irq_flags
suffix:semicolon
multiline_comment|/* flags */
DECL|member|irq_share_cnt
r_int
id|irq_share_cnt
suffix:semicolon
multiline_comment|/* num devices sharing IRQ   */
)brace
suffix:semicolon
r_extern
r_void
id|sn_send_IPI_phys
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|CPU_VECTOR_TO_IRQ
mdefine_line|#define CPU_VECTOR_TO_IRQ(cpuid,vector) (vector)
macro_line|#endif /* _ASM_IA64_SN_INTR_H */
eof
