multiline_comment|/********************************************************&n;* Header file for eata_pio.c Linux EATA-PIO SCSI driver *&n;* (c) 1993-96 Michael Neuffer  &t;                        *&n;*********************************************************&n;* last change: 2002/11/02&t;&t;&t;&t;*&n;********************************************************/
macro_line|#ifndef _EATA_PIO_H
DECL|macro|_EATA_PIO_H
mdefine_line|#define _EATA_PIO_H
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &lt;scsi/scsicam.h&gt;
macro_line|#include &quot;eata_generic.h&quot;
DECL|macro|VER_MAJOR
mdefine_line|#define VER_MAJOR 0
DECL|macro|VER_MINOR
mdefine_line|#define VER_MINOR 0
DECL|macro|VER_SUB
mdefine_line|#define VER_SUB&t;  &quot;1b&quot;
multiline_comment|/************************************************************************&n; * Here you can switch parts of the code on and of&t;&t;&t;*&n; ************************************************************************/
DECL|macro|VERBOSE_SETUP
mdefine_line|#define VERBOSE_SETUP&t;&t;/* show startup screen of 2001 */
DECL|macro|ALLOW_DMA_BOARDS
mdefine_line|#define ALLOW_DMA_BOARDS 1
multiline_comment|/************************************************************************&n; * Debug options.&t;&t;&t;&t;&t;&t;&t;* &n; * Enable DEBUG and whichever options you require.&t;&t;&t;*&n; ************************************************************************/
DECL|macro|DEBUG_EATA
mdefine_line|#define DEBUG_EATA&t;1&t;/* Enable debug code.                       */
DECL|macro|DPT_DEBUG
mdefine_line|#define DPT_DEBUG&t;0&t;/* Bobs special                             */
DECL|macro|DBG_DELAY
mdefine_line|#define DBG_DELAY&t;0&t;/* Build in delays so debug messages can be&n;&t;&t;&t;&t; * be read before they vanish of the top of&n;&t;&t;&t;&t; * the screen!&n;&t;&t;&t;&t; */
DECL|macro|DBG_PROBE
mdefine_line|#define DBG_PROBE&t;0&t;/* Debug probe routines.                    */
DECL|macro|DBG_ISA
mdefine_line|#define DBG_ISA&t;&t;0&t;/* Trace ISA routines                       */
DECL|macro|DBG_EISA
mdefine_line|#define DBG_EISA&t;0&t;/* Trace EISA routines                      */
DECL|macro|DBG_PCI
mdefine_line|#define DBG_PCI&t;&t;0&t;/* Trace PCI routines                       */
DECL|macro|DBG_PIO
mdefine_line|#define DBG_PIO&t;&t;0&t;/* Trace get_config_PIO                     */
DECL|macro|DBG_COM
mdefine_line|#define DBG_COM&t;&t;0&t;/* Trace command call                       */
DECL|macro|DBG_QUEUE
mdefine_line|#define DBG_QUEUE&t;0&t;/* Trace command queueing.                  */
DECL|macro|DBG_INTR
mdefine_line|#define DBG_INTR&t;0&t;/* Trace interrupt service routine.         */
DECL|macro|DBG_INTR2
mdefine_line|#define DBG_INTR2&t;0&t;/* Trace interrupt service routine.         */
DECL|macro|DBG_PROC
mdefine_line|#define DBG_PROC&t;0&t;/* Debug proc-fs related statistics         */
DECL|macro|DBG_PROC_WRITE
mdefine_line|#define DBG_PROC_WRITE&t;0
DECL|macro|DBG_REGISTER
mdefine_line|#define DBG_REGISTER&t;0&t;/* */
DECL|macro|DBG_ABNORM
mdefine_line|#define DBG_ABNORM&t;1&t;/* Debug abnormal actions (reset, abort)    */
macro_line|#if DEBUG_EATA
DECL|macro|DBG
mdefine_line|#define DBG(x, y)   if ((x)) {y;}
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x, y)
macro_line|#endif
r_static
r_int
id|eata_pio_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_static
r_int
id|eata_pio_queue
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
r_static
r_int
id|eata_pio_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|eata_pio_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|eata_pio_proc_info
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
r_static
r_int
id|eata_pio_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|macro|EATA_PIO
mdefine_line|#define EATA_PIO {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.proc_info         &t;= eata_pio_proc_info, /* procinfo&t;  */&t;&bslash;&n;&t;.name              &t;= &quot;EATA (Extended Attachment) PIO driver&quot;,&bslash;&n;&t;.detect            &t;= eata_pio_detect,&t;&t;&t;&bslash;&n;&t;.release           &t;= eata_pio_release,&t;&t;&t;&bslash;&n;&t;.queuecommand      &t;= eata_pio_queue,&t;&t;&t;&t;&bslash;&n;&t;.eh_abort_handler  &t;= eata_pio_abort,&t;&t;&t;&t;&bslash;&n;&t;.eh_host_reset_handler&t;= eata_pio_host_reset,&t;&t;&t;&bslash;&n;&t;.use_clustering    &t;= ENABLE_CLUSTERING &t;&t;&t;&bslash;&n;}
macro_line|#endif&t;&t;&t;&t;/* _EATA_PIO_H */
eof
