multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2004 Silicon Graphics, Inc. All rights reserved.&n; *&n; * Data types used by the SN_SAL_HWPERF_OP SAL call for monitoring&n; * SGI Altix node and router hardware&n; *&n; * Mark Goodwin &lt;markgw@sgi.com&gt; Mon Aug 30 12:23:46 EST 2004&n; */
macro_line|#ifndef SN_HWPERF_H
DECL|macro|SN_HWPERF_H
mdefine_line|#define SN_HWPERF_H
multiline_comment|/*&n; * object structure. SN_HWPERF_ENUM_OBJECTS and SN_HWPERF_GET_CPU_INFO&n; * return an array of these. Do not change this without also&n; * changing the corresponding SAL code.&n; */
DECL|macro|SN_HWPERF_MAXSTRING
mdefine_line|#define SN_HWPERF_MAXSTRING&t;&t;128
DECL|struct|sn_hwperf_object_info
r_struct
id|sn_hwperf_object_info
(brace
DECL|member|id
id|u32
id|id
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|this_part
id|u64
id|this_part
suffix:colon
l_int|1
suffix:semicolon
DECL|member|is_shared
id|u64
id|is_shared
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
r_struct
(brace
DECL|member|flags
id|u64
id|flags
suffix:semicolon
DECL|member|reserved
id|u64
id|reserved
suffix:semicolon
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|member|f
)brace
id|f
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|SN_HWPERF_MAXSTRING
)braket
suffix:semicolon
DECL|member|location
r_char
id|location
(braket
id|SN_HWPERF_MAXSTRING
)braket
suffix:semicolon
DECL|member|ports
id|u32
id|ports
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|sn_hwp_this_part
mdefine_line|#define sn_hwp_this_part&t;f.fields.this_part
DECL|macro|sn_hwp_is_shared
mdefine_line|#define sn_hwp_is_shared&t;f.fields.is_shared
DECL|macro|sn_hwp_flags
mdefine_line|#define sn_hwp_flags&t;&t;f.b.flags
multiline_comment|/* macros for object classification */
DECL|macro|SN_HWPERF_IS_NODE
mdefine_line|#define SN_HWPERF_IS_NODE(x)&t;&t;((x) &amp;&amp; strstr((x)-&gt;name, &quot;SHub&quot;))
DECL|macro|SN_HWPERF_IS_IONODE
mdefine_line|#define SN_HWPERF_IS_IONODE(x)&t;&t;((x) &amp;&amp; strstr((x)-&gt;name, &quot;TIO&quot;))
DECL|macro|SN_HWPERF_IS_ROUTER
mdefine_line|#define SN_HWPERF_IS_ROUTER(x)&t;&t;((x) &amp;&amp; strstr((x)-&gt;name, &quot;Router&quot;))
DECL|macro|SN_HWPERF_IS_NL3ROUTER
mdefine_line|#define SN_HWPERF_IS_NL3ROUTER(x)&t;((x) &amp;&amp; strstr((x)-&gt;name, &quot;NL3Router&quot;))
DECL|macro|SN_HWPERF_FOREIGN
mdefine_line|#define SN_HWPERF_FOREIGN(x)&t;&t;((x) &amp;&amp; !(x)-&gt;sn_hwp_this_part &amp;&amp; !(x)-&gt;sn_hwp_is_shared)
DECL|macro|SN_HWPERF_SAME_OBJTYPE
mdefine_line|#define SN_HWPERF_SAME_OBJTYPE(x,y)&t;((SN_HWPERF_IS_NODE(x) &amp;&amp; SN_HWPERF_IS_NODE(y)) ||&bslash;&n;&t;&t;&t;&t;&t;(SN_HWPERF_IS_IONODE(x) &amp;&amp; SN_HWPERF_IS_IONODE(y)) ||&bslash;&n;&t;&t;&t;&t;&t;(SN_HWPERF_IS_ROUTER(x) &amp;&amp; SN_HWPERF_IS_ROUTER(y)))
multiline_comment|/* numa port structure, SN_HWPERF_ENUM_PORTS returns an array of these */
DECL|struct|sn_hwperf_port_info
r_struct
id|sn_hwperf_port_info
(brace
DECL|member|port
id|u32
id|port
suffix:semicolon
DECL|member|conn_id
id|u32
id|conn_id
suffix:semicolon
DECL|member|conn_port
id|u32
id|conn_port
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* for HWPERF_{GET,SET}_MMRS */
DECL|struct|sn_hwperf_data
r_struct
id|sn_hwperf_data
(brace
DECL|member|addr
id|u64
id|addr
suffix:semicolon
DECL|member|data
id|u64
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* user ioctl() argument, see below */
DECL|struct|sn_hwperf_ioctl_args
r_struct
id|sn_hwperf_ioctl_args
(brace
DECL|member|arg
id|u64
id|arg
suffix:semicolon
multiline_comment|/* argument, usually an object id */
DECL|member|sz
id|u64
id|sz
suffix:semicolon
multiline_comment|/* size of transfer */
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
multiline_comment|/* pointer to source/target */
DECL|member|v0
id|u32
id|v0
suffix:semicolon
multiline_comment|/* second return value */
)brace
suffix:semicolon
multiline_comment|/*&n; * For SN_HWPERF_{GET,SET}_MMRS and SN_HWPERF_OBJECT_DISTANCE,&n; * sn_hwperf_ioctl_args.arg can be used to specify a CPU on which&n; * to call SAL, and whether to use an interprocessor interrupt&n; * or task migration in order to do so. If the CPU specified is&n; * SN_HWPERF_ARG_ANY_CPU, then the current CPU will be used.&n; */
DECL|macro|SN_HWPERF_ARG_ANY_CPU
mdefine_line|#define SN_HWPERF_ARG_ANY_CPU&t;&t;0x7fffffffUL
DECL|macro|SN_HWPERF_ARG_CPU_MASK
mdefine_line|#define SN_HWPERF_ARG_CPU_MASK&t;&t;0x7fffffff00000000ULL
DECL|macro|SN_HWPERF_ARG_USE_IPI_MASK
mdefine_line|#define SN_HWPERF_ARG_USE_IPI_MASK&t;0x8000000000000000ULL
DECL|macro|SN_HWPERF_ARG_OBJID_MASK
mdefine_line|#define SN_HWPERF_ARG_OBJID_MASK&t;0x00000000ffffffffULL
multiline_comment|/* &n; * ioctl requests on the &quot;sn_hwperf&quot; misc device that call SAL.&n; */
DECL|macro|SN_HWPERF_OP_MEM_COPYIN
mdefine_line|#define SN_HWPERF_OP_MEM_COPYIN&t;&t;0x1000
DECL|macro|SN_HWPERF_OP_MEM_COPYOUT
mdefine_line|#define SN_HWPERF_OP_MEM_COPYOUT&t;0x2000
DECL|macro|SN_HWPERF_OP_MASK
mdefine_line|#define SN_HWPERF_OP_MASK&t;&t;0x0fff
multiline_comment|/*&n; * Determine mem requirement.&n; * arg&t;don&squot;t care&n; * sz&t;8&n; * p&t;pointer to u64 integer&n; */
DECL|macro|SN_HWPERF_GET_HEAPSIZE
mdefine_line|#define&t;SN_HWPERF_GET_HEAPSIZE&t;&t;1
multiline_comment|/*&n; * Install mem for SAL drvr&n; * arg&t;don&squot;t care&n; * sz&t;sizeof buffer pointed to by p&n; * p&t;pointer to buffer for scratch area&n; */
DECL|macro|SN_HWPERF_INSTALL_HEAP
mdefine_line|#define SN_HWPERF_INSTALL_HEAP&t;&t;2
multiline_comment|/*&n; * Determine number of objects&n; * arg&t;don&squot;t care&n; * sz&t;8&n; * p&t;pointer to u64 integer&n; */
DECL|macro|SN_HWPERF_OBJECT_COUNT
mdefine_line|#define SN_HWPERF_OBJECT_COUNT&t;&t;(10|SN_HWPERF_OP_MEM_COPYOUT)
multiline_comment|/*&n; * Determine object &quot;distance&quot;, relative to a cpu. This operation can&n; * execute on a designated logical cpu number, using either an IPI or&n; * via task migration. If the cpu number is SN_HWPERF_ANY_CPU, then&n; * the current CPU is used. See the SN_HWPERF_ARG_* macros above.&n; *&n; * arg&t;bitmap of IPI flag, cpu number and object id&n; * sz&t;8&n; * p&t;pointer to u64 integer&n; */
DECL|macro|SN_HWPERF_OBJECT_DISTANCE
mdefine_line|#define SN_HWPERF_OBJECT_DISTANCE&t;(11|SN_HWPERF_OP_MEM_COPYOUT)
multiline_comment|/*&n; * Enumerate objects. Special case if sz == 8, returns the required&n; * buffer size.&n; * arg&t;don&squot;t care&n; * sz&t;sizeof buffer pointed to by p&n; * p&t;pointer to array of struct sn_hwperf_object_info&n; */
DECL|macro|SN_HWPERF_ENUM_OBJECTS
mdefine_line|#define SN_HWPERF_ENUM_OBJECTS&t;&t;(12|SN_HWPERF_OP_MEM_COPYOUT)
multiline_comment|/*&n; * Enumerate NumaLink ports for an object. Special case if sz == 8,&n; * returns the required buffer size.&n; * arg&t;object id&n; * sz&t;sizeof buffer pointed to by p&n; * p&t;pointer to array of struct sn_hwperf_port_info&n; */
DECL|macro|SN_HWPERF_ENUM_PORTS
mdefine_line|#define SN_HWPERF_ENUM_PORTS&t;&t;(13|SN_HWPERF_OP_MEM_COPYOUT)
multiline_comment|/*&n; * SET/GET memory mapped registers. These operations can execute&n; * on a designated logical cpu number, using either an IPI or via&n; * task migration. If the cpu number is SN_HWPERF_ANY_CPU, then&n; * the current CPU is used. See the SN_HWPERF_ARG_* macros above.&n; *&n; * arg&t;bitmap of ipi flag, cpu number and object id&n; * sz&t;sizeof buffer pointed to by p&n; * p&t;pointer to array of struct sn_hwperf_data&n; */
DECL|macro|SN_HWPERF_SET_MMRS
mdefine_line|#define SN_HWPERF_SET_MMRS&t;&t;(14|SN_HWPERF_OP_MEM_COPYIN)
DECL|macro|SN_HWPERF_GET_MMRS
mdefine_line|#define SN_HWPERF_GET_MMRS&t;&t;(15|SN_HWPERF_OP_MEM_COPYOUT| &bslash;&n;&t;&t;&t;&t;&t;    SN_HWPERF_OP_MEM_COPYIN)
multiline_comment|/*&n; * Lock a shared object&n; * arg&t;object id&n; * sz&t;don&squot;t care&n; * p&t;don&squot;t care&n; */
DECL|macro|SN_HWPERF_ACQUIRE
mdefine_line|#define SN_HWPERF_ACQUIRE&t;&t;16
multiline_comment|/*&n; * Unlock a shared object&n; * arg&t;object id&n; * sz&t;don&squot;t care&n; * p&t;don&squot;t care&n; */
DECL|macro|SN_HWPERF_RELEASE
mdefine_line|#define SN_HWPERF_RELEASE&t;&t;17
multiline_comment|/*&n; * Break a lock on a shared object&n; * arg&t;object id&n; * sz&t;don&squot;t care&n; * p&t;don&squot;t care&n; */
DECL|macro|SN_HWPERF_FORCE_RELEASE
mdefine_line|#define SN_HWPERF_FORCE_RELEASE&t;&t;18
multiline_comment|/*&n; * ioctl requests on &quot;sn_hwperf&quot; that do not call SAL&n; */
multiline_comment|/*&n; * get cpu info as an array of hwperf_object_info_t. &n; * id is logical CPU number, name is description, location&n; * is geoid (e.g. 001c04#1c). Special case if sz == 8,&n; * returns the required buffer size.&n; *&n; * arg&t;don&squot;t care&n; * sz&t;sizeof buffer pointed to by p&n; * p&t;pointer to array of struct sn_hwperf_object_info&n; */
DECL|macro|SN_HWPERF_GET_CPU_INFO
mdefine_line|#define SN_HWPERF_GET_CPU_INFO&t;&t;(100|SN_HWPERF_OP_MEM_COPYOUT)
multiline_comment|/*&n; * Given an object id, return it&squot;s node number (aka cnode).&n; * arg&t;object id&n; * sz&t;8&n; * p&t;pointer to u64 integer&n; */
DECL|macro|SN_HWPERF_GET_OBJ_NODE
mdefine_line|#define SN_HWPERF_GET_OBJ_NODE&t;&t;(101|SN_HWPERF_OP_MEM_COPYOUT)
multiline_comment|/*&n; * Given a node number (cnode), return it&squot;s nasid.&n; * arg&t;ordinal node number (aka cnodeid)&n; * sz&t;8&n; * p&t;pointer to u64 integer&n; */
DECL|macro|SN_HWPERF_GET_NODE_NASID
mdefine_line|#define SN_HWPERF_GET_NODE_NASID&t;(102|SN_HWPERF_OP_MEM_COPYOUT)
multiline_comment|/* return codes */
DECL|macro|SN_HWPERF_OP_OK
mdefine_line|#define SN_HWPERF_OP_OK&t;&t;&t;0
DECL|macro|SN_HWPERF_OP_NOMEM
mdefine_line|#define SN_HWPERF_OP_NOMEM&t;&t;1
DECL|macro|SN_HWPERF_OP_NO_PERM
mdefine_line|#define SN_HWPERF_OP_NO_PERM&t;&t;2
DECL|macro|SN_HWPERF_OP_IO_ERROR
mdefine_line|#define SN_HWPERF_OP_IO_ERROR&t;&t;3
DECL|macro|SN_HWPERF_OP_BUSY
mdefine_line|#define SN_HWPERF_OP_BUSY&t;&t;4
DECL|macro|SN_HWPERF_OP_RECONFIGURE
mdefine_line|#define SN_HWPERF_OP_RECONFIGURE&t;253
DECL|macro|SN_HWPERF_OP_INVAL
mdefine_line|#define SN_HWPERF_OP_INVAL&t;&t;254
macro_line|#endif&t;&t;&t;&t;/* SN_HWPERF_H */
eof
