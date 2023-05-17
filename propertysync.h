// Copyright (C) 2023 Tasuku Suzuki <stasuku@gmail.com>
// SPDX-License-Identifier: BSD-3-Clause

#ifndef PROPERTYSYNC_H
#define PROPERTYSYNC_H

#include <QtCore/QObject>
#include <QtQml/qqml.h>
#include <QtQml/private/qqmlpropertyvalueinterceptor_p.h>
#include <QtQml/QQmlProperty>

class PropertySync : public QObject, public QQmlPropertyValueInterceptor
{
    Q_OBJECT
    QML_ELEMENT
    Q_INTERFACES(QQmlPropertyValueInterceptor)
    Q_PROPERTY(QObject *target MEMBER m_target NOTIFY targetChanged)
    Q_PROPERTY(QString propertyName MEMBER m_propertyName NOTIFY propertyNameChanged)

public:
    explicit PropertySync(QObject *parent = nullptr);

    void setTarget(const QQmlProperty &property) override;
    void write(const QVariant &value) override;

signals:
    void targetChanged();
    void propertyNameChanged();

private slots:
    void update();

private:
    bool m_updating = false;
    QObject *m_target = nullptr;
    QString m_propertyName;
    QQmlProperty m_propertyA;
    QQmlProperty m_propertyB;
};

#endif // PROPERTYSYNC_H
