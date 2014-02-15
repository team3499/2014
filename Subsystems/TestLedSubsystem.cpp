#include "TestLedSubsystem.h"
#include "Robotmap.h"

TestLedSubsystem::TestLedSubsystem() : Subsystem("TestLedSubsystem") {
    digitalOutput = new DigitalOutput(TEST_LED_CHANNEL);
}

void TestLedSubsystem::On() {
    digitalOutput->Set(0);
}

void TestLedSubsystem::Off() {
    digitalOutput->Set(1);
}
