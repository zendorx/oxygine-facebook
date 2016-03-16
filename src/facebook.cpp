#include "FacebookAdapter.h"

#ifdef __ANDROID__
#include "android/AndroidFacebook.h"
#else
#include "sim/FacebookSimulator.h"
#endif

#define FB_EXT_ENABLED 1

namespace facebook {

    spEventDispatcher _dispatcher;

    spEventDispatcher dispatcher()
    {
        return _dispatcher;
    }

    void init() {
#if !FB_EXT_ENABLED
		return;
#endif

        log::messageln("facebook::init");
        _dispatcher = new EventDispatcher;

#ifdef __ANDROID__
        jniFacebookInit();
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

#ifdef __ANDROID__
        jniFacebookFree();
#endif
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
#else
       facebookSimulatorLogin();
#endif
        log::messageln("facebook::login done");
    }

	bool appInviteDialog(const string& appLinkUrl, const string& previewImageUrl)
	{
#if !FB_EXT_ENABLED
		return false;
#endif
		log::messageln("facebook::AppInviteDialog");

#ifdef __ANDROID__
		return jniFacebookAppInviteDialog(appLinkUrl, previewImageUrl);
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
#else
        return facebookSimulatorIsLoggedIn();
#endif
        return false;
    }

    namespace internal {

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
		void newMeRequestResult(const string& data, bool error) {
			log::messageln("facebook::internal::newMeRequestResult %s", data.c_str());

            NewMeRequestEvent event;
			Json::Reader reader;
			Json::Value root;
			bool parsingSuccessful = reader.parse(data.c_str(), root);     //parse process
			if (!parsingSuccessful || error)
			{
                event.error = true;
				log::messageln("newMeRequestResult error" + error ? "response error" : "parse error" );
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

