multiline_comment|/* &n; * File...........: linux/drivers/s390/block/dasd_9336_erp.c&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 2000&n; */
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER &quot;dasd_erp(9336)&quot;
macro_line|#include &quot;dasd_int.h&quot;
multiline_comment|/*&n; * DASD_9336_ERP_EXAMINE &n; *&n; * DESCRIPTION&n; *   Checks only for fatal/no/recover error. &n; *   A detailed examination of the sense data is done later outside&n; *   the interrupt handler.&n; *&n; *   The logic is based on the &squot;IBM 3880 Storage Control Reference&squot; manual&n; *   &squot;Chapter 7. 9336 Sense Data&squot;.&n; *&n; * RETURN VALUES&n; *   dasd_era_none&t;no error &n; *   dasd_era_fatal&t;for all fatal (unrecoverable errors)&n; *   dasd_era_recover&t;for all others.&n; */
id|dasd_era_t
DECL|function|dasd_9336_erp_examine
id|dasd_9336_erp_examine
c_func
(paren
id|dasd_ccw_req_t
op_star
id|cqr
comma
id|devstat_t
op_star
id|stat
)paren
(brace
multiline_comment|/* check for successful execution first */
r_if
c_cond
(paren
id|stat-&gt;cstat
op_eq
l_int|0x00
op_logical_and
id|stat-&gt;dstat
op_eq
(paren
id|DEV_STAT_CHN_END
op_or
id|DEV_STAT_DEV_END
)paren
)paren
r_return
id|dasd_era_none
suffix:semicolon
multiline_comment|/* examine the 24 byte sense data */
r_return
id|dasd_era_recover
suffix:semicolon
)brace
multiline_comment|/* END dasd_9336_erp_examine */
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4 &n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: 1&n; * tab-width: 8&n; * End:&n; */
eof
