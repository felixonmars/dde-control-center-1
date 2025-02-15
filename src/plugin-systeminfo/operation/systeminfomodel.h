//SPDX-FileCopyrightText: 2018 - 2023 UnionTech Software Technology Co., Ltd.
//
//SPDX-License-Identifier: GPL-3.0-or-later
#ifndef SYSTEMINFOMODEL_H
#define SYSTEMINFOMODEL_H

#include <QObject>

#include "include/interface/namespace.h"
#include "src/plugin-systeminfo/window/utils.h"

namespace DCC_NAMESPACE{

enum ActiveState {
    Unknown = -1,  //未知
    Unauthorized = 0,  //未授权
    Authorized,  //已授权
    AuthorizedLapse,  //授权失效
    TrialAuthorized, //试用期已授权
    TrialExpired //试用期已过期
};

// !!! 不要用C++11的前置声明枚举类型，这里lupdate命令有个bug．具体见
// https://stackoverflow.com/questions/6504902/lupdate-error-qualifying-with-unknown-namespace-class

class SystemInfoModel : public QObject
{
    Q_OBJECT
public:
    explicit SystemInfoModel(QObject *parent = nullptr);

    QString productName() const { return m_productName;}
    QString versionNumber() const { return m_versionNumber;}
    QString version() const { return m_version;}
    QString type() const { return m_type;}
    QString processor() const { return m_processor;}
    QString memory() const { return m_memory;}
    QString kernel() const { return m_kernel;}
    QString hostName() const { return  m_hostName;}

    inline ActiveState licenseState() const { return m_licenseState; }

Q_SIGNALS:
    void productNameChanged(const QString& version);
    void versionNumberChanged(const QString& version);
    void versionChanged(const QString& version);
    void typeChanged(const QString& type);
    void processorChanged(const QString& processor);
    void memoryChanged(const QString& memory);
    void kernelChanged(const QString& kernel);
    void licenseStateChanged(ActiveState state);
    void hostNameChanged(const QString& hostName);
    void setHostNameError(const QString& error);

public Q_SLOTS:
    void setProductName(const QString& name);
    void setVersionNumber(const QString& number);
    void setVersion(const QString& version);
    void setType(qlonglong type);
    void setProcessor(const QString& processor);
    void setMemory(qulonglong totalMemory, qulonglong installedMemory);
    void setKernel(const QString &kernel);
    void setLicenseState(DCC_NAMESPACE::ActiveState state);
    void setHostName(const QString& hostName);

private:
    QString m_version;
    QString m_productName;
    QString m_versionNumber;
    QString m_type;
    QString m_processor;
    QString m_memory;
    QString m_kernel;
    QString m_hostName;
    DCC_NAMESPACE::ActiveState m_licenseState;
};

}
Q_DECLARE_METATYPE(DCC_NAMESPACE::ActiveState);
#endif // SYSTEMINFOMODEL_H
