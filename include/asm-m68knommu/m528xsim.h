multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;m528xsim.h -- ColdFire 5280/5282 System Integration Module support.&n; *&n; *&t;(C) Copyright 2003, Greg Ungerer (gerg@snapgear.com)&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;m528xsim_h
DECL|macro|m528xsim_h
mdefine_line|#define&t;m528xsim_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;Define the 5280/5282 SIM register set addresses.&n; */
DECL|macro|MCFICM_INTC0
mdefine_line|#define&t;MCFICM_INTC0&t;&t;0x0c00&t;&t;/* Base for Interrupt Ctrl 0 */
DECL|macro|MCFICM_INTC1
mdefine_line|#define&t;MCFICM_INTC1&t;&t;0x0d00&t;&t;/* Base for Interrupt Ctrl 0 */
DECL|macro|MCFINTC_IPRH
mdefine_line|#define&t;MCFINTC_IPRH&t;&t;0x00&t;&t;/* Interrupt pending 32-63 */
DECL|macro|MCFINTC_IPRL
mdefine_line|#define&t;MCFINTC_IPRL&t;&t;0x04&t;&t;/* Interrupt pending 1-31 */
DECL|macro|MCFINTC_IMRH
mdefine_line|#define&t;MCFINTC_IMRH&t;&t;0x08&t;&t;/* Interrupt mask 32-63 */
DECL|macro|MCFINTC_IMRL
mdefine_line|#define&t;MCFINTC_IMRL&t;&t;0x0c&t;&t;/* Interrupt mask 1-31 */
DECL|macro|MCFINTC_INTFRCH
mdefine_line|#define&t;MCFINTC_INTFRCH&t;&t;0x10&t;&t;/* Interrupt force 32-63 */
DECL|macro|MCFINTC_INTFRCL
mdefine_line|#define&t;MCFINTC_INTFRCL&t;&t;0x14&t;&t;/* Interrupt force 1-31 */
DECL|macro|MCFINTC_IRLR
mdefine_line|#define&t;MCFINTC_IRLR&t;&t;0x18&t;&t;/* */
DECL|macro|MCFINTC_IACKL
mdefine_line|#define&t;MCFINTC_IACKL&t;&t;0x19&t;&t;/* */
DECL|macro|MCFINTC_ICR0
mdefine_line|#define&t;MCFINTC_ICR0&t;&t;0x40&t;&t;/* Base ICR register */
DECL|macro|MCFINT_VECBASE
mdefine_line|#define&t;MCFINT_VECBASE&t;&t;64&t;&t;/* Vector base number */
DECL|macro|MCFINT_UART0
mdefine_line|#define&t;MCFINT_UART0&t;&t;13&t;&t;/* Interrupt number for UART0 */
DECL|macro|MCFINT_PIT1
mdefine_line|#define&t;MCFINT_PIT1&t;&t;55&t;&t;/* Interrupt number for PIT1 */
multiline_comment|/*&n; *&t;SDRAM configuration registers.&n; */
DECL|macro|MCFSIM_DCR
mdefine_line|#define&t;MCFSIM_DCR&t;&t;0x44&t;&t;/* SDRAM control */
DECL|macro|MCFSIM_DACR0
mdefine_line|#define&t;MCFSIM_DACR0&t;&t;0x48&t;&t;/* SDRAM base address 0 */
DECL|macro|MCFSIM_DMR0
mdefine_line|#define&t;MCFSIM_DMR0&t;&t;0x4c&t;&t;/* SDRAM address mask 0 */
DECL|macro|MCFSIM_DACR1
mdefine_line|#define&t;MCFSIM_DACR1&t;&t;0x50&t;&t;/* SDRAM base address 1 */
DECL|macro|MCFSIM_DMR1
mdefine_line|#define&t;MCFSIM_DMR1&t;&t;0x54&t;&t;/* SDRAM address mask 1 */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* m528xsim_h */
eof
