#------------------------------------------------------------------------------
# sources.cmake
# Module : G4phys_builders
# Package: Geant4.src.G4physicslists.G4phys_builders
#
# Sources description for a library.
# Lists the sources and headers of the code explicitely.
# Lists include paths needed.
# Lists the internal granular and global dependencies of the library.
# Source specific properties should be added at the end.
#
# Generated on : 24/9/2010
#
# $Id: sources.cmake 76279 2013-11-08 12:50:46Z gcosmo $
#
#------------------------------------------------------------------------------

# List external includes needed.
include_directories(${CLHEP_INCLUDE_DIRS})
include_directories(${EXPAT_INCLUDE_DIRS})

# List internal includes needed.
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/magneticfield/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/navigation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/volumes/include)
include_directories(${CMAKE_SOURCE_DIR}/source/global/HEPGeometry/include)
include_directories(${CMAKE_SOURCE_DIR}/source/global/HEPNumerics/include)
include_directories(${CMAKE_SOURCE_DIR}/source/global/HEPRandom/include)
include_directories(${CMAKE_SOURCE_DIR}/source/global/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/intercoms/include)
include_directories(${CMAKE_SOURCE_DIR}/source/materials/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/bosons/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/hadrons/barions/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/hadrons/ions/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/hadrons/mesons/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/leptons/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/shortlived/include)
include_directories(${CMAKE_SOURCE_DIR}/source/physics_lists/constructors/factory/include)
include_directories(${CMAKE_SOURCE_DIR}/source/physics_lists/util/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/cuts/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/decay/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/dna/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/dna/molecules/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/dna/molecules/types/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/dna/models/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/dna/processes/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/dna/utils/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/highenergy/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/lowenergy/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/muons/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/standard/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/utils/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/xrays/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/cross_sections/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/binary_cascade/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/cascade/cascade/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/coherent_elastic/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/evaporation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/fermi_breakup/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/handler/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/multifragmentation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/photon_evaporation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/util/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/im_r_matrix/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/inclxx/utils/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/inclxx/incl_physics/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/inclxx/interface/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/lend/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/lepto_nuclear/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/neutron_hp/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/parton_string/diffraction/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/parton_string/hadronization/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/parton_string/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/parton_string/qgsm/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/pre_equilibrium/exciton_model/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/qmd/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/radioactive_decay/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/theo_high_energy/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/util/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/processes/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/stopping/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/util/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/util/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/optical/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/transportation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/run/include)
include_directories(${CMAKE_SOURCE_DIR}/source/track/include)

#
# Define the Geant4 Module.
#
include(Geant4MacroDefineModule)
GEANT4_DEFINE_MODULE(NAME G4phys_builders
    HEADERS
        G4AntiBarionBuilder.hh
        G4BertiniKaonBuilder.hh
        G4BertiniNeutronBuilder.hh
        G4BertiniPiKBuilder.hh
        G4BertiniPionBuilder.hh
        G4BertiniProtonBuilder.hh
        G4BinaryNeutronBuilder.hh
        G4BinaryPiKBuilder.hh
        G4BinaryPionBuilder.hh
        G4BinaryProtonBuilder.hh
        G4BuilderType.hh
        G4FTFBinaryKaonBuilder.hh
        G4FTFBinaryNeutronBuilder.hh
        G4FTFBinaryPiKBuilder.hh
        G4FTFBinaryPionBuilder.hh
        G4FTFBinaryProtonBuilder.hh
        G4FTFBuilder.hh
        G4FTFPAntiBarionBuilder.hh
        G4FTFPKaonBuilder.hh
        G4FTFPNeutronBuilder.hh
        G4FTFPPiKBuilder.hh
        G4FTFPPionBuilder.hh
        G4FTFPProtonBuilder.hh
        G4HyperonFTFPBuilder.hh
        G4INCLXXNeutronBuilder.hh
        G4INCLXXPiKBuilder.hh
        G4INCLXXProtonBuilder.hh
        G4KaonBuilder.hh
        G4NeutronBuilder.hh
        G4NeutronCrossSectionXS.hh
        G4NeutronHPBuilder.hh
        G4NeutronLENDBuilder.hh
        G4PiKBuilder.hh
        G4PionBuilder.hh
        G4PrecoNeutronBuilder.hh
        G4PrecoProtonBuilder.hh
        G4ProtonBuilder.hh
        G4QGSBinaryKaonBuilder.hh
        G4QGSBinaryNeutronBuilder.hh
        G4QGSBinaryPiKBuilder.hh
        G4QGSBinaryPionBuilder.hh
        G4QGSBinaryProtonBuilder.hh
        G4QGSBuilder.hh
        G4QGSPNeutronBuilder.hh
        G4QGSPPiKBuilder.hh
        G4QGSPPionBuilder.hh
        G4QGSPProtonBuilder.hh
        G4VAntiBarionBuilder.hh
        G4VHadronModelBuilder.hh
        G4VKaonBuilder.hh
        G4VNeutronBuilder.hh
        G4VPiKBuilder.hh
        G4VPionBuilder.hh
        G4VProtonBuilder.hh
        TheoModelFactory.hh
    SOURCES
        G4AntiBarionBuilder.cc
        G4BertiniKaonBuilder.cc
        G4BertiniNeutronBuilder.cc
        G4BertiniPiKBuilder.cc
        G4BertiniPionBuilder.cc
        G4BertiniProtonBuilder.cc
        G4BinaryNeutronBuilder.cc
        G4BinaryPiKBuilder.cc
        G4BinaryPionBuilder.cc
        G4BinaryProtonBuilder.cc
        G4FTFBinaryKaonBuilder.cc
        G4FTFBinaryNeutronBuilder.cc
        G4FTFBinaryPiKBuilder.cc
        G4FTFBinaryPionBuilder.cc
        G4FTFBinaryProtonBuilder.cc
        G4FTFBuilder.cc
        G4FTFPAntiBarionBuilder.cc
        G4FTFPKaonBuilder.cc
        G4FTFPNeutronBuilder.cc
        G4FTFPPiKBuilder.cc
        G4FTFPPionBuilder.cc
        G4FTFPProtonBuilder.cc
        G4HyperonFTFPBuilder.cc
        G4INCLXXNeutronBuilder.cc
        G4INCLXXPiKBuilder.cc
        G4INCLXXProtonBuilder.cc
        G4KaonBuilder.cc
        G4NeutronBuilder.cc
        G4NeutronCrossSectionXS.cc
        G4NeutronHPBuilder.cc
        G4NeutronLENDBuilder.cc
        G4PiKBuilder.cc
        G4PionBuilder.cc
        G4PrecoNeutronBuilder.cc
        G4PrecoProtonBuilder.cc
        G4ProtonBuilder.cc
        G4QGSBinaryKaonBuilder.cc
        G4QGSBinaryNeutronBuilder.cc
        G4QGSBinaryPiKBuilder.cc
        G4QGSBinaryPionBuilder.cc
        G4QGSBinaryProtonBuilder.cc
        G4QGSBuilder.cc
        G4QGSPNeutronBuilder.cc
        G4QGSPPiKBuilder.cc
        G4QGSPPionBuilder.cc
        G4QGSPProtonBuilder.cc
        G4VAntiBarionBuilder.cc
        G4VHadronModelBuilder.cc
        G4VKaonBuilder.cc
        G4VNeutronBuilder.cc
        G4VPiKBuilder.cc
        G4VPionBuilder.cc
        G4VProtonBuilder.cc
    GRANULAR_DEPENDENCIES
        G4baryons
        G4bosons
        G4cuts
        G4decay
        G4emdna-processes
        G4emdna-models
        G4emdna-utils
        G4emhighenergy
        G4emlowenergy
        G4emstandard
        G4emutils
        G4geometrymng
        G4globman
        G4had_im_r_matrix
        G4had_lend
        G4had_mod_man
        G4had_mod_util
        G4had_lept_nuclear
        G4had_neu_hp
        G4had_preequ_exciton
        G4had_string_diff
        G4had_string_frag
        G4had_string_man
        G4had_theo_max
        G4hadronic_HE
        G4hadronic_LE
        G4hadronic_bert_cascade
        G4hadronic_binary
        G4hadronic_coherent_elastic
        G4hadronic_deex_evaporation
        G4hadronic_deex_fermi_breakup
        G4hadronic_deex_handler
        G4hadronic_deex_management
        G4hadronic_deex_multifragmentation
        G4hadronic_deex_photon_evaporation
        G4hadronic_deex_util
        G4hadronic_inclxx_interface
        G4hadronic_inclxx_physics
        G4hadronic_inclxx_utils
        G4hadronic_mgt
        G4hadronic_proc
        G4hadronic_qgstring
        G4hadronic_qmd
        G4hadronic_radioactivedecay
        G4hadronic_stop
        G4hadronic_util
        G4hadronic_xsect
        G4hepnumerics
        G4intercoms
        G4ions
        G4leptons
        G4magneticfield
        G4materials
        G4mesons
        G4muons
        G4navigation
        G4optical
        G4partman
        G4procman
        G4run
        G4shortlived
        G4track
        G4transportation
        G4volumes
        G4xrays
    GLOBAL_DEPENDENCIES
        G4geometry
        G4global
        G4intercoms
        G4materials
        G4particles
        G4processes
        G4run
        G4track
    LINK_LIBRARIES
)

# List any source specific properties here

