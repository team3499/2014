#include "CompressorSubsystem.h"
#include "Robotmap.h"

CompressorSubsystem::CompressorSubsystem() : Subsystem("CompressorSubsystem") {
    compressor = new Compressor(COMPRESSOR_CHANNEL, PRESSURE_SWITCH_CHANNEL);
}

void CompressorSubsystem::Start() {
    compressor->Start();
}

void CompressorSubsystem::Stop() {
    compressor->Stop();
}

bool CompressorSubsystem::IsEnabled() {
    return compressor->Enabled();
}

bool CompressorSubsystem::IsCharged() {
    return compressor->GetPressureSwitchValue() != 0;
}

bool CompressorSubsystem::NeedsAir() {
    return !IsCharged();
}
