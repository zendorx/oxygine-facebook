#pragma once

#include <string>

using namespace std;

void jniFacebookInit();
void jniFacebookFree();

bool jniFacebookIsLoggedIn();
void jniFacebookGetFriends();
void jniFacebookLogin();
void jniFacebookNewMeRequest();
bool jniFacebookAppInviteDialog(const string& appLinkUrl, const string& previewImageUrl);