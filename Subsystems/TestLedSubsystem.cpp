#include "TestLedSubsystem.h"
#include "Robotmap.h"

TestLedSubsystem::TestLedSubsystem() : Subsystem("TestLedSubsystem") {
    digitalOutput = new DigitalOutput(TEST_LED_CHANNEL);
    state         = true;
}

void TestLedSubsystem::Set(bool state) {
    this->state = state;

    if (state) { digitalOutput->Set(0); }
    else { digitalOutput->Set(1); }
}

bool TestLedSubsystem::Get() {
    return state;
}
