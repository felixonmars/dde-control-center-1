//SPDX-FileCopyrightText: 2018 - 2023 UnionTech Software Technology Co., Ltd.
//
//SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "interface/namespace.h"

#include <QFuture>
#include <QObject>

class QPluginLoader;

namespace DCC_NAMESPACE {
class ModuleObject;
class PluginInterface;
class LayoutManager;
}

struct PluginData
{
    QString Follow;
    QString Location;
    DCC_NAMESPACE::ModuleObject *Module;
    DCC_NAMESPACE::PluginInterface *Plugin;
};

Q_DECLARE_METATYPE(PluginData)

namespace DCC_NAMESPACE
{
class PluginManager : public QObject
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = nullptr);
    void loadModules(ModuleObject *root, bool async = true);
    bool loadFinished() const;

public Q_SLOTS:
    void cancelLoad();

Q_SIGNALS:
    void loadedModule(const PluginData &data);
    void loadAllFinished();

private:
    ModuleObject *findModule(ModuleObject *module, const QString &name);
    void initModules(const PluginData &data);
    void insertChild(bool force);

    QList<PluginData> m_datas;      //cache for other plugin
    ModuleObject *m_rootModule;     //root module from MainWindow
    bool m_loadAllFinished;
    QFuture<PluginData> m_future;
};

} // namespace DCC_NAMESPACE
