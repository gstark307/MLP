#pragma once
#include <Arduino.h>
#include "CommandParameter.h"

namespace MLP
{
  struct CommandCallback 
  {
    const prog_char *m_strCommand;
    void (*m_Callback)(CommandParameter &rParameters);
  };

  class CommandDispatcherBase
  {
    // Array of up to m_uMaxCommands we can match & dispatch. 
    CommandCallback *const m_pCommands;
    const uint8_t m_uMaxCommands;
    uint8_t m_uLastCommand;

    // Handler called (if not null) when no command matches. 
    void (*m_fnDefaultHandler)();

  protected:
    CommandDispatcherBase(CommandCallback *pCallbackBuffer, uint8_t uCallbackBufferLength);

  public:
    bool AddCommand(const __FlashStringHelper *pCommand, void(*CallbackFunction)(CommandParameter &rParameters));
    void SetDefaultHandler(void(*CallbackFunction)());
    void ClearCommands();

    void DispatchCommand(char *pchMessage, Print& rSource) const;

  protected:
    enum EConstants { NO_MATCH = 0 };
    uint8_t MatchCommand(const prog_char *pchCommand, const char *pchTest) const;
  };
}