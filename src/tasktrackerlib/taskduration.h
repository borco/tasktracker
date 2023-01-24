/*
    Copyright (C) 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#pragma once

#include "yamlbackingstore.h"

#include <QTime>

namespace YAML { class Node; }

namespace tasktrackerlib {

class TaskDuration : public YamlBackingStore
{
public:
    TaskDuration();

    void loadFromYaml(const YAML::Node &node) override;

    QTime start() const;
    void setStart(const QTime& time);

    QTime stop() const;
    void setStop(const QTime& time);

    int seconds() const;

private:
    QTime m_start;
    QTime m_stop;
    int m_seconds = 0;
};

} // namespace tasktrackerlib
