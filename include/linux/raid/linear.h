macro_line|#ifndef _LINEAR_H
DECL|macro|_LINEAR_H
mdefine_line|#define _LINEAR_H
macro_line|#include &lt;linux/raid/md.h&gt;
DECL|struct|dev_info
r_struct
id|dev_info
(brace
DECL|member|bdev
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|dev_info_t
r_typedef
r_struct
id|dev_info
id|dev_info_t
suffix:semicolon
DECL|struct|linear_hash
r_struct
id|linear_hash
(brace
DECL|member|dev0
DECL|member|dev1
id|dev_info_t
op_star
id|dev0
comma
op_star
id|dev1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|linear_private_data
r_struct
id|linear_private_data
(brace
DECL|member|hash_table
r_struct
id|linear_hash
op_star
id|hash_table
suffix:semicolon
DECL|member|disks
id|dev_info_t
id|disks
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
DECL|member|smallest
id|dev_info_t
op_star
id|smallest
suffix:semicolon
DECL|member|nr_zones
r_int
id|nr_zones
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|linear_conf_t
r_typedef
r_struct
id|linear_private_data
id|linear_conf_t
suffix:semicolon
DECL|macro|mddev_to_conf
mdefine_line|#define mddev_to_conf(mddev) ((linear_conf_t *) mddev-&gt;private)
macro_line|#endif
eof
