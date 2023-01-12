/*
    Copyright 2023 by Ioan Calin Borcoman <iborco@gmail.com>
*/

#include "task.h"

using namespace tasktrackerlib;

Task::Task(QObject *parent)
    : QObject{parent}
{

}

void Task::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}
