multiline_comment|/***************************************************************************&n; *&n; *  drivers/s390/char/tape3480.c&n; *    tape device discipline for 3480 tapes.&n; *&n; *  S390 and zSeries version&n; *    Copyright (C) 2001 IBM Corporation&n; *    Author(s): Carsten Otte &lt;cotte@de.ibm.com&gt;&n; *               Tuan Ngo-Anh &lt;ngoanh@de.ibm.com&gt;&n; * &n; ****************************************************************************&n; */
macro_line|#include &quot;tapedefs.h&quot;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/ccwcache.h&gt;&t;/* CCW allocations      */
macro_line|#include &lt;asm/s390dyn.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;linux/compatmac.h&gt;
macro_line|#include &quot;tape.h&quot;
macro_line|#include &quot;tape34xx.h&quot;
macro_line|#include &quot;tape3480.h&quot;
DECL|variable|tape3480_event_handler_table
id|tape_event_handler_t
id|tape3480_event_handler_table
(braket
id|TS_SIZE
)braket
(braket
id|TE_SIZE
)braket
op_assign
(brace
multiline_comment|/* {START , DONE, FAILED, ERROR, OTHER } */
(brace
l_int|NULL
comma
id|tape34xx_unused_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_UNUSED */
(brace
l_int|NULL
comma
id|tape34xx_idle_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_IDLE */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_DONE */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_FAILED */
(brace
l_int|NULL
comma
id|tape34xx_block_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_BLOCK_INIT */
(brace
l_int|NULL
comma
id|tape34xx_bsb_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_BSB_INIT */
(brace
l_int|NULL
comma
id|tape34xx_bsf_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_BSF_INIT */
(brace
l_int|NULL
comma
id|tape34xx_dse_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_DSE_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_EGA_INIT */
(brace
l_int|NULL
comma
id|tape34xx_fsb_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_FSB_INIT */
(brace
l_int|NULL
comma
id|tape34xx_fsf_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_FSF_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_LDI_INIT */
(brace
l_int|NULL
comma
id|tape34xx_lbl_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_LBL_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_MSE_INIT */
(brace
l_int|NULL
comma
id|tape34xx_nop_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_NOP_INIT */
(brace
l_int|NULL
comma
id|tape34xx_rfo_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_RBA_INIT */
(brace
l_int|NULL
comma
id|tape34xx_rbi_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_RBI_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_RBU_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_RBL_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_RDC_INIT */
(brace
l_int|NULL
comma
id|tape34xx_rfo_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_RFO_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_RSD_INIT */
(brace
l_int|NULL
comma
id|tape34xx_rew_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_REW_INIT */
(brace
l_int|NULL
comma
id|tape34xx_rew_release_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_REW_RELEASE_IMIT */
(brace
l_int|NULL
comma
id|tape34xx_run_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_RUN_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_SEN_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_SID_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_SNP_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_SPG_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_SWI_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_SMR_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_SYN_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_TIO_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_UNA_INIT */
(brace
l_int|NULL
comma
id|tape34xx_wri_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_WRI_INIT */
(brace
l_int|NULL
comma
id|tape34xx_wtm_init_done
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
comma
multiline_comment|/* TS_WTM_INIT */
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
multiline_comment|/* TS_NOT_OPER */
DECL|variable|tape3480_devreg
id|devreg_t
id|tape3480_devreg
op_assign
(brace
id|ci
suffix:colon
(brace
id|hc
suffix:colon
(brace
id|ctype
suffix:colon
l_int|0x3480
)brace
)brace
comma
id|flag
suffix:colon
id|DEVREG_MATCH_CU_TYPE
op_or
id|DEVREG_TYPE_DEVCHARS
comma
id|oper_func
suffix:colon
id|tape_oper_handler
)brace
suffix:semicolon
r_void
DECL|function|tape3480_setup_assist
id|tape3480_setup_assist
(paren
id|tape_info_t
op_star
id|ti
)paren
(brace
id|tape3480_disc_data_t
op_star
id|data
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|6
comma
l_string|&quot;3480 dsetu&quot;
)paren
suffix:semicolon
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|6
comma
l_string|&quot;dev:&quot;
)paren
suffix:semicolon
id|debug_int_event
(paren
id|tape_debug_area
comma
l_int|6
comma
id|ti-&gt;blk_minor
)paren
suffix:semicolon
macro_line|#endif /* TAPE_DEBUG */
r_while
c_loop
(paren
id|data
op_eq
l_int|NULL
)paren
id|data
op_assign
id|kmalloc
(paren
r_sizeof
(paren
id|tape3480_disc_data_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|data-&gt;modeset_byte
op_assign
l_int|0x00
suffix:semicolon
id|ti-&gt;discdata
op_assign
(paren
r_void
op_star
)paren
id|data
suffix:semicolon
)brace
r_void
DECL|function|tape3480_shutdown
id|tape3480_shutdown
(paren
r_int
id|autoprobe
)paren
(brace
r_if
c_cond
(paren
id|autoprobe
)paren
id|s390_device_unregister
c_func
(paren
op_amp
id|tape3480_devreg
)paren
suffix:semicolon
)brace
id|tape_discipline_t
op_star
DECL|function|tape3480_init
id|tape3480_init
(paren
r_int
id|autoprobe
)paren
(brace
id|tape_discipline_t
op_star
id|disc
suffix:semicolon
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|3
comma
l_string|&quot;3480 init&quot;
)paren
suffix:semicolon
macro_line|#endif /* TAPE_DEBUG */
id|disc
op_assign
id|kmalloc
(paren
r_sizeof
(paren
id|tape_discipline_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|disc
op_eq
l_int|NULL
)paren
(brace
macro_line|#ifdef TAPE_DEBUG
id|debug_text_exception
(paren
id|tape_debug_area
comma
l_int|3
comma
l_string|&quot;disc:nomem&quot;
)paren
suffix:semicolon
macro_line|#endif /* TAPE_DEBUG */
r_return
id|disc
suffix:semicolon
)brace
id|disc-&gt;cu_type
op_assign
l_int|0x3480
suffix:semicolon
id|disc-&gt;setup_assist
op_assign
id|tape3480_setup_assist
suffix:semicolon
id|disc-&gt;error_recovery
op_assign
id|tape34xx_error_recovery
suffix:semicolon
id|disc-&gt;write_block
op_assign
id|tape34xx_write_block
suffix:semicolon
id|disc-&gt;free_write_block
op_assign
id|tape34xx_free_write_block
suffix:semicolon
id|disc-&gt;read_block
op_assign
id|tape34xx_read_block
suffix:semicolon
id|disc-&gt;free_read_block
op_assign
id|tape34xx_free_read_block
suffix:semicolon
id|disc-&gt;mtfsf
op_assign
id|tape34xx_mtfsf
suffix:semicolon
id|disc-&gt;mtbsf
op_assign
id|tape34xx_mtbsf
suffix:semicolon
id|disc-&gt;mtfsr
op_assign
id|tape34xx_mtfsr
suffix:semicolon
id|disc-&gt;mtbsr
op_assign
id|tape34xx_mtbsr
suffix:semicolon
id|disc-&gt;mtweof
op_assign
id|tape34xx_mtweof
suffix:semicolon
id|disc-&gt;mtrew
op_assign
id|tape34xx_mtrew
suffix:semicolon
id|disc-&gt;mtoffl
op_assign
id|tape34xx_mtoffl
suffix:semicolon
id|disc-&gt;mtnop
op_assign
id|tape34xx_mtnop
suffix:semicolon
id|disc-&gt;mtbsfm
op_assign
id|tape34xx_mtbsfm
suffix:semicolon
id|disc-&gt;mtfsfm
op_assign
id|tape34xx_mtfsfm
suffix:semicolon
id|disc-&gt;mteom
op_assign
id|tape34xx_mteom
suffix:semicolon
id|disc-&gt;mterase
op_assign
id|tape34xx_mterase
suffix:semicolon
id|disc-&gt;mtsetdensity
op_assign
id|tape34xx_mtsetdensity
suffix:semicolon
id|disc-&gt;mtseek
op_assign
id|tape34xx_mtseek
suffix:semicolon
id|disc-&gt;mttell
op_assign
id|tape34xx_mttell
suffix:semicolon
id|disc-&gt;mtsetdrvbuffer
op_assign
id|tape34xx_mtsetdrvbuffer
suffix:semicolon
id|disc-&gt;mtlock
op_assign
id|tape34xx_mtlock
suffix:semicolon
id|disc-&gt;mtunlock
op_assign
id|tape34xx_mtunlock
suffix:semicolon
id|disc-&gt;mtload
op_assign
id|tape34xx_mtload
suffix:semicolon
id|disc-&gt;mtunload
op_assign
id|tape34xx_mtunload
suffix:semicolon
id|disc-&gt;mtcompression
op_assign
id|tape34xx_mtcompression
suffix:semicolon
id|disc-&gt;mtsetpart
op_assign
id|tape34xx_mtsetpart
suffix:semicolon
id|disc-&gt;mtmkpart
op_assign
id|tape34xx_mtmkpart
suffix:semicolon
id|disc-&gt;mtiocget
op_assign
id|tape34xx_mtiocget
suffix:semicolon
id|disc-&gt;mtiocpos
op_assign
id|tape34xx_mtiocpos
suffix:semicolon
id|disc-&gt;shutdown
op_assign
id|tape3480_shutdown
suffix:semicolon
id|disc-&gt;discipline_ioctl_overload
op_assign
id|tape34xx_ioctl_overload
suffix:semicolon
id|disc-&gt;event_table
op_assign
op_amp
id|tape3480_event_handler_table
suffix:semicolon
id|disc-&gt;default_handler
op_assign
id|tape34xx_default_handler
suffix:semicolon
id|disc-&gt;bread
op_assign
id|tape34xx_bread
suffix:semicolon
id|disc-&gt;free_bread
op_assign
id|tape34xx_free_bread
suffix:semicolon
id|disc-&gt;tape
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* pointer for backreference */
id|disc-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|autoprobe
)paren
id|s390_device_register
c_func
(paren
op_amp
id|tape3480_devreg
)paren
suffix:semicolon
macro_line|#ifdef TAPE_DEBUG
id|debug_text_event
(paren
id|tape_debug_area
comma
l_int|3
comma
l_string|&quot;3480 regis&quot;
)paren
suffix:semicolon
macro_line|#endif /* TAPE_DEBUG */
r_return
id|disc
suffix:semicolon
)brace
eof
