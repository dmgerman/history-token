multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SERIAL_H
DECL|macro|_ASM_SERIAL_H
mdefine_line|#define _ASM_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (1843200 / 16)
macro_line|#ifdef CONFIG_HAVE_STD_PC_SERIAL_PORT
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
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&t;&bslash;&n;&t;/* UART CLK   PORT IRQ     FLAGS        */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3F8, 4, STD_COM_FLAGS },&t;/* ttyS0 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2F8, 3, STD_COM_FLAGS },&t;/* ttyS1 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x3E8, 4, STD_COM_FLAGS },&t;/* ttyS2 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2E8, 3, STD_COM4_FLAGS },&t;/* ttyS3 */
macro_line|#else /* CONFIG_HAVE_STD_PC_SERIAL_PORTS */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS
macro_line|#endif /* CONFIG_HAVE_STD_PC_SERIAL_PORTS */
macro_line|#ifdef CONFIG_MIPS_SEAD
macro_line|#include &lt;asm/mips-boards/sead.h&gt;
macro_line|#include &lt;asm/mips-boards/seadint.h&gt;
DECL|macro|SEAD_SERIAL_PORT_DEFNS
mdefine_line|#define SEAD_SERIAL_PORT_DEFNS                  &bslash;&n;&t;/* UART CLK   PORT IRQ     FLAGS        */                      &bslash;&n;&t;{ 0, SEAD_BASE_BAUD, SEAD_UART0_REGS_BASE, SEADINT_UART0, STD_COM_FLAGS },     /* ttyS0 */
macro_line|#else
DECL|macro|SEAD_SERIAL_PORT_DEFNS
mdefine_line|#define SEAD_SERIAL_PORT_DEFNS
macro_line|#endif
macro_line|#ifdef CONFIG_MOMENCO_OCELOT_C
multiline_comment|/* Ordinary NS16552 duart with a 20MHz crystal.  */
DECL|macro|OCELOT_C_BASE_BAUD
mdefine_line|#define OCELOT_C_BASE_BAUD ( 20000000 / 16 )
DECL|macro|OCELOT_C_SERIAL1_IRQ
mdefine_line|#define OCELOT_C_SERIAL1_IRQ&t;80
DECL|macro|OCELOT_C_SERIAL1_BASE
mdefine_line|#define OCELOT_C_SERIAL1_BASE&t;0xfd000020
DECL|macro|OCELOT_C_SERIAL2_IRQ
mdefine_line|#define OCELOT_C_SERIAL2_IRQ&t;81
DECL|macro|OCELOT_C_SERIAL2_BASE
mdefine_line|#define OCELOT_C_SERIAL2_BASE&t;0xfd000000
DECL|macro|_OCELOT_C_SERIAL_INIT
mdefine_line|#define _OCELOT_C_SERIAL_INIT(int, base)&t;&t;&t;&t;&bslash;&n;&t;{ .baud_base&t;&t;= OCELOT_C_BASE_BAUD,&t;&t;&t;&bslash;&n;&t;  .irq&t;&t;&t;= (int),&t;&t;&t;&t;&bslash;&n;&t;  .flags&t;&t;= STD_COM_FLAGS,&t;&t;&t;&bslash;&n;&t;  .iomem_base&t;&t;= (u8 *) base,&t;&t;&t;&t;&bslash;&n;&t;  .iomem_reg_shift&t;= 2,&t;&t;&t;&t;&t;&bslash;&n;&t;  .io_type&t;&t;= SERIAL_IO_MEM&t;&t;&t;&t;&bslash;&n;&t; }
DECL|macro|MOMENCO_OCELOT_C_SERIAL_PORT_DEFNS
mdefine_line|#define MOMENCO_OCELOT_C_SERIAL_PORT_DEFNS&t;&t;&t;&t;&bslash;&n;&t;_OCELOT_C_SERIAL_INIT(OCELOT_C_SERIAL1_IRQ, OCELOT_C_SERIAL1_BASE), &bslash;&n;&t;_OCELOT_C_SERIAL_INIT(OCELOT_C_SERIAL2_IRQ, OCELOT_C_SERIAL2_BASE)
macro_line|#else
DECL|macro|MOMENCO_OCELOT_C_SERIAL_PORT_DEFNS
mdefine_line|#define MOMENCO_OCELOT_C_SERIAL_PORT_DEFNS
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_IP27
multiline_comment|/*&n; * Note about serial ports and consoles:&n; * For console output, everyone uses the IOC3 UARTA (offset 0x178)&n; * connected to the master node (look in ip27_setup_console() and&n; * ip27prom_console_write()).&n; *&n; * For serial (/dev/ttyS0 etc), we can not have hardcoded serial port&n; * addresses on a partitioned machine. Since we currently use the ioc3&n; * serial ports, we use dynamic serial port discovery that the serial.c&n; * driver uses for pci/pnp ports (there is an entry for the SGI ioc3&n; * boards in pci_boards[]). Unfortunately, UARTA&squot;s pio address is greater&n; * than UARTB&squot;s, although UARTA on o200s has traditionally been known as&n; * port 0. So, we just use one serial port from each ioc3 (since the&n; * serial driver adds addresses to get to higher ports).&n; *&n; * The first one to do a register_console becomes the preferred console&n; * (if there is no kernel command line console= directive). /dev/console&n; * (ie 5, 1) is then &quot;aliased&quot; into the device number returned by the&n; * &quot;device&quot; routine referred to in this console structure&n; * (ip27prom_console_dev).&n; *&n; * Also look in ip27-pci.c:pci_fixuop_ioc3() for some comments on working&n; * around ioc3 oddities in this respect.&n; *&n; * The IOC3 serials use a 22MHz clock rate with an additional divider by 3.&n; * (IOC3_BAUD = (22000000 / (3*16)))&n; *&n; * At the moment this is only a skeleton definition as we register all serials&n; * at runtime.&n; */
DECL|macro|IP27_SERIAL_PORT_DEFNS
mdefine_line|#define IP27_SERIAL_PORT_DEFNS
macro_line|#else
DECL|macro|IP27_SERIAL_PORT_DEFNS
mdefine_line|#define IP27_SERIAL_PORT_DEFNS
macro_line|#endif /* CONFIG_SGI_IP27 */
macro_line|#ifdef CONFIG_SGI_IP32
macro_line|#include &lt;asm/ip32/ip32_ints.h&gt;
multiline_comment|/*&n; * The IP32 (SGI O2) has standard serial ports (UART 16550A) mapped in memory&n; */
multiline_comment|/* Standard COM flags (except for COM4, because of the 8514 problem) */
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST | ASYNC_AUTO_IRQ)
DECL|macro|STD_COM4_FLAGS
mdefine_line|#define STD_COM4_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF/* | ASYNC_SKIP_TEST*/)
DECL|macro|STD_COM4_FLAGS
mdefine_line|#define STD_COM4_FLAGS ASYNC_BOOT_AUTOCONF
macro_line|#endif
DECL|macro|IP32_SERIAL_PORT_DEFNS
mdefine_line|#define IP32_SERIAL_PORT_DEFNS&t;&t;&t;&t;&bslash;&n;        { .baud_base = BASE_BAUD,&t;&t;&t;&t;&bslash;&n;&t;  .irq = MACEISA_SERIAL1_IRQ,&t;&t;&t;&bslash;&n;          .flags = STD_COM_FLAGS,&t;&t;&t;&t;&bslash;&n;          .iomem_base = (u8*)MACE_BASE+MACEISA_SER1_BASE,&t;&bslash;&n;          .iomem_reg_shift = 8,&t;&t;&t;&t;&bslash;&n;          .io_type = SERIAL_IO_MEM},                      &bslash;&n;        { .baud_base = BASE_BAUD,&t;&t;&t;&t;&bslash;&n;&t;  .irq = MACEISA_SERIAL2_IRQ,&t;&t;&t;&bslash;&n;          .flags = STD_COM_FLAGS,&t;&t;&t;&t;&bslash;&n;          .iomem_base = (u8*)MACE_BASE+MACEISA_SER2_BASE,&t;&bslash;&n;          .iomem_reg_shift = 8,&t;&t;&t;&t;&bslash;&n;          .io_type = SERIAL_IO_MEM},
macro_line|#else
DECL|macro|IP32_SERIAL_PORT_DEFNS
mdefine_line|#define IP32_SERIAL_PORT_DEFNS
macro_line|#endif /* CONFIG_SGI_IP31 */
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&t;&t;&t;&bslash;&n;&t;IP27_SERIAL_PORT_DEFNS&t;&t;&t;&t;&bslash;&n;&t;IP32_SERIAL_PORT_DEFNS&t;&t;&t;&t;&bslash;&n;&t;MOMENCO_OCELOT_C_SERIAL_PORT_DEFNS&t;&t;&bslash;&n;&t;SEAD_SERIAL_PORT_DEFNS&t;&t;&t;&t;&bslash;&n;&t;STD_SERIAL_PORT_DEFNS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;64
macro_line|#endif /* _ASM_SERIAL_H */
eof
