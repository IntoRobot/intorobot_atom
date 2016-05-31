/**
 *******************************************************************************
 * @file:       application.cpp
 * @author:  robin
 * @version: V1.0.0
 * @date:     30-November-2014
 * @brief:     the header of application.cpp
 *******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
 */

#include "application.h"
     
     
//SYSTEM_MODE(SEMI_AUTOMATIC);
//cmd
#define CMD_GRAPH_TOTALSETPINMODE "channel/coreCtrl/cmd/mode_bak"    //get the total pin mode
#define CMD_GRAPH_SETPINMODE "channel/coreCtrl/cmd/mode"    //get the total pin mode

#define CMD_GRAPH_TOTALSETPINDATA "channel/coreCtrl/cmd/write_bak"    //get the total pin set value
#define CMD_GRAPH_SETPINDATA "channel/coreCtrl/cmd/write"    //get the total pin mode

#define CMD_GRAPH_TOTALPINFBDATA "channel/coreCtrl/cmd/getread"     //get the total pin feedback value

//data
#define DATA_GRAPH_PINFBDATA "channel/coreCtrl/data/read" //realtime changed value

#define DIGITMAXNUM      16
#define ANALOGMAXNUM     25

#define ANALOGDIFF       20


//digit pin mode
u8 DMode[DIGITMAXNUM]={0};
//digit pin data last
s32 DDataLast[DIGITMAXNUM]={0};

//analog pin mode  
u8 AMode[ANALOGMAXNUM]={0};
//analog pin data last
s32 ADataLast[ANALOGMAXNUM]={0};

aJsonClass aJson;

void CmdGraphTotalSetPinModeCb(uint8_t * payload, uint32_t len);
void CmdGraphSetPinModeCb(uint8_t * payload, uint32_t len);
void CmdGraphTotalSetPinDataCb(uint8_t * payload, uint32_t len);
void CmdGraphSetPinDataCb(uint8_t * payload, uint32_t len);
void CmdGraphTotalPinFbDataCb(uint8_t * payload, uint32_t len);
void GetPinFeedbackData(bool total);



void CmdGraphTotalSetPinModeCb(uint8_t * payload, uint32_t len)
{
    CmdGraphSetPinModeCb(payload,len);
    IntoRobot.unsubscribe(CMD_GRAPH_TOTALSETPINMODE, NULL);
    IntoRobot.subscribe(CMD_GRAPH_TOTALSETPINDATA, NULL, CmdGraphTotalSetPinDataCb);
}

void CmdGraphSetPinModeCb(uint8_t * payload, uint32_t len)
{
    u32 i,num,pinnum;
    String tmp;

    for(i=0; i<len; i++)
    {tmp+=(char)payload[i];}
    
    aJsonObject *root = aJson.parse((char *)tmp.c_str());
    if (root == NULL) 
    {return;}

    aJsonObject* Item_Object;
    num=aJson.getArraySize(root);
    for(i=0; i<num; i++)
    {
        Item_Object=aJson.getArrayItem(root, i);
        if (Item_Object == NULL) 
        {return;}
        pinnum=atoi(&Item_Object->name[1]);

        if(Item_Object->valueint>4)
        {continue;}
        switch(Item_Object->name[0])
        {
            case 'D':
                if(pinnum>=DIGITMAXNUM)
                {continue;}
                DMode[pinnum]=Item_Object->valueint;
                if((Item_Object->valueint!=1)&&(Item_Object->valueint!=3))
                {
                    DDataLast[pinnum]=-1;
                }
                break;
            case 'A':
                if(pinnum>=ANALOGMAXNUM)
                {continue;}
                AMode[pinnum]=Item_Object->valueint;
                if((Item_Object->valueint!=1)&&(Item_Object->valueint!=3))
                {
                    ADataLast[pinnum]=-1;
                }
                pinnum+=30;
                break;
            default:
                continue;
                break;
        }
        
        switch(Item_Object->valueint)
        {
            case 1: //digit read
                pinMode(pinnum,INPUT_PULLDOWN);
                break;
            case 3: //analog read
                pinMode(pinnum,AN_INPUT);
                break;
            case 2: //digit write
            case 4: //analog write
            default:
                pinMode(pinnum,OUTPUT);
                break;
        }
    }
    aJson.deleteItem(root);
}

void CmdGraphTotalSetPinDataCb(uint8_t * payload, uint32_t len)
{
    CmdGraphSetPinDataCb(payload, len);
    IntoRobot.unsubscribe(CMD_GRAPH_TOTALSETPINDATA, NULL);
    IntoRobot.subscribe(CMD_GRAPH_SETPINMODE, NULL, CmdGraphSetPinModeCb);
    IntoRobot.subscribe(CMD_GRAPH_SETPINDATA, NULL, CmdGraphSetPinDataCb);
}

void CmdGraphSetPinDataCb(uint8_t * payload, uint32_t len)
{
    u32 i,num,pinnum;
    String tmp;

    for(i=0; i<len; i++)
    {tmp+=(char)payload[i];}
    
    aJsonObject *root = aJson.parse((char *)tmp.c_str());
    if (root == NULL) 
    {return;}

    aJsonObject* Item_Object;
    num=aJson.getArraySize(root);
    for(i=0; i<num; i++)
    {
        Item_Object=aJson.getArrayItem(root, i);
        if (Item_Object == NULL) 
        {return;}
        pinnum=atoi(&Item_Object->name[1]);
        switch(Item_Object->name[0])
        {
            case 'D':
                if(pinnum>=DIGITMAXNUM)
                {continue;}
                if(Item_Object->valueint>1)
                {continue;}
                if(DMode[pinnum]==2)       //digit write
                {
                    digitalWrite(pinnum, Item_Object->valueint);
                }
                else if(DMode[pinnum]==4)  //analog write
                {
                    analogWrite(pinnum, Item_Object->valueint);
                }
                break;
            case 'A':
                if(pinnum>=ANALOGMAXNUM)
                {continue;}
                if(Item_Object->valueint>255)
                {continue;}
                if(AMode[pinnum]==2)       //digit write
                {
                    analogWrite(pinnum+30, Item_Object->valueint);
                }
                else if(AMode[pinnum]==4)  //analog write
                {
                    analogWrite(pinnum+30, Item_Object->valueint);
                }
                break;
            default:
                continue;
                break;
        }
    }
    aJson.deleteItem(root);
}

void CmdGraphTotalPinFbDataCb(uint8_t * payload, uint32_t len)
{
    GetPinFeedbackData(true);
}

void GetPinFeedbackData(bool total)
{
    char temp[16];
    int i;
    s32 value,diff;

    aJsonObject* root = aJson.createObject();
    if (root == NULL) 
    {return;}
    
    //digit  
    for(i=0; i<DIGITMAXNUM; i++)
    {
        switch(DMode[i])
        {
            case 1://digit read
                value=digitalRead(i);
                if((total==true)||(value!=DDataLast[i]))
                {
                    DDataLast[i]=value;
                    memset(temp,0,sizeof(temp));
                    sprintf(temp,"D%d",i);
                    aJson.addNumberToObject(root, temp, (int)value);
                } 
                break;
            default:
                break;
        }
    }
    //analog
    for(i=0; i<ANALOGMAXNUM; i++)
    {
        switch(AMode[i])
        {
            case 1: //digit read
                value=digitalRead(i+30);
                if((total==true)||(value!=ADataLast[i]))
                {
                    ADataLast[i]=value;
                    memset(temp,0,sizeof(temp));
                    sprintf(temp,"A%d",i);
                    aJson.addNumberToObject(root, temp, (int)value);
                }
                break;
                
            case 3: //analog read
                value=analogRead(i+30);
                if(value>ADataLast[i])
                {diff=value-ADataLast[i];}
                else
                {diff=ADataLast[i]-value;}
                if((total==true)||(diff>ANALOGDIFF))
                {
                    ADataLast[i]=value;
                    memset(temp,0,sizeof(temp));
                    sprintf(temp,"A%d",i);
                    aJson.addNumberToObject(root, temp, (int)value);
                }
                break;
            default:
                break;
        }
    }

    if(aJson.getArraySize(root))
    {
        char* string = aJson.print(root);
        IntoRobot.publish(DATA_GRAPH_PINFBDATA, (uint8_t *)string,strlen(string));
        free(string);
    }
    aJson.deleteItem(root);
}


void setup() 
{
    s32 i=0;
    
    //-1 initial status
    for(i=0; i<DIGITMAXNUM; i++)
    {DDataLast[i]=-1;}
    
    for(i=0; i<ANALOGMAXNUM; i++)
    {ADataLast[i]=-1;}

    IntoRobot.subscribe(CMD_GRAPH_TOTALSETPINMODE, NULL, CmdGraphTotalSetPinModeCb);
}


void loop() 
{
    GetPinFeedbackData(false);
    delay(1000);
}

