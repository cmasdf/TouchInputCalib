/**
 * @file AppWindowData.h
 * @author Daniel Matthes
 * @date 09.12.2020
 */

#include <model/AppWindowModel.h>

int AppWindowModel::rowCount(const QModelIndex &parent) const {
    return m_listAppWindowData.count();
}

QVariant AppWindowModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    const AppWindowData &appWindowData = m_listAppWindowData[index.row()];

    switch (role) {
        case AppWindowDataTitleRole:
            return appWindowData.title();
        case AppWindowDataObjectNameRole:
            return appWindowData.objectName();
        case AppWindowDataDeviceInfoRole:
            return appWindowData.deviceInfo();
        case AppWindowDataWidthRole:
            return appWindowData.width();
        case AppWindowDataHeightRole:
            return appWindowData.height();
        case AppWindowDataXRole:
            return appWindowData.x();
        case AppWindowDataYRole:
            return appWindowData.y();
        default:
            return QVariant();
    }
}

void AppWindowModel::addAppWindowData(const AppWindowData &appWindowData) {
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));
    m_listAppWindowData << appWindowData;
    endInsertRows();
}

QHash<int, QByteArray> AppWindowModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[AppWindowDataTitleRole] = "title";
    roles[AppWindowDataObjectNameRole] = "objectName";
    roles[AppWindowDataDeviceInfoRole] = "deviceInfo";
    roles[AppWindowDataWidthRole] = "width";
    roles[AppWindowDataHeightRole] = "height";
    roles[AppWindowDataXRole] = "x";
    roles[AppWindowDataYRole] = "y";
    roles[AppWindowDataYRole] = "y";
    return roles;
}
