#ifndef MC_MOVE_FACTORY
#define MC_MOVE_FACTORY

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010 - 2012, David Morse (morse012@umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include "McMoveFactory.h" // Class header

#include "common/AtomDisplaceMove.h"
#include "common/RigidDisplaceMove.h"
#include "common/HybridMdMove.h"
#include "common/HybridNphMdMove.h"
#include "common/MdMove.h"
#include "common/DpdMove.h"

#include "linear/EndSwapMove.h"
#include "linear/CfbEndMove.h"
#include "linear/CfbHomoReptationMove.h"
#include "linear/CfbReptationMove.h"
#include "linear/CfbRebridgeMove.h"
#include "linear/CfbDoubleRebridgeMove.h"

#include "ring/CfbRingRebridgeMove.h"
#include "ring/RingTetraRebridgeMove.h"
#include "ring/RingOctaRebridgeMove.h"

#include "semigrand/HomopolymerSemiGrandMove.h"

namespace McMd
{

   using namespace Util;

   /* 
   * Return a pointer to a instance of Species subclass className.
   */
   McMove* McMoveFactory::factory(const std::string &className) const
   {
      McMove* ptr = 0;
    
      // Try subfactories first  
      ptr = trySubfactories(className);
      if (ptr) return ptr;

      if (className == "HybridMdMove") {
         ptr = new HybridMdMove(*systemPtr_);
      } else 
      if (className == "HybridNphMdMove") {
         ptr = new HybridNphMdMove(*systemPtr_);
      } else 
      if (className == "MdMove") {
         ptr = new MdMove(*systemPtr_);
      } else 
      if (className == "DpdMove") {
         ptr = new DpdMove(*systemPtr_);
      } else 
      if (className == "AtomDisplaceMove") {
         ptr = new AtomDisplaceMove(*systemPtr_);
      } else
      if (className == "RigidDisplaceMove") {
         ptr = new RigidDisplaceMove(*systemPtr_);
      } else
      if (className == "EndSwapMove") {
         ptr = new EndSwapMove(*systemPtr_);
      } else 
      if (className == "CfbEndMove") {
         ptr = new CfbEndMove(*systemPtr_);
      } else 
      if (className == "CfbHomoReptationMove") {
         ptr = new CfbHomoReptationMove(*systemPtr_);
      } else 
      if (className == "CfbReptationMove") {
         ptr = new CfbReptationMove(*systemPtr_);
      } else 
      if (className == "CfbRebridgeMove") {
         ptr = new CfbRebridgeMove(*systemPtr_);
      } else 
      if (className == "CfbDoubleRebridgeMove") {
         ptr = new CfbDoubleRebridgeMove(*systemPtr_);
      } else 
      if (className == "CfbRingRebridgeMove") {
         ptr = new CfbRingRebridgeMove(*systemPtr_);
      } else 
      if (className == "RingTetraRebridgeMove") {
         ptr = new RingTetraRebridgeMove(*systemPtr_);
      } else 
      if (className == "RingOctaRebridgeMove") {
         ptr = new RingOctaRebridgeMove(*systemPtr_);
      } else 
      if (className == "HomopolymerSemiGrandMove") {
         ptr = new HomopolymerSemiGrandMove(*systemPtr_);
      } 
      return ptr;
   }

}
#endif
