// Copyright (C) 2023 Tasuku Suzuki <stasuku@gmail.com>
// SPDX-License-Identifier: BSD-3-Clause

#include "propertysync.h"

#include <QtQml/private/qqmlproperty_p.h>

PropertySync::PropertySync(QObject *parent)
    : QObject{parent}
{
    auto connectNotifySignal = [this]() {
        if (m_target && !m_propertyName.isEmpty()) {
            m_propertyB = QQmlProperty{m_target, m_propertyName};
            m_propertyB.connectNotifySignal(this, SLOT(update()));
            update();
        }
    };
    connect(this, &PropertySync::targetChanged, connectNotifySignal);
    connect(this, &PropertySync::propertyNameChanged, connectNotifySignal);
}

void PropertySync::setTarget(const QQmlProperty &property)
{
    m_propertyA = property;
    m_propertyA.connectNotifySignal(this, SLOT(update()));
}

void PropertySync::update()
{
    const auto *sender = QObject::sender();
    if (sender == m_propertyA.object()) {
        m_propertyB.write(m_propertyA.read());
    } else  {
        m_propertyA.write(m_propertyB.read());
    }
}
