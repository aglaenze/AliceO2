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

/// \file ClusterTopology.cxx
/// \brief Implementation of the ClusterTopology class.
///
/// \author Luca Barioglio, University and INFN of Torino

#include "DataFormatsITSMFT/ClusterTopology.h"
#include "Framework/Logger.h"
#include <iostream>
#include <TMath.h>

ClassImp(o2::itsmft::ClusterTopology);

namespace o2
{
namespace itsmft
{
ClusterTopology::ClusterTopology() : mPattern{}, mHash{0} {}

ClusterTopology::ClusterTopology(int nRow, int nCol, const unsigned char patt[ClusterPattern::MaxPatternBytes]) : mHash{0}
{
  setPattern(nRow, nCol, patt);
}

ClusterTopology::ClusterTopology(const ClusterPattern& patt)
{
  setPattern(patt);
}

void ClusterTopology::setPattern(int nRow, int nCol, const unsigned char patt[ClusterPattern::MaxPatternBytes])
{
  mPattern.setPattern(nRow, nCol, patt);
  mHash = getCompleteHash(*this);
}

void ClusterTopology::setPattern(const ClusterPattern& patt)
{
  mPattern = patt;
  mHash = getCompleteHash(*this);
}

unsigned int ClusterTopology::hashFunction(const void* key, int len)
{
  //
  // Developed from https://github.com/rurban/smhasher , function MurMur2
  //
  // 'm' and 'r' are mixing constants generated offline.
  const unsigned int m = 0x5bd1e995;
  const int r = 24;
  // Initialize the hash
  unsigned int h = len ^ 0xdeadbeef;
  // Mix 4 bytes at a time into the hash
  const unsigned char* data = (const unsigned char*)key;
  // int recIndex=0;
  while (len >= 4) {
    unsigned int k = *(unsigned int*)data;
    k *= m;
    k ^= k >> r;
    k *= m;
    h *= m;
    h ^= k;
    data += 4;
    len -= 4;
  }
  // Handle the last few bytes of the input array
  switch (len) {
    case 3:
      h ^= data[2] << 16;
      break;
    case 2:
      h ^= data[1] << 8;
      break;
    case 1:
      h ^= data[0];
      h *= m;
      break;
  };
  // Do a few final mixes of the hash to ensure the last few
  // bytes are well-incorporated.
  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;
  return h;
}

unsigned long ClusterTopology::getCompleteHash(int nRow, int nCol,
                                               const unsigned char patt[ClusterPattern::MaxPatternBytes])
{
  unsigned char extended_pattern[ClusterPattern::kExtendedPatternBytes] = {0};
  extended_pattern[0] = (unsigned char)nRow;
  extended_pattern[1] = (unsigned char)nCol;
  int nBits = nRow * nCol;
  int nBytes = nBits / 8;
  if (nBits % 8 != 0) {
    nBytes++;
  }
  memcpy(&extended_pattern[2], patt, nBytes);

  unsigned long partialHash = (unsigned long)hashFunction(extended_pattern, nBytes);
  // The first four bytes are directly taken from partialHash
  unsigned long completeHash = partialHash << 32;
  // The last four bytes of the hash are the first 32 pixels of the topology.
  // The bits reserved for the pattern that are not used are set to 0.
  if (nBytes == 1) {
    completeHash += ((((unsigned long)extended_pattern[2]) << 24));
  } else if (nBytes == 2) {
    completeHash += ((((unsigned long)extended_pattern[2]) << 24) + (((unsigned long)extended_pattern[3]) << 16));
  } else if (nBytes == 3) {
    completeHash += ((((unsigned long)extended_pattern[2]) << 24) + (((unsigned long)extended_pattern[3]) << 16) +
                     (((unsigned long)extended_pattern[4]) << 8));
  } else if (nBytes >= 4) {
    completeHash += ((((unsigned long)extended_pattern[2]) << 24) + (((unsigned long)extended_pattern[3]) << 16) +
                     (((unsigned long)extended_pattern[4]) << 8) + ((unsigned long)extended_pattern[5]));
  } else {
    LOG(error) << "No fired pixels in small topology";
    throw std::runtime_error("No fired pixels in small topology");
  }
  return completeHash;
}

unsigned long ClusterTopology::getCompleteHash(const ClusterTopology& topology)
{
  const auto& patt = topology.getPattern();
  int nBytesUsed = topology.getUsedBytes();
  unsigned long partialHash = (unsigned long)hashFunction(patt.data(), nBytesUsed);
  // The first four bytes are directly taken from partialHash
  unsigned long completeHash = partialHash << 32;
  // The last four bytes of the hash are the first 32 pixels of the topology.
  // The bits reserved for the pattern that are not used are set to 0.
  if (nBytesUsed == 1) {
    completeHash += ((((unsigned long)patt[2]) << 24));
  } else if (nBytesUsed == 2) {
    completeHash += ((((unsigned long)patt[2]) << 24) + (((unsigned long)patt[3]) << 16));
  } else if (nBytesUsed == 3) {
    completeHash +=
      ((((unsigned long)patt[2]) << 24) + (((unsigned long)patt[3]) << 16) + (((unsigned long)patt[4]) << 8));
  } else if (nBytesUsed >= 4) {
    completeHash += ((((unsigned long)patt[2]) << 24) + (((unsigned long)patt[3]) << 16) +
                     (((unsigned long)patt[4]) << 8) + ((unsigned long)patt[5]));
  } else {
    LOG(error) << "No fired pixels in small topology";
    throw std::runtime_error("No fired pixels in small topology");
  }
  return completeHash;
}

void ClusterTopology::print() const
{
  std::cout << (*this) << "\n";
}

std::ostream& operator<<(std::ostream& os, const ClusterTopology& topology)
{
  os << topology.mPattern << std::endl;
  return os;
}

} // namespace itsmft
} // namespace o2
