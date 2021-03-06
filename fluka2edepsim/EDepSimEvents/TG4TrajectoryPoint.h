//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Feb 25 18:16:23 2020 by ROOT version 6.18/04)
//      from the StreamerInfo in file /eos/user/l/ldinoto/ECALSTT_FHC_Horn1Y_r1_001_5e16.200102.edep.root
//////////////////////////////////////////////////////////


#ifndef TG4TrajectoryPoint_h
#define TG4TrajectoryPoint_h
class TG4TrajectoryPoint;

#include "Rtypes.h"
#include "TObject.h"
#include "TLorentzVector.h"
#include "TVector3.h"

class TG4TrajectoryPoint : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   TLorentzVector Position;    //
   TVector3       Momentum;    //
   int            Process;     //
   int            Subprocess;    //

   TG4TrajectoryPoint();
   TG4TrajectoryPoint(TG4TrajectoryPoint && ) = default;
   TG4TrajectoryPoint(const TG4TrajectoryPoint & );
   virtual ~TG4TrajectoryPoint();

   ClassDef(TG4TrajectoryPoint,2); // Generated by MakeProject.
};
#endif
