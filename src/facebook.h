#pragma once

#include "EventDispatcher.h"
#include "Event.h"
#include "json/json.h"
#include <string>
#include <list>

using namespace std;
using namespace oxygine;

namespace facebook
{

    void init();
    void free();

    class NewMeRequestEvent : public Event
    {
    public:
        enum { EVENT = sysEventID('f', 'b', 'n') };
        NewMeRequestEvent() : Event(EVENT) {}

        string id;
        string link;
        string name;
        bool error = false;
    };

    class LoginEvent : public Event
    {
    public:
        enum { EVENT = sysEventID('f', 'b', 'l')};
        LoginEvent() : Event(EVENT) {}
        bool isLoggedIn = false;
    };

    class FriendsEvent : public Event
    {
        enum { EVENT = sysEventID('f', 'b', 'f')};
        FriendsEvent() : Event(EVENT) {}

        struct friend_Data
        {
            string name;
        };

        typedef list<friend_Data> friends_list;

        friends_list friends;
        bool error = false;

    };

    class TokenEvent : public Event
    {
    public:
        enum { EVENT = sysEventID('f', 'b', 't')};
        TokenEvent() : Event(EVENT) {};

        string token;
    };

    spEventDispatcher dispatcher();

    bool isLoggedIn();
    void login();
    void getFriends();
    void newMeRequest();
    bool appInviteDialog(const string& appLinkUrl, const string& previewImageUrl);

    string getAccessToken();
    string getUserID();

    namespace internal
    {
        void newMeRequestResult(const string& data, bool error);
        void loginResult(bool value);
        void newToken(const string& value);
        void newMyFriendsRequestResult(const string& data, bool error);
    }
};