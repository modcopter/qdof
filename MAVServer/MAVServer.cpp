#include "MAVServer.h"

#include <string>
#include <mavlink.h>
#include <json/json.h>

std::string MAVServer::getMavlinkMessageName(mavlink_message_t msg) { 
	switch (msg.msgid) {
	case 0: 
		return "HEARTBEAT";
	case 1: 
		return "SYS_STATUS";
	case 2: 
		return "SYSTEM_TIME";
	case 4: 
		return "PING";
	case 5: 
		return "CHANGE_OPERATOR_CONTROL";
	case 6: 
		return "CHANGE_OPERATOR_CONTROL_ACK";
	case 7: 
		return "AUTH_KEY";
	case 11: 
		return "SET_MODE";
	case 21: 
		return "PARAM_REQUEST_LIST";
	case 20: 
		return "PARAM_REQUEST_READ";
	case 23: 
		return "PARAM_SET";
	case 22: 
		return "PARAM_VALUE";
	case 25: 
		return "GPS_STATUS";
	case 24: 
		return "GPS_RAW_INT";
	case 27: 
		return "RAW_IMU";
	case 26: 
		return "SCALED_IMU";
	case 29: 
		return "SCALED_PRESSURE";
	case 28: 
		return "RAW_PRESSURE";
	case 31: 
		return "ATTITUDE_QUATERNION";
	case 30: 
		return "ATTITUDE";
	case 34: 
		return "RC_CHANNELS_SCALED";
	case 35: 
		return "RC_CHANNELS_RAW";
	case 32: 
		return "LOCAL_POSITION_NED";
	case 33: 
		return "GLOBAL_POSITION_INT";
	case 38: 
		return "MISSION_WRITE_PARTIAL_LIST";
	case 39: 
		return "MISSION_ITEM";
	case 36: 
		return "SERVO_OUTPUT_RAW";
	case 37: 
		return "MISSION_REQUEST_PARTIAL_LIST";
	case 42: 
		return "MISSION_CURRENT";
	case 43: 
		return "MISSION_REQUEST_LIST";
	case 40: 
		return "MISSION_REQUEST";
	case 41: 
		return "MISSION_SET_CURRENT";
	case 46: 
		return "MISSION_ITEM_REACHED";
	case 47: 
		return "MISSION_ACK";
	case 44: 
		return "MISSION_COUNT";
	case 45: 
		return "MISSION_CLEAR_ALL";
	case 51: 
		return "LOCAL_POSITION_SETPOINT";
	case 50: 
		return "SET_LOCAL_POSITION_SETPOINT";
	case 49: 
		return "GPS_GLOBAL_ORIGIN";
	case 48: 
		return "SET_GPS_GLOBAL_ORIGIN";
	case 55: 
		return "SAFETY_ALLOWED_AREA";
	case 54: 
		return "SAFETY_SET_ALLOWED_AREA";
	case 53: 
		return "SET_GLOBAL_POSITION_SETPOINT_INT";
	case 52: 
		return "GLOBAL_POSITION_SETPOINT_INT";
	case 59: 
		return "ROLL_PITCH_YAW_SPEED_THRUST_SETPOINT";
	case 58: 
		return "ROLL_PITCH_YAW_THRUST_SETPOINT";
	case 57: 
		return "SET_ROLL_PITCH_YAW_SPEED_THRUST";
	case 56: 
		return "SET_ROLL_PITCH_YAW_THRUST";
	case 62: 
		return "NAV_CONTROLLER_OUTPUT";
	case 61: 
		return "SET_QUAD_SWARM_ROLL_PITCH_YAW_THRUST";
	case 60: 
		return "SET_QUAD_MOTORS_SETPOINT";
	case 69: 
		return "MANUAL_CONTROL";
	case 70: 
		return "RC_CHANNELS_OVERRIDE";
	case 64: 
		return "STATE_CORRECTION";
	case 66: 
		return "REQUEST_DATA_STREAM";
	case 67: 
		return "DATA_STREAM";
	case 76: 
		return "COMMAND_LONG";
	case 77: 
		return "COMMAND_ACK";
	case 74: 
		return "VFR_HUD";
	case 92: 
		return "HIL_RC_INPUTS_RAW";
	case 89: 
		return "LOCAL_POSITION_NED_SYSTEM_GLOBAL_OFFSET";
	case 91: 
		return "HIL_CONTROLS";
	case 90: 
		return "HIL_STATE";
	case 102: 
		return "VISION_POSITION_ESTIMATE";
	case 103: 
		return "VISION_SPEED_ESTIMATE";
	case 100: 
		return "OPTICAL_FLOW";
	case 101: 
		return "GLOBAL_VISION_POSITION_ESTIMATE";
	case 104: 
		return "VICON_POSITION_ESTIMATE";
	case 254: 
		return "DEBUG";
	case 252: 
		return "NAMED_VALUE_INT";
	case 253: 
		return "STATUSTEXT";
	case 250: 
		return "DEBUG_VECT";
	case 251: 
		return "NAMED_VALUE_FLOAT";
	case 249: 
		return "MEMORY_VECT";
	default: 
		return "UNDEFINED";

	}
}

Json::Value MAVServer::getMavlinkParams(mavlink_message_t msg) { 
	Json::Value content;
	switch (msg.msgid) {
	case 0: {	//HEARTBEAT
		content["type"] = mavlink_msg_heartbeat_get_type(&msg);
		content["autopilot"] = mavlink_msg_heartbeat_get_autopilot(&msg);
		content["base_mode"] = mavlink_msg_heartbeat_get_base_mode(&msg);
		content["custom_mode"] = mavlink_msg_heartbeat_get_custom_mode(&msg);
		content["system_status"] = mavlink_msg_heartbeat_get_system_status(&msg);
		content["mavlink_version"] = mavlink_msg_heartbeat_get_mavlink_version(&msg);
		break;
		}

	case 1: {	//SYS_STATUS
		content["onboard_control_sensors_present"] = mavlink_msg_sys_status_get_onboard_control_sensors_present(&msg);
		content["onboard_control_sensors_enabled"] = mavlink_msg_sys_status_get_onboard_control_sensors_enabled(&msg);
		content["onboard_control_sensors_health"] = mavlink_msg_sys_status_get_onboard_control_sensors_health(&msg);
		content["load"] = mavlink_msg_sys_status_get_load(&msg);
		content["voltage_battery"] = mavlink_msg_sys_status_get_voltage_battery(&msg);
		content["current_battery"] = mavlink_msg_sys_status_get_current_battery(&msg);
		content["battery_remaining"] = mavlink_msg_sys_status_get_battery_remaining(&msg);
		content["drop_rate_comm"] = mavlink_msg_sys_status_get_drop_rate_comm(&msg);
		content["errors_comm"] = mavlink_msg_sys_status_get_errors_comm(&msg);
		content["errors_count1"] = mavlink_msg_sys_status_get_errors_count1(&msg);
		content["errors_count2"] = mavlink_msg_sys_status_get_errors_count2(&msg);
		content["errors_count3"] = mavlink_msg_sys_status_get_errors_count3(&msg);
		content["errors_count4"] = mavlink_msg_sys_status_get_errors_count4(&msg);
		break;
		}

	case 2: {	//SYSTEM_TIME
		content["time_unix_usec"] = mavlink_msg_system_time_get_time_unix_usec(&msg);
		content["time_boot_ms"] = mavlink_msg_system_time_get_time_boot_ms(&msg);
		break;
		}

	case 4: {	//PING
		content["time_usec"] = mavlink_msg_ping_get_time_usec(&msg);
		content["seq"] = mavlink_msg_ping_get_seq(&msg);
		content["target_system"] = mavlink_msg_ping_get_target_system(&msg);
		content["target_component"] = mavlink_msg_ping_get_target_component(&msg);
		break;
		}

	case 5: {	//CHANGE_OPERATOR_CONTROL
		content["target_system"] = mavlink_msg_change_operator_control_get_target_system(&msg);
		content["control_request"] = mavlink_msg_change_operator_control_get_control_request(&msg);
		content["version"] = mavlink_msg_change_operator_control_get_version(&msg);

		char arr_passkey[25]; mavlink_msg_change_operator_control_get_passkey(&msg, arr_passkey); 
		content["passkey"] = std::string(arr_passkey, 25);

		break;
		}

	case 6: {	//CHANGE_OPERATOR_CONTROL_ACK
		content["gcs_system_id"] = mavlink_msg_change_operator_control_ack_get_gcs_system_id(&msg);
		content["control_request"] = mavlink_msg_change_operator_control_ack_get_control_request(&msg);
		content["ack"] = mavlink_msg_change_operator_control_ack_get_ack(&msg);
		break;
		}

	case 7: {	//AUTH_KEY

		char arr_key[32]; mavlink_msg_auth_key_get_key(&msg, arr_key); 
		content["key"] = std::string(arr_key, 32);

		break;
		}

	case 11: {	//SET_MODE
		content["target_system"] = mavlink_msg_set_mode_get_target_system(&msg);
		content["base_mode"] = mavlink_msg_set_mode_get_base_mode(&msg);
		content["custom_mode"] = mavlink_msg_set_mode_get_custom_mode(&msg);
		break;
		}

	case 20: {	//PARAM_REQUEST_READ
		content["target_system"] = mavlink_msg_param_request_read_get_target_system(&msg);
		content["target_component"] = mavlink_msg_param_request_read_get_target_component(&msg);

		char arr_param_id[16]; mavlink_msg_param_request_read_get_param_id(&msg, arr_param_id); 
		content["param_id"] = std::string(arr_param_id, 16);

		content["param_index"] = mavlink_msg_param_request_read_get_param_index(&msg);
		break;
		}

	case 21: {	//PARAM_REQUEST_LIST
		content["target_system"] = mavlink_msg_param_request_list_get_target_system(&msg);
		content["target_component"] = mavlink_msg_param_request_list_get_target_component(&msg);
		break;
		}

	case 22: {	//PARAM_VALUE

		char arr_param_id[16]; mavlink_msg_param_value_get_param_id(&msg, arr_param_id); 
		content["param_id"] = std::string(arr_param_id, 16);

		content["param_value"] = mavlink_msg_param_value_get_param_value(&msg);
		content["param_type"] = mavlink_msg_param_value_get_param_type(&msg);
		content["param_count"] = mavlink_msg_param_value_get_param_count(&msg);
		content["param_index"] = mavlink_msg_param_value_get_param_index(&msg);
		break;
		}

	case 23: {	//PARAM_SET
		content["target_system"] = mavlink_msg_param_set_get_target_system(&msg);
		content["target_component"] = mavlink_msg_param_set_get_target_component(&msg);

		char arr_param_id[16]; mavlink_msg_param_set_get_param_id(&msg, arr_param_id); 
		content["param_id"] = std::string(arr_param_id, 16);

		content["param_value"] = mavlink_msg_param_set_get_param_value(&msg);
		content["param_type"] = mavlink_msg_param_set_get_param_type(&msg);
		break;
		}

	case 24: {	//GPS_RAW_INT
		content["time_usec"] = mavlink_msg_gps_raw_int_get_time_usec(&msg);
		content["fix_type"] = mavlink_msg_gps_raw_int_get_fix_type(&msg);
		content["lat"] = mavlink_msg_gps_raw_int_get_lat(&msg);
		content["lon"] = mavlink_msg_gps_raw_int_get_lon(&msg);
		content["alt"] = mavlink_msg_gps_raw_int_get_alt(&msg);
		content["eph"] = mavlink_msg_gps_raw_int_get_eph(&msg);
		content["epv"] = mavlink_msg_gps_raw_int_get_epv(&msg);
		content["vel"] = mavlink_msg_gps_raw_int_get_vel(&msg);
		content["cog"] = mavlink_msg_gps_raw_int_get_cog(&msg);
		content["satellites_visible"] = mavlink_msg_gps_raw_int_get_satellites_visible(&msg);
		break;
		}

	case 25: {	//GPS_STATUS
		content["satellites_visible"] = mavlink_msg_gps_status_get_satellites_visible(&msg);

		uint8_t arr_satellite_prn[20]; mavlink_msg_gps_status_get_satellite_prn(&msg, arr_satellite_prn); 
		content["satellite_prn"] = Json::Value(Json::arrayValue);

		for(uint8_t i : arr_satellite_prn) {
			content["satellite_prn"].append(i);
		}

		uint8_t arr_satellite_used[20]; mavlink_msg_gps_status_get_satellite_used(&msg, arr_satellite_used); 
		content["satellite_used"] = Json::Value(Json::arrayValue);

		for(uint8_t i : arr_satellite_used) {
			content["satellite_used"].append(i);
		}

		uint8_t arr_satellite_elevation[20]; mavlink_msg_gps_status_get_satellite_elevation(&msg, arr_satellite_elevation); 
		content["satellite_elevation"] = Json::Value(Json::arrayValue);

		for(uint8_t i : arr_satellite_elevation) {
			content["satellite_elevation"].append(i);
		}

		uint8_t arr_satellite_azimuth[20]; mavlink_msg_gps_status_get_satellite_azimuth(&msg, arr_satellite_azimuth); 
		content["satellite_azimuth"] = Json::Value(Json::arrayValue);

		for(uint8_t i : arr_satellite_azimuth) {
			content["satellite_azimuth"].append(i);
		}

		uint8_t arr_satellite_snr[20]; mavlink_msg_gps_status_get_satellite_snr(&msg, arr_satellite_snr); 
		content["satellite_snr"] = Json::Value(Json::arrayValue);

		for(uint8_t i : arr_satellite_snr) {
			content["satellite_snr"].append(i);
		}
		break;
		}

	case 26: {	//SCALED_IMU
		content["time_boot_ms"] = mavlink_msg_scaled_imu_get_time_boot_ms(&msg);
		content["xacc"] = mavlink_msg_scaled_imu_get_xacc(&msg);
		content["yacc"] = mavlink_msg_scaled_imu_get_yacc(&msg);
		content["zacc"] = mavlink_msg_scaled_imu_get_zacc(&msg);
		content["xgyro"] = mavlink_msg_scaled_imu_get_xgyro(&msg);
		content["ygyro"] = mavlink_msg_scaled_imu_get_ygyro(&msg);
		content["zgyro"] = mavlink_msg_scaled_imu_get_zgyro(&msg);
		content["xmag"] = mavlink_msg_scaled_imu_get_xmag(&msg);
		content["ymag"] = mavlink_msg_scaled_imu_get_ymag(&msg);
		content["zmag"] = mavlink_msg_scaled_imu_get_zmag(&msg);
		break;
		}

	case 27: {	//RAW_IMU
		content["time_usec"] = mavlink_msg_raw_imu_get_time_usec(&msg);
		content["xacc"] = mavlink_msg_raw_imu_get_xacc(&msg);
		content["yacc"] = mavlink_msg_raw_imu_get_yacc(&msg);
		content["zacc"] = mavlink_msg_raw_imu_get_zacc(&msg);
		content["xgyro"] = mavlink_msg_raw_imu_get_xgyro(&msg);
		content["ygyro"] = mavlink_msg_raw_imu_get_ygyro(&msg);
		content["zgyro"] = mavlink_msg_raw_imu_get_zgyro(&msg);
		content["xmag"] = mavlink_msg_raw_imu_get_xmag(&msg);
		content["ymag"] = mavlink_msg_raw_imu_get_ymag(&msg);
		content["zmag"] = mavlink_msg_raw_imu_get_zmag(&msg);
		break;
		}

	case 28: {	//RAW_PRESSURE
		content["time_usec"] = mavlink_msg_raw_pressure_get_time_usec(&msg);
		content["press_abs"] = mavlink_msg_raw_pressure_get_press_abs(&msg);
		content["press_diff1"] = mavlink_msg_raw_pressure_get_press_diff1(&msg);
		content["press_diff2"] = mavlink_msg_raw_pressure_get_press_diff2(&msg);
		content["temperature"] = mavlink_msg_raw_pressure_get_temperature(&msg);
		break;
		}

	case 29: {	//SCALED_PRESSURE
		content["time_boot_ms"] = mavlink_msg_scaled_pressure_get_time_boot_ms(&msg);
		content["press_abs"] = mavlink_msg_scaled_pressure_get_press_abs(&msg);
		content["press_diff"] = mavlink_msg_scaled_pressure_get_press_diff(&msg);
		content["temperature"] = mavlink_msg_scaled_pressure_get_temperature(&msg);
		break;
		}

	case 30: {	//ATTITUDE
		content["time_boot_ms"] = mavlink_msg_attitude_get_time_boot_ms(&msg);
		content["roll"] = mavlink_msg_attitude_get_roll(&msg);
		content["pitch"] = mavlink_msg_attitude_get_pitch(&msg);
		content["yaw"] = mavlink_msg_attitude_get_yaw(&msg);
		content["rollspeed"] = mavlink_msg_attitude_get_rollspeed(&msg);
		content["pitchspeed"] = mavlink_msg_attitude_get_pitchspeed(&msg);
		content["yawspeed"] = mavlink_msg_attitude_get_yawspeed(&msg);
		break;
		}

	case 31: {	//ATTITUDE_QUATERNION
		content["time_boot_ms"] = mavlink_msg_attitude_quaternion_get_time_boot_ms(&msg);
		content["q1"] = mavlink_msg_attitude_quaternion_get_q1(&msg);
		content["q2"] = mavlink_msg_attitude_quaternion_get_q2(&msg);
		content["q3"] = mavlink_msg_attitude_quaternion_get_q3(&msg);
		content["q4"] = mavlink_msg_attitude_quaternion_get_q4(&msg);
		content["rollspeed"] = mavlink_msg_attitude_quaternion_get_rollspeed(&msg);
		content["pitchspeed"] = mavlink_msg_attitude_quaternion_get_pitchspeed(&msg);
		content["yawspeed"] = mavlink_msg_attitude_quaternion_get_yawspeed(&msg);
		break;
		}

	case 32: {	//LOCAL_POSITION_NED
		content["time_boot_ms"] = mavlink_msg_local_position_ned_get_time_boot_ms(&msg);
		content["x"] = mavlink_msg_local_position_ned_get_x(&msg);
		content["y"] = mavlink_msg_local_position_ned_get_y(&msg);
		content["z"] = mavlink_msg_local_position_ned_get_z(&msg);
		content["vx"] = mavlink_msg_local_position_ned_get_vx(&msg);
		content["vy"] = mavlink_msg_local_position_ned_get_vy(&msg);
		content["vz"] = mavlink_msg_local_position_ned_get_vz(&msg);
		break;
		}

	case 33: {	//GLOBAL_POSITION_INT
		content["time_boot_ms"] = mavlink_msg_global_position_int_get_time_boot_ms(&msg);
		content["lat"] = mavlink_msg_global_position_int_get_lat(&msg);
		content["lon"] = mavlink_msg_global_position_int_get_lon(&msg);
		content["alt"] = mavlink_msg_global_position_int_get_alt(&msg);
		content["relative_alt"] = mavlink_msg_global_position_int_get_relative_alt(&msg);
		content["vx"] = mavlink_msg_global_position_int_get_vx(&msg);
		content["vy"] = mavlink_msg_global_position_int_get_vy(&msg);
		content["vz"] = mavlink_msg_global_position_int_get_vz(&msg);
		content["hdg"] = mavlink_msg_global_position_int_get_hdg(&msg);
		break;
		}

	case 34: {	//RC_CHANNELS_SCALED
		content["time_boot_ms"] = mavlink_msg_rc_channels_scaled_get_time_boot_ms(&msg);
		content["port"] = mavlink_msg_rc_channels_scaled_get_port(&msg);
		content["chan1_scaled"] = mavlink_msg_rc_channels_scaled_get_chan1_scaled(&msg);
		content["chan2_scaled"] = mavlink_msg_rc_channels_scaled_get_chan2_scaled(&msg);
		content["chan3_scaled"] = mavlink_msg_rc_channels_scaled_get_chan3_scaled(&msg);
		content["chan4_scaled"] = mavlink_msg_rc_channels_scaled_get_chan4_scaled(&msg);
		content["chan5_scaled"] = mavlink_msg_rc_channels_scaled_get_chan5_scaled(&msg);
		content["chan6_scaled"] = mavlink_msg_rc_channels_scaled_get_chan6_scaled(&msg);
		content["chan7_scaled"] = mavlink_msg_rc_channels_scaled_get_chan7_scaled(&msg);
		content["chan8_scaled"] = mavlink_msg_rc_channels_scaled_get_chan8_scaled(&msg);
		content["rssi"] = mavlink_msg_rc_channels_scaled_get_rssi(&msg);
		break;
		}

	case 35: {	//RC_CHANNELS_RAW
		content["time_boot_ms"] = mavlink_msg_rc_channels_raw_get_time_boot_ms(&msg);
		content["port"] = mavlink_msg_rc_channels_raw_get_port(&msg);
		content["chan1_raw"] = mavlink_msg_rc_channels_raw_get_chan1_raw(&msg);
		content["chan2_raw"] = mavlink_msg_rc_channels_raw_get_chan2_raw(&msg);
		content["chan3_raw"] = mavlink_msg_rc_channels_raw_get_chan3_raw(&msg);
		content["chan4_raw"] = mavlink_msg_rc_channels_raw_get_chan4_raw(&msg);
		content["chan5_raw"] = mavlink_msg_rc_channels_raw_get_chan5_raw(&msg);
		content["chan6_raw"] = mavlink_msg_rc_channels_raw_get_chan6_raw(&msg);
		content["chan7_raw"] = mavlink_msg_rc_channels_raw_get_chan7_raw(&msg);
		content["chan8_raw"] = mavlink_msg_rc_channels_raw_get_chan8_raw(&msg);
		content["rssi"] = mavlink_msg_rc_channels_raw_get_rssi(&msg);
		break;
		}

	case 36: {	//SERVO_OUTPUT_RAW
		content["time_usec"] = mavlink_msg_servo_output_raw_get_time_usec(&msg);
		content["port"] = mavlink_msg_servo_output_raw_get_port(&msg);
		content["servo1_raw"] = mavlink_msg_servo_output_raw_get_servo1_raw(&msg);
		content["servo2_raw"] = mavlink_msg_servo_output_raw_get_servo2_raw(&msg);
		content["servo3_raw"] = mavlink_msg_servo_output_raw_get_servo3_raw(&msg);
		content["servo4_raw"] = mavlink_msg_servo_output_raw_get_servo4_raw(&msg);
		content["servo5_raw"] = mavlink_msg_servo_output_raw_get_servo5_raw(&msg);
		content["servo6_raw"] = mavlink_msg_servo_output_raw_get_servo6_raw(&msg);
		content["servo7_raw"] = mavlink_msg_servo_output_raw_get_servo7_raw(&msg);
		content["servo8_raw"] = mavlink_msg_servo_output_raw_get_servo8_raw(&msg);
		break;
		}

	case 37: {	//MISSION_REQUEST_PARTIAL_LIST
		content["target_system"] = mavlink_msg_mission_request_partial_list_get_target_system(&msg);
		content["target_component"] = mavlink_msg_mission_request_partial_list_get_target_component(&msg);
		content["start_index"] = mavlink_msg_mission_request_partial_list_get_start_index(&msg);
		content["end_index"] = mavlink_msg_mission_request_partial_list_get_end_index(&msg);
		break;
		}

	case 38: {	//MISSION_WRITE_PARTIAL_LIST
		content["target_system"] = mavlink_msg_mission_write_partial_list_get_target_system(&msg);
		content["target_component"] = mavlink_msg_mission_write_partial_list_get_target_component(&msg);
		content["start_index"] = mavlink_msg_mission_write_partial_list_get_start_index(&msg);
		content["end_index"] = mavlink_msg_mission_write_partial_list_get_end_index(&msg);
		break;
		}

	case 39: {	//MISSION_ITEM
		content["target_system"] = mavlink_msg_mission_item_get_target_system(&msg);
		content["target_component"] = mavlink_msg_mission_item_get_target_component(&msg);
		content["seq"] = mavlink_msg_mission_item_get_seq(&msg);
		content["frame"] = mavlink_msg_mission_item_get_frame(&msg);
		content["command"] = mavlink_msg_mission_item_get_command(&msg);
		content["current"] = mavlink_msg_mission_item_get_current(&msg);
		content["autocontinue"] = mavlink_msg_mission_item_get_autocontinue(&msg);
		content["param1"] = mavlink_msg_mission_item_get_param1(&msg);
		content["param2"] = mavlink_msg_mission_item_get_param2(&msg);
		content["param3"] = mavlink_msg_mission_item_get_param3(&msg);
		content["param4"] = mavlink_msg_mission_item_get_param4(&msg);
		content["x"] = mavlink_msg_mission_item_get_x(&msg);
		content["y"] = mavlink_msg_mission_item_get_y(&msg);
		content["z"] = mavlink_msg_mission_item_get_z(&msg);
		break;
		}

	case 40: {	//MISSION_REQUEST
		content["target_system"] = mavlink_msg_mission_request_get_target_system(&msg);
		content["target_component"] = mavlink_msg_mission_request_get_target_component(&msg);
		content["seq"] = mavlink_msg_mission_request_get_seq(&msg);
		break;
		}

	case 41: {	//MISSION_SET_CURRENT
		content["target_system"] = mavlink_msg_mission_set_current_get_target_system(&msg);
		content["target_component"] = mavlink_msg_mission_set_current_get_target_component(&msg);
		content["seq"] = mavlink_msg_mission_set_current_get_seq(&msg);
		break;
		}

	case 42: {	//MISSION_CURRENT
		content["seq"] = mavlink_msg_mission_current_get_seq(&msg);
		break;
		}

	case 43: {	//MISSION_REQUEST_LIST
		content["target_system"] = mavlink_msg_mission_request_list_get_target_system(&msg);
		content["target_component"] = mavlink_msg_mission_request_list_get_target_component(&msg);
		break;
		}

	case 44: {	//MISSION_COUNT
		content["target_system"] = mavlink_msg_mission_count_get_target_system(&msg);
		content["target_component"] = mavlink_msg_mission_count_get_target_component(&msg);
		content["count"] = mavlink_msg_mission_count_get_count(&msg);
		break;
		}

	case 45: {	//MISSION_CLEAR_ALL
		content["target_system"] = mavlink_msg_mission_clear_all_get_target_system(&msg);
		content["target_component"] = mavlink_msg_mission_clear_all_get_target_component(&msg);
		break;
		}

	case 46: {	//MISSION_ITEM_REACHED
		content["seq"] = mavlink_msg_mission_item_reached_get_seq(&msg);
		break;
		}

	case 47: {	//MISSION_ACK
		content["target_system"] = mavlink_msg_mission_ack_get_target_system(&msg);
		content["target_component"] = mavlink_msg_mission_ack_get_target_component(&msg);
		content["type"] = mavlink_msg_mission_ack_get_type(&msg);
		break;
		}

	case 48: {	//SET_GPS_GLOBAL_ORIGIN
		content["target_system"] = mavlink_msg_set_gps_global_origin_get_target_system(&msg);
		content["latitude"] = mavlink_msg_set_gps_global_origin_get_latitude(&msg);
		content["longitude"] = mavlink_msg_set_gps_global_origin_get_longitude(&msg);
		content["altitude"] = mavlink_msg_set_gps_global_origin_get_altitude(&msg);
		break;
		}

	case 49: {	//GPS_GLOBAL_ORIGIN
		content["latitude"] = mavlink_msg_gps_global_origin_get_latitude(&msg);
		content["longitude"] = mavlink_msg_gps_global_origin_get_longitude(&msg);
		content["altitude"] = mavlink_msg_gps_global_origin_get_altitude(&msg);
		break;
		}

	case 50: {	//SET_LOCAL_POSITION_SETPOINT
		content["target_system"] = mavlink_msg_set_local_position_setpoint_get_target_system(&msg);
		content["target_component"] = mavlink_msg_set_local_position_setpoint_get_target_component(&msg);
		content["coordinate_frame"] = mavlink_msg_set_local_position_setpoint_get_coordinate_frame(&msg);
		content["x"] = mavlink_msg_set_local_position_setpoint_get_x(&msg);
		content["y"] = mavlink_msg_set_local_position_setpoint_get_y(&msg);
		content["z"] = mavlink_msg_set_local_position_setpoint_get_z(&msg);
		content["yaw"] = mavlink_msg_set_local_position_setpoint_get_yaw(&msg);
		break;
		}

	case 51: {	//LOCAL_POSITION_SETPOINT
		content["coordinate_frame"] = mavlink_msg_local_position_setpoint_get_coordinate_frame(&msg);
		content["x"] = mavlink_msg_local_position_setpoint_get_x(&msg);
		content["y"] = mavlink_msg_local_position_setpoint_get_y(&msg);
		content["z"] = mavlink_msg_local_position_setpoint_get_z(&msg);
		content["yaw"] = mavlink_msg_local_position_setpoint_get_yaw(&msg);
		break;
		}

	case 52: {	//GLOBAL_POSITION_SETPOINT_INT
		content["coordinate_frame"] = mavlink_msg_global_position_setpoint_int_get_coordinate_frame(&msg);
		content["latitude"] = mavlink_msg_global_position_setpoint_int_get_latitude(&msg);
		content["longitude"] = mavlink_msg_global_position_setpoint_int_get_longitude(&msg);
		content["altitude"] = mavlink_msg_global_position_setpoint_int_get_altitude(&msg);
		content["yaw"] = mavlink_msg_global_position_setpoint_int_get_yaw(&msg);
		break;
		}

	case 53: {	//SET_GLOBAL_POSITION_SETPOINT_INT
		content["coordinate_frame"] = mavlink_msg_set_global_position_setpoint_int_get_coordinate_frame(&msg);
		content["latitude"] = mavlink_msg_set_global_position_setpoint_int_get_latitude(&msg);
		content["longitude"] = mavlink_msg_set_global_position_setpoint_int_get_longitude(&msg);
		content["altitude"] = mavlink_msg_set_global_position_setpoint_int_get_altitude(&msg);
		content["yaw"] = mavlink_msg_set_global_position_setpoint_int_get_yaw(&msg);
		break;
		}

	case 54: {	//SAFETY_SET_ALLOWED_AREA
		content["target_system"] = mavlink_msg_safety_set_allowed_area_get_target_system(&msg);
		content["target_component"] = mavlink_msg_safety_set_allowed_area_get_target_component(&msg);
		content["frame"] = mavlink_msg_safety_set_allowed_area_get_frame(&msg);
		content["p1x"] = mavlink_msg_safety_set_allowed_area_get_p1x(&msg);
		content["p1y"] = mavlink_msg_safety_set_allowed_area_get_p1y(&msg);
		content["p1z"] = mavlink_msg_safety_set_allowed_area_get_p1z(&msg);
		content["p2x"] = mavlink_msg_safety_set_allowed_area_get_p2x(&msg);
		content["p2y"] = mavlink_msg_safety_set_allowed_area_get_p2y(&msg);
		content["p2z"] = mavlink_msg_safety_set_allowed_area_get_p2z(&msg);
		break;
		}

	case 55: {	//SAFETY_ALLOWED_AREA
		content["frame"] = mavlink_msg_safety_allowed_area_get_frame(&msg);
		content["p1x"] = mavlink_msg_safety_allowed_area_get_p1x(&msg);
		content["p1y"] = mavlink_msg_safety_allowed_area_get_p1y(&msg);
		content["p1z"] = mavlink_msg_safety_allowed_area_get_p1z(&msg);
		content["p2x"] = mavlink_msg_safety_allowed_area_get_p2x(&msg);
		content["p2y"] = mavlink_msg_safety_allowed_area_get_p2y(&msg);
		content["p2z"] = mavlink_msg_safety_allowed_area_get_p2z(&msg);
		break;
		}

	case 56: {	//SET_ROLL_PITCH_YAW_THRUST
		content["target_system"] = mavlink_msg_set_roll_pitch_yaw_thrust_get_target_system(&msg);
		content["target_component"] = mavlink_msg_set_roll_pitch_yaw_thrust_get_target_component(&msg);
		content["roll"] = mavlink_msg_set_roll_pitch_yaw_thrust_get_roll(&msg);
		content["pitch"] = mavlink_msg_set_roll_pitch_yaw_thrust_get_pitch(&msg);
		content["yaw"] = mavlink_msg_set_roll_pitch_yaw_thrust_get_yaw(&msg);
		content["thrust"] = mavlink_msg_set_roll_pitch_yaw_thrust_get_thrust(&msg);
		break;
		}

	case 57: {	//SET_ROLL_PITCH_YAW_SPEED_THRUST
		content["target_system"] = mavlink_msg_set_roll_pitch_yaw_speed_thrust_get_target_system(&msg);
		content["target_component"] = mavlink_msg_set_roll_pitch_yaw_speed_thrust_get_target_component(&msg);
		content["roll_speed"] = mavlink_msg_set_roll_pitch_yaw_speed_thrust_get_roll_speed(&msg);
		content["pitch_speed"] = mavlink_msg_set_roll_pitch_yaw_speed_thrust_get_pitch_speed(&msg);
		content["yaw_speed"] = mavlink_msg_set_roll_pitch_yaw_speed_thrust_get_yaw_speed(&msg);
		content["thrust"] = mavlink_msg_set_roll_pitch_yaw_speed_thrust_get_thrust(&msg);
		break;
		}

	case 58: {	//ROLL_PITCH_YAW_THRUST_SETPOINT
		content["time_boot_ms"] = mavlink_msg_roll_pitch_yaw_thrust_setpoint_get_time_boot_ms(&msg);
		content["roll"] = mavlink_msg_roll_pitch_yaw_thrust_setpoint_get_roll(&msg);
		content["pitch"] = mavlink_msg_roll_pitch_yaw_thrust_setpoint_get_pitch(&msg);
		content["yaw"] = mavlink_msg_roll_pitch_yaw_thrust_setpoint_get_yaw(&msg);
		content["thrust"] = mavlink_msg_roll_pitch_yaw_thrust_setpoint_get_thrust(&msg);
		break;
		}

	case 59: {	//ROLL_PITCH_YAW_SPEED_THRUST_SETPOINT
		content["time_boot_ms"] = mavlink_msg_roll_pitch_yaw_speed_thrust_setpoint_get_time_boot_ms(&msg);
		content["roll_speed"] = mavlink_msg_roll_pitch_yaw_speed_thrust_setpoint_get_roll_speed(&msg);
		content["pitch_speed"] = mavlink_msg_roll_pitch_yaw_speed_thrust_setpoint_get_pitch_speed(&msg);
		content["yaw_speed"] = mavlink_msg_roll_pitch_yaw_speed_thrust_setpoint_get_yaw_speed(&msg);
		content["thrust"] = mavlink_msg_roll_pitch_yaw_speed_thrust_setpoint_get_thrust(&msg);
		break;
		}

	case 60: {	//SET_QUAD_MOTORS_SETPOINT
		content["target_system"] = mavlink_msg_set_quad_motors_setpoint_get_target_system(&msg);
		content["motor_front_nw"] = mavlink_msg_set_quad_motors_setpoint_get_motor_front_nw(&msg);
		content["motor_right_ne"] = mavlink_msg_set_quad_motors_setpoint_get_motor_right_ne(&msg);
		content["motor_back_se"] = mavlink_msg_set_quad_motors_setpoint_get_motor_back_se(&msg);
		content["motor_left_sw"] = mavlink_msg_set_quad_motors_setpoint_get_motor_left_sw(&msg);
		break;
		}

	case 61: {	//SET_QUAD_SWARM_ROLL_PITCH_YAW_THRUST

		uint8_t arr_target_systems[6]; mavlink_msg_set_quad_swarm_roll_pitch_yaw_thrust_get_target_systems(&msg, arr_target_systems); 
		content["target_systems"] = Json::Value(Json::arrayValue);

		for(uint8_t i : arr_target_systems) {
			content["target_systems"].append(i);
		}

		int16_t arr_roll[6]; mavlink_msg_set_quad_swarm_roll_pitch_yaw_thrust_get_roll(&msg, arr_roll); 
		content["roll"] = Json::Value(Json::arrayValue);

		for(int16_t i : arr_roll) {
			content["roll"].append(i);
		}

		int16_t arr_pitch[6]; mavlink_msg_set_quad_swarm_roll_pitch_yaw_thrust_get_pitch(&msg, arr_pitch); 
		content["pitch"] = Json::Value(Json::arrayValue);

		for(int16_t i : arr_pitch) {
			content["pitch"].append(i);
		}

		int16_t arr_yaw[6]; mavlink_msg_set_quad_swarm_roll_pitch_yaw_thrust_get_yaw(&msg, arr_yaw); 
		content["yaw"] = Json::Value(Json::arrayValue);

		for(int16_t i : arr_yaw) {
			content["yaw"].append(i);
		}

		uint16_t arr_thrust[6]; mavlink_msg_set_quad_swarm_roll_pitch_yaw_thrust_get_thrust(&msg, arr_thrust); 
		content["thrust"] = Json::Value(Json::arrayValue);

		for(uint16_t i : arr_thrust) {
			content["thrust"].append(i);
		}
		break;
		}

	case 62: {	//NAV_CONTROLLER_OUTPUT
		content["nav_roll"] = mavlink_msg_nav_controller_output_get_nav_roll(&msg);
		content["nav_pitch"] = mavlink_msg_nav_controller_output_get_nav_pitch(&msg);
		content["nav_bearing"] = mavlink_msg_nav_controller_output_get_nav_bearing(&msg);
		content["target_bearing"] = mavlink_msg_nav_controller_output_get_target_bearing(&msg);
		content["wp_dist"] = mavlink_msg_nav_controller_output_get_wp_dist(&msg);
		content["alt_error"] = mavlink_msg_nav_controller_output_get_alt_error(&msg);
		content["aspd_error"] = mavlink_msg_nav_controller_output_get_aspd_error(&msg);
		content["xtrack_error"] = mavlink_msg_nav_controller_output_get_xtrack_error(&msg);
		break;
		}

	case 64: {	//STATE_CORRECTION
		content["xErr"] = mavlink_msg_state_correction_get_xErr(&msg);
		content["yErr"] = mavlink_msg_state_correction_get_yErr(&msg);
		content["zErr"] = mavlink_msg_state_correction_get_zErr(&msg);
		content["rollErr"] = mavlink_msg_state_correction_get_rollErr(&msg);
		content["pitchErr"] = mavlink_msg_state_correction_get_pitchErr(&msg);
		content["yawErr"] = mavlink_msg_state_correction_get_yawErr(&msg);
		content["vxErr"] = mavlink_msg_state_correction_get_vxErr(&msg);
		content["vyErr"] = mavlink_msg_state_correction_get_vyErr(&msg);
		content["vzErr"] = mavlink_msg_state_correction_get_vzErr(&msg);
		break;
		}

	case 66: {	//REQUEST_DATA_STREAM
		content["target_system"] = mavlink_msg_request_data_stream_get_target_system(&msg);
		content["target_component"] = mavlink_msg_request_data_stream_get_target_component(&msg);
		content["req_stream_id"] = mavlink_msg_request_data_stream_get_req_stream_id(&msg);
		content["req_message_rate"] = mavlink_msg_request_data_stream_get_req_message_rate(&msg);
		content["start_stop"] = mavlink_msg_request_data_stream_get_start_stop(&msg);
		break;
		}

	case 67: {	//DATA_STREAM
		content["stream_id"] = mavlink_msg_data_stream_get_stream_id(&msg);
		content["message_rate"] = mavlink_msg_data_stream_get_message_rate(&msg);
		content["on_off"] = mavlink_msg_data_stream_get_on_off(&msg);
		break;
		}

	case 69: {	//MANUAL_CONTROL
		content["target"] = mavlink_msg_manual_control_get_target(&msg);
		content["roll"] = mavlink_msg_manual_control_get_roll(&msg);
		content["pitch"] = mavlink_msg_manual_control_get_pitch(&msg);
		content["yaw"] = mavlink_msg_manual_control_get_yaw(&msg);
		content["thrust"] = mavlink_msg_manual_control_get_thrust(&msg);
		content["roll_manual"] = mavlink_msg_manual_control_get_roll_manual(&msg);
		content["pitch_manual"] = mavlink_msg_manual_control_get_pitch_manual(&msg);
		content["yaw_manual"] = mavlink_msg_manual_control_get_yaw_manual(&msg);
		content["thrust_manual"] = mavlink_msg_manual_control_get_thrust_manual(&msg);
		break;
		}

	case 70: {	//RC_CHANNELS_OVERRIDE
		content["target_system"] = mavlink_msg_rc_channels_override_get_target_system(&msg);
		content["target_component"] = mavlink_msg_rc_channels_override_get_target_component(&msg);
		content["chan1_raw"] = mavlink_msg_rc_channels_override_get_chan1_raw(&msg);
		content["chan2_raw"] = mavlink_msg_rc_channels_override_get_chan2_raw(&msg);
		content["chan3_raw"] = mavlink_msg_rc_channels_override_get_chan3_raw(&msg);
		content["chan4_raw"] = mavlink_msg_rc_channels_override_get_chan4_raw(&msg);
		content["chan5_raw"] = mavlink_msg_rc_channels_override_get_chan5_raw(&msg);
		content["chan6_raw"] = mavlink_msg_rc_channels_override_get_chan6_raw(&msg);
		content["chan7_raw"] = mavlink_msg_rc_channels_override_get_chan7_raw(&msg);
		content["chan8_raw"] = mavlink_msg_rc_channels_override_get_chan8_raw(&msg);
		break;
		}

	case 74: {	//VFR_HUD
		content["airspeed"] = mavlink_msg_vfr_hud_get_airspeed(&msg);
		content["groundspeed"] = mavlink_msg_vfr_hud_get_groundspeed(&msg);
		content["heading"] = mavlink_msg_vfr_hud_get_heading(&msg);
		content["throttle"] = mavlink_msg_vfr_hud_get_throttle(&msg);
		content["alt"] = mavlink_msg_vfr_hud_get_alt(&msg);
		content["climb"] = mavlink_msg_vfr_hud_get_climb(&msg);
		break;
		}

	case 76: {	//COMMAND_LONG
		content["target_system"] = mavlink_msg_command_long_get_target_system(&msg);
		content["target_component"] = mavlink_msg_command_long_get_target_component(&msg);
		content["command"] = mavlink_msg_command_long_get_command(&msg);
		content["confirmation"] = mavlink_msg_command_long_get_confirmation(&msg);
		content["param1"] = mavlink_msg_command_long_get_param1(&msg);
		content["param2"] = mavlink_msg_command_long_get_param2(&msg);
		content["param3"] = mavlink_msg_command_long_get_param3(&msg);
		content["param4"] = mavlink_msg_command_long_get_param4(&msg);
		content["param5"] = mavlink_msg_command_long_get_param5(&msg);
		content["param6"] = mavlink_msg_command_long_get_param6(&msg);
		content["param7"] = mavlink_msg_command_long_get_param7(&msg);
		break;
		}

	case 77: {	//COMMAND_ACK
		content["command"] = mavlink_msg_command_ack_get_command(&msg);
		content["result"] = mavlink_msg_command_ack_get_result(&msg);
		break;
		}

	case 89: {	//LOCAL_POSITION_NED_SYSTEM_GLOBAL_OFFSET
		content["time_boot_ms"] = mavlink_msg_local_position_ned_system_global_offset_get_time_boot_ms(&msg);
		content["x"] = mavlink_msg_local_position_ned_system_global_offset_get_x(&msg);
		content["y"] = mavlink_msg_local_position_ned_system_global_offset_get_y(&msg);
		content["z"] = mavlink_msg_local_position_ned_system_global_offset_get_z(&msg);
		content["roll"] = mavlink_msg_local_position_ned_system_global_offset_get_roll(&msg);
		content["pitch"] = mavlink_msg_local_position_ned_system_global_offset_get_pitch(&msg);
		content["yaw"] = mavlink_msg_local_position_ned_system_global_offset_get_yaw(&msg);
		break;
		}

	case 90: {	//HIL_STATE
		content["time_usec"] = mavlink_msg_hil_state_get_time_usec(&msg);
		content["roll"] = mavlink_msg_hil_state_get_roll(&msg);
		content["pitch"] = mavlink_msg_hil_state_get_pitch(&msg);
		content["yaw"] = mavlink_msg_hil_state_get_yaw(&msg);
		content["rollspeed"] = mavlink_msg_hil_state_get_rollspeed(&msg);
		content["pitchspeed"] = mavlink_msg_hil_state_get_pitchspeed(&msg);
		content["yawspeed"] = mavlink_msg_hil_state_get_yawspeed(&msg);
		content["lat"] = mavlink_msg_hil_state_get_lat(&msg);
		content["lon"] = mavlink_msg_hil_state_get_lon(&msg);
		content["alt"] = mavlink_msg_hil_state_get_alt(&msg);
		content["vx"] = mavlink_msg_hil_state_get_vx(&msg);
		content["vy"] = mavlink_msg_hil_state_get_vy(&msg);
		content["vz"] = mavlink_msg_hil_state_get_vz(&msg);
		content["xacc"] = mavlink_msg_hil_state_get_xacc(&msg);
		content["yacc"] = mavlink_msg_hil_state_get_yacc(&msg);
		content["zacc"] = mavlink_msg_hil_state_get_zacc(&msg);
		break;
		}

	case 91: {	//HIL_CONTROLS
		content["time_usec"] = mavlink_msg_hil_controls_get_time_usec(&msg);
		content["roll_ailerons"] = mavlink_msg_hil_controls_get_roll_ailerons(&msg);
		content["pitch_elevator"] = mavlink_msg_hil_controls_get_pitch_elevator(&msg);
		content["yaw_rudder"] = mavlink_msg_hil_controls_get_yaw_rudder(&msg);
		content["throttle"] = mavlink_msg_hil_controls_get_throttle(&msg);
		content["aux1"] = mavlink_msg_hil_controls_get_aux1(&msg);
		content["aux2"] = mavlink_msg_hil_controls_get_aux2(&msg);
		content["aux3"] = mavlink_msg_hil_controls_get_aux3(&msg);
		content["aux4"] = mavlink_msg_hil_controls_get_aux4(&msg);
		content["mode"] = mavlink_msg_hil_controls_get_mode(&msg);
		content["nav_mode"] = mavlink_msg_hil_controls_get_nav_mode(&msg);
		break;
		}

	case 92: {	//HIL_RC_INPUTS_RAW
		content["time_usec"] = mavlink_msg_hil_rc_inputs_raw_get_time_usec(&msg);
		content["chan1_raw"] = mavlink_msg_hil_rc_inputs_raw_get_chan1_raw(&msg);
		content["chan2_raw"] = mavlink_msg_hil_rc_inputs_raw_get_chan2_raw(&msg);
		content["chan3_raw"] = mavlink_msg_hil_rc_inputs_raw_get_chan3_raw(&msg);
		content["chan4_raw"] = mavlink_msg_hil_rc_inputs_raw_get_chan4_raw(&msg);
		content["chan5_raw"] = mavlink_msg_hil_rc_inputs_raw_get_chan5_raw(&msg);
		content["chan6_raw"] = mavlink_msg_hil_rc_inputs_raw_get_chan6_raw(&msg);
		content["chan7_raw"] = mavlink_msg_hil_rc_inputs_raw_get_chan7_raw(&msg);
		content["chan8_raw"] = mavlink_msg_hil_rc_inputs_raw_get_chan8_raw(&msg);
		content["chan9_raw"] = mavlink_msg_hil_rc_inputs_raw_get_chan9_raw(&msg);
		content["chan10_raw"] = mavlink_msg_hil_rc_inputs_raw_get_chan10_raw(&msg);
		content["chan11_raw"] = mavlink_msg_hil_rc_inputs_raw_get_chan11_raw(&msg);
		content["chan12_raw"] = mavlink_msg_hil_rc_inputs_raw_get_chan12_raw(&msg);
		content["rssi"] = mavlink_msg_hil_rc_inputs_raw_get_rssi(&msg);
		break;
		}

	case 100: {	//OPTICAL_FLOW
		content["time_usec"] = mavlink_msg_optical_flow_get_time_usec(&msg);
		content["sensor_id"] = mavlink_msg_optical_flow_get_sensor_id(&msg);
		content["flow_x"] = mavlink_msg_optical_flow_get_flow_x(&msg);
		content["flow_y"] = mavlink_msg_optical_flow_get_flow_y(&msg);
		content["flow_comp_m_x"] = mavlink_msg_optical_flow_get_flow_comp_m_x(&msg);
		content["flow_comp_m_y"] = mavlink_msg_optical_flow_get_flow_comp_m_y(&msg);
		content["quality"] = mavlink_msg_optical_flow_get_quality(&msg);
		content["ground_distance"] = mavlink_msg_optical_flow_get_ground_distance(&msg);
		break;
		}

	case 101: {	//GLOBAL_VISION_POSITION_ESTIMATE
		content["usec"] = mavlink_msg_global_vision_position_estimate_get_usec(&msg);
		content["x"] = mavlink_msg_global_vision_position_estimate_get_x(&msg);
		content["y"] = mavlink_msg_global_vision_position_estimate_get_y(&msg);
		content["z"] = mavlink_msg_global_vision_position_estimate_get_z(&msg);
		content["roll"] = mavlink_msg_global_vision_position_estimate_get_roll(&msg);
		content["pitch"] = mavlink_msg_global_vision_position_estimate_get_pitch(&msg);
		content["yaw"] = mavlink_msg_global_vision_position_estimate_get_yaw(&msg);
		break;
		}

	case 102: {	//VISION_POSITION_ESTIMATE
		content["usec"] = mavlink_msg_vision_position_estimate_get_usec(&msg);
		content["x"] = mavlink_msg_vision_position_estimate_get_x(&msg);
		content["y"] = mavlink_msg_vision_position_estimate_get_y(&msg);
		content["z"] = mavlink_msg_vision_position_estimate_get_z(&msg);
		content["roll"] = mavlink_msg_vision_position_estimate_get_roll(&msg);
		content["pitch"] = mavlink_msg_vision_position_estimate_get_pitch(&msg);
		content["yaw"] = mavlink_msg_vision_position_estimate_get_yaw(&msg);
		break;
		}

	case 103: {	//VISION_SPEED_ESTIMATE
		content["usec"] = mavlink_msg_vision_speed_estimate_get_usec(&msg);
		content["x"] = mavlink_msg_vision_speed_estimate_get_x(&msg);
		content["y"] = mavlink_msg_vision_speed_estimate_get_y(&msg);
		content["z"] = mavlink_msg_vision_speed_estimate_get_z(&msg);
		break;
		}

	case 104: {	//VICON_POSITION_ESTIMATE
		content["usec"] = mavlink_msg_vicon_position_estimate_get_usec(&msg);
		content["x"] = mavlink_msg_vicon_position_estimate_get_x(&msg);
		content["y"] = mavlink_msg_vicon_position_estimate_get_y(&msg);
		content["z"] = mavlink_msg_vicon_position_estimate_get_z(&msg);
		content["roll"] = mavlink_msg_vicon_position_estimate_get_roll(&msg);
		content["pitch"] = mavlink_msg_vicon_position_estimate_get_pitch(&msg);
		content["yaw"] = mavlink_msg_vicon_position_estimate_get_yaw(&msg);
		break;
		}

	case 249: {	//MEMORY_VECT
		content["address"] = mavlink_msg_memory_vect_get_address(&msg);
		content["ver"] = mavlink_msg_memory_vect_get_ver(&msg);
		content["type"] = mavlink_msg_memory_vect_get_type(&msg);
		
		int8_t arr_value[32]; mavlink_msg_memory_vect_get_value(&msg, arr_value);
		content["value"] = Json::Value(Json::arrayValue);

		for(int8_t i : arr_value) {
			content["value"].append(i);
		}

		break;
		}

	case 250: {	//DEBUG_VECT

		char arr_name[10]; mavlink_msg_debug_vect_get_name(&msg, arr_name); 
		content["name"] = std::string(arr_name, 10);

		content["time_usec"] = mavlink_msg_debug_vect_get_time_usec(&msg);
		content["x"] = mavlink_msg_debug_vect_get_x(&msg);
		content["y"] = mavlink_msg_debug_vect_get_y(&msg);
		content["z"] = mavlink_msg_debug_vect_get_z(&msg);
		break;
		}

	case 251: {	//NAMED_VALUE_FLOAT
		content["time_boot_ms"] = mavlink_msg_named_value_float_get_time_boot_ms(&msg);

		char arr_name[10]; mavlink_msg_named_value_float_get_name(&msg, arr_name); 
		content["name"] = std::string(arr_name, 10);

		content["value"] = mavlink_msg_named_value_float_get_value(&msg);
		break;
		}

	case 252: {	//NAMED_VALUE_INT
		content["time_boot_ms"] = mavlink_msg_named_value_int_get_time_boot_ms(&msg);

		char arr_name[10]; mavlink_msg_named_value_int_get_name(&msg, arr_name); 
		content["name"] = std::string(arr_name, 10);

		content["value"] = mavlink_msg_named_value_int_get_value(&msg);
		break;
		}

	case 253: {	//STATUSTEXT
		content["severity"] = mavlink_msg_statustext_get_severity(&msg);

		char arr_text[50]; mavlink_msg_statustext_get_text(&msg, arr_text); 
		content["text"] = std::string(arr_text, 50);

		break;
		}

	case 254: {	//DEBUG
		content["time_boot_ms"] = mavlink_msg_debug_get_time_boot_ms(&msg);
		content["ind"] = mavlink_msg_debug_get_ind(&msg);
		content["value"] = mavlink_msg_debug_get_value(&msg);
		break;
		}

	}
	return content;
}