macro_line|#ifndef _RAID0_H
DECL|macro|_RAID0_H
mdefine_line|#define _RAID0_H
macro_line|#include &lt;linux/raid/md.h&gt;
DECL|struct|strip_zone
r_struct
id|strip_zone
(brace
DECL|member|zone_offset
r_int
r_int
id|zone_offset
suffix:semicolon
multiline_comment|/* Zone offset in md_dev */
DECL|member|dev_offset
r_int
r_int
id|dev_offset
suffix:semicolon
multiline_comment|/* Zone offset in real dev */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* Zone size */
DECL|member|nb_dev
r_int
id|nb_dev
suffix:semicolon
multiline_comment|/* # of devices attached to the zone */
DECL|member|dev
id|mdk_rdev_t
op_star
id|dev
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
multiline_comment|/* Devices attached to the zone */
)brace
suffix:semicolon
DECL|struct|raid0_hash
r_struct
id|raid0_hash
(brace
DECL|member|zone0
DECL|member|zone1
r_struct
id|strip_zone
op_star
id|zone0
comma
op_star
id|zone1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|raid0_private_data
r_struct
id|raid0_private_data
(brace
DECL|member|hash_table
r_struct
id|raid0_hash
op_star
id|hash_table
suffix:semicolon
multiline_comment|/* Dynamically allocated */
DECL|member|strip_zone
r_struct
id|strip_zone
op_star
id|strip_zone
suffix:semicolon
multiline_comment|/* This one too */
DECL|member|nr_strip_zones
r_int
id|nr_strip_zones
suffix:semicolon
DECL|member|smallest
r_struct
id|strip_zone
op_star
id|smallest
suffix:semicolon
DECL|member|nr_zones
r_int
id|nr_zones
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|raid0_conf_t
r_typedef
r_struct
id|raid0_private_data
id|raid0_conf_t
suffix:semicolon
DECL|macro|mddev_to_conf
mdefine_line|#define mddev_to_conf(mddev) ((raid0_conf_t *) mddev-&gt;private)
macro_line|#endif
eof
