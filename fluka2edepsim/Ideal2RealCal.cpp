#include "Ideal2RealCal.h"
#include <TMath.h>
#include <iostream>

const float Ideal2RealCal::a = 4.4;
const float Ideal2RealCal::b = 4.6;
const float Ideal2RealCal::c = 4.6;
const float Ideal2RealCal::d = 4.6;
const float Ideal2RealCal::e = 4.8;
const float Ideal2RealCal::v_fiber = 1e11/5.85;  // 1/(5.85 ns/m) = 1/5.85 m/ns = 100/5.85 cm/ns = 1e2/5.85*1e9 cm/s
const float Ideal2RealCal::Xendcap = 169.0; // fixed on 3/12/2018 (it was 170 before, but looking at PosInStt it seems it is 169)
const float Ideal2RealCal::Xbarrel = 215.0;
const float Ideal2RealCal::Xint_intcatcher = 252.999;
const float Ideal2RealCal::Xext_intcatcher = 254.001;
const float Ideal2RealCal::Xint_extcatcher = 299.999;
const float Ideal2RealCal::Xext_extcatcher = 301.001;
const float Ideal2RealCal::Rint_intcatcher = 291.999;
const float Ideal2RealCal::Rext_intcatcher = 293.501;
const float Ideal2RealCal::Rint_extcatcher = 348.499;
const float Ideal2RealCal::Rext_extcatcher = 349.501;
// Division of the module (ring composed of different modules) in cells (angular segmentation)
//const float Ideal2RealCal::TMath::Pi() = 3.141592656;
const float Ideal2RealCal::DeltaTheta = 2.0*TMath::Pi()/(24.0*12.0); // 24 modules times 12 cells is the number of cells in each ring/
const float Ideal2RealCal::DeltaThetaRanger = 2.0*TMath::Pi()/(24.0); // 24 modules
const float Ideal2RealCal::PEperMeV = 40;  // per side, used from 15 Nov 2019, 10:29



// EStt can be either EdepStt or EdqStt, depending on what has been put in the constructor in SaveCalTree.cpp
Ideal2RealCal::Ideal2RealCal(){}

Ideal2RealCal::Ideal2RealCal(float EStt, float* PosInStt, float* PosOuStt, int IdStt, float TimeStt){

    EStt_c = EStt;
    PosInStt_c[0] = PosInStt[0];
    PosInStt_c[1] = PosInStt[1];
    PosInStt_c[2] = PosInStt[2];
    PosOuStt_c[0] = PosOuStt[0]; // on jan 8th 2019 PosStt has been implemented. It now considers the average between PosIn and PosOut.
    PosOuStt_c[1] = PosOuStt[1];
    PosOuStt_c[2] = PosOuStt[2];
    PosStt_c[0] = (PosInStt[0]+PosOuStt[0])/2;
    PosStt_c[1] = (PosInStt[1]+PosOuStt[1])/2;
    PosStt_c[2] = (PosInStt[2]+PosOuStt[2])/2;
    IdStt_c = IdStt;
    TimeStt_c = TimeStt;
    // Compute polar coordinates
    RhoInStt_c = sqrt(pow(PosStt_c[1],2)+pow(PosStt_c[2],2));
    //cout << "rho " << RhoInStt_c << endl;
    if (PosStt_c[1]!=0) ThetaStt_c = 2*atan( PosStt_c[1] / (PosStt_c[2] + sqrt(pow(PosStt_c[2],2)+pow(PosStt_c[1],2))) );
    else if (PosStt_c[1]==0) {
        if (PosStt_c[2]>0) ThetaStt_c = 0;
        if (PosStt_c[2]<0) ThetaStt_c = TMath::Pi();
        if (PosStt_c[2]==0) ThetaStt_c = 0;
    }

    XInStt_c = PosStt_c[0];

    //cout << "polari: " << RhoInStt_c  << "\t" << ThetaStt_c << "\t" << XInStt_c << endl;
    // Distance to the PMTs in the barrel and plane determination
    if (RhoInStt_c>=200.0) {

        alpharanger = ((int)((ThetaStt_c+TMath::Sign((float)6,(float)ThetaStt_c)*DeltaThetaRanger)/(DeltaThetaRanger)) * DeltaThetaRanger);
        alpha = ((int)((ThetaStt_c+TMath::Sign((float)6,(float)ThetaStt_c)*DeltaTheta)/(12*DeltaTheta)) * 12*DeltaTheta);
        rotated_z = PosStt_c[2]*cos(-alpha) - PosStt_c[1]*sin(-alpha);
        rotated_y = PosStt_c[2]*sin(-alpha) + PosStt_c[1]*cos(-alpha);

        //std::cout << "y: " << PosStt_c[1] << "\t\tz: " << PosStt_c[2] << std::endl;
        //std::cout << "roty: " << rotated_y << "\t\trotz: " << rotated_z << std::endl;

        if (rotated_z>=200 && rotated_z<200+a)                          plane_c = 1;
        else if (rotated_z>=200+a && rotated_z<200+a+b)                 plane_c = 2;
        else if (rotated_z>=200+a+b && rotated_z<200+a+b+c)             plane_c = 3;
        else if (rotated_z>=200+a+b+c && rotated_z<200+a+b+c+d)         plane_c = 4;
        else if (rotated_z>=200+a+b+c+d && rotated_z<200+a+b+c+d+e)     plane_c = 5;
        else if (rotated_z>=200+a+b+c+d+e)                              plane_c = 6;

        if (rotated_z>=200 && rotated_z<=200+a+b+c+d+e) {
            d1_c = Xbarrel + XInStt_c;
            d2_c = Xbarrel - XInStt_c;
        } else if (rotated_z>=Rint_intcatcher && rotated_z<=Rext_intcatcher) {
            d1_c = Xext_intcatcher + XInStt_c;
            d2_c = Xext_intcatcher - XInStt_c;
        } else if (rotated_z>=Rint_extcatcher && rotated_z<=Rext_extcatcher) {
            d1_c = Xext_extcatcher + XInStt_c;
            d2_c = Xext_extcatcher - XInStt_c;
        }

    }
    // Distance to the PMTs in the endcaps and plane determination
    if (RhoInStt_c<200 && abs(XInStt_c)>=Xendcap) {

        if (abs(XInStt_c)>=Xendcap && abs(XInStt_c)<Xendcap+a)                          plane_c = 1;
        else if (abs(XInStt_c)>=Xendcap+a && abs(XInStt_c)<Xendcap+a+b)                 plane_c = 2;
        else if (abs(XInStt_c)>=Xendcap+a+b && abs(XInStt_c)<Xendcap+a+b+c)             plane_c = 3;
        else if (abs(XInStt_c)>=Xendcap+a+b+c && abs(XInStt_c)<Xendcap+a+b+c+d)         plane_c = 4;
        else if (abs(XInStt_c)>=Xendcap+a+b+c+d && abs(XInStt_c)<Xendcap+a+b+c+d+e)     plane_c = 5;
        else if (abs(XInStt_c)>=Xendcap+a+b+c+d+e)                                      plane_c = 6;

        if (abs(XInStt_c)<=Xendcap+a+b+c+d+e) {
            d1_c = sqrt(200.0*200.0-PosStt_c[2]*PosStt_c[2]) + PosStt_c[1];
            d2_c = sqrt(200.0*200.0-PosStt_c[2]*PosStt_c[2]) - PosStt_c[1];
        } else if (abs(XInStt_c)>=Xint_intcatcher && abs(XInStt_c)<=Xext_intcatcher) {
            d1_c = sqrt(Rext_intcatcher*Rext_intcatcher - PosStt_c[2]*PosStt_c[2]) + PosStt_c[1];
            d2_c = sqrt(Rext_intcatcher*Rext_intcatcher - PosStt_c[2]*PosStt_c[2]) - PosStt_c[1];
        } else if (abs(XInStt_c)>=Xint_extcatcher && abs(XInStt_c)<=Xext_extcatcher) {
            d1_c = sqrt(Rext_extcatcher*Rext_extcatcher - PosStt_c[2]*PosStt_c[2]) + PosStt_c[1];
            d2_c = sqrt(Rext_extcatcher*Rext_extcatcher - PosStt_c[2]*PosStt_c[2]) - PosStt_c[1];
        }
    }
    // Not in the barrel nor in the endcaps
    if (RhoInStt_c<200 && abs(XInStt_c)<Xendcap) {
        d1_c = 0;
        d2_c = 0;
    }
}



int Ideal2RealCal::Get_Plane() {
    return plane_c;
}



float Ideal2RealCal::Attenuation(float distance) {
    float p1 = 0.35;
    float atl1 = 50.0;
    float atl2 = 380;
    // Each plane has its own optical properties
    if (plane_c == 1 || plane_c == 2)       atl2 = 430.0;
    else if (plane_c == 3)                  atl2 = 380.0;
    else if (plane_c == 4 || plane_c == 5)  atl2 = 330.0;
    else if (plane_c == 6)                  atl2 = 330.0;
    return p1*exp(-distance/atl1) + (1.0-p1)*exp(-distance/atl2);
}



void Ideal2RealCal::Set_EStt(float Edep) {
    EStt_c = Edep;
}



void Ideal2RealCal::Set_IdStt(int IdStt) {
    IdStt_c = IdStt;
}



float* Ideal2RealCal::CFD_Time(int* npe) {
    static float CFDtime[2];
    float Tscin = 3.08*1e-9; // 3.08 ns        scintillation time!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    float Tscex = 0.588;
    TRandom3 *uniform_random = new TRandom3();
    uniform_random->SetSeed(0);

    std::vector<double> photontime1, photontime2;
    photontime1.clear();
    photontime2.clear();
    for (int i=0; i<npe[0]; i++) {
        photontime1.push_back( Tscin * pow( 1.0/(uniform_random->TRandom3::Rndm()) - 1.0, Tscex) );
    }
    for (int i=0; i<npe[1]; i++) {
        photontime2.push_back( Tscin * pow( 1.0/(uniform_random->TRandom3::Rndm()) - 1.0, Tscex) );
    }
    if (photontime1.size()!=0) {
        std::sort(photontime1.begin(), photontime1.end());
        CFDtime[0] = photontime1[floor(npe[0]*0.15)];
    } else CFDtime[0] = 0;
    if (photontime2.size()!=0) {
        std::sort(photontime2.begin(), photontime2.end());
        CFDtime[1] = photontime2[floor(npe[1]*0.15)];
    } else CFDtime[1] = 0;

    delete uniform_random;
    return CFDtime;
}



float* Ideal2RealCal::Get_Time() { // ancora da implementare la somma col tempo di arrivo (se la vogliamo mettere qui dentro)

    static float time[3];
    TRandom3 *gaussian_random = new TRandom3();
    gaussian_random->SetSeed(0);
    time[0] = TimeStt_c + d1_c/v_fiber + Ideal2RealCal::CFD_Time(Ideal2RealCal::Get_Npe(Ideal2RealCal::Get_EnPmt()))[0] + gaussian_random->Gaus(0.0,260e-12);
    time[1] = TimeStt_c + d2_c/v_fiber + Ideal2RealCal::CFD_Time(Ideal2RealCal::Get_Npe(Ideal2RealCal::Get_EnPmt()))[1] + gaussian_random->Gaus(0.0,260e-12);

    time[2] = 0.5*(time[0] + time[1] - (d1_c + d2_c)/v_fiber); // Time resolution depends on time distribution of photoelectrons
    
    delete gaussian_random;
    return time;
}



float* Ideal2RealCal::Get_EnPmt(){
    //static float EnPmt[2];
    EnPmt_c[0] = Ideal2RealCal::Attenuation(d1_c)*EStt_c/2;        // has "/2" to be taken into account???
    EnPmt_c[1] = Ideal2RealCal::Attenuation(d2_c)*EStt_c/2;
    return EnPmt_c;
}



int* Ideal2RealCal::Get_Npe(float* enpmt){
    // Photo-electrons per MeV for each particle (still to complete with missing particles...)
    // Calculation of the number of photo-electrons
    TRandom3 *poisson_random = new TRandom3();
    poisson_random->SetSeed(0);
    if (EStt_c!=0) {
        Npe[0] = poisson_random->Poisson(PEperMeV*enpmt[0]*1.0e3);
        Npe[1] = poisson_random->Poisson(PEperMeV*enpmt[1]*1.0e3);
    }
    else if (EStt_c==0) {
        Npe[0] = 0;
        Npe[1] = 0;
    }
    delete poisson_random;
    return Npe;
}



int* Ideal2RealCal::Get_Npe(){
    // Photo-electrons per MeV for each particle (still to complete with missing particles...)
    // Calculation of the number of photo-electrons
    TRandom3 *poisson_random = new TRandom3();
    poisson_random->SetSeed(0);
    if (EStt_c!=0) {
        //Npe_total_noattenuation = poisson_random->Poisson(PEperMeV*EStt_c*1e3);
        //Npe[0] = (int)(Ideal2RealCal::Attenuation(d1_c) * Npe_total_noattenuation/2);
        //Npe[1] = (int)(Ideal2RealCal::Attenuation(d2_c) * Npe_total_noattenuation/2);
        Npe[0] = poisson_random->Poisson(PEperMeV*Ideal2RealCal::Get_EnPmt()[0]*1.0e3);
        Npe[1] = poisson_random->Poisson(PEperMeV*Ideal2RealCal::Get_EnPmt()[1]*1.0e3);
    }
    else if (EStt_c==0) {
        Npe[0] = 0;
        Npe[1] = 0;
    }
    delete poisson_random;
    return Npe;
}




float Ideal2RealCal::Get_GaussTimeUnc() {
    TRandom3 *gaussian_random = new TRandom3();
    gaussian_random->SetSeed(0);
    float random = 0;
    random = gaussian_random->Gaus(0,1);
    delete gaussian_random;
    return random;
}



float* Ideal2RealCal::Get_Pos() {

    // Division of the endcaps along the beam direction
    int ZDivisions = 80;
    double DeltaZ = 400/ZDivisions;

    // External catcher barrel
    if (RhoInStt_c>348.499 && RhoInStt_c<349.501 && abs(XInStt_c)<301.001) { // 11 Jun 19 to take into account the catcher
        Pos_c[0] = PosStt_c[0];

        if (PosStt_c[1]!=0) ThetaStt_c = 2*atan( PosStt_c[1] / (PosStt_c[2] + sqrt(pow(PosStt_c[2],2)+pow(PosStt_c[1],2))) );
        else if (PosStt_c[1]==0) {
            if (PosStt_c[2]>0) ThetaStt_c = 0;
            if (PosStt_c[2]<0) ThetaStt_c = TMath::Pi();
            if (PosStt_c[2]==0) ThetaStt_c = 0;
        }

        Theta_c = (int)(ThetaStt_c/DeltaThetaRanger) * DeltaThetaRanger + 0*TMath::Sign((float)1.,(float)ThetaStt_c)*DeltaThetaRanger/2; // same angular granularity as the calorimeter barrel

        Pos_c[2] =  (348.5+0.5)*cos(Theta_c-alpharanger)            * cos(-alpharanger) + (348.5+0.5)*sin((Theta_c-alpharanger))             * sin(-alpharanger);
        Pos_c[1] = -(348.5+0.5)*cos(Theta_c-alpharanger)            * sin(-alpharanger) + (348.5+0.5)*sin((Theta_c-alpharanger))             * cos(-alpharanger);
    }

    // External catcher endcap
    if (RhoInStt_c<349.501 && abs(XInStt_c)>299.999 && abs(XInStt_c)<301.001) { // 11 Jun 19 to take into account the catcher
        Pos_c[0] = TMath::Sign((float)1.,(float)PosStt_c[0])*(300+0.5);

        Pos_c[1] = PosStt_c[1];
        Pos_c[2] = (int)(PosStt_c[2]/DeltaZ) * DeltaZ + TMath::Sign((float)1.,(float)PosStt_c[2])*DeltaZ/2; // same angular granularity as the calorimeter endcap
        Rho_c = sqrt(pow(Pos_c[2], 2) + pow(Pos_c[1], 2));

        if (PosStt_c[1]!=0)       Theta_c = 2*atan( Pos_c[1] / (Pos_c[2] + sqrt(pow(Pos_c[2],2)+pow(Pos_c[1],2))) );
        else if(PosStt_c[1]==0) {
            if (PosStt_c[2]>0)    Theta_c = 0;
            if (PosStt_c[2]<0)    Theta_c = TMath::Pi();
            if (PosStt_c[2]==0)   Theta_c = 0;
        }
    }

    // Internal catcher barrel
    if (RhoInStt_c>291.999 && RhoInStt_c<293.501 && abs(XInStt_c)<254.001) { // 11 Jun 19 to take into account the catcher
        Pos_c[0] = PosStt_c[0];

        if (PosStt_c[1]!=0) ThetaStt_c = 2*atan( PosStt_c[1] / (PosStt_c[2] + sqrt(pow(PosStt_c[2],2)+pow(PosStt_c[1],2))) );
        else if (PosStt_c[1]==0) {
            if (PosStt_c[2]>0) ThetaStt_c = 0;
            if (PosStt_c[2]<0) ThetaStt_c = TMath::Pi();
            if (PosStt_c[2]==0) ThetaStt_c = 0;
        }

        Theta_c = (int)(ThetaStt_c/DeltaThetaRanger) * DeltaThetaRanger + 0*TMath::Sign((float)1.,(float)ThetaStt_c)*DeltaThetaRanger/2; // same angular granularity as the calorimeter barrel

        Pos_c[2] =  (292+0.75)*cos(Theta_c-alpharanger)            * cos(-alpharanger) + (292+0.75)*sin((Theta_c-alpharanger))             * sin(-alpharanger);
        Pos_c[1] = -(292+0.75)*cos(Theta_c-alpharanger)            * sin(-alpharanger) + (292+0.75)*sin((Theta_c-alpharanger))             * cos(-alpharanger);

    }

    // Internal catcher endcap
    if (RhoInStt_c<293.501 && abs(XInStt_c)>252.999 && abs(XInStt_c)<254.001) { // 11 Jun 19 to take into account the catcher
        Pos_c[0] = TMath::Sign((float)1.,(float)PosStt_c[0])*(253+0.5);

        Pos_c[1] = PosStt_c[1];
        Pos_c[2] = (int)(PosStt_c[2]/DeltaZ) * DeltaZ + TMath::Sign((float)1.,(float)PosStt_c[2])*DeltaZ/2; // same angular granularity as the calorimeter endcap
        Rho_c = sqrt(pow(Pos_c[2], 2) + pow(Pos_c[1], 2));

        if (PosStt_c[1]!=0)       Theta_c = 2*atan( Pos_c[1] / (Pos_c[2] + sqrt(pow(Pos_c[2],2)+pow(Pos_c[1],2))) );
        else if(PosStt_c[1]==0) {
            if (PosStt_c[2]>0)    Theta_c = 0;
            if (PosStt_c[2]<0)    Theta_c = TMath::Pi();
            if (PosStt_c[2]==0)   Theta_c = 0;
        }
    }

    // Calorimeter barrel
    //if (RhoInStt_c>=200 && RhoInStt_c<=200+a+b+c+d+e && abs(XInStt_c)<=215) { // "if (RhoInStt_c>=200)" modified 11 Jun 19 to take into account the catcher // Commented on 18 Oct 2019 to correct bug_20191018_1
    if (RhoInStt_c>=200 && rotated_z<=200+a+b+c+d+e && abs(XInStt_c)<=215) {

        // 16 Jan 2019
        if (PosStt_c[1]!=0) ThetaStt_c = 2*atan( PosStt_c[1] / (PosStt_c[2] + sqrt(pow(PosStt_c[2],2)+pow(PosStt_c[1],2))) );
        else if (PosStt_c[1]==0) {
            if (PosStt_c[2]>0) ThetaStt_c = 0;
            if (PosStt_c[2]<0) ThetaStt_c = TMath::Pi();
            if (PosStt_c[2]==0) ThetaStt_c = 0;
        }

        Theta_c = (int)(ThetaStt_c/DeltaTheta) * DeltaTheta + TMath::Sign((float)1.,(float)ThetaStt_c)*DeltaTheta/2;
        Pos_c[0] = PosStt_c[0];

        if (plane_c==1) {
            Pos_c[2] =  (200+a/2)            * cos(-alpha) + (200+a/2)*tan((Theta_c-alpha))             * sin(-alpha);
            Pos_c[1] = -(200+a/2)            * sin(-alpha) + (200+a/2)*tan((Theta_c-alpha))             * cos(-alpha);
        }
        if (plane_c==2) {
            Pos_c[2] =  (200+a+b/2)          * cos(-alpha) + (200+a+b/2)*tan((Theta_c-alpha))           * sin(-alpha);
            Pos_c[1] = -(200+a+b/2)          * sin(-alpha) + (200+a+b/2)*tan((Theta_c-alpha))           * cos(-alpha);
        }
        if (plane_c==3) {
            Pos_c[2] =  (200+a+b+c/2)        * cos(-alpha) + (200+a+b+c/2)*tan((Theta_c-alpha))         * sin(-alpha);
            Pos_c[1] = -(200+a+b+c/2)        * sin(-alpha) + (200+a+b+c/2)*tan((Theta_c-alpha))         * cos(-alpha);
        }
        if (plane_c==4) {
            Pos_c[2] =  (200+a+b+c+d/2)      * cos(-alpha) + (200+a+b+c+d/2)*tan((Theta_c-alpha))       * sin(-alpha);
            Pos_c[1] = -(200+a+b+c+d/2)      * sin(-alpha) + (200+a+b+c+d/2)*tan((Theta_c-alpha))       * cos(-alpha);
        }
        if (plane_c==5) {
            Pos_c[2] =  (200+a+b+c+d+e/2)    * cos(-alpha) + (200+a+b+c+d+e/2)*tan((Theta_c-alpha))     * sin(-alpha);
            Pos_c[1] = -(200+a+b+c+d+e/2)    * sin(-alpha) + (200+a+b+c+d+e/2)*tan((Theta_c-alpha))     * cos(-alpha);
        }

    }

    // Calorimeter endcaps 
    if (RhoInStt_c<200 && abs(XInStt_c)>=Xendcap && abs(XInStt_c)<=215) { // "else if (RhoInStt_c<200 && abs(XInStt_c)>=Xendcap)" modified 11 Jun 19 to take into account the catcher

        if (plane_c==1) Pos_c[0] = TMath::Sign((float)1.,(float)PosStt_c[0])*(Xendcap+a/2);
        if (plane_c==2) Pos_c[0] = TMath::Sign((float)1.,(float)PosStt_c[0])*(Xendcap+a+b/2);
        if (plane_c==3) Pos_c[0] = TMath::Sign((float)1.,(float)PosStt_c[0])*(Xendcap+a+b+c/2);
        if (plane_c==4) Pos_c[0] = TMath::Sign((float)1.,(float)PosStt_c[0])*(Xendcap+a+b+c+d/2);
        if (plane_c==5) Pos_c[0] = TMath::Sign((float)1.,(float)PosStt_c[0])*(Xendcap+a+b+c+d+e/2);

        Pos_c[1] = PosStt_c[1];
        Pos_c[2] = (int)(PosStt_c[2]/DeltaZ) * DeltaZ + TMath::Sign((float)1.,(float)PosStt_c[2])*DeltaZ/2;
        Rho_c = sqrt(pow(Pos_c[2], 2) + pow(Pos_c[1], 2));

        if (PosStt_c[1]!=0)       Theta_c = 2*atan( Pos_c[1] / (Pos_c[2] + sqrt(pow(Pos_c[2],2)+pow(Pos_c[1],2))) );
        else if(PosStt_c[1]==0) {
            if (PosStt_c[2]>0)    Theta_c = 0;
            if (PosStt_c[2]<0)    Theta_c = TMath::Pi();
            if (PosStt_c[2]==0)   Theta_c = 0;
        }

    } 

    // STT 
    if (rotated_z<200 && abs(XInStt_c)<Xendcap) {
        Pos_c[0] = 0.0;
        Pos_c[1] = 0.0;
        Pos_c[2] = 0.0;
    }

    return Pos_c;
}
