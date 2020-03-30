/*
 *
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "test_harness/test_harness.hpp"

#include <level_zero/ze_api.h>
#include "utils/utils.hpp"

namespace lzt = level_zero_tests;

namespace level_zero_tests {

uint32_t get_temp_handle_count(ze_device_handle_t device) {
  uint32_t count = 0;
  zet_sysman_handle_t hSysman = lzt::get_sysman_handle(device);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zetSysmanTemperatureGet(hSysman, &count, nullptr));
  EXPECT_GT(count, 0);
  return count;
}
std::vector<zet_sysman_temp_handle_t> get_temp_handles(ze_device_handle_t device,
                                                     uint32_t &count) {
  zet_sysman_handle_t hSysman = lzt::get_sysman_handle(device);
  if (count == 0) {
    count = get_temp_handle_count(device);
  }
  std::vector<zet_sysman_temp_handle_t> tempHandles(count);
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zetSysmanTemperatureGet(hSysman, &count, tempHandles.data()));
  EXPECT_EQ(tempHandles.size(), count);
  return tempHandles;
}

zet_temp_properties_t get_temp_properties(zet_sysman_temp_handle_t tempHandle) {
  zet_temp_properties_t properties;
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zetSysmanTemperatureGetProperties(tempHandle, &properties));
  return properties;
}
double get_temp_state(zet_sysman_temp_handle_t tempHandle) {
  double temp;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zetSysmanTemperatureGetState(tempHandle, &temp));
}
zet_temp_config_t get_temp_configuration(zet_sysman_temp_handle_t tempHandle) {
  zet_temp_config_t config;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zetSysmanTemperatureGetConfig(tempHandle, &config));
  return config;
}
void set_temp_configuration(zet_sysman_temp_handle_t tempHandle,
                           zet_temp_config_t &config) {
  EXPECT_EQ(ZE_RESULT_SUCCESS, zetSysmanTemperatureSetConfig(tempHandle, &config));
}
} // namespace level_zero_tests

