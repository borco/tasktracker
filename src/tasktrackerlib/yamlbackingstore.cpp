/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "yamlbackingstore.h"

#include "yaml-cpp/yaml.h" // IWYU pragma: keep

namespace tasktrackerlib {

YamlBackingStore::YamlBackingStore()
{
}

YamlBackingStore::~YamlBackingStore()
{
}

void YamlBackingStore::loadFromData(const QByteArray &data)
{
    YAML::Node node = YAML::Load(data.toStdString());
    loadFromYaml(node);
}

} // tasktrackerlib
