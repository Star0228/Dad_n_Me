//
// Created by 16579 on 2024/7/9.
//

#ifndef DAD_N_ME_RESOURCEMANAGER_H
#define DAD_N_ME_RESOURCEMANAGER_H

#include <QWidget>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QImage>
#include <QDebug>
#include <QString>
#include <cmath>
#include <QHash>
#include <QKeyEvent>


class ResourceManager {
public:
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }

    QImage getImage(const QString& path) {
        if (!imageCache.contains(path)) {
            QImage image(path);
            if (image.isNull()) {
                qDebug() << "Failed to load image:" << path;
            } else {
                imageCache[path] = image;
            }
        }
        return imageCache.value(path);
    }

private:
    ResourceManager() {}
    ~ResourceManager() = default;

    QHash<QString, QImage> imageCache;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
};

#endif //DAD_N_ME_RESOURCEMANAGER_H
