macro_line|#ifndef _ASM_ATARI_ACSI_H
DECL|macro|_ASM_ATARI_ACSI_H
mdefine_line|#define _ASM_ATARI_ACSI_H
multiline_comment|/* Functions exported by drivers/block/acsi.c */
r_void
id|acsi_delay_start
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|acsi_delay_end
c_func
(paren
r_int
id|usec
)paren
suffix:semicolon
r_int
id|acsi_wait_for_IRQ
c_func
(paren
r_int
id|timeout
)paren
suffix:semicolon
r_int
id|acsi_wait_for_noIRQ
c_func
(paren
r_int
id|timeout
)paren
suffix:semicolon
r_int
id|acsicmd_nodma
c_func
(paren
r_const
r_char
op_star
id|cmd
comma
r_int
id|enable
)paren
suffix:semicolon
r_int
id|acsi_getstatus
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|acsi_extstatus
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|cnt
)paren
suffix:semicolon
r_void
id|acsi_end_extstatus
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|acsi_extcmd
c_func
(paren
r_int
r_char
op_star
id|buffer
comma
r_int
id|cnt
)paren
suffix:semicolon
multiline_comment|/* The ACSI buffer is guarantueed to reside in ST-RAM and may be used by other&n; * drivers that work on the ACSI bus, too. It&squot;s data are valid only as long as&n; * the ST-DMA is locked. */
r_extern
r_char
op_star
id|acsi_buffer
suffix:semicolon
r_extern
r_int
r_int
id|phys_acsi_buffer
suffix:semicolon
multiline_comment|/* Utility macros */
multiline_comment|/* Send one data byte over the bus and set mode for next operation&n; * with one move.l -- Atari recommends this...&n; */
DECL|macro|DMA_LONG_WRITE
mdefine_line|#define DMA_LONG_WRITE(data,mode)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*((unsigned long *)&amp;dma_wd.fdc_acces_seccount) = &t;&bslash;&n;&t;&t;&t;((data)&lt;&lt;16) | (mode);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while(0)
DECL|macro|ENABLE_IRQ
mdefine_line|#define ENABLE_IRQ()&t;atari_turnon_irq( IRQ_MFP_ACSI )
DECL|macro|DISABLE_IRQ
mdefine_line|#define DISABLE_IRQ()&t;atari_turnoff_irq( IRQ_MFP_ACSI )
macro_line|#endif /* _ASM_ATARI_ACSI_H */
eof
