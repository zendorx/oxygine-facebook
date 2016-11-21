#include "facebook.h"

#ifdef __ANDROID__
#include "android/AndroidFacebook.h"

#elif __APPLE__
#include <TargetConditionals.h>
#include "ios/iosFacebook.h"
#else
#include "sim/FacebookSimulator.h"
#endif



#define FB_EXT_ENABLED 1

namespace facebook
{

    spEventDispatcher _dispatcher;

    spEventDispatcher dispatcher()
    {
        return _dispatcher;
    }

    void init()
    {
        log::messageln("facebook::init");
        OX_ASSERT(_dispatcher == 0);
        _dispatcher = new EventDispatcher;


#if !FB_EXT_ENABLED
        return;
#endif

#ifdef __ANDROID__
        jniFacebookInit();
#elif TARGET_OS_IPHONE

#else
        facebookSimulatorInit();
#endif
        log::messageln("facebook::init done");
    }

    void free()
    {
#if !FB_EXT_ENABLED
        return;
#endif

        log::messageln("facebook::free");

        OX_ASSERT(_dispatcher);

#ifdef __ANDROID__
        jniFacebookFree();
#endif
        _dispatcher->removeAllEventListeners();
        _dispatcher = 0;
        log::messageln("facebook::free done");
    }

    void login()
    {
#if !FB_EXT_ENABLED
        return;
#endif
        log::messageln("facebook::login");

#ifdef __ANDROID__
        jniFacebookLogin();
#elif __APPLE__
        iosFacebookLogin();
#else
        facebookSimulatorLogin();
#endif
        log::messageln("facebook::login done");
    }

    void logout()
    {
#if !FB_EXT_ENABLED
        return;
#endif
        log::messageln("facebook::logout");

#ifdef __ANDROID__
        jniFacebookLogout();
#elif __APPLE__
        iosFacebookLogout();
#else
        facebookSimulatorLogout();
#endif
        log::messageln("facebook::logout done");
    }

    bool appInviteDialog(const string& appLinkUrl, const string& previewImageUrl)
    {
#if !FB_EXT_ENABLED
        return false;
#endif
        log::messageln("facebook::AppInviteDialog");

#ifdef __ANDROID__
        return jniFacebookAppInviteDialog(appLinkUrl, previewImageUrl);
#elif TARGET_OS_IPHONE
#else
        return facebookSimulatorAppInviteDialog(appLinkUrl, previewImageUrl);
#endif
        return false;

    }

    void newMeRequest()
    {
#if !FB_EXT_ENABLED
        return;
#endif

        log::messageln("facebook::newMeRequest");

#ifdef __ANDROID__
        jniFacebookNewMeRequest();
#elif TARGET_OS_IPHONE
#else
        facebookSimulatorNewMeRequest();
#endif
        log::messageln("facebook::newMeRequest done");
    }

    void getFriends()
    {
#if !FB_EXT_ENABLED
        return;
#endif
        log::messageln("facebook::getFriends");

#ifdef __ANDROID__
        jniFacebookGetFriends();
#elif TARGET_OS_IPHONE
#else
        facebookSimulatorGetFriends();
#endif
        log::messageln("facebook::getFriends done");
    }

    bool isLoggedIn()
    {
#if !FB_EXT_ENABLED
        return false;
#endif
        log::messageln("facebook::isLoggined");

#ifdef __ANDROID__
        return jniFacebookIsLoggedIn();
#elif TARGET_OS_IPHONE
#else
        return facebookSimulatorIsLoggedIn();
#endif
        return false;
    }

    string getAccessToken()
    {
#if !FB_EXT_ENABLED
        return "";
#endif
        log::messageln("facebook::getAccessToken");

#ifdef __ANDROID__
        return jniFacebookGetAccessToken();
#elif TARGET_OS_IPHONE
        return iosFacebookGetAccessToken();
#else
        return facebookSimulatorGetAccessToken();
#endif
        return "";
    }

    string getUserID()
    {

#if !FB_EXT_ENABLED
        return "";
#endif
        log::messageln("facebook::getUserID");

#ifdef __ANDROID__
        return jniFacebookGetUserID();
#elif TARGET_OS_IPHONE
        return iosFacebookGetUserID();
#else
        return facebookSimulatorGetUserID();
#endif
        return "";
    }

    string getAppID()
    {

#if !FB_EXT_ENABLED
        return "";
#endif

#ifdef __ANDROID__
        return jniFacebookGetAppID();
#elif TARGET_OS_IPHONE
        return iosFacebookGetUserID();
#else
        return facebookSimulatorGetAppID();
#endif
        return "";

    }

    namespace internal
    {

        void newToken(const string& value)
        {
            log::messageln("facebook::internal::newToken %s", value.c_str());
            TokenEvent ev;
            ev.token = value;
            _dispatcher->dispatchEvent(&ev);
        }

        void loginResult(bool value)
        {
            log::messageln("facebook::internal::loginResult %d", value);
            LoginEvent ev;
            ev.isLoggedIn = value;
            _dispatcher->dispatchEvent(&ev);
        }


        /*
            {
                "id":"1035749669829946",
                "link" : "https:\/\/www.facebook.com\/app_scoped_user_id\/1035749669829946\/",
                "name" : "Denis Sachkov"
            }
        */
        void newMeRequestResult(const string& data, bool error)
        {
            log::messageln("facebook::internal::newMeRequestResult %s", data.c_str());

            NewMeRequestEvent event;
            Json::Reader reader;
            Json::Value root;
            bool parsingSuccessful = reader.parse(data.c_str(), root);     //parse process
            if (!parsingSuccessful || error)
            {
                event.error = true;
                log::messageln("newMeRequestResult error %s", error ? "response error" : "parse error");
                return;
            }
            else
            {
                event.id = root["id"].asCString();
                event.link = root["link"].asCString();
                event.name = root["name"].asCString();
            }

            _dispatcher->dispatchEvent(&event);
        }

        void newMyFriendsRequestResult(const string& data, bool error)
        {
            log::messageln("facebook::internal::newMyFriendsRequestResult %s", data.c_str());


        }
    }
}

