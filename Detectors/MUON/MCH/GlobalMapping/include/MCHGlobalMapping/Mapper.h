// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#ifndef O2_MCH_GLOBAL_MAPPING_MAPPER_H_
#define O2_MCH_GLOBAL_MAPPING_MAPPER_H_

#include <cstdint>
#include <utility>

#include "MCHRawElecMap/DsDetId.h"

namespace o2::mch
{
/** DsIndex is an integer, from 0 to 16719, which uniquely identifies
 * one pair (deId,dsId), i.e. one DualSampa, within the whole detector
 */
using DsIndex = uint16_t;

constexpr uint16_t NumberOfDualSampas = 16820;

/** getDsIndex returns the unique index of one dual sampa. */
DsIndex getDsIndex(const o2::mch::raw::DsDetId& dsDetId);

/** decodeDsIndex converts a unique dual sampa index into a pair (deId,dsId). */
o2::mch::raw::DsDetId getDsDetId(DsIndex dsIndex);

/** get the number of channels for a given dual sampa (will be 64 in most of the cases. */
uint8_t numberOfDualSampaChannels(DsIndex dsIndex);
} // namespace o2::mch

#endif
