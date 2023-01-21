/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "taskcount.h"

#include "qtyamlcppadapter/yamlhelper.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"

namespace {
static const char* DateYamlName = "date";
static const char* CountYamlName = "count";
}

namespace tasktrackerlib {

TaskCount::TaskCount(QObject *parent)
    : QObject{parent}
{
}

QDate TaskCount::date() const
{
    return m_date;
}

void TaskCount::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

int TaskCount::count() const
{
    return m_count;
}

void TaskCount::setCount(int newCount)
{
    if (m_count == newCount)
        return;
    m_count = newCount;
    emit countChanged();
}

void TaskCount::loadFromData(const QByteArray &data)
{
    YAML::Node node = YAML::Load(data.toStdString());
    loadFromYaml(node);
}

void TaskCount::loadFromYaml(const YAML::Node &node)
{
    using namespace qtyamlcppadapter;

    if (!node.IsMap() && !node.IsNull()) {
        qCritical() << "Task: yaml node is not a map";
        return;
    }

    setDate(dateFromYaml(node, DateYamlName, QDate()));
    setCount(intFromYaml(node, CountYamlName, 0));
}

} // namespace tasktrackerlib
