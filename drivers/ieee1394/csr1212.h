multiline_comment|/*&n; * csr1212.h -- IEEE 1212 Control and Status Register support for Linux&n; *&n; * Copyright (C) 2003 Francois Retief &lt;fgretief@sun.ac.za&gt;&n; *                    Steve Kinneberg &lt;kinnebergsteve@acmsystems.com&gt;&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions are met:&n; *&n; *    1. Redistributions of source code must retain the above copyright notice,&n; *       this list of conditions and the following disclaimer.&n; *    2. Redistributions in binary form must reproduce the above copyright&n; *       notice, this list of conditions and the following disclaimer in the&n; *       documentation and/or other materials provided with the distribution.&n; *    3. The name of the author may not be used to endorse or promote products&n; *       derived from this software without specific prior written permission.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO&n; * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,&n; * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,&n; * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;&n; * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,&n; * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR&n; * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF&n; * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; */
macro_line|#ifndef __CSR1212_H__
DECL|macro|__CSR1212_H__
mdefine_line|#define __CSR1212_H__
multiline_comment|/* Compatibility layer */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
DECL|macro|CSR1212_MALLOC
mdefine_line|#define CSR1212_MALLOC(size)&t;&t;vmalloc((size))
DECL|macro|CSR1212_FREE
mdefine_line|#define CSR1212_FREE(ptr)&t;&t;vfree(ptr)
DECL|macro|CSR1212_BE16_TO_CPU
mdefine_line|#define CSR1212_BE16_TO_CPU(quad)&t;be16_to_cpu(quad)
DECL|macro|CSR1212_CPU_TO_BE16
mdefine_line|#define CSR1212_CPU_TO_BE16(quad)&t;cpu_to_be16(quad)
DECL|macro|CSR1212_BE32_TO_CPU
mdefine_line|#define CSR1212_BE32_TO_CPU(quad)&t;be32_to_cpu(quad)
DECL|macro|CSR1212_CPU_TO_BE32
mdefine_line|#define CSR1212_CPU_TO_BE32(quad)&t;cpu_to_be32(quad)
DECL|macro|CSR1212_BE64_TO_CPU
mdefine_line|#define CSR1212_BE64_TO_CPU(quad)&t;be64_to_cpu(quad)
DECL|macro|CSR1212_CPU_TO_BE64
mdefine_line|#define CSR1212_CPU_TO_BE64(quad)&t;cpu_to_be64(quad)
DECL|macro|CSR1212_LE16_TO_CPU
mdefine_line|#define CSR1212_LE16_TO_CPU(quad)&t;le16_to_cpu(quad)
DECL|macro|CSR1212_CPU_TO_LE16
mdefine_line|#define CSR1212_CPU_TO_LE16(quad)&t;cpu_to_le16(quad)
DECL|macro|CSR1212_LE32_TO_CPU
mdefine_line|#define CSR1212_LE32_TO_CPU(quad)&t;le32_to_cpu(quad)
DECL|macro|CSR1212_CPU_TO_LE32
mdefine_line|#define CSR1212_CPU_TO_LE32(quad)&t;cpu_to_le32(quad)
DECL|macro|CSR1212_LE64_TO_CPU
mdefine_line|#define CSR1212_LE64_TO_CPU(quad)&t;le64_to_cpu(quad)
DECL|macro|CSR1212_CPU_TO_LE64
mdefine_line|#define CSR1212_CPU_TO_LE64(quad)&t;cpu_to_le64(quad)
macro_line|#include &lt;linux/errno.h&gt;
DECL|macro|CSR1212_SUCCESS
mdefine_line|#define CSR1212_SUCCESS (0)
DECL|macro|CSR1212_EINVAL
mdefine_line|#define CSR1212_EINVAL&t;(-EINVAL)
DECL|macro|CSR1212_ENOMEM
mdefine_line|#define CSR1212_ENOMEM&t;(-ENOMEM)
DECL|macro|CSR1212_ENOENT
mdefine_line|#define CSR1212_ENOENT&t;(-ENOENT)
DECL|macro|CSR1212_EIO
mdefine_line|#define CSR1212_EIO&t;(-EIO)
DECL|macro|CSR1212_EBUSY
mdefine_line|#define CSR1212_EBUSY&t;(-EBUSY)
macro_line|#else&t;/* Userspace */
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;malloc.h&gt;
DECL|macro|CSR1212_MALLOC
mdefine_line|#define CSR1212_MALLOC(size)&t;&t;malloc(size)
DECL|macro|CSR1212_FREE
mdefine_line|#define CSR1212_FREE(ptr)&t;&t;free(ptr)
macro_line|#include &lt;endian.h&gt;
macro_line|#if __BYTE_ORDER == __LITTLE_ENDIAN
macro_line|#include &lt;byteswap.h&gt;
DECL|macro|CSR1212_BE16_TO_CPU
mdefine_line|#define CSR1212_BE16_TO_CPU(quad)&t;bswap_16(quad)
DECL|macro|CSR1212_CPU_TO_BE16
mdefine_line|#define CSR1212_CPU_TO_BE16(quad)&t;bswap_16(quad)
DECL|macro|CSR1212_BE32_TO_CPU
mdefine_line|#define CSR1212_BE32_TO_CPU(quad)&t;bswap_32(quad)
DECL|macro|CSR1212_CPU_TO_BE32
mdefine_line|#define CSR1212_CPU_TO_BE32(quad)&t;bswap_32(quad)
DECL|macro|CSR1212_BE64_TO_CPU
mdefine_line|#define CSR1212_BE64_TO_CPU(quad)&t;bswap_64(quad)
DECL|macro|CSR1212_CPU_TO_BE64
mdefine_line|#define CSR1212_CPU_TO_BE64(quad)&t;bswap_64(quad)
DECL|macro|CSR1212_LE16_TO_CPU
mdefine_line|#define CSR1212_LE16_TO_CPU(quad)&t;(quad)
DECL|macro|CSR1212_CPU_TO_LE16
mdefine_line|#define CSR1212_CPU_TO_LE16(quad)&t;(quad)
DECL|macro|CSR1212_LE32_TO_CPU
mdefine_line|#define CSR1212_LE32_TO_CPU(quad)&t;(quad)
DECL|macro|CSR1212_CPU_TO_LE32
mdefine_line|#define CSR1212_CPU_TO_LE32(quad)&t;(quad)
DECL|macro|CSR1212_LE64_TO_CPU
mdefine_line|#define CSR1212_LE64_TO_CPU(quad)&t;(quad)
DECL|macro|CSR1212_CPU_TO_LE64
mdefine_line|#define CSR1212_CPU_TO_LE64(quad)&t;(quad)
macro_line|#else
DECL|macro|CSR1212_BE16_TO_CPU
mdefine_line|#define CSR1212_BE16_TO_CPU(quad)&t;(quad)
DECL|macro|CSR1212_CPU_TO_BE16
mdefine_line|#define CSR1212_CPU_TO_BE16(quad)&t;(quad)
DECL|macro|CSR1212_BE32_TO_CPU
mdefine_line|#define CSR1212_BE32_TO_CPU(quad)&t;(quad)
DECL|macro|CSR1212_CPU_TO_BE32
mdefine_line|#define CSR1212_CPU_TO_BE32(quad)&t;(quad)
DECL|macro|CSR1212_BE64_TO_CPU
mdefine_line|#define CSR1212_BE64_TO_CPU(quad)&t;(quad)
DECL|macro|CSR1212_CPU_TO_BE64
mdefine_line|#define CSR1212_CPU_TO_BE64(quad)&t;(quad)
DECL|macro|CSR1212_LE16_TO_CPU
mdefine_line|#define CSR1212_LE16_TO_CPU(quad)&t;bswap_16(quad)
DECL|macro|CSR1212_CPU_TO_LE16
mdefine_line|#define CSR1212_CPU_TO_LE16(quad)&t;bswap_16(quad)
DECL|macro|CSR1212_LE32_TO_CPU
mdefine_line|#define CSR1212_LE32_TO_CPU(quad)&t;bswap_32(quad)
DECL|macro|CSR1212_CPU_TO_LE32
mdefine_line|#define CSR1212_CPU_TO_LE32(quad)&t;bswap_32(quad)
DECL|macro|CSR1212_LE64_TO_CPU
mdefine_line|#define CSR1212_LE64_TO_CPU(quad)&t;bswap_64(quad)
DECL|macro|CSR1212_CPU_TO_LE64
mdefine_line|#define CSR1212_CPU_TO_LE64(quad)&t;bswap_64(quad)
macro_line|#endif
macro_line|#include &lt;errno.h&gt;
DECL|macro|CSR1212_SUCCESS
mdefine_line|#define CSR1212_SUCCESS (0)
DECL|macro|CSR1212_EINVAL
mdefine_line|#define CSR1212_EINVAL&t;(EINVAL)
DECL|macro|CSR1212_ENOMEM
mdefine_line|#define CSR1212_ENOMEM&t;(ENOMEM)
DECL|macro|CSR1212_ENOENT
mdefine_line|#define CSR1212_ENOENT&t;(ENOENT)
DECL|macro|CSR1212_EIO
mdefine_line|#define CSR1212_EIO&t;(EIO)
DECL|macro|CSR1212_EBUSY
mdefine_line|#define CSR1212_EBUSY&t;(EBUSY)
macro_line|#endif
DECL|macro|CSR1212_KV_VAL_MASK
mdefine_line|#define CSR1212_KV_VAL_MASK&t;&t;&t;0xffffff
DECL|macro|CSR1212_KV_KEY_SHIFT
mdefine_line|#define CSR1212_KV_KEY_SHIFT&t;&t;&t;24
DECL|macro|CSR1212_KV_KEY_TYPE_SHIFT
mdefine_line|#define CSR1212_KV_KEY_TYPE_SHIFT&t;&t;6
DECL|macro|CSR1212_KV_KEY_ID_MASK
mdefine_line|#define CSR1212_KV_KEY_ID_MASK&t;&t;&t;0x3f
DECL|macro|CSR1212_KV_KEY_TYPE_MASK
mdefine_line|#define CSR1212_KV_KEY_TYPE_MASK&t;&t;0x3&t;&t;/* After shift */
multiline_comment|/* CSR 1212 key types */
DECL|macro|CSR1212_KV_TYPE_IMMEDIATE
mdefine_line|#define CSR1212_KV_TYPE_IMMEDIATE&t;&t;0
DECL|macro|CSR1212_KV_TYPE_CSR_OFFSET
mdefine_line|#define CSR1212_KV_TYPE_CSR_OFFSET&t;&t;1
DECL|macro|CSR1212_KV_TYPE_LEAF
mdefine_line|#define CSR1212_KV_TYPE_LEAF&t;&t;&t;2
DECL|macro|CSR1212_KV_TYPE_DIRECTORY
mdefine_line|#define CSR1212_KV_TYPE_DIRECTORY&t;&t;3
multiline_comment|/* CSR 1212 key ids */
DECL|macro|CSR1212_KV_ID_DESCRIPTOR
mdefine_line|#define CSR1212_KV_ID_DESCRIPTOR&t;&t;0x01
DECL|macro|CSR1212_KV_ID_BUS_DEPENDENT_INFO
mdefine_line|#define CSR1212_KV_ID_BUS_DEPENDENT_INFO&t;0x02
DECL|macro|CSR1212_KV_ID_VENDOR
mdefine_line|#define CSR1212_KV_ID_VENDOR&t;&t;&t;0x03
DECL|macro|CSR1212_KV_ID_HARDWARE_VERSION
mdefine_line|#define CSR1212_KV_ID_HARDWARE_VERSION&t;&t;0x04
DECL|macro|CSR1212_KV_ID_MODULE
mdefine_line|#define CSR1212_KV_ID_MODULE&t;&t;&t;0x07
DECL|macro|CSR1212_KV_ID_NODE_CAPABILITIES
mdefine_line|#define CSR1212_KV_ID_NODE_CAPABILITIES&t;&t;0x0C
DECL|macro|CSR1212_KV_ID_EUI_64
mdefine_line|#define CSR1212_KV_ID_EUI_64&t;&t;&t;0x0D
DECL|macro|CSR1212_KV_ID_UNIT
mdefine_line|#define CSR1212_KV_ID_UNIT&t;&t;&t;0x11
DECL|macro|CSR1212_KV_ID_SPECIFIER_ID
mdefine_line|#define CSR1212_KV_ID_SPECIFIER_ID&t;&t;0x12
DECL|macro|CSR1212_KV_ID_VERSION
mdefine_line|#define CSR1212_KV_ID_VERSION&t;&t;&t;0x13
DECL|macro|CSR1212_KV_ID_DEPENDENT_INFO
mdefine_line|#define CSR1212_KV_ID_DEPENDENT_INFO&t;&t;0x14
DECL|macro|CSR1212_KV_ID_UNIT_LOCATION
mdefine_line|#define CSR1212_KV_ID_UNIT_LOCATION&t;&t;0x15
DECL|macro|CSR1212_KV_ID_MODEL
mdefine_line|#define CSR1212_KV_ID_MODEL&t;&t;&t;0x17
DECL|macro|CSR1212_KV_ID_INSTANCE
mdefine_line|#define CSR1212_KV_ID_INSTANCE&t;&t;&t;0x18
DECL|macro|CSR1212_KV_ID_KEYWORD
mdefine_line|#define CSR1212_KV_ID_KEYWORD&t;&t;&t;0x19
DECL|macro|CSR1212_KV_ID_FEATURE
mdefine_line|#define CSR1212_KV_ID_FEATURE&t;&t;&t;0x1A
DECL|macro|CSR1212_KV_ID_EXTENDED_ROM
mdefine_line|#define CSR1212_KV_ID_EXTENDED_ROM&t;&t;0x1B
DECL|macro|CSR1212_KV_ID_EXTENDED_KEY_SPECIFIER_ID
mdefine_line|#define CSR1212_KV_ID_EXTENDED_KEY_SPECIFIER_ID&t;0x1C
DECL|macro|CSR1212_KV_ID_EXTENDED_KEY
mdefine_line|#define CSR1212_KV_ID_EXTENDED_KEY&t;&t;0x1D
DECL|macro|CSR1212_KV_ID_EXTENDED_DATA
mdefine_line|#define CSR1212_KV_ID_EXTENDED_DATA&t;&t;0x1E
DECL|macro|CSR1212_KV_ID_MODIFIABLE_DESCRIPTOR
mdefine_line|#define CSR1212_KV_ID_MODIFIABLE_DESCRIPTOR&t;0x1F
DECL|macro|CSR1212_KV_ID_DIRECTORY_ID
mdefine_line|#define CSR1212_KV_ID_DIRECTORY_ID&t;&t;0x20
DECL|macro|CSR1212_KV_ID_REVISION
mdefine_line|#define CSR1212_KV_ID_REVISION&t;&t;&t;0x21
multiline_comment|/* IEEE 1212 Address space map */
DECL|macro|CSR1212_ALL_SPACE_BASE
mdefine_line|#define CSR1212_ALL_SPACE_BASE&t;&t;&t;(0x000000000000ULL)
DECL|macro|CSR1212_ALL_SPACE_SIZE
mdefine_line|#define CSR1212_ALL_SPACE_SIZE&t;&t;&t;(1ULL &lt;&lt; 48)
DECL|macro|CSR1212_ALL_SPACE_END
mdefine_line|#define CSR1212_ALL_SPACE_END&t;&t;&t;(CSR1212_ALL_SPACE_BASE + CSR1212_ALL_SPACE_SIZE)
DECL|macro|CSR1212_MEMORY_SPACE_BASE
mdefine_line|#define  CSR1212_MEMORY_SPACE_BASE&t;&t;(0x000000000000ULL)
DECL|macro|CSR1212_MEMORY_SPACE_SIZE
mdefine_line|#define  CSR1212_MEMORY_SPACE_SIZE&t;&t;((256ULL * (1ULL &lt;&lt; 40)) - (512ULL * (1ULL &lt;&lt; 20)))
DECL|macro|CSR1212_MEMORY_SPACE_END
mdefine_line|#define  CSR1212_MEMORY_SPACE_END&t;&t;(CSR1212_MEMORY_SPACE_BASE + CSR1212_MEMORY_SPACE_SIZE)
DECL|macro|CSR1212_PRIVATE_SPACE_BASE
mdefine_line|#define  CSR1212_PRIVATE_SPACE_BASE&t;&t;(0xffffe0000000ULL)
DECL|macro|CSR1212_PRIVATE_SPACE_SIZE
mdefine_line|#define  CSR1212_PRIVATE_SPACE_SIZE&t;&t;(256ULL * (1ULL &lt;&lt; 20))
DECL|macro|CSR1212_PRIVATE_SPACE_END
mdefine_line|#define  CSR1212_PRIVATE_SPACE_END&t;&t;(CSR1212_PRIVATE_SPACE_BASE + CSR1212_PRIVATE_SPACE_SIZE)
DECL|macro|CSR1212_REGISTER_SPACE_BASE
mdefine_line|#define  CSR1212_REGISTER_SPACE_BASE&t;&t;(0xfffff0000000ULL)
DECL|macro|CSR1212_REGISTER_SPACE_SIZE
mdefine_line|#define  CSR1212_REGISTER_SPACE_SIZE&t;&t;(256ULL * (1ULL &lt;&lt; 20))
DECL|macro|CSR1212_REGISTER_SPACE_END
mdefine_line|#define  CSR1212_REGISTER_SPACE_END&t;&t;(CSR1212_REGISTER_SPACE_BASE + CSR1212_REGISTER_SPACE_SIZE)
DECL|macro|CSR1212_CSR_ARCH_REG_SPACE_BASE
mdefine_line|#define  CSR1212_CSR_ARCH_REG_SPACE_BASE&t;(0xfffff0000000ULL)
DECL|macro|CSR1212_CSR_ARCH_REG_SPACE_SIZE
mdefine_line|#define  CSR1212_CSR_ARCH_REG_SPACE_SIZE&t;(512)
DECL|macro|CSR1212_CSR_ARCH_REG_SPACE_END
mdefine_line|#define  CSR1212_CSR_ARCH_REG_SPACE_END&t;&t;(CSR1212_CSR_ARCH_REG_SPACE_BASE + CSR1212_CSR_ARCH_REG_SPACE_SIZE)
DECL|macro|CSR1212_CSR_ARCH_REG_SPACE_OFFSET
mdefine_line|#define  CSR1212_CSR_ARCH_REG_SPACE_OFFSET&t;(CSR1212_CSR_ARCH_REG_SPACE_BASE - CSR1212_REGISTER_SPACE_BASE)
DECL|macro|CSR1212_CSR_BUS_DEP_REG_SPACE_BASE
mdefine_line|#define  CSR1212_CSR_BUS_DEP_REG_SPACE_BASE&t;(0xfffff0000200ULL)
DECL|macro|CSR1212_CSR_BUS_DEP_REG_SPACE_SIZE
mdefine_line|#define  CSR1212_CSR_BUS_DEP_REG_SPACE_SIZE&t;(512)
DECL|macro|CSR1212_CSR_BUS_DEP_REG_SPACE_END
mdefine_line|#define  CSR1212_CSR_BUS_DEP_REG_SPACE_END&t;(CSR1212_CSR_BUS_DEP_REG_SPACE_BASE + CSR1212_CSR_BUS_DEP_REG_SPACE_SIZE)
DECL|macro|CSR1212_CSR_BUS_DEP_REG_SPACE_OFFSET
mdefine_line|#define  CSR1212_CSR_BUS_DEP_REG_SPACE_OFFSET&t;(CSR1212_CSR_BUS_DEP_REG_SPACE_BASE - CSR1212_REGISTER_SPACE_BASE)
DECL|macro|CSR1212_CONFIG_ROM_SPACE_BASE
mdefine_line|#define  CSR1212_CONFIG_ROM_SPACE_BASE&t;&t;(0xfffff0000400ULL)
DECL|macro|CSR1212_CONFIG_ROM_SPACE_SIZE
mdefine_line|#define  CSR1212_CONFIG_ROM_SPACE_SIZE&t;&t;(1024)
DECL|macro|CSR1212_CONFIG_ROM_SPACE_END
mdefine_line|#define  CSR1212_CONFIG_ROM_SPACE_END&t;&t;(CSR1212_CONFIG_ROM_SPACE_BASE + CSR1212_CONFIG_ROM_SPACE_SIZE)
DECL|macro|CSR1212_CONFIG_ROM_SPACE_OFFSET
mdefine_line|#define  CSR1212_CONFIG_ROM_SPACE_OFFSET&t;(CSR1212_CONFIG_ROM_SPACE_BASE - CSR1212_REGISTER_SPACE_BASE)
DECL|macro|CSR1212_UNITS_SPACE_BASE
mdefine_line|#define  CSR1212_UNITS_SPACE_BASE&t;&t;(0xfffff0000800ULL)
DECL|macro|CSR1212_UNITS_SPACE_SIZE
mdefine_line|#define  CSR1212_UNITS_SPACE_SIZE&t;&t;((256ULL * (1ULL &lt;&lt; 20)) - 2048)
DECL|macro|CSR1212_UNITS_SPACE_END
mdefine_line|#define  CSR1212_UNITS_SPACE_END&t;&t;(CSR1212_UNITS_SPACE_BASE + CSR1212_UNITS_SPACE_SIZE)
DECL|macro|CSR1212_UNITS_SPACE_OFFSET
mdefine_line|#define  CSR1212_UNITS_SPACE_OFFSET&t;&t;(CSR1212_UNITS_SPACE_BASE - CSR1212_REGISTER_SPACE_BASE)
DECL|macro|CSR1212_EXTENDED_ROM_SIZE
mdefine_line|#define  CSR1212_EXTENDED_ROM_SIZE&t;&t;(0x10000 * sizeof(u_int32_t))
multiline_comment|/* Config ROM image structures */
DECL|struct|csr1212_bus_info_block_img
r_struct
id|csr1212_bus_info_block_img
(brace
DECL|member|length
id|u_int8_t
id|length
suffix:semicolon
DECL|member|crc_length
id|u_int8_t
id|crc_length
suffix:semicolon
DECL|member|crc
id|u_int16_t
id|crc
suffix:semicolon
multiline_comment|/* Must be last */
DECL|member|data
id|u_int32_t
id|data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* older gcc can&squot;t handle [] which is standard */
)brace
suffix:semicolon
DECL|macro|CSR1212_KV_KEY
mdefine_line|#define CSR1212_KV_KEY(quad)&t;&t;(CSR1212_BE32_TO_CPU(quad) &gt;&gt; CSR1212_KV_KEY_SHIFT)
DECL|macro|CSR1212_KV_KEY_TYPE
mdefine_line|#define CSR1212_KV_KEY_TYPE(quad)&t;(CSR1212_KV_KEY(quad) &gt;&gt; CSR1212_KV_KEY_TYPE_SHIFT)
DECL|macro|CSR1212_KV_KEY_ID
mdefine_line|#define CSR1212_KV_KEY_ID(quad)&t;&t;(CSR1212_KV_KEY(quad) &amp; CSR1212_KV_KEY_ID_MASK)
DECL|macro|CSR1212_KV_VAL
mdefine_line|#define CSR1212_KV_VAL(quad)&t;&t;(CSR1212_BE32_TO_CPU(quad) &amp; CSR1212_KV_VAL_MASK)
DECL|macro|CSR1212_SET_KV_KEY
mdefine_line|#define CSR1212_SET_KV_KEY(quad, key)&t;((quad) = &bslash;&n;&t;CSR1212_CPU_TO_BE32(CSR1212_KV_VAL(quad) | ((key) &lt;&lt; CSR1212_KV_KEY_SHIFT)))
DECL|macro|CSR1212_SET_KV_VAL
mdefine_line|#define CSR1212_SET_KV_VAL(quad, val)&t;((quad) = &bslash;&n;&t;CSR1212_CPU_TO_BE32((CSR1212_KV_KEY(quad) &lt;&lt; CSR1212_KV_KEY_SHIFT) | (val)))
DECL|macro|CSR1212_SET_KV_TYPEID
mdefine_line|#define CSR1212_SET_KV_TYPEID(quad, type, id)&t;((quad) = &bslash;&n;&t;CSR1212_CPU_TO_BE32(CSR1212_KV_VAL(quad) | &bslash;&n;&t;(((((type) &amp; CSR1212_KV_KEY_TYPE_MASK) &lt;&lt; CSR1212_KV_KEY_TYPE_SHIFT) | &bslash;&n;&t;  ((id) &amp; CSR1212_KV_KEY_ID_MASK)) &lt;&lt; CSR1212_KV_KEY_SHIFT)))
DECL|typedef|csr1212_quad_t
r_typedef
id|u_int32_t
id|csr1212_quad_t
suffix:semicolon
DECL|struct|csr1212_keyval_img
r_struct
id|csr1212_keyval_img
(brace
DECL|member|length
id|u_int16_t
id|length
suffix:semicolon
DECL|member|crc
id|u_int16_t
id|crc
suffix:semicolon
multiline_comment|/* Must be last */
DECL|member|data
id|csr1212_quad_t
id|data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* older gcc can&squot;t handle [] which is standard */
)brace
suffix:semicolon
DECL|struct|csr1212_leaf
r_struct
id|csr1212_leaf
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|data
id|u_int32_t
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|csr1212_dentry
r_struct
id|csr1212_dentry
(brace
DECL|member|next
DECL|member|prev
r_struct
id|csr1212_dentry
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
DECL|member|kv
r_struct
id|csr1212_keyval
op_star
id|kv
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|csr1212_directory
r_struct
id|csr1212_directory
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|dentries_head
DECL|member|dentries_tail
r_struct
id|csr1212_dentry
op_star
id|dentries_head
comma
op_star
id|dentries_tail
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|csr1212_keyval
r_struct
id|csr1212_keyval
(brace
r_struct
(brace
DECL|member|type
id|u_int8_t
id|type
suffix:semicolon
DECL|member|id
id|u_int8_t
id|id
suffix:semicolon
DECL|member|key
)brace
id|key
suffix:semicolon
r_union
(brace
DECL|member|immediate
id|u_int32_t
id|immediate
suffix:semicolon
DECL|member|csr_offset
id|u_int32_t
id|csr_offset
suffix:semicolon
DECL|member|leaf
r_struct
id|csr1212_leaf
id|leaf
suffix:semicolon
DECL|member|directory
r_struct
id|csr1212_directory
id|directory
suffix:semicolon
DECL|member|value
)brace
id|value
suffix:semicolon
DECL|member|associate
r_struct
id|csr1212_keyval
op_star
id|associate
suffix:semicolon
DECL|member|refcnt
r_int
id|refcnt
suffix:semicolon
multiline_comment|/* used in generating and/or parsing CSR image */
DECL|member|next
DECL|member|prev
r_struct
id|csr1212_keyval
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
multiline_comment|/* flat list of CSR elements */
DECL|member|offset
id|u_int32_t
id|offset
suffix:semicolon
multiline_comment|/* position in CSR from 0xffff f000 0000 */
DECL|member|valid
id|u_int8_t
id|valid
suffix:semicolon
multiline_comment|/* flag indicating keyval has valid data*/
)brace
suffix:semicolon
DECL|struct|csr1212_cache_region
r_struct
id|csr1212_cache_region
(brace
DECL|member|next
DECL|member|prev
r_struct
id|csr1212_cache_region
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
DECL|member|offset_start
id|u_int32_t
id|offset_start
suffix:semicolon
multiline_comment|/* inclusive */
DECL|member|offset_end
id|u_int32_t
id|offset_end
suffix:semicolon
multiline_comment|/* exclusive */
)brace
suffix:semicolon
DECL|struct|csr1212_csr_rom_cache
r_struct
id|csr1212_csr_rom_cache
(brace
DECL|member|next
DECL|member|prev
r_struct
id|csr1212_csr_rom_cache
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
DECL|member|filled_head
DECL|member|filled_tail
r_struct
id|csr1212_cache_region
op_star
id|filled_head
comma
op_star
id|filled_tail
suffix:semicolon
DECL|member|layout_head
DECL|member|layout_tail
r_struct
id|csr1212_keyval
op_star
id|layout_head
comma
op_star
id|layout_tail
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|offset
id|u_int32_t
id|offset
suffix:semicolon
DECL|member|ext_rom
r_struct
id|csr1212_keyval
op_star
id|ext_rom
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* Must be last */
DECL|member|data
id|u_int32_t
id|data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* older gcc can&squot;t handle [] which is standard */
)brace
suffix:semicolon
DECL|struct|csr1212_csr
r_struct
id|csr1212_csr
(brace
DECL|member|bus_info_len
r_int
id|bus_info_len
suffix:semicolon
multiline_comment|/* bus info block length in bytes */
DECL|member|crc_len
r_int
id|crc_len
suffix:semicolon
multiline_comment|/* crc length in bytes */
DECL|member|bus_info_data
id|u_int32_t
op_star
id|bus_info_data
suffix:semicolon
multiline_comment|/* bus info data incl bus name and EUI */
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
multiline_comment|/* private, bus specific data */
DECL|member|ops
r_struct
id|csr1212_bus_ops
op_star
id|ops
suffix:semicolon
DECL|member|root_kv
r_struct
id|csr1212_keyval
op_star
id|root_kv
suffix:semicolon
DECL|member|max_rom
r_int
id|max_rom
suffix:semicolon
multiline_comment|/* max bytes readable in Config ROM region */
multiline_comment|/* Items below used for image parsing and generation */
DECL|member|cache_head
DECL|member|cache_tail
r_struct
id|csr1212_csr_rom_cache
op_star
id|cache_head
comma
op_star
id|cache_tail
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|csr1212_bus_ops
r_struct
id|csr1212_bus_ops
(brace
multiline_comment|/* This function is used by csr1212 to read additional information&n;&t; * from remote nodes when parsing a Config ROM (i.e., read Config ROM&n;&t; * entries located in the Units Space.  Must return 0 on success&n;&t; * anything else indicates an error. */
DECL|member|bus_read
r_int
(paren
op_star
id|bus_read
)paren
(paren
r_struct
id|csr1212_csr
op_star
id|csr
comma
id|u_int64_t
id|addr
comma
id|u_int16_t
id|length
comma
r_void
op_star
id|buffer
comma
r_void
op_star
r_private
)paren
suffix:semicolon
multiline_comment|/* This function is used by csr1212 to allocate a region in units space&n;&t; * in the event that Config ROM entries don&squot;t all fit in the predefined&n;&t; * 1K region.  The void *private parameter is private member of struct&n;&t; * csr1212_csr. */
DECL|member|allocate_addr_range
id|u_int64_t
(paren
op_star
id|allocate_addr_range
)paren
(paren
id|u_int64_t
id|size
comma
id|u_int32_t
id|alignment
comma
r_void
op_star
r_private
)paren
suffix:semicolon
multiline_comment|/* This function is used by csr1212 to release a region in units space&n;&t; * that is no longer needed. */
DECL|member|release_addr
r_void
(paren
op_star
id|release_addr
)paren
(paren
id|u_int64_t
id|addr
comma
r_void
op_star
r_private
)paren
suffix:semicolon
multiline_comment|/* This function is used by csr1212 to determine the max read request&n;&t; * supported by a remote node when reading the ConfigROM space.  Must&n;&t; * return 0, 1, or 2 per IEEE 1212.  */
DECL|member|get_max_rom
r_int
(paren
op_star
id|get_max_rom
)paren
(paren
id|u_int32_t
op_star
id|bus_info
comma
r_void
op_star
r_private
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Descriptor Leaf manipulation macros */
DECL|macro|CSR1212_DESCRIPTOR_LEAF_TYPE_SHIFT
mdefine_line|#define CSR1212_DESCRIPTOR_LEAF_TYPE_SHIFT 24
DECL|macro|CSR1212_DESCRIPTOR_LEAF_SPECIFIER_ID_MASK
mdefine_line|#define CSR1212_DESCRIPTOR_LEAF_SPECIFIER_ID_MASK 0xffffff
DECL|macro|CSR1212_DESCRIPTOR_LEAF_OVERHEAD
mdefine_line|#define CSR1212_DESCRIPTOR_LEAF_OVERHEAD (1 * sizeof(u_int32_t))
DECL|macro|CSR1212_DESCRIPTOR_LEAF_TYPE
mdefine_line|#define CSR1212_DESCRIPTOR_LEAF_TYPE(kv) &bslash;&n;&t;(CSR1212_BE32_TO_CPU((kv)-&gt;value.leaf.data[0]) &gt;&gt; CSR1212_DESCRIPTOR_LEAF_TYPE_SHIFT)
DECL|macro|CSR1212_DESCRIPTOR_LEAF_SPECIFIER_ID
mdefine_line|#define CSR1212_DESCRIPTOR_LEAF_SPECIFIER_ID(kv) &bslash;&n;&t;(CSR1212_BE32_TO_CPU((kv)-&gt;value.leaf.data[0]) &amp; &bslash;&n;&t; CSR1212_DESCRIPTOR_LEAF_SPECIFIER_ID_MASK)
DECL|macro|CSR1212_DESCRIPTOR_LEAF_DATA
mdefine_line|#define CSR1212_DESCRIPTOR_LEAF_DATA(kv) &bslash;&n;&t;(&amp;((kv)-&gt;value.leaf.data[1]))
DECL|macro|CSR1212_DESCRIPTOR_LEAF_SET_TYPE
mdefine_line|#define CSR1212_DESCRIPTOR_LEAF_SET_TYPE(kv, type) &bslash;&n;&t;((kv)-&gt;value.leaf.data[0] = &bslash;&n;&t; CSR1212_CPU_TO_BE32(CSR1212_DESCRIPTOR_LEAF_SPECIFIER_ID(kv) | &bslash;&n;&t;&t;&t;     ((type) &lt;&lt; CSR1212_DESCRIPTOR_LEAF_TYPE_SHIFT)))
DECL|macro|CSR1212_DESCRIPTOR_LEAF_SET_SPECIFIER_ID
mdefine_line|#define CSR1212_DESCRIPTOR_LEAF_SET_SPECIFIER_ID(kv, spec_id) &bslash;&n;&t;((kv)-&gt;value.leaf.data[0] = &bslash;&n;&t; CSR1212_CPU_TO_BE32((CSR1212_DESCRIPTOR_LEAF_TYPE(kv) &lt;&lt; &bslash;&n;&t;&t;&t;      CSR1212_DESCRIPTOR_LEAF_TYPE_SHIFT) | &bslash;&n;&t;&t;&t;     ((spec_id) &amp; CSR1212_DESCRIPTOR_LEAF_SPECIFIER_ID_MASK)))
multiline_comment|/* Text Descriptor Leaf manipulation macros */
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_WIDTH_SHIFT
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_WIDTH_SHIFT 28
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_WIDTH_MASK
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_WIDTH_MASK 0xf /* after shift */
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_CHAR_SET_SHIFT
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_CHAR_SET_SHIFT 16
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_CHAR_SET_MASK
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_CHAR_SET_MASK 0xfff  /* after shift */
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_LANGUAGE_MASK
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_LANGUAGE_MASK 0xffff
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_OVERHEAD
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_OVERHEAD (1 * sizeof(u_int32_t))
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_WIDTH
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_WIDTH(kv) &bslash;&n;&t;(CSR1212_BE32_TO_CPU((kv)-&gt;value.leaf.data[1]) &gt;&gt; &bslash;&n;&t; CSR1212_TEXTUAL_DESCRIPTOR_LEAF_WIDTH_SHIFT)
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_CHAR_SET
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_CHAR_SET(kv) &bslash;&n;&t;((CSR1212_BE32_TO_CPU((kv)-&gt;value.leaf.data[1]) &gt;&gt; &bslash;&n;&t;&t;&t;     CSR1212_TEXTUAL_DESCRIPTOR_LEAF_CHAR_SET_SHIFT) &amp; &bslash;&n;&t;&t;&t;    CSR1212_TEXTUAL_DESCRIPTOR_LEAF_CHAR_SET_MASK)
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_LANGUAGE
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_LANGUAGE(kv) &bslash;&n;&t;(CSR1212_BE32_TO_CPU((kv)-&gt;value.leaf.data[1]) &amp; &bslash;&n;&t; CSR1212_TEXTUAL_DESCRIPTOR_LEAF_LANGUAGE_MASK)
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_DATA
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_DATA(kv) &bslash;&n;&t;(&amp;((kv)-&gt;value.leaf.data[2]))
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_SET_WIDTH
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_SET_WIDTH(kv, width) &bslash;&n;&t;((kv)-&gt;value.leaf.data[1] = &bslash;&n;&t; ((kv)-&gt;value.leaf.data[1] &amp; &bslash;&n;&t;  CSR1212_CPU_TO_BE32(~(CSR1212_TEXTUAL_DESCRIPTOR_LEAF_WIDTH_MASK &lt;&lt; &bslash;&n;&t;&t;&t;&t;CSR1212_TEXTUAL_DESCRIPTOR_LEAF_WIDTH_SHIFT))) | &bslash;&n;&t; CSR1212_CPU_TO_BE32(((width) &amp; &bslash;&n;&t;&t;&t;      CSR1212_TEXTUAL_DESCRIPTOR_LEAF_WIDTH_MASK) &lt;&lt; &bslash;&n;&t;&t;&t;     CSR1212_TEXTUAL_DESCRIPTOR_LEAF_WIDTH_SHIFT))
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_SET_CHAR_SET
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_SET_CHAR_SET(kv, char_set) &bslash;&n;&t;((kv)-&gt;value.leaf.data[1] = &bslash;&n;&t; ((kv)-&gt;value.leaf.data[1] &amp; &bslash;&n;&t;  CSR1212_CPU_TO_BE32(~(CSR1212_TEXTUAL_DESCRIPTOR_LEAF_CHAR_SET_MASK &lt;&lt; &bslash;&n;&t;&t;&t;&t;CSR1212_TEXTUAL_DESCRIPTOR_LEAF_CHAR_SET_SHIFT))) | &bslash;&n;&t; CSR1212_CPU_TO_BE32(((char_set) &amp; &bslash;&n;&t;&t;&t;      CSR1212_TEXTUAL_DESCRIPTOR_LEAF_CHAR_SET_MASK) &lt;&lt; &bslash;&n;&t;&t;&t;     CSR1212_TEXTUAL_DESCRIPTOR_LEAF_CHAR_SET_SHIFT))
DECL|macro|CSR1212_TEXTUAL_DESCRIPTOR_LEAF_SET_LANGUAGE
mdefine_line|#define CSR1212_TEXTUAL_DESCRIPTOR_LEAF_SET_LANGUAGE(kv, language) &bslash;&n;&t;((kv)-&gt;value.leaf.data[1] = &bslash;&n;&t; ((kv)-&gt;value.leaf.data[1] &amp; &bslash;&n;&t;  CSR1212_CPU_TO_BE32(~(CSR1212_TEXTUAL_DESCRIPTOR_LEAF_LANGUAGE_MASK))) | &bslash;&n;&t; CSR1212_CPU_TO_BE32(((language) &amp; &bslash;&n;&t;&t;&t;      CSR1212_TEXTUAL_DESCRIPTOR_LEAF_LANGUAGE_MASK)))
multiline_comment|/* Icon Descriptor Leaf manipulation macros */
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_VERSION_MASK
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_VERSION_MASK 0xffffff
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE_DEPTH_SHIFT
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE_DEPTH_SHIFT 30
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE_DEPTH_MASK
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE_DEPTH_MASK 0x3 /* after shift */
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE_SHIFT
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE_SHIFT 16
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE_MASK
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE_MASK 0xf /* after shift */
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_LANGUAGE_MASK
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_LANGUAGE_MASK 0xffff
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_HSCAN_SHIFT
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_HSCAN_SHIFT 16
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_HSCAN_MASK
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_HSCAN_MASK 0xffff /* after shift */
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_VSCAN_MASK
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_VSCAN_MASK 0xffff
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_OVERHEAD
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_OVERHEAD (3 * sizeof(u_int32_t))
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_VERSION
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_VERSION(kv) &bslash;&n;&t;(CSR1212_BE32_TO_CPU((kv)-&gt;value.leaf.data[2]) &amp; &bslash;&n;&t; CSR1212_ICON_DESCRIPTOR_LEAF_VERSION_MASK)
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE_DEPTH
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE_DEPTH(kv) &bslash;&n;&t;(CSR1212_BE32_TO_CPU((kv)-&gt;value.leaf.data[3]) &gt;&gt; &bslash;&n;&t; CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE_DEPTH_SHIFT)
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE(kv) &bslash;&n;&t;((CSR1212_BE32_TO_CPU((kv)-&gt;value.leaf.data[3]) &gt;&gt; &bslash;&n;&t;  CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE_SHIFT) &amp; &bslash;&n;&t; CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE_MASK)
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_LANGUAGE
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_LANGUAGE(kv) &bslash;&n;&t;(CSR1212_BE32_TO_CPU((kv)-&gt;value.leaf.data[3]) &amp; &bslash;&n;&t; CSR1212_ICON_DESCRIPTOR_LEAF_LANGUAGE_MASK)
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_HSCAN
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_HSCAN(kv) &bslash;&n;&t;((CSR1212_BE32_TO_CPU((kv)-&gt;value.leaf.data[4]) &gt;&gt; &bslash;&n;&t;  CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_HSCAN_SHIFT) &amp; &bslash;&n;&t; CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_HSCAN_MASK)
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_VSCAN
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_VSCAN(kv) &bslash;&n;&t;(CSR1212_BE32_TO_CPU((kv)-&gt;value.leaf.data[4]) &amp; &bslash;&n;&t; CSR1212_ICON_DESCRIPTOR_LEAF_VSCAN_MASK)
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE(kv) &bslash;&n;&t;(&amp;((kv)-&gt;value.leaf.data[5]))
DECL|function|CSR1212_ICON_DESCRIPTOR_LEAF_PIXELS
r_static
r_inline
id|u_int32_t
op_star
id|CSR1212_ICON_DESCRIPTOR_LEAF_PIXELS
c_func
(paren
r_struct
id|csr1212_keyval
op_star
id|kv
)paren
(brace
r_static
r_const
r_int
id|pd
(braket
l_int|4
)braket
op_assign
(brace
l_int|0
comma
l_int|4
comma
l_int|16
comma
l_int|256
)brace
suffix:semicolon
r_static
r_const
r_int
id|cs
(braket
l_int|16
)braket
op_assign
(brace
l_int|4
comma
l_int|2
)brace
suffix:semicolon
r_int
id|ps
op_assign
id|pd
(braket
id|CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE_DEPTH
c_func
(paren
id|kv
)paren
)braket
suffix:semicolon
r_return
op_amp
id|kv-&gt;value.leaf.data
(braket
l_int|5
op_plus
(paren
id|ps
op_star
id|cs
(braket
id|CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE
c_func
(paren
id|kv
)paren
)braket
)paren
op_div
r_sizeof
(paren
id|u_int32_t
)paren
)braket
suffix:semicolon
)brace
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_SET_VERSION
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_SET_VERSION(kv, version) &bslash;&n;&t;((kv)-&gt;value.leaf.data[2] = &bslash;&n;&t; ((kv)-&gt;value.leaf.data[2] &amp; &bslash;&n;&t;  CSR1212_CPU_TO_BE32(~(CSR1212_ICON_DESCRIPTOR_LEAF_VERSION_MASK))) | &bslash;&n;&t; CSR1212_CPU_TO_BE32(((version) &amp; &bslash;&n;&t;&t;&t;      CSR1212_ICON_DESCRIPTOR_LEAF_VERSION_MASK)))
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_SET_PALETTE_DEPTH
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_SET_PALETTE_DEPTH(kv, palette_depth) &bslash;&n;&t;((kv)-&gt;value.leaf.data[3] = &bslash;&n;&t; ((kv)-&gt;value.leaf.data[3] &amp; &bslash;&n;&t;  CSR1212_CPU_TO_BE32(~(CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE_DEPTH_MASK &lt;&lt; &bslash;&n;&t;&t;&t;&t;CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE_DEPTH_SHIFT))) | &bslash;&n;&t; CSR1212_CPU_TO_BE32(((palette_depth) &amp; &bslash;&n;&t;&t;&t;      CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE_DEPTH_MASK) &lt;&lt; &bslash;&n;&t;&t;&t;     CSR1212_ICON_DESCRIPTOR_LEAF_PALETTE_DEPTH_SHIFT))
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_SET_COLOR_SPACE
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_SET_COLOR_SPACE(kv, color_space) &bslash;&n;&t;((kv)-&gt;value.leaf.data[3] = &bslash;&n;&t; ((kv)-&gt;value.leaf.data[3] &amp; &bslash;&n;&t;  CSR1212_CPU_TO_BE32(~(CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE_MASK &lt;&lt; &bslash;&n;&t;&t;&t;&t;CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE_SHIFT))) | &bslash;&n;&t; CSR1212_CPU_TO_BE32(((color_space) &amp; &bslash;&n;&t;&t;&t;      CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE_MASK) &lt;&lt; &bslash;&n;&t;&t;&t;     CSR1212_ICON_DESCRIPTOR_LEAF_COLOR_SPACE_SHIFT))
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_SET_LANGUAGE
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_SET_LANGUAGE(kv, language) &bslash;&n;&t;((kv)-&gt;value.leaf.data[3] = &bslash;&n;&t; ((kv)-&gt;value.leaf.data[3] &amp; &bslash;&n;&t;  CSR1212_CPU_TO_BE32(~(CSR1212_ICON_DESCRIPTOR_LEAF_LANGUAGE_MASK))) | &bslash;&n;&t; CSR1212_CPU_TO_BE32(((language) &amp; &bslash;&n;&t;&t;&t;      CSR1212_ICON_DESCRIPTOR_LEAF_LANGUAGE_MASK)))
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_SET_HSCAN
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_SET_HSCAN(kv, hscan) &bslash;&n;&t;((kv)-&gt;value.leaf.data[4] = &bslash;&n;&t; ((kv)-&gt;value.leaf.data[4] &amp; &bslash;&n;&t;  CSR1212_CPU_TO_BE32(~(CSR1212_ICON_DESCRIPTOR_LEAF_HSCAN_MASK &lt;&lt; &bslash;&n;&t;&t;&t;&t;CSR1212_ICON_DESCRIPTOR_LEAF_HSCAN_SHIFT))) | &bslash;&n;&t; CSR1212_CPU_TO_BE32(((hscan) &amp; &bslash;&n;&t;&t;&t;      CSR1212_ICON_DESCRIPTOR_LEAF_HSCAN_MASK) &lt;&lt; &bslash;&n;&t;&t;&t;     CSR1212_ICON_DESCRIPTOR_LEAF_HSCAN_SHIFT))
DECL|macro|CSR1212_ICON_DESCRIPTOR_LEAF_SET_VSCAN
mdefine_line|#define CSR1212_ICON_DESCRIPTOR_LEAF_SET_VSCAN(kv, vscan) &bslash;&n;&t;((kv)-&gt;value.leaf.data[4] = &bslash;&n;&t; (((kv)-&gt;value.leaf.data[4] &amp; &bslash;&n;&t;  CSR1212_CPU_TO_BE32(~CSR1212_ICON_DESCRIPTOR_LEAF_VSCAN_MASK))) | &bslash;&n;&t; CSR1212_CPU_TO_BE32(((vscan) &amp; &bslash;&n;&t;&t;&t;      CSR1212_ICON_DESCRIPTOR_LEAF_VSCAN_MASK)))
multiline_comment|/* Modifiable Descriptor Leaf manipulation macros */
DECL|macro|CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_MAX_SIZE_SHIFT
mdefine_line|#define CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_MAX_SIZE_SHIFT 16
DECL|macro|CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_MAX_SIZE_MASK
mdefine_line|#define CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_MAX_SIZE_MASK 0xffff
DECL|macro|CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_ADDR_HI_SHIFT
mdefine_line|#define CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_ADDR_HI_SHIFT 32
DECL|macro|CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_ADDR_HI_MASK
mdefine_line|#define CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_ADDR_HI_MASK 0xffff
DECL|macro|CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_ADDR_LO_MASK
mdefine_line|#define CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_ADDR_LO_MASK 0xffffffffULL
DECL|macro|CSR1212_MODIFIABLE_DESCRIPTOR_MAX_SIZE
mdefine_line|#define CSR1212_MODIFIABLE_DESCRIPTOR_MAX_SIZE(kv) &bslash;&n;&t;CSR1212_BE16_TO_CPU((kv)-&gt;value.leaf.data[0] &gt;&gt; CSR1212_MODIFIABLE_DESCRIPTOR_MAX_SIZE_SHIFT)
DECL|macro|CSR1212_MODIFIABLE_DESCRIPTOR_ADDRESS
mdefine_line|#define CSR1212_MODIFIABLE_DESCRIPTOR_ADDRESS(kv) &bslash;&n;&t;(CSR1212_BE16_TO_CPU(((u_int64_t)((kv)-&gt;value.leaf.data[0])) &lt;&lt; &bslash;&n;&t;&t;&t;     CSR1212_MODIFIABLE_DESCRIPTOR_ADDR_HI_SHIFT) | &bslash;&n;&t; CSR1212_BE32_TO_CPU((kv)-&gt;value.leaf.data[1]))
DECL|macro|CSR1212_MODIFIABLE_DESCRIPTOR_SET_MAX_SIZE
mdefine_line|#define CSR1212_MODIFIABLE_DESCRIPTOR_SET_MAX_SIZE(kv, size) &bslash;&n;&t;((kv)-&gt;value.leaf.data[0] = &bslash;&n;&t; ((kv)-&gt;value.leaf.data[0] &amp; &bslash;&n;&t;  CSR1212_CPU_TO_BE32(~(CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_MAX_SIZE_MASK &lt;&lt; &bslash;&n;&t;&t;&t;&t;CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_MAX_SIZE_SHIFT))) | &bslash;&n;&t; CSR1212_CPU_TO_BE32(((size) &amp; &bslash;&n;&t;&t;&t;      CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_MAX_SIZE_MASK) &lt;&lt; &bslash;&n;&t;&t;&t;     CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_MAX_SIZE_SHIFT))
DECL|macro|CSR1212_MODIFIABLE_DESCRIPTOR_SET_ADDRESS_HI
mdefine_line|#define CSR1212_MODIFIABLE_DESCRIPTOR_SET_ADDRESS_HI(kv, addr) &bslash;&n;&t;((kv)-&gt;value.leaf.data[0] = &bslash;&n;&t; ((kv)-&gt;value.leaf.data[0] &amp; &bslash;&n;&t;  CSR1212_CPU_TO_BE32(~(CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_ADDR_HI_MASK))) | &bslash;&n;&t;  CSR1212_CPU_TO_BE32(((addr) &amp; &bslash;&n;&t;&t;&t;       CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_ADDR_HI_MASK)))
DECL|macro|CSR1212_MODIFIABLE_DESCRIPTOR_SET_ADDRESS_LO
mdefine_line|#define CSR1212_MODIFIABLE_DESCRIPTOR_SET_ADDRESS_LO(kv, addr) &bslash;&n;&t;((kv)-&gt;value.leaf.data[1] = &bslash;&n;&t; CSR1212_CPU_TO_BE32(addr &amp; CSR1212_MODIFIABLE_DESCRIPTOR_LEAF_ADDR_LO_MASK))
multiline_comment|/* The following 2 function are for creating new Configuration ROM trees.  The&n; * first function is used for both creating local trees and parsing remote&n; * trees.  The second function adds pertinent information to local Configuration&n; * ROM trees - namely data for the bus information block. */
r_extern
r_struct
id|csr1212_csr
op_star
id|csr1212_create_csr
c_func
(paren
r_struct
id|csr1212_bus_ops
op_star
id|ops
comma
r_int
id|bus_info_size
comma
r_void
op_star
r_private
)paren
suffix:semicolon
r_extern
r_void
id|csr1212_init_local_csr
c_func
(paren
r_struct
id|csr1212_csr
op_star
id|csr
comma
r_const
id|u_int32_t
op_star
id|bus_info_data
comma
r_int
id|max_rom
)paren
suffix:semicolon
multiline_comment|/* The following function destroys a Configuration ROM tree and release all&n; * memory taken by the tree. */
r_extern
r_void
id|csr1212_destroy_csr
c_func
(paren
r_struct
id|csr1212_csr
op_star
id|csr
)paren
suffix:semicolon
multiline_comment|/* The following set of functions are fore creating new keyvals for placement in&n; * a Configuration ROM tree.  Code that creates new keyvals with these functions&n; * must release those keyvals with csr1212_release_keyval() when they are no&n; * longer needed. */
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_new_immediate
c_func
(paren
id|u_int8_t
id|key
comma
id|u_int32_t
id|value
)paren
suffix:semicolon
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_new_leaf
c_func
(paren
id|u_int8_t
id|key
comma
r_const
r_void
op_star
id|data
comma
r_int
id|data_len
)paren
suffix:semicolon
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_new_csr_offset
c_func
(paren
id|u_int8_t
id|key
comma
id|u_int32_t
id|csr_offset
)paren
suffix:semicolon
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_new_directory
c_func
(paren
id|u_int8_t
id|key
)paren
suffix:semicolon
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_new_extended_immediate
c_func
(paren
id|u_int32_t
id|spec
comma
id|u_int32_t
id|key
comma
id|u_int32_t
id|value
)paren
suffix:semicolon
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_new_extended_leaf
c_func
(paren
id|u_int32_t
id|spec
comma
id|u_int32_t
id|key
comma
r_const
r_void
op_star
id|data
comma
r_int
id|data_len
)paren
suffix:semicolon
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_new_descriptor_leaf
c_func
(paren
id|u_int8_t
id|dtype
comma
id|u_int32_t
id|specifier_id
comma
r_const
r_void
op_star
id|data
comma
r_int
id|data_len
)paren
suffix:semicolon
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_new_textual_descriptor_leaf
c_func
(paren
id|u_int8_t
id|cwidth
comma
id|u_int16_t
id|cset
comma
id|u_int16_t
id|language
comma
r_const
r_void
op_star
id|data
comma
r_int
id|data_len
)paren
suffix:semicolon
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_new_string_descriptor_leaf
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_new_icon_descriptor_leaf
c_func
(paren
id|u_int32_t
id|version
comma
id|u_int8_t
id|palette_depth
comma
id|u_int8_t
id|color_space
comma
id|u_int16_t
id|language
comma
id|u_int16_t
id|hscan
comma
id|u_int16_t
id|vscan
comma
id|u_int32_t
op_star
id|palette
comma
id|u_int32_t
op_star
id|pixels
)paren
suffix:semicolon
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_new_modifiable_descriptor_leaf
c_func
(paren
id|u_int16_t
id|max_size
comma
id|u_int64_t
id|address
)paren
suffix:semicolon
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_new_keyword_leaf
c_func
(paren
r_int
id|strc
comma
r_const
r_char
op_star
id|strv
(braket
)braket
)paren
suffix:semicolon
multiline_comment|/* The following functions manage association between keyvals.  Typically,&n; * Descriptor Leaves and Directories will be associated with another keyval and&n; * it is desirable for the Descriptor keyval to be place immediately after the&n; * keyval that it is associated with.*/
r_extern
r_int
id|csr1212_associate_keyval
c_func
(paren
r_struct
id|csr1212_keyval
op_star
id|kv
comma
r_struct
id|csr1212_keyval
op_star
id|associate
)paren
suffix:semicolon
r_extern
r_void
id|csr1212_disassociate_keyval
c_func
(paren
r_struct
id|csr1212_keyval
op_star
id|kv
)paren
suffix:semicolon
multiline_comment|/* The following functions manage the association of a keyval and directories.&n; * A keyval may be attached to more than one directory. */
r_extern
r_int
id|csr1212_attach_keyval_to_directory
c_func
(paren
r_struct
id|csr1212_keyval
op_star
id|dir
comma
r_struct
id|csr1212_keyval
op_star
id|kv
)paren
suffix:semicolon
r_extern
r_void
id|csr1212_detach_keyval_from_directory
c_func
(paren
r_struct
id|csr1212_keyval
op_star
id|dir
comma
r_struct
id|csr1212_keyval
op_star
id|kv
)paren
suffix:semicolon
multiline_comment|/* The following functions create a Configuration ROM image from the tree of&n; * keyvals provided.  csr1212_generate_csr_image() creates a complete image in&n; * the list of caches available via csr-&gt;cache_head.  The other functions are&n; * provided should there be a need to create a flat image without restrictions&n; * placed by IEEE 1212. */
r_extern
r_struct
id|csr1212_keyval
op_star
id|csr1212_generate_positions
c_func
(paren
r_struct
id|csr1212_csr_rom_cache
op_star
id|cache
comma
r_struct
id|csr1212_keyval
op_star
id|start_kv
comma
r_int
id|start_pos
)paren
suffix:semicolon
r_extern
r_int
id|csr1212_generate_layout_order
c_func
(paren
r_struct
id|csr1212_keyval
op_star
id|kv
)paren
suffix:semicolon
r_extern
r_void
id|csr1212_fill_cache
c_func
(paren
r_struct
id|csr1212_csr_rom_cache
op_star
id|cache
)paren
suffix:semicolon
r_extern
r_int
id|csr1212_generate_csr_image
c_func
(paren
r_struct
id|csr1212_csr
op_star
id|csr
)paren
suffix:semicolon
multiline_comment|/* This is a convience function for reading a block of data out of one of the&n; * caches in the csr-&gt;cache_head list. */
r_extern
r_int
id|csr1212_read
c_func
(paren
r_struct
id|csr1212_csr
op_star
id|csr
comma
id|u_int32_t
id|offset
comma
r_void
op_star
id|buffer
comma
id|u_int32_t
id|len
)paren
suffix:semicolon
multiline_comment|/* The following functions are in place for parsing Configuration ROM images.&n; * csr1212_parse_keyval() is used should there be a need to directly parse a&n; * Configuration ROM directly. */
r_extern
r_int
id|csr1212_parse_keyval
c_func
(paren
r_struct
id|csr1212_keyval
op_star
id|kv
comma
r_struct
id|csr1212_csr_rom_cache
op_star
id|cache
)paren
suffix:semicolon
r_extern
r_int
id|csr1212_parse_csr
c_func
(paren
r_struct
id|csr1212_csr
op_star
id|csr
)paren
suffix:semicolon
multiline_comment|/* These are internal functions referenced by inline functions below. */
r_extern
r_int
id|_csr1212_read_keyval
c_func
(paren
r_struct
id|csr1212_csr
op_star
id|csr
comma
r_struct
id|csr1212_keyval
op_star
id|kv
)paren
suffix:semicolon
r_extern
r_void
id|_csr1212_destroy_keyval
c_func
(paren
r_struct
id|csr1212_keyval
op_star
id|kv
)paren
suffix:semicolon
multiline_comment|/* This function allocates a new cache which may be used for either parsing or&n; * generating sub-sets of Configuration ROM images. */
DECL|function|csr1212_rom_cache_malloc
r_static
r_inline
r_struct
id|csr1212_csr_rom_cache
op_star
id|csr1212_rom_cache_malloc
c_func
(paren
id|u_int32_t
id|offset
comma
r_int
id|size
)paren
(brace
r_struct
id|csr1212_csr_rom_cache
op_star
id|cache
suffix:semicolon
id|cache
op_assign
id|CSR1212_MALLOC
c_func
(paren
r_sizeof
(paren
r_struct
id|csr1212_csr_rom_cache
)paren
op_plus
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache
)paren
r_return
l_int|NULL
suffix:semicolon
id|cache-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|cache-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|cache-&gt;filled_head
op_assign
l_int|NULL
suffix:semicolon
id|cache-&gt;filled_tail
op_assign
l_int|NULL
suffix:semicolon
id|cache-&gt;layout_head
op_assign
l_int|NULL
suffix:semicolon
id|cache-&gt;layout_tail
op_assign
l_int|NULL
suffix:semicolon
id|cache-&gt;offset
op_assign
id|offset
suffix:semicolon
id|cache-&gt;size
op_assign
id|size
suffix:semicolon
id|cache-&gt;ext_rom
op_assign
l_int|NULL
suffix:semicolon
r_return
id|cache
suffix:semicolon
)brace
multiline_comment|/* This function ensures that a keyval contains data when referencing a keyval&n; * created by parsing a Configuration ROM. */
DECL|function|csr1212_get_keyval
r_static
r_inline
r_struct
id|csr1212_keyval
op_star
id|csr1212_get_keyval
c_func
(paren
r_struct
id|csr1212_csr
op_star
id|csr
comma
r_struct
id|csr1212_keyval
op_star
id|kv
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|kv
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kv-&gt;valid
)paren
r_if
c_cond
(paren
id|_csr1212_read_keyval
c_func
(paren
id|csr
comma
id|kv
)paren
op_ne
id|CSR1212_SUCCESS
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|kv
suffix:semicolon
)brace
multiline_comment|/* This function increments the reference count for a keyval should there be a&n; * need for code to retain a keyval that has been parsed. */
DECL|function|csr1212_keep_keyval
r_static
r_inline
r_void
id|csr1212_keep_keyval
c_func
(paren
r_struct
id|csr1212_keyval
op_star
id|kv
)paren
(brace
id|kv-&gt;refcnt
op_increment
suffix:semicolon
)brace
multiline_comment|/* This function decrements a keyval&squot;s reference count and will destroy the&n; * keyval when there are no more users of the keyval.  This should be called by&n; * any code that calls csr1212_keep_keyval() or any of the keyval creation&n; * routines csr1212_new_*(). */
DECL|function|csr1212_release_keyval
r_static
r_inline
r_void
id|csr1212_release_keyval
c_func
(paren
r_struct
id|csr1212_keyval
op_star
id|kv
)paren
(brace
r_if
c_cond
(paren
id|kv-&gt;refcnt
OG
l_int|1
)paren
id|kv-&gt;refcnt
op_decrement
suffix:semicolon
r_else
id|_csr1212_destroy_keyval
c_func
(paren
id|kv
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This macro allows for looping over the keyval entries in a directory and it&n; * ensures that keyvals from remote ConfigROMs are parsed properly.&n; *&n; * _csr is a struct csr1212_csr * that points to CSR associated with dir.&n; * _kv is a struct csr1212_keyval * that&squot;ll point to the current keyval (loop index).&n; * _dir is a struct csr1212_keyval * that points to the directory to be looped.&n; * _pos is a struct csr1212_dentry * that is used internally for indexing.&n; *&n; * kv will be NULL upon exit of the loop.&n; */
DECL|macro|csr1212_for_each_dir_entry
mdefine_line|#define csr1212_for_each_dir_entry(_csr, _kv, _dir, _pos)&t;&t;&t;&bslash;&n;&t;for (csr1212_get_keyval((_csr), (_dir)),&t;&t;&t;&t;&bslash;&n;&t;     _pos = (_dir)-&gt;value.directory.dentries_head,&t;&t;&t;&bslash;&n;&t;     _kv = (_pos) ? csr1212_get_keyval((_csr), _pos-&gt;kv) : NULL;&t;&bslash;&n;&t;     (_kv) &amp;&amp; (_pos);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     (_kv-&gt;associate == NULL) ?&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     ((_pos = _pos-&gt;next), &t;&t;&t;&t;&t;&bslash;&n;&t;&t;      (_kv = (_pos) ? csr1212_get_keyval((_csr), _pos-&gt;kv) :&t;&bslash;&n;                          NULL)) :&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     (_kv = csr1212_get_keyval((_csr), _kv-&gt;associate)))
macro_line|#endif /* __CSR1212_H__ */
eof
