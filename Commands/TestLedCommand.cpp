#include "TestLedCommand.h"

TestLedCommand::TestLedCommand() {
    Requires(testLedSubsystem);
}

void TestLedCommand::Initialize() {
    testLedSubsystem->Set(!testLedSubsystem->Get());  // toggle LED
}

void TestLedCommand::Execute() {

}

bool TestLedCommand::IsFinished() {
    return true;
}

void TestLedCommand::End() {

}

void TestLedCommand::Interrupted() {
    End();
}
