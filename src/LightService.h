#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "LightProperty.h"
#include "LightAction.h"
#include "LightClient.h"
#include "LightSender.h"
#include <WebSocketsServer.h>
#include "LightDefines.h"

#define MAX_CLIENTS 5

class Device;

struct PropertyNode
{
    Property *property;
    PropertyNode *next;
};

struct ActionNode
{
    Action *action;
    ActionNode *next;
};

class Service
{
public:
    Service(String id, std::vector<const char *> types, String description);

    void update(Sender *sender);

    void addProperty(Property &property);
    void addAction(const char *id, std::vector<const char *> types, const char *description, void (*handler)(ActionStatus *actionStatus, JsonVariant data));
    void createJSONDescription(JsonObject jsonObject);
    void interpretMessage(HClient &client, Sender *sender, JsonObject &json);

    void setDevice(Device *device)
    {
        this->device = device;
    }

    String getId()
    {
        return id;
    }

private:
    String id;
    std::vector<const char *> types;
    int typesLength;
    String description;

    PropertyNode *propertyList;
    ActionNode *actionList;

    Device *device;

    Action *findActionWithId(String id);
    Property *findPropertyWithId(String id);
    DynamicJsonDocument prepareMessage(int capacity, String type);
};