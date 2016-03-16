#include "FacebookSimulator.h"
#include "facebook.h"


bool _is_logged_in = false;
string facebook_token = "CAANycbhXMg0BAMpzvMM7M8sTjnRghS5heVq3EatYJssa9TKSnZArS715tcVZBAIpLyactx5GPUiIAdOegDjvuFThLMzrw0SDZBMnnRXI2MyxKOZA5VyPdOH6EZBfg8G0tapYZAZC77NVDWwl8VdI0YFyhpWLQ3MsbBN7xdzF75S7U3CjZANZCeFvLuw9rHBlavHYCl05RS6myPdEWLBKlr7Ijll94lstdnLEYstn5sN8RggZDZD";

void facebookSimulatorLogin()
{
    _is_logged_in = true;
    facebook::internal::loginResult(true);
    facebook::internal::newToken(facebook_token);
}

void facebookSimulatorInit()
{
    log::messageln("Facebook Simulator Init");

}

void facebookSimulatorNewMeRequest()
{
    string data = "{\"id\":\"1035749669829946\",\"link\" : \"https:\/\/www.facebook.com\/app_scoped_user_id\/1035749669829946\/\",\"name\" : \"Denis Sachkov\"}";
    facebook::internal::newMeRequestResult(data, false);
}


void facebookSimulatorGetFriends()
{

}

bool facebookSimulatorAppInviteDialog(const string& appLinkUrl, const string& previewImageUrl)
{
    return false;
}

bool facebookSimulatorIsLoggedIn()
{
    return _is_logged_in;
}