multiline_comment|/* &n; * File...........: linux/drivers/s390/block/dasd_9345_erp.h&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 2000&n; */
macro_line|#include &lt;asm/ccwcache.h&gt;
macro_line|#include &lt;asm/dasd.h&gt;
macro_line|#ifdef PRINTK_HEADER
DECL|macro|PRINTK_HEADER
macro_line|#undef PRINTK_HEADER
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER &quot;dasd_erp(9343)&quot;
macro_line|#endif&t;&t;&t;&t;/* PRINTK_HEADER */
id|dasd_era_t
DECL|function|dasd_9343_erp_examine
id|dasd_9343_erp_examine
(paren
id|ccw_req_t
op_star
id|cqr
comma
id|devstat_t
op_star
id|stat
)paren
(brace
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
id|dasd_era_recover
suffix:semicolon
)brace
eof
