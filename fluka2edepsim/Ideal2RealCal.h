#ifndef _IDEAL2REALCAL_H_
#define _IDEAL2REALCAL_H_

#include <cmath>
#include <TRandom3.h>
#include "math.h"

class Ideal2RealCal{

    private:
        float EStt_c;
        float PosInStt_c[3];
        float PosOuStt_c[3];
        float PosStt_c[3];
        float RhoInStt_c, ThetaStt_c, XInStt_c, Rho_c, TimeStt_c;
        int IdStt_c;
        float Pos_c[3];
        float Theta_c;
        float d1_c, d2_c;
        int plane_c;
        double alpha;
        double alpharanger;
        double rotated_y;
        double rotated_z;
        int Npe[2];
        float EnPmt_c[2];
        
        // Thickness of the planes of the calorimeter module
        static const float a;
        static const float b;
        static const float c;
        static const float d;
        static const float e;
        static const float v_fiber;  // 1/(5.85 ns/m) = 1/5.85 m/ns = 100/5.85 cm/ns = 1e2/5.85*1e9 cm/s
        static const float Xendcap; // fixed on 3/12/2018 (it was 170 before, but looking at PosInStt it seems it is 169)
        static const float Xbarrel;
        static const float Xint_intcatcher;
        static const float Xext_intcatcher;
        static const float Xint_extcatcher;
        static const float Xext_extcatcher;
        static const float Rint_intcatcher;
        static const float Rext_intcatcher;
        static const float Rint_extcatcher;
        static const float Rext_extcatcher;
        //static const float pigreco;
        static const float DeltaTheta; // 24 modules times 12 cells is the number of cells in each ring
        static const float DeltaThetaRanger; // 24 modules
        static const float PEperMeV;



    public:
        // Constructor and destructor
        Ideal2RealCal();
        Ideal2RealCal(float, float*, float*, int, float);
        virtual ~Ideal2RealCal(){};
        
        // Public functions
        void Set_EStt(float);
        void Set_PosInStt(float *);
        void Set_PosOuStt(float *);
        void Set_PosStt(float *);
        void Set_IdStt(int);
        float Attenuation(float);
        float* Get_Time();
        float* Get_Pos();
        float Get_GaussTimeUnc();
        float* Get_EnPmt();
        int* Get_Npe(float *);
        int* Get_Npe();
        float* CFD_Time(int *);
        int Get_Plane();
};
#endif
