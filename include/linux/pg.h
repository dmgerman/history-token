multiline_comment|/* &t;pg.h (c) 1998  Grant R. Guenther &lt;grant@torque.net&gt;&n; &t;&t;       Under the terms of the GNU General Public License&n;&n;&n;&t;pg.h defines the user interface to the generic ATAPI packet&n;        command driver for parallel port ATAPI devices (pg). The&n;&t;driver is loosely modelled after the generic SCSI driver, sg,&n;&t;although the actual interface is different.&n;&n;&t;The pg driver provides a simple character device interface for&n;        sending ATAPI commands to a device.  With the exception of the&n;&t;ATAPI reset operation, all operations are performed by a pair&n;        of read and write operations to the appropriate /dev/pgN device.&n;&t;A write operation delivers a command and any outbound data in&n;        a single buffer.  Normally, the write will succeed unless the&n;        device is offline or malfunctioning, or there is already another&n;&t;command pending.  If the write succeeds, it should be followed&n;        immediately by a read operation, to obtain any returned data and&n;        status information.  A read will fail if there is no operation&n;        in progress.&n;&n;&t;As a special case, the device can be reset with a write operation,&n;        and in this case, no following read is expected, or permitted.&n;&n;&t;There are no ioctl() operations.  Any single operation&n;&t;may transfer at most PG_MAX_DATA bytes.  Note that the driver must&n;        copy the data through an internal buffer.  In keeping with all&n;&t;current ATAPI devices, command packets are assumed to be exactly&n;&t;12 bytes in length.&n;&n;&t;To permit future changes to this interface, the headers in the&n;&t;read and write buffers contain a single character &quot;magic&quot; flag.&n;        Currently this flag must be the character &quot;P&quot;.&n;&n;*/
DECL|macro|PG_MAGIC
mdefine_line|#define PG_MAGIC&t;&squot;P&squot;
DECL|macro|PG_RESET
mdefine_line|#define PG_RESET&t;&squot;Z&squot;
DECL|macro|PG_COMMAND
mdefine_line|#define PG_COMMAND&t;&squot;C&squot;
DECL|macro|PG_MAX_DATA
mdefine_line|#define PG_MAX_DATA&t;32768
DECL|struct|pg_write_hdr
r_struct
id|pg_write_hdr
(brace
DECL|member|magic
r_char
id|magic
suffix:semicolon
multiline_comment|/* == PG_MAGIC */
DECL|member|func
r_char
id|func
suffix:semicolon
multiline_comment|/* PG_RESET or PG_COMMAND */
DECL|member|dlen
r_int
id|dlen
suffix:semicolon
multiline_comment|/* number of bytes expected to transfer */
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/* number of seconds before timeout */
DECL|member|packet
r_char
id|packet
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* packet command */
)brace
suffix:semicolon
DECL|struct|pg_read_hdr
r_struct
id|pg_read_hdr
(brace
DECL|member|magic
r_char
id|magic
suffix:semicolon
multiline_comment|/* == PG_MAGIC */
DECL|member|scsi
r_char
id|scsi
suffix:semicolon
multiline_comment|/* &quot;scsi&quot; status == sense key */
DECL|member|dlen
r_int
id|dlen
suffix:semicolon
multiline_comment|/* size of device transfer request */
DECL|member|duration
r_int
id|duration
suffix:semicolon
multiline_comment|/* time in seconds command took */
DECL|member|pad
r_char
id|pad
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* not used */
)brace
suffix:semicolon
multiline_comment|/* end of pg.h */
eof
