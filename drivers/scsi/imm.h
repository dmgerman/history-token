multiline_comment|/*  Driver for the Iomega MatchMaker parallel port SCSI HBA embedded in &n; * the Iomega ZIP Plus drive&n; * &n; * (c) 1998     David Campbell     campbell@torque.net&n; *&n; * Please note that I live in Perth, Western Australia. GMT+0800&n; */
macro_line|#ifndef _IMM_H
DECL|macro|_IMM_H
mdefine_line|#define _IMM_H
DECL|macro|IMM_VERSION
mdefine_line|#define   IMM_VERSION   &quot;2.05 (for Linux 2.4.0)&quot;
multiline_comment|/* &n; * 10 Apr 1998 (Good Friday) - Received EN144302 by email from Iomega.&n; * Scarry thing is the level of support from one of their managers.&n; * The onus is now on us (the developers) to shut up and start coding.&n; *                                              11Apr98 [ 0.10 ]&n; *&n; * --- SNIP ---&n; *&n; * It manages to find the drive which is a good start. Writing data during&n; * data phase is known to be broken (due to requirements of two byte writes).&n; * Removing &quot;Phase&quot; debug messages.&n; *&n; * PS: Took four hours of coding after I bought a drive.&n; *      ANZAC Day (Aus &quot;War Veterans Holiday&quot;)  25Apr98 [ 0.14 ]&n; *&n; * Ten minutes later after a few fixes.... (LITERALLY!!!)&n; * Have mounted disk, copied file, dismounted disk, remount disk, diff file&n; *                    -----  It actually works!!! -----&n; *                                              25Apr98 [ 0.15 ]&n; *&n; * Twenty minutes of mucking around, rearanged the IEEE negotiate mechanism.&n; * Now have byte mode working (only EPP and ECP to go now... :=)&n; *                                              26Apr98 [ 0.16 ]&n; *&n; * Thirty minutes of further coding results in EPP working on my machine.&n; *                                              27Apr98 [ 0.17 ]&n; *&n; * Due to work commitments and inability to get a &quot;true&quot; ECP mode functioning&n; * I have decided to code the parport support into imm.&n; *                                              09Jun98 [ 0.18 ]&n; *&n; * Driver is now out of beta testing.&n; * Support for parport has been added.&n; * Now distributed with the ppa driver.&n; *                                              12Jun98 [ 2.00 ]&n; *&n; * Err.. It appears that imm-2.00 was broken....&n; *                                              18Jun98 [ 2.01 ]&n; *&n; * Patch applied to sync this against the Linux 2.1.x kernel code&n; * Included qboot_zip.sh&n; *                                              21Jun98 [ 2.02 ]&n; *&n; * Other clean ups include the follow changes:&n; *    CONFIG_SCSI_PPA_HAVE_PEDANTIC =&gt; CONFIG_SCSI_IZIP_EPP16&n; *    added CONFIG_SCSI_IZIP_SLOW_CTR option&n; *                                                      [2.03]&n; *  Fix kernel panic on scsi timeout.&t;&t;20Aug00 [2.04]&n; *&n; *  Avoid io_request_lock problems.&n; *  John Cavan &lt;johncavan@home.com&gt;&t;&t;16Nov00 [2.05]&n; */
multiline_comment|/* ------ END OF USER CONFIGURABLE PARAMETERS ----- */
macro_line|#include  &lt;linux/config.h&gt;
macro_line|#include  &lt;linux/stddef.h&gt;
macro_line|#include  &lt;linux/module.h&gt;
macro_line|#include  &lt;linux/kernel.h&gt;
macro_line|#include  &lt;linux/ioport.h&gt;
macro_line|#include  &lt;linux/delay.h&gt;
macro_line|#include  &lt;linux/proc_fs.h&gt;
macro_line|#include  &lt;linux/stat.h&gt;
macro_line|#include  &lt;linux/blkdev.h&gt;
macro_line|#include  &lt;linux/sched.h&gt;
macro_line|#include  &lt;linux/interrupt.h&gt;
macro_line|#include  &lt;asm/io.h&gt;
macro_line|#include  &lt;scsi/scsi_host.h&gt;
multiline_comment|/* batteries not included :-) */
multiline_comment|/*&n; * modes in which the driver can operate &n; */
DECL|macro|IMM_AUTODETECT
mdefine_line|#define   IMM_AUTODETECT        0&t;/* Autodetect mode                */
DECL|macro|IMM_NIBBLE
mdefine_line|#define   IMM_NIBBLE            1&t;/* work in standard 4 bit mode    */
DECL|macro|IMM_PS2
mdefine_line|#define   IMM_PS2               2&t;/* PS/2 byte mode         */
DECL|macro|IMM_EPP_8
mdefine_line|#define   IMM_EPP_8             3&t;/* EPP mode, 8 bit                */
DECL|macro|IMM_EPP_16
mdefine_line|#define   IMM_EPP_16            4&t;/* EPP mode, 16 bit               */
DECL|macro|IMM_EPP_32
mdefine_line|#define   IMM_EPP_32            5&t;/* EPP mode, 32 bit               */
DECL|macro|IMM_UNKNOWN
mdefine_line|#define   IMM_UNKNOWN           6&t;/* Just in case...                */
DECL|variable|IMM_MODE_STRING
r_static
r_char
op_star
id|IMM_MODE_STRING
(braket
)braket
op_assign
(brace
(braket
id|IMM_AUTODETECT
)braket
op_assign
l_string|&quot;Autodetect&quot;
comma
(braket
id|IMM_NIBBLE
)braket
op_assign
l_string|&quot;SPP&quot;
comma
(braket
id|IMM_PS2
)braket
op_assign
l_string|&quot;PS/2&quot;
comma
(braket
id|IMM_EPP_8
)braket
op_assign
l_string|&quot;EPP 8 bit&quot;
comma
(braket
id|IMM_EPP_16
)braket
op_assign
l_string|&quot;EPP 16 bit&quot;
comma
macro_line|#ifdef CONFIG_SCSI_IZIP_EPP16
(braket
id|IMM_EPP_32
)braket
op_assign
l_string|&quot;EPP 16 bit&quot;
comma
macro_line|#else
(braket
id|IMM_EPP_32
)braket
op_assign
l_string|&quot;EPP 32 bit&quot;
comma
macro_line|#endif
(braket
id|IMM_UNKNOWN
)braket
op_assign
l_string|&quot;Unknown&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* other options */
DECL|macro|IMM_BURST_SIZE
mdefine_line|#define IMM_BURST_SIZE&t;512&t;/* data burst size */
DECL|macro|IMM_SELECT_TMO
mdefine_line|#define IMM_SELECT_TMO  500&t;/* 500 how long to wait for target ? */
DECL|macro|IMM_SPIN_TMO
mdefine_line|#define IMM_SPIN_TMO    5000&t;/* 50000 imm_wait loop limiter */
DECL|macro|IMM_DEBUG
mdefine_line|#define IMM_DEBUG&t;0&t;/* debugging option */
DECL|macro|IN_EPP_MODE
mdefine_line|#define IN_EPP_MODE(x) (x == IMM_EPP_8 || x == IMM_EPP_16 || x == IMM_EPP_32)
multiline_comment|/* args to imm_connect */
DECL|macro|CONNECT_EPP_MAYBE
mdefine_line|#define CONNECT_EPP_MAYBE 1
DECL|macro|CONNECT_NORMAL
mdefine_line|#define CONNECT_NORMAL  0
DECL|macro|r_dtr
mdefine_line|#define r_dtr(x)        (unsigned char)inb((x))
DECL|macro|r_str
mdefine_line|#define r_str(x)        (unsigned char)inb((x)+1)
DECL|macro|r_ctr
mdefine_line|#define r_ctr(x)        (unsigned char)inb((x)+2)
DECL|macro|r_epp
mdefine_line|#define r_epp(x)        (unsigned char)inb((x)+4)
DECL|macro|r_fifo
mdefine_line|#define r_fifo(x)       (unsigned char)inb((x))   /* x must be base_hi */
multiline_comment|/* On PCI is: base+0x400 != base_hi */
DECL|macro|r_ecr
mdefine_line|#define r_ecr(x)        (unsigned char)inb((x)+2) /* x must be base_hi */
DECL|macro|w_dtr
mdefine_line|#define w_dtr(x,y)      outb(y, (x))
DECL|macro|w_str
mdefine_line|#define w_str(x,y)      outb(y, (x)+1)
DECL|macro|w_epp
mdefine_line|#define w_epp(x,y)      outb(y, (x)+4)
DECL|macro|w_fifo
mdefine_line|#define w_fifo(x,y)     outb(y, (x))     /* x must be base_hi */
DECL|macro|w_ecr
mdefine_line|#define w_ecr(x,y)      outb(y, (x)+0x2) /* x must be base_hi */
macro_line|#ifdef CONFIG_SCSI_IZIP_SLOW_CTR
DECL|macro|w_ctr
mdefine_line|#define w_ctr(x,y)      outb_p(y, (x)+2)
macro_line|#else
DECL|macro|w_ctr
mdefine_line|#define w_ctr(x,y)      outb(y, (x)+2)
macro_line|#endif
r_static
r_int
id|imm_engine
c_func
(paren
id|imm_struct
op_star
comma
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _IMM_H */
eof
