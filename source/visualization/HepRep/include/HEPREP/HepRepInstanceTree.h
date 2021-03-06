// -*- C++ -*-
// AID-GENERATED
// =========================================================================
// This class was generated by AID - Abstract Interface Definition          
// DO NOT MODIFY, but use the org.freehep.aid.Aid utility to regenerate it. 
// =========================================================================
#ifndef HEPREP_HEPREPINSTANCETREE_H
#define HEPREP_HEPREPINSTANCETREE_H 1

// Copyright 2000-2005, FreeHEP.

#include <vector>

#include "HEPREP/HepRepTreeID.h"

namespace HEPREP {

class HepRepInstance;
class HepRepSelectFilter;
class HepRepTreeID;
class HepRepTypeTree;

/**
 * HepRepInstanceTree interface.
 *
 * @author Mark Donszelmann
 */
class HepRepInstanceTree : virtual public HepRepTreeID {

public: 
    /// Destructor.
    virtual ~HepRepInstanceTree() { /* nop */; }

    /**
     * Overlays the instance tree on the current tree.
     *
     * The list of instances of the instanceTree has to be the same as the current tree.
     */
    virtual void overlay(HepRepInstanceTree * instanceTree) = 0;

    /**
     * Adds an instance to this instancetree.
     *
     * @param instance to be added.
     */
    virtual void addInstance(HepRepInstance * instance) = 0;

    /**
     * Removes an instance from this instancetree.
     *
     * @param instance to be removed.
     */
    virtual void removeInstance(HepRepInstance * instance) = 0;

    /**
     * Returns a collection of instances.
     *
     * @return collection of HepRepInstances.
     */
    virtual std::vector<HepRepInstance *>  getInstances() = 0;

    /**
     * Adds a related instance tree to this instancetree.
     *
     * @param instanceTree related instancetree.
     */
    virtual void addInstanceTree(HepRepTreeID * instanceTree) = 0;

    /**
     * Returns a collection of associated instance trees.
     *
     * @return collection of HepRepTreeIDs.
     */
    virtual std::vector<HepRepTreeID *>  getInstanceTreeList() = 0;

    /**
     * Returns the associated typetree.
     *
     * @return TreeID of the associated typetree.
     */
    virtual HepRepTreeID * getTypeTree() = 0;

    /**
     * Returns a deep copy of this instancetree.
     *
     * @param filter to filter the instances.
     * @return copy of this instancetree.
     */
    virtual HepRepInstanceTree * copy(HepRepTypeTree * typeTree, HepRepSelectFilter * filter = NULL) = 0;
}; // class
} // namespace HEPREP
#endif /* ifndef HEPREP_HEPREPINSTANCETREE_H */
