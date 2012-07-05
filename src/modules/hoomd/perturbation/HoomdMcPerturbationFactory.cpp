#ifdef  MCMD_PERTURB
#ifndef HOOMD_MC_PERTURBATION_FACTORY_CPP
#define HOOMD_MC_PERTURBATION_FACTORY_CPP

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010 - 2012, David Morse (morse012@umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include "HoomdMcPerturbationFactory.h"  

// Subclasses of Perturbation
#ifndef INTER_NOPAIR
#include <mcMd/perturb/mcSystem/McPairPerturbation.h>
#include <mcMd/mcSimulation/McSystem.h>
#include <mcMd/potentials/pair/McPairPotential.h>

#include <modules/hoomd/potentials/pair/HoomdLJPair.h>
#include <modules/hoomd/potentials/pair/HoomdDpdPair.h>
#endif
#ifdef INTER_EXTERNAL
#include <mcMd/perturb/mcSystem/McExternalPerturbation.h>
#include <mcMd/mcSimulation/McSystem.h>
#include <mcMd/potentials/external/ExternalPotential.h>

#include <modules/hoomd/potentials/external/HoomdLamellarExternal.h>
#endif

#ifndef INTER_NOPAIR
#ifdef INTER_EXTERNAL
#include <mcMd/perturb/mcSystem/McPairExternalPerturbation.h>
#endif
#endif


namespace McMd
{

   using namespace Util;

   HoomdMcPerturbationFactory::HoomdMcPerturbationFactory(McSystem& system)
    : systemPtr_(&system)
   {}

   /* 
   * Return a pointer to a instance of Peturbation subclass className.
   */
   Perturbation* HoomdMcPerturbationFactory::factory(const std::string &className) const
   {
      Perturbation *ptr = 0;

      #ifndef INTER_NOPAIR
      if (className == "McPairPerturbation") {
         const std::string& interactionClassName = systemPtr_->pairPotential().
            interactionClassName();
         if (interactionClassName == "HoomdLJPair") {
            ptr = new McPairPerturbation<HoomdLJPair> (*systemPtr_);
         } else if (interactionClassName == "HoomdDpdPair") {
            ptr = new McPairPerturbation<HoomdDpdPair> (*systemPtr_);
         } 
      } 
      #endif
      #ifdef INTER_EXTERNAL
      if (className == "McExternalPerturbation") {
         const std::string& interactionClassName = systemPtr_->externalPotential().
            interactionClassName();
         if (interactionClassName == "HoomdLamellarExternal") {
            ptr = new McExternalPerturbation<HoomdLamellarExternal> (*systemPtr_);
         }
      }
      #endif
      #ifdef INTER_EXTERNAL
      #ifndef INTER_NOPAIR
      if (className == "McPairExternalPerturbation") {
         const std::string& pairInteractionClassName = systemPtr_->pairPotential().
            interactionClassName();
         const std::string& externalInteractionClassName = systemPtr_->externalPotential().
            interactionClassName();
         if (pairInteractionClassName == "HoomdLJPair") {
            if (externalInteractionClassName == "HoomdLamellarExternal") {
               ptr = new McPairExternalPerturbation<HoomdLJPair,HoomdLamellarExternal> (*systemPtr_);
            } else {
               UTIL_THROW("Unsupported external potential.");
            }
         } else if (pairInteractionClassName == "HoomdDpdPair") {
            if (externalInteractionClassName == "HoomdLamellarExternal") {
               ptr = new McPairExternalPerturbation<HoomdDpdPair,HoomdLamellarExternal> (*systemPtr_);
            } else {
               UTIL_THROW("Unsupported external potential.");
            }
         } 
      }
      #endif
      #endif

      return ptr;
   }

}

#endif
#endif  // #ifdef  MCMD_PERTURB
