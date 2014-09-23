#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H

class OwnEngine;
class GuiInterface_IF;
class PlantInfo;
class QObject;
class ErrorNotifier_IF;


class PlantFactory
{
public:
   PlantFactory(GuiInterface_IF &guiInterface, ErrorNotifier_IF &errorNotifier);

   OwnEngine * buildOwnEngine(const PlantInfo &plantInfo);

private:
   GuiInterface_IF & m_guiInterface;
   ErrorNotifier_IF & m_errorLogger;

   /* reference hold to destory last built engine */
   QObject *parent;
};

#endif // PLANTFACTORY_H