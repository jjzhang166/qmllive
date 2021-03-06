/*
  Copyright (c) 2014, Pelagicore AG.
  All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QObject *parent) :
    QFileSystemModel(parent) ,
    m_dirSelectable(true)
{
}

void FileSystemModel::setAllowedTypesFilter(QStringList allowed)
{
    m_allowedTypes = allowed;
}

QStringList FileSystemModel::allowedTypesFilter() const
{
    return m_allowedTypes;
}

void FileSystemModel::setDirectoriesSelectable(bool enabled)
{
    m_dirSelectable = enabled;
}

bool FileSystemModel::directoriesSelectable() const
{
    return m_dirSelectable;
}

Qt::ItemFlags FileSystemModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags f = QFileSystemModel::flags(index);

    if (isDir(index)) {
        if (m_dirSelectable)
            return f;
        else
            return f & ~Qt::ItemIsSelectable;
    }

    QString path = filePath(index);

    foreach(QString type, m_allowedTypes) {
        if (path.contains(QRegExp(type, Qt::CaseInsensitive, QRegExp::Wildcard)))
            return f;
    }

    return f & ~Qt::ItemIsSelectable;
}


