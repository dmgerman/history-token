multiline_comment|/*&n; *  drivers/s390/block/mdisk.h&n; *    VM minidisk device driver.&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com)&n; */
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|MDISK_DEVS
mdefine_line|#define MDISK_DEVS 8                   /* for disks                        */
DECL|macro|MDISK_RAHEAD
mdefine_line|#define MDISK_RAHEAD 8                 /* read ahead                       */
DECL|macro|MDISK_BLKSIZE
mdefine_line|#define MDISK_BLKSIZE 1024             /* 1k blocks                        */
DECL|macro|MDISK_HARDSECT
mdefine_line|#define MDISK_HARDSECT 512             /* FIXME -- 512 byte blocks         */
DECL|macro|MDISK_MAXSECTORS
mdefine_line|#define MDISK_MAXSECTORS 256           /* max sectors for one request      */
multiline_comment|/* &n; * low level io defines for diagnose 250&n; */
DECL|macro|MDISK_WRITE_REQ
mdefine_line|#define MDISK_WRITE_REQ 0x01                                                 
DECL|macro|MDISK_READ_REQ
mdefine_line|#define MDISK_READ_REQ  0x02                                                   
DECL|macro|MDISK_SYNC
mdefine_line|#define MDISK_SYNC      0x00
DECL|macro|MDISK_ASYNC
mdefine_line|#define MDISK_ASYNC     0x02
DECL|macro|INIT_BIO
mdefine_line|#define INIT_BIO        0x00
DECL|macro|RW_BIO
mdefine_line|#define RW_BIO          0x01
DECL|macro|TERM_BIO
mdefine_line|#define TERM_BIO        0x02
multiline_comment|/*&n; * This stucture is used for clustered request&n; * up to 256 different request can be handled with one invocation&n; */
r_typedef
r_struct
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|status
id|u8
id|status
suffix:semicolon
DECL|member|spare1
id|u16
id|spare1
suffix:semicolon
DECL|member|block_number
id|u32
id|block_number
suffix:semicolon
DECL|member|alet
id|u32
id|alet
suffix:semicolon
DECL|member|buffer
id|u32
id|buffer
suffix:semicolon
DECL|typedef|mdisk_bio_t
)brace
id|mdisk_bio_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|dev_nr
id|u16
id|dev_nr
suffix:semicolon
DECL|member|spare1
id|u16
id|spare1
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|block_size
id|u32
id|block_size
suffix:semicolon
DECL|member|offset
id|u32
id|offset
suffix:semicolon
DECL|member|start_block
id|u32
id|start_block
suffix:semicolon
DECL|member|end_block
id|u32
id|end_block
suffix:semicolon
DECL|member|spare2
id|u32
id|spare2
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|mdisk_init_io_t
)brace
id|mdisk_init_io_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|dev_nr
id|u16
id|dev_nr
suffix:semicolon
DECL|member|spare1
id|u16
id|spare1
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|key
id|u8
id|key
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|spare2
id|u16
id|spare2
suffix:semicolon
DECL|member|block_count
id|u32
id|block_count
suffix:semicolon
DECL|member|alet
id|u32
id|alet
suffix:semicolon
DECL|member|bio_list
id|u32
id|bio_list
suffix:semicolon
DECL|member|interrupt_params
id|u32
id|interrupt_params
suffix:semicolon
DECL|member|spare3
id|u32
id|spare3
(braket
l_int|5
)braket
suffix:semicolon
DECL|typedef|mdisk_rw_io_t
)brace
id|mdisk_rw_io_t
suffix:semicolon
multiline_comment|/*&n; * low level definitions for Diagnose 210&n; */
DECL|macro|DEV_CLASS_FBA
mdefine_line|#define DEV_CLASS_FBA   0x01
multiline_comment|/*&n; * Data structures for Diagnose 210&n; */
r_typedef
r_struct
(brace
DECL|member|dev_nr
id|u16
id|dev_nr
suffix:semicolon
DECL|member|rdc_len
id|u16
id|rdc_len
suffix:semicolon
DECL|member|vdev_class
id|u8
id|vdev_class
suffix:semicolon
DECL|member|vdev_type
id|u8
id|vdev_type
suffix:semicolon
DECL|member|vdev_status
id|u8
id|vdev_status
suffix:semicolon
DECL|member|vdev_flags
id|u8
id|vdev_flags
suffix:semicolon
DECL|member|rdev_class
id|u8
id|rdev_class
suffix:semicolon
DECL|member|rdev_type
id|u8
id|rdev_type
suffix:semicolon
DECL|member|rdev_model
id|u8
id|rdev_model
suffix:semicolon
DECL|member|rdev_features
id|u8
id|rdev_features
suffix:semicolon
DECL|typedef|mdisk_dev_char_t
)brace
id|mdisk_dev_char_t
suffix:semicolon
eof
