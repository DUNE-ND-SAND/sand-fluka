//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Feb 25 18:16:23 2020 by ROOT version 6.18/04)
//      from the StreamerInfo in file /eos/user/l/ldinoto/ECALSTT_FHC_Horn1Y_r1_001_5e16.200102.edep.root
//////////////////////////////////////////////////////////


#ifndef TG4HitSegment_h
#define TG4HitSegment_h
class TG4HitSegment;

#include "Rtypes.h"
#include "TObject.h"
#include "Riostream.h"
#include <vector>
#include "TLorentzVector.h"

class TG4HitSegment : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   vector<int> Contrib;     //
   int         PrimaryId;    //
   float       EnergyDeposit;    //
   float       SecondaryDeposit;    //
   float       TrackLength;         //
   TLorentzVector Start;               //
   TLorentzVector Stop;                //

   TG4HitSegment();
   TG4HitSegment(TG4HitSegment && ) = default;
   TG4HitSegment(const TG4HitSegment & );
   virtual ~TG4HitSegment();

   ClassDef(TG4HitSegment,2); // Generated by MakeProject.
};
#endif
