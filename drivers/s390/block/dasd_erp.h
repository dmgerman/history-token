multiline_comment|/* &n; * File...........: linux/drivers/s390/block/dasd_erp.h&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 2000&n; */
macro_line|#include &quot;dasd_types.h&quot;
r_typedef
r_enum
(brace
DECL|enumerator|dasd_era_fatal
id|dasd_era_fatal
op_assign
op_minus
l_int|1
comma
DECL|enumerator|dasd_era_none
id|dasd_era_none
op_assign
l_int|0
DECL|typedef|dasd_era_t
)brace
id|dasd_era_t
suffix:semicolon
id|dasd_era_t
id|dasd_erp_examine
(paren
id|cqr_t
op_star
)paren
suffix:semicolon
eof
