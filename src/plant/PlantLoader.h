#ifndef PLANTLOADER_H
#define PLANTLOADER_H

class PlantInfo;
class GuiInterface_IF;
class PlantFactory_IF;


class PlantLoader
{
public:
   PlantLoader( GuiInterface_IF & guiinterface,
                PlantFactory_IF & plantFactory);

   void load( const PlantInfo & plantInfo);

private:
   GuiInterface_IF & m_guiInterface;
   PlantFactory_IF & m_plantFactory;

private:
   void loadPlantLayout(const PlantInfo& plantInfo);
   void loadLightpoints(const PlantInfo& plantInfo);
};

#endif // PLANTLOADER_H
