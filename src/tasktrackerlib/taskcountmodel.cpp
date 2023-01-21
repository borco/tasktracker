#include "taskcountmodel.h"

#include "taskcount.h"

#include "yaml-cpp/yaml.h" // IWYU pragma: keep

namespace {
static const char* CountsYamlNode = "counts";

enum Roles {
    Date = Qt::UserRole + 1,
    Count,
};
}

namespace tasktrackerlib {

TaskCountModel::TaskCountModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

TaskCountModel::~TaskCountModel()
{
    qDeleteAll(m_counts);
}

int TaskCountModel::size() const
{
    return m_counts.size();
}

TaskCount *TaskCountModel::get(int index) const
{
    return m_counts[index];
}

int TaskCountModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return size();
}

QHash<int, QByteArray> TaskCountModel::roleNames() const
{
    return {
        { Date, "date" },
        { Count, "count" },
    };
}

QVariant TaskCountModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto count = m_counts[index.row()];

    switch(role) {
    case Date:
        return count->date();
    case Count:
        return count->count();
    }

    return QVariant();
}

bool TaskCountModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

void TaskCountModel::loadFromData(const QByteArray &data)
{
    YAML::Node node = YAML::Load(data.toStdString());
    loadFromYaml(node);
}

void TaskCountModel::loadFromYaml(const YAML::Node &node)
{
    assert(node.IsMap() || node.IsNull());

    if (node.IsNull()) {
        clear();
        return;
    }

    auto counts_node = node[CountsYamlNode];
    if (!counts_node) {
        clear();
        return;
    }

    if (!counts_node.IsSequence()) {
        qCritical().nospace() << "TaskCountModel: '" << CountsYamlNode << "' is not a list";
        clear();
        return;
    }

    beginResetModel();
    qDeleteAll(m_counts);
    m_counts.clear();

    for (unsigned int i = 0; i < counts_node.size(); ++i) {
        auto count = new TaskCount(this);
        count->loadFromYaml(counts_node[i]);
        insertCount(i, count);
    }

    std::sort(m_counts.begin(), m_counts.end(), [](const TaskCount* e1, const TaskCount* e2) { return e1->date() < e2->date(); });

    endResetModel();
}

void TaskCountModel::insertCount(int row, TaskCount *count)
{
    beginInsertRows(QModelIndex(), row, row);
    m_counts.insert(row, count);
    endInsertRows();
}

void TaskCountModel::clear()
{
    beginResetModel();
    qDeleteAll(m_counts);
    m_counts.clear();
    endResetModel();
}

} // namespace tasktrackerlib
