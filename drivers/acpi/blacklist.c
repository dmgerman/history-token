multiline_comment|/*&n; *  blacklist.c&n; *&n; *  Check to see if the given machine has a known bad ACPI BIOS&n; *&n; *  Copyright (C) 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &quot;acpi_bus.h&quot;
DECL|enum|acpi_blacklist_predicates
r_enum
id|acpi_blacklist_predicates
(brace
DECL|enumerator|all_versions
id|all_versions
comma
DECL|enumerator|less_than_or_equal
id|less_than_or_equal
comma
DECL|enumerator|equal
id|equal
comma
DECL|enumerator|greater_than_or_equal
id|greater_than_or_equal
comma
)brace
suffix:semicolon
DECL|struct|acpi_blacklist_item
r_struct
id|acpi_blacklist_item
(brace
DECL|member|oem_id
r_char
id|oem_id
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|oem_table_id
r_char
id|oem_table_id
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|oem_revision
id|u32
id|oem_revision
suffix:semicolon
DECL|member|table
id|acpi_table_type
id|table
suffix:semicolon
DECL|member|oem_revision_predicate
r_enum
id|acpi_blacklist_predicates
id|oem_revision_predicate
suffix:semicolon
DECL|member|reason
r_char
op_star
id|reason
suffix:semicolon
DECL|member|is_critical_error
id|u32
id|is_critical_error
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * POLICY: If *anything* doesn&squot;t work, put it on the blacklist.&n; *&t;   If they are critical errors, mark it critical, and abort driver load.&n; */
DECL|variable|__initdata
r_static
r_struct
id|acpi_blacklist_item
id|acpi_blacklist
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* Portege 7020, BIOS 8.10 */
(brace
l_string|&quot;TOSHIB&quot;
comma
l_string|&quot;7020CT  &quot;
comma
l_int|0x19991112
comma
id|ACPI_DSDT
comma
id|all_versions
comma
l_string|&quot;Implicit Return&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Portege 4030 */
(brace
l_string|&quot;TOSHIB&quot;
comma
l_string|&quot;4030    &quot;
comma
l_int|0x19991112
comma
id|ACPI_DSDT
comma
id|all_versions
comma
l_string|&quot;Implicit Return&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Portege 310/320, BIOS 7.1 */
(brace
l_string|&quot;TOSHIB&quot;
comma
l_string|&quot;310     &quot;
comma
l_int|0x19990511
comma
id|ACPI_DSDT
comma
id|all_versions
comma
l_string|&quot;Implicit Return&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Seattle 2, old bios rev. */
(brace
l_string|&quot;INTEL &quot;
comma
l_string|&quot;440BX   &quot;
comma
l_int|0x00001000
comma
id|ACPI_DSDT
comma
id|less_than_or_equal
comma
l_string|&quot;Field beyond end of region&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* ASUS K7M */
(brace
l_string|&quot;ASUS  &quot;
comma
l_string|&quot;K7M     &quot;
comma
l_int|0x00001000
comma
id|ACPI_DSDT
comma
id|less_than_or_equal
comma
l_string|&quot;Field beyond end of region&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Intel 810 Motherboard? */
(brace
l_string|&quot;MNTRAL&quot;
comma
l_string|&quot;MO81010A&quot;
comma
l_int|0x00000012
comma
id|ACPI_DSDT
comma
id|less_than_or_equal
comma
l_string|&quot;Field beyond end of region&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Compaq Presario 711FR */
(brace
l_string|&quot;COMAPQ&quot;
comma
l_string|&quot;EAGLES&quot;
comma
l_int|0x06040000
comma
id|ACPI_DSDT
comma
id|less_than_or_equal
comma
l_string|&quot;SCI issues (C2 disabled)&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Compaq Presario 1700 */
(brace
l_string|&quot;PTLTD &quot;
comma
l_string|&quot;  DSDT  &quot;
comma
l_int|0x06040000
comma
id|ACPI_DSDT
comma
id|less_than_or_equal
comma
l_string|&quot;Multiple problems&quot;
comma
l_int|1
)brace
comma
multiline_comment|/* Sony FX120, FX140, FX150? */
(brace
l_string|&quot;SONY  &quot;
comma
l_string|&quot;U0      &quot;
comma
l_int|0x20010313
comma
id|ACPI_DSDT
comma
id|less_than_or_equal
comma
l_string|&quot;ACPI driver problem&quot;
comma
l_int|1
)brace
comma
multiline_comment|/* Compaq Presario 800, Insyde BIOS */
(brace
l_string|&quot;INT440&quot;
comma
l_string|&quot;SYSFexxx&quot;
comma
l_int|0x00001001
comma
id|ACPI_DSDT
comma
id|less_than_or_equal
comma
l_string|&quot;Does not use _REG to protect EC OpRegions&quot;
comma
l_int|1
)brace
comma
multiline_comment|/* IBM 600E - _ADR should return 7, but it returns 1 */
(brace
l_string|&quot;IBM   &quot;
comma
l_string|&quot;TP600E  &quot;
comma
l_int|0x00000105
comma
id|ACPI_DSDT
comma
id|less_than_or_equal
comma
l_string|&quot;Incorrect _ADR&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;VIA694&quot;
comma
l_string|&quot;AWRDACPI&quot;
comma
l_int|0
comma
id|ACPI_DSDT
comma
id|all_versions
comma
l_string|&quot;Bogus table&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;ASUS&bslash;0&bslash;0&quot;
comma
l_string|&quot;P2B-S   &quot;
comma
l_int|0
comma
id|ACPI_DSDT
comma
id|all_versions
comma
l_string|&quot;Bogus PCI routing&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;COMPAQ&quot;
comma
l_string|&quot;DSDT&quot;
comma
l_int|0
comma
id|ACPI_DSDT
comma
id|all_versions
comma
l_string|&quot;Bogus PCI routing&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;&quot;
)brace
)brace
suffix:semicolon
r_int
id|__init
DECL|function|acpi_blacklisted
id|acpi_blacklisted
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|blacklisted
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_table_header
op_star
id|table_header
suffix:semicolon
r_while
c_loop
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_id
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|acpi_get_table_header_early
c_func
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|table
comma
op_amp
id|table_header
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_id
comma
id|table_header-&gt;oem_id
comma
l_int|6
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_table_id
comma
id|table_header-&gt;oem_table_id
comma
l_int|8
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision_predicate
op_eq
id|all_versions
)paren
op_logical_or
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision_predicate
op_eq
id|less_than_or_equal
op_logical_and
id|table_header-&gt;oem_revision
op_le
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision
)paren
op_logical_or
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision_predicate
op_eq
id|greater_than_or_equal
op_logical_and
id|table_header-&gt;oem_revision
op_ge
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision
)paren
op_logical_or
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision_predicate
op_eq
id|equal
op_logical_and
id|table_header-&gt;oem_revision
op_eq
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Vendor &bslash;&quot;%6.6s&bslash;&quot; System &bslash;&quot;%8.8s&bslash;&quot; &quot;
l_string|&quot;Revision 0x%x has a known ACPI BIOS problem.&bslash;n&quot;
comma
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_id
comma
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_table_id
comma
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Reason: %s. This is a %s error&bslash;n&quot;
comma
id|acpi_blacklist
(braket
id|i
)braket
dot
id|reason
comma
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|is_critical_error
ques
c_cond
l_string|&quot;non-recoverable&quot;
suffix:colon
l_string|&quot;recoverable&quot;
)paren
)paren
suffix:semicolon
id|blacklisted
op_assign
id|acpi_blacklist
(braket
id|i
)braket
dot
id|is_critical_error
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
id|i
op_increment
suffix:semicolon
)brace
)brace
r_return
id|blacklisted
suffix:semicolon
)brace
eof