#ifndef SETTINGSUNTIL_H
#define SETTINGSUNTIL_H

#include <QSettings>
#include <QString>
#include <QVariant>

#define SGROUP_WINDOW_GEOMETRY "WindowGeometry"
#define SGROUP_PLAYLIST "Playlist"
#define SGROUP_PLAYER "Player"

#define SKEY_WINDOW_POS "WindowPos"
#define SKEY_WINDOW_SIZE "WindowSize"
#define SKEY_CURR_PLAYLIST_ITEM "CurrPlaylistItem"
#define SKEY_PLAYER_POS "PlayerPosition"
#define SKEY_IS_PLAYER_PAUSED "IsPlayerPaused"

void saveParameter(const QString &key, const QVariant &value,
                   const QString &group);
QVariant loadParameter(const QString &key,  const QString &group,
                       const QVariant &defaultValue);

#endif // SETTINGSUNTIL_H
