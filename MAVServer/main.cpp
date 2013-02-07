#include <iostream>
#include <conio.h>

#include <mavlink.h>

#include "MAVServer.h"
#include "SerialPort.h"

using namespace std;

MAVServer mavServ;

SerialPort serPort;

int main() {
	mavServ.async_run();
	//
	serPort.open("\\\\.\\COM1", 115200);
	//
	while(1) {
		/*mavlink_message_t msg;
		mavlink_status_t status;

		if (mavlink_parse_char(MAVLINK_COMM_0, serPort.readByte(), &msg, &status)) {
			cout << "Complete MAVLink Message received! ID: " << msg.msgid << " SYSTEM: " << msg.sysid << endl;
			//
			mavServ.sendMessage(msg);
		}*/

		mavlink_message_t msg;
		mavlink_heartbeat_t hrtbt;
		//
		hrtbt.autopilot = MAV_AUTOPILOT_INVALID;
		hrtbt.base_mode = 0;
		hrtbt.custom_mode = 0;
		hrtbt.system_status = MAV_STATE_ACTIVE;
		hrtbt.type = MAV_TYPE_GCS;
		//
		mavlink_msg_heartbeat_encode(0, 0, &msg, &hrtbt);
		//
		mavServ.sendMessage(msg);
		//
		Sleep(1000);

		if (_kbhit()) {
			exit(0);
		}
	}
}