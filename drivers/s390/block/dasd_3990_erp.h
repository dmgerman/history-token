multiline_comment|/* &n; * File...........: linux/drivers/s390/block/dasd_3990_erp.h&n; * Author(s)......: Horst Hummel &lt;Horst Hummel@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 2000&n; *&n; * History of changes (starts July 2000)&n; */
macro_line|#ifndef DASD_3990_ERP_H
DECL|macro|DASD_3990_ERP_H
mdefine_line|#define DASD_3990_ERP_H
id|dasd_era_t
id|dasd_3990_erp_examine
c_func
(paren
id|dasd_ccw_req_t
op_star
comma
id|devstat_t
op_star
)paren
suffix:semicolon
id|dasd_ccw_req_t
op_star
id|dasd_3990_erp_action
c_func
(paren
id|dasd_ccw_req_t
op_star
)paren
suffix:semicolon
id|dasd_ccw_req_t
op_star
id|dasd_2105_erp_action
c_func
(paren
id|ccw_req_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_3990_erp_restart_queue
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|struct|DCTL_data_t
r_typedef
r_struct
id|DCTL_data_t
(brace
DECL|member|subcommand
r_int
r_char
id|subcommand
suffix:semicolon
multiline_comment|/* e.g Inhibit Write, Enable Write,... */
DECL|member|modifier
r_int
r_char
id|modifier
suffix:semicolon
multiline_comment|/* Subcommand modifier&t;&t;       */
DECL|member|res
r_int
r_int
id|res
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|DCTL_data_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|DCTL_data_t
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* DASD_3990_ERP_H */
eof
