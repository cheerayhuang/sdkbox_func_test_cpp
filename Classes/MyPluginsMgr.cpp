//
//  PluginsMgr.cpp
//  cpp361
//
//  Created by Huang Qiyu on 15/8/31.
//
//

#include "cocos2d.h"

#include "MyPluginsMgr.h"

#include "PluginAdcolony/PluginAdcolony.h"
#include "PluginAgeCheq/PluginAgeCheq.h"
#include "PluginChartboost/PluginChartboost.h"
#include "PluginVungle/PluginVungle.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#include "PluginIAP/PluginIAP.h"
#include "PluginKochava/PluginKochava.h"
#include "PluginTune/PluginTune.h"
#include "PluginFacebook/PluginFacebook.h"
#include "PluginFlurryAnalytics/PluginFlurryAnalytics.h"
#include "PluginFyber/PluginFyber.h"
#include "PluginReview/PluginReview.h"

USING_NS_CC;
using namespace sdkbox;

//adcolony

class ADListener : public sdkbox::AdColonyListener
{
public:
    void onAdColonyChange(const sdkbox::AdColonyAdInfo& info, bool available)
    {
        if (available)
        {
            CCLOG("AdColony Zone: %s available", info.zoneID.c_str());
        }
        else
        {
            CCLOG("AdColony Zone: %s not available", info.zoneID.c_str());
        }
    }
    void onAdColonyReward(const sdkbox::AdColonyAdInfo& info, const std::string& currencyName, int amount, bool success)
    {
        if(success)
        {
            CCLOG("AdColony reward zone: %s, reward: %d %s ", info.zoneID.c_str(), amount, currencyName.c_str());
        }
        else
        {
            CCLOG("AdColony reward failed.");
        }
    }
    void onAdColonyStarted(const sdkbox::AdColonyAdInfo& info)
    {
        CCLOG("Ad Started: %s", info.zoneID.c_str());
    }
    void onAdColonyFinished(const sdkbox::AdColonyAdInfo& info)
    {
        if (info.shown)
        {
            CCLOG("AdColony Ad shown");
        }
        else
        {
            CCLOG("AdColony Ad not shown");
        }
    }
};

void MyPluginsMgr::initAdColony()
{
    PluginAdColony::init();
    PluginAdColony::setListener(new ADListener);
    PluginAdColony::getStatus("video");
    PluginAdColony::setCustomID("test");
}

void MyPluginsMgr::adcolonyFunc(float)
{
    CCLOG("calling adcolony funcstions");

    PluginAdColony::show("video");
    PluginAdColony::show("v4vc");

}

// Chartboost

class CBListener : public sdkbox::ChartboostListener
{
private:
    static bool isPlayed;

public:
    //Ad callbacks
    void onChartboostCached(const std::string& name)
    {
        CCLOG("Chartboost ad: %s cached", name.c_str());

        if (!isPlayed) {
            PluginChartboost::show(CB_Location_Default);
            PluginChartboost::show("Level Complete");
            isPlayed = false;
        }
    }
    bool onChartboostShouldDisplay(const std::string& name)
    {
        CCLOG("Chartboost ad: %s should display", name.c_str());
        return true;
    }
    void onChartboostDisplay(const std::string& name)
    {
        CCLOG("Chartboost ad: %s display", name.c_str());
    }
    void onChartboostDismiss(const std::string& name)
    {
        CCLOG("Chartboost ad: %s dismiss", name.c_str());
    }
    void onChartboostClose(const std::string& name)
    {
        CCLOG("Chartboost ad: %s close", name.c_str());
    }
    void onChartboostClick(const std::string& name)
    {
        CCLOG("Chartboost ad: %s click", name.c_str());
    }
    void onChartboostReward(const std::string& name, int reward)
    {
        CCLOG("Chartboost ad: %s reward: %d", name.c_str(), reward);
    }
    void onChartboostFailedToLoad(const std::string& name, sdkbox::CB_LoadError e)
    {
        CCLOG("Chartboost ad: %s Failed to load: error: %d", name.c_str(), e);
    }
    void onChartboostFailToRecordClick(const std::string& name, sdkbox::CB_ClickError e)
    {
        CCLOG("Chartboost ad: %s Failed to record click: %d", name.c_str(), e);
    }

    //Miscellaneous callbacks
    void onChartboostConfirmation()
    {
        CCLOG("Chartboost ad confirmation show your confirmation dialog here");
    }
    void onChartboostCompleteStore()
    {
        CCLOG("Chartboost ad coming back from store");
    }
};

bool CBListener::isPlayed = false;

void MyPluginsMgr::initChartBoost()
{
    PluginChartboost::init();
    PluginChartboost::setListener(new CBListener);

}

void MyPluginsMgr::chartboostFunc(float)
{

}

// vungle

class VungleListenerDemo : public sdkbox::VungleListener
{
private:
    static bool isPlayed;

public:
    void onVungleCacheAvailable()
    {
        CCLOG("Cache Available");

        if (!isPlayed) {
            CCLOG("show video");
            PluginVungle::show("video");

            CCLOG("show reward");
            PluginVungle::show("reward");

            isPlayed = true;
        }
    }
    void onVungleStarted()
    {
        CCLOG("Start Displaying ad, disable game/music here");
    }
    void onVungleFinished()
    {
        CCLOG("Finish Displaying ad, resume game/music here");
    }

    void onVungleAdViewed(bool isComplete)
    {
        if (isComplete) {
            CCLOG("User finish viewing the ad");
        } else {
            CCLOG("User didn't finish viewing the ad");
        }
    }

    void onVungleAdReward(const std::string& adName){}
};

bool VungleListenerDemo::isPlayed = false;

void MyPluginsMgr::initVungle()
{
    sdkbox::PluginVungle::init();
    sdkbox::PluginVungle::setDebug(true);
    sdkbox::PluginVungle::setListener(new VungleListenerDemo);

}

void MyPluginsMgr::vungleFunc(float)
{

}

// flurryanalystics


static bool flurryAnalyticsSendData() {
    std::string ret;

    bool retBool = sdkbox::PluginFlurryAnalytics::activeSessionExists();
    if (!retBool) {
        CCLOG("session not exist return");
        return false;
    }

    ret = sdkbox::PluginFlurryAnalytics::getSessionID();
    CCLOG("Flurry analytics session : %s", ret.c_str());

    std::string origin = "this is origin name";
    std::string originVersion = "origin version";
    sdkbox::PluginFlurryAnalytics::addOrigin(origin, originVersion);

    origin = "other origin";
    originVersion = "other origin version";
    std::map<std::string, std::string> params;
    params.insert(std::make_pair("key1", "value1"));
    params.insert(std::make_pair("key2", "value2"));
    sdkbox::PluginFlurryAnalytics::addOrigin(origin, originVersion, params);

    ret = "test event1";
    sdkbox::PluginFlurryAnalytics::logEvent(ret);

    ret = "test event2";
    params.clear();
    params.insert(std::make_pair("eKey1", "eVal1"));
    params.insert(std::make_pair("eKey2", "eVal2"));
    sdkbox::PluginFlurryAnalytics::logEvent(ret, params);

    ret = "test event3";
    sdkbox::PluginFlurryAnalytics::logEvent(ret, true);
    sdkbox::PluginFlurryAnalytics::endTimedEvent(ret);

    ret = "test event4";
    params.clear();
    params.insert(std::make_pair("eKey3", "eVal3"));
    params.insert(std::make_pair("eKey4", "eVal4"));
    sdkbox::PluginFlurryAnalytics::logEvent(ret, params, true);
    sdkbox::PluginFlurryAnalytics::endTimedEvent(ret, params);

    ret = "error test";
    std::string msg = "log errror msg";
    std::string ifno = "log error info";
    sdkbox::PluginFlurryAnalytics::logError(ret, msg, ifno);

    sdkbox::PluginFlurryAnalytics::logPageView();

    ret = "this is user id";
    sdkbox::PluginFlurryAnalytics::setUserID(ret);
    sdkbox::PluginFlurryAnalytics::setAge(11);
    ret = "m"; // m:male  f:female  u:unkonw
    sdkbox::PluginFlurryAnalytics::setGender(ret);

    sdkbox::PluginFlurryAnalytics::pauseBackgroundSession();

    sdkbox::PluginFlurryAnalytics::setReportLocation(true);

    sdkbox::PluginFlurryAnalytics::clearLocation();
    //chendu, sichuan, china
    sdkbox::PluginFlurryAnalytics::setLatitude(104.06, 30.67, 0, 0);

    sdkbox::PluginFlurryAnalytics::setSessionReportsOnCloseEnabled(true);
    sdkbox::PluginFlurryAnalytics::setSessionReportsOnPauseEnabled(true);
    sdkbox::PluginFlurryAnalytics::setBackgroundSessionEnabled(true);

    sdkbox::PluginFlurryAnalytics::setEventLoggingEnabled(true);
    sdkbox::PluginFlurryAnalytics::setPulseEnabled(true);

    sdkbox::PluginFlurryAnalytics::endSession();

    CCLOG("Flurry analytics send data finish");

    return  true;
}
class FAListener : public sdkbox::FlurryAnalyticsListener {

public:
    void flurrySessionDidCreateWithInfo(std::map<std::string, std::string>& info)
    {
        CCLOG("FlurryAnalytics callback entry");
        CCLOG("MAP INFO BEGIN");
        for (auto item : info) {
            CCLOG("Item %s : %s", item.first.c_str(), item.second.c_str());
        }
        CCLOG("MAP INFO END");
    }
};

void MyPluginsMgr::initFlurry()
{
    bool bInit = sdkbox::PluginFlurryAnalytics::init();
    if (!bInit) {
        CCLOG(">>> FAIL! init flurry analytics fail<<<");
        return ;
    }

    //must call befor start session
    std::string ret = sdkbox::PluginFlurryAnalytics::getFlurryAgentVersion();
    CCLOG("FlurryVersion: %s", ret.c_str());
    sdkbox::PluginFlurryAnalytics::setShowErrorInLogEnabled(true);

    CCLOG("invoke set listener");
    sdkbox::FlurryAnalyticsListener *listener = new FAListener();
    sdkbox::PluginFlurryAnalytics::setListener(listener);

}

void MyPluginsMgr::flurryFunc(float)
{
    sdkbox::PluginFlurryAnalytics::startSession();
    flurryAnalyticsSendData();
}


// googleanalytics

void MyPluginsMgr::initGoogleAnalytics()
{
    PluginGoogleAnalytics::init();

}

void MyPluginsMgr::googleFunc(float)
{
    CCLOG("[GoogleAnalytics] sending data");

    PluginGoogleAnalytics::logTiming("Startup", 0, "timing name", "timing label");
    PluginGoogleAnalytics::logEvent("EventCategory 1", "EventAction 1", "EventLabel 1", 10);
    PluginGoogleAnalytics::logScreen("Screen1");
    PluginGoogleAnalytics::logEvent("Read", "Press", "Button1", 10);
    PluginGoogleAnalytics::logEvent("Read", "Press", "Button2", 20);
    PluginGoogleAnalytics::logEvent("Dispose", "Release", "Button22", 20);
    PluginGoogleAnalytics::logScreen("Screen2");
    PluginGoogleAnalytics::logSocial("twitter", "retweet", "retweet esto fu.");
    PluginGoogleAnalytics::logException("Algo se ha roto", false);
    PluginGoogleAnalytics::dispatchPeriodically(60);
}


// IAP

class IAPListenerDemo : public sdkbox::IAPListener
{
public:
    IAPListenerDemo()
    {
        Product test;
        test.name = "remove_ads";

        _products.push_back(test);
        updateIAP(_products);
    }

    // a selector callback
    void onShowAds(cocos2d::Ref* sender)
    {
        CCLOG("Show Ads");
    }
    void onRequestIAP(cocos2d::Ref* sender)
    {
        IAP::refresh();
    }
    void onRestoreIAP(cocos2d::Ref* sender)
    {
        IAP::restore();
    }
    void onIAP(cocos2d::Ref* sender)
    {
        auto btn = static_cast<Node*>(sender);
        Product* p = (Product*)btn->getUserData();

        CCLOG("Start IAP %s", p->name.c_str());
        IAP::purchase(p->name);
    }

private:

    void updateIAP(const std::vector<sdkbox::Product>& products)
    {

    }

    virtual void onSuccess(sdkbox::Product const& p) override
    {
    }

    virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override
    {

    }

    virtual void onCanceled(sdkbox::Product const& p) override
    {

    }

    virtual void onRestored(sdkbox::Product const& p) override
    {

    }

    virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override
    {

    }

    virtual void onProductRequestFailure(const std::string &msg) override
    {

    }

    virtual void onInitialized(bool ok)
    {

    }

    virtual void onRestoreComplete(bool ok, const std::string &msg)
    {

    }

    std::vector<sdkbox::Product> _products;
};

void MyPluginsMgr::initIAP()
{
    IAP::init();
    IAP::setDebug(true);
    IAP::setListener(new IAPListenerDemo);

}

void MyPluginsMgr::iapFunc(float)
{
    CCLOG("[IAP] Making purchase");
    IAP::purchase("remove_ads");
}


// kochava

void MyPluginsMgr::initKochava()
{
    PluginKochava::init();

    PluginKochava::trackEvent("KochavaCustomEvent", "HelloWorld");
}

void MyPluginsMgr::kochavaFunc(float)
{
    auto callback = [](const std::map<std::string, std::string>* attribution)
    {
        if (attribution)
        {
            typedef std::map<std::string, std::string> map_type;
            const map_type& m = *attribution;

            for (map_type::const_iterator it = m.begin(); it != m.end(); ++it)
            {
                const map_type::value_type& kv = *it;
                printf("[kochava] %s -> %s", kv.first.c_str(), kv.second.c_str());
            }
        }
    };

    PluginKochava::setAttributionCallback(callback);

    sdkbox::PluginKochava::trackEvent("KochavaCustomEvent", "HelloWorld");
    sdkbox::PluginKochava::spatialEvent("test", 100, 101, 102);

}


// Tune

class TuneListenerDemo : public sdkbox::TuneListener
{
public:
    void onMobileAppTrackerEnqueuedActionWithReferenceId(const std::string &referenceId) override
    {
        CCLOG("%s: %s", __FUNCTION__, referenceId.data());
    }
    void onMobileAppTrackerDidSucceedWithData(const std::string &data) override
    {
        CCLOG("%s: %s", __FUNCTION__, data.data());
    }
    void onMobileAppTrackerDidFailWithError(const std::string &errorString) override
    {
        CCLOG("%s: %s", __FUNCTION__, errorString.data());
    }
    void onMobileAppTrackerDidReceiveDeeplink(const std::string &deeplink, bool timeout) override
    {
        CCLOG("%s: %s", __FUNCTION__, deeplink.data());
    }

    void onMobileAppTrackerDidFailDeeplinkWithError(const std::string &errorString)
    {
        CCLOG("%s: %s", __FUNCTION__, errorString.c_str());
    }
};

static void testTuneMeasureEvent()
{
    // https://developers.mobileapptracking.com/event-function-templates/
    {
        PluginTune::measureEventName("purchase");
        PluginTune::measureEventId(1122334455);

        TuneEvent event;
        event.eventName = "purchase2";
        event.refId     = "RJ1357";
        event.searchString = "sweet srisp red apples";
        event.attribute1 = "srisp";
        event.attribute2 = "red";
        event.quantity = 3;
        PluginTune::measureEvent(event);
    }

    {
        TuneEventItem item1;
        item1.item = "ball1";
        item1.unitPrice = 3.99;
        item1.quantity = 2;

        TuneEventItem item2;
        item2.item = "ball2";
        item2.unitPrice = 9.99;
        item2.quantity = 1;
        item2.revenue = 9.99;
        item2.attribute1 = "red";
        item2.attribute2 = "inflatable";


        PluginTune::setUserId("US13579");
        PluginTune::setFacebookUserId("321321321321");
        PluginTune::setGoogleUserId("11223344556677");
        PluginTune::setTwitterUserId("1357924680");
        PluginTune::setLatitude(9.142276, -79.724052, 15);

        TuneEvent event;
        event.eventName = "purchase";
        event.eventItems.push_back(item1);
        event.eventItems.push_back(item2);
        event.refId = "ref13571";
        event.revenue = 13.97;
        event.currencyCode = "USD";

        PluginTune::measureEvent(event);

    }

    // https://developers.mobileapptracking.com/settings-for-pre-loaded-apps/
    {
        TunePreloadData pd;
        pd.publisherId = "112233";
        pd.offerId = "offer_id";
        pd.agencyId = "agency_id";
        pd.publisherReferenceId = "publisher_ref_id";
        pd.publisherSub1 = "pub_sub1";
        pd.publisherSub2 = "pub_sub2";
        pd.publisherSub3 = "pub_sub3";
        pd.publisherSub4 = "pub_sub4";
        pd.publisherSub5 = "pub_sub5";
        pd.publisherSubAd = "pub_sub_ad";
        pd.publisherSubAdgroup = "pub_sub_adgroup";
        pd.publisherSubCampaign = "pub_sub_campaign";
        pd.publisherSubKeyword = "pub_sub_keyword";
        pd.publisherSubPublisher = "pub_sub_publisher";
        pd.publisherSubSite = "pub_sub_site";
        pd.advertiserSubAd = "ad_sub_ad";
        pd.advertiserSubAdgroup = "ad_sub_adgroup";
        pd.advertiserSubCampaign = "ad_sub_campaign";
        pd.advertiserSubKeyword = "ad_sub_keyword";
        pd.advertiserSubPublisher = "ad_sub_publisher";
        pd.advertiserSubSite = "ad_sub_site";

        PluginTune::setPreloadData(pd);
        PluginTune::measureSession();

    }
}

void MyPluginsMgr::initTune()
{
    PluginTune::init();
    //PluginTune::setPackageName("your.package.name");
    PluginTune::setListener(new TuneListenerDemo);
    PluginTune::measureSession();
}

void MyPluginsMgr::tuneFunc(float)
{
    //PluginTune::setAllowDuplicateRequests(true);
    PluginTune::checkForDeferredDeeplinkWithTimeout(60);
    PluginTune::automateIapEventMeasurement(true);
    PluginTune::setCurrencyCode("RMB");
    PluginTune::setUserEmail("natalie@somedomain.com");
    PluginTune::setUserName("natalie123");
    PluginTune::setAge(43);
    PluginTune::setGender(PluginTune::GenderFemale);
    PluginTune::setUserId("US13579");
    PluginTune::setFacebookUserId("321321321321");
    PluginTune::setGoogleUserId("11223344556677");
    PluginTune::setTwitterUserId("1357924680");
    PluginTune::setLatitude(9.142276, -79.724052, 15);
    PluginTune::setAppAdTracking(true);
    PluginTune::measureEventName("login");

    testTuneMeasureEvent();
}


// agecheq

class ACListener : public sdkbox::AgeCheqListener {
public:
    void checkResponse(const std::string& rtn,
                       const std::string& rtnmsg,
                       int apiversion,
                       int checktype,
                       bool appauthorized,
                       bool appblocked,
                       int parentverified,
                       bool under13,
                       bool under18,
                       bool underdevage,
                       int trials);

    void associateDataResponse(const std::string& rtn,
                               const std::string& rtnmsg);

};

void ACListener::checkResponse(const std::string &rtn, const std::string &rtnmsg, int apiversion, int checktype, bool appauthorized, bool appblocked, int parentverified, bool under13, bool under18, bool underdevage, int trials) {
    CCLOG("AgeCheq listener checkResponse rtn:%s, rtnmsg:%s, apiversion:%d, checktype:%d, appauthorized:%d, appblocked:%d, parentverifed:%d, under13:%d, under18:%d, underdevage:%d, trials:%d", rtn.c_str(), rtnmsg.c_str(), apiversion, checktype, appauthorized, appblocked, parentverified, under13, under18, underdevage, trials);
}

void ACListener::associateDataResponse(const std::string &rtn, const std::string &rtnmsg) {
    CCLOG("AgeCheq listener associateDataResponse rtn:%s, rtnmsg:%s", rtn.c_str(), rtnmsg.c_str());
}

void MyPluginsMgr::initAgeCheq()
{
    sdkbox::PluginAgeCheq::init();
    sdkbox::PluginAgeCheq::setListener(new ACListener());

}

void MyPluginsMgr::agecheqFunc(float)
{
    CCLOG("[agecheq] check 1426");
    sdkbox::PluginAgeCheq::check("1426");

    CCLOG("associateData 1426, ikfill");
    sdkbox::PluginAgeCheq::associateData("1426", "ikfill");
}


// facebook

class MyFacebookListener : public FacebookListener
{
public:
    MyFacebookListener(){}

    void onLogin(bool isLogin, const std::string& error)
    {
        CCLOG("##FB isLogin: %d, error: %s", isLogin, error.c_str());
        std::string title = "login ";
        title.append((isLogin ? "success" : "failed"));
        MessageBox(error.c_str(), title.c_str());
    }
    void onAPI(const std::string& tag, const std::string& jsonData)
    {
        CCLOG("##FB onAPI: tag -> %s, json -> %s", tag.c_str(), jsonData.c_str());
    }
    void onSharedSuccess(const std::string& message)
    {
        CCLOG("##FB onSharedSuccess:%s", message.c_str());

        MessageBox(message.c_str(), "share success");
    }
    void onSharedFailed(const std::string& message)
    {
        CCLOG("##FB onSharedFailed:%s", message.c_str());

        MessageBox(message.c_str(), "share failed");
    }
    void onSharedCancel()
    {
        CCLOG("##FB onSharedCancel");

        MessageBox("", "share cancel");
    }
    void onPermission(bool isLogin, const std::string& error)
    {
        CCLOG("##FB onPermission: %d, error: %s", isLogin, error.c_str());

        std::string title = "permission ";
        title.append((isLogin ? "success" : "failed"));
        MessageBox(error.c_str(), title.c_str());
    }
    void onFetchFriends(bool ok, const std::string& msg)
    {
        CCLOG("##FB %s: %d = %s", __FUNCTION__, ok, msg.data());

        const std::vector<sdkbox::FBGraphUser>& friends = PluginFacebook::getFriends();
        for (int i = 0; i < friends.size(); i++)
        {
            const sdkbox::FBGraphUser& user = friends.at(i);
            CCLOG("##FB> -------------------------------");
            CCLOG("##FB>> %s", user.uid.data());
            CCLOG("##FB>> %s", user.firstName.data());
            CCLOG("##FB>> %s", user.lastName.data());
            CCLOG("##FB>> %s", user.name.data());
            CCLOG("##FB>> %s", user.isInstalled ? "app is installed" : "app is not installed");
            CCLOG("##FB");
        }

        MessageBox("", "fetch friends");
    }
};

void MyPluginsMgr::initFacebook()
{
    PluginFacebook::init();
    PluginFacebook::setListener(new MyFacebookListener);
}

void MyPluginsMgr::facebookFunc(float)
{

}

// fyber
//
class MyFyberListener : public FyberListener
{
private:
    string BOOL_TO_STRING(bool ok) {
        return ok ? "yes" : "no";
    }
public:
    void onVirtualCurrencyConnectorFailed(int error,
                                          const std::string& errorCode,
                                          const std::string& errorMsg)
    {
        CCLOG("[Fyber] onVirtualCurrencyConnectorFailed: error(%d)", error);
        CCLOG("[Fyber] onVirtualCurrencyConnectorFailed: errorCode(%s)", errorCode.data());
        CCLOG("[Fyber] onVirtualCurrencyConnectorFailed: errorMsg(%s)", errorMsg.data());
    }
    void onVirtualCurrencyConnectorSuccess(double deltaOfCoins,
                                           const std::string& currencyId,
                                           const std::string& currencyName,
                                           const std::string& transactionId)
    {
        CCLOG("[Fyber] onVirtualCurrencyConnectorSuccess: deltaOfCoins(%lf)", deltaOfCoins);
        CCLOG("[Fyber] onVirtualCurrencyConnectorSuccess: currencyId(%s)", currencyId.data());
        CCLOG("[Fyber] onVirtualCurrencyConnectorSuccess: currencyName(%s)", currencyName.data());
        CCLOG("[Fyber] onVirtualCurrencyConnectorSuccess: transactionId(%s)", transactionId.data());
    }
    void onCanShowInterstitial(bool canShowInterstitial)
    {
        CCLOG("[Fyber] onCanShowInterstitial: canShowInterstitial(%s)",
              BOOL_TO_STRING(canShowInterstitial).c_str());

        if (canShowInterstitial)
        {
            PluginFyber::showInterstitial();
        }
    }
    void onInterstitialDidShow()
    {
        CCLOG("[Fyber] onInterstitialDidShow");
    }
    void onInterstitialDismiss(const std::string& reason)
    {
        CCLOG("[Fyber] onInterstitialDismiss: reason(%s)", reason.data());
    }
    void onInterstitialFailed()
    {
        CCLOG("[Fyber] onInterstitialFailed");
    }

    void onBrandEngageClientReceiveOffers(bool areOffersAvailable)
    {
        CCLOG("[Fyber] onBrandEngageClientReceiveOffers: available(%s)",
              BOOL_TO_STRING(areOffersAvailable).c_str());
        if (areOffersAvailable)
        {
            PluginFyber::showOffers();
        }
    }
    void onBrandEngageClientChangeStatus(int status, const std::string& msg)
    {
        CCLOG("[Fyber] onBrandEngageClientChangeStatus: status(%d)", status);
        CCLOG("[Fyber] onBrandEngageClientChangeStatus: message(%s)", msg.data());
    }

    void onOfferWallFinish(int status)
    {
        CCLOG("[Fyber] onOfferWallFinish: status(%d)", status);
    }
};

void MyPluginsMgr::initFyber()
{
    PluginFyber::init();
    PluginFyber::setListener(new MyFyberListener);
}

void MyPluginsMgr::fyberFunc(float)
{
    CCLOG("[Fyber] Calling fyber apis.");
    PluginFyber::requestInterstitial();
    PluginFyber::showOfferWall("rmb");
    PluginFyber::showOfferWall("rmb");
    PluginFyber::requestDeltaOfCoins("rmb");
}

// Review

class MyRVListener : public sdkbox::ReviewListener {
public:
    virtual void onDisplayAlert() override;
    virtual void onDeclineToRate() override;
    virtual void onRate() override;
    virtual void onRemindLater() override;
};

void MyRVListener::onDisplayAlert() {
    CCLOG("Review listener didDisplayAlert");
}

void MyRVListener::onDeclineToRate() {
    CCLOG("Review listener didDeclineToRate");
}

void MyRVListener::onRate() {
    CCLOG("Review listener didToRate");
}

void MyRVListener::onRemindLater() {
    CCLOG("Review listener didToRemindLater");
}

void MyPluginsMgr::initReview()
{
    PluginReview::init();
    PluginReview::setListener(new MyRVListener);
}

void MyPluginsMgr::reviewFunc(float)
{
    CCLOG("[Review] Calling review plugin apis.");
    PluginReview::show();
    //PluginReview::show(true);
}

// method of MyPluginsMgr

MyPluginsMgr::MyPluginsMgr()
{
}

MyPluginsMgr *MyPluginsMgr::getInstance()
{
    static MyPluginsMgr *instance = 0;
    if (!instance)
    {
        instance = new MyPluginsMgr();
    }
    return instance;
}

bool MyPluginsMgr::init()
{
    initAdColony();
    initChartBoost();
    initFlurry();
    initGoogleAnalytics();
    initIAP();
    initKochava();
    initTune();
    initVungle();
    initFacebook();
    initAgeCheq();
    initFyber();
    initReview();

    return true;
}
