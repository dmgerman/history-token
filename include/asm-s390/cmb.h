macro_line|#ifndef S390_CMB_H
DECL|macro|S390_CMB_H
mdefine_line|#define S390_CMB_H
multiline_comment|/**&n; * struct cmbdata -- channel measurement block data for user space&n; *&n; * @size:&t;size of the stored data&n; * @ssch_rsch_count: XXX&n; * @sample_count:&n; * @device_connect_time:&n; * @function_pending_time:&n; * @device_disconnect_time:&n; * @control_unit_queuing_time:&n; * @device_active_only_time:&n; * @device_busy_time:&n; * @initial_command_response_time:&n; *&n; * all values are stored as 64 bit for simplicity, especially&n; * in 32 bit emulation mode. All time values are normalized to&n; * nanoseconds.&n; * Currently, two formats are known, which differ by the size of&n; * this structure, i.e. the last two members are only set when&n; * the extended channel measurement facility (first shipped in&n; * z990 machines) is activated.&n; * Potentially, more fields could be added, which results in a&n; * new ioctl number.&n; **/
DECL|struct|cmbdata
r_struct
id|cmbdata
(brace
DECL|member|size
id|__u64
id|size
suffix:semicolon
DECL|member|elapsed_time
id|__u64
id|elapsed_time
suffix:semicolon
multiline_comment|/* basic and exended format: */
DECL|member|ssch_rsch_count
id|__u64
id|ssch_rsch_count
suffix:semicolon
DECL|member|sample_count
id|__u64
id|sample_count
suffix:semicolon
DECL|member|device_connect_time
id|__u64
id|device_connect_time
suffix:semicolon
DECL|member|function_pending_time
id|__u64
id|function_pending_time
suffix:semicolon
DECL|member|device_disconnect_time
id|__u64
id|device_disconnect_time
suffix:semicolon
DECL|member|control_unit_queuing_time
id|__u64
id|control_unit_queuing_time
suffix:semicolon
DECL|member|device_active_only_time
id|__u64
id|device_active_only_time
suffix:semicolon
multiline_comment|/* extended format only: */
DECL|member|device_busy_time
id|__u64
id|device_busy_time
suffix:semicolon
DECL|member|initial_command_response_time
id|__u64
id|initial_command_response_time
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* enable channel measurement */
DECL|macro|BIODASDCMFENABLE
mdefine_line|#define BIODASDCMFENABLE&t;_IO(DASD_IOCTL_LETTER,32)
multiline_comment|/* enable channel measurement */
DECL|macro|BIODASDCMFDISABLE
mdefine_line|#define BIODASDCMFDISABLE&t;_IO(DASD_IOCTL_LETTER,33)
multiline_comment|/* reset channel measurement block */
DECL|macro|BIODASDRESETCMB
mdefine_line|#define BIODASDRESETCMB&t;&t;_IO(DASD_IOCTL_LETTER,34)
multiline_comment|/* read channel measurement data */
DECL|macro|BIODASDREADCMB
mdefine_line|#define BIODASDREADCMB&t;&t;_IOWR(DASD_IOCTL_LETTER,32,u64)
multiline_comment|/* read channel measurement data */
DECL|macro|BIODASDREADALLCMB
mdefine_line|#define BIODASDREADALLCMB&t;_IOWR(DASD_IOCTL_LETTER,33,struct cmbdata)
macro_line|#ifdef __KERNEL__
multiline_comment|/**&n; * enable_cmf() - switch on the channel measurement for a specific device&n; *  @cdev:&t;The ccw device to be enabled&n; *  returns 0 for success or a negative error value.&n; *&n; *  Context:&n; *    non-atomic&n; **/
r_extern
r_int
id|enable_cmf
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
suffix:semicolon
multiline_comment|/**&n; * disable_cmf() - switch off the channel measurement for a specific device&n; *  @cdev:&t;The ccw device to be disabled&n; *  returns 0 for success or a negative error value.&n; *&n; *  Context:&n; *    non-atomic&n; **/
r_extern
r_int
id|disable_cmf
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
suffix:semicolon
multiline_comment|/**&n; * cmf_read() - read one value from the current channel measurement block&n; * @cmf:&t;the channel to be read&n; * @index:&t;the name of the value that is read&n; *&n; *  Context:&n; *    any&n; **/
r_extern
id|u64
id|cmf_read
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_int
id|index
)paren
suffix:semicolon
multiline_comment|/**&n; * cmf_readall() - read one value from the current channel measurement block&n; * @cmf:&t;the channel to be read&n; * @data:&t;a pointer to a data block that will be filled&n; *&n; *  Context:&n; *    any&n; **/
r_extern
r_int
id|cmf_readall
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_struct
id|cmbdata
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|cmf_reset
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* S390_CMB_H */
eof
