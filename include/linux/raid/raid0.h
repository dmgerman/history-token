macro_line|#ifndef _RAID0_H
DECL|macro|_RAID0_H
mdefine_line|#define _RAID0_H
macro_line|#include &lt;linux/raid/md.h&gt;
DECL|struct|strip_zone
r_struct
id|strip_zone
(brace
DECL|member|zone_offset
id|sector_t
id|zone_offset
suffix:semicolon
multiline_comment|/* Zone offset in md_dev */
DECL|member|dev_offset
id|sector_t
id|dev_offset
suffix:semicolon
multiline_comment|/* Zone offset in real dev */
DECL|member|size
id|sector_t
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
op_star
id|dev
suffix:semicolon
multiline_comment|/* Devices attached to the zone */
)brace
suffix:semicolon
DECL|struct|raid0_private_data
r_struct
id|raid0_private_data
(brace
DECL|member|hash_table
r_struct
id|strip_zone
op_star
op_star
id|hash_table
suffix:semicolon
multiline_comment|/* Table of indexes into strip_zone */
DECL|member|strip_zone
r_struct
id|strip_zone
op_star
id|strip_zone
suffix:semicolon
DECL|member|devlist
id|mdk_rdev_t
op_star
op_star
id|devlist
suffix:semicolon
multiline_comment|/* lists of rdevs, pointed to by strip_zone-&gt;dev */
DECL|member|nr_strip_zones
r_int
id|nr_strip_zones
suffix:semicolon
DECL|member|hash_spacing
id|sector_t
id|hash_spacing
suffix:semicolon
DECL|member|preshift
r_int
id|preshift
suffix:semicolon
multiline_comment|/* shift this before divide by hash_spacing */
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
