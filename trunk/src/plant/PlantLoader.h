#ifndef PLANTLOADER_H
#define PLANTLOADER_H

class PlantInfo;
class GuiInterface_IF;


class PlantLoader
{
public:
   PlantLoader( GuiInterface_IF & guiinterface);

   void load( const PlantInfo & plantInfo);

private:
   GuiInterface_IF & m_guiInterface;

private:
   void loadPlantLayout(const PlantInfo& plantInfo);
   void loadLightpoints(const PlantInfo& plantInfo);
};

#endif // PLANTLOADER_H
