multiline_comment|/********************************************************&n;* Header file for eata_dma.c Linux EATA-DMA SCSI driver *&n;* (c) 1993-96 Michael Neuffer                           *&n;*             mike@i-Connect.Net                        *&n;*             neuffer@mail.uni-mainz.de                 *&n;*********************************************************&n;* last change: 96/10/14                                 *&n;********************************************************/
macro_line|#ifndef _EATA_DMA_H
DECL|macro|_EATA_DMA_H
mdefine_line|#define _EATA_DMA_H
macro_line|#include &quot;eata_generic.h&quot;
DECL|macro|VER_MAJOR
mdefine_line|#define VER_MAJOR 2
DECL|macro|VER_MINOR
mdefine_line|#define VER_MINOR 5
DECL|macro|VER_SUB
mdefine_line|#define VER_SUB   &quot;9b&quot;
multiline_comment|/************************************************************************&n; * Here you can switch parts of the code on and of                      *&n; ************************************************************************/
DECL|macro|CHECKPAL
mdefine_line|#define CHECKPAL        0        /* EISA pal checking on/off            */
DECL|macro|CHECK_BLINK
mdefine_line|#define CHECK_BLINK     1        /* Switch Blink state check off, might *&n;                                  * be nessessary for some MIPS machines*/ 
DECL|macro|CRIPPLE_QUEUE
mdefine_line|#define CRIPPLE_QUEUE   0        /* Only enable this if the interrupt &n;                                  * controller on your motherboard is &n;                                  * broken and you are experiencing &n;                                  * massive interrupt losses */
multiline_comment|/************************************************************************&n; * Debug options.                                                       * &n; * Enable DEBUG and whichever options you require.                      *&n; ************************************************************************/
DECL|macro|DEBUG_EATA
mdefine_line|#define DEBUG_EATA      1       /* Enable debug code.                   */
DECL|macro|DPT_DEBUG
mdefine_line|#define DPT_DEBUG       0       /* Bobs special                         */
DECL|macro|DBG_DELAY
mdefine_line|#define DBG_DELAY       0       /* Build in delays so debug messages can be&n;&t;&t;&t;&t; * be read before they vanish of the top of&n;&t;&t;&t;&t; * the screen!                          */
DECL|macro|DBG_PROBE
mdefine_line|#define DBG_PROBE       0       /* Debug probe routines.                */
DECL|macro|DBG_PCI
mdefine_line|#define DBG_PCI         0       /* Trace PCI routines                   */
DECL|macro|DBG_EISA
mdefine_line|#define DBG_EISA        0       /* Trace EISA routines                  */
DECL|macro|DBG_ISA
mdefine_line|#define DBG_ISA         0       /* Trace ISA routines                   */ 
DECL|macro|DBG_BLINK
mdefine_line|#define DBG_BLINK       0       /* Trace Blink check                    */
DECL|macro|DBG_PIO
mdefine_line|#define DBG_PIO         0       /* Trace get_config_PIO                 */
DECL|macro|DBG_COM
mdefine_line|#define DBG_COM         0       /* Trace command call                   */
DECL|macro|DBG_QUEUE
mdefine_line|#define DBG_QUEUE       0       /* Trace command queueing.              */
DECL|macro|DBG_QUEUE2
mdefine_line|#define DBG_QUEUE2      0       /* Trace command queueing SG.           */
DECL|macro|DBG_INTR
mdefine_line|#define DBG_INTR        0       /* Trace interrupt service routine.     */
DECL|macro|DBG_INTR2
mdefine_line|#define DBG_INTR2       0       /* Trace interrupt service routine.     */
DECL|macro|DBG_INTR3
mdefine_line|#define DBG_INTR3       0       /* Trace get_board_data interrupts.     */
DECL|macro|DBG_REQSENSE
mdefine_line|#define DBG_REQSENSE    0       /* Trace request sense commands         */     
DECL|macro|DBG_RESET
mdefine_line|#define DBG_RESET       0       /* Trace reset calls                    */     
DECL|macro|DBG_STATUS
mdefine_line|#define DBG_STATUS      0       /* Trace status generation              */
DECL|macro|DBG_PROC
mdefine_line|#define DBG_PROC        0       /* Debug proc-fs related statistics     */
DECL|macro|DBG_PROC_WRITE
mdefine_line|#define DBG_PROC_WRITE  0
DECL|macro|DBG_REGISTER
mdefine_line|#define DBG_REGISTER    0       /* */
DECL|macro|DBG_ABNORM
mdefine_line|#define DBG_ABNORM      1       /* Debug abnormal actions (reset, abort)*/
macro_line|#if DEBUG_EATA 
DECL|macro|DBG
mdefine_line|#define DBG(x, y)   if ((x)) {y;} 
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x, y)
macro_line|#endif
r_int
id|eata_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|eata_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|eata_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|eata_queue
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
id|eata_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|eata_reset
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
id|eata_proc_info
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
id|eata_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|eata_release
mdefine_line|#define eata_release NULL  
macro_line|#endif
macro_line|#include &lt;scsi/scsicam.h&gt;
DECL|macro|EATA_DMA
mdefine_line|#define EATA_DMA {                                      &bslash;&n;        proc_info:         eata_proc_info,     /* procinfo       */ &bslash;&n;        name:              &quot;EATA (Extended Attachment) HBA driver&quot;, &bslash;&n;        detect:            eata_detect,                 &bslash;&n;        release:           eata_release,                &bslash;&n;&t;queuecommand:      eata_queue,                  &bslash;&n;&t;abort:             eata_abort,                  &bslash;&n;&t;reset:             eata_reset,                  &bslash;&n;&t;bios_param:        scsicam_bios_param,          &bslash;&n;&t;unchecked_isa_dma: 1,      /* True if ISA  */   &bslash;&n;&t;use_clustering:    ENABLE_CLUSTERING }
macro_line|#endif /* _EATA_DMA_H */
multiline_comment|/*&n; * Overrides for Emacs so that we almost follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
