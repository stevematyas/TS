/* Copyright (C) 2010 Ion Torrent Systems, Inc. All Rights Reserved */
#ifndef DARKHALO_H
#define DARKHALO_H

#include <vector>
#include "BkgMagicDefines.h"
#include "Serialization.h"

#if (NUMNUC > NUM_DM_PCA)
   #define NUMDM NUMNUC
#else
   #define NUMDM NUM_DM_PCA
#endif

typedef enum {
   Unspecified = 0,
   PerNucAverage = 1,
   PCAVector = 2
} DarkMatterType;

class Halo{
  public:
    // this is a regional parameter, even if not obviously so
    int   npts;
    int   nuc_flow_t;  // a useful number
    std::vector<float> dark_matter_compensator;  // compensate for systematic errors in background hydrogen modeling, "dark matter"
    float weight[NUMDM];
    DarkMatterType mytype;
    bool training_only;
    float *dark_nuc_comp[NUMDM];

    Halo();
    void Alloc(int npts);
    void SetupDarkNumComp();
    void Delete();
    void ResetDarkMatter();
    void NormalizeDarkMatter();
    void AccumulateDarkMatter(float *residual, int inuc);
    void DumpDarkMatter(FILE *my_fp, int x, int y, float darkness);
    void DumpDarkMatterTitle(FILE *my_fp);

 private:

    // Boost serialization support:
    friend class boost::serialization::access;
    template<class Archive>
      void load(Archive& ar, const unsigned int version)
      {
	// fprintf(stdout, "Serialize: load Halo ... ");
	ar
	  & npts
	  & nuc_flow_t
	  & dark_matter_compensator
	  & weight
          & mytype;
	// & dark_nuc_comp

	SetupDarkNumComp();
	// fprintf(stdout, "done Halo\n");
      }
    template<class Archive>
      void save(Archive& ar, const unsigned int version) const
      {
	// fprintf(stdout, "Serialize: save Halo ... ");
	ar
	  & npts
	  & nuc_flow_t
	  & dark_matter_compensator
	  & weight
          & mytype;
	// & dark_nuc_comp

	// fprintf(stdout, "done Halo\n");
      }
      BOOST_SERIALIZATION_SPLIT_MEMBER()
};

#endif // DARKHALO_H
