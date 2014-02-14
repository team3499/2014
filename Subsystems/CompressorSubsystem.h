#ifndef __COMPRESSOR_SUBSYSTEM_H__
#define __COMPRESSOR_SUBSYSTEM_H__

#include "Commands/Subsystem.h"
#include "WPILib.h"

class CompressorSubsystem : public Subsystem {

  private:
    Compressor * compressor;

  public:
    CompressorSubsystem();

    void Start();
    void Stop();
    bool IsEnabled();
    bool IsCharged();
    bool NeedsAir();
};

#endif /* __COMPRESSOR_SUBSYSTEM_H__ */
