#include "FacebookSimulator.h"
#include "facebook.h"
#include "json/json.h"
#include "core/file.h"
#include "Box9Sprite.h"
#include "TextField.h"
#include "DebugActor.h"
#include "res/Resources.h"
#include "Stage.h"
#include "core/oxygine.h"

bool _isLoggedIn = false;
string _facebookToken = "CAACk349LXq8BAEQqlvXMISPzBcsnE6uC5IDzrOJ9g5iDj7JAfqFO36ZC231gpigo1RFaZAZApPzUcPMu1ovCgZAUUAN0Tz0fk6ZBOxjtzzjOvYsJ4udSkXp3X7QSdaLCcawwvUr16pKB6IYpUMJkU9EWkWNL3YSDky5SCmUGXo5YH2cQxZCPqxFnqnqc7aZBwvr71D7IcY2vwZDZD";
string _userID = "10209410932054945";



DECLARE_SMART(Btn, spBtn);
class Btn : public Box9Sprite
{
public:
    Btn()
    {
        _txt = new TextField;
        _txt->setText("OK");
        _txt->setAlign(TextStyle::VALIGN_MIDDLE, TextStyle::HALIGN_CENTER);
        addChild(_txt);

        setColor(Color::Green);
        setResAnim(DebugActor::resSystem->getResAnim("btn"));

        addEventListener(TouchEvent::OVER, CLOSURE(this, &Btn::touch));
        addEventListener(TouchEvent::OUT, CLOSURE(this, &Btn::touch));
    }

    void setText(const string& txt)
    {
        _txt->setText(txt);
    }

    void touch(Event* ev)
    {
        if (ev->type == TouchEvent::OVER)
            setColor(Color::GreenYellow);
        if (ev->type == TouchEvent::OUT)
            setColor(Color::Green);
    }

    void sizeChanged(const Vector2& size)
    {
        _txt->setSize(size);
    }

    spTextField _txt;
};

DECLARE_SMART(FacebookDialog, spFacebookDialog);
class FacebookDialog : public Actor
{
public:
    enum
    {
        EVENT_OK = 12323,
        EVENT_CANCEL
    };

    FacebookDialog()
    {
        setPriority(9999);

        spActor blocker = new Actor;
        blocker->setPosition(-getStage()->getSize());
        blocker->setSize(getStage()->getSize() * 3);
        addChild(blocker);

        _bg = new Box9Sprite;
        addChild(_bg);

        _title = new TextField;
        _title->setAlign(TextStyle::VALIGN_MIDDLE, TextStyle::HALIGN_CENTER);
        _title->setMultiline(true);
        _title->setColor(Color::Black);
        addChild(_title);

        _btnOk = new Btn();
        _btnOk->setSize(70, 30);
        _btnOk->setText("Ok");
        addChild(_btnOk);

        _btnCancel = new Btn();
        _btnCancel->setSize(70, 30);
        _btnCancel->setText("Cancel");
        addChild(_btnCancel);
    }

    void setTitle(const string& txt)
    {
        _title->setText(txt);
    }

    void doRender(const RenderState& rs)
    {
        //Stage::render()
    }

    void sizeChanged(const Vector2& size)
    {
        _bg->setSize(size);

        Vector2 center = core::getDisplaySize().cast<Vector2>() / 2.0f;
        center = getStage()->global2local(center);

        float sx = getStage()->getScaleX();
        setPosition(center - size / sx / 2);

        _btnOk->setPosition(size - _btnOk->getSize() - Vector2(10, 10));
        _btnCancel->setPosition(10, getHeight() - 10 - _btnCancel->getHeight());
        _title->setWidth(getWidth());
        _title->setHeight(_btnCancel->getY());
    }

    spBox9Sprite        _bg;
    spTextField         _title;
    spBtn               _btnOk;
    spBtn               _btnCancel;
};


Json::Value _facebook(Json::objectValue);

void facebookSimulatorLogin()
{
    spFacebookDialog dialog = new FacebookDialog;
    dialog->setScale(1.0f / getStage()->getScaleX());
    dialog->setSize(500, 300);
    getStage()->addChild(dialog);

    dialog->_btnOk->addClickListener([ = ](Event * e)
    {

        dialog->detach();
        e->removeListener();
        _isLoggedIn = true;

        facebook::internal::loginResult(true);
    });

    dialog->_btnCancel->addClickListener([ = ](Event * e)
    {
        dialog->detach();
        e->removeListener();
    });


    //_is_logged_in = true;
    //facebook::internal::loginResult(true);
    //facebook::internal::newToken(_facebookToken);
}

void facebookSimulatorInit()
{
    log::messageln("Facebook Simulator Init");


    file::buffer bf;
    file::read(".facebook", bf, ep_ignore_error);

    if (!bf.empty())
    {
        Json::Reader reader;
        reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), _facebook, false);
    }
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
    return _isLoggedIn;
}

std::string facebookSimulatorGetAccessToken()
{
    return _facebookToken;
}

std::string facebookSimulatorGetUserID()
{
    return _userID;
}