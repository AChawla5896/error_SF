#ifndef HARMONIC_BOND_H
#define HARMONIC_BOND_H

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include <util/global.h>
#include <util/param/ParamComposite.h>  // base class

#include <util/random/Random.h>           // Util namespace 

#include <cmath>

namespace Inter
{

   using namespace Util;

   //class Random;
   
   /**
   * A harmonic covalent bond potential.
   *
   * Implements a harmonic potential with a nonzero rest length.
   *
   * \ingroup Bond_Module
   */
   class HarmonicBond : public ParamComposite 
   {
   
   public:

      /**
      * Default constructor.
      */
      HarmonicBond();
   
      /**
      * Copy constructor.
      */
      HarmonicBond(const HarmonicBond& other);
   
      /**
      * Assignment.
      */
      HarmonicBond& operator = (const HarmonicBond& other);
  
      // Default C++ destructor.
 
      /**
      * Set the number of bond types.
      *
      * \param nBondType number of bond types
      */
      void setNBondType(int nBondType);

      /**
      * Returns bond stiffness
      */
      double stiffness(unsigned int bondType) const;

      /**
      * Returns bond length
      */
      double length(unsigned int bondType) const;

      /**
      * Read bond interaction parameters from input stream.
      *
      * Format:
      *     kappa  CArray<double>
      *     length CArray<double>
      *
      * \pre nBondType must be set, by calling setNBondType().
      *
      * \param in input stream
      */
      void readParam(std::istream &in);

      /**
      * Returns potential energy for one bond.
      *
      * \param rSq  square of distance between bonded particles.
      * \param type type of bond.
      */
      double energy(double rSq, int type) const;
   
      /**
      * Returns force/distance for one bond, for use in MD.
      *
      * A positive return value represents a repulsive radial force.
      *
      * \param rSq  square of distance between bonded particles.
      * \param type type of bond.
      * \return     scalar repulsive force divided by distance.
      */
      double forceOverR(double rSq, int type) const;

      /**
      * Return bond length chosen from equilibrium distribution.
      *
      * This function returns a bond length chosen from the Boltzmann
      * distribution of lengths for bonds of random orientation. The
      * distribution P(l) of values of the length l is proportional 
      * to l*l*exp[-beta*phi(l) ], where phi(l) is the bond energy. 
      *
      * \param random pointer to random number generator object.
      * \param beta   inverse temperature
      * \param type   bond type
      * \return random bond length chosen from equilibrium distribution.
      */
      double randomBondLength(Random *random, double beta, int type) const;
   
      /**
      * Return name string "HarmonicBond" for this evaluator class.
      */
      std::string className() const;
 
   private:
   
      /// Maximum possible number of bond types
      static const int MaxNBondType = 2;
   
      double kappa_[MaxNBondType];  ///< spring constant
      double length_[MaxNBondType]; ///< equilibrium length
      int    nBondType_;            ///< number of bond types

   };
   
   // Inline method definitions

   /*
    * Return bond stiffness
    */
   inline double HarmonicBond::stiffness(unsigned int bondType) const
   {
      assert(bondType < nBondType_);
      return kappa_[bondType];
   }

   /*
    * Return bond length
    */
   inline double HarmonicBond::length(unsigned int bondType) const
   {
      assert(bondType < nBondType_);
      return length_[bondType];
   }

   /* 
   * Return interaction energy for one bond
   */
   inline double HarmonicBond::energy(double rSq, int type) const
   {
      double dl = sqrt(rSq) - length_[type];
      return 0.5*kappa_[type]*dl*dl;
   }

   /* 
   * Return force / distance for one bond, for use in MD
   */
   inline 
   double HarmonicBond::forceOverR(double rSq, int type) const
   {
      double r  = sqrt(rSq);
      double dl = length_[type] - r;
      return kappa_[type]*dl/r;
   }
  
} 
#endif