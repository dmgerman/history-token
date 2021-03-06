multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;m527xsim.h -- ColdFire 5270/5271 System Integration Module support.&n; *&n; *&t;(C) Copyright 2004, Greg Ungerer (gerg@snapgear.com)&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;m527xsim_h
DECL|macro|m527xsim_h
mdefine_line|#define&t;m527xsim_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;Define the 5270/5271 SIM register set addresses.&n; */
DECL|macro|MCFICM_INTC0
mdefine_line|#define&t;MCFICM_INTC0&t;&t;0x0c00&t;&t;/* Base for Interrupt Ctrl 0 */
DECL|macro|MCFICM_INTC1
mdefine_line|#define&t;MCFICM_INTC1&t;&t;0x0d00&t;&t;/* Base for Interrupt Ctrl 1 */
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
DECL|macro|MCFINT_UART1
mdefine_line|#define&t;MCFINT_UART1&t;&t;14&t;&t;/* Interrupt number for UART1 */
DECL|macro|MCFINT_UART2
mdefine_line|#define&t;MCFINT_UART2&t;&t;15&t;&t;/* Interrupt number for UART2 */
DECL|macro|MCFINT_PIT1
mdefine_line|#define&t;MCFINT_PIT1&t;&t;36&t;&t;/* Interrupt number for PIT1 */
multiline_comment|/*&n; *&t;SDRAM configuration registers.&n; */
macro_line|#ifdef CONFIG_M5271EVB
DECL|macro|MCFSIM_DCR
mdefine_line|#define&t;MCFSIM_DCR&t;&t;0x40&t;&t;/* SDRAM control */
DECL|macro|MCFSIM_DACR0
mdefine_line|#define&t;MCFSIM_DACR0&t;&t;0x48&t;&t;/* SDRAM base address 0 */
DECL|macro|MCFSIM_DMR0
mdefine_line|#define&t;MCFSIM_DMR0&t;&t;0x4c&t;&t;/* SDRAM address mask 0 */
DECL|macro|MCFSIM_DACR1
mdefine_line|#define&t;MCFSIM_DACR1&t;&t;0x50&t;&t;/* SDRAM base address 1 */
DECL|macro|MCFSIM_DMR1
mdefine_line|#define&t;MCFSIM_DMR1&t;&t;0x54&t;&t;/* SDRAM address mask 1 */
macro_line|#else
DECL|macro|MCFSIM_DMR
mdefine_line|#define&t;MCFSIM_DMR&t;&t;0x40&t;&t;/* SDRAM mode */
DECL|macro|MCFSIM_DCR
mdefine_line|#define&t;MCFSIM_DCR&t;&t;0x44&t;&t;/* SDRAM control */
DECL|macro|MCFSIM_DCFG1
mdefine_line|#define&t;MCFSIM_DCFG1&t;&t;0x48&t;&t;/* SDRAM configuration 1 */
DECL|macro|MCFSIM_DCFG2
mdefine_line|#define&t;MCFSIM_DCFG2&t;&t;0x4c&t;&t;/* SDRAM configuration 2 */
DECL|macro|MCFSIM_DBAR0
mdefine_line|#define&t;MCFSIM_DBAR0&t;&t;0x50&t;&t;/* SDRAM base address 0 */
DECL|macro|MCFSIM_DMR0
mdefine_line|#define&t;MCFSIM_DMR0&t;&t;0x54&t;&t;/* SDRAM address mask 0 */
DECL|macro|MCFSIM_DBAR1
mdefine_line|#define&t;MCFSIM_DBAR1&t;&t;0x58&t;&t;/* SDRAM base address 1 */
DECL|macro|MCFSIM_DMR1
mdefine_line|#define&t;MCFSIM_DMR1&t;&t;0x5c&t;&t;/* SDRAM address mask 1 */
macro_line|#endif
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* m527xsim_h */
eof
