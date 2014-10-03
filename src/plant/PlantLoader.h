#ifndef PLANTLOADER_H
#define PLANTLOADER_H

#include <QObject>

class PlantInfo;
class GuiInterface_IF;
class PlantFactory_IF;
class OwnEngine;

/**
 * @brief The PlantLoader class has the responsability to pass the
 * configuration (loaded into an instance of \a PlantInfo) to the GUI.
 *
 * An engine is created that links plant to GUI.
 */
class PlantLoader :public QObject
{
   Q_OBJECT
public:
   PlantLoader(QObject *parent = NULL);

   ~PlantLoader();

   /**
    * @brief fill engine and GUI with data relative to the plant
    * @param plantInfo holds all info about plant
    * @param guiInterface is target GUI
    * @param ownEngine is target engine
    */
   void load(const PlantInfo & plantInfo,
              GuiInterface_IF *guiInterface,
              OwnEngine *ownEngine);

   /**
    * @brief clean data into GUI and engine, without de-allocating them.
    */
   void unload();

signals:
   /** with param 'true', notifies that a plant has been
    * succesfully loaded; with param 'false', the plant has
    * been unloaded or load has failed. */
   void plantLoaded(bool);

private:
   GuiInterface_IF *m_guiInterface;
   OwnEngine *m_ownEngine;

private:
   void loadPlantLayout(const PlantInfo& plantInfo);
   void loadLightpoints(const PlantInfo& plantInfo);
};

#endif // PLANTLOADER_H
