#------------------------------------------------------------------------------
# CMakeLists.txt
# Module : G4phys_lists
# Package: Geant4.src.G4physicslists.G4phys_lists
#
# CMakeLists.txt for building a single granular library.
#
# Generated on : 24/9/2010
#
# $Id: CMakeLists.txt 66704 2013-01-10 18:20:17Z gunter $
#
#------------------------------------------------------------------------------

if(GEANT4_BUILD_GRANULAR_LIBS)
    include(Geant4MacroLibraryTargets)
    GEANT4_GRANULAR_LIBRARY_TARGET(COMPONENT sources.cmake)
endif()

