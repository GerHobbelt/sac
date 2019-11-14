#ifndef PRED_H
#define PRED_H

#include "../pred/lms.h"
#include "../pred/lms_cascade.h"
#include "../pred/lpc.h"
#include "../pred/bias.h"

class Predictor {
  public:
    struct tparam {
      int nA,nS0,nS1,k;
      std::vector <int>vn0,vn1;
      std::vector <double>vmu0,vmu1;
      std::vector <double>vmudecay0,vmudecay1;
      std::vector <double>vpowdecay0,vpowdecay1;
      double lambda0,lambda1,ols_nu0,ols_nu1,mu_mix0,mu_mix1,mu_mix_beta0,mu_mix_beta1;
    };
    Predictor(const tparam &p);
    double PredictMaster();
    double PredictSlave(const int32_t *ch_master,int nsample,int numsamples);
    void UpdateMaster(double val);
    void UpdateSlave(double val);
  private:
    void FillSlaveHist(const int32_t *ch_master,int nsample,int numsamples,vec1D &buf);
    tparam p;
    int nA,nS0,nS1;
    OLS<double>ols0,ols1;
    LMSCascade lms0,lms1;
    BiasEstimator be0,be1;
    vec1D hist0,hist1,tbuf;
    double p_lpc0,p_lpc1,p_lms0,p_lms1;
};

#endif // PRED_H