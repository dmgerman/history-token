multiline_comment|/********************************************************&n;* Header file for eata_pio.c Linux EATA-PIO SCSI driver *&n;* (c) 1993-96 Michael Neuffer  &t;                        *&n;*********************************************************&n;* last change: 96/05/05&t;&t;&t;&t;&t;*&n;********************************************************/
macro_line|#ifndef _EATA_PIO_H
DECL|macro|_EATA_PIO_H
mdefine_line|#define _EATA_PIO_H
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &lt;scsi/scsicam.h&gt;
macro_line|#ifndef HOSTS_C
macro_line|#include &quot;eata_generic.h&quot;
DECL|macro|VER_MAJOR
mdefine_line|#define VER_MAJOR 0
DECL|macro|VER_MINOR
mdefine_line|#define VER_MINOR 0
DECL|macro|VER_SUB
mdefine_line|#define VER_SUB&t;  &quot;1b&quot;
multiline_comment|/************************************************************************&n; * Here you can switch parts of the code on and of&t;&t;&t;*&n; ************************************************************************/
DECL|macro|VERBOSE_SETUP
mdefine_line|#define VERBOSE_SETUP&t;&t;&t;/* show startup screen of 2001 */
DECL|macro|ALLOW_DMA_BOARDS
mdefine_line|#define ALLOW_DMA_BOARDS 1
multiline_comment|/************************************************************************&n; * Debug options.&t;&t;&t;&t;&t;&t;&t;* &n; * Enable DEBUG and whichever options you require.&t;&t;&t;*&n; ************************************************************************/
DECL|macro|DEBUG_EATA
mdefine_line|#define DEBUG_EATA&t;1   /* Enable debug code.&t;&t;&t;*/
DECL|macro|DPT_DEBUG
mdefine_line|#define DPT_DEBUG&t;0   /* Bobs special&t;&t;&t;&t;*/
DECL|macro|DBG_DELAY
mdefine_line|#define DBG_DELAY&t;0   /* Build in delays so debug messages can be&n;                             * be read before they vanish of the top of&n;                             * the screen!&n;                             */
DECL|macro|DBG_PROBE
mdefine_line|#define DBG_PROBE&t;0   /* Debug probe routines.&t;&t;&t;*/
DECL|macro|DBG_ISA
mdefine_line|#define DBG_ISA&t;&t;0   /* Trace ISA routines&t;&t;&t;*/ 
DECL|macro|DBG_EISA
mdefine_line|#define DBG_EISA&t;0   /* Trace EISA routines&t;&t;&t;*/ 
DECL|macro|DBG_PCI
mdefine_line|#define DBG_PCI&t;&t;0   /* Trace PCI routines&t;&t;&t;*/ 
DECL|macro|DBG_PIO
mdefine_line|#define DBG_PIO&t;&t;0   /* Trace get_config_PIO&t;&t;&t;*/
DECL|macro|DBG_COM
mdefine_line|#define DBG_COM&t;&t;0   /* Trace command call&t;&t;&t;*/
DECL|macro|DBG_QUEUE
mdefine_line|#define DBG_QUEUE&t;0   /* Trace command queueing.&t;&t;&t;*/
DECL|macro|DBG_INTR
mdefine_line|#define DBG_INTR&t;0   /* Trace interrupt service routine.&t;&t;*/
DECL|macro|DBG_INTR2
mdefine_line|#define DBG_INTR2&t;0   /* Trace interrupt service routine.&t;&t;*/
DECL|macro|DBG_PROC
mdefine_line|#define DBG_PROC&t;0   /* Debug proc-fs related statistics&t;&t;*/
DECL|macro|DBG_PROC_WRITE
mdefine_line|#define DBG_PROC_WRITE&t;0
DECL|macro|DBG_REGISTER
mdefine_line|#define DBG_REGISTER&t;0   /* */
DECL|macro|DBG_ABNORM
mdefine_line|#define DBG_ABNORM&t;1   /* Debug abnormal actions (reset, abort)&t;*/
macro_line|#if DEBUG_EATA 
DECL|macro|DBG
mdefine_line|#define DBG(x, y)   if ((x)) {y;} 
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x, y)
macro_line|#endif
macro_line|#endif /* !HOSTS_C */
r_int
id|eata_pio_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|eata_pio_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|eata_pio_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
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
r_int
id|eata_pio_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|eata_pio_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
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
macro_line|#ifdef MODULE
r_int
id|eata_pio_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|eata_pio_release
mdefine_line|#define eata_pio_release NULL  
macro_line|#endif
DECL|macro|EATA_PIO
mdefine_line|#define EATA_PIO {&t;&t;&t;&t;&t;&t;&bslash;&n;    proc_info:         eata_pio_proc_info, /* procinfo&t;  */&t;&bslash;&n;    name:              &quot;EATA (Extended Attachment) PIO driver&quot;,&t;&bslash;&n;    detect:            eata_pio_detect,&t;&t;&t;&t;&bslash;&n;    release:           eata_pio_release,&t;&t;&t;&bslash;&n;    queuecommand:      eata_pio_queue,&t;&t;&t;&t;&bslash;&n;    abort:             eata_pio_abort,&t;&t;&t;&t;&bslash;&n;    reset:             eata_pio_reset,&t;&t;&t;&t;&bslash;&n;    bios_param:        scsicam_bios_param,&t;&t;&t;&bslash;&n;    unchecked_isa_dma: 1,&t;    /* True if ISA  */&t;&t;&bslash;&n;    use_clustering:    ENABLE_CLUSTERING }
macro_line|#endif /* _EATA_PIO_H */
multiline_comment|/*&n; * Overrides for Emacs so that we almost follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * tab-width: 8&n; * End:&n; */
eof
