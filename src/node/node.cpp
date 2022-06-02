#include "node.h"

#include <utility>

#include "homie.h"
Node::Node(const char* name, const char* id, Device* device) {
    id_ = id;
    name_ = name;
    device_ = device;
    device->AddNode(this);
}

bool Node::Init(Homie* homie) {
    Serial.print("Node::Init: ");
    Serial.println(name_);

    bool status = true;

    homie_ = homie;
    if (!homie->Publish(*this, "name", name_, true)) status = false;
    if (!homie->Publish(*this, "state", state_, true)) status = false;

    for (auto it = begin(properties_); it != end(properties_); ++it) {
        if (!(*it->second).Init(homie_)) status = false;
    }

    if (!status) Serial.printf("Init node %s failed\r\n", name_.c_str());

    return status;
}

bool Node::Subscribe(Homie* homie) {
    Serial.print("Node::Subscribe: ");
    Serial.println(name_);
    homie_ = homie;

    for (auto it = begin(properties_); it != end(properties_); ++it) {
        if (!(*it->second).Subscribe(homie_)) {
            Serial.printf("Subscription to %s failed!\n", (*it->second).GetId());
            return false;
        }
    }
    return true;
}

void Node::AddProperty(Property* property) {
    properties_.insert(std::pair<String, Property*>(property->GetId(), property));
}

String Node::GetId() const { return id_; }
Device* Node::GetDevice() const { return this->device_; }

Property* Node::GetProperty(String id) { return properties_.find(id)->second; }

void Node::HandleCurrentState() {
    for (auto it = begin(properties_); it != end(properties_); ++it) {
        (*it->second).HandleCurrentState();
    }
}
