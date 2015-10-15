//
//  Header.h
//  cpp361
//
//  Created by Huang Qiyu on 15/8/31.
//
//

#ifndef cpp361_Header_h
#define cpp361_Header_h

class MyPluginsMgr : public cocos2d::Ref
{
public:
    static MyPluginsMgr *getInstance();

    bool init();

    //void applicationWillEnterForeground();

public:

    // timer callback functions, for testing plugins.
    //void adcolonyFunc(float);
    void chartboostFunc(float);
    void vungleFunc(float);
    void flurryFunc(float);
    void googleFunc(float);
    void iapFunc(float);
    void kochavaFunc(float);
    void tuneFunc(float);
    void agecheqFunc(float);
    void facebookFunc(float);
    //void fyberFunc(float);
    void reviewFunc(float);


private:
    MyPluginsMgr();

    //void initAdColony();
    void initChartBoost();
    void initFlurry();
    void initGoogleAnalytics();
    void initIAP();
    void initKochava();
    void initTune();
    void initVungle();
    void initFacebook();
    void initAgeCheq();
    //void initFyber();
    void initReview();

};


#endif
