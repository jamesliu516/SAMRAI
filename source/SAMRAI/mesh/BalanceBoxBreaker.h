/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER.
 *
 * Copyright:     (c) 1997-2013 Lawrence Livermore National Security, LLC
 * Description:   Utilitiy for breaking boxes during partitioning.
 *
 ************************************************************************/

#ifndef included_mesh_BalanceBoxBreaker
#define included_mesh_BalanceBoxBreaker

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/hier/Box.h"
#include "SAMRAI/mesh/PartitioningParams.h"

#include <vector>

namespace SAMRAI {
namespace mesh {

/*!
 * @brief Utilities for breaking up boxes during partitioning.
 */

class BalanceBoxBreaker {

public:

   BalanceBoxBreaker(const PartitioningParams &pparams) :
      d_pparams(&pparams),
      d_print_steps(false),
      d_print_break_steps(false)
      {
         setTimers();
      }


   /*!
    * @brief Break off a given load size from a given Box.
    *
    * Attempt to break off the ideal_load, or at least a load
    * inside the range [low_load, high_load].
    *
    * @param[out] breakoff Boxes broken off (usually just one).
    *
    * @param[out] leftover Remainder of box after breakoff is gone.
    *
    * @param[out] brk_load The load broken off.
    *
    * @param[in] box Box to break.
    *
    * @param[in] ideal_load Ideal load to break.
    *
    * @param[in] low_load
    *
    * @param[in] high_load
    *
    * @return whether a successful break was made.
    *
    * @pre ideal_load_to_break > 0
    */
   bool
   breakOffLoad(
      std::vector<hier::Box>& breakoff,
      std::vector<hier::Box>& leftover,
      double& brk_load,
      const hier::Box& box,
      double ideal_load,
      double low_load,
      double high_load ) const;


private:

   bool
   breakOffLoad_planar(
      std::vector<hier::Box>& breakoff,
      std::vector<hier::Box>& leftover,
      double& brk_load,
      const hier::Box& box,
      double ideal_load,
      double low_load,
      double high_load,
      const std::vector<std::vector<bool> >& bad_cuts ) const;

   bool
   breakOffLoad_cubic(
      std::vector<hier::Box>& breakoff,
      std::vector<hier::Box>& leftover,
      double& brk_load,
      const hier::Box& box,
      double ideal_load,
      double low_load,
      double high_load,
      const std::vector<std::vector<bool> >& bad_cuts ) const;

   double
   computeBalancePenalty(double imbalance) const
   {
      return tbox::MathUtilities<double>::Abs(imbalance);
   }

   void
   burstBox(
      std::vector<hier::Box>& boxes,
      const hier::Box& bursty,
      const hier::Box& solid ) const;

   void setTimers();

   const PartitioningParams *d_pparams;

   //@{
   //! @name Debugging and diagnostic data

   bool d_print_steps;
   bool d_print_break_steps;
   boost::shared_ptr<tbox::Timer> t_break_off_load;
   boost::shared_ptr<tbox::Timer> t_find_bad_cuts;

   //@}

};

}
}
#endif