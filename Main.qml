// Copyright (C) 2023 Tasuku Suzuki <stasuku@gmail.com>
// SPDX-License-Identifier: BSD-3-Clause

import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import PropertySync

Window {
    width: 300
    height: 200
    visible: true
    title: qsTr("Sync property values")

    ColumnLayout {
        anchors.fill: parent

        TabBar {
            id: bar
            width: parent.width
            TabButton {
                text: qsTr("Controls")
            }
            TabButton {
                text: qsTr("API call")
            }
            TabButton {
                text: qsTr("Delegate")
            }
        }

        StackLayout {
            width: parent.width
            currentIndex: bar.currentIndex
            Item {
                RowLayout {
                    anchors.fill: parent
                    Slider {
                        id: slider
                        to: 99
//                        value: spinbox.value
                    }
                    SpinBox {
                        id: spinbox
//                        value: slider.value
                        PropertySync on value {
                            target: slider
                            propertyName: 'value'
                        }
                    }
                }
            }
            Item {
                QtObject {
                    id: api
                    property bool loading: false
                }

                ColumnLayout {
                    anchors.fill: parent
                    Switch {
                        text: 'loading: ' + api.loading
                        PropertySync on checked {
                            target: api
                            propertyName: 'loading'
                        }
                    }
                    Button {
                        text: 'Toggle'
                        onClicked: api.loading = !api.loading
                    }
                }
            }
            ListView {
                model: ListModel {
                    ListElement {
                        name: "Hello"
                    }
                    ListElement {
                        name: "World"
                    }
                }
                delegate: RowLayout {
                    width: ListView.view.width
                    height: 40
                    Text {
                        Layout.fillWidth: true
                        Layout.preferredWidth: 1
                        text: model.name
                    }
                    TextField {
                        Layout.fillWidth: true
                        Layout.preferredWidth: 1
                        PropertySync on text {
                            target: model
                            propertyName: "name"
                        }
                    }
                }
            }
        }
    }
}
