multiline_comment|/*&n; *  linux/drivers/s390/crypto/z90crypt.h&n; *&n; *  z90crypt 1.3.2&n; *&n; *  Copyright (C)  2001, 2004 IBM Corporation&n; *  Author(s): Robert Burroughs (burrough@us.ibm.com)&n; *             Eric Rossman (edrossma@us.ibm.com)&n; *&n; *  Hotplug &amp; misc device support: Jochen Roehrig (roehrig@de.ibm.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _Z90CRYPT_H_
DECL|macro|_Z90CRYPT_H_
mdefine_line|#define _Z90CRYPT_H_
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|VERSION_Z90CRYPT_H
mdefine_line|#define VERSION_Z90CRYPT_H &quot;$Revision: 1.11 $&quot;
DECL|macro|z90crypt_VERSION
mdefine_line|#define z90crypt_VERSION 1
DECL|macro|z90crypt_RELEASE
mdefine_line|#define z90crypt_RELEASE 3&t;
singleline_comment|// 2 = PCIXCC, 3 = rewrite for coding standards
DECL|macro|z90crypt_VARIANT
mdefine_line|#define z90crypt_VARIANT 2&t;
singleline_comment|// 2 = added PCIXCC MCL3 and CEX2C support
multiline_comment|/**&n; * If we are not using the sparse checker, __user has no use.&n; */
macro_line|#ifdef __CHECKER__
DECL|macro|__user
macro_line|# define __user&t;&t;__attribute__((noderef, address_space(1)))
macro_line|#else
DECL|macro|__user
macro_line|# define __user
macro_line|#endif
multiline_comment|/**&n; * struct ica_rsa_modexpo&n; *&n; * Requirements:&n; * - outputdatalength is at least as large as inputdatalength.&n; * - All key parts are right justified in their fields, padded on&n; *   the left with zeroes.&n; * - length(b_key) = inputdatalength&n; * - length(n_modulus) = inputdatalength&n; */
DECL|struct|ica_rsa_modexpo
r_struct
id|ica_rsa_modexpo
(brace
DECL|member|inputdata
r_char
id|__user
op_star
id|inputdata
suffix:semicolon
DECL|member|inputdatalength
r_int
r_int
id|inputdatalength
suffix:semicolon
DECL|member|outputdata
r_char
id|__user
op_star
id|outputdata
suffix:semicolon
DECL|member|outputdatalength
r_int
r_int
id|outputdatalength
suffix:semicolon
DECL|member|b_key
r_char
id|__user
op_star
id|b_key
suffix:semicolon
DECL|member|n_modulus
r_char
id|__user
op_star
id|n_modulus
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct ica_rsa_modexpo_crt&n; *&n; * Requirements:&n; * - inputdatalength is even.&n; * - outputdatalength is at least as large as inputdatalength.&n; * - All key parts are right justified in their fields, padded on&n; *   the left with zeroes.&n; * - length(bp_key)&t;= inputdatalength/2 + 8&n; * - length(bq_key)&t;= inputdatalength/2&n; * - length(np_key)&t;= inputdatalength/2 + 8&n; * - length(nq_key)&t;= inputdatalength/2&n; * - length(u_mult_inv) = inputdatalength/2 + 8&n; */
DECL|struct|ica_rsa_modexpo_crt
r_struct
id|ica_rsa_modexpo_crt
(brace
DECL|member|inputdata
r_char
id|__user
op_star
id|inputdata
suffix:semicolon
DECL|member|inputdatalength
r_int
r_int
id|inputdatalength
suffix:semicolon
DECL|member|outputdata
r_char
id|__user
op_star
id|outputdata
suffix:semicolon
DECL|member|outputdatalength
r_int
r_int
id|outputdatalength
suffix:semicolon
DECL|member|bp_key
r_char
id|__user
op_star
id|bp_key
suffix:semicolon
DECL|member|bq_key
r_char
id|__user
op_star
id|bq_key
suffix:semicolon
DECL|member|np_prime
r_char
id|__user
op_star
id|np_prime
suffix:semicolon
DECL|member|nq_prime
r_char
id|__user
op_star
id|nq_prime
suffix:semicolon
DECL|member|u_mult_inv
r_char
id|__user
op_star
id|u_mult_inv
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|Z90_IOCTL_MAGIC
mdefine_line|#define Z90_IOCTL_MAGIC &squot;z&squot;  
singleline_comment|// NOTE:  Need to allocate from linux folks
multiline_comment|/**&n; * Interface notes:&n; *&n; * The ioctl()s which are implemented (along with relevant details)&n; * are:&n; *&n; *   ICARSAMODEXPO&n; *     Perform an RSA operation using a Modulus-Exponent pair&n; *     This takes an ica_rsa_modexpo struct as its arg.&n; *&n; *     NOTE: please refer to the comments preceding this structure&n; *           for the implementation details for the contents of the&n; *           block&n; *&n; *   ICARSACRT&n; *     Perform an RSA operation using a Chinese-Remainder Theorem key&n; *     This takes an ica_rsa_modexpo_crt struct as its arg.&n; *&n; *     NOTE: please refer to the comments preceding this structure&n; *           for the implementation details for the contents of the&n; *           block&n; *&n; *   Z90STAT_TOTALCOUNT&n; *     Return an integer count of all device types together.&n; *&n; *   Z90STAT_PCICACOUNT&n; *     Return an integer count of all PCICAs.&n; *&n; *   Z90STAT_PCICCCOUNT&n; *     Return an integer count of all PCICCs.&n; *&n; *   Z90STAT_PCIXCCMCL2COUNT&n; *     Return an integer count of all MCL2 PCIXCCs.&n; *&n; *   Z90STAT_PCIXCCMCL3COUNT&n; *     Return an integer count of all MCL3 PCIXCCs.&n; *&n; *   Z90STAT_CEX2CCOUNT&n; *     Return an integer count of all CEX2Cs.&n; *&n; *   Z90STAT_REQUESTQ_COUNT&n; *     Return an integer count of the number of entries waiting to be&n; *     sent to a device.&n; *&n; *   Z90STAT_PENDINGQ_COUNT&n; *     Return an integer count of the number of entries sent to a&n; *     device awaiting the reply.&n; *&n; *   Z90STAT_TOTALOPEN_COUNT&n; *     Return an integer count of the number of open file handles.&n; *&n; *   Z90STAT_DOMAIN_INDEX&n; *     Return the integer value of the Cryptographic Domain.&n; *&n; *   Z90STAT_STATUS_MASK&n; *     Return an 64 element array of unsigned chars for the status of&n; *     all devices.&n; *       0x01: PCICA&n; *       0x02: PCICC&n; *       0x03: PCIXCC_MCL2&n; *       0x04: PCIXCC_MCL3&n; *       0x05: CEX2C&n; *       0x0d: device is disabled via the proc filesystem&n; *&n; *   Z90STAT_QDEPTH_MASK&n; *     Return an 64 element array of unsigned chars for the queue&n; *     depth of all devices.&n; *&n; *   Z90STAT_PERDEV_REQCNT&n; *     Return an 64 element array of unsigned integers for the number&n; *     of successfully completed requests per device since the device&n; *     was detected and made available.&n; *&n; *   ICAZ90STATUS (deprecated)&n; *     Return some device driver status in a ica_z90_status struct&n; *     This takes an ica_z90_status struct as its arg.&n; *&n; *     NOTE: this ioctl() is deprecated, and has been replaced with&n; *           single ioctl()s for each type of status being requested&n; *&n; *   Z90STAT_PCIXCCCOUNT (deprecated)&n; *     Return an integer count of all PCIXCCs (MCL2 + MCL3).&n; *     This is DEPRECATED now that MCL3 PCIXCCs are treated differently from&n; *     MCL2 PCIXCCs.&n; *&n; *   Z90QUIESCE (not recommended)&n; *     Quiesce the driver.  This is intended to stop all new&n; *     requests from being processed.  Its use is NOT recommended,&n; *     except in circumstances where there is no other way to stop&n; *     callers from accessing the driver.  Its original use was to&n; *     allow the driver to be &quot;drained&quot; of work in preparation for&n; *     a system shutdown.&n; *&n; *     NOTE: once issued, this ban on new work cannot be undone&n; *           except by unloading and reloading the driver.&n; */
multiline_comment|/**&n; * Supported ioctl calls&n; */
DECL|macro|ICARSAMODEXPO
mdefine_line|#define ICARSAMODEXPO&t;_IOC(_IOC_READ|_IOC_WRITE, Z90_IOCTL_MAGIC, 0x05, 0)
DECL|macro|ICARSACRT
mdefine_line|#define ICARSACRT&t;_IOC(_IOC_READ|_IOC_WRITE, Z90_IOCTL_MAGIC, 0x06, 0)
multiline_comment|/* DEPRECATED status calls (bound for removal at some point) */
DECL|macro|ICAZ90STATUS
mdefine_line|#define ICAZ90STATUS&t;_IOR(Z90_IOCTL_MAGIC, 0x10, struct ica_z90_status)
DECL|macro|Z90STAT_PCIXCCCOUNT
mdefine_line|#define Z90STAT_PCIXCCCOUNT&t;_IOR(Z90_IOCTL_MAGIC, 0x43, int)
multiline_comment|/* unrelated to ICA callers */
DECL|macro|Z90QUIESCE
mdefine_line|#define Z90QUIESCE&t;_IO(Z90_IOCTL_MAGIC, 0x11)
multiline_comment|/* New status calls */
DECL|macro|Z90STAT_TOTALCOUNT
mdefine_line|#define Z90STAT_TOTALCOUNT&t;_IOR(Z90_IOCTL_MAGIC, 0x40, int)
DECL|macro|Z90STAT_PCICACOUNT
mdefine_line|#define Z90STAT_PCICACOUNT&t;_IOR(Z90_IOCTL_MAGIC, 0x41, int)
DECL|macro|Z90STAT_PCICCCOUNT
mdefine_line|#define Z90STAT_PCICCCOUNT&t;_IOR(Z90_IOCTL_MAGIC, 0x42, int)
DECL|macro|Z90STAT_PCIXCCMCL2COUNT
mdefine_line|#define Z90STAT_PCIXCCMCL2COUNT&t;_IOR(Z90_IOCTL_MAGIC, 0x4b, int)
DECL|macro|Z90STAT_PCIXCCMCL3COUNT
mdefine_line|#define Z90STAT_PCIXCCMCL3COUNT&t;_IOR(Z90_IOCTL_MAGIC, 0x4c, int)
DECL|macro|Z90STAT_CEX2CCOUNT
mdefine_line|#define Z90STAT_CEX2CCOUNT&t;_IOR(Z90_IOCTL_MAGIC, 0x4d, int)
DECL|macro|Z90STAT_REQUESTQ_COUNT
mdefine_line|#define Z90STAT_REQUESTQ_COUNT&t;_IOR(Z90_IOCTL_MAGIC, 0x44, int)
DECL|macro|Z90STAT_PENDINGQ_COUNT
mdefine_line|#define Z90STAT_PENDINGQ_COUNT&t;_IOR(Z90_IOCTL_MAGIC, 0x45, int)
DECL|macro|Z90STAT_TOTALOPEN_COUNT
mdefine_line|#define Z90STAT_TOTALOPEN_COUNT _IOR(Z90_IOCTL_MAGIC, 0x46, int)
DECL|macro|Z90STAT_DOMAIN_INDEX
mdefine_line|#define Z90STAT_DOMAIN_INDEX&t;_IOR(Z90_IOCTL_MAGIC, 0x47, int)
DECL|macro|Z90STAT_STATUS_MASK
mdefine_line|#define Z90STAT_STATUS_MASK&t;_IOR(Z90_IOCTL_MAGIC, 0x48, char[64])
DECL|macro|Z90STAT_QDEPTH_MASK
mdefine_line|#define Z90STAT_QDEPTH_MASK&t;_IOR(Z90_IOCTL_MAGIC, 0x49, char[64])
DECL|macro|Z90STAT_PERDEV_REQCNT
mdefine_line|#define Z90STAT_PERDEV_REQCNT&t;_IOR(Z90_IOCTL_MAGIC, 0x4a, int[64])
multiline_comment|/**&n; * local errno definitions&n; */
DECL|macro|ENOBUFF
mdefine_line|#define ENOBUFF&t;  129&t;
singleline_comment|// filp-&gt;private_data-&gt;...&gt;work_elem_p-&gt;buffer is NULL
DECL|macro|EWORKPEND
mdefine_line|#define EWORKPEND 130&t;
singleline_comment|// user issues ioctl while another pending
DECL|macro|ERELEASED
mdefine_line|#define ERELEASED 131&t;
singleline_comment|// user released while ioctl pending
DECL|macro|EQUIESCE
mdefine_line|#define EQUIESCE  132&t;
singleline_comment|// z90crypt quiescing (no more work allowed)
DECL|macro|ETIMEOUT
mdefine_line|#define ETIMEOUT  133&t;
singleline_comment|// request timed out
DECL|macro|EUNKNOWN
mdefine_line|#define EUNKNOWN  134&t;
singleline_comment|// some unrecognized error occured (retry may succeed)
DECL|macro|EGETBUFF
mdefine_line|#define EGETBUFF  135&t;
singleline_comment|// Error getting buffer or hardware lacks capability
singleline_comment|// (retry in software)
multiline_comment|/**&n; * DEPRECATED STRUCTURES&n; */
multiline_comment|/**&n; * This structure is DEPRECATED and the corresponding ioctl() has been&n; * replaced with individual ioctl()s for each piece of data!&n; * This structure will NOT survive past version 1.3.1, so switch to the&n; * new ioctl()s.&n; */
DECL|macro|MASK_LENGTH
mdefine_line|#define MASK_LENGTH 64 
singleline_comment|// mask length
DECL|struct|ica_z90_status
r_struct
id|ica_z90_status
(brace
DECL|member|totalcount
r_int
id|totalcount
suffix:semicolon
DECL|member|leedslitecount
r_int
id|leedslitecount
suffix:semicolon
singleline_comment|// PCICA
DECL|member|leeds2count
r_int
id|leeds2count
suffix:semicolon
singleline_comment|// PCICC
singleline_comment|// int PCIXCCCount; is not in struct for backward compatibility
DECL|member|requestqWaitCount
r_int
id|requestqWaitCount
suffix:semicolon
DECL|member|pendingqWaitCount
r_int
id|pendingqWaitCount
suffix:semicolon
DECL|member|totalOpenCount
r_int
id|totalOpenCount
suffix:semicolon
DECL|member|cryptoDomain
r_int
id|cryptoDomain
suffix:semicolon
singleline_comment|// status: 0=not there, 1=PCICA, 2=PCICC, 3=PCIXCC_MCL2, 4=PCIXCC_MCL3,
singleline_comment|//         5=CEX2C
DECL|member|status
r_int
r_char
id|status
(braket
id|MASK_LENGTH
)braket
suffix:semicolon
singleline_comment|// qdepth: # work elements waiting for each device
DECL|member|qdepth
r_int
r_char
id|qdepth
(braket
id|MASK_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _Z90CRYPT_H_ */
eof
