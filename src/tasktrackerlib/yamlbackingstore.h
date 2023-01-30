/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include <QByteArray>

namespace YAML {
class Emitter;
class Node;
}

namespace tasktrackerlib {

class YamlBackingStore
{
public:
    void loadFromData(const QByteArray& data);
    virtual void loadFromYaml(const YAML::Node &node) = 0;
    virtual void saveToYaml(YAML::Emitter& out) const = 0;

protected:
    YamlBackingStore();
    virtual ~YamlBackingStore();
};

} // tasktrackerlib
