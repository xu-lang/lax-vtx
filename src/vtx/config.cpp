#include "Config.h"
#include "main.h"
#include "string.h"

#define CONF_POLL_INTERVAL 100;
Config g_config;

static inline void print_config(const Config& config)
{
    debug("\n"
          "version:        %d\n"
          "vtxMode:        %d\n"
          "currFreq:       %d\n"
          "channel:        %d\n"
          "freqMode:       %d\n"
          "pitMode:        %d\n"
          "pitmodeInRange: %d\n"
          "pitmodeOutRange:%d\n"
          "pitmodeFreq:    %d\n"
          "currPowerdB:    %d\n"
          "unlocked:       %d\n",
          config.version,
          config.vtxMode,
          config.currFreq,
          config.channel,
          config.freqMode,
          config.pitMode,
          config.pitmodeInRange,
          config.pitmodeOutRange,
          config.pitmodeFreq,
          config.currPowerdB,
          config.unlocked);
};

int Config::load(void)
{
    g_disk.read(0, (uint8_t *)this, sizeof(*this));

    if (this->version != versionEEPROM)
    {
        return loaddefault();
    }
    print_config(*this);
    return 0;
}

int Config::loaddefault(void)
{
    this->version = versionEEPROM;
    this->vtxMode = Protocol::BUTTON;
    this->currFreq = 5800;
    this->channel = 27;      // F4
    this->freqMode = 0;
    this->pitMode = 0;
    this->pitmodeInRange = 0;
    this->pitmodeOutRange = 0;
    this->pitmodeFreq = 5584;
    this->currPowerdB = 14;
    this->unlocked = 1;
    return 0;
}

int Config::save(void)
{
    Config tmp;
    tmp.load();
    if (memcmp(&tmp, this, sizeof(tmp)) == 0)
        return 0;
    g_disk.write(0, (uint8_t *)this, sizeof(*this));
    print_config(*this);
    return 0;
}
