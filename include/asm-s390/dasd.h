multiline_comment|/* &n; * File...........: linux/drivers/s390/block/dasd.c&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999,2000&n; *&n; * This file is the interface of the DASD device driver, which is exported to user space&n; * any future changes wrt the API will result in a change of the APIVERSION reported&n; * to userspace by the DASDAPIVER-ioctl&n; *&n; * History of changes (starts July 2000)&n; * 05/04/01 created by moving the kernel interface to drivers/s390/block/dasd_int.h&n; * 12/06/01 DASD_API_VERSION 2 - binary compatible to 0 (new BIODASDINFO2)&n; * 01/23/02 DASD_API_VERSION 3 - added BIODASDPSRD (and BIODASDENAPAV) IOCTL&n; * 02/15/02 DASD_API_VERSION 4 - added BIODASDSATTR IOCTL&n; *         &n; */
macro_line|#ifndef DASD_H
DECL|macro|DASD_H
mdefine_line|#define DASD_H
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|DASD_IOCTL_LETTER
mdefine_line|#define DASD_IOCTL_LETTER &squot;D&squot;
DECL|macro|DASD_API_VERSION
mdefine_line|#define DASD_API_VERSION 4
multiline_comment|/* &n; * struct dasd_information2_t&n; * represents any data about the device, which is visible to userspace.&n; *  including foramt and featueres.&n; */
DECL|struct|dasd_information2_t
r_typedef
r_struct
id|dasd_information2_t
(brace
DECL|member|devno
r_int
r_int
id|devno
suffix:semicolon
multiline_comment|/* S/390 devno */
DECL|member|real_devno
r_int
r_int
id|real_devno
suffix:semicolon
multiline_comment|/* for aliases */
DECL|member|schid
r_int
r_int
id|schid
suffix:semicolon
multiline_comment|/* S/390 subchannel identifier */
DECL|member|cu_type
r_int
r_int
id|cu_type
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* from SenseID */
DECL|member|cu_model
r_int
r_int
id|cu_model
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* from SenseID */
DECL|member|dev_type
r_int
r_int
id|dev_type
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* from SenseID */
DECL|member|dev_model
r_int
r_int
id|dev_model
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* from SenseID */
DECL|member|open_count
r_int
r_int
id|open_count
suffix:semicolon
DECL|member|req_queue_len
r_int
r_int
id|req_queue_len
suffix:semicolon
DECL|member|chanq_len
r_int
r_int
id|chanq_len
suffix:semicolon
multiline_comment|/* length of chanq */
DECL|member|type
r_char
id|type
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* from discipline.name, &squot;none&squot; for unknown */
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* current device level */
DECL|member|label_block
r_int
r_int
id|label_block
suffix:semicolon
multiline_comment|/* where to find the VOLSER */
DECL|member|FBA_layout
r_int
r_int
id|FBA_layout
suffix:semicolon
multiline_comment|/* fixed block size (like AIXVOL) */
DECL|member|characteristics_size
r_int
r_int
id|characteristics_size
suffix:semicolon
DECL|member|confdata_size
r_int
r_int
id|confdata_size
suffix:semicolon
DECL|member|characteristics
r_char
id|characteristics
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* from read_device_characteristics */
DECL|member|configuration_data
r_char
id|configuration_data
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* from read_configuration_data */
DECL|member|format
r_int
r_int
id|format
suffix:semicolon
multiline_comment|/* format info like formatted/cdl/ldl/... */
DECL|member|features
r_int
r_int
id|features
suffix:semicolon
multiline_comment|/* dasd features like &squot;ro&squot;,...            */
DECL|member|reserved0
r_int
r_int
id|reserved0
suffix:semicolon
multiline_comment|/* reserved for further use ,...          */
DECL|member|reserved1
r_int
r_int
id|reserved1
suffix:semicolon
multiline_comment|/* reserved for further use ,...          */
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:semicolon
multiline_comment|/* reserved for further use ,...          */
DECL|member|reserved3
r_int
r_int
id|reserved3
suffix:semicolon
multiline_comment|/* reserved for further use ,...          */
DECL|member|reserved4
r_int
r_int
id|reserved4
suffix:semicolon
multiline_comment|/* reserved for further use ,...          */
DECL|member|reserved5
r_int
r_int
id|reserved5
suffix:semicolon
multiline_comment|/* reserved for further use ,...          */
DECL|member|reserved6
r_int
r_int
id|reserved6
suffix:semicolon
multiline_comment|/* reserved for further use ,...          */
DECL|member|reserved7
r_int
r_int
id|reserved7
suffix:semicolon
multiline_comment|/* reserved for further use ,...          */
DECL|typedef|dasd_information2_t
)brace
id|dasd_information2_t
suffix:semicolon
multiline_comment|/*&n; * values to be used for dasd_information_t.format&n; * 0x00: NOT formatted&n; * 0x01: Linux disc layout&n; * 0x02: Common disc layout&n; */
DECL|macro|DASD_FORMAT_NONE
mdefine_line|#define DASD_FORMAT_NONE 0
DECL|macro|DASD_FORMAT_LDL
mdefine_line|#define DASD_FORMAT_LDL  1
DECL|macro|DASD_FORMAT_CDL
mdefine_line|#define DASD_FORMAT_CDL  2
multiline_comment|/*&n; * values to be used for dasd_information_t.features&n; * 0x00: default features&n; * 0x01: readonly (ro)&n; */
DECL|macro|DASD_FEATURE_DEFAULT
mdefine_line|#define DASD_FEATURE_DEFAULT  0
DECL|macro|DASD_FEATURE_READONLY
mdefine_line|#define DASD_FEATURE_READONLY 1
DECL|macro|DASD_PARTN_BITS
mdefine_line|#define DASD_PARTN_BITS 2
multiline_comment|/* &n; * struct dasd_information_t&n; * represents any data about the data, which is visible to userspace&n; */
DECL|struct|dasd_information_t
r_typedef
r_struct
id|dasd_information_t
(brace
DECL|member|devno
r_int
r_int
id|devno
suffix:semicolon
multiline_comment|/* S/390 devno */
DECL|member|real_devno
r_int
r_int
id|real_devno
suffix:semicolon
multiline_comment|/* for aliases */
DECL|member|schid
r_int
r_int
id|schid
suffix:semicolon
multiline_comment|/* S/390 subchannel identifier */
DECL|member|cu_type
r_int
r_int
id|cu_type
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* from SenseID */
DECL|member|cu_model
r_int
r_int
id|cu_model
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* from SenseID */
DECL|member|dev_type
r_int
r_int
id|dev_type
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* from SenseID */
DECL|member|dev_model
r_int
r_int
id|dev_model
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* from SenseID */
DECL|member|open_count
r_int
r_int
id|open_count
suffix:semicolon
DECL|member|req_queue_len
r_int
r_int
id|req_queue_len
suffix:semicolon
DECL|member|chanq_len
r_int
r_int
id|chanq_len
suffix:semicolon
multiline_comment|/* length of chanq */
DECL|member|type
r_char
id|type
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* from discipline.name, &squot;none&squot; for unknown */
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* current device level */
DECL|member|label_block
r_int
r_int
id|label_block
suffix:semicolon
multiline_comment|/* where to find the VOLSER */
DECL|member|FBA_layout
r_int
r_int
id|FBA_layout
suffix:semicolon
multiline_comment|/* fixed block size (like AIXVOL) */
DECL|member|characteristics_size
r_int
r_int
id|characteristics_size
suffix:semicolon
DECL|member|confdata_size
r_int
r_int
id|confdata_size
suffix:semicolon
DECL|member|characteristics
r_char
id|characteristics
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* from read_device_characteristics */
DECL|member|configuration_data
r_char
id|configuration_data
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* from read_configuration_data */
DECL|typedef|dasd_information_t
)brace
id|dasd_information_t
suffix:semicolon
multiline_comment|/*&n; * Read Subsystem Data - Perfomance Statistics&n; */
DECL|struct|dasd_rssd_perf_stats_t
r_typedef
r_struct
id|dasd_rssd_perf_stats_t
(brace
DECL|member|invalid
r_int
r_char
id|invalid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|format
r_int
r_char
id|format
suffix:colon
l_int|3
suffix:semicolon
DECL|member|data_format
r_int
r_char
id|data_format
suffix:colon
l_int|4
suffix:semicolon
DECL|member|unit_address
r_int
r_char
id|unit_address
suffix:semicolon
DECL|member|device_status
r_int
r_int
id|device_status
suffix:semicolon
DECL|member|nr_read_normal
r_int
r_int
id|nr_read_normal
suffix:semicolon
DECL|member|nr_read_normal_hits
r_int
r_int
id|nr_read_normal_hits
suffix:semicolon
DECL|member|nr_write_normal
r_int
r_int
id|nr_write_normal
suffix:semicolon
DECL|member|nr_write_fast_normal_hits
r_int
r_int
id|nr_write_fast_normal_hits
suffix:semicolon
DECL|member|nr_read_seq
r_int
r_int
id|nr_read_seq
suffix:semicolon
DECL|member|nr_read_seq_hits
r_int
r_int
id|nr_read_seq_hits
suffix:semicolon
DECL|member|nr_write_seq
r_int
r_int
id|nr_write_seq
suffix:semicolon
DECL|member|nr_write_fast_seq_hits
r_int
r_int
id|nr_write_fast_seq_hits
suffix:semicolon
DECL|member|nr_read_cache
r_int
r_int
id|nr_read_cache
suffix:semicolon
DECL|member|nr_read_cache_hits
r_int
r_int
id|nr_read_cache_hits
suffix:semicolon
DECL|member|nr_write_cache
r_int
r_int
id|nr_write_cache
suffix:semicolon
DECL|member|nr_write_fast_cache_hits
r_int
r_int
id|nr_write_fast_cache_hits
suffix:semicolon
DECL|member|nr_inhibit_cache
r_int
r_int
id|nr_inhibit_cache
suffix:semicolon
DECL|member|nr_bybass_cache
r_int
r_int
id|nr_bybass_cache
suffix:semicolon
DECL|member|nr_seq_dasd_to_cache
r_int
r_int
id|nr_seq_dasd_to_cache
suffix:semicolon
DECL|member|nr_dasd_to_cache
r_int
r_int
id|nr_dasd_to_cache
suffix:semicolon
DECL|member|nr_cache_to_dasd
r_int
r_int
id|nr_cache_to_dasd
suffix:semicolon
DECL|member|nr_delayed_fast_write
r_int
r_int
id|nr_delayed_fast_write
suffix:semicolon
DECL|member|nr_normal_fast_write
r_int
r_int
id|nr_normal_fast_write
suffix:semicolon
DECL|member|nr_seq_fast_write
r_int
r_int
id|nr_seq_fast_write
suffix:semicolon
DECL|member|nr_cache_miss
r_int
r_int
id|nr_cache_miss
suffix:semicolon
DECL|member|status2
r_int
r_char
id|status2
suffix:semicolon
DECL|member|nr_quick_write_promotes
r_int
r_int
id|nr_quick_write_promotes
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|ssid
r_int
r_int
id|ssid
suffix:semicolon
DECL|member|reseved2
r_int
r_char
id|reseved2
(braket
l_int|96
)braket
suffix:semicolon
DECL|typedef|dasd_rssd_perf_stats_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|dasd_rssd_perf_stats_t
suffix:semicolon
multiline_comment|/* &n; * struct profile_info_t&n; * holds the profinling information &n; */
DECL|struct|dasd_profile_info_t
r_typedef
r_struct
id|dasd_profile_info_t
(brace
DECL|member|dasd_io_reqs
r_int
r_int
id|dasd_io_reqs
suffix:semicolon
multiline_comment|/* number of requests processed at all */
DECL|member|dasd_io_sects
r_int
r_int
id|dasd_io_sects
suffix:semicolon
multiline_comment|/* number of sectors processed at all */
DECL|member|dasd_io_secs
r_int
r_int
id|dasd_io_secs
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of request&squot;s sizes */
DECL|member|dasd_io_times
r_int
r_int
id|dasd_io_times
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of requests&squot;s times */
DECL|member|dasd_io_timps
r_int
r_int
id|dasd_io_timps
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of requests&squot;s times per sector */
DECL|member|dasd_io_time1
r_int
r_int
id|dasd_io_time1
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of time from build to start */
DECL|member|dasd_io_time2
r_int
r_int
id|dasd_io_time2
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of time from start to irq */
DECL|member|dasd_io_time2ps
r_int
r_int
id|dasd_io_time2ps
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of time from start to irq */
DECL|member|dasd_io_time3
r_int
r_int
id|dasd_io_time3
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of time from irq to end */
DECL|member|dasd_io_nr_req
r_int
r_int
id|dasd_io_nr_req
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of # of requests in chanq */
DECL|typedef|dasd_profile_info_t
)brace
id|dasd_profile_info_t
suffix:semicolon
multiline_comment|/* &n; * struct format_data_t&n; * represents all data necessary to format a dasd&n; */
DECL|struct|format_data_t
r_typedef
r_struct
id|format_data_t
(brace
DECL|member|start_unit
r_int
id|start_unit
suffix:semicolon
multiline_comment|/* from track */
DECL|member|stop_unit
r_int
id|stop_unit
suffix:semicolon
multiline_comment|/* to track */
DECL|member|blksize
r_int
id|blksize
suffix:semicolon
multiline_comment|/* sectorsize */
DECL|member|intensity
r_int
id|intensity
suffix:semicolon
DECL|typedef|format_data_t
)brace
id|format_data_t
suffix:semicolon
multiline_comment|/*&n; * values to be used for format_data_t.intensity&n; * 0/8: normal format&n; * 1/9: also write record zero&n; * 3/11: also write home address&n; * 4/12: invalidate track&n; */
DECL|macro|DASD_FMT_INT_FMT_R0
mdefine_line|#define DASD_FMT_INT_FMT_R0 1 /* write record zero */
DECL|macro|DASD_FMT_INT_FMT_HA
mdefine_line|#define DASD_FMT_INT_FMT_HA 2 /* write home address, also set FMT_R0 ! */
DECL|macro|DASD_FMT_INT_INVAL
mdefine_line|#define DASD_FMT_INT_INVAL  4 /* invalidate tracks */
DECL|macro|DASD_FMT_INT_COMPAT
mdefine_line|#define DASD_FMT_INT_COMPAT 8 /* use OS/390 compatible disk layout */
multiline_comment|/* &n; * struct attrib_data_t&n; * represents the operation (cache) bits for the device.&n; * Used in DE to influence caching of the DASD.&n; */
DECL|struct|attrib_data_t
r_typedef
r_struct
id|attrib_data_t
(brace
DECL|member|operation
r_int
r_char
id|operation
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* cache operation mode */
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* cache operation mode */
DECL|member|nr_cyl
id|__u16
id|nr_cyl
suffix:semicolon
multiline_comment|/* no of cyliners for read ahaed */
DECL|member|reserved2
id|__u8
id|reserved2
(braket
l_int|29
)braket
suffix:semicolon
multiline_comment|/* for future use */
DECL|typedef|attrib_data_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|attrib_data_t
suffix:semicolon
multiline_comment|/* definition of operation (cache) bits within attributes of DE */
DECL|macro|DASD_NORMAL_CACHE
mdefine_line|#define DASD_NORMAL_CACHE  0x0
DECL|macro|DASD_BYPASS_CACHE
mdefine_line|#define DASD_BYPASS_CACHE  0x1
DECL|macro|DASD_INHIBIT_LOAD
mdefine_line|#define DASD_INHIBIT_LOAD  0x2
DECL|macro|DASD_SEQ_ACCESS
mdefine_line|#define DASD_SEQ_ACCESS    0x3
DECL|macro|DASD_SEQ_PRESTAGE
mdefine_line|#define DASD_SEQ_PRESTAGE  0x4
DECL|macro|DASD_REC_ACCESS
mdefine_line|#define DASD_REC_ACCESS    0x5
multiline_comment|/********************************************************************************&n; * SECTION: Definition of IOCTLs&n; *&n; * Here ist how the ioctl-nr should be used:&n; *    0 -   31   DASD driver itself&n; *   32 -  239   still open&n; *  240 -  255   reserved for EMC &n; *******************************************************************************/
multiline_comment|/* Disable the volume (for Linux) */
DECL|macro|BIODASDDISABLE
mdefine_line|#define BIODASDDISABLE _IO(DASD_IOCTL_LETTER,0) 
multiline_comment|/* Enable the volume (for Linux) */
DECL|macro|BIODASDENABLE
mdefine_line|#define BIODASDENABLE  _IO(DASD_IOCTL_LETTER,1)  
multiline_comment|/* Issue a reserve/release command, rsp. */
DECL|macro|BIODASDRSRV
mdefine_line|#define BIODASDRSRV    _IO(DASD_IOCTL_LETTER,2) /* reserve */
DECL|macro|BIODASDRLSE
mdefine_line|#define BIODASDRLSE    _IO(DASD_IOCTL_LETTER,3) /* release */
DECL|macro|BIODASDSLCK
mdefine_line|#define BIODASDSLCK    _IO(DASD_IOCTL_LETTER,4) /* steal lock */
multiline_comment|/* reset profiling information of a device */
DECL|macro|BIODASDPRRST
mdefine_line|#define BIODASDPRRST   _IO(DASD_IOCTL_LETTER,5)
multiline_comment|/* enable PAV */
DECL|macro|BIODASDENAPAV
mdefine_line|#define BIODASDENAPAV  _IO(DASD_IOCTL_LETTER,6)
multiline_comment|/* retrieve API version number */
DECL|macro|DASDAPIVER
mdefine_line|#define DASDAPIVER     _IOR(DASD_IOCTL_LETTER,0,int)
multiline_comment|/* Get information on a dasd device */
DECL|macro|BIODASDINFO
mdefine_line|#define BIODASDINFO    _IOR(DASD_IOCTL_LETTER,1,dasd_information_t)
multiline_comment|/* retrieve profiling information of a device */
DECL|macro|BIODASDPRRD
mdefine_line|#define BIODASDPRRD    _IOR(DASD_IOCTL_LETTER,2,dasd_profile_info_t)
multiline_comment|/* Get information on a dasd device (enhanced) */
DECL|macro|BIODASDINFO2
mdefine_line|#define BIODASDINFO2   _IOR(DASD_IOCTL_LETTER,3,dasd_information2_t)
multiline_comment|/* Performance Statistics Read */
DECL|macro|BIODASDPSRD
mdefine_line|#define BIODASDPSRD    _IOR(DASD_IOCTL_LETTER,4,dasd_rssd_perf_stats_t)
multiline_comment|/* #define BIODASDFORMAT  _IOW(IOCTL_LETTER,0,format_data_t) , deprecated */
DECL|macro|BIODASDFMT
mdefine_line|#define BIODASDFMT     _IOW(DASD_IOCTL_LETTER,1,format_data_t) 
multiline_comment|/* Set Attributes (cache operations) */
DECL|macro|BIODASDSATTR
mdefine_line|#define BIODASDSATTR   _IOW(DASD_IOCTL_LETTER,2,attrib_data_t) 
macro_line|#endif&t;&t;&t;&t;/* DASD_H */
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4 &n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
