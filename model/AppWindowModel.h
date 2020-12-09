/**
 * @file AppWindowData.h
 * @author Daniel Matthes
 * @date 09.12.2020
 * @brief Application window data model for application window list
 */
#ifndef APPWINDOWMODEL_H
#define APPWINDOWMODEL_H

#include <QAbstractListModel>
#include <model/AppWindowData.h>

/**
 * @class Application window data model
 *
 * @brief List model for application window data item lists
 *
 * Derived from QAbstractListModel
 */
class AppWindowModel : public QAbstractListModel {
Q_OBJECT
public:
    /**
     * @brief The enumeration of the share data roles
     */
     enum AppWindowDataRoles {
         AppWindowDataTitleRole = Qt::UserRole + 1,     /// application title role
         AppWindowDataObjectNameRole,                   /// application object name role
         AppWindowDataDeviceInfoRole,                   /// application device info role
         AppWindowDataWidthRole,                        /// application width role
         AppWindowDataHeightRole,                       /// application height role
         AppWindowDataXRole,                            /// application x offset role
         AppWindowDataYRole                             /// application y offset role
     };

    /**
     * @name implementation of virtual functions of parent class QAbstractListModel
     */
    ///@{
    /**
     * @brief Get number of rows in list model
     * @param parent - model index
     * @return number of rows in list model
     */
    int rowCount(const QModelIndex &parent) const override;

    /**
     * @brief Get data of given role at given index
     * @param index - model index
     * @param role - ShareDataRole
     * @return
     */
    QVariant data(const QModelIndex &index, int role) const override;
    ///@}

    /**
     * @brief Add new application window to list
     * @param appWindowData - app window Item
     */
    void addAppWindowData(const AppWindowData &appWindowData);

    protected:
    /**
     * @name implementation of virtual functions of parent class QAbstractListModel
     */
    ///@{
    /**
     * @brief Get names of list model roles
     * @return roleName
     */
    QHash<int, QByteArray> roleNames() const override;
    ///@}

private:
    QList<AppWindowData> m_listAppWindowData;               ///< application window data list
};


#endif //APPWINDOWMODEL_H
