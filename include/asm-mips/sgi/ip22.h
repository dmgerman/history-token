multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License. See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * ip22.h: Definitions for SGI IP22 machines&n; *&n; * Copyright (C) 1996 David S. Miller&n; * Copyright (C) 1997, 1998, 1999, 2000 Ralf Baechle&n; */
macro_line|#ifndef _SGI_IP22_H
DECL|macro|_SGI_IP22_H
mdefine_line|#define _SGI_IP22_H
multiline_comment|/* &n; * These are the virtual IRQ numbers, we divide all IRQ&squot;s into&n; * &squot;spaces&squot;, the &squot;space&squot; determines where and how to enable/disable&n; * that particular IRQ on an SGI machine. HPC DMA and MC DMA interrups&n; * are not supported this way. Driver is supposed to allocate HPC/MC&n; * interrupt as shareable and then look to proper status bit (see&n; * HAL2 driver). This will prevent many complications, trust me ;-)&n; */
macro_line|#include &lt;asm/sgi/ioc.h&gt;
DECL|macro|SGINT_EISA
mdefine_line|#define SGINT_EISA&t;0&t;/* INDIGO 2 has 16 EISA irq levels */
DECL|macro|SGINT_CPU
mdefine_line|#define SGINT_CPU&t;16&t;/* MIPS CPU define 8 interrupt sources */
DECL|macro|SGINT_LOCAL0
mdefine_line|#define SGINT_LOCAL0&t;24&t;/* INDY has 8 local0 irq levels */
DECL|macro|SGINT_LOCAL1
mdefine_line|#define SGINT_LOCAL1&t;32&t;/* INDY has 8 local1 irq levels */
DECL|macro|SGINT_LOCAL2
mdefine_line|#define SGINT_LOCAL2&t;40&t;/* INDY has 8 local2 vectored irq levels */
DECL|macro|SGINT_LOCAL3
mdefine_line|#define SGINT_LOCAL3&t;48&t;/* INDY has 8 local3 vectored irq levels */
DECL|macro|SGINT_END
mdefine_line|#define SGINT_END&t;56&t;/* End of &squot;spaces&squot; */
multiline_comment|/*&n; * Individual interrupt definitions for the Indy and Indigo2&n; */
DECL|macro|SGI_SOFT_0_IRQ
mdefine_line|#define SGI_SOFT_0_IRQ&t;SGINT_CPU + 0
DECL|macro|SGI_SOFT_1_IRQ
mdefine_line|#define SGI_SOFT_1_IRQ&t;SGINT_CPU + 1
DECL|macro|SGI_LOCAL_0_IRQ
mdefine_line|#define SGI_LOCAL_0_IRQ&t;SGINT_CPU + 2
DECL|macro|SGI_LOCAL_1_IRQ
mdefine_line|#define SGI_LOCAL_1_IRQ&t;SGINT_CPU + 3
DECL|macro|SGI_8254_0_IRQ
mdefine_line|#define SGI_8254_0_IRQ&t;SGINT_CPU + 4
DECL|macro|SGI_8254_1_IRQ
mdefine_line|#define SGI_8254_1_IRQ&t;SGINT_CPU + 5
DECL|macro|SGI_BUSERR_IRQ
mdefine_line|#define SGI_BUSERR_IRQ&t;SGINT_CPU + 6
DECL|macro|SGI_TIMER_IRQ
mdefine_line|#define SGI_TIMER_IRQ&t;SGINT_CPU + 7
DECL|macro|SGI_FIFO_IRQ
mdefine_line|#define SGI_FIFO_IRQ&t;SGINT_LOCAL0 + 0&t;/* FIFO full */
DECL|macro|SGI_GIO_0_IRQ
mdefine_line|#define SGI_GIO_0_IRQ&t;SGI_FIFO_IRQ&t;&t;/* GIO-0 */
DECL|macro|SGI_WD93_0_IRQ
mdefine_line|#define SGI_WD93_0_IRQ&t;SGINT_LOCAL0 + 1&t;/* 1st onboard WD93 */
DECL|macro|SGI_WD93_1_IRQ
mdefine_line|#define SGI_WD93_1_IRQ&t;SGINT_LOCAL0 + 2&t;/* 2nd onboard WD93 */
DECL|macro|SGI_ENET_IRQ
mdefine_line|#define SGI_ENET_IRQ&t;SGINT_LOCAL0 + 3&t;/* onboard ethernet */
DECL|macro|SGI_MCDMA_IRQ
mdefine_line|#define SGI_MCDMA_IRQ&t;SGINT_LOCAL0 + 4&t;/* MC DMA done */
DECL|macro|SGI_PARPORT_IRQ
mdefine_line|#define SGI_PARPORT_IRQ&t;SGINT_LOCAL0 + 5&t;/* Parallel port */
DECL|macro|SGI_GIO_1_IRQ
mdefine_line|#define SGI_GIO_1_IRQ&t;SGINT_LOCAL0 + 6&t;/* GE / GIO-1 / 2nd-HPC */
DECL|macro|SGI_MAP_0_IRQ
mdefine_line|#define SGI_MAP_0_IRQ&t;SGINT_LOCAL0 + 7&t;/* Mappable interrupt 0 */
DECL|macro|SGI_GPL0_IRQ
mdefine_line|#define SGI_GPL0_IRQ&t;SGINT_LOCAL1 + 0&t;/* General Purpose LOCAL1_N&lt;0&gt; */
DECL|macro|SGI_PANEL_IRQ
mdefine_line|#define SGI_PANEL_IRQ&t;SGINT_LOCAL1 + 1&t;/* front panel */
DECL|macro|SGI_GPL2_IRQ
mdefine_line|#define SGI_GPL2_IRQ&t;SGINT_LOCAL1 + 2&t;/* General Purpose LOCAL1_N&lt;2&gt; */
DECL|macro|SGI_MAP_1_IRQ
mdefine_line|#define SGI_MAP_1_IRQ&t;SGINT_LOCAL1 + 3&t;/* Mappable interrupt 1 */
DECL|macro|SGI_HPCDMA_IRQ
mdefine_line|#define SGI_HPCDMA_IRQ&t;SGINT_LOCAL1 + 4&t;/* HPC DMA done */
DECL|macro|SGI_ACFAIL_IRQ
mdefine_line|#define SGI_ACFAIL_IRQ&t;SGINT_LOCAL1 + 5&t;/* AC fail */
DECL|macro|SGI_VINO_IRQ
mdefine_line|#define SGI_VINO_IRQ&t;SGINT_LOCAL1 + 6&t;/* Indy VINO */
DECL|macro|SGI_GIO_2_IRQ
mdefine_line|#define SGI_GIO_2_IRQ&t;SGINT_LOCAL1 + 7&t;/* Vert retrace / GIO-2 */
multiline_comment|/* Mapped interrupts. These interrupts may be mapped to either 0, or 1 */
DECL|macro|SGI_VERT_IRQ
mdefine_line|#define SGI_VERT_IRQ&t;SGINT_LOCAL2 + 0&t;/* INT3: newport vertical status */
DECL|macro|SGI_EISA_IRQ
mdefine_line|#define SGI_EISA_IRQ&t;SGINT_LOCAL2 + 3&t;/* EISA interrupts */
DECL|macro|SGI_KEYBD_IRQ
mdefine_line|#define SGI_KEYBD_IRQ&t;SGINT_LOCAL2 + 4&t;/* keyboard */
DECL|macro|SGI_SERIAL_IRQ
mdefine_line|#define SGI_SERIAL_IRQ&t;SGINT_LOCAL2 + 5&t;/* onboard serial */
DECL|macro|ip22_is_fullhouse
mdefine_line|#define ip22_is_fullhouse()&t;(sgioc-&gt;sysid &amp; SGIOC_SYSID_FULLHOUSE)
r_extern
r_int
r_int
id|ip22_eeprom_read
c_func
(paren
r_volatile
r_int
r_int
op_star
id|ctrl
comma
r_int
id|reg
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ip22_nvram_read
c_func
(paren
r_int
id|reg
)paren
suffix:semicolon
macro_line|#endif
eof
