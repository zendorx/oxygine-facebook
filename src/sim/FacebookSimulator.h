#pragma once
#include <string>

using namespace std;


void facebookSimulatorInit();
void facebookSimulatorLogin();
void facebookSimulatorLogout();
void facebookSimulatorGetFriends();
bool facebookSimulatorIsLoggedIn();
void facebookSimulatorNewMeRequest();
bool facebookSimulatorAppInviteDialog(const string& appLinkUrl, const string& previewImageUrl);

std::string facebookSimulatorGetAccessToken();
std::string facebookSimulatorGetUserID();
std::string facebookSimulatorGetAppID();