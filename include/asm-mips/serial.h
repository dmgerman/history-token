multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
macro_line|#ifndef CONFIG_OLIVETTI_M700
multiline_comment|/* Some Jazz machines seem to have an 8MHz crystal clock but I don&squot;t know&n;      exactly which ones ... XXX */
DECL|macro|JAZZ_BASE_BAUD
mdefine_line|#define JAZZ_BASE_BAUD ( 8000000 / 16 ) /* ( 3072000 / 16) */
macro_line|#else
multiline_comment|/* but the M700 isn&squot;t such a strange beast */
DECL|macro|JAZZ_BASE_BAUD
mdefine_line|#define JAZZ_BASE_BAUD BASE_BAUD
macro_line|#endif
multiline_comment|/* Standard COM flags (except for COM4, because of the 8514 problem) */
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST | ASYNC_AUTO_IRQ)
DECL|macro|STD_COM4_FLAGS
mdefine_line|#define STD_COM4_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
DECL|macro|STD_COM4_FLAGS
mdefine_line|#define STD_COM4_FLAGS ASYNC_BOOT_AUTOCONF
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|FOURPORT_FLAGS
mdefine_line|#define FOURPORT_FLAGS ASYNC_FOURPORT
DECL|macro|ACCENT_FLAGS
mdefine_line|#define ACCENT_FLAGS 0
DECL|macro|BOCA_FLAGS
mdefine_line|#define BOCA_FLAGS 0
DECL|macro|HUB6_FLAGS
mdefine_line|#define HUB6_FLAGS 0
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE
macro_line|#endif
multiline_comment|/*&n; * The following define the access methods for the HUB6 card. All&n; * access is through two ports for all 24 possible chips. The card is&n; * selected through the high 2 bits, the port on that card with the&n; * &quot;middle&quot; 3 bits, and the register on that port with the bottom&n; * 3 bits.&n; *&n; * While the access port and interrupt is configurable, the default&n; * port locations are 0x302 for the port control register, and 0x303&n; * for the data read/write register. Normally, the interrupt is at irq3&n; * but can be anything from 3 to 7 inclusive. Note that using 3 will&n; * require disabling com2.&n; */
DECL|macro|C_P
mdefine_line|#define C_P(card,port) (((card)&lt;&lt;6|(port)&lt;&lt;3) + 1)
macro_line|#ifdef CONFIG_MIPS_JAZZ
DECL|macro|_JAZZ_SERIAL_INIT
mdefine_line|#define _JAZZ_SERIAL_INIT(int, base)&t;&t;&t;&t;&t;&bslash;&n;&t;{ baud_base: JAZZ_BASE_BAUD, irq: int, flags: STD_COM_FLAGS,&t;&bslash;&n;&t;  iomem_base: (u8 *) base, iomem_reg_shift: 0,&t;&t;&t;&bslash;&n;&t;  io_type: SERIAL_IO_MEM }
DECL|macro|JAZZ_SERIAL_PORT_DEFNS
mdefine_line|#define JAZZ_SERIAL_PORT_DEFNS&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_JAZZ_SERIAL_INIT(JAZZ_SERIAL1_IRQ, JAZZ_SERIAL1_BASE),&t;&t;&bslash;&n;&t;_JAZZ_SERIAL_INIT(JAZZ_SERIAL2_IRQ, JAZZ_SERIAL2_BASE),
macro_line|#else
DECL|macro|JAZZ_SERIAL_PORT_DEFNS
mdefine_line|#define JAZZ_SERIAL_PORT_DEFNS
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_ATLAS
macro_line|#include &lt;asm/mips-boards/atlas.h&gt;
macro_line|#include &lt;asm/mips-boards/atlasint.h&gt;
DECL|macro|ATLAS_SERIAL_PORT_DEFNS
mdefine_line|#define ATLAS_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;/* UART CLK   PORT IRQ     FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, ATLAS_BASE_BAUD, ATLAS_UART_REGS_BASE, ATLASINT_UART, STD_COM_FLAGS },     /* ttyS0 */
macro_line|#else
DECL|macro|ATLAS_SERIAL_PORT_DEFNS
mdefine_line|#define ATLAS_SERIAL_PORT_DEFNS
macro_line|#endif
multiline_comment|/*&n; * Both Galileo boards have the same UART mappings.&n; */
macro_line|#if defined (CONFIG_MIPS_EV96100) || defined (CONFIG_MIPS_EV64120)
macro_line|#include &lt;asm/galileo-boards/ev96100.h&gt;
macro_line|#include &lt;asm/galileo-boards/ev96100int.h&gt;
DECL|macro|EV96100_SERIAL_PORT_DEFNS
mdefine_line|#define EV96100_SERIAL_PORT_DEFNS                                  &bslash;&n;    { baud_base: EV96100_BASE_BAUD, port: EV96100_UART0_REGS_BASE, &bslash;&n;      irq: EV96100INT_UART_0, flags: STD_COM_FLAGS, type: 0x3,   &bslash;&n;      iomem_base: EV96100_UART0_REGS_BASE },                       &bslash;&n;    { baud_base: EV96100_BASE_BAUD, port: EV96100_UART1_REGS_BASE, &bslash;&n;      irq: EV96100INT_UART_0, flags: STD_COM_FLAGS, type: 0x3,   &bslash;&n;      iomem_base: EV96100_UART1_REGS_BASE },
macro_line|#else
DECL|macro|EV96100_SERIAL_PORT_DEFNS
mdefine_line|#define EV96100_SERIAL_PORT_DEFNS
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_ITE8172
macro_line|#include &lt;asm/it8172/it8172.h&gt;
macro_line|#include &lt;asm/it8172/it8172_int.h&gt;
macro_line|#include &lt;asm/it8712.h&gt;
DECL|macro|ITE_SERIAL_PORT_DEFNS
mdefine_line|#define ITE_SERIAL_PORT_DEFNS                                  &bslash;&n;    { baud_base: BASE_BAUD, port: (IT8172_PCI_IO_BASE + IT_UART_BASE), &bslash;&n;      irq: IT8172_UART_IRQ, flags: STD_COM_FLAGS, type: 0x3 }, &bslash;&n;    { baud_base: (24000000/(16*13)), port: (IT8172_PCI_IO_BASE + IT8712_UART1_PORT), &bslash;&n;      irq: IT8172_SERIRQ_4, flags: STD_COM_FLAGS, type: 0x3 }, &bslash;&n;    /* Smart Card Reader 0 */ &bslash;&n;    { baud_base: BASE_BAUD, port: (IT8172_PCI_IO_BASE + IT_SCR0_BASE), &bslash;&n;      irq: IT8172_SCR0_IRQ, flags: STD_COM_FLAGS, type: 0x3 }, &bslash;&n;    /* Smart Card Reader 1 */ &bslash;&n;    { baud_base: BASE_BAUD, port: (IT8172_PCI_IO_BASE + IT_SCR1_BASE), &bslash;&n;      irq: IT8172_SCR1_IRQ, flags: STD_COM_FLAGS, type: 0x3 },
macro_line|#else
DECL|macro|ITE_SERIAL_PORT_DEFNS
mdefine_line|#define ITE_SERIAL_PORT_DEFNS
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_IVR
macro_line|#include &lt;asm/it8172/it8172.h&gt;
macro_line|#include &lt;asm/it8172/it8172_int.h&gt;
DECL|macro|IVR_SERIAL_PORT_DEFNS
mdefine_line|#define IVR_SERIAL_PORT_DEFNS                                  &bslash;&n;    { baud_base: BASE_BAUD, port: (IT8172_PCI_IO_BASE + IT_UART_BASE), &bslash;&n;      irq: IT8172_UART_IRQ, flags: STD_COM_FLAGS, type: 0x3 },         &bslash;&n;    /* Smart Card Reader 1 */ &bslash;&n;    { baud_base: BASE_BAUD, port: (IT8172_PCI_IO_BASE + IT_SCR1_BASE), &bslash;&n;      irq: IT8172_SCR1_IRQ, flags: STD_COM_FLAGS, type: 0x3 },
macro_line|#else
DECL|macro|IVR_SERIAL_PORT_DEFNS
mdefine_line|#define IVR_SERIAL_PORT_DEFNS
macro_line|#endif
macro_line|#ifdef CONFIG_AU1000_UART
macro_line|#include &lt;asm/au1000.h&gt;
DECL|macro|AU1000_SERIAL_PORT_DEFNS
mdefine_line|#define AU1000_SERIAL_PORT_DEFNS                              &bslash;&n;    { baud_base: 0, port: UART0_ADDR, irq: AU1000_UART0_INT,  &bslash;&n;      flags: STD_COM_FLAGS, type: 1 },                        &bslash;&n;    { baud_base: 0, port: UART1_ADDR, irq: AU1000_UART1_INT,  &bslash;&n;      flags: STD_COM_FLAGS, type: 1 },     &bslash;&n;    { baud_base: 0, port: UART2_ADDR, irq: AU1000_UART2_INT,  &bslash;&n;      flags: STD_COM_FLAGS, type: 1 },    &bslash;&n;    { baud_base: 0, port: UART3_ADDR, irq: AU1000_UART3_INT,  &bslash;&n;      flags: STD_COM_FLAGS, type: 1 },
macro_line|#else
DECL|macro|AU1000_SERIAL_PORT_DEFNS
mdefine_line|#define AU1000_SERIAL_PORT_DEFNS
macro_line|#endif
macro_line|#ifdef CONFIG_HAVE_STD_PC_SERIAL_PORT
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;/* UART CLK   PORT IRQ     FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3F8, 4, STD_COM_FLAGS },&t;/* ttyS0 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2F8, 3, STD_COM_FLAGS },&t;/* ttyS1 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3E8, 4, STD_COM_FLAGS },&t;/* ttyS2 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2E8, 3, STD_COM4_FLAGS },&t;/* ttyS3 */
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x1A0, 9, FOURPORT_FLAGS }, &t;/* ttyS4 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x1A8, 9, FOURPORT_FLAGS },&t;/* ttyS5 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x1B0, 9, FOURPORT_FLAGS },&t;/* ttyS6 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x1B8, 9, FOURPORT_FLAGS },&t;/* ttyS7 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2A0, 5, FOURPORT_FLAGS },&t;/* ttyS8 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2A8, 5, FOURPORT_FLAGS },&t;/* ttyS9 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2B0, 5, FOURPORT_FLAGS },&t;/* ttyS10 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2B8, 5, FOURPORT_FLAGS },&t;/* ttyS11 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x330, 4, ACCENT_FLAGS },&t;/* ttyS12 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x338, 4, ACCENT_FLAGS },&t;/* ttyS13 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x000, 0, 0 },&t;&t;&t;/* ttyS14 (spare) */ &bslash;&n;&t;{ 0, BASE_BAUD, 0x000, 0, 0 },&t;&t;&t;/* ttyS15 (spare) */ &bslash;&n;&t;{ 0, BASE_BAUD, 0x100, 12, BOCA_FLAGS },&t;/* ttyS16 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x108, 12, BOCA_FLAGS },&t;/* ttyS17 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x110, 12, BOCA_FLAGS },&t;/* ttyS18 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x118, 12, BOCA_FLAGS },&t;/* ttyS19 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x120, 12, BOCA_FLAGS },&t;/* ttyS20 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x128, 12, BOCA_FLAGS },&t;/* ttyS21 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x130, 12, BOCA_FLAGS },&t;/* ttyS22 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x138, 12, BOCA_FLAGS },&t;/* ttyS23 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x140, 12, BOCA_FLAGS },&t;/* ttyS24 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x148, 12, BOCA_FLAGS },&t;/* ttyS25 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x150, 12, BOCA_FLAGS },&t;/* ttyS26 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x158, 12, BOCA_FLAGS },&t;/* ttyS27 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x160, 12, BOCA_FLAGS },&t;/* ttyS28 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x168, 12, BOCA_FLAGS },&t;/* ttyS29 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x170, 12, BOCA_FLAGS },&t;/* ttyS30 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x178, 12, BOCA_FLAGS },&t;/* ttyS31 */
macro_line|#else /* CONFIG_SERIAL_MANY_PORTS */
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
macro_line|#endif /* CONFIG_SERIAL_MANY_PORTS */
macro_line|#else /* CONFIG_HAVE_STD_PC_SERIAL_PORTS */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
macro_line|#endif /* CONFIG_HAVE_STD_PC_SERIAL_PORTS */
multiline_comment|/* You can have up to four HUB6&squot;s in the system, but I&squot;ve only&n; * included two cards here for a total of twelve ports.&n; */
macro_line|#if (defined(CONFIG_HUB6) &amp;&amp; defined(CONFIG_SERIAL_MANY_PORTS))
DECL|macro|HUB6_SERIAL_PORT_DFNS
mdefine_line|#define HUB6_SERIAL_PORT_DFNS&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(0,0) },  /* ttyS32 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(0,1) },  /* ttyS33 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(0,2) },  /* ttyS34 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(0,3) },  /* ttyS35 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(0,4) },  /* ttyS36 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(0,5) },  /* ttyS37 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(1,0) },  /* ttyS38 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(1,1) },  /* ttyS39 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(1,2) },  /* ttyS40 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(1,3) },  /* ttyS41 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(1,4) },  /* ttyS42 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x302, 3, HUB6_FLAGS, C_P(1,5) },  /* ttyS43 */
macro_line|#else
DECL|macro|HUB6_SERIAL_PORT_DFNS
mdefine_line|#define HUB6_SERIAL_PORT_DFNS
macro_line|#endif
macro_line|#ifdef CONFIG_MCA
DECL|macro|MCA_SERIAL_PORT_DFNS
mdefine_line|#define MCA_SERIAL_PORT_DFNS&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3220, 3, STD_COM_FLAGS },&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3228, 3, STD_COM_FLAGS },&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x4220, 3, STD_COM_FLAGS },&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x4228, 3, STD_COM_FLAGS },&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x5220, 3, STD_COM_FLAGS },&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x5228, 3, STD_COM_FLAGS },
macro_line|#else
DECL|macro|MCA_SERIAL_PORT_DFNS
mdefine_line|#define MCA_SERIAL_PORT_DFNS
macro_line|#endif
macro_line|#ifdef CONFIG_MOMENCO_OCELOT
multiline_comment|/* Ordinary NS16552 duart with a 20MHz crystal.  */
DECL|macro|OCELOT_BASE_BAUD
mdefine_line|#define OCELOT_BASE_BAUD ( 20000000 / 16 )
DECL|macro|OCELOT_SERIAL1_IRQ
mdefine_line|#define OCELOT_SERIAL1_IRQ&t;4
DECL|macro|OCELOT_SERIAL1_BASE
mdefine_line|#define OCELOT_SERIAL1_BASE&t;0xe0001020
DECL|macro|_OCELOT_SERIAL_INIT
mdefine_line|#define _OCELOT_SERIAL_INIT(int, base)&t;&t;&t;&t;&t;&bslash;&n;&t;{ baud_base: OCELOT_BASE_BAUD, irq: int, flags: STD_COM_FLAGS,&t;&bslash;&n;&t;  iomem_base: (u8 *) base, iomem_reg_shift: 2,&t;&t;&t;&bslash;&n;&t;  io_type: SERIAL_IO_MEM }
DECL|macro|MOMENCO_OCELOT_SERIAL_PORT_DEFNS
mdefine_line|#define MOMENCO_OCELOT_SERIAL_PORT_DEFNS&t;&t;&t;&t;&bslash;&n;&t;_OCELOT_SERIAL_INIT(OCELOT_SERIAL1_IRQ, OCELOT_SERIAL1_BASE)
macro_line|#else
DECL|macro|MOMENCO_OCELOT_SERIAL_PORT_DEFNS
mdefine_line|#define MOMENCO_OCELOT_SERIAL_PORT_DEFNS
macro_line|#endif
macro_line|#ifdef CONFIG_DDB5477
DECL|macro|DDB5477_SERIAL_PORT_DEFNS
mdefine_line|#define DDB5477_SERIAL_PORT_DEFNS                                       &bslash;&n;        { baud_base: BASE_BAUD, irq: 12, flags: STD_COM_FLAGS,          &bslash;&n;          iomem_base: (u8*)0xbfa04200, iomem_reg_shift: 3,              &bslash;&n;          io_type: SERIAL_IO_MEM},&bslash;&n;        { baud_base: BASE_BAUD, irq: 28, flags: STD_COM_FLAGS,          &bslash;&n;          iomem_base: (u8*)0xbfa04240, iomem_reg_shift: 3,              &bslash;&n;          io_type: SERIAL_IO_MEM},
macro_line|#else
DECL|macro|DDB5477_SERIAL_PORT_DEFNS
mdefine_line|#define DDB5477_SERIAL_PORT_DEFNS
macro_line|#endif
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&t;&bslash;&n;&t;IVR_SERIAL_PORT_DEFNS           &bslash;&n;&t;ITE_SERIAL_PORT_DEFNS           &bslash;&n;&t;ATLAS_SERIAL_PORT_DEFNS&t;&t;&bslash;&n;&t;EV96100_SERIAL_PORT_DEFNS&t;&bslash;&n;&t;JAZZ_SERIAL_PORT_DEFNS&t;&t;&bslash;&n;&t;STD_SERIAL_PORT_DEFNS&t;&t;&bslash;&n;&t;EXTRA_SERIAL_PORT_DEFNS&t;&t;&bslash;&n;&t;HUB6_SERIAL_PORT_DFNS&t;&t;&bslash;&n;&t;MOMENCO_OCELOT_SERIAL_PORT_DEFNS&bslash;&n;&t;AU1000_SERIAL_PORT_DEFNS&t;&bslash;&n;&t;DDB5477_SERIAL_PORT_DEFNS
eof
