/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER.
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   Concrete factory to create standard copy and time transactions
 *                for refine schedules.
 *
 ************************************************************************/

#ifndef included_xfer_StandardRefineTransactionFactory
#define included_xfer_StandardRefineTransactionFactory

#include "SAMRAI/SAMRAI_config.h"
#include "SAMRAI/hier/Box.h"
#include "SAMRAI/hier/BoxOverlap.h"
#include "SAMRAI/hier/PatchLevel.h"
#include "SAMRAI/tbox/Transaction.h"
#include "SAMRAI/xfer/RefineClasses.h"
#include "SAMRAI/xfer/RefineTransactionFactory.h"

#include <boost/shared_ptr.hpp>

namespace SAMRAI {
namespace xfer {

/*!
 * @brief Concrete subclass of RefineTransactionFactory base class that allocates
 * RefineCopyTransaction and RefineTimeTransaction objects for a
 * RefineSchedule object.
 *
 * @see xfer::RefineCopyTransaction
 * @see xfer::RefineTimeTransaction
 * @see xfer::RefineTransactionFactory
 */

class StandardRefineTransactionFactory:public RefineTransactionFactory
{
public:
   /*!
    * @brief Default constructor.
    */
   StandardRefineTransactionFactory();

   /*!
    * @brief Virtual destructor.
    */
   virtual ~StandardRefineTransactionFactory();

   /*!
    * @brief Set the array of RefineClass::Data items used by the transactions.
    */
   void
   setRefineItems(
      const RefineClasses::Data ** refine_items,
      int num_refine_items);

   /*!
    * @brief Clear the array of RefineClass::Data items used by the transactions.
    */
   void
   unsetRefineItems();

   /*!
    * @brief Set simulation time used by the refine time transaction objects.
    */
   void
   setTransactionTime(
      double fill_time);

   /*!
    * @brief Allocate an appropriate refine copy or time transaction object.
    * When time interpolation flag is passed as true a RefineTimeTransaction
    * object will be created.  Otherwise, a RefineCopyTransaction aill be
    * created.
    *
    * @param dst_level      boost::shared_ptr to destination patch level.
    * @param src_level      boost::shared_ptr to source patch level.
    * @param overlap        boost::shared_ptr to overlap region between patches.
    * @param dst_patch_id   Integer index of destination patch in destination
    *                       patch level.
    * @param src_patch_id   Integer index of source patch in source patch level.
    * @param ritem_id       Integer index of RefineClass::Data item associated
    *                       with transaction.
    * @param box            Optional const reference to box defining region of
    *                       refine transaction.  Default is an empty box.
    * @param use_time_interpolation  Optional boolean flag indicating whether the
    *                       refine transaction involves time interpolation.
    *                       Default is false.
    */
   boost::shared_ptr<tbox::Transaction>
   allocate(
      const boost::shared_ptr<hier::PatchLevel>& dst_level,
      const boost::shared_ptr<hier::PatchLevel>& src_level,
      const boost::shared_ptr<hier::BoxOverlap>& overlap,
      const hier::Box& dst_mapped_box,
      const hier::Box& src_mapped_box,
      int ritem_id,
      const hier::Box& box,       // Default in v 2.x  = hier::Box()
      bool use_time_interpolation = false) const;

   /*!
    * @brief Virtual function allowing transaction factory to preprocess scratch
    * space data before transactactions use it if they need to.  This function is
    * optional for the concrete transaction factory object.
    * The default implementation is a no-op.
    *
    * @param level        boost::shared_ptr to patch level holding scratch data.
    * @param fill_time    Double value of simulation time corresponding to
    *                     RefineSchedule operations.
    * @param preprocess_vector Const reference to ComponentSelector that indicates
    *                     patch data array indices of scratch patch data objects
    *                     to preprocess.
    */
   virtual void
   preprocessScratchSpace(
      const boost::shared_ptr<hier::PatchLevel>& level,
      double fill_time,
      const hier::ComponentSelector& preprocess_vector) const;

private:
   // The following two functions are not implemented
   StandardRefineTransactionFactory(
      const StandardRefineTransactionFactory&);
   void
   operator = (
      const StandardRefineTransactionFactory&);

   const RefineClasses::Data** d_refine_items;
   int d_num_refine_items;

};

}
}
#endif
