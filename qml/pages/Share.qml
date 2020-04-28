/*
    A simple audio recording tool.
    Copyright (C) 2014  Corné Dorrestijn

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.TransferEngine 1.0
import QtMultimedia 5.0


Page {
    property string title
    property alias path: shareMethodList.source
    property alias filter: transferMethodsModel.filter

    id: sharePage

    SailfishTransferMethodsModel {
        id: transferMethodsModel
    }

    ShareMethodList {
        id: shareMethodList
        model: transferMethodsModel

        header: PageHeader {
            title: sharePage.title
        }
    }
}
