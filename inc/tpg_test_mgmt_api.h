/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER
 *
 * Copyright (c) 2016, Juniper Networks, Inc. All rights reserved.
 *
 *
 * The contents of this file are subject to the terms of the BSD 3 clause
 * License (the "License"). You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at
 * https://github.com/Juniper/warp17/blob/master/LICENSE.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * File name:
 *     tpg_test_mgmt_api.h
 *
 * Description:
 *     API to be used for managing the tests (configure/monitor/start/stop).
 *
 * Author:
 *     Dumitru Ceara, Eelco Chaudron
 *
 * Initial Created:
 *     05/13/2016
 *
 * Notes:
 *
 */

/*****************************************************************************
 * Multiple include protection
 ****************************************************************************/
#ifndef _H_TPG_TEST_MGMT_API_
#define _H_TPG_TEST_MGMT_API_

/*****************************************************************************
 * Mgmt API
 ****************************************************************************/
#define __tpg_api_func __attribute__((warn_unused_result))

extern void
test_init_defaults(tpg_test_case_t *te, tpg_test_case_type_t type,
                   uint32_t eth_port,
                   uint32_t test_case_id);
/*
 * Returns:
 *  -EINVAL when arguments are wrong.
 *  -EALREADY: tests already started on port.
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_add_port_cfg(uint32_t eth_port, const tpg_port_cfg_t *cfg,
                       printer_arg_t *printer_arg);

/*
 * Returns:
 *  NULL when config doesn't exist.
 *  Pointer to the config otherwise.
 */
extern __tpg_api_func const tpg_port_cfg_t *
test_mgmt_get_port_cfg(uint32_t eth_port, printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOMEM: TPG_TEST_MAX_L3_INTF reached.
 *  -EEXIST: interface already configured.
 *  -EALREADY: tests already started on port
 *  -EINVAL: when arguments are wrong.
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_add_port_cfg_l3_intf(uint32_t eth_port,
                               const tpg_l3_intf_t *l3_intf,
                               printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EINVAL when arguments are wrong.
 *  -EALREADY: tests already started on port
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_add_port_cfg_l3_gw(uint32_t eth_port, tpg_ip_t *gw,
                             printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOMEM: testcase id >= TPG_TEST_MAX_ENTRIES
 *  -EEXIST: trying to configure an existing testcase id
 *  -EALREADY: tests already started on port
 *  -EINVAL when arguments are wrong.
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_add_test_case(uint32_t eth_port, const tpg_test_case_t *cfg,
                        printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: test case id is not configured.
 *  -EALREADY: tests already started on port.
 *  -EINVAL when arguments are wrong.
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_del_test_case(uint32_t eth_port, uint32_t test_case_id,
                        printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: test_case_id not found.
 *  -EALREADY: tests already started on port
 *  -EINVAL when arguments are wrong.
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_update_test_case(uint32_t eth_port, uint32_t test_case_id,
                           const tpg_update_arg_t *update_arg,
                           printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: test_case_id not found.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_test_case_cfg(uint32_t eth_port, uint32_t test_case_id,
                            tpg_test_case_t *out,
                            printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: test_case_id not found.
 *  -EALREADY: tests already started on port.
 *  -EINVAL: when arguments are wrong.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_test_case_app_cfg(uint32_t eth_port, uint32_t test_case_id,
                                tpg_app_t *out,
                                printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: test_case_id not found.
 *  -EALREADY: tests already started on port
 *  -EINVAL when arguments are wrong.
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_update_test_case_app(uint32_t eth_port, uint32_t test_case_id,
                               const tpg_app_t *app_cfg,
                               printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOMEM: imix id >= TPG_IMIX_MAX_GROUPS
 *  -EEXIST: trying to configure an existing imix id
 *  -EINVAL when arguments are wrong.
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_add_imix_group(uint32_t imix_id, const tpg_imix_group_t *imix_group,
                         printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: imix id is not configured.
 *  -EBUSY: imix group used in a test case.
 *  -EINVAL when arguments are wrong.
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_del_imix_group(uint32_t imix_id, printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: imix id not found.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_imix_group(uint32_t imix_id, tpg_imix_group_t *out,
                         printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: imix id not found.
 *  -EINVAL when arguments are wrong.
 *  0 on success
 */
extern int test_mgmt_get_imix_stats(uint32_t imix_id, tpg_imix_app_stats_t *out,
                                    printer_arg_t *printer_arg);
/*
 * Returns:
 *  Number of configured testcases on the given port.
 */
extern uint32_t
test_mgmt_get_test_case_count(uint32_t eth_port);

/*
 * Returns:
 *  -ENOENT: test_case_id not found.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_test_case_state(uint32_t eth_port, uint32_t test_case_id,
                              test_env_oper_state_t *out,
                              printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EALREADY: tests already started on port.
 *  -EINVAL: when arguments are wrong.
 *  -E*: when internal errors occur
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_set_port_options(uint32_t eth_port, tpg_port_options_t *options,
                           printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: test_case_id not found.
 *  -EINVAL: invalid arguments or wrong test case type.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_port_options(uint32_t eth_port, tpg_port_options_t *out,
                           printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EALREADY: tests already started on port.
 *  -ENOENT: no such test case exists.
 *  -EINVAL: when arguments are wrong.
 *  -E*: when internal errors occur
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_set_tcp_sockopt(uint32_t eth_port, uint32_t test_case_id,
                          const tpg_tcp_sockopt_t *options,
                          printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: test_case_id not found.
 *  -EINVAL: invalid arguments or wrong test case type.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_ipv4_sockopt(uint32_t eth_port, uint32_t test_case_id,
                           tpg_ipv4_sockopt_t *out,
                           printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EALREADY: tests already started on port.
 *  -ENOENT: no such test case exists.
 *  -EINVAL: when arguments are wrong.
 *  -E*: when internal errors occur
 *  0 on success.
 */
 extern __tpg_api_func int
 test_mgmt_set_ipv4_sockopt(uint32_t eth_port, uint32_t test_case_id,
                            const tpg_ipv4_sockopt_t *options,
                            printer_arg_t *printer_arg);

 /*
  * Returns:
  *  -ENOENT: test_case_id not found.
  *  -EINVAL: invalid arguments or wrong test case type.
  *  0 on success
  */
 extern __tpg_api_func int
 test_mgmt_get_tcp_sockopt(uint32_t eth_port, uint32_t test_case_id,
                           tpg_tcp_sockopt_t *out,
                           printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EALREADY: tests already started on port.
 *  -EINVAL: when arguments are wrong.
 *  -E*: when internal errors occur
 *  0 on success.
 */
 extern __tpg_api_func int
 test_mgmt_set_vlan_sockopt(uint32_t eth_port, uint32_t test_case_id,
                            const tpg_vlan_sockopt_t *options,
                            printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: test_case_id not found.
 *  -EINVAL: invalid arguments or wrong test case type.
 *  0 on success
 */
 extern __tpg_api_func int
 test_mgmt_get_vlan_sockopt(uint32_t eth_port, uint32_t test_case_id,
                            tpg_vlan_sockopt_t *out,
                            printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EALREADY: tests already started on port.
 *  -ENOENT: no tests configured on port.
 *  -EINVAL: when arguments are wrong.
 *  -E*: when internal errors occur
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_start_port(uint32_t eth_port, printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: no tests running on port.
 *  -EINVAL when arguments are wrong.
 *  -E*: when internal errors occur
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_stop_port(uint32_t eth_port, printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: test_case_id not found.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_test_case_stats(uint32_t eth_port, uint32_t test_case_id,
                              tpg_gen_stats_t *out,
                              printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: test_case_id not found.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_test_case_rate_stats(uint32_t eth_port, uint32_t test_case_id,
                                   tpg_rate_stats_t *out,
                                   printer_arg_t *printer_arg);

/*
 * Returns:
 *  -ENOENT: test_case_id not found.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_test_case_app_stats(uint32_t eth_port, uint32_t test_case_id,
                                  tpg_app_stats_t *out,
                                  printer_arg_t *printer_arg);

/*
* Returns:
*  -EINVAL: port not valid.
*  0 on success
*/
extern __tpg_api_func int
test_mgmt_get_port_stats(uint32_t eth_port, tpg_port_statistics_t *total_stats,
                         printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EINVAL: port not valid.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_phy_stats(uint32_t eth_port, tpg_phy_statistics_t *total_stats,
                        printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EINVAL: port not valid.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_phy_rate_stats(uint32_t eth_port, tpg_phy_statistics_t *rate_stats,
                             printer_arg_t *printer_arg);


/*
 * Returns:
 *  -EINVAL: port not valid.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_eth_stats(uint32_t eth_port,
                        tpg_eth_statistics_t *total_stats,
                        printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EINVAL: port not valid.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_arp_stats(uint32_t eth_port,
                        tpg_arp_statistics_t *total_stats,
                        printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EINVAL: port not valid.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_route_stats(uint32_t eth_port,
                          tpg_route_statistics_t *total_stats,
                          printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EINVAL: port not valid.
 *  0 on success
 */
extern int
test_mgmt_get_ipv4_stats(uint32_t eth_port,
                         tpg_ipv4_statistics_t *total_ipv4_stats,
                         printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EINVAL: port not valid.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_udp_stats(uint32_t eth_port,
                        tpg_udp_statistics_t *total_udp_stats,
                        printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EINVAL: port not valid.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_tcp_stats(uint32_t eth_port,
                        tpg_tcp_statistics_t *total_tcp_stats,
                        printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EINVAL: port not valid.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_tsm_stats(uint32_t eth_port, tpg_tsm_statistics_t *total_stats,
                        printer_arg_t *printer_arg);

/*
 * Always returns SUCCESS:
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_msg_stats(tpg_msg_statistics_t *total_stats,
                        printer_arg_t *printer_arg);

/*
 * Returns:
 *  -EINVAL: port not valid.
 *  0 on success
 */
extern __tpg_api_func int
test_mgmt_get_timer_stats(uint32_t eth_port,
                          tpg_timer_statistics_t *total_stats,
                          printer_arg_t *printer_arg);
/*
 * Returns:
 *  -EINVAL: when arguments are wrong.
 *  0 on success.
 */
extern __tpg_api_func int
test_mgmt_clear_statistics(uint32_t eth_port, printer_arg_t *printer_arg);

/*
 * Returns:
 *  true if rx timestamping is enabled for this test case + sockopt combination
 *  false otherwise
 */
extern bool test_mgmt_rx_tstamp_enabled(const tpg_test_case_t *entry);

/*
 * Returns:
 *  true if tx timestamping is enabled for this test case + sockopt combination
 *  false otherwise
 */
extern bool test_mgmt_tx_tstamp_enabled(const tpg_test_case_t *entry);

#endif /* _H_TPG_TEST_MGMT_API */

