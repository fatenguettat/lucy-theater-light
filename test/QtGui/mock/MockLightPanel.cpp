#include "MockLightPanel.h"

MockLightPanel::MockLightPanel(QWidget *parent) :
   LightPanel(parent),
   m_action(ACTION_INVALID)
{
}

void MockLightPanel::mockArmAction(MockLightPanel::Action action)
{
   m_action = action;
}


int MockLightPanel::exec()
{
   switch (m_action)
   {
   case ACTION_PUSH_ON:
      emit requestTurnOn();
      break;

   case ACTION_PUSH_OFF:
      emit requestTurnOff();
      break;

   case ACTION_LEVEL_20:
      emit requestSetLevel(own::LEVEL_20);
      break;

   case ACTION_LEVEL_80:
      emit requestSetLevel(own::LEVEL_80);
      break;

   default:
   case ACTION_INVALID:
      break;
   }

   return 0;
}

