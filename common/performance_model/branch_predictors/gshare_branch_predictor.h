#ifndef GSHARE_BRANCH_PREDICTOR_H 
#define GSHARE_BRANCH_PREDICTOR_H 
#include <boost/scoped_array.hpp>
#include "simulator.h"
#include "branch_predictor.h"
#include "saturating_predictor.h"

class GshareBranchPredictor : public BranchPredictor
{

public:

   GshareBranchPredictor(String name, core_id_t core_id, UInt32 entries)
      : m_num_entries(entries)
      , m_table(entries, 0), BranchPredictor(name, core_id)
   {
      reset();
      uint32_t hist_len = ilog2(m_num_entries);  
      m_mask = 0;
      m_mask = (1 << hist_len) - 1;
   }

    bool predict(bool indirect, IntPtr ip, IntPtr target) 
   {
      uint32_t index;  
      gen_index(ip, index); 
      return (m_table[index].predict());
   }

   void update(bool predicted, bool actual, bool indirect, IntPtr ip, IntPtr target)
   {
      updateCounters(predicted, actual);
      UInt32 index; 
      gen_index(ip, index); 
      if (actual)
      {
         ++m_table[index];
      }
      else
      {
         --m_table[index];
      }
      	// update the global history table
     update_ghr(actual); 
   }

   void reset()
   {
      for (unsigned int i = 0 ; i < m_num_entries ; i++) {
         m_table[i].reset();
      }
   }

private:
   void gen_index(uint32_t ip, uint32_t& index){ 
    //   create a bit mask of lenght n
      // extract the first n bit
      uint32_t ip_mask = ip & m_mask; 
      uint32_t ghr_mask = ghr & m_mask; // should not be needed; 
      // XOR them to get the index 
      index = ghr_mask ^ ip_mask; 
   }

   void update_ghr(bool actual){
        // Clear the LSB of the number
        uint32_t clearedNumber = ghr & 0xFFFFFFFE; // Mask with all bits set except the LSB
        // Set the LSB to the specified bit value
        ghr = clearedNumber | static_cast<uint32_t>(actual);
    }
   
   template<typename Addr>
   Addr ilog2(Addr n)
   {
      Addr i;
      for(i=0;n>0;n>>=1,i++) {}
      return i-1;
   }

private:

   uint32_t m_num_entries;
   IntPtr m_mask; 
   uint32_t ghr;
   std::vector<SaturatingPredictor<2>> m_table;

};

#endif /* BIMODAL_TABLE_H */
