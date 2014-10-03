#ifndef MOCKLIGHTPANEL_H
#define MOCKLIGHTPANEL_H

#include "LightPanel.h"

class MockLightPanel : public LightPanel
{
   Q_OBJECT
public:
   typedef enum
   {
      ACTION_INVALID = 0,
      ACTION_PUSH_ON,
      ACTION_PUSH_OFF,
      ACTION_LEVEL_20,
      ACTION_LEVEL_80,
   } Action;

public:
   explicit MockLightPanel(QWidget *parent = 0);

public:
   /**
    * @brief select the (single) action that will be triggered
    *  as soon as \a exec is called. Once done, \a exec returns
    * @param action see type
    */
   void mockArmAction(Action action);

   // QDialog interface
public slots:
   /** non blocking version of exec function,
    * for test purpose */
   virtual int exec();

private:
   Action m_action;
};

#endif // MOCKLIGHTPANEL_H
