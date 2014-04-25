#ifndef MDPP_PROCESSOR_H
#define MDPP_PROCESSOR_H

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010 - 2012, David Morse (morse012@umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/ParamComposite.h>        // base class
#include <util/boundary/Boundary.h>           // member 
#include <util/containers/DSArray.h>          // member (template)
#include <util/containers/ArrayIterator.h>    // inline function
#include <mdPp/chemistry/Atom.h>              // member (template argument)
#include <mdPp/chemistry/Group.h>             // member (template argument)
#include <mdPp/configIos/ConfigIoFactory.h>   // member 
#include <mdPp/analyzers/AnalyzerManager.h>   // member 

namespace MdPp 
{

   class ConfigIo;

   using namespace Util;

   /**
   * A post-processor for analyzing outputs of MD simulations.
   */
   class Processor : public ParamComposite 
   {

   public:

      typedef ArrayIterator<Atom> AtomIterator;
      typedef ArrayIterator<Group <2> > BondIterator;

      /**
      * Constructor
      */
      Processor();

      /**
      * Destructor
      */
      ~Processor();

      using ParamComposite::readParam;

      /**
      * Read parameters and analyze.
      */
      void readParameters(std::istream& in);

      /**
      * Read a single configuration file.
      */
      void readConfig(std::ifstream& in)
      {  configIoPtr_->readConfig(in); }

      /**
      * Read a single configuration file.
      */
      void writeConfig(std::ofstream& out)
      {  configIoPtr_->writeConfig(out); }

      /**
      * Analyze a sequence of dump files.
      */
      void analyzeDumps(std::string& filename);

      /**
      * Analyze a trajectory file.
      */
      void analyzeTrajectory(std::string& filename);

      // Mutators for use in ConfigIo classes.

      /**
      * Return pointer to location for new atom.
      *
      * \param  global id for new atom
      * \return pointer to location of new atom
      */
      Atom* newAtomPtr();

      /**
      * Finalize addition of atom (allows lookup by id).
      */
      void addAtom();

      /**
      * Add bond to list of those read from file.
      *
      * \return pointer to location of new atom
      */
      Group<2>* newBondPtr();

      // etc. for angles and dihedrals
  
      // Accessors, for use in Analyzer and ConfigIo classes.

      /**
      * Get the Boundary by non-const reference
      */
      Boundary& boundary();

      /**
      * Get number of atoms.
      */ 
      int nAtom() const;

      /**
      * Get an atom reference by global id.
      */
      Atom* atomPtr(int id);

      /**
      * Initialize an iterator for atoms.
      */
      void initAtomIterator(AtomIterator& iter);

      /**
      * Get number of bonds.
      */ 
      int nBond() const;

      /**
      * Initialize a bond iterator.
      */
      void initBondIterator(BondIterator& iter);

   private:
     
      /// Array of atom objects, added in order read from file.
      DSArray<Atom> atoms_;

      /// Array of bond objects, added in order read from file.
      DSArray< Group<2> > bonds_;

      /// Pointers to atoms indexed by ids. Missing atoms are null pointers.
      DArray<Atom*> atomPtrs_;

      /// Boundary object defines periodic boundary conditions.
      Boundary boundary_;

      /// Pointer to current ConfigIo object.
      ConfigIo* configIoPtr_;

      /// Factory for generating ConfigIo at run time.
      ConfigIoFactory configIoFactory_;

      /// Manager for analyzers
      AnalyzerManager analyzerManager_;

      /// Pointer to new atom.
      Atom* newAtomPtr_;

      /// Maximum allowed atom id + 1 (used to allocate arrays).
      int atomCapacity_;

      /// Maximum allowed bond id + 1 (used to allocate arrays).
      int bondCapacity_;

      /// etc. for angles and dihedrals

      /// String identifier for ConfigIo class name
      std::string configIoName_;

      /// Name of configuration or trajectory input file
      std::string configFileName_;

   };

   // inline functions

   /*
   * Return the Boundary by reference.
   */
   inline Boundary& Processor::boundary() 
   {  return boundary_; }

   /*
   * Return number of atoms.
   */
   inline int Processor::nAtom() const
   {  return atoms_.size(); }

   /*
   * Return a pointer to an atom with a specific id.
   */
   inline Atom* Processor::atomPtr(int id)
   {  return atomPtrs_[id]; }

   /*
   * Return number of bonds.
   */
   inline int Processor::nBond() const
   {  return bonds_.size(); }
   
   /*
   * Initialize an iterator for atoms.
   */
   inline 
   void Processor::initAtomIterator(Processor::AtomIterator& iter)
   {  atoms_.begin(iter); }

   /*
   * Initialize an iterator for bonds.
   */
   inline 
   void Processor::initBondIterator(Processor::BondIterator& iter)
   {  bonds_.begin(iter); }

}
#endif
