multiline_comment|/* $Id: serial.h,v 1.2 2000/01/17 23:32:47 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SERIAL_H
DECL|macro|_ASM_SERIAL_H
mdefine_line|#define _ASM_SERIAL_H
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (1843200 / 16)
multiline_comment|/*&n; * Note about serial ports and consoles:&n; * For console output, everyone uses the IOC3 UARTA (offset 0x178)&n; * connected to the master node (look in ip27_setup_console() and&n; * ip27prom_console_write()).&n; *&n; * For serial (/dev/ttyS0 etc), we can not have hardcoded serial port&n; * addresses on a partitioned machine. Since we currently use the ioc3&n; * serial ports, we use dynamic serial port discovery that the serial.c&n; * driver uses for pci/pnp ports (there is an entry for the SGI ioc3&n; * boards in pci_boards[]). Unfortunately, UARTA&squot;s pio address is greater&n; * than UARTB&squot;s, although UARTA on o200s has traditionally been known as&n; * port 0. So, we just use one serial port from each ioc3 (since the&n; * serial driver adds addresses to get to higher ports).&n; *&n; * The first one to do a register_console becomes the preferred console&n; * (if there is no kernel command line console= directive). /dev/console&n; * (ie 5, 1) is then &quot;aliased&quot; into the device number returned by the &n; * &quot;device&quot; routine referred to in this console structure &n; * (ip27prom_console_dev).&n; *&n; * Also look in ip27-pci.c:pci_fixuop_ioc3() for some comments on working&n; * around ioc3 oddities in this respect.&n; *&n; * The IOC3 serials use a 22MHz clock rate with an additional divider by 3.&n; * (IOC3_BAUD = (22000000 / (3*16)))&n; */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;64
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS
macro_line|#endif /* _ASM_SERIAL_H */
eof
