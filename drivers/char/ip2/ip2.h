multiline_comment|/*******************************************************************************&n;*&n;*   (c) 1998 by Computone Corporation&n;*&n;********************************************************************************&n;*&n;*&n;*   PACKAGE:     Linux tty Device Driver for IntelliPort II family of multiport&n;*                serial I/O controllers.&n;*&n;*   DESCRIPTION: Driver constants for configuration and tuning&n;*&n;*   NOTES:&n;*&n;*******************************************************************************/
macro_line|#ifndef IP2_H
DECL|macro|IP2_H
mdefine_line|#define IP2_H
macro_line|#include &quot;ip2types.h&quot;
macro_line|#include &quot;i2cmd.h&quot;
multiline_comment|/*************/
multiline_comment|/* Constants */
multiline_comment|/*************/
multiline_comment|/* Device major numbers&n; * The first set are the major numbers allocated from the Linux Device Registry.&n; * This was expanded from 64 to 128 with version 2.0.26. If this code is built&n; * under earlier versions we use majors from the LOCAL/EXPERIMENTAL range.&n; */
macro_line|#if MAX_CHRDEV &gt; 64
DECL|macro|IP2_TTY_MAJOR
macro_line|#&t;define IP2_TTY_MAJOR      71
DECL|macro|IP2_CALLOUT_MAJOR
macro_line|#&t;define IP2_CALLOUT_MAJOR  72
DECL|macro|IP2_IPL_MAJOR
macro_line|#&t;define IP2_IPL_MAJOR      73
macro_line|#else
DECL|macro|IP2_TTY_MAJOR
macro_line|#&t;define IP2_TTY_MAJOR      60
DECL|macro|IP2_CALLOUT_MAJOR
macro_line|#&t;define IP2_CALLOUT_MAJOR  61
DECL|macro|IP2_IPL_MAJOR
macro_line|#&t;define IP2_IPL_MAJOR      62
macro_line|#endif
multiline_comment|/* Board configuration array.&n; * This array defines the hardware irq and address for up to IP2_MAX_BOARDS&n; * (4 supported per ip2_types.h) ISA board addresses and irqs MUST be specified,&n; * PCI and EISA boards are probed for and automagicly configed&n; * iff the addresses are set to 1 and 2 respectivily.&n; *    0x0100 - 0x03f0 == ISA&n; *&t;         1        == PCI&n; *&t;         2        == EISA&n; *&t;         0        == (skip this board)&n; * This array defines the hardware addresses for them. Special &n; * addresses are EISA and PCI which go sniffing for boards. &n;&n; * In a multiboard system the position in the array determines which port&n; * devices are assigned to each board: &n; *&t;&t;board 0 is assigned ttyF0.. to ttyF63, &n; *&t;&t;board 1 is assigned ttyF64  to ttyF127,&n; *&t;&t;board 2 is assigned ttyF128 to ttyF191,&n; *&t;&t;board 3 is assigned ttyF192 to ttyF255. &n; *&n; * In PCI and EISA bus systems each range is mapped to card in &n; * monotonically increasing slot number order, ISA position is as specified&n; * here.&n;&n; * If the irqs are ALL set to 0,0,0,0 all boards operate in &n; * polled mode. For interrupt operation ISA boards require that the IRQ be &n; * specified, while PCI and EISA boards any nonzero entry &n; * will enable interrupts using the BIOS configured irq for the board. &n; * An invalid irq entry will default to polled mode for that card and print&n; * console warning.&n; &n; * When the driver is loaded as a module these setting can be overridden on the &n; * modprobe command line or on an option line in /etc/modules.conf.&n; * If the driver is built-in the configuration must be &n; * set here for ISA cards and address set to 1 and 2 for PCI and EISA.&n; *&n; * Here is an example that shows most if not all possibe combinations:&n;&n; *static ip2config_t ip2config =&n; *{&n; *&t;{11,1,0,0},&t;&t;// irqs&n; *&t;{&t;&t;&t;&t;// Addresses&n; *&t;&t;0x0308,&t;&t;// Board 0, ttyF0   - ttyF63// ISA card at io=0x308, irq=11&n; *&t;&t;0x0001,&t;&t;// Board 1, ttyF64  - ttyF127//PCI card configured by BIOS&n; *&t;&t;0x0000,&t;&t;// Board 2, ttyF128 - ttyF191// Slot skipped&n; *&t;&t;0x0002&t;&t;// Board 3, ttyF192 - ttyF255//EISA card configured by BIOS&n; *&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; // but polled not irq driven&n; *&t;}&n; *};&n; */
multiline_comment|/* this structure is zeroed out because the suggested method is to configure&n;  * the driver as a module, set up the parameters with an options line in&n;  * /etc/modules.conf and load with modprobe, kerneld or kmod, the kernel&n;  * module loader&n;  */
DECL|variable|ip2config
r_static
id|ip2config_t
id|ip2config
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
singleline_comment|// irqs
(brace
singleline_comment|// Addresses
l_int|0x0000
comma
singleline_comment|// Board 0, ttyF0   - ttyF63
l_int|0x0000
comma
singleline_comment|// Board 1, ttyF64  - ttyF127
l_int|0x0000
comma
singleline_comment|// Board 2, ttyF128 - ttyF191
l_int|0x0000
singleline_comment|// Board 3, ttyF192 - ttyF255
)brace
)brace
suffix:semicolon
macro_line|#endif
eof
