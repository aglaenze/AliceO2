# Copyright 2019-2020 CERN and copyright holders of ALICE O2.
# See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
# All rights not expressly granted are reserved.
#
# This software is distributed under the terms of the GNU General Public
# License v3 (GPL Version 3), copied verbatim in the file "COPYING".
#
# In applying this license CERN does not waive the privileges and immunities
# granted to it by virtue of its status as an Intergovernmental Organization
# or submit itself to any jurisdiction.

o2_add_library(ReconstructionDataFormats
               SOURCES src/TrackParametrization.cxx
                       src/TrackParametrizationWithError.cxx
                       src/TrackFwd.cxx
                       src/BaseCluster.cxx
                       src/TrackTPCITS.cxx
                       src/Vertex.cxx
                       src/PrimaryVertex.cxx
                       src/MatchInfoTOF.cxx
                       src/MatchInfoTOFReco.cxx
                       src/TrackLTIntegral.cxx
                       src/PID.cxx
                       src/DCA.cxx
                       src/V0.cxx
                       src/Cascade.cxx
                       src/GlobalTrackID.cxx
                       src/VtxTrackIndex.cxx
                       src/VtxTrackRef.cxx
                       src/TrackTPCTOF.cxx
                       src/TrackCosmics.cxx
                       src/TrackMCHMID.cxx
                       src/MatchInfoHMP.cxx
               PUBLIC_LINK_LIBRARIES O2::GPUCommon
                                     O2::GPUUtils
                                     O2::FrameworkLogger
                                     O2::DetectorsCommonDataFormats
                                     O2::CommonDataFormat)

o2_target_root_dictionary(
  ReconstructionDataFormats
  HEADERS include/ReconstructionDataFormats/Track.h
          include/ReconstructionDataFormats/TrackFwd.h
          include/ReconstructionDataFormats/BaseCluster.h
          include/ReconstructionDataFormats/TrackTPCITS.h
          include/ReconstructionDataFormats/GlobalFwdTrack.h
          include/ReconstructionDataFormats/Vertex.h
          include/ReconstructionDataFormats/PrimaryVertex.h
          include/ReconstructionDataFormats/MatchInfoTOF.h
          include/ReconstructionDataFormats/MatchInfoTOFReco.h
          include/ReconstructionDataFormats/TrackLTIntegral.h
          include/ReconstructionDataFormats/PID.h
          include/ReconstructionDataFormats/DCA.h
          include/ReconstructionDataFormats/V0.h
          include/ReconstructionDataFormats/Cascade.h
          include/ReconstructionDataFormats/GlobalTrackID.h
          include/ReconstructionDataFormats/VtxTrackIndex.h
          include/ReconstructionDataFormats/VtxTrackRef.h
          include/ReconstructionDataFormats/TrackTPCTOF.h
          include/ReconstructionDataFormats/TrackCosmics.h
          include/ReconstructionDataFormats/TrackMCHMID.h
          include/ReconstructionDataFormats/MatchInfoFwd.h
          include/ReconstructionDataFormats/BCRange.h
          include/ReconstructionDataFormats/MatchInfoHMP.h
  )

o2_add_test(Vertex
            SOURCES test/testVertex.cxx
            COMPONENT_NAME ReconstructionDataFormats
            PUBLIC_LINK_LIBRARIES O2::ReconstructionDataFormats
                                  O2::CommonDataFormat)

o2_add_test(LTOFIntegration
            SOURCES test/testLTOFIntegration.cxx
            COMPONENT_NAME ReconstructionDataFormats
            PUBLIC_LINK_LIBRARIES O2::ReconstructionDataFormats)
