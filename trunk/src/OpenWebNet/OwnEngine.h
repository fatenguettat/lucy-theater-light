#ifndef OWNENGINE_H
#define OWNENGINE_H

#include <QObject>

class GuiInterface_IF;
class NetworkUi_IF;
class OwnLink;
class OwnFormatter;


class OwnEngine : public QObject
{
   Q_OBJECT
public:
   explicit OwnEngine( GuiInterface_IF & guiInterface, NetworkUi_IF & networkInterface,
                       OwnLink & ownLink, OwnFormatter & ownformatter,
                       QObject *parent = 0);
   ~OwnEngine() {}

private slots:
   void onLightPointRequestOn( int ownAddress);
   void onLightPointRequestOff( int ownAddress);

private:
   GuiInterface_IF  & m_guiInterface;
   NetworkUi_IF  & m_networkInterface;
   OwnLink  & m_ownLink;
   OwnFormatter  & m_ownFormatter;
};

#endif // OWNENGINE_H
