multiline_comment|/* &n; * File...........: linux/drivers/s390/block/dasd_erp.c&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 2000&n; */
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/dasd.h&gt;
macro_line|#include &quot;dasd_erp.h&quot;
macro_line|#include &quot;dasd_types.h&quot;
id|dasd_era_t
DECL|function|dasd_erp_examine
id|dasd_erp_examine
(paren
id|cqr_t
op_star
id|cqr
)paren
(brace
id|devstat_t
op_star
id|stat
op_assign
id|cqr-&gt;dstat
suffix:semicolon
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
r_return
id|dasd_era_fatal
suffix:semicolon
)brace
eof
