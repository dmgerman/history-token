multiline_comment|/*  Driver for the Iomega MatchMaker parallel port SCSI HBA embedded in &n; * the Iomega ZIP Plus drive&n; * &n; * (c) 1998     David Campbell     campbell@torque.net&n; *&n; * Please note that I live in Perth, Western Australia. GMT+0800&n; */
macro_line|#ifndef _IMM_H
DECL|macro|_IMM_H
mdefine_line|#define _IMM_H
DECL|macro|IMM_VERSION
mdefine_line|#define   IMM_VERSION   &quot;2.05 (for Linux 2.4.0)&quot;
multiline_comment|/* &n; * 10 Apr 1998 (Good Friday) - Received EN144302 by email from Iomega.&n; * Scarry thing is the level of support from one of their managers.&n; * The onus is now on us (the developers) to shut up and start coding.&n; *                                              11Apr98 [ 0.10 ]&n; *&n; * --- SNIP ---&n; *&n; * It manages to find the drive which is a good start. Writing data during&n; * data phase is known to be broken (due to requirements of two byte writes).&n; * Removing &quot;Phase&quot; debug messages.&n; *&n; * PS: Took four hours of coding after I bought a drive.&n; *      ANZAC Day (Aus &quot;War Veterans Holiday&quot;)  25Apr98 [ 0.14 ]&n; *&n; * Ten minutes later after a few fixes.... (LITERALLY!!!)&n; * Have mounted disk, copied file, dismounted disk, remount disk, diff file&n; *                    -----  It actually works!!! -----&n; *                                              25Apr98 [ 0.15 ]&n; *&n; * Twenty minutes of mucking around, rearanged the IEEE negotiate mechanism.&n; * Now have byte mode working (only EPP and ECP to go now... :=)&n; *                                              26Apr98 [ 0.16 ]&n; *&n; * Thirty minutes of further coding results in EPP working on my machine.&n; *                                              27Apr98 [ 0.17 ]&n; *&n; * Due to work commitments and inability to get a &quot;true&quot; ECP mode functioning&n; * I have decided to code the parport support into imm.&n; *                                              09Jun98 [ 0.18 ]&n; *&n; * Driver is now out of beta testing.&n; * Support for parport has been added.&n; * Now distributed with the ppa driver.&n; *                                              12Jun98 [ 2.00 ]&n; *&n; * Err.. It appears that imm-2.00 was broken....&n; *                                              18Jun98 [ 2.01 ]&n; *&n; * Patch applied to sync this against the Linux 2.1.x kernel code&n; * Included qboot_zip.sh&n; *                                              21Jun98 [ 2.02 ]&n; *&n; * Other clean ups include the follow changes:&n; *    CONFIG_SCSI_PPA_HAVE_PEDANTIC =&gt; CONFIG_SCSI_IZIP_EPP16&n; *    added CONFIG_SCSI_IZIP_SLOW_CTR option&n; *                                                      [2.03]&n; *  Fix kernel panic on scsi timeout.&t;&t;20Aug00 [2.04]&n; *&n; *  Avoid io_request_lock problems.&n; *  John Cavan &lt;johncavan@home.com&gt;&t;&t;16Nov00 [2.05]&n; */
multiline_comment|/* ------ END OF USER CONFIGURABLE PARAMETERS ----- */
macro_line|#ifdef IMM_CODE
macro_line|#include  &lt;linux/config.h&gt;
macro_line|#include  &lt;linux/stddef.h&gt;
macro_line|#include  &lt;linux/module.h&gt;
macro_line|#include  &lt;linux/kernel.h&gt;
macro_line|#include  &lt;linux/tqueue.h&gt;
macro_line|#include  &lt;linux/ioport.h&gt;
macro_line|#include  &lt;linux/delay.h&gt;
macro_line|#include  &lt;linux/proc_fs.h&gt;
macro_line|#include  &lt;linux/stat.h&gt;
macro_line|#include  &lt;linux/blk.h&gt;
macro_line|#include  &lt;linux/sched.h&gt;
macro_line|#include  &lt;linux/interrupt.h&gt;
macro_line|#include  &lt;asm/io.h&gt;
macro_line|#include  &quot;sd.h&quot;
macro_line|#include  &quot;hosts.h&quot;
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
l_string|&quot;Autodetect&quot;
comma
l_string|&quot;SPP&quot;
comma
l_string|&quot;PS/2&quot;
comma
l_string|&quot;EPP 8 bit&quot;
comma
l_string|&quot;EPP 16 bit&quot;
comma
macro_line|#ifdef CONFIG_SCSI_IZIP_EPP16
l_string|&quot;EPP 16 bit&quot;
comma
macro_line|#else
l_string|&quot;EPP 32 bit&quot;
comma
macro_line|#endif
l_string|&quot;Unknown&quot;
)brace
suffix:semicolon
multiline_comment|/* This is a global option */
DECL|variable|imm_sg
r_int
id|imm_sg
op_assign
id|SG_ALL
suffix:semicolon
multiline_comment|/* enable/disable scatter-gather. */
multiline_comment|/* other options */
DECL|macro|IMM_CAN_QUEUE
mdefine_line|#define IMM_CAN_QUEUE   1&t;/* use &quot;queueing&quot; interface */
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
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|imm_in
c_func
(paren
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|imm_init
c_func
(paren
r_int
)paren
suffix:semicolon
r_static
r_void
id|imm_interrupt
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_static
r_int
id|imm_out
c_func
(paren
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#else
DECL|macro|imm_release
mdefine_line|#define imm_release 0
macro_line|#endif
r_int
id|imm_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|imm_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|imm_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|imm_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|imm_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|imm_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|imm_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|imm_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
DECL|macro|IMM
mdefine_line|#define IMM {&t;proc_name:&t;&t;&t;&quot;imm&quot;,&t;&t;&t;&bslash;&n;&t;&t;proc_info:&t;&t;&t;imm_proc_info,&t;&t;&bslash;&n;&t;&t;name:&t;&t;&t;&t;&quot;Iomega VPI2 (imm) interface&quot;,&bslash;&n;&t;&t;detect:&t;&t;&t;&t;imm_detect,&t;&t;&bslash;&n;&t;&t;release:&t;&t;&t;imm_release,&t;&t;&bslash;&n;&t;&t;command:&t;&t;&t;imm_command,&t;&t;&bslash;&n;&t;&t;queuecommand:&t;&t;&t;imm_queuecommand,&t;&bslash;&n;                eh_abort_handler:               imm_abort,              &bslash;&n;                eh_device_reset_handler:        NULL,                   &bslash;&n;                eh_bus_reset_handler:           imm_reset,              &bslash;&n;                eh_host_reset_handler:          imm_reset,              &bslash;&n;&t;&t;use_new_eh_code:&t;&t;1,&t;&t;&t;&bslash;&n;&t;&t;bios_param:&t;&t;        imm_biosparam,&t;&t;&bslash;&n;&t;&t;this_id:&t;&t;&t;7,&t;&t;&t;&bslash;&n;&t;&t;sg_tablesize:&t;&t;&t;SG_ALL,&t;&t;&t;&bslash;&n;&t;&t;cmd_per_lun:&t;&t;&t;1,&t;&t;&t;&bslash;&n;&t;&t;use_clustering:&t;&t;&t;ENABLE_CLUSTERING&t;&bslash;&n;}
macro_line|#endif&t;&t;&t;&t;/* _IMM_H */
eof
