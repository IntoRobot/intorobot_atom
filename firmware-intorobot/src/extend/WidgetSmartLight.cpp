#include "WidgetSmartLight.h"


WidgetSmartLight::WidgetSmartLight(uint8_t ucItem)
{
    _Item=ucItem;
    memset(pCmdSwitchTopic,0,sizeof(pCmdSwitchTopic));
    memset(pDataStatusTopic,0,sizeof(pDataStatusTopic));
    sprintf(pCmdSwitchTopic,"channel/smartLight_%d/cmd/switch",_Item);    //智能灯控件控制命令topic
    sprintf(pDataStatusTopic,"channel/smartLight_%d/data/status",_Item);  //智能灯控件状态数据topic
}

WidgetSmartLight::~WidgetSmartLight()
{

}

void WidgetSmartLight::begin(void (*UserCallBack)(void))
{
    _EventCb=UserCallBack;
    IntoRobot.subscribe(pCmdSwitchTopic, NULL, this);
}

uint8_t WidgetSmartLight::getSwitch(void)
{
    return _SwitchKey;
}

void WidgetSmartLight::displayStatus(uint8_t ucVal)
{
    IntoRobot.publish(pDataStatusTopic,ucVal);
}

void WidgetSmartLight::control(uint8_t ucPin, uint8_t ucVal)
{
    pinMode(ucPin,OUTPUT);
    digitalWrite(ucPin, ucVal);
    displayStatus(ucVal);
}

void WidgetSmartLight::widgetBaseCallBack(uint8_t *payload, uint32_t len)
{
    if(payload[0] == '1')
    {
        _SwitchKey = ON;
    }
    else
    {
        _SwitchKey = OFF;
    }
    _EventCb();
}
