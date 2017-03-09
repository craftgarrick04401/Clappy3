#include "Robot.h"

std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<GearPCM> Robot::gearPCM;
std::shared_ptr<GearArm> Robot::gearArm;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<Climber> Robot::climber;

void Robot::RobotInit() {
	RobotMap::init();


	gearCam = CameraServer::GetInstance()->StartAutomaticCapture(0);
	gearCam.SetResolution(640, 480);
	frc::Wait(1);
	backCam = CameraServer::GetInstance()->StartAutomaticCapture(1);
	backCam.SetResolution(640, 480);
	frc::Wait(1);

    driveTrain.reset(new DriveTrain());
    gearPCM.reset(new GearPCM());
    gearArm.reset(new GearArm());
    climber.reset(new Climber());
	oi.reset(new OI());

	autonomousCommand.reset(new AutonomousCommand());

  }

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {

	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();

	driveTrain->SetDirection(Direction::FORWARD);


}

void Robot::TeleopPeriodic() {

	Scheduler::GetInstance()->Run();

	SmartDashboard::PutString("Robot Direction", driveTrain->GetDirectionS());
	SmartDashboard::PutString("GearPCM Status", gearPCM->GetPCMStatusS());
	SmartDashboard::PutNumber("Encoder Position", gearArm->GetDegreesD());
	SmartDashboard::PutBoolean("Limit Switch", gearArm->GetHomeSwitch());
	SmartDashboard::PutString("GearArm Position", gearArm->GetTargetPositionS());

}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);

